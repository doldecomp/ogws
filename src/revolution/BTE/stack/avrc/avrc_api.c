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
 *  nterface to AVRCP mandatory commands
 *
 ******************************************************************************/
#include <string.h>

#include "gki.h"
#include "avrc_api.h"
#include "avrc_int.h"
#include "wcassert.h"

/*****************************************************************************
**  Global data
*****************************************************************************/


#define AVRC_MAX_RCV_CTRL_EVT   AVCT_BROWSE_UNCONG_IND_EVT

static const UINT8 avrc_ctrl_event_map[] =
{
    AVRC_OPEN_IND_EVT,  /* AVCT_CONNECT_CFM_EVT */
    AVRC_OPEN_IND_EVT,  /* AVCT_CONNECT_IND_EVT */
    AVRC_CLOSE_IND_EVT, /* AVCT_DISCONNECT_CFM_EVT */
    AVRC_CLOSE_IND_EVT, /* AVCT_DISCONNECT_IND_EVT */
    AVRC_CONG_IND_EVT,  /* AVCT_CONG_IND_EVT */
    AVRC_UNCONG_IND_EVT,/* AVCT_UNCONG_IND_EVT */
    AVRC_BROWSE_OPEN_IND_EVT,  /* AVCT_BROWSE_CONN_CFM_EVT   */
    AVRC_BROWSE_OPEN_IND_EVT,  /* AVCT_BROWSE_CONN_IND_EVT   */
    AVRC_BROWSE_CLOSE_IND_EVT, /* AVCT_BROWSE_DISCONN_CFM_EVT */
    AVRC_BROWSE_CLOSE_IND_EVT, /* AVCT_BROWSE_DISCONN_IND_EVT */
    AVRC_BROWSE_CONG_IND_EVT,  /* AVCT_BROWSE_CONG_IND_EVT    */
    AVRC_BROWSE_UNCONG_IND_EVT /* AVCT_BROWSE_UNCONG_IND_EVT  */
};

#define AVRC_OP_DROP        0xFE    /* use this unused opcode to indication no need to call the callback function */
#define AVRC_OP_DROP_N_FREE 0xFD    /* use this unused opcode to indication no need to call the callback function & free buffer */

/******************************************************************************
**
** Function         avrc_ctrl_cback
**
** Description      This is the callback function used by AVCTP to report
**                  received link events.
**
** Returns          Nothing.
**
******************************************************************************/
static void avrc_ctrl_cback(UINT8 handle, UINT8 event, UINT16 result,
                                BD_ADDR peer_addr)
{
    UINT8   avrc_event;

    if (event <= AVRC_MAX_RCV_CTRL_EVT && avrc_cb.ccb[handle].p_ctrl_cback)
    {
        avrc_event = avrc_ctrl_event_map[event];
        if (event == AVCT_CONNECT_CFM_EVT)
        {
            if (result != 0) /* failed */
                avrc_event = AVRC_CLOSE_IND_EVT;
        }
        (*avrc_cb.ccb[handle].p_ctrl_cback)(handle, avrc_event, result, peer_addr);
    }
    /* else drop the unknown event*/
}

/******************************************************************************
**
** Function         avrc_get_data_ptr
**
** Description      If the offset in the received buffer is smaller than required
**                  move the portion of data AVRC cares.
**
** Returns          Nothing.
**
******************************************************************************/
static UINT8 * avrc_get_data_ptr(BT_HDR *p_pkt)
{
    UINT8   *p_data = (UINT8 *)(p_pkt+1) + p_pkt->offset;
    int     i, gap;

    if (p_pkt->offset < AVCT_MSG_OFFSET)
    {
        gap = AVCT_MSG_OFFSET - p_pkt->offset;
        for(i=p_pkt->len; i>0; i--)
        {
            *(p_data + i + gap) = *(p_data + i);
        }
        p_pkt->offset   += gap;
        p_data          = (UINT8 *)(p_pkt+1) + p_pkt->offset;
    }
    *p_data         = AVRC_RSP_IMPL_STBL;
    return p_data;
}


