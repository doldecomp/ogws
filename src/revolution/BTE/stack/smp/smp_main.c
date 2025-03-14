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
    #include "smp_int.h"


const char * const smp_state_name [] =
{
    "SMP_ST_IDLE",
    "SMP_ST_WAIT_APP_RSP",
    "SMP_ST_SEC_REQ_PENDING",
    "SMP_ST_PAIR_REQ_RSP",
    "SMP_ST_WAIT_CONFIRM",
    "SMP_ST_CONFIRM",
    "SMP_ST_RAND",
    "SMP_ST_ENC_PENDING",
    "SMP_ST_BOND_PENDING",
    "SMP_ST_RELEASE_DELAY",
    "SMP_ST_MAX"
};
const char * const smp_event_name [] =
{
    "PAIRING_REQ_EVT",
    "PAIRING_RSP_EVT",
    "CONFIRM_EVT",
    "RAND_EVT",
    "PAIRING_FAILED_EVT",
    "ENC_INFO_EVT",
    "MASTER_ID_EVT",
    "ID_INFO_EVT",
    "ID_ADDR_EVT",
    "SIGN_INFO_EVT",
    "SECURITY_REQ_EVT",
    "KEY_READY_EVT",
    "ENCRYPTED_EVT",
    "L2CAP_CONN_EVT",
    "L2CAP_DISCONN_EVT",
    "API_IO_RSP_EVT",
    "API_SEC_GRANT_EVT",
    "TK_REQ_EVT",
    "AUTH_CMPL_EVT",
    "ENC_REQ_EVT",
    "BOND_REQ_EVT",
    "DISCARD_SEC_REQ_EVT",
    "RELEASE_DELAY_EVT",
    "RELEASE_DELAY_TOUT_EVT",
    "MAX_EVT"
};
const char * smp_get_event_name(tSMP_EVENT event);
const char * smp_get_state_name(tSMP_STATE state);

    #define SMP_SM_IGNORE       0
    #define SMP_NUM_ACTIONS     2
    #define SMP_SME_NEXT_STATE  2
    #define SMP_SM_NUM_COLS     3
typedef const UINT8 (*tSMP_SM_TBL)[SMP_SM_NUM_COLS];

enum
{
    SMP_PROC_SEC_REQ,
    SMP_SEND_PAIR_REQ,
    SMP_SEND_PAIR_RSP,
    SMP_SEND_CONFIRM,
    SMP_SEND_PAIR_FAIL,
    SMP_SEND_INIT,
    SMP_SEND_SECU_INFO,
    SMP_SEND_ID_INFO,
    SMP_SEND_LTK_REPLY,
    SMP_PROC_PAIR_CMD,
    SMP_PROC_PAIR_FAIL,
    SMP_PROC_CONFIRM,
    SMP_PROC_INIT,
    SMP_PROC_ENC_INFO,
    SMP_PROC_MASTER_ID,
    SMP_PROC_ID_INFO,
    SMP_PROC_ID_ADDR,
    SMP_PROC_SRK_INFO,
    SMP_PROC_SEC_GRANT,
    SMP_PROC_SL_KEY,
    SMP_PROC_COMPARE,
    SMP_PROC_IO_RSP,
    SMP_GENERATE_COMPARE,
    SMP_GENERATE_CONFIRM,
    SMP_GENERATE_STK,
    SMP_KEY_DISTRIBUTE,
    SMP_START_ENC,
    SMP_PAIRING_CMPL,
    SMP_DECIDE_ASSO_MODEL,
    SMP_SEND_APP_CBACK,
    SMP_CHECK_AUTH_REQ,
    SMP_PAIR_TERMINATE,
    SMP_ENC_CMPL,
    SMP_PROC_DISCARD,
    SMP_PROC_REL_DELAY,
    SMP_PROC_REL_DELAY_TOUT,
    SMP_SM_NO_ACTION
};

