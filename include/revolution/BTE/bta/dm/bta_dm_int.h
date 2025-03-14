/******************************************************************************
 *
 *  NOTICE OF CHANGES
 *  2024/03/26:
 *      - Add tBTA_DM_COMPRESS_CFG structure for RVL target
 *      - Added prototypes missing from bta_dm_act
 * 
 *  Compile with REVOLUTION defined to include these changes.
 * 
 ******************************************************************************/



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
 *  This is the private interface file for the BTA device manager.
 *
 ******************************************************************************/
#ifndef BTA_DM_INT_H
#define BTA_DM_INT_H

#include "bt_target.h"

#if (BLE_INCLUDED == TRUE && (defined BTA_GATT_INCLUDED) && (BTA_GATT_INCLUDED == TRUE))
    #include "bta_gatt_api.h"
#endif



/*****************************************************************************
**  Constants and data types
*****************************************************************************/


#define BTA_COPY_DEVICE_CLASS(coddst, codsrc)   {((UINT8 *)(coddst))[0] = ((UINT8 *)(codsrc))[0]; \
                                                 ((UINT8 *)(coddst))[1] = ((UINT8 *)(codsrc))[1];  \
                                                 ((UINT8 *)(coddst))[2] = ((UINT8 *)(codsrc))[2];}


#define BTA_DM_MSG_LEN 50

#define BTA_SERVICE_ID_TO_SERVICE_MASK(id)       (1 << (id))

/* DM events */
enum
{
    /* device manager local device API events */
    BTA_DM_API_ENABLE_EVT = BTA_SYS_EVT_START(BTA_ID_DM),
    BTA_DM_API_DISABLE_EVT,
    BTA_DM_API_SET_NAME_EVT,
    BTA_DM_API_SET_VISIBILITY_EVT,
    BTA_DM_API_SET_AFH_CHANNELS_EVT,
    BTA_API_DM_SIG_STRENGTH_EVT,
    BTA_DM_API_VENDOR_SPECIFIC_COMMAND_EVT,
    BTA_DM_API_TX_INQPWR_EVT,
    BTA_DM_ACL_CHANGE_EVT,
    BTA_DM_API_ADD_DEVICE_EVT,

    /* security API events */
    BTA_DM_API_BOND_EVT,
    BTA_DM_API_BOND_CANCEL_EVT,
    BTA_DM_API_PIN_REPLY_EVT,
    BTA_DM_API_LINK_POLICY_EVT,
    BTA_DM_API_AUTH_REPLY_EVT,

    /* power manger events */
    BTA_DM_PM_BTM_STATUS_EVT,
    BTA_DM_PM_TIMER_EVT,

    /* simple pairing events */
    BTA_DM_API_CONFIRM_EVT,

    BTA_DM_API_SET_ENCRYPTION_EVT,

#if (BTM_LOCAL_IO_CAPS != BTM_IO_CAP_NONE)
    BTA_DM_API_PASKY_CANCEL_EVT,
#endif
#if (BTM_OOB_INCLUDED == TRUE)
    BTA_DM_API_LOC_OOB_EVT,
    BTA_DM_CI_IO_REQ_EVT,
    BTA_DM_CI_RMT_OOB_EVT,
#endif /* BTM_OOB_INCLUDED */

    BTA_DM_API_REMOVE_DEVICE_EVT,

#if BLE_INCLUDED == TRUE
    BTA_DM_API_ADD_BLEKEY_EVT,
    BTA_DM_API_ADD_BLEDEVICE_EVT,
    BTA_DM_API_BLE_PASSKEY_REPLY_EVT,
    BTA_DM_API_BLE_SEC_GRANT_EVT,
    BTA_DM_API_BLE_SET_BG_CONN_TYPE,
    BTA_DM_API_BLE_CONN_PARAM_EVT,
    BTA_DM_API_BLE_SCAN_PARAM_EVT,
#endif

#if ( BTM_EIR_SERVER_INCLUDED == TRUE )&&( BTA_EIR_CANNED_UUID_LIST != TRUE )&&(BTA_EIR_SERVER_NUM_CUSTOM_UUID > 0)
    BTA_DM_API_UPDATE_EIR_UUID_EVT,
#endif
#if (BTM_EIR_SERVER_INCLUDED == TRUE)
    BTA_DM_API_SET_EIR_CONFIG_EVT,
#endif

    BTA_DM_API_ENABLE_TEST_MODE_EVT,
    BTA_DM_API_DISABLE_TEST_MODE_EVT,
    BTA_DM_API_EXECUTE_CBACK_EVT,
    BTA_DM_API_SET_AFH_CHANNEL_ASSESMENT_EVT,
    BTA_DM_MAX_EVT
};


