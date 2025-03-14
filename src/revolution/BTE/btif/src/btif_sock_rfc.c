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
 *  Filename:      btif_sock_rfc.c
 *
 *  Description:   Handsfree Profile Bluetooth Interface
 *
 ***********************************************************************************/
#include <hardware/bluetooth.h>
#include <hardware/bt_sock.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/ioctl.h>

#define LOG_TAG "BTIF_SOCK"
#include "btif_common.h"
#include "btif_util.h"

#include "bd.h"

#include "bta_api.h"
#include "btif_sock_thread.h"
#include "btif_sock_sdp.h"
#include "btif_sock_util.h"

#include "bt_target.h"
#include "gki.h"
#include "hcimsgs.h"
#include "sdp_api.h"
#include "btu.h"
#include "btm_api.h"
#include "btm_int.h"
#include "bta_jv_api.h"
#include "bta_jv_co.h"
#include "port_api.h"

#include <cutils/log.h>
#include <hardware/bluetooth.h>
#define asrt(s) if(!(s)) APPL_TRACE_ERROR3("## %s assert %s failed at line:%d ##",__FUNCTION__, #s, __LINE__)

extern void uuid_to_string(bt_uuid_t *p_uuid, char *str);
static inline void logu(const char* title, const uint8_t * p_uuid)
{
    char uuids[128];
    uuid_to_string((bt_uuid_t*)p_uuid, uuids);
    ALOGD("%s: %s", title, uuids);
}



#define MAX_RFC_CHANNEL 30
#define MAX_RFC_SESSION BTA_JV_MAX_RFC_SR_SESSION //3 by default
typedef struct {
    int outgoing_congest : 1;
    int pending_sdp_request : 1;
    int doing_sdp_request : 1;
    int server : 1;
    int connected : 1;
    int closing : 1;
} flags_t;

typedef struct {
  flags_t f;
  uint32_t id;
  int security;
  int scn;
  bt_bdaddr_t addr;
  uint8_t service_uuid[16];
  char service_name[256];
  int fd, app_fd;
  int mtu;
  uint8_t* packet;
  int sdp_handle;
  int rfc_handle;
  int rfc_port_handle;
  int role;
  BUFFER_Q incoming_que;
} rfc_slot_t;

static rfc_slot_t rfc_slots[MAX_RFC_CHANNEL];
static uint32_t rfc_slot_id;
static volatile int pth = -1; //poll thread handle
static void jv_dm_cback(tBTA_JV_EVT event, tBTA_JV *p_data, void *user_data);
static void cleanup_rfc_slot(rfc_slot_t* rs);
static inline void close_rfc_connection(int rfc_handle, int server);
static bt_status_t dm_get_remote_service_record(bt_bdaddr_t *remote_addr,
                                                    bt_uuid_t *uuid);
static void *rfcomm_cback(tBTA_JV_EVT event, tBTA_JV *p_data, void *user_data);
static inline BOOLEAN send_app_scn(rfc_slot_t* rs);
static pthread_mutex_t slot_lock;
#define is_init_done() (pth != -1)
static inline void clear_slot_flag(flags_t* f)
{
    memset(f, 0, sizeof(*f));
}

static inline void bd_copy(UINT8* dest, UINT8* src, BOOLEAN swap)
{
    if (swap)
    {
        int i;
        for (i =0; i < 6 ;i++)
            dest[i]= src[5-i];
    }
    else memcpy(dest, src, 6);
}
static inline void free_gki_que(BUFFER_Q* q)
{
    while(!GKI_queue_is_empty(q))
           GKI_freebuf(GKI_dequeue(q));
}
static void init_rfc_slots()
{
    int i;
    memset(rfc_slots, 0, sizeof(rfc_slot_t)*MAX_RFC_CHANNEL);
    for(i = 0; i < MAX_RFC_CHANNEL; i++)
    {
        rfc_slots[i].scn = -1;
        rfc_slots[i].sdp_handle = 0;
        rfc_slots[i].fd = rfc_slots[i].app_fd = -1;
        GKI_init_q(&rfc_slots[i].incoming_que);
    }
    BTA_JvEnable(jv_dm_cback);
    init_slot_lock(&slot_lock);
}
bt_status_t btsock_rfc_init(int poll_thread_handle)
{
    pth = poll_thread_handle;
    init_rfc_slots();
    return BT_STATUS_SUCCESS;
}
void btsock_rfc_cleanup()
{
    int curr_pth = pth;
    pth = -1;
    btsock_thread_exit(curr_pth);
    lock_slot(&slot_lock);
    int i;
    for(i = 0; i < MAX_RFC_CHANNEL; i++)
    {
        if(rfc_slots[i].id)
            cleanup_rfc_slot(&rfc_slots[i]);
    }
    unlock_slot(&slot_lock);
}
static inline rfc_slot_t* find_free_slot()
{
    int i;
    for(i = 0; i < MAX_RFC_CHANNEL; i++)
    {
        if(rfc_slots[i].fd == -1)
        {
             return &rfc_slots[i];
        }
    }
    return NULL;
}
static inline rfc_slot_t* find_rfc_slot_by_id(uint32_t id)
{
    int i;
    if(id)
    {
        for(i = 0; i < MAX_RFC_CHANNEL; i++)
        {
            if(rfc_slots[i].id == id)
            {
                return &rfc_slots[i];
            }
        }
    }
    APPL_TRACE_WARNING1("invalid rfc slot id: %d", id);
    return NULL;
}
static inline rfc_slot_t* find_rfc_slot_by_pending_sdp()
{
    uint32_t min_id = (uint32_t)-1;
    int slot = -1;
    int i;
    for(i = 0; i < MAX_RFC_CHANNEL; i++)
    {
        if(rfc_slots[i].id && rfc_slots[i].f.pending_sdp_request)
        {
            if(rfc_slots[i].id < min_id)
            {
                min_id = rfc_slots[i].id;
                slot = i;
            }
        }
    }
    if(0<= slot && slot < MAX_RFC_CHANNEL)
        return &rfc_slots[slot];
    return NULL;
}
static inline rfc_slot_t* find_rfc_slot_requesting_sdp()
{
    int i;
    for(i = 0; i < MAX_RFC_CHANNEL; i++)
    {
        if(rfc_slots[i].id && rfc_slots[i].f.doing_sdp_request)
                return &rfc_slots[i];
    }
    APPL_TRACE_DEBUG0("can not find any slot is requesting sdp");
    return NULL;
}

