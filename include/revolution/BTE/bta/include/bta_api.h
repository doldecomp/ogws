/******************************************************************************
 *
 *  NOTICE OF CHANGES
 *  2024/03/26:
 *      - Add power mode #defines for RVL target
 * 
 *  2025/03/11:
 *      - Restore old function signatures
 *      - Change search callback event IDs
 *      - Change tBTA_DM_INQ_RES structure
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
 *  This is the public interface file for BTA, Broadcom's Bluetooth
 *  application layer for mobile phones.
 *
 ******************************************************************************/
#ifndef BTA_API_H
#define BTA_API_H

#include "data_types.h"
#include "bt_target.h"
#include "bt_types.h"
#include "btm_api.h"
#include "uipc_msg.h"

#if BLE_INCLUDED == TRUE
#include "btm_ble_api.h"
#endif

/*****************************************************************************
**  Constants and data types
*****************************************************************************/

/* Status Return Value */
#define BTA_SUCCESS             0           /* Successful operation. */
#define BTA_FAILURE             1           /* Generic failure. */
#define BTA_PENDING             2           /* API cannot be completed right now */
#define BTA_BUSY                3
#define BTA_NO_RESOURCES        4
#define BTA_WRONG_MODE          5

typedef UINT8 tBTA_STATUS;

/*
 * Service ID
 *
 * NOTES: When you add a new Service ID for BTA AND require to change the value of BTA_MAX_SERVICE_ID,
 *        make sure that the correct security ID of the new service from Security service definitions (btm_api.h)
 *        should be added to bta_service_id_to_btm_srv_id_lkup_tbl table in bta_dm_act.c.
 */

#define BTA_RES_SERVICE_ID      0           /* Reserved */
#define BTA_SPP_SERVICE_ID      1           /* Serial port profile. */
#define BTA_DUN_SERVICE_ID      2           /* Dial-up networking profile. */
#define BTA_A2DP_SOURCE_SERVICE_ID      3   /* A2DP Source profile. */
#define BTA_LAP_SERVICE_ID      4           /* LAN access profile. */
#define BTA_HSP_SERVICE_ID      5           /* Headset profile. */
#define BTA_HFP_SERVICE_ID      6           /* Hands-free profile. */
#define BTA_OPP_SERVICE_ID      7           /* Object push  */
#define BTA_FTP_SERVICE_ID      8           /* File transfer */
#define BTA_CTP_SERVICE_ID      9           /* Cordless Terminal */
#define BTA_ICP_SERVICE_ID      10          /* Intercom Terminal */
#define BTA_SYNC_SERVICE_ID     11          /* Synchronization */
#define BTA_BPP_SERVICE_ID      12          /* Basic printing profile */
#define BTA_BIP_SERVICE_ID      13          /* Basic Imaging profile */
#define BTA_PANU_SERVICE_ID     14          /* PAN User */
#define BTA_NAP_SERVICE_ID      15          /* PAN Network access point */
#define BTA_GN_SERVICE_ID       16          /* PAN Group Ad-hoc networks */
#define BTA_SAP_SERVICE_ID      17          /* SIM Access profile */
#define BTA_A2DP_SERVICE_ID     18          /* A2DP Sink */
#define BTA_AVRCP_SERVICE_ID    19          /* A/V remote control */
#define BTA_HID_SERVICE_ID      20          /* HID */
#define BTA_VDP_SERVICE_ID      21          /* Video distribution */
#define BTA_PBAP_SERVICE_ID     22          /* PhoneBook Access Server*/
#define BTA_HSP_HS_SERVICE_ID   23          /* HFP HS role */
#define BTA_HFP_HS_SERVICE_ID   24          /* HSP HS role */
#define BTA_MAP_SERVICE_ID      25          /* Message Access Profile */
#define BTA_MN_SERVICE_ID       26          /* Message Notification Service */
#define BTA_HDP_SERVICE_ID      27          /* Health Device Profile */
#define BTA_PCE_SERVICE_ID      28          /* PhoneBook Access Client*/

#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
/* BLE profile service ID */
#define BTA_BLE_SERVICE_ID      29          /* GATT profile */

// btla-specific ++
#define BTA_USER_SERVICE_ID     30          /* User requested UUID */

#define BTA_MAX_SERVICE_ID      31
// btla-specific --
#else
#define BTA_USER_SERVICE_ID     29          /* User requested UUID */
#define BTA_MAX_SERVICE_ID      30
#endif
/* service IDs (BTM_SEC_SERVICE_FIRST_EMPTY + 1) to (BTM_SEC_MAX_SERVICES - 1)
 * are used by BTA JV */
#define BTA_FIRST_JV_SERVICE_ID     (BTM_SEC_SERVICE_FIRST_EMPTY + 1)
#define BTA_LAST_JV_SERVICE_ID      (BTM_SEC_MAX_SERVICES - 1)

typedef UINT8 tBTA_SERVICE_ID;

/* Service ID Mask */
#define BTA_RES_SERVICE_MASK        0x00000001  /* Reserved */
#define BTA_SPP_SERVICE_MASK        0x00000002  /* Serial port profile. */
#define BTA_DUN_SERVICE_MASK        0x00000004  /* Dial-up networking profile. */
#define BTA_FAX_SERVICE_MASK        0x00000008  /* Fax profile. */
#define BTA_LAP_SERVICE_MASK        0x00000010  /* LAN access profile. */
#define BTA_HSP_SERVICE_MASK        0x00000020  /* HSP AG role. */
#define BTA_HFP_SERVICE_MASK        0x00000040  /* HFP AG role */
#define BTA_OPP_SERVICE_MASK        0x00000080  /* Object push  */
#define BTA_FTP_SERVICE_MASK        0x00000100  /* File transfer */
#define BTA_CTP_SERVICE_MASK        0x00000200  /* Cordless Terminal */
#define BTA_ICP_SERVICE_MASK        0x00000400  /* Intercom Terminal */
#define BTA_SYNC_SERVICE_MASK       0x00000800  /* Synchronization */
#define BTA_BPP_SERVICE_MASK        0x00001000  /* Print server */
#define BTA_BIP_SERVICE_MASK        0x00002000  /* Basic Imaging */
#define BTA_PANU_SERVICE_MASK       0x00004000  /* PAN User */
#define BTA_NAP_SERVICE_MASK        0x00008000  /* PAN Network access point */
#define BTA_GN_SERVICE_MASK         0x00010000  /* PAN Group Ad-hoc networks */
#define BTA_SAP_SERVICE_MASK        0x00020000  /* PAN Group Ad-hoc networks */
#define BTA_A2DP_SERVICE_MASK       0x00040000  /* Advanced audio distribution */
#define BTA_AVRCP_SERVICE_MASK      0x00080000  /* A/V remote control */
#define BTA_HID_SERVICE_MASK        0x00100000  /* HID */
#define BTA_VDP_SERVICE_MASK        0x00200000  /* Video distribution */
#define BTA_PBAP_SERVICE_MASK       0x00400000  /* Phone Book Server */
#define BTA_HSP_HS_SERVICE_MASK     0x00800000  /* HFP HS role */
#define BTA_HFP_HS_SERVICE_MASK     0x01000000  /* HSP HS role */
#define BTA_MAS_SERVICE_MASK        0x02000000  /* Message Access Profile */
#define BTA_MN_SERVICE_MASK         0x04000000  /* Message Notification Profile */
#define BTA_HL_SERVICE_MASK         0x08000000  /* Health Device Profile */
#define BTA_PCE_SERVICE_MASK        0x10000000  /* Phone Book Client */

#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
#define BTA_BLE_SERVICE_MASK        0x20000000  /* GATT based service */
// btla-specific ++
#define BTA_USER_SERVICE_MASK       0x40000000  /* Message Notification Profile */
// btla-specific --
#else
// btla-specific ++
#define BTA_USER_SERVICE_MASK       0x20000000  /* Message Notification Profile */
// btla-specific --
#endif

#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
#define BTA_ALL_SERVICE_MASK        0x3FFFFFFF  /* All services supported by BTA. */
#else
#define BTA_ALL_SERVICE_MASK        0x1FFFFFFF  /* All services supported by BTA. */
#endif

typedef UINT32 tBTA_SERVICE_MASK;

/* extended service mask, including mask with one or more GATT UUID */
typedef struct
{
    tBTA_SERVICE_MASK   srvc_mask;
    UINT8               num_uuid;
    tBT_UUID            *p_uuid;
}tBTA_SERVICE_MASK_EXT;

/* Security Setting Mask */
#define BTA_SEC_NONE            BTM_SEC_NONE                                         /* No security. */
#define BTA_SEC_AUTHORIZE       (BTM_SEC_IN_AUTHORIZE )                              /* Authorization required (only needed for out going connection )*/
#define BTA_SEC_AUTHENTICATE    (BTM_SEC_IN_AUTHENTICATE | BTM_SEC_OUT_AUTHENTICATE) /* Authentication required. */
#define BTA_SEC_ENCRYPT         (BTM_SEC_IN_ENCRYPT | BTM_SEC_OUT_ENCRYPT)           /* Encryption required. */

typedef UINT8 tBTA_SEC;

/* Ignore for Discoverable, Connectable, Pairable and Connectable Paired only device modes */

