/******************************************************************************
 *
 *  Copyright (C) 2003-2012 Broadcom Corporation
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
 *  This file contains the GATT client action functions for the state
 *  machine.
 *
 ******************************************************************************/

#include "bt_target.h"

#if defined(BTA_GATT_INCLUDED) && (BTA_GATT_INCLUDED == TRUE)


#include "utl.h"
#include "gki.h"
#include "bd.h"
#include "bta_sys.h"

#include "bta_gattc_int.h"
#include "l2c_api.h"


#include <string.h>

/*****************************************************************************
**  Constants
*****************************************************************************/
static void bta_gattc_conn_cback(tGATT_IF gattc_if, BD_ADDR bda, UINT16 conn_id,
                                 BOOLEAN connected, tGATT_DISCONN_REASON reason);

static void  bta_gattc_cmpl_cback(UINT16 conn_id, tGATTC_OPTYPE op, tGATT_STATUS status,
                                  tGATT_CL_COMPLETE *p_data);

static tGATT_CBACK bta_gattc_cl_cback =
{
    bta_gattc_conn_cback,
    bta_gattc_cmpl_cback,
    bta_gattc_disc_res_cback,
    bta_gattc_disc_cmpl_cback,
    NULL
};

/* opcode(tGATTC_OPTYPE) order has to be comply with internal event order */
static UINT16 bta_gattc_opcode_to_int_evt[] =
{
    BTA_GATTC_API_READ_EVT,
    BTA_GATTC_API_WRITE_EVT,
    BTA_GATTC_API_EXEC_EVT
};

#if (BT_TRACE_VERBOSE == TRUE)
static const char *bta_gattc_op_code_name[] =
{
    "Unknown",
    "Discovery",
    "Read",
    "Write",
    "Exec",
    "Config",
    "Notification",
    "Indication"
};
#endif
/*****************************************************************************
**  Action Functions
*****************************************************************************/

/*******************************************************************************
**
** Function         bta_gattc_register
**
** Description      Register a GATT client application with BTA.
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_register(tBTA_GATTC_CB *p_cb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATTC               cb_data;
    UINT8                    i;
    tBT_UUID                 *p_app_uuid = &p_data->api_reg.app_uuid;
    tBTA_GATTC_INT_START_IF  *p_buf;


    /* todo need to check duplicate uuid */
    for (i = 0; i < BTA_GATTC_CL_MAX; i ++)
    {
        if (!p_cb->cl_rcb[i].in_use)
        {
            if ((p_app_uuid == NULL) || (p_cb->cl_rcb[i].client_if = GATT_Register(p_app_uuid, &bta_gattc_cl_cback)) == 0)
            {
                APPL_TRACE_ERROR0("Register with GATT stack failed.");
                cb_data.reg_oper.status = BTA_GATT_ERROR;
            }
            else

            {
                p_cb->cl_rcb[i].in_use = TRUE;
                p_cb->cl_rcb[i].p_cback = p_data->api_reg.p_cback;
                memcpy(&p_cb->cl_rcb[i].app_uuid, p_app_uuid, sizeof(tBT_UUID));

                /* BTA use the same client interface as BTE GATT statck */
                cb_data.reg_oper.client_if = p_cb->cl_rcb[i].client_if;
// btla-specific ++
                memcpy(&(cb_data.reg_oper.app_uuid),p_app_uuid,sizeof(tBT_UUID));
// btla-specific --

                cb_data.reg_oper.status = BTA_GATT_OK;

                if ((p_buf = (tBTA_GATTC_INT_START_IF *) GKI_getbuf(sizeof(tBTA_GATTC_INT_START_IF))) != NULL)
                {
                    p_buf->hdr.event    = BTA_GATTC_INT_START_IF_EVT;
                    p_buf->client_if    = p_cb->cl_rcb[i].client_if;

                    bta_sys_sendmsg(p_buf);
                }
                else
                {
                    cb_data.reg_oper.status = BTA_GATT_NO_RESOURCES;
                    memset( &p_cb->cl_rcb[i], 0 , sizeof(tBTA_GATTC_RCB));
                }
                break;
            }
        }
    }
    /* callback with register event */
    if (p_data->api_reg.p_cback)
    {
        (*p_data->api_reg.p_cback)(BTA_GATTC_REG_EVT,  (tBTA_GATTC *)&cb_data);
    }
}

/*******************************************************************************
**
** Function         bta_gattc_start_if
**
** Description      start an application interface.
**
** Returns          none.
**
*******************************************************************************/
void bta_gattc_start_if(tBTA_GATTC_CB *p_cb, tBTA_GATTC_DATA *p_msg)
{
    if (bta_gattc_cl_get_regcb(p_msg->int_start_if.client_if) !=NULL )
    {
        GATT_StartIf(p_msg->int_start_if.client_if);
    }
    else
    {
        APPL_TRACE_ERROR1("Unable to start app.: Unknown interface =%d",p_msg->int_start_if.client_if );
    }
}


/*******************************************************************************
**
** Function         bta_gattc_deregister_cmpl
**
** Description      De-Register a GATT client application with BTA completed.
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_int_deregister_cmpl(tBTA_GATTC_RCB *p_clreg, tBTA_GATTC_IF client_if)
{
    tBTA_GATTC_CBACK    *p_cback = p_clreg->p_cback;
    tBTA_GATTC          cb_data;


    APPL_TRACE_DEBUG1("bta_gattc_int_deregister_cmpl client_if=%d", client_if );

    GATT_Deregister(p_clreg->client_if);
    memset(p_clreg, 0, sizeof(tBTA_GATTC_RCB));

    cb_data.reg_oper.client_if = client_if;
    cb_data.reg_oper.status    = BTA_GATT_OK;

    if (p_cback)
        /* callback with de-register event */
        (*p_cback)(BTA_GATTC_DEREG_EVT,  (tBTA_GATTC *)&cb_data);
}


/*******************************************************************************
**
** Function         bta_gattc_deregister_cmpl
**
** Description      De-Register a GATT client application with BTA completed.
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_deregister_cmpl(tBTA_GATTC_RCB *p_clreg, tBTA_GATTC_IF client_if)
{
    tBTA_GATTC_INT_DEREG  *p_buf;

    APPL_TRACE_DEBUG1("bta_gattc_deregister_cmpl client_if=%d", client_if );

    if ((p_buf = (tBTA_GATTC_INT_DEREG *) GKI_getbuf(sizeof(tBTA_GATTC_INT_DEREG))) != NULL)
    {
        p_buf->hdr.event = BTA_GATTC_INT_DEREG_EVT;
        p_buf->client_if = client_if;
        bta_sys_sendmsg(p_buf);
    }
    else
    {
        APPL_TRACE_ERROR1("bta_gattc_deregister_cmpl unable to allocate buffer to complete dereg=%d", client_if);
    }

}

/*******************************************************************************
**
** Function         bta_gattc_deregister
**
** Description      De-Register a GATT client application with BTA.
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_int_deregister(tBTA_GATTC_CB *p_cb, tBTA_GATTC_DATA *p_data)
{

    tBTA_GATTC_IF       client_if = p_data->int_dereg.client_if;
    tBTA_GATTC_CBACK    *p_cback;
    tBTA_GATTC          cb_data;
    tBTA_GATTC_RCB      *p_clreg;


    APPL_TRACE_DEBUG1("bta_gattc_int_deregister_cmpl client_if=%d", client_if );

    if ((p_clreg = bta_gattc_cl_get_regcb(client_if)) != NULL)
    {
        p_cback = p_clreg->p_cback;
        GATT_Deregister(client_if);
        memset(p_clreg, 0, sizeof(tBTA_GATTC_RCB));
        cb_data.reg_oper.client_if = client_if;
        cb_data.reg_oper.status    = BTA_GATT_OK;

        if (p_cback)
            /* callback with de-register event */
            (*p_cback)(BTA_GATTC_DEREG_EVT,  (tBTA_GATTC *)&cb_data);
    }
    else
    {
        APPL_TRACE_ERROR1("bta_gattc_int_deregister Deregister Failed, unknown client_if: %d", p_data->int_dereg.client_if);
    }
}


