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
 *  This file contains functions for the SMP L2Cap utility functions
 *
 ******************************************************************************/
#include "bt_target.h"

#if SMP_INCLUDED == TRUE

#include "bt_types.h"
#include <string.h>
#include <ctype.h>
#include "hcidefs.h"
#include "btm_ble_api.h"
#include "l2c_api.h"
#include "l2c_int.h"
#include "smp_int.h"


#define SMP_PAIRING_REQ_SIZE    7
#define SMP_CONFIRM_CMD_SIZE    (BT_OCTET16_LEN + 1)
#define SMP_INIT_CMD_SIZE       (BT_OCTET16_LEN + 1)
#define SMP_ENC_INFO_SIZE       (BT_OCTET16_LEN + 1)
#define SMP_MASTER_ID_SIZE      (BT_OCTET8_LEN + 2 + 1)
#define SMP_ID_INFO_SIZE        (BT_OCTET16_LEN + 1)
#define SMP_ID_ADDR_SIZE        (BD_ADDR_LEN + 1 + 1)
#define SMP_SIGN_INFO_SIZE      (BT_OCTET16_LEN + 1)
#define SMP_PAIR_FAIL_SIZE      2


/* type for action functions */
typedef BT_HDR * (*tSMP_CMD_ACT)(UINT8 cmd_code, tSMP_CB *p_cb);

static BT_HDR * smp_build_pairing_cmd(UINT8 cmd_code, tSMP_CB *p_cb);
static BT_HDR * smp_build_confirm_cmd(UINT8 cmd_code, tSMP_CB *p_cb);
static BT_HDR * smp_build_rand_cmd(UINT8 cmd_code, tSMP_CB *p_cb);
static BT_HDR * smp_build_pairing_fail(UINT8 cmd_code, tSMP_CB *p_cb);
static BT_HDR * smp_build_identity_info_cmd(UINT8 cmd_code, tSMP_CB *p_cb);
static BT_HDR * smp_build_encrypt_info_cmd(UINT8 cmd_code, tSMP_CB *p_cb);
static BT_HDR * smp_build_security_request(UINT8 cmd_code, tSMP_CB *p_cb);
static BT_HDR * smp_build_signing_info_cmd(UINT8 cmd_code, tSMP_CB *p_cb);
static BT_HDR * smp_build_master_id_cmd(UINT8 cmd_code, tSMP_CB *p_cb);
static BT_HDR * smp_build_id_addr_cmd(UINT8 cmd_code, tSMP_CB *p_cb);

