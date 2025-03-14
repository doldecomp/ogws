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
 *  this file contains GATT database building and query functions
 *
 ******************************************************************************/

#include "bt_target.h"

#if BLE_INCLUDED == TRUE

#include "bt_trace.h"

#include <stdio.h>
#include <string.h>
#include "gatt_int.h"
#include "l2c_api.h"

/********************************************************************************
**              L O C A L    F U N C T I O N     P R O T O T Y P E S            *
*********************************************************************************/
static BOOLEAN allocate_svc_db_buf(tGATT_SVC_DB *p_db);
static void *allocate_attr_in_db(tGATT_SVC_DB *p_db, UINT16 uuid16, UINT8 *p_uuid128, tGATT_PERM perm);
static BOOLEAN deallocate_attr_in_db(tGATT_SVC_DB *p_db, void *p_attr);
static BOOLEAN copy_extra_byte_in_db(tGATT_SVC_DB *p_db, void **p_dst, UINT16 len);

static void gatts_db_add_service_declaration(tGATT_SVC_DB *p_db, tBT_UUID service, BOOLEAN is_pri);
static tGATT_STATUS gatts_send_app_read_request(tGATT_TCB *p_tcb, UINT8 op_code,
                                                UINT16 handle, UINT16 offset, UINT32 trans_id);

/*******************************************************************************
**
** Function         gatts_init_service_db
**
** Description      This function initialize a memory space to be a service database.
**
** Parameter        p_db: database pointer.
**                  len: size of the memory space.
**
** Returns          Status of te operation.
**
*******************************************************************************/
BOOLEAN gatts_init_service_db (tGATT_SVC_DB *p_db, tBT_UUID service,  BOOLEAN is_pri,
                               UINT16 s_hdl, UINT16 num_handle)
{
    if (!allocate_svc_db_buf(p_db))
    {
        GATT_TRACE_ERROR0("gatts_init_service_db failed, no resources");
        return FALSE;
    }

    GATT_TRACE_DEBUG0("gatts_init_service_db");
    GATT_TRACE_DEBUG2("s_hdl = %d num_handle = %d", s_hdl, num_handle );

    /* update service database information */
    p_db->next_handle   = s_hdl;
    p_db->end_handle    = s_hdl + num_handle;

    gatts_db_add_service_declaration(p_db, service, is_pri);

    return TRUE;
}

/*******************************************************************************
**
** Function         gatts_init_service_db
**
** Description      This function initialize a memory space to be a service database.
**
** Parameter        p_db: database pointer.
**                  len: size of the memory space.
**
** Returns          Status of te operation.
**
*******************************************************************************/
tBT_UUID * gatts_get_service_uuid (tGATT_SVC_DB *p_db)
{
    if (!p_db || !p_db->p_attr_list)
    {
        GATT_TRACE_ERROR0("service DB empty");

        return NULL;
    }
    else
    {
        return &((tGATT_ATTR16 *)p_db->p_attr_list)->p_value->uuid;
    }
}

/*******************************************************************************
**
** Function         gatts_check_attr_readability
**
** Description      check attribute readability
**
** Returns          status of operation.
**
*******************************************************************************/
static tGATT_STATUS gatts_check_attr_readability(tGATT_ATTR16 *p_attr,
                                                 UINT16 offset,
                                                 BOOLEAN read_long,
                                                 tGATT_SEC_FLAG sec_flag,
                                                 UINT8 key_size)
{
    UINT16          min_key_size;
    tGATT_PERM      perm = p_attr->permission;

    min_key_size = (((perm & GATT_ENCRYPT_KEY_SIZE_MASK) >> 12));
    if (min_key_size != 0 )
    {
        min_key_size +=6;
    }

    if (!(perm & GATT_READ_ALLOWED))
    {
        GATT_TRACE_ERROR0( "GATT_READ_NOT_PERMIT");
        return GATT_READ_NOT_PERMIT;
    }

    if ((perm & GATT_READ_AUTH_REQUIRED ) && !(sec_flag & GATT_SEC_FLAG_LKEY_UNAUTHED))
    {
        GATT_TRACE_ERROR0( "GATT_INSUF_AUTHENTICATION");
        return GATT_INSUF_AUTHENTICATION;
    }

    if ((perm & GATT_READ_MITM_REQUIRED ) && !(sec_flag & GATT_SEC_FLAG_LKEY_AUTHED))
    {
        GATT_TRACE_ERROR0( "GATT_INSUF_AUTHENTICATION: MITM Required");
        return GATT_INSUF_AUTHENTICATION;
    }

    if ((perm & GATT_READ_ENCRYPTED_REQUIRED ) && !(sec_flag & GATT_SEC_FLAG_ENCRYPTED))
    {
        GATT_TRACE_ERROR0( "GATT_INSUF_ENCRYPTION");
        return GATT_INSUF_ENCRYPTION;
    }

    if ( (perm & GATT_READ_ENCRYPTED_REQUIRED) && (sec_flag & GATT_SEC_FLAG_ENCRYPTED) && (key_size < min_key_size))
    {
        GATT_TRACE_ERROR0( "GATT_INSUF_KEY_SIZE");
        return GATT_INSUF_KEY_SIZE;
    }


    if (read_long)
    {
        switch (p_attr->uuid)
        {
            case GATT_UUID_PRI_SERVICE:
            case GATT_UUID_SEC_SERVICE:
            case GATT_UUID_CHAR_DECLARE:
            case GATT_UUID_INCLUDE_SERVICE:
            case GATT_UUID_CHAR_EXT_PROP:
            case GATT_UUID_CHAR_CLIENT_CONFIG:
            case GATT_UUID_CHAR_SRVR_CONFIG:
            case GATT_UUID_CHAR_PRESENT_FORMAT:
                GATT_TRACE_ERROR0("GATT_NOT_LONG");
                return GATT_NOT_LONG;

            default:
                break;
        }
    }

    return GATT_SUCCESS;
}

