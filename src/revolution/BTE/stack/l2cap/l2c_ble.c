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
 *  this file contains functions relating to BLE management.
 *
 ******************************************************************************/

#include <string.h>
#include "bt_target.h"
#include "l2cdefs.h"
#include "l2c_int.h"
#include "btu.h"
#include "btm_int.h"
#include "hcimsgs.h"

#if (BLE_INCLUDED == TRUE)

/*******************************************************************************
**
**  Function        L2CA_CancelBleConnectReq
**
**  Description     Cancel a pending connection attempt to a BLE device.
**
**  Parameters:     BD Address of remote
**
**  Return value:   TRUE if connection was cancelled
**
*******************************************************************************/
BOOLEAN L2CA_CancelBleConnectReq (BD_ADDR rem_bda)
{
    tL2C_LCB *p_lcb;

    /* There can be only one BLE connection request outstanding at a time */
    if (!l2cb.is_ble_connecting)
    {
        L2CAP_TRACE_WARNING0 ("L2CA_CancelBleConnectReq - no connection pending");
        return(FALSE);
    }

    if (memcmp (rem_bda, l2cb.ble_connecting_bda, BD_ADDR_LEN))
    {
        L2CAP_TRACE_WARNING4 ("L2CA_CancelBleConnectReq - different  BDA Connecting: %08x%04x  Cancel: %08x%04x",
                              (l2cb.ble_connecting_bda[0]<<24)+(l2cb.ble_connecting_bda[1]<<16)+(l2cb.ble_connecting_bda[2]<<8)+l2cb.ble_connecting_bda[3],
                              (l2cb.ble_connecting_bda[4]<<8)+l2cb.ble_connecting_bda[5],
                              (rem_bda[0]<<24)+(rem_bda[1]<<16)+(rem_bda[2]<<8)+rem_bda[3], (rem_bda[4]<<8)+rem_bda[5]);

        return(FALSE);
    }

    if (btsnd_hcic_ble_create_conn_cancel())
    {

        if ((p_lcb = l2cu_find_lcb_by_bd_addr (rem_bda)) != NULL)
        {
            p_lcb->disc_reason = L2CAP_CONN_CANCEL;
            l2cu_release_lcb (p_lcb);
        }

        l2cb.is_ble_connecting = FALSE;
        btm_ble_update_bg_state();
        btm_ble_resume_bg_conn(NULL, TRUE);

        return(TRUE);
    }
    else
        return(FALSE);
}


/*******************************************************************************
**
**  Function        L2CA_UpdateBleConnParams
**
**  Description     Update BLE connection parameters.
**
**  Parameters:     BD Address of remote
**
**  Return value:   TRUE if update started
**
*******************************************************************************/
BOOLEAN L2CA_UpdateBleConnParams (BD_ADDR rem_bda, UINT16 min_int, UINT16 max_int, UINT16 latency, UINT16 timeout)
{
    tL2C_LCB            *p_lcb;

    /* See if we have a link control block for the remote device */
    p_lcb = l2cu_find_lcb_by_bd_addr (rem_bda);

    /* If we don't have one, create one and accept the connection. */
    if (!p_lcb)
    {
        L2CAP_TRACE_WARNING2 ("L2CA_UpdateBleConnParams - unknown BD_ADDR %08x%04x",
                              (rem_bda[0]<<24)+(rem_bda[1]<<16)+(rem_bda[2]<<8)+rem_bda[3], (rem_bda[4]<<8)+rem_bda[5]);
        return(FALSE);
    }

    if (!p_lcb->is_ble_link)
    {
        L2CAP_TRACE_WARNING2 ("L2CA_UpdateBleConnParams - BD_ADDR %08x%04x not LE",
                              (rem_bda[0]<<24)+(rem_bda[1]<<16)+(rem_bda[2]<<8)+rem_bda[3], (rem_bda[4]<<8)+rem_bda[5]);
        return(FALSE);
    }

    if (p_lcb->link_role == HCI_ROLE_MASTER)
        btsnd_hcic_ble_upd_ll_conn_params (p_lcb->handle, min_int, max_int, latency, timeout, 0, 0);
    else
        l2cu_send_peer_ble_par_req (p_lcb, min_int, max_int, latency, timeout);

    return(TRUE);
}


