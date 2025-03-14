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
 *  This file contains interfaces which are internal to MCAP.
 *
 ******************************************************************************/
#ifndef MCA_INT_H
#define MCA_INT_H
#include "gki.h"
#include "mca_api.h"

/*****************************************************************************
** constants
*****************************************************************************/

/* INT initiates the L2CAP channel */
#define MCA_ACP     0
#define MCA_INT     1

/*****************************************************************************
**  Type Definitions
*****************************************************************************/

/* Header structure for api/received request/response. */
typedef struct {
    BT_HDR          hdr;        /* layer specific information */
    UINT8           op_code;    /* the request/response opcode */
    UINT8           rsp_code;   /* valid only if op_code is a response */
    UINT16          mdl_id;     /* the MDL ID associated with this request/response */
    UINT8           param;      /* other parameter */
    UINT8           mdep_id;    /* the MDEP ID associated with this request/response */
    /* tMCA_HANDLE     rcb_idx;    For internal use only */
    /* tMCA_CL         ccb_idx;    For internal use only */
    tMCA_DL         dcb_idx;    /* For internal use only */
} tMCA_CCB_MSG;

/* This data structure is associated with the AVDT_OPEN_IND_EVT and AVDT_OPEN_CFM_EVT. */
typedef struct {
    BT_HDR          hdr;                /* Event header */
    UINT16          peer_mtu;           /* Transport channel L2CAP MTU of the peer */
    UINT16          lcid;               /* L2CAP LCID  */
    UINT8           param;
} tMCA_OPEN;

typedef struct {
    UINT16          reason;     /* disconnect reason from L2CAP */
    UINT8           param;      /* MCA_INT or MCA_ACP */
    UINT16          lcid;       /* L2CAP LCID  */
} tMCA_CLOSE;

/* Header structure for state machine event parameters. */
typedef union {
    BT_HDR          hdr;        /* layer specific information */
    tMCA_CCB_MSG    api;
    BOOLEAN         llcong;
    UINT8           param;
    tMCA_OPEN       open;
    tMCA_CLOSE      close;
} tMCA_CCB_EVT;

/* control channel states */
enum
{
    MCA_CCB_NULL_ST,        /* not allocated */
    MCA_CCB_OPENING_ST,
    MCA_CCB_OPEN_ST,        /* open */
    MCA_CCB_CLOSING_ST,		/* disconnecting */
    MCA_CCB_MAX_ST
};
typedef UINT8 tMCA_CCB_STATE;

/* control channel events */
enum
{
    MCA_CCB_API_CONNECT_EVT,    /* application initiates a connect request. */
    MCA_CCB_API_DISCONNECT_EVT, /* application initiates a disconnect request. */
    MCA_CCB_API_REQ_EVT,        /* application initiates a request. The request may be create_mdl, delete_mdl, reconnect_mdl or abort_mdl. */
    MCA_CCB_API_RSP_EVT,        /* application initiates a create_mdl or reconnect_mdl response. */
    MCA_CCB_MSG_REQ_EVT,        /* a create_mdl, delete_mdl, reconnect_mdl or abort_mdl request message is received from the peer. */
    MCA_CCB_MSG_RSP_EVT,        /* Response received event.  This event is sent whenever a response message is received for an outstanding request message. */
    MCA_CCB_DL_OPEN_EVT,        /* data channel open. */
    MCA_CCB_LL_OPEN_EVT,        /* Lower layer open.  This event is sent when the lower layer channel is open.  */
    MCA_CCB_LL_CLOSE_EVT,       /* Lower layer close.  This event is sent when the lower layer channel is closed. */
    MCA_CCB_LL_CONG_EVT,        /* Lower layer congestion.  This event is sent when the lower layer is congested. */
    MCA_CCB_RSP_TOUT_EVT        /* time out for waiting the message response on the control channel */
};