/* DM search events */
enum
{
    /* DM search API events */
    BTA_DM_API_SEARCH_EVT = BTA_SYS_EVT_START(BTA_ID_DM_SEARCH),
    BTA_DM_API_SEARCH_CANCEL_EVT,
    BTA_DM_API_DISCOVER_EVT,
    BTA_DM_INQUIRY_CMPL_EVT,
    BTA_DM_REMT_NAME_EVT,
    BTA_DM_SDP_RESULT_EVT,
    BTA_DM_SEARCH_CMPL_EVT,
    BTA_DM_DISCOVERY_RESULT_EVT,
    BTA_DM_API_DI_DISCOVER_EVT

};

/* data type for BTA_DM_API_ENABLE_EVT */
typedef struct
{
    BT_HDR              hdr;
    tBTA_DM_SEC_CBACK *p_sec_cback;
} tBTA_DM_API_ENABLE;

/* data type for BTA_DM_API_SET_NAME_EVT */
typedef struct
{
    BT_HDR              hdr;
    char    name[BD_NAME_LEN];
} tBTA_DM_API_SET_NAME;

/* data type for BTA_DM_API_SET_VISIBILITY_EVT */
typedef struct
{
    BT_HDR              hdr;
    tBTA_DM_DISC    disc_mode;
    tBTA_DM_CONN    conn_mode;
    UINT8           pair_mode;
    UINT8           conn_paired_only;
} tBTA_DM_API_SET_VISIBILITY;

/* data type for BTA_DM_API_SET_AFH_CHANNELS_EVT */
typedef struct
{
    BT_HDR              hdr;
    UINT8           first;
    UINT8           last;
} tBTA_DM_API_SET_AFH_CHANNELS_EVT;

/* data type for BTA_DM_API_VENDOR_SPECIFIC_COMMAND_EVT */
typedef struct
{
    BT_HDR              hdr;
    UINT16              opcode;
    UINT8               param_len;
    UINT8               *p_param_buf;
    tBTA_VENDOR_CMPL_CBACK *p_cback;

} tBTA_DM_API_VENDOR_SPECIFIC_COMMAND;

enum
{
    BTA_DM_RS_NONE,     /* straight API call */
    BTA_DM_RS_OK,       /* the role switch result - successful */
    BTA_DM_RS_FAIL      /* the role switch result - failed */
};
typedef UINT8 tBTA_DM_RS_RES;

/* data type for BTA_DM_API_SEARCH_EVT */
typedef struct
{
    BT_HDR      hdr;
    tBTA_DM_INQ inq_params;
    tBTA_SERVICE_MASK services;
    tBTA_DM_SEARCH_CBACK * p_cback;
    tBTA_DM_RS_RES  rs_res;
#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
    UINT8           num_uuid;
    tBT_UUID        *p_uuid;
#endif
} tBTA_DM_API_SEARCH;

/* data type for BTA_DM_API_DISCOVER_EVT */
typedef struct
{
    BT_HDR      hdr;
    BD_ADDR bd_addr;
    tBTA_SERVICE_MASK services;
    tBTA_DM_SEARCH_CBACK * p_cback;
    BOOLEAN         sdp_search;
#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
    UINT8           num_uuid;
    tBT_UUID        *p_uuid;
#endif
    tSDP_UUID    uuid;
} tBTA_DM_API_DISCOVER;

/* data type for BTA_DM_API_DI_DISC_EVT */
typedef struct
{
    BT_HDR              hdr;
    BD_ADDR             bd_addr;
    tBTA_DISCOVERY_DB   *p_sdp_db;
    UINT32              len;
    tBTA_DM_SEARCH_CBACK * p_cback;
}tBTA_DM_API_DI_DISC;

/* data type for BTA_DM_API_BOND_EVT */
typedef struct
{
    BT_HDR      hdr;
    BD_ADDR bd_addr;
} tBTA_DM_API_BOND;

/* data type for BTA_DM_API_BOND_CANCEL_EVT */
typedef struct
{
    BT_HDR          hdr;
    BD_ADDR         bd_addr;
} tBTA_DM_API_BOND_CANCEL;

/* data type for BTA_DM_API_PIN_REPLY_EVT */
typedef struct
{
    BT_HDR      hdr;
    BD_ADDR bd_addr;
    BOOLEAN accept;
    UINT8 pin_len;
    UINT8 p_pin[PIN_CODE_LEN];
} tBTA_DM_API_PIN_REPLY;

/* data type for BTA_DM_API_LINK_POLICY_EVT */
typedef struct
{
    BT_HDR      hdr;
    BD_ADDR     bd_addr;
    UINT16      policy_mask;
    BOOLEAN     set;
} tBTA_DM_API_LINK_POLICY;

/* data type for BTA_DM_API_AUTH_REPLY_EVT */
typedef struct
{
    BT_HDR      hdr;
    BD_ADDR bd_addr;
    tBTA_SERVICE_ID service;
    tBTA_AUTH_RESP response;
} tBTA_DM_API_AUTH_REPLY;

