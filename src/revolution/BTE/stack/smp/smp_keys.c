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
 *  This file contains the implementation of the SMP utility functions used
 *  by SMP.
 *
 ******************************************************************************/

#include "bt_target.h"

#if SMP_INCLUDED == TRUE
    #if SMP_DEBUG == TRUE
        #include <stdio.h>
    #endif
    #include <string.h>

    #include "btm_ble_api.h"
    #include "smp_int.h"
    #include "btm_int.h"
    #include "btm_ble_int.h"
    #include "hcimsgs.h"
    #include "aes.h"
    #ifndef SMP_MAX_ENC_REPEAT
        #define SMP_MAX_ENC_REPEAT      3
    #endif

static void smp_rand_back(tBTM_RAND_ENC *p);
static void smp_genenrate_confirm(tSMP_CB *p_cb, tSMP_INT_DATA *p_data);
static void smp_genenrate_ltk_cont(tSMP_CB *p_cb, tSMP_INT_DATA *p_data);
static void smp_generate_y(tSMP_CB *p_cb, tSMP_INT_DATA *p);
static void smp_generate_rand_vector (tSMP_CB *p_cb, tSMP_INT_DATA *p);
static void smp_process_stk(tSMP_CB *p_cb, tSMP_ENC *p);
static void smp_calculate_comfirm_cont(tSMP_CB *p_cb, tSMP_ENC *p);
static void smp_process_confirm(tSMP_CB *p_cb, tSMP_ENC *p);
static void smp_process_compare(tSMP_CB *p_cb, tSMP_ENC *p);
static void smp_process_ediv(tSMP_CB *p_cb, tSMP_ENC *p);

static const tSMP_ACT smp_encrypt_action[] =
{
    smp_generate_compare,           /* SMP_GEN_COMPARE */
    smp_genenrate_confirm,          /* SMP_GEN_CONFIRM*/
    smp_generate_stk,               /* SMP_GEN_STK*/
    smp_genenrate_ltk_cont,          /* SMP_GEN_LTK */
    smp_generate_ltk,               /* SMP_GEN_DIV_LTK */
    smp_generate_rand_vector,        /* SMP_GEN_RAND_V */
    smp_generate_y,                  /* SMP_GEN_EDIV */
    smp_generate_passkey,           /* SMP_GEN_TK */
    smp_generate_confirm,           /* SMP_GEN_SRAND_MRAND */
    smp_genenrate_rand_cont         /* SMP_GEN_SRAND_MRAND_CONT */
};


    #define SMP_PASSKEY_MASK    0xfff00000

    #if SMP_DEBUG == TRUE
static void smp_debug_print_nbyte_little_endian (UINT8 *p, const UINT8 *key_name, UINT8 len)
{
    int     i, x = 0;
    UINT8   p_buf[100];
    memset(p_buf, 0, 100);

    for (i = 0; i < len; i ++)
    {
        x += sprintf ((char *)&p_buf[x], "%02x ", p[i]);
    }
    SMP_TRACE_WARNING2("%s(LSB ~ MSB) = %s", key_name, p_buf);
}
    #else
        #define smp_debug_print_nbyte_little_endian(p, key_name, len)
    #endif