/*******************************************************************************
**
** Function         read_attr_value
**
** Description      Utility function to read an attribute value.
**
** Parameter        p_attr: pointer to the attribute to read.
**                  offset: read offset.
**                  p_value: output parameter to carry out the attribute value.
**                  p_len: output parameter to carry out the attribute length.
**                  read_long: this is a read blob request.
**                  mtu: MTU
**                  sec_flag: current link security status.
**                  key_size: encryption key size.
**
** Returns          status of operation.
**
*******************************************************************************/
static tGATT_STATUS read_attr_value (void *p_attr,
                                     UINT16 offset,
                                     UINT8 **p_data,
                                     BOOLEAN read_long,
                                     UINT16 mtu,
                                     UINT16 *p_len,
                                     tGATT_SEC_FLAG sec_flag,
                                     UINT8 key_size)
{
    UINT16          len = 0, uuid16 = 0;
    UINT8           *p = *p_data;
    tGATT_STATUS    status;
    UINT16          read_long_uuid=0;
    tGATT_ATTR16    *p_attr16  = (tGATT_ATTR16  *)p_attr;

    GATT_TRACE_DEBUG5("read_attr_value uuid=0x%04x perm=0x%0x sec_flag=0x%x offset=%d read_long=%d",
                      p_attr16->uuid,
                      p_attr16->permission,
                      sec_flag,
                      offset,
                      read_long);

    status = gatts_check_attr_readability((tGATT_ATTR16 *)p_attr, offset, read_long, sec_flag, key_size);

    if (p_attr16->uuid_type == GATT_ATTR_UUID_TYPE_16)
        uuid16 = p_attr16->uuid;

    if (status != GATT_SUCCESS)
        return status;

    status = GATT_NO_RESOURCES;

    if (read_long &&
        (uuid16 == GATT_UUID_CHAR_DESCRIPTION || uuid16 == GATT_UUID_CHAR_AGG_FORMAT))
    {
        read_long_uuid = p_attr16->uuid;
    }

    if (uuid16 == GATT_UUID_PRI_SERVICE || uuid16 == GATT_UUID_SEC_SERVICE)
    {
        len = p_attr16->p_value->uuid.len;
        if (mtu >= p_attr16->p_value->uuid.len)
        {
            gatt_build_uuid_to_stream(&p, p_attr16->p_value->uuid);
            status = GATT_SUCCESS;
        }
    }
    else if (uuid16 == GATT_UUID_CHAR_DECLARE)
    {
        len = (((tGATT_ATTR16 *)(p_attr16->p_next))->uuid_type == GATT_ATTR_UUID_TYPE_16) ? 5 :19;

        if (mtu >= len)
        {
            UINT8_TO_STREAM(p, p_attr16->p_value->char_decl.property);
            UINT16_TO_STREAM(p, p_attr16->p_value->char_decl.char_val_handle);

            if (((tGATT_ATTR16 *)(p_attr16->p_next))->uuid_type == GATT_ATTR_UUID_TYPE_16)
            {
                UINT16_TO_STREAM(p, ((tGATT_ATTR16 *)(p_attr16->p_next))->uuid);
            }
            else
            {
                ARRAY_TO_STREAM (p, ((tGATT_ATTR128 *)(p_attr16->p_next))->uuid, LEN_UUID_128);
            }
            status = GATT_SUCCESS;
        }

    }
    else if (uuid16 == GATT_UUID_INCLUDE_SERVICE)
    {
        len = (p_attr16->p_value->incl_handle.service_type.len == 2) ? 6 : 4;
        if (mtu >= len)
        {
            UINT16_TO_STREAM(p, p_attr16->p_value->incl_handle.s_handle);
            UINT16_TO_STREAM(p, p_attr16->p_value->incl_handle.e_handle);

            if (p_attr16->p_value->incl_handle.service_type.len == 2)
            {
                UINT16_TO_STREAM(p, p_attr16->p_value->incl_handle.service_type.uu.uuid16);
            }
            status = GATT_SUCCESS;
        }
    }
    else /* characteristic description or characteristic value */
    {
        status = GATT_PENDING;
    }

    *p_len = len;
    *p_data = p;
    return status;
}

