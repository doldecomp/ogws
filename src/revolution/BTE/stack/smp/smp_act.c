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

#include "bt_target.h"

#if SMP_INCLUDED == TRUE

    #include <string.h>
    #include "btm_int.h"
    #include "l2c_api.h"
    #include "smp_int.h"


const UINT8 smp_association_table[2][SMP_IO_CAP_MAX][SMP_IO_CAP_MAX] =
{
    /* initiator */
    {{SMP_MODEL_ENC_ONLY, SMP_MODEL_ENC_ONLY,   SMP_MODEL_PASSKEY,   SMP_MODEL_ENC_ONLY,    SMP_MODEL_PASSKEY}, /* Display Only */
        {SMP_MODEL_ENC_ONLY,  SMP_MODEL_ENC_ONLY,   SMP_MODEL_PASSKEY,   SMP_MODEL_ENC_ONLY,    SMP_MODEL_PASSKEY}, /* SMP_CAP_IO = 1 */
        {SMP_MODEL_KEY_NOTIF, SMP_MODEL_KEY_NOTIF,  SMP_MODEL_PASSKEY,   SMP_MODEL_ENC_ONLY,    SMP_MODEL_KEY_NOTIF}, /* keyboard only */
        {SMP_MODEL_ENC_ONLY,  SMP_MODEL_ENC_ONLY,   SMP_MODEL_ENC_ONLY,  SMP_MODEL_ENC_ONLY,    SMP_MODEL_ENC_ONLY},/* No Input No Output */
        {SMP_MODEL_KEY_NOTIF, SMP_MODEL_KEY_NOTIF,  SMP_MODEL_PASSKEY,   SMP_MODEL_ENC_ONLY,    SMP_MODEL_KEY_NOTIF}}, /* keyboard display */
    /* responder */
    {{SMP_MODEL_ENC_ONLY, SMP_MODEL_ENC_ONLY,   SMP_MODEL_KEY_NOTIF, SMP_MODEL_ENC_ONLY,    SMP_MODEL_KEY_NOTIF}, /* Display Only */
        {SMP_MODEL_ENC_ONLY,  SMP_MODEL_ENC_ONLY,   SMP_MODEL_PASSKEY,   SMP_MODEL_ENC_ONLY,    SMP_MODEL_KEY_NOTIF}, /* SMP_CAP_IO = 1 */
        {SMP_MODEL_PASSKEY,   SMP_MODEL_PASSKEY,    SMP_MODEL_PASSKEY,   SMP_MODEL_ENC_ONLY,    SMP_MODEL_PASSKEY}, /* keyboard only */
        {SMP_MODEL_ENC_ONLY,  SMP_MODEL_ENC_ONLY,   SMP_MODEL_ENC_ONLY,  SMP_MODEL_ENC_ONLY,    SMP_MODEL_ENC_ONLY},/* No Input No Output */
        {SMP_MODEL_PASSKEY,   SMP_MODEL_PASSKEY,    SMP_MODEL_KEY_NOTIF, SMP_MODEL_ENC_ONLY,    SMP_MODEL_PASSKEY}} /* keyboard display */
    /* display only */    /*SMP_CAP_IO = 1 */  /* keyboard only */   /* No InputOutput */  /* keyboard display */
};

const tSMP_ACT smp_distribute_act [] =
{
    smp_generate_ltk,
    smp_send_id_info,
    smp_generate_csrk
};

