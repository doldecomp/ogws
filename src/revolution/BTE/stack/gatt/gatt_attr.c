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
 *  this file contains the main GATT server attributes access request
 *  handling functions.
 *
 ******************************************************************************/

#include "bt_target.h"

#include "gatt_api.h"
#include "gatt_int.h"

#if BLE_INCLUDED == TRUE

#define GATTP_MAX_NUM_INC_SVR       0
#define GATTP_MAX_CHAR_NUM          2
#define GATTP_MAX_ATTR_NUM          (GATTP_MAX_CHAR_NUM * 2 + GATTP_MAX_NUM_INC_SVR + 1)
#define GATTP_MAX_CHAR_VALUE_SIZE   50

#ifndef GATTP_ATTR_DB_SIZE
#define GATTP_ATTR_DB_SIZE      GATT_DB_MEM_SIZE(GATTP_MAX_NUM_INC_SVR, GATTP_MAX_CHAR_NUM, GATTP_MAX_CHAR_VALUE_SIZE)
#endif

static void gatt_profile_request_cback (UINT16 conn_id, UINT32 trans_id, UINT8 op_code, tGATTS_DATA *p_data);
static void gatt_profile_connect_cback (tGATT_IF gatt_if, BD_ADDR bda, UINT16 conn_id, BOOLEAN connected, tGATT_DISCONN_REASON reason);

static tGATT_CBACK gatt_profile_cback =
{
    gatt_profile_connect_cback,
    NULL,
    NULL,
    NULL,
    gatt_profile_request_cback
} ;

/*******************************************************************************
**
** Function         gatt_profile_find_conn_id_by_bd_addr
**
** Description      The function searches all LCB with macthing bd address
**
** Returns          total number of clcb found.
**
*******************************************************************************/
UINT16 gatt_profile_find_conn_id_by_bd_addr(BD_ADDR bda)
{
    UINT8 i_clcb;
    tGATT_PROFILE_CLCB    *p_clcb = NULL;

    for (i_clcb = 0, p_clcb= gatt_cb.profile_clcb; i_clcb < GATT_MAX_APPS; i_clcb++, p_clcb++)
    {
        if (p_clcb->in_use && p_clcb->connected && !memcmp(p_clcb->bda, bda, BD_ADDR_LEN))
        {
            return p_clcb->conn_id;
        }
    }

    return GATT_INVALID_CONN_ID;
}

/*******************************************************************************
**
** Function         gatt_profile_find_clcb_by_bd_addr
**
** Description      The function searches all LCBs with macthing bd address.
**
** Returns          Pointer to the found link conenction control block.
**
*******************************************************************************/
tGATT_PROFILE_CLCB *gatt_profile_find_clcb_by_bd_addr(BD_ADDR bda)
{
    UINT8 i_clcb;
    tGATT_PROFILE_CLCB    *p_clcb = NULL;

    for (i_clcb = 0, p_clcb= gatt_cb.profile_clcb; i_clcb < GATT_MAX_APPS; i_clcb++, p_clcb++)
    {
        if (p_clcb->in_use && p_clcb->connected && !memcmp(p_clcb->bda, bda, BD_ADDR_LEN))
        {
            return p_clcb;
        }
    }

    return p_clcb;
}

/*******************************************************************************
**
** Function         gatt_profile_clcb_alloc
**
** Description      The function allocates a GATT profile  connection link control block
**
** Returns           NULL if not found. Otherwise pointer to the connection link block.
**
*******************************************************************************/
tGATT_PROFILE_CLCB *gatt_profile_clcb_alloc (UINT16 conn_id, BD_ADDR bda)
{
    UINT8                   i_clcb = 0;
    tGATT_PROFILE_CLCB      *p_clcb = NULL;

    for (i_clcb = 0, p_clcb= gatt_cb.profile_clcb; i_clcb < GATT_MAX_APPS; i_clcb++, p_clcb++)
    {
        if (!p_clcb->in_use)
        {
            p_clcb->in_use      = TRUE;
            p_clcb->conn_id     = conn_id;
            p_clcb->connected   = TRUE;
            memcpy (p_clcb->bda, bda, BD_ADDR_LEN);
            break;
        }
    }
    return p_clcb;
}
/*******************************************************************************
**
** Function         gatt_profile_clcb_dealloc
**
** Description      The function deallocates a GATT profile  connection link control block
**
** Returns           NTrue the deallocation is successful
**
*******************************************************************************/
BOOLEAN gatt_profile_clcb_dealloc (UINT16 conn_id)
{
    UINT8                   i_clcb = 0;
    tGATT_PROFILE_CLCB      *p_clcb = NULL;

    for (i_clcb = 0, p_clcb= gatt_cb.profile_clcb; i_clcb < GATT_MAX_APPS; i_clcb++, p_clcb++)
    {
        if (p_clcb->in_use && p_clcb->connected && (p_clcb->conn_id == conn_id))
        {
            memset(p_clcb, 0, sizeof(tGATT_PROFILE_CLCB));
            return TRUE;
        }
    }
    return FALSE;
}