/*******************************************************************************
**
** Function         gatts_db_read_attr_value_by_type
**
** Description      Query attribute value by attribute type.
**
** Parameter        p_db: pointer to the attribute database.
**                  p_rsp: Read By type response data.
**                  s_handle: starting handle of the range we are looking for.
**                  e_handle: ending handle of the range we are looking for.
**                  type: Attribute type.
**                  mtu: MTU.
**                  sec_flag: current link security status.
**                  key_size: encryption key size.
**
** Returns          Status of the operation.
**
*******************************************************************************/
tGATT_STATUS gatts_db_read_attr_value_by_type (tGATT_TCB   *p_tcb,
                                               tGATT_SVC_DB    *p_db,
                                               UINT8        op_code,
                                               BT_HDR      *p_rsp,
                                               UINT16       s_handle,
                                               UINT16       e_handle,
                                               tBT_UUID     type,
                                               UINT16      *p_len,
                                               tGATT_SEC_FLAG sec_flag,
                                               UINT8        key_size,
                                               UINT32       trans_id,
                                               UINT16       *p_cur_handle)
{
    tGATT_STATUS status = GATT_NOT_FOUND;
    tGATT_ATTR16  *p_attr;
    UINT16      len = 0;
    UINT8       *p = (UINT8 *)(p_rsp + 1) + p_rsp->len + L2CAP_MIN_OFFSET;
    tBT_UUID    attr_uuid;

    if (p_db && p_db->p_attr_list)
    {
        p_attr = (tGATT_ATTR16 *)p_db->p_attr_list;

        while (p_attr && p_attr->handle <= e_handle)
        {
            if (p_attr->uuid_type == GATT_ATTR_UUID_TYPE_16)
            {
                attr_uuid.len = LEN_UUID_16;
                attr_uuid.uu.uuid16 = p_attr->uuid;
            }
            else
            {
                attr_uuid.len = LEN_UUID_128;
                memcpy(attr_uuid.uu.uuid128, ((tGATT_ATTR128 *)p_attr)->uuid, LEN_UUID_128);
            }

            if (p_attr->handle >= s_handle && gatt_uuid_compare(type, attr_uuid))
            {
                if (*p_len <= 2)
                {
                    status = GATT_NO_RESOURCES;
                    break;
                }

                UINT16_TO_STREAM (p, p_attr->handle);

                status = read_attr_value ((void *)p_attr, 0, &p, FALSE, (UINT16)(*p_len -2), &len, sec_flag, key_size);

                if (status == GATT_PENDING)
                {
                    status = gatts_send_app_read_request(p_tcb, op_code, p_attr->handle, 0, trans_id);

                    /* one callback at a time */
                    break;
                }
                else if (status == GATT_SUCCESS)
                {
                    if (p_rsp->offset == 0)
                        p_rsp->offset = len + 2;

                    if (p_rsp->offset == len + 2)
                    {
                        p_rsp->len += (len  + 2);
                        *p_len -= (len + 2);
                    }
                    else
                    {
                        GATT_TRACE_ERROR0("format mismatch");
                        status = GATT_NO_RESOURCES;
                        break;
                    }
                }
                else
                {
                    *p_cur_handle = p_attr->handle;
                    break;
                }
            }
            p_attr = (tGATT_ATTR16 *)p_attr->p_next;
        }
    }

    return status;
}

/*******************************************************************************
**
** Function         gatts_add_included_service
**
** Description      This function adds an included service into a database.
**
** Parameter        p_db: database pointer.
**                  inc_srvc_type: included service type.
**
** Returns          Status of the operation.
**
*******************************************************************************/
UINT16 gatts_add_included_service (tGATT_SVC_DB *p_db, UINT16 s_handle, UINT16 e_handle,
                                   tBT_UUID service)
{
    tGATT_ATTR16      *p_attr;

    GATT_TRACE_DEBUG3("gatts_add_included_service: s_hdl = 0x%04x e_hdl = 0x%04x uuid = 0x%04x",
                      s_handle, e_handle, service.uu.uuid16);

    if (service.len == 0 || s_handle == 0 || e_handle == 0)
    {
        GATT_TRACE_ERROR0("gatts_add_included_service Illegal Params.");
        return 0;
    }

    if ((p_attr = (tGATT_ATTR16 *) allocate_attr_in_db(p_db, GATT_UUID_INCLUDE_SERVICE, NULL, GATT_PERM_READ)) != NULL)
    {
        if (copy_extra_byte_in_db(p_db, (void **)&p_attr->p_value, sizeof(tGATT_INCL_SRVC)))
        {
            p_attr->p_value->incl_handle.s_handle = s_handle;
            p_attr->p_value->incl_handle.e_handle = e_handle;
            memcpy(&p_attr->p_value->incl_handle.service_type, &service, sizeof(tBT_UUID));

            return p_attr->handle;
        }
        else
        {
            deallocate_attr_in_db(p_db, p_attr);
        }
    }

    return 0;
}