/* Header structure for callback event parameters. */
typedef union {
    tMCA_OPEN       open;
    tMCA_CLOSE      close;
    BT_HDR          hdr;        /* layer specific information */
    BT_HDR          *p_pkt;
    BOOLEAN         llcong;
    UINT16          mdl_id;     /* the MDL ID associated with this request/response */
    /* tMCA_HANDLE     rcb_idx;    For internal use only */
    /* tMCA_CL         ccb_idx;    For internal use only */
    /* tMCA_DL         dcb_idx;    For internal use only */
} tMCA_DCB_EVT;

/* data channel states */
enum
{
    MCA_DCB_NULL_ST,        /* not allocated */
    MCA_DCB_OPENING_ST,     /* create/reconnect sequence is successful, waiting for data channel connection */
    MCA_DCB_OPEN_ST,        /* open */
    MCA_DCB_CLOSING_ST,     /* disconnecting */
    MCA_DCB_MAX_ST
};
typedef UINT8 tMCA_DCB_STATE;

/* data channel events */
enum
{
    MCA_DCB_API_CLOSE_EVT,      /* This event is sent when the application wants to disconnect the data channel.*/
    MCA_DCB_API_WRITE_EVT,      /* This event is sent when the application wants to send a data packet to the peer.*/
    MCA_DCB_TC_OPEN_EVT,        /* Transport Channel open.  This event is sent when the channel is open.*/
    MCA_DCB_TC_CLOSE_EVT,       /* Transport Channel close.*/
    MCA_DCB_TC_CONG_EVT,        /* Transport Channel congestion status.*/
    MCA_DCB_TC_DATA_EVT         /* This event is sent when a data packet is received from the peer.*/
};




/* "states" used in transport channel table */
#define MCA_TC_ST_UNUSED   0       /* Unused - unallocated */
#define MCA_TC_ST_IDLE     1       /* No connection */
#define MCA_TC_ST_ACP      2       /* Waiting to accept a connection */
#define MCA_TC_ST_INT      3       /* Initiating a connection */
#define MCA_TC_ST_CONN     4       /* Waiting for connection confirm */
#define MCA_TC_ST_CFG      5       /* Waiting for configuration complete */
#define MCA_TC_ST_OPEN     6       /* Channel opened */
#define MCA_TC_ST_SEC_INT  7       /* Security process as INT */
#define MCA_TC_ST_SEC_ACP  8       /* Security process as ACP */

/* Configuration flags. tMCA_TC_TBL.cfg_flags */
#define MCA_L2C_CFG_IND_DONE   (1<<0)
#define MCA_L2C_CFG_CFM_DONE   (1<<1)
#define MCA_L2C_CFG_CONN_INT   (1<<2)
#define MCA_L2C_CFG_CONN_ACP   (1<<3)
#define MCA_L2C_CFG_DISCN_INT  (1<<4)
#define MCA_L2C_CFG_DISCN_ACP  (1<<5)


#define MCA_CTRL_TCID       0   /* to identify control channel by tMCA_TC_TBL.tcid */

/* transport channel table */
typedef struct {
    UINT16  peer_mtu;       /* L2CAP mtu of the peer device */
    UINT16  my_mtu;         /* Our MTU for this channel */
    UINT16  lcid;           /* L2CAP LCID */
    UINT8   tcid;           /* transport channel id (0, for control channel. (MDEP ID + 1) for data channel) */
    tMCA_DL cb_idx;         /* 1-based index to ccb or dcb */
    UINT8   state;          /* transport channel state */
    UINT8   cfg_flags;      /* L2CAP configuration flags */
    UINT8   id;             /* L2CAP id sent by peer device (need this to handle security pending) */
} tMCA_TC_TBL;

/* transport control block */
typedef struct {
    tMCA_TC_TBL     tc_tbl[MCA_NUM_TC_TBL];
    UINT8           lcid_tbl[MAX_L2CAP_CHANNELS];   /* map LCID to tc_tbl index */
} tMCA_TC;