/*******************************************************************************
**
** Function         bta_gattc_deregister
**
** Description      De-Register a GATT client application with BTA.
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_deregister(tBTA_GATTC_CB *p_cb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATTC_RCB      *p_clreg;
    UINT8               i;
    BT_HDR              buf;

    if ((p_clreg = bta_gattc_cl_get_regcb(p_data->api_dereg.client_if)) != NULL)
    {
        if (p_clreg->num_clcb > 0)
        {
            /* close all CLCB related to this app */
            for (i= 0; i < BTA_GATTC_CLCB_MAX; i ++)
            {
                if (p_cb->clcb[i].in_use && (p_cb->clcb[i].p_rcb == p_clreg))
                {
                    p_clreg->dereg_pending = TRUE;

                    buf.event = BTA_GATTC_API_CLOSE_EVT;
                    buf.layer_specific = p_cb->clcb[i].bta_conn_id;
                    bta_gattc_close(&p_cb->clcb[i], (tBTA_GATTC_DATA *)&buf)  ;
                }
            }
        }
        else
            bta_gattc_deregister_cmpl(p_clreg, p_clreg->client_if);
    }
    else
    {
        APPL_TRACE_ERROR1("bta_gattc_deregister Deregister Failed, unknown client_if: %d", p_data->api_dereg.client_if);
    }
}
/*******************************************************************************
**
** Function         bta_gattc_process_api_open
**
** Description      process connect API request.
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_process_api_open (tBTA_GATTC_CB *p_cb, tBTA_GATTC_DATA * p_msg)
{
    UINT16 event = ((BT_HDR *)p_msg)->event;
    tBTA_GATTC_CLCB *p_clcb = NULL;
    tBTA_GATTC_RCB *p_clreg = bta_gattc_cl_get_regcb(p_msg->api_conn.client_if);

    if (p_clreg != NULL)
    {
        if (p_msg->api_conn.is_direct)
        {
            if ((p_clcb = bta_gattc_find_alloc_clcb(p_msg->api_conn.client_if,
                                                    p_msg->api_conn.remote_bda)) != NULL)
            {
                bta_gattc_sm_execute(p_clcb, event, p_msg);
            }
            else
            {
                APPL_TRACE_ERROR0("No resources to open a new connection.");

                bta_gattc_send_open_cback(p_clreg,
                                          BTA_GATT_NO_RESOURCES,
                                          p_msg->api_conn.remote_bda,
                                          BTA_GATT_INVALID_CONN_ID);
            }
        }
        else
        {
            bta_gattc_init_bk_conn(&p_msg->api_conn, p_clreg);
        }
    }
    else
    {
        APPL_TRACE_ERROR1("bta_gattc_process_api_open Failed, unknown client_if: %d",
                        p_msg->api_conn.client_if);
    }
}
/*******************************************************************************
**
** Function         bta_gattc_process_api_open_cancel
**
** Description      process connect API request.
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_process_api_open_cancel (tBTA_GATTC_CB *p_cb, tBTA_GATTC_DATA * p_msg)
{
    UINT16 event = ((BT_HDR *)p_msg)->event;
    tBTA_GATTC_CLCB *p_clcb = NULL;
    tBTA_GATTC_RCB *p_clreg;
    tBTA_GATT_STATUS status = BTA_GATT_ERROR;

    if (p_msg->api_cancel_conn.is_direct)
    {
        if ((p_clcb = bta_gattc_find_clcb_by_cif(p_msg->api_cancel_conn.client_if,
                                                 p_msg->api_cancel_conn.remote_bda)) != NULL)
        {
            bta_gattc_sm_execute(p_clcb, event, p_msg);
        }
        else
        {
            APPL_TRACE_ERROR0("No such connection need to be cancelled");

            p_clreg = bta_gattc_cl_get_regcb(p_msg->api_cancel_conn.client_if);

            if (p_clreg && p_clreg->p_cback)
            {
                (*p_clreg->p_cback)(BTA_GATTC_CANCEL_OPEN_EVT, (tBTA_GATTC *)&status);
            }
        }
    }
    else
    {
        bta_gattc_cancel_bk_conn(&p_msg->api_cancel_conn);

    }
}

/*******************************************************************************
**
** Function         bta_gattc_cancel_open_error
**
** Description
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_cancel_open_error(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATT_STATUS status=BTA_GATT_ERROR;

    if ( p_clcb->p_rcb->p_cback )
        (*p_clcb->p_rcb->p_cback)(BTA_GATTC_CANCEL_OPEN_EVT, (tBTA_GATTC *)&status);
}

/*******************************************************************************
**
** Function         bta_gattc_open_error
**
** Description
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_open_error(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    APPL_TRACE_ERROR0("Connection already opened. wrong state");

    bta_gattc_send_open_cback(p_clcb->p_rcb,
                              BTA_GATT_ALREADY_OPEN,
                              p_clcb->bda,
                              p_clcb->bta_conn_id);
}
/*******************************************************************************
**
** Function         bta_gattc_open_fail
**
** Description
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_open_fail(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    bta_gattc_open_error(p_clcb, p_data);
    /* open failure, remove clcb */
    bta_gattc_clcb_dealloc(p_clcb);
}