static const tSMP_ACT smp_sm_action[] =
{
    smp_proc_sec_req,
    smp_send_pair_req,
    smp_send_pair_rsp,
    smp_send_confirm,
    smp_send_pair_fail,
    smp_send_init,
    smp_send_enc_info,
    smp_send_id_info,
    smp_send_ltk_reply,
    smp_proc_pair_cmd,
    smp_proc_pair_fail,
    smp_proc_confirm,
    smp_proc_init,
    smp_proc_enc_info,
    smp_proc_master_id,
    smp_proc_id_info,
    smp_proc_id_addr,
    smp_proc_srk_info,
    smp_proc_sec_grant,
    smp_proc_sl_key,
    smp_proc_compare,
    smp_proc_io_rsp,
    smp_generate_compare,
    smp_generate_confirm,
    smp_generate_stk,
    smp_key_distribution,
    smp_start_enc,
    smp_pairing_cmpl,
    smp_decide_asso_model,
    smp_send_app_cback,
    smp_check_auth_req,
    smp_pair_terminate,
    smp_enc_cmpl,
    smp_proc_discard,
    smp_proc_release_delay,
    smp_proc_release_delay_tout,
};
/************ SMP Master FSM State/Event Indirection Table **************/
static const UINT8 smp_ma_entry_map[][SMP_ST_MAX] =
{
/* state name:           Idle WaitApp SecReq Pair   Wait Confirm Init Enc   Bond  Rel
                               Rsp    Pend   ReqRsp Cfm              Pend  Pend   Delay    */
/* PAIR_REQ           */{ 0,    0,     0,      0,     0,   0,    0,   0,    0,     0   },
/* PAIR_RSP           */{ 0,    0,     0,      1,     0,   0,    0,   0,    0,     0   },
/* CONFIRM            */{ 0,    0,     0,      0,     0,   1,    0,   0,    0,     0   },
/* INIT               */{ 0,    0,     0,      0,     0,   0,    1,   0,    0,     0   },
/* PAIR_FAIL          */{ 0,    0x81,  0,      0x81,  0x81,0x81, 0x81,0,    0,     0   },
/* ENC_INFO           */{ 0,    0,     0,      0,     0,   0,    0,   0,    1,     0   },
/* MASTER_ID          */{ 0,    0,     0,      0,     0,   0,    0,   0,    4,     0   },
/* ID_INFO            */{ 0,    0,     0,      0,     0,   0,    0,   0,    2,     0   },
/* ID_ADDR            */{ 0,    0,     0,      0,     0,   0,    0,   0,    5,     0   },
/* SIGN_INFO          */{ 0,    0,     0,      0,     0,   0,    0,   0,    3,     0   },
/* SEC_REQ            */{ 2,    0,     0,      0,     0,   0,    0,   0,    0,     0   },
/* KEY_READY          */{ 0,    3,     0,      3,     1,   0,    2,   1,    6,     0   },
/* ENC_CMPL           */{ 0,    0,     0,      0,     0,   0,    0,   2,    0,     0   },
/* L2C_CONN           */{ 1,    0,     0,      0,     0,   0,    0,   0,    0,     0   },
/* L2C_DISC           */{ 0,    0x83,  0,      0x83,  0x83,0x83, 0x83,0x83, 0x83,  2   },
/* IO_RSP             */{ 0,    2,     0,      0,     0,   0,    0,   0,    0,     0   },
/* SEC_GRANT          */{ 0,    1,     0,      0,     0,   0,    0,   0,    0,     0   },
/* TK_REQ             */{ 0,    0,     0,      2,     0,   0,    0,   0,    0,     0   },
/* AUTH_CMPL          */{ 0,    0x82,  0,      0x82,  0x82,0x82, 0x82,0x82, 0x82,  0   },
/* ENC_REQ            */{ 0,    4,     0,      0,     0,   0,    3,   0,    0,     0   },
/* BOND_REQ           */{ 0,    0,     0,      0,     0,   0,    0,   3,    0,     0   },
/* DISCARD_SEC_REQ    */{ 0,    5,     0,      0,     0,   0,    0,   3,    0,     0   },
/* RELEASE_DELAY      */{ 0,    0,     0,      0,     0,   0,    0,   0,    0,     1   },
/* RELEASE_DELAY_TOUT */{ 0,    0,     0,      0,     0,   0,    0,   0,    0,     2   },
};

