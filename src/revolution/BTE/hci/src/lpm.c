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
 *  Filename:      lpm.c
 *
 *  Description:   Contains low power mode implementation
 *
 ******************************************************************************/

#define LOG_TAG "bt_lpm"

#include <utils/Log.h>
#include <signal.h>
#include <time.h>
#include "bt_hci_bdroid.h"
#include "bt_vendor_lib.h"

/******************************************************************************
**  Constants & Macros
******************************************************************************/

#ifndef BTLPM_DBG
#define BTLPM_DBG FALSE
#endif

#if (BTLPM_DBG == TRUE)
#define BTLPMDBG(param, ...) {ALOGD(param, ## __VA_ARGS__);}
#else
#define BTLPMDBG(param, ...) {}
#endif

#ifndef DEFAULT_LPM_IDLE_TIMEOUT
#define DEFAULT_LPM_IDLE_TIMEOUT    3000
#endif

/******************************************************************************
**  Externs
******************************************************************************/

extern bt_vendor_interface_t *bt_vnd_if;

/******************************************************************************
**  Local type definitions
******************************************************************************/

/* Low power mode state */
enum {
    LPM_DISABLED = 0,                    /* initial state */
    LPM_ENABLED,
    LPM_ENABLING,
    LPM_DISABLING
};

/* LPM WAKE state */
enum {
    LPM_WAKE_DEASSERTED = 0,              /* initial state */
    LPM_WAKE_W4_TX_DONE,
    LPM_WAKE_W4_TIMEOUT,
    LPM_WAKE_ASSERTED
};

/* low power mode control block */
typedef struct
{
    uint8_t state;                          /* Low power mode state */
    uint8_t wake_state;                     /* LPM WAKE state */
    uint8_t no_tx_data;
    uint8_t timer_created;
    timer_t timer_id;
    uint32_t timeout_ms;
} bt_lpm_cb_t;


/******************************************************************************
**  Static variables
******************************************************************************/

static bt_lpm_cb_t bt_lpm_cb;

/******************************************************************************
**   LPM Static Functions
******************************************************************************/

/*******************************************************************************
**
** Function        lpm_idle_timeout
**
** Description     Timeout thread of transport idle timer
**
** Returns         None
**
*******************************************************************************/
static void lpm_idle_timeout(union sigval arg)
{
    BTLPMDBG("..lpm_idle_timeout..");

    if ((bt_lpm_cb.state == LPM_ENABLED) && \
        (bt_lpm_cb.wake_state == LPM_WAKE_W4_TIMEOUT))
    {
        bthc_signal_event(HC_EVENT_LPM_IDLE_TIMEOUT);
    }
}

/*******************************************************************************
**
** Function        lpm_start_transport_idle_timer
**
** Description     Launch transport idle timer
**
** Returns         None
**
*******************************************************************************/
static void lpm_start_transport_idle_timer(void)
{
    int status;
    struct itimerspec ts;
    struct sigevent se;

    if (bt_lpm_cb.state != LPM_ENABLED)
        return;

    if (bt_lpm_cb.timer_created == FALSE)
    {
        se.sigev_notify = SIGEV_THREAD;
        se.sigev_value.sival_ptr = &bt_lpm_cb.timer_id;
        se.sigev_notify_function = lpm_idle_timeout;
        se.sigev_notify_attributes = NULL;

        status = timer_create(CLOCK_MONOTONIC, &se, &bt_lpm_cb.timer_id);

        if (status == 0)
            bt_lpm_cb.timer_created = TRUE;
    }

    if (bt_lpm_cb.timer_created == TRUE)
    {
        ts.it_value.tv_sec = bt_lpm_cb.timeout_ms/1000;
        ts.it_value.tv_nsec = 1000*(bt_lpm_cb.timeout_ms%1000);
        ts.it_interval.tv_sec = 0;
        ts.it_interval.tv_nsec = 0;

        status = timer_settime(bt_lpm_cb.timer_id, 0, &ts, 0);
        if (status == -1)
            ALOGE("[START] Failed to set LPM idle timeout");
    }
}