/*******************************************************************************
** Function         smp_update_key_mask
** Description      This function updates the key mask for sending or receiving.
*******************************************************************************/
static void smp_update_key_mask (tSMP_CB *p_cb, UINT8 key_type, BOOLEAN recv)
{
    SMP_TRACE_DEBUG0 ("smp_update_key_mask ");
    SMP_TRACE_DEBUG4("before update role=%d recv=%d loc_i_key = %02x, loc_r_key = %02x", p_cb->role, recv, p_cb->loc_i_key, p_cb->loc_r_key);
    if (p_cb->role == HCI_ROLE_SLAVE)
    {
        if (recv)
            p_cb->loc_i_key &= ~key_type;
        else
            p_cb->loc_r_key &= ~key_type;
    }
    else
    {
        if (recv)
            p_cb->loc_r_key &= ~key_type;
        else
            p_cb->loc_i_key &= ~key_type;
    }

    SMP_TRACE_DEBUG2("updated loc_i_key = %02x, loc_r_key = %02x", p_cb->loc_i_key, p_cb->loc_r_key);
}
/*******************************************************************************
** Function     smp_io_cap_req
** Description  send SMP IO request
*******************************************************************************/
void smp_send_app_cback(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    tSMP_EVT_DATA   cb_data;
    tSMP_STATUS callback_rc;
    SMP_TRACE_DEBUG1 ("smp_send_app_cback p_cb->cb_evt=%d", p_cb->cb_evt );
    if (p_cb->p_callback && p_cb->cb_evt != 0)
    {
        if (p_cb->cb_evt == SMP_IO_CAP_REQ_EVT)
        {
            cb_data.io_req.auth_req = p_cb->peer_auth_req;
            cb_data.io_req.oob_data = SMP_OOB_NONE;
            cb_data.io_req.io_cap = SMP_DEFAULT_IO_CAPS;
            cb_data.io_req.max_key_size = SMP_MAX_ENC_KEY_SIZE;
            cb_data.io_req.init_keys = p_cb->loc_i_key ;
            cb_data.io_req.resp_keys = p_cb->loc_r_key ;

            SMP_TRACE_WARNING1( "io_cap = %d",cb_data.io_req.io_cap);
        }
        callback_rc = (*p_cb->p_callback)(p_cb->cb_evt, p_cb->pairing_bda, &cb_data);

        SMP_TRACE_DEBUG2 ("callback_rc=%d  p_cb->cb_evt=%d",callback_rc, p_cb->cb_evt );

        if (callback_rc == SMP_SUCCESS && p_cb->cb_evt == SMP_IO_CAP_REQ_EVT)
        {
            p_cb->loc_auth_req   = cb_data.io_req.auth_req;
            p_cb->loc_io_caps    = cb_data.io_req.io_cap;
            p_cb->loc_oob_flag   = cb_data.io_req.oob_data;
            p_cb->loc_enc_size   = cb_data.io_req.max_key_size;
            p_cb->loc_i_key      = cb_data.io_req.init_keys;
            p_cb->loc_r_key      = cb_data.io_req.resp_keys;

            SMP_TRACE_WARNING2( "new io_cap = %d p_cb->loc_enc_size = %d",p_cb->loc_io_caps, p_cb->loc_enc_size);

            smp_sm_event(p_cb, SMP_IO_RSP_EVT, NULL);
        }
    }

    if (!p_cb->cb_evt && p_cb->discard_sec_req)
    {
        p_cb->discard_sec_req = FALSE;
        smp_sm_event(p_cb, SMP_DISCARD_SEC_REQ_EVT, NULL);
    }
    SMP_TRACE_DEBUG0 ("smp_send_app_cback return");
}
/*******************************************************************************
** Function     smp_send_pair_fail
** Description  pairing failure to peer device if needed.
*******************************************************************************/
void smp_send_pair_fail(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    p_cb->status = *(UINT8 *)p_data;
    p_cb->failure = *(UINT8 *)p_data;

    SMP_TRACE_DEBUG2 ("smp_send_pair_fail status=%d failure=%d ",p_cb->status, p_cb->failure);

    if (p_cb->status <= SMP_REPEATED_ATTEMPTS && p_cb->status != SMP_SUCCESS)
    {
        smp_send_cmd(SMP_OPCODE_PAIRING_FAILED, p_cb);
    }
}

/*******************************************************************************
** Function     smp_send_pair_req
** Description  process pairing request to slave device
*******************************************************************************/
void smp_send_pair_req(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev (p_cb->pairing_bda);
    SMP_TRACE_DEBUG0 ("smp_send_pair_req  ");

    /* erase all keys when master sends pairing req*/
    if (p_dev_rec)
        btm_sec_clear_ble_keys(p_dev_rec);
    /* do not manipulate the key, let app decide,
       leave out to BTM to mandate key distribution for bonding case */
    smp_send_cmd(SMP_OPCODE_PAIRING_REQ, p_cb);
}
/*******************************************************************************
** Function     smp_send_pair_rsp
** Description  process pairing response to slave device
*******************************************************************************/
void smp_send_pair_rsp(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_send_pair_rsp  ");

    p_cb->loc_i_key &= p_cb->peer_i_key;
    p_cb->loc_r_key &= p_cb->peer_r_key;

    if (smp_send_cmd (SMP_OPCODE_PAIRING_RSP, p_cb))
    {
        smp_decide_asso_model(p_cb, NULL);
    }
}