const tSMP_CMD_ACT smp_cmd_build_act[] =
{
    NULL,
    smp_build_pairing_cmd,      /* 0x01: pairing request */
    smp_build_pairing_cmd,      /* 0x02: pairing response */
    smp_build_confirm_cmd,      /* 0x03: pairing confirm */
    smp_build_rand_cmd,         /* 0x04: pairing initializer request */
    smp_build_pairing_fail,     /* 0x05: pairing failure */
    smp_build_encrypt_info_cmd, /* 0x06: security information command */
    smp_build_master_id_cmd,    /* 0x07: master identity command */
    smp_build_identity_info_cmd,  /* 0x08: identity information command */
    smp_build_id_addr_cmd,          /* 0x09: signing information */
    smp_build_signing_info_cmd,    /* 0x0A: signing information */
    smp_build_security_request    /* 0x0B: security request */
};
/*******************************************************************************
**
** Function         smp_send_msg_to_L2CAP
**
** Description      Send message to L2CAP.
**
*******************************************************************************/
BOOLEAN  smp_send_msg_to_L2CAP(BD_ADDR rem_bda, BT_HDR *p_toL2CAP)
{
    UINT16              l2cap_ret;

    SMP_TRACE_EVENT0("smp_send_msg_to_L2CAP");

    if ((l2cap_ret = L2CA_SendFixedChnlData (L2CAP_SMP_CID, rem_bda, p_toL2CAP)) == L2CAP_DW_FAILED)
    {
        SMP_TRACE_ERROR1("SMP   failed to pass msg:0x%0x to L2CAP",
                         *((UINT8 *)(p_toL2CAP + 1) + p_toL2CAP->offset));
        GKI_freebuf(p_toL2CAP);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
/*******************************************************************************
**
** Function         smp_send_cmd
**
** Description      send a SMP command on L2CAP channel.
**
*******************************************************************************/
BOOLEAN smp_send_cmd(UINT8 cmd_code, tSMP_CB *p_cb)
{
    BT_HDR *p_buf;
    BOOLEAN sent = FALSE;
    UINT8 failure = SMP_PAIR_INTERNAL_ERR;
    SMP_TRACE_EVENT1("smp_send_cmd on l2cap cmd_code=0x%x", cmd_code);
    if ( cmd_code < SMP_OPCODE_MAX &&
         smp_cmd_build_act[cmd_code] != NULL)
    {
        p_buf = (*smp_cmd_build_act[cmd_code])(cmd_code, p_cb);

        if (p_buf != NULL &&
            smp_send_msg_to_L2CAP(p_cb->pairing_bda, p_buf))
        {
            sent = TRUE;

            btu_stop_timer (&p_cb->rsp_timer_ent);
            btu_start_timer (&p_cb->rsp_timer_ent, BTU_TTYPE_SMP_PAIRING_CMD,
                             SMP_WAIT_FOR_RSP_TOUT);
        }
    }

    if (!sent)
    {
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &failure);
    }
    return sent;
}



/*******************************************************************************
**
** Function         smp_rsp_timeout
**
** Description      Called when SMP wait for SMP command response timer expires
**
** Returns          void
**
*******************************************************************************/
void smp_rsp_timeout(TIMER_LIST_ENT *p_tle)
{
    tSMP_CB   *p_cb = &smp_cb;
    UINT8 failure = SMP_RSP_TIMEOUT;

    SMP_TRACE_EVENT1("smp_rsp_timeout state:%d", p_cb->state);

    if (smp_get_state() == SMP_ST_RELEASE_DELAY)
    {
        smp_sm_event(p_cb, SMP_RELEASE_DELAY_TOUT_EVT, NULL);
    }
    else
    {
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &failure);
    }
}

/*******************************************************************************
**
** Function         smp_build_pairing_req_cmd
**
** Description      Build pairing request command.
**
*******************************************************************************/
BT_HDR * smp_build_pairing_cmd(UINT8 cmd_code, tSMP_CB *p_cb)
{
    BT_HDR      *p_buf = NULL ;
    UINT8       *p;
    SMP_TRACE_EVENT0("smp_build_pairing_cmd");
    if ((p_buf = (BT_HDR *)GKI_getbuf(sizeof(BT_HDR) + SMP_PAIRING_REQ_SIZE + L2CAP_MIN_OFFSET)) != NULL)
    {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        UINT8_TO_STREAM (p, cmd_code);
        UINT8_TO_STREAM (p, p_cb->loc_io_caps);
        UINT8_TO_STREAM (p, p_cb->loc_oob_flag);
        UINT8_TO_STREAM (p, p_cb->loc_auth_req);
        UINT8_TO_STREAM (p, p_cb->loc_enc_size);
        UINT8_TO_STREAM (p, p_cb->loc_i_key);
        UINT8_TO_STREAM (p, p_cb->loc_r_key);

        p_buf->offset = L2CAP_MIN_OFFSET;
        /* 1B ERR_RSP op code + 1B cmd_op_code + 2B handle + 1B status */
        p_buf->len = SMP_PAIRING_REQ_SIZE;
    }

    return p_buf;
}

