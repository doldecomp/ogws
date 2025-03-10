/******************************************************************************
 *
 *  Copyright (C) 2010-2012 Broadcom Corporation
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
 *  This is the implementation of the API for GATT module of BTA.
 *
 ******************************************************************************/

#include "bt_target.h"

#if defined(BTA_GATT_INCLUDED) && (BTA_GATT_INCLUDED == TRUE)

#include <string.h>
#include "gki.h"
#include "bta_sys.h"
#include "bta_gatt_api.h"
#include "bta_gattc_int.h"

/*****************************************************************************
**  Constants
*****************************************************************************/

static const tBTA_SYS_REG bta_gatt_reg =
{
    bta_gattc_hdl_event,
    NULL        /* need a disable functino to be called when BT is disabled */
};

/*******************************************************************************
**
** Function         BTA_GATTC_AppRegister
**
** Description      This function is called to register application callbacks
**                    with BTA GATTC module.
**
** Parameters       p_app_uuid - applicaiton UUID
**                  p_client_cb - pointer to the application callback function.
**
** Returns          None
**
*******************************************************************************/
void BTA_GATTC_AppRegister(tBT_UUID *p_app_uuid, tBTA_GATTC_CBACK *p_client_cb)
{
    tBTA_GATTC_API_REG  *p_buf;

    /* register with BTA system manager */
    GKI_sched_lock();
    bta_sys_register(BTA_ID_GATTC, &bta_gatt_reg);
    GKI_sched_unlock();

    if ((p_buf = (tBTA_GATTC_API_REG *) GKI_getbuf(sizeof(tBTA_GATTC_API_REG))) != NULL)
    {
        p_buf->hdr.event    = BTA_GATTC_API_REG_EVT;
        if (p_app_uuid != NULL)
            memcpy(&p_buf->app_uuid, p_app_uuid, sizeof(tBT_UUID));
        p_buf->p_cback      = p_client_cb;

        bta_sys_sendmsg(p_buf);
    }
    return;
}

/*******************************************************************************
**
** Function         BTA_GATTC_AppDeregister
**
** Description      This function is called to deregister an application
**                  from BTA GATTC module.
**
** Parameters       client_if - client interface identifier.
**
** Returns          None
**
*******************************************************************************/
void BTA_GATTC_AppDeregister(tBTA_GATTC_IF client_if)
{
    tBTA_GATTC_API_DEREG  *p_buf;

    if ((p_buf = (tBTA_GATTC_API_DEREG *) GKI_getbuf(sizeof(tBTA_GATTC_API_DEREG))) != NULL)
    {
        p_buf->hdr.event = BTA_GATTC_API_DEREG_EVT;
        p_buf->client_if = client_if;
        bta_sys_sendmsg(p_buf);
    }
    return;
}

/*******************************************************************************
**
** Function         BTA_GATTC_Open
**
** Description      Open a direct connection or add a background auto connection
**                  bd address
**
** Parameters       client_if: server interface.
**                  remote_bda: remote device BD address.
**                  is_direct: direct connection or background auto connection
**
** Returns          void
**
*******************************************************************************/
void BTA_GATTC_Open(tBTA_GATTC_IF client_if, BD_ADDR remote_bda, BOOLEAN is_direct)
{
    tBTA_GATTC_API_OPEN  *p_buf;

    if ((p_buf = (tBTA_GATTC_API_OPEN *) GKI_getbuf(sizeof(tBTA_GATTC_API_OPEN))) != NULL)
    {
        p_buf->hdr.event = BTA_GATTC_API_OPEN_EVT;

        p_buf->client_if = client_if;
        p_buf->is_direct = is_direct;
        memcpy(p_buf->remote_bda, remote_bda, BD_ADDR_LEN);


        bta_sys_sendmsg(p_buf);
    }
    return;
}

