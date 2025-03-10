/******************************************************************************
 *
 *  Copyright (C) 2008-2012 Broadcom Corporation
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
 *  this file contains the main ATT functions
 *
 ******************************************************************************/

#include "bt_target.h"

#if BLE_INCLUDED == TRUE

#include "gki.h"
#include "gatt_int.h"
#include "l2c_api.h"
#include "btm_int.h"
#include "btm_ble_int.h"

/* Configuration flags. */
#define GATT_L2C_CFG_IND_DONE   (1<<0)
#define GATT_L2C_CFG_CFM_DONE   (1<<1)

/********************************************************************************/
/*              L O C A L    F U N C T I O N     P R O T O T Y P E S            */
/********************************************************************************/
static void gatt_le_connect_cback (BD_ADDR bd_addr, BOOLEAN connected, UINT16 reason);
static void gatt_le_data_ind (BD_ADDR bd_addr, BT_HDR *p_buf);

static void gatt_l2cif_connect_ind_cback (BD_ADDR  bd_addr, UINT16 l2cap_cid, UINT16 psm, UINT8 l2cap_id);
static void gatt_l2cif_connect_cfm_cback (UINT16 l2cap_cid, UINT16 result);
static void gatt_l2cif_config_ind_cback (UINT16 l2cap_cid, tL2CAP_CFG_INFO *p_cfg);
static void gatt_l2cif_config_cfm_cback (UINT16 l2cap_cid, tL2CAP_CFG_INFO *p_cfg);
static void gatt_l2cif_disconnect_ind_cback (UINT16 l2cap_cid, BOOLEAN ack_needed);
static void gatt_l2cif_disconnect_cfm_cback (UINT16 l2cap_cid, UINT16 result);
static void gatt_l2cif_data_ind_cback (UINT16 l2cap_cid, BT_HDR *p_msg);
static void gatt_send_conn_cback (BOOLEAN is_bg_conn, tGATT_TCB *p_tcb);

static const tL2CAP_APPL_INFO dyn_info =
{
    gatt_l2cif_connect_ind_cback,
    gatt_l2cif_connect_cfm_cback,
    NULL,
    gatt_l2cif_config_ind_cback,
    gatt_l2cif_config_cfm_cback,
    gatt_l2cif_disconnect_ind_cback,
    gatt_l2cif_disconnect_cfm_cback,
    NULL,
    gatt_l2cif_data_ind_cback,
    NULL
} ;

#if GATT_DYNAMIC_MEMORY == FALSE
tGATT_CB  gatt_cb;
#endif

/*******************************************************************************
**
** Function         gatt_init
**
** Description      This function is enable the GATT profile on the device.
**                  It clears out the control blocks, and registers with L2CAP.
**
** Returns          void
**
*******************************************************************************/
void gatt_init (void)
{
    tL2CAP_FIXED_CHNL_REG  fixed_reg;

    GATT_TRACE_DEBUG0("gatt_init()");

    memset (&gatt_cb, 0, sizeof(tGATT_CB));

#if defined(GATT_INITIAL_TRACE_LEVEL)
    gatt_cb.trace_level = GATT_INITIAL_TRACE_LEVEL;
#else
    gatt_cb.trace_level = BT_TRACE_LEVEL_NONE;    /* No traces */
#endif
    gatt_cb.def_mtu_size = GATT_DEF_BLE_MTU_SIZE;
    GKI_init_q (&gatt_cb.sign_op_queue);
    /* First, register fixed L2CAP channel for ATT over BLE */
    fixed_reg.fixed_chnl_opts.mode         = L2CAP_FCR_BASIC_MODE;
    fixed_reg.fixed_chnl_opts.max_transmit = 0xFF;
    fixed_reg.fixed_chnl_opts.rtrans_tout  = 2000;
    fixed_reg.fixed_chnl_opts.mon_tout     = 12000;
    fixed_reg.fixed_chnl_opts.mps          = 670;
    fixed_reg.fixed_chnl_opts.tx_win_sz    = 1;

    fixed_reg.pL2CA_FixedConn_Cb = gatt_le_connect_cback;
    fixed_reg.pL2CA_FixedData_Cb = gatt_le_data_ind;
    fixed_reg.default_idle_tout  = 0xffff;                  /* 0xffff default idle timeout */

    L2CA_RegisterFixedChannel (L2CAP_ATT_CID, &fixed_reg);

    /* Now, register with L2CAP for ATT PSM over BR/EDR */
    if (!L2CA_Register (BT_PSM_ATT, (tL2CAP_APPL_INFO *) &dyn_info))
    {
        GATT_TRACE_ERROR0 ("ATT Dynamic Registration failed");
    }

    BTM_SetSecurityLevel(TRUE, "", BTM_SEC_SERVICE_ATT, BTM_SEC_NONE, BT_PSM_ATT, 0, 0);
    BTM_SetSecurityLevel(FALSE, "", BTM_SEC_SERVICE_ATT, BTM_SEC_NONE, BT_PSM_ATT, 0, 0);

    gatt_cb.hdl_cfg.gatt_start_hdl = GATT_GATT_START_HANDLE;
    gatt_cb.hdl_cfg.gap_start_hdl  = GATT_GAP_START_HANDLE;
    gatt_cb.hdl_cfg.app_start_hdl  = GATT_APP_START_HANDLE;
    gatt_profile_db_init();

}



