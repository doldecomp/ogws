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
 *  this file contains GATT authentication handling functions
 *
 ******************************************************************************/
#include "bt_target.h"

#if BLE_INCLUDED == TRUE
#include <string.h>
#include "gki.h"

#include "gatt_int.h"
#include "gatt_api.h"
#include "btm_int.h"

/*******************************************************************************
**
** Function         gatt_sign_data
**
** Description      This function sign the data for write command.
**
** Returns          TRUE if encrypted, otherwise FALSE.
**
*******************************************************************************/
static BOOLEAN gatt_sign_data (tGATT_CLCB *p_clcb)
{
    tGATT_VALUE         *p_attr = (tGATT_VALUE *)p_clcb->p_attr_buf;
    UINT8               *p_data = NULL, *p;
    UINT16              payload_size = p_clcb->p_tcb->payload_size;
    BOOLEAN             status = FALSE;
    UINT8                *p_signature;

    p_data = (UINT8 *)GKI_getbuf((UINT16)(p_attr->len + 3)); /* 3 = 2 byte handle + opcode */

    if (p_data != NULL)
    {
        p = p_data;
        UINT8_TO_STREAM(p, GATT_SIGN_CMD_WRITE);
        UINT16_TO_STREAM(p, p_attr->handle);
        ARRAY_TO_STREAM(p, p_attr->value, p_attr->len);

        /* sign data length should be attribulte value length plus 2B handle + 1B op code */
        if ((payload_size - GATT_AUTH_SIGN_LEN - 3) < p_attr->len)
            p_attr->len = payload_size - GATT_AUTH_SIGN_LEN - 3;

        p_signature = p_attr->value + p_attr->len;
        if (BTM_BleDataSignature(p_clcb->p_tcb->peer_bda,
                                p_data,
                                (UINT16)(p_attr->len + 3), /* 3 = 2 byte handle + opcode */
                                p_signature))
        {
            p_attr->len += BTM_BLE_AUTH_SIGN_LEN;
            gatt_set_ch_state(p_clcb->p_tcb, GATT_CH_OPEN);
            gatt_act_write(p_clcb);
        }
        else
        {
            gatt_end_operation(p_clcb, GATT_INTERNAL_ERROR, NULL);
        }

        GKI_freebuf(p_data);
    }

    return status;
}

/*******************************************************************************
**
** Function         gatt_verify_signature
**
** Description      This function start to verify the sign data when receiving
**                  the data from peer device.
**
** Returns
**
*******************************************************************************/
void gatt_verify_signature(tGATT_TCB *p_tcb, BT_HDR *p_buf)
{
    UINT16  cmd_len;
    UINT8   op_code;
    UINT8   *p, *p_orig = (UINT8 *)(p_buf + 1) + p_buf->offset;
    UINT32  counter;

    cmd_len = p_buf->len - GATT_AUTH_SIGN_LEN + 4;
    p =  p_orig + cmd_len - 4;
    STREAM_TO_UINT32(counter, p);

    if (BTM_BleVerifySignature(p_tcb->peer_bda, p_orig, cmd_len, counter, p))
    {
        STREAM_TO_UINT8(op_code, p_orig);
        gatt_server_handle_client_req (p_tcb, op_code, (UINT16)(p_buf->len - 1), p_orig);
    }
    else
    {
        /* if this is a bad signature, assume from attacker, ignore it */
        GATT_TRACE_ERROR0("Signature Verification Failed");
        gatt_disconnect(p_tcb->peer_bda);
    }

    return;
}
/*******************************************************************************
**
** Function         gatt_sec_check_complete
**
** Description      security check complete and proceed to data sending action.
**
** Returns          void.
**
*******************************************************************************/
void gatt_sec_check_complete(BOOLEAN sec_check_ok, tGATT_CLCB   *p_clcb)
{
    p_clcb->p_tcb->p_clcb = NULL;
    gatt_set_sec_act(p_clcb->p_tcb, GATT_SEC_NONE);

    if (!sec_check_ok)
    {
        gatt_end_operation(p_clcb, GATT_AUTH_FAIL, NULL);
    }
    else if (p_clcb->operation == GATTC_OPTYPE_WRITE)
    {
        gatt_act_write(p_clcb);
    }
    else if (p_clcb->operation == GATTC_OPTYPE_READ)
    {
        gatt_act_read(p_clcb, p_clcb->counter);
    }
}
/*******************************************************************************
**
** Function         gatt_enc_cmpl_cback
**
** Description      link encryption complete callback.
**
** Returns
**
*******************************************************************************/
void gatt_enc_cmpl_cback(BD_ADDR bd_addr, void *p_ref_data, tBTM_STATUS result)
{
    tGATT_TCB   *p_tcb;
    UINT8       sec_flag;
    BOOLEAN     status = FALSE;

    GATT_TRACE_DEBUG0("gatt_enc_cmpl_cback");
    if ((p_tcb = gatt_find_tcb_by_addr(bd_addr)) != NULL)
    {
        gatt_set_ch_state(p_tcb, GATT_CH_OPEN);

        if (result == BTM_SUCCESS)
        {
            if (gatt_get_sec_act(p_tcb) == GATT_SEC_ENCRYPT_MITM )
            {
                BTM_GetSecurityFlags(bd_addr, &sec_flag);
                if (sec_flag & sec_flag & BTM_SEC_FLAG_LKEY_AUTHED)
                {
                    status = TRUE;
                }
            }
            else
            {
                status = TRUE;
            }
        }
        gatt_sec_check_complete(status , (tGATT_CLCB   *)p_tcb->p_clcb);
    }
    else
    {
        GATT_TRACE_ERROR0("enc callback for unknown bd_addr");
    }
}