#define BTA_DM_IGNORE           0xFF


/* Discoverable Modes */
#define BTA_DM_NON_DISC         BTM_NON_DISCOVERABLE        /* Device is not discoverable. */
#define BTA_DM_GENERAL_DISC     BTM_GENERAL_DISCOVERABLE    /* General discoverable. */
#define BTA_DM_LIMITED_DISC     BTM_LIMITED_DISCOVERABLE    /* Limited discoverable. */

// btla-specific ++
typedef UINT16 tBTA_DM_DISC;
// btla-specific --

/* Connectable Modes */
#define BTA_DM_NON_CONN         BTM_NON_CONNECTABLE         /* Device is not connectable. */
#define BTA_DM_CONN             BTM_CONNECTABLE             /* Device is connectable. */

// btla-specific ++
typedef UINT16 tBTA_DM_CONN;
// btla-specific --

/* Pairable Modes */
#define BTA_DM_PAIRABLE         1
#define BTA_DM_NON_PAIRABLE     0

/* Connectable Paired Only Mode */
#define BTA_DM_CONN_ALL         0
#define BTA_DM_CONN_PAIRED      1

/* Inquiry Modes */
#define BTA_DM_GENERAL_INQUIRY  BTM_GENERAL_INQUIRY         /* Perform general inquiry. */
#define BTA_DM_LIMITED_INQUIRY  BTM_LIMITED_INQUIRY         /* Perform limited inquiry. */

#if ((defined BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
#define BTA_BLE_INQUIRY_NONE    BTM_BLE_INQUIRY_NONE
#define BTA_BLE_GENERAL_INQUIRY BTM_BLE_GENERAL_INQUIRY      /* Perform LE general inquiry. */
#define BTA_BLE_LIMITED_INQUIRY BTM_BLE_LIMITED_INQUIRY      /* Perform LE limited inquiry. */
#endif
typedef UINT8 tBTA_DM_INQ_MODE;

/* Inquiry Filter Type */
#define BTA_DM_INQ_CLR          BTM_CLR_INQUIRY_FILTER          /* Clear inquiry filter. */
#define BTA_DM_INQ_DEV_CLASS    BTM_FILTER_COND_DEVICE_CLASS    /* Filter on device class. */
#define BTA_DM_INQ_BD_ADDR      BTM_FILTER_COND_BD_ADDR         /* Filter on a specific  BD address. */

typedef UINT8 tBTA_DM_INQ_FILT;

/* Authorize Response */
#define BTA_DM_AUTH_PERM        0      /* Authorized for future connections to the service */
#define BTA_DM_AUTH_TEMP        1      /* Authorized for current connection only */
#define BTA_DM_NOT_AUTH         2      /* Not authorized for the service */

typedef UINT8 tBTA_AUTH_RESP;

/* M/S preferred roles */
#define BTA_ANY_ROLE          0x00
#define BTA_MASTER_ROLE_PREF  0x01
#define BTA_MASTER_ROLE_ONLY  0x02

typedef UINT8 tBTA_PREF_ROLES;

enum
{

    BTA_DM_NO_SCATTERNET,        /* Device doesn't support scatternet, it might
                                    support "role switch during connection" for
                                    an incoming connection, when it already has
                                    another connection in master role */
    BTA_DM_PARTIAL_SCATTERNET,   /* Device supports partial scatternet. It can have
                                    simulateous connection in Master and Slave roles
                                    for short period of time */
    BTA_DM_FULL_SCATTERNET       /* Device can have simultaneous connection in master
                                    and slave roles */

};


/* Inquiry filter device class condition */
typedef struct
{
    DEV_CLASS       dev_class;        /* device class of interest */
    DEV_CLASS       dev_class_mask;   /* mask to determine the bits of device class of interest */
} tBTA_DM_COD_COND;


/* Inquiry Filter Condition */
typedef union
{
    BD_ADDR              bd_addr;            /* BD address of  device to filter. */
    tBTA_DM_COD_COND     dev_class_cond;     /* Device class filter condition */
} tBTA_DM_INQ_COND;

/* Inquiry Parameters */
typedef struct
{
    tBTA_DM_INQ_MODE    mode;           /* Inquiry mode, limited or general. */
    UINT8               duration;       /* Inquiry duration in 1.28 sec units. */
    UINT8               max_resps;      /* Maximum inquiry responses.  Set to zero for unlimited responses. */
    BOOLEAN             report_dup;     /* report duplicated inquiry response with higher RSSI value */
    tBTA_DM_INQ_FILT    filter_type;    /* Filter condition type. */
    tBTA_DM_INQ_COND    filter_cond;    /* Filter condition data. */
} tBTA_DM_INQ;

typedef struct
{
    UINT8   bta_dm_eir_min_name_len;        /* minimum length of local name when it is shortened */
#if (BTA_EIR_CANNED_UUID_LIST == TRUE)
    UINT8   bta_dm_eir_uuid16_len;          /* length of 16-bit UUIDs */
    UINT8  *bta_dm_eir_uuid16;              /* 16-bit UUIDs */
#else
    UINT32  uuid_mask[BTM_EIR_SERVICE_ARRAY_SIZE]; /* mask of UUID list in EIR */
#endif
    INT8   *bta_dm_eir_inq_tx_power;        /* Inquiry TX power         */
    UINT8   bta_dm_eir_flag_len;            /* length of flags in bytes */
    UINT8  *bta_dm_eir_flags;               /* flags for EIR */
    UINT8   bta_dm_eir_manufac_spec_len;    /* length of manufacturer specific in bytes */
    UINT8  *bta_dm_eir_manufac_spec;        /* manufacturer specific */
} tBTA_DM_EIR_CONF;

#if BLE_INCLUDED == TRUE
/* ADV data flag bit definition used for BTM_BLE_AD_TYPE_FLAG */
#define BTA_BLE_LIMIT_DISC_FLAG     BTM_BLE_LIMIT_DISC_FLAG
#define BTA_BLE_GEN_DISC_FLAG       BTM_BLE_GEN_DISC_FLAG
#define BTA_BLE_BREDR_NOT_SPT       BTM_BLE_BREDR_NOT_SPT
#define BTA_BLE_NON_LIMIT_DISC_FLAG BTM_BLE_NON_LIMIT_DISC_FLAG
#define BTA_BLE_ADV_FLAG_MASK       BTM_BLE_ADV_FLAG_MASK
#define BTA_BLE_LIMIT_DISC_MASK     BTM_BLE_LIMIT_DISC_MASK

#define BTA_BLE_AD_BIT_DEV_NAME     BTM_BLE_AD_BIT_DEV_NAME
#define BTA_BLE_AD_BIT_FLAGS        BTM_BLE_AD_BIT_FLAGS
#define BTA_BLE_AD_BIT_MANU         BTM_BLE_AD_BIT_MANU
#define BTA_BLE_AD_BIT_TX_PWR       BTM_BLE_AD_BIT_TX_PWR
#define BTA_BLE_AD_BIT_ATTR         BTM_BLE_AD_BIT_ATTR
#define BTA_BLE_AD_BIT_INT_RANGE    BTM_BLE_AD_BIT_INT_RANGE
#define BTA_BLE_AD_BIT_SERVICE      BTM_BLE_AD_BIT_SERVICE
#define BTA_BLE_AD_BIT_SERVICE_SOL  BTM_BLE_AD_BIT_SERVICE_SOL
#define BTA_BLE_AD_BIT_SERVICE_DATA BTM_BLE_AD_BIT_SERVICE_DATA
#define BTA_BLE_AD_BIT_SIGN_DATA    BTM_BLE_AD_BIT_SIGN_DATA
typedef  UINT16  tBTA_BLE_AD_MASK;

/* slave preferred connection interval range */
typedef struct
{
    UINT16  low;
    UINT16  hi;

}tBTA_BLE_INT_RANGE;

/* Service tag supported in the device */
typedef struct
{
    UINT8       num_service;
    BOOLEAN     list_cmpl;
    UINT16      *p_uuid;
}tBTA_BLE_SERVICE;

/* attribute data */
typedef struct
{
    UINT16       uuid;
    UINT16       data_len;
    UINT8       *p_data;
}tBTA_BLE_ATTR;

#define BTA_BLE_NUM_AD_ATTR_MAX         BTM_BLE_NUM_AD_ATTR_MAX

/* attribute list contained in adv data */
typedef struct
{
    UINT8               num_attr;
    tBTA_BLE_ATTR       attr_list[BTA_BLE_NUM_AD_ATTR_MAX];
}tBTA_BLE_ATTR_DATA;

typedef struct
{
    UINT8       len;
    UINT8      *p_val;
}tBTA_BLE_MANU;

typedef struct
{
    tBTA_BLE_MANU       manu;        /* manufactuer data */
    tBTA_BLE_INT_RANGE  int_range;      /* slave prefered conn interval range */
    tBTA_BLE_SERVICE    services;       /* services */
    tBTA_BLE_ATTR_DATA  attr;           /* attribute data */
    UINT8               flag;
}tBTA_BLE_ADV_DATA;

