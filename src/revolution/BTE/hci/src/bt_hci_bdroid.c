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
 *  Filename:      bt_hci_bdroid.c
 *
 *  Description:   Bluedroid Bluetooth Host/Controller interface library
 *                 implementation
 *
 ******************************************************************************/

#define LOG_TAG "bt_hci_bdroid"

#include <utils/Log.h>
#include <pthread.h>
#include "bt_hci_bdroid.h"
#include "bt_vendor_lib.h"
#include "utils.h"
#include "hci.h"
#include "userial.h"
#include "bt_utils.h"
#include <sys/prctl.h>

#ifndef BTHC_DBG
#define BTHC_DBG FALSE
#endif

#if (BTHC_DBG == TRUE)
#define BTHCDBG(param, ...) {ALOGD(param, ## __VA_ARGS__);}
#else
#define BTHCDBG(param, ...) {}
#endif

/******************************************************************************
**  Externs
******************************************************************************/

extern bt_vendor_interface_t *bt_vnd_if;
extern int num_hci_cmd_pkts;
void lpm_init(void);
void lpm_cleanup(void);
void lpm_enable(uint8_t turn_on);
void lpm_wake_deassert(void);
void lpm_allow_bt_device_sleep(void);
void lpm_wake_assert(void);
void init_vnd_if(unsigned char *local_bdaddr);
void btsnoop_open(char *p_path);
void btsnoop_close(void);

/******************************************************************************
**  Variables
******************************************************************************/

bt_hc_callbacks_t *bt_hc_cbacks = NULL;
BUFFER_Q tx_q;
tHCI_IF *p_hci_if;

/******************************************************************************
**  Local type definitions
******************************************************************************/

/* Host/Controller lib thread control block */
typedef struct
{
    pthread_t       worker_thread;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
} bt_hc_cb_t;

/******************************************************************************
**  Static Variables
******************************************************************************/

static bt_hc_cb_t hc_cb;
static volatile uint8_t lib_running = 0;
static volatile uint16_t ready_events = 0;
static volatile uint8_t tx_cmd_pkts_pending = FALSE;

/******************************************************************************
**  Functions
******************************************************************************/

static void *bt_hc_worker_thread(void *arg);

void bthc_signal_event(uint16_t event)
{
    pthread_mutex_lock(&hc_cb.mutex);
    ready_events |= event;
    pthread_cond_signal(&hc_cb.cond);
    pthread_mutex_unlock(&hc_cb.mutex);
}

/*****************************************************************************
**
**   BLUETOOTH HOST/CONTROLLER INTERFACE LIBRARY FUNCTIONS
**
*****************************************************************************/

static int init(const bt_hc_callbacks_t* p_cb, unsigned char *local_bdaddr)
{
    pthread_attr_t thread_attr;
    struct sched_param param;
    int policy, result;

    ALOGI("init");

    if (p_cb == NULL)
    {
        ALOGE("init failed with no user callbacks!");
        return BT_HC_STATUS_FAIL;
    }

    /* store reference to user callbacks */
    bt_hc_cbacks = (bt_hc_callbacks_t *) p_cb;

    init_vnd_if(local_bdaddr);

    utils_init();
#ifdef HCI_USE_MCT
    extern tHCI_IF hci_mct_func_table;
    p_hci_if = &hci_mct_func_table;
#else
    extern tHCI_IF hci_h4_func_table;
    p_hci_if = &hci_h4_func_table;
#endif

    p_hci_if->init();

    userial_init();
    lpm_init();

    utils_queue_init(&tx_q);

    if (lib_running)
    {
        ALOGW("init has been called repeatedly without calling cleanup ?");
    }

    lib_running = 1;
    ready_events = 0;
    pthread_mutex_init(&hc_cb.mutex, NULL);
    pthread_cond_init(&hc_cb.cond, NULL);
    pthread_attr_init(&thread_attr);

    if (pthread_create(&hc_cb.worker_thread, &thread_attr, \
                       bt_hc_worker_thread, NULL) != 0)
    {
        ALOGE("pthread_create failed!");
        lib_running = 0;
        return BT_HC_STATUS_FAIL;
    }

    if(pthread_getschedparam(hc_cb.worker_thread, &policy, &param)==0)
    {
        policy = BTHC_LINUX_BASE_POLICY;
#if (BTHC_LINUX_BASE_POLICY!=SCHED_NORMAL)
        param.sched_priority = BTHC_MAIN_THREAD_PRIORITY;
#endif
        result = pthread_setschedparam(hc_cb.worker_thread, policy, &param);
        if (result != 0)
        {
            ALOGW("libbt-hci init: pthread_setschedparam failed (%s)", \
                  strerror(result));
        }
    }

    return BT_HC_STATUS_SUCCESS;
}