/*******************************************************************************
**
** Function         smp_build_confirm_cmd
**
** Description      Build confirm request command.
**
*******************************************************************************/
static BT_HDR * smp_build_confirm_cmd(UINT8 cmd_code, tSMP_CB *p_cb)
{
    BT_HDR      *p_buf = NULL ;
    UINT8       *p;
    SMP_TRACE_EVENT0("smp_build_confirm_cmd");
    if ((p_buf = (BT_HDR *)GKI_getbuf(sizeof(BT_HDR) + SMP_CONFIRM_CMD_SIZE + L2CAP_MIN_OFFSET)) != NULL)
    {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        UINT8_TO_STREAM (p, SMP_OPCODE_CONFIRM);
        ARRAY_TO_STREAM (p, p_cb->confirm, BT_OCTET16_LEN);

        p_buf->offset = L2CAP_MIN_OFFSET;
        p_buf->len = SMP_CONFIRM_CMD_SIZE;
    }

    return p_buf;
}
/*******************************************************************************
**
** Function         smp_build_rand_cmd
**
** Description      Build Initializer command.
**
*******************************************************************************/
static BT_HDR * smp_build_rand_cmd(UINT8 cmd_code, tSMP_CB *p_cb)
{
    BT_HDR      *p_buf = NULL ;
    UINT8       *p;
    SMP_TRACE_EVENT0("smp_build_rand_cmd");
    if ((p_buf = (BT_HDR *)GKI_getbuf(sizeof(BT_HDR) + SMP_INIT_CMD_SIZE + L2CAP_MIN_OFFSET)) != NULL)
    {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        UINT8_TO_STREAM (p, SMP_OPCODE_INIT);
        ARRAY_TO_STREAM (p, p_cb->rand, BT_OCTET16_LEN);

        p_buf->offset = L2CAP_MIN_OFFSET;
        p_buf->len = SMP_INIT_CMD_SIZE;
    }

    return p_buf;
}
/*******************************************************************************
**
** Function         smp_build_encrypt_info_cmd
**
** Description      Build security information command.
**
*******************************************************************************/
static BT_HDR * smp_build_encrypt_info_cmd(UINT8 cmd_code, tSMP_CB *p_cb)
{
    BT_HDR      *p_buf = NULL ;
    UINT8       *p;
    SMP_TRACE_EVENT0("smp_build_encrypt_info_cmd");
    if ((p_buf = (BT_HDR *)GKI_getbuf(sizeof(BT_HDR) + SMP_ENC_INFO_SIZE + L2CAP_MIN_OFFSET)) != NULL)
    {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        UINT8_TO_STREAM (p, SMP_OPCODE_ENCRYPT_INFO);
        ARRAY_TO_STREAM (p, p_cb->ltk, BT_OCTET16_LEN);

        p_buf->offset = L2CAP_MIN_OFFSET;
        p_buf->len = SMP_ENC_INFO_SIZE;
    }

    return p_buf;
}
/*******************************************************************************
**
** Function         smp_build_master_id_cmd
**
** Description      Build security information command.
**
*******************************************************************************/
static BT_HDR * smp_build_master_id_cmd(UINT8 cmd_code, tSMP_CB *p_cb)
{
    BT_HDR      *p_buf = NULL ;
    UINT8       *p;
    SMP_TRACE_EVENT0("smp_build_master_id_cmd ");
    if ((p_buf = (BT_HDR *)GKI_getbuf(sizeof(BT_HDR) + SMP_MASTER_ID_SIZE + L2CAP_MIN_OFFSET)) != NULL)
    {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        UINT8_TO_STREAM (p, SMP_OPCODE_MASTER_ID);
        UINT16_TO_STREAM (p, p_cb->ediv);
        ARRAY_TO_STREAM (p, p_cb->enc_rand, BT_OCTET8_LEN);

        p_buf->offset = L2CAP_MIN_OFFSET;
        p_buf->len = SMP_MASTER_ID_SIZE;
    }

    return p_buf;
}
/*******************************************************************************
**
** Function         smp_build_identity_info_cmd
**
** Description      Build identity information command.
**
*******************************************************************************/
static BT_HDR * smp_build_identity_info_cmd(UINT8 cmd_code, tSMP_CB *p_cb)
{
    BT_HDR      *p_buf = NULL ;
    UINT8       *p;
    BT_OCTET16  irk;
    SMP_TRACE_EVENT0("smp_build_identity_info_cmd");
    if ((p_buf = (BT_HDR *)GKI_getbuf(sizeof(BT_HDR) + SMP_ID_INFO_SIZE + L2CAP_MIN_OFFSET)) != NULL)
    {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        BTM_GetDeviceIDRoot(irk);

        UINT8_TO_STREAM (p, SMP_OPCODE_IDENTITY_INFO);
        ARRAY_TO_STREAM (p,  irk, BT_OCTET16_LEN);

        p_buf->offset = L2CAP_MIN_OFFSET;
        p_buf->len = SMP_ID_INFO_SIZE;
    }

    return p_buf;
}
/*******************************************************************************
**
** Function         smp_build_id_addr_cmd
**
** Description      Build identity address information command.
**
*******************************************************************************/
static BT_HDR * smp_build_id_addr_cmd(UINT8 cmd_code, tSMP_CB *p_cb)
{
    BT_HDR      *p_buf = NULL ;
    UINT8       *p;
    BT_OCTET16  irk;
    SMP_TRACE_EVENT0("smp_build_id_addr_cmd");
    if ((p_buf = (BT_HDR *)GKI_getbuf(sizeof(BT_HDR) + SMP_ID_ADDR_SIZE + L2CAP_MIN_OFFSET)) != NULL)
    {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        BTM_GetDeviceIDRoot(irk);

        UINT8_TO_STREAM (p, SMP_OPCODE_ID_ADDR);
        UINT8_TO_STREAM (p, 0);     /* TODO: update with local address type */
        BTM_ReadConnectionAddr(p_cb->local_bda);
        BDADDR_TO_STREAM (p, p_cb->local_bda);

        p_buf->offset = L2CAP_MIN_OFFSET;
        p_buf->len = SMP_ID_ADDR_SIZE;
    }

    return p_buf;
}

