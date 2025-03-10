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
 *  this file contains the main GATT client functions
 *
 ******************************************************************************/

#include "bt_target.h"

#if BLE_INCLUDED == TRUE

#include <string.h>
#include "gki.h"
#include "gatt_int.h"

#define GATT_WRITE_LONG_HDR_SIZE    5 /* 1 opcode + 2 handle + 2 offset */
#define GATT_READ_CHAR_VALUE_HDL    (GATT_READ_CHAR_VALUE | 0x80)
#define GATT_READ_INC_SRV_UUID128   (GATT_DISC_INC_SRVC   | 0x90)

/********************************************************************************
**                       G L O B A L      G A T T       D A T A                 *
*********************************************************************************/
void gatt_send_prepare_write(tGATT_TCB  *p_tcb, tGATT_CLCB *p_clcb);

UINT8   disc_type_to_att_opcode[GATT_DISC_MAX] =
{
    0,
    GATT_REQ_READ_BY_GRP_TYPE,     /*  GATT_DISC_SRVC_ALL = 1, */
    GATT_REQ_FIND_TYPE_VALUE,      /*  GATT_DISC_SRVC_BY_UUID,  */
    GATT_REQ_READ_BY_TYPE,         /*  GATT_DISC_INC_SRVC,      */
    GATT_REQ_READ_BY_TYPE,         /*  GATT_DISC_CHAR,          */
    GATT_REQ_FIND_INFO             /*  GATT_DISC_CHAR_DSCPT,    */
};

UINT16 disc_type_to_uuid[GATT_DISC_MAX] =
{
    0,                  /* reserved */
    GATT_UUID_PRI_SERVICE, /* <service> DISC_SRVC_ALL */
    GATT_UUID_PRI_SERVICE, /* <service> for DISC_SERVC_BY_UUID */
    GATT_UUID_INCLUDE_SERVICE, /* <include_service> for DISC_INC_SRVC */
    GATT_UUID_CHAR_DECLARE,   /* <characteristic> for DISC_CHAR */
    0                   /* no type filtering for DISC_CHAR_DSCPT */
};


/*******************************************************************************
**
** Function         gatt_act_discovery
**
** Description      GATT discovery operation.
**
** Returns          void.
**
*******************************************************************************/
void gatt_act_discovery(tGATT_CLCB *p_clcb)
{
    UINT8       op_code = disc_type_to_att_opcode[p_clcb->op_subtype];
    tGATT_CL_MSG   cl_req;

    if (p_clcb->s_handle <= p_clcb->e_handle && p_clcb->s_handle != 0)
    {
        memset(&cl_req, 0, sizeof(tGATT_CL_MSG));

        cl_req.browse.s_handle = p_clcb->s_handle;
        cl_req.browse.e_handle = p_clcb->e_handle;

        if (disc_type_to_uuid[p_clcb->op_subtype] != 0)
        {
            cl_req.browse.uuid.len = 2;
            cl_req.browse.uuid.uu.uuid16 = disc_type_to_uuid[p_clcb->op_subtype];
        }

        if (p_clcb->op_subtype == GATT_DISC_SRVC_BY_UUID) /* fill in the FindByTypeValue request info*/
        {
            cl_req.find_type_value.uuid.len = 2;
            cl_req.find_type_value.uuid.uu.uuid16 = disc_type_to_uuid[p_clcb->op_subtype];
            cl_req.find_type_value.s_handle = p_clcb->s_handle;
            cl_req.find_type_value.e_handle = p_clcb->e_handle;
            cl_req.find_type_value.value_len = p_clcb->uuid.len;
            memcpy (cl_req.find_type_value.value,  &p_clcb->uuid.uu, p_clcb->uuid.len);
        }

        if (attp_send_cl_msg(p_clcb->p_tcb, p_clcb->clcb_idx, op_code, &cl_req) !=  GATT_SUCCESS)
        {
            gatt_end_operation(p_clcb, GATT_ERROR, NULL);
        }
    }
    else /* end of handle range */
        gatt_end_operation(p_clcb, GATT_SUCCESS, NULL);
}

