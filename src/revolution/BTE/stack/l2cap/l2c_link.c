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
 *  this file contains the functions relating to link management. A "link"
 *  is a connection between this device and another device. Only ACL links
 *  are managed.
 *
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "gki.h"
#include "bt_types.h"
#include "hcimsgs.h"
#include "l2cdefs.h"
#include "l2c_int.h"
#include "l2c_api.h"
#include "btu.h"
#include "btm_api.h"
#include "btm_int.h"

static BOOLEAN l2c_link_send_to_lower (tL2C_LCB *p_lcb, BT_HDR *p_buf);

#define L2C_LINK_SEND_ACL_DATA(x)  HCI_ACL_DATA_TO_LOWER((x))

#if (BLE_INCLUDED == TRUE)
#define L2C_LINK_SEND_BLE_ACL_DATA(x)  HCI_BLE_ACL_DATA_TO_LOWER((x))
#endif

/*******************************************************************************
**
** Function         l2c_link_hci_conn_req
**
** Description      This function is called when an HCI Connection Request
**                  event is received.
**
** Returns          TRUE, if accept conn
**
*******************************************************************************/
BOOLEAN l2c_link_hci_conn_req (BD_ADDR bd_addr)
{
    tL2C_LCB        *p_lcb;
    tL2C_LCB        *p_lcb_cur;
    int             xx;
    BOOLEAN         no_links;

    /* See if we have a link control block for the remote device */
    p_lcb = l2cu_find_lcb_by_bd_addr (bd_addr);

    /* If we don't have one, create one and accept the connection. */
    if (!p_lcb)
    {
        p_lcb = l2cu_allocate_lcb (bd_addr, FALSE);
        if (!p_lcb)
        {
            btsnd_hcic_reject_conn (bd_addr, HCI_ERR_HOST_REJECT_RESOURCES);
            L2CAP_TRACE_ERROR0 ("L2CAP failed to allocate LCB");
            return FALSE;
        }

        no_links = TRUE;

        /* If we already have connection, accept as a master */
        for (xx = 0, p_lcb_cur = &l2cb.lcb_pool[0]; xx < MAX_L2CAP_LINKS; xx++, p_lcb_cur++)
        {
            if (p_lcb_cur == p_lcb)
                continue;

            if (p_lcb_cur->in_use)
            {
                no_links = FALSE;
                p_lcb->link_role = HCI_ROLE_MASTER;
                break;
            }
        }

        if (no_links)
        {
            if (!btm_dev_support_switch (bd_addr))
                p_lcb->link_role = HCI_ROLE_SLAVE;
            else
                p_lcb->link_role = l2cu_get_conn_role(p_lcb);
        }

        /* Tell the other side we accept the connection */
        btsnd_hcic_accept_conn (bd_addr, p_lcb->link_role);

        p_lcb->link_state = LST_CONNECTING;

        /* Start a timer waiting for connect complete */
        btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, L2CAP_LINK_CONNECT_TOUT);
        return (TRUE);
    }

    /* We already had a link control block to the guy. Check what state it is in */
    if ((p_lcb->link_state == LST_CONNECTING) || (p_lcb->link_state == LST_CONNECT_HOLDING))
    {
        /* Connection collision. Accept the connection anyways. */

        if (!btm_dev_support_switch (bd_addr))
            p_lcb->link_role = HCI_ROLE_SLAVE;
        else
            p_lcb->link_role = l2cu_get_conn_role(p_lcb);

        btsnd_hcic_accept_conn (bd_addr, p_lcb->link_role);

        p_lcb->link_state = LST_CONNECTING;
        return (TRUE);
    }
    else if (p_lcb->link_state == LST_DISCONNECTING)
    {
        /* In disconnecting state, reject the connection. */
        btsnd_hcic_reject_conn (bd_addr, HCI_ERR_HOST_REJECT_DEVICE);
    }
    else
    {
        L2CAP_TRACE_ERROR0 ("L2CAP got conn_req while connected");
    }
    return (FALSE);
}

/*******************************************************************************
**
** Function         l2c_link_hci_conn_comp
**
** Description      This function is called when an HCI Connection Complete
**                  event is received.
**
** Returns          void
**
*******************************************************************************/
BOOLEAN l2c_link_hci_conn_comp (UINT8 status, UINT16 handle, BD_ADDR p_bda)
{
    tL2C_CONN_INFO       ci;
    tL2C_LCB            *p_lcb;
    tL2C_CCB            *p_ccb;
    tBTM_SEC_DEV_REC    *p_dev_info = NULL;

#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
    btm_acl_update_busy_level (BTM_BLI_PAGE_DONE_EVT);
#endif

    /* Save the parameters */
    ci.status       = status;
    memcpy (ci.bd_addr, p_bda, BD_ADDR_LEN);

    /* See if we have a link control block for the remote device */
    p_lcb = l2cu_find_lcb_by_bd_addr (ci.bd_addr);

    /* If we don't have one, this is an error */
    if (!p_lcb)
    {
        L2CAP_TRACE_WARNING0 ("L2CAP got conn_comp for unknown BD_ADDR");
        return (FALSE);
    }

    if (p_lcb->link_state != LST_CONNECTING)
    {
        L2CAP_TRACE_ERROR2 ("L2CAP got conn_comp in bad state: %d  status: 0x%d", p_lcb->link_state, status);

        if (status != HCI_SUCCESS)
            l2c_link_hci_disc_comp (p_lcb->handle, status);

        return (FALSE);
    }

    /* Save the handle */
    p_lcb->handle = handle;

    if (ci.status == HCI_SUCCESS)
    {
        /* Connected OK. Change state to connected */
        p_lcb->link_state = LST_CONNECTED;

        /* Get the peer information if the l2cap flow-control/rtrans is supported */
        l2cu_send_peer_info_req (p_lcb, L2CAP_EXTENDED_FEATURES_INFO_TYPE);

        /* Tell BTM Acl management about the link */
        if ((p_dev_info = btm_find_dev (p_bda)) != NULL)
            btm_acl_created (ci.bd_addr, p_dev_info->dev_class,
                             p_dev_info->sec_bd_name, handle,
                             p_lcb->link_role, FALSE);
        else
            btm_acl_created (ci.bd_addr, NULL, NULL, handle, p_lcb->link_role, FALSE);

        /* If dedicated bonding do not process any further */
        if (p_lcb->is_bonding)
        {
            if (l2cu_start_post_bond_timer(handle))
                return (TRUE);
        }

        /* Update the timeouts in the hold queue */
        l2c_process_held_packets(FALSE);

        btu_stop_timer (&p_lcb->timer_entry);

        /* For all channels, send the event through their FSMs */
        for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_ccb->p_next_ccb)
        {
            l2c_csm_execute (p_ccb, L2CEVT_LP_CONNECT_CFM, &ci);
        }

        if (p_lcb->p_echo_rsp_cb)
        {
            l2cu_send_peer_echo_req (p_lcb, NULL, 0);
            btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, L2CAP_ECHO_RSP_TOUT);
        }
        else if (!p_lcb->ccb_queue.p_first_ccb)
        {
            btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, L2CAP_LINK_STARTUP_TOUT);
        }
    }
    /* Max number of acl connections.                          */
    /* If there's an lcb disconnecting set this one to holding */
    else if ((ci.status == HCI_ERR_MAX_NUM_OF_CONNECTIONS) && l2cu_lcb_disconnecting())
    {
        p_lcb->link_state = LST_CONNECT_HOLDING;
        p_lcb->handle = HCI_INVALID_HANDLE;
    }
    else
    {
        /* Just in case app decides to try again in the callback context */
        p_lcb->link_state = LST_DISCONNECTING;

        /* Connection failed. For all channels, send the event through */
        /* their FSMs. The CCBs should remove themselves from the LCB  */
        for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; )
        {
            tL2C_CCB *pn = p_ccb->p_next_ccb;

            l2c_csm_execute (p_ccb, L2CEVT_LP_CONNECT_CFM_NEG, &ci);

            p_ccb = pn;
        }

        p_lcb->disc_reason = status;
        /* Release the LCB */
        if (p_lcb->ccb_queue.p_first_ccb == NULL)
            l2cu_release_lcb (p_lcb);
        else                              /* there are any CCBs remaining */
        {
            if (ci.status == HCI_ERR_CONNECTION_EXISTS)
            {
                /* we are in collision situation, wait for connecttion request from controller */
                p_lcb->link_state = LST_CONNECTING;
            }
            else
            {
                l2cu_create_conn(p_lcb);
            }
        }
    }
    return (TRUE);
}