/* data type for BTA_DM_API_LOC_OOB_EVT */
typedef struct
{
    BT_HDR      hdr;
} tBTA_DM_API_LOC_OOB;

/* data type for BTA_DM_API_CONFIRM_EVT */
typedef struct
{
    BT_HDR      hdr;
    BD_ADDR     bd_addr;
    BOOLEAN     accept;
} tBTA_DM_API_CONFIRM;

/* data type for BTA_DM_API_PASKY_CANCEL_EVT*/
typedef struct
{
    BT_HDR      hdr;
    BD_ADDR     bd_addr;
} tBTA_DM_API_PASKY_CANCEL;

/* data type for BTA_DM_CI_IO_REQ_EVT */
typedef struct
{
    BT_HDR          hdr;
    BD_ADDR         bd_addr;
    tBTA_IO_CAP     io_cap;
    tBTA_OOB_DATA   oob_data;
    tBTA_AUTH_REQ   auth_req;
} tBTA_DM_CI_IO_REQ;

/* data type for BTA_DM_CI_RMT_OOB_EVT */
typedef struct
{
    BT_HDR      hdr;
    BD_ADDR     bd_addr;
    BT_OCTET16  c;
    BT_OCTET16  r;
    BOOLEAN     accept;
} tBTA_DM_CI_RMT_OOB;

/* data type for BTA_DM_REMT_NAME_EVT */
typedef struct
{
    BT_HDR      hdr;
    tBTA_DM_SEARCH  result;
} tBTA_DM_REM_NAME;

/* data type for tBTA_DM_DISC_RESULT */
typedef struct
{
    BT_HDR      hdr;
    tBTA_DM_SEARCH  result;
} tBTA_DM_DISC_RESULT;


/* data type for BTA_DM_INQUIRY_CMPL_EVT */
typedef struct
{
    BT_HDR      hdr;
    UINT8       num;
} tBTA_DM_INQUIRY_CMPL;

/* data type for BTA_DM_SDP_RESULT_EVT */
typedef struct
{
    BT_HDR      hdr;
    UINT16 sdp_result;
} tBTA_DM_SDP_RESULT;

/* data type for BTA_API_DM_SIG_STRENGTH_EVT */
typedef struct
{
    BT_HDR      hdr;
    tBTA_SIG_STRENGTH_MASK mask;
    UINT16 period;
    BOOLEAN start;
} tBTA_API_DM_SIG_STRENGTH;

/* data type for tBTA_API_DM_TX_INQPWR */
typedef struct
{
    BT_HDR      hdr;
    INT8        tx_power;
}tBTA_API_DM_TX_INQPWR;

/* data type for BTA_DM_ACL_CHANGE_EVT */
typedef struct
{
    BT_HDR          hdr;
    tBTM_BL_EVENT   event;
    UINT8           busy_level;
    BOOLEAN         is_new;
    UINT8           new_role;
    BD_ADDR         bd_addr;
    UINT8           hci_status;
} tBTA_DM_ACL_CHANGE;

/* data type for BTA_DM_PM_BTM_STATUS_EVT */
typedef struct
{

    BT_HDR          hdr;
    BD_ADDR         bd_addr;
    tBTM_PM_STATUS  status;
    UINT16          value;
    UINT8           hci_status;

} tBTA_DM_PM_BTM_STATUS;

/* data type for BTA_DM_PM_TIMER_EVT */
typedef struct
{
    BT_HDR          hdr;
    BD_ADDR         bd_addr;

} tBTA_DM_PM_TIMER;


/* data type for BTA_DM_API_ADD_DEVICE_EVT */
typedef struct
{
    BT_HDR              hdr;
    BD_ADDR             bd_addr;
    DEV_CLASS           dc;
    LINK_KEY            link_key;
    tBTA_SERVICE_MASK   tm;
    BOOLEAN             is_trusted;
    UINT8               key_type;
    tBTA_IO_CAP         io_cap;
    BOOLEAN             link_key_known;
    BOOLEAN             dc_known;
    BD_NAME             bd_name;
    BD_FEATURES         features;
} tBTA_DM_API_ADD_DEVICE;

/* data type for BTA_DM_API_REMOVE_ACL_EVT */
typedef struct
{
    BT_HDR              hdr;
    BD_ADDR             bd_addr;
} tBTA_DM_API_REMOVE_DEVICE;

/* data type for BTA_DM_API_EXECUTE_CBACK_EVT */
typedef struct
{
    BT_HDR               hdr;
    void *               p_param;
    tBTA_DM_EXEC_CBACK  *p_exec_cback;
} tBTA_DM_API_EXECUTE_CBACK;