/*******************************************************************************
** Function     smp_send_pair_request
** Description  process pairing request to slave device
*******************************************************************************/
void smp_send_confirm(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_send_confirm  ");
    smp_send_cmd(SMP_OPCODE_CONFIRM, p_cb);
}
/*******************************************************************************
** Function     smp_send_init
** Description  process pairing initializer to slave device
*******************************************************************************/
void smp_send_init(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_send_init  ");

#if SMP_CONFORMANCE_TESTING == TRUE
    if (p_cb->enable_test_rand_val)
    {
        SMP_TRACE_DEBUG0 ("Use rand value from script");
        memcpy(p_cb->rand, p_cb->test_rand, BT_OCTET16_LEN);
    }
#endif

    smp_send_cmd(SMP_OPCODE_INIT, p_cb);
}
/*******************************************************************************
** Function     smp_send_enc_info
** Description  send security information command.
*******************************************************************************/
void smp_send_enc_info(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    tBTM_LE_LENC_KEYS   le_key;

    SMP_TRACE_DEBUG1 ("smp_send_enc_info  p_cb->loc_enc_size = %d", p_cb->loc_enc_size);
    smp_update_key_mask (p_cb, SMP_SEC_KEY_TYPE_ENC, FALSE);

    smp_send_cmd(SMP_OPCODE_ENCRYPT_INFO, p_cb);
    smp_send_cmd(SMP_OPCODE_MASTER_ID, p_cb);

    /* save the DIV and key size information when acting as slave device */
    le_key.div =  p_cb->div;
    le_key.key_size = p_cb->loc_enc_size;
    le_key.sec_level = p_cb->sec_level;
    btm_sec_save_le_key(p_cb->pairing_bda, BTM_LE_KEY_LENC, (tBTM_LE_KEY_VALUE *)&le_key, TRUE);

    SMP_TRACE_WARNING0( "smp_send_enc_info");

    smp_key_distribution(p_cb, NULL);
}
/*******************************************************************************
** Function     smp_send_id_info
** Description  send ID information command.
*******************************************************************************/
void smp_send_id_info(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_send_id_info  ");
    smp_update_key_mask (p_cb, SMP_SEC_KEY_TYPE_ID, FALSE);

    smp_send_cmd(SMP_OPCODE_IDENTITY_INFO, p_cb);
    smp_send_cmd(SMP_OPCODE_ID_ADDR, p_cb);

    SMP_TRACE_WARNING0( "smp_send_id_info");

    smp_key_distribution(p_cb, NULL);
}
/*******************************************************************************
** Function     smp_send_csrk_info
** Description  send CSRK command.
*******************************************************************************/
void smp_send_csrk_info(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    tBTM_LE_KEY_VALUE   key;
    SMP_TRACE_DEBUG0 ("smp_send_csrk_info ");
    smp_update_key_mask (p_cb, SMP_SEC_KEY_TYPE_CSRK, FALSE);

    if (smp_send_cmd(SMP_OPCODE_SIGN_INFO, p_cb))
    {
        key.lcsrk_key.div = p_cb->div;
        key.lcsrk_key.sec_level = p_cb->sec_level;
        key.lcsrk_key.counter = 0; /* initialize the local counter */
        btm_sec_save_le_key(p_cb->pairing_bda, BTM_LE_KEY_LCSRK, &key, TRUE);
    }

    smp_key_distribution(p_cb, NULL);
}

