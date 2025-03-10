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

/******************************************************************************
 *
 *  Filename:      userial.c
 *
 *  Description:   Contains open/read/write/close functions on serial port
 *
 ******************************************************************************/

#define LOG_TAG "bt_userial"

#include <utils/Log.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include "bt_hci_bdroid.h"
#include "userial.h"
#include "utils.h"
#include "bt_vendor_lib.h"
#include <sys/prctl.h>

/******************************************************************************
**  Constants & Macros
******************************************************************************/

#ifndef USERIAL_DBG
#define USERIAL_DBG FALSE
#endif

#if (USERIAL_DBG == TRUE)
#define USERIALDBG(param, ...) {ALOGD(param, ## __VA_ARGS__);}
#else
#define USERIALDBG(param, ...) {}
#endif

#define MAX_SERIAL_PORT (USERIAL_PORT_3 + 1)
#define READ_LIMIT (BTHC_USERIAL_READ_MEM_SIZE - BT_HC_HDR_SIZE)

enum {
    USERIAL_RX_EXIT,
    USERIAL_RX_FLOW_OFF,
    USERIAL_RX_FLOW_ON
};

/******************************************************************************
**  Externs
******************************************************************************/

extern bt_vendor_interface_t *bt_vnd_if;

/******************************************************************************
**  Local type definitions
******************************************************************************/

typedef struct
{
    int             fd;
    uint8_t         port;
    pthread_t       read_thread;
    BUFFER_Q        rx_q;
    HC_BT_HDR      *p_rx_hdr;
} tUSERIAL_CB;

/******************************************************************************
**  Static variables
******************************************************************************/

static tUSERIAL_CB userial_cb;
static volatile uint8_t userial_running = 0;

/******************************************************************************
**  Static functions
******************************************************************************/

/*****************************************************************************
**   Socket signal functions to wake up userial_read_thread for termination
**
**   creating an unnamed pair of connected sockets
**      - signal_fds[0]: join fd_set in select call of userial_read_thread
**      - signal_fds[1]: trigger from userial_close
*****************************************************************************/
static int signal_fds[2]={0,1};
static uint8_t rx_flow_on = TRUE;
static inline int create_signal_fds(fd_set* set)
{
    if(signal_fds[0]==0 && socketpair(AF_UNIX, SOCK_STREAM, 0, signal_fds)<0)
    {
        ALOGE("create_signal_sockets:socketpair failed, errno: %d", errno);
        return -1;
    }
    FD_SET(signal_fds[0], set);
    return signal_fds[0];
}
static inline int send_wakeup_signal(char sig_cmd)
{
    return send(signal_fds[1], &sig_cmd, sizeof(sig_cmd), 0);
}
static inline char reset_signal()
{
    char sig_recv = -1;
    recv(signal_fds[0], &sig_recv, sizeof(sig_recv), MSG_WAITALL);
    return sig_recv;
}
static inline int is_signaled(fd_set* set)
{
    return FD_ISSET(signal_fds[0], set);
}

/*******************************************************************************
**
** Function        select_read
**
** Description     check if fd is ready for reading and listen for termination
**                  signal. need to use select in order to avoid collision
**                  between read and close on the same fd
**
** Returns         -1: termination
**                 >=0: numbers of bytes read back from fd
**
*******************************************************************************/
static int select_read(int fd, uint8_t *pbuf, int len)
{
    fd_set input;
    int n = 0, ret = -1;
    char reason = 0;

    while (userial_running)
    {
        /* Initialize the input fd set */
        FD_ZERO(&input);
        if (rx_flow_on == TRUE)
        {
            FD_SET(fd, &input);
        }
        int fd_max = create_signal_fds(&input);
        fd_max = fd_max > fd ? fd_max : fd;

        /* Do the select */
        n = select(fd_max+1, &input, NULL, NULL, NULL);
        if(is_signaled(&input))
        {
            reason = reset_signal();
            if (reason == USERIAL_RX_EXIT)
            {
                USERIALDBG("RX termination");
                return -1;
            }
            else if (reason == USERIAL_RX_FLOW_OFF)
            {
                USERIALDBG("RX flow OFF");
                rx_flow_on = FALSE;
            }
            else if (reason == USERIAL_RX_FLOW_ON)
            {
                USERIALDBG("RX flow ON");
                rx_flow_on = TRUE;
            }
        }

        if (n > 0)
        {
            /* We might have input */
            if (FD_ISSET(fd, &input))
            {
                ret = read(fd, pbuf, (size_t)len);
                if (0 == ret)
                    ALOGW( "read() returned 0!" );

                return ret;
            }
        }
        else if (n < 0)
            ALOGW( "select() Failed");
        else if (n == 0)
            ALOGW( "Got a select() TIMEOUT");

    }

    return ret;
}