/*******************************************************************************
**
** Function         gatt_set_sec_act
**
** Description      This function set the sec_act in clcb
**
** Returns          none
**
*******************************************************************************/
void gatt_set_sec_act(tGATT_TCB *p_tcb, tGATT_SEC_ACTION sec_act)
{
    if (p_tcb)
    {
        p_tcb->sec_act = sec_act;
    }
}
/*******************************************************************************
**
** Function         gatt_get_sec_act
**
** Description      This function get the sec_act in clcb
**
** Returns          none
**
*******************************************************************************/
tGATT_SEC_ACTION gatt_get_sec_act(tGATT_TCB *p_tcb)
{
    tGATT_SEC_ACTION sec_act = GATT_SEC_NONE;
    if (p_tcb)
    {
        sec_act = p_tcb->sec_act;
    }
    return sec_act;
}
/*******************************************************************************
**
** Function         gatt_determine_sec_act
**
** Description      This routine determine the security action based on auth_request and
**                  current link status
**
** Returns          tGATT_SEC_ACTION security action
**
*******************************************************************************/
tGATT_SEC_ACTION gatt_determine_sec_act(tGATT_CLCB *p_clcb )
{
    tGATT_SEC_ACTION    act = GATT_SEC_OK;
    UINT8               sec_flag;
    tGATT_TCB           *p_tcb = p_clcb->p_tcb;
    tGATT_AUTH_REQ      auth_req = p_clcb->auth_req;

    BOOLEAN             is_link_encrypted= FALSE;
    BOOLEAN             is_le_link=FALSE;
    BOOLEAN             is_link_key_known=FALSE;
    BOOLEAN             is_key_mitm=FALSE;
    UINT8               key_type;

    if (auth_req == GATT_AUTH_REQ_NONE )
        return act;

    is_le_link = btm_ble_check_link_type(p_tcb->peer_bda);
    BTM_GetSecurityFlags(p_tcb->peer_bda, &sec_flag);

    if (sec_flag & BTM_SEC_FLAG_ENCRYPTED)
    {
        is_link_encrypted = TRUE;
    }
    if (sec_flag & BTM_SEC_FLAG_LKEY_KNOWN)
    {
        is_link_key_known = TRUE;
        if (sec_flag & BTM_SEC_FLAG_LKEY_AUTHED)
        {
            is_key_mitm = TRUE;
        }
    }

    /* first check link key upgrade required or not */
    switch (auth_req)
    {
        case GATT_AUTH_REQ_MITM:
        case GATT_AUTH_REQ_SIGNED_MITM:
            if (!is_key_mitm)
                act = GATT_SEC_ENCRYPT_MITM;
            break;

        case GATT_AUTH_REQ_NO_MITM:
        case GATT_AUTH_REQ_SIGNED_NO_MITM:
            if (!is_link_key_known)
                act = GATT_SEC_ENCRYPT_NO_MITM;
            break;
        default:
            break;
    }

    /* now check link needs to be encrypted or not if the link key upgrade is not required */
    if (act == GATT_SEC_OK)
    {
        if (is_le_link &&
            (p_clcb->operation == GATTC_OPTYPE_WRITE) &&
            (p_clcb->op_subtype == GATT_WRITE_NO_RSP))
        {
            /* this is a write command request
               check data signing required or not */
            if (!is_link_encrypted)
            {
                btm_ble_get_enc_key_type(p_tcb->peer_bda, &key_type);

                if ( (key_type & BTM_LE_KEY_LCSRK) &&
                     ((auth_req == GATT_AUTH_REQ_SIGNED_NO_MITM) ||
                      (auth_req == GATT_AUTH_REQ_SIGNED_MITM)))
                {
                    act = GATT_SEC_SIGN_DATA;
                }
                else
                {
                    act = GATT_SEC_ENCRYPT;
                }
            }
        }
        else
        {
            if (!is_link_encrypted)
            {
                act = GATT_SEC_ENCRYPT;
            }
        }

    }

    return  act ;

}