/*******************************************************************************
**
** Function        lpm_stop_transport_idle_timer
**
** Description     Launch transport idle timer
**
** Returns         None
**
*******************************************************************************/
static void lpm_stop_transport_idle_timer(void)
{
    int status;
    struct itimerspec ts;

    if (bt_lpm_cb.timer_created == TRUE)
    {
        ts.it_value.tv_sec = 0;
        ts.it_value.tv_nsec = 0;
        ts.it_interval.tv_sec = 0;
        ts.it_interval.tv_nsec = 0;

        status = timer_settime(bt_lpm_cb.timer_id, 0, &ts, 0);
        if (status == -1)
            ALOGE("[STOP] Failed to set LPM idle timeout");
    }
}

/*******************************************************************************
**
** Function         lpm_vnd_cback
**
** Description      Callback of vendor specific result for lpm enable/disable
**                  rquest
**
** Returns          None
**
*******************************************************************************/
void lpm_vnd_cback(uint8_t vnd_result)
{
    if (vnd_result == 0)
    {
        /* Status == Success */
        bt_lpm_cb.state = (bt_lpm_cb.state == LPM_ENABLING) ? \
                          LPM_ENABLED : LPM_DISABLED;
    }
    else
    {
        bt_lpm_cb.state = (bt_lpm_cb.state == LPM_ENABLING) ? \
                          LPM_DISABLED : LPM_ENABLED;
    }

    if (bt_hc_cbacks)
    {
        if (bt_lpm_cb.state == LPM_ENABLED)
            bt_hc_cbacks->lpm_cb(BT_HC_LPM_ENABLED);
        else
            bt_hc_cbacks->lpm_cb(BT_HC_LPM_DISABLED);
    }

    if (bt_lpm_cb.state == LPM_DISABLED)
    {
        if (bt_lpm_cb.timer_created == TRUE)
        {
            timer_delete(bt_lpm_cb.timer_id);
        }

        memset(&bt_lpm_cb, 0, sizeof(bt_lpm_cb_t));
    }
}


/*****************************************************************************
**   Low Power Mode Interface Functions
*****************************************************************************/

/*******************************************************************************
**
** Function        lpm_init
**
** Description     Init LPM
**
** Returns         None
**
*******************************************************************************/
void lpm_init(void)
{
    memset(&bt_lpm_cb, 0, sizeof(bt_lpm_cb_t));

    /* Calling vendor-specific part */
    if (bt_vnd_if)
        bt_vnd_if->op(BT_VND_OP_GET_LPM_IDLE_TIMEOUT, &(bt_lpm_cb.timeout_ms));
    else
        bt_lpm_cb.timeout_ms = DEFAULT_LPM_IDLE_TIMEOUT;
}

/*******************************************************************************
**
** Function        lpm_cleanup
**
** Description     Clean up
**
** Returns         None
**
*******************************************************************************/
void lpm_cleanup(void)
{
    if (bt_lpm_cb.timer_created == TRUE)
    {
        timer_delete(bt_lpm_cb.timer_id);
    }
}

/*******************************************************************************
**
** Function        lpm_enable
**
** Description     Enalbe/Disable LPM
**
** Returns         None
**
*******************************************************************************/
void lpm_enable(uint8_t turn_on)
{
    if ((bt_lpm_cb.state!=LPM_DISABLED) && (bt_lpm_cb.state!=LPM_ENABLED))
    {
        ALOGW("Still busy on processing prior LPM enable/disable request...");
        return;
    }

    if ((turn_on == TRUE) && (bt_lpm_cb.state == LPM_ENABLED))
    {
        ALOGI("LPM is already on!!!");
        if (bt_hc_cbacks)
            bt_hc_cbacks->lpm_cb(BT_HC_LPM_ENABLED);
    }
    else if ((turn_on == FALSE) && (bt_lpm_cb.state == LPM_DISABLED))
    {
        ALOGI("LPM is already off!!!");
        if (bt_hc_cbacks)
            bt_hc_cbacks->lpm_cb(BT_HC_LPM_DISABLED);
    }

    /* Calling vendor-specific part */
    if (bt_vnd_if)
    {
        uint8_t lpm_cmd = (turn_on) ? BT_VND_LPM_ENABLE : BT_VND_LPM_DISABLE;
        bt_lpm_cb.state = (turn_on) ? LPM_ENABLING : LPM_DISABLING;
        bt_vnd_if->op(BT_VND_OP_LPM_SET_MODE, &lpm_cmd);
    }
}