/*******************************************************************************
**
**  Function        L2CA_EnableUpdateBleConnParams
**
**  Description     Enable or disable update based on the request from the peer
**
**  Parameters:     BD Address of remote
**
**  Return value:   TRUE if update started
**
*******************************************************************************/
BOOLEAN L2CA_EnableUpdateBleConnParams (BD_ADDR rem_bda, BOOLEAN enable)
{
    tL2C_LCB            *p_lcb;

    /* See if we have a link control block for the remote device */
    p_lcb = l2cu_find_lcb_by_bd_addr (rem_bda);

    /* If we don't have one, create one and accept the connection. */
    if (!p_lcb)
    {
        L2CAP_TRACE_WARNING2 ("L2CA_EnableUpdateBleConnParams - unknown BD_ADDR %08x%04x",
            (rem_bda[0]<<24)+(rem_bda[1]<<16)+(rem_bda[2]<<8)+rem_bda[3], (rem_bda[4]<<8)+rem_bda[5]);
        return (FALSE);
    }

    L2CAP_TRACE_API4 ("L2CA_EnableUpdateBleConnParams - BD_ADDR %08x%04x enable %d current upd state %d",
        (rem_bda[0]<<24)+(rem_bda[1]<<16)+(rem_bda[2]<<8)+rem_bda[3], (rem_bda[4]<<8)+rem_bda[5], enable, p_lcb->upd_disabled);

    if (!p_lcb->is_ble_link || (p_lcb->link_role != HCI_ROLE_MASTER))
    {
        L2CAP_TRACE_WARNING3 ("L2CA_EnableUpdateBleConnParams - BD_ADDR %08x%04x not LE or not master %d",
                              (rem_bda[0]<<24)+(rem_bda[1]<<16)+(rem_bda[2]<<8)+rem_bda[3], (rem_bda[4]<<8)+rem_bda[5], p_lcb->link_role);
        return (FALSE);
    }

    if (enable)
    {
        /* application allows to do update, if we were delaying one do it now, otherwise
        just mark lcb that updates are enabled */
        if (p_lcb->upd_disabled == UPD_PENDING)
        {
            btsnd_hcic_ble_upd_ll_conn_params (p_lcb->handle, p_lcb->min_interval, p_lcb->max_interval,
                                               p_lcb->latency, p_lcb->timeout, 0, 0);
            p_lcb->upd_disabled = UPD_UPDATED;
        }
        else
        {
            p_lcb->upd_disabled = UPD_ENABLED;
        }
    }
    else
    {
        /* application requests to disable parameters update.  If parameters are already updated, lets set them
        up to what has been requested during connection establishement */
        if (p_lcb->upd_disabled == UPD_UPDATED)
        {
            tBTM_SEC_DEV_REC    *p_dev_rec = btm_find_or_alloc_dev (rem_bda);

            btsnd_hcic_ble_upd_ll_conn_params (p_lcb->handle,
                (UINT16)((p_dev_rec->conn_params.min_conn_int != BTM_BLE_CONN_PARAM_UNDEF) ? p_dev_rec->conn_params.min_conn_int : L2CAP_LE_INT_MIN),
                (UINT16)((p_dev_rec->conn_params.max_conn_int != BTM_BLE_CONN_PARAM_UNDEF) ? p_dev_rec->conn_params.max_conn_int : L2CAP_LE_INT_MAX),
                (UINT16)((p_dev_rec->conn_params.slave_latency != BTM_BLE_CONN_PARAM_UNDEF) ? p_dev_rec->conn_params.slave_latency : 0),
                (UINT16) ((p_dev_rec->conn_params.supervision_tout != BTM_BLE_CONN_PARAM_UNDEF) ? p_dev_rec->conn_params.supervision_tout : L2CAP_LE_TIMEOUT_MAX),
                0, 0);
        }
        p_lcb->upd_disabled = UPD_DISABLED;
    }

    return (TRUE);
}

/*******************************************************************************
**
** Function         L2CA_GetBleConnRole
**
** Description      This function returns the connection role.
**
** Returns          link role.
**
*******************************************************************************/
UINT8 L2CA_GetBleConnRole (BD_ADDR bd_addr)
{
    UINT8       role = HCI_ROLE_UNKNOWN;

    tL2C_LCB *p_lcb;

    if ((p_lcb = l2cu_find_lcb_by_bd_addr (bd_addr)) != NULL)
        role = p_lcb->link_role;

    return role;
}
/*******************************************************************************
**
** Function         L2CA_GetDisconnectReason
**
** Description      This function returns the disconnect reason code.
**
** Returns          disconnect reason
**
*******************************************************************************/
UINT16 L2CA_GetDisconnectReason (BD_ADDR remote_bda)
{
    tL2C_LCB            *p_lcb;
    UINT16              reason = 0;

    if ((p_lcb = l2cu_find_lcb_by_bd_addr (remote_bda)) != NULL)
        reason = p_lcb->disc_reason;

    L2CAP_TRACE_DEBUG1 ("L2CA_GetDisconnectReason=%d ",reason);

    return reason;
}

