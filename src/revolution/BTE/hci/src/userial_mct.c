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
 *  Filename:      userial_mct.c
 *
 *  Description:   Contains open/read/write/close functions on multi-channels
 *
 ******************************************************************************/

#define LOG_TAG "bt_userial_mct"

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

/******************************************************************************
**  Constants & Macros
******************************************************************************/

#define USERIAL_DBG TRUE

#ifndef USERIAL_DBG
#define USERIAL_DBG FALSE
#endif

#if (USERIAL_DBG == TRUE)
#define USERIALDBG(param, ...) {ALOGD(param, ## __VA_ARGS__);}
#else
#define USERIALDBG(param, ...) {}
#endif

#define MAX_SERIAL_PORT (USERIAL_PORT_3 + 1)

enum {
    USERIAL_RX_EXIT,
    USERIAL_RX_FLOW_OFF,
    USERIAL_RX_FLOW_ON
};

/******************************************************************************
**  Externs
******************************************************************************/

extern bt_vendor_interface_t *bt_vnd_if;
uint16_t hci_mct_receive_evt_msg(void);
uint16_t hci_mct_receive_acl_msg(void);


/******************************************************************************
**  Local type definitions
******************************************************************************/

typedef struct
{
    int             fd[CH_MAX];
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
** Function        userial_evt_read_thread
**
** Description     The reading thread on EVT and ACL_IN channels
**
** Returns         void *
**
*******************************************************************************/
static void *userial_read_thread(void *arg)
{
    fd_set input;
    int n;
    char reason = 0;

    USERIALDBG("Entering userial_read_thread()");

    rx_flow_on = TRUE;
    userial_running = 1;

    while (userial_running)
    {
        /* Initialize the input fd set */
        FD_ZERO(&input);
        if (rx_flow_on == TRUE)
        {
            FD_SET(userial_cb.fd[CH_EVT], &input);
            FD_SET(userial_cb.fd[CH_ACL_IN], &input);
        }

        int fd_max = create_signal_fds(&input);
        fd_max = (fd_max>userial_cb.fd[CH_EVT]) ? fd_max : userial_cb.fd[CH_EVT];
        fd_max = (fd_max>userial_cb.fd[CH_ACL_IN]) ? fd_max : userial_cb.fd[CH_ACL_IN];

        /* Do the select */
        n = 0;
        n = select(fd_max+1, &input, NULL, NULL, NULL);
        if(is_signaled(&input))
        {
            reason = reset_signal();
            if (reason == USERIAL_RX_EXIT)
            {
                ALOGI("exiting userial_read_thread");
                userial_running = 0;
                break;
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
            if (FD_ISSET(userial_cb.fd[CH_EVT], &input))
            {
                hci_mct_receive_evt_msg();
            }

            if (FD_ISSET(userial_cb.fd[CH_ACL_IN], &input))
            {
                hci_mct_receive_acl_msg();
            }
        }
        else if (n < 0)
            ALOGW( "select() Failed");
        else if (n == 0)
            ALOGW( "Got a select() TIMEOUT");
    } /* while */

    userial_running = 0;
    USERIALDBG("Leaving userial_evt_read_thread()");
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
    int idx;

    USERIALDBG("userial_init");
    memset(&userial_cb, 0, sizeof(tUSERIAL_CB));
    for (idx=0; idx < CH_MAX; idx++)
        userial_cb.fd[idx] = -1;
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
        result = bt_vnd_if->op(BT_VND_OP_USERIAL_OPEN, &userial_cb.fd);

        if ((result != 2) && (result != 4))
        {
            ALOGE("userial_open: wrong numbers of open fd in vendor lib [%d]!",
                    result);
            ALOGE("userial_open: HCI MCT expects 2 or 4 open file descriptors");
            bt_vnd_if->op(BT_VND_OP_USERIAL_CLOSE, NULL);
            return FALSE;
        }
    }
    else
    {
        ALOGE("userial_open: missing vendor lib interface !!!");
        ALOGE("userial_open: unable to open BT transport");
        return FALSE;
    }

    ALOGI("CMD=%d, EVT=%d, ACL_Out=%d, ACL_In=%d", \
        userial_cb.fd[CH_CMD], userial_cb.fd[CH_EVT], \
        userial_cb.fd[CH_ACL_OUT], userial_cb.fd[CH_ACL_IN]);

    if ((userial_cb.fd[CH_CMD] == -1) || (userial_cb.fd[CH_EVT] == -1) ||
        (userial_cb.fd[CH_ACL_OUT] == -1) || (userial_cb.fd[CH_ACL_IN] == -1))
    {
        ALOGE("userial_open: failed to open BT transport");
        bt_vnd_if->op(BT_VND_OP_USERIAL_CLOSE, NULL);
        return FALSE;
    }

    userial_cb.port = port;

    /* Start listening thread */
    pthread_attr_init(&thread_attr);

    if (pthread_create(&(userial_cb.read_thread), &thread_attr, \
                       userial_read_thread, NULL) != 0 )
    {
        ALOGE("pthread_create failed!");
        bt_vnd_if->op(BT_VND_OP_USERIAL_CLOSE, NULL);
        return FALSE;
    }

    if(pthread_getschedparam(userial_cb.read_thread, &policy, &param)==0)
    {
        policy = BTHC_LINUX_BASE_POLICY;
#if (BTHC_LINUX_BASE_POLICY!=SCHED_NORMAL)
        param.sched_priority = BTHC_USERIAL_READ_THREAD_PRIORITY;
#endif
        result=pthread_setschedparam(userial_cb.read_thread,policy,&param);
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
** Description     Read data from the userial channel
**
** Returns         Number of bytes actually read from the userial port and
**                 copied into p_data.  This may be less than len.
**
*******************************************************************************/
uint16_t  userial_read(uint16_t msg_id, uint8_t *p_buffer, uint16_t len)
{
    int ret = -1;
    int ch_idx = (msg_id == MSG_HC_TO_STACK_HCI_EVT) ? CH_EVT : CH_ACL_IN;

    ret = read(userial_cb.fd[ch_idx], p_buffer, (size_t)len);
    if (ret <= 0)
        ALOGW( "userial_read: read() returned %d!", ret);

    return (uint16_t) ((ret >= 0) ? ret : 0);
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
    int ch_idx = (msg_id == MSG_STACK_TO_HC_HCI_CMD) ? CH_CMD : CH_ACL_OUT;

    while(len != 0)
    {
        ret = write(userial_cb.fd[ch_idx], p_data+total, len);
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
    int idx, result;

    USERIALDBG("userial_close");

    if (userial_running)
        send_wakeup_signal(USERIAL_RX_EXIT);

    if ((result=pthread_join(userial_cb.read_thread, NULL)) < 0)
        ALOGE( "pthread_join() FAILED result:%d", result);

    /* Calling vendor-specific part */
    if (bt_vnd_if)
        bt_vnd_if->op(BT_VND_OP_USERIAL_CLOSE, NULL);

    for (idx=0; idx < CH_MAX; idx++)
        userial_cb.fd[idx] = -1;
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

