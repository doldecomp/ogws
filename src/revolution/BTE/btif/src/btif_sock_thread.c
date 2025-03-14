/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/************************************************************************************
 *
 *  Filename:      btif_sock_thread.c
 *
 *  Description:   socket select thread
 *
 *
 ***********************************************************************************/

#include <hardware/bluetooth.h>
#include <hardware/bt_sock.h>

//bta_jv_co_rfc_data
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <ctype.h>

#include <sys/select.h>
#include <sys/poll.h>
#include <cutils/sockets.h>
#include <alloca.h>

#define LOG_TAG "BTIF_SOCK"
#include "btif_common.h"
#include "btif_util.h"

#include "bd.h"

#include "bta_api.h"
#include "btif_sock.h"
#include "btif_sock_thread.h"
#include "btif_sock_util.h"

#include <cutils/log.h>
#define asrt(s) if(!(s)) APPL_TRACE_ERROR3("## %s assert %s failed at line:%d ##",__FUNCTION__, #s, __LINE__)
#define print_events(events) do { \
    APPL_TRACE_DEBUG1("print poll event:%x", events); \
    if (events & POLLIN) APPL_TRACE_DEBUG0(  "   POLLIN "); \
    if (events & POLLPRI) APPL_TRACE_DEBUG0( "   POLLPRI "); \
    if (events & POLLOUT) APPL_TRACE_DEBUG0( "   POLLOUT "); \
    if (events & POLLERR) APPL_TRACE_DEBUG0( "   POLLERR "); \
    if (events & POLLHUP) APPL_TRACE_DEBUG0( "   POLLHUP "); \
    if (events & POLLNVAL) APPL_TRACE_DEBUG0("   POLLNVAL "); \
    if (events & POLLRDHUP) APPL_TRACE_DEBUG0("   POLLRDHUP"); \
    } while(0)

#define MAX_THREAD 8
#define MAX_POLL 64
#define POLL_EXCEPTION_EVENTS (POLLHUP | POLLRDHUP | POLLERR | POLLNVAL)
#define IS_EXCEPTION(e) ((e) & POLL_EXCEPTION_EVENTS)
#define IS_READ(e) ((e) & POLLIN)
#define IS_WRITE(e) ((e) & POLLOUT)
/*cmd executes in socket poll thread */
#define CMD_WAKEUP       1
#define CMD_EXIT         2
#define CMD_ADD_FD       3
#define CMD_USER_PRIVATE 4

typedef struct {
    struct pollfd pfd;
    uint32_t user_id;
    int type;
    int flags;
} poll_slot_t;
typedef struct {
    int cmd_fdr, cmd_fdw;
    int poll_count;
    poll_slot_t ps[MAX_POLL];
    int psi[MAX_POLL]; //index of poll slot
    volatile pid_t thread_id;
    btsock_signaled_cb callback;
    btsock_cmd_cb cmd_callback;
    int used;
} thread_slot_t;
static thread_slot_t ts[MAX_THREAD];



static void *sock_poll_thread(void *arg);
static inline void close_cmd_fd(int h);

static inline void add_poll(int h, int fd, int type, int flags, uint32_t user_id);

static pthread_mutex_t thread_slot_lock;


static inline void set_socket_blocking(int s, int blocking)
{
    int opts;
    opts = fcntl(s, F_GETFL);
    if (opts<0) APPL_TRACE_ERROR1("set blocking (%s)", strerror(errno));
    if(blocking)
        opts &= ~O_NONBLOCK;
    else opts |= O_NONBLOCK;
    fcntl(s, F_SETFL, opts);
}