/* These are the fields returned in each device adv packet.  It
** is returned in the results callback if registered.
*/
typedef struct
{
    UINT8               conn_mode;
    tBTA_BLE_AD_MASK    ad_mask;        /* mask of the valid adv data field */
    UINT8               flag;
    UINT8               tx_power_level;
    UINT8               remote_name_len;
    UINT8               *p_remote_name;
    tBTA_BLE_ATTR_DATA  attr_data;
    tBTA_BLE_SERVICE    service;
} tBTA_BLE_INQ_DATA;
#endif

typedef INT8 tBTA_DM_RSSI_VALUE;
typedef UINT8 tBTA_DM_LINK_QUALITY_VALUE;


/* signal strength mask */
#define BTA_SIG_STRENGTH_RSSI_MASK          1
#define BTA_SIG_STRENGTH_LINK_QUALITY_MASK  2

typedef UINT8 tBTA_SIG_STRENGTH_MASK;


/* Security Callback Events */
#define BTA_DM_ENABLE_EVT               0       /* Enable Event */
#define BTA_DM_DISABLE_EVT              1       /* Disable Event */
#define BTA_DM_PIN_REQ_EVT              2       /* PIN request. */
#define BTA_DM_AUTH_CMPL_EVT            3       /* Authentication complete indication. */
#define BTA_DM_AUTHORIZE_EVT            4       /* Authorization request. */
#define BTA_DM_LINK_UP_EVT              5       /* Connection UP event */
#define BTA_DM_LINK_DOWN_EVT            6       /* Connection DOWN event */
#define BTA_DM_SIG_STRENGTH_EVT         7       /* Signal strength for bluetooth connection */
#define BTA_DM_BUSY_LEVEL_EVT           8       /* System busy level */
#define BTA_DM_BOND_CANCEL_CMPL_EVT     9       /* Bond cancel complete indication */
#define BTA_DM_SP_CFM_REQ_EVT           10      /* Simple Pairing User Confirmation request. */
#define BTA_DM_SP_KEY_NOTIF_EVT         11      /* Simple Pairing Passkey Notification */
#define BTA_DM_SP_RMT_OOB_EVT           12      /* Simple Pairing Remote OOB Data request. */
#define BTA_DM_SP_KEYPRESS_EVT          13      /* Key press notification event. */
#define BTA_DM_ROLE_CHG_EVT             14      /* Role Change event. */
#define BTA_DM_BLE_KEY_EVT              15      /* BLE SMP key event for peer device keys */
#define BTA_DM_BLE_SEC_REQ_EVT          16      /* BLE SMP security request */
#define BTA_DM_BLE_PASSKEY_NOTIF_EVT    17      /* SMP passkey notification event */
#define BTA_DM_BLE_PASSKEY_REQ_EVT      18      /* SMP passkey request event */
#define BTA_DM_BLE_OOB_REQ_EVT          19      /* SMP OOB request event */
#define BTA_DM_BLE_LOCAL_IR_EVT         20      /* BLE local IR event */
#define BTA_DM_BLE_LOCAL_ER_EVT         21      /* BLE local ER event */
// btla-specific ++
#define BTA_DM_BLE_AUTH_CMPL_EVT        22      /* BLE Auth complete */
// btla-specific --
#define BTA_DM_DEV_UNPAIRED_EVT         23
#define BTA_DM_HW_ERROR_EVT             24      /* BT Chip H/W error */
typedef UINT8 tBTA_DM_SEC_EVT;

/* Structure associated with BTA_DM_ENABLE_EVT */
typedef struct
{
    BD_ADDR         bd_addr;            /* BD address of local device. */
    tBTA_STATUS    status;
} tBTA_DM_ENABLE;

/* Structure associated with BTA_DM_PIN_REQ_EVT */
typedef struct
{
    BD_ADDR         bd_addr;            /* BD address peer device. */
    BD_NAME         bd_name;            /* Name of peer device. */
    DEV_CLASS       dev_class;          /* Class of Device */
} tBTA_DM_PIN_REQ;

/* BLE related definition */

#define BTA_DM_AUTH_FAIL_BASE                   (HCI_ERR_MAX_ERR + 10)
#define BTA_DM_AUTH_CONVERT_SMP_CODE(x)        (BTA_DM_AUTH_FAIL_BASE + (x))
#define BTA_DM_AUTH_SMP_PASSKEY_FAIL             BTA_DM_AUTH_CONVERT_SMP_CODE (SMP_PASSKEY_ENTRY_FAIL)
#define BTA_DM_AUTH_SMP_OOB_FAIL                (BTA_DM_AUTH_FAIL_BASE + SMP_OOB_FAIL)
#define BTA_DM_AUTH_SMP_PAIR_AUTH_FAIL          (BTA_DM_AUTH_FAIL_BASE + SMP_PAIR_AUTH_FAIL)
#define BTA_DM_AUTH_SMP_CONFIRM_VALUE_FAIL      (BTA_DM_AUTH_FAIL_BASE + SMP_CONFIRM_VALUE_ERR)
#define BTA_DM_AUTH_SMP_PAIR_NOT_SUPPORT        (BTA_DM_AUTH_FAIL_BASE + SMP_PAIR_NOT_SUPPORT)
#define BTA_DM_AUTH_SMP_ENC_KEY_SIZE            (BTA_DM_AUTH_FAIL_BASE + SMP_ENC_KEY_SIZE)
#define BTA_DM_AUTH_SMP_INVALID_CMD             (BTA_DM_AUTH_FAIL_BASE + SMP_INVALID_CMD)
#define BTA_DM_AUTH_SMP_UNKNOWN_ERR             (BTA_DM_AUTH_FAIL_BASE + SMP_PAIR_FAIL_UNKNOWN)
#define BTA_DM_AUTH_SMP_REPEATED_ATTEMPT        (BTA_DM_AUTH_FAIL_BASE + SMP_REPEATED_ATTEMPTS)
#define BTA_DM_AUTH_SMP_INTERNAL_ERR            (BTA_DM_AUTH_FAIL_BASE + SMP_PAIR_INTERNAL_ERR)
#define BTA_DM_AUTH_SMP_UNKNOWN_IO              (BTA_DM_AUTH_FAIL_BASE + SMP_UNKNOWN_IO_CAP)
#define BTA_DM_AUTH_SMP_INIT_FAIL               (BTA_DM_AUTH_FAIL_BASE + SMP_INIT_FAIL)
#define BTA_DM_AUTH_SMP_CONFIRM_FAIL            (BTA_DM_AUTH_FAIL_BASE + SMP_CONFIRM_FAIL)
#define BTA_DM_AUTH_SMP_BUSY                    (BTA_DM_AUTH_FAIL_BASE + SMP_BUSY)
#define BTA_DM_AUTH_SMP_ENC_FAIL                (BTA_DM_AUTH_FAIL_BASE + SMP_ENC_FAIL)
#define BTA_DM_AUTH_SMP_RSP_TIMEOUT             (BTA_DM_AUTH_FAIL_BASE + SMP_RSP_TIMEOUT)

/* connection parameter boundary value and dummy value */
#define BTA_DM_BLE_SCAN_INT_MIN          BTM_BLE_SCAN_INT_MIN
#define BTA_DM_BLE_SCAN_INT_MAX          BTM_BLE_SCAN_INT_MAX
#define BTA_DM_BLE_SCAN_WIN_MIN          BTM_BLE_SCAN_WIN_MIN
#define BTA_DM_BLE_SCAN_WIN_MAX          BTM_BLE_SCAN_WIN_MAX
#define BTA_DM_BLE_CONN_INT_MIN          BTM_BLE_CONN_INT_MIN
#define BTA_DM_BLE_CONN_INT_MAX          BTM_BLE_CONN_INT_MAX
#define BTA_DM_BLE_CONN_LATENCY_MAX      BTM_BLE_CONN_LATENCY_MAX
#define BTA_DM_BLE_CONN_SUP_TOUT_MIN     BTM_BLE_CONN_SUP_TOUT_MIN
#define BTA_DM_BLE_CONN_SUP_TOUT_MAX     BTM_BLE_CONN_SUP_TOUT_MAX
#define BTA_DM_BLE_CONN_PARAM_UNDEF      BTM_BLE_CONN_PARAM_UNDEF  /* use this value when a specific value not to be overwritten */


#define BTA_LE_KEY_PENC      BTM_LE_KEY_PENC  /* encryption information of peer device */
#define BTA_LE_KEY_PID       BTM_LE_KEY_PID   /* identity key of the peer device */
#define BTA_LE_KEY_PCSRK     BTM_LE_KEY_PCSRK   /* peer SRK */
#define BTA_LE_KEY_LENC      BTM_LE_KEY_LENC        /* master role security information:div */
#define BTA_LE_KEY_LID       BTM_LE_KEY_LID         /* master device ID key */
#define BTA_LE_KEY_LCSRK     BTM_LE_KEY_LCSRK        /* local CSRK has been deliver to peer */
typedef UINT8 tBTA_LE_KEY_TYPE; /* can be used as a bit mask */


typedef tBTM_LE_PENC_KEYS  tBTA_LE_PENC_KEYS ;
typedef tBTM_LE_PCSRK_KEYS tBTA_LE_PCSRK_KEYS;
typedef tBTM_LE_LENC_KEYS  tBTA_LE_LENC_KEYS  ;
typedef tBTM_LE_LCSRK_KEYS tBTA_LE_LCSRK_KEYS ;