/*******************************************************************************
**
** Function         gatts_add_characteristic
**
** Description      This function add a characteristics and its descriptor into
**                  a servce identified by the service database pointer.
**
** Parameter        p_db: database pointer.
**                  perm: permission (authentication and key size requirements)
**                  property: property of the characteristic.
**                  p_char: characteristic value information.
**
** Returns          Status of te operation.
**
*******************************************************************************/
UINT16 gatts_add_characteristic (tGATT_SVC_DB *p_db, tGATT_PERM perm,
                                 tGATT_CHAR_PROP property,
                                 tBT_UUID * p_char_uuid)
{
    tGATT_ATTR16     *p_char_decl, *p_char_val;
    UINT16          uuid16 = (p_char_uuid->len == LEN_UUID_16) ? p_char_uuid->uu.uuid16 : 0;

    GATT_TRACE_DEBUG2("gatts_add_characteristic perm=0x%0x property=0x%0x", perm, property);

    if ((p_char_decl = (tGATT_ATTR16 *)allocate_attr_in_db(p_db, GATT_UUID_CHAR_DECLARE, NULL, GATT_PERM_READ)) != NULL)
    {
        if (!copy_extra_byte_in_db(p_db, (void **)&p_char_decl->p_value, sizeof(tGATT_CHAR_DECL)))
        {
            deallocate_attr_in_db(p_db, p_char_decl);
            return 0;
        }

        p_char_val = (tGATT_ATTR16 *)allocate_attr_in_db(p_db, uuid16, p_char_uuid->uu.uuid128, perm);

        if (p_char_val == NULL)
        {
            deallocate_attr_in_db(p_db, p_char_decl);
            return 0;
        }

        p_char_decl->p_value->char_decl.property = property;
        p_char_decl->p_value->char_decl.char_val_handle  = p_char_val->handle;

        p_char_val->p_value = NULL;

        return p_char_val->handle;
    }

    return 0;
}

/*******************************************************************************
**
** Function         gatt_convertchar_descr_type
**
** Description      This function convert a char descript UUID into descriptor type.
**
** Returns          descriptor type.
**
*******************************************************************************/
UINT8 gatt_convertchar_descr_type(tBT_UUID *p_descr_uuid)
{
    tBT_UUID std_descr = {LEN_UUID_16, {GATT_UUID_CHAR_EXT_PROP}};

    if (gatt_uuid_compare(std_descr, * p_descr_uuid))
        return GATT_DESCR_EXT_DSCPTOR;

    std_descr.uu.uuid16 ++;
    if (gatt_uuid_compare(std_descr,  * p_descr_uuid))
        return GATT_DESCR_USER_DSCPTOR;

    std_descr.uu.uuid16 ++;
    if (gatt_uuid_compare(std_descr,  * p_descr_uuid))
        return GATT_DESCR_CLT_CONFIG;

    std_descr.uu.uuid16 ++;
    if (gatt_uuid_compare(std_descr,  * p_descr_uuid))
        return GATT_DESCR_SVR_CONFIG;

    std_descr.uu.uuid16 ++;
    if (gatt_uuid_compare(std_descr,  * p_descr_uuid))
        return GATT_DESCR_PRES_FORMAT;

    std_descr.uu.uuid16 ++;
    if (gatt_uuid_compare(std_descr,  * p_descr_uuid))
        return GATT_DESCR_AGGR_FORMAT;

    std_descr.uu.uuid16 ++;
    if (gatt_uuid_compare(std_descr,  * p_descr_uuid))
        return GATT_DESCR_VALID_RANGE;


    return GATT_DESCR_UNKNOWN;
}

/*******************************************************************************
**
** Function         gatts_add_char_descr
**
** Description      This function add a characteristics descriptor.
**
** Parameter        p_db: database pointer.
**                  perm: characteristic descriptor permission type.
**                  char_dscp_tpye: the characteristic descriptor masks.
**                  p_dscp_params: characteristic descriptors values.
**
** Returns          Status of the operation.
**
*******************************************************************************/
UINT16 gatts_add_char_descr (tGATT_SVC_DB *p_db, tGATT_PERM perm,
                             tBT_UUID *     p_descr_uuid)
{
    tGATT_ATTR16    *p_char_dscptr;
    UINT16    uuid16  = (p_descr_uuid->len == LEN_UUID_16)? p_descr_uuid->uu.uuid16 : 0;

    GATT_TRACE_DEBUG1("gatts_add_char_descr uuid=0x%04x", p_descr_uuid->uu.uuid16);

    /* Add characteristic descriptors */
    if ((p_char_dscptr = (tGATT_ATTR16 *)allocate_attr_in_db(p_db,
                                                             uuid16,
                                                             p_descr_uuid->uu.uuid128,
                                                             perm))
        == NULL)
    {
        GATT_TRACE_DEBUG0("gatts_add_char_descr Fail for adding char descriptors.");
        return 0;
    }
    else
    {
        return p_char_dscptr->handle;
    }
}