/*******************************************************************************
**
** Function         bta_gattc_open
**
** Description      Process API connection function.
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_open(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATTC_DATA gattc_data;

    /* open/hold a connection */
    if (!GATT_Connect(p_clcb->p_rcb->client_if, p_data->api_conn.remote_bda, TRUE))
    {
        APPL_TRACE_ERROR0("Connection open failure");

        bta_gattc_sm_execute(p_clcb, BTA_GATTC_INT_OPEN_FAIL_EVT, p_data);
    }
    else
    {
        /* a connected remote device */
        if (GATT_GetConnIdIfConnected(p_clcb->p_rcb->client_if,
                                      p_data->api_conn.remote_bda,
                                      &p_clcb->bta_conn_id))
        {
            gattc_data.hdr.layer_specific = p_clcb->bta_conn_id;

            bta_gattc_sm_execute(p_clcb, BTA_GATTC_INT_CONN_EVT, &gattc_data);
        }
        /* else wait for the callback event */
    }
}
/*******************************************************************************
**
** Function         bta_gattc_init_bk_conn
**
** Description      Process API Open for a background connection
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_init_bk_conn(tBTA_GATTC_API_OPEN *p_data, tBTA_GATTC_RCB *p_clreg)
{
    tBTA_GATT_STATUS         status = BTA_GATT_NO_RESOURCES;
    UINT16                   conn_id;
    tBTA_GATTC_CLCB         *p_clcb;
    tBTA_GATTC_DATA         gattc_data;

    if (bta_gattc_mark_bg_conn(p_data->client_if, p_data->remote_bda, TRUE))
    {
        /* alwaya call open to hold a connection */
        if (!GATT_Connect(p_data->client_if, p_data->remote_bda, FALSE))
        {
            status = BTA_GATT_ERROR;
            APPL_TRACE_ERROR0("bta_gattc_init_bk_conn failed");
        }
        else
        {
            status = BTA_GATT_OK;

            /* if is a connected remote device */
            if (GATT_GetConnIdIfConnected(p_data->client_if,
                                          p_data->remote_bda,
                                          &conn_id))
            {
                if ((p_clcb = bta_gattc_clcb_alloc(p_data->client_if, p_data->remote_bda)) != NULL)
                {
                    gattc_data.hdr.layer_specific = p_clcb->bta_conn_id = conn_id;

                    /* open connection */
                    bta_gattc_sm_execute(p_clcb, BTA_GATTC_INT_CONN_EVT, &gattc_data);
                    status = BTA_GATT_OK;
                }
            }
        }
    }

    /* open failure, report OPEN_EVT */
    if (status != BTA_GATT_OK)
    {
        bta_gattc_send_open_cback(p_clreg, status, p_data->remote_bda, BTA_GATT_INVALID_CONN_ID);
    }
}
/*******************************************************************************
**
** Function         bta_gattc_cancel_bk_conn
**
** Description      Process API Cancel Open for a background connection
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_cancel_bk_conn(tBTA_GATTC_API_CANCEL_OPEN *p_data)
{
    tBTA_GATTC_RCB      *p_clreg;
    tBTA_GATT_STATUS    status = BTA_GATT_ERROR;

    /* remove the device from the bg connection mask */
    if (bta_gattc_mark_bg_conn(p_data->client_if, p_data->remote_bda, FALSE))
    {
        if (GATT_CancelConnect(p_data->client_if, p_data->remote_bda, FALSE))
        {
            status = BTA_GATT_OK;
        }
        else
        {
            APPL_TRACE_ERROR0("bta_gattc_cancel_bk_conn failed");
        }
    }
    p_clreg = bta_gattc_cl_get_regcb(p_data->client_if);

    if (p_clreg && p_clreg->p_cback)
    {
        (*p_clreg->p_cback)(BTA_GATTC_CANCEL_OPEN_EVT, (tBTA_GATTC *)&status);
    }

}
/*******************************************************************************
**
** Function         bta_gattc_int_cancel_open_ok
**
** Description
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_cancel_open_ok(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATT_STATUS status = BTA_GATT_OK;

    if ( p_clcb->p_rcb->p_cback )
    {
        (*p_clcb->p_rcb->p_cback)(BTA_GATTC_CANCEL_OPEN_EVT, (tBTA_GATTC *)&status);
    }

    bta_gattc_clcb_dealloc(p_clcb);
}

/*******************************************************************************
**
** Function         bta_gattc_cancel_open
**
** Description
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_cancel_open(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATT_STATUS status=BTA_GATT_ERROR;

    if (GATT_CancelConnect(p_clcb->p_rcb->client_if, p_data->api_cancel_conn.remote_bda, TRUE))
    {
        bta_gattc_sm_execute(p_clcb, BTA_GATTC_INT_CANCEL_OPEN_OK_EVT, p_data);
    }
    else
    {
        if ( p_clcb->p_rcb->p_cback )
        {
            (*p_clcb->p_rcb->p_cback)(BTA_GATTC_CANCEL_OPEN_EVT, (tBTA_GATTC *)&status);
        }
    }
}
/*******************************************************************************
**
** Function         bta_gattc_conn
**
** Description      receive connection callback from stack
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_conn(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATTC_IF   gatt_if;
    APPL_TRACE_DEBUG1("bta_gattc_conn server cache state=%d",p_clcb->p_srcb->state);

    if (p_data != NULL)
    {
        APPL_TRACE_DEBUG1("bta_gattc_conn conn_id=%d",p_data->hdr.layer_specific);

        p_clcb->p_srcb->connected = TRUE;
        p_clcb->bta_conn_id  = p_data->hdr.layer_specific;
        GATT_GetConnectionInfor(p_data->hdr.layer_specific, &gatt_if, p_clcb->bda);

        /* start database cache if needed */
        if (p_clcb->p_srcb->p_srvc_cache == NULL)
        {
            if (p_clcb->p_srcb->state == BTA_GATTC_SERV_IDLE)
            {
                p_clcb->p_srcb->state = BTA_GATTC_SERV_LOAD;
                bta_gattc_sm_execute(p_clcb, BTA_GATTC_START_CACHE_EVT, p_data);
            }
            else /* cache is building */
                p_clcb->state = BTA_GATTC_DISCOVER_ST;
        }

        else
        {
            /* a pending service handle change indication */
            if (p_clcb->p_srcb->srvc_hdl_chg)
            {
                p_clcb->p_srcb->srvc_hdl_chg = FALSE;
                /* start discovery */
                bta_gattc_sm_execute(p_clcb, BTA_GATTC_INT_DISCOVER_EVT, NULL);
            }
        }

        if (p_clcb->p_rcb)
        {
            bta_gattc_send_open_cback(p_clcb->p_rcb,
                                      BTA_GATT_OK,
                                      p_clcb->bda,
                                      p_clcb->bta_conn_id);
        }
    }
}

/*******************************************************************************
**
** Function         bta_gattc_close_fail
**
** Description      close a  connection.
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_close_fail(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATTC           cb_data;

    if ( p_clcb->p_rcb->p_cback )
    {
        memset(&cb_data, 0, sizeof(tBTA_GATTC));
        cb_data.close.client_if = p_clcb->p_rcb->client_if;
        cb_data.close.conn_id   = p_data->hdr.layer_specific;
        bdcpy(cb_data.close.remote_bda, p_clcb->bda);
        cb_data.close.status    = BTA_GATT_ERROR;
        cb_data.close.reason    = BTA_GATT_CONN_NONE;


        (*p_clcb->p_rcb->p_cback)(BTA_GATTC_CLOSE_EVT, &cb_data);
    }
}
/*******************************************************************************
**
** Function         bta_gattc_api_close
**
** Description      close a GATTC connection.
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_close(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATTC_CBACK    *p_cback = p_clcb->p_rcb->p_cback;
    tBTA_GATTC_RCB      *p_clreg = p_clcb->p_rcb;
    tBTA_GATTC           cb_data;

    APPL_TRACE_DEBUG1("bta_gattc_close conn_id=%d",p_clcb->bta_conn_id);

    if (p_data->hdr.event == BTA_GATTC_API_CLOSE_EVT)
        p_clcb->status = GATT_Disconnect(p_clcb->bta_conn_id);

    cb_data.close.client_if = p_clcb->p_rcb->client_if;
    cb_data.close.conn_id   = p_clcb->bta_conn_id;
    cb_data.close.status    = p_clcb->status;
    cb_data.close.reason    = p_clcb->reason;
    bdcpy(cb_data.close.remote_bda, p_clcb->bda);

    if (p_clcb->status == BTA_GATT_OK)
    {
        /* if the srcb is no longer needed, reset the state */
        if ( -- p_clcb->p_srcb->num_clcb == 0)
        {
            APPL_TRACE_DEBUG0("Update srcb connection status");
            p_clcb->p_srcb->connected = FALSE;
            p_clcb->p_srcb->state = BTA_GATTC_SERV_IDLE;
        }

        bta_gattc_clcb_dealloc(p_clcb);
    }

    ( * p_cback)(BTA_GATTC_CLOSE_EVT,   (tBTA_GATTC *)&cb_data);

    if (-- p_clreg->num_clcb == 0 && p_clreg->dereg_pending)
    {
        bta_gattc_deregister_cmpl(p_clreg, p_clreg->client_if);
    }

}