/* registration control block */
typedef struct {
    tMCA_REG        reg;                /* the parameter at register */
    tMCA_CS         dep[MCA_NUM_DEPS];  /* the registration info for each MDEP */
    tMCA_CTRL_CBACK *p_cback;           /* control callback function */
} tMCA_RCB;

enum
{
    MCA_CCB_STAT_NORM,      /* normal operation (based on ccb state) */
    MCA_CCB_STAT_PENDING,   /* waiting for data channel  */
    MCA_CCB_STAT_RECONN,    /* reinitiate connection after transitioning from CLOSING to IDLE state  */
    MCA_CCB_STAT_DISC       /* MCA_DisconnectReq or MCA_Deregister is called. waiting for all associated CL and DL to detach */
};
typedef UINT8 tMCA_CCB_STAT;

/* control channel control block */
/* the ccbs association with the rcbs
 * ccb[0]              ...ccb[MCA_NUM_LINKS*1-1] -> rcb[0]
 * ccb[MCA_NUM_LINKS*1]...ccb[MCA_NUM_LINKS*2-1] -> rcb[1]
 * ccb[MCA_NUM_LINKS*2]...ccb[MCA_NUM_LINKS*3-1] -> rcb[2]
 */
typedef struct {
    tMCA_RCB        *p_rcb;             /* the associated registration control block */
    TIMER_LIST_ENT  timer_entry;        /* CCB timer list entry */
    tMCA_CCB_MSG    *p_tx_req;          /* Current request being sent/awaiting response */
    tMCA_CCB_MSG    *p_rx_msg;          /* Current message received/being processed */
    BD_ADDR         peer_addr;          /* BD address of peer */
    UINT16          sec_mask;           /* Security mask for connections as initiator */
    UINT16          ctrl_vpsm;          /* The virtual PSM that peer is listening for control channel */
    UINT16          data_vpsm;          /* The virtual PSM that peer is listening for data channel. */
    UINT16          lcid;               /* L2CAP lcid for this control channel */
    UINT8           state;              /* The CCB state machine state */
    BOOLEAN         cong;               /* Whether control channel is congested */
    tMCA_CCB_STAT   status;             /* see tMCA_CCB_STAT */
} tMCA_CCB;
typedef void (*tMCA_CCB_ACTION)(tMCA_CCB *p_ccb, tMCA_CCB_EVT *p_data);

enum
{
    MCA_DCB_STAT_NORM,      /* normal operation (based on dcb state) */
    MCA_DCB_STAT_DEL,       /* MCA_Delete is called. waiting for the DL to detach */
    MCA_DCB_STAT_DISC       /* MCA_CloseReq is called. waiting for the DL to detach */
};
typedef UINT8 tMCA_DCB_STAT;

/* data channel control block */
/* the dcbs association with the ccbs
 * dcb[0]             ...dcb[MCA_NUM_MDLS*1-1] -> ccb[0]
 * dcb[MCA_NUM_MDLS*1]...dcb[MCA_NUM_MDLS*2-1] -> ccb[1]
 * dcb[MCA_NUM_MDLS*2]...dcb[MCA_NUM_MDLS*3-1] -> ccb[2]
 *
 * the dcbs association with the rcbs
 * dcb[0]                             ...dcb[MCA_NUM_MDLS*1*MCA_NUM_LINKS*1-1] -> rcb[0]
 * dcb[MCA_NUM_MDLS*1*MCA_NUM_LINKS*1]...dcb[MCA_NUM_MDLS*2*MCA_NUM_LINKS*2-1] -> rcb[1]
 * dcb[MCA_NUM_MDLS*2*MCA_NUM_LINKS*2]...dcb[MCA_NUM_MDLS*3*MCA_NUM_LINKS*3-1] -> rcb[2]
 */