/*******************************************************************************
**
** Function         l2c_link_sec_comp
**
** Description      This function is called when required security procedures
**                  are completed.
**
** Returns          void
**
*******************************************************************************/
void l2c_link_sec_comp (BD_ADDR p_bda, void *p_ref_data, UINT8 status)
{
    tL2C_CONN_INFO  ci;
    tL2C_LCB        *p_lcb;
    tL2C_CCB        *p_ccb;
    tL2C_CCB        *p_next_ccb;
    UINT8           event;

    L2CAP_TRACE_DEBUG2 ("l2c_link_sec_comp: %d, 0x%x", status, p_ref_data);

    if (status == BTM_SUCCESS_NO_SECURITY)
        status = BTM_SUCCESS;

    /* Save the parameters */
    ci.status       = status;
    memcpy (ci.bd_addr, p_bda, BD_ADDR_LEN);

    p_lcb = l2cu_find_lcb_by_bd_addr (p_bda);

    /* If we don't have one, this is an error */
    if (!p_lcb)
    {
        L2CAP_TRACE_WARNING0 ("L2CAP got sec_comp for unknown BD_ADDR");
        return;
    }

    /* Match p_ccb with p_ref_data returned by sec manager */
    for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_next_ccb)
    {
        p_next_ccb = p_ccb->p_next_ccb;

        if (p_ccb == p_ref_data)
        {
            switch(status)
            {
            case BTM_SUCCESS:
                L2CAP_TRACE_DEBUG1 ("ccb timer ticks: %u", p_ccb->timer_entry.ticks);
                event = L2CEVT_SEC_COMP;
                break;

            case BTM_DELAY_CHECK:
                /* start a timer - encryption change not received before L2CAP connect req */
                btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_DELAY_CHECK_SM4);
                return;

            default:
                event = L2CEVT_SEC_COMP_NEG;
            }
            l2c_csm_execute (p_ccb, event, &ci);
            break;
        }
    }
}


/*******************************************************************************
**
** Function         l2c_link_hci_disc_comp
**
** Description      This function is called when an HCI Disconnect Complete
**                  event is received.
**
** Returns          TRUE if the link is known about, else FALSE
**
*******************************************************************************/
BOOLEAN l2c_link_hci_disc_comp (UINT16 handle, UINT8 reason)
{
    tL2C_LCB    *p_lcb;
    tL2C_CCB    *p_ccb;
    BOOLEAN     status = TRUE;
    BOOLEAN     lcb_is_free = TRUE;

    /* See if we have a link control block for the connection */
    p_lcb = l2cu_find_lcb_by_handle (handle);

    /* If we don't have one, maybe an SCO link. Send to MM */
    if (!p_lcb)
    {
        status = FALSE;
    }
    else
    {
        /* There can be a case when we rejected PIN code authentication */
        /* otherwise save a new reason */
        if (btm_cb.acl_disc_reason != HCI_ERR_HOST_REJECT_SECURITY)
            btm_cb.acl_disc_reason = reason;

        p_lcb->disc_reason = btm_cb.acl_disc_reason;

        /* Just in case app decides to try again in the callback context */
        p_lcb->link_state = LST_DISCONNECTING;

        /* Link is disconnected. For all channels, send the event through */
        /* their FSMs. The CCBs should remove themselves from the LCB     */
        for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; )
        {
            tL2C_CCB *pn = p_ccb->p_next_ccb;

            /* Keep connect pending control block (if exists)
             * Possible Race condition when a reconnect occurs
             * on the channel during a disconnect of link. This
             * ccb will be automatically retried after link disconnect
             * arrives
             */
            if (p_ccb != p_lcb->p_pending_ccb)
            {
                l2c_csm_execute (p_ccb, L2CEVT_LP_DISCONNECT_IND, &reason);
            }
            p_ccb = pn;
        }

#if BTM_SCO_INCLUDED == TRUE
        /* Tell SCO management to drop any SCOs on this ACL */
        btm_sco_acl_removed (p_lcb->remote_bd_addr);
#endif

        /* If waiting for disconnect and reconnect is pending start the reconnect now
           race condition where layer above issued connect request on link that was
           disconnecting
         */
        if (p_lcb->ccb_queue.p_first_ccb != NULL)
        {
#if (L2CAP_NUM_FIXED_CHNLS > 0)
            /* If we are going to re-use the LCB without dropping it, release all fixed channels here */
            int         xx;

            for (xx = 0; xx < L2CAP_NUM_FIXED_CHNLS; xx++)
            {
                if (p_lcb->p_fixed_ccbs[xx])
                {
                    (*l2cb.fixed_reg[xx].pL2CA_FixedConn_Cb)(p_lcb->remote_bd_addr, FALSE, p_lcb->disc_reason);
                    l2cu_release_ccb (p_lcb->p_fixed_ccbs[xx]);

                    p_lcb->p_fixed_ccbs[xx] = NULL;
                }
            }
#endif
            L2CAP_TRACE_DEBUG0("l2c_link_hci_disc_comp: Restarting pending ACL request");

            if (l2cu_create_conn(p_lcb))
                lcb_is_free = FALSE; /* still using this lcb */
        }

        p_lcb->p_pending_ccb = NULL;

        /* Release the LCB */
        if (lcb_is_free)
            l2cu_release_lcb (p_lcb);
    }

    /* Now that we have a free acl connection, see if any lcbs are pending */
    if (lcb_is_free && ((p_lcb = l2cu_find_lcb_by_state(LST_CONNECT_HOLDING)) != NULL))
    {
        /* we found one-- create a connection */
        l2cu_create_conn(p_lcb);
    }

    return status;
}


/*******************************************************************************
**
** Function         l2c_link_hci_qos_violation
**
** Description      This function is called when an HCI QOS Violation
**                  event is received.
**
** Returns          TRUE if the link is known about, else FALSE
**
*******************************************************************************/
BOOLEAN l2c_link_hci_qos_violation (UINT16 handle)
{
    tL2C_LCB        *p_lcb;
    tL2C_CCB        *p_ccb;

    /* See if we have a link control block for the connection */
    p_lcb = l2cu_find_lcb_by_handle (handle);

    /* If we don't have one, maybe an SCO link. */
    if (!p_lcb)
        return (FALSE);

    /* For all channels, tell the upper layer about it */
    for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_ccb->p_next_ccb)
    {
        if (p_ccb->p_rcb->api.pL2CA_QoSViolationInd_Cb)
            l2c_csm_execute (p_ccb, L2CEVT_LP_QOS_VIOLATION_IND, NULL);
    }

    return (TRUE);
}