typedef union
{
    tBTA_LE_PENC_KEYS   penc_key;       /* received peer encryption key */
    tBTA_LE_PCSRK_KEYS  psrk_key;       /* received peer device SRK */
    BT_OCTET16          pid_key;        /* peer device ID key */
    tBTA_LE_LENC_KEYS   lenc_key;       /* local encryption reproduction keys LTK = = d1(ER,DIV,0)*/
    tBTA_LE_LCSRK_KEYS  lcsrk_key;      /* local device CSRK = d1(ER,DIV,1)*/
}tBTA_LE_KEY_VALUE;

#define BTA_BLE_LOCAL_KEY_TYPE_ID         1
#define BTA_BLE_LOCAL_KEY_TYPE_ER         2
typedef UINT8 tBTA_DM_BLE_LOCAL_KEY_MASK;

typedef struct
{
    BT_OCTET16       ir;
    BT_OCTET16       irk;
    BT_OCTET16       dhk;
}tBTA_BLE_LOCAL_ID_KEYS;

#define BTA_DM_SEC_GRANTED              BTA_SUCCESS
#define BTA_DM_SEC_PAIR_NOT_SPT         BTA_DM_AUTH_SMP_PAIR_NOT_SUPPORT
#define BTA_DM_SEC_REP_ATTEMPTS         BTA_DM_AUTH_SMP_REPEATED_ATTEMPT
typedef UINT8 tBTA_DM_BLE_SEC_GRANT;


#define BTA_DM_BLE_ONN_NONE             BTM_BLE_CONN_NONE
#define BTA_DM_BLE_CONN_AUTO            BTM_BLE_CONN_AUTO
#define BTA_DM_BLE_CONN_SELECTIVE       BTM_BLE_CONN_SELECTIVE
typedef UINT8 tBTA_DM_BLE_CONN_TYPE;

typedef BOOLEAN (tBTA_DM_BLE_SEL_CBACK)(BD_ADDR random_bda, UINT8 *p_remote_name);

/* Structure associated with BTA_DM_BLE_SEC_REQ_EVT */
typedef struct
{
    BD_ADDR         bd_addr;        /* peer address */
    BD_NAME         bd_name;        /* peer device name */
} tBTA_DM_BLE_SEC_REQ;

typedef struct
{
    BD_ADDR                 bd_addr;        /* peer address */
    tBTM_LE_KEY_TYPE        key_type;
    tBTM_LE_KEY_VALUE       key_value;
}tBTA_DM_BLE_KEY;

/* Structure associated with BTA_DM_AUTH_CMPL_EVT */
typedef struct
{
    BD_ADDR         bd_addr;            /* BD address peer device. */
    BD_NAME         bd_name;            /* Name of peer device. */
    BOOLEAN         key_present;        /* Valid link key value in key element */
    LINK_KEY        key;                /* Link key associated with peer device. */
    UINT8           key_type;           /* The type of Link Key */
    BOOLEAN         success;            /* TRUE of authentication succeeded, FALSE if failed. */
    UINT8           fail_reason;        /* The HCI reason/error code for when success=FALSE */

} tBTA_DM_AUTH_CMPL;


/* Structure associated with BTA_DM_AUTHORIZE_EVT */
typedef struct
{
    BD_ADDR         bd_addr;            /* BD address peer device. */
    BD_NAME         bd_name;            /* Name of peer device. */
    tBTA_SERVICE_ID service;            /* Service ID to authorize. */
// btla-specific ++
    DEV_CLASS      dev_class;
// btla-specific --
} tBTA_DM_AUTHORIZE;

/* Structure associated with BTA_DM_LINK_UP_EVT */
typedef struct
{
    BD_ADDR         bd_addr;            /* BD address peer device. */
} tBTA_DM_LINK_UP;

/* Structure associated with BTA_DM_LINK_DOWN_EVT */
typedef struct
{
    BD_ADDR         bd_addr;            /* BD address peer device. */
    UINT8           status;             /* connection open/closed */
} tBTA_DM_LINK_DOWN;

/* Structure associated with BTA_DM_ROLE_CHG_EVT */
typedef struct
{
    BD_ADDR         bd_addr;            /* BD address peer device. */
    UINT8           new_role;           /* the new connection role */
} tBTA_DM_ROLE_CHG;

/* Structure associated with BTA_DM_SIG_STRENGTH_EVT */
typedef struct
{
    BD_ADDR         bd_addr;            /* BD address peer device. */
    tBTA_SIG_STRENGTH_MASK mask;        /* mask for the values that are valid */
    tBTA_DM_RSSI_VALUE  rssi_value;
    tBTA_DM_LINK_QUALITY_VALUE link_quality_value;

} tBTA_DM_SIG_STRENGTH;

/* Structure associated with BTA_DM_BUSY_LEVEL_EVT */
typedef struct
{
    UINT8           level;     /* when paging or inquiring, level is 10.
                                    Otherwise, the number of ACL links */
} tBTA_DM_BUSY_LEVEL;

#define BTA_IO_CAP_OUT      BTM_IO_CAP_OUT      /* DisplayOnly */
#define BTA_IO_CAP_IO       BTM_IO_CAP_IO       /* DisplayYesNo */
#define BTA_IO_CAP_IN       BTM_IO_CAP_IN       /* KeyboardOnly */
#define BTA_IO_CAP_NONE     BTM_IO_CAP_NONE     /* NoInputNoOutput */
typedef tBTM_IO_CAP     tBTA_IO_CAP;

#define BTA_AUTH_SP_NO    BTM_AUTH_SP_NO      /* 0 MITM Protection Not Required - Single Profile/non-bonding
                                                Numeric comparison with automatic accept allowed */
#define BTA_AUTH_SP_YES   BTM_AUTH_SP_YES     /* 1 MITM Protection Required - Single Profile/non-bonding
                                                Use IO Capabilities to determine authentication procedure */
#define BTA_AUTH_AP_NO    BTM_AUTH_AP_NO      /* 2 MITM Protection Not Required - All Profiles/dedicated bonding
                                                Numeric comparison with automatic accept allowed */
#define BTA_AUTH_AP_YES   BTM_AUTH_AP_YES     /* 3 MITM Protection Required - All Profiles/dedicated bonding
                                                Use IO Capabilities to determine authentication procedure */
#define BTA_AUTH_SPGB_NO  BTM_AUTH_SPGB_NO    /* 4 MITM Protection Not Required - Single Profiles/general bonding
                                                Numeric comparison with automatic accept allowed */
#define BTA_AUTH_SPGB_YES BTM_AUTH_SPGB_YES   /* 5 MITM Protection Required - Single Profiles/general bonding
                                                Use IO Capabilities to determine authentication procedure */
typedef tBTM_AUTH_REQ   tBTA_AUTH_REQ;

#define BTA_AUTH_DD_BOND    BTM_AUTH_DD_BOND  /* 2 this bit is set for dedicated bonding */
#define BTA_AUTH_GEN_BOND   BTM_AUTH_SPGB_NO  /* 4 this bit is set for general bonding */
#define BTA_AUTH_BONDS      BTM_AUTH_BONDS    /* 6 the general/dedicated bonding bits  */

#define BTA_LE_AUTH_NO_BOND    BTM_LE_AUTH_REQ_NO_BOND  /* 0*/
#define BTA_LE_AUTH_BOND       BTM_LE_AUTH_REQ_BOND     /* 1 << 0 */
#define BTA_LE_AUTH_REQ_MITM   BTM_LE_AUTH_REQ_MITM    /* 1 << 2 */
typedef tBTM_LE_AUTH_REQ       tBTA_LE_AUTH_REQ;       /* combination of the above bit pattern */

#define BTA_OOB_NONE        BTM_OOB_NONE
#define BTA_OOB_PRESENT     BTM_OOB_PRESENT
#if BTM_OOB_INCLUDED == TRUE
#define BTA_OOB_UNKNOWN     BTM_OOB_UNKNOWN
#endif
typedef tBTM_OOB_DATA   tBTA_OOB_DATA;

/* Structure associated with BTA_DM_SP_CFM_REQ_EVT */
typedef struct
{
    BD_ADDR         bd_addr;        /* peer address */
    DEV_CLASS       dev_class;      /* peer CoD */
    BD_NAME         bd_name;        /* peer device name */
    UINT32          num_val;        /* the numeric value for comparison. If just_works, do not show this number to UI */
    BOOLEAN         just_works;     /* TRUE, if "Just Works" association model */
    tBTA_AUTH_REQ   loc_auth_req;   /* Authentication required for local device */
    tBTA_AUTH_REQ   rmt_auth_req;   /* Authentication required for peer device */
    tBTA_IO_CAP     loc_io_caps;    /* IO Capabilities of local device */
    tBTA_AUTH_REQ   rmt_io_caps;    /* IO Capabilities of remote device */
} tBTA_DM_SP_CFM_REQ;

enum
{
    BTA_SP_KEY_STARTED,         /* passkey entry started */
    BTA_SP_KEY_ENTERED,         /* passkey digit entered */
    BTA_SP_KEY_ERASED,          /* passkey digit erased */
    BTA_SP_KEY_CLEARED,         /* passkey cleared */
    BTA_SP_KEY_COMPLT           /* passkey entry completed */
};
typedef UINT8   tBTA_SP_KEY_TYPE;

