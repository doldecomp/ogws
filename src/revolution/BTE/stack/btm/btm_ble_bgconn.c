/******************************************************************************
 *
 *  Copyright (C) 1999-2012 Broadcom Corporation
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
 *  This file contains functions for BLE whitelist operation.
 *
 ******************************************************************************/

#include <string.h>

#include "bt_types.h"
#include "btu.h"
#include "btm_int.h"
#include "l2c_int.h"
#include "hcimsgs.h"

#ifndef BTM_BLE_SCAN_PARAM_TOUT
#define BTM_BLE_SCAN_PARAM_TOUT      50    /* 50 seconds */
#endif

#if (BLE_INCLUDED == TRUE)
/*******************************************************************************
**
** Function         btm_update_scanner_filter_policy
**
** Description      This function update the filter policy of scnner or advertiser.
*******************************************************************************/
void btm_update_scanner_filter_policy(tBTM_BLE_SFP scan_policy)
{
    tBTM_BLE_INQ_CB *p_inq = &btm_cb.ble_ctr_cb.inq_var;
    BTM_TRACE_EVENT0 ("btm_update_scanner_filter_policy");
    btm_cb.ble_ctr_cb.inq_var.sfp = scan_policy;

    btsnd_hcic_ble_set_scan_params ((UINT8)((p_inq->scan_type == BTM_BLE_SCAN_MODE_NONE) ? BTM_BLE_SCAN_MODE_ACTI: p_inq->scan_type),
                                    (UINT16)(!p_inq->scan_interval ? BTM_BLE_GAP_DISC_SCAN_INT : p_inq->scan_interval),
                                    (UINT16)(!p_inq->scan_window ? BTM_BLE_GAP_DISC_SCAN_WIN : p_inq->scan_window),
                                     BLE_ADDR_PUBLIC,
                                     scan_policy);
}
/*******************************************************************************
**
** Function         btm_update_adv_filter_policy
**
** Description      This function update the filter policy of scnner or advertiser.
*******************************************************************************/
void btm_update_adv_filter_policy(tBTM_BLE_AFP adv_policy)
{
    tBTM_BLE_INQ_CB *p_cb = &btm_cb.ble_ctr_cb.inq_var;
    BTM_TRACE_EVENT0 ("btm_update_adv_filter_policy");
    p_cb->afp = adv_policy;
}
/*******************************************************************************
**
** Function         btm_update_dev_to_white_list
**
** Description      This function adds a device into white list.
*******************************************************************************/
BOOLEAN btm_update_dev_to_white_list(BOOLEAN to_add, BD_ADDR bd_addr, tBLE_ADDR_TYPE addr_type)
{
    /* look up the sec device record, and find the address */
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    tBTM_SEC_DEV_REC    *p_dev_rec;
    BD_ADDR             dummy_bda = {0};
    BOOLEAN             started = FALSE, suspend = FALSE;

    if (btm_cb.btm_inq_vars.inq_active)
    {
        suspend = TRUE;
        btsnd_hcic_ble_set_scan_enable (BTM_BLE_SCAN_DISABLE, BTM_BLE_DUPLICATE_ENABLE);
    }

    if ((p_dev_rec = btm_find_dev (bd_addr)) != NULL &&
        p_dev_rec->device_type == BT_DEVICE_TYPE_BLE)
    {
        BTM_TRACE_DEBUG0("btm_update_dev_to_white_list 1");

        if ((to_add && p_cb->num_empty_filter == 0) ||
            (!to_add && p_cb->num_empty_filter == p_cb->max_filter_entries))
        {
            BTM_TRACE_ERROR1("num_entry available in controller: %d", p_cb->num_empty_filter);
            return started;
        }


        if ( p_dev_rec->ble.ble_addr_type == BLE_ADDR_PUBLIC)
        {
            if (to_add)
                started = btsnd_hcic_ble_add_white_list (BLE_ADDR_PUBLIC, bd_addr);
            else
                started = btsnd_hcic_ble_remove_from_white_list (BLE_ADDR_PUBLIC, bd_addr);
        }
        else
        {
            if (BLE_ADDR_IS_STATIC(bd_addr))
            {
                if (to_add)
                    started = btsnd_hcic_ble_add_white_list (BLE_ADDR_RANDOM, bd_addr);
                else
                    started = btsnd_hcic_ble_remove_from_white_list (BLE_ADDR_RANDOM, bd_addr);

            }
            if (memcmp(p_dev_rec->ble.reconn_addr, dummy_bda, BD_ADDR_LEN) != 0)
            {
                if (to_add)
                    started = btsnd_hcic_ble_add_white_list (BLE_ADDR_RANDOM, p_dev_rec->ble.reconn_addr);
                else
                    started = btsnd_hcic_ble_remove_from_white_list (BLE_ADDR_RANDOM, p_dev_rec->ble.reconn_addr);
            }
        }
    }
    /* if not a known device, shall we add it? */
    else
    {
        if (to_add)
            started = btsnd_hcic_ble_add_white_list (addr_type, bd_addr);
        else
            started = btsnd_hcic_ble_remove_from_white_list (addr_type, bd_addr);
    }

    if (suspend)
    {
        btsnd_hcic_ble_set_scan_enable (BTM_BLE_SCAN_ENABLE, BTM_BLE_DUPLICATE_DISABLE);
    }

    return started;
}
/*******************************************************************************
**
** Function         btm_ble_clear_white_list
**
** Description      This function clears the white list.
*******************************************************************************/
void btm_ble_clear_white_list (void)
{
    BTM_TRACE_EVENT0 ("btm_ble_clear_white_list");
    btsnd_hcic_ble_clear_white_list();
}