/*******************************************************************************
**
** Function         l2c_link_timeout
**
** Description      This function is called when a link timer expires
**
** Returns          void
**
*******************************************************************************/
void l2c_link_timeout (tL2C_LCB *p_lcb)
{
    tL2C_CCB   *p_ccb;
    UINT16      timeout;
    tBTM_STATUS rc;

     L2CAP_TRACE_EVENT3 ("L2CAP - l2c_link_timeout() link state %d first CCB %p is_bonding:%d",
         p_lcb->link_state, p_lcb->ccb_queue.p_first_ccb, p_lcb->is_bonding);

    /* If link was connecting or disconnecting, clear all channels and drop the LCB */
    if ((p_lcb->link_state == LST_CONNECTING_WAIT_SWITCH) ||
        (p_lcb->link_state == LST_CONNECTING) ||
        (p_lcb->link_state == LST_CONNECT_HOLDING) ||
        (p_lcb->link_state == LST_DISCONNECTING))
    {
        p_lcb->p_pending_ccb = NULL;

        /* For all channels, send a disconnect indication event through */
        /* their FSMs. The CCBs should remove themselves from the LCB   */
        for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; )
        {
            tL2C_CCB *pn = p_ccb->p_next_ccb;

            l2c_csm_execute (p_ccb, L2CEVT_LP_DISCONNECT_IND, NULL);

            p_ccb = pn;
        }
#if (BLE_INCLUDED == TRUE)
        if (p_lcb->link_state == LST_CONNECTING &&
            l2cb.is_ble_connecting == TRUE)
        {
            L2CA_CancelBleConnectReq(l2cb.ble_connecting_bda);
        }
#endif
        /* Release the LCB */
        l2cu_release_lcb (p_lcb);
    }

    /* If link is connected, check for inactivity timeout */
    if (p_lcb->link_state == LST_CONNECTED)
    {
        /* Check for ping outstanding */
        if (p_lcb->p_echo_rsp_cb)
        {
            tL2CA_ECHO_RSP_CB *p_cb = p_lcb->p_echo_rsp_cb;

            /* Zero out the callback in case app immediately calls us again */
            p_lcb->p_echo_rsp_cb = NULL;

            (*p_cb) (L2CAP_PING_RESULT_NO_RESP);

             L2CAP_TRACE_WARNING0 ("L2CAP - ping timeout");

            /* For all channels, send a disconnect indication event through */
            /* their FSMs. The CCBs should remove themselves from the LCB   */
            for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; )
            {
                tL2C_CCB *pn = p_ccb->p_next_ccb;

                l2c_csm_execute (p_ccb, L2CEVT_LP_DISCONNECT_IND, NULL);

                p_ccb = pn;
            }
        }

        /* If no channels in use, drop the link. */
        if (!p_lcb->ccb_queue.p_first_ccb)
        {
            rc = btm_sec_disconnect (p_lcb->handle, HCI_ERR_PEER_USER);

            if (rc == BTM_CMD_STORED)
            {
                /* Security Manager will take care of disconnecting, state will be updated at that time */
                timeout = 0xFFFF;
            }
            else if (rc == BTM_CMD_STARTED)
            {
                p_lcb->link_state = LST_DISCONNECTING;
                timeout = L2CAP_LINK_DISCONNECT_TOUT;
            }
            else if (rc == BTM_SUCCESS)
            {
                /* BTM SEC will make sure that link is release (probably after pairing is done) */
                p_lcb->link_state = LST_DISCONNECTING;
                timeout = 0xFFFF;
            }
            else if (rc == BTM_BUSY)
            {
                /* BTM is still executing security process. Let lcb stay as connected */
                timeout = 0xFFFF;
            }
            else if ((p_lcb->is_bonding)
                  && (btsnd_hcic_disconnect (p_lcb->handle, HCI_ERR_PEER_USER)))
            {
                p_lcb->link_state = LST_DISCONNECTING;
                timeout = L2CAP_LINK_DISCONNECT_TOUT;
            }
            else
            {
                /* probably no buffer to send disconnect */
                timeout = BT_1SEC_TIMEOUT;
            }

            if (timeout != 0xFFFF)
            {
                btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, timeout);
            }
        }
        else
        {
            /* Check in case we were flow controlled */
            l2c_link_check_send_pkts (p_lcb, NULL, NULL);
        }
    }
}

/*******************************************************************************
**
** Function         l2c_info_timeout
**
** Description      This function is called when an info request times out
**
** Returns          void
**
*******************************************************************************/
void l2c_info_timeout (tL2C_LCB *p_lcb)
{
    tL2C_CCB   *p_ccb;
    tL2C_CONN_INFO  ci;

    /* If we timed out waiting for info response, just continue using basic if allowed */
    if (p_lcb->w4_info_rsp)
    {
        /* If waiting for security complete, restart the info response timer */
        for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_ccb->p_next_ccb)
        {
            if ( (p_ccb->chnl_state == CST_ORIG_W4_SEC_COMP) || (p_ccb->chnl_state == CST_TERM_W4_SEC_COMP) )
            {
                btu_start_timer (&p_lcb->info_timer_entry, BTU_TTYPE_L2CAP_INFO, L2CAP_WAIT_INFO_RSP_TOUT);
                return;
            }
        }

        p_lcb->w4_info_rsp = FALSE;

        /* If link is in process of being brought up */
        if ((p_lcb->link_state != LST_DISCONNECTED) &&
            (p_lcb->link_state != LST_DISCONNECTING))
        {
            /* Notify active channels that peer info is finished */
            if (p_lcb->ccb_queue.p_first_ccb)
            {
                ci.status = HCI_SUCCESS;
                memcpy (ci.bd_addr, p_lcb->remote_bd_addr, sizeof(BD_ADDR));

                for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_ccb->p_next_ccb)
                {
                    l2c_csm_execute (p_ccb, L2CEVT_L2CAP_INFO_RSP, &ci);
                }
            }
        }
    }
}