/* data type for tBTA_DM_API_SET_ENCRYPTION */
typedef struct
{
    BT_HDR                    hdr;
    tBTA_DM_ENCRYPT_CBACK     *p_callback;
    tBTA_DM_BLE_SEC_ACT       sec_act;
    BD_ADDR                   bd_addr;
} tBTA_DM_API_SET_ENCRYPTION;

#if BLE_INCLUDED == TRUE
typedef struct
{
    BT_HDR                  hdr;
    BD_ADDR                 bd_addr;
    tBTA_LE_KEY_VALUE       blekey;
    tBTA_LE_KEY_TYPE        key_type;

}tBTA_DM_API_ADD_BLEKEY;

typedef struct
{
    BT_HDR                  hdr;
    BD_ADDR                 bd_addr;
    tBT_DEVICE_TYPE         dev_type ;
    tBLE_ADDR_TYPE          addr_type;

}tBTA_DM_API_ADD_BLE_DEVICE;

typedef struct
{
    BT_HDR                  hdr;
    BD_ADDR                 bd_addr;
    BOOLEAN                 accept;
    UINT32                  passkey;
}tBTA_DM_API_PASSKEY_REPLY;

typedef struct
{
    BT_HDR                  hdr;
    BD_ADDR                 bd_addr;
    tBTA_DM_BLE_SEC_GRANT   res;
}tBTA_DM_API_BLE_SEC_GRANT;


typedef struct
{
    BT_HDR                  hdr;
    tBTA_DM_BLE_CONN_TYPE   bg_conn_type;
    tBTA_DM_BLE_SEL_CBACK   *p_select_cback;
}tBTA_DM_API_BLE_SET_BG_CONN_TYPE;

/* set prefered BLE connection parameters for a device */
typedef struct
{
    BT_HDR                  hdr;
    BD_ADDR                 peer_bda;
    UINT16                  conn_int_min;
    UINT16                  conn_int_max;
    UINT16                  supervision_tout;
    UINT16                  slave_latency;

}tBTA_DM_API_BLE_CONN_PARAMS;

/* set scan parameter for BLE connections */
typedef struct
{
    BT_HDR                  hdr;
    UINT16                  scan_int;
    UINT16                  scan_window;
}tBTA_DM_API_BLE_SCAN_PARAMS;

#endif

typedef struct
{
    BT_HDR                  hdr;
    BOOLEAN                 enable_or_disable;
}tBTA_DM_API_SET_AFH_CHANNEL_ASSESSMENT;

#if ( BTM_EIR_SERVER_INCLUDED == TRUE )&&( BTA_EIR_CANNED_UUID_LIST != TRUE )&&(BTA_EIR_SERVER_NUM_CUSTOM_UUID > 0)
/* data type for BTA_DM_API_UPDATE_EIR_UUID_EVT */
typedef struct
{
    BT_HDR          hdr;
    BOOLEAN         is_add;
    tBT_UUID        uuid;
}tBTA_DM_API_UPDATE_EIR_UUID;
#endif

#if (BTM_EIR_SERVER_INCLUDED == TRUE)
/* data type for BTA_DM_API_SET_EIR_CONFIG_EVT */
typedef struct
{
    BT_HDR              hdr;
    tBTA_DM_EIR_CONF    *p_eir_cfg;
}tBTA_DM_API_SET_EIR_CONFIG;
#endif