/*******************************************************************************
**
** Function         BTA_GATTC_CancelOpen
**
** Description      Cancel a direct open connection or remove a background auto connection
**                  bd address
**
** Parameters       client_if: server interface.
**                  remote_bda: remote device BD address.
**                  is_direct: direct connection or background auto connection
**
** Returns          void
**
*******************************************************************************/
void BTA_GATTC_CancelOpen(tBTA_GATTC_IF client_if, BD_ADDR remote_bda, BOOLEAN is_direct)
{
    tBTA_GATTC_API_CANCEL_OPEN  *p_buf;

    if ((p_buf = (tBTA_GATTC_API_CANCEL_OPEN *) GKI_getbuf(sizeof(tBTA_GATTC_API_CANCEL_OPEN))) != NULL)
    {
        p_buf->hdr.event = BTA_GATTC_API_CANCEL_OPEN_EVT;

        p_buf->client_if = client_if;
        p_buf->is_direct = is_direct;
        memcpy(p_buf->remote_bda, remote_bda, BD_ADDR_LEN);

        bta_sys_sendmsg(p_buf);
    }
    return;
}

/*******************************************************************************
**
** Function         BTA_GATTC_Close
**
** Description      Close a connection to a GATT server.
**
** Parameters       conn_id: connectino ID to be closed.
**
** Returns          void
**
*******************************************************************************/
void BTA_GATTC_Close(UINT16 conn_id)
{
    BT_HDR  *p_buf;

    if ((p_buf = (BT_HDR *) GKI_getbuf(sizeof(BT_HDR))) != NULL)
    {
        p_buf->event = BTA_GATTC_API_CLOSE_EVT;

        p_buf->layer_specific = conn_id;

        bta_sys_sendmsg(p_buf);
    }
    return;

}
/*******************************************************************************
**
** Function         BTA_GATTC_ServiceSearchRequest
**
** Description      This function is called to request a GATT service discovery
**                    on a GATT server. This function report service search result
**                  by a callback event, and followed by a service search complete
**                  event.
**
** Parameters       conn_id: connection ID.
**                  p_srvc_uuid: a UUID of the service application is interested in.
**                              If Null, discover for all services.
**
** Returns          None
**
*******************************************************************************/
void BTA_GATTC_ServiceSearchRequest (UINT16 conn_id, tBT_UUID *p_srvc_uuid)
{
    tBTA_GATTC_API_SEARCH  *p_buf;
    UINT16  len = sizeof(tBTA_GATTC_API_SEARCH) + sizeof(tBT_UUID);

    if ((p_buf = (tBTA_GATTC_API_SEARCH *) GKI_getbuf(len)) != NULL)
    {
        memset(p_buf, 0, len);

        p_buf->hdr.event = BTA_GATTC_API_SEARCH_EVT;
        p_buf->hdr.layer_specific = conn_id;

        if (p_srvc_uuid)
        {
            memcpy(&p_buf->srvc_uuid, p_srvc_uuid, sizeof(tBT_UUID));
        }
        bta_sys_sendmsg(p_buf);
    }
    return;
}


/*******************************************************************************
**
** Function         BTA_GATTC_GetFirstChar
**
** Description      This function is called to find the first charatceristic of the
**                  service on the given server.
**
** Parameters       conn_id: connection ID which identify the server.
**                  p_srvc_id: the service ID of which the characteristic is belonged to.
**                  p_char_uuid_cond: Characteristic UUID, if NULL find the first available
**                               characteristic.
**                  p_char_result: output parameter which will store the GATT
**                                  characteristic ID.
**                  p_property: output parameter to carry the characteristic property.
**
** Returns          returns status.
**
*******************************************************************************/
tBTA_GATT_STATUS  BTA_GATTC_GetFirstChar (UINT16 conn_id, tBTA_GATT_SRVC_ID *p_srvc_id,
                                          tBT_UUID *p_char_uuid_cond,
                                          tBTA_GATTC_CHAR_ID *p_char_result,
                                          tBTA_GATT_CHAR_PROP *p_property)
{
    tBTA_GATT_STATUS    status;

    if (!p_srvc_id || !p_char_result)
        return BTA_GATT_ILLEGAL_PARAMETER;

    if ((status = bta_gattc_query_cache(conn_id, BTA_GATTC_ATTR_TYPE_CHAR, p_srvc_id, NULL,
                                        p_char_uuid_cond, &p_char_result->char_id, p_property))
        == BTA_GATT_OK)
    {
        memcpy(&p_char_result->srvc_id, p_srvc_id, sizeof(tBTA_GATT_SRVC_ID));
    }

    return status;

}
/*******************************************************************************
**
** Function         BTA_GATTC_GetNextChar
**
** Description      This function is called to find the next charatceristic of the
**                  service on the given server.
**
** Parameters       conn_id: connection ID which identify the server.
**                  p_start_char_id: start the characteristic search from the next record
**                           after the one identified by char_id.
**                  p_char_uuid_cond: Characteristic UUID, if NULL find the first available
**                               characteristic.
**                  p_char_result: output parameter which will store the GATT
**                                  characteristic ID.
**                  p_property: output parameter to carry the characteristic property.
**
** Returns          returns status.
**
*******************************************************************************/
tBTA_GATT_STATUS  BTA_GATTC_GetNextChar (UINT16 conn_id,
                                         tBTA_GATTC_CHAR_ID *p_start_char_id,
                                         tBT_UUID           *p_char_uuid_cond,
                                         tBTA_GATTC_CHAR_ID *p_char_result,
                                         tBTA_GATT_CHAR_PROP    *p_property)
{
    tBTA_GATT_STATUS    status;

    if (!p_start_char_id || !p_char_result)
        return BTA_GATT_ILLEGAL_PARAMETER;

    if ((status = bta_gattc_query_cache(conn_id, BTA_GATTC_ATTR_TYPE_CHAR,
                                        &p_start_char_id->srvc_id,
                                        &p_start_char_id->char_id,
                                        p_char_uuid_cond,
                                        &p_char_result->char_id,
                                        p_property))
        == BTA_GATT_OK)
    {
        memcpy(&p_char_result->srvc_id, &p_start_char_id->srvc_id, sizeof(tBTA_GATT_SRVC_ID));
    }

    return status;
}