/*******************************************************************************
**
** Function         gatt_connect
**
** Description      This function is called to initiate a connection to a peer device.
**
** Parameter        rem_bda: remote device address to connect to.
**
** Returns          TRUE if connection is started, otherwise return FALSE.
**
*******************************************************************************/
BOOLEAN gatt_connect (BD_ADDR rem_bda, tGATT_TCB *p_tcb)
{
    BOOLEAN             gatt_ret = TRUE;
    tBT_DEVICE_TYPE     dev_type;
    tBLE_ADDR_TYPE      addr_type;

    BTM_ReadDevInfo(rem_bda, &dev_type, &addr_type);

    gatt_set_ch_state(p_tcb, GATT_CH_CONN);

    if (dev_type == BT_DEVICE_TYPE_BLE)
    {
        p_tcb->att_lcid = L2CAP_ATT_CID;
        gatt_ret = L2CA_ConnectFixedChnl (L2CAP_ATT_CID, rem_bda);
    }
    else
    {
        if ((p_tcb->att_lcid = L2CA_ConnectReq(BT_PSM_ATT, rem_bda)) == 0)
            gatt_ret = FALSE;
    }

    return gatt_ret;
}

/*******************************************************************************
**
** Function         gatt_disconnect
**
** Description      This function is called to disconnect to an ATT device.
**
** Parameter        rem_bda: remote device address to disconnect from.
**
** Returns          TRUE: if connection found and to be disconnected; otherwise
**                  return FALSE.
**
*******************************************************************************/
BOOLEAN gatt_disconnect (BD_ADDR rem_bda)
{
    tGATT_TCB           *p_tcb = gatt_find_tcb_by_addr(rem_bda);
    BOOLEAN             ret = FALSE;
    tGATT_CH_STATE      ch_state;
    GATT_TRACE_DEBUG0 ("gatt_disconnect ");

    if (p_tcb != NULL)
    {
        ret = TRUE;
        if ( (ch_state = gatt_get_ch_state(p_tcb)) != GATT_CH_CLOSING )
        {
            if (p_tcb->att_lcid == L2CAP_ATT_CID)
            {
                if (ch_state == GATT_CH_OPEN)
                    /* only LCB exist between remote device and local */
                    ret = L2CA_RemoveFixedChnl (L2CAP_ATT_CID, rem_bda);
                else
                {
                    gatt_set_ch_state(p_tcb, GATT_CH_CLOSING);
                    ret = L2CA_CancelBleConnectReq (rem_bda);
                }
            }
            else
            {
                ret = L2CA_DisconnectReq(p_tcb->att_lcid);
            }
        }
        else
        {
            GATT_TRACE_DEBUG0 ("gatt_disconnect already in closing state");
        }
    }

    return ret;
}

/*******************************************************************************
**
** Function         gatt_update_app_hold_link_status
**
** Description      Update the application use link status
**
** Returns          void.
**
*******************************************************************************/
void gatt_update_app_hold_link_status (tGATT_IF gatt_if, tGATT_TCB *p_tcb, BOOLEAN is_add)
{
    UINT8 i;
    BOOLEAN found=FALSE;

    if (p_tcb == NULL)
    {
        GATT_TRACE_ERROR0("gatt_update_app_hold_link_status p_tcb=NULL");
        return;
    }


    for (i=0; i<GATT_MAX_APPS; i++)
    {
        if (p_tcb->app_hold_link[i] ==  gatt_if)
        {
            found = TRUE;
            if (!is_add)
            {
                p_tcb->app_hold_link[i] = 0;
                break;
            }
        }
    }

    if (!found && is_add)
    {
        for (i=0; i<GATT_MAX_APPS; i++)
        {
            if (p_tcb->app_hold_link[i] ==  0)
            {
                p_tcb->app_hold_link[i] = gatt_if;
                found = TRUE;
                break;
            }
        }
    }

    GATT_TRACE_DEBUG4("gatt_update_app_hold_link_status found=%d[1-found] idx=%d gatt_if=%d is_add=%d", found, i, gatt_if, is_add);

}