static const UINT8 smp_all_table[][SMP_SM_NUM_COLS] = {
/* Event       			Action                              Next State */
/* PAIR_FAIL */          {SMP_PROC_PAIR_FAIL,       SMP_PROC_REL_DELAY_TOUT,    SMP_ST_IDLE},
/* AUTH_CMPL */          {SMP_SEND_PAIR_FAIL,      SMP_PAIRING_CMPL,      SMP_ST_RELEASE_DELAY},
/* L2C_DISC  */          {SMP_PAIR_TERMINATE,      SMP_SM_NO_ACTION,      SMP_ST_IDLE}
};

static const UINT8 smp_ma_idle_table[][SMP_SM_NUM_COLS] = {
/* Event       Action                   Next State */
/* L2C_CONN */      {SMP_SEND_APP_CBACK,     SMP_SM_NO_ACTION,   SMP_ST_WAIT_APP_RSP},
/* SEC_REQ  */      {SMP_PROC_SEC_REQ,       SMP_SEND_APP_CBACK, SMP_ST_WAIT_APP_RSP}
};

static const UINT8 smp_ma_wait_app_rsp_table[][SMP_SM_NUM_COLS] = {
/* Event       			                                 Action          Next State */
/* SEC_GRANT            */ { SMP_PROC_SEC_GRANT,   SMP_SEND_APP_CBACK, SMP_ST_WAIT_APP_RSP},
/* IO_RSP               */ { SMP_SEND_PAIR_REQ,    SMP_SM_NO_ACTION,   SMP_ST_PAIR_REQ_RSP},
/* KEY_READY            */ { SMP_GENERATE_CONFIRM, SMP_SM_NO_ACTION,   SMP_ST_WAIT_CONFIRM},/* TK ready */
/* ENC_REQ              */ { SMP_START_ENC,        SMP_SM_NO_ACTION,   SMP_ST_ENC_PENDING},/* start enc mode setup */
/* DISCARD_SEC_REQ      */ { SMP_PROC_DISCARD,     SMP_SM_NO_ACTION,   SMP_ST_IDLE}
};

static const UINT8 smp_ma_pair_req_rsp_table [][SMP_SM_NUM_COLS] = {
/* Event       		Action              Next State */
/* PAIR_RSP */ { SMP_PROC_PAIR_CMD,     SMP_DECIDE_ASSO_MODEL,  SMP_ST_PAIR_REQ_RSP},
/* TK_REQ   */ { SMP_SEND_APP_CBACK,    SMP_SM_NO_ACTION,       SMP_ST_WAIT_APP_RSP},
/* KEY_READY */{ SMP_GENERATE_CONFIRM,  SMP_SM_NO_ACTION,       SMP_ST_WAIT_CONFIRM} /* TK ready */
};

static const UINT8 smp_ma_wait_confirm_table[][SMP_SM_NUM_COLS] = {
/* Event       			Action          Next State */
/* KEY_READY*/ {SMP_SEND_CONFIRM,       SMP_SM_NO_ACTION,       SMP_ST_CONFIRM}/* CONFIRM ready */
};

static const UINT8 smp_ma_confirm_table [][SMP_SM_NUM_COLS] = {
/* Event       			Action          Next State */
/* CONFIRM  */ { SMP_PROC_CONFIRM,      SMP_SEND_INIT,          SMP_ST_RAND}
};

static const UINT8 smp_ma_init_table [][SMP_SM_NUM_COLS] = {
/* Event       			Action          Next State */
/* INIT     */ { SMP_PROC_INIT,         SMP_GENERATE_COMPARE,    SMP_ST_RAND},
/* KEY_READY*/ { SMP_PROC_COMPARE,      SMP_SM_NO_ACTION,   SMP_ST_RAND},  /* Compare ready */
/* ENC_REQ  */ { SMP_GENERATE_STK,      SMP_SM_NO_ACTION,   SMP_ST_ENC_PENDING}
};
static const UINT8 smp_ma_enc_pending_table[][SMP_SM_NUM_COLS] = {
/* Event       			Action          Next State */
/* KEY_READY */ { SMP_START_ENC,        SMP_SM_NO_ACTION,   SMP_ST_ENC_PENDING},  /* STK ready */
/* ENCRYPTED */ { SMP_CHECK_AUTH_REQ,   SMP_SM_NO_ACTION,   SMP_ST_ENC_PENDING},
/* BOND_REQ  */ { SMP_KEY_DISTRIBUTE,   SMP_SM_NO_ACTION,   SMP_ST_BOND_PENDING}
};
static const UINT8 smp_ma_bond_pending_table[][SMP_SM_NUM_COLS] = {
/* Event       			Action          Next State */
/* ENC_INFO */ { SMP_PROC_ENC_INFO,     SMP_SM_NO_ACTION,   SMP_ST_BOND_PENDING},
/* ID_INFO  */ { SMP_PROC_ID_INFO,      SMP_SM_NO_ACTION,   SMP_ST_BOND_PENDING},
/* SIGN_INFO*/ { SMP_PROC_SRK_INFO,     SMP_SM_NO_ACTION,   SMP_ST_BOND_PENDING},
/* MASTER_ID*/ { SMP_PROC_MASTER_ID,    SMP_SM_NO_ACTION,   SMP_ST_BOND_PENDING},
/* ID_ADDR  */ { SMP_PROC_ID_ADDR,      SMP_SM_NO_ACTION,   SMP_ST_BOND_PENDING},
/* KEY_READY */ {SMP_SEND_SECU_INFO,    SMP_SM_NO_ACTION,   SMP_ST_BOND_PENDING}   /* LTK ready */
};