/*******************************************************************************
**
** Function          lpm_tx_done
**
** Description       This function is to inform the lpm module
**                   if data is waiting in the Tx Q or not.
**
**                   IsTxDone: TRUE if All data in the Tx Q are gone
**                             FALSE if any data is still in the Tx Q.
**                   Typicaly this function must be called
**                   before USERIAL Write and in the Tx Done routine
**
** Returns           None
**
*******************************************************************************/
void lpm_tx_done(uint8_t is_tx_done)
{
    bt_lpm_cb.no_tx_data = is_tx_done;

    if ((bt_lpm_cb.wake_state==LPM_WAKE_W4_TX_DONE) && (is_tx_done==TRUE))
    {
        bt_lpm_cb.wake_state = LPM_WAKE_W4_TIMEOUT;
        lpm_start_transport_idle_timer();
    }
}

/*******************************************************************************
**
** Function        lpm_wake_assert
**
** Description     Called to wake up Bluetooth chip.
**                 Normally this is called when there is data to be sent
**                 over UART.
**
** Returns         TRUE/FALSE
**
*******************************************************************************/
void lpm_wake_assert(void)
{
    if (bt_lpm_cb.state != LPM_DISABLED)
    {
        BTLPMDBG("LPM WAKE assert");

        /* Calling vendor-specific part */
        if (bt_vnd_if)
        {
            uint8_t state = BT_VND_LPM_WAKE_ASSERT;
            bt_vnd_if->op(BT_VND_OP_LPM_WAKE_SET_STATE, &state);
        }

        lpm_stop_transport_idle_timer();

        bt_lpm_cb.wake_state = LPM_WAKE_ASSERTED;
    }

    lpm_tx_done(FALSE);
}

/*******************************************************************************
**
** Function        lpm_allow_bt_device_sleep
**
** Description     Start LPM idle timer if allowed
**
** Returns         None
**
*******************************************************************************/
void lpm_allow_bt_device_sleep(void)
{
    if ((bt_lpm_cb.state == LPM_ENABLED) && \
        (bt_lpm_cb.wake_state == LPM_WAKE_ASSERTED))
    {
        if(bt_lpm_cb.no_tx_data == TRUE)
        {
            bt_lpm_cb.wake_state = LPM_WAKE_W4_TIMEOUT;
            lpm_start_transport_idle_timer();
        }
        else
        {
            bt_lpm_cb.wake_state = LPM_WAKE_W4_TX_DONE;
        }
    }
}

/*******************************************************************************
**
** Function         lpm_wake_deassert
**
** Description      Deassert wake if allowed
**
** Returns          None
**
*******************************************************************************/
void lpm_wake_deassert(void)
{
    if ((bt_lpm_cb.state == LPM_ENABLED) && (bt_lpm_cb.no_tx_data == TRUE))
    {
        BTLPMDBG("LPM WAKE deassert");

        /* Calling vendor-specific part */
        if (bt_vnd_if)
        {
            uint8_t state = BT_VND_LPM_WAKE_DEASSERT;
            bt_vnd_if->op(BT_VND_OP_LPM_WAKE_SET_STATE, &state);
        }

        bt_lpm_cb.wake_state = LPM_WAKE_DEASSERTED;
    }
}