static inline int create_server_socket(const char* name)
{
    int s = socket(AF_LOCAL, SOCK_STREAM, 0);
    APPL_TRACE_DEBUG1("covert name to android abstract name:%s", name);
    if(socket_local_server_bind(s, name, ANDROID_SOCKET_NAMESPACE_ABSTRACT) >= 0)
    {
        if(listen(s, 5) == 0)
        {
            APPL_TRACE_DEBUG2("listen to local socket:%s, fd:%d", name, s);
            return s;
        }
        else APPL_TRACE_ERROR3("listen to local socket:%s, fd:%d failed, errno:%d", name, s, errno);
    }
    else APPL_TRACE_ERROR3("create local socket:%s fd:%d, failed, errno:%d", name, s, errno);
    close(s);
    return -1;
}
static inline int connect_server_socket(const char* name)
{
    int s = socket(AF_LOCAL, SOCK_STREAM, 0);
    set_socket_blocking(s, TRUE);
    if(socket_local_client_connect(s, name, ANDROID_SOCKET_NAMESPACE_ABSTRACT, SOCK_STREAM) >= 0)
    {
        APPL_TRACE_DEBUG2("connected to local socket:%s, fd:%d", name, s);
        return s;
    }
    else APPL_TRACE_ERROR3("connect to local socket:%s, fd:%d failed, errno:%d", name, s, errno);
    close(s);
    return -1;
}
static inline int accept_server_socket(int s)
{
    struct sockaddr_un client_address;
    socklen_t clen;
    int fd = accept(s, (struct sockaddr*)&client_address, &clen);
    APPL_TRACE_DEBUG2("accepted fd:%d for server fd:%d", fd, s);
    return fd;
}
static inline pthread_t create_thread(void *(*start_routine)(void *), void * arg)
{
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);
    pthread_t thread_id = -1;
    if( pthread_create(&thread_id, &thread_attr, start_routine, arg)!=0 )
    {
        APPL_TRACE_ERROR1("pthread_create : %s", strerror(errno));
        return -1;
    }
    return thread_id;
}
static void init_poll(int cmd_fd);
static int alloc_thread_slot()
{
    int i;
    //revserd order to save guard uninitialized access to 0 index
    for(i = MAX_THREAD - 1; i >=0; i--)
    {
        APPL_TRACE_DEBUG2("ts[%d].used:%d", i, ts[i].used);
        if(!ts[i].used)
        {
            ts[i].used = 1;
            return i;
        }
    }
    APPL_TRACE_ERROR0("execeeded max thread count");
    return -1;
}
static void free_thread_slot(int h)
{
    if(0 <= h && h < MAX_THREAD)
    {
        close_cmd_fd(h);
        ts[h].used = 0;
    }
    else APPL_TRACE_ERROR1("invalid thread handle:%d", h);
}
int btsock_thread_init()
{
    static int initialized;
    APPL_TRACE_DEBUG1("in initialized:%d", initialized);
    if(!initialized)
    {
        initialized = 1;
        init_slot_lock(&thread_slot_lock);
        int h;
        for(h = 0; h < MAX_THREAD; h++)
        {
            ts[h].cmd_fdr = ts[h].cmd_fdw = -1;
            ts[h].used = 0;
            ts[h].thread_id = -1;
            ts[h].poll_count = 0;
            ts[h].callback = NULL;
            ts[h].cmd_callback = NULL;
        }
    }
    return TRUE;
}
int btsock_thread_create(btsock_signaled_cb callback, btsock_cmd_cb cmd_callback)
{
    int ret = FALSE;
    asrt(callback || cmd_callback);
    lock_slot(&thread_slot_lock);
    int h = alloc_thread_slot();
    unlock_slot(&thread_slot_lock);
    APPL_TRACE_DEBUG1("alloc_thread_slot ret:%d", h);
    if(h >= 0)
    {
        init_poll(h);
        if((ts[h].thread_id = create_thread(sock_poll_thread, (void*)h)) != -1)
        {
            APPL_TRACE_DEBUG2("h:%d, thread id:%d", h, ts[h].thread_id);
            ts[h].callback = callback;
            ts[h].cmd_callback = cmd_callback;
        }
        else
        {
            free_thread_slot(h);
            h = -1;
        }
    }
    return h;
}