/*******************************************************************************
**
** Function         BTA_GATTC_GetFirstCharDescr
**
** Description      This function is called to find the first charatceristic descriptor of the
**                  charatceristic on the given server.
**
** Parameters       conn_id: connection ID which identify the server.
**                  p_char_id: the characteristic ID of which the descriptor is belonged to.
**                  p_descr_uuid_cond: Characteristic Descr UUID, if NULL find the first available
**                               characteristic.
**                  p_descr_result: output parameter which will store the GATT
**                                  characteristic descriptor ID.
**
** Returns          returns status.
**
*******************************************************************************/
tBTA_GATT_STATUS  BTA_GATTC_GetFirstCharDescr (UINT16 conn_id, tBTA_GATTC_CHAR_ID *p_char_id,
                                                tBT_UUID *p_descr_uuid_cond,
                                                tBTA_GATTC_CHAR_DESCR_ID *p_descr_result)
{
    tBTA_GATT_STATUS    status;

    if (!p_char_id || !p_descr_result)
        return BTA_GATT_ILLEGAL_PARAMETER;

    memset(p_descr_result, 0, sizeof(tBTA_GATTC_CHAR_DESCR_ID));

    if ((status = bta_gattc_query_cache(conn_id,
                                        BTA_GATTC_ATTR_TYPE_CHAR_DESCR,
                                        &p_char_id->srvc_id,
                                        &p_char_id->char_id,
                                        p_descr_uuid_cond,
                                        &p_descr_result->char_id.char_id,
                                        NULL))
        == BTA_GATT_OK)
    {
        memcpy(&p_descr_result->descr_type, &p_descr_result->char_id.char_id.uuid, sizeof(tBT_UUID));
        memcpy(&p_descr_result->char_id, p_char_id, sizeof(tBTA_GATTC_CHAR_ID));
    }

    return status;

}
/*******************************************************************************
**
** Function         BTA_GATTC_GetNextCharDescr
**
** Description      This function is called to find the next charatceristic of the
**                  service on the given server.
**
** Parameters       conn_id: connection ID which identify the server.
**                  p_start_descr_id: start the characteristic search from the next record
**                           after the one identified by p_start_descr_id.
**                  p_descr_uuid_cond: Characteristic descriptor UUID, if NULL find
**                               the first available characteristic descriptor.
**                  p_descr_result: output parameter which will store the GATT
**                                  characteristic descriptor ID.
**
** Returns          returns status.
**
*******************************************************************************/
tBTA_GATT_STATUS  BTA_GATTC_GetNextCharDescr (UINT16 conn_id,
                                             tBTA_GATTC_CHAR_DESCR_ID *p_start_descr_id,
                                             tBT_UUID           *p_descr_uuid_cond,
                                             tBTA_GATTC_CHAR_DESCR_ID *p_descr_result)
{
    tBTA_GATT_STATUS    status;

    if (!p_start_descr_id || !p_descr_result)
        return BTA_GATT_ILLEGAL_PARAMETER;

    memset(p_descr_result, 0, sizeof(tBTA_GATTC_CHAR_DESCR_ID));

    if ((status = bta_gattc_query_cache(conn_id, BTA_GATTC_ATTR_TYPE_CHAR_DESCR,
                                        &p_start_descr_id->char_id.srvc_id,
                                        &p_start_descr_id->char_id.char_id,
                                        p_descr_uuid_cond,
                                        &p_descr_result->char_id.char_id,
                                        (void *)&p_start_descr_id->descr_type))
        == BTA_GATT_OK)
    {
        memcpy(&p_descr_result->descr_type, &p_descr_result->char_id.char_id.uuid, sizeof(tBT_UUID));
        memcpy(&p_descr_result->char_id, p_start_descr_id, sizeof(tBTA_GATTC_CHAR_ID));
    }

    return status;
}