static const UINT8 smp_ma_rel_delay_table[][SMP_SM_NUM_COLS] = {
/* Event       Action                   Next State */
/* RELEASE_DELAY*/       {SMP_PROC_REL_DELAY,      SMP_SM_NO_ACTION,      SMP_ST_RELEASE_DELAY},
/* RELEASE_DELAY_TOUT*/  {SMP_PROC_REL_DELAY_TOUT, SMP_SM_NO_ACTION,      SMP_ST_IDLE}
};


/************ SMP Slave FSM State/Event Indirection Table **************/
static const UINT8 smp_sl_entry_map[][SMP_ST_MAX] =
{
/* state name:            Idle Wait   SecReq Pair   Wait Confirm Init Enc   Bond  Rel
                               AppRsp Pend   ReqRsp Cfm              Pend  Pend   Delay   */
/* PAIR_REQ */           { 2,    0,    1,      0,     0,   0,    0,   0,    0,     0       },
/* PAIR_RSP */           { 0,    0,    0,      0,     0,   0,    0,   0,    0,     0       },
/* CONFIRM  */           { 0,    4,    0,      1,     1,   0,    0,   0,    0,     0       },
/* INIT     */           { 0,    0,    0,      0,     0,   1,    2,   0,    0,     0       },
/* PAIR_FAIL*/           { 0,    0x81, 0x81,   0x81,  0x81,0x81, 0x81,0x81, 0,     0       },
/* ENC_INFO */           { 0,    0,    0,      0,     0,   0,    0,   0,    3,     0       },
/* MASTER_ID*/           { 0,    0,    0,      0,     0,   0,    0,   0,    5,     0       },
/* ID_INFO  */           { 0,    0,    0,      0,     0,   0,    0,   0,    4,     0       },
/* ID_ADDR  */           { 0,    0,    0,      0,     0,   0,    0,   0,    6,     0       },
/* SIGN_INFO*/           { 0,    0,    0,      0,     0,   0,    0,   0,    2,     0       },
/* SEC_REQ  */           { 0,    0,    0,      0,     0,   0,    0,   0,    0,     0       },

/* KEY_READY*/           { 0,    3,    0,      3,     2,   2,    1,   2,    1,     0       },
/* ENC_CMPL */           { 0,    0,    2,      0,     0,   0,    0,   3,    0,     0       },
/* L2C_CONN */           { 1,    0,    0,      0,     0,   0,    0,   0,    0,     0       },
/* L2C_DISC */           { 0,    0x83, 0x83,   0x83,  0x83,0x83, 0x83,0x83, 0x83,  2       },
/* IO_RSP   */           { 0,    1,    0,      0,     0,   0,    0,   0,    0,     0       },
/* SEC_GRANT*/           { 0,    2,    0,      0,     0,   0,    0,   0,    0,     0       },

/* TK_REQ   */           { 0,    0,    0,      2,     0,   0,    0,   0,    0,     0       },
/* AUTH_CMPL*/           { 0,    0x82, 0x82,   0x82,  0x82,0x82, 0x82,0x82, 0x82,  0       },
/* ENC_REQ  */           { 0,    0,    0,      0,     0,   0,    0,   1,    0,     0       },
/* BOND_REQ */           { 0,    0,    0,      0,     0,   0,    0,   4,    0,     0       },
/* DISCARD_SEC_REQ    */ { 0,    0,    0,      0,     0,   0,    0,   0,    0,     0       },
/* RELEASE_DELAY      */ { 0,    0,    0,      0,     0,   0,    0,   0,    0,     1       },
/* RELEASE_DELAY_TOUT */ { 0,    0,    0,      0,     0,   0,    0,   0,    0,     2       },
};