/*******************************************************************************
**
** Function         l2cble_scanner_conn_comp
**
** Description      This function is called when an HCI Connection Complete
**                  event is received while we are a scanner (so we are master).
**
** Returns          void
**
*******************************************************************************/
void l2cble_scanner_conn_comp (UINT16 handle, BD_ADDR bda, tBLE_ADDR_TYPE type, UINT16 conn_interval, UINT16 conn_latency, UINT16 conn_timeout)
{
    tL2C_LCB            *p_lcb;
    tBTM_SEC_DEV_REC    *p_dev_rec = btm_find_or_alloc_dev (bda);

    L2CAP_TRACE_DEBUG5 ("l2cble_scanner_conn_comp: HANDLE=%d addr_type=%d conn_interval=%d slave_latency=%d supervision_tout=%d",
                        handle,  type, conn_interval, conn_latency, conn_timeout);

    l2cb.is_ble_connecting = FALSE;

    p_dev_rec->device_type   = BT_DEVICE_TYPE_BLE;
    p_dev_rec->ble.ble_addr_type = type;

    /* See if we have a link control block for the remote device */
    p_lcb = l2cu_find_lcb_by_bd_addr (bda);

    /* If we don't have one, create one. this is auto connection complete. */
    if (!p_lcb)
    {
        p_lcb = l2cu_allocate_lcb (bda, FALSE);
        if (!p_lcb)
        {
            btm_sec_disconnect (handle, HCI_ERR_NO_CONNECTION);
            L2CAP_TRACE_ERROR0 ("l2cble_scanner_conn_comp - failed to allocate LCB");
            return;
        }
        else
        {
            if (!l2cu_initialize_fixed_ccb (p_lcb, L2CAP_ATT_CID, &l2cb.fixed_reg[L2CAP_ATT_CID - L2CAP_FIRST_FIXED_CHNL].fixed_chnl_opts))
            {
                btm_sec_disconnect (handle, HCI_ERR_NO_CONNECTION);
                L2CAP_TRACE_WARNING0 ("l2cble_scanner_conn_comp - LCB but no CCB");
                return ;
            }
        }
    }
    else if (p_lcb->link_state != LST_CONNECTING)
    {
        L2CAP_TRACE_ERROR1 ("L2CAP got BLE scanner conn_comp in bad state: %d", p_lcb->link_state);
        return;
    }
    btu_stop_timer(&p_lcb->timer_entry);

    /* Save the handle */
    p_lcb->handle = handle;

    /* Connected OK. Change state to connected, we were scanning so we are master */
    p_lcb->link_state = LST_CONNECTED;
    p_lcb->link_role  = HCI_ROLE_MASTER;
    p_lcb->is_ble_link = TRUE;

    /* If there are any preferred connection parameters, set them now */
    if ( (p_dev_rec->conn_params.min_conn_int     >= L2CAP_LE_INT_MIN ) &&
         (p_dev_rec->conn_params.min_conn_int     <= L2CAP_LE_INT_MAX ) &&
         (p_dev_rec->conn_params.max_conn_int     >= L2CAP_LE_INT_MIN ) &&
         (p_dev_rec->conn_params.max_conn_int     <= L2CAP_LE_INT_MAX ) &&
         (p_dev_rec->conn_params.slave_latency    <= L2CAP_LE_LATENCY_MAX ) &&
         (p_dev_rec->conn_params.supervision_tout >= L2CAP_LE_TIMEOUT_MIN) &&
         (p_dev_rec->conn_params.supervision_tout <= L2CAP_LE_TIMEOUT_MAX) &&
         ((conn_interval < p_dev_rec->conn_params.min_conn_int &&
          p_dev_rec->conn_params.min_conn_int != BTM_BLE_CONN_PARAM_UNDEF) ||
          (conn_interval > p_dev_rec->conn_params.max_conn_int) ||
          (conn_latency > p_dev_rec->conn_params.slave_latency) ||
          (conn_timeout > p_dev_rec->conn_params.supervision_tout)))
    {
        L2CAP_TRACE_ERROR5 ("upd_ll_conn_params: HANDLE=%d min_conn_int=%d max_conn_int=%d slave_latency=%d supervision_tout=%d",
                            handle, p_dev_rec->conn_params.min_conn_int, p_dev_rec->conn_params.max_conn_int,
                            p_dev_rec->conn_params.slave_latency, p_dev_rec->conn_params.supervision_tout);

        btsnd_hcic_ble_upd_ll_conn_params (handle,
                                           p_dev_rec->conn_params.min_conn_int,
                                           p_dev_rec->conn_params.max_conn_int,
                                           p_dev_rec->conn_params.slave_latency,
                                           p_dev_rec->conn_params.supervision_tout,
                                           0, 0);
    }

    /* Tell BTM Acl management about the link */
    btm_acl_created (bda, NULL, p_dev_rec->sec_bd_name, handle, p_lcb->link_role, TRUE);

    if (p_lcb->p_echo_rsp_cb)
    {
        L2CAP_TRACE_ERROR0 ("l2cu_send_peer_echo_req");
        l2cu_send_peer_echo_req (p_lcb, NULL, 0);
    }

    p_lcb->peer_chnl_mask[0] = L2CAP_FIXED_CHNL_ATT_BIT | L2CAP_FIXED_CHNL_BLE_SIG_BIT | L2CAP_FIXED_CHNL_SMP_BIT;

    l2cu_process_fixed_chnl_resp (p_lcb);
}