/*******************************************************************************
**
** Function         gatt_act_read
**
** Description      GATT read operation.
**
** Returns          void.
**
*******************************************************************************/
void gatt_act_read (tGATT_CLCB *p_clcb, UINT16 offset)
{
    tGATT_TCB  *p_tcb = p_clcb->p_tcb;
    UINT8   rt = GATT_INTERNAL_ERROR;
    tGATT_CL_MSG  msg;
    UINT8        op_code = 0;

    memset (&msg, 0, sizeof(tGATT_CL_MSG));

    switch (p_clcb->op_subtype)
    {
        case GATT_READ_CHAR_VALUE:
        case GATT_READ_BY_TYPE:
            op_code = GATT_REQ_READ_BY_TYPE;
            msg.browse.s_handle = p_clcb->s_handle;
            msg.browse.e_handle = p_clcb->e_handle;
            if (p_clcb->op_subtype == GATT_READ_BY_TYPE)
                memcpy(&msg.browse.uuid, &p_clcb->uuid, sizeof(tBT_UUID));
            else
            {
                msg.browse.uuid.len = LEN_UUID_16;
                msg.browse.uuid.uu.uuid16 = GATT_UUID_CHAR_DECLARE;
            }
            break;

        case GATT_READ_CHAR_VALUE_HDL:
        case GATT_READ_BY_HANDLE:
            if (!p_clcb->counter)
            {
                op_code = GATT_REQ_READ;
                msg.handle = p_clcb->s_handle;
            }
            else
            {
                if (!p_clcb->first_read_blob_after_read)
                    p_clcb->first_read_blob_after_read = TRUE;
                else
                    p_clcb->first_read_blob_after_read = FALSE;

                GATT_TRACE_DEBUG1("gatt_act_read first_read_blob_after_read=%d",
                                  p_clcb->first_read_blob_after_read);
                op_code = GATT_REQ_READ_BLOB;
                msg.read_blob.offset = offset;
                msg.read_blob.handle = p_clcb->s_handle;
            }
            p_clcb->op_subtype &= ~ 0x80;
            break;

        case GATT_READ_PARTIAL:
            op_code = GATT_REQ_READ_BLOB;
            msg.read_blob.handle = p_clcb->s_handle;
            msg.read_blob.offset = offset;
            break;

        case GATT_READ_MULTIPLE:
            op_code = GATT_REQ_READ_MULTI;
            memcpy (&msg.read_multi, p_clcb->p_attr_buf, sizeof(tGATT_READ_MULTI));
            break;

        case GATT_READ_INC_SRV_UUID128:
            op_code = GATT_REQ_READ;
            msg.handle = p_clcb->s_handle;
            p_clcb->op_subtype &= ~ 0x90;
            break;

        default:
            GATT_TRACE_ERROR1("Unknown read type: %d", p_clcb->op_subtype);
            break;
    }

    if ( op_code == 0 ||
         (rt = attp_send_cl_msg(p_tcb, p_clcb->clcb_idx, op_code, &msg)) != GATT_SUCCESS)
    {
        gatt_end_operation(p_clcb, rt, NULL);
    }
}

/*******************************************************************************
**
** Function         gatt_act_write
**
** Description      GATT write operation.
**
** Returns          void.
**
*******************************************************************************/
void gatt_act_write (tGATT_CLCB *p_clcb)
{
    tGATT_TCB           *p_tcb = p_clcb->p_tcb;
    UINT8               rt = GATT_SUCCESS, op_code;
    tGATT_VALUE         *p_attr = (tGATT_VALUE *)p_clcb->p_attr_buf;

    if (p_attr)
    {
        switch (p_clcb->op_subtype)
        {
            case GATT_WRITE_NO_RSP:
                p_clcb->s_handle = p_attr->handle;
                op_code = (p_tcb->sec_act & GATT_SEC_SIGN_DATA) ? GATT_SIGN_CMD_WRITE : GATT_CMD_WRITE;
                rt = gatt_send_write_msg(p_tcb,
                                         p_clcb->clcb_idx,
                                         op_code,
                                         p_attr->handle,
                                         p_attr->len,
                                         0,
                                         p_attr->value);
                break;

            case GATT_WRITE:
                if (p_attr->len <= (p_tcb->payload_size - GATT_HDR_SIZE))
                {
                    p_clcb->s_handle = p_attr->handle;

                    rt = gatt_send_write_msg(p_tcb,
                                             p_clcb->clcb_idx,
                                             GATT_REQ_WRITE,
                                             p_attr->handle,
                                             p_attr->len,
                                             0,
                                             p_attr->value);
                }
                else /* prepare write for long attribute */
                {
                    gatt_send_prepare_write(p_tcb, p_clcb);
                }
                break;

            case GATT_WRITE_PREPARE:
                gatt_send_prepare_write(p_tcb, p_clcb);
                break;

            default:
                rt = GATT_INTERNAL_ERROR;
                GATT_TRACE_ERROR1("Unknown write type: %d", p_clcb->op_subtype);
                break;
        }
    }
    else
        rt = GATT_INTERNAL_ERROR;

    if ((rt != GATT_SUCCESS  && rt != GATT_CMD_STARTED)
        || (rt != GATT_CMD_STARTED && p_clcb->op_subtype == GATT_WRITE_NO_RSP))
    {
        if (rt != GATT_SUCCESS)
        {
            GATT_TRACE_ERROR1("gatt_act_write() failed op_code=0x%x", op_code);
        }
        gatt_end_operation(p_clcb, rt, NULL);
    }
}
/*******************************************************************************
**
** Function         gatt_send_queue_write_cancel
**
** Description      send queue write cancel
**
** Returns          void.
**
*******************************************************************************/
void gatt_send_queue_write_cancel (tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, tGATT_EXEC_FLAG flag)
{
    UINT8       rt ;

    GATT_TRACE_DEBUG0("gatt_send_queue_write_cancel ");

    rt = attp_send_cl_msg(p_tcb, p_clcb->clcb_idx, GATT_REQ_EXEC_WRITE, (tGATT_CL_MSG *)&flag);

    if (rt != GATT_SUCCESS)
    {
        gatt_end_operation(p_clcb, rt, NULL);
    }
}
/*******************************************************************************
**
** Function         gatt_check_write_long_terminate
**
** Description      To terminate write long or not.
**
** Returns          TRUE: write long is terminated; FALSE keep sending.
**
*******************************************************************************/
BOOLEAN gatt_check_write_long_terminate(tGATT_TCB  *p_tcb, tGATT_CLCB *p_clcb, tGATT_VALUE *p_rsp_value)
{
    tGATT_VALUE         *p_attr = (tGATT_VALUE *)p_clcb->p_attr_buf;
    BOOLEAN             exec = FALSE;
    tGATT_EXEC_FLAG     flag = GATT_PREP_WRITE_EXEC;

    GATT_TRACE_DEBUG0("gatt_check_write_long_terminate ");
    /* check the first write response status */
    if (p_rsp_value != NULL)
    {
        if (p_rsp_value->handle != p_attr->handle ||
            p_rsp_value->len != p_clcb->counter ||
            memcmp(p_rsp_value->value, p_attr->value + p_attr->offset, p_rsp_value->len))
        {
            /* data does not match    */
            p_clcb->status = GATT_ERROR;
            flag = GATT_PREP_WRITE_CANCEL;
            exec = TRUE;
        }
        else /* response checking is good */
        {
            p_clcb->status = GATT_SUCCESS;
            /* update write offset and check if end of attribute value */
            if ((p_attr->offset += p_rsp_value->len) >= p_attr->len)
                exec = TRUE;
        }
    }
    if (exec)
    {
        gatt_send_queue_write_cancel (p_tcb, p_clcb, flag);
        return TRUE;
    }
    return FALSE;
}
/*******************************************************************************
**
** Function         gatt_send_prepare_write
**
** Description      Send prepare write.
**
** Returns          void.
**
*******************************************************************************/
void gatt_send_prepare_write(tGATT_TCB  *p_tcb, tGATT_CLCB *p_clcb)
{
    tGATT_VALUE  *p_attr = (tGATT_VALUE *)p_clcb->p_attr_buf;
    UINT16  to_send, offset;
    UINT8   rt = GATT_SUCCESS;
    UINT8   type = p_clcb->op_subtype;

    GATT_TRACE_DEBUG1("gatt_send_prepare_write type=0x%x", type );
    to_send = p_attr->len - p_attr->offset;

    if (to_send > (p_tcb->payload_size - GATT_WRITE_LONG_HDR_SIZE)) /* 2 = UINT16 offset bytes  */
        to_send = p_tcb->payload_size - GATT_WRITE_LONG_HDR_SIZE;

    p_clcb->s_handle = p_attr->handle;

    offset = p_attr->offset;
    if (type == GATT_WRITE_PREPARE)
    {
        offset += p_clcb->start_offset;
    }

    GATT_TRACE_DEBUG2("offset =0x%x len=%d", offset, to_send );

    rt = gatt_send_write_msg(p_tcb,
                             p_clcb->clcb_idx,
                             GATT_REQ_PREPARE_WRITE,
                             p_attr->handle,
                             to_send,                           /* length */
                             offset,                            /* used as offset */
                             p_attr->value + p_attr->offset);   /* data */

    /* remember the write long attribute length */
    p_clcb->counter = to_send;

    if (rt != GATT_SUCCESS )
    {
        gatt_end_operation(p_clcb, rt, NULL);
    }
}