/* create dummy socket pair used to wake up select loop */
static inline void init_cmd_fd(int h)
{
    asrt(ts[h].cmd_fdr == -1 && ts[h].cmd_fdw == -1);
    if(socketpair(AF_UNIX, SOCK_STREAM, 0, &ts[h].cmd_fdr) < 0)
    {
        APPL_TRACE_ERROR1("socketpair failed: %s", strerror(errno));
        return;
    }
    APPL_TRACE_DEBUG3("h:%d, cmd_fdr:%d, cmd_fdw:%d", h, ts[h].cmd_fdr, ts[h].cmd_fdw);
    //add the cmd fd for read & write
    add_poll(h, ts[h].cmd_fdr, 0, SOCK_THREAD_FD_RD, 0);
}
static inline void close_cmd_fd(int h)
{
    if(ts[h].cmd_fdr != -1)
    {
        close(ts[h].cmd_fdr);
        ts[h].cmd_fdr = -1;
    }
    if(ts[h].cmd_fdw != -1)
    {
        close(ts[h].cmd_fdw);
        ts[h].cmd_fdw = -1;
    }
}
typedef struct
{
    int id;
    int fd;
    int type;
    int flags;
    uint32_t user_id;
} sock_cmd_t;
int btsock_thread_add_fd(int h, int fd, int type, int flags, uint32_t user_id)
{
    if(h < 0 || h >= MAX_THREAD)
    {
        APPL_TRACE_ERROR1("invalid bt thread handle:%d", h);
        return FALSE;
    }
    if(ts[h].cmd_fdw == -1)
    {
        APPL_TRACE_ERROR0("cmd socket is not created. socket thread may not initialized");
        return FALSE;
    }
    if(flags & SOCK_THREAD_ADD_FD_SYNC)
    {
        //must executed in socket poll thread
        if(ts[h].thread_id == pthread_self())
        {
            //cleanup one-time flags
            flags &= ~SOCK_THREAD_ADD_FD_SYNC;
            add_poll(h, fd, type, flags, user_id);
            return TRUE;
        }
        APPL_TRACE_DEBUG0("THREAD_ADD_FD_SYNC is not called in poll thread, fallback to async");
    }
    sock_cmd_t cmd = {CMD_ADD_FD, fd, type, flags, user_id};
    APPL_TRACE_DEBUG2("adding fd:%d, flags:0x%x", fd, flags);
    return send(ts[h].cmd_fdw, &cmd, sizeof(cmd), 0) == sizeof(cmd);
}
int btsock_thread_post_cmd(int h, int type, const unsigned char* data, int size, uint32_t user_id)
{
    if(h < 0 || h >= MAX_THREAD)
    {
        APPL_TRACE_ERROR1("invalid bt thread handle:%d", h);
        return FALSE;
    }
    if(ts[h].cmd_fdw == -1)
    {
        APPL_TRACE_ERROR0("cmd socket is not created. socket thread may not initialized");
        return FALSE;
    }
    sock_cmd_t cmd = {CMD_USER_PRIVATE, 0, type, size, user_id};
    APPL_TRACE_DEBUG3("post cmd type:%d, size:%d, h:%d, ", type, size, h);
    sock_cmd_t* cmd_send = &cmd;
    int size_send = sizeof(cmd);
    if(data && size)
    {
        size_send = sizeof(cmd) + size;
        cmd_send = (sock_cmd_t*)alloca(size_send);
        if(cmd_send)
        {
            *cmd_send = cmd;
            memcpy(cmd_send + 1, data, size);
        }
        else
        {
            APPL_TRACE_ERROR3("alloca failed at h:%d, cmd type:%d, size:%d", h, type, size_send);
            return FALSE;
        }
    }
    return send(ts[h].cmd_fdw, cmd_send, size_send, 0) == size_send;
}
int btsock_thread_wakeup(int h)
{
    if(h < 0 || h >= MAX_THREAD)
    {
        APPL_TRACE_ERROR1("invalid bt thread handle:%d", h);
        return FALSE;
    }
    if(ts[h].cmd_fdw == -1)
    {
        APPL_TRACE_ERROR1("thread handle:%d, cmd socket is not created", h);
        return FALSE;
    }
    sock_cmd_t cmd = {CMD_WAKEUP, 0, 0, 0, 0};
    return send(ts[h].cmd_fdw, &cmd, sizeof(cmd), 0) == sizeof(cmd);
}
int btsock_thread_exit(int h)
{
    if(h < 0 || h >= MAX_THREAD)
    {
        APPL_TRACE_ERROR1("invalid bt thread handle:%d", h);
        return FALSE;
    }
    if(ts[h].cmd_fdw == -1)
    {
        APPL_TRACE_ERROR0("cmd socket is not created");
        return FALSE;
    }
    sock_cmd_t cmd = {CMD_EXIT, 0, 0, 0, 0};
    if(send(ts[h].cmd_fdw, &cmd, sizeof(cmd), 0) == sizeof(cmd))
    {
        pthread_join(ts[h].thread_id, 0);
        lock_slot(&thread_slot_lock);
        free_thread_slot(h);
        unlock_slot(&thread_slot_lock);
        return TRUE;
    }
    return FALSE;
}
static void init_poll(int h)
{
    int i;
    ts[h].poll_count = 0;
    ts[h].thread_id = -1;
    ts[h].callback = NULL;
    ts[h].cmd_callback = NULL;
    for(i = 0; i < MAX_POLL; i++)
    {
        ts[h].ps[i].pfd.fd = -1;
        ts[h].psi[i] = -1;
    }
    init_cmd_fd(h);
}
static inline unsigned int flags2pevents(int flags)
{
    unsigned int pevents = 0;
    if(flags & SOCK_THREAD_FD_WR)
        pevents |= POLLOUT;
    if(flags & SOCK_THREAD_FD_RD)
        pevents |= POLLIN;
    pevents |= POLL_EXCEPTION_EVENTS;
    return pevents;
}