static inline rfc_slot_t* find_rfc_slot_by_fd(int fd)
{
    int i;
    if(fd >= 0)
    {
        for(i = 0; i < MAX_RFC_CHANNEL; i++)
        {
            if(rfc_slots[i].fd == fd)
            {
                if(rfc_slots[i].id)
                    return &rfc_slots[i];
                else
                {
                    APPL_TRACE_ERROR0("invalid rfc slot id, cannot be 0");
                    break;
                }
            }
        }
    }
    return NULL;
}
static rfc_slot_t* alloc_rfc_slot(const bt_bdaddr_t *addr, const char* name, const uint8_t* uuid, int channel, int flags, BOOLEAN server)
{
    int security = 0;
    if(flags & BTSOCK_FLAG_ENCRYPT)
        security |= server ? BTM_SEC_IN_ENCRYPT : BTM_SEC_OUT_ENCRYPT;
    if(flags & BTSOCK_FLAG_AUTH)
        security |= server ? BTM_SEC_IN_AUTHENTICATE : BTM_SEC_OUT_AUTHENTICATE;

    rfc_slot_t* rs = find_free_slot();
    if(rs)
    {
        int fds[2] = {-1, -1};
        if(socketpair(AF_LOCAL, SOCK_STREAM, 0, fds))
        {
            APPL_TRACE_ERROR1("socketpair failed, errno:%d", errno);
            return NULL;
        }
        rs->fd = fds[0];
        rs->app_fd = fds[1];
        rs->security = security;
        rs->scn = channel;
        if(uuid)
            memcpy(rs->service_uuid, uuid, sizeof(rs->service_uuid));
        else memset(rs->service_uuid, 0, sizeof(rs->service_uuid));
        if(name && *name)
            strncpy(rs->service_name, name, sizeof(rs->service_name) -1);
        if(addr)
            rs->addr = *addr;
        ++rfc_slot_id;
        if(rfc_slot_id == 0)
            rfc_slot_id = 1; //skip 0 when wrapped
        rs->id = rfc_slot_id;
        rs->f.server = server;
    }
    return rs;
}
// rfc_slot_t* accept_rs = create_srv_accept_rfc_slot(srv_rs, p_open->rem_bda,p_opne->handle,  p_open->new_listen_handle);
static inline rfc_slot_t* create_srv_accept_rfc_slot(rfc_slot_t* srv_rs, const bt_bdaddr_t* addr,
                                        int open_handle, int new_listen_handle)
{
    rfc_slot_t *accept_rs = alloc_rfc_slot(addr, srv_rs->service_name, srv_rs->service_uuid, srv_rs->scn, 0, FALSE);
    clear_slot_flag(&accept_rs->f);
    accept_rs->f.server = FALSE;
    accept_rs->f.connected = TRUE;
    accept_rs->security = srv_rs->security;
    accept_rs->mtu = srv_rs->mtu;
    accept_rs->role = srv_rs->role;
    accept_rs->rfc_handle = open_handle;
    accept_rs->rfc_port_handle = BTA_JvRfcommGetPortHdl(open_handle);
    asrt(accept_rs->rfc_handle == srv_rs->rfc_handle);
    asrt(accept_rs->rfc_port_handle == srv_rs->rfc_port_handle);
    //now update listen handle of server slot
    srv_rs->rfc_handle = new_listen_handle;
    srv_rs->rfc_port_handle =  BTA_JvRfcommGetPortHdl(new_listen_handle);
    //now swap the slot id
    uint32_t new_listen_id = accept_rs->id;
    accept_rs->id = srv_rs->id;
    srv_rs->id = new_listen_id;
    return accept_rs;
}
bt_status_t btsock_rfc_listen(const char* service_name, const uint8_t* service_uuid, int channel,
                            int* sock_fd, int flags)
{
    if(sock_fd == NULL || (service_uuid == NULL && (channel < 1 || channel > 30)))
    {
        APPL_TRACE_ERROR3("invalid rfc channel:%d or sock_fd:%p, uuid:%p", channel, sock_fd, service_uuid);
        return BT_STATUS_PARM_INVALID;
    }
    *sock_fd = -1;
    if(!is_init_done())
        return BT_STATUS_NOT_READY;
    if(is_uuid_empty(service_uuid))
        service_uuid = UUID_SPP; //use serial port profile to listen to specified channel
    else
    {
        //Check the service_uuid. overwrite the channel # if reserved
        int reserved_channel = get_reserved_rfc_channel(service_uuid);
        if(reserved_channel > 0)
        {
            channel = reserved_channel;
        }
    }
    int status = BT_STATUS_FAIL;
    lock_slot(&slot_lock);
    rfc_slot_t* rs = alloc_rfc_slot(NULL, service_name, service_uuid, channel, flags, TRUE);
    if(rs)
    {
        BTA_JvCreateRecordByUser((void *)rs->id);
        *sock_fd = rs->app_fd;
        rs->app_fd = -1; //the fd ownership is transferred to app
        status = BT_STATUS_SUCCESS;
        btsock_thread_add_fd(pth, rs->fd, BTSOCK_RFCOMM, SOCK_THREAD_FD_EXCEPTION, rs->id);
    }
    unlock_slot(&slot_lock);
    return status;
}
bt_status_t btsock_rfc_connect(const bt_bdaddr_t *bd_addr, const uint8_t* service_uuid,
        int channel, int* sock_fd, int flags)
{
    if(sock_fd == NULL || (service_uuid == NULL && (channel < 1 || channel > 30)))
    {
        APPL_TRACE_ERROR3("invalid rfc channel:%d or sock_fd:%p, uuid:%p", channel, sock_fd,
                          service_uuid);
        return BT_STATUS_PARM_INVALID;
    }
    *sock_fd = -1;
    if(!is_init_done())
        return BT_STATUS_NOT_READY;
    int status = BT_STATUS_FAIL;
    lock_slot(&slot_lock);
    rfc_slot_t* rs = alloc_rfc_slot(bd_addr, NULL, service_uuid, channel, flags, FALSE);
    if(rs)
    {
        if(is_uuid_empty(service_uuid))
        {
            APPL_TRACE_DEBUG1("connecting to rfcomm channel:%d without service discovery", channel);
            if(BTA_JvRfcommConnect(rs->security, rs->role, rs->scn, rs->addr.address,
                        rfcomm_cback, (void*)rs->id) == BTA_JV_SUCCESS)
            {
                if(send_app_scn(rs))
                {
                    btsock_thread_add_fd(pth, rs->fd, BTSOCK_RFCOMM,
                                                        SOCK_THREAD_FD_RD, rs->id);
                    *sock_fd = rs->app_fd;
                    rs->app_fd = -1; //the fd ownership is transferred to app
                    status = BT_STATUS_SUCCESS;
                }
                else cleanup_rfc_slot(rs);
            }
            else cleanup_rfc_slot(rs);
        }
        else
        {
            tSDP_UUID sdp_uuid;
            sdp_uuid.len = 16;
            memcpy(sdp_uuid.uu.uuid128, service_uuid, sizeof(sdp_uuid.uu.uuid128));
            logu("service_uuid", service_uuid);
            *sock_fd = rs->app_fd;
            rs->app_fd = -1; //the fd ownership is transferred to app
            status = BT_STATUS_SUCCESS;
            rfc_slot_t* rs_doing_sdp = find_rfc_slot_requesting_sdp();
            if(rs_doing_sdp == NULL)
            {
                BTA_JvStartDiscovery((UINT8*)bd_addr->address, 1, &sdp_uuid, (void*)rs->id);
                rs->f.pending_sdp_request = FALSE;
                rs->f.doing_sdp_request = TRUE;
            }
            else
            {
                rs->f.pending_sdp_request = TRUE;
                rs->f.doing_sdp_request = FALSE;
            }
            btsock_thread_add_fd(pth, rs->fd, BTSOCK_RFCOMM, SOCK_THREAD_FD_RD, rs->id);
        }
    }
    unlock_slot(&slot_lock);
    return status;
}