/******************************************************************************
**
** Function         avrc_msg_cback
**
** Description      This is the callback function used by AVCTP to report
**                  received AV control messages.
**
** Returns          Nothing.
**
******************************************************************************/
static void avrc_msg_cback(UINT8 handle, UINT8 label, UINT8 cr,
                               BT_HDR *p_pkt)
{
    UINT8       opcode;
    tAVRC_MSG   msg;
    UINT8       *p_data;
    UINT8       *p_begin;
    BOOLEAN     drop = FALSE;
    BOOLEAN     free = TRUE;
    BT_HDR      *p_rsp = NULL;
    UINT8       *p_rsp_data;
    int         xx;
    BOOLEAN     reject = FALSE;
#if (BT_USE_TRACES == TRUE)
    char        *p_drop_msg = "dropped";
#endif
    tAVRC_MSG_VENDOR *p_msg = &msg.vendor;

    if (cr == AVCT_CMD &&
        (p_pkt->layer_specific & AVCT_DATA_CTRL && AVRC_PACKET_LEN < sizeof(p_pkt->len)))
    {
        /* Ignore the invalid AV/C command frame */
#if (BT_USE_TRACES == TRUE)
        p_drop_msg = "dropped - too long AV/C cmd frame size";
#endif
        GKI_freebuf(p_pkt);
        return;
    }

    if (cr == AVCT_REJ)
    {
        /* The peer thinks that this PID is no longer open - remove this handle */
        /*  */
        GKI_freebuf(p_pkt);
        AVCT_RemoveConn(handle);
        return;
    }

    p_data  = (UINT8 *)(p_pkt+1) + p_pkt->offset;
    memset(&msg, 0, sizeof(tAVRC_MSG) );
    {
        msg.hdr.ctype           = p_data[0] & AVRC_CTYPE_MASK;
        AVRC_TRACE_DEBUG4("avrc_msg_cback handle:%d, ctype:%d, offset:%d, len: %d",
                handle, msg.hdr.ctype, p_pkt->offset, p_pkt->len);
        msg.hdr.subunit_type    = (p_data[1] & AVRC_SUBTYPE_MASK) >> AVRC_SUBTYPE_SHIFT;
        msg.hdr.subunit_id      = p_data[1] & AVRC_SUBID_MASK;
        opcode                  = p_data[2];
    }

    if ( ((avrc_cb.ccb[handle].control & AVRC_CT_TARGET) && (cr == AVCT_CMD)) ||
        ((avrc_cb.ccb[handle].control & AVRC_CT_CONTROL) && (cr == AVCT_RSP)) )
    {

        switch(opcode)
        {
        case AVRC_OP_UNIT_INFO:
            if (cr == AVCT_CMD)
            {
                /* send the response to the peer */
                p_rsp           = p_pkt; /* this also sets free = FALSE, drop = TRUE */
                /* check & set the offset. set response code, set subunit_type & subunit_id,
                   set AVRC_OP_UNIT_INFO */
                p_rsp_data      = avrc_get_data_ptr(p_pkt) + AVRC_AVC_HDR_SIZE; /* 3 bytes: ctype, subunit*, opcode */
                *p_rsp_data++   = 7;
                /* Panel subunit & id=0 */
                *p_rsp_data++   = (AVRC_SUB_PANEL << AVRC_SUBTYPE_SHIFT);
                AVRC_CO_ID_TO_BE_STREAM(p_rsp_data, avrc_cb.ccb[handle].company_id);
                p_rsp->len      = (UINT16) (p_rsp_data - (UINT8 *)(p_rsp + 1) - p_rsp->offset);
                cr = AVCT_RSP;
#if (BT_USE_TRACES == TRUE)
                p_drop_msg = "auto respond";
#endif
            }
            else
            {
                /* parse response */
                p_data += 4; /* 3 bytes: ctype, subunit*, opcode + octet 3 (is 7)*/
                msg.unit.unit_type  = (*p_data & AVRC_SUBTYPE_MASK) >> AVRC_SUBTYPE_SHIFT;
                msg.unit.unit       = *p_data & AVRC_SUBID_MASK;
                p_data++;
                AVRC_BE_STREAM_TO_CO_ID(msg.unit.company_id, p_data);
            }
            break;

        case AVRC_OP_SUB_INFO:
            if (cr == AVCT_CMD)
            {
                /* send the response to the peer */
                p_rsp           = p_pkt; /* this also sets free = FALSE, drop = TRUE */
                /* check & set the offset. set response code, set (subunit_type & subunit_id),
                   set AVRC_OP_SUB_INFO, set (page & extention code) */
                p_rsp_data      = avrc_get_data_ptr(p_pkt) + 4;
                /* Panel subunit & id=0 */
                *p_rsp_data++   = (AVRC_SUB_PANEL << AVRC_SUBTYPE_SHIFT);
                memset(p_rsp_data, AVRC_CMD_OPRND_PAD, AVRC_SUBRSP_OPRND_BYTES);
                p_rsp_data      += AVRC_SUBRSP_OPRND_BYTES;
                p_rsp->len      = (UINT16) (p_rsp_data - (UINT8 *)(p_rsp + 1) - p_rsp->offset);
                cr = AVCT_RSP;
#if (BT_USE_TRACES == TRUE)
                p_drop_msg = "auto responded";
#endif
            }
            else
            {
                /* parse response */
                p_data += AVRC_AVC_HDR_SIZE; /* 3 bytes: ctype, subunit*, opcode */
                msg.sub.page    = (*p_data++ >> AVRC_SUB_PAGE_SHIFT) & AVRC_SUB_PAGE_MASK;
                xx      = 0;
                while (*p_data != AVRC_CMD_OPRND_PAD && xx<AVRC_SUB_TYPE_LEN)
                {
                    msg.sub.subunit_type[xx] = *p_data++ >> AVRC_SUBTYPE_SHIFT;
                    if (msg.sub.subunit_type[xx] == AVRC_SUB_PANEL)
                        msg.sub.panel   = TRUE;
                    xx++;
                }
            }
            break;

        case AVRC_OP_VENDOR:
            p_data  = (UINT8 *)(p_pkt+1) + p_pkt->offset;
            p_begin = p_data;
            if (p_pkt->len < AVRC_VENDOR_HDR_SIZE) /* 6 = ctype, subunit*, opcode & CO_ID */
            {
                if (cr == AVCT_CMD)
                    reject = TRUE;
                else
                    drop = TRUE;
                break;
            }
            p_data += AVRC_AVC_HDR_SIZE; /* skip the first 3 bytes: ctype, subunit*, opcode */
            AVRC_BE_STREAM_TO_CO_ID(p_msg->company_id, p_data);
            p_msg->p_vendor_data   = p_data;
            p_msg->vendor_len      = p_pkt->len - (p_data - p_begin);

            break;

        case AVRC_OP_PASS_THRU:
            if (p_pkt->len < 5) /* 3 bytes: ctype, subunit*, opcode & op_id & len */
            {
                if (cr == AVCT_CMD)
                    reject = TRUE;
                else
                    drop = TRUE;
                break;
            }
            p_data += AVRC_AVC_HDR_SIZE; /* skip the first 3 bytes: ctype, subunit*, opcode */
            msg.pass.op_id  = (AVRC_PASS_OP_ID_MASK & *p_data);
            if (AVRC_PASS_STATE_MASK & *p_data)
                msg.pass.state  = TRUE;
            else
                msg.pass.state  = FALSE;
            p_data++;
            msg.pass.pass_len    = *p_data++;
            if (msg.pass.pass_len != p_pkt->len - 5)
                msg.pass.pass_len = p_pkt->len - 5;
            if (msg.pass.pass_len)
                msg.pass.p_pass_data = p_data;
            else
                msg.pass.p_pass_data = NULL;
            break;


        default:
            if ((avrc_cb.ccb[handle].control & AVRC_CT_TARGET) && (cr == AVCT_CMD))
            {
                /* reject unsupported opcode */
                reject = TRUE;
            }
            drop    = TRUE;
            break;
        }
    }
    else /* drop the event */
    {
            drop    = TRUE;
    }

    if (reject)
    {
        /* reject unsupported opcode */
        p_rsp           = p_pkt; /* this also sets free = FALSE, drop = TRUE */
        p_rsp_data      = avrc_get_data_ptr(p_pkt);
        *p_rsp_data     = AVRC_RSP_REJ;
#if (BT_USE_TRACES == TRUE)
        p_drop_msg = "rejected";
#endif
        cr      = AVCT_RSP;
        drop    = TRUE;
    }

    if (p_rsp)
    {
        /* set to send response right away */
        AVCT_MsgReq( handle, label, cr, p_rsp);
        free = FALSE;
        drop = TRUE;
    }

    if (drop == FALSE)
    {
        msg.hdr.opcode = opcode;
        (*avrc_cb.ccb[handle].p_msg_cback)(handle, label, opcode, &msg);
    }
#if (BT_USE_TRACES == TRUE)
    else
    {
        AVRC_TRACE_WARNING5("avrc_msg_cback %s msg handle:%d, control:%d, cr:%d, opcode:x%x",
                p_drop_msg,
                handle, avrc_cb.ccb[handle].control, cr, opcode);
    }
#endif


    if (free)
        GKI_freebuf(p_pkt);
}