static const UINT8 smp_sl_idle_table[][SMP_SM_NUM_COLS] = {
/* Event       			Action                              Next State */
/* L2C_CONN */      {SMP_SEND_APP_CBACK,  SMP_SM_NO_ACTION,       SMP_ST_WAIT_APP_RSP},
/* PAIR_REQ */      {SMP_PROC_PAIR_CMD,   SMP_SEND_APP_CBACK,     SMP_ST_WAIT_APP_RSP}
};

static const UINT8 smp_sl_wait_app_rsp_table [][SMP_SM_NUM_COLS] = {
/* Event       			Action              Next State */
/* IO_RSP    */ {SMP_PROC_IO_RSP,       SMP_SM_NO_ACTION,       SMP_ST_PAIR_REQ_RSP},
/* SEC_GRANT */ {SMP_PROC_SEC_GRANT,    SMP_SEND_APP_CBACK,     SMP_ST_WAIT_APP_RSP},
/* KEY_READY */ {SMP_PROC_SL_KEY,       SMP_SM_NO_ACTION,       SMP_ST_WAIT_APP_RSP},/* TK ready */
/* CONFIRM   */ {SMP_PROC_CONFIRM,      SMP_SM_NO_ACTION,       SMP_ST_CONFIRM}
};

static const UINT8 smp_sl_sec_request_table[][SMP_SM_NUM_COLS] = {
/* Event       			Action          Next State */
/* PAIR_REQ */{SMP_PROC_PAIR_CMD,       SMP_SEND_PAIR_RSP,      SMP_ST_PAIR_REQ_RSP},
/* ENCRYPTED*/{SMP_ENC_CMPL,        SMP_SM_NO_ACTION,       SMP_ST_PAIR_REQ_RSP},
};

static const UINT8 smp_sl_pair_req_rsp_table[][SMP_SM_NUM_COLS] = {
/* Event       			Action                   		Next State */
/* CONFIRM  */ {SMP_PROC_CONFIRM,       SMP_SM_NO_ACTION,   SMP_ST_CONFIRM},
/* TK_REQ   */ {SMP_SEND_APP_CBACK,     SMP_SM_NO_ACTION,   SMP_ST_WAIT_APP_RSP},
/* KEY_READY */{SMP_PROC_SL_KEY,        SMP_SM_NO_ACTION,   SMP_ST_PAIR_REQ_RSP} /* TK/Confirm ready */

};