static int create_server_sdp_record(rfc_slot_t* rs)
{
    int scn = rs->scn;
    if(rs->scn > 0)
    {
        if(BTM_TryAllocateSCN(rs->scn) == FALSE)
        {
            APPL_TRACE_ERROR1("rfc channel:%d already in use", scn);
            return FALSE;
        }
    }
    else if((rs->scn = BTM_AllocateSCN()) == 0)
    {
        APPL_TRACE_ERROR0("run out of rfc channels");
        return FALSE;
    }
    if((rs->sdp_handle = add_rfc_sdp_rec(rs->service_name, rs->service_uuid, rs->scn)) <= 0)
    {
        return FALSE;
    }
    return TRUE;
}
const char * jv_evt[] = {
    "BTA_JV_ENABLE_EVT",
    "BTA_JV_SET_DISCOVER_EVT",
    "BTA_JV_LOCAL_ADDR_EVT",
    "BTA_JV_LOCAL_NAME_EVT",
    "BTA_JV_REMOTE_NAME_EVT",
    "BTA_JV_SET_ENCRYPTION_EVT",
    "BTA_JV_GET_SCN_EVT",
    "BTA_JV_GET_PSM_EVT",
    "BTA_JV_DISCOVERY_COMP_EVT",
    "BTA_JV_SERVICES_LEN_EVT",
    "BTA_JV_SERVICE_SEL_EVT",
    "BTA_JV_CREATE_RECORD_EVT",
    "BTA_JV_UPDATE_RECORD_EVT",
    "BTA_JV_ADD_ATTR_EVT",
    "BTA_JV_DELETE_ATTR_EVT",
    "BTA_JV_CANCEL_DISCVRY_EVT",

    "BTA_JV_L2CAP_OPEN_EVT",
    "BTA_JV_L2CAP_CLOSE_EVT",
    "BTA_JV_L2CAP_START_EVT",
    "BTA_JV_L2CAP_CL_INIT_EVT",
    "BTA_JV_L2CAP_DATA_IND_EVT",
    "BTA_JV_L2CAP_CONG_EVT",
    "BTA_JV_L2CAP_READ_EVT",
    "BTA_JV_L2CAP_RECEIVE_EVT",
    "BTA_JV_L2CAP_WRITE_EVT",

    "BTA_JV_RFCOMM_OPEN_EVT",
    "BTA_JV_RFCOMM_CLOSE_EVT",
    "BTA_JV_RFCOMM_START_EVT",
    "BTA_JV_RFCOMM_CL_INIT_EVT",
    "BTA_JV_RFCOMM_DATA_IND_EVT",
    "BTA_JV_RFCOMM_CONG_EVT",
    "BTA_JV_RFCOMM_READ_EVT",
    "BTA_JV_RFCOMM_WRITE_EVT",
    "BTA_JV_RFCOMM_SRV_OPEN_EVT", //  33 /* open status of Server RFCOMM connection */
    "BTA_JV_MAX_EVT"
};
static inline void free_rfc_slot_scn(rfc_slot_t* rs)
{
    if(rs->scn > 0)
    {
        if(rs->f.server && !rs->f.closing)
        {
            BTA_JvRfcommStopServer(rs->rfc_handle);
            rs->rfc_handle = 0;
        }
        BTM_FreeSCN(rs->scn);
        rs->scn = 0;
    }
}
static void cleanup_rfc_slot(rfc_slot_t* rs)
{
    APPL_TRACE_DEBUG3("cleanup slot:%d, fd:%d, scn:%d", rs->id, rs->fd, rs->scn);
    if(rs->fd != -1)
    {
        shutdown(rs->fd, 2);
        close(rs->fd);
        rs->fd = -1;
    }
    if(rs->app_fd != -1)
    {
        close(rs->app_fd);
        rs->app_fd = -1;
    }
    if(rs->sdp_handle > 0)
    {
        del_rfc_sdp_rec(rs->sdp_handle);
        rs->sdp_handle = 0;
    }
    if(rs->rfc_handle && !rs->f.closing && !rs->f.server)
    {
        APPL_TRACE_DEBUG1("closing rfcomm connection, rfc_handle:%d", rs->rfc_handle);
        BTA_JvRfcommClose(rs->rfc_handle);
        rs->rfc_handle = 0;
    }
    free_rfc_slot_scn(rs);
    free_gki_que(&rs->incoming_que);

    rs->rfc_port_handle = 0;
    //cleanup the flag
    memset(&rs->f, 0, sizeof(rs->f));
    rs->id = 0;
}
static inline BOOLEAN send_app_scn(rfc_slot_t* rs)
{
    if(sock_send_all(rs->fd, (const uint8_t*)&rs->scn, sizeof(rs->scn)) == sizeof(rs->scn))
    {
        return TRUE;
    }

    return FALSE;
}
static BOOLEAN send_app_connect_signal(int fd, const bt_bdaddr_t* addr, int channel, int status, int send_fd)
{
/*
    typedef struct {
    short size;
    bt_bdaddr_t bd_addr;
    int channel;
    int status;
} __attribute__((packed)) sock_connect_signal_t;
*/
    sock_connect_signal_t cs;
    cs.size = sizeof(cs);
    cs.bd_addr = *addr;
    cs.channel = channel;
    cs.status = status;
    if(send_fd != -1)
    {
        if(sock_send_fd(fd, (const uint8_t*)&cs, sizeof(cs), send_fd) == sizeof(cs))
            return TRUE;
        else APPL_TRACE_ERROR2("sock_send_fd failed, fd:%d, send_fd:%d", fd, send_fd);
    }
    else if(sock_send_all(fd, (const uint8_t*)&cs, sizeof(cs)) == sizeof(cs))
    {
        return TRUE;
    }
    return FALSE;
}
static void on_cl_rfc_init(tBTA_JV_RFCOMM_CL_INIT *p_init, uint32_t id)
{
   lock_slot(&slot_lock);
    rfc_slot_t* rs = find_rfc_slot_by_id(id);
    if(rs)
    {
        if (p_init->status != BTA_JV_SUCCESS)
            cleanup_rfc_slot(rs);
        else
        {
            rs->rfc_handle = p_init->handle;
        }
    }
    unlock_slot(&slot_lock);
}
static void  on_srv_rfc_listen_started(tBTA_JV_RFCOMM_START *p_start, uint32_t id)
{
    lock_slot(&slot_lock);
    rfc_slot_t* rs = find_rfc_slot_by_id(id);
    if(rs)
    {
        if (p_start->status != BTA_JV_SUCCESS)
            cleanup_rfc_slot(rs);
        else
        {
            rs->rfc_handle = p_start->handle;

            if(!send_app_scn(rs))
            {
                //closed
                APPL_TRACE_DEBUG1("send_app_scn() failed, close rs->id:%d", rs->id);
                cleanup_rfc_slot(rs);
            }
        }
    }
    unlock_slot(&slot_lock);
}
static uint32_t on_srv_rfc_connect(tBTA_JV_RFCOMM_SRV_OPEN *p_open, uint32_t id)
{
    uint32_t new_listen_slot_id = 0;
    lock_slot(&slot_lock);
    rfc_slot_t* srv_rs = find_rfc_slot_by_id(id);
    if(srv_rs)
    {
        rfc_slot_t* accept_rs = create_srv_accept_rfc_slot(srv_rs, (const bt_bdaddr_t*)p_open->rem_bda,
                                                           p_open->handle, p_open->new_listen_handle);
        if(accept_rs)
        {
            //start monitor the socket
            btsock_thread_add_fd(pth, srv_rs->fd, BTSOCK_RFCOMM, SOCK_THREAD_FD_EXCEPTION, srv_rs->id);
            btsock_thread_add_fd(pth, accept_rs->fd, BTSOCK_RFCOMM, SOCK_THREAD_FD_RD, accept_rs->id);
            APPL_TRACE_DEBUG1("sending connect signal & app fd:%dto app server to accept() the connection",
                             accept_rs->app_fd);
            APPL_TRACE_DEBUG2("server fd:%d, scn:%d", srv_rs->fd, srv_rs->scn);
            send_app_connect_signal(srv_rs->fd, &accept_rs->addr, srv_rs->scn, 0, accept_rs->app_fd);
            accept_rs->app_fd = -1; //the fd is closed after sent to app
            new_listen_slot_id = srv_rs->id;
        }
    }
    unlock_slot(&slot_lock);
    return new_listen_slot_id;
}
static void on_cli_rfc_connect(tBTA_JV_RFCOMM_OPEN *p_open, uint32_t id)
{
    lock_slot(&slot_lock);
    rfc_slot_t* rs = find_rfc_slot_by_id(id);
    if(rs && p_open->status == BTA_JV_SUCCESS)
    {
        rs->rfc_port_handle = BTA_JvRfcommGetPortHdl(p_open->handle);
        bd_copy(rs->addr.address, p_open->rem_bda, 0);
        //notify app rfc is connected
        APPL_TRACE_DEBUG4("call send_app_connect_signal, slot id:%d, fd:%d, rfc scn:%d, server:%d",
                         rs->id, rs->fd, rs->scn, rs->f.server);
        if(send_app_connect_signal(rs->fd, &rs->addr, rs->scn, 0, -1))
        {
            //start monitoring the socketpair to get call back when app writing data
            APPL_TRACE_DEBUG3("on_rfc_connect_ind, connect signal sent, slot id:%d, rfc scn:%d, server:%d",
                             rs->id, rs->scn, rs->f.server);
            rs->f.connected = TRUE;
        }
        else APPL_TRACE_ERROR0("send_app_connect_signal failed");
    }
    else if(rs)
        cleanup_rfc_slot(rs);
    unlock_slot(&slot_lock);
}
static void on_rfc_close(tBTA_JV_RFCOMM_CLOSE * p_close, uint32_t id)
{
    lock_slot(&slot_lock);
    rfc_slot_t* rs = find_rfc_slot_by_id(id);
    if(rs)
    {
        APPL_TRACE_DEBUG4("on_rfc_close, slot id:%d, fd:%d, rfc scn:%d, server:%d",
                         rs->id, rs->fd, rs->scn, rs->f.server);
        free_rfc_slot_scn(rs);
        //rfc_handle already closed when receiving rfcomm close event from stack.
        rs->rfc_handle = 0;
        rs->f.connected = FALSE;
        cleanup_rfc_slot(rs);
    }
    unlock_slot(&slot_lock);
}
static void on_rfc_write_done(tBTA_JV_RFCOMM_WRITE *p, uint32_t id)
{
    lock_slot(&slot_lock);
    rfc_slot_t* rs = find_rfc_slot_by_id(id);
    if(rs && !rs->f.outgoing_congest)
    {
        //mointer the fd for any outgoing data
        btsock_thread_add_fd(pth, rs->fd, BTSOCK_RFCOMM, SOCK_THREAD_FD_RD, rs->id);
    }
    unlock_slot(&slot_lock);
}
static void on_rfc_outgoing_congest(tBTA_JV_RFCOMM_CONG *p, uint32_t id)
{
    lock_slot(&slot_lock);
    rfc_slot_t* rs = find_rfc_slot_by_id(id);
    if(rs)
    {
        rs->f.outgoing_congest = p->cong ? 1 : 0;
        //mointer the fd for any outgoing data
        if(!rs->f.outgoing_congest)
            btsock_thread_add_fd(pth, rs->fd, BTSOCK_RFCOMM, SOCK_THREAD_FD_RD, rs->id);
    }
    unlock_slot(&slot_lock);
}