/*******************************************************************************/
/* Service Attribute Database Query Utility Functions */
/*******************************************************************************/
/*******************************************************************************
**
** Function         gatts_read_attr_value_by_handle
**
** Description      Query attribute value by attribute handle.
**
** Parameter        p_db: pointer to the attribute database.
**                  handle: Attribute handle to read.
**                  offset: Read offset.
**                  p_value: output parameter to carry out the attribute value.
**                  p_len: output parameter as attribute length read.
**                  read_long: this is a read blob request.
**                  mtu: MTU.
**                  sec_flag: current link security status.
**                  key_size: encryption key size
**
** Returns          Status of operation.
**
*******************************************************************************/
tGATT_STATUS gatts_read_attr_value_by_handle(tGATT_TCB *p_tcb,
                                             tGATT_SVC_DB *p_db,
                                             UINT8 op_code,
                                             UINT16 handle, UINT16 offset,
                                             UINT8 *p_value, UINT16 *p_len,
                                             UINT16 mtu,
                                             tGATT_SEC_FLAG sec_flag,
                                             UINT8 key_size,
                                             UINT32 trans_id)
{
    tGATT_STATUS status = GATT_NOT_FOUND;
    tGATT_ATTR16  *p_attr;
    UINT8       *pp = p_value;

    if (p_db && p_db->p_attr_list)
    {
        p_attr = (tGATT_ATTR16 *)p_db->p_attr_list;

        while (p_attr && handle >= p_attr->handle)
        {
            if (p_attr->handle == handle)
            {
                status = read_attr_value (p_attr, offset, &pp,
                                          (BOOLEAN)(op_code == GATT_REQ_READ_BLOB),
                                          mtu, p_len, sec_flag, key_size);

                if (status == GATT_PENDING)
                {
                    status = gatts_send_app_read_request(p_tcb, op_code, p_attr->handle, offset, trans_id);
                }
                break;
            }
            p_attr = (tGATT_ATTR16 *)p_attr->p_next;
        }
    }

    return status;
}