/*******************************************************************************
**
** Function         gatt_update_app_use_link_flag
**
** Description      Update the application use link flag and optional to check the acl link
**                  if the link is up then set the idle time out accordingly
**
** Returns          void.
**
*******************************************************************************/
void gatt_update_app_use_link_flag (tGATT_IF gatt_if, tGATT_TCB *p_tcb, BOOLEAN is_add, BOOLEAN check_acl_link)
{
    GATT_TRACE_DEBUG2("gatt_update_app_use_link_flag  is_add=%d chk_link=%d",
                      is_add, check_acl_link);

    gatt_update_app_hold_link_status(gatt_if, p_tcb, is_add);

    if (check_acl_link &&
        p_tcb &&
        (BTM_GetHCIConnHandle(p_tcb->peer_bda) != GATT_INVALID_ACL_HANDLE))
    {
        if (is_add)
        {
            GATT_TRACE_DEBUG0("GATT disables link idle timer");
            /* acl link is connected disable the idle timeout */
            GATT_SetIdleTimeout(p_tcb->peer_bda, GATT_LINK_NO_IDLE_TIMEOUT);
        }
        else
        {
            if (!gatt_num_apps_hold_link(p_tcb))
            {
                /* acl link is connected but no application needs to use the link
                   so set the timeout value to GATT_LINK_IDLE_TIMEOUT_WHEN_NO_APP seconds */
                GATT_TRACE_DEBUG1("GATT starts link idle timer =%d sec", GATT_LINK_IDLE_TIMEOUT_WHEN_NO_APP);
                GATT_SetIdleTimeout(p_tcb->peer_bda, GATT_LINK_IDLE_TIMEOUT_WHEN_NO_APP);
            }

        }
    }
}

/*******************************************************************************
**
** Function         gatt_act_connect
**
** Description      GATT connection initiation.
**
** Returns          void.
**
*******************************************************************************/
BOOLEAN gatt_act_connect (tGATT_REG *p_reg, BD_ADDR bd_addr)
{
    BOOLEAN     ret = FALSE;
    tGATT_TCB   *p_tcb;

    GATT_TRACE_DEBUG0("gatt_act_connect");

    if ((p_tcb = gatt_find_tcb_by_addr(bd_addr)) != NULL)
    {
        ret = TRUE;
        if(gatt_get_ch_state(p_tcb) == GATT_CH_CLOSING )
        {
            /* need to complete the closing first */
            ret = FALSE;
        }
    }
    else
    {
        if ((p_tcb = gatt_allocate_tcb_by_bdaddr(bd_addr)) != NULL)
        {
            if (!gatt_connect(bd_addr,  p_tcb))
            {
                GATT_TRACE_ERROR0("gatt_connect failed");
                memset(p_tcb, 0, sizeof(tGATT_TCB));
            }
            else
                ret = TRUE;
        }
        else
        {
            ret = 0;
            GATT_TRACE_ERROR1("Max TCB for gatt_if [%d] reached.", p_reg->gatt_if);
        }
    }

    if (ret)
    {
        gatt_update_app_use_link_flag(p_reg->gatt_if, p_tcb, TRUE, FALSE);
    }

    return ret;
}

/*******************************************************************************
**
** Function         gatt_le_connect_cback
**
** Description      This callback function is called by L2CAP to indicate that
**                  the ATT fixed channel for LE is
**                      connected (conn = TRUE)/disconnected (conn = FALSE).
**
*******************************************************************************/
static void gatt_le_connect_cback (BD_ADDR bd_addr, BOOLEAN connected, UINT16 reason)
{

    tGATT_TCB       *p_tcb = gatt_find_tcb_by_addr(bd_addr);

    BOOLEAN                 check_srv_chg = FALSE;
    tGATTS_SRV_CHG          *p_srv_chg_clt=NULL;
    BOOLEAN                 is_bg_conn = FALSE;


    GATT_TRACE_DEBUG3 ("GATT   ATT protocol channel with BDA: %08x%04x is %s",
                       (bd_addr[0]<<24)+(bd_addr[1]<<16)+(bd_addr[2]<<8)+bd_addr[3],
                       (bd_addr[4]<<8)+bd_addr[5], (connected) ? "connected" : "disconnected");


    if ((p_srv_chg_clt = gatt_is_bda_in_the_srv_chg_clt_list(bd_addr)) != NULL)
    {
        check_srv_chg = TRUE;
    }
    else
    {
        if (btm_sec_is_a_bonded_dev(bd_addr))
            gatt_add_a_bonded_dev_for_srv_chg(bd_addr);
    }

    if (connected)
    {
        GATT_TRACE_DEBUG1("connected is TRUE reason=%d",reason );
        /* BR/EDR lik, ignore this callback */
        if (reason == 0)
            return;

        /* do we have a channel initiating a connection? */
        if (p_tcb)
        {
            if (check_srv_chg)
                gatt_chk_srv_chg (p_srv_chg_clt);
            /* we are initiating connection */
            if ( gatt_get_ch_state(p_tcb) == GATT_CH_CONN)
            {
                /* send callback */
                gatt_set_ch_state(p_tcb, GATT_CH_OPEN);
                p_tcb->payload_size = GATT_DEF_BLE_MTU_SIZE;

                gatt_send_conn_cback(FALSE, p_tcb);
            }
            else /* there was an exisiting link, ignore the callback */
            {
                GATT_TRACE_ERROR0("connection already up, ignore it");
                return;
            }
        }
        /* this is incoming connection or background connection callback */
        else
        {
            if ((p_tcb = gatt_allocate_tcb_by_bdaddr(bd_addr)) != NULL)
            {
                p_tcb->att_lcid = L2CAP_ATT_CID;

                gatt_set_ch_state(p_tcb, GATT_CH_OPEN);

                p_tcb->payload_size = GATT_DEF_BLE_MTU_SIZE;
                if (L2CA_GetBleConnRole(p_tcb->peer_bda)== HCI_ROLE_MASTER)
                {
                    is_bg_conn = TRUE;
                }
                gatt_send_conn_cback (is_bg_conn, p_tcb);
                if (check_srv_chg)
                {
                    gatt_chk_srv_chg (p_srv_chg_clt);
                }
            }
            else
            {
                GATT_TRACE_ERROR0("CCB max out, no rsources");
            }
        }
    }
    else
    {
        gatt_cleanup_upon_disc(bd_addr, reason);
        GATT_TRACE_DEBUG0 ("ATT disconnected");
    }
}