/*******************************************************************************
**
** Function         smp_encrypt_data
**
** Description      This function is called to generate passkey.
**
** Returns          void
**
*******************************************************************************/
BOOLEAN smp_encrypt_data (UINT8 *key, UINT8 key_len,
                          UINT8 *plain_text, UINT8 pt_len,
                          tSMP_ENC *p_out)
{
    aes_context     ctx;
    UINT8           *p_start = NULL;
    UINT8           *p = NULL;
    UINT8           *p_rev_data = NULL;    /* input data in big endilan format */
    UINT8           *p_rev_key = NULL;     /* input key in big endilan format */
    UINT8           *p_rev_output = NULL;  /* encrypted output in big endilan format */

    SMP_TRACE_DEBUG0 ("smp_encrypt_data");
    if ( (p_out == NULL ) || (key_len != SMP_ENCRYT_KEY_SIZE) )
    {
        BTM_TRACE_ERROR0 ("smp_encrypt_data Failed");
        return(FALSE);
    }

    if ((p_start = (UINT8 *)GKI_getbuf((SMP_ENCRYT_DATA_SIZE*4))) == NULL)
    {
        BTM_TRACE_ERROR0 ("smp_encrypt_data Failed unable to allocate buffer");
        return(FALSE);
    }

    if (pt_len > SMP_ENCRYT_DATA_SIZE)
        pt_len = SMP_ENCRYT_DATA_SIZE;

    memset(p_start, 0, SMP_ENCRYT_DATA_SIZE * 4);
    p = p_start;
    ARRAY_TO_STREAM (p, plain_text, pt_len); /* byte 0 to byte 15 */
    p_rev_data = p = p_start + SMP_ENCRYT_DATA_SIZE; /* start at byte 16 */
    REVERSE_ARRAY_TO_STREAM (p, p_start, SMP_ENCRYT_DATA_SIZE);  /* byte 16 to byte 31 */
    p_rev_key = p; /* start at byte 32 */
    REVERSE_ARRAY_TO_STREAM (p, key, SMP_ENCRYT_KEY_SIZE); /* byte 32 to byte 47 */

    smp_debug_print_nbyte_little_endian(key, (const UINT8 *)"Key", SMP_ENCRYT_KEY_SIZE);
    smp_debug_print_nbyte_little_endian(p_start, (const UINT8 *)"Plain text", SMP_ENCRYT_DATA_SIZE);
    p_rev_output = p;
    aes_set_key(p_rev_key, SMP_ENCRYT_KEY_SIZE, &ctx);
    aes_encrypt(p_rev_data, p, &ctx);  /* outputs in byte 48 to byte 63 */

    p = p_out->param_buf;
    REVERSE_ARRAY_TO_STREAM (p, p_rev_output, SMP_ENCRYT_DATA_SIZE);
    smp_debug_print_nbyte_little_endian(p_out->param_buf, (const UINT8 *)"Encrypted text", SMP_ENCRYT_KEY_SIZE);

    p_out->param_len = SMP_ENCRYT_KEY_SIZE;
    p_out->status = HCI_SUCCESS;
    p_out->opcode =  HCI_BLE_ENCRYPT;

    GKI_freebuf(p_start);

    return(TRUE);
}


/*******************************************************************************
**
** Function         smp_generate_passkey
**
** Description      This function is called to generate passkey.
**
** Returns          void
**
*******************************************************************************/
void smp_generate_passkey(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_generate_passkey");
    p_cb->rand_enc_proc = SMP_GEN_TK;

    /* generate MRand or SRand */
    if (!btsnd_hcic_ble_rand((void *)smp_rand_back))
        smp_rand_back(NULL);
}
/*******************************************************************************
**
** Function         smp_proc_passkey
**
** Description      This function is called to process a passkey.
**
** Returns          void
**
*******************************************************************************/
void smp_proc_passkey(tSMP_CB *p_cb , tBTM_RAND_ENC *p)
{
    UINT8   *tt = p_cb->tk;
    tSMP_KEY    key;
    UINT32  passkey; //= 19655 test number; */
    UINT8 *pp = p->param_buf;

    SMP_TRACE_DEBUG0 ("smp_proc_passkey ");
    STREAM_TO_UINT32(passkey, pp);
    passkey &= ~SMP_PASSKEY_MASK;

    /* truncate by maximum value */
    while (passkey > BTM_MAX_PASSKEY_VAL)
        passkey >>= 1;
    SMP_TRACE_ERROR1("Passkey generated = %d", passkey);

    /* save the TK */
    memset(p_cb->tk, 0, BT_OCTET16_LEN);
    UINT32_TO_STREAM(tt, passkey);

    key.key_type = SMP_KEY_TYPE_TK;
    key.p_data  = p_cb->tk;

    if (p_cb->p_callback)
    {
        (*p_cb->p_callback)(SMP_PASSKEY_NOTIF_EVT, p_cb->pairing_bda, (tSMP_EVT_DATA *)&passkey);
    }

    smp_sm_event(p_cb, SMP_KEY_READY_EVT, (tSMP_INT_DATA *)&key);
}