/*******************************************************************************
** Function     smp_send_ltk_reply
** Description  send LTK reply
*******************************************************************************/
void smp_send_ltk_reply(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_send_ltk_reply ");
    /* send stk as LTK response */
    btm_ble_ltk_request_reply(p_cb->pairing_bda, TRUE, p_data->key.p_data);
}
/*******************************************************************************
** Function     smp_proc_sec_req
** Description  process security request.
*******************************************************************************/
void smp_proc_sec_req(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    tBTM_LE_AUTH_REQ        auth_req = *(tBTM_LE_AUTH_REQ *)p_data;
    tBTM_BLE_SEC_REQ_ACT    sec_req_act;


    SMP_TRACE_DEBUG1 ("smp_proc_sec_req  auth_req=0x%x",auth_req);

    p_cb->cb_evt = 0;

    btm_ble_link_sec_check(p_cb->pairing_bda, auth_req,  &sec_req_act);

    SMP_TRACE_DEBUG1 ("smp_proc_sec_req  sec_req_act=0x%x",sec_req_act);

    switch (sec_req_act)
    {
        case  BTM_BLE_SEC_REQ_ACT_ENCRYPT:
            SMP_TRACE_DEBUG0 ("smp_proc_sec_req BTM_BLE_SEC_REQ_ACT_ENCRYPT");
            smp_sm_event(p_cb, SMP_ENC_REQ_EVT, NULL);
            break;

        case BTM_BLE_SEC_REQ_ACT_PAIR:
            /* initialize local i/r key to be default keys */
            SMP_TRACE_DEBUG0 ("smp_proc_sec_req BTM_BLE_SEC_REQ_ACT_PAIR");
            p_cb->peer_auth_req = auth_req;
            p_cb->loc_r_key = p_cb->loc_i_key = SMP_SEC_DEFAULT_KEY ;
            p_cb->cb_evt = SMP_SEC_REQUEST_EVT;
            break;

        case BTM_BLE_SEC_REQ_ACT_DISCARD:
            p_cb->discard_sec_req = TRUE;
            break;

        default:
            /* do nothing */
            break;
    }
}
/*******************************************************************************
** Function     smp_proc_sec_grant
** Description  process security grant.
*******************************************************************************/
void smp_proc_sec_grant(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8 res= *(UINT8 *)p_data;
    SMP_TRACE_DEBUG0 ("smp_proc_sec_grant ");
    if (res != SMP_SUCCESS)
    {
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, p_data);
    }
    else /*otherwise, start pairing */
    {
        /* send IO request callback */
        p_cb->cb_evt = SMP_IO_CAP_REQ_EVT;
    }
}
/*******************************************************************************
** Function     smp_proc_pair_fail
** Description  process pairing failure from peer device
*******************************************************************************/
void smp_proc_pair_fail(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_proc_pair_fail   ");
    p_cb->status = *(UINT8 *)p_data;
}
/*******************************************************************************
** Function     smp_proc_pair_cmd
** Description  Process the SMP pairing request/response from peer device
*******************************************************************************/
void smp_proc_pair_cmd(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8   *p = (UINT8 *)p_data;
    UINT8   reason = SMP_ENC_KEY_SIZE;
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev (p_cb->pairing_bda);

    SMP_TRACE_DEBUG0 ("smp_proc_pair_cmd  ");
    /* erase all keys if it is slave proc pairing req*/
    if (p_dev_rec && (p_cb->role == HCI_ROLE_SLAVE))
        btm_sec_clear_ble_keys(p_dev_rec);

    p_cb->flags |= SMP_PAIR_FLAG_ENC_AFTER_PAIR;

    STREAM_TO_UINT8(p_cb->peer_io_caps, p);
    STREAM_TO_UINT8(p_cb->peer_oob_flag, p);
    STREAM_TO_UINT8(p_cb->peer_auth_req, p);
    STREAM_TO_UINT8(p_cb->peer_enc_size, p);
    STREAM_TO_UINT8(p_cb->peer_i_key, p);
    STREAM_TO_UINT8(p_cb->peer_r_key, p);

#if SMP_CONFORMANCE_TESTING == TRUE
    if (p_cb->enable_test_pair_fail)
    {
        SMP_TRACE_DEBUG0 ("Forced pair fair");
        if (p_cb->peer_enc_size < SMP_MIN_ENC_KEY_SIZE)
        {
            smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &reason);
        }
        else
        {
            smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &(p_cb->pair_fail_status));
        }
        return;
    }
#endif


    if (p_cb->peer_enc_size < SMP_MIN_ENC_KEY_SIZE)
    {
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &reason);
    }
    else if (p_cb->role == HCI_ROLE_SLAVE)
    {
        if (!(p_cb->flags & SMP_PAIR_FLAGS_WE_STARTED_DD))
        {
            p_cb->loc_i_key = p_cb->peer_i_key;
            p_cb->loc_r_key = p_cb->peer_r_key;
        }
        else /* update local i/r key according to pairing request */
        {
            p_cb->loc_i_key &= p_cb->peer_i_key;
            p_cb->loc_r_key &= p_cb->peer_r_key;
        }

        p_cb->cb_evt = SMP_SEC_REQUEST_EVT;
    }
}
/*******************************************************************************
** Function     smp_proc_confirm
** Description  process pairing confirm from peer device
*******************************************************************************/
void smp_proc_confirm(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8 *p = (UINT8 *)p_data;

    SMP_TRACE_DEBUG0 ("smp_proc_confirm  ");
    if (p != NULL)
    {
        /* save the SConfirm for comparison later */
        STREAM_TO_ARRAY(p_cb->rconfirm, p, BT_OCTET16_LEN);
    }

    p_cb->flags |= SMP_PAIR_FLAGS_CMD_CONFIRM;
}