/** Chip power control */
static void set_power(bt_hc_chip_power_state_t state)
{
    int pwr_state;

    BTHCDBG("set_power %d", state);

    /* Calling vendor-specific part */
    pwr_state = (state == BT_HC_CHIP_PWR_ON) ? BT_VND_PWR_ON : BT_VND_PWR_OFF;

    if (bt_vnd_if)
        bt_vnd_if->op(BT_VND_OP_POWER_CTRL, &pwr_state);
    else
        ALOGE("vendor lib is missing!");
}


/** Configure low power mode wake state */
static int lpm(bt_hc_low_power_event_t event)
{
    uint8_t status = TRUE;

    switch (event)
    {
        case BT_HC_LPM_DISABLE:
            bthc_signal_event(HC_EVENT_LPM_DISABLE);
            break;

        case BT_HC_LPM_ENABLE:
            bthc_signal_event(HC_EVENT_LPM_ENABLE);
            break;

        case BT_HC_LPM_WAKE_ASSERT:
            bthc_signal_event(HC_EVENT_LPM_WAKE_DEVICE);
            break;

        case BT_HC_LPM_WAKE_DEASSERT:
            bthc_signal_event(HC_EVENT_LPM_ALLOW_SLEEP);
            break;
    }

    return(status == TRUE) ? BT_HC_STATUS_SUCCESS : BT_HC_STATUS_FAIL;
}


/** Called prio to stack initialization */
static void preload(TRANSAC transac)
{
    BTHCDBG("preload");
    bthc_signal_event(HC_EVENT_PRELOAD);
}


/** Called post stack initialization */
static void postload(TRANSAC transac)
{
    BTHCDBG("postload");
    bthc_signal_event(HC_EVENT_POSTLOAD);
}


/** Transmit frame */
static int transmit_buf(TRANSAC transac, char *p_buf, int len)
{
    utils_enqueue(&tx_q, (void *) transac);

    bthc_signal_event(HC_EVENT_TX);

    return BT_HC_STATUS_SUCCESS;
}


/** Controls receive flow */
static int set_rxflow(bt_rx_flow_state_t state)
{
    BTHCDBG("set_rxflow %d", state);

    userial_ioctl(\
     ((state == BT_RXFLOW_ON) ? USERIAL_OP_RXFLOW_ON : USERIAL_OP_RXFLOW_OFF), \
     NULL);

    return BT_HC_STATUS_SUCCESS;
}


/** Controls HCI logging on/off */
static int logging(bt_hc_logging_state_t state, char *p_path)
{
    BTHCDBG("logging %d", state);

    if (state == BT_HC_LOGGING_ON)
    {
        if (p_path != NULL)
            btsnoop_open(p_path);
    }
    else
    {
        btsnoop_close();
    }

    return BT_HC_STATUS_SUCCESS;
}


/** Closes the interface */
static void cleanup( void )
{
    BTHCDBG("cleanup");

    if (lib_running)
    {
        lib_running = 0;
        bthc_signal_event(HC_EVENT_EXIT);
        pthread_join(hc_cb.worker_thread, NULL);
    }

    lpm_cleanup();
    userial_close();
    p_hci_if->cleanup();
    utils_cleanup();

    /* Calling vendor-specific part */
    if (bt_vnd_if)
        bt_vnd_if->cleanup();

    bt_hc_cbacks = NULL;
}


static const bt_hc_interface_t bluetoothHCLibInterface = {
    sizeof(bt_hc_interface_t),
    init,
    set_power,
    lpm,
    preload,
    postload,
    transmit_buf,
    set_rxflow,
    logging,
    cleanup
};