static void *rfcomm_cback(tBTA_JV_EVT event, tBTA_JV *p_data, void *user_data)
{
    int rc;
    void* new_user_data = NULL;
    APPL_TRACE_DEBUG1("event=%s", jv_evt[event]);

    switch (event)
    {
    case BTA_JV_RFCOMM_START_EVT:
        on_srv_rfc_listen_started(&p_data->rfc_start, (uint32_t)user_data);
        break;

    case BTA_JV_RFCOMM_CL_INIT_EVT:
        on_cl_rfc_init(&p_data->rfc_cl_init, (uint32_t)user_data);
        break;

    case BTA_JV_RFCOMM_OPEN_EVT:
        on_cli_rfc_connect(&p_data->rfc_open, (uint32_t)user_data);
        break;
    case BTA_JV_RFCOMM_SRV_OPEN_EVT:
        new_user_data = (void*)on_srv_rfc_connect(&p_data->rfc_srv_open, (uint32_t)user_data);
        break;

    case BTA_JV_RFCOMM_CLOSE_EVT:
        on_rfc_close(&p_data->rfc_close, (uint32_t)user_data);
        break;

    case BTA_JV_RFCOMM_READ_EVT:
        APPL_TRACE_DEBUG0("BTA_JV_RFCOMM_READ_EVT not used");
        break;

    case BTA_JV_RFCOMM_WRITE_EVT:
        on_rfc_write_done(&p_data->rfc_write, (uint32_t)user_data);
        break;

    case BTA_JV_RFCOMM_DATA_IND_EVT:
        APPL_TRACE_DEBUG0("BTA_JV_RFCOMM_DATA_IND_EVT not used");
        break;

    case BTA_JV_RFCOMM_CONG_EVT:
        //on_rfc_cong(&p_data->rfc_cong);
        on_rfc_outgoing_congest(&p_data->rfc_cong, (uint32_t)user_data);
        break;
    default:
        APPL_TRACE_ERROR2("unhandled event %d, slot id:%d", event, (uint32_t)user_data);
        break;
    }
    return new_user_data;
}