/*******************************************************************************
** Function     smp_proc_init
** Description  process pairing initializer from peer device
*******************************************************************************/
void smp_proc_init(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8 *p = (UINT8 *)p_data;
    SMP_TRACE_DEBUG0 ("smp_proc_init ");
    /* save the SRand for comparison */
    STREAM_TO_ARRAY(p_cb->rrand, p, BT_OCTET16_LEN);

}
/*******************************************************************************
** Function     smp_proc_enc_info
** Description  process encryption information from peer device
*******************************************************************************/
void smp_proc_enc_info(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8   *p = (UINT8 *)p_data;

    SMP_TRACE_DEBUG0 ("smp_proc_enc_info  ");
    STREAM_TO_ARRAY(p_cb->ltk, p, BT_OCTET16_LEN);

    smp_key_distribution(p_cb, NULL);
}
/*******************************************************************************
** Function     smp_proc_master_id
** Description  process master ID from slave device
*******************************************************************************/
void smp_proc_master_id(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8   *p = (UINT8 *)p_data;
    tBTM_LE_PENC_KEYS   le_key;

    SMP_TRACE_DEBUG0 (" smp_proc_master_id");
    smp_update_key_mask (p_cb, SMP_SEC_KEY_TYPE_ENC, TRUE);

    STREAM_TO_UINT16(le_key.ediv, p);
    STREAM_TO_ARRAY(le_key.rand, p, BT_OCTET8_LEN );

    /* store the encryption keys from peer device */
    memcpy(le_key.ltk, p_cb->ltk, BT_OCTET16_LEN);
    le_key.sec_level = p_cb->sec_level;
    le_key.key_size  = p_cb->loc_enc_size;
    btm_sec_save_le_key(p_cb->pairing_bda, BTM_LE_KEY_PENC, (tBTM_LE_KEY_VALUE *)&le_key, TRUE);

    smp_key_distribution(p_cb, NULL);
}
/*******************************************************************************
** Function     smp_proc_enc_info
** Description  process identity information from peer device
*******************************************************************************/
void smp_proc_id_info(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8   *p = (UINT8 *)p_data;

    SMP_TRACE_DEBUG0 ("smp_proc_id_info ");
    STREAM_TO_ARRAY (p_cb->tk, p, BT_OCTET16_LEN);   /* reuse TK for IRK */
    /* store the ID key from peer device */
    btm_sec_save_le_key(p_cb->pairing_bda, BTM_LE_KEY_PID, (tBTM_LE_KEY_VALUE *)&p_cb->tk, TRUE);

    smp_key_distribution(p_cb, NULL);
}
/*******************************************************************************
** Function     smp_proc_id_addr
** Description  process identity address from peer device
*******************************************************************************/
void smp_proc_id_addr(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8   *p = (UINT8 *)p_data;
    BD_ADDR    mac_bda;

    SMP_TRACE_DEBUG0 ("smp_proc_id_addr  ");
    smp_update_key_mask (p_cb, SMP_SEC_KEY_TYPE_ID, TRUE);

    STREAM_TO_BDADDR(mac_bda, p);

    /* TODO, update MAC address */

    smp_key_distribution(p_cb, NULL);
}
/*******************************************************************************
** Function     smp_proc_srk_info
** Description  process security information from peer device
*******************************************************************************/
void smp_proc_srk_info(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    tBTM_LE_PCSRK_KEYS   le_key;

    SMP_TRACE_DEBUG0 ("smp_proc_srk_info ");
    smp_update_key_mask (p_cb, SMP_SEC_KEY_TYPE_CSRK, TRUE);

    /* save CSRK to security record */
    le_key.sec_level = p_cb->sec_level;
    memcpy (le_key.csrk, p_data, BT_OCTET16_LEN);   /* get peer CSRK */
    le_key.counter = 0; /* initialize the peer counter */
    btm_sec_save_le_key(p_cb->pairing_bda, BTM_LE_KEY_PCSRK, (tBTM_LE_KEY_VALUE *)&le_key, TRUE);

    smp_key_distribution(p_cb, NULL);
}

/*******************************************************************************
** Function     smp_proc_compare
** Description  process compare value
*******************************************************************************/
void smp_proc_compare(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8   reason;

    SMP_TRACE_DEBUG0 ("smp_proc_compare  ");
    if (!memcmp(p_cb->rconfirm, p_data->key.p_data, BT_OCTET16_LEN))
    {
        /* compare the max encryption key size, and save the smaller one for the link */
        if ( p_cb->peer_enc_size < p_cb->loc_enc_size)
            p_cb->loc_enc_size = p_cb->peer_enc_size;

        if (p_cb->role == HCI_ROLE_SLAVE)
            smp_sm_event(p_cb, SMP_RAND_EVT, NULL);
        else
        {
            /* master device always use received i/r key as keys to distribute */
            p_cb->loc_i_key = p_cb->peer_i_key;
            p_cb->loc_r_key = p_cb->peer_r_key;

            smp_sm_event(p_cb, SMP_ENC_REQ_EVT, NULL);
        }

    }
    else
    {
        reason = p_cb->failure = SMP_CONFIRM_VALUE_ERR;
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &reason);
    }
}
/*******************************************************************************
** Function     smp_proc_sl_key
** Description  process key ready events.
*******************************************************************************/
void smp_proc_sl_key(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8 key_type = p_data->key.key_type;

    SMP_TRACE_DEBUG0 ("smp_proc_sl_keysmp_proc_sl_key  ");
    if (key_type == SMP_KEY_TYPE_TK)
    {
        smp_generate_confirm(p_cb, NULL);
    }
    else if (key_type == SMP_KEY_TYPE_CFM)
    {
        smp_set_state(SMP_ST_WAIT_CONFIRM);

        if (p_cb->flags & SMP_PAIR_FLAGS_CMD_CONFIRM)
            smp_sm_event(p_cb, SMP_CONFIRM_EVT, NULL);

    }
}
/*******************************************************************************
** Function     smp_start_enc
** Description  start encryption
*******************************************************************************/
void smp_start_enc(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    BOOLEAN cmd;
    UINT8 reason = SMP_ENC_FAIL;

    SMP_TRACE_DEBUG0 ("smp_start_enc ");
    if (p_data != NULL)
        cmd = btm_ble_start_encrypt(p_cb->pairing_bda, TRUE, p_data->key.p_data);
    else
        cmd = btm_ble_start_encrypt(p_cb->pairing_bda, FALSE, NULL);

    if (!cmd)
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &reason);

}