/* union of all data types */
typedef union
{
    /* GKI event buffer header */
    BT_HDR              hdr;
    tBTA_DM_API_ENABLE  enable;

    tBTA_DM_API_SET_NAME set_name;

    tBTA_DM_API_SET_VISIBILITY set_visibility;

    tBTA_DM_API_SET_AFH_CHANNELS_EVT set_afhchannels;

    tBTA_DM_API_VENDOR_SPECIFIC_COMMAND vendor_command;

    tBTA_DM_API_ADD_DEVICE  add_dev;

    tBTA_DM_API_REMOVE_DEVICE remove_dev;

    tBTA_DM_API_SEARCH search;

    tBTA_DM_API_DISCOVER discover;

    tBTA_DM_API_BOND bond;

    tBTA_DM_API_BOND_CANCEL bond_cancel;

    tBTA_DM_API_PIN_REPLY pin_reply;
    tBTA_DM_API_LINK_POLICY link_policy;

    tBTA_DM_API_LOC_OOB     loc_oob;
    tBTA_DM_API_CONFIRM     confirm;
    tBTA_DM_API_PASKY_CANCEL passkey_cancel;
    tBTA_DM_CI_IO_REQ       ci_io_req;
    tBTA_DM_CI_RMT_OOB      ci_rmt_oob;

    tBTA_DM_API_AUTH_REPLY auth_reply;

    tBTA_DM_REM_NAME rem_name;

    tBTA_DM_DISC_RESULT disc_result;

    tBTA_DM_INQUIRY_CMPL inq_cmpl;

    tBTA_DM_SDP_RESULT sdp_event;

    tBTA_API_DM_SIG_STRENGTH sig_strength;

    tBTA_API_DM_TX_INQPWR   tx_inq_pwr;

    tBTA_DM_ACL_CHANGE  acl_change;

    tBTA_DM_PM_BTM_STATUS pm_status;

    tBTA_DM_PM_TIMER pm_timer;

    tBTA_DM_API_DI_DISC     di_disc;

    tBTA_DM_API_EXECUTE_CBACK exec_cback;

    tBTA_DM_API_SET_ENCRYPTION     set_encryption;

#if BLE_INCLUDED == TRUE
    tBTA_DM_API_ADD_BLEKEY              add_ble_key;
    tBTA_DM_API_ADD_BLE_DEVICE          add_ble_device;
    tBTA_DM_API_PASSKEY_REPLY           ble_passkey_reply;
    tBTA_DM_API_BLE_SEC_GRANT           ble_sec_grant;
    tBTA_DM_API_BLE_SET_BG_CONN_TYPE    ble_set_bd_conn_type;
    tBTA_DM_API_BLE_CONN_PARAMS         ble_set_conn_params;
    tBTA_DM_API_BLE_SCAN_PARAMS         ble_set_scan_params;
#endif

    tBTA_DM_API_SET_AFH_CHANNEL_ASSESSMENT set_afh_channel_assessment;

#if ( BTM_EIR_SERVER_INCLUDED == TRUE )&&( BTA_EIR_CANNED_UUID_LIST != TRUE )&&(BTA_EIR_SERVER_NUM_CUSTOM_UUID > 0)
    tBTA_DM_API_UPDATE_EIR_UUID     update_eir_uuid;
#endif
#if (BTM_EIR_SERVER_INCLUDED == TRUE)
    tBTA_DM_API_SET_EIR_CONFIG          set_eir_cfg;
#endif

} tBTA_DM_MSG;


#define BTA_DM_NUM_PEER_DEVICE 7

#define BTA_DM_NOT_CONNECTED  0
#define BTA_DM_CONNECTED      1
#define BTA_DM_UNPAIRING      2
typedef UINT8 tBTA_DM_CONN_STATE;


#define BTA_DM_DI_NONE          0x00       /* nothing special */
#define BTA_DM_DI_USE_SSR       0x10       /* set this bit if ssr is supported for this link */
#define BTA_DM_DI_AV_ACTIVE     0x20       /* set this bit if AV is active for this link */
#define BTA_DM_DI_SET_SNIFF     0x01       /* set this bit if call BTM_SetPowerMode(sniff) */
#define BTA_DM_DI_INT_SNIFF     0x02       /* set this bit if call BTM_SetPowerMode(sniff) & enter sniff mode */
#define BTA_DM_DI_ACP_SNIFF     0x04       /* set this bit if peer init sniff */
typedef UINT8 tBTA_DM_DEV_INFO;

typedef struct
{
    BD_ADDR                     peer_bdaddr;
    UINT16                      link_policy;
    tBTA_DM_CONN_STATE          conn_state;
    tBTA_PREF_ROLES             pref_role;
    BOOLEAN                     in_use;
    tBTA_DM_DEV_INFO            info;
#if (BTM_SSR_INCLUDED == TRUE)
    tBTM_PM_STATUS              prev_low;   /* previous low power mode used */
#endif
    tBTA_DM_PM_ACTTION          pm_mode_attempted;
    tBTA_DM_PM_ACTTION          pm_mode_failed;

} tBTA_DM_PEER_DEVICE;



/* structure to store list of
  active connections */
typedef struct
{
    tBTA_DM_PEER_DEVICE    peer_device[BTA_DM_NUM_PEER_DEVICE];
    UINT8                  count;

} tBTA_DM_ACTIVE_LINK;


typedef struct
{
    BD_ADDR                 peer_bdaddr;
    tBTA_SYS_ID             id;
    UINT8                   app_id;
    tBTA_SYS_CONN_STATUS    state;


} tBTA_DM_SRVCS;

#define BTA_DM_NUM_CONN_SRVS   5

typedef struct
{

    UINT8 count;
    tBTA_DM_SRVCS  conn_srvc[BTA_DM_NUM_CONN_SRVS];

}  tBTA_DM_CONNECTED_SRVCS;

typedef struct
{
    TIMER_LIST_ENT          timer;
    BD_ADDR                 peer_bdaddr;
    BOOLEAN                 in_use;

} tBTA_PM_TIMER;

extern tBTA_DM_CONNECTED_SRVCS bta_dm_conn_srvcs;

#define BTA_DM_NUM_PM_TIMER 3