/*******************************************************************************
**
** Function         gatt_get_link_encrypt_status
**
** Description      This routine get the encryption status of the specified link
**
**
** Returns          tGATT_STATUS link encryption status
**
*******************************************************************************/
tGATT_STATUS gatt_get_link_encrypt_status(tGATT_TCB *p_tcb)
{
    tGATT_STATUS    encrypt_status = GATT_NOT_ENCRYPTED;
    UINT8           sec_flag=0;

    BTM_GetSecurityFlags(p_tcb->peer_bda, &sec_flag);

    if ((sec_flag & BTM_SEC_FLAG_ENCRYPTED) && (sec_flag & BTM_SEC_FLAG_LKEY_KNOWN))
    {
        encrypt_status = GATT_ENCRYPED_NO_MITM;
        if (sec_flag & BTM_SEC_FLAG_LKEY_AUTHED)
            encrypt_status = GATT_ENCRYPED_MITM;
    }

    GATT_TRACE_DEBUG1("gatt_get_link_encrypt_status status=0x%x",encrypt_status);
    return  encrypt_status ;
}


/*******************************************************************************
**
** Function          gatt_convert_sec_action
**
** Description      Convert GATT security action enum into equivalent BTM BLE security action enum
**
** Returns          BOOLEAN TRUE - conversation is successful
**
*******************************************************************************/
static BOOLEAN gatt_convert_sec_action(tGATT_SEC_ACTION gatt_sec_act, tBTM_BLE_SEC_ACT *p_btm_sec_act )
{
    BOOLEAN status = TRUE;
    switch (gatt_sec_act)
    {
        case GATT_SEC_ENCRYPT:
            *p_btm_sec_act = BTM_BLE_SEC_ENCRYPT;
            break;
        case GATT_SEC_ENCRYPT_NO_MITM:
            *p_btm_sec_act = BTM_BLE_SEC_ENCRYPT_NO_MITM;
            break;
        case GATT_SEC_ENCRYPT_MITM:
            *p_btm_sec_act = BTM_BLE_SEC_ENCRYPT_MITM;
            break;
        default:
            status = FALSE;
            break;
    }

    return status;
}
/*******************************************************************************
**
** Function         gatt_check_enc_req
**
** Description      check link security.
**
** Returns          TRUE if encrypted, otherwise FALSE.
**
*******************************************************************************/
BOOLEAN gatt_security_check_start(tGATT_CLCB *p_clcb)
{
    tGATT_TCB           *p_tcb = p_clcb->p_tcb;
    tGATT_SEC_ACTION    gatt_sec_act;
    tBTM_BLE_SEC_ACT    btm_ble_sec_act;
    BOOLEAN             status = TRUE;
    tBTM_STATUS         btm_status;

    if ( gatt_get_ch_state(p_tcb) == GATT_CH_OPEN)
    {
        gatt_sec_act = gatt_determine_sec_act(p_clcb);
        gatt_set_sec_act(p_tcb, gatt_sec_act);
        switch (gatt_sec_act )
        {
            case GATT_SEC_SIGN_DATA:
                GATT_TRACE_DEBUG0("gatt_security_check_start: Do data signing");
                gatt_set_ch_state(p_tcb, GATT_CH_W4_DATA_SIGN_COMP);
                gatt_sign_data(p_clcb);
                break;
            case GATT_SEC_ENCRYPT:
            case GATT_SEC_ENCRYPT_NO_MITM:
            case GATT_SEC_ENCRYPT_MITM:
                GATT_TRACE_DEBUG0("gatt_security_check_start: Encrypt now or key upgreade first");
                gatt_convert_sec_action(p_tcb->sec_act, &btm_ble_sec_act);
                gatt_set_ch_state(p_tcb, GATT_CH_W4_SEC_COMP);
                p_tcb->p_clcb = p_clcb;           /* keep the clcb pointer in CCB */
                btm_status = BTM_SetEncryption(p_tcb->peer_bda, gatt_enc_cmpl_cback, &btm_ble_sec_act);
                if ( (btm_status != BTM_SUCCESS) && (btm_status != BTM_CMD_STARTED))
                {
                    GATT_TRACE_ERROR1("gatt_security_check_start BTM_SetEncryption failed btm_status=%d", btm_status);
                    p_tcb->p_clcb  = NULL;
                    status = FALSE;
                }
                break;
            default:
                gatt_sec_check_complete(TRUE, p_clcb);
                break;
        }

        if (status == FALSE)
        {
            gatt_set_sec_act(p_tcb, GATT_SEC_NONE);
            gatt_set_ch_state(p_tcb, GATT_CH_OPEN);
        }
    }
    else
    {
        GATT_TRACE_ERROR0("gatt_security_check_start channel not open");
        status = FALSE;
    }

    return status;
}


#endif  /* BLE_INCLUDED */