/*******************************************************************************
**
** Function         bta_gattc_reset_discover_st
**
** Description      when a SRCB finished discovery, tell all related clcb.
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_reset_discover_st(tBTA_GATTC_SERV *p_srcb)
{
    tBTA_GATTC_CB   *p_cb = &bta_gattc_cb;
    UINT8 i;

    for (i = 0; i < BTA_GATTC_CLCB_MAX; i ++)
    {
        if (p_cb->clcb[i].p_srcb == p_srcb)
        {
            bta_gattc_sm_execute(&p_cb->clcb[i], BTA_GATTC_DISCOVER_CMPL_EVT, NULL);
        }
    }
}
/*******************************************************************************
**
** Function         bta_gattc_set_discover_st
**
** Description      when a SRCB start discovery, tell all related clcb and set
**                  the state.
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_set_discover_st(tBTA_GATTC_SERV *p_srcb)
{
    tBTA_GATTC_CB   *p_cb = &bta_gattc_cb;
    UINT8   i;

#if BLE_INCLUDED == TRUE
    L2CA_EnableUpdateBleConnParams(p_srcb->server_bda, FALSE);
#endif
    for (i = 0; i < BTA_GATTC_CLCB_MAX; i ++)
    {
        if (p_cb->clcb[i].p_srcb == p_srcb)
        {
            p_cb->clcb[i].state = BTA_GATTC_DISCOVER_ST;
        }
    }
}
/*******************************************************************************
**
** Function         bta_gattc_start_discover
**
** Description      Start a discovery on server.
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_start_discover(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    /* pending operation, wait until it finishes */

    APPL_TRACE_DEBUG1("bta_gattc_start_discover conn_id=%d",p_clcb->bta_conn_id);
    if (p_clcb->p_q_cmd != NULL && p_clcb->auto_update == BTA_GATTC_NO_SCHEDULE &&
        p_clcb->p_srcb->state == BTA_GATTC_SERV_IDLE)
    {
        p_clcb->auto_update = BTA_GATTC_DISC_WAITING;
        p_clcb->state = BTA_GATTC_CONN_ST; /* set clcb state */
    }
    else /* no pending operation, start discovery right away */
    {
        p_clcb->auto_update = BTA_GATTC_NO_SCHEDULE;

        if (p_clcb->p_srcb != NULL)
        {
            /* clear the service change mask */
            p_clcb->p_srcb->srvc_hdl_chg = FALSE;
            p_clcb->p_srcb->update_count = 0;

            /* set all srcb related clcb into discovery ST */
            bta_gattc_set_discover_st(p_clcb->p_srcb);

            if ( bta_gattc_init_cache(p_clcb->p_srcb) ||
                 bta_gattc_discover_pri_service(p_clcb->bta_conn_id, p_clcb->p_srcb, GATT_DISC_SRVC_ALL) != BTA_GATT_OK)
            {
                APPL_TRACE_ERROR0("discovery on server failed");
                bta_gattc_reset_discover_st(p_clcb->p_srcb);
            }
        }
        else
        {
            APPL_TRACE_ERROR0("unknown device, can not start discovery");
        }
    }
}
/*******************************************************************************
**
** Function         bta_gattc_disc_cmpl
**
** Description      discovery on server is finished
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_disc_cmpl(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATTC_DATA *p_q_cmd = p_clcb->p_q_cmd;
    APPL_TRACE_DEBUG1("bta_gattc_disc_cmpl conn_id=%d",p_clcb->bta_conn_id);

#if BLE_INCLUDED == TRUE
    L2CA_EnableUpdateBleConnParams(p_clcb->p_srcb->server_bda, TRUE);
#endif
    p_clcb->p_srcb->state = BTA_GATTC_SERV_IDLE;

    /* release pending attribute list buffer */
    utl_freebuf((void **)&p_clcb->p_srcb->p_srvc_list);

    /* get any queued command to proceed */
    if (p_q_cmd != NULL)
    {
        p_clcb->p_q_cmd = NULL;

        bta_gattc_sm_execute(p_clcb, p_q_cmd->hdr.event, p_q_cmd);

        utl_freebuf((void **)&p_q_cmd);

    }
}
/*******************************************************************************
**
** Function         bta_gattc_read
**
** Description      Read an attribute
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_read(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    UINT16 handle = 0;
    tGATT_READ_PARAM    read_param;
    tBTA_GATTC_OP_CMPL  op_cmpl;

    memset (&read_param, 0 ,sizeof(tGATT_READ_PARAM));
    memset (&op_cmpl, 0 ,sizeof(tBTA_GATTC_OP_CMPL));

    if (bta_gattc_enqueue(p_clcb, p_data))
    {
        if ((handle = bta_gattc_id2handle(p_clcb->p_srcb,
                                          &p_data->api_read.srvc_id,
                                          &p_data->api_read.char_id,
                                          p_data->api_read.descr_type)) == 0)
        {
            op_cmpl.status = BTA_GATT_ERROR;
        }
        else
        {
            read_param.by_handle.handle = handle;
            read_param.by_handle.auth_req = p_data->api_read.auth_req;

            op_cmpl.status = GATTC_Read(p_clcb->bta_conn_id, GATT_READ_BY_HANDLE, &read_param);
        }

        /* read fail */
        if (op_cmpl.status != BTA_GATT_OK)
        {
            op_cmpl.op_code = GATTC_OPTYPE_READ;
            op_cmpl.p_cmpl = NULL;

            bta_gattc_sm_execute(p_clcb, BTA_GATTC_OP_CMPL_EVT, (tBTA_GATTC_DATA *)&op_cmpl);
        }
    }
}
/*******************************************************************************
**
** Function         bta_gattc_read_multi
**
** Description      read multiple
**
** Returns          None.
*********************************************************************************/
void bta_gattc_read_multi(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    UINT16              i, handle;
    tBTA_GATT_STATUS    status = BTA_GATT_OK;
    tGATT_READ_PARAM    read_param;
    tBTA_GATTC_OP_CMPL  op_cmpl;
    tBTA_GATTC_ATTR_ID  *p_id;
    tBT_UUID            dummy_uuid;

    if (bta_gattc_enqueue(p_clcb, p_data))
    {
        memset(&dummy_uuid, 0, sizeof(tBT_UUID));
        memset(&read_param, 0, sizeof(tGATT_READ_PARAM));

        p_id = p_data->api_read_multi.p_id_list;

        for (i = 0; i < p_data->api_read_multi.num_attr && p_id; i ++, p_id ++)
        {
            handle = 0;

            if (p_id->id_type == BTA_GATT_TYPE_CHAR)
            {
                handle = bta_gattc_id2handle(p_clcb->p_srcb,
                                     &p_id->id_value.char_id.srvc_id,
                                     &p_id->id_value.char_id.char_id,
                                     dummy_uuid);
            }
            else if (p_id->id_type == BTA_GATT_TYPE_CHAR_DESCR)
            {
                handle = bta_gattc_id2handle(p_clcb->p_srcb,
                                     &p_id->id_value.char_descr_id.char_id.srvc_id,
                                     &p_id->id_value.char_descr_id.char_id.char_id,
                                     p_id->id_value.char_descr_id.descr_type);
            }
            else
            {
                APPL_TRACE_ERROR1("invalud ID type: %d", p_id->id_type);
            }

            if (handle == 0)
            {
                status = BTA_GATT_ERROR;
                break;
            }
        }
        if (status == BTA_GATT_OK)
        {
            read_param.read_multiple.num_handles = p_data->api_read_multi.num_attr;
            read_param.read_multiple.auth_req = p_data->api_read_multi.auth_req;

            status = GATTC_Read(p_clcb->bta_conn_id, GATT_READ_MULTIPLE, &read_param);
        }

        /* read fail */
        if (status != BTA_GATT_OK)
        {
            memset(&op_cmpl, 0, sizeof(tBTA_GATTC_OP_CMPL));

            op_cmpl.status  = status;
            op_cmpl.op_code = GATTC_OPTYPE_READ;
            op_cmpl.p_cmpl  = NULL;

            bta_gattc_sm_execute(p_clcb, BTA_GATTC_OP_CMPL_EVT, (tBTA_GATTC_DATA *)&op_cmpl);
        }
    }
}
/*******************************************************************************
**
** Function         bta_gattc_write
**
** Description      Write an attribute
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_write(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    UINT16              handle = 0;
    tGATT_VALUE         attr = {0};
    tBTA_GATTC_OP_CMPL  op_cmpl;
    tBTA_GATT_STATUS    status = BTA_GATT_OK;

    if (bta_gattc_enqueue(p_clcb, p_data))
    {
        if ((handle = bta_gattc_id2handle(p_clcb->p_srcb,
                                          &p_data->api_write.srvc_id,
                                          &p_data->api_write.char_id,
                                          p_data->api_write.descr_type)) == 0)
        {
            status = BTA_GATT_ERROR;
        }
        else
        {
            attr.handle= handle;
            attr.offset = p_data->api_write.offset;
            attr.len    = p_data->api_write.len;
            attr.auth_req = p_data->api_write.auth_req;

            if (p_data->api_write.p_value)
                memcpy(attr.value, p_data->api_write.p_value, p_data->api_write.len);

            status = GATTC_Write(p_clcb->bta_conn_id, p_data->api_write.write_type, &attr);
        }

        /* write fail */
        if (status != BTA_GATT_OK)
        {
            memset(&op_cmpl, 0, sizeof(tBTA_GATTC_OP_CMPL));

            op_cmpl.status  = status;
            op_cmpl.op_code = GATTC_OPTYPE_WRITE;
            op_cmpl.p_cmpl  = NULL;

            bta_gattc_sm_execute(p_clcb, BTA_GATTC_OP_CMPL_EVT, (tBTA_GATTC_DATA *)&op_cmpl);
        }
    }
}
/*******************************************************************************
**
** Function         bta_gattc_execute
**
** Description      send execute write
**
** Returns          None.
*********************************************************************************/
void bta_gattc_execute(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATTC_OP_CMPL  op_cmpl;
    tBTA_GATT_STATUS    status;

    if (bta_gattc_enqueue(p_clcb, p_data))
    {
        status = GATTC_ExecuteWrite(p_clcb->bta_conn_id, p_data->api_exec.is_execute);

        if (status != BTA_GATT_OK)
        {
            memset(&op_cmpl, 0, sizeof(tBTA_GATTC_OP_CMPL));

            op_cmpl.status  = status;
            op_cmpl.op_code = GATTC_OPTYPE_EXE_WRITE;
            op_cmpl.p_cmpl  = NULL;

            bta_gattc_sm_execute(p_clcb, BTA_GATTC_OP_CMPL_EVT, (tBTA_GATTC_DATA *)&op_cmpl);
        }
    }
}