/* DM control block */
typedef struct
{
    BOOLEAN                     is_bta_dm_active;
    tBTA_DM_ACTIVE_LINK         device_list;
    tBTA_DM_SEC_CBACK           *p_sec_cback;
    TIMER_LIST_ENT              signal_strength_timer;
    tBTA_SIG_STRENGTH_MASK      signal_strength_mask;
    UINT16                      state;
    UINT16                      signal_strength_period;
    BOOLEAN                     disabling;
    TIMER_LIST_ENT              disable_timer;
    UINT32                      wbt_sdp_handle;          /* WIDCOMM Extensions SDP record handle */
    UINT8                       wbt_scn;                 /* WIDCOMM Extensions SCN */
    UINT8                       num_master_only;
    UINT8                       pm_id;
    tBTA_PM_TIMER               pm_timer[BTA_DM_NUM_PM_TIMER];
    UINT32                      role_policy_mask;   /* the bits set indicates the modules that wants to remove role switch from the default link policy */
    UINT16                      cur_policy;         /* current default link policy */
    UINT16                      rs_event;           /* the event waiting for role switch */
    UINT8                       cur_av_count;       /* current AV connecions */
    BOOLEAN                     disable_pair_mode;          /* disable pair mode or not */
    BOOLEAN                     conn_paired_only;   /* allow connectable to paired device only or not */
    tBTA_DM_API_SEARCH          search_msg;
    UINT16                      page_scan_interval;
    UINT16                      page_scan_window;
    UINT16                      inquiry_scan_interval;
    UINT16                      inquiry_scan_window;

    /* Storage for pin code request parameters */
    BD_ADDR                     pin_bd_addr;
    DEV_CLASS                   pin_dev_class;
    tBTA_DM_SEC_EVT             pin_evt;
    UINT32          num_val;        /* the numeric value for comparison. If just_works, do not show this number to UI */
    BOOLEAN         just_works;     /* TRUE, if "Just Works" association model */
#if ( BTM_EIR_SERVER_INCLUDED == TRUE )&&( BTA_EIR_CANNED_UUID_LIST != TRUE )
    /* store UUID list for EIR */
    TIMER_LIST_ENT              app_ready_timer;
    UINT32                      eir_uuid[BTM_EIR_SERVICE_ARRAY_SIZE];
#if (BTA_EIR_SERVER_NUM_CUSTOM_UUID > 0)
    tBT_UUID                    custom_uuid[BTA_EIR_SERVER_NUM_CUSTOM_UUID];
#endif

#endif

    tBTA_DM_ENCRYPT_CBACK      *p_encrypt_cback;
    tBTA_DM_BLE_SEC_ACT         sec_act;
    TIMER_LIST_ENT              switch_delay_timer;

} tBTA_DM_CB;

#ifndef BTA_DM_SDP_DB_SIZE
#define BTA_DM_SDP_DB_SIZE 250
#endif

/* DM search control block */
typedef struct
{

    tBTA_DM_SEARCH_CBACK * p_search_cback;
    tBTM_INQ_INFO        * p_btm_inq_info;
    tBTA_SERVICE_MASK      services;
    tBTA_SERVICE_MASK      services_to_search;
    tBTA_SERVICE_MASK      services_found;
    tSDP_DISCOVERY_DB    * p_sdp_db;
    UINT16                 state;
    BD_ADDR                peer_bdaddr;
    BOOLEAN                name_discover_done;
    char                   peer_name[BD_NAME_LEN];
    TIMER_LIST_ENT         search_timer;
    UINT8                  service_index;
    tBTA_DM_MSG          * p_search_queue;   /* search or discover commands during search cancel stored here */
    BOOLEAN                wait_disc;
    BOOLEAN                sdp_results;
    tSDP_UUID              uuid;
    UINT8                  peer_scn;
    BOOLEAN                sdp_search;

#if ((defined BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
#if ((defined BTA_GATT_INCLUDED) && (BTA_GATT_INCLUDED == TRUE))
    tBTA_GATTC_IF          client_if;
    UINT8                  num_uuid;
    tBT_UUID               *p_srvc_uuid;
    UINT8                  uuid_to_search;
    BOOLEAN                gatt_disc_active;
    UINT16                 conn_id;
    UINT8 *                 p_ble_rawdata;
    UINT32                 ble_raw_size;
    UINT32                 ble_raw_used;
#endif
#endif


} tBTA_DM_SEARCH_CB;

/* DI control block */
typedef struct
{
    tSDP_DISCOVERY_DB    * p_di_db;     /* pointer to the DI discovery database */
    UINT8               di_num;         /* total local DI record number */
    UINT32              di_handle[BTA_DI_NUM_MAX];  /* local DI record handle, the first one is primary record */
}tBTA_DM_DI_CB;

/* DM search state */
enum
{

    BTA_DM_SEARCH_IDLE,
    BTA_DM_SEARCH_ACTIVE,
    BTA_DM_SEARCH_CANCELLING,
    BTA_DM_DISCOVER_ACTIVE

};