static inline void set_poll(poll_slot_t* ps, int fd, int type, int flags, uint32_t user_id)
{
    ps->pfd.fd = fd;
    ps->user_id = user_id;
    if(ps->type != 0 && ps->type != type)
        APPL_TRACE_ERROR2("poll socket type should not changed! type was:%d, type now:%d", ps->type, type);
    ps->type = type;
    ps->flags = flags;
    ps->pfd.events = flags2pevents(flags);
    ps->pfd.revents = 0;
}
static inline void add_poll(int h, int fd, int type, int flags, uint32_t user_id)
{
    asrt(fd != -1);
    int i;
    int empty = -1;
    poll_slot_t* ps = ts[h].ps;

    for(i = 0; i < MAX_POLL; i++)
    {
        if(ps[i].pfd.fd == fd)
        {
            asrt(ts[h].poll_count < MAX_POLL);

            set_poll(&ps[i], fd, type, flags | ps[i].flags, user_id);
            return;
        }
        else if(empty < 0 && ps[i].pfd.fd == -1)
            empty = i;
    }
    if(empty >= 0)
    {
        asrt(ts[h].poll_count < MAX_POLL);
        set_poll(&ps[empty], fd, type, flags, user_id);
        ++ts[h].poll_count;
        return;
    }
    APPL_TRACE_ERROR1("exceeded max poll slot:%d!", MAX_POLL);
}
static inline void remove_poll(int h, poll_slot_t* ps, int flags)
{
    if(flags == ps->flags)
    {
        //all monitored events signaled. To remove it, just clear the slot
        --ts[h].poll_count;
        memset(ps, 0, sizeof(*ps));
        ps->pfd.fd = -1;
    }
    else
    {
        //one read or one write monitor event signaled, removed the accordding bit
        ps->flags &= ~flags;
        //update the poll events mask
        ps->pfd.events = flags2pevents(ps->flags);
    }
}
static int process_cmd_sock(int h)
{
    sock_cmd_t cmd = {-1, 0, 0, 0, 0};
    int fd = ts[h].cmd_fdr;
    if(recv(fd, &cmd, sizeof(cmd), MSG_WAITALL) != sizeof(cmd))
    {
        APPL_TRACE_ERROR1("recv cmd errno:%d", errno);
        return FALSE;
    }
    APPL_TRACE_DEBUG1("cmd.id:%d", cmd.id);
    switch(cmd.id)
    {
        case CMD_ADD_FD:
            add_poll(h, cmd.fd, cmd.type, cmd.flags, cmd.user_id);
            break;
        case CMD_WAKEUP:
            break;
        case CMD_USER_PRIVATE:
            asrt(ts[h].cmd_callback);
            if(ts[h].cmd_callback)
                ts[h].cmd_callback(fd, cmd.type, cmd.flags, cmd.user_id);
            break;
        case CMD_EXIT:
            return FALSE;
        default:
            APPL_TRACE_DEBUG1("unknown cmd: %d", cmd.id);
             break;
    }
    return TRUE;
}
static void process_data_sock(int h, struct pollfd *pfds, int count)
{
    asrt(count <= ts[h].poll_count);
    int i;
    for( i= 1; i < ts[h].poll_count; i++)
    {
        if(pfds[i].revents)
        {
            int ps_i = ts[h].psi[i];
            asrt(pfds[i].fd == ts[h].ps[ps_i].pfd.fd);
            uint32_t user_id = ts[h].ps[ps_i].user_id;
            int type = ts[h].ps[ps_i].type;
            int flags = 0;
            print_events(pfds[i].revents);
            if(IS_READ(pfds[i].revents))
            {
                flags |= SOCK_THREAD_FD_RD;
            }
            if(IS_WRITE(pfds[i].revents))
            {
                flags |= SOCK_THREAD_FD_WR;
            }
            if(IS_EXCEPTION(pfds[i].revents))
            {
                flags |= SOCK_THREAD_FD_EXCEPTION;
                //remove the whole slot not flags
                remove_poll(h, &ts[h].ps[ps_i], ts[h].ps[ps_i].flags);
            }
            else if(flags)
                 remove_poll(h, &ts[h].ps[ps_i], flags); //remove the monitor flags that already processed
            if(flags)
                ts[h].callback(pfds[i].fd, type, flags, user_id);
        }
    }
}