/*******************************************************************************
**
** Function         gatt_le_data_ind
**
** Description      This function is called when data is received from L2CAP.
**                  if we are the originator of the connection, we are the ATT
**                  client, and the received message is queued up for the client.
**
**                  If we are the destination of the connection, we are the ATT
**                  server, so the message is passed to the server processing
**                  function.
**
** Returns          void
**
*******************************************************************************/
static void gatt_le_data_ind (BD_ADDR bd_addr, BT_HDR *p_buf)
{
    tGATT_TCB    *p_tcb;

    /* Find CCB based on bd addr */
    if ((p_tcb = gatt_find_tcb_by_addr (bd_addr)) != NULL &&
        gatt_get_ch_state(p_tcb) >= GATT_CH_OPEN)
    {
        gatt_data_process(p_tcb, p_buf);
    }
    else
    {
        GKI_freebuf (p_buf);

        if (p_tcb != NULL)
        {
            GATT_TRACE_WARNING1 ("ATT - Ignored L2CAP data while in state: %d",
                                 gatt_get_ch_state(p_tcb));
        }
    }
}

/*******************************************************************************
**
** Function         gatt_l2cif_connect_ind
**
** Description      This function handles an inbound connection indication
**                  from L2CAP. This is the case where we are acting as a
**                  server.
**
** Returns          void
**
*******************************************************************************/
static void gatt_l2cif_connect_ind_cback (BD_ADDR  bd_addr, UINT16 lcid, UINT16 psm, UINT8 id)
{
    /* do we already have a control channel for this peer? */
    UINT8       result = L2CAP_CONN_OK;
    tL2CAP_CFG_INFO cfg;
    tGATT_TCB       *p_tcb = gatt_find_tcb_by_addr(bd_addr);

    GATT_TRACE_ERROR1("Connection indication cid = %d", lcid);
    /* new connection ? */
    if (p_tcb == NULL)
    {
        /* allocate tcb */
        if ((p_tcb = gatt_allocate_tcb_by_bdaddr(bd_addr)) == NULL)
        {
            /* no tcb available, reject L2CAP connection */
            result = L2CAP_CONN_NO_RESOURCES;
        }
        else
            p_tcb->att_lcid = lcid;

    }
    else /* existing connection , reject it */
    {
        result = L2CAP_CONN_NO_RESOURCES;
    }

    /* Send L2CAP connect rsp */
    L2CA_ConnectRsp(bd_addr, id, lcid, result, 0);

    /* if result ok, proceed with connection */
    if (result == L2CAP_CONN_OK)
    {
        /* transition to configuration state */
        gatt_set_ch_state(p_tcb, GATT_CH_CFG);

        /* Send L2CAP config req */
        memset(&cfg, 0, sizeof(tL2CAP_CFG_INFO));
        cfg.mtu_present = TRUE;
        cfg.mtu = GATT_MAX_MTU_SIZE;

        L2CA_ConfigReq(lcid, &cfg);
    }
}