typedef struct
{
    DEV_CLASS      dev_class;          /* local device class */
    UINT16         policy_settings;    /* link policy setting hold, sniff, park, MS switch */
    UINT16         page_timeout;       /* timeout for page in slots */
    UINT16         link_timeout;       /* link supervision timeout in slots */
    BOOLEAN        avoid_scatter;      /* TRUE to avoid scatternet when av is streaming (be the master) */

} tBTA_DM_CFG;

extern const UINT32 bta_service_id_to_btm_srv_id_lkup_tbl[];

extern const tBTA_DM_CFG bta_dm_cfg;



#define BTA_ALL_APP_ID 0xff

typedef struct
{
    UINT8   id;
    UINT8   app_id;
    UINT8   cfg;

} tBTA_DM_RM ;

extern tBTA_DM_CFG *p_bta_dm_cfg;
extern tBTA_DM_RM *p_bta_dm_rm_cfg;

typedef struct
{

  UINT8  id;
  UINT8  app_id;
  UINT8  spec_idx;  /* index of spec table to use */

} tBTA_DM_PM_CFG;


#ifdef REVOLUTION
typedef struct
{
    UINT8   id;
    UINT8   app_id;
    UINT8   mask;
} tBTA_DM_COMPRESS_CFG;

extern tBTA_DM_COMPRESS_CFG* p_bta_dm_compress_cfg;
#endif

typedef struct
{

  tBTA_DM_PM_ACTTION  power_mode;
  UINT16              timeout;

} tBTA_DM_PM_ACTN;

typedef struct
{

  UINT8  allow_mask;         /* mask of sniff/hold/park modes to allow */
#if (BTM_SSR_INCLUDED == TRUE)
  UINT8  ssr;                /* set SSR on conn open/unpark */
#endif
  tBTA_DM_PM_ACTN actn_tbl [BTA_DM_PM_NUM_EVTS][2];

} tBTA_DM_PM_SPEC;

typedef struct
{
    UINT16      max_lat;
    UINT16      min_rmt_to;
    UINT16      min_loc_to;
} tBTA_DM_SSR_SPEC;

typedef struct
{
   UINT16 manufacturer;
   UINT16 lmp_sub_version;
   UINT8 lmp_version;
}tBTA_DM_LMP_VER_INFO;

extern tBTA_DM_PM_CFG *p_bta_dm_pm_cfg;
extern tBTA_DM_PM_SPEC *p_bta_dm_pm_spec;
extern tBTM_PM_PWR_MD *p_bta_dm_pm_md;
#if (BTM_SSR_INCLUDED == TRUE)
extern tBTA_DM_SSR_SPEC *p_bta_dm_ssr_spec;
#endif

#if ( BTM_EIR_SERVER_INCLUDED == TRUE )
/* update dynamic BRCM Aware EIR data */
extern const tBTA_DM_EIR_CONF bta_dm_eir_cfg;
extern tBTA_DM_EIR_CONF *p_bta_dm_eir_cfg;
#endif

/* DM control block */
#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_DM_CB  bta_dm_cb;
#else
extern tBTA_DM_CB *bta_dm_cb_ptr;
#define bta_dm_cb (*bta_dm_cb_ptr)
#endif

/* DM search control block */
#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_DM_SEARCH_CB  bta_dm_search_cb;
#else
extern tBTA_DM_SEARCH_CB *bta_dm_search_cb_ptr;
#define bta_dm_search_cb (*bta_dm_search_cb_ptr)
#endif

/* DI control block */
#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_DM_DI_CB  bta_dm_di_cb;
#else
extern tBTA_DM_DI_CB *bta_dm_di_cb_ptr;
#define bta_dm_di_cb (*bta_dm_di_cb_ptr)
#endif

extern BOOLEAN bta_dm_sm_execute(BT_HDR *p_msg);
extern void bta_dm_sm_disable( void );
extern BOOLEAN bta_dm_search_sm_execute(BT_HDR *p_msg);
extern void bta_dm_search_sm_disable( void );


extern void bta_dm_enable (tBTA_DM_MSG *p_data);
extern void bta_dm_disable (tBTA_DM_MSG *p_data);
extern void bta_dm_set_dev_name (tBTA_DM_MSG *p_data);
extern void bta_dm_set_visibility (tBTA_DM_MSG *p_data);
extern void bta_dm_set_afhchannels (tBTA_DM_MSG *p_data);
extern void bta_dm_vendor_spec_command(tBTA_DM_MSG *p_data);
extern void bta_dm_bond (tBTA_DM_MSG *p_data);
extern void bta_dm_bond_cancel (tBTA_DM_MSG *p_data);
extern void bta_dm_pin_reply (tBTA_DM_MSG *p_data);
extern void bta_dm_link_policy (tBTA_DM_MSG *p_data);
extern void bta_dm_auth_reply (tBTA_DM_MSG *p_data);
extern void bta_dm_signal_strength(tBTA_DM_MSG *p_data);
extern void bta_dm_tx_inqpower(tBTA_DM_MSG *p_data);
extern void bta_dm_acl_change(tBTA_DM_MSG *p_data);
extern void bta_dm_add_device (tBTA_DM_MSG *p_data);
extern void bta_dm_remove_device (tBTA_DM_MSG *p_data);