/* Structure associated with BTA_DM_SP_KEYPRESS_EVT */
typedef struct
{
    BD_ADDR             bd_addr;        /* peer address */
    tBTA_SP_KEY_TYPE   notif_type;
}tBTA_DM_SP_KEY_PRESS;

/* Structure associated with BTA_DM_SP_KEY_NOTIF_EVT */
typedef struct
{
    BD_ADDR         bd_addr;        /* peer address */
    DEV_CLASS       dev_class;      /* peer CoD */
    BD_NAME         bd_name;        /* peer device name */
    UINT32          passkey;        /* the numeric value for comparison. If just_works, do not show this number to UI */
} tBTA_DM_SP_KEY_NOTIF;

/* Structure associated with BTA_DM_SP_RMT_OOB_EVT */
typedef struct
{
    BD_ADDR         bd_addr;        /* peer address */
    DEV_CLASS       dev_class;      /* peer CoD */
    BD_NAME         bd_name;        /* peer device name */
} tBTA_DM_SP_RMT_OOB;

/* Structure associated with BTA_DM_BOND_CANCEL_CMPL_EVT */
typedef struct
{
    tBTA_STATUS     result;    /* TRUE of bond cancel succeeded, FALSE if failed. */
} tBTA_DM_BOND_CANCEL_CMPL;

/* Union of all security callback structures */
typedef union
{
    tBTA_DM_ENABLE      enable;         /* BTA enabled */
    tBTA_DM_PIN_REQ     pin_req;        /* PIN request. */
    tBTA_DM_AUTH_CMPL   auth_cmpl;      /* Authentication complete indication. */
    tBTA_DM_AUTHORIZE   authorize;      /* Authorization request. */
    tBTA_DM_LINK_UP     link_up;       /* ACL connection down event */
    tBTA_DM_LINK_DOWN   link_down;       /* ACL connection down event */
    tBTA_DM_SIG_STRENGTH sig_strength;  /* rssi and link quality value */
    tBTA_DM_BUSY_LEVEL  busy_level;     /* System busy level */
    tBTA_DM_SP_CFM_REQ  cfm_req;        /* user confirm request */
    tBTA_DM_SP_KEY_NOTIF key_notif;     /* passkey notification */
    tBTA_DM_SP_RMT_OOB  rmt_oob;        /* remote oob */
    tBTA_DM_BOND_CANCEL_CMPL bond_cancel_cmpl; /* Bond Cancel Complete indication */
    tBTA_DM_SP_KEY_PRESS   key_press;   /* key press notification event */
    tBTA_DM_ROLE_CHG     role_chg;       /* role change event */
    tBTA_DM_BLE_SEC_REQ  ble_req;        /* BLE SMP related request */
    tBTA_DM_BLE_KEY      ble_key;        /* BLE SMP keys used when pairing */
    tBTA_BLE_LOCAL_ID_KEYS  ble_id_keys;  /* IR event */
    BT_OCTET16              ble_er;       /* ER event data */
} tBTA_DM_SEC;

/* Security callback */
typedef void (tBTA_DM_SEC_CBACK)(tBTA_DM_SEC_EVT event, tBTA_DM_SEC *p_data);

/* Vendor Specific Command Callback */
typedef tBTM_VSC_CMPL_CB        tBTA_VENDOR_CMPL_CBACK;

/* Search callback events */
#ifdef REVOLUTION
#define BTA_DM_INQ_RES_EVT              0       /* Inquiry result for a peer device. */
#define BTA_DM_INQ_CMPL_EVT             1       /* Inquiry complete. */
#define BTA_DM_DISC_RES_EVT             2       /* Discovery result for a peer device. */
#define BTA_DM_DISC_CMPL_EVT            3       /* Discovery complete. */
#define BTA_DM_SEARCH_CANCEL_CMPL_EVT   4       /* Search cancelled */
#else
#define BTA_DM_INQ_RES_EVT              0       /* Inquiry result for a peer device. */
#define BTA_DM_INQ_CMPL_EVT             1       /* Inquiry complete. */
#define BTA_DM_DISC_RES_EVT             2       /* Discovery result for a peer device. */
#define BTA_DM_DISC_BLE_RES_EVT         3       /* Discovery result for BLE GATT based servoce on a peer device. */
#define BTA_DM_DISC_CMPL_EVT            4       /* Discovery complete. */
#define BTA_DM_DI_DISC_CMPL_EVT         5       /* Discovery complete. */
#define BTA_DM_SEARCH_CANCEL_CMPL_EVT   6       /* Search cancelled */
#endif

typedef UINT8 tBTA_DM_SEARCH_EVT;

#define BTA_DM_INQ_RES_IGNORE_RSSI      BTM_INQ_RES_IGNORE_RSSI /* 0x7f RSSI value not supplied (ignore it) */

/* Structure associated with BTA_DM_INQ_RES_EVT */
typedef struct
{
    BD_ADDR         bd_addr;                /* BD address peer device. */
    DEV_CLASS       dev_class;              /* Device class of peer device. */
#ifndef REVOLUTION
    BOOLEAN         remt_name_not_required; /* Application sets this flag if it already knows the name of the device */
                                            /* If the device name is known to application BTA skips the remote name request */
    BOOLEAN         is_limited;             /* TRUE, if the limited inquiry bit is set in the CoD */
#endif
    INT8            rssi;                   /* The rssi value */
    UINT8           *p_eir;                 /* received EIR */
#if (BLE_INCLUDED == TRUE)
    UINT8               inq_result_type;
    UINT8               ble_addr_type;
    tBTM_BLE_EVT_TYPE   ble_evt_type;
    tBT_DEVICE_TYPE     device_type;
#endif

} tBTA_DM_INQ_RES;

/* Structure associated with BTA_DM_INQ_CMPL_EVT */
typedef struct
{
    UINT8           num_resps;          /* Number of inquiry responses. */
} tBTA_DM_INQ_CMPL;

/* Structure associated with BTA_DM_DI_DISC_CMPL_EVT */
typedef struct
{
    BD_ADDR             bd_addr;        /* BD address peer device. */
    UINT8               num_record;     /* Number of DI record */
    tBTA_STATUS         result;
} tBTA_DM_DI_DISC_CMPL;

/* Structure associated with BTA_DM_DISC_RES_EVT */
typedef struct
{
    BD_ADDR             bd_addr;        /* BD address peer device. */
    BD_NAME             bd_name;        /* Name of peer device. */
    tBTA_SERVICE_MASK   services;       /* Services found on peer device. */
// btla-specific ++
    UINT8           *   p_raw_data;     /* Raw data for discovery DB */
    UINT32              raw_data_size;  /* size of raw data */
    tBT_DEVICE_TYPE     device_type;    /* device type in case it is BLE device */
    UINT32              num_uuids;
    UINT8               *p_uuid_list;
// btla-specific --
    tBTA_STATUS         result;
} tBTA_DM_DISC_RES;

/* Structure associated with tBTA_DM_DISC_BLE_RES */
typedef struct
{
    BD_ADDR             bd_addr;        /* BD address peer device. */
    BD_NAME             bd_name;        /* Name of peer device. */
    tBT_UUID            service;        /* GATT based Services UUID found on peer device. */
} tBTA_DM_DISC_BLE_RES;


/* Union of all search callback structures */
typedef union
{
    tBTA_DM_INQ_RES     inq_res;        /* Inquiry result for a peer device. */
    tBTA_DM_INQ_CMPL    inq_cmpl;       /* Inquiry complete. */
    tBTA_DM_DISC_RES    disc_res;       /* Discovery result for a peer device. */
    tBTA_DM_DISC_BLE_RES    disc_ble_res;   /* discovery result for GATT based service */
    tBTA_DM_DI_DISC_CMPL    di_disc;        /* DI discovery result for a peer device */

} tBTA_DM_SEARCH;

/* Search callback */
typedef void (tBTA_DM_SEARCH_CBACK)(tBTA_DM_SEARCH_EVT event, tBTA_DM_SEARCH *p_data);

/* Execute call back */
typedef void (tBTA_DM_EXEC_CBACK) (void * p_param);

/* Encryption callback*/
typedef void (tBTA_DM_ENCRYPT_CBACK) (BD_ADDR bd_addr, tBTA_STATUS result);

#if BLE_INCLUDED == TRUE
#define BTA_DM_BLE_SEC_NONE         BTM_BLE_SEC_NONE
#define BTA_DM_BLE_SEC_ENCRYPT      BTM_BLE_SEC_ENCRYPT
#define BTA_DM_BLE_SEC_NO_MITM      BTM_BLE_SEC_ENCRYPT_NO_MITM
#define BTA_DM_BLE_SEC_MITM         BTM_BLE_SEC_ENCRYPT_MITM
typedef tBTM_BLE_SEC_ACT            tBTA_DM_BLE_SEC_ACT;
#else
typedef UINT8                       tBTA_DM_BLE_SEC_ACT;
#endif