/*******************************************************************************
**
** Function         smp_build_signing_info_cmd
**
** Description      Build signing information command.
**
*******************************************************************************/
static BT_HDR * smp_build_signing_info_cmd(UINT8 cmd_code, tSMP_CB *p_cb)
{
    BT_HDR      *p_buf = NULL ;
    UINT8       *p;
    //BT_OCTET16  srk; remove
    SMP_TRACE_EVENT0("smp_build_signing_info_cmd");
    if ((p_buf = (BT_HDR *)GKI_getbuf(sizeof(BT_HDR) + SMP_SIGN_INFO_SIZE + L2CAP_MIN_OFFSET)) != NULL)
    {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        UINT8_TO_STREAM (p, SMP_OPCODE_SIGN_INFO);
        ARRAY_TO_STREAM (p, p_cb->csrk, BT_OCTET16_LEN);

        p_buf->offset = L2CAP_MIN_OFFSET;
        p_buf->len = SMP_SIGN_INFO_SIZE;
    }

    return p_buf;
}
/*******************************************************************************
**
** Function         smp_build_pairing_fail
**
** Description      Build Pairing Fail command.
**
*******************************************************************************/
static BT_HDR * smp_build_pairing_fail(UINT8 cmd_code, tSMP_CB *p_cb)
{
    BT_HDR      *p_buf = NULL ;
    UINT8       *p;
    SMP_TRACE_EVENT0("smp_build_pairing_fail");
    if ((p_buf = (BT_HDR *)GKI_getbuf(sizeof(BT_HDR) + SMP_PAIR_FAIL_SIZE + L2CAP_MIN_OFFSET)) != NULL)
    {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        UINT8_TO_STREAM (p, SMP_OPCODE_PAIRING_FAILED);
        UINT8_TO_STREAM (p, p_cb->failure);

        p_buf->offset = L2CAP_MIN_OFFSET;
        p_buf->len = SMP_PAIR_FAIL_SIZE;
    }

    return p_buf;
}
/*******************************************************************************
**
** Function         smp_build_security_request
**
** Description      Build security request command.
**
*******************************************************************************/
static BT_HDR * smp_build_security_request(UINT8 cmd_code, tSMP_CB *p_cb)
{
    BT_HDR      *p_buf = NULL ;
    UINT8       *p;
    SMP_TRACE_EVENT0("smp_build_security_request");

    if ((p_buf = (BT_HDR *)GKI_getbuf(sizeof(BT_HDR) + 2 + L2CAP_MIN_OFFSET)) != NULL)
    {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        UINT8_TO_STREAM (p, SMP_OPCODE_SEC_REQ);
        UINT8_TO_STREAM (p,  p_cb->loc_auth_req);

        p_buf->offset = L2CAP_MIN_OFFSET;
        p_buf->len = 2;

        SMP_TRACE_EVENT2("opcode=%d auth_req=0x%x",SMP_OPCODE_SEC_REQ,  p_cb->loc_auth_req );
    }

    return p_buf;

}