/*******************************************************************************
**
** Function         gatt_proc_disc_read_by_type_rsp
**
** Description      This function process the read by type response and send another
**                  request if needed.
**
** Returns          void.
**
*******************************************************************************/
void gatt_proc_disc_read_by_type_rsp(tGATT_CLCB *p_clcb, UINT16 len, UINT8 *p_data)
{
    /*
      tGATT_TCB   *p_tcb = p_clcb->p_tcb;
      tGATT_DISCOVERY_DB  *p_db = p_clcb->p_disc_db;
      tGATT_DISC_REC      *p_rec;
      tGATT_STATUS         status = GATT_INTERNAL_ERROR;


      if ((p_rec = gatt_add_record(p_clcb->p_disc_db)) != NULL)
      {
          p_rec->handle   = handle;
          p_rec->type     = p_db->uuid_filter;
          p_rec->attr_len = len;

          // copy the attibute value into DB
          p_rec->p_value  = p_db->p_free_mem;
          memcpy(p_rec->p_value, p_value, len);
          p_db->p_free_mem += len;
          p_db->mem_free -= len;

          if (handle < p_clcb->e_handle)
          {
              // send another request
              if (gatt_act_send_browse(p_tcb, p_clcb->conn_id,
                                       GATT_REQ_READ_BY_TYPE,
                                       (UINT16)(handle + 1), // starting handle
                                       p_clcb->e_handle,              // end handle
                                       p_clcb->p_disc_db->uuid_filter) // uuid filter /
                          == GATT_SUCCESS)
              {
                  status = GATT_SUCCESS;
              }
          }
      }
      else
          status = GATT_DB_FULL;

      if (status != GATT_SUCCESS) // DB full
      {
          gatt_end_operation(p_clcb, status, NULL);
      }*/
}
/*******************************************************************************
**
** Function         gatt_process_find_type_value_rsp
**
** Description      This function is called to handle find by type value response.
**
**
** Returns          void
**
*******************************************************************************/
void gatt_process_find_type_value_rsp (tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, UINT16 len, UINT8 *p_data)
{
    tGATT_DISC_RES      result;
    tGATT_DISC_VALUE    record_value;
    UINT8               *p = p_data;

    GATT_TRACE_DEBUG0("gatt_process_find_type_value_rsp ");
    /* unexpected response */
    if (p_clcb->operation != GATTC_OPTYPE_DISCOVERY || p_clcb->op_subtype != GATT_DISC_SRVC_BY_UUID)
        return;

    memset (&record_value, 0, sizeof(tGATT_DISC_VALUE));
    result.type.len = 2;
    result.type.uu.uuid16 = GATT_UUID_PRI_SERVICE;

    /* returns a series of handle ranges */
    while (len >= 4)
    {
        STREAM_TO_UINT16 (result.handle, p);
        STREAM_TO_UINT16 (record_value.handle, p);
        len -= 4;

        memcpy (&result.value, &record_value, sizeof (result.value));;

        if (p_clcb->p_reg->app_cb.p_disc_res_cb)
            (*p_clcb->p_reg->app_cb.p_disc_res_cb)(p_clcb->conn_id, p_clcb->op_subtype, &result);
    }

    /* last handle  + 1 */
    p_clcb->s_handle = (record_value.handle == 0) ? 0 : (record_value.handle + 1);
    /* initiate another request */
    gatt_act_discovery(p_clcb) ;
}
/*******************************************************************************
**
** Function         gatt_process_read_info_rsp
**
** Description      This function is called to handle the read information
**                  response.
**
**
** Returns          void
**
*******************************************************************************/
void gatt_process_read_info_rsp(tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, UINT8 op_code,
                                UINT16 len, UINT8 *p_data)
{
    tGATT_DISC_RES  result;
    UINT8   *p = p_data, uuid_len = 0, type;

    /* unexpected response */
    if (p_clcb->operation != GATTC_OPTYPE_DISCOVERY || p_clcb->op_subtype != GATT_DISC_CHAR_DSCPT)
        return;

    STREAM_TO_UINT8(type, p);
    len -= 1;

    if (type == GATT_INFO_TYPE_PAIR_16)
        uuid_len = LEN_UUID_16;
    else if (type == GATT_INFO_TYPE_PAIR_128)
        uuid_len = LEN_UUID_128;

    while (len >= uuid_len + 2)
    {
        STREAM_TO_UINT16 (result.handle, p);

        if (uuid_len > 0)
        {
            if (!gatt_parse_uuid_from_cmd(&result.type, uuid_len, &p))
                break;
        }
        else
            memcpy (&result.type, &p_clcb->uuid, sizeof(tBT_UUID));

        len -= (uuid_len + 2);

        if (p_clcb->p_reg->app_cb.p_disc_res_cb)
            (*p_clcb->p_reg->app_cb.p_disc_res_cb)(p_clcb->conn_id, p_clcb->op_subtype, &result);
    }

    p_clcb->s_handle = (result.handle == 0) ? 0 :(result.handle + 1);
    /* initiate another request */
    gatt_act_discovery(p_clcb) ;
}
/*******************************************************************************
**
** Function         gatt_proc_disc_error_rsp
**
** Description      This function process the read by type response and send another
**                  request if needed.
**
** Returns          void.
**
*******************************************************************************/
void gatt_proc_disc_error_rsp(tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, UINT8 opcode,
                              UINT16 handle, UINT8 reason)
{
    tGATT_STATUS    status = (tGATT_STATUS) reason;

    GATT_TRACE_DEBUG2("gatt_proc_disc_error_rsp reason: %02x cmd_code %04x", reason, opcode);

    switch (opcode)
    {
        case GATT_REQ_READ_BY_GRP_TYPE:
        case GATT_REQ_FIND_TYPE_VALUE:
        case GATT_REQ_READ_BY_TYPE:
        case GATT_REQ_FIND_INFO:
            if (reason == GATT_NOT_FOUND)
            {
                status = GATT_SUCCESS;
                GATT_TRACE_DEBUG0("Discovery completed");
            }
            break;
        default:
            GATT_TRACE_ERROR1("Incorrect discovery opcode %04x",   opcode);
            break;
    }

    gatt_end_operation(p_clcb, status, NULL);
}