typedef struct {
    tMCA_CCB            *p_ccb;         /* the associated control control block */
    BT_HDR              *p_data;        /* data packet held due to L2CAP channel congestion */
    tMCA_CS             *p_cs;          /* the associated MDEP info. p_cs->type is the mdep id(internal use) */
    const tMCA_CHNL_CFG *p_chnl_cfg;    /* cfg params for L2CAP channel */
    UINT16              mdl_id;         /* the MDL ID for this data channel */
    UINT16              lcid;           /* L2CAP lcid */
    UINT8               state;          /* The DCB state machine state */
    BOOLEAN             cong;           /* Whether data channel is congested */
    tMCA_DCB_STAT       status;         /* see tMCA_DCB_STAT */
} tMCA_DCB;

typedef void (*tMCA_DCB_ACTION)(tMCA_DCB *p_ccb, tMCA_DCB_EVT *p_data);

/* Control block for MCA */
typedef struct {
    tMCA_RCB        rcb[MCA_NUM_REGS];  /* registration control block */
    tMCA_CCB        ccb[MCA_NUM_CCBS];  /* control channel control blocks */
    tMCA_DCB        dcb[MCA_NUM_DCBS];  /* data channel control blocks */
    tMCA_TC         tc;                 /* transport control block */
    UINT8           trace_level;        /* trace level */
} tMCA_CB;

/* csm functions */
extern void mca_ccb_event(tMCA_CCB *p_ccb, UINT8 event, tMCA_CCB_EVT *p_data);
extern tMCA_CCB *mca_ccb_by_bd(tMCA_HANDLE handle, BD_ADDR bd_addr);
extern tMCA_CCB *mca_ccb_alloc(tMCA_HANDLE handle, BD_ADDR bd_addr);
extern void mca_ccb_rsp_tout(tMCA_CCB *p_ccb, tMCA_CCB_EVT *p_data);
extern void mca_ccb_dealloc(tMCA_CCB *p_ccb, tMCA_CCB_EVT *p_data);
extern tMCA_CL mca_ccb_to_hdl(tMCA_CCB *p_ccb);
extern tMCA_CCB *mca_ccb_by_hdl(tMCA_CL mcl);
extern BOOLEAN mca_ccb_uses_mdl_id(tMCA_CCB *p_ccb, UINT16 mdl_id);

/* cact functions */
extern void mca_ccb_report_event(tMCA_CCB *p_ccb, UINT8 event, tMCA_CTRL *p_data);
extern void mca_ccb_free_msg(tMCA_CCB *p_ccb, tMCA_CCB_EVT *p_data);
extern void mca_ccb_snd_req(tMCA_CCB *p_ccb, tMCA_CCB_EVT *p_data);
extern void mca_ccb_snd_rsp(tMCA_CCB *p_ccb, tMCA_CCB_EVT *p_data);
extern void mca_ccb_do_disconn (tMCA_CCB *p_ccb, tMCA_CCB_EVT *p_data);
extern void mca_ccb_cong(tMCA_CCB *p_ccb, tMCA_CCB_EVT *p_data);
extern void mca_ccb_hdl_req(tMCA_CCB *p_ccb, tMCA_CCB_EVT *p_data);
extern void mca_ccb_hdl_rsp(tMCA_CCB *p_ccb, tMCA_CCB_EVT *p_data);
extern void mca_ccb_ll_open (tMCA_CCB *p_ccb, tMCA_CCB_EVT *p_data);
extern void mca_ccb_dl_open (tMCA_CCB *p_ccb, tMCA_CCB_EVT *p_data);

/* dsm functions */
extern void mca_dcb_event(tMCA_DCB *p_dcb, UINT8 event, tMCA_DCB_EVT *p_data);
extern tMCA_DCB *mca_dcb_alloc(tMCA_CCB*p_ccb, tMCA_DEP dep);
extern UINT8 mca_dep_free_mdl(tMCA_CCB*p_ccb, tMCA_DEP dep);
extern void mca_dcb_dealloc(tMCA_DCB *p_dcb, tMCA_DCB_EVT *p_data);
extern tMCA_DL mca_dcb_to_hdl(tMCA_DCB *p_dcb);
extern tMCA_DCB *mca_dcb_by_hdl(tMCA_DL hdl);
extern void mca_dcb_close_by_mdl_id(tMCA_CCB*p_ccb, UINT16 mdl_id);