static void jv_dm_cback(tBTA_JV_EVT event, tBTA_JV *p_data, void *user_data)
{
    uint32_t id = (uint32_t)user_data;
    APPL_TRACE_DEBUG2("event:%d, slot id:%d", event, id);
    switch(event)
    {
        case BTA_JV_CREATE_RECORD_EVT:
            {
                lock_slot(&slot_lock);
                rfc_slot_t* rs = find_rfc_slot_by_id(id);
                if(rs && create_server_sdp_record(rs))
                {
                    //now start the rfcomm server after sdp & channel # assigned
                    BTA_JvRfcommStartServer(rs->security, rs->role, rs->scn, MAX_RFC_SESSION, rfcomm_cback,
                                            (void*)rs->id);
                }
                unlock_slot(&slot_lock);
                break;
            }
        case BTA_JV_DISCOVERY_COMP_EVT:
            {
                rfc_slot_t* rs = NULL;
                lock_slot(&slot_lock);
                if(p_data->disc_comp.status == BTA_JV_SUCCESS && p_data->disc_comp.scn)
                {
                    APPL_TRACE_DEBUG3("BTA_JV_DISCOVERY_COMP_EVT, slot id:%d, status:%d, scn:%d",
                                      id, p_data->disc_comp.status, p_data->disc_comp.scn);

                    rs = find_rfc_slot_by_id(id);
                    if(rs && rs->f.doing_sdp_request)
                    {
                        if(BTA_JvRfcommConnect(rs->security, rs->role, p_data->disc_comp.scn, rs->addr.address,
                                    rfcomm_cback, (void*)rs->id) == BTA_JV_SUCCESS)
                        {
                            rs->scn = p_data->disc_comp.scn;
                            rs->f.doing_sdp_request = FALSE;
                            if(!send_app_scn(rs))
                                cleanup_rfc_slot(rs);
                        }
                        else cleanup_rfc_slot(rs);
                    }
                    else if(rs)
                    {
                        APPL_TRACE_ERROR3("DISCOVERY_COMP_EVT no pending sdp request, slot id:%d, \
                                flag sdp pending:%d, flag sdp doing:%d",
                                id, rs->f.pending_sdp_request, rs->f.doing_sdp_request);
                    }
                }
                else
                {
                    APPL_TRACE_ERROR3("DISCOVERY_COMP_EVT slot id:%d, failed to find channle, \
                                      status:%d, scn:%d", id, p_data->disc_comp.status,
                                      p_data->disc_comp.scn);
                    rs = find_rfc_slot_by_id(id);
                    if(rs)
                        cleanup_rfc_slot(rs);
                }
                rs = find_rfc_slot_by_pending_sdp();
                if(rs)
                {
                    APPL_TRACE_DEBUG0("BTA_JV_DISCOVERY_COMP_EVT, start another pending scn sdp request");
                    tSDP_UUID sdp_uuid;
                    sdp_uuid.len = 16;
                    memcpy(sdp_uuid.uu.uuid128, rs->service_uuid, sizeof(sdp_uuid.uu.uuid128));
                    BTA_JvStartDiscovery((UINT8*)rs->addr.address, 1, &sdp_uuid, (void*)rs->id);
                    rs->f.pending_sdp_request = FALSE;
                    rs->f.doing_sdp_request = TRUE;
                }
                unlock_slot(&slot_lock);
                break;
            }
        default:
            APPL_TRACE_DEBUG2("unhandled event:%d, slot id:%d", event, id);
            break;
    }

}
#define SENT_ALL 2
#define SENT_PARTIAL 1
#define SENT_NONE 0
#define SENT_FAILED (-1)
static int send_data_to_app(int fd, BT_HDR *p_buf)
{
    if(p_buf->len == 0)
        return SENT_ALL;
    int sent = send(fd, (UINT8 *)(p_buf + 1) + p_buf->offset,  p_buf->len, MSG_DONTWAIT);
    if(sent == p_buf->len)
        return SENT_ALL;

    if(sent > 0 && sent < p_buf->len)
    {
        //sent partial
        APPL_TRACE_ERROR2("send partial, sent:%d, p_buf->len:%d", sent, p_buf->len);
        p_buf->offset += sent;
        p_buf->len -= sent;
        return SENT_PARTIAL;

    }
    if(sent < 0 &&
        (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
    {
        APPL_TRACE_ERROR1("send none, EAGAIN or EWOULDBLOCK, errno:%d", errno);
        return SENT_NONE;
    }
    APPL_TRACE_ERROR3("unknown send() error, sent:%d, p_buf->len:%d,  errno:%d", sent, p_buf->len, errno);
    return SENT_FAILED;
}
static BOOLEAN flush_incoming_que_on_wr_signal(rfc_slot_t* rs)
{
    while(!GKI_queue_is_empty(&rs->incoming_que))
    {
        BT_HDR *p_buf = GKI_dequeue(&rs->incoming_que);
        int sent = send_data_to_app(rs->fd, p_buf);
        switch(sent)
        {
            case SENT_NONE:
            case SENT_PARTIAL:
                //add it back to the queue at same position
                GKI_enqueue_head (&rs->incoming_que, p_buf);
                //monitor the fd to get callback when app is ready to receive data
                btsock_thread_add_fd(pth, rs->fd, BTSOCK_RFCOMM, SOCK_THREAD_FD_WR, rs->id);
                return TRUE;
            case SENT_ALL:
                GKI_freebuf(p_buf);
                break;
            case SENT_FAILED:
                GKI_freebuf(p_buf);
                return FALSE;
        }
    }

    //app is ready to receive data, tell stack to start the data flow
    //fix me: need a jv flow control api to serialize the call in stack
    PORT_FlowControl(rs->rfc_port_handle, TRUE);
    return TRUE;
}
void btsock_rfc_signaled(int fd, int flags, uint32_t user_id)
{
    lock_slot(&slot_lock);
    rfc_slot_t* rs = find_rfc_slot_by_id(user_id);
    if(rs)
    {
        APPL_TRACE_DEBUG3("rfc slot id:%d, fd:%d, flags:%x", rs->id, fd, flags);
        BOOLEAN need_close = FALSE;
        if(flags & SOCK_THREAD_FD_RD)
        {
            //data available from app, tell stack we have outgoing data
            if(!rs->f.server)
            {
                if(rs->f.connected)
                    BTA_JvRfcommWrite(rs->rfc_handle, (UINT32)rs->id);
                else
                {
                    APPL_TRACE_ERROR2("SOCK_THREAD_FD_RD signaled when rfc is not connected, \
                                      slot id:%d, channel:%d", rs->id, rs->scn);
                    need_close = TRUE;
                }
            }
        }
        if(flags & SOCK_THREAD_FD_WR)
        {
            //app is ready to receive more data, tell stack to enable the data flow
            if(!rs->f.connected || !flush_incoming_que_on_wr_signal(rs))
            {
                need_close = TRUE;
                APPL_TRACE_ERROR2("SOCK_THREAD_FD_WR signaled when rfc is not connected \
                                  or app closed fd, slot id:%d, channel:%d", rs->id, rs->scn);
            }

        }
        if(need_close || (flags & SOCK_THREAD_FD_EXCEPTION))
        {
            APPL_TRACE_DEBUG1("SOCK_THREAD_FD_EXCEPTION, flags:%x", flags);
            rs->f.closing = TRUE;
            if(rs->f.server)
               BTA_JvRfcommStopServer(rs->rfc_handle);
            else
                BTA_JvRfcommClose(rs->rfc_handle);
        }
    }
    unlock_slot(&slot_lock);
}
//stack rfcomm callout functions
//[
int bta_co_rfc_data_incoming(void *user_data, BT_HDR *p_buf)
{
    uint32_t id = (uint32_t)user_data;
    int ret = 0;
    lock_slot(&slot_lock);
    rfc_slot_t* rs = find_rfc_slot_by_id(id);
    if(rs)
    {

        int sent = send_data_to_app(rs->fd, p_buf);
        switch(sent)
        {
            case SENT_NONE:
            case SENT_PARTIAL:
                //add it to the end of the queue
                GKI_enqueue(&rs->incoming_que, p_buf);
                //monitor the fd to get callback when app is ready to receive data
                btsock_thread_add_fd(pth, rs->fd, BTSOCK_RFCOMM, SOCK_THREAD_FD_WR, rs->id);
                break;
            case SENT_ALL:
                GKI_freebuf(p_buf);
                ret = 1;//enable the data flow
                break;
            case SENT_FAILED:
                GKI_freebuf(p_buf);
                cleanup_rfc_slot(rs);
                break;
        }
     }
    unlock_slot(&slot_lock);
    return ret;//return 0 to disable data flow
}
int bta_co_rfc_data_outgoing_size(void *user_data, int *size)
{
    uint32_t id = (uint32_t)user_data;
    int ret = FALSE;
    *size = 0;
    lock_slot(&slot_lock);
    rfc_slot_t* rs = find_rfc_slot_by_id(id);
    if(rs)
    {
        if(ioctl(rs->fd, FIONREAD, size) == 0)
        {
            APPL_TRACE_DEBUG2("ioctl read avaiable size:%d, fd:%d", *size, rs->fd);
            ret = TRUE;
        }
        else
        {
            APPL_TRACE_ERROR2("ioctl FIONREAD error, errno:%d, fd:%d", errno, rs->fd);
            cleanup_rfc_slot(rs);
        }
    }
    unlock_slot(&slot_lock);
    return ret;
}
int bta_co_rfc_data_outgoing(void *user_data, UINT8* buf, UINT16 size)
{
    uint32_t id = (uint32_t)user_data;
    int ret = FALSE;
    lock_slot(&slot_lock);
    rfc_slot_t* rs = find_rfc_slot_by_id(id);
    if(rs)
    {
        int received = recv(rs->fd, buf, size, 0);
        if(received == size)
            ret = TRUE;
        else
        {
            APPL_TRACE_ERROR4("recv error, errno:%d, fd:%d, size:%d, received:%d",
                             errno, rs->fd, size, received);
            cleanup_rfc_slot(rs);
        }
    }
    unlock_slot(&slot_lock);
    return ret;
}
//]