/*******************************************************************************
**
** Function         gatts_read_attr_perm_check
**
** Description      Check attribute readability.
**
** Parameter        p_db: pointer to the attribute database.
**                  handle: Attribute handle to read.
**                  offset: Read offset.
**                  p_value: output parameter to carry out the attribute value.
**                  p_len: output parameter as attribute length read.
**                  read_long: this is a read blob request.
**                  mtu: MTU.
**                  sec_flag: current link security status.
**                  key_size: encryption key size
**
** Returns          Status of operation.
**
*******************************************************************************/
tGATT_STATUS gatts_read_attr_perm_check(tGATT_SVC_DB *p_db,
                                        BOOLEAN is_long,
                                        UINT16 handle,
                                        tGATT_SEC_FLAG sec_flag,
                                        UINT8 key_size)
{
    tGATT_STATUS status = GATT_NOT_FOUND;
    tGATT_ATTR16  *p_attr;

    if (p_db && p_db->p_attr_list)
    {
        p_attr = (tGATT_ATTR16 *)p_db->p_attr_list;

        while (p_attr && handle >= p_attr->handle)
        {
            if (p_attr->handle == handle)
            {
                status = gatts_check_attr_readability (p_attr, 0,
                                                       is_long,
                                                       sec_flag, key_size);
                break;
            }
            p_attr = (tGATT_ATTR16 *) p_attr->p_next;
        }
    }

    return status;
}
/*******************************************************************************
**
** Function         gatts_write_attr_perm_check
**
** Description      Write attribute value into database.
**
** Parameter        p_db: pointer to the attribute database.
**                  op_code:op code of this write.
**                  handle: handle of the attribute to write.
**                  offset: Write offset if write op code is write blob.
**                  p_data: Attribute value to write.
**                  len: attribute data length.
**                  sec_flag: current link security status.
**                  key_size: encryption key size
**
** Returns          Status of the operation.
**
*******************************************************************************/
tGATT_STATUS gatts_write_attr_perm_check (tGATT_SVC_DB *p_db, UINT8 op_code,
                                          UINT16 handle, UINT16 offset, UINT8 *p_data,
                                          UINT16 len, tGATT_SEC_FLAG sec_flag, UINT8 key_size)
{
    tGATT_STATUS    status = GATT_NOT_FOUND;
    tGATT_ATTR16    *p_attr;
    UINT16          max_size = 0;
    tGATT_PERM      perm;
    UINT16          min_key_size;

    GATT_TRACE_DEBUG6( "gatts_write_attr_perm_check op_code=0x%0x handle=0x%04x offset=%d len=%d sec_flag=0x%0x key_size=%d",
                       op_code, handle, offset, len, sec_flag, key_size);

    if (p_db != NULL)
    {
        p_attr = (tGATT_ATTR16 *) p_db->p_attr_list;

        while (p_attr != NULL)
        {
            if (p_attr->handle == handle)
            {
                perm = p_attr->permission;
                min_key_size = (((perm & GATT_ENCRYPT_KEY_SIZE_MASK) >> 12));
                if (min_key_size != 0 )
                {
                    min_key_size +=6;
                }
                GATT_TRACE_DEBUG2( "gatts_write_attr_perm_check p_attr->permission =0x%04x min_key_size==0x%04x",
                                   p_attr->permission,
                                   min_key_size);

                if ((op_code == GATT_CMD_WRITE) && (perm & GATT_WRITE_SIGNED_PERM) )
                {
                    /* use the rules for the mixed security see section 10.2.3*/
                    if (perm & GATT_PERM_WRITE_SIGNED)
                    {
                        perm = GATT_PERM_WRITE_ENCRYPTED;
                    }
                    else
                    {
                        perm = GATT_PERM_WRITE_ENC_MITM;
                    }
                }

                if ((op_code == GATT_SIGN_CMD_WRITE) && !(perm & GATT_WRITE_SIGNED_PERM))
                {
                    status = GATT_WRITE_NOT_PERMIT;
                    GATT_TRACE_DEBUG0( "gatts_write_attr_perm_check - sign cmd write not allowed");
                }
                 if ((op_code == GATT_SIGN_CMD_WRITE) && (sec_flag & GATT_SEC_FLAG_ENCRYPTED))
                {
                    status = GATT_INVALID_PDU;
                    GATT_TRACE_ERROR0( "gatts_write_attr_perm_check - Error!! sign cmd write sent on a encypted link");
                }
                else if (!(perm & GATT_WRITE_ALLOWED))
                {
                    status = GATT_WRITE_NOT_PERMIT;
                    GATT_TRACE_ERROR0( "gatts_write_attr_perm_check - GATT_WRITE_NOT_PERMIT");
                }
                else if ((perm & GATT_WRITE_AUTH_REQUIRED ) && !(sec_flag & GATT_SEC_FLAG_LKEY_UNAUTHED))
                {
                    status = GATT_INSUF_AUTHENTICATION;
                    GATT_TRACE_ERROR0( "gatts_write_attr_perm_check - GATT_INSUF_AUTHENTICATION");
                }
                else if ((perm & GATT_WRITE_MITM_REQUIRED ) && !(sec_flag & GATT_SEC_FLAG_LKEY_AUTHED))
                {
                    status = GATT_INSUF_AUTHENTICATION;
                    GATT_TRACE_ERROR0( "gatts_write_attr_perm_check - GATT_INSUF_AUTHENTICATION: MITM required");
                }
                else if ((perm & GATT_WRITE_ENCRYPTED_PERM ) && !(sec_flag & GATT_SEC_FLAG_ENCRYPTED))
                {
                    status = GATT_INSUF_ENCRYPTION;
                    GATT_TRACE_ERROR0( "gatts_write_attr_perm_check - GATT_INSUF_ENCRYPTION");
                }
                else if ((perm & GATT_WRITE_ENCRYPTED_PERM ) && (sec_flag & GATT_SEC_FLAG_ENCRYPTED) && (key_size < min_key_size))
                {
                    status = GATT_INSUF_KEY_SIZE;
                    GATT_TRACE_ERROR0( "gatts_write_attr_perm_check - GATT_INSUF_KEY_SIZE");
                }
                else /* writable: must be char value declaration or char descritpors */
                {
                    if(p_attr->uuid_type == GATT_ATTR_UUID_TYPE_16)
                    {
                    switch (p_attr->uuid)
                    {
                        case GATT_UUID_CHAR_PRESENT_FORMAT:/* should be readable only */
                        case GATT_UUID_CHAR_EXT_PROP:/* should be readable only */
                        case GATT_UUID_CHAR_AGG_FORMAT: /* should be readable only */
                            case GATT_UUID_CHAR_VALID_RANGE:
                            status = GATT_WRITE_NOT_PERMIT;
                            break;

                        case GATT_UUID_CHAR_CLIENT_CONFIG:
                        case GATT_UUID_CHAR_SRVR_CONFIG:
                            max_size = 2;
                        case GATT_UUID_CHAR_DESCRIPTION:
                        default: /* any other must be character value declaration */
                            status = GATT_SUCCESS;
                            break;
                        }
                    }
                    else if (p_attr->uuid_type == GATT_ATTR_UUID_TYPE_128)
                    {
                         status = GATT_SUCCESS;
                    }
                    else
                    {
                        status = GATT_INVALID_PDU;
                    }

                    if (p_data == NULL && len  > 0)
                    {
                        status = GATT_INVALID_PDU;
                    }
                    /* these attribute does not allow write blob */
// btla-specific ++
                    else if ( (p_attr->uuid_type == GATT_ATTR_UUID_TYPE_16) &&
                              (p_attr->uuid == GATT_UUID_CHAR_CLIENT_CONFIG ||
                               p_attr->uuid == GATT_UUID_CHAR_SRVR_CONFIG) )
// btla-specific --
                    {
                        if (op_code == GATT_REQ_PREPARE_WRITE && offset != 0) /* does not allow write blob */
                        {
                            status = GATT_NOT_LONG;
                            GATT_TRACE_ERROR0( "gatts_write_attr_perm_check - GATT_NOT_LONG");
                        }
                        else if (len != max_size)    /* data does not match the required format */
                        {
                            status = GATT_INVALID_PDU;
                            GATT_TRACE_ERROR0( "gatts_write_attr_perm_check - GATT_INVALID_PDU");
                        }
                        else
                        {
                            status = GATT_SUCCESS;
                        }
                    }
                }
                break;
            }
            else
                p_attr = (tGATT_ATTR16 *)p_attr->p_next;
        }
    }

    return status;
}