/*******************************************************************************
**
** Function         l2cble_advertiser_conn_comp
**
** Description      This function is called when an HCI Connection Complete
**                  event is received while we are an advertiser (so we are slave).
**
** Returns          void
**
*******************************************************************************/
void l2cble_advertiser_conn_comp (UINT16 handle, BD_ADDR bda, tBLE_ADDR_TYPE type,
                                  UINT16 conn_interval, UINT16 conn_latency, UINT16 conn_timeout)
{
    tL2C_LCB            *p_lcb;
    tBTM_SEC_DEV_REC    *p_dev_rec;

    /* See if we have a link control block for the remote device */
    p_lcb = l2cu_find_lcb_by_bd_addr (bda);

    /* If we don't have one, create one and accept the connection. */
    if (!p_lcb)
    {
        p_lcb = l2cu_allocate_lcb (bda, FALSE);
        if (!p_lcb)
        {
            btm_sec_disconnect (handle, HCI_ERR_NO_CONNECTION);
            L2CAP_TRACE_ERROR0 ("l2cble_advertiser_conn_comp - failed to allocate LCB");
            return;
        }
        else
        {
            if (!l2cu_initialize_fixed_ccb (p_lcb, L2CAP_ATT_CID, &l2cb.fixed_reg[L2CAP_ATT_CID - L2CAP_FIRST_FIXED_CHNL].fixed_chnl_opts))
            {
                btm_sec_disconnect (handle, HCI_ERR_NO_CONNECTION);
                L2CAP_TRACE_WARNING0 ("l2cble_scanner_conn_comp - LCB but no CCB");
                return ;
            }
        }
    }

    /* Save the handle */
    p_lcb->handle = handle;

    /* Connected OK. Change state to connected, we were advertising, so we are slave */
    p_lcb->link_state = LST_CONNECTED;
    p_lcb->link_role  = HCI_ROLE_SLAVE;
    p_lcb->is_ble_link = TRUE;

    /* Tell BTM Acl management about the link */
    p_dev_rec = btm_find_or_alloc_dev (bda);

    p_dev_rec->device_type   = BT_DEVICE_TYPE_BLE;
    p_dev_rec->ble.ble_addr_type = type;

    btm_acl_created (bda, NULL, p_dev_rec->sec_bd_name, handle, p_lcb->link_role, TRUE);

    p_lcb->peer_chnl_mask[0] = L2CAP_FIXED_CHNL_ATT_BIT | L2CAP_FIXED_CHNL_BLE_SIG_BIT | L2CAP_FIXED_CHNL_SMP_BIT;

    l2cu_process_fixed_chnl_resp (p_lcb);
}