/*******************************************************************************
**
** Function         gatt_l2c_connect_cfm_cback
**
** Description      This is the L2CAP connect confirm callback function.
**
**
** Returns          void
**
*******************************************************************************/
void gatt_l2cif_connect_cfm_cback(UINT16 lcid, UINT16 result)
{
    tGATT_TCB       *p_tcb;
    tL2CAP_CFG_INFO cfg;

    /* look up clcb for this channel */
    if ((p_tcb = gatt_find_tcb_by_cid(lcid)) != NULL)
    {
        GATT_TRACE_DEBUG3("gatt_l2c_connect_cfm_cback result: %d ch_state: %d, lcid:0x%x", result, gatt_get_ch_state(p_tcb), p_tcb->att_lcid);

        /* if in correct state */
        if (gatt_get_ch_state(p_tcb) == GATT_CH_CONN)
        {
            /* if result successful */
            if (result == L2CAP_CONN_OK)
            {
                /* set channel state */
                gatt_set_ch_state(p_tcb, GATT_CH_CFG);

                /* Send L2CAP config req */
                memset(&cfg, 0, sizeof(tL2CAP_CFG_INFO));
                cfg.mtu_present = TRUE;
                cfg.mtu = GATT_MAX_MTU_SIZE;
                L2CA_ConfigReq(lcid, &cfg);
            }
            /* else initiating connection failure */
            else
            {
                gatt_cleanup_upon_disc(p_tcb->peer_bda, result);
            }
        }
        else /* wrong state, disconnect it */
        {
            if (result == L2CAP_CONN_OK)
            {
                /* just in case the peer also accepts our connection - Send L2CAP disconnect req */
                L2CA_DisconnectReq(lcid);
            }
        }
    }
}

/*******************************************************************************
**
** Function         gatt_l2cif_config_cfm_cback
**
** Description      This is the L2CAP config confirm callback function.
**
**
** Returns          void
**
*******************************************************************************/
void gatt_l2cif_config_cfm_cback(UINT16 lcid, tL2CAP_CFG_INFO *p_cfg)
{
    tGATT_TCB       *p_tcb;
    tGATTS_SRV_CHG  *p_srv_chg_clt=NULL;

    /* look up clcb for this channel */
    if ((p_tcb = gatt_find_tcb_by_cid(lcid)) != NULL)
    {
        /* if in correct state */
        if ( gatt_get_ch_state(p_tcb) == GATT_CH_CFG)
        {
            /* if result successful */
            if (p_cfg->result == L2CAP_CFG_OK)
            {
                /* update flags */
                p_tcb->ch_flags |= GATT_L2C_CFG_CFM_DONE;

                /* if configuration complete */
                if (p_tcb->ch_flags & GATT_L2C_CFG_IND_DONE)
                {
                    gatt_set_ch_state(p_tcb, GATT_CH_OPEN);

                    if ((p_srv_chg_clt = gatt_is_bda_in_the_srv_chg_clt_list(p_tcb->peer_bda)) != NULL)
                    {
                        gatt_chk_srv_chg(p_srv_chg_clt);
                    }
                    else
                    {
                        if (btm_sec_is_a_bonded_dev(p_tcb->peer_bda))
                            gatt_add_a_bonded_dev_for_srv_chg(p_tcb->peer_bda);
                    }

                    /* send callback */
                    gatt_send_conn_cback(FALSE, p_tcb);
                }
            }
            /* else failure */
            else
            {
                /* Send L2CAP disconnect req */
                L2CA_DisconnectReq(lcid);
            }
        }
    }
}

/*******************************************************************************
**
** Function         gatt_l2cif_config_ind_cback
**
** Description      This is the L2CAP config indication callback function.
**
**
** Returns          void
**
*******************************************************************************/
void gatt_l2cif_config_ind_cback(UINT16 lcid, tL2CAP_CFG_INFO *p_cfg)
{
    tGATT_TCB       *p_tcb;
    tGATTS_SRV_CHG  *p_srv_chg_clt=NULL;
    /* look up clcb for this channel */
    if ((p_tcb = gatt_find_tcb_by_cid(lcid)) != NULL)
    {
        /* GATT uses the smaller of our MTU and peer's MTU  */
        if ( (p_cfg->mtu_present) && (p_cfg->mtu < L2CAP_DEFAULT_MTU) )
            p_tcb->payload_size = p_cfg->mtu;
        else
            p_tcb->payload_size = L2CAP_DEFAULT_MTU;

        /* send L2CAP configure response */
        memset(p_cfg, 0, sizeof(tL2CAP_CFG_INFO));
        p_cfg->result = L2CAP_CFG_OK;
        L2CA_ConfigRsp(lcid, p_cfg);

        /* if first config ind */
        if ((p_tcb->ch_flags & GATT_L2C_CFG_IND_DONE) == 0)
        {
            /* update flags */
            p_tcb->ch_flags |= GATT_L2C_CFG_IND_DONE;

            /* if configuration complete */
            if (p_tcb->ch_flags & GATT_L2C_CFG_CFM_DONE)
            {
                gatt_set_ch_state(p_tcb, GATT_CH_OPEN);
                if ((p_srv_chg_clt = gatt_is_bda_in_the_srv_chg_clt_list(p_tcb->peer_bda)) != NULL)
                {
                    gatt_chk_srv_chg(p_srv_chg_clt);
                }
                else
                {
                    if (btm_sec_is_a_bonded_dev(p_tcb->peer_bda))
                        gatt_add_a_bonded_dev_for_srv_chg(p_tcb->peer_bda);
                }

                /* send callback */
                gatt_send_conn_cback(FALSE, p_tcb);
            }
        }
    }
}