/*******************************************************************************
**
** Function         allocate_attr_in_db
**
** Description      Allocate a memory space for a new attribute, and link this
**                  attribute into the database attribute list.
**
**
** Parameter        p_db    : database pointer.
**                  service : type of attribute to be added.
**
** Returns          pointer to the newly allocated attribute.
**
*******************************************************************************/
static void *allocate_attr_in_db(tGATT_SVC_DB *p_db, UINT16 uuid16, UINT8 *uuid128, tGATT_PERM perm)
{
    tGATT_ATTR16    *p_attr16 = NULL, *p_last;
    tGATT_ATTR128   *p_attr128 = NULL;
    UINT16      len = (uuid16 == 0) ? sizeof(tGATT_ATTR128): sizeof(tGATT_ATTR16);

    GATT_TRACE_DEBUG1("allocate attr %d bytes ",len);

    if (uuid16 == GATT_ILLEGAL_UUID && uuid128 == NULL)
    {
        GATT_TRACE_ERROR0("illegal UUID");
        return NULL;
    }

    if (p_db->end_handle <= p_db->next_handle)
    {
        GATT_TRACE_DEBUG2("handle space full. handle_max = %d next_handle = %d",
                          p_db->end_handle, p_db->next_handle);
        return NULL;
    }

    if (p_db->mem_free < len)
    {
        if (!allocate_svc_db_buf(p_db))
        {
            GATT_TRACE_ERROR0("allocate_attr_in_db failed, no resources");
            return NULL;
        }
    }

    p_attr16 = (tGATT_ATTR16 *) p_db->p_free_mem;
    p_attr128 = (tGATT_ATTR128 *) p_db->p_free_mem;

    memset(p_attr16, 0, len);

    if (uuid16 != GATT_ILLEGAL_UUID)
    {
        p_attr16->uuid_type = GATT_ATTR_UUID_TYPE_16;
        p_attr16->uuid = uuid16;
    }
    else
    {
        p_attr128->uuid_type = GATT_ATTR_UUID_TYPE_128;
        memcpy(p_attr128->uuid, uuid128, LEN_UUID_128);
    }

    p_db->p_free_mem += len;
    p_db->mem_free -= len;

    p_attr16->handle = p_db->next_handle++;
    p_attr16->permission = perm;
    p_attr16->p_next = NULL;

    /* link the attribute record into the end of DB */
    if (p_db->p_attr_list == NULL)
        p_db->p_attr_list = p_attr16;
    else
    {
        p_last = (tGATT_ATTR16 *)p_db->p_attr_list;

        while (p_last != NULL && p_last->p_next != NULL)
            p_last = (tGATT_ATTR16 *)p_last->p_next;

        p_last->p_next = p_attr16;
    }

    if (p_attr16->uuid_type == GATT_ATTR_UUID_TYPE_16)
    {
        GATT_TRACE_DEBUG3("=====> handle = [0x%04x] uuid = [0x%04x] perm=0x%02x ",
                          p_attr16->handle, p_attr16->uuid, p_attr16->permission);
    }
    else
    {
        GATT_TRACE_DEBUG4("=====> handle = [0x%04x] uuid128 = [0x%02x:0x%02x] perm=0x%02x ",
                          p_attr128->handle, p_attr128->uuid[0],p_attr128->uuid[1],
                          p_attr128->permission);
    }
    return(void *)p_attr16;
}

/*******************************************************************************
**
** Function         deallocate_attr_in_db
**
** Description      Free an attribute within the database.
**
** Parameter        p_db: database pointer.
**                  p_attr: pointer to the attribute record to be freed.
**
** Returns          BOOLEAN: success
**
*******************************************************************************/
static BOOLEAN deallocate_attr_in_db(tGATT_SVC_DB *p_db, void *p_attr)
{
    tGATT_ATTR16  *p_cur, *p_next;
    BOOLEAN     found = FALSE;

    if (p_db->p_attr_list == NULL)
        return found;

    p_cur   = (tGATT_ATTR16 *) p_db->p_attr_list;
    p_next  = (tGATT_ATTR16 *) p_cur->p_next;

    for (; p_cur != NULL && p_next != NULL;
        p_cur = p_next, p_next = (tGATT_ATTR16 *)p_next->p_next)
    {
        if (p_next == p_attr)
        {
            p_cur->p_next = p_next->p_next;
            found = TRUE;
        }
    }
    if (p_cur == p_attr && p_cur == p_db->p_attr_list)
    {
        p_db->p_attr_list = p_cur->p_next;
        found = TRUE;
    }
    /* else attr not found */
    if ( found)
        p_db->next_handle --;

    return found;
}