/*******************************************************************************
**
** Function        bt_hc_worker_thread
**
** Description     Mian worker thread
**
** Returns         void *
**
*******************************************************************************/
static void *bt_hc_worker_thread(void *arg)
{
    uint16_t events;
    HC_BT_HDR *p_msg, *p_next_msg;

    ALOGI("bt_hc_worker_thread started");
    prctl(PR_SET_NAME, (unsigned long)"bt_hc_worker", 0, 0, 0);
    tx_cmd_pkts_pending = FALSE;

    raise_priority_a2dp(TASK_HIGH_HCI_WORKER);

    while (lib_running)
    {
        pthread_mutex_lock(&hc_cb.mutex);
        while (ready_events == 0)
        {
            pthread_cond_wait(&hc_cb.cond, &hc_cb.mutex);
        }
        events = ready_events;
        ready_events = 0;
        pthread_mutex_unlock(&hc_cb.mutex);

#ifndef HCI_USE_MCT
        if (events & HC_EVENT_RX)
        {
            p_hci_if->rcv();

            if ((tx_cmd_pkts_pending == TRUE) && (num_hci_cmd_pkts > 0))
            {
                /* Got HCI Cmd Credits from Controller.
                 * Prepare to send prior pending Cmd packets in the
                 * following HC_EVENT_TX session.
                 */
                events |= HC_EVENT_TX;
            }
        }
#endif

        if (events & HC_EVENT_PRELOAD)
        {
            userial_open(USERIAL_PORT_1);

            /* Calling vendor-specific part */
            if (bt_vnd_if)
            {
                bt_vnd_if->op(BT_VND_OP_FW_CFG, NULL);
            }
            else
            {
                if (bt_hc_cbacks)
                    bt_hc_cbacks->preload_cb(NULL, BT_HC_PRELOAD_FAIL);
            }
        }

        if (events & HC_EVENT_POSTLOAD)
        {
            /* Start from SCO related H/W configuration, if SCO configuration
             * is required. Then, follow with reading requests of getting
             * ACL data length for both BR/EDR and LE.
             */
            int result = -1;

            /* Calling vendor-specific part */
            if (bt_vnd_if)
                result = bt_vnd_if->op(BT_VND_OP_SCO_CFG, NULL);

            if (result == -1)
                p_hci_if->get_acl_max_len();
        }

        if (events & HC_EVENT_TX)
        {
            /*
             *  We will go through every packets in the tx queue.
             *  Fine to clear tx_cmd_pkts_pending.
             */
            tx_cmd_pkts_pending = FALSE;
            HC_BT_HDR * sending_msg_que[64];
            int sending_msg_count = 0;
            utils_lock();
            p_next_msg = tx_q.p_first;
            while (p_next_msg && sending_msg_count <
                            (int)sizeof(sending_msg_que)/sizeof(sending_msg_que[0]))
            {
                if ((p_next_msg->event & MSG_EVT_MASK)==MSG_STACK_TO_HC_HCI_CMD)
                {
                    /*
                     *  if we have used up controller's outstanding HCI command
                     *  credits (normally is 1), skip all HCI command packets in
                     *  the queue.
                     *  The pending command packets will be sent once controller
                     *  gives back us credits through CommandCompleteEvent or
                     *  CommandStatusEvent.
                     */
                    if ((tx_cmd_pkts_pending == TRUE) || (num_hci_cmd_pkts <= 0))
                    {
                        tx_cmd_pkts_pending = TRUE;
                        p_next_msg = utils_getnext(p_next_msg);
                        continue;
                    }
                }

                p_msg = p_next_msg;
                p_next_msg = utils_getnext(p_msg);
                utils_remove_from_queue_unlocked(&tx_q, p_msg);
                sending_msg_que[sending_msg_count++] = p_msg;
            }
            utils_unlock();
            int i;
            for(i = 0; i < sending_msg_count; i++)
                p_hci_if->send(sending_msg_que[i]);
            if (tx_cmd_pkts_pending == TRUE)
                BTHCDBG("Used up Tx Cmd credits");

        }

        if (events & HC_EVENT_LPM_ENABLE)
        {
            lpm_enable(TRUE);
        }

        if (events & HC_EVENT_LPM_DISABLE)
        {
            lpm_enable(FALSE);
        }

        if (events & HC_EVENT_LPM_IDLE_TIMEOUT)
        {
            lpm_wake_deassert();
        }

        if (events & HC_EVENT_LPM_ALLOW_SLEEP)
        {
            lpm_allow_bt_device_sleep();
        }

        if (events & HC_EVENT_LPM_WAKE_DEVICE)
        {
            lpm_wake_assert();
        }

        if (events & HC_EVENT_EXIT)
            break;
    }

    ALOGI("bt_hc_worker_thread exiting");

    pthread_exit(NULL);

    return NULL;    // compiler friendly
}


/*******************************************************************************
**
** Function        bt_hc_get_interface
**
** Description     Caller calls this function to get API instance
**
** Returns         API table
**
*******************************************************************************/
const bt_hc_interface_t *bt_hc_get_interface(void)
{
    return &bluetoothHCLibInterface;
}