/* Maximum service name length */
#define BTA_SERVICE_NAME_LEN    35
#define BTA_SERVICE_DESP_LEN    BTA_SERVICE_NAME_LEN
#define BTA_PROVIDER_NAME_LEN   BTA_SERVICE_NAME_LEN


/* link policy masks  */
#define BTA_DM_LP_SWITCH        HCI_ENABLE_MASTER_SLAVE_SWITCH
#define BTA_DM_LP_HOLD          HCI_ENABLE_HOLD_MODE
#define BTA_DM_LP_SNIFF         HCI_ENABLE_SNIFF_MODE
#define BTA_DM_LP_PARK          HCI_ENABLE_PARK_MODE
typedef UINT16 tBTA_DM_LP_MASK;

/* power mode actions  */
#define BTA_DM_PM_NO_ACTION    0x00       /* no change to the current pm setting */
#define BTA_DM_PM_PARK         0x10       /* prefers park mode */
#define BTA_DM_PM_SNIFF        0x20       /* prefers sniff mode */
#define BTA_DM_PM_SNIFF1       0x21       /* prefers sniff1 mode */
#define BTA_DM_PM_SNIFF2       0x22       /* prefers sniff2 mode */
#define BTA_DM_PM_SNIFF3       0x23       /* prefers sniff3 mode */
#define BTA_DM_PM_SNIFF4       0x24       /* prefers sniff4 mode */
#define BTA_DM_PM_SNIFF5       0x25       /* prefers sniff5 mode */
#define BTA_DM_PM_SNIFF6       0x26       /* prefers sniff6 mode */
#define BTA_DM_PM_SNIFF7       0x27       /* prefers sniff7 mode */
#define BTA_DM_PM_SNIFF_USER0  0x28       /* prefers user-defined sniff0 mode (testtool only) */
#define BTA_DM_PM_SNIFF_USER1  0x29       /* prefers user-defined sniff1 mode (testtool only) */
#define BTA_DM_PM_ACTIVE       0x40       /* prefers active mode */
#define BTA_DM_PM_RETRY        0x80       /* retry power mode based on current settings */
#define BTA_DM_PM_NO_PREF      0x01       /* service has no prefernce on power mode setting. eg. connection to service got closed */

#ifdef REVOLUTION
// Were these values previously reversed?
#define BTA_DM_PM_SNIFF_RVL 0x02
#define BTA_DM_PM_RETRY_RVL 0x08
#endif

typedef UINT8 tBTA_DM_PM_ACTTION;

/* index to bta_dm_ssr_spec */
#define BTA_DM_PM_SSR0          0
#define BTA_DM_PM_SSR1          1
#define BTA_DM_PM_SSR2          2
#define BTA_DM_PM_SSR3          3
#define BTA_DM_PM_SSR4          4
#define BTA_DM_PM_SSR5          5
#define BTA_DM_PM_SSR6          6

#define BTA_DM_PM_NUM_EVTS      9

#ifndef BTA_DM_PM_PARK_IDX
#define BTA_DM_PM_PARK_IDX      5 /* the actual index to bta_dm_pm_md[] for PARK mode */
#endif

#define BTA_DM_SW_BB_TO_MM      BTM_SW_BB_TO_MM
#define BTA_DM_SW_MM_TO_BB      BTM_SW_MM_TO_BB
#define BTA_DM_SW_BB_TO_BTC     BTM_SW_BB_TO_BTC
#define BTA_DM_SW_BTC_TO_BB     BTM_SW_BTC_TO_BB

typedef tBTM_SW_DIR tBTA_DM_SW_DIR;

/* Switch callback events */
#define BTA_DM_SWITCH_CMPL_EVT      0       /* Completion of the Switch API */

typedef UINT8 tBTA_DM_SWITCH_EVT;
typedef void (tBTA_DM_SWITCH_CBACK)(tBTA_DM_SWITCH_EVT event, tBTA_STATUS status);

/* Audio routing out configuration */
#define BTA_DM_ROUTE_NONE       0x00    /* No Audio output */
#define BTA_DM_ROUTE_DAC        0x01    /* routing over analog output */
#define BTA_DM_ROUTE_I2S        0x02    /* routing over digital (I2S) output */
#define BTA_DM_ROUTE_BT_MONO    0x04    /* routing over SCO */
#define BTA_DM_ROUTE_BT_STEREO  0x08    /* routing over BT Stereo */
#define BTA_DM_ROUTE_HOST       0x10    /* routing over Host */
#define BTA_DM_ROUTE_FMTX       0x20    /* routing over FMTX */
#define BTA_DM_ROUTE_FMRX       0x40    /* routing over FMRX */
#define BTA_DM_ROUTE_BTSNK      0x80    /* routing over BT SNK */

typedef UINT8 tBTA_DM_ROUTE_PATH;


/* Device Identification (DI) data structure
*/
/* Used to set the DI record */
typedef tSDP_DI_RECORD          tBTA_DI_RECORD;
/* Used to get the DI record */
typedef tSDP_DI_GET_RECORD      tBTA_DI_GET_RECORD;
/* SDP discovery database */
typedef tSDP_DISCOVERY_DB       tBTA_DISCOVERY_DB;

#ifndef         BTA_DI_NUM_MAX
#define         BTA_DI_NUM_MAX       3
#endif

/*****************************************************************************
**  External Function Declarations
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**
** Function         BTA_EnableBluetooth
**
** Description      This function initializes BTA and prepares BTA and the
**                  Bluetooth protocol stack for use.  This function is
**                  typically called at startup or when Bluetooth services
**                  are required by the phone.  This function must be called
**                  before calling any other API function.
**
**
** Returns          BTA_SUCCESS if successful.
**                  BTA_FAIL if internal failure.
**
*******************************************************************************/
BTA_API extern tBTA_STATUS BTA_EnableBluetooth(tBTA_DM_SEC_CBACK *p_cback);

/*******************************************************************************
**
** Function         BTA_DisableBluetooth
**
** Description      This function disables BTA and the Bluetooth protocol
**                  stack.  It is called when BTA is no longer being used
**                  by any application in the system.
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern tBTA_STATUS BTA_DisableBluetooth(void);

/*******************************************************************************
**
** Function         BTA_EnableTestMode
**
** Description      Enables bluetooth device under test mode
**
**
** Returns          tBTA_STATUS
**
*******************************************************************************/
BTA_API extern tBTA_STATUS BTA_EnableTestMode(void);

/*******************************************************************************
**
** Function         BTA_DisableTestMode
**
** Description      Disable bluetooth device under test mode
**
**
** Returns          None
**
*******************************************************************************/
BTA_API extern void BTA_DisableTestMode(void);

/*******************************************************************************
**
** Function         BTA_DmIsDeviceUp
**
** Description      This function tests whether the Bluetooth module is up
**                  and ready.  This is a direct execution function that
**                  may lock task scheduling on some platforms.
**
**
** Returns          TRUE if the module is ready.
**                  FALSE if the module is not ready.
**
*******************************************************************************/
BTA_API extern BOOLEAN BTA_DmIsDeviceUp(void);

/*******************************************************************************
**
** Function         BTA_DmSetDeviceName
**
** Description      This function sets the Bluetooth name of the local device.
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmSetDeviceName(char *p_name);

/*******************************************************************************
**
** Function         BTA_DmSetVisibility
**
** Description      This function sets the Bluetooth connectable,discoverable,
**                  pairable and conn paired only modesmodes of the local device.
**                  This controls whether other Bluetooth devices can find and connect to
**                  the local device.
**
**
** Returns          void
**
*******************************************************************************/
#ifdef REVOLUTION
BTA_API extern void BTA_DmSetVisibility(tBTA_DM_DISC disc_mode, tBTA_DM_CONN conn_mode);
#else
BTA_API extern void BTA_DmSetVisibility(tBTA_DM_DISC disc_mode, tBTA_DM_CONN conn_mode, UINT8 pairable_mode, UINT8 conn_filter);
#endif

/*******************************************************************************
**
** Function         BTA_DmSetScanParam
**
** Description      This function sets the parameters for page scan and
**                  inquiry scan.
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmSetScanParam (UINT16 page_scan_interval, UINT16 page_scan_window,
                                  UINT16 inquiry_scan_interval, UINT16 inquiry_scan_window);

/*******************************************************************************
**
** Function         BTA_DmSetAfhChannels
**
** Description      This function sets the AFH first and
**                  last disable channel, so channels within
**                  that range are disabled.
**                  In order to use this API, BTM_BYPASS_AMP_AUTO_AFH must be set
**                  to be TRUE
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmSetAfhChannels(UINT8 first, UINT8 last);


/*******************************************************************************
**
** Function         BTA_DmVendorSpecificCommand
**
** Description      This function sends the vendor specific command
**                  to the controller
**
**
** Returns          tBTA_STATUS
**
*******************************************************************************/
BTA_API extern tBTA_STATUS BTA_DmVendorSpecificCommand (UINT16 opcode, UINT8 param_len,UINT8 *p_param_buf, tBTA_VENDOR_CMPL_CBACK *p_cback);