/*******************************************************************************
**
** Function         l2c_link_adjust_allocation
**
** Description      This function is called when a link is created or removed
**                  to calculate the amount of packets each link may send to
**                  the HCI without an ack coming back.
**
**                  Currently, this is a simple allocation, dividing the
**                  number of Controller Packets by the number of links. In
**                  the future, QOS configuration should be examined.
**
** Returns          void
**
*******************************************************************************/
void l2c_link_adjust_allocation (void)
{
    UINT16      qq, yy, qq_remainder;
    tL2C_LCB    *p_lcb;
    UINT16      hi_quota, low_quota;
    UINT16      num_lowpri_links = 0;
    UINT16      num_hipri_links  = 0;
    UINT16      controller_xmit_quota = l2cb.num_lm_acl_bufs;
    UINT16      high_pri_link_quota = L2CAP_HIGH_PRI_MIN_XMIT_QUOTA_A;

    /* If no links active, nothing to do. */
    if (l2cb.num_links_active == 0)
    {
        l2cb.controller_xmit_window = l2cb.num_lm_acl_bufs;
        l2cb.round_robin_quota = l2cb.round_robin_unacked = 0;
        return;
    }

    /* First, count the links */
    for (yy = 0, p_lcb = &l2cb.lcb_pool[0]; yy < MAX_L2CAP_LINKS; yy++, p_lcb++)
    {
        if (p_lcb->in_use)
        {
            if (p_lcb->acl_priority == L2CAP_PRIORITY_HIGH)
                num_hipri_links++;
            else
                num_lowpri_links++;
        }
    }

    /* now adjust high priority link quota */
    low_quota = num_lowpri_links ? 1 : 0;
    while ( (num_hipri_links * high_pri_link_quota + low_quota) > controller_xmit_quota )
        high_pri_link_quota--;

    /* Work out the xmit quota and buffer quota high and low priorities */
    hi_quota  = num_hipri_links * high_pri_link_quota;
    low_quota = (hi_quota < controller_xmit_quota) ? controller_xmit_quota - hi_quota : 1;

    /* Work out and save the HCI xmit quota for each low priority link */

    /* If each low priority link cannot have at least one buffer */
    if (num_lowpri_links > low_quota)
    {
        l2cb.round_robin_quota = low_quota;
        qq = qq_remainder = 0;
    }
    /* If each low priority link can have at least one buffer */
    else if (num_lowpri_links > 0)
    {
        l2cb.round_robin_quota = 0;
        l2cb.round_robin_unacked = 0;
        qq = low_quota / num_lowpri_links;
        qq_remainder = low_quota % num_lowpri_links;
    }
    /* If no low priority link */
    else
    {
        l2cb.round_robin_quota = 0;
        l2cb.round_robin_unacked = 0;
        qq = qq_remainder = 0;
    }

    L2CAP_TRACE_EVENT5 ("l2c_link_adjust_allocation  num_hipri: %u  num_lowpri: %u  low_quota: %u  round_robin_quota: %u  qq: %u",
                        num_hipri_links, num_lowpri_links, low_quota,
                        l2cb.round_robin_quota, qq);

    /* Now, assign the quotas to each link */
    for (yy = 0, p_lcb = &l2cb.lcb_pool[0]; yy < MAX_L2CAP_LINKS; yy++, p_lcb++)
    {
        if (p_lcb->in_use)
        {
            if (p_lcb->acl_priority == L2CAP_PRIORITY_HIGH)
            {
                p_lcb->link_xmit_quota   = high_pri_link_quota;
            }
            else
            {
                /* Safety check in case we switched to round-robin with something outstanding */
                /* if sent_not_acked is added into round_robin_unacked then don't add it again */
                /* l2cap keeps updating sent_not_acked for exiting from round robin */
                if (( p_lcb->link_xmit_quota > 0 )&&( qq == 0 ))
                    l2cb.round_robin_unacked += p_lcb->sent_not_acked;

                p_lcb->link_xmit_quota   = qq;
                if (qq_remainder > 0)
                {
                    p_lcb->link_xmit_quota++;
                    qq_remainder--;
                }
            }

#if L2CAP_HOST_FLOW_CTRL
            p_lcb->link_ack_thresh = L2CAP_HOST_FC_ACL_BUFS / l2cb.num_links_active;
#endif
            L2CAP_TRACE_EVENT3 ("l2c_link_adjust_allocation LCB %d   Priority: %d  XmitQuota: %d",
                                yy, p_lcb->acl_priority, p_lcb->link_xmit_quota);

            L2CAP_TRACE_EVENT2 ("        SentNotAcked: %d  RRUnacked: %d",
                                p_lcb->sent_not_acked, l2cb.round_robin_unacked);

            /* There is a special case where we have readjusted the link quotas and  */
            /* this link may have sent anything but some other link sent packets so  */
            /* so we may need a timer to kick off this link's transmissions.         */
            if ( (p_lcb->link_state == LST_CONNECTED)
              && (p_lcb->link_xmit_data_q.count)
              && (p_lcb->sent_not_acked < p_lcb->link_xmit_quota) )
                btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, L2CAP_LINK_FLOW_CONTROL_TOUT);
        }
    }

}

/*******************************************************************************
**
** Function         l2c_link_adjust_chnl_allocation
**
** Description      This function is called to calculate the amount of packets each
**                  non-F&EC channel may have outstanding.
**
**                  Currently, this is a simple allocation, dividing the number
**                  of packets allocated to the link by the number of channels. In
**                  the future, QOS configuration should be examined.
**
** Returns          void
**
*******************************************************************************/
void l2c_link_adjust_chnl_allocation (void)
{
    tL2C_CCB    *p_ccb;
    UINT8       xx;

    UINT16      weighted_chnls[GKI_NUM_TOTAL_BUF_POOLS];
    UINT16      quota_per_weighted_chnls[GKI_NUM_TOTAL_BUF_POOLS];
    UINT16      reserved_buff[GKI_NUM_TOTAL_BUF_POOLS];

    L2CAP_TRACE_DEBUG0 ("l2c_link_adjust_chnl_allocation");

    /* initialize variables */
    for (xx = 0; xx < GKI_NUM_TOTAL_BUF_POOLS; xx++ )
    {
        weighted_chnls[xx] = 0;
        reserved_buff[xx] = 0;
    }

    /* add up all of tx and rx data rate requirement */
    /* channel required higher data rate will get more buffer quota */
    for (xx = 0; xx < MAX_L2CAP_CHANNELS; xx++)
    {
        p_ccb = l2cb.ccb_pool + xx;

        if (!p_ccb->in_use)
            continue;

        if (p_ccb->peer_cfg.fcr.mode != L2CAP_FCR_BASIC_MODE)
        {
            weighted_chnls[p_ccb->ertm_info.user_tx_pool_id] += p_ccb->tx_data_rate;
            weighted_chnls[p_ccb->ertm_info.user_rx_pool_id] += p_ccb->rx_data_rate;

            if (p_ccb->ertm_info.fcr_tx_pool_id == HCI_ACL_POOL_ID)
            {
                /* reserve buffers only for wait_for_ack_q to maximize throughput */
                /* retrans_q will work based on buffer status */
                reserved_buff[HCI_ACL_POOL_ID] += p_ccb->peer_cfg.fcr.tx_win_sz;
            }

            if (p_ccb->ertm_info.fcr_rx_pool_id == HCI_ACL_POOL_ID)
            {
                /* reserve buffers for srej_rcv_hold_q */
                reserved_buff[HCI_ACL_POOL_ID] += p_ccb->peer_cfg.fcr.tx_win_sz;
            }
        }
        else
        {
            /* low data rate is 1, medium is 2, high is 3 and no traffic is 0 */
            weighted_chnls[HCI_ACL_POOL_ID] += p_ccb->tx_data_rate + p_ccb->rx_data_rate;
        }
    }


    /* get unit quota per pool */
    for (xx = 0; xx < GKI_NUM_TOTAL_BUF_POOLS; xx++ )
    {
        if ( weighted_chnls[xx] > 0 )
        {
            if (GKI_poolcount(xx) > reserved_buff[xx])
                quota_per_weighted_chnls[xx] = ((GKI_poolcount(xx) - reserved_buff[xx])/weighted_chnls[xx]) + 1;
            else
                quota_per_weighted_chnls[xx] = 1;

            L2CAP_TRACE_DEBUG5 ("POOL ID:%d, GKI_poolcount = %d, reserved_buff = %d, weighted_chnls = %d, quota_per_weighted_chnls = %d",
                                 xx, GKI_poolcount(xx), reserved_buff[xx], weighted_chnls[xx], quota_per_weighted_chnls[xx] );
        }
        else
            quota_per_weighted_chnls[xx] = 0;
    }


    /* assign buffer quota to each channel based on its data rate requirement */
    for (xx = 0; xx < MAX_L2CAP_CHANNELS; xx++)
    {
        p_ccb = l2cb.ccb_pool + xx;

        if (!p_ccb->in_use)
            continue;

        if (p_ccb->peer_cfg.fcr.mode != L2CAP_FCR_BASIC_MODE)
        {
            p_ccb->buff_quota = quota_per_weighted_chnls[p_ccb->ertm_info.user_tx_pool_id] * p_ccb->tx_data_rate;

            L2CAP_TRACE_EVENT6 ("CID:0x%04x FCR Mode:%u UserTxPool:%u Priority:%u TxDataRate:%u Quota:%u",
                                p_ccb->local_cid, p_ccb->peer_cfg.fcr.mode, p_ccb->ertm_info.user_tx_pool_id,
                                p_ccb->ccb_priority, p_ccb->tx_data_rate, p_ccb->buff_quota);

        }
        else
        {
            p_ccb->buff_quota = quota_per_weighted_chnls[HCI_ACL_POOL_ID] * p_ccb->tx_data_rate;

            L2CAP_TRACE_EVENT4 ("CID:0x%04x Priority:%u TxDataRate:%u Quota:%u",
                                p_ccb->local_cid,
                                p_ccb->ccb_priority, p_ccb->tx_data_rate, p_ccb->buff_quota);
        }

        /* quota may be change so check congestion */
        l2cu_check_channel_congestion (p_ccb);
    }
}