/*******************************************************************************
**
** Function         smp_convert_string_to_tk
**
** Description      This function is called to convert a 6 to 16 digits numeric
**                  character string into SMP TK.
**
**
** Returns          void
**
*******************************************************************************/
void smp_convert_string_to_tk(BT_OCTET16 tk, UINT32 passkey)
{
    UINT8   *p = tk;
    tSMP_KEY    key;
    SMP_TRACE_EVENT0("smp_convert_string_to_tk");
    UINT32_TO_STREAM(p, passkey);

    key.key_type    = SMP_KEY_TYPE_TK;
    key.p_data      = tk;

    smp_sm_event(&smp_cb, SMP_KEY_READY_EVT, &key);
}

/*******************************************************************************
**
** Function         smp_mask_enc_key
**
** Description      This function is called to mask off the encryption key based
**                  on the maximum encryption key size.
**
**
** Returns          void
**
*******************************************************************************/
void smp_mask_enc_key(UINT8 loc_enc_size, UINT8 * p_data)
{
    SMP_TRACE_EVENT0("smp_mask_enc_key");
    if (loc_enc_size < BT_OCTET16_LEN)
    {
        for (; loc_enc_size < BT_OCTET16_LEN; loc_enc_size ++)
            * (p_data + loc_enc_size) = 0;
    }
    return;
}
/*******************************************************************************
**
** Function         smp_xor_128
**
** Description      utility function to do an biteise exclusive-OR of two bit
**                  strings of the length of BT_OCTET16_LEN.
**
** Returns          void
**
*******************************************************************************/
void smp_xor_128(BT_OCTET16 a, BT_OCTET16 b)
{
    UINT8 i, *aa = a, *bb = b;

    SMP_TRACE_EVENT0("smp_xor_128");
    for (i = 0; i < BT_OCTET16_LEN; i++)
    {
        aa[i] = aa[i] ^ bb[i];
    }
}