/*******************************************************************************
**
** Function         gatt_process_error_rsp
**
** Description      This function is called to handle the error response
**
**
** Returns          void
**
*******************************************************************************/
void gatt_process_error_rsp(tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, UINT8 op_code,
                            UINT16 len, UINT8 *p_data)
{
    UINT8   opcode, reason, * p= p_data;
    UINT16  handle;
    tGATT_VALUE  *p_attr = (tGATT_VALUE *)p_clcb->p_attr_buf;

    GATT_TRACE_DEBUG0("gatt_process_error_rsp ");
    STREAM_TO_UINT8(opcode, p);
    STREAM_TO_UINT16(handle, p);
    STREAM_TO_UINT8(reason, p);

    if (p_clcb->operation == GATTC_OPTYPE_DISCOVERY)
    {
        gatt_proc_disc_error_rsp(p_tcb, p_clcb, opcode, handle, reason);
    }
    else
    {
        if ( (p_clcb->operation == GATTC_OPTYPE_WRITE) &&
             (p_clcb->op_subtype == GATT_WRITE) &&
             (opcode == GATT_REQ_PREPARE_WRITE) &&
             (p_attr) &&
             (handle == p_attr->handle)  )
        {
            p_clcb->status = reason;
            gatt_send_queue_write_cancel(p_tcb, p_clcb, GATT_PREP_WRITE_CANCEL);
        }
        else if ((p_clcb->operation == GATTC_OPTYPE_READ) &&
                 ((p_clcb->op_subtype == GATT_READ_CHAR_VALUE_HDL) ||
                  (p_clcb->op_subtype == GATT_READ_BY_HANDLE)) &&
                 (opcode == GATT_REQ_READ_BLOB) &&
                 p_clcb->first_read_blob_after_read &&
                 (reason == GATT_NOT_LONG))
        {
            gatt_end_operation(p_clcb, GATT_SUCCESS, (void *)p_clcb->p_attr_buf);
        }
        else
            gatt_end_operation(p_clcb, reason, NULL);
    }
}
/*******************************************************************************
**
** Function         gatt_process_prep_write_rsp
**
** Description      This function is called to handle the read response
**
**
** Returns          void
**
*******************************************************************************/
void gatt_process_prep_write_rsp (tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, UINT8 op_code,
                                  UINT16 len, UINT8 *p_data)
{
    tGATT_VALUE  value = {0};
    UINT8        *p= p_data;

    GATT_TRACE_ERROR2("value resp op_code = %s len = %d", gatt_dbg_op_name(op_code), len);

    STREAM_TO_UINT16 (value.handle, p);
    STREAM_TO_UINT16 (value.offset, p);

    value.len = len - 4;

    memcpy (value.value, p, value.len);

    if (p_clcb->op_subtype == GATT_WRITE_PREPARE)
    {
        p_clcb->status = GATT_SUCCESS;
        /* application should verify handle offset
           and value are matched or not */

        gatt_end_operation(p_clcb, p_clcb->status, &value);
    }
    else if (p_clcb->op_subtype == GATT_WRITE )
    {
        if (!gatt_check_write_long_terminate(p_tcb, p_clcb, &value))
            gatt_send_prepare_write(p_tcb, p_clcb);
    }

}
/*******************************************************************************
**
** Function         gatt_process_notification
**
** Description      This function is called to handle the handle value indication
**                  or handle value notification.
**
**
** Returns          void
**
*******************************************************************************/
void gatt_process_notification(tGATT_TCB *p_tcb, UINT8 op_code,
                               UINT16 len, UINT8 *p_data)
{
    tGATT_VALUE     value = {0};
    tGATT_REG       *p_reg;
    UINT16          conn_id;
    tGATT_STATUS    encrypt_status;
    UINT8           *p= p_data, i,
    event = (op_code == GATT_HANDLE_VALUE_NOTIF) ? GATTC_OPTYPE_NOTIFICATION : GATTC_OPTYPE_INDICATION;

    GATT_TRACE_DEBUG0("gatt_process_notification ");

    STREAM_TO_UINT16 (value.handle, p);
    value.len = len - 2;
    memcpy (value.value, p, value.len);

    if (!GATT_HANDLE_IS_VALID(value.handle))
    {
        /* illegal handle, send ack now */
        if (op_code == GATT_HANDLE_VALUE_IND)
            attp_send_cl_msg(p_tcb, 0, GATT_HANDLE_VALUE_CONF, NULL);
        return;
    }

    if (event == GATTC_OPTYPE_INDICATION)
    {
        if (p_tcb->ind_count)
        {
            /* this is an error case that receiving an indication but we
               still has an indication not being acked yet.
               For now, just log the error reset the counter.
               Later we need to disconnect the link unconditionally.
            */
            GATT_TRACE_ERROR1("gatt_process_notification rcv Ind. but ind_count=%d (will reset ind_count)",  p_tcb->ind_count);
        }
        p_tcb->ind_count = 0;
    }

    /* should notify all registered client with the handle value notificaion/indication
       Note: need to do the indication count and start timer first then do callback
     */

    for (i = 0, p_reg = gatt_cb.cl_rcb; i < GATT_MAX_APPS; i++, p_reg++)
    {
        if (p_reg->in_use && p_reg->app_cb.p_cmpl_cb && (event == GATTC_OPTYPE_INDICATION))
            p_tcb->ind_count++;
    }

    if (event == GATTC_OPTYPE_INDICATION)
    {
        /* start a timer for app confirmation */
        if (p_tcb->ind_count > 0)
            gatt_start_ind_ack_timer(p_tcb);
        else /* no app to indicate, or invalid handle */
            attp_send_cl_msg(p_tcb, 0, GATT_HANDLE_VALUE_CONF, NULL);
    }

    for (i = 0, p_reg = gatt_cb.cl_rcb; i < GATT_MAX_APPS; i++, p_reg++)
    {
        if (p_reg->in_use && p_reg->app_cb.p_cmpl_cb)
        {
            conn_id = GATT_CREATE_CONN_ID(p_tcb->tcb_idx, p_reg->gatt_if);
            encrypt_status = gatt_get_link_encrypt_status(p_tcb);
            (*p_reg->app_cb.p_cmpl_cb) (conn_id, event, encrypt_status, (tGATT_CL_COMPLETE *)&value);
        }
    }

}