/*******************************************************************************
**
** Function         l2c_link_processs_num_bufs
**
** Description      This function is called when a "controller buffer size"
**                  event is first received from the controller. It updates
**                  the L2CAP values.
**
** Returns          void
**
*******************************************************************************/
void l2c_link_processs_num_bufs (UINT16 num_lm_acl_bufs)
{
    l2cb.num_lm_acl_bufs = l2cb.controller_xmit_window = num_lm_acl_bufs;

}

/*******************************************************************************
**
** Function         l2c_link_pkts_rcvd
**
** Description      This function is called from the HCI transport when it is time
**                  tto send a "Host ready for packets" command. This is only when
**                  host to controller flow control is used. If fills in the arrays
**                  of numbers of packets and handles.
**
** Returns          count of number of entries filled in
**
*******************************************************************************/
UINT8 l2c_link_pkts_rcvd (UINT16 *num_pkts, UINT16 *handles)
{
    UINT8       num_found = 0;

#if (L2CAP_HOST_FLOW_CTRL == TRUE)

    int         xx;
    tL2C_LCB    *p_lcb = &l2cb.lcb_pool[0];

    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_lcb++)
    {
        if ((p_lcb->in_use) && (p_lcb->link_pkts_unacked))
        {
            num_pkts[num_found] = p_lcb->link_pkts_unacked;
            handles[num_found]  = p_lcb->handle;
            p_lcb->link_pkts_unacked = 0;
            num_found++;
        }
    }

#endif

    return (num_found);
}

/*******************************************************************************
**
** Function         l2c_link_role_changed
**
** Description      This function is called whan a link's master/slave role change
**                  event is received. It simply updates the link control block.
**
** Returns          void
**
*******************************************************************************/
void l2c_link_role_changed (BD_ADDR bd_addr, UINT8 new_role, UINT8 hci_status)
{
    tL2C_LCB *p_lcb;
    int      xx;

    /* Make sure not called from HCI Command Status (bd_addr and new_role are invalid) */
    if (bd_addr)
    {
        /* If here came form hci role change event */
        p_lcb = l2cu_find_lcb_by_bd_addr (bd_addr);
        if (p_lcb)
        {
            p_lcb->link_role = new_role;

            /* Reset high priority link if needed */
            if (hci_status == HCI_SUCCESS)
                l2cu_set_acl_priority(bd_addr, p_lcb->acl_priority, TRUE);
        }
    }

    /* Check if any LCB was waiting for switch to be completed */
    for (xx = 0, p_lcb = &l2cb.lcb_pool[0]; xx < MAX_L2CAP_LINKS; xx++, p_lcb++)
    {
        if ((p_lcb->in_use) && (p_lcb->link_state == LST_CONNECTING_WAIT_SWITCH))
        {
            l2cu_create_conn_after_switch (p_lcb);
        }
    }
}

/*******************************************************************************
**
** Function         l2c_pin_code_request
**
** Description      This function is called whan a pin-code request is received
**                  on a connection. If there are no channels active yet on the
**                  link, it extends the link first connection timer.  Make sure
**                  that inactivity timer is not extended if PIN code happens
**                  to be after last ccb released.
**
** Returns          void
**
*******************************************************************************/
void l2c_pin_code_request (BD_ADDR bd_addr)
{
    tL2C_LCB *p_lcb = l2cu_find_lcb_by_bd_addr (bd_addr);

    if ( (p_lcb) && (!p_lcb->ccb_queue.p_first_ccb) )
    {
        btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, L2CAP_LINK_CONNECT_TOUT_EXT);
    }
}

#if ((BTM_PWR_MGR_INCLUDED == TRUE) && L2CAP_WAKE_PARKED_LINK == TRUE)
/*******************************************************************************
**
** Function         l2c_link_check_power_mode
**
** Description      This function is called to check power mode.
**
** Returns          TRUE if link is going to be active from park
**                  FALSE if nothing to send or not in park mode
**
*******************************************************************************/
BOOLEAN l2c_link_check_power_mode (tL2C_LCB *p_lcb)
{
    tBTM_PM_MODE     mode;
    tBTM_PM_PWR_MD   pm;
    tL2C_CCB    *p_ccb;
    BOOLEAN need_to_active = FALSE;

    /*
     * We only switch park to active only if we have unsent packets
     */
    if ( p_lcb->link_xmit_data_q.count == 0 )
    {
        for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_ccb->p_next_ccb)
        {
            if (p_ccb->xmit_hold_q.count != 0)
            {
                need_to_active = TRUE;
                break;
            }
        }
    }
    else
        need_to_active = TRUE;

    /* if we have packets to send */
    if ( need_to_active )
    {
        /* check power mode */
        if (BTM_ReadPowerMode(p_lcb->remote_bd_addr, &mode) == BTM_SUCCESS)
        {
            /*
            if ( mode == BTM_PM_MD_PARK )
            {
                L2CAP_TRACE_DEBUG1 ("LCB(0x%x) is in park mode", p_lcb->handle);
// Coverity:
// FALSE-POSITIVE error from Coverity test tool. Please do NOT remove following comment.
// coverity[uninit_use_in_call] False-positive: setting the mode to BTM_PM_MD_ACTIVE only uses settings.mode
                                the other data members of tBTM_PM_PWR_MD are ignored

                memset((void*)&pm, 0, sizeof(pm));
                pm.mode = BTM_PM_MD_ACTIVE;
                BTM_SetPowerMode(BTM_PM_SET_ONLY_ID, p_lcb->remote_bd_addr, &pm);
                btu_start_timer (&p_lcb->timer_entry,
                                 BTU_TTYPE_L2CAP_LINK, L2CAP_WAIT_UNPARK_TOUT);
                return TRUE;
            }
            */
            if ( mode == BTM_PM_STS_PENDING )
            {
                L2CAP_TRACE_DEBUG1 ("LCB(0x%x) is in PM pending state", p_lcb->handle);

                btu_start_timer (&p_lcb->timer_entry,
                                 BTU_TTYPE_L2CAP_LINK, L2CAP_WAIT_UNPARK_TOUT);
                return TRUE;
            }
        }
    }
    return FALSE;
}
#endif /* ((BTM_PWR_MGR_INCLUDED == TRUE) && L2CAP_WAKE_PARKED_LINK == TRUE) */