/*******************************************************************************
**
** Function         smp_generate_stk
**
** Description      This function is called to generate STK calculated by running
**                  AES with the TK value as key and a concatenation of the random
**                  values.
**
** Returns          void
**
*******************************************************************************/
void smp_generate_stk (tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    BT_OCTET16      ptext;
    UINT8           *p = ptext;
    tSMP_ENC        output;
    tSMP_STATUS     status = SMP_PAIR_FAIL_UNKNOWN;

    SMP_TRACE_DEBUG0 ("smp_generate_stk ");

    memset(p, 0, BT_OCTET16_LEN);
    if (p_cb->role == HCI_ROLE_MASTER)
    {
        memcpy(p, p_cb->rand, BT_OCTET8_LEN);
        memcpy(&p[BT_OCTET8_LEN], p_cb->rrand, BT_OCTET8_LEN);
    }
    else
    {
        memcpy(p, p_cb->rrand, BT_OCTET8_LEN);
        memcpy(&p[BT_OCTET8_LEN], p_cb->rand, BT_OCTET8_LEN);
    }

    /* generate STK = Etk(rand|rrand)*/
    if (!SMP_Encrypt( p_cb->tk, BT_OCTET16_LEN, ptext, BT_OCTET16_LEN, &output))
    {
        SMP_TRACE_ERROR0("smp_generate_stk failed");
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &status);
    }
    else
    {
        smp_process_stk(p_cb, &output);
    }

}
/*******************************************************************************
**
** Function         smp_generate_confirm
**
** Description      This function is called to start the second pairing phase by
**                  start generating initializer random number.
**
**
** Returns          void
**
*******************************************************************************/
void smp_generate_confirm (tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_generate_confirm");
    p_cb->rand_enc_proc = SMP_GEN_SRAND_MRAND;
    /* generate MRand or SRand */
    if (!btsnd_hcic_ble_rand((void *)smp_rand_back))
        smp_rand_back(NULL);
}
/*******************************************************************************
**
** Function         smp_genenrate_rand_cont
**
** Description      This function is called to generate another 64 bits random for
**                  MRand or Srand.
**
** Returns          void
**
*******************************************************************************/
void smp_genenrate_rand_cont(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_genenrate_rand_cont ");
    p_cb->rand_enc_proc = SMP_GEN_SRAND_MRAND_CONT;
    /* generate 64 MSB of MRand or SRand */

    if (!btsnd_hcic_ble_rand((void *)smp_rand_back))
        smp_rand_back(NULL);
}
/*******************************************************************************
**
** Function         smp_generate_ltk
**
** Description      This function is called to calculate LTK, starting with DIV
**                  generation.
**
**
** Returns          void
**
*******************************************************************************/
void smp_generate_ltk(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    BOOLEAN     div_status;

    SMP_TRACE_DEBUG0 ("smp_generate_ltk ");

    div_status = btm_get_local_div(p_cb->pairing_bda, &p_cb->div);

    if (div_status)
    {
        smp_genenrate_ltk_cont(p_cb, NULL);
    }
    else
    {
        SMP_TRACE_DEBUG0 ("Generate DIV for LTK");
        p_cb->rand_enc_proc = SMP_GEN_DIV_LTK;
        /* generate MRand or SRand */
        if (!btsnd_hcic_ble_rand((void *)smp_rand_back))
            smp_rand_back(NULL);
    }
}