/*******************************************************************************
**
** Function         gatt_process_read_by_type_rsp
**
** Description      This function is called to handle the read by type response.
**                  read by type can be used for discovery, or read by type or
**                  read characteristic value.
**
** Returns          void
**
*******************************************************************************/
void gatt_process_read_by_type_rsp (tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, UINT8 op_code,
                                    UINT16 len, UINT8 *p_data)
{
    tGATT_DISC_RES      result;
    tGATT_DISC_VALUE    record_value;
    UINT8               *p = p_data, value_len, handle_len = 2;
    UINT16              handle = 0;

    /* discovery procedure and no callback function registered */
    if (((!p_clcb->p_reg) || (!p_clcb->p_reg->app_cb.p_disc_res_cb)) && (p_clcb->operation == GATTC_OPTYPE_DISCOVERY))
        return;

    STREAM_TO_UINT8(value_len, p);

    if ((value_len > (p_tcb->payload_size - 2)) || (value_len > (len-1))  )
    {
        /* this is an error case that server's response containing a value length which is larger than MTU-2
           or value_len > message total length -1 */
        GATT_TRACE_ERROR4("gatt_process_read_by_type_rsp: Discard response op_code=%d vale_len=%d > (MTU-2=%d or msg_len-1=%d)",
                          op_code, value_len, (p_tcb->payload_size - 2), (len-1));
        gatt_end_operation(p_clcb, GATT_ERROR, NULL);
        return;
    }

    if (op_code == GATT_RSP_READ_BY_GRP_TYPE)
        handle_len = 4;

    value_len -= handle_len; /* substract the handle pairs bytes */
    len -= 1;

    while (len >= (handle_len + value_len))
    {
        STREAM_TO_UINT16(handle, p);

        if (!GATT_HANDLE_IS_VALID(handle))
        {
            gatt_end_operation(p_clcb, GATT_INVALID_HANDLE, NULL);
            return;
        }

        memset(&result, 0, sizeof(tGATT_DISC_RES));
        memset(&record_value, 0, sizeof(tGATT_DISC_VALUE));

        result.handle = handle;
        result.type.len = 2;
        result.type.uu.uuid16 = disc_type_to_uuid[p_clcb->op_subtype];

        /* discover all services */
        if (p_clcb->operation == GATTC_OPTYPE_DISCOVERY &&
            p_clcb->op_subtype == GATT_DISC_SRVC_ALL &&
            op_code == GATT_RSP_READ_BY_GRP_TYPE)
        {
            STREAM_TO_UINT16(handle, p);

            if (!GATT_HANDLE_IS_VALID(handle))
            {
                gatt_end_operation(p_clcb, GATT_INVALID_HANDLE, NULL);
                return;
            }
            else
            {
                record_value.group_value.e_handle = handle;
                if (!gatt_parse_uuid_from_cmd(&record_value.group_value.service_type, value_len, &p))
                {
                    GATT_TRACE_ERROR0("discover all service response parsing failure");
                    break;
                }
            }
        }
        /* discover included service */
        else if (p_clcb->operation == GATTC_OPTYPE_DISCOVERY && p_clcb->op_subtype == GATT_DISC_INC_SRVC)
        {
            STREAM_TO_UINT16(record_value.incl_service.s_handle, p);
            STREAM_TO_UINT16(record_value.incl_service.e_handle, p);

            if (!GATT_HANDLE_IS_VALID(record_value.incl_service.s_handle) ||
                !GATT_HANDLE_IS_VALID(record_value.incl_service.e_handle))
            {
                gatt_end_operation(p_clcb, GATT_INVALID_HANDLE, NULL);
                return;
            }

            if(value_len == 6)
            {
                STREAM_TO_UINT16(record_value.incl_service.service_type.uu.uuid16, p);
                record_value.incl_service.service_type.len = LEN_UUID_16;
            }
            else if (value_len == 4)
            {
                p_clcb->s_handle = record_value.incl_service.s_handle;
                p_clcb->read_uuid128.wait_for_read_rsp = TRUE;
                p_clcb->read_uuid128.next_disc_start_hdl = handle + 1;
                memcpy(&p_clcb->read_uuid128.result, &result, sizeof(result));
                memcpy(&p_clcb->read_uuid128.result.value, &record_value, sizeof (result.value));
                p_clcb->op_subtype |= 0x90;
                gatt_act_read(p_clcb, 0);
                return;
            }
            else
            {
               GATT_TRACE_ERROR1("gatt_process_read_by_type_rsp INCL_SRVC failed with invalid data value_len=%d", value_len);
               gatt_end_operation(p_clcb, GATT_INVALID_PDU, (void *)p);
               return;
            }
        }
        /* read by type */
        else if (p_clcb->operation == GATTC_OPTYPE_READ && p_clcb->op_subtype == GATT_READ_BY_TYPE)
        {
            p_clcb->counter = len - 2;
            p_clcb->s_handle = handle;
            if ( p_clcb->counter == (p_clcb->p_tcb->payload_size -4))
            {
                p_clcb->op_subtype = GATT_READ_BY_HANDLE;
                if (!p_clcb->p_attr_buf)
                    p_clcb->p_attr_buf = (UINT8 *)GKI_getbuf(GATT_MAX_ATTR_LEN);
                if (p_clcb->p_attr_buf && p_clcb->counter <= GATT_MAX_ATTR_LEN)
                {
                    memcpy(p_clcb->p_attr_buf, p, p_clcb->counter);
                    gatt_act_read(p_clcb, p_clcb->counter);
                }
                else
                   gatt_end_operation(p_clcb, GATT_INTERNAL_ERROR, (void *)p);
            }
            else
            {
                 gatt_end_operation(p_clcb, GATT_SUCCESS, (void *)p);
            }
            return;
        }
        else /* discover characterisitic or read characteristic value */
        {
            STREAM_TO_UINT8 (record_value.dclr_value.char_prop, p);
            STREAM_TO_UINT16(record_value.dclr_value.val_handle, p);
            if (!GATT_HANDLE_IS_VALID(record_value.dclr_value.val_handle))
            {
                gatt_end_operation(p_clcb, GATT_INVALID_HANDLE, NULL);
                return;
            }
            gatt_parse_uuid_from_cmd(&record_value.dclr_value.char_uuid, (UINT16)(value_len - 3), &p);

            /* UUID not matching */
            if (!gatt_uuid_compare(record_value.dclr_value.char_uuid, p_clcb->uuid))
            {
                len -= (value_len + 2);
                continue; /* skip the result, and look for next one */
            }
            else if (p_clcb->operation == GATTC_OPTYPE_READ)
            /* UUID match for read characteristic value */
            {
                /* only read the first matching UUID characteristic value, and
                  discard the rest results */
                p_clcb->s_handle = record_value.dclr_value.val_handle;
                p_clcb->op_subtype |= 0x80;
                gatt_act_read(p_clcb, 0);
                return;
            }
        }
        len -= (value_len + handle_len);

        /* result is (handle, 16bits UUID) pairs */
        memcpy (&result.value, &record_value, sizeof (result.value));

        /* send callback if is discover procedure */
        if (p_clcb->operation == GATTC_OPTYPE_DISCOVERY && p_clcb->p_reg->app_cb.p_disc_res_cb)
            (*p_clcb->p_reg->app_cb.p_disc_res_cb)(p_clcb->conn_id, p_clcb->op_subtype, &result);
    }

    p_clcb->s_handle = (handle == 0) ? 0 : (handle + 1);

    if (p_clcb->operation == GATTC_OPTYPE_DISCOVERY)
    {
        /* initiate another request */
        gatt_act_discovery(p_clcb) ;
    }
    else /* read characteristic value */
    {
        gatt_act_read(p_clcb, 0);
    }
}