/*******************************************************************************
**
** Function         BTA_DmSearch
**
** Description      This function searches for peer Bluetooth devices.  It
**                  first performs an inquiry; for each device found from the
**                  inquiry it gets the remote name of the device.  If
**                  parameter services is nonzero, service discovery will be
**                  performed on each device for the services specified.
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmSearch(tBTA_DM_INQ *p_dm_inq, tBTA_SERVICE_MASK services,
                                 tBTA_DM_SEARCH_CBACK *p_cback);

/*******************************************************************************
**
** Function         BTA_DmSearchCancel
**
** Description      This function cancels a search that has been initiated
**                  by calling BTA_DmSearch().
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmSearchCancel(void);

/*******************************************************************************
**
** Function         BTA_DmDiscover
**
** Description      This function performs service discovery for the services
**                  of a particular peer device.
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmDiscover(BD_ADDR bd_addr, tBTA_SERVICE_MASK services,
                                   tBTA_DM_SEARCH_CBACK *p_cback, BOOLEAN sdp_search);

// btla-specific ++
/*******************************************************************************
**
** Function         BTA_DmDiscoverUUID
**
** Description      This function performs service discovery for the services
**                  of a particular peer device.
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmDiscoverUUID(BD_ADDR bd_addr, tSDP_UUID *uuid,
                    tBTA_DM_SEARCH_CBACK *p_cback, BOOLEAN sdp_search);

/*******************************************************************************
**
** Function         BTA_DmGetCachedRemoteName
**
** Description      Retieve cached remote name if available
**
** Returns          BTA_SUCCESS if cached name was retrieved
**                  BTA_FAILURE if cached name is not available
**
*******************************************************************************/
tBTA_STATUS BTA_DmGetCachedRemoteName(BD_ADDR remote_device, UINT8 **pp_cached_name);
// btla-specific --