/*******************************************************************************
**
** Function        userial_read_thread
**
** Description
**
** Returns         void *
**
*******************************************************************************/
static void *userial_read_thread(void *arg)
{
    int rx_length = 0;
    HC_BT_HDR *p_buf = NULL;
    uint8_t *p;

    USERIALDBG("Entering userial_read_thread()");
    prctl(PR_SET_NAME, (unsigned long)"userial_read", 0, 0, 0);

    rx_flow_on = TRUE;
    userial_running = 1;

    while (userial_running)
    {
        if (bt_hc_cbacks)
        {
            p_buf = (HC_BT_HDR *) bt_hc_cbacks->alloc( \
                                                BTHC_USERIAL_READ_MEM_SIZE);
        }
        else
            p_buf = NULL;

        if (p_buf != NULL)
        {
            p_buf->offset = 0;
            p_buf->layer_specific = 0;

            p = (uint8_t *) (p_buf + 1);
            rx_length = select_read(userial_cb.fd, p, READ_LIMIT);
        }
        else
        {
            rx_length = 0;
            utils_delay(100);
            ALOGW("userial_read_thread() failed to gain buffers");
            continue;
        }


        if (rx_length > 0)
        {
            p_buf->len = (uint16_t)rx_length;
            utils_enqueue(&(userial_cb.rx_q), p_buf);
            bthc_signal_event(HC_EVENT_RX);
        }
        else /* either 0 or < 0 */
        {
            ALOGW("select_read return size <=0:%d, exiting userial_read_thread",\
                 rx_length);
            /* if we get here, we should have a buffer */
            bt_hc_cbacks->dealloc((TRANSAC) p_buf, (char *) (p_buf + 1));
            /* negative value means exit thread */
            break;
        }
    } /* for */

    userial_running = 0;
    USERIALDBG("Leaving userial_read_thread()");
    pthread_exit(NULL);

    return NULL;    // Compiler friendly
}


/*****************************************************************************
**   Userial API Functions
*****************************************************************************/

/*******************************************************************************
**
** Function        userial_init
**
** Description     Initializes the userial driver
**
** Returns         TRUE/FALSE
**
*******************************************************************************/
uint8_t userial_init(void)
{
    USERIALDBG("userial_init");
    memset(&userial_cb, 0, sizeof(tUSERIAL_CB));
    userial_cb.fd = -1;
    utils_queue_init(&(userial_cb.rx_q));
    return TRUE;
}


/*******************************************************************************
**
** Function        userial_open
**
** Description     Open Bluetooth device with the port ID
**
** Returns         TRUE/FALSE
**
*******************************************************************************/
uint8_t userial_open(uint8_t port)
{
    struct sched_param param;
    int policy, result;
    pthread_attr_t thread_attr;
    int fd_array[CH_MAX];

    USERIALDBG("userial_open(port:%d)", port);

    if (userial_running)
    {
        /* Userial is open; close it first */
        userial_close();
        utils_delay(50);
    }

    if (port >= MAX_SERIAL_PORT)
    {
        ALOGE("Port > MAX_SERIAL_PORT");
        return FALSE;
    }

    /* Calling vendor-specific part */
    if (bt_vnd_if)
    {
        result = bt_vnd_if->op(BT_VND_OP_USERIAL_OPEN, &fd_array);

        if (result != 1)
        {
            ALOGE("userial_open: wrong numbers of open fd in vendor lib [%d]!",
                    result);
            ALOGE("userial_open: HCI UART expects only one open fd");
            bt_vnd_if->op(BT_VND_OP_USERIAL_CLOSE, NULL);
            return FALSE;
        }

        userial_cb.fd = fd_array[0];
    }
    else
    {
        ALOGE("userial_open: missing vendor lib interface !!!");
        ALOGE("userial_open: unable to open UART port");
        return FALSE;
    }

    if (userial_cb.fd == -1)
    {
        ALOGE("userial_open: failed to open UART port");
        return FALSE;
    }

    USERIALDBG( "fd = %d", userial_cb.fd);

    userial_cb.port = port;

    pthread_attr_init(&thread_attr);

    if (pthread_create(&(userial_cb.read_thread), &thread_attr, \
                       userial_read_thread, NULL) != 0 )
    {
        ALOGE("pthread_create failed!");
        return FALSE;
    }

    if(pthread_getschedparam(userial_cb.read_thread, &policy, &param)==0)
    {
        policy = BTHC_LINUX_BASE_POLICY;
#if (BTHC_LINUX_BASE_POLICY!=SCHED_NORMAL)
        param.sched_priority = BTHC_USERIAL_READ_THREAD_PRIORITY;
#endif
        result = pthread_setschedparam(userial_cb.read_thread, policy, &param);
        if (result != 0)
        {
            ALOGW("userial_open: pthread_setschedparam failed (%s)", \
                  strerror(result));
        }
    }

    return TRUE;
}