/*******************************************************************************
**
** Function         l2c_link_check_send_pkts
**
** Description      This function is called to check if it can send packets
**                  to the Host Controller. It may be passed the address of
**                  a packet to send.
**
** Returns          void
**
*******************************************************************************/
void l2c_link_check_send_pkts (tL2C_LCB *p_lcb, tL2C_CCB *p_ccb, BT_HDR *p_buf)
{
    int         xx;
    BOOLEAN     single_write = FALSE;

    /* Save the channel ID for faster counting */
    if (p_buf)
    {
        if (p_ccb != NULL)
        {
            p_buf->event = p_ccb->local_cid;
            single_write = TRUE;
        }
        else
            p_buf->event = 0;

        p_buf->layer_specific = 0;
        GKI_enqueue (&p_lcb->link_xmit_data_q, p_buf);

        if (p_lcb->link_xmit_quota == 0)
            l2cb.check_round_robin = TRUE;
    }

    /* If this is called from uncongested callback context break recursive calling.
    ** This LCB will be served when receiving number of completed packet event.
    */
    if (l2cb.is_cong_cback_context)
        return;

    /* If we are in a scenario where there are not enough buffers for each link to
    ** have at least 1, then do a round-robin for all the LCBs
    */
    if ( (p_lcb == NULL) || (p_lcb->link_xmit_quota == 0) )
    {
        if (p_lcb == NULL)
            p_lcb = l2cb.lcb_pool;
        else if (!single_write)
            p_lcb++;

        /* Loop through, starting at the next */
        for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_lcb++)
        {
            /* If controller window is full, nothing to do */
            if ( (l2cb.controller_xmit_window == 0
#if (BLE_INCLUDED == TRUE)
                  && !p_lcb->is_ble_link
#endif
                )
#if (BLE_INCLUDED == TRUE)
                || (p_lcb->is_ble_link && l2cb.controller_le_xmit_window == 0 )
#endif
              || (l2cb.round_robin_unacked >= l2cb.round_robin_quota) )
                break;

            /* Check for wraparound */
            if (p_lcb == &l2cb.lcb_pool[MAX_L2CAP_LINKS])
                p_lcb = &l2cb.lcb_pool[0];

            if ( (!p_lcb->in_use)
               || (p_lcb->partial_segment_being_sent)
               || (p_lcb->link_state != LST_CONNECTED)
               || (p_lcb->link_xmit_quota != 0)
               || (L2C_LINK_CHECK_POWER_MODE (p_lcb)) )
                continue;

            /* See if we can send anything from the Link Queue */
            if ((p_buf = (BT_HDR *)GKI_dequeue (&p_lcb->link_xmit_data_q)) != NULL)
            {
                l2c_link_send_to_lower (p_lcb, p_buf);
            }
            else if (single_write)
            {
                /* If only doing one write, break out */
                break;
            }
            /* If nothing on the link queue, check the channel queue */
            else if ((p_buf = l2cu_get_next_buffer_to_send (p_lcb)) != NULL)
            {
                l2c_link_send_to_lower (p_lcb, p_buf);
            }
        }

        /* If we finished without using up our quota, no need for a safety check */
#if (BLE_INCLUDED == TRUE)
        if ( ((l2cb.controller_xmit_window > 0 && !p_lcb->is_ble_link) ||
             (l2cb.controller_le_xmit_window > 0 && p_lcb->is_ble_link))
          && (l2cb.round_robin_unacked < l2cb.round_robin_quota) )
#else
        if ( (l2cb.controller_xmit_window > 0)
          && (l2cb.round_robin_unacked < l2cb.round_robin_quota) )

#endif
            l2cb.check_round_robin = FALSE;
    }
    else /* if this is not round-robin service */
    {
        /* If a partial segment is being sent, can't send anything else */
        if ( (p_lcb->partial_segment_being_sent)
          || (p_lcb->link_state != LST_CONNECTED)
          || (L2C_LINK_CHECK_POWER_MODE (p_lcb)) )
            return;

        /* See if we can send anything from the link queue */
#if (BLE_INCLUDED == TRUE)
        while ( ((l2cb.controller_xmit_window != 0 && !p_lcb->is_ble_link) ||
                 (l2cb.controller_le_xmit_window != 0 && p_lcb->is_ble_link))
             && (p_lcb->sent_not_acked < p_lcb->link_xmit_quota))
#else
        while ( (l2cb.controller_xmit_window != 0)
             && (p_lcb->sent_not_acked < p_lcb->link_xmit_quota))
#endif
        {
            if ((p_buf = (BT_HDR *)GKI_dequeue (&p_lcb->link_xmit_data_q)) == NULL)
                break;

            if (!l2c_link_send_to_lower (p_lcb, p_buf))
                break;
        }

        if (!single_write)
        {
            /* See if we can send anything for any channel */
#if (BLE_INCLUDED == TRUE)
            while ( ((l2cb.controller_xmit_window != 0 && !p_lcb->is_ble_link) ||
                    (l2cb.controller_le_xmit_window != 0 && p_lcb->is_ble_link))
                    && (p_lcb->sent_not_acked < p_lcb->link_xmit_quota))
#else
            while ((l2cb.controller_xmit_window != 0) && (p_lcb->sent_not_acked < p_lcb->link_xmit_quota))
#endif
            {
                if ((p_buf = l2cu_get_next_buffer_to_send (p_lcb)) == NULL)
                    break;

                if (!l2c_link_send_to_lower (p_lcb, p_buf))
                    break;
            }
        }

        /* There is a special case where we have readjusted the link quotas and  */
        /* this link may have sent anything but some other link sent packets so  */
        /* so we may need a timer to kick off this link's transmissions.         */
        if ( (p_lcb->link_xmit_data_q.count) && (p_lcb->sent_not_acked < p_lcb->link_xmit_quota) )
            btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, L2CAP_LINK_FLOW_CONTROL_TOUT);
    }

}