/*******************************************************************************
**
** Function         gatt_profile_request_cback
**
** Description      GATT profile attribute access request callback.
**
** Returns          void.
**
*******************************************************************************/
static void gatt_profile_request_cback (UINT16 conn_id, UINT32 trans_id, tGATTS_REQ_TYPE type,
                                        tGATTS_DATA *p_data)
{
    UINT8       status = GATT_INVALID_PDU;
    tGATTS_RSP   rsp_msg ;
    BOOLEAN     ignore = FALSE;

    memset(&rsp_msg, 0, sizeof(tGATTS_RSP));

    switch (type)
    {
        case GATTS_REQ_TYPE_READ:
            status = GATT_READ_NOT_PERMIT;
            break;

        case GATTS_REQ_TYPE_WRITE:
            status = GATT_WRITE_NOT_PERMIT;
            break;

        case GATTS_REQ_TYPE_WRITE_EXEC:
            //case GATT_CMD_WRITE:
            ignore = TRUE;
            GATT_TRACE_EVENT0("Ignore GATT_REQ_EXEC_WRITE/WRITE_CMD" );
            break;

        case GATTS_REQ_TYPE_MTU:
            GATT_TRACE_EVENT1("Get MTU exchange new mtu size: %d", p_data->mtu);
            ignore = TRUE;
            break;

        default:
            GATT_TRACE_EVENT1("Unknown/unexpected LE GAP ATT request: 0x%02x", type);
            break;
    }

    if (!ignore)
        GATTS_SendRsp (conn_id, trans_id, status, &rsp_msg);

}

/*******************************************************************************
**
** Function         gatt_profile_connect_cback
**
** Description      Gatt profile connection callback.
**
** Returns          void
**
*******************************************************************************/
static void gatt_profile_connect_cback (tGATT_IF gatt_if, BD_ADDR bda, UINT16 conn_id,
                                        BOOLEAN connected, tGATT_DISCONN_REASON reason)
{
    GATT_TRACE_EVENT5 ("gatt_profile_connect_cback: from %08x%04x connected:%d conn_id=%d reason = 0x%04x",
                       (bda[0]<<24)+(bda[1]<<16)+(bda[2]<<8)+bda[3],
                       (bda[4]<<8)+bda[5], connected, conn_id, reason);

    if (connected)
    {
        if (gatt_profile_clcb_alloc(conn_id, bda) == NULL)
        {
            GATT_TRACE_ERROR0 ("gatt_profile_connect_cback: no_resource");
            return;
        }
    }
    else
    {
        gatt_profile_clcb_dealloc(conn_id);
    }

}

/*******************************************************************************
**
** Function         gatt_profile_db_init
**
** Description      Initializa the GATT profile attribute database.
**
*******************************************************************************/
void gatt_profile_db_init (void)
{
    tBT_UUID          app_uuid = {LEN_UUID_128, {0}};
    tBT_UUID          uuid = {LEN_UUID_16, {UUID_SERVCLASS_GATT_SERVER}};
    UINT16            service_handle = 0;
    tGATT_STATUS      status;

    /* Fill our internal UUID with a fixed pattern 0x81 */
    memset (&app_uuid.uu.uuid128, 0x81, LEN_UUID_128);


    /* Create a GATT profile service */
    gatt_cb.gatt_if = GATT_Register(&app_uuid, &gatt_profile_cback);
    GATT_StartIf(gatt_cb.gatt_if);

    service_handle = GATTS_CreateService (gatt_cb.gatt_if , &uuid, 0, GATTP_MAX_ATTR_NUM, TRUE);
    /* add Service Changed characteristic
    */
    uuid.uu.uuid16 = gatt_cb.gattp_attr.uuid = GATT_UUID_GATT_SRV_CHGD;
    gatt_cb.gattp_attr.service_change = 0;
    gatt_cb.gattp_attr.handle   =
    gatt_cb.handle_of_h_r       = GATTS_AddCharacteristic(service_handle, &uuid, 0, GATT_CHAR_PROP_BIT_INDICATE);

    GATT_TRACE_DEBUG1 ("gatt_profile_db_init:  handle of service changed%d",
                       gatt_cb.handle_of_h_r  );

    /* start service
    */
    status = GATTS_StartService (gatt_cb.gatt_if, service_handle, GATT_TRANSPORT_LE_BR_EDR);

    GATT_TRACE_DEBUG2 ("gatt_profile_db_init:  gatt_if=%d   start status%d",
                       gatt_cb.gatt_if,  status);
}

#endif  /* BLE_INCLUDED */