/*******************************************************************************
** Function     smp_proc_discard
** Description   processing for discard security request
*******************************************************************************/
void smp_proc_discard(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_proc_discard ");
    smp_cb_cleanup(p_cb);
}
/*******************************************************************************
** Function     smp_proc_release_delay
** Description  process the release delay request
*******************************************************************************/
void smp_proc_release_delay(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_proc_release_delay ");
    btu_stop_timer (&p_cb->rsp_timer_ent);
    btu_start_timer (&p_cb->rsp_timer_ent, BTU_TTYPE_SMP_PAIRING_CMD,
                     SMP_WAIT_FOR_REL_DELAY_TOUT);
}

/*******************************************************************************
** Function      smp_proc_release_delay_tout
** Description   processing the release delay timeout
*******************************************************************************/
void smp_proc_release_delay_tout(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_proc_release_delay_tout ");
    btu_stop_timer (&p_cb->rsp_timer_ent);
    smp_proc_pairing_cmpl(p_cb);
}


/*******************************************************************************
** Function     smp_enc_cmpl
** Description   encryption success
*******************************************************************************/
void smp_enc_cmpl(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8 enc_enable = *(UINT8 *)p_data;
    UINT8 reason = enc_enable ? SMP_SUCCESS : SMP_ENC_FAIL;

    SMP_TRACE_DEBUG0 ("smp_enc_cmpl ");
    smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &reason);
}


/*******************************************************************************
** Function     smp_check_auth_req
** Description  check authentication request
*******************************************************************************/
void smp_check_auth_req(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8 enc_enable = *(UINT8 *)p_data;
    UINT8 reason = enc_enable ? SMP_SUCCESS : SMP_ENC_FAIL;

    SMP_TRACE_DEBUG3 ("smp_check_auth_req enc_enable=%d i_keys=0x%x r_keys=0x%x (i-initiator r-responder)",
                      enc_enable, p_cb->loc_i_key, p_cb->loc_r_key);
    if (enc_enable == 1)
    {
        if (/*((p_cb->peer_auth_req & SMP_AUTH_BOND) ||
             (p_cb->loc_auth_req & SMP_AUTH_BOND)) &&*/
            (p_cb->loc_i_key || p_cb->loc_r_key))
        {
            smp_sm_event(p_cb, SMP_BOND_REQ_EVT, NULL);
        }
        else
            smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &reason);
    }
    else if (enc_enable == 0)
    {
        /* if failed for encryption after pairing, send callback */
        if (p_cb->flags & SMP_PAIR_FLAG_ENC_AFTER_PAIR)
            smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &reason);
        /* if enc failed for old security information */
        /* if master device, clean up and abck to idle; slave device do nothing */
        else if (p_cb->role == HCI_ROLE_MASTER)
        {
            smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &reason);
        }
    }
}