/*******************************************************************************
**
** Function         smp_compute_csrk
**
** Description      This function is called to calculate CSRK
**
**
** Returns          void
**
*******************************************************************************/
void smp_compute_csrk(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    BT_OCTET16  er;
    UINT8       buffer[4]; /* for (r || DIV)  r=1*/
    UINT16      r=1;
    UINT8       *p=buffer;
    tSMP_ENC    output;
    tSMP_STATUS   status = SMP_PAIR_FAIL_UNKNOWN;

    SMP_TRACE_DEBUG1 ("smp_compute_csrk div=%x", p_cb->div);
    BTM_GetDeviceEncRoot(er);
    /* CSRK = d1(ER, DIV, 1) */
    UINT16_TO_STREAM(p, p_cb->div);
    UINT16_TO_STREAM(p, r);

    if (!SMP_Encrypt(er, BT_OCTET16_LEN, buffer, 4, &output))
    {
        SMP_TRACE_ERROR0("smp_generate_csrk failed");
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &status);
    }
    else
    {
        memcpy((void *)p_cb->csrk, output.param_buf, BT_OCTET16_LEN);
        smp_send_csrk_info(p_cb, NULL);
    }
}

/*******************************************************************************
**
** Function         smp_generate_csrk
**
** Description      This function is called to calculate LTK, starting with DIV
**                  generation.
**
**
** Returns          void
**
*******************************************************************************/
void smp_generate_csrk(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    BOOLEAN     div_status;

    SMP_TRACE_DEBUG0 ("smp_generate_csrk");

    div_status = btm_get_local_div(p_cb->pairing_bda, &p_cb->div);
    if (div_status)
    {
        smp_compute_csrk(p_cb, NULL);
    }
    else
    {
        SMP_TRACE_DEBUG0 ("Generate DIV for CSRK");
        p_cb->rand_enc_proc = SMP_GEN_DIV_CSRK;
        if (!btsnd_hcic_ble_rand((void *)smp_rand_back))
            smp_rand_back(NULL);
    }
}