/*******************************************************************************
**
** Function         gatt_l2cif_disconnect_ind_cback
**
** Description      This is the L2CAP disconnect indication callback function.
**
**
** Returns          void
**
*******************************************************************************/
void gatt_l2cif_disconnect_ind_cback(UINT16 lcid, BOOLEAN ack_needed)
{
    tGATT_TCB       *p_tcb;
    UINT16          reason;

    /* look up clcb for this channel */
    if ((p_tcb = gatt_find_tcb_by_cid(lcid)) != NULL)
    {
        if (ack_needed)
        {
            /* send L2CAP disconnect response */
            L2CA_DisconnectRsp(lcid);
        }
        if (btm_sec_is_a_bonded_dev(p_tcb->peer_bda))
            gatt_add_a_bonded_dev_for_srv_chg(p_tcb->peer_bda);
        /* if ACL link is still up, no reason is logged, l2cap is disconnect from peer */
        if ((reason = L2CA_GetDisconnectReason(p_tcb->peer_bda)) == 0)
            reason = GATT_CONN_TERMINATE_PEER_USER;

        /* send disconnect callback */
        gatt_cleanup_upon_disc(p_tcb->peer_bda, reason);
    }
}

/*******************************************************************************
**
** Function         gatt_l2cif_disconnect_cfm_cback
**
** Description      This is the L2CAP disconnect confirm callback function.
**
**
** Returns          void
**
*******************************************************************************/
void gatt_l2cif_disconnect_cfm_cback(UINT16 lcid, UINT16 result)
{
    tGATT_TCB       *p_tcb;
    UINT16          reason;

    /* look up clcb for this channel */
    if ((p_tcb = gatt_find_tcb_by_cid(lcid)) != NULL)
    {
        if (btm_sec_is_a_bonded_dev(p_tcb->peer_bda))
            gatt_add_a_bonded_dev_for_srv_chg(p_tcb->peer_bda);
        /* send disconnect callback */
        /* if ACL link is still up, no reason is logged, l2cap is disconnect from peer */
        if ((reason = L2CA_GetDisconnectReason(p_tcb->peer_bda)) == 0)
            reason = GATT_CONN_TERMINATE_LOCAL_HOST;

        gatt_cleanup_upon_disc(p_tcb->peer_bda, reason);
    }
}

/*******************************************************************************
**
** Function         gatt_l2cif_data_ind_cback
**
** Description      This is the L2CAP data indication callback function.
**
**
** Returns          void
**
*******************************************************************************/
void gatt_l2cif_data_ind_cback(UINT16 lcid, BT_HDR *p_buf)
{
    tGATT_TCB       *p_tcb;

    /* look up clcb for this channel */
    if ((p_tcb = gatt_find_tcb_by_cid(lcid)) != NULL &&
        gatt_get_ch_state(p_tcb) == GATT_CH_OPEN)
    {
        /* process the data */
        gatt_data_process(p_tcb, p_buf);
    }
    else /* prevent buffer leak */
        GKI_freebuf(p_buf);
}

/*******************************************************************************
**
** Function         gatt_send_conn_cback
**
** Description      Callback used to notify layer above about a connection.
**
**
** Returns          void
**
*******************************************************************************/
static void gatt_send_conn_cback(BOOLEAN is_bg_conn, tGATT_TCB *p_tcb)
{
    UINT8               i;
    tGATT_REG           *p_reg;
    tGATT_BG_CONN_DEV   *p_bg_dev=NULL;
    UINT16              conn_id;

    if (is_bg_conn)
        p_bg_dev = gatt_find_bg_dev(p_tcb->peer_bda);

    /* notifying all applications for the connection up event */
    for (i = 0,  p_reg = gatt_cb.cl_rcb ; i < GATT_MAX_APPS; i++, p_reg++)
    {
        if (p_reg->in_use)
        {
            if (p_bg_dev && gatt_is_bg_dev_for_app(p_bg_dev, p_reg->gatt_if))
                gatt_update_app_use_link_flag(p_reg->gatt_if, p_tcb, TRUE, TRUE);

            if (p_reg->app_cb.p_conn_cb)
            {
                conn_id = GATT_CREATE_CONN_ID(p_tcb->tcb_idx, p_reg->gatt_if);
                (*p_reg->app_cb.p_conn_cb)(p_reg->gatt_if, p_tcb->peer_bda, conn_id, TRUE, 0);
            }
        }
    }


    if (gatt_num_apps_hold_link(p_tcb))
    {
        /* disable idle timeout if one or more clients are holding the link disable the idle timer */
        GATT_SetIdleTimeout(p_tcb->peer_bda, GATT_LINK_NO_IDLE_TIMEOUT);
    }
}