/*******************************************************************************
**
** Function         bta_gattc_confirm
**
** Description      send handle value confirmation
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_confirm(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    UINT16 handle;
    tBT_UUID    null_uuid = {0};

    if ((handle = bta_gattc_id2handle(p_clcb->p_srcb,
                                      &p_data->api_confirm.srvc_id,
                                      &p_data->api_confirm.char_id,
                                      null_uuid)) == 0)
    {
        APPL_TRACE_ERROR0("Can not map service/char ID into valid handle");
    }
    else
    {
        if (GATTC_SendHandleValueConfirm(p_data->api_confirm.hdr.layer_specific, handle)
            != GATT_SUCCESS)
        {
            APPL_TRACE_ERROR1("bta_gattc_confirm to handle [0x%04x] failed", handle);
        }
    }
}
/*******************************************************************************
**
** Function         bta_gattc_read_cmpl
**
** Description      read complete
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_read_cmpl(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_OP_CMPL *p_data)
{
    UINT8               event;
    tBTA_GATTC          cb_data;
    tBTA_GATT_READ_VAL  read_value;

    memset(&cb_data, 0, sizeof(tBTA_GATTC));
    memset(&read_value, 0, sizeof(tBTA_GATT_READ_VAL));

    cb_data.read.status     = p_data->status;

    if (p_data->p_cmpl != NULL && p_data->status == BTA_GATT_OK)
    {
        if (bta_gattc_handle2id(p_clcb->p_srcb,
                                p_data->p_cmpl->att_value.handle,
                                &cb_data.read.srvc_id,
                                &cb_data.read.char_id,
                                &cb_data.read.descr_type) == FALSE)
        {
            cb_data.read.status = BTA_GATT_INTERNAL_ERROR;
            APPL_TRACE_ERROR1("can not map to GATT ID. handle = 0x%04x", p_data->p_cmpl->att_value.handle);
        }
        else
        {
            cb_data.read.status = bta_gattc_pack_read_cb_data(p_clcb->p_srcb,
                                                              cb_data.read.descr_type,
                                                              &p_data->p_cmpl->att_value,
                                                              &read_value);
            cb_data.read.p_value = &read_value;
        }
    }
    else
    {
        cb_data.read.srvc_id = p_clcb->p_q_cmd->api_read.srvc_id;
        cb_data.read.char_id = p_clcb->p_q_cmd->api_read.char_id;
        cb_data.read.descr_type = p_clcb->p_q_cmd->api_read.descr_type;
    }

    event = (p_clcb->p_q_cmd->api_read.descr_type.len == 0) ? BTA_GATTC_READ_CHAR_EVT: BTA_GATTC_READ_DESCR_EVT;
    cb_data.read.conn_id = p_clcb->bta_conn_id;

    utl_freebuf((void **)&p_clcb->p_q_cmd);
    /* read complete, callback */
    ( *p_clcb->p_rcb->p_cback)(event, (tBTA_GATTC *)&cb_data);

}
/*******************************************************************************
**
** Function         bta_gattc_write_cmpl
**
** Description      read complete
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_write_cmpl(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_OP_CMPL *p_data)
{
    tBTA_GATTC      cb_data = {0};
    UINT8          event;

    cb_data.write.status     = p_data->status;

    if (p_data->p_cmpl != NULL)
    {
        bta_gattc_handle2id(p_clcb->p_srcb, p_data->p_cmpl->handle,
                            &cb_data.write.srvc_id, &cb_data.write.char_id,
                            &cb_data.write.descr_type);
    }
    else
    {
        cb_data.write.srvc_id = p_clcb->p_q_cmd->api_write.srvc_id;
        cb_data.write.char_id = p_clcb->p_q_cmd->api_write.char_id;
        cb_data.write.descr_type = p_clcb->p_q_cmd->api_write.descr_type;
    }

    if (p_clcb->p_q_cmd->api_write.hdr.event == BTA_GATTC_API_WRITE_EVT &&
        p_clcb->p_q_cmd->api_write.write_type == BTA_GATTC_WRITE_PREPARE)

        event = BTA_GATTC_PREP_WRITE_EVT;

    else if (p_clcb->p_q_cmd->api_write.descr_type.len == 0)

        event = BTA_GATTC_WRITE_CHAR_EVT;

    else
        event = BTA_GATTC_WRITE_DESCR_EVT;

    utl_freebuf((void **)&p_clcb->p_q_cmd);
    cb_data.write.conn_id = p_clcb->bta_conn_id;
    /* write complete, callback */
    ( *p_clcb->p_rcb->p_cback)(event, (tBTA_GATTC *)&cb_data);

}
/*******************************************************************************
**
** Function         bta_gattc_exec_cmpl
**
** Description      execute write complete
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_exec_cmpl(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_OP_CMPL *p_data)
{
    tBTA_GATTC          cb_data;

    utl_freebuf((void **)&p_clcb->p_q_cmd);

    p_clcb->status      = BTA_GATT_OK;

    /* execute complete, callback */
    cb_data.exec_cmpl.conn_id = p_clcb->bta_conn_id;
    cb_data.exec_cmpl.status = p_data->status;

    ( *p_clcb->p_rcb->p_cback)(BTA_GATTC_EXEC_EVT,  &cb_data);

}