/*******************************************************************************
** Function         smp_concatenate_peer
**                  add pairing command sent from local device into p1.
*******************************************************************************/
void smp_concatenate_local( tSMP_CB *p_cb, UINT8 **p_data, UINT8 op_code)
{
    UINT8   *p = *p_data;

    SMP_TRACE_DEBUG0 ("smp_concatenate_local ");
    UINT8_TO_STREAM(p, op_code);
    UINT8_TO_STREAM(p, p_cb->loc_io_caps);
    UINT8_TO_STREAM(p, p_cb->loc_oob_flag);
    UINT8_TO_STREAM(p, p_cb->loc_auth_req);
    UINT8_TO_STREAM(p, p_cb->loc_enc_size);
    UINT8_TO_STREAM(p, p_cb->loc_i_key);
    UINT8_TO_STREAM(p, p_cb->loc_r_key);

    *p_data = p;
}
/*******************************************************************************
** Function         smp_concatenate_peer
**                  add pairing command received from peer device into p1.
*******************************************************************************/
void smp_concatenate_peer( tSMP_CB *p_cb, UINT8 **p_data, UINT8 op_code)
{
    UINT8   *p = *p_data;

    SMP_TRACE_DEBUG0 ("smp_concatenate_peer ");
    UINT8_TO_STREAM(p, op_code);
    UINT8_TO_STREAM(p, p_cb->peer_io_caps);
    UINT8_TO_STREAM(p, p_cb->peer_oob_flag);
    UINT8_TO_STREAM(p, p_cb->peer_auth_req);
    UINT8_TO_STREAM(p, p_cb->peer_enc_size);
    UINT8_TO_STREAM(p, p_cb->peer_i_key);
    UINT8_TO_STREAM(p, p_cb->peer_r_key);

    *p_data = p;
}
/*******************************************************************************
**
** Function         smp_gen_p1_4_confirm
**
** Description      Generate Confirm/Compare Step1:
**                  p1 = pres || preq || rat' || iat'
**
** Returns          void
**
*******************************************************************************/
void smp_gen_p1_4_confirm( tSMP_CB *p_cb, BT_OCTET16 p1)
{
    UINT8 *p = (UINT8 *)p1;
    tBTM_SEC_DEV_REC  *p_dev_rec;

    SMP_TRACE_DEBUG0 ("smp_gen_p1_4_confirm");
    if ((p_dev_rec = btm_find_dev (p_cb->pairing_bda)) == NULL)
    {
        SMP_TRACE_ERROR0("can not generate confirm for unknown device");
        return;
    }

    BTM_ReadConnectionAddr(p_cb->local_bda);

    if (p_cb->role == HCI_ROLE_MASTER)
    {
        /* LSB : rat': initiator's(local) address type */
        UINT8_TO_STREAM(p, 0);
        /* LSB : iat': responder's address type */
        UINT8_TO_STREAM(p, p_dev_rec->ble.ble_addr_type);
        /* concatinate preq */
        smp_concatenate_local(p_cb, &p, SMP_OPCODE_PAIRING_REQ);
        /* concatinate pres */
        smp_concatenate_peer(p_cb, &p, SMP_OPCODE_PAIRING_RSP);
    }
    else
    {
        /* LSB : iat': initiator's address type */
        UINT8_TO_STREAM(p, p_dev_rec->ble.ble_addr_type);
        /* LSB : rat': responder's(local) address type */
        UINT8_TO_STREAM(p, 0);
        /* concatinate preq */
        smp_concatenate_peer(p_cb, &p, SMP_OPCODE_PAIRING_REQ);
        /* concatinate pres */
        smp_concatenate_local(p_cb, &p, SMP_OPCODE_PAIRING_RSP);
    }
#if SMP_DEBUG == TRUE
    SMP_TRACE_DEBUG0("p1 = pres || preq || rat' || iat'");
    smp_debug_print_nbyte_little_endian ((UINT8 *)p1, (const UINT8 *)"P1", 16);
#endif
}
/*******************************************************************************
**
** Function         smp_gen_p2_4_confirm
**
** Description      Generate Confirm/Compare Step2:
**                  p2 = padding || ia || ra
**
** Returns          void
**
*******************************************************************************/
void smp_gen_p2_4_confirm( tSMP_CB *p_cb, BT_OCTET16 p2)
{
    UINT8   *p = (UINT8 *)p2;

    SMP_TRACE_DEBUG0 ("smp_gen_p2_4_confirm");
    memset(p, 0, sizeof(BT_OCTET16));

    if (p_cb->role == HCI_ROLE_MASTER)
    {
        /* LSB ra */
        BDADDR_TO_STREAM(p, p_cb->pairing_bda);
        /* ia */
        BDADDR_TO_STREAM(p, p_cb->local_bda);
    }
    else
    {
        /* LSB ra */
        BDADDR_TO_STREAM(p, p_cb->local_bda);
        /* ia */
        BDADDR_TO_STREAM(p, p_cb->pairing_bda);
    }
#if SMP_DEBUG == TRUE
    SMP_TRACE_DEBUG0("p2 = padding || ia || ra");
    smp_debug_print_nbyte_little_endian(p2, (const UINT8 *)"p2", 16);
#endif
}
/*******************************************************************************
**
** Function         smp_calculate_comfirm
**
** Description      This function is called to calculate Confirm value.
**
** Returns          void
**
*******************************************************************************/
void smp_calculate_comfirm (tSMP_CB *p_cb, BT_OCTET16 rand, BD_ADDR bda)
{
    BT_OCTET16      p1;
    tSMP_ENC       output;
    tSMP_STATUS     status = SMP_PAIR_FAIL_UNKNOWN;

    SMP_TRACE_DEBUG0 ("smp_calculate_comfirm ");
    /* generate p1 = pres || preq || rat' || iat' */
    smp_gen_p1_4_confirm(p_cb, p1);

    /* p1 = rand XOR p1 */
    smp_xor_128(p1, rand);

    smp_debug_print_nbyte_little_endian ((UINT8 *)p1, (const UINT8 *)"P1' = r XOR p1", 16);

    /* calculate e(k, r XOR p1), where k = TK */
    if (!SMP_Encrypt(p_cb->tk, BT_OCTET16_LEN, p1, BT_OCTET16_LEN, &output))
    {
        SMP_TRACE_ERROR0("smp_generate_csrk failed");
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &status);
    }
    else
    {
        smp_calculate_comfirm_cont(p_cb, &output);
    }
}
/*******************************************************************************
**
** Function         smp_calculate_comfirm_cont
**
** Description      This function is called when SConfirm/MConfirm is generated
**                  proceed to send the Confirm request/response to peer device.
**
** Returns          void
**
*******************************************************************************/
static void smp_calculate_comfirm_cont(tSMP_CB *p_cb, tSMP_ENC *p)
{
    BT_OCTET16    p2;
    tSMP_ENC      output;
    tSMP_STATUS     status = SMP_PAIR_FAIL_UNKNOWN;

    SMP_TRACE_DEBUG0 ("smp_calculate_comfirm_cont ");
#if SMP_DEBUG == TRUE
    SMP_TRACE_DEBUG0("Confirm step 1 p1' = e(k, r XOR p1)  Generated");
    smp_debug_print_nbyte_little_endian (p->param_buf, (const UINT8 *)"C1", 16);
#endif

    smp_gen_p2_4_confirm(p_cb, p2);

    /* calculate p2 = (p1' XOR p2) */
    smp_xor_128(p2, p->param_buf);
    smp_debug_print_nbyte_little_endian ((UINT8 *)p2, (const UINT8 *)"p2' = C1 xor p2", 16);

    /* calculate: Confirm = E(k, p1' XOR p2) */
    if (!SMP_Encrypt(p_cb->tk, BT_OCTET16_LEN, p2, BT_OCTET16_LEN, &output))
    {
        SMP_TRACE_ERROR0("smp_calculate_comfirm_cont failed");
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &status);
    }
    else
    {
        switch (p_cb->rand_enc_proc)
        {
            case SMP_GEN_CONFIRM:
                smp_process_confirm(p_cb, &output);
                break;

            case SMP_GEN_COMPARE:
                smp_process_compare(p_cb, &output);
                break;
        }
    }
}
/*******************************************************************************
**
** Function         smp_genenrate_confirm
**
** Description      This function is called when a 48 bits random number is generated
**                  as SRand or MRand, continue to calculate Sconfirm or MConfirm.
**
** Returns          void
**
*******************************************************************************/
static void smp_genenrate_confirm(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_genenrate_confirm ");
    p_cb->rand_enc_proc = SMP_GEN_CONFIRM;

    smp_debug_print_nbyte_little_endian ((UINT8 *)p_cb->rand,  (const UINT8 *)"local rand", 16);

    smp_calculate_comfirm(p_cb, p_cb->rand, p_cb->pairing_bda);
}
/*******************************************************************************
**
** Function         smp_generate_compare
**
** Description      This function is called to generate SConfirm for Slave device,
**                  or MSlave for Master device. This function can be also used for
**                  generating Compare number for confirm value check.
**
** Returns          void
**
*******************************************************************************/
void smp_generate_compare (tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    SMP_TRACE_DEBUG0 ("smp_generate_compare ");
    p_cb->rand_enc_proc = SMP_GEN_COMPARE;

    smp_debug_print_nbyte_little_endian ((UINT8 *)p_cb->rrand,  (const UINT8 *)"peer rand", 16);

    smp_calculate_comfirm(p_cb, p_cb->rrand, p_cb->local_bda);
}
/*******************************************************************************
**
** Function         smp_process_confirm
**
** Description      This function is called when SConfirm/MConfirm is generated
**                  proceed to send the Confirm request/response to peer device.
**
** Returns          void
**
*******************************************************************************/
static void smp_process_confirm(tSMP_CB *p_cb, tSMP_ENC *p)
{
    tSMP_KEY    key;

    SMP_TRACE_DEBUG0 ("smp_process_confirm ");
#if SMP_CONFORMANCE_TESTING == TRUE
    if (p_cb->enable_test_confirm_val)
    {
        BTM_TRACE_DEBUG0 ("Use confirm value from script");
        memcpy(p_cb->confirm, p_cb->test_confirm, BT_OCTET16_LEN);
    }
    else
        memcpy(p_cb->confirm, p->param_buf, BT_OCTET16_LEN);
#else
    memcpy(p_cb->confirm, p->param_buf, BT_OCTET16_LEN);
#endif


#if (SMP_DEBUG == TRUE)
    SMP_TRACE_DEBUG0("Confirm  Generated");
    smp_debug_print_nbyte_little_endian ((UINT8 *)p_cb->confirm,  (const UINT8 *)"Confirm", 16);
#endif

    key.key_type = SMP_KEY_TYPE_CFM;
    key.p_data = p->param_buf;

    smp_sm_event(p_cb, SMP_KEY_READY_EVT, &key);
}
/*******************************************************************************
**
** Function         smp_process_compare
**
** Description      This function is called when Compare is generated using the
**                  RRand and local BDA, TK information.
**
** Returns          void
**
*******************************************************************************/
static void smp_process_compare(tSMP_CB *p_cb, tSMP_ENC *p)
{
    tSMP_KEY    key;

    SMP_TRACE_DEBUG0 ("smp_process_compare ");
#if (SMP_DEBUG == TRUE)
    SMP_TRACE_DEBUG0("Compare Generated");
    smp_debug_print_nbyte_little_endian (p->param_buf,  (const UINT8 *)"Compare", 16);
#endif
    key.key_type = SMP_KEY_TYPE_CMP;
    key.p_data   = p->param_buf;

    smp_sm_event(p_cb, SMP_KEY_READY_EVT, &key);
}