static const UINT8 smp_sl_wait_confirm_table[][SMP_SM_NUM_COLS] = {
/* Event       			Action                   			Next State */
/* CONFIRM  */ {SMP_PROC_CONFIRM,       SMP_SEND_CONFIRM,   SMP_ST_CONFIRM},
/* KEY_READY*/ {SMP_PROC_SL_KEY,        SMP_SM_NO_ACTION,   SMP_ST_WAIT_CONFIRM}
};
static const UINT8 smp_sl_confirm_table [][SMP_SM_NUM_COLS] = {
/* Event       			Action                   		Next State */
/* INIT_EVT */{ SMP_PROC_INIT,          SMP_GENERATE_COMPARE,   SMP_ST_RAND},
/* KEY_READY*/ {SMP_PROC_SL_KEY,        SMP_SM_NO_ACTION,       SMP_ST_CONFIRM} /* TK/Confirm ready */
};
static const UINT8 smp_sl_init_table [][SMP_SM_NUM_COLS] = {
/* Event       			Action                   		        Next State */
/* KEY_READY */ {SMP_PROC_COMPARE,      SMP_SM_NO_ACTION,       SMP_ST_RAND},   /* compare match */
/* INIT_EVT  */ {SMP_SEND_INIT,         SMP_SM_NO_ACTION,       SMP_ST_ENC_PENDING}
};
static const UINT8 smp_sl_enc_pending_table[][SMP_SM_NUM_COLS] = {
/* Event       			Action                   		Next State */
/* ENC_REQ   */ {SMP_GENERATE_STK,      SMP_SM_NO_ACTION,       SMP_ST_ENC_PENDING},
/* KEY_READY */ {SMP_SEND_LTK_REPLY,    SMP_SM_NO_ACTION,       SMP_ST_ENC_PENDING},/* STK ready */
/* ENCRYPTED */ {SMP_CHECK_AUTH_REQ,    SMP_SM_NO_ACTION,       SMP_ST_ENC_PENDING},
/* BOND_REQ  */ {SMP_KEY_DISTRIBUTE,    SMP_SM_NO_ACTION,       SMP_ST_BOND_PENDING}
};
static const UINT8 smp_sl_bond_pending_table[][SMP_SM_NUM_COLS] = {
/* Event       			Action                   		Next State */
/* KEY_READY */ {SMP_SEND_SECU_INFO,    SMP_SM_NO_ACTION,       SMP_ST_BOND_PENDING},   /* LTK ready */
/* SIGN_INFO */ {SMP_PROC_SRK_INFO,     SMP_SM_NO_ACTION,       SMP_ST_BOND_PENDING},   /* rev SRK */
/* ENC_INFO */ { SMP_PROC_ENC_INFO,     SMP_SM_NO_ACTION,       SMP_ST_BOND_PENDING},
/* ID_INFO  */ { SMP_PROC_ID_INFO,      SMP_SM_NO_ACTION,       SMP_ST_BOND_PENDING},
/* MASTER_ID*/ { SMP_PROC_MASTER_ID,    SMP_SM_NO_ACTION,       SMP_ST_BOND_PENDING},
/* ID_ADDR  */ { SMP_PROC_ID_ADDR,      SMP_SM_NO_ACTION,       SMP_ST_BOND_PENDING}

};

static const UINT8 smp_sl_rel_delay_table[][SMP_SM_NUM_COLS] = {
/* Event       Action                   Next State */
/* RELEASE_DELAY*/       {SMP_PROC_REL_DELAY,      SMP_SM_NO_ACTION,      SMP_ST_RELEASE_DELAY},
/* RELEASE_DELAY_TOUT*/  {SMP_PROC_REL_DELAY_TOUT, SMP_SM_NO_ACTION,      SMP_ST_IDLE}
};

static const tSMP_SM_TBL smp_state_table[][2] = {
    {smp_ma_idle_table,          smp_sl_idle_table},                  /* SMP_ST_IDLE*/
    {smp_ma_wait_app_rsp_table,  smp_sl_wait_app_rsp_table},           /* SMP_ST_WAIT_APP_RSP */
    {NULL,                       smp_sl_sec_request_table},            /* SMP_ST_SEC_REQ_PENDING */
    {smp_ma_pair_req_rsp_table,  smp_sl_pair_req_rsp_table},           /* SMP_ST_PAIR_REQ_RSP */
    {smp_ma_wait_confirm_table,  smp_sl_wait_confirm_table},           /* SMP_ST_WAIT_CONFIRM */
    {smp_ma_confirm_table,       smp_sl_confirm_table},                /* SMP_ST_CONFIRM */
    {smp_ma_init_table,          smp_sl_init_table},                   /* SMP_ST_RAND */
    {smp_ma_enc_pending_table,   smp_sl_enc_pending_table},            /* SMP_ST_ENC_PENDING */
    {smp_ma_bond_pending_table,  smp_sl_bond_pending_table},           /* SMP_ST_BOND_PENDING */
    {smp_ma_rel_delay_table,     smp_sl_rel_delay_table}               /* SMP_ST_RELEASE_DELAY */
};

typedef const UINT8 (*tSMP_ENTRY_TBL)[SMP_ST_MAX];
static const tSMP_ENTRY_TBL smp_entry_table[] ={
    smp_ma_entry_map,
    smp_sl_entry_map
};

#if SMP_DYNAMIC_MEMORY == FALSE
tSMP_CB  smp_cb;
#endif
#define SMP_ALL_TBL_MASK        0x80