extern void bta_dm_pm_btm_status(tBTA_DM_MSG *p_data);
extern void bta_dm_pm_timer(tBTA_DM_MSG *p_data);
extern void bta_dm_add_ampkey (tBTA_DM_MSG *p_data);

#if BLE_INCLUDED == TRUE
extern void bta_dm_add_blekey (tBTA_DM_MSG *p_data);
extern void bta_dm_add_ble_device (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_passkey_reply (tBTA_DM_MSG *p_data);
extern void bta_dm_security_grant (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_bg_conn_type (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_conn_params (tBTA_DM_MSG *p_data);
extern void bta_dm_ble_set_scan_params (tBTA_DM_MSG *p_data);
#endif
extern void bta_dm_set_encryption(tBTA_DM_MSG *p_data);
extern void bta_dm_confirm(tBTA_DM_MSG *p_data);
extern void bta_dm_passkey_cancel(tBTA_DM_MSG *p_data);
#if (BTM_OOB_INCLUDED == TRUE)
extern void bta_dm_loc_oob(tBTA_DM_MSG *p_data);
extern void bta_dm_ci_io_req_act(tBTA_DM_MSG *p_data);
extern void bta_dm_ci_rmt_oob_act(tBTA_DM_MSG *p_data);
#endif /* BTM_OOB_INCLUDED */

extern void bta_dm_init_pm(void);
extern void bta_dm_disable_pm(void);

extern void bta_dm_search_start (tBTA_DM_MSG *p_data);
extern void bta_dm_search_cancel (tBTA_DM_MSG *p_data);
extern void bta_dm_discover (tBTA_DM_MSG *p_data);
extern void bta_dm_di_disc (tBTA_DM_MSG *p_data);
extern void bta_dm_inq_cmpl (tBTA_DM_MSG *p_data);
extern void bta_dm_rmt_name (tBTA_DM_MSG *p_data);
extern void bta_dm_sdp_result (tBTA_DM_MSG *p_data);
extern void bta_dm_search_cmpl (tBTA_DM_MSG *p_data);
extern void bta_dm_free_sdp_db (tBTA_DM_MSG *p_data);
extern void bta_dm_disc_result (tBTA_DM_MSG *p_data);
extern void bta_dm_search_result (tBTA_DM_MSG *p_data);
extern void bta_dm_discovery_cmpl (tBTA_DM_MSG *p_data);
extern void bta_dm_queue_search (tBTA_DM_MSG *p_data);
extern void bta_dm_queue_disc (tBTA_DM_MSG *p_data);
extern void bta_dm_search_clear_queue (tBTA_DM_MSG *p_data);
extern void bta_dm_search_cancel_cmpl (tBTA_DM_MSG *p_data);
extern void bta_dm_search_cancel_notify (tBTA_DM_MSG *p_data);
extern void bta_dm_search_cancel_transac_cmpl(tBTA_DM_MSG *p_data);
extern void bta_dm_disc_rmt_name (tBTA_DM_MSG *p_data);
extern tBTA_DM_PEER_DEVICE * bta_dm_find_peer_device(BD_ADDR peer_addr);
extern void bta_dm_immediate_disable(void);

extern void bta_dm_pm_active(BD_ADDR peer_addr);

#if ( BTM_EIR_SERVER_INCLUDED == TRUE )
void bta_dm_eir_update_uuid(UINT16 uuid16, BOOLEAN adding);
#else
#define bta_dm_eir_update_uuid(x, y)
#endif

#if ( BTM_EIR_SERVER_INCLUDED == TRUE )&&( BTA_EIR_CANNED_UUID_LIST != TRUE )&&(BTA_EIR_SERVER_NUM_CUSTOM_UUID > 0)
extern void bta_dm_update_eir_uuid (tBTA_DM_MSG *p_data);
#endif
#if (BTM_EIR_SERVER_INCLUDED == TRUE)
extern void bta_dm_set_eir_config (tBTA_DM_MSG *p_data);
#endif
extern void bta_dm_enable_test_mode(tBTA_DM_MSG *p_data);
extern void bta_dm_disable_test_mode(tBTA_DM_MSG *p_data);
extern void bta_dm_execute_callback(tBTA_DM_MSG *p_data);

extern void bta_dm_set_afh_channel_assesment(tBTA_DM_MSG *p_data);

#endif /* BTA_DM_INT_H */