/*******************************************************************************
**
** Function         smp_process_stk
**
** Description      This function is called when STK is generated
**                  proceed to send the encrypt the link using STK.
**
** Returns          void
**
*******************************************************************************/
static void smp_process_stk(tSMP_CB *p_cb, tSMP_ENC *p)
{
    tSMP_KEY    key;

    SMP_TRACE_DEBUG0 ("smp_process_stk ");
#if (SMP_DEBUG == TRUE)
    SMP_TRACE_ERROR0("STK Generated");
#endif
    smp_mask_enc_key(p_cb->loc_enc_size, p->param_buf);

    key.key_type = SMP_KEY_TYPE_STK;
    key.p_data   = p->param_buf;

    smp_sm_event(p_cb, SMP_KEY_READY_EVT, &key);
}

/*******************************************************************************
**
** Function         smp_genenrate_ltk_cont
**
** Description      This function is to calculate LTK = d1(ER, DIV, 0)= e(ER, DIV)
**
** Returns          void
**
*******************************************************************************/
static void smp_genenrate_ltk_cont(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    BT_OCTET16  er;
    tSMP_ENC    output;
    tSMP_STATUS     status = SMP_PAIR_FAIL_UNKNOWN;

    SMP_TRACE_DEBUG0 ("smp_genenrate_ltk_cont ");
    BTM_GetDeviceEncRoot(er);

    /* LTK = d1(ER, DIV, 0)= e(ER, DIV)*/
    if (!SMP_Encrypt(er, BT_OCTET16_LEN, (UINT8 *)&p_cb->div,
                     sizeof(UINT16), &output))
    {
        SMP_TRACE_ERROR0("smp_genenrate_ltk_cont failed");
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &status);
    }
    else
    {
        /* mask the LTK */
        smp_mask_enc_key(p_cb->loc_enc_size, output.param_buf);
        memcpy((void *)p_cb->ltk, output.param_buf, BT_OCTET16_LEN);
        smp_generate_rand_vector(p_cb, NULL);
    }

}