/*******************************************************************************
**
** Function         l2c_link_send_to_lower
**
** Description      This function queues the buffer for HCI transmission
**
** Returns          TRUE for success, FALSE for fail
**
*******************************************************************************/
static BOOLEAN l2c_link_send_to_lower (tL2C_LCB *p_lcb, BT_HDR *p_buf)
{
    UINT16      num_segs;
    UINT16      xmit_window, acl_data_size;

#if (BLE_INCLUDED == TRUE)
    if ((!p_lcb->is_ble_link && (p_buf->len <= btu_cb.hcit_acl_pkt_size)) ||
        (p_lcb->is_ble_link && (p_buf->len <= btu_cb.hcit_ble_acl_pkt_size)))
#else
    if (p_buf->len <= btu_cb.hcit_acl_pkt_size)
#endif
    {
        if (p_lcb->link_xmit_quota == 0)
            l2cb.round_robin_unacked++;

        p_lcb->sent_not_acked++;
        p_buf->layer_specific = 0;

#if (BLE_INCLUDED == TRUE)
        if (p_lcb->is_ble_link)
        {
            l2cb.controller_le_xmit_window--;
            L2C_LINK_SEND_BLE_ACL_DATA (p_buf);
        }
        else
#endif
        {
            l2cb.controller_xmit_window--;
            L2C_LINK_SEND_ACL_DATA (p_buf);
        }
    }
    else
    {
#if BLE_INCLUDED == TRUE
        if (p_lcb->is_ble_link)
        {
            acl_data_size = btu_cb.hcit_ble_acl_data_size;
            xmit_window = l2cb.controller_le_xmit_window;

        }
        else
#endif
        {
            acl_data_size = btu_cb.hcit_acl_data_size;
            xmit_window = l2cb.controller_xmit_window;
        }
        num_segs = (p_buf->len - HCI_DATA_PREAMBLE_SIZE + acl_data_size - 1) / acl_data_size;


        /* If doing round-robin, then only 1 segment each time */
        if (p_lcb->link_xmit_quota == 0)
        {
            num_segs = 1;
            p_lcb->partial_segment_being_sent = TRUE;
        }
        else
        {
            /* Multi-segment packet. Make sure it can fit */
            if (num_segs > xmit_window)
            {
                num_segs = xmit_window;
                p_lcb->partial_segment_being_sent = TRUE;
            }

            if (num_segs > (p_lcb->link_xmit_quota - p_lcb->sent_not_acked))
            {
                num_segs = (p_lcb->link_xmit_quota - p_lcb->sent_not_acked);
                p_lcb->partial_segment_being_sent = TRUE;
            }
        }

        p_buf->layer_specific        = num_segs;
#if BLE_INCLUDED == TRUE
        if (p_lcb->is_ble_link)
        {
            l2cb.controller_le_xmit_window -= num_segs;

        }
        else
#endif
        l2cb.controller_xmit_window -= num_segs;

        if (p_lcb->link_xmit_quota == 0)
            l2cb.round_robin_unacked += num_segs;

        p_lcb->sent_not_acked += num_segs;
#if BLE_INCLUDED == TRUE
        if (p_lcb->is_ble_link)
        {
            L2C_LINK_SEND_BLE_ACL_DATA(p_buf);
        }
        else
#endif
        {
            L2C_LINK_SEND_ACL_DATA (p_buf);
        }
    }

#if (L2CAP_HCI_FLOW_CONTROL_DEBUG == TRUE)
#if (BLE_INCLUDED == TRUE)
    if (p_lcb->is_ble_link)
    {
        L2CAP_TRACE_DEBUG6 ("TotalWin=%d,Hndl=0x%x,Quota=%d,Unack=%d,RRQuota=%d,RRUnack=%d",
                l2cb.controller_le_xmit_window,
                p_lcb->handle,
                p_lcb->link_xmit_quota, p_lcb->sent_not_acked,
                l2cb.round_robin_quota, l2cb.round_robin_unacked);
    }
    else
#endif
    {
        L2CAP_TRACE_DEBUG6 ("TotalWin=%d,Hndl=0x%x,Quota=%d,Unack=%d,RRQuota=%d,RRUnack=%d",
                l2cb.controller_xmit_window,
                p_lcb->handle,
                p_lcb->link_xmit_quota, p_lcb->sent_not_acked,
                l2cb.round_robin_quota, l2cb.round_robin_unacked);
    }
#endif

    return TRUE;
}

/*******************************************************************************
**
** Function         l2c_link_process_num_completed_pkts
**
** Description      This function is called when a "number-of-completed-packets"
**                  event is received from the controller. It updates all the
**                  LCB transmit counts.
**
** Returns          void
**
*******************************************************************************/
void l2c_link_process_num_completed_pkts (UINT8 *p)
{
    UINT8       num_handles, xx;
    UINT16      handle;
    UINT16      num_sent;
    tL2C_LCB    *p_lcb;

    STREAM_TO_UINT8 (num_handles, p);

    for (xx = 0; xx < num_handles; xx++)
    {
        STREAM_TO_UINT16 (handle, p);
        STREAM_TO_UINT16 (num_sent, p);

        p_lcb = l2cu_find_lcb_by_handle (handle);

        /* Callback for number of completed packet event    */
        /* Originally designed for [3DSG]                   */
        if((p_lcb != NULL) && (p_lcb->p_nocp_cb))
        {
            L2CAP_TRACE_DEBUG0 ("L2CAP - calling NoCP callback");
            (*p_lcb->p_nocp_cb)(p_lcb->remote_bd_addr);
        }

#if (BLE_INCLUDED == TRUE)
        if (p_lcb && p_lcb->is_ble_link)
            l2cb.controller_le_xmit_window += num_sent;
        else
#endif
        {

            /* Maintain the total window to the controller */
            l2cb.controller_xmit_window += num_sent;
        }

        if (p_lcb)
        {
            /* If doing round-robin, adjust communal counts */
            if (p_lcb->link_xmit_quota == 0)
            {
                /* Don't go negative */
                if (l2cb.round_robin_unacked > num_sent)
                    l2cb.round_robin_unacked -= num_sent;
                else
                    l2cb.round_robin_unacked = 0;
            }

            /* Don't go negative */
            if (p_lcb->sent_not_acked > num_sent)
                p_lcb->sent_not_acked -= num_sent;
            else
                p_lcb->sent_not_acked = 0;

            l2c_link_check_send_pkts (p_lcb, NULL, NULL);

            /* If we were doing round-robin for low priority links, check 'em */
            if ( (p_lcb->acl_priority == L2CAP_PRIORITY_HIGH)
              && (l2cb.check_round_robin)
              && (l2cb.round_robin_unacked < l2cb.round_robin_quota) )
            {
              l2c_link_check_send_pkts (NULL, NULL, NULL);
            }
        }

#if (L2CAP_HCI_FLOW_CONTROL_DEBUG == TRUE)
        if (p_lcb)
        {
#if (BLE_INCLUDED == TRUE)
            if (p_lcb->is_ble_link)
            {
                L2CAP_TRACE_DEBUG5 ("TotalWin=%d,LinkUnack(0x%x)=%d,RRCheck=%d,RRUnack=%d",
                    l2cb.controller_le_xmit_window,
                    p_lcb->handle, p_lcb->sent_not_acked,
                    l2cb.check_round_robin, l2cb.round_robin_unacked);
            }
            else
#endif
            {
                L2CAP_TRACE_DEBUG5 ("TotalWin=%d,LinkUnack(0x%x)=%d,RRCheck=%d,RRUnack=%d",
                    l2cb.controller_xmit_window,
                    p_lcb->handle, p_lcb->sent_not_acked,
                    l2cb.check_round_robin, l2cb.round_robin_unacked);

            }
        }
        else
        {
#if (BLE_INCLUDED == TRUE)
            L2CAP_TRACE_DEBUG5 ("TotalWin=%d  LE_Win: %d, Handle=0x%x, RRCheck=%d, RRUnack=%d",
                l2cb.controller_xmit_window,
                l2cb.controller_le_xmit_window,
                handle,
                l2cb.check_round_robin, l2cb.round_robin_unacked);
#else
            L2CAP_TRACE_DEBUG4 ("TotalWin=%d  Handle=0x%x  RRCheck=%d  RRUnack=%d",
                l2cb.controller_xmit_window,
                handle,
                l2cb.check_round_robin, l2cb.round_robin_unacked);
#endif
        }
#endif
    }

#if (defined(HCILP_INCLUDED) && HCILP_INCLUDED == TRUE)
    /* only full stack can enable sleep mode */
    btu_check_bt_sleep ();
#endif
}