/*******************************************************************************
** Function     smp_key_pick_key
** Description  Pick a key distribution function based on the key mask.
*******************************************************************************/
void smp_key_pick_key(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8   key_to_dist = (p_cb->role == HCI_ROLE_SLAVE) ? p_cb->loc_r_key : p_cb->loc_i_key;
    UINT8   i = 0;

    SMP_TRACE_DEBUG1 ("smp_key_pick_key key_to_dist=0x%x", key_to_dist);
    while (i < 3)
    {
        SMP_TRACE_DEBUG2("key to send = %02x, i = %d",  key_to_dist, i);

        if (key_to_dist & (1 << i))
        {
            SMP_TRACE_DEBUG1 ("smp_distribute_act[%d]", i);
            (* smp_distribute_act[i])(p_cb, p_data);
            break;
        }
        i ++;
    }
}
/*******************************************************************************
** Function     smp_key_distribution
** Description  start key distribution if required.
*******************************************************************************/
void smp_key_distribution(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8   reason = SMP_SUCCESS;
    SMP_TRACE_DEBUG3 ("smp_key_distribution role=%d (0-master) r_keys=0x%x i_keys=0x%x",
                      p_cb->role, p_cb->loc_r_key, p_cb->loc_i_key);

    if (p_cb->role == HCI_ROLE_SLAVE||
        (!p_cb->loc_r_key && p_cb->role == HCI_ROLE_MASTER))
    {
        smp_key_pick_key(p_cb, p_data);
    }

    if (!p_cb->loc_i_key && !p_cb->loc_r_key)
    {
        /* state check to prevent re-entrant */
        if (smp_get_state() == SMP_ST_BOND_PENDING)
            smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &reason);
    }
}
/*******************************************************************************
** Function         smp_decide_asso_model
** Description      This function is called to compare both sides' io capability
**                  oob data flag and authentication request, and decide the
**                  association model to use for the authentication.
*******************************************************************************/
void smp_decide_asso_model(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UINT8   failure = SMP_UNKNOWN_IO_CAP;
    tSMP_ASSO_MODEL model = SMP_MODEL_MAX;
    UINT8 int_evt = 0;
    tSMP_KEY key;
    tSMP_INT_DATA   *p;

    SMP_TRACE_DEBUG3 ("smp_decide_asso_model p_cb->peer_io_caps = %d p_cb->loc_io_caps = %d \
                       p_cb->peer_auth_req = %02x",
                       p_cb->peer_io_caps, p_cb->loc_io_caps, p_cb->peer_auth_req);

    /* OOB data present on both devices, use OOB association model */
    if (p_cb->peer_oob_flag == SMP_OOB_PRESENT && p_cb->loc_oob_flag == SMP_OOB_PRESENT)
    {
        model = SMP_MODEL_OOB;
    }
    /* no MITM required, ignore IO cap, use encryption only */
    else if (SMP_NO_MITM_REQUIRED (p_cb->peer_auth_req) &&
             SMP_NO_MITM_REQUIRED(p_cb->loc_auth_req))
    {
        model = SMP_MODEL_ENC_ONLY;
    }
    else/* use IO capability to decide assiciation model */
    {
        if (p_cb->peer_io_caps < SMP_IO_CAP_MAX && p_cb->loc_io_caps < SMP_IO_CAP_MAX)
        {
            if (p_cb->role == HCI_ROLE_MASTER)
                model = smp_association_table[p_cb->role][p_cb->peer_io_caps][p_cb->loc_io_caps];
            else
                model = smp_association_table[p_cb->role][p_cb->loc_io_caps][p_cb->peer_io_caps];
        }
    }

    SMP_TRACE_DEBUG1("Association Model = %d", model);

    if (model == SMP_MODEL_OOB)
    {
        SMP_TRACE_ERROR0("Association Model = SMP_MODEL_OOB");
        p_cb->sec_level = SMP_SEC_AUTHENTICATED;
        SMP_TRACE_EVENT1 ("p_cb->sec_level =%d (SMP_SEC_AUTHENTICATED) ", p_cb->sec_level );
        p_cb->cb_evt = SMP_OOB_REQ_EVT;

        int_evt = SMP_TK_REQ_EVT;
    }
    else if (model == SMP_MODEL_PASSKEY)
    {
        p_cb->sec_level = SMP_SEC_AUTHENTICATED;
        SMP_TRACE_EVENT1 ("p_cb->sec_level =%d (SMP_SEC_AUTHENTICATED) ", p_cb->sec_level );

        p_cb->cb_evt = SMP_PASSKEY_REQ_EVT;
        int_evt = SMP_TK_REQ_EVT;
    }
    else if (model == SMP_MODEL_KEY_NOTIF)
    {
        p_cb->sec_level = SMP_SEC_AUTHENTICATED;

        SMP_TRACE_DEBUG0("Need to generate Passkey");
        /* generate passkey and notify application */
        smp_generate_passkey(p_cb, NULL);
    }
    else if (model == SMP_MODEL_ENC_ONLY) /* TK = 0, go calculate Confirm */
    {
        if (p_cb->role == HCI_ROLE_MASTER &&
            ((p_cb->peer_auth_req & SMP_AUTH_YN_BIT) != 0) &&
            ((p_cb->loc_auth_req & SMP_AUTH_YN_BIT) == 0))
        {
            SMP_TRACE_ERROR0("IO capability does not meet authentication requirement");
            failure = SMP_PAIR_AUTH_FAIL;
            p = (tSMP_INT_DATA *)&failure;
            int_evt = SMP_AUTH_CMPL_EVT;
        }
        else
        {
            p_cb->sec_level = SMP_SEC_UNAUTHENTICATE;
            SMP_TRACE_EVENT1 ("p_cb->sec_level =%d (SMP_SEC_UNAUTHENTICATE) ", p_cb->sec_level );

            key.key_type = SMP_KEY_TYPE_TK;
            key.p_data = p_cb->tk;
            p = (tSMP_INT_DATA *)&key;

            memset(p_cb->tk, 0, BT_OCTET16_LEN);
            /* TK, ready  */
            int_evt = SMP_KEY_READY_EVT;
        }
    }
    else if (model == SMP_MODEL_MAX)
    {
        SMP_TRACE_ERROR0("Association Model = SMP_MODEL_MAX (failed)");
        p = (tSMP_INT_DATA *)&failure;
        int_evt = SMP_AUTH_CMPL_EVT;
    }

    SMP_TRACE_EVENT1 ("sec_level=%d ", p_cb->sec_level );
    if (int_evt)
        smp_sm_event(p_cb, int_evt, p);
}