/*******************************************************************************
**
** Function         smp_generate_y
**
** Description      This function is to proceed generate Y = E(DHK, Rand)
**
** Returns          void
**
*******************************************************************************/
static void smp_generate_y(tSMP_CB *p_cb, tSMP_INT_DATA *p)
{
    BT_OCTET16  dhk;
    tSMP_ENC   output;
    tSMP_STATUS     status = SMP_PAIR_FAIL_UNKNOWN;


    SMP_TRACE_DEBUG0 ("smp_generate_y ");
    BTM_GetDeviceDHK(dhk);

    if (!SMP_Encrypt(dhk, BT_OCTET16_LEN, p_cb->enc_rand,
                     BT_OCTET8_LEN, &output))
    {
        SMP_TRACE_ERROR0("smp_generate_y failed");
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &status);
    }
    else
    {
        smp_process_ediv(p_cb, &output);
    }
}
/*******************************************************************************
**
** Function         smp_generate_rand_vector
**
** Description      This function is called when LTK is generated, send state machine
**                  event to SMP.
**
** Returns          void
**
*******************************************************************************/
static void smp_generate_rand_vector (tSMP_CB *p_cb, tSMP_INT_DATA *p)
{
    /* generate EDIV and rand now */
    /* generate random vector */
    SMP_TRACE_DEBUG0 ("smp_generate_rand_vector ");
    p_cb->rand_enc_proc = SMP_GEN_RAND_V;
    if (!btsnd_hcic_ble_rand((void *)smp_rand_back))
        smp_rand_back(NULL);

}
/*******************************************************************************
**
** Function         smp_genenrate_smp_process_edivltk_cont
**
** Description      This function is to calculate EDIV = Y xor DIV
**
** Returns          void
**
*******************************************************************************/
static void smp_process_ediv(tSMP_CB *p_cb, tSMP_ENC *p)
{
    tSMP_KEY    key;
    UINT8 *pp= p->param_buf;
    UINT16  y;

    SMP_TRACE_DEBUG0 ("smp_process_ediv ");
    STREAM_TO_UINT16(y, pp);

    /* EDIV = Y xor DIV */
    p_cb->ediv = p_cb->div ^ y;
    /* send LTK ready */
    SMP_TRACE_ERROR0("LTK ready");
    key.key_type = SMP_KEY_TYPE_LTK;
    key.p_data   = p->param_buf;

    smp_sm_event(p_cb, SMP_KEY_READY_EVT, &key);
}