/*******************************************************************************
**
** Function         gatt_le_data_ind
**
** Description      This function is called when data is received from L2CAP.
**                  if we are the originator of the connection, we are the ATT
**                  client, and the received message is queued up for the client.
**
**                  If we are the destination of the connection, we are the ATT
**                  server, so the message is passed to the server processing
**                  function.
**
** Returns          void
**
*******************************************************************************/
void gatt_data_process (tGATT_TCB *p_tcb, BT_HDR *p_buf)
{
    UINT8   *p = (UINT8 *)(p_buf + 1) + p_buf->offset;
    UINT8   op_code, pseudo_op_code;
    UINT16  msg_len;


    if (p_buf->len > 0)
    {
        msg_len = p_buf->len - 1;
        STREAM_TO_UINT8(op_code, p);

        /* remove the two MSBs associated with sign write and write cmd */
        pseudo_op_code = op_code & (~GATT_WRITE_CMD_MASK);

        if (pseudo_op_code < GATT_OP_CODE_MAX)
        {
            if (op_code == GATT_SIGN_CMD_WRITE)
            {
                gatt_verify_signature(p_tcb, p_buf);
                return;
            }
            else
            {
                /* message from client */
                if ((op_code % 2) == 0)
                    gatt_server_handle_client_req (p_tcb, op_code, msg_len, p);
                else
                    gatt_client_handle_server_rsp (p_tcb, op_code, msg_len, p);
            }
        }
        else
        {
            GATT_TRACE_ERROR1 ("ATT - Rcvd L2CAP data, unknown cmd: 0x%x", op_code);
        }
    }
    else
    {
        GATT_TRACE_ERROR0 ("invalid data length, ignore");
    }

    GKI_freebuf (p_buf);
}

/*******************************************************************************
**
** Function         gatt_add_a_bonded_dev_for_srv_chg
**
** Description      Add a bonded dev to the service changed client list
**
** Returns          void
**
*******************************************************************************/
void gatt_add_a_bonded_dev_for_srv_chg (BD_ADDR bda)
{
    tGATTS_SRV_CHG *p_buf;
    tGATTS_SRV_CHG_REQ req;
    tGATTS_SRV_CHG srv_chg_clt;

    memcpy(srv_chg_clt.bda, bda, BD_ADDR_LEN);
    srv_chg_clt.srv_changed = FALSE;
    if ((p_buf = gatt_add_srv_chg_clt(&srv_chg_clt)) != NULL)
    {
        memcpy(req.srv_chg.bda, bda, BD_ADDR_LEN);
        req.srv_chg.srv_changed = FALSE;
        if (gatt_cb.cb_info.p_srv_chg_callback)
            (*gatt_cb.cb_info.p_srv_chg_callback)(GATTS_SRV_CHG_CMD_ADD_CLIENT, &req, NULL);
    }

}

/*******************************************************************************
**
** Function         gatt_send_srv_chg_ind
**
** Description      This function is called to send a service chnaged indication to
**                  the specified bd address
**
** Returns          void
**
*******************************************************************************/
void gatt_send_srv_chg_ind (BD_ADDR peer_bda)
{
    UINT8   handle_range[GATT_SIZE_OF_SRV_CHG_HNDL_RANGE];
    UINT8   *p = handle_range;
    UINT16  conn_id;

    GATT_TRACE_DEBUG0("gatt_send_srv_chg_ind");

    if (gatt_cb.handle_of_h_r)
    {
        if ((conn_id = gatt_profile_find_conn_id_by_bd_addr(peer_bda)) != GATT_INVALID_CONN_ID)
        {
            UINT16_TO_STREAM (p, 1);
            UINT16_TO_STREAM (p, 0xFFFF);
            GATTS_HandleValueIndication (conn_id,
                                         gatt_cb.handle_of_h_r,
                                         GATT_SIZE_OF_SRV_CHG_HNDL_RANGE,
                                         handle_range);
        }
        else
        {
            GATT_TRACE_ERROR2("Unable to find conn_id for  %08x%04x ",
                              (peer_bda[0]<<24)+(peer_bda[1]<<16)+(peer_bda[2]<<8)+peer_bda[3],
                              (peer_bda[4]<<8)+peer_bda[5] );
        }
    }
}