/*******************************************************************************
** Function     smp_set_state
** Returns      None
*******************************************************************************/
void smp_set_state(tSMP_STATE state)
{
    if (state < SMP_ST_MAX)
    {
        SMP_TRACE_DEBUG4( "State change: %s(%d) ==> %s(%d)",
                          smp_get_state_name(smp_cb.state), smp_cb.state,
                          smp_get_state_name(state), state );
        smp_cb.state = state;
    }
    else
    {
        SMP_TRACE_DEBUG1("smp_set_state invalid state =%d", state );
    }
}

/*******************************************************************************
** Function     smp_get_state
** Returns      The smp state
*******************************************************************************/
tSMP_STATE smp_get_state(void)
{
    return smp_cb.state;
}


/*******************************************************************************
**
** Function     smp_sm_event
**
** Description  Handle events to the state machine. It looks up the entry
**              in the smp_entry_table array.
**              If it is a valid entry, it gets the state table.Set the next state,
**              if not NULL state.Execute the action function according to the
**              state table. If the state returned by action function is not NULL
**              state, adjust the new state to the returned state.If (api_evt != MAX),
**              call callback function.
**
** Returns      void.
**
*******************************************************************************/
void smp_sm_event(tSMP_CB *p_cb, tSMP_EVENT event, void *p_data)
{
    UINT8           curr_state = p_cb->state;
    tSMP_SM_TBL     state_table;
    UINT8           action, entry, i;
    tSMP_ENTRY_TBL  entry_table =  smp_entry_table[p_cb->role];

    SMP_TRACE_EVENT0("main smp_sm_event");
    if (curr_state >= SMP_ST_MAX)
    {
        SMP_TRACE_DEBUG1( "Invalid state: %d", curr_state) ;
        return;
    }

    SMP_TRACE_DEBUG5( "SMP Role: %s State: [%s (%d)], Event: [%s (%d)]",\
                      (p_cb->role == 0x01) ?"Slave" : "Master", smp_get_state_name( p_cb->state),
                      p_cb->state, smp_get_event_name(event), event) ;

    /* look up the state table for the current state */
    /* lookup entry /w event & curr_state */
    /* If entry is ignore, return.
     * Otherwise, get state table (according to curr_state or all_state) */
    if ( (entry = entry_table[event - 1][curr_state]) != SMP_SM_IGNORE )
    {
        if (entry & SMP_ALL_TBL_MASK)
        {
            entry &= ~SMP_ALL_TBL_MASK;
            state_table = smp_all_table;
        }
        else
            state_table = smp_state_table[curr_state][p_cb->role];
    }
    else
    {
        SMP_TRACE_DEBUG4( "Ignore event [%s (%d)] in state [%s (%d)]",
                          smp_get_event_name(event), event, smp_get_state_name(curr_state), curr_state);
        return;
    }

    /* Get possible next state from state table. */

    smp_set_state(state_table[entry-1][SMP_SME_NEXT_STATE]);

    /* If action is not ignore, clear param, exec action and get next state.
     * The action function may set the Param for cback.
     * Depending on param, call cback or free buffer. */
    /* execute action */
    /* execute action functions */
    for (i = 0; i < SMP_NUM_ACTIONS; i++)
    {
        if ((action = state_table[entry-1][i]) != SMP_SM_NO_ACTION)
        {
            (*smp_sm_action[action])(p_cb, (tSMP_INT_DATA *)p_data);
        }
        else
        {
            break;
        }
    }
    SMP_TRACE_DEBUG1( "result state = %s", smp_get_state_name( p_cb->state ) ) ;
}


/*******************************************************************************
** Function     smp_get_state_name
** Returns      The smp state name.
*******************************************************************************/
const char * smp_get_state_name(tSMP_STATE state)
{
    const char * p_str = smp_state_name[SMP_ST_MAX];

    if (state < SMP_ST_MAX)
    {
        p_str = smp_state_name[state];
    }
    return p_str;
}
/*******************************************************************************
** Function     smp_get_event_name
** Returns      The smp event name.
*******************************************************************************/
const char * smp_get_event_name(tSMP_EVENT event)
{
    const char * p_str = smp_event_name[SMP_MAX_EVT - 1];

    if (event < SMP_MAX_EVT)
    {
        p_str = smp_event_name[event- 1];
    }
    return p_str;
}
#endif