/*******************************************************************************
**
** Function         btm_ble_clear_white_list_complete
**
** Description      This function clears the white list complete.
*******************************************************************************/
void btm_ble_clear_white_list_complete(UINT8 *p_data, UINT16 evt_len)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    UINT8       status;
    BTM_TRACE_EVENT0 ("btm_ble_clear_white_list_complete");
    STREAM_TO_UINT8  (status, p_data);

    if (status == HCI_SUCCESS)
        p_cb->num_empty_filter = p_cb->max_filter_entries;

}
/*******************************************************************************
**
** Function         btm_ble_add_2_white_list_complete
**
** Description      This function read the current white list size.
*******************************************************************************/
void btm_ble_add_2_white_list_complete(UINT8 *p, UINT16 evt_len)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    BTM_TRACE_EVENT0 ("btm_ble_add_2_white_list_complete");

    if (*p == HCI_SUCCESS)
    {
        p_cb->num_empty_filter --;
    }
}
/*******************************************************************************
**
** Function         btm_ble_add_2_white_list_complete
**
** Description      This function read the current white list size.
*******************************************************************************/
void btm_ble_remove_from_white_list_complete(UINT8 *p, UINT16 evt_len)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    BTM_TRACE_EVENT0 ("btm_ble_remove_from_white_list_complete");
    if (*p == HCI_SUCCESS)
    {
        p_cb->num_empty_filter ++;
    }
}
/*******************************************************************************
**
** Function         btm_ble_find_dev_in_whitelist
**
** Description      This function check if the device is in the white list
*******************************************************************************/
BOOLEAN btm_ble_find_dev_in_whitelist(BD_ADDR bd_addr)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    UINT8 i;

    BTM_TRACE_EVENT0 ("btm_ble_find_dev_in_whitelist");

    /* empty wl */
    if (p_cb->num_empty_filter == p_cb->max_filter_entries)
    {
        BTM_TRACE_DEBUG0("white list empty");
        return FALSE;
    }

    for (i = 0; i < BTM_BLE_MAX_BG_CONN_DEV_NUM && i < p_cb->max_filter_entries; i ++)
    {
        if (memcmp(p_cb->bg_conn_dev_list[i], bd_addr, BD_ADDR_LEN) == 0)
            return TRUE;
    }
    return FALSE;
}
/*******************************************************************************
**
** Function         btm_ble_count_unconn_dev_in_whitelist
**
** Description      This function check the number of unconnected device in white list.
*******************************************************************************/
UINT8 btm_ble_count_unconn_dev_in_whitelist(void)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    UINT8 count = 0, i;
    BD_ADDR dummy_bda ={0};

    BTM_TRACE_EVENT0 ("btm_ble_find_dev_in_whitelist");

    for (i = 0; i < BTM_BLE_MAX_BG_CONN_DEV_NUM && i < p_cb->max_filter_entries; i ++)
    {
        if (memcmp(p_cb->bg_conn_dev_list[i], dummy_bda, BD_ADDR_LEN) != 0 &&
            !BTM_IsAclConnectionUp(p_cb->bg_conn_dev_list[i]))
        {
            count ++;
        }
    }
    return count;
}
/*******************************************************************************
**
** Function         btm_update_bg_conn_list
**
** Description      This function update the local background connection device list.
*******************************************************************************/
BOOLEAN btm_update_bg_conn_list(BOOLEAN to_add, BD_ADDR bd_addr)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    UINT8 i;
    BD_ADDR dummy_bda = {0};
    BTM_TRACE_EVENT0 ("btm_update_bg_conn_list");
    if ((to_add && (p_cb->bg_conn_dev_num == BTM_BLE_MAX_BG_CONN_DEV_NUM || p_cb->num_empty_filter == 0)) ||
        (!to_add && p_cb->num_empty_filter == p_cb->max_filter_entries))
    {
        BTM_TRACE_DEBUG1("num_empty_filter = %d", p_cb->num_empty_filter);
        return FALSE;
    }

    for (i = 0; i < BTM_BLE_MAX_BG_CONN_DEV_NUM && i < p_cb->max_filter_entries; i ++)
    {
        /* to add */
        if (memcmp(p_cb->bg_conn_dev_list[i], dummy_bda, BD_ADDR_LEN) == 0 && to_add)
        {
            memcpy(p_cb->bg_conn_dev_list[i], bd_addr, BD_ADDR_LEN);
            p_cb->bg_conn_dev_num ++;
            return TRUE;
        }
        /* to remove */
        if (!to_add && memcmp(p_cb->bg_conn_dev_list[i], bd_addr, BD_ADDR_LEN) == 0)
        {
            memset(p_cb->bg_conn_dev_list[i], 0, BD_ADDR_LEN);
            p_cb->bg_conn_dev_num --;
            return TRUE;
        }
    }
    return FALSE;
}
/*******************************************************************************
**
** Function         btm_write_bg_conn_wl
**
** Description      This function write background connection device list into
**                  controller.
*******************************************************************************/
void btm_write_bg_conn_wl(void)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    UINT8       i;
    BTM_TRACE_EVENT0 ("btm_write_bg_conn_wl");
    btm_ble_clear_white_list();

    for (i = 0; i < p_cb->bg_conn_dev_num; i ++)
    {
        if (!btm_update_dev_to_white_list(TRUE, p_cb->bg_conn_dev_list[i], BLE_ADDR_PUBLIC))
            break;
    }
    return;
}
/*******************************************************************************
**
** Function         btm_ble_start_auto_conn
**
** Description      This function is to start/stop auto connection procedure.
**
** Parameters       start: TRUE to start; FALSE to stop.
**
** Returns          void
**
*******************************************************************************/
BOOLEAN btm_ble_start_auto_conn(BOOLEAN start)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    BD_ADDR dummy_bda = {0};
    BOOLEAN exec = TRUE;
    UINT16 scan_int, scan_win;

    scan_int = (p_cb->scan_int == BTM_BLE_CONN_PARAM_UNDEF) ? BTM_BLE_CONN_EST_SCAN_INT : p_cb->scan_int;
    scan_win = (p_cb->scan_win == BTM_BLE_CONN_PARAM_UNDEF) ? BTM_BLE_CONN_EST_SCAN_WIND : p_cb->scan_win;

    if (start)
    {
        if (!l2cb.is_ble_connecting &&
            btm_ble_count_unconn_dev_in_whitelist() > 0)
        {
            if (p_cb->bg_conn_state != BLE_BG_CONN_ACTIVE && p_cb->bg_conn_dev_num > 0)
            {
                if (!btsnd_hcic_ble_create_ll_conn (scan_int,  /* UINT16 scan_int      */
                                                    scan_win,    /* UINT16 scan_win      */
                                                    0x01,                   /* UINT8 white_list     */
                                                    BLE_ADDR_PUBLIC,        /* UINT8 addr_type_peer */
                                                    dummy_bda,              /* BD_ADDR bda_peer     */
                                                    BLE_ADDR_PUBLIC,         /* UINT8 addr_type_own  */
                                                    BTM_BLE_CONN_INT_MIN_DEF,   /* UINT16 conn_int_min  */
                                                    BTM_BLE_CONN_INT_MAX_DEF,   /* UINT16 conn_int_max  */
                                                    BTM_BLE_CONN_SLAVE_LATENCY_DEF,  /* UINT16 conn_latency  */
                                                    BTM_BLE_CONN_TIMEOUT_DEF,        /* UINT16 conn_timeout  */
                                                    0,                       /* UINT16 min_len       */
                                                    0))                      /* UINT16 max_len       */
                {
                    /* start auto connection failed */
                    exec =  FALSE;
                }
                else
                {
                    p_cb->bg_conn_state = BLE_BG_CONN_ACTIVE;
                }
            }
        }
        else
            exec = FALSE;
    }
    else
    {
        if (p_cb->bg_conn_state == BLE_BG_CONN_ACTIVE)
        {
            if (!btsnd_hcic_ble_create_conn_cancel())
                exec = FALSE;
            else
                p_cb->bg_conn_state = BLE_BG_CONN_IDLE;
        }
    }
    return exec;
}