/*******************************************************************************
**
** Function         gatt_chk_srv_chg
**
** Description      Check sending service chnaged Indication is required or not
**                  if required then send the Indication
**
** Returns          void
**
*******************************************************************************/
void gatt_chk_srv_chg(tGATTS_SRV_CHG *p_srv_chg_clt)
{
    GATT_TRACE_DEBUG1("gatt_chk_srv_chg srv_changed=%d", p_srv_chg_clt->srv_changed );

    if (p_srv_chg_clt->srv_changed)
    {
        gatt_send_srv_chg_ind(p_srv_chg_clt->bda);
    }
    else
    {
        GATT_TRACE_DEBUG0("No need to send srv chg ");
    }

}

/*******************************************************************************
**
** Function         gatt_init_srv_chg
**
** Description      This function is used to initialize the service changed
**                  attribute value
**
** Returns          void
**
*******************************************************************************/
void gatt_init_srv_chg (void)
{
    tGATTS_SRV_CHG_REQ req;
    tGATTS_SRV_CHG_RSP rsp;
    BOOLEAN status;
    UINT8 num_clients,i;
    tGATTS_SRV_CHG  srv_chg_clt;

    GATT_TRACE_DEBUG0("gatt_init_srv_chg");
    if (gatt_cb.cb_info.p_srv_chg_callback)
    {
        status = (*gatt_cb.cb_info.p_srv_chg_callback)(GATTS_SRV_CHG_CMD_READ_NUM_CLENTS, NULL, &rsp);

        if (status && rsp.num_clients)
        {
            GATT_TRACE_DEBUG1("gatt_init_srv_chg num_srv_chg_clt_clients=%d", rsp.num_clients);
            num_clients = rsp.num_clients;
            i = 1; /* use one based index */
            while ((i <= num_clients) && status)
            {
                req.client_read_index = i;
                if ((status = (*gatt_cb.cb_info.p_srv_chg_callback)(GATTS_SRV_CHG_CMD_READ_CLENT, &req, &rsp)))
                {
                    memcpy(&srv_chg_clt, &rsp.srv_chg ,sizeof(tGATTS_SRV_CHG));
                    if (gatt_add_srv_chg_clt(&srv_chg_clt) == NULL)
                    {
                        GATT_TRACE_ERROR0("Unable to add a service change client");
                        status = FALSE;
                    }
                }
                i++;
            }
        }
    }
    else
    {
        GATT_TRACE_DEBUG0("gatt_init_srv_chg callback not registered yet");
    }
}

/*******************************************************************************
**
** Function         gatt_proc_srv_chg
**
** Description      This function is process the service changed request
**
** Returns          void
**
*******************************************************************************/
void gatt_proc_srv_chg (void)
{
    UINT8               start_idx, found_idx;
    BD_ADDR             bda;
    BOOLEAN             srv_chg_ind_pending=FALSE;
    tGATT_TCB           *p_tcb;

    GATT_TRACE_DEBUG0 ("gatt_proc_srv_chg");

    if (gatt_cb.cb_info.p_srv_chg_callback && gatt_cb.handle_of_h_r)
    {
        gatt_set_srv_chg();
        start_idx =0;
        while (gatt_find_the_connected_bda(start_idx, bda, &found_idx))
        {
            p_tcb = &gatt_cb.tcb[found_idx];;
            srv_chg_ind_pending  = gatt_is_srv_chg_ind_pending(p_tcb);

            if (!srv_chg_ind_pending)
            {
                gatt_send_srv_chg_ind(bda);
            }
            else
            {
                GATT_TRACE_DEBUG0 ("discard srv chg - already has one in the queue");
            }
            start_idx = ++found_idx;
        }
    }
}

/*******************************************************************************
**
** Function         gatt_set_ch_state
**
** Description      This function set the ch_state in tcb
**
** Returns          none
**
*******************************************************************************/
void gatt_set_ch_state(tGATT_TCB *p_tcb, tGATT_CH_STATE ch_state)
{
    if (p_tcb)
    {
        GATT_TRACE_DEBUG2 ("gatt_set_ch_state: old=%d new=%d", p_tcb->ch_state, ch_state);
        p_tcb->ch_state = ch_state;
    }
}

/*******************************************************************************
**
** Function         gatt_get_ch_state
**
** Description      This function get the ch_state in tcb
**
** Returns          none
**
*******************************************************************************/
tGATT_CH_STATE gatt_get_ch_state(tGATT_TCB *p_tcb)
{
    tGATT_CH_STATE ch_state = GATT_CH_CLOSE;
    if (p_tcb)
    {
        GATT_TRACE_DEBUG1 ("gatt_get_ch_state: ch_state=%d", p_tcb->ch_state);
        ch_state = p_tcb->ch_state;
    }
    return ch_state;
}

#endif /* BLE_INCLUDED */