static void prepare_poll_fds(int h, struct pollfd* pfds)
{
    int count = 0;
    int ps_i = 0;
    int pfd_i = 0;
    asrt(ts[h].poll_count <= MAX_POLL);
    memset(pfds, 0, sizeof(pfds[0])*ts[h].poll_count);
    while(count < ts[h].poll_count)
    {
        if(ps_i >= MAX_POLL)
        {
            APPL_TRACE_ERROR4("exceed max poll range, ps_i:%d, MAX_POLL:%d, count:%d, ts[h].poll_count:%d",
                    ps_i, MAX_POLL, count, ts[h].poll_count);
            return;
        }
        if(ts[h].ps[ps_i].pfd.fd >= 0)
        {
            pfds[pfd_i] =  ts[h].ps[ps_i].pfd;
            ts[h].psi[pfd_i] = ps_i;
            count++;
            pfd_i++;
        }
        ps_i++;
    }
}
static void *sock_poll_thread(void *arg)
{
    struct pollfd pfds[MAX_POLL];
    memset(pfds, 0, sizeof(pfds));
    int h = (int)arg;
    for(;;)
    {
        prepare_poll_fds(h, pfds);
        int ret = poll(pfds, ts[h].poll_count, -1);
        if(ret == -1)
        {
            APPL_TRACE_ERROR2("poll ret -1, exit the thread, errno:%d, err:%s", errno, strerror(errno));
            break;
        }
        if(ret != 0)
        {
            int need_process_data_fd = TRUE;
            if(pfds[0].revents) //cmd fd always is the first one
            {
                asrt(pfds[0].fd == ts[h].cmd_fdr);
                if(!process_cmd_sock(h))
                {
                    APPL_TRACE_DEBUG1("h:%d, process_cmd_sock return false, exit...", h);
                    break;
                }
                if(ret == 1)
                    need_process_data_fd = FALSE;
                else ret--; //exclude the cmd fd
            }
            if(need_process_data_fd)
                process_data_sock(h, pfds, ret);
        }
        else {APPL_TRACE_DEBUG1("no data, select ret: %d", ret)};
    }
    ts[h].thread_id = -1;
    APPL_TRACE_DEBUG1("socket poll thread exiting, h:%d", h);
    return 0;
}