/*******************************************************************************
**
** Function         bta_gattc_op_cmpl
**
** Description      operation completed.
**
** Returns          None.
**
*******************************************************************************/
void  bta_gattc_op_cmpl(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    UINT8           op = (UINT8)p_data->op_cmpl.op_code;
    UINT8           mapped_op = 0;

    APPL_TRACE_DEBUG1("bta_gattc_op_cmpl op = %d", op);

    if (op == GATTC_OPTYPE_INDICATION || op == GATTC_OPTYPE_NOTIFICATION)
    {
        APPL_TRACE_ERROR0("unexpected operation, ignored");
    }
    else if (op >= GATTC_OPTYPE_READ)
    {
        if (p_clcb->p_q_cmd == NULL)
        {
            APPL_TRACE_ERROR0("No pending command");
            return;
        }
        if (p_clcb->p_q_cmd->hdr.event != bta_gattc_opcode_to_int_evt[op - GATTC_OPTYPE_READ])
        {
            mapped_op = p_clcb->p_q_cmd->hdr.event - BTA_GATTC_API_READ_EVT + GATTC_OPTYPE_READ;
            if ( mapped_op > GATTC_OPTYPE_INDICATION)   mapped_op = 0;

#if (BT_TRACE_VERBOSE == TRUE)
            APPL_TRACE_ERROR3("expect op:(%s :0x%04x), receive unexpected operation (%s).",
                                bta_gattc_op_code_name[mapped_op] , p_clcb->p_q_cmd->hdr.event,
                                bta_gattc_op_code_name[op]);
#else
            APPL_TRACE_ERROR3("expect op:(%u :0x%04x), receive unexpected operation (%u).",
                                mapped_op , p_clcb->p_q_cmd->hdr.event, op);
#endif
            return;
        }

        /* service handle change void the response, discard it */
        if (p_clcb->auto_update == BTA_GATTC_DISC_WAITING)
        {
            p_clcb->auto_update = BTA_GATTC_REQ_WAITING;
            bta_gattc_sm_execute(p_clcb, BTA_GATTC_INT_DISCOVER_EVT, NULL);
        }
        else if (op == GATTC_OPTYPE_READ)
            bta_gattc_read_cmpl(p_clcb, &p_data->op_cmpl);

        else if (op == GATTC_OPTYPE_WRITE)
            bta_gattc_write_cmpl(p_clcb, &p_data->op_cmpl);

        else if (op == GATTC_OPTYPE_EXE_WRITE)
            bta_gattc_exec_cmpl(p_clcb, &p_data->op_cmpl);
        /*
        else if (op == GATTC_OPTYPE_CONFIG) // API to be added
        {
        }
       */
    }
}
/*******************************************************************************
**
** Function         bta_gattc_op_cmpl
**
** Description      operation completed.
**
** Returns          None.
**
*******************************************************************************/
void  bta_gattc_ignore_op_cmpl(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    /* receive op complete when discovery is started, ignore the response,
        and wait for discovery finish and resent */
    APPL_TRACE_DEBUG1("bta_gattc_ignore_op_cmpl op = %d", p_data->hdr.layer_specific);

}
/*******************************************************************************
**
** Function         bta_gattc_search
**
** Description      start a search in the local server cache
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_search(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATT_STATUS    status = GATT_INTERNAL_ERROR;
    tBTA_GATTC cb_data;
    APPL_TRACE_DEBUG1("bta_gattc_search conn_id=%d",p_clcb->bta_conn_id);
    if (p_clcb->p_srcb && p_clcb->p_srcb->p_srvc_cache)
    {
        status = BTA_GATT_OK;
        /* search the local cache of a server device */
        bta_gattc_search_service(p_clcb, p_data->api_search.srvc_uuid);
    }
    cb_data.search_cmpl.status  = status;
    cb_data.search_cmpl.conn_id = p_clcb->bta_conn_id;

    /* end of search or no server cache available */
    ( *p_clcb->p_rcb->p_cback)(BTA_GATTC_SEARCH_CMPL_EVT,  &cb_data);
}
/*******************************************************************************
**
** Function         bta_gattc_q_cmd
**
** Description      enqueue a command into control block, usually because discovery
**                  operation is busy.
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_q_cmd(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    bta_gattc_enqueue(p_clcb, p_data);
}
/*******************************************************************************
**
** Function         bta_gattc_cache_open
**
** Description      open a NV cache for loading
**
** Returns          void
**
*******************************************************************************/
void bta_gattc_cache_open(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    bta_gattc_set_discover_st(p_clcb->p_srcb);

    APPL_TRACE_DEBUG1("bta_gattc_cache_open conn_id=%d",p_clcb->bta_conn_id);
    bta_gattc_co_cache_open(p_clcb->p_srcb->server_bda, BTA_GATTC_CI_CACHE_OPEN_EVT,
                            p_clcb->bta_conn_id, FALSE);
}
/*******************************************************************************
**
** Function         bta_gattc_start_load
**
** Description      start cache loading by sending callout open cache
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_ci_open(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    APPL_TRACE_DEBUG2("bta_gattc_ci_open conn_id=%d server state=%d" ,
                      p_clcb->bta_conn_id, p_clcb->p_srcb->state);
    if (p_clcb->p_srcb->state == BTA_GATTC_SERV_LOAD)
    {
        if (p_data->ci_open.status == BTA_GATT_OK)
        {
            p_clcb->p_srcb->attr_index = 0;
            bta_gattc_co_cache_load(p_clcb->p_srcb->server_bda,
                                    BTA_GATTC_CI_CACHE_LOAD_EVT,
                                    p_clcb->p_srcb->attr_index,
                                    p_clcb->bta_conn_id);
        }
        else
        {
            /* cache open failure, start discovery */
            bta_gattc_start_discover(p_clcb, NULL);
        }
    }
    if (p_clcb->p_srcb->state == BTA_GATTC_SERV_SAVE)
    {
        if (p_data->ci_open.status == BTA_GATT_OK)
        {
            if (!bta_gattc_cache_save(p_clcb->p_srcb, p_clcb->bta_conn_id))
            {
                p_data->ci_open.status = BTA_GATT_ERROR;
            }
        }
        if (p_data->ci_open.status != BTA_GATT_OK)
        {
            p_clcb->p_srcb->attr_index = 0;
            bta_gattc_co_cache_close(p_clcb->p_srcb->server_bda, p_clcb->bta_conn_id);
            bta_gattc_reset_discover_st(p_clcb->p_srcb);

        }
    }
}
/*******************************************************************************
**
** Function         bta_gattc_ci_load
**
** Description      cache loading received.
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_ci_load(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{

    APPL_TRACE_DEBUG2("bta_gattc_ci_load conn_id=%d load status=%d" ,
                      p_clcb->bta_conn_id, p_data->ci_load.status );
    bta_gattc_co_cache_close(p_clcb->p_srcb->server_bda, 0);

    if ((p_data->ci_load.status == BTA_GATT_OK ||
         p_data->ci_load.status == BTA_GATT_MORE) &&
        p_data->ci_load.num_attr > 0)
    {
        bta_gattc_rebuild_cache(p_clcb->p_srcb, p_data->ci_load.num_attr, p_data->ci_load.attr, p_clcb->p_srcb->attr_index);

        if (p_data->ci_load.status == BTA_GATT_OK)
        {
            p_clcb->p_srcb->attr_index = 0;
            bta_gattc_reset_discover_st(p_clcb->p_srcb);

        }
        else /* load more */
        {
            p_clcb->p_srcb->attr_index += p_data->ci_load.num_attr;

            bta_gattc_co_cache_load(p_clcb->p_srcb->server_bda,
                                    BTA_GATTC_CI_CACHE_LOAD_EVT,
                                    p_clcb->p_srcb->attr_index,
                                    p_clcb->bta_conn_id);
        }
    }
    else
    {
        p_clcb->p_srcb->attr_index = 0;
        /* cache open failure, start discovery */
        bta_gattc_start_discover(p_clcb, NULL);
    }
}
/*******************************************************************************
**
** Function         bta_gattc_ci_load
**
** Description      cache loading received.
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_ci_save(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    APPL_TRACE_DEBUG1("bta_gattc_ci_save conn_id=%d  " ,
                      p_clcb->bta_conn_id   );

    if (!bta_gattc_cache_save(p_clcb->p_srcb, p_clcb->bta_conn_id))
    {
        p_clcb->p_srcb->attr_index = 0;
        bta_gattc_co_cache_close(p_clcb->p_srcb->server_bda, 0);
        bta_gattc_reset_discover_st(p_clcb->p_srcb);
    }
}

/*******************************************************************************
**
** Function         bta_gattc_fail
**
** Description      report API call failure back to apps
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_fail(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    if (p_clcb->status == BTA_GATT_OK)
    {
        APPL_TRACE_ERROR1("operation not supported at current state [%d]", p_clcb->state);
    }
}
/*******************************************************************************
**
** Function         bta_gattc_conn_cback
**                  bta_gattc_cmpl_cback
**
** Description      callback functions to GATT client stack.
**
** Returns          void
**
*******************************************************************************/
static void bta_gattc_conn_cback(tGATT_IF gattc_if, BD_ADDR bda, UINT16 conn_id,
                                 BOOLEAN connected, tGATT_DISCONN_REASON reason)
{
    BT_HDR          *p_buf;
    tBTA_GATTC_CLCB *p_clcb = NULL;

    APPL_TRACE_DEBUG4("bta_gattc_conn_cback: cif = %d connected = %d conn_id = %d reaosn = 0x%04x",
                      gattc_if, connected, conn_id, reason);

    if (connected)
    {
        /* outgoing connection : locate a logic channel */
        if ((p_clcb = bta_gattc_find_clcb_by_cif(gattc_if, bda)) == NULL)
        {

#if BLE_INCLUDED == TRUE
            /* for a background connection */
            if (L2CA_GetBleConnRole(bda)== HCI_ROLE_MASTER &&
                bta_gattc_check_bg_conn(gattc_if, bda))
            {
                /* allocate a new channel */
                p_clcb = bta_gattc_clcb_alloc(gattc_if, bda);
            }
#endif
        }
        if (p_clcb != NULL)
        {
            p_clcb->bta_conn_id = conn_id;

            if ((p_buf = (BT_HDR *) GKI_getbuf(sizeof(BT_HDR))) != NULL)
            {
                p_buf->event = BTA_GATTC_INT_CONN_EVT;
                p_buf->layer_specific = conn_id;

                bta_sys_sendmsg(p_buf);
            }
        }
    }
    else
    {
        /* connection attempt timeout, send connection callback event */
        if (reason == GATT_CONN_CANCEL )
        {
            p_clcb = bta_gattc_clcb_alloc(gattc_if, bda);
            p_clcb->bta_conn_id = conn_id;
        }
        if ((p_clcb = bta_gattc_find_clcb_by_conn_id(conn_id)) != NULL)
        {
            if ((p_buf = (BT_HDR *) GKI_getbuf(sizeof(BT_HDR))) != NULL)
            {
                p_buf->event = BTA_GATTC_INT_DISCONN_EVT;
                p_buf->layer_specific = conn_id;
                p_clcb->reason        = reason;

                bta_sys_sendmsg(p_buf);
            }
        }
        else
        {
            APPL_TRACE_DEBUG1(" connection ID: [%d] not used by BTA", conn_id);
        }
    }
}
/*******************************************************************************
**
** Function         bta_gattc_process_srvc_chg_ind
**
** Description      process service change indication.
**
** Returns          None.
**
*******************************************************************************/
BOOLEAN bta_gattc_process_srvc_chg_ind(UINT16 conn_id,
                                       tBTA_GATTC_RCB      *p_clrcb,
                                       tBTA_GATTC_SERV     *p_srcb,
                                       tBTA_GATTC_CLCB      *p_clcb,
                                       tBTA_GATTC_NOTIFY    *p_notify,
                                       UINT16 handle)
{
    tBT_UUID        gattp_uuid, srvc_chg_uuid;
    BOOLEAN         processed = FALSE;
    UINT8           i;

    gattp_uuid.len = 2;
    gattp_uuid.uu.uuid16 = UUID_SERVCLASS_GATT_SERVER;

    srvc_chg_uuid.len = 2;
    srvc_chg_uuid.uu.uuid16 = GATT_UUID_GATT_SRV_CHGD;

    if (bta_gattc_uuid_compare(p_notify->char_id.srvc_id.id.uuid, gattp_uuid, TRUE) &&
        bta_gattc_uuid_compare(p_notify->char_id.char_id.uuid, srvc_chg_uuid, TRUE))
    {
        processed = TRUE;
        /* mark service handle change pending */
        p_srcb->srvc_hdl_chg = TRUE;
        /* clear up all notification/indication registration */
        bta_gattc_clear_notif_registration(conn_id);
        /* service change indication all received, do discovery update */
        if ( ++ p_srcb->update_count == bta_gattc_num_reg_app())
        {
            /* not an opened connection; or connection busy */
            /* search for first available clcb and start discovery */
            if (p_clcb == NULL || (p_clcb && p_clcb->p_q_cmd != NULL))
            {
                for (i = 0 ; i < BTA_GATTC_CLCB_MAX; i ++)
                {
                    if (bta_gattc_cb.clcb[i].in_use &&
                        bta_gattc_cb.clcb[i].p_srcb == p_srcb &&
                        bta_gattc_cb.clcb[i].p_q_cmd == NULL)
                    {
                        p_clcb = &bta_gattc_cb.clcb[i];
                        break;
                    }
                }
            }
            /* send confirmation here if this is an indication, it should always be */
            GATTC_SendHandleValueConfirm(conn_id, handle);

            /* if connection available, refresh cache by doing discovery now */
            if (p_clcb != NULL)
                bta_gattc_sm_execute(p_clcb, BTA_GATTC_INT_DISCOVER_EVT, NULL);
        }
        /* notify applicationf or service change */
        if (p_clrcb->p_cback != NULL)
        {
            APPL_TRACE_ERROR0("bta_gattc_process_srvc_chg_ind 2");
           (* p_clrcb->p_cback)(BTA_GATTC_SRVC_CHG_EVT, (tBTA_GATTC *)p_srcb->server_bda);
        }

    }

    return processed;

}
/*******************************************************************************
**
** Function         bta_gattc_proc_other_indication
**
** Description      process all non-service change indication/notification.
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_proc_other_indication(tBTA_GATTC_CLCB *p_clcb, UINT8 op,
                                     tGATT_CL_COMPLETE *p_data,
                                     tBTA_GATTC_NOTIFY *p_notify)
{
    APPL_TRACE_DEBUG2("bta_gattc_proc_other_indication check \
                       p_data->att_value.handle=%d p_data->handle=%d",
                       p_data->att_value.handle, p_data->handle);
    APPL_TRACE_DEBUG1("is_notify", p_notify->is_notify);

    p_notify->is_notify = (op == GATTC_OPTYPE_INDICATION) ? FALSE : TRUE;
    p_notify->len = p_data->att_value.len;
    bdcpy(p_notify->bda, p_clcb->bda);
    memcpy(p_notify->value, p_data->att_value.value, p_data->att_value.len);
    p_notify->conn_id = p_clcb->bta_conn_id;

    if (p_clcb->p_rcb->p_cback)
        (*p_clcb->p_rcb->p_cback)(BTA_GATTC_NOTIF_EVT,  (tBTA_GATTC *)p_notify);

}
/*******************************************************************************
**
** Function         bta_gattc_process_indicate
**
** Description      process indication/notification.
**
** Returns          None.
**
*******************************************************************************/
void bta_gattc_process_indicate(UINT16 conn_id, tGATTC_OPTYPE op, tGATT_CL_COMPLETE *p_data)
{
    UINT16              handle = p_data->att_value.handle;
    tBTA_GATTC_CLCB     *p_clcb ;
    tBTA_GATTC_RCB      *p_clrcb = NULL;
    tBTA_GATTC_SERV     *p_srcb = NULL;
    tBTA_GATTC_NOTIFY   notify;
    BD_ADDR             remote_bda;
    tBTA_GATTC_IF       gatt_if;

    if (!GATT_GetConnectionInfor(conn_id, &gatt_if, remote_bda))
    {
        APPL_TRACE_ERROR0("indication/notif for unknown app");
        return;
    }

    if ((p_clrcb = bta_gattc_cl_get_regcb(gatt_if)) == NULL)
    {
        APPL_TRACE_ERROR0("indication/notif for unregistered app");
        return;
    }

    if ((p_srcb = bta_gattc_find_srcb(remote_bda)) == NULL)
    {
        APPL_TRACE_ERROR0("indication/notif for unknown device, ignore");
        return;
    }

    p_clcb = bta_gattc_find_clcb_by_conn_id(conn_id);

    if (bta_gattc_handle2id(p_srcb, handle,
                            &notify.char_id.srvc_id,
                            &notify.char_id.char_id,
                            &notify.descr_type))
    {
        /* if non-service change indication/notification, forward to application */
        if (!bta_gattc_process_srvc_chg_ind(conn_id, p_clrcb, p_srcb, p_clcb, &notify, handle))
        {
            /* if app registered for the notification */
            if (bta_gattc_check_notif_registry(p_clrcb, p_srcb, &notify))
            {
                /* connection not open yet */
                if (p_clcb == NULL)
                {
                    if ((p_clcb = bta_gattc_clcb_alloc(gatt_if, remote_bda)) != NULL)
                    {
                        p_clcb->bta_conn_id = conn_id;

                        /* send connection event */
                        bta_gattc_send_open_cback(p_clrcb,
                                                  BTA_GATT_OK,
                                                  remote_bda,
                                                  conn_id);
                    }
                    else
                    {
                        APPL_TRACE_ERROR0("No resources");
                    }
                }

                if (p_clcb != NULL)
                    bta_gattc_proc_other_indication(p_clcb, op, p_data, &notify);
            }
            /* no one intersted and need ack? */
            else if (op == GATTC_OPTYPE_INDICATION)
            {
                APPL_TRACE_DEBUG0("no one interested, ack now");
                GATTC_SendHandleValueConfirm(conn_id, handle);
            }
        }
    }
    else
    {
        APPL_TRACE_ERROR1("Indi/Notif for Unknown handle[0x%04x], can not find in local cache.", handle);
    }
}