/* dact functions */
extern void mca_dcb_tc_open (tMCA_DCB *p_dcb, tMCA_DCB_EVT *p_data);
extern void mca_dcb_cong (tMCA_DCB *p_dcb, tMCA_DCB_EVT *p_data);
extern void mca_dcb_free_data (tMCA_DCB *p_dcb, tMCA_DCB_EVT *p_data);
extern void mca_dcb_do_disconn (tMCA_DCB *p_dcb, tMCA_DCB_EVT *p_data);
extern void mca_dcb_snd_data (tMCA_DCB *p_dcb, tMCA_DCB_EVT *p_data);
extern void mca_dcb_hdl_data (tMCA_DCB *p_dcb, tMCA_DCB_EVT *p_data);


/* main/utils functions */
extern tMCA_HANDLE mca_handle_by_cpsm(UINT16 psm);
extern tMCA_HANDLE mca_handle_by_dpsm(UINT16 psm);
extern tMCA_TC_TBL * mca_tc_tbl_calloc(tMCA_CCB *p_ccb);
extern tMCA_TC_TBL * mca_tc_tbl_dalloc(tMCA_DCB *p_dcb);
extern tMCA_TC_TBL * mca_tc_tbl_by_lcid(UINT16 lcid);
extern void mca_free_tc_tbl_by_lcid(UINT16 lcid);
extern void mca_set_cfg_by_tbl(tL2CAP_CFG_INFO *p_cfg, tMCA_TC_TBL *p_tbl);
extern void mca_tc_close_ind(tMCA_TC_TBL *p_tbl, UINT16 reason);
extern void mca_tc_open_ind(tMCA_TC_TBL *p_tbl);
extern void mca_tc_cong_ind(tMCA_TC_TBL *p_tbl, BOOLEAN is_congested);
extern void mca_tc_data_ind(tMCA_TC_TBL *p_tbl, BT_HDR *p_buf);
extern tMCA_RCB * mca_rcb_alloc(tMCA_REG *p_reg);
extern void mca_rcb_dealloc(tMCA_HANDLE handle);
extern tMCA_HANDLE mca_rcb_to_handle(tMCA_RCB *p_rcb);
extern tMCA_RCB *mca_rcb_by_handle(tMCA_HANDLE handle);
extern BOOLEAN mca_is_valid_dep_id(tMCA_RCB *p_rcb, tMCA_DEP dep);
extern void mca_free_buf(void **p_buf);
extern void mca_process_timeout(TIMER_LIST_ENT *p_tle);
extern void mca_stop_timer(tMCA_CCB *p_ccb);

/* l2c functions */
extern void mca_l2c_cconn_ind_cback(BD_ADDR bd_addr, UINT16 lcid, UINT16 psm, UINT8 id);
extern void mca_l2c_dconn_ind_cback(BD_ADDR bd_addr, UINT16 lcid, UINT16 psm, UINT8 id);
extern UINT16 mca_l2c_open_req(BD_ADDR bd_addr, UINT16 PSM, const tMCA_CHNL_CFG *p_chnl_cfg);

/*****************************************************************************
** global data
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
** Main Control Block
*******************************************************************************/
#if MCA_DYNAMIC_MEMORY == FALSE
MCA_API extern tMCA_CB  mca_cb;
#else
MCA_API extern tMCA_CB *mca_cb_ptr;
#define mca_cb (*mca_cb_ptr)
#endif

/* L2CAP callback registration structure */
extern const tL2CAP_APPL_INFO mca_l2c_int_appl;
extern const tL2CAP_FCR_OPTS mca_l2c_fcr_opts_def;
extern const UINT8 mca_std_msg_len[];

#ifdef __cplusplus
}
#endif

#endif /* MCA_INT_H */