/*******************************************************************************
**
** Function         BTA_DmIsMaster
**
** Description      This function checks if the local device is the master of
**                  the link to the given device
**
** Returns          TRUE if master.
**                  FALSE if not.
**
*******************************************************************************/
BTA_API extern BOOLEAN BTA_DmIsMaster(BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         BTA_DmBond
**
** Description      This function initiates a bonding procedure with a peer
**                  device.  The bonding procedure enables authentication
**                  and optionally encryption on the Bluetooth link.
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmBond(BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         BTA_DmBondCancel
**
** Description      This function cancels a bonding procedure with a peer
**                  device.
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmBondCancel(BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         BTA_DmPinReply
**
** Description      This function provides a PIN when one is requested by DM
**                  during a bonding procedure.  The application should call
**                  this function after the security callback is called with
**                  a BTA_DM_PIN_REQ_EVT.
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmPinReply(BD_ADDR bd_addr, BOOLEAN accept, UINT8 pin_len,
                                   UINT8 *p_pin);

/*******************************************************************************
**
** Function         BTA_DmLinkPolicy
**
** Description      This function sets/clears the link policy mask to the given
**                  bd_addr.
**                  If clearing the sniff or park mode mask, the link is put
**                  in active mode.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmLinkPolicy(BD_ADDR bd_addr, tBTA_DM_LP_MASK policy_mask,
                                     BOOLEAN set);

#if (BTM_OOB_INCLUDED == TRUE)
/*******************************************************************************
**
** Function         BTA_DmLocalOob
**
** Description      This function retrieves the OOB data from local controller.
**                  The result is reported by bta_dm_co_loc_oob().
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmLocalOob(void);
#endif /* BTM_OOB_INCLUDED */

/*******************************************************************************
**
** Function         BTA_DmConfirm
**
** Description      This function accepts or rejects the numerical value of the
**                  Simple Pairing process on BTA_DM_SP_CFM_REQ_EVT
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmConfirm(BD_ADDR bd_addr, BOOLEAN accept);

/*******************************************************************************
**
** Function         BTA_DmPasskeyCancel
**
** Description      This function is called to cancel the simple pairing process
**                  reported by BTA_DM_SP_KEY_NOTIF_EVT
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmPasskeyCancel(BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         BTA_DmAddDevice
**
** Description      This function adds a device to the security database list
**                  of peer devices. This function would typically be called
**                  at system startup to initialize the security database with
**                  known peer devices.  This is a direct execution function
**                  that may lock task scheduling on some platforms.
**
** Returns          void
**
*******************************************************************************/
#ifdef REVOLUTION
BTA_API extern tBTA_STATUS BTA_DmAddDevice(BD_ADDR bd_addr, LINK_KEY link_key,
                                           tBTA_SERVICE_MASK trusted_mask,
                                           BOOLEAN is_trusted);
#else
BTA_API extern void BTA_DmAddDevice(BD_ADDR bd_addr, DEV_CLASS dev_class,
                                    LINK_KEY link_key, tBTA_SERVICE_MASK trusted_mask,
                                    BOOLEAN is_trusted, UINT8 key_type,
                                    tBTA_IO_CAP io_cap);
#endif

/*******************************************************************************
**
** Function         BTA_DmAddDevWithName
**
** Description      This function is newer version of  BTA_DmAddDevice()
**                  which added bd_name and features as input parameters.
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmAddDevWithName (BD_ADDR bd_addr, DEV_CLASS dev_class,
                                      BD_NAME bd_name, BD_FEATURES features,
                                      LINK_KEY link_key, tBTA_SERVICE_MASK trusted_mask,
                                      BOOLEAN is_trusted, UINT8 key_type, tBTA_IO_CAP io_cap);

/*******************************************************************************
**
** Function         BTA_DmRemoveDevice
**
** Description      This function removes a device from the security database.
**                  This is a direct execution function that may lock task
**                  scheduling on some platforms.
**
**
** Returns          BTA_SUCCESS if successful.
**                  BTA_FAIL if operation failed.
**
*******************************************************************************/
BTA_API extern tBTA_STATUS BTA_DmRemoveDevice(BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         BTA_DmAuthorizeReply
**
** Description      This function provides an authorization reply when
**                  authorization is requested by BTA.  The application calls
**                  this function after the security callback is called with
**                  a BTA_DM_AUTHORIZE_EVT.
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmAuthorizeReply(BD_ADDR bd_addr, tBTA_SERVICE_ID service,
                                         tBTA_AUTH_RESP response);

/*******************************************************************************
**
** Function         BTA_DmSignalStrength
**
** Description      This function initiates RSSI and channnel quality
**                  measurments. BTA_DM_SIG_STRENGTH_EVT is sent to
**                  application with the values of RSSI and channel
**                  quality
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmSignalStrength(tBTA_SIG_STRENGTH_MASK mask, UINT16 period, BOOLEAN start);

/*******************************************************************************
**
** Function         BTA_DmWriteInqTxPower
**
** Description      This command is used to write the inquiry transmit power level
**                  used to transmit the inquiry (ID) data packets.
**
** Parameters       tx_power - tx inquiry power to use, valid value is -70 ~ 20

** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmWriteInqTxPower(INT8 tx_power);

/*******************************************************************************
**
** Function         BTA_DmEirAddUUID
**
** Description      This function is called to add UUID into EIR.
**
** Parameters       tBT_UUID - UUID
**
** Returns          None
**
*******************************************************************************/
BTA_API extern void BTA_DmEirAddUUID (tBT_UUID *p_uuid);

/*******************************************************************************
**
** Function         BTA_DmEirRemoveUUID
**
** Description      This function is called to remove UUID from EIR.
**
** Parameters       tBT_UUID - UUID
**
** Returns          None
**
*******************************************************************************/
BTA_API extern void BTA_DmEirRemoveUUID (tBT_UUID *p_uuid);

/*******************************************************************************
**
** Function         BTA_DmSetEIRConfig
**
** Description      This function is called to override the BTA default EIR parameters.
**                  This funciton is only valid in a system where BTU & App task
**                  are in the same memory space.
**
** Parameters       Pointer to User defined EIR config
**
** Returns          None
**
*******************************************************************************/
BTA_API extern void BTA_DmSetEIRConfig (tBTA_DM_EIR_CONF *p_eir_cfg);

/*******************************************************************************
**
** Function         BTA_CheckEirData
**
** Description      This function is called to get EIR data from significant part.
**
** Parameters       p_eir - pointer of EIR significant part
**                  type   - finding EIR data type
**                  p_length - return the length of EIR data
**
** Returns          pointer of EIR data
**
*******************************************************************************/
BTA_API extern UINT8 *BTA_CheckEirData( UINT8 *p_eir, UINT8 tag, UINT8 *p_length );

/*******************************************************************************
**
** Function         BTA_GetEirService
**
** Description      This function is called to get BTA service mask from EIR.
**
** Parameters       p_eir - pointer of EIR significant part
**                  p_services - return the BTA service mask
**
** Returns          None
**
*******************************************************************************/
BTA_API extern void BTA_GetEirService( UINT8 *p_eir, tBTA_SERVICE_MASK *p_services );

/*******************************************************************************
**
** Function         BTA_DmUseSsr
**
** Description      This function is called to check if the connected peer device
**                  supports SSR or not.
**
** Returns          TRUE, if SSR is supported
**
*******************************************************************************/
BTA_API extern BOOLEAN BTA_DmUseSsr( BD_ADDR bd_addr );


/*******************************************************************************
**
** Function         BTA_DmSetLocalDiRecord
**
** Description      This function adds a DI record to the local SDP database.
**
** Returns          BTA_SUCCESS if record set sucessfully, otherwise error code.
**
*******************************************************************************/
BTA_API extern tBTA_STATUS BTA_DmSetLocalDiRecord( tBTA_DI_RECORD *p_device_info,
	                          UINT32 *p_handle );

/*******************************************************************************
**
** Function         BTA_DmGetLocalDiRecord
**
** Description      Get a specified DI record to the local SDP database. If no
**                  record handle is provided, the primary DI record will be
**                  returned.
**
** Returns          BTA_SUCCESS if record set sucessfully, otherwise error code.
**
*******************************************************************************/
BTA_API extern tBTA_STATUS BTA_DmGetLocalDiRecord( tBTA_DI_GET_RECORD *p_device_info,
	                          UINT32 *p_handle );

/*******************************************************************************
**
** Function         BTA_DmDiDiscover
**
** Description      This function queries a remote device for DI information.
**
** Returns          None.
**
*******************************************************************************/
BTA_API extern void BTA_DmDiDiscover( BD_ADDR remote_device, tBTA_DISCOVERY_DB *p_db,
                       UINT32 len, tBTA_DM_SEARCH_CBACK *p_cback );

/*******************************************************************************
**
** Function         BTA_DmGetDiRecord
**
** Description      This function retrieves a remote device's DI record from
**                  the specified database.
**
** Returns          None.
**
*******************************************************************************/
BTA_API extern tBTA_STATUS BTA_DmGetDiRecord( UINT8 get_record_index, tBTA_DI_GET_RECORD *p_device_info,
                        tBTA_DISCOVERY_DB *p_db );

/*******************************************************************************
**
** Function         BTA_SysFeatures
**
** Description      This function is called to set system features.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_SysFeatures (UINT16 sys_features);

/*******************************************************************************
**
** Function         bta_dmexecutecallback
**
** Description      This function will request BTA to execute a call back in the context of BTU task
**                  This API was named in lower case because it is only intended
**                  for the internal customers(like BTIF).
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_dmexecutecallback (tBTA_DM_EXEC_CBACK* p_callback, void * p_param);

#if (BTM_SCO_HCI_INCLUDED == TRUE)
/*******************************************************************************
**
** Function         BTA_DmPcmInitSamples
**
** Description      initialize the down sample converter.
**
**                  src_sps: original samples per second (source audio data)
**                            (ex. 44100, 48000)
**                  bits: number of bits per pcm sample (16)
**                  n_channels: number of channels (i.e. mono(1), stereo(2)...)
**
** Returns          none
**
*******************************************************************************/
BTA_API extern void BTA_DmPcmInitSamples (UINT32 src_sps, UINT32 bits, UINT32 n_channels);

/**************************************************************************************
** Function         BTA_DmPcmResample
**
** Description      Down sampling utility to convert higher sampling rate into 8K/16bits
**                  PCM samples.
**
** Parameters       p_src: pointer to the buffer where the original sampling PCM
**                              are stored.
**                  in_bytes:  Length of the input PCM sample buffer in byte.
**                  p_dst:      pointer to the buffer which is to be used to store
**                              the converted PCM samples.
**
**
** Returns          INT32: number of samples converted.
**
**************************************************************************************/
BTA_API extern INT32 BTA_DmPcmResample (void *p_src, UINT32 in_bytes, void *p_dst);
#endif

#if ((defined BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
/* BLE related API functions */
/*******************************************************************************
**
** Function         BTA_DmBleSecurityGrant
**
** Description      Grant security request access.
**
** Parameters:      bd_addr          - BD address of the peer
**                  res              - security grant status.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmBleSecurityGrant(BD_ADDR bd_addr, tBTA_DM_BLE_SEC_GRANT res);



/*******************************************************************************
**
** Function         BTA_DmBleSetBgConnType
**
** Description      This function is called to set BLE connectable mode for a
**                  peripheral device.
**
** Parameters       bg_conn_type: it can be auto connection, or selective connection.
**                  p_select_cback: callback function when selective connection procedure
**                              is being used.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmBleSetBgConnType(tBTA_DM_BLE_CONN_TYPE bg_conn_type, tBTA_DM_BLE_SEL_CBACK *p_select_cback);

/*******************************************************************************
**
** Function         BTA_DmBlePasskeyReply
**
** Description      Send BLE SMP passkey reply.
**
** Parameters:      bd_addr          - BD address of the peer
**                  accept           - passkey entry sucessful or declined.
**                  passkey          - passkey value, must be a 6 digit number,
**                                     can be lead by 0.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmBlePasskeyReply(BD_ADDR bd_addr, BOOLEAN accept, UINT32 passkey);

/*******************************************************************************
**
** Function         BTA_DmAddBleDevice
**
** Description      Add a BLE device.  This function will be normally called
**                  during host startup to restore all required information
**                  for a LE device stored in the NVRAM.
**
** Parameters:      bd_addr          - BD address of the peer
**                  dev_type         - Remote device's device type.
**                  addr_type        - LE device address type.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmAddBleDevice(BD_ADDR bd_addr, tBLE_ADDR_TYPE addr_type,
                                       tBT_DEVICE_TYPE dev_type);


/*******************************************************************************
**
** Function         BTA_DmAddBleKey
**
** Description      Add/modify LE device information.  This function will be
**                  normally called during host startup to restore all required
**                  information stored in the NVRAM.
**
** Parameters:      bd_addr          - BD address of the peer
**                  p_le_key         - LE key values.
**                  key_type         - LE SMP key type.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmAddBleKey (BD_ADDR bd_addr, tBTA_LE_KEY_VALUE *p_le_key,
                                     tBTA_LE_KEY_TYPE key_type);

/*******************************************************************************
**
** Function         BTA_DmSetBlePrefConnParams
**
** Description      This function is called to set the preferred connection
**                  parameters when default connection parameter is not desired.
**
** Parameters:      bd_addr          - BD address of the peripheral
**                  min_conn_int     - minimum preferred connection interval
**                  max_conn_int     - maximum preferred connection interval
**                  slave_latency    - preferred slave latency
**                  supervision_tout - preferred supervision timeout
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmSetBlePrefConnParams(BD_ADDR bd_addr,
                               UINT16 min_conn_int, UINT16 max_conn_int,
                               UINT16 slave_latency, UINT16 supervision_tout );

/*******************************************************************************
**
** Function         BTA_DmSetBleConnScanParams
**
** Description      This function is called to set scan parameters used in
**                  BLE connection request
**
** Parameters:      bd_addr          - BD address of the peripheral
**                  scan_interval    - scan interval
**                  scan_window      - scan window
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmSetBleConnScanParams(UINT16 scan_interval,
                                               UINT16 scan_window );

/*******************************************************************************
**
** Function         BTA_DmSearchExt
**
** Description      This function searches for peer Bluetooth devices. It performs
**                  an inquiry and gets the remote name for devices. Service
**                  discovery is done if services is non zero
**
** Parameters       p_dm_inq: inquiry conditions
**                  services: if service is not empty, service discovery will be done.
**                            for all GATT based service condition, put num_uuid, and
**                            p_uuid is the pointer to the list of UUID values.
**                  p_cback: callback functino when search is completed.
**
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmSearchExt(tBTA_DM_INQ *p_dm_inq, tBTA_SERVICE_MASK_EXT *p_services,
                                    tBTA_DM_SEARCH_CBACK *p_cback);

/*******************************************************************************
**
** Function         BTA_DmDiscoverExt
**
** Description      This function does service discovery for services of a
**                  peer device. When services.num_uuid is 0, it indicates all
**                  GATT based services are to be searched; other wise a list of
**                  UUID of interested services should be provided through
**                  services.p_uuid.
**
**
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_DmDiscoverExt(BD_ADDR bd_addr, tBTA_SERVICE_MASK_EXT *p_services,
                                    tBTA_DM_SEARCH_CBACK *p_cback, BOOLEAN sdp_search);


/*******************************************************************************
**
** Function         BTA_DmSetEncryption
**
** Description      This function is called to ensure that connection is
**                  encrypted.  Should be called only on an open connection.
**                  Typically only needed for connections that first want to
**                  bring up unencrypted links, then later encrypt them.
**
** Parameters:      bd_addr       - Address of the peer device
**                  p_callback    - Pointer to callback function to indicat the
**                                  link encryption status
**                  sec_act       - This is the security action to indicate
**                                  what knid of BLE security level is required for
**                                  the BLE link if the BLE is supported
**                                  Note: This parameter is ignored for the BR/EDR link
**                                        or the BLE is not supported
**
** Returns          void
**
**
*******************************************************************************/
BTA_API extern void BTA_DmSetEncryption(BD_ADDR bd_addr, tBTA_DM_ENCRYPT_CBACK *p_callback,
                            tBTA_DM_BLE_SEC_ACT sec_act);

#endif

// btla-specific ++
/*******************************************************************************
**
** Function         BTA_DmSetAfhChannelAssessment
**
** Description      This function is called to set the channel assessment mode on or off
**
** Returns          status
**
*******************************************************************************/
BTA_API extern void BTA_DmSetAfhChannelAssessment (BOOLEAN enable_or_disable);
// btla-specific --

#ifdef __cplusplus
}
#endif

#endif /* BTA_API_H */