/*******************************************************************************
** Function     smp_proc_io_rsp
** Description  process IO response for a slave device.
*******************************************************************************/
void smp_proc_io_rsp(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_proc_io_rsp ");
    if (p_cb->flags & SMP_PAIR_FLAGS_WE_STARTED_DD)
    {
        smp_set_state(SMP_ST_SEC_REQ_PENDING);
        smp_send_cmd(SMP_OPCODE_SEC_REQ, p_cb);
    }
    else /* respond to pairing request */
    {
        smp_send_pair_rsp(p_cb, NULL);
    }
}
/*******************************************************************************
** Function         smp_pairing_cmpl
** Description      This function is called to send the pairing complete callback
**                  and remove the connection if needed.
*******************************************************************************/
void smp_pairing_cmpl(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{

    SMP_TRACE_DEBUG0 ("smp_pairing_cmpl ");

    if ((p_cb->status == SMP_SUCCESS) ||
        (p_cb->status <= SMP_REPEATED_ATTEMPTS && p_cb->status != SMP_SUCCESS))
    {
        smp_sm_event(p_cb, SMP_RELEASE_DELAY_EVT, p_data);
    }
    else
    {
        /* this will transition to idle state right away */
        smp_sm_event(p_cb, SMP_RELEASE_DELAY_TOUT_EVT, p_data);
    }

}
/*******************************************************************************
** Function         smp_pair_terminate
** Description      This function is called to send the pairing complete callback
**                  and remove the connection if needed.
*******************************************************************************/
void smp_pair_terminate(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_pair_terminate ");
    p_cb->status = SMP_PAIR_FAIL_UNKNOWN;
    smp_proc_pairing_cmpl(p_cb);
}
/*******************************************************************************
** Function         smp_idle_terminate
** Description      This function calledin idle state to determine to send authentication
**                  complete or not.
*******************************************************************************/
void smp_idle_terminate(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    if (p_cb->flags & SMP_PAIR_FLAGS_WE_STARTED_DD)
    {
        SMP_TRACE_DEBUG0("Pairing terminated at IDLE state.");
        p_cb->status = SMP_FAIL;
        smp_proc_pairing_cmpl(p_cb);
    }
}
/*******************************************************************************
**
** Function         smp_link_encrypted
**
** Description      This function is called when link is encrypted and notified to
**                  slave device. Proceed to to send LTK, DIV and ER to master if
**                  bonding the devices.
**
**
** Returns          void
**
*******************************************************************************/
void smp_link_encrypted(BD_ADDR bda, UINT8 encr_enable)
{
    tSMP_CB *p_cb = &smp_cb;

    SMP_TRACE_DEBUG1 ("smp_link_encrypted encr_enable=%d",encr_enable);

    if (memcmp(&smp_cb.pairing_bda[0], bda, BD_ADDR_LEN) == 0)
    {
        /* encryption completed with STK, remmeber the key size now, could be overwite
        *  when key exchange happens                                        */
        if (p_cb->loc_enc_size != 0 && encr_enable)
        {
            /* update the link encryption key size if a SMP pairing just performed */
            btm_ble_update_sec_key_size(bda, p_cb->loc_enc_size);
        }

        smp_sm_event(&smp_cb, SMP_ENCRYPTED_EVT, &encr_enable);
    }
}
/*******************************************************************************
**
** Function         smp_proc_ltk_request
**
** Description      This function is called when LTK request is received from
**                  controller.
**
** Returns          void
**
*******************************************************************************/
BOOLEAN smp_proc_ltk_request(BD_ADDR bda)
{
    SMP_TRACE_DEBUG1 ("smp_proc_ltk_request state = %d", smp_cb.state);
    if ( smp_cb.state == SMP_ST_ENC_PENDING &&
         !memcmp(bda, smp_cb.pairing_bda, BD_ADDR_LEN))
    {
        smp_sm_event(&smp_cb, SMP_ENC_REQ_EVT, NULL);

        return TRUE;
    }

    return FALSE;
}
#endif