/*******************************************************************************
**
** Function         BTA_GATTC_GetFirstIncludedService
**
** Description      This function is called to find the first included service of the
**                  service on the given server.
**
** Parameters       conn_id: connection ID which identify the server.
**                  p_srvc_id: the service ID of which the characteristic is belonged to.
**                  p_uuid_cond: Characteristic UUID, if NULL find the first available
**                               characteristic.
**                  p_result: output parameter which will store the GATT ID
**                              of the included service found.
**
** Returns          returns status.
**
*******************************************************************************/
tBTA_GATT_STATUS  BTA_GATTC_GetFirstIncludedService(UINT16 conn_id, tBTA_GATT_SRVC_ID *p_srvc_id,
                                                    tBT_UUID *p_uuid_cond, tBTA_GATTC_INCL_SVC_ID *p_result)
{
    tBTA_GATT_STATUS    status;

    if (!p_srvc_id || !p_result)
        return BTA_GATT_ILLEGAL_PARAMETER;

    if ((status = bta_gattc_query_cache(conn_id,
                                        BTA_GATTC_ATTR_TYPE_INCL_SRVC,
                                        p_srvc_id,
                                        NULL,
                                        p_uuid_cond,
                                        &p_result->incl_svc_id.id,
                                        (tBTA_GATT_CHAR_PROP *)&p_result->incl_svc_id.is_primary))
        == BTA_GATT_OK)
    {
        memcpy(&p_result->srvc_id, p_srvc_id, sizeof(tBTA_GATT_SRVC_ID));
    }

    return status;
}
/*******************************************************************************
**
** Function         BTA_GATTC_GetNextIncludedService
**
** Description      This function is called to find the next included service of the
**                  service on the given server.
**
** Parameters       conn_id: connection ID which identify the server.
**                  p_start_id: start the search from the next record
**                                  after the one identified by p_start_id.
**                  p_uuid_cond: Included service UUID, if NULL find the first available
**                               included service.
**                  p_result: output parameter which will store the GATT ID
**                              of the included service found.
**
** Returns          returns status.
**
*******************************************************************************/
tBTA_GATT_STATUS  BTA_GATTC_GetNextIncludedService(UINT16 conn_id,
                                                   tBTA_GATTC_INCL_SVC_ID *p_start_id,
                                                   tBT_UUID               *p_uuid_cond,
                                                   tBTA_GATTC_INCL_SVC_ID *p_result)
{
    tBTA_GATT_STATUS    status;

    if (!p_start_id || !p_result)
        return BTA_GATT_ILLEGAL_PARAMETER;

    if ((status = bta_gattc_query_cache(conn_id,
                                        BTA_GATTC_ATTR_TYPE_INCL_SRVC,
                                        &p_start_id->srvc_id,
                                        &p_start_id->incl_svc_id.id,
                                        p_uuid_cond,
                                        &p_result->incl_svc_id.id,
                                        (tBTA_GATT_CHAR_PROP *)&p_result->incl_svc_id.is_primary))
        == BTA_GATT_OK)
    {
        memcpy(&p_result->srvc_id, &p_start_id->srvc_id, sizeof(tBTA_GATT_SRVC_ID));
    }

    return status;
}