/*******************************************************************************
**
** Function         l2cap_link_chk_pkt_start
**
** Description      This function is called from the HCI transport when the first
**                  4 bytes of an HCI ACL packet have been received. It checks if the
**                  packet is the next segment of a fragmented L2CAP message. If it
**                  is, and the length is OK, it returns the address of the
**                  starting L2CAP message segment buffer.
**
** Returns          the address of the receive buffer HCIT should use
**                  (CR419: Modified to return NULL in case of error.)
**
** NOTE             This assumes that the L2CAP MTU size is less than the size
**                  of an HCI ACL buffer, so the maximum L2CAP message will fit
**                  into one buffer.
**
*******************************************************************************/
BT_HDR *l2cap_link_chk_pkt_start (BT_HDR *p_cur_buf)
{
    UINT8       *p;
    UINT16      handle;
    UINT16      hci_len;
    UINT16      pkt_type;
    tL2C_LCB    *p_lcb;
    BT_HDR *	p_return_buf;       /* CR419: To avoid returning from too many places */


    if (p_cur_buf)
    {
        p = (UINT8 *)(p_cur_buf + 1) + p_cur_buf->offset;
    }
    else
    {
        return (NULL);
    }

    /* L2CAP expects all rcvd packets to have a layer-specific value of 0 */
    p_cur_buf->layer_specific = 0;

    STREAM_TO_UINT16 (handle, p);
    STREAM_TO_UINT16 (hci_len, p);

    pkt_type = HCID_GET_EVENT (handle);
    handle   = HCID_GET_HANDLE (handle);

    l2cb.p_cur_hcit_lcb = NULL;

    /* Find the link that is associated with this handle */
    p_lcb = l2cu_find_lcb_by_handle (handle);

    /* If no link for this handle, nothing to do. */
    if (!p_lcb)
        return (p_cur_buf) ;

    if (pkt_type == L2CAP_PKT_START)            /*** START PACKET ***/
    {
        /* Start of packet. If we were in the middle of receiving */
        /* a packet, it is incomplete. Drop it.                   */
        if (p_lcb->p_hcit_rcv_acl)
        {
            L2CAP_TRACE_WARNING0 ("L2CAP - dropping incomplete pkt");
            GKI_freebuf (p_lcb->p_hcit_rcv_acl);
            p_lcb->p_hcit_rcv_acl = NULL;
        }

        /* Save the active buffer address in the LCB  */
        if ((p_return_buf = p_cur_buf) != NULL)
        {
            p_lcb->p_hcit_rcv_acl = p_return_buf;
            l2cb.p_cur_hcit_lcb   = p_lcb;
        }
    }
    else                                        /*** CONTINUATION PACKET ***/
    {
        /* Packet continuation. Check if we were expecting it */
        if (p_lcb->p_hcit_rcv_acl)
        {
            UINT16  total_len;
            BT_HDR  *p_base_buf = p_lcb->p_hcit_rcv_acl;
            UINT8   *p_f        = (UINT8 *)(p_base_buf + 1) + p_base_buf->offset + 2;

            STREAM_TO_UINT16 (total_len, p_f);

            /* We were expecting the CONTINUATION packet. If length fits, it can go in the  */
            /* current buffer.                                                              */
            if ((total_len + hci_len) <= (L2CAP_MTU_SIZE + HCI_DATA_PREAMBLE_SIZE))
            {
                /* GKI_freebuf (p_cur_buf); CR419:Do not free it yet */
                p_return_buf        = p_lcb->p_hcit_rcv_acl;	/* CR419: return base buffer */
                l2cb.p_cur_hcit_lcb = p_lcb;

                if ((p_cur_buf->len > HCI_DATA_PREAMBLE_SIZE))
                {
                    UINT8 *	p		= (UINT8 *)(p_cur_buf + 1)
                                                + p_cur_buf->offset
                                                + HCI_DATA_PREAMBLE_SIZE;
                    UINT8 *	p1		= (UINT8 *)(p_return_buf + 1)
                                                + p_return_buf->offset
                                                + p_return_buf->len;

                    /* Copy data from new buffer into base buffer then update the data  */
                    /* count in the base buffer accordingly.                            */
                    memcpy (p1, p, p_cur_buf->len - HCI_DATA_PREAMBLE_SIZE);
                    p_return_buf->len   += (p_cur_buf->len - HCI_DATA_PREAMBLE_SIZE);
                }

                GKI_freebuf (p_cur_buf);
                p_cur_buf = NULL;

                /* Update HCI header of first segment (base buffer) with new length */
                total_len += hci_len;
                p_f        = (UINT8 *)(p_base_buf + 1) + p_base_buf->offset + 2;
                UINT16_TO_STREAM (p_f, total_len);
            }
            else
            {
                /* Packet too long. Drop the base packet */
                L2CAP_TRACE_WARNING3 ("L2CAP - dropping too long pkt BufLen: %d  total_len: %d  hci_len: %d",
                                      p_lcb->p_hcit_rcv_acl->len, total_len, hci_len);

                GKI_freebuf (p_lcb->p_hcit_rcv_acl);
                p_lcb->p_hcit_rcv_acl = NULL;
                p_return_buf          = NULL ; /* Can't hold onto it any more */
            }
        }
        else                                    /*** NEITHER START OR CONTINUATION PACKET ***/
        {
            p_return_buf = NULL ;
        }
    }

    if (p_return_buf == NULL)                   /* if error is indicated..  */
    {
        if (p_cur_buf != NULL)                  /* ..drop input buffer      */
            GKI_freebuf(p_cur_buf);             /*     (if present)         */
    }

    return (p_return_buf);
}

/*******************************************************************************
**
** Function         l2cap_link_chk_pkt_end
**
** Description      This function is called from the HCI transport when the last
**                  byte of an HCI ACL packet has been received. It checks if the
**                  L2CAP message is complete, i.e. no more continuation packets
**                  are expected.
**
** Returns          TRUE if message complete, FALSE if continuation expected
**
*******************************************************************************/
BOOLEAN l2cap_link_chk_pkt_end (void)
{
    UINT8       *p;
    BT_HDR      *p_buf;
    UINT16      l2cap_len;
    tL2C_LCB    *p_lcb;

    /* If link or buffer pointer not set up, let main line handle it */
    if (((p_lcb = l2cb.p_cur_hcit_lcb) == NULL) || ((p_buf = p_lcb->p_hcit_rcv_acl) == NULL))
        return (TRUE);

    /* Point to the L2CAP length */
    p = (UINT8 *)(p_buf + 1) + p_buf->offset + HCI_DATA_PREAMBLE_SIZE;

    STREAM_TO_UINT16 (l2cap_len, p);

    /* If the L2CAP length has not been reached, tell HCIT not to send this buffer to BTU */
    if (l2cap_len > (p_buf->len - (HCI_DATA_PREAMBLE_SIZE + L2CAP_PKT_OVERHEAD)))
    {
        return (FALSE);
    }
    else
    {
        p_lcb->p_hcit_rcv_acl = NULL;
        return (TRUE);
    }
}


/*******************************************************************************
**
** Function         l2c_link_segments_xmitted
**
** Description      This function is called from the HCI Interface when an ACL
**                  data packet segment is transmitted.
**
** Returns          void
**
*******************************************************************************/
void l2c_link_segments_xmitted (BT_HDR *p_msg)
{
    UINT8       *p = (UINT8 *)(p_msg + 1) + p_msg->offset;
    UINT16      handle;
    tL2C_LCB    *p_lcb;

    /* Extract the handle */
    STREAM_TO_UINT16 (handle, p);
    handle   = HCID_GET_HANDLE (handle);

    /* Find the LCB based on the handle */
    if ((p_lcb = l2cu_find_lcb_by_handle (handle)) == NULL)
    {
        L2CAP_TRACE_WARNING1 ("L2CAP - rcvd segment complete, unknown handle: %d", handle);
        GKI_freebuf (p_msg);
        return;
    }

    if (p_lcb->link_state == LST_CONNECTED)
    {
        /* Enqueue the buffer to the head of the transmit queue, and see */
        /* if we can transmit anything more.                             */
        GKI_enqueue_head (&p_lcb->link_xmit_data_q, p_msg);

        p_lcb->partial_segment_being_sent = FALSE;

        l2c_link_check_send_pkts (p_lcb, NULL, NULL);
    }
    else
        GKI_freebuf (p_msg);
}
