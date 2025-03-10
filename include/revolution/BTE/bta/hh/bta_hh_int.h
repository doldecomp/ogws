/******************************************************************************
 *
 *  Copyright (C) 2005-2012 Broadcom Corporation
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
 *  This file contains BTA HID Host internal definitions
 *
 ******************************************************************************/

#ifndef BTA_HH_INT_H
#define BTA_HH_INT_H

#include "bta_sys.h"
#include "bd.h"
#include "utl.h"
#include "bta_hh_api.h"

/* can be moved to bta_api.h */
#define BTA_HH_MAX_RPT_CHARS    8


/* state machine events, these events are handled by the state machine */
enum
{
    BTA_HH_API_OPEN_EVT     = BTA_SYS_EVT_START(BTA_ID_HH),
    BTA_HH_API_CLOSE_EVT,
    BTA_HH_INT_OPEN_EVT,
    BTA_HH_INT_CLOSE_EVT,
    BTA_HH_INT_DATA_EVT,
    BTA_HH_INT_CTRL_DATA,
    BTA_HH_INT_HANDSK_EVT,
    BTA_HH_SDP_CMPL_EVT,
    BTA_HH_API_WRITE_DEV_EVT,
    BTA_HH_API_GET_DSCP_EVT,
    BTA_HH_API_MAINT_DEV_EVT,
    BTA_HH_OPEN_CMPL_EVT,

    /* not handled by execute state machine */
    BTA_HH_API_ENABLE_EVT,
    BTA_HH_API_DISABLE_EVT,
    BTA_HH_DISC_CMPL_EVT
};
typedef UINT16 tBTA_HH_INT_EVT;         /* HID host internal events */

#define BTA_HH_INVALID_EVT      (BTA_HH_DISC_CMPL_EVT + 1)

/* event used to map between BTE event and BTA event */
#define BTA_HH_FST_TRANS_CB_EVT         BTA_HH_GET_RPT_EVT
#define BTA_HH_FST_BTE_TRANS_EVT        HID_TRANS_GET_REPORT

/* sub event code used for device maintainence API call */
#define BTA_HH_ADD_DEV          0
#define BTA_HH_REMOVE_DEV       1

/* state machine states */
enum
{
    BTA_HH_NULL_ST,
    BTA_HH_IDLE_ST,
    BTA_HH_W4_CONN_ST,
    BTA_HH_CONN_ST
};
typedef UINT8 tBTA_HH_STATE;

/* data structure used to send a command/data to HID device */
typedef struct
{
    BT_HDR           hdr;
    UINT8            t_type;
    UINT8            param;
    UINT8            rpt_id;
    UINT16           data;
    BT_HDR           *p_data;
}tBTA_HH_CMD_DATA;

/* data type for BTA_HH_API_ENABLE_EVT */
typedef struct
{
    BT_HDR              hdr;
    UINT8               sec_mask;
    UINT8               service_name[BTA_SERVICE_NAME_LEN+1];
    tBTA_HH_CBACK   *p_cback;
} tBTA_HH_API_ENABLE;

typedef struct
{
    BT_HDR          hdr;
    BD_ADDR         bd_addr;
    UINT8           sec_mask;
    tBTA_HH_PROTO_MODE  mode;
}tBTA_HH_API_CONN;

/* internal event data from BTE HID callback */
typedef struct
{
    BT_HDR          hdr;
    UINT32          data;
    BT_HDR          *p_data;
}tBTA_HH_CBACK_DATA;

typedef struct
{
    BT_HDR              hdr;
    BD_ADDR             bda;
    UINT16              attr_mask;
    UINT16              sub_event;
    UINT8               sub_class;
    UINT8               app_id;
    tBTA_HH_DEV_DSCP_INFO      dscp_info;
}tBTA_HH_MAINT_DEV;

/* union of all event data types */
typedef union
{
    BT_HDR                   hdr;
    tBTA_HH_API_ENABLE       api_enable;
    tBTA_HH_API_CONN         api_conn;
    tBTA_HH_CMD_DATA         api_sndcmd;
    tBTA_HH_CBACK_DATA       hid_cback;
    tBTA_HH_STATUS           status;
    tBTA_HH_MAINT_DEV        api_maintdev;
} tBTA_HH_DATA;