/*******************************************************************************
**
** Function         smp_rand_back
**
** Description      This function is to process the rand command finished,
**                  process the random/encrypted number for further action.
**
** Returns          void
**
*******************************************************************************/
static void smp_rand_back(tBTM_RAND_ENC *p)
{
    tSMP_CB *p_cb = &smp_cb;
    UINT8   *pp = p->param_buf;
    UINT8   failure = SMP_PAIR_FAIL_UNKNOWN;
    UINT8   state = p_cb->rand_enc_proc & ~0x80;

    SMP_TRACE_DEBUG1 ("smp_rand_back state=0x%x", state);
    if (p && p->status == HCI_SUCCESS)
    {
        switch (state)
        {

            case SMP_GEN_SRAND_MRAND:
                memcpy((void *)p_cb->rand, p->param_buf, p->param_len);
                smp_genenrate_rand_cont(p_cb, NULL);
                break;

            case SMP_GEN_SRAND_MRAND_CONT:
                memcpy((void *)&p_cb->rand[8], p->param_buf, p->param_len);
                smp_genenrate_confirm(p_cb, NULL);
                break;

            case SMP_GEN_DIV_LTK:
                STREAM_TO_UINT16(p_cb->div, pp);
                smp_genenrate_ltk_cont(p_cb, NULL);
                break;

            case SMP_GEN_DIV_CSRK:
                STREAM_TO_UINT16(p_cb->div, pp);
                smp_compute_csrk(p_cb, NULL);
                break;

            case SMP_GEN_TK:
                smp_proc_passkey(p_cb, p);
                break;

            case SMP_GEN_RAND_V:
                memcpy(p_cb->enc_rand, p->param_buf, BT_OCTET8_LEN);
                smp_generate_y(p_cb, NULL);
                break;

        }

        return;
    }

    SMP_TRACE_ERROR1("smp_rand_back Key generation failed: (%d)", p_cb->rand_enc_proc);

    smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &failure);

}
#endif