/*******************************************************************************
**
** Function         BTA_GATTC_ReadCharacteristic
**
** Description      This function is called to read a service's characteristics of
**                    the given characteritisc ID.
**
** Parameters       conn_id - connectino ID.
**                    p_char_id - characteritic ID to read.
**
** Returns          None
**
*******************************************************************************/
void BTA_GATTC_ReadCharacteristic(UINT16 conn_id, tBTA_GATTC_CHAR_ID *p_char_id,
                                  tBTA_GATT_AUTH_REQ auth_req)
{
    tBTA_GATTC_API_READ  *p_buf;

    if ((p_buf = (tBTA_GATTC_API_READ *) GKI_getbuf(sizeof(tBTA_GATTC_API_READ))) != NULL)
    {
        memset(p_buf, 0, sizeof(tBTA_GATTC_API_READ));

        p_buf->hdr.event = BTA_GATTC_API_READ_EVT;
        p_buf->hdr.layer_specific = conn_id;
        p_buf->auth_req = auth_req;

        memcpy(&p_buf->srvc_id, &p_char_id->srvc_id, sizeof(tBTA_GATT_SRVC_ID));
        memcpy(&p_buf->char_id, &p_char_id->char_id, sizeof(tBTA_GATT_ID));

        bta_sys_sendmsg(p_buf);
    }
    return;
}

/*******************************************************************************
**
** Function         BTA_GATTC_ReadCharDescr
**
** Description      This function is called to read a characteristics descriptor.
**
** Parameters       conn_id - connection ID.
**                    p_char_descr_id - characteritic descriptor ID to read.
**
** Returns          None
**
*******************************************************************************/
void BTA_GATTC_ReadCharDescr (UINT16 conn_id,
                              tBTA_GATTC_CHAR_DESCR_ID  *p_descr_id,
                              tBTA_GATT_AUTH_REQ auth_req)
{
    tBTA_GATTC_API_READ  *p_buf;

    if ((p_buf = (tBTA_GATTC_API_READ *) GKI_getbuf(sizeof(tBTA_GATTC_API_READ))) != NULL)
    {
        memset(p_buf, 0, sizeof(tBTA_GATTC_API_READ));

        p_buf->hdr.event = BTA_GATTC_API_READ_EVT;
        p_buf->hdr.layer_specific = conn_id;
        p_buf->auth_req = auth_req;

        memcpy(&p_buf->srvc_id, &p_descr_id->char_id.srvc_id, sizeof(tBTA_GATT_SRVC_ID));
        memcpy(&p_buf->char_id, &p_descr_id->char_id.char_id, sizeof(tBTA_GATT_ID));
        memcpy(&p_buf->descr_type, &p_descr_id->descr_type, sizeof(tBT_UUID));

        bta_sys_sendmsg(p_buf);
    }
    return;

}
/*******************************************************************************
**
** Function         BTA_GATTC_ReadMultiple
**
** Description      This function is called to read multiple characteristic or
**                  characteristic descriptors.
**
** Parameters       conn_id - connectino ID.
**                    p_read_multi - pointer to the read multiple parameter.
**
** Returns          None
**
*******************************************************************************/
void BTA_GATTC_ReadMultiple(UINT16 conn_id, tBTA_GATTC_MULTI *p_read_multi,
                            tBTA_GATT_AUTH_REQ auth_req)
{
    tBTA_GATTC_API_READ_MULTI  *p_buf;
    tBTA_GATTC_ATTR_ID          *p_value;
    UINT16      len = (UINT16)(sizeof(tBTA_GATTC_API_READ_MULTI) +
                               p_read_multi->num_attr * sizeof(tBTA_GATTC_ATTR_ID));
    UINT8       i;

    if ((p_buf = (tBTA_GATTC_API_READ_MULTI *) GKI_getbuf(len)) != NULL)
    {
        memset(p_buf, 0, len);

        p_buf->hdr.event = BTA_GATTC_API_READ_MULTI_EVT;
        p_buf->hdr.layer_specific = conn_id;
        p_buf->auth_req = auth_req;

        p_buf->num_attr = p_read_multi->num_attr;

        if (p_buf->num_attr > 0)
        {
            p_buf->p_id_list = p_value = (tBTA_GATTC_ATTR_ID *)(p_buf + 1);

            for (i = 0; i < p_buf->num_attr; i ++, p_value ++)
            {
                memcpy(p_value, &p_read_multi->id_list[i], sizeof(tBTA_GATTC_ATTR_ID));
            }
        }
        bta_sys_sendmsg(p_buf);
    }
    return;
}