/*******************************************************************************
**
** Function         smp_cb_cleanup
**
** Description      Clean up SMP control block
**
** Returns          void
**
*******************************************************************************/
void smp_cb_cleanup(tSMP_CB   *p_cb)
{
    tSMP_CALLBACK   *p_callback = p_cb->p_callback;
    UINT8           trace_level = p_cb->trace_level;

    SMP_TRACE_EVENT0("smp_cb_cleanup");
    memset(p_cb, 0, sizeof(tSMP_CB));
    p_cb->p_callback = p_callback;
    p_cb->trace_level = trace_level;
}
/*******************************************************************************
**
** Function         smp_reset_control_value
**
** Description      This function is called to reset the control block value when
**                  pairing procedure finished.
**
**
** Returns          void
**
*******************************************************************************/
void smp_reset_control_value(tSMP_CB *p_cb)
{
    SMP_TRACE_EVENT0("smp_reset_control_value");
    btu_stop_timer (&p_cb->rsp_timer_ent);
#if SMP_CONFORMANCE_TESTING == TRUE

    SMP_TRACE_EVENT1("smp_cb.remove_fixed_channel_disable=%d", smp_cb.remove_fixed_channel_disable);
    if (!smp_cb.remove_fixed_channel_disable)
    {
        L2CA_RemoveFixedChnl (L2CAP_SMP_CID, p_cb->pairing_bda);
    }
    else
    {
        SMP_TRACE_EVENT0("disable the removal of the fixed channel");
    }


#else
    /* We can tell L2CAP to remove the fixed channel (if it has one) */
    L2CA_RemoveFixedChnl (L2CAP_SMP_CID, p_cb->pairing_bda);

#endif
    smp_cb_cleanup(p_cb);

}
/*******************************************************************************
**
** Function         smp_proc_pairing_cmpl
**
** Description      This function is called to process pairing complete
**
**
** Returns          void
**
*******************************************************************************/
void smp_proc_pairing_cmpl(tSMP_CB *p_cb)
{
    tSMP_EVT_DATA   evt_data = {0};

    SMP_TRACE_DEBUG0 ("smp_proc_pairing_cmpl ");

    evt_data.cmplt.reason = p_cb->status;

    if (p_cb->status == SMP_SUCCESS)
        evt_data.cmplt.sec_level = p_cb->sec_level;

    evt_data.cmplt.is_pair_cancel  = FALSE;

    if (p_cb->is_pair_cancel)
        evt_data.cmplt.is_pair_cancel = TRUE;


    SMP_TRACE_DEBUG2 ("send SMP_COMPLT_EVT reason=0x%0x sec_level=0x%0x",
                      evt_data.cmplt.reason,
                      evt_data.cmplt.sec_level );
    if (p_cb->p_callback)
        (*p_cb->p_callback) (SMP_COMPLT_EVT, p_cb->pairing_bda, &evt_data);

#if 0 /* TESTING CODE : as a master, reencrypt using LTK */
    if (evt_data.cmplt.reason == 0 && p_cb->role == HCI_ROLE_MASTER)
    {
        btm_ble_start_encrypt(p_cb->pairing_bda, FALSE, NULL);
    }
#endif

    smp_reset_control_value(p_cb);
}

#if SMP_CONFORMANCE_TESTING == TRUE
/*******************************************************************************
**
** Function         smp_set_test_confirm_value
**
** Description      This function is called to set the test confirm value
**
** Returns          void
**
*******************************************************************************/
void smp_set_test_confirm_value(BOOLEAN enable, UINT8 *p_c_val)
{
    SMP_TRACE_DEBUG1("smp_set_test_confirm_value enable=%d", enable);
    smp_cb.enable_test_confirm_val = enable;
    memcpy(smp_cb.test_confirm, p_c_val, BT_OCTET16_LEN);
}


/*******************************************************************************
**
** Function         smp_set_test_confirm_value
**
** Description      This function is called to set the test rand value
**
** Returns          void
**
*******************************************************************************/
void smp_set_test_rand_value(BOOLEAN enable, UINT8 *p_c_val)
{
    SMP_TRACE_DEBUG1("smp_set_test_rand_value enable=%d", enable);
    smp_cb.enable_test_rand_val = enable;
    memcpy(smp_cb.test_rand, p_c_val, BT_OCTET16_LEN);
}


/*******************************************************************************
**
** Function         smp_set_test_pair_fail_status
**
** Description      This function is called to set the test fairing fair status
**
** Returns          void
**
*******************************************************************************/
void smp_set_test_pair_fail_status (BOOLEAN enable, UINT8 status)
{
    SMP_TRACE_DEBUG1("smp_set_test_confirm_value enable=%d", enable);
    smp_cb.enable_test_pair_fail = enable;
    smp_cb.pair_fail_status = status;
}

/*******************************************************************************
**
** Function         smp_set_test_pair_fail_status
**
** Description      This function is called to disable the removal of fixed channel
**                  in  smp_reset_control_value
** Returns          void
**
*******************************************************************************/
void smp_remove_fixed_channel_disable (BOOLEAN disable)
{
    SMP_TRACE_DEBUG1("smp_remove_fixed_channel_disable disable =%d", disable);
    smp_cb.remove_fixed_channel_disable = disable;
}

#endif


#endif