/*******************************************************************************
**
** Function        userial_read
**
** Description     Read data from the userial port
**
** Returns         Number of bytes actually read from the userial port and
**                 copied into p_data.  This may be less than len.
**
*******************************************************************************/
uint16_t  userial_read(uint16_t msg_id, uint8_t *p_buffer, uint16_t len)
{
    uint16_t total_len = 0;
    uint16_t copy_len = 0;
    uint8_t *p_data = NULL;

    do
    {
        if(userial_cb.p_rx_hdr != NULL)
        {
            p_data = ((uint8_t *)(userial_cb.p_rx_hdr + 1)) + \
                     (userial_cb.p_rx_hdr->offset);

            if((userial_cb.p_rx_hdr->len) <= (len - total_len))
                copy_len = userial_cb.p_rx_hdr->len;
            else
                copy_len = (len - total_len);

            memcpy((p_buffer + total_len), p_data, copy_len);

            total_len += copy_len;

            userial_cb.p_rx_hdr->offset += copy_len;
            userial_cb.p_rx_hdr->len -= copy_len;

            if(userial_cb.p_rx_hdr->len == 0)
            {
                if (bt_hc_cbacks)
                    bt_hc_cbacks->dealloc((TRANSAC) userial_cb.p_rx_hdr, \
                                              (char *) (userial_cb.p_rx_hdr+1));

                userial_cb.p_rx_hdr = NULL;
            }
        }

        if(userial_cb.p_rx_hdr == NULL)
        {
            userial_cb.p_rx_hdr=(HC_BT_HDR *)utils_dequeue(&(userial_cb.rx_q));
        }
    } while ((userial_cb.p_rx_hdr != NULL) && (total_len < len));

    return total_len;
}

/*******************************************************************************
**
** Function        userial_write
**
** Description     Write data to the userial port
**
** Returns         Number of bytes actually written to the userial port. This
**                 may be less than len.
**
*******************************************************************************/
uint16_t userial_write(uint16_t msg_id, uint8_t *p_data, uint16_t len)
{
    int ret, total = 0;

    while(len != 0)
    {
        ret = write(userial_cb.fd, p_data+total, len);
        total += ret;
        len -= ret;
    }

    return ((uint16_t)total);
}

/*******************************************************************************
**
** Function        userial_close
**
** Description     Close the userial port
**
** Returns         None
**
*******************************************************************************/
void userial_close(void)
{
    int result;
    TRANSAC p_buf;

    USERIALDBG("userial_close(fd:%d)", userial_cb.fd);

    if (userial_running)
        send_wakeup_signal(USERIAL_RX_EXIT);

    if ((result=pthread_join(userial_cb.read_thread, NULL)) < 0)
        ALOGE( "pthread_join() FAILED result:%d", result);

    /* Calling vendor-specific part */
    if (bt_vnd_if)
        bt_vnd_if->op(BT_VND_OP_USERIAL_CLOSE, NULL);

    userial_cb.fd = -1;

    if (bt_hc_cbacks)
    {
        while ((p_buf = utils_dequeue (&(userial_cb.rx_q))) != NULL)
        {
            bt_hc_cbacks->dealloc(p_buf, (char *) ((HC_BT_HDR *)p_buf+1));
        }
    }
}

/*******************************************************************************
**
** Function        userial_ioctl
**
** Description     ioctl inteface
**
** Returns         None
**
*******************************************************************************/
void userial_ioctl(userial_ioctl_op_t op, void *p_data)
{
    switch(op)
    {
        case USERIAL_OP_RXFLOW_ON:
            if (userial_running)
                send_wakeup_signal(USERIAL_RX_FLOW_ON);
            break;

        case USERIAL_OP_RXFLOW_OFF:
            if (userial_running)
                send_wakeup_signal(USERIAL_RX_FLOW_OFF);
            break;

        case USERIAL_OP_INIT:
        default:
            break;
    }
}