/*******************************************************************************
**
** Function         gatt_process_read_rsp
**
** Description      This function is called to handle the read BLOB response
**
**
** Returns          void
**
*******************************************************************************/
void gatt_process_read_rsp(tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb,  UINT8 op_code,
                           UINT16 len, UINT8 *p_data)
{
    UINT16      offset = p_clcb->counter;
    UINT8       * p= p_data;

    if (p_clcb->operation == GATTC_OPTYPE_READ)
    {
        if (p_clcb->op_subtype != GATT_READ_BY_HANDLE)
        {
            p_clcb->counter = len;
            gatt_end_operation(p_clcb, GATT_SUCCESS, (void *)p);
        }
        else
        {

            /* allocate GKI buffer holding up long attribute value  */
            if (!p_clcb->p_attr_buf)
                p_clcb->p_attr_buf = (UINT8 *)GKI_getbuf(GATT_MAX_ATTR_LEN);

            /* copy attrobute value into cb buffer  */
            if (p_clcb->p_attr_buf && offset < GATT_MAX_ATTR_LEN)
            {
                if ((len + offset) > GATT_MAX_ATTR_LEN)
                    len = GATT_MAX_ATTR_LEN - offset;

                p_clcb->counter += len;

                memcpy(p_clcb->p_attr_buf + offset, p, len);

                /* send next request if needed  */

                if (len == (p_tcb->payload_size - 1) && /* full packet for read or read blob rsp */
                    len + offset < GATT_MAX_ATTR_LEN)
                {
                    GATT_TRACE_DEBUG3("full pkt issue read blob for remianing bytes old offset=%d len=%d new offset=%d",
                                      offset, len, p_clcb->counter);
                    gatt_act_read(p_clcb, p_clcb->counter);
                }
                else /* end of request, send callback */
                {
                    gatt_end_operation(p_clcb, GATT_SUCCESS, (void *)p_clcb->p_attr_buf);
                }
            }
            else /* exception, should not happen */
            {
                GATT_TRACE_ERROR2("attr offset = %d p_attr_buf = %d ", offset, p_clcb->p_attr_buf);
                gatt_end_operation(p_clcb, GATT_NO_RESOURCES, (void *)p_clcb->p_attr_buf);
            }
        }
    }
    else
    {
        if (p_clcb->operation == GATTC_OPTYPE_DISCOVERY &&
            p_clcb->op_subtype == GATT_DISC_INC_SRVC &&
            p_clcb->read_uuid128.wait_for_read_rsp )
        {
            p_clcb->s_handle = p_clcb->read_uuid128.next_disc_start_hdl;
            p_clcb->read_uuid128.wait_for_read_rsp = FALSE;
            if (len == LEN_UUID_128)
            {

                memcpy(p_clcb->read_uuid128.result.value.incl_service.service_type.uu.uuid128, p, len);
                p_clcb->read_uuid128.result.value.incl_service.service_type.len = LEN_UUID_128;
                if ( p_clcb->p_reg->app_cb.p_disc_res_cb)
                    (*p_clcb->p_reg->app_cb.p_disc_res_cb)(p_clcb->conn_id, p_clcb->op_subtype, &p_clcb->read_uuid128.result);
                gatt_act_discovery(p_clcb) ;
            }
            else
            {
                gatt_end_operation(p_clcb, GATT_INVALID_PDU, (void *)p);
            }
        }
    }

}