/*******************************************************************************
**
** Function         l2cble_conn_comp
**
** Description      This function is called when an HCI Connection Complete
**                  event is received.
**
** Returns          void
**
*******************************************************************************/
void l2cble_conn_comp(UINT16 handle, UINT8 role, BD_ADDR bda, tBLE_ADDR_TYPE type,
                      UINT16 conn_interval, UINT16 conn_latency, UINT16 conn_timeout)
{
    if (role == HCI_ROLE_MASTER)
    {
        l2cble_scanner_conn_comp(handle, bda, type, conn_interval, conn_latency, conn_timeout);
    }
    else
    {
        l2cble_advertiser_conn_comp(handle, bda, type, conn_interval, conn_latency, conn_timeout);
    }
}
/*******************************************************************************
**
** Function         l2cble_process_sig_cmd
**
** Description      This function is called when a signalling packet is received
**                  on the BLE signalling CID
**
** Returns          void
**
*******************************************************************************/
void l2cble_process_sig_cmd (tL2C_LCB *p_lcb, UINT8 *p, UINT16 pkt_len)
{
    UINT8           *p_pkt_end;
    UINT8           cmd_code, id;
    UINT16          cmd_len, rej_reason;
    UINT16          result;
    UINT16          min_interval, max_interval, latency, timeout;

    p_pkt_end = p + pkt_len;

    STREAM_TO_UINT8  (cmd_code, p);
    STREAM_TO_UINT8  (id, p);
    STREAM_TO_UINT16 (cmd_len, p);

    /* Check command length does not exceed packet length */
    if ((p + cmd_len) > p_pkt_end)
    {
        L2CAP_TRACE_WARNING3 ("L2CAP - LE - format error, pkt_len: %d  cmd_len: %d  code: %d", pkt_len, cmd_len, cmd_code);
        return;
    }

    switch (cmd_code)
    {
        case L2CAP_CMD_REJECT:
        case L2CAP_CMD_ECHO_RSP:
        case L2CAP_CMD_INFO_RSP:
            STREAM_TO_UINT16 (rej_reason, p);
            break;
        case L2CAP_CMD_ECHO_REQ:
        case L2CAP_CMD_INFO_REQ:
            l2cu_send_peer_cmd_reject (p_lcb, L2CAP_CMD_REJ_NOT_UNDERSTOOD, id, 0, 0);
            break;

        case L2CAP_CMD_BLE_UPDATE_REQ:
            STREAM_TO_UINT16 (min_interval, p); /* 0x0006 - 0x0C80 */
            STREAM_TO_UINT16 (max_interval, p); /* 0x0006 - 0x0C80 */
            STREAM_TO_UINT16 (latency, p);  /* 0x0000 - 0x03E8 */
            STREAM_TO_UINT16 (timeout, p);  /* 0x000A - 0x0C80 */
            /* If we are a master, the slave wants to update the parameters */
            if (p_lcb->link_role == HCI_ROLE_MASTER)
            {
                if (min_interval < L2CAP_LE_INT_MIN || min_interval > L2CAP_LE_INT_MAX ||
                    max_interval < L2CAP_LE_INT_MIN || max_interval > L2CAP_LE_INT_MAX ||
                    latency  > L2CAP_LE_LATENCY_MAX ||
                    /*(timeout >= max_interval && latency > (timeout * 10/(max_interval * 1.25) - 1)) ||*/
                    timeout < L2CAP_LE_TIMEOUT_MIN || timeout > L2CAP_LE_TIMEOUT_MAX ||
                    max_interval < min_interval)
                {
                    result = L2CAP_CFG_UNACCEPTABLE_PARAMS;
                }
                else
                {

                    l2cu_send_peer_ble_par_rsp (p_lcb, L2CAP_CFG_OK, id);

                    p_lcb->min_interval = min_interval;
                    p_lcb->max_interval = max_interval;
                    p_lcb->latency = latency;
                    p_lcb->timeout = timeout;

                    if (p_lcb->upd_disabled == UPD_ENABLED)
                    {
                        btsnd_hcic_ble_upd_ll_conn_params (p_lcb->handle, min_interval, max_interval,
                                                            latency, timeout, 0, 0);
                        p_lcb->upd_disabled = UPD_UPDATED;
                    }
                    else
                    {
                        L2CAP_TRACE_EVENT0 ("L2CAP - LE - update currently disabled");
                        p_lcb->upd_disabled = UPD_PENDING;
                    }
                }
            }
            else
                l2cu_send_peer_cmd_reject (p_lcb, L2CAP_CMD_REJ_NOT_UNDERSTOOD, id, 0, 0);
            break;

        case L2CAP_CMD_BLE_UPDATE_RSP:
            STREAM_TO_UINT16 (result, p);
            break;

        default:
            L2CAP_TRACE_WARNING1 ("L2CAP - LE - unknown cmd code: %d", cmd_code);
            l2cu_send_peer_cmd_reject (p_lcb, L2CAP_CMD_REJ_NOT_UNDERSTOOD, id, 0, 0);
            return;
    }
}