/*******************************************************************************
**
** Function         BTA_GATTC_WriteCharValue
**
** Description      This function is called to write characteristic value.
**
** Parameters       conn_id - connection ID.
**                    p_char_id - characteristic ID to write.
**                    write_type - type of write.
**                  len: length of the data to be written.
**                  p_value - the value to be written.
**
** Returns          None
**
*******************************************************************************/
void BTA_GATTC_WriteCharValue ( UINT16 conn_id,
                                tBTA_GATTC_CHAR_ID *p_char_id,
                                tBTA_GATTC_WRITE_TYPE  write_type,
                                UINT16 len,
                                UINT8 *p_value,
                                tBTA_GATT_AUTH_REQ auth_req)
{
    tBTA_GATTC_API_WRITE  *p_buf;

    if ((p_buf = (tBTA_GATTC_API_WRITE *) GKI_getbuf((UINT16)(sizeof(tBTA_GATTC_API_WRITE) + len))) != NULL)
    {
        memset(p_buf, 0, sizeof(tBTA_GATTC_API_WRITE) + len);

        p_buf->hdr.event = BTA_GATTC_API_WRITE_EVT;
        p_buf->hdr.layer_specific = conn_id;
        p_buf->auth_req = auth_req;

        memcpy(&p_buf->srvc_id, &p_char_id->srvc_id, sizeof(tBTA_GATT_SRVC_ID));
        memcpy(&p_buf->char_id, &p_char_id->char_id, sizeof(tBTA_GATT_ID));

        p_buf->write_type = write_type;
        p_buf->len = len;

        if (p_value && len > 0)
        {
            p_buf->p_value = (UINT8 *)(p_buf + 1);
            memcpy(p_buf->p_value, p_value, len);
        }

        bta_sys_sendmsg(p_buf);
    }
    return;
}
/*******************************************************************************
**
** Function         BTA_GATTC_WriteCharDescr
**
** Description      This function is called to write characteristic descriptor value.
**
** Parameters       conn_id - connection ID
**                    p_char_descr_id - characteristic descriptor ID to write.
**                  write_type - write type.
**                  p_value - the value to be written.
**
** Returns          None
**
*******************************************************************************/
void BTA_GATTC_WriteCharDescr (UINT16 conn_id,
                               tBTA_GATTC_CHAR_DESCR_ID *p_char_descr_id,
                               tBTA_GATTC_WRITE_TYPE  write_type,
                               tBTA_GATT_UNFMT      *p_data,
                               tBTA_GATT_AUTH_REQ auth_req)
{
    tBTA_GATTC_API_WRITE  *p_buf;
    UINT16  len = sizeof(tBTA_GATTC_API_WRITE) + p_data->len;

    if ((p_buf = (tBTA_GATTC_API_WRITE *) GKI_getbuf(len)) != NULL)
    {
        memset(p_buf, 0, len);

        p_buf->hdr.event = BTA_GATTC_API_WRITE_EVT;
        p_buf->hdr.layer_specific = conn_id;
        p_buf->auth_req = auth_req;

        memcpy(&p_buf->srvc_id, &p_char_descr_id->char_id.srvc_id, sizeof(tBTA_GATT_SRVC_ID));
        memcpy(&p_buf->char_id, &p_char_descr_id->char_id.char_id, sizeof(tBTA_GATT_ID));
        memcpy(&p_buf->descr_type, &p_char_descr_id->descr_type, sizeof(tBT_UUID));
        p_buf->write_type = write_type;

        if (p_data && p_data->len != 0)
        {
            p_buf->p_value  = (UINT8 *)(p_buf + 1);
            p_buf->len      = p_data->len;
            /* pack the descr data */
            memcpy(p_buf->p_value, p_data->p_value, p_data->len);
        }

        bta_sys_sendmsg(p_buf);
    }
    return;

}
/*******************************************************************************
**
** Function         BTA_GATTC_PrepareWrite
**
** Description      This function is called to prepare write a characteristic value.
**
** Parameters       conn_id - connection ID.
**                    p_char_id - GATT characteritic ID of the service.
**                  offset - offset of the write value.
**                  len: length of the data to be written.
**                  p_value - the value to be written.
**
** Returns          None
**
*******************************************************************************/
void BTA_GATTC_PrepareWrite  (UINT16 conn_id, tBTA_GATTC_CHAR_ID *p_char_id,
                              UINT16 offset, UINT16 len, UINT8 *p_value,
                              tBTA_GATT_AUTH_REQ auth_req)
{
    tBTA_GATTC_API_WRITE  *p_buf;

    if ((p_buf = (tBTA_GATTC_API_WRITE *) GKI_getbuf((UINT16)(sizeof(tBTA_GATTC_API_WRITE) + len))) != NULL)
    {
        memset(p_buf, 0, sizeof(tBTA_GATTC_API_WRITE) + len);

        p_buf->hdr.event = BTA_GATTC_API_WRITE_EVT;
        p_buf->hdr.layer_specific = conn_id;
        p_buf->auth_req = auth_req;

        memcpy(&p_buf->srvc_id, &p_char_id->srvc_id, sizeof(tBTA_GATT_SRVC_ID));
        memcpy(&p_buf->char_id, &p_char_id->char_id, sizeof(tBTA_GATT_ID));

        p_buf->write_type = BTA_GATTC_WRITE_PREPARE;
        p_buf->offset   = offset;
        p_buf->len = len;

        if (p_value && len > 0)
        {
            p_buf->p_value = (UINT8 *)(p_buf + 1);
            memcpy(p_buf->p_value, p_value, len);
        }

        bta_sys_sendmsg(p_buf);
    }
    return;

}
/*******************************************************************************
**
** Function         BTA_GATTC_ExecuteWrite
**
** Description      This function is called to execute write a prepare write sequence.
**
** Parameters       conn_id - connection ID.
**                    is_execute - execute or cancel.
**
** Returns          None
**
*******************************************************************************/
void BTA_GATTC_ExecuteWrite  (UINT16 conn_id, BOOLEAN is_execute)
{
    tBTA_GATTC_API_EXEC  *p_buf;

    if ((p_buf = (tBTA_GATTC_API_EXEC *) GKI_getbuf((UINT16)sizeof(tBTA_GATTC_API_EXEC))) != NULL)
    {
        memset(p_buf, 0, sizeof(tBTA_GATTC_API_EXEC));

        p_buf->hdr.event = BTA_GATTC_API_EXEC_EVT;
        p_buf->hdr.layer_specific = conn_id;

        p_buf->is_execute = is_execute;

        bta_sys_sendmsg(p_buf);
    }
    return;

}
/*******************************************************************************
**
** Function         BTA_GATTC_SendIndConfirm
**
** Description      This function is called to send handle value confirmation.
**
** Parameters       conn_id - connection ID.
**                    p_char_id - characteristic ID to confirm.
**
** Returns          None
**
*******************************************************************************/
void BTA_GATTC_SendIndConfirm (UINT16 conn_id, tBTA_GATTC_CHAR_ID *p_char_id)
{
    tBTA_GATTC_API_CONFIRM  *p_buf;

    APPL_TRACE_API3("BTA_GATTC_SendIndConfirm conn_id=%d service uuid1=0x%x char uuid=0x%x",
                    conn_id, p_char_id->srvc_id.id.uuid.uu.uuid16, p_char_id->char_id.uuid.uu.uuid16); //toto

    if ((p_buf = (tBTA_GATTC_API_CONFIRM *) GKI_getbuf(sizeof(tBTA_GATTC_API_CONFIRM))) != NULL)
    {
        memset(p_buf, 0, sizeof(tBTA_GATTC_API_CONFIRM));

        p_buf->hdr.event = BTA_GATTC_API_CONFIRM_EVT;
        p_buf->hdr.layer_specific = conn_id;

        memcpy(&p_buf->srvc_id, &p_char_id->srvc_id, sizeof(tBTA_GATT_SRVC_ID));
        memcpy(&p_buf->char_id, &p_char_id->char_id, sizeof(tBTA_GATT_ID));

        bta_sys_sendmsg(p_buf);
    }
    return;

}