/*******************************************************************************
**
** Function         gatt_process_handle_rsp
**
** Description      This function is called to handle the write response
**
**
** Returns          void
**
*******************************************************************************/
void gatt_process_handle_rsp(tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, UINT8 op_code, UINT16 len, UINT8 *p_data)
{
    UINT16      handle;
    UINT8       * p= p_data;

    STREAM_TO_UINT16(handle, p);
    len -= 2;

    if (op_code == GATT_RSP_WRITE)
        gatt_end_operation(p_clcb, GATT_SUCCESS, NULL);
}
/*******************************************************************************
**
** Function         gatt_process_mtu_rsp
**
** Description      This function is called to process the configure MTU response.
**
**
** Returns          void
**
*******************************************************************************/
void gatt_process_mtu_rsp(tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, UINT16 len, UINT8 *p_data)
{
    UINT16 mtu;

    STREAM_TO_UINT16(mtu, p_data);

    if (mtu < p_tcb->payload_size && mtu >= GATT_DEF_BLE_MTU_SIZE)
        p_tcb->payload_size = mtu;

    gatt_end_operation(p_clcb, p_clcb->status, NULL);
}
/*******************************************************************************
**
** Function         gatt_cmd_to_rsp_code
**
** Description      The function convert a ATT command op code into the corresponding
**                  response code assume no error occurs.
**
** Returns          response code.
**
*******************************************************************************/
UINT8 gatt_cmd_to_rsp_code (UINT8 cmd_code)
{
    UINT8   rsp_code  = 0;

    if (cmd_code > 1 && cmd_code != GATT_CMD_WRITE)
    {
        rsp_code = cmd_code + 1;
    }
    return rsp_code;
}
/*******************************************************************************
**
** Function         gatt_cl_send_next_cmd_inq
**
** Description      Find next command in queue and sent to server
**
** Returns          TRUE if command sent, otherwise FALSE.
**
*******************************************************************************/
BOOLEAN gatt_cl_send_next_cmd_inq(tGATT_TCB *p_tcb)
{
    tGATT_CMD_Q  *p_cmd = &p_tcb->cl_cmd_q[p_tcb->pending_cl_req];
    BOOLEAN     sent = FALSE;

    while (!sent &&
           p_tcb->pending_cl_req != p_tcb->next_slot_inq &&
           p_cmd->to_send && p_cmd->p_cmd != NULL)
    {
        sent = attp_send_msg_to_L2CAP(p_tcb, p_cmd->p_cmd);

        if (sent)
        {
            p_cmd->to_send = FALSE;
            p_cmd->p_cmd = NULL;

            gatt_start_rsp_timer (p_tcb);
        }
        else
        {
            GATT_TRACE_ERROR0("gatt_cl_send_next_cmd_inq: L2CAP sent error");

            memset(p_cmd, 0, sizeof(tGATT_CMD_Q));
            p_tcb->pending_cl_req ++;
            p_cmd = &p_tcb->cl_cmd_q[p_tcb->pending_cl_req];
        }
    }
    return sent;
}