/*******************************************************************************
**
** Function         copy_extra_byte_in_db
**
** Description      Utility function to allocate extra bytes memory in DB and copy
**                  the value from a source place.
**
**
** Parameter        p_db: database pointer.
**                  p_dst: destination data pointer.
**                  p_src: source data pointer.
**                  len: data length to be copied.
**
** Returns          None.
**
*******************************************************************************/
static BOOLEAN copy_extra_byte_in_db(tGATT_SVC_DB *p_db, void **p_dst, UINT16 len)
{
    UINT8 *p = (UINT8 *)*p_dst;

    if (p_db->mem_free < len)
    {
        if (!allocate_svc_db_buf(p_db))
        {
            GATT_TRACE_ERROR0("copy_extra_byte_in_db failed, no resources");
            return FALSE;
        }
    }

    p = p_db->p_free_mem;
    p_db->p_free_mem += len;
    p_db->mem_free -= len;
    memset((void *)p, 0, len);
    *p_dst = (void *)p;

    return TRUE;
}

/*******************************************************************************
**
** Function         allocate_svc_db_buf
**
** Description      Utility function to allocate extra buffer for service database.
**
** Returns          TRUE if allocation succeed, otherwise FALSE.
**
*******************************************************************************/
static BOOLEAN allocate_svc_db_buf(tGATT_SVC_DB *p_db)
{
    BT_HDR  *p_buf;

    GATT_TRACE_DEBUG0("allocate_svc_db_buf allocating extra buffer");

    if ((p_buf = (BT_HDR *)GKI_getpoolbuf(GATT_DB_POOL_ID)) == NULL)
    {
        GATT_TRACE_ERROR0("allocate_svc_db_buf failed, no resources");
        return FALSE;
    }

    memset(p_buf, 0, GKI_get_buf_size(p_buf));
    p_db->p_free_mem    = (UINT8 *) p_buf;
    p_db->mem_free      = GKI_get_buf_size(p_buf);

    GKI_enqueue(&p_db->svc_buffer, p_buf);

    return TRUE;

}

/*******************************************************************************
**
** Function         gatts_send_app_read_request
**
** Description      Send application read request callback
**
** Returns          status of operation.
**
*******************************************************************************/
static tGATT_STATUS gatts_send_app_read_request(tGATT_TCB *p_tcb, UINT8 op_code,
                                                UINT16 handle, UINT16 offset, UINT32 trans_id)
{
    tGATTS_DATA   sr_data;
    UINT8       i_rcb;
    tGATT_SR_REG *p_sreg;
    UINT16   conn_id;

    i_rcb = gatt_sr_find_i_rcb_by_handle(handle);
    p_sreg = &gatt_cb.sr_reg[i_rcb];
    conn_id = GATT_CREATE_CONN_ID(p_tcb->tcb_idx, p_sreg->gatt_if);

    if (trans_id == 0)
    {
        trans_id = gatt_sr_enqueue_cmd(p_tcb, op_code, handle);
        gatt_sr_update_cback_cnt(p_tcb, p_sreg->gatt_if, TRUE, TRUE);
    }

    if (trans_id != 0 )
    {
        memset(&sr_data, 0, sizeof(tGATTS_DATA));

        sr_data.read_req.handle = handle;
        sr_data.read_req.is_long = (BOOLEAN)(op_code == GATT_REQ_READ_BLOB);
        sr_data.read_req.offset = offset;

        gatt_sr_send_req_callback(conn_id,
                                  trans_id, GATTS_REQ_TYPE_READ, &sr_data);
        return(tGATT_STATUS) GATT_PENDING;
    }
    else
        return(tGATT_STATUS) GATT_BUSY; /* max pending command, application error */

}

/*******************************************************************************
**
** Function         gatts_db_add_service_declaration
**
** Description      Update a service database service declaration record.
**
** Parameter        p_db: database pointer.
**                  service: UUID of the service.
**
** Returns          void
**
*******************************************************************************/
static void gatts_db_add_service_declaration(tGATT_SVC_DB *p_db, tBT_UUID service, BOOLEAN is_pri)
{
    tGATT_ATTR16  *p_attr;
    UINT16      service_type = is_pri ? GATT_UUID_PRI_SERVICE: GATT_UUID_SEC_SERVICE;

    GATT_TRACE_DEBUG0( "add_service_declaration");

    /* add service declration record */
    if ((p_attr = (tGATT_ATTR16 *)(allocate_attr_in_db(p_db, service_type, NULL, GATT_PERM_READ))) != NULL)
    {
        if (copy_extra_byte_in_db (p_db, (void **)&p_attr->p_value, sizeof(tBT_UUID)))
        {
            memcpy (&p_attr->p_value->uuid, &service, sizeof(tBT_UUID));
        }
    }
}

#endif /* BLE_INCLUDED */