/*******************************************************************************
**
** Function         btm_ble_start_select_conn
**
** Description      This function is to start/stop selective connection procedure.
**
** Parameters       start: TRUE to start; FALSE to stop.
**                  p_select_cback: callback function to return application
**                                  selection.
**
** Returns          BOOLEAN: selective connectino procedure is started.
**
*******************************************************************************/
BOOLEAN btm_ble_start_select_conn(BOOLEAN start,tBTM_BLE_SEL_CBACK   *p_select_cback)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    UINT16 scan_int, scan_win;

    BTM_TRACE_EVENT0 ("btm_ble_start_select_conn");

    scan_int = (p_cb->scan_int == BTM_BLE_CONN_PARAM_UNDEF) ? BTM_BLE_CONN_EST_SCAN_INT : p_cb->scan_int;
    scan_win = (p_cb->scan_win == BTM_BLE_CONN_PARAM_UNDEF) ? BTM_BLE_CONN_EST_SCAN_WIND : p_cb->scan_win;

    if (start)
    {
        if (!btm_cb.btm_inq_vars.inq_active)
        {
            btm_cb.ble_ctr_cb.p_select_cback = p_select_cback;

            btm_update_scanner_filter_policy(SP_ADV_WL);

            if (!btsnd_hcic_ble_set_scan_params(BTM_BLE_SCAN_MODE_PASS,  /* use passive scan by default */
                                                scan_int, /* scan interval */
                                                scan_win,    /* scan window */
                                                BLE_ADDR_PUBLIC,         /* own device, DUMO always use public */
                                                SP_ADV_WL)              /* process advertising packets only from devices in the White List */
                )
                return FALSE;

            if (p_cb->inq_var.adv_mode == BTM_BLE_ADV_ENABLE)
            {
                BTM_TRACE_ERROR0("peripheral device cannot initiate a selective connection");
                return FALSE;
            }
            else if (p_cb->bg_conn_dev_num > 0 && btm_ble_count_unconn_dev_in_whitelist() > 0 )
            {

                if (!btsnd_hcic_ble_set_scan_enable(TRUE, TRUE)) /* duplicate filtering enabled */
                    return FALSE;

                /* mark up inquiry status flag */
                btm_cb.btm_inq_vars.inq_active = TRUE;
                btm_cb.ble_ctr_cb.inq_var.proc_mode = BTM_BLE_SELECT_SCAN;

                p_cb->bg_conn_state = BLE_BG_CONN_ACTIVE;

            }
        }
        else
        {
            BTM_TRACE_ERROR0("scan active, can not start selective connection procedure");
            return FALSE;
        }
    }
    else /* disable selective connection mode */
    {
        p_cb->p_select_cback = NULL;
        btm_cb.btm_inq_vars.inq_active = FALSE;
        btm_cb.ble_ctr_cb.inq_var.proc_mode = BTM_BLE_INQUIRY_NONE;

        btm_update_scanner_filter_policy(SP_ADV_ALL);

        /* stop scanning */
        if (p_cb->bg_conn_dev_num > 0)
        {
            if (!btsnd_hcic_ble_set_scan_enable(FALSE, TRUE)) /* duplicate filtering enabled */
                return FALSE;
        }
    }
    return TRUE;
}
/*******************************************************************************
**
** Function         btm_ble_initiate_select_conn
**
** Description      This function is to start/stop selective connection procedure.
**
** Parameters       start: TRUE to start; FALSE to stop.
**                  p_select_cback: callback function to return application
**                                  selection.
**
** Returns          BOOLEAN: selective connectino procedure is started.
**
*******************************************************************************/
void btm_ble_initiate_select_conn(BD_ADDR bda)
{
    UINT8   addr_type;
    BTM_TRACE_EVENT0 ("btm_ble_initiate_select_conn");
    addr_type = btm_ble_map_bda_to_conn_bda(bda);

    /* use direct connection procedure to initiate connection */
    if (!L2CA_ConnectFixedChnl(L2CAP_ATT_CID, bda))
    {
        BTM_TRACE_ERROR0("btm_ble_initiate_select_conn failed");
    }
}
/*******************************************************************************
**
** Function         btm_ble_suspend_bg_sele_conn
**
** Description      This function is to suspend an active background connection
**                  procedure.
**
** Parameters       none.
**
** Returns          none.
**
*******************************************************************************/
void btm_ble_suspend_bg_sele_conn(void)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    BTM_TRACE_EVENT0 ("btm_ble_suspend_bg_sele_conn");

    if (p_cb->bg_conn_type == BTM_BLE_CONN_SELECTIVE)
    {
        p_cb->bg_conn_state = BLE_BG_CONN_SUSPEND;
        btm_ble_start_select_conn(FALSE, NULL);
    }
}
/*******************************************************************************
**
** Function         btm_ble_suspend_bg_conn
**
** Description      This function is to suspend an active background connection
**                  procedure.
**
** Parameters       none.
**
** Returns          none.
**
*******************************************************************************/
void btm_ble_suspend_bg_conn(void)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    BTM_TRACE_EVENT0 ("btm_ble_suspend_bg_conn");

    if (p_cb->bg_conn_type == BTM_BLE_CONN_AUTO)
    {
        if (btm_ble_start_auto_conn(FALSE))
            p_cb->bg_conn_state = BLE_BG_CONN_SUSPEND;
    }
}
/*******************************************************************************
**
** Function         btm_ble_scan_param_idle
**
** Description      This function is to process the scan parameter idle timeout
**                  timeout.
********************************************************************************/
void btm_ble_scan_param_idle(void)
{
    BTM_BleSetConnScanParams(BTM_BLE_CONN_EST_SCAN_INT_LO, BTM_BLE_CONN_EST_SCAN_WIND_LO);
}
/*******************************************************************************
**
** Function         btm_ble_resume_bg_conn
**
** Description      This function is to resume a background auto connection
**                  procedure.
**
** Parameters       none.
**
** Returns          none.
**
*******************************************************************************/
BOOLEAN btm_ble_resume_bg_conn(tBTM_BLE_SEL_CBACK *p_sele_callback, BOOLEAN def_param)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    BOOLEAN ret = FALSE;

    if (p_cb->bg_conn_state != BLE_BG_CONN_ACTIVE )
    {
        if (def_param)
        {
            p_cb->scan_int = BTM_BLE_CONN_PARAM_UNDEF;
            p_cb->scan_win = BTM_BLE_CONN_PARAM_UNDEF;

            /* start scan param idle timer */
            btu_start_timer(&p_cb->scan_param_idle_timer,
                            BTU_TTYPE_BLE_SCAN_PARAM_IDLE,
                            BTM_BLE_SCAN_PARAM_TOUT);
        }

        if (p_cb->bg_conn_type == BTM_BLE_CONN_AUTO)
            ret = btm_ble_start_auto_conn(TRUE);

        if (p_cb->bg_conn_type == BTM_BLE_CONN_SELECTIVE)
        {
            /* terminate selective connection mode if all devices are connected */
            if (btm_ble_count_unconn_dev_in_whitelist() == 0)
            {
                btsnd_hcic_ble_set_scan_enable (BTM_BLE_SCAN_DISABLE, BTM_BLE_DUPLICATE_DISABLE);
                btm_cb.ble_ctr_cb.inq_var.proc_mode = BTM_BLE_INQUIRY_NONE;
                btm_cb.btm_inq_vars.inq_active = FALSE;
            }
            else if (!btm_cb.btm_inq_vars.inq_active)
                btm_ble_start_select_conn(TRUE, btm_cb.ble_ctr_cb.p_select_cback);
        }

        if (ret)
            p_cb->bg_conn_state = BLE_BG_CONN_ACTIVE;

    }

    return ret;
}
/*******************************************************************************
**
** Function         btm_ble_update_bg_state
**
** Description      This function is to update the bg connection status.
**
** Parameters       none.
**
** Returns          none.
**
*******************************************************************************/
void btm_ble_update_bg_state(void)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;

    if (!l2cb.is_ble_connecting && (p_cb->bg_conn_state != BLE_BG_CONN_SUSPEND))
        p_cb->bg_conn_state = BLE_BG_CONN_IDLE;

}

#endif