/******************************************************************************
**
** Function         avrc_pass_msg
**
** Description      Compose a PASS THROUGH command according to p_msg
**
**                  Input Parameters:
**                      p_msg: Pointer to PASS THROUGH message structure.
**
**                  Output Parameters:
**                      None.
**
** Returns          pointer to a valid GKI buffer if successful.
**                  NULL if p_msg is NULL.
**
******************************************************************************/
static BT_HDR  * avrc_pass_msg(tAVRC_MSG_PASS *p_msg)
{
    BT_HDR  *p_cmd = NULL;
    UINT8   *p_data;

    WC_ASSERT(p_msg != NULL);
    WC_ASSERT(AVRC_CMD_POOL_SIZE > (AVRC_MIN_CMD_LEN+p_msg->pass_len));

    if ((p_cmd = (BT_HDR *) GKI_getpoolbuf(AVRC_CMD_POOL_ID)) != NULL)
    {
        p_cmd->offset   = AVCT_MSG_OFFSET;
        p_cmd->layer_specific   = AVCT_DATA_CTRL;
        p_data          = (UINT8 *)(p_cmd + 1) + p_cmd->offset;
        *p_data++       = (p_msg->hdr.ctype & AVRC_CTYPE_MASK);
        *p_data++       = (AVRC_SUB_PANEL << AVRC_SUBTYPE_SHIFT); /* Panel subunit & id=0 */
        *p_data++       = AVRC_OP_PASS_THRU;
        *p_data         = (AVRC_PASS_OP_ID_MASK&p_msg->op_id);
        if (p_msg->state)
            *p_data     |= AVRC_PASS_STATE_MASK;
        p_data++;

        if (p_msg->op_id == AVRC_ID_VENDOR)
        {
            *p_data++       = p_msg->pass_len;
            if (p_msg->pass_len && p_msg->p_pass_data)
            {
                memcpy(p_data, p_msg->p_pass_data, p_msg->pass_len);
                p_data += p_msg->pass_len;
            }
        }
        else /* set msg len to 0 for other op_id */
        {
            /* set msg len to 0 for other op_id */
            *p_data++       = 0;
        }
        p_cmd->len      = (UINT16) (p_data - (UINT8 *)(p_cmd + 1) - p_cmd->offset);
    }
    return p_cmd;
}