/* device control block */
typedef struct
{
    tBTA_HH_DEV_DSCP_INFO  dscp_info;      /* report descriptor and DI information */
    BD_ADDR             addr;           /* BD-Addr of the HID device */
    UINT16              attr_mask;      /* attribute mask */
    UINT16              w4_evt;         /* W4_handshake event name */
    UINT8               index;          /* index number referenced to handle index */
    UINT8               sub_class;      /* Cod sub class */
    UINT8               sec_mask;       /* security mask */
    UINT8               app_id;         /* application ID for this connection */
    UINT8               hid_handle;     /* device handle */
    BOOLEAN             vp;             /* virtually unplug flag */
    BOOLEAN             in_use;         /* control block currently in use */
    BOOLEAN             incoming_conn;  /* is incoming connection? */
    BOOLEAN             opened;         /* TRUE if device successfully opened HID connection */
    tBTA_HH_PROTO_MODE  mode;           /* protocol mode */
    tBTA_HH_STATE       state;          /* CB state */
} tBTA_HH_DEV_CB;

/* key board parsing control block */
typedef struct
{
    BOOLEAN             mod_key[4]; /* ctrl, shift(upper), Alt, GUI */
    BOOLEAN             num_lock;
    BOOLEAN             caps_lock;
    UINT8               last_report[BTA_HH_MAX_RPT_CHARS];
} tBTA_HH_KB_CB;

/******************************************************************************
** Main Control Block
*******************************************************************************/
typedef struct
{
    tBTA_HH_KB_CB           kb_cb;                  /* key board control block,
                                                       suppose BTA will connect
                                                       to only one keyboard at
                                                        the same time */
    tBTA_HH_DEV_CB          kdev[BTA_HH_MAX_KNOWN]; /* device control block */
    tBTA_HH_DEV_CB*         p_cur;              /* current device control
                                                       block idx, used in sdp */
    UINT8                   cb_index[BTA_HH_MAX_KNOWN]; /* maintain a CB index
                                                        map to dev handle */
    tBTA_HH_CBACK       *p_cback;               /* Application callbacks */
    tSDP_DISCOVERY_DB*      p_disc_db;
    UINT8                   trace_level;            /* tracing level */
    UINT8                   cnt_num;                /* connected device number */
    BOOLEAN                 w4_disable;             /* w4 disable flag */
}
tBTA_HH_CB;

#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_HH_CB  bta_hh_cb;
#else
extern tBTA_HH_CB *bta_hh_cb_ptr;
#define bta_hh_cb (*bta_hh_cb_ptr)
#endif

/* from bta_hh_cfg.c */
extern tBTA_HH_CFG *p_bta_hh_cfg;

/*****************************************************************************
**  Function prototypes
*****************************************************************************/
extern BOOLEAN bta_hh_hdl_event(BT_HDR *p_msg);
extern void bta_hh_sm_execute(tBTA_HH_DEV_CB *p_cb, UINT16 event,
                              tBTA_HH_DATA *p_data);

/* action functions */
extern void bta_hh_api_disc_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_open_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_close_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_data_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA * p_data);
extern void bta_hh_ctrl_dat_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA * p_data);
extern void bta_hh_start_sdp(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_sdp_cmpl(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_write_dev_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_get_dscp_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_handsk_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_maint_dev_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);
extern void bta_hh_open_cmpl_act(tBTA_HH_DEV_CB *p_cb, tBTA_HH_DATA *p_data);

/* utility functions */
extern UINT8  bta_hh_find_cb(BD_ADDR bda);
extern void bta_hh_parse_keybd_rpt(tBTA_HH_BOOT_RPT *p_kb_data,
             UINT8 *p_report, UINT16 report_len);
extern void bta_hh_parse_mice_rpt(tBTA_HH_BOOT_RPT *p_kb_data,
                                  UINT8 *p_report, UINT16 report_len);
extern BOOLEAN bta_hh_tod_spt(tBTA_HH_DEV_CB *p_cb,UINT8 sub_class);
extern void bta_hh_clean_up_kdev(tBTA_HH_DEV_CB *p_cb);

extern void bta_hh_add_device_to_list(tBTA_HH_DEV_CB *p_cb, UINT8 handle,
                                      UINT16 attr_mask,
                                      tHID_DEV_DSCP_INFO *p_dscp_info,
                                      UINT8 sub_class, UINT16 max_latency, UINT16 min_tout, UINT8 app_id);
extern void bta_hh_update_di_info(tBTA_HH_DEV_CB *p_cb, UINT16 vendor_id, UINT16 product_id,
                           UINT16 version);

/* action functions used outside state machine */
extern void bta_hh_api_enable(tBTA_HH_DATA *p_data);
extern void bta_hh_api_disable(void);
extern void bta_hh_disc_cmpl(void);


#if BTA_HH_DEBUG
extern void bta_hh_trace_dev_db(void);
#endif

#endif