/*******************************************************************************
**
** Function         bta_gattc_cmpl_cback
**
** Description      client operation complete callback register with BTE GATT.
**
** Returns          None.
**
*******************************************************************************/
static void  bta_gattc_cmpl_cback(UINT16 conn_id, tGATTC_OPTYPE op, tGATT_STATUS status,
                                  tGATT_CL_COMPLETE *p_data)
{
    tBTA_GATTC_CLCB     *p_clcb ;
    tBTA_GATTC_OP_CMPL  *p_buf;
    UINT16              len = sizeof(tBTA_GATTC_OP_CMPL) + sizeof(tGATT_CL_COMPLETE);

    APPL_TRACE_DEBUG3("bta_gattc_cmpl_cback: conn_id = %d op = %d status = %d",
                      conn_id, op, status);

    /* notification and indication processed right away */
    if (op == GATTC_OPTYPE_NOTIFICATION || op == GATTC_OPTYPE_INDICATION)
    {
        bta_gattc_process_indicate(conn_id, op, p_data);
        return;
    }
    /* for all other operation, not expected if w/o connection */
    else if ((p_clcb = bta_gattc_find_clcb_by_conn_id(conn_id)) == NULL)
    {
        APPL_TRACE_ERROR1("bta_gattc_cmpl_cback unknown conn_id =  %d, ignore data", conn_id);
        return;
    }


    if ((p_buf = (tBTA_GATTC_OP_CMPL *) GKI_getbuf(len)) != NULL)
    {
        memset(p_buf, 0, len);
        p_buf->hdr.event = BTA_GATTC_OP_CMPL_EVT;
        p_buf->hdr.layer_specific = conn_id;
        p_buf->status = status;
        p_buf->op_code = op;

        if (p_data != NULL)
        {
            p_buf->p_cmpl = (tGATT_CL_COMPLETE *)(p_buf + 1);
            memcpy(p_buf->p_cmpl, p_data, sizeof(tGATT_CL_COMPLETE));
        }

        bta_sys_sendmsg(p_buf);
    }

    return;
}
#endif /* BTA_GATT_INCLUDED */