/*******************************************************************************
**
** Function         gatt_client_handle_server_rsp
**
** Description      This function is called to handle the server response to
**                  client.
**
**
** Returns          void
**
*******************************************************************************/
void gatt_client_handle_server_rsp (tGATT_TCB *p_tcb, UINT8 op_code,
                                    UINT16 len, UINT8 *p_data)
{
    tGATT_CLCB   *p_clcb = NULL;
    UINT8        rsp_code;

    if (op_code != GATT_HANDLE_VALUE_IND && op_code != GATT_HANDLE_VALUE_NOTIF)
    {
        p_clcb = gatt_cmd_dequeue(p_tcb, &rsp_code);

        rsp_code = gatt_cmd_to_rsp_code(rsp_code);

        if (p_clcb == NULL || (rsp_code != op_code && op_code != GATT_RSP_ERROR))
        {
            GATT_TRACE_WARNING2 ("ATT - Ignore wrong response. Receives (%02x) \
                                Request(%02x) Ignored", op_code, rsp_code);

            return;
        }
        else
            btu_stop_timer (&p_tcb->rsp_timer_ent);
    }
    /* the size of the message may not be bigger than the local max PDU size*/
    /* The message has to be smaller than the agreed MTU, len does not count op_code */
    if (len >= p_tcb->payload_size)
    {
        GATT_TRACE_ERROR2("invalid response/indicate pkt size: %d, PDU size: %d", len + 1, p_tcb->payload_size);
        if (op_code != GATT_HANDLE_VALUE_NOTIF &&
            op_code != GATT_HANDLE_VALUE_IND)
            gatt_end_operation(p_clcb, GATT_ERROR, NULL);
    }
    else
    {
        switch (op_code)
        {
            case GATT_RSP_ERROR:
                gatt_process_error_rsp(p_tcb, p_clcb, op_code, len, p_data);
                break;

            case GATT_RSP_MTU:       /* 2 bytes mtu */
                gatt_process_mtu_rsp(p_tcb, p_clcb, len ,p_data);
                break;

            case GATT_RSP_FIND_INFO:
                gatt_process_read_info_rsp(p_tcb, p_clcb, op_code, len, p_data);
                break;

            case GATT_RSP_READ_BY_TYPE:
            case GATT_RSP_READ_BY_GRP_TYPE:
                gatt_process_read_by_type_rsp(p_tcb, p_clcb, op_code, len, p_data);
                break;

            case GATT_RSP_READ:
            case GATT_RSP_READ_BLOB:
            case GATT_RSP_READ_MULTI:
                gatt_process_read_rsp(p_tcb, p_clcb, op_code, len, p_data);
                break;

            case GATT_RSP_FIND_TYPE_VALUE: /* disc service with UUID */
                gatt_process_find_type_value_rsp(p_tcb, p_clcb, len, p_data);
                break;

            case GATT_RSP_WRITE:
                gatt_process_handle_rsp(p_tcb, p_clcb, op_code, len, p_data);
                break;

            case GATT_RSP_PREPARE_WRITE:
                gatt_process_prep_write_rsp(p_tcb, p_clcb, op_code, len, p_data);
                break;

            case GATT_RSP_EXEC_WRITE:
                gatt_end_operation(p_clcb, p_clcb->status, NULL);
                break;

            case GATT_HANDLE_VALUE_NOTIF:
            case GATT_HANDLE_VALUE_IND:
                gatt_process_notification(p_tcb, op_code, len, p_data);
                break;

            default:
                GATT_TRACE_ERROR1("Unknown opcode = %d", op_code);
                break;
        }
    }

    if (op_code != GATT_HANDLE_VALUE_IND && op_code != GATT_HANDLE_VALUE_NOTIF)
    {
        gatt_cl_send_next_cmd_inq(p_tcb);
    }

    return;
}

#endif  /* BLE_INCLUDED */