/******************************************************************************
**
** Function         AVRC_Open
**
** Description      This function is called to open a connection to AVCTP.
**                  The connection can be either an initiator or acceptor, as
**                  determined by the p_ccb->stream parameter.
**                  The connection can be a target, a controller or for both role,
**                  as determined by the p_ccb->control parameter.
**                  By definition, a target connection is an acceptor connection
**                  that waits for an incoming AVCTP connection from the peer.
**                  The connection remains available to the application until
**                  the application closes it by calling AVRC_Close().  The
**                  application does not need to reopen the connection after an
**                  AVRC_CLOSE_IND_EVT is received.
**
**                  Input Parameters:
**                      p_ccb->company_id: Company Identifier.
**
**                      p_ccb->p_ctrl_cback:  Pointer to control callback function.
**
**                      p_ccb->p_msg_cback:  Pointer to message callback function.
**
**                      p_ccb->conn: AVCTP connection role.  This is set to
**                      AVCTP_INT for initiator connections and AVCTP_ACP
**                      for acceptor connections.
**
**                      p_ccb->control: Control role.  This is set to
**                      AVRC_CT_TARGET for target connections, AVRC_CT_CONTROL
**                      for control connections or (AVRC_CT_TARGET|AVRC_CT_CONTROL)
**                      for connections that support both roles.
**
**                      peer_addr: BD address of peer device.  This value is
**                      only used for initiator connections; for acceptor
**                      connections it can be set to NULL.
**
**                  Output Parameters:
**                      p_handle: Pointer to handle.  This parameter is only
**                                valid if AVRC_SUCCESS is returned.
**
** Returns          AVRC_SUCCESS if successful.
**                  AVRC_NO_RESOURCES if there are not enough resources to open
**                  the connection.
**
******************************************************************************/
UINT16 AVRC_Open(UINT8 *p_handle, tAVRC_CONN_CB *p_ccb, BD_ADDR_PTR peer_addr)
{
    UINT16      status;
    tAVCT_CC    cc;

    cc.p_ctrl_cback = avrc_ctrl_cback;      /* Control callback */
    cc.p_msg_cback  = avrc_msg_cback;       /* Message callback */
    cc.pid          = UUID_SERVCLASS_AV_REMOTE_CONTROL;  /* Profile ID */
    cc.role         = p_ccb->conn;          /* Initiator/acceptor role */
    cc.control      = p_ccb->control;       /* Control role (Control/Target) */

    status = AVCT_CreateConn(p_handle, &cc, peer_addr);
    if (status == AVCT_SUCCESS)
    {
        memcpy(&avrc_cb.ccb[*p_handle], p_ccb, sizeof(tAVRC_CONN_CB));
    }
    AVRC_TRACE_DEBUG4("AVRC_Open role: %d, control:%d status:%d, handle:%d", cc.role, cc.control, status, *p_handle);

    return status;
}