/*******************************************************************************
**
** Function         BTA_GATTC_RegisterForNotifications
**
** Description      This function is called to register for notification of a service.
**
** Parameters       client_if - client interface.
**                  bda - target GATT server.
**                  p_char_id - pointer to GATT characteristic ID.
**
** Returns          OK if registration succeed, otherwise failed.
**
*******************************************************************************/
tBTA_GATT_STATUS BTA_GATTC_RegisterForNotifications (tBTA_GATTC_IF client_if,
                                                     BD_ADDR bda,
                                                     tBTA_GATTC_CHAR_ID *p_char_id)
{
    tBTA_GATTC_RCB      *p_clreg;
    tBTA_GATT_STATUS    status = BTA_GATT_ILLEGAL_PARAMETER;
    UINT8               i;

    if (!p_char_id)
    {
        APPL_TRACE_ERROR0("deregistration failed, unknow char id");
        return status;
    }

    /* lock other GKI task */
    GKI_sched_lock();

    if ((p_clreg = bta_gattc_cl_get_regcb(client_if)) != NULL)
    {
        for (i = 0; i < BTA_GATTC_NOTIF_REG_MAX; i ++)
        {
            if (!p_clreg->notif_reg[i].in_use)
            {
                memset(&p_clreg->notif_reg, 0, sizeof(tBTA_GATTC_NOTIF_REG));

                p_clreg->notif_reg[i].in_use = TRUE;
                memcpy(p_clreg->notif_reg[i].remote_bda, bda, BD_ADDR_LEN);
                memcpy(&p_clreg->notif_reg[i].char_id, p_char_id, sizeof(tBTA_GATTC_CHAR_ID));

                status = BTA_GATT_OK;
                break;
            }
        }
        if (i == BTA_GATTC_NOTIF_REG_MAX)
        {
            status = BTA_GATT_NO_RESOURCES;
            APPL_TRACE_ERROR0("Max Notification Reached, registration failed.");
        }
    }
    else
    {
        APPL_TRACE_ERROR1("Client_if: %d Not Registered", client_if);
    }

    GKI_sched_unlock();

    return status;
}