/*******************************************************************************
**
** Function         l2cble_create_conn
**
** Description      This function initiates an acl connection via HCI
**
** Returns          TRUE if successful, FALSE if connection not started.
**
*******************************************************************************/
BOOLEAN l2cble_create_conn (tL2C_LCB *p_lcb)
{
    tBTM_SEC_DEV_REC    *p_dev_rec = btm_find_or_alloc_dev (p_lcb->remote_bd_addr);
    tBTM_BLE_CB     *p_cb = &btm_cb.ble_ctr_cb;
    UINT16          scan_int, scan_win;

    /* There can be only one BLE connection request outstanding at a time */
    if (l2cb.is_ble_connecting)
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - LE - cannot start new connection, already connecting");
        return(FALSE);
    }

    p_lcb->link_state      = LST_CONNECTING;
    l2cb.is_ble_connecting = TRUE;

    memcpy (l2cb.ble_connecting_bda, p_lcb->remote_bd_addr, BD_ADDR_LEN);
    btm_ble_suspend_bg_conn();

    scan_int = (p_cb->scan_int == BTM_BLE_CONN_PARAM_UNDEF) ? L2CAP_LE_INT_MIN : p_cb->scan_int;
    scan_win = (p_cb->scan_win == BTM_BLE_CONN_PARAM_UNDEF) ? L2CAP_LE_INT_MIN : p_cb->scan_win;

    if (!btsnd_hcic_ble_create_ll_conn (scan_int,/* UINT16 scan_int      */
                                        scan_win, /* UINT16 scan_win      */
                                        FALSE,                   /* UINT8 white_list     */
                                        p_lcb->ble_addr_type,    /* UINT8 addr_type_peer */
                                        p_lcb->remote_bd_addr,   /* BD_ADDR bda_peer     */
                                        BLE_ADDR_PUBLIC,         /* UINT8 addr_type_own  */
                                        (UINT16) ((p_dev_rec->conn_params.min_conn_int != BTM_BLE_CONN_PARAM_UNDEF) ? p_dev_rec->conn_params.min_conn_int : L2CAP_LE_INT_MIN),  /* UINT16 conn_int_min  */
                                        (UINT16) ((p_dev_rec->conn_params.max_conn_int != BTM_BLE_CONN_PARAM_UNDEF) ? p_dev_rec->conn_params.max_conn_int : L2CAP_LE_INT_MIN),  /* UINT16 conn_int_max  */
                                        (UINT16) ((p_dev_rec->conn_params.slave_latency != BTM_BLE_CONN_PARAM_UNDEF) ? p_dev_rec->conn_params.slave_latency : 0), /* UINT16 conn_latency  */
                                        (UINT16) ((p_dev_rec->conn_params.supervision_tout != BTM_BLE_CONN_PARAM_UNDEF) ? p_dev_rec->conn_params.supervision_tout : L2CAP_LE_TIMEOUT_MAX), /* UINT16 conn_timeout  */
                                        0,                       /* UINT16 min_len       */
                                        0))                      /* UINT16 max_len       */
    {
        /* No buffer for connection request ? */
        l2cb.is_ble_connecting = FALSE;
        p_lcb->disc_reason = L2CAP_CONN_NO_RESOURCES;
        l2cu_release_lcb (p_lcb);
        return(FALSE);
    }
    else
        btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, L2CAP_BLE_LINK_CONNECT_TOUT);

    return(TRUE);
}

/*******************************************************************************
**
** Function         l2c_link_processs_ble_num_bufs
**
** Description      This function is called when a "controller buffer size"
**                  event is first received from the controller. It updates
**                  the L2CAP values.
**
** Returns          void
**
*******************************************************************************/
void l2c_link_processs_ble_num_bufs (UINT16 num_lm_ble_bufs)
{
    l2cb.num_lm_ble_bufs = l2cb.controller_le_xmit_window = num_lm_ble_bufs;
}

#endif /* (BLE_INCLUDED == TRUE) */