/******************************************************************************
**
** Function         AVRC_Close
**
** Description      Close a connection opened with AVRC_Open().
**                  This function is called when the
**                  application is no longer using a connection.
**
**                  Input Parameters:
**                      handle: Handle of this connection.
**
**                  Output Parameters:
**                      None.
**
** Returns          AVRC_SUCCESS if successful.
**                  AVRC_BAD_HANDLE if handle is invalid.
**
******************************************************************************/
UINT16 AVRC_Close(UINT8 handle)
{
    AVRC_TRACE_DEBUG1("AVRC_Close handle:%d", handle);
    return AVCT_RemoveConn(handle);
}


/******************************************************************************
**
** Function         AVRC_MsgReq
**
** Description      This function is used to send the AVRCP byte stream in p_pkt
**                  down to AVCTP.
**
**                  It is expected that p_pkt->offset is at least AVCT_MSG_OFFSET
**                  p_pkt->layer_specific is AVCT_DATA_CTRL or AVCT_DATA_BROWSE
**                  p_pkt->event is AVRC_OP_VENDOR, AVRC_OP_PASS_THRU or AVRC_OP_BROWSE
**                  The above BT_HDR settings are set by the AVRC_Bld* functions.
**
** Returns          AVRC_SUCCESS if successful.
**                  AVRC_BAD_HANDLE if handle is invalid.
**
******************************************************************************/
UINT16 AVRC_MsgReq (UINT8 handle, UINT8 label, UINT8 ctype, BT_HDR *p_pkt)
{
    return AVRC_NO_RESOURCES;
}


/******************************************************************************
**
** Function         AVRC_PassCmd
**
** Description      Send a PASS THROUGH command to the peer device.  This
**                  function can only be called for controller role connections.
**                  Any response message from the peer is passed back through
**                  the tAVRC_MSG_CBACK callback function.
**
**                  Input Parameters:
**                      handle: Handle of this connection.
**
**                      label: Transaction label.
**
**                      p_msg: Pointer to PASS THROUGH message structure.
**
**                  Output Parameters:
**                      None.
**
** Returns          AVRC_SUCCESS if successful.
**                  AVRC_BAD_HANDLE if handle is invalid.
**
******************************************************************************/
UINT16 AVRC_PassCmd(UINT8 handle, UINT8 label, tAVRC_MSG_PASS *p_msg)
{
    BT_HDR *p_buf;
    WC_ASSERT(p_msg != NULL);
    if (p_msg)
    {
        p_msg->hdr.ctype    = AVRC_CMD_CTRL;
        p_buf = avrc_pass_msg(p_msg);
        if (p_buf)
            return AVCT_MsgReq( handle, label, AVCT_CMD, p_buf);
    }
    return AVRC_NO_RESOURCES;
}

/******************************************************************************
**
** Function         AVRC_PassRsp
**
** Description      Send a PASS THROUGH response to the peer device.  This
**                  function can only be called for target role connections.
**                  This function must be called when a PASS THROUGH command
**                  message is received from the peer through the
**                  tAVRC_MSG_CBACK callback function.
**
**                  Input Parameters:
**                      handle: Handle of this connection.
**
**                      label: Transaction label.  Must be the same value as
**                      passed with the command message in the callback function.
**
**                      p_msg: Pointer to PASS THROUGH message structure.
**
**                  Output Parameters:
**                      None.
**
** Returns          AVRC_SUCCESS if successful.
**                  AVRC_BAD_HANDLE if handle is invalid.
**
******************************************************************************/
UINT16 AVRC_PassRsp(UINT8 handle, UINT8 label, tAVRC_MSG_PASS *p_msg)
{
    BT_HDR *p_buf;
    WC_ASSERT(p_msg != NULL);
    if (p_msg)
    {
        p_buf = avrc_pass_msg(p_msg);
        if (p_buf)
            return AVCT_MsgReq( handle, label, AVCT_RSP, p_buf);
    }
    return AVRC_NO_RESOURCES;
}