/*******************************************************************************
**
** Function         BTA_GATTC_DeregisterForNotifications
**
** Description      This function is called to de-register for notification of a service.
**
** Parameters       client_if - client interface.
**                  bda - target GATT server.
**                  p_char_id - pointer to GATT characteristic ID.
**
** Returns          OK if deregistration succeed, otherwise failed.
**
*******************************************************************************/
tBTA_GATT_STATUS BTA_GATTC_DeregisterForNotifications (tBTA_GATTC_IF client_if,
                                                       BD_ADDR bda,
                                                       tBTA_GATTC_CHAR_ID *p_char_id)
{
    tBTA_GATTC_RCB      *p_clreg;
    tBTA_GATT_STATUS    status = BTA_GATT_ILLEGAL_PARAMETER;
    UINT8               i;

    if (!p_char_id)
    {
        APPL_TRACE_ERROR0("deregistration failed, unknow char id");
        return status;
    }

    /* lock other GKI task */
    GKI_sched_lock();

    if ((p_clreg = bta_gattc_cl_get_regcb(client_if)) != NULL)
    {
        for (i = 0; i < BTA_GATTC_NOTIF_REG_MAX; i ++)
        {
            if (p_clreg->notif_reg[i].in_use &&
                !memcmp(p_clreg->notif_reg[i].remote_bda, bda, BD_ADDR_LEN) &&
                !memcmp(&p_clreg->notif_reg[i].char_id, p_char_id, sizeof(tBTA_GATTC_CHAR_ID)))
            {
                APPL_TRACE_DEBUG0("Deregistered.");

                memset(&p_clreg->notif_reg[i], 0, sizeof(tBTA_GATTC_NOTIF_REG));
                status = BTA_GATT_OK;
                break;
            }
        }
        if (i == BTA_GATTC_NOTIF_REG_MAX)
        {
            status = BTA_GATT_ERROR;

            APPL_TRACE_ERROR0("registration not found");
        }
    }
    else
    {
        APPL_TRACE_ERROR1("Client_if: %d Not Registered", client_if);
    }

    GKI_sched_unlock();

    return status;
}

#endif /* BTA_GATT_INCLUDED */
