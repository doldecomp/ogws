/******************************************************************************
 *
 *  NOTICE OF CHANGES
 *  2024/03/25:
 *      - Add #defines for RVL target
 * 
 *  Compile with REVOLUTION defined to include these changes.
 * 
 ******************************************************************************/



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

#ifndef BT_TARGET_H
#define BT_TARGET_H

/**
 * Modifications for decomp
 */
#ifdef REVOLUTION

#define HAS_NO_BDROID_BUILDCFG

#define RFCOMM_INCLUDED         TRUE
#define GAP_INCLUDED            TRUE
#define HID_DEV_INCLUDED        TRUE
#define HID_HOST_INCLUDED       TRUE
#define BNEP_INCLUDED           FALSE
#define A2D_INCLUDED            FALSE
#define AVRC_INCLUDED           FALSE

#define BT_USE_TRACES           TRUE

#define BTM_SSR_INCLUDED        FALSE
#define BTM_EIR_SERVER_INCLUDED FALSE

#define BTA_DM_COD              {0x40, 0x02, 0x04}
#define BTA_SYS_TIMER_PERIOD    1000

#endif

#ifndef BUILDCFG
#define BUILDCFG
#endif
#include "data_types.h"


#ifndef BTIF_HSAG_SERVICE_NAME
#define BTIF_HSAG_SERVICE_NAME  ("Headset Gateway")
#endif

#ifndef BTIF_HFAG_SERVICE_NAME
#define BTIF_HFAG_SERVICE_NAME  ("Handsfree Gateway")
#endif


#ifdef BUILDCFG

#if !defined(HAS_BDROID_BUILDCFG) && !defined(HAS_NO_BDROID_BUILDCFG)
#error "An Android.mk file did not include bdroid_CFLAGS and possibly not bdorid_C_INCLUDES"
#endif

#ifdef HAS_BDROID_BUILDCFG
#include "bdroid_buildcfg.h"
#endif

#endif

/* Include common GKI definitions used by this platform */
#include "gki_target.h"

#include "bt_types.h"   /* This must be defined AFTER buildcfg.h */
#include "dyn_mem.h"    /* defines static and/or dynamic memory for components */


//------------------Added from Bluedroid buildcfg.h---------------------
#ifndef UNV_INCLUDED
#define UNV_INCLUDED FALSE
#endif

#ifndef GATT_PTS
#define GATT_PTS FALSE
#endif

#ifndef L2CAP_INCLUDED
#define L2CAP_INCLUDED TRUE
#endif

#ifndef L2CAP_EXTFEA_SUPPORTED_MASK
#define L2CAP_EXTFEA_SUPPORTED_MASK (L2CAP_EXTFEA_ENH_RETRANS | L2CAP_EXTFEA_STREAM_MODE | L2CAP_EXTFEA_NO_CRC | L2CAP_EXTFEA_FIXED_CHNLS)
#endif

#ifndef BTUI_OPS_FORMATS
#define BTUI_OPS_FORMATS (BTA_OP_VCARD21_MASK | BTA_OP_ANY_MASK)
#endif

#ifndef BTA_RFC_MTU_SIZE
#define BTA_RFC_MTU_SIZE (L2CAP_MTU_SIZE-L2CAP_MIN_OFFSET-RFCOMM_DATA_OVERHEAD)
#endif

#ifndef BTA_DUN_MTU
#define BTA_DUN_MTU BTA_RFC_MTU_SIZE
#endif

#ifndef BTA_SPP_MTU
#define BTA_SPP_MTU BTA_RFC_MTU_SIZE
#endif

#ifndef BTA_FAX_MTU
#define BTA_FAX_MTU BTA_RFC_MTU_SIZE
#endif

#ifndef SDP_RAW_PDU_INCLUDED
#define SDP_RAW_PDU_INCLUDED  TRUE
#endif

#ifndef GATTS_APPU_USE_GATT_TRACE
#define GATTS_APPU_USE_GATT_TRACE FALSE
#endif

#ifndef SMP_HOST_ENCRYPT_INCLUDED
#define SMP_HOST_ENCRYPT_INCLUDED FALSE
#endif

#ifndef SAP_INCLUDED
#define SAP_INCLUDED FALSE
#endif

#ifndef SBC_NO_PCM_CPY_OPTION
#define SBC_NO_PCM_CPY_OPTION FALSE
#endif

#ifndef SBC_IPAQ_OPT
#define SBC_IPAQ_OPT FALSE
#endif

#ifndef SBC_IS_64_MULT_IN_QUANTIZER
#define SBC_IS_64_MULT_IN_QUANTIZER FALSE
#endif

#ifndef BTA_INCLUDED
#define BTA_INCLUDED TRUE
#endif

#ifndef BTA_AG_INCLUDED
#define BTA_AG_INCLUDED  TRUE
#endif

#ifndef BTA_CT_INCLUDED
#define BTA_CT_INCLUDED  FALSE
#endif

#ifndef BTA_CG_INCLUDED
#define BTA_CG_INCLUDED  FALSE
#endif

#ifndef BTA_DG_INCLUDED
#define BTA_DG_INCLUDED  FALSE
#endif

#ifndef BTA_FT_INCLUDED
#define BTA_FT_INCLUDED FALSE
#endif

#ifndef BTA_OP_INCLUDED
#define BTA_OP_INCLUDED FALSE
#endif

#ifndef BTA_PR_INCLUDED
#define BTA_PR_INCLUDED FALSE
#endif

#ifndef BTA_SS_INCLUDED
#define BTA_SS_INCLUDED FALSE
#endif

#ifndef BTA_DM_INCLUDED
#define BTA_DM_INCLUDED TRUE
#endif


#ifndef BTA_DI_INCLUDED
#define BTA_DI_INCLUDED FALSE
#endif

#ifndef BTA_BI_INCLUDED
#define BTA_BI_INCLUDED FALSE
#endif

#ifndef BTA_SC_INCLUDED
#define BTA_SC_INCLUDED FALSE
#endif

#ifndef BTA_PAN_INCLUDED
#define BTA_PAN_INCLUDED TRUE
#endif

#ifndef BTA_FS_INCLUDED
#define BTA_FS_INCLUDED TRUE
#endif

#ifndef BTA_AC_INCLUDED
#define BTA_AC_INCLUDED FALSE
#endif

#ifndef BTA_HD_INCLUDED
#define BTA_HD_INCLUDED FALSE
#endif

#ifndef BTA_HH_INCLUDED
#define BTA_HH_INCLUDED TRUE
#endif

#ifndef BTA_HH_ROLE
#define BTA_HH_ROLE BTA_MASTER_ROLE_PREF
#endif

#ifndef BTA_AR_INCLUDED
#define BTA_AR_INCLUDED TRUE
#endif

#ifndef BTA_AV_INCLUDED
#define BTA_AV_INCLUDED TRUE
#endif

#ifndef BTA_AV_VDP_INCLUDED
#define BTA_AV_VDP_INCLUDED FALSE
#endif

#ifndef BTA_AVK_INCLUDED
#define BTA_AVK_INCLUDED FALSE
#endif

#ifndef BTA_PBS_INCLUDED
#define BTA_PBS_INCLUDED FALSE
#endif

#ifndef BTA_PBC_INCLUDED
#define BTA_PBC_INCLUDED FALSE
#endif

#ifndef BTA_FM_INCLUDED
#define BTA_FM_INCLUDED FALSE
#endif

#ifndef BTA_FM_DEBUG
#define BTA_FM_DEBUG FALSE
#endif

#ifndef BTA_FMTX_INCLUDED
#define BTA_FMTX_INCLUDED FALSE
#endif

#ifndef BTA_FMTX_DEBUG
#define BTA_FMTX_DEBUG FALSE
#endif

#ifndef BTA_FMTX_FMRX_SWITCH_WORKAROUND
#define BTA_FMTX_FMRX_SWITCH_WORKAROUND FALSE
#endif

#ifndef BTA_FMTX_US_FCC_RULES
#define BTA_FMTX_US_FCC_RULES FALSE
#endif

#ifndef BTA_HS_INCLUDED
#define BTA_HS_INCLUDED FALSE
#endif

#ifndef BTA_MSE_INCLUDED
#define BTA_MSE_INCLUDED FALSE
#endif

#ifndef BTA_MCE_INCLUDED
#define BTA_MCE_INCLUDED FALSE
#endif

#ifndef BTA_PLAYBACK_INCLUDED
#define BTA_PLAYBACK_INCLUDED FALSE
#endif

#ifndef BTA_SSR_INCLUDED
#define BTA_SSR_INCLUDED FALSE
#endif

#ifndef BTA_JV_INCLUDED
#define BTA_JV_INCLUDED FALSE
#endif

#ifndef BTA_GATT_INCLUDED
#define BTA_GATT_INCLUDED FALSE
#endif

#ifndef BTA_DISABLE_DELAY
#define BTA_DISABLE_DELAY 200 /* in milliseconds */
#endif

#ifndef RPC_TRACE_ONLY
#define RPC_TRACE_ONLY  FALSE
#endif

#ifndef ANDROID_APP_INCLUDED
#define ANDROID_APP_INCLUDED  TRUE
#endif

#ifndef ANDROID_USE_LOGCAT
#define ANDROID_USE_LOGCAT  TRUE
#endif

#ifndef LINUX_GKI_INCLUDED
#define LINUX_GKI_INCLUDED  TRUE
#endif

#ifndef BTA_SYS_TIMER_PERIOD
#define BTA_SYS_TIMER_PERIOD  100
#endif

#ifndef GKI_SHUTDOWN_EVT
#define GKI_SHUTDOWN_EVT  APPL_EVT_7
#endif

#ifndef GKI_PTHREAD_JOINABLE
#define GKI_PTHREAD_JOINABLE  TRUE
#endif

#ifndef LINUX_DRV_INCLUDED
#define LINUX_DRV_INCLUDED  TRUE
#endif

#ifndef LINUX_OS
#define LINUX_OS  TRUE
#endif

#ifndef BTM_APP_DEV_INIT
#define BTM_APP_DEV_INIT  bte_main_post_reset_init
#endif

#ifndef SBC_FOR_EMBEDDED_LINUX
#define SBC_FOR_EMBEDDED_LINUX TRUE
#endif

#ifndef BTA_DM_REMOTE_DEVICE_NAME_LENGTH
#define BTA_DM_REMOTE_DEVICE_NAME_LENGTH 248
#endif

#ifndef AVDT_VERSION
#define AVDT_VERSION  0x0102
#endif

#ifndef BTA_AG_AT_MAX_LEN
#define BTA_AG_AT_MAX_LEN  512
#endif

#ifndef BTA_AVRCP_FF_RW_SUPPORT
#define BTA_AVRCP_FF_RW_SUPPORT TRUE
#endif

#ifndef BTA_AG_SCO_PKT_TYPES
#define BTA_AG_SCO_PKT_TYPES  (BTM_SCO_LINK_ONLY_MASK | BTM_SCO_PKT_TYPES_MASK_EV3 |  BTM_SCO_PKT_TYPES_MASK_NO_3_EV3 | BTM_SCO_PKT_TYPES_MASK_NO_2_EV5 | BTM_SCO_PKT_TYPES_MASK_NO_3_EV5)
#endif

#ifndef BTA_AV_MAX_A2DP_MTU
#define BTA_AV_MAX_A2DP_MTU  668
#endif

#ifndef BTA_AV_RET_TOUT
#define BTA_AV_RET_TOUT 15
#endif

#ifndef PORCHE_PAIRING_CONFLICT
#define PORCHE_PAIRING_CONFLICT  TRUE
#endif

#ifndef BTA_AV_CO_CP_SCMS_T
#define BTA_AV_CO_CP_SCMS_T  FALSE
#endif

#ifndef AVDT_CONNECT_CP_ONLY
#define AVDT_CONNECT_CP_ONLY  FALSE
#endif

#ifndef BT_TRACE_PROTOCOL
#define BT_TRACE_PROTOCOL  TRUE
#endif

#ifndef BT_USE_TRACES
#define BT_USE_TRACES  TRUE
#endif

#ifndef BT_TRACE_BTIF
#define BT_TRACE_BTIF  TRUE
#endif

#ifndef BTTRC_INCLUDED
#define BTTRC_INCLUDED  FALSE
#endif

#ifndef BT_TRACE_VERBOSE
#define BT_TRACE_VERBOSE  FALSE
#endif

#ifndef BTTRC_PARSER_INCLUDED
#define BTTRC_PARSER_INCLUDED  FALSE
#endif

#ifndef MAX_TRACE_RAM_SIZE
#define MAX_TRACE_RAM_SIZE  10000
#endif

#ifndef OBX_INITIAL_TRACE_LEVEL
#define OBX_INITIAL_TRACE_LEVEL  BT_TRACE_LEVEL_ERROR
#endif

#ifndef PBAP_ZERO_VCARD_IN_DB
#define PBAP_ZERO_VCARD_IN_DB  FALSE
#endif

#ifndef BTA_DM_SDP_DB_SIZE
#define BTA_DM_SDP_DB_SIZE  8000
#endif

#ifndef FTS_REJECT_INVALID_OBEX_SET_PATH_REQ
#define FTS_REJECT_INVALID_OBEX_SET_PATH_REQ FALSE
#endif

#ifndef HL_INCLUDED
#define HL_INCLUDED  TRUE
#endif

#ifndef NO_GKI_RUN_RETURN
#define NO_GKI_RUN_RETURN  TRUE
#endif

#ifndef AG_VOICE_SETTINGS
#define AG_VOICE_SETTINGS  HCI_DEFAULT_VOICE_SETTINGS
#endif

#ifndef BTIF_DM_OOB_TEST
#define BTIF_DM_OOB_TEST  TRUE
#endif
//------------------End added from Bluedroid buildcfg.h---------------------



/* #define BYPASS_AVDATATRACE */

/******************************************************************************
**
** Platform-Specific
**
******************************************************************************/

/* API macros for simulator */

#define BTAPI

#ifndef BTE_BSE_WRAPPER
#ifdef  BTE_SIM_APP
#undef  BTAPI
#define BTAPI         __declspec(dllexport)
#endif
#endif

#define BT_API          BTAPI
#define BTU_API         BTAPI
#define A2D_API         BTAPI
#define VDP_API         BTAPI
#define AVDT_API        BTAPI
#define AVCT_API        BTAPI
#define AVRC_API        BTAPI
#define BIP_API         BTAPI
#define BNEP_API        BTAPI
#define BPP_API         BTAPI
#define BTM_API         BTAPI
#define CTP_API         BTAPI
#define DUN_API         BTAPI
#define FTP_API         BTAPI
#define GAP_API         BTAPI
#define GOEP_API        BTAPI
#define HCI_API         BTAPI
#define HCRP_API        BTAPI
#define HID_API         BTAPI
#define HFP_API         BTAPI
#define HSP2_API        BTAPI
#define ICP_API         BTAPI
#define L2C_API         BTAPI
#define OBX_API         BTAPI
#define OPP_API         BTAPI
#define PAN_API         BTAPI
#define RFC_API         BTAPI
#define RPC_API         BTAPI
#define SDP_API         BTAPI
#define SPP_API         BTAPI
#define TCS_API         BTAPI
#define XML_API         BTAPI
#define BTA_API         BTAPI
#define SBC_API         BTAPI
#define MCE_API         BTAPI
#define MCA_API         BTAPI
#define GATT_API        BTAPI
#define SMP_API         BTAPI


/******************************************************************************
**
** GKI Buffer Pools
**
******************************************************************************/

/* Receives HCI events from the lower-layer. */
#ifndef HCI_CMD_POOL_ID
#define HCI_CMD_POOL_ID             GKI_POOL_ID_2
#endif

#ifndef HCI_CMD_POOL_BUF_SIZE
#define HCI_CMD_POOL_BUF_SIZE       GKI_BUF2_SIZE
#endif

/* Receives ACL data packets from thelower-layer. */
#ifndef HCI_ACL_POOL_ID
#define HCI_ACL_POOL_ID             GKI_POOL_ID_3
#endif

#ifndef HCI_ACL_POOL_BUF_SIZE
#define HCI_ACL_POOL_BUF_SIZE       GKI_BUF3_SIZE
#endif

/* Maximum number of buffers available for ACL receive data. */
#ifndef HCI_ACL_BUF_MAX
#define HCI_ACL_BUF_MAX             GKI_BUF3_MAX
#endif

/* Receives SCO data packets from the lower-layer. */
#ifndef HCI_SCO_POOL_ID
#define HCI_SCO_POOL_ID             GKI_POOL_ID_6
#endif

/* Not used. */
#ifndef HCI_DATA_DESCR_POOL_ID
#define HCI_DATA_DESCR_POOL_ID      GKI_POOL_ID_0
#endif

/* Sends SDP data packets. */
#ifndef SDP_POOL_ID
#define SDP_POOL_ID                 3
#endif

/* Sends RFCOMM command packets. */
#ifndef RFCOMM_CMD_POOL_ID
#define RFCOMM_CMD_POOL_ID          GKI_POOL_ID_2
#endif

#ifndef RFCOMM_CMD_POOL_BUF_SIZE
#define RFCOMM_CMD_POOL_BUF_SIZE    GKI_BUF2_SIZE
#endif

/* Sends RFCOMM data packets. */
#ifndef RFCOMM_DATA_POOL_ID
#define RFCOMM_DATA_POOL_ID         GKI_POOL_ID_3
#endif

#ifndef RFCOMM_DATA_POOL_BUF_SIZE
#define RFCOMM_DATA_POOL_BUF_SIZE   GKI_BUF3_SIZE
#endif

/* Sends L2CAP packets to the peer and HCI messages to the controller. */
#ifndef L2CAP_CMD_POOL_ID
#define L2CAP_CMD_POOL_ID           GKI_POOL_ID_2
#endif

/* Sends L2CAP segmented packets in ERTM mode */
#ifndef L2CAP_FCR_TX_POOL_ID
#define L2CAP_FCR_TX_POOL_ID        HCI_ACL_POOL_ID
#endif

/* Receives L2CAP segmented packets in ERTM mode */
#ifndef L2CAP_FCR_RX_POOL_ID
#define L2CAP_FCR_RX_POOL_ID        HCI_ACL_POOL_ID
#endif

/* Used by BTM when it sends HCI commands to the controller. */
#ifndef BTM_CMD_POOL_ID
#define BTM_CMD_POOL_ID             GKI_POOL_ID_2
#endif

/* Sends TCS messages. */
#ifndef TCS_MSG_POOL_ID
#define TCS_MSG_POOL_ID             GKI_POOL_ID_2
#endif

#ifndef OBX_CMD_POOL_SIZE
#define OBX_CMD_POOL_SIZE           GKI_BUF2_SIZE
#endif

#ifndef OBX_LRG_DATA_POOL_SIZE
#define OBX_LRG_DATA_POOL_SIZE      GKI_BUF4_SIZE
#endif

#ifndef OBX_LRG_DATA_POOL_ID
#define OBX_LRG_DATA_POOL_ID        GKI_POOL_ID_4
#endif

/* Used for CTP discovery database. */
#ifndef CTP_SDP_DB_POOL_ID
#define CTP_SDP_DB_POOL_ID          GKI_POOL_ID_3
#endif

/* Used for CTP data exchange feature. */
#ifndef CTP_DATA_EXCHG_POOL_ID
#define CTP_DATA_EXCHG_POOL_ID      GKI_POOL_ID_2
#endif

/* Used to send data to L2CAP. */
#ifndef GAP_DATA_POOL_ID
#define GAP_DATA_POOL_ID            GKI_POOL_ID_3
#endif

/* Used for SPP inquiry and discovery databases. */
#ifndef SPP_DB_POOL_ID
#define SPP_DB_POOL_ID              GKI_POOL_ID_3
#endif

#ifndef SPP_DB_SIZE
#define SPP_DB_SIZE                 GKI_BUF3_SIZE
#endif

/* HCRP protocol and internal commands. */
#ifndef HCRP_CMD_POOL_ID
#define HCRP_CMD_POOL_ID            GKI_POOL_ID_2
#endif

#ifndef HCRP_CMD_POOL_SIZE
#define HCRP_CMD_POOL_SIZE          GKI_BUF2_SIZE
#endif

#ifndef BIP_EVT_POOL_SIZE
#define BIP_EVT_POOL_SIZE           GKI_BUF3_SIZE
#endif

#ifndef BIP_DB_SIZE
#define BIP_DB_SIZE                 GKI_BUF3_SIZE
#endif


/* BNEP data and protocol messages. */
#ifndef BNEP_POOL_ID
#define BNEP_POOL_ID                GKI_POOL_ID_3
#endif

/* RPC pool for temporary trace message buffers. */
#ifndef RPC_SCRATCH_POOL_ID
#define RPC_SCRATCH_POOL_ID         GKI_POOL_ID_2
#endif

/* RPC scratch buffer size (not related to RPC_SCRATCH_POOL_ID) */
#ifndef RPC_SCRATCH_BUF_SIZE
#define RPC_SCRATCH_BUF_SIZE        GKI_BUF3_SIZE
#endif

/* RPC pool for protocol messages */
#ifndef RPC_MSG_POOL_ID
#define RPC_MSG_POOL_ID             GKI_POOL_ID_3
#endif

#ifndef RPC_MSG_POOL_SIZE
#define RPC_MSG_POOL_SIZE           GKI_BUF3_SIZE
#endif

/* AVDTP pool for protocol messages */
#ifndef AVDT_CMD_POOL_ID
#define AVDT_CMD_POOL_ID            GKI_POOL_ID_2
#endif

/* AVDTP pool size for media packets in case of fragmentation */
#ifndef AVDT_DATA_POOL_SIZE
#define AVDT_DATA_POOL_SIZE         GKI_BUF3_SIZE
#endif

#ifndef PAN_POOL_ID
#define PAN_POOL_ID                 GKI_POOL_ID_3
#endif

/* UNV pool for read/write serialization */
#ifndef UNV_MSG_POOL_ID
#define UNV_MSG_POOL_ID             GKI_POOL_ID_2
#endif

#ifndef UNV_MSG_POOL_SIZE
#define UNV_MSG_POOL_SIZE           GKI_BUF2_SIZE
#endif

/* AVCTP pool for protocol messages */
#ifndef AVCT_CMD_POOL_ID
#define AVCT_CMD_POOL_ID            GKI_POOL_ID_1
#endif

#ifndef AVCT_META_CMD_POOL_ID
#define AVCT_META_CMD_POOL_ID       GKI_POOL_ID_2
#endif

/* AVRCP pool for protocol messages */
#ifndef AVRC_CMD_POOL_ID
#define AVRC_CMD_POOL_ID            GKI_POOL_ID_1
#endif

/* AVRCP pool size for protocol messages */
#ifndef AVRC_CMD_POOL_SIZE
#define AVRC_CMD_POOL_SIZE          GKI_BUF1_SIZE
#endif

/* AVRCP Metadata pool for protocol messages */
#ifndef AVRC_META_CMD_POOL_ID
#define AVRC_META_CMD_POOL_ID       GKI_POOL_ID_2
#endif

/* AVRCP Metadata pool size for protocol messages */
#ifndef AVRC_META_CMD_POOL_SIZE
#define AVRC_META_CMD_POOL_SIZE     GKI_BUF2_SIZE
#endif


/* AVRCP buffer size for browsing channel messages */
#ifndef AVRC_BROWSE_POOL_SIZE
#define AVRC_BROWSE_POOL_SIZE     GKI_MAX_BUF_SIZE
#endif

/*  HDP buffer size for the Pulse Oximeter  */
#ifndef BTA_HL_LRG_DATA_POOL_SIZE
#define BTA_HL_LRG_DATA_POOL_SIZE      GKI_BUF7_SIZE
#endif

#ifndef BTA_HL_LRG_DATA_POOL_ID
#define BTA_HL_LRG_DATA_POOL_ID        GKI_POOL_ID_7
#endif

/* GATT Server Database pool ID */
#ifndef GATT_DB_POOL_ID
#define GATT_DB_POOL_ID                 GKI_POOL_ID_8
#endif

/******************************************************************************
**
** Lower Layer Interface
**
******************************************************************************/

/* Sends ACL data received over HCI to the upper stack. */
#ifndef HCI_ACL_DATA_TO_UPPER
#define HCI_ACL_DATA_TO_UPPER(p)    {((BT_HDR *)p)->event = BT_EVT_TO_BTU_HCI_ACL; GKI_send_msg (BTU_TASK, BTU_HCI_RCV_MBOX, p);}
#endif

/* Sends SCO data received over HCI to the upper stack. */
#ifndef HCI_SCO_DATA_TO_UPPER
#define HCI_SCO_DATA_TO_UPPER(p)    {((BT_HDR *)p)->event = BT_EVT_TO_BTU_HCI_SCO; GKI_send_msg (BTU_TASK, BTU_HCI_RCV_MBOX, p);}
#endif

/* Sends an HCI event received over HCI to theupper stack. */
#ifndef HCI_EVT_TO_UPPER
#define HCI_EVT_TO_UPPER(p)         {((BT_HDR *)p)->event = BT_EVT_TO_BTU_HCI_EVT; GKI_send_msg (BTU_TASK, BTU_HCI_RCV_MBOX, p);}
#endif

/* Macro for allocating buffer for HCI commands */
#ifndef HCI_GET_CMD_BUF
#if (!defined(HCI_USE_VARIABLE_SIZE_CMD_BUF) || (HCI_USE_VARIABLE_SIZE_CMD_BUF == FALSE))
/* Allocate fixed-size buffer from HCI_CMD_POOL (default case) */
#define HCI_GET_CMD_BUF(paramlen)    ((BT_HDR *)GKI_getpoolbuf (HCI_CMD_POOL_ID))
#else
/* Allocate smallest possible buffer (for platforms with limited RAM) */
#define HCI_GET_CMD_BUF(paramlen)    ((BT_HDR *)GKI_getbuf ((UINT16)(BT_HDR_SIZE + HCIC_PREAMBLE_SIZE + (paramlen))))
#endif
#endif  /* HCI_GET_CMD_BUF */

/******************************************************************************
**
** HCI Services (H4)
**
******************************************************************************/
#ifndef HCISU_H4_INCLUDED
#define HCISU_H4_INCLUDED               TRUE
#endif

#ifdef __cplusplus
extern "C" {
#endif

BT_API extern void bte_main_hci_send (BT_HDR *p_msg, UINT16 event);
#if (HCISU_H4_INCLUDED == TRUE)
BT_API extern void bte_main_lpm_allow_bt_device_sleep(void);
#endif

#ifdef __cplusplus
}
#endif

/* Sends ACL data received from the upper stack to the BD/EDR HCI transport. */
#ifndef HCI_ACL_DATA_TO_LOWER
#define HCI_ACL_DATA_TO_LOWER(p)    bte_main_hci_send((BT_HDR *)(p), BT_EVT_TO_LM_HCI_ACL);
#endif

#ifndef HCI_BLE_ACL_DATA_TO_LOWER
#define HCI_BLE_ACL_DATA_TO_LOWER(p)    bte_main_hci_send((BT_HDR *)(p), (UINT16)(BT_EVT_TO_LM_HCI_ACL|LOCAL_BLE_CONTROLLER_ID));
#endif

/* Sends SCO data received from the upper stack to the HCI transport. */
#ifndef HCI_SCO_DATA_TO_LOWER
#define HCI_SCO_DATA_TO_LOWER(p)    bte_main_hci_send((BT_HDR *)(p), BT_EVT_TO_LM_HCI_SCO);
#endif

/* Sends an HCI command received from the upper stack to the BD/EDR HCI transport. */
#ifndef HCI_CMD_TO_LOWER
#define HCI_CMD_TO_LOWER(p)         bte_main_hci_send((BT_HDR *)(p), BT_EVT_TO_LM_HCI_CMD);
#endif

/* Sends an LM Diagnosic command received from the upper stack to the HCI transport. */
#ifndef HCI_LM_DIAG_TO_LOWER
#define HCI_LM_DIAG_TO_LOWER(p)     bte_main_hci_send((BT_HDR *)(p), BT_EVT_TO_LM_DIAG);
#endif

/* Send HCISU a message to allow BT sleep */
#ifndef HCI_LP_ALLOW_BT_DEVICE_SLEEP
#define HCI_LP_ALLOW_BT_DEVICE_SLEEP()       bte_main_lpm_allow_bt_device_sleep()
#endif

/* If nonzero, the upper-layer sends at most this number of HCI commands to the lower-layer. */
#ifndef HCI_MAX_SIMUL_CMDS
#define HCI_MAX_SIMUL_CMDS          0
#endif

/* Timeout for receiving response to HCI command */
#ifndef BTU_CMD_CMPL_TIMEOUT
#define BTU_CMD_CMPL_TIMEOUT        8
#endif

/* If TRUE, BTU task will check HCISU again when HCI command timer expires */
#ifndef BTU_CMD_CMPL_TOUT_DOUBLE_CHECK
#define BTU_CMD_CMPL_TOUT_DOUBLE_CHECK      FALSE
#endif

/* Use 2 second for low-resolution systems, override to 1 for high-resolution systems */
#ifndef BT_1SEC_TIMEOUT
#define BT_1SEC_TIMEOUT             (2)
#endif

/* Quick Timer */
/* if L2CAP_FCR_INCLUDED is TRUE then it should have 100 millisecond resolution */
/* if none of them is included then QUICK_TIMER_TICKS_PER_SEC is set to 0 to exclude quick timer */
#ifndef QUICK_TIMER_TICKS_PER_SEC
#define QUICK_TIMER_TICKS_PER_SEC   10       /* 10ms timer */
#endif

/******************************************************************************
**
** BTM
**
******************************************************************************/
/* if set to TRUE, stack will automatically send an HCI reset at start-up. To be
set to FALSE for advanced start-up / shut-down procedures using USER_HW_ENABLE_API
and USER_HW_DISABLE_API macros */
#ifndef BTM_AUTOMATIC_HCI_RESET
#define BTM_AUTOMATIC_HCI_RESET      FALSE
#endif

/* Include BTM Discovery database and code. */
#ifndef BTM_DISCOVERY_INCLUDED
#define BTM_DISCOVERY_INCLUDED      TRUE
#endif

/* Include inquiry code. */
#ifndef BTM_INQUIRY_INCLUDED
#define BTM_INQUIRY_INCLUDED        TRUE
#endif

/* Cancel Inquiry on incoming SSP */
#ifndef BTM_NO_SSP_ON_INQUIRY
#define BTM_NO_SSP_ON_INQUIRY       FALSE
#endif

/* Include periodic inquiry code (used when BTM_INQUIRY_INCLUDED is TRUE). */
#ifndef BTM_PERIODIC_INQ_INCLUDED
#define BTM_PERIODIC_INQ_INCLUDED   TRUE
#endif

/* Include security authorization code */
#ifndef BTM_AUTHORIZATION_INCLUDED
#define BTM_AUTHORIZATION_INCLUDED  TRUE
#endif

/* Includes SCO if TRUE */
#ifndef BTM_SCO_INCLUDED
#define BTM_SCO_INCLUDED            TRUE       /* TRUE includes SCO code */
#endif

/* Includes SCO if TRUE */
#ifndef BTM_SCO_HCI_INCLUDED
#define BTM_SCO_HCI_INCLUDED            FALSE       /* TRUE includes SCO over HCI code */
#endif

/* Includes WBS if TRUE */
#ifndef BTM_WBS_INCLUDED
#define BTM_WBS_INCLUDED            FALSE       /* TRUE includes WBS code */
#endif

/* Includes PCM2 support if TRUE */
#ifndef BTM_PCM2_INCLUDED
#define BTM_PCM2_INCLUDED           FALSE
#endif

/*  This is used to work around a controller bug that doesn't like Disconnect
**  issued while there is a role switch in progress
*/
#ifndef BTM_DISC_DURING_RS
#define BTM_DISC_DURING_RS TRUE
#endif

/**************************
** Initial SCO TX credit
*************************/
/* max TX SCO data packet size */
#ifndef BTM_SCO_DATA_SIZE_MAX
#define BTM_SCO_DATA_SIZE_MAX       240
#endif

/* maximum BTM buffering capacity */
#ifndef BTM_SCO_MAX_BUF_CAP
#define BTM_SCO_MAX_BUF_CAP     (BTM_SCO_INIT_XMIT_CREDIT * 4)
#endif

/* The size in bytes of the BTM inquiry database. */
#ifndef BTM_INQ_DB_SIZE
#define BTM_INQ_DB_SIZE             40
#endif

/* This is set to enable automatic periodic inquiry at startup. */
#ifndef BTM_ENABLE_AUTO_INQUIRY
#define BTM_ENABLE_AUTO_INQUIRY     FALSE
#endif

/* This is set to always try to acquire the remote device name. */
#ifndef BTM_INQ_GET_REMOTE_NAME
#define BTM_INQ_GET_REMOTE_NAME     FALSE
#endif

/* The inquiry duration in 1.28 second units when auto inquiry is enabled. */
#ifndef BTM_DEFAULT_INQ_DUR
#define BTM_DEFAULT_INQ_DUR         5
#endif

/* The inquiry mode when auto inquiry is enabled. */
#ifndef BTM_DEFAULT_INQ_MODE
#define BTM_DEFAULT_INQ_MODE        BTM_GENERAL_INQUIRY
#endif

/* The default periodic inquiry maximum delay when auto inquiry is enabled, in 1.28 second units. */
#ifndef BTM_DEFAULT_INQ_MAX_DELAY
#define BTM_DEFAULT_INQ_MAX_DELAY   30
#endif

/* The default periodic inquiry minimum delay when auto inquiry is enabled, in 1.28 second units. */
#ifndef BTM_DEFAULT_INQ_MIN_DELAY
#define BTM_DEFAULT_INQ_MIN_DELAY   20
#endif

/* The maximum age of entries in inquiry database in seconds ('0' disables feature). */
#ifndef BTM_INQ_MAX_AGE
#define BTM_INQ_MAX_AGE             0
#endif

/* The maximum age of entries in inquiry database based on inquiry response failure ('0' disables feature). */
#ifndef BTM_INQ_AGE_BY_COUNT
#define BTM_INQ_AGE_BY_COUNT        0
#endif

/* TRUE if controller does not support inquiry event filtering. */
#ifndef BTM_BYPASS_EVENT_FILTERING
#define BTM_BYPASS_EVENT_FILTERING  FALSE
#endif

/* TRUE if inquiry filtering is desired from BTM. */
#ifndef BTM_USE_INQ_RESULTS_FILTER
#define BTM_USE_INQ_RESULTS_FILTER  TRUE
#endif

/* The default scan mode */
#ifndef BTM_DEFAULT_SCAN_TYPE
#define BTM_DEFAULT_SCAN_TYPE       BTM_SCAN_TYPE_INTERLACED
#endif

/* Should connections to unknown devices be allowed when not discoverable? */
#ifndef BTM_ALLOW_CONN_IF_NONDISCOVER
#define BTM_ALLOW_CONN_IF_NONDISCOVER   TRUE
#endif

/* When connectable mode is set to TRUE, the device will respond to paging. */
#ifndef BTM_IS_CONNECTABLE
#define BTM_IS_CONNECTABLE          FALSE
#endif

/* Sets the Page_Scan_Window:  the length of time that the device is performing a page scan. */
#ifndef BTM_DEFAULT_CONN_WINDOW
#define BTM_DEFAULT_CONN_WINDOW     0x0012
#endif

/* Sets the Page_Scan_Activity:  the interval between the start of two consecutive page scans. */
#ifndef BTM_DEFAULT_CONN_INTERVAL
#define BTM_DEFAULT_CONN_INTERVAL   0x0800
#endif

/* This is set to automatically perform inquiry scan on startup. */
#ifndef BTM_IS_DISCOVERABLE
#define BTM_IS_DISCOVERABLE         FALSE
#endif

/* When automatic inquiry scan is enabled, this sets the discovery mode. */
#ifndef BTM_DEFAULT_DISC_MODE
#define BTM_DEFAULT_DISC_MODE       BTM_GENERAL_DISCOVERABLE
#endif

/* When automatic inquiry scan is enabled, this sets the inquiry scan window. */
#ifndef BTM_DEFAULT_DISC_WINDOW
#define BTM_DEFAULT_DISC_WINDOW     0x0012
#endif

/* When automatic inquiry scan is enabled, this sets the inquiry scan interval. */
#ifndef BTM_DEFAULT_DISC_INTERVAL
#define BTM_DEFAULT_DISC_INTERVAL   0x0800
#endif

/* Sets the period, in seconds, to automatically perform service discovery. */
#ifndef BTM_AUTO_DISCOVERY_PERIOD
#define BTM_AUTO_DISCOVERY_PERIOD   0
#endif

/* The size in bytes of the BTM discovery database (if discovery is included). */
#ifndef BTM_DISCOVERY_DB_SIZE
#define BTM_DISCOVERY_DB_SIZE       4000
#endif

/* Number of milliseconds to delay BTU task startup upon device initialization. */
#ifndef BTU_STARTUP_DELAY
#define BTU_STARTUP_DELAY           0
#endif

/* Whether BTA is included in BTU task. */
#ifndef BTU_BTA_INCLUDED
#define BTU_BTA_INCLUDED            TRUE
#endif

/* Number of seconds to wait to send an HCI Reset command upon device initialization. */
#ifndef BTM_FIRST_RESET_DELAY
#define BTM_FIRST_RESET_DELAY       0
#endif

/* The number of seconds to wait for controller module to reset after issuing an HCI Reset command. */
#ifndef BTM_AFTER_RESET_TIMEOUT
#define BTM_AFTER_RESET_TIMEOUT     0
#endif

/* Default class of device
* {SERVICE_CLASS, MAJOR_CLASS, MINOR_CLASS}
*
* SERVICE_CLASS:0x5A (Bit17 -Networking,Bit19 - Capturing,Bit20 -Object Transfer,Bit22 -Telephony)
* MAJOR_CLASS:0x02 - PHONE
* MINOR_CLASS:0x0C - SMART_PHONE
*
*/
#ifndef BTA_DM_COD
#define BTA_DM_COD {0x5A, 0x02, 0x0C}
#endif

/* The number of SCO links. */
#ifndef BTM_MAX_SCO_LINKS
#define BTM_MAX_SCO_LINKS           2
#endif

/* The preferred type of SCO links (2-eSCO, 0-SCO). */
#ifndef BTM_DEFAULT_SCO_MODE
#define BTM_DEFAULT_SCO_MODE        2
#endif

/* The number of security records for peer devices. */
#ifndef BTM_SEC_MAX_DEVICE_RECORDS
#define BTM_SEC_MAX_DEVICE_RECORDS  100
#endif

/* The number of security records for services. */
#ifndef BTM_SEC_MAX_SERVICE_RECORDS
#define BTM_SEC_MAX_SERVICE_RECORDS 32
#endif

/* If True, force a retrieval of remote device name for each bond in case it's changed */
#ifndef BTM_SEC_FORCE_RNR_FOR_DBOND
#define BTM_SEC_FORCE_RNR_FOR_DBOND  FALSE
#endif

/* Maximum device name length used in btm database. */
#ifndef BTM_MAX_REM_BD_NAME_LEN
#define BTM_MAX_REM_BD_NAME_LEN     248
#endif

/* Maximum local device name length stored btm database.
  '0' disables storage of the local name in BTM */
#ifndef BTM_MAX_LOC_BD_NAME_LEN
#define BTM_MAX_LOC_BD_NAME_LEN     248
#endif

/* TRUE if default string is used, FALSE if device name is set in the application */
#ifndef BTM_USE_DEF_LOCAL_NAME
#define BTM_USE_DEF_LOCAL_NAME      TRUE
#endif

/* Fixed Default String (Ignored if BTM_USE_DEF_LOCAL_NAME is FALSE) */
#ifndef BTM_DEF_LOCAL_NAME
#define BTM_DEF_LOCAL_NAME      ""
#endif

/* Maximum service name stored with security authorization (0 if not needed) */
#ifndef BTM_SEC_SERVICE_NAME_LEN
#define BTM_SEC_SERVICE_NAME_LEN    BT_MAX_SERVICE_NAME_LEN
#endif

/* Maximum number of pending security callback */
#ifndef BTM_SEC_MAX_CALLBACKS
#define BTM_SEC_MAX_CALLBACKS       7
#endif

/* Maximum length of the service name. */
#ifndef BT_MAX_SERVICE_NAME_LEN
#define BT_MAX_SERVICE_NAME_LEN     21
#endif

/* ACL buffer size in HCI Host Buffer Size command. */
#ifndef BTM_ACL_BUF_SIZE
#define BTM_ACL_BUF_SIZE            0
#endif

/* This is set to use the BTM power manager. */
#ifndef BTM_PWR_MGR_INCLUDED
#define BTM_PWR_MGR_INCLUDED        TRUE
#endif

/* The maximum number of clients that can register with the power manager. */
#ifndef BTM_MAX_PM_RECORDS
#define BTM_MAX_PM_RECORDS          2
#endif

/* This is set to show debug trace messages for the power manager. */
#ifndef BTM_PM_DEBUG
#define BTM_PM_DEBUG                FALSE
#endif

/* This is set to TRUE if link is to be unparked due to BTM_CreateSCO API. */
#ifndef BTM_SCO_WAKE_PARKED_LINK
#define BTM_SCO_WAKE_PARKED_LINK    TRUE
#endif

/* May be set to the the name of a function used for vendor specific chip initialization */
#ifndef BTM_APP_DEV_INIT
/* #define BTM_APP_DEV_INIT         myInitFunction() */
#endif

/* This is set to TRUE if the busy level change event is desired. (replace ACL change event) */
#ifndef BTM_BUSY_LEVEL_CHANGE_INCLUDED
#define BTM_BUSY_LEVEL_CHANGE_INCLUDED  TRUE
#endif

/* If the user does not respond to security process requests within this many seconds,
 * a negative response would be sent automatically.
 * It's recommended to use a value between 30 and OBX_TIMEOUT_VALUE
 * 30 is LMP response timeout value */
#ifndef BTM_SEC_TIMEOUT_VALUE
#define BTM_SEC_TIMEOUT_VALUE           35
#endif

/* Maximum number of callbacks that can be registered using BTM_RegisterForVSEvents */
#ifndef BTM_MAX_VSE_CALLBACKS
#define BTM_MAX_VSE_CALLBACKS           3
#endif

/* Number of streams for dual stack */
#ifndef BTM_SYNC_INFO_NUM_STR
#define BTM_SYNC_INFO_NUM_STR           2
#endif

/* Number of streams for dual stack in BT Controller */
#ifndef BTM_SYNC_INFO_NUM_STR_BTC
#define BTM_SYNC_INFO_NUM_STR_BTC       2
#endif

/******************************************
**    Lisbon Features
*******************************************/
/* This is set to TRUE if the server Extended Inquiry Response feature is desired. */
/* server sends EIR to client */
#ifndef BTM_EIR_SERVER_INCLUDED
#define BTM_EIR_SERVER_INCLUDED         TRUE
#endif

/* This is set to TRUE if the client Extended Inquiry Response feature is desired. */
/* client inquiry to server */
#ifndef BTM_EIR_CLIENT_INCLUDED
#define BTM_EIR_CLIENT_INCLUDED         TRUE
#endif

/* This is set to TRUE if the FEC is required for EIR packet. */
#ifndef BTM_EIR_DEFAULT_FEC_REQUIRED
#define BTM_EIR_DEFAULT_FEC_REQUIRED    TRUE
#endif

/* User defined UUID look up table */
#ifndef BTM_EIR_UUID_LKUP_TBL
#endif

/* The IO capability of the local device (for Simple Pairing) */
#ifndef BTM_LOCAL_IO_CAPS
#define BTM_LOCAL_IO_CAPS               BTM_IO_CAP_IO
#endif

/* The default MITM Protection Requirement (for Simple Pairing)
 * Possible values are BTM_AUTH_SP_YES or BTM_AUTH_SP_NO */
#ifndef BTM_DEFAULT_AUTH_REQ
#define BTM_DEFAULT_AUTH_REQ            BTM_AUTH_SP_NO
#endif

/* The default MITM Protection Requirement for dedicated bonding using Simple Pairing
 * Possible values are BTM_AUTH_AP_YES or BTM_AUTH_AP_NO */
#ifndef BTM_DEFAULT_DD_AUTH_REQ
#define BTM_DEFAULT_DD_AUTH_REQ            BTM_AUTH_AP_YES
#endif

/* Include Out-of-Band implementation for Simple Pairing */
#ifndef BTM_OOB_INCLUDED
#define BTM_OOB_INCLUDED                TRUE
#endif

/* TRUE to include Sniff Subrating */
#ifndef BTM_SSR_INCLUDED
#define BTM_SSR_INCLUDED                TRUE
#endif

/*************************
** End of Lisbon Features
**************************/

/* Used for conformance testing ONLY */
#ifndef BTM_BLE_CONFORMANCE_TESTING
#define BTM_BLE_CONFORMANCE_TESTING           FALSE
#endif


/******************************************************************************
**
** L2CAP
**
******************************************************************************/

/* Flow control and retransmission mode */

#ifndef L2CAP_FCR_INCLUDED
#define L2CAP_FCR_INCLUDED TRUE
#endif

/* The maximum number of simultaneous links that L2CAP can support. */
#ifndef MAX_ACL_CONNECTIONS
#define MAX_L2CAP_LINKS             7
#else
#define MAX_L2CAP_LINKS             MAX_ACL_CONNECTIONS
#endif

/* The maximum number of simultaneous channels that L2CAP can support. */
#ifndef MAX_L2CAP_CHANNELS
#define MAX_L2CAP_CHANNELS          10
#endif

/* The maximum number of simultaneous applications that can register with L2CAP. */
#ifndef MAX_L2CAP_CLIENTS
#define MAX_L2CAP_CLIENTS           15
#endif

/* The number of seconds of link inactivity before a link is disconnected. */
#ifndef L2CAP_LINK_INACTIVITY_TOUT
#define L2CAP_LINK_INACTIVITY_TOUT  4
#endif

/* The number of seconds of link inactivity after bonding before a link is disconnected. */
#ifndef L2CAP_BONDING_TIMEOUT
#define L2CAP_BONDING_TIMEOUT       3
#endif

/* The time from the HCI connection complete to disconnect if no channel is established. */
#ifndef L2CAP_LINK_STARTUP_TOUT
#define L2CAP_LINK_STARTUP_TOUT     60
#endif

/* The L2CAP MTU; must be in accord with the HCI ACL pool size. */
#ifndef L2CAP_MTU_SIZE
#define L2CAP_MTU_SIZE              1691
#endif

/* The L2CAP MPS over Bluetooth; must be in accord with the FCR tx pool size and ACL down buffer size. */
#ifndef L2CAP_MPS_OVER_BR_EDR
#define L2CAP_MPS_OVER_BR_EDR       1010
#endif

/* This is set to enable host flow control. */
#ifndef L2CAP_HOST_FLOW_CTRL
#define L2CAP_HOST_FLOW_CTRL        FALSE
#endif

/* If host flow control enabled, this is the number of buffers the controller can have unacknowledged. */
#ifndef L2CAP_HOST_FC_ACL_BUFS
#define L2CAP_HOST_FC_ACL_BUFS      20
#endif

/* The percentage of the queue size allowed before a congestion event is sent to the L2CAP client (typically 120%). */
#ifndef L2CAP_FWD_CONG_THRESH
#define L2CAP_FWD_CONG_THRESH       120
#endif

/* This is set to enable L2CAP to  take the ACL link out of park mode when ACL data is to be sent. */
#ifndef L2CAP_WAKE_PARKED_LINK
#define L2CAP_WAKE_PARKED_LINK      TRUE
#endif

/* Whether link wants to be the master or the slave. */
#ifndef L2CAP_DESIRED_LINK_ROLE
#define L2CAP_DESIRED_LINK_ROLE     HCI_ROLE_SLAVE
#endif

/* Include Non-Flushable Packet Boundary Flag feature of Lisbon */
#ifndef L2CAP_NON_FLUSHABLE_PB_INCLUDED
#define L2CAP_NON_FLUSHABLE_PB_INCLUDED     TRUE
#endif

/* Minimum number of ACL credit for high priority link */
#ifndef L2CAP_HIGH_PRI_MIN_XMIT_QUOTA
#define L2CAP_HIGH_PRI_MIN_XMIT_QUOTA       4
#endif

/* used for monitoring HCI ACL credit management */
#ifndef L2CAP_HCI_FLOW_CONTROL_DEBUG
#define L2CAP_HCI_FLOW_CONTROL_DEBUG        TRUE
#endif

/* Used for calculating transmit buffers off of */
#ifndef L2CAP_NUM_XMIT_BUFFS
#define L2CAP_NUM_XMIT_BUFFS                HCI_ACL_BUF_MAX
#endif

/* Unicast Connectionless Data */
#ifndef L2CAP_UCD_INCLUDED
#define L2CAP_UCD_INCLUDED                  FALSE
#endif

/* Unicast Connectionless Data MTU */
#ifndef L2CAP_UCD_MTU
#define L2CAP_UCD_MTU                       L2CAP_MTU_SIZE
#endif

/* Unicast Connectionless Data Idle Timeout */
#ifndef L2CAP_UCD_IDLE_TIMEOUT
#define L2CAP_UCD_IDLE_TIMEOUT              2
#endif

/* Unicast Connectionless Data Idle Timeout */
#ifndef L2CAP_UCD_CH_PRIORITY
#define L2CAP_UCD_CH_PRIORITY               L2CAP_CHNL_PRIORITY_MEDIUM
#endif

/* Max clients on Unicast Connectionless Data */
#ifndef L2CAP_MAX_UCD_CLIENTS
#define L2CAP_MAX_UCD_CLIENTS               5
#endif

/* Used for features using fixed channels; set to zero if no fixed channels supported (BLE, etc.) */
/* Excluding L2CAP signaling channel and UCD */
#ifndef L2CAP_NUM_FIXED_CHNLS
#define L2CAP_NUM_FIXED_CHNLS               4
#endif

/* First fixed channel supported */
#ifndef L2CAP_FIRST_FIXED_CHNL
#define L2CAP_FIRST_FIXED_CHNL              3
#endif

#ifndef L2CAP_LAST_FIXED_CHNL
#define L2CAP_LAST_FIXED_CHNL           (L2CAP_FIRST_FIXED_CHNL + L2CAP_NUM_FIXED_CHNLS - 1)
#endif

/* Round Robin service channels in link */
#ifndef L2CAP_ROUND_ROBIN_CHANNEL_SERVICE
#define L2CAP_ROUND_ROBIN_CHANNEL_SERVICE   TRUE
#endif

/* Used for calculating transmit buffers off of */
#ifndef L2CAP_NUM_XMIT_BUFFS
#define L2CAP_NUM_XMIT_BUFFS                HCI_ACL_BUF_MAX
#endif

/* Used for features using fixed channels; set to zero if no fixed channels supported (BLE, etc.) */
#ifndef L2CAP_NUM_FIXED_CHNLS
#define L2CAP_NUM_FIXED_CHNLS               1
#endif

/* First fixed channel supported */
#ifndef L2CAP_FIRST_FIXED_CHNL
#define L2CAP_FIRST_FIXED_CHNL              3
#endif

#ifndef L2CAP_LAST_FIXED_CHNL
#define L2CAP_LAST_FIXED_CHNL           (L2CAP_FIRST_FIXED_CHNL + L2CAP_NUM_FIXED_CHNLS - 1)
#endif

/* used for monitoring eL2CAP data flow */
#ifndef L2CAP_ERTM_STATS
#define L2CAP_ERTM_STATS                    FALSE
#endif

/* USED FOR FCR TEST ONLY:  When TRUE generates bad tx and rx packets */
#ifndef L2CAP_CORRUPT_ERTM_PKTS
#define L2CAP_CORRUPT_ERTM_PKTS             FALSE
#endif

/* Used for conformance testing ONLY:  When TRUE lets scriptwrapper overwrite info response */
#ifndef L2CAP_CONFORMANCE_TESTING
#define L2CAP_CONFORMANCE_TESTING           FALSE
#endif


#ifndef TIMER_PARAM_TYPE
#ifdef  WIN2000
#define TIMER_PARAM_TYPE    void *
#else
#define TIMER_PARAM_TYPE    UINT32
#endif
#endif

/******************************************************************************
**
** BLE
**
******************************************************************************/

#ifndef BLE_INCLUDED
#define BLE_INCLUDED            FALSE
#endif

#ifndef LOCAL_BLE_CONTROLLER_ID
#define LOCAL_BLE_CONTROLLER_ID         (1)
#endif

/******************************************************************************
**
** ATT/GATT Protocol/Profile Settings
**
******************************************************************************/
#ifndef ATT_INCLUDED
#define ATT_INCLUDED         FALSE
#endif

#ifndef ATT_DEBUG
#define ATT_DEBUG           FALSE
#endif

#ifndef GATT_SERVER_ENABLED
#define GATT_SERVER_ENABLED          FALSE
#endif

#ifndef GATT_CLIENT_ENABLED
#define GATT_CLIENT_ENABLED          FALSE
#endif

#ifndef GATT_MAX_SR_PROFILES
#define GATT_MAX_SR_PROFILES        32 /* max is 32 */
#endif

#ifndef GATT_MAX_APPS
#define GATT_MAX_APPS            10 /* note: 2 apps used internally GATT and GAP */
#endif

#ifndef GATT_MAX_CL_PROFILES
#define GATT_MAX_CL_PROFILES        4
#endif

#ifndef GATT_MAX_PHY_CHANNEL
#define GATT_MAX_PHY_CHANNEL        4
#endif

/* Used for conformance testing ONLY */
#ifndef GATT_CONFORMANCE_TESTING
#define GATT_CONFORMANCE_TESTING           FALSE
#endif

/* number of background connection device allowence, ideally to be the same as WL size
*/
#ifndef GATT_MAX_BG_CONN_DEV
#define GATT_MAX_BG_CONN_DEV        32
#endif

/******************************************************************************
**
** SMP
**
******************************************************************************/
#ifndef SMP_INCLUDED
#define SMP_INCLUDED         FALSE
#endif

#ifndef SMP_DEBUG
#define SMP_DEBUG            FALSE
#endif

#ifndef SMP_DEFAULT_AUTH_REQ
#define SMP_DEFAULT_AUTH_REQ    SMP_AUTH_NB_ENC_ONLY
#endif

#ifndef SMP_MAX_ENC_KEY_SIZE
#define SMP_MAX_ENC_KEY_SIZE    16
#endif

#ifndef SMP_MIN_ENC_KEY_SIZE
#define SMP_MIN_ENC_KEY_SIZE    7
#endif

/* Used for conformance testing ONLY */
#ifndef SMP_CONFORMANCE_TESTING
#define SMP_CONFORMANCE_TESTING           FALSE
#endif

/******************************************************************************
**
** SDP
**
******************************************************************************/

/* This is set to enable SDP server functionality. */
#ifndef SDP_SERVER_ENABLED
#define SDP_SERVER_ENABLED          TRUE
#endif

/* The maximum number of SDP records the server can support. */
#ifndef SDP_MAX_RECORDS
#define SDP_MAX_RECORDS             20
#endif

/* The maximum number of attributes in each record. */
#ifndef SDP_MAX_REC_ATTR
//#if defined(HID_DEV_INCLUDED) && (HID_DEV_INCLUDED==TRUE)
#define SDP_MAX_REC_ATTR            25
//#else
//#define SDP_MAX_REC_ATTR            13
//#endif
#endif

#ifndef SDP_MAX_PAD_LEN
#define SDP_MAX_PAD_LEN             600
#endif

/* The maximum length, in bytes, of an attribute. */
#ifndef SDP_MAX_ATTR_LEN
//#if defined(HID_DEV_INCLUDED) && (HID_DEV_INCLUDED==TRUE)
//#define SDP_MAX_ATTR_LEN            80
//#else
//#define SDP_MAX_ATTR_LEN            100
//#endif
#define SDP_MAX_ATTR_LEN            400
#endif

/* The maximum number of attribute filters supported by SDP databases. */
#ifndef SDP_MAX_ATTR_FILTERS
#define SDP_MAX_ATTR_FILTERS        15
#endif

/* The maximum number of UUID filters supported by SDP databases. */
#ifndef SDP_MAX_UUID_FILTERS
#define SDP_MAX_UUID_FILTERS        3
#endif

/* This is set to enable SDP client functionality. */
#ifndef SDP_CLIENT_ENABLED
#define SDP_CLIENT_ENABLED          TRUE
#endif

/* The maximum number of record handles retrieved in a search. */
#ifndef SDP_MAX_DISC_SERVER_RECS
#define SDP_MAX_DISC_SERVER_RECS    21
#endif

/* The size of a scratchpad buffer, in bytes, for storing the response to an attribute request. */
#ifndef SDP_MAX_LIST_BYTE_COUNT
#define SDP_MAX_LIST_BYTE_COUNT     4096
#endif

/* The maximum number of parameters in an SDP protocol element. */
#ifndef SDP_MAX_PROTOCOL_PARAMS
#define SDP_MAX_PROTOCOL_PARAMS     2
#endif

/* The maximum number of simultaneous client and server connections. */
#ifndef SDP_MAX_CONNECTIONS
#define SDP_MAX_CONNECTIONS         4
#endif

/* The MTU size for the L2CAP configuration. */
#ifndef SDP_MTU_SIZE
#define SDP_MTU_SIZE                256
#endif

/* The flush timeout for the L2CAP configuration. */
#ifndef SDP_FLUSH_TO
#define SDP_FLUSH_TO                0xFFFF
#endif

/* The name for security authorization. */
#ifndef SDP_SERVICE_NAME
#define SDP_SERVICE_NAME            "Service Discovery"
#endif

/* The security level for BTM. */
#ifndef SDP_SECURITY_LEVEL
#define SDP_SECURITY_LEVEL          BTM_SEC_NONE
#endif

/* Device identification feature. */
#ifndef SDP_DI_INCLUDED
#define SDP_DI_INCLUDED             TRUE
#endif

/******************************************************************************
**
** RFCOMM
**
******************************************************************************/

#ifndef RFCOMM_INCLUDED
#define RFCOMM_INCLUDED             TRUE
#endif

/* The maximum number of ports supported. */
#ifndef MAX_RFC_PORTS
#define MAX_RFC_PORTS               30
#endif

/* The maximum simultaneous links to different devices. */
#ifndef MAX_ACL_CONNECTIONS
#define MAX_BD_CONNECTIONS          7
#else
#define MAX_BD_CONNECTIONS          MAX_ACL_CONNECTIONS
#endif

/* The port receive queue low watermark level, in bytes. */
#ifndef PORT_RX_LOW_WM
#define PORT_RX_LOW_WM              (BTA_RFC_MTU_SIZE * PORT_RX_BUF_LOW_WM)
#endif

/* The port receive queue high watermark level, in bytes. */
#ifndef PORT_RX_HIGH_WM
#define PORT_RX_HIGH_WM             (BTA_RFC_MTU_SIZE * PORT_RX_BUF_HIGH_WM)
#endif

/* The port receive queue critical watermark level, in bytes. */
#ifndef PORT_RX_CRITICAL_WM
#define PORT_RX_CRITICAL_WM         (BTA_RFC_MTU_SIZE * PORT_RX_BUF_CRITICAL_WM)
#endif

/* The port receive queue low watermark level, in number of buffers. */
#ifndef PORT_RX_BUF_LOW_WM
#define PORT_RX_BUF_LOW_WM          4
#endif

/* The port receive queue high watermark level, in number of buffers. */
#ifndef PORT_RX_BUF_HIGH_WM
#define PORT_RX_BUF_HIGH_WM         10
#endif

/* The port receive queue critical watermark level, in number of buffers. */
#ifndef PORT_RX_BUF_CRITICAL_WM
#define PORT_RX_BUF_CRITICAL_WM     15
#endif

/* The port transmit queue high watermark level, in bytes. */
#ifndef PORT_TX_HIGH_WM
#define PORT_TX_HIGH_WM             (BTA_RFC_MTU_SIZE * PORT_TX_BUF_HIGH_WM)
#endif

/* The port transmit queue critical watermark level, in bytes. */
#ifndef PORT_TX_CRITICAL_WM
#define PORT_TX_CRITICAL_WM         (BTA_RFC_MTU_SIZE * PORT_TX_BUF_CRITICAL_WM)
#endif

/* The port transmit queue high watermark level, in number of buffers. */
#ifndef PORT_TX_BUF_HIGH_WM
#define PORT_TX_BUF_HIGH_WM         10
#endif

/* The port transmit queue high watermark level, in number of buffers. */
#ifndef PORT_TX_BUF_CRITICAL_WM
#define PORT_TX_BUF_CRITICAL_WM     15
#endif

/* The RFCOMM multiplexer preferred flow control mechanism. */
#ifndef PORT_FC_DEFAULT
#define PORT_FC_DEFAULT             PORT_FC_CREDIT
#endif

/* The maximum number of credits receiver sends to peer when using credit-based flow control. */
#ifndef PORT_CREDIT_RX_MAX
#define PORT_CREDIT_RX_MAX          16
#endif

/* The credit low watermark level. */
#ifndef PORT_CREDIT_RX_LOW
#define PORT_CREDIT_RX_LOW          8
#endif

/* Test code allowing l2cap FEC on RFCOMM.*/
#ifndef PORT_ENABLE_L2CAP_FCR_TEST
#define PORT_ENABLE_L2CAP_FCR_TEST  FALSE
#endif

/* if application like BTA, Java or script test engine is running on other than BTU thread, */
/* PORT_SCHEDULE_LOCK shall be defined as GKI_sched_lock() or GKI_disable() */
#ifndef PORT_SCHEDULE_LOCK
#define PORT_SCHEDULE_LOCK          GKI_disable()
#endif

/* if application like BTA, Java or script test engine is running on other than BTU thread, */
/* PORT_SCHEDULE_LOCK shall be defined as GKI_sched_unlock() or GKI_enable() */
#ifndef PORT_SCHEDULE_UNLOCK
#define PORT_SCHEDULE_UNLOCK        GKI_enable()
#endif

/******************************************************************************
**
** TCS
**
******************************************************************************/

#ifndef TCS_INCLUDED
#define TCS_INCLUDED                FALSE
#endif

/* If set to TRUE, gives lean TCS state machine configuration. */
#ifndef TCS_LEAN
#define TCS_LEAN                    FALSE
#endif

/* To include/exclude point-to-multipoint broadcast SETUP configuration. */
#ifndef TCS_BCST_SETUP_INCLUDED
#define TCS_BCST_SETUP_INCLUDED     TRUE
#endif

/* To include/exclude supplementary services. */
#ifndef TCS_SUPP_SVCS_INCLUDED
#define TCS_SUPP_SVCS_INCLUDED      TRUE
#endif

/* To include/exclude WUG master role. */
#ifndef TCS_WUG_MASTER_INCLUDED
#define TCS_WUG_MASTER_INCLUDED     TRUE
#endif

/* To include/exclude WUG member role. */
#ifndef TCS_WUG_MEMBER_INCLUDED
#define TCS_WUG_MEMBER_INCLUDED     TRUE
#endif

/* Maximum number of WUG members. */
#ifndef TCS_MAX_WUG_MEMBERS
#define TCS_MAX_WUG_MEMBERS         7
#endif

/* Broadcom specific acknowledgement message to ensure fast and robust operation of WUG FIMA procedure. */
#ifndef TCS_WUG_LISTEN_ACPT_ACK_INCLUDED
#define TCS_WUG_LISTEN_ACPT_ACK_INCLUDED TRUE
#endif

/* The number of simultaneous calls supported. */
#ifndef TCS_MAX_NUM_SIMUL_CALLS
#define TCS_MAX_NUM_SIMUL_CALLS     3
#endif

/* The number of devices the device can connect to. */
#ifndef TCS_MAX_NUM_ACL_CONNS
#define TCS_MAX_NUM_ACL_CONNS       7
#endif

/* The maximum length, in bytes, of the company specific information element. */
#ifndef TCS_MAX_CO_SPEC_LEN
#define TCS_MAX_CO_SPEC_LEN         40
#endif

/* The maximum length, in bytes, of the audio control information element . */
#ifndef TCS_MAX_AUDIO_CTL_LEN
#define TCS_MAX_AUDIO_CTL_LEN       40
#endif

/* (Dis)allow EDR ESCO */
#ifndef TCS_AUDIO_USE_ESCO_EDR
#define TCS_AUDIO_USE_ESCO_EDR      FALSE
#endif

/******************************************************************************
**
** OBX
**
******************************************************************************/
#ifndef OBX_INCLUDED
#define OBX_INCLUDED               FALSE
#endif

#ifndef OBX_CLIENT_INCLUDED
#define OBX_CLIENT_INCLUDED        TRUE
#endif

#ifndef OBX_SERVER_INCLUDED
#define OBX_SERVER_INCLUDED        TRUE
#endif

/* TRUE to include OBEX authentication/MD5 code */
#ifndef OBX_MD5_INCLUDED
#define OBX_MD5_INCLUDED           TRUE
#endif

/* TRUE to include OBEX authentication/MD5 test code */
#ifndef OBX_MD5_TEST_INCLUDED
#define OBX_MD5_TEST_INCLUDED       FALSE
#endif

/* TRUE to include OBEX 1.4 enhancement (including Obex Over L2CAP) */
#ifndef OBX_14_INCLUDED
#define OBX_14_INCLUDED             FALSE
#endif
/* MD5 code is required to use OBEX 1.4 features (Reliable session) */
#if (OBX_MD5_INCLUDED == FALSE)
#undef OBX_14_INCLUDED
#define OBX_14_INCLUDED             FALSE
#endif

/* L2CAP FCR/eRTM mode is required to use OBEX Over L2CAP */
#if (L2CAP_FCR_INCLUDED == FALSE)
#undef OBX_14_INCLUDED
#define OBX_14_INCLUDED             FALSE
#endif

/* The timeout value (in seconds) for reliable sessions to remain in suspend. 0xFFFFFFFF for no timeout event. */
#ifndef OBX_SESS_TIMEOUT_VALUE
#define OBX_SESS_TIMEOUT_VALUE      600
#endif

/* The idle timeout value. 0 for no timeout event. */
#ifndef OBX_TIMEOUT_VALUE
#define OBX_TIMEOUT_VALUE           60
#endif

/* Timeout value used for disconnect */
#ifndef OBX_DISC_TOUT_VALUE
#define OBX_DISC_TOUT_VALUE         5
#endif

/* The maximum number of registered servers. */
#ifndef OBX_NUM_SERVERS
#define OBX_NUM_SERVERS             12
#endif

/* The maximum number of sessions per registered server. */
#ifndef OBX_MAX_SR_SESSION
#define OBX_MAX_SR_SESSION          4
#endif

/* The maximum number of sessions for all registered servers.
 * (must be equal or bigger than OBX_NUM_SERVERS) */
#ifndef OBX_NUM_SR_SESSIONS
#define OBX_NUM_SR_SESSIONS         26
#endif

/* The maximum number of sessions per registered server.
 * must be less than MAX_BD_CONNECTIONS */
#ifndef OBX_MAX_SR_SESSION
#define OBX_MAX_SR_SESSION          4
#endif

/* The maximum number of suspended sessions per registered servers. */
#ifndef OBX_MAX_SUSPEND_SESSIONS
#define OBX_MAX_SUSPEND_SESSIONS    4
#endif

/* The maximum number of active clients. */
#ifndef OBX_NUM_CLIENTS
#define OBX_NUM_CLIENTS             8
#endif

/* The maximum length of OBEX target header.*/
#ifndef OBX_MAX_TARGET_LEN
#define OBX_MAX_TARGET_LEN          16
#endif

/* The maximum length of authentication challenge realm.*/
#ifndef OBX_MAX_REALM_LEN
#define OBX_MAX_REALM_LEN           30
#endif

/* The maximum of GKI buffer queued at OBX before flow control L2CAP */
#ifndef OBX_MAX_RX_QUEUE_COUNT
#define OBX_MAX_RX_QUEUE_COUNT      3
#endif

/* This option is application when OBX_14_INCLUDED=TRUE
   Pool ID where to reassemble the SDU.
   This Pool will allow buffers to be used that are larger than
   the L2CAP_MAX_MTU. */
#ifndef OBX_USER_RX_POOL_ID
#define OBX_USER_RX_POOL_ID     OBX_LRG_DATA_POOL_ID
#endif

/* This option is application when OBX_14_INCLUDED=TRUE
   Pool ID where to hold the SDU.
   This Pool will allow buffers to be used that are larger than
   the L2CAP_MAX_MTU. */
#ifndef OBX_USER_TX_POOL_ID
#define OBX_USER_TX_POOL_ID     OBX_LRG_DATA_POOL_ID
#endif

/* This option is application when OBX_14_INCLUDED=TRUE
GKI Buffer Pool ID used to hold MPS segments during SDU reassembly
*/
#ifndef OBX_FCR_RX_POOL_ID
#define OBX_FCR_RX_POOL_ID      HCI_ACL_POOL_ID
#endif

/* This option is application when OBX_14_INCLUDED=TRUE
GKI Buffer Pool ID used to hold MPS segments used in (re)transmissions.
L2CAP_DEFAULT_ERM_POOL_ID is specified to use the HCI ACL data pool.
Note:  This pool needs to have enough buffers to hold two times the window size negotiated
 in the L2CA_SetFCROptions (2 * tx_win_size)  to allow for retransmissions.
 The size of each buffer must be able to hold the maximum MPS segment size passed in
 L2CA_SetFCROptions plus BT_HDR (8) + HCI preamble (4) + L2CAP_MIN_OFFSET (11 - as of BT 2.1 + EDR Spec).
*/
#ifndef OBX_FCR_TX_POOL_ID
#define OBX_FCR_TX_POOL_ID      HCI_ACL_POOL_ID
#endif

/* This option is application when OBX_14_INCLUDED=TRUE
Size of the transmission window when using enhanced retransmission mode. Not used
in basic and streaming modes. Range: 1 - 63
*/
#ifndef OBX_FCR_OPT_TX_WINDOW_SIZE_BR_EDR
#define OBX_FCR_OPT_TX_WINDOW_SIZE_BR_EDR       20
#endif

/* This option is application when OBX_14_INCLUDED=TRUE
Number of transmission attempts for a single I-Frame before taking
Down the connection. Used In ERTM mode only. Value is Ignored in basic and
Streaming modes.
Range: 0, 1-0xFF
0 - infinite retransmissions
1 - single transmission
*/
#ifndef OBX_FCR_OPT_MAX_TX_B4_DISCNT
#define OBX_FCR_OPT_MAX_TX_B4_DISCNT    20
#endif

/* This option is application when OBX_14_INCLUDED=TRUE
Retransmission Timeout
Range: Minimum 2000 (2 secs) on BR/EDR when supporting PBF.
 */
#ifndef OBX_FCR_OPT_RETX_TOUT
#define OBX_FCR_OPT_RETX_TOUT           2000
#endif

/* This option is application when OBX_14_INCLUDED=TRUE
Monitor Timeout
Range: Minimum 12000 (12 secs) on BR/EDR when supporting PBF.
*/
#ifndef OBX_FCR_OPT_MONITOR_TOUT
#define OBX_FCR_OPT_MONITOR_TOUT        12000
#endif

/******************************************************************************
**
** BNEP
**
******************************************************************************/

#ifndef BNEP_INCLUDED
#define BNEP_INCLUDED               TRUE
#endif

/* Protocol filtering is an optional feature. Bydefault it will be turned on */
#ifndef BNEP_SUPPORTS_PROT_FILTERS
#define BNEP_SUPPORTS_PROT_FILTERS          TRUE
#endif

/* Multicast filtering is an optional feature. Bydefault it will be turned on */
#ifndef BNEP_SUPPORTS_MULTI_FILTERS
#define BNEP_SUPPORTS_MULTI_FILTERS         TRUE
#endif

/* BNEP status API call is used mainly to get the L2CAP handle */
#ifndef BNEP_SUPPORTS_STATUS_API
#define BNEP_SUPPORTS_STATUS_API            TRUE
#endif

/* This is just a debug function */
#ifndef BNEP_SUPPORTS_DEBUG_DUMP
#define BNEP_SUPPORTS_DEBUG_DUMP            TRUE
#endif

#ifndef BNEP_SUPPORTS_ALL_UUID_LENGTHS
#define BNEP_SUPPORTS_ALL_UUID_LENGTHS      TRUE    /* Otherwise it will support only 16bit UUIDs */
#endif

/*
** When BNEP connection changes roles after the connection is established
** we will do an authentication check again on the new role
*/
#ifndef BNEP_DO_AUTH_FOR_ROLE_SWITCH
#define BNEP_DO_AUTH_FOR_ROLE_SWITCH        TRUE
#endif


/* Maximum number of protocol filters supported. */
#ifndef BNEP_MAX_PROT_FILTERS
#define BNEP_MAX_PROT_FILTERS       5
#endif

/* Maximum number of multicast filters supported. */
#ifndef BNEP_MAX_MULTI_FILTERS
#define BNEP_MAX_MULTI_FILTERS      5
#endif

/* Minimum MTU size. */
#ifndef BNEP_MIN_MTU_SIZE
#define BNEP_MIN_MTU_SIZE           L2CAP_MTU_SIZE
#endif

/* Preferred MTU size. */
#ifndef BNEP_MTU_SIZE
#define BNEP_MTU_SIZE               BNEP_MIN_MTU_SIZE
#endif

/* Maximum size of user data, in bytes.  */
#ifndef BNEP_MAX_USER_DATA_SIZE
#define BNEP_MAX_USER_DATA_SIZE     1500
#endif

/* Maximum number of buffers allowed in transmit data queue. */
#ifndef BNEP_MAX_XMITQ_DEPTH
#define BNEP_MAX_XMITQ_DEPTH        20
#endif

/* Maximum number BNEP of connections supported. */
#ifndef BNEP_MAX_CONNECTIONS
#define BNEP_MAX_CONNECTIONS        7
#endif


/******************************************************************************
**
** AVDTP
**
******************************************************************************/

#ifndef AVDT_INCLUDED
#define AVDT_INCLUDED               TRUE
#endif

/* Include reporting capability in AVDTP */
#ifndef AVDT_REPORTING
#define AVDT_REPORTING              TRUE
#endif

/* Include multiplexing capability in AVDTP */
#ifndef AVDT_MULTIPLEXING
#define AVDT_MULTIPLEXING           TRUE
#endif

/* Number of simultaneous links to different peer devices. */
#ifndef AVDT_NUM_LINKS
#define AVDT_NUM_LINKS              2
#endif

/* Number of simultaneous stream endpoints. */
#ifndef AVDT_NUM_SEPS
#define AVDT_NUM_SEPS               3
#endif

/* Number of transport channels setup per media stream(audio or video) */
#ifndef AVDT_NUM_CHANNELS

#if AVDT_REPORTING == TRUE
/* signaling, media and reporting channels */
#define AVDT_NUM_CHANNELS   3
#else
/* signaling and media channels */
#define AVDT_NUM_CHANNELS   2
#endif

#endif

/* Number of transport channels setup by AVDT for all media streams
 * AVDT_NUM_CHANNELS * Number of simultaneous streams.
 */
#ifndef AVDT_NUM_TC_TBL
#define AVDT_NUM_TC_TBL             6
#endif


/* Maximum size in bytes of the codec capabilities information element. */
#ifndef AVDT_CODEC_SIZE
#define AVDT_CODEC_SIZE             10
#endif

/* Maximum size in bytes of the content protection information element. */
#ifndef AVDT_PROTECT_SIZE
#define AVDT_PROTECT_SIZE           90
#endif

/* Maximum number of GKI buffers in the fragment queue (for video frames).
 * Must be less than the number of buffers in the buffer pool of size AVDT_DATA_POOL_SIZE */
#ifndef AVDT_MAX_FRAG_COUNT
#define AVDT_MAX_FRAG_COUNT         15
#endif

/******************************************************************************
**
** PAN
**
******************************************************************************/

#ifndef PAN_INCLUDED
#define PAN_INCLUDED                     TRUE
#endif

/* This will enable the PANU role */
#ifndef PAN_SUPPORTS_ROLE_PANU
#define PAN_SUPPORTS_ROLE_PANU              TRUE
#endif

/* This will enable the GN role */
#ifndef PAN_SUPPORTS_ROLE_GN
#define PAN_SUPPORTS_ROLE_GN                TRUE
#endif

/* This will enable the NAP role */
#ifndef PAN_SUPPORTS_ROLE_NAP
#define PAN_SUPPORTS_ROLE_NAP               TRUE
#endif

/* This is just for debugging purposes */
#ifndef PAN_SUPPORTS_DEBUG_DUMP
#define PAN_SUPPORTS_DEBUG_DUMP             TRUE
#endif


/* Maximum number of PAN connections allowed */
#ifndef MAX_PAN_CONNS
#define MAX_PAN_CONNS                    7
#endif

/* Default service name for NAP role */
#ifndef PAN_NAP_DEFAULT_SERVICE_NAME
#define PAN_NAP_DEFAULT_SERVICE_NAME    "Network Access Point Service"
#endif

/* Default service name for GN role */
#ifndef PAN_GN_DEFAULT_SERVICE_NAME
#define PAN_GN_DEFAULT_SERVICE_NAME     "Group Network Service"
#endif

/* Default service name for PANU role */
#ifndef PAN_PANU_DEFAULT_SERVICE_NAME
#define PAN_PANU_DEFAULT_SERVICE_NAME   "PAN User Service"
#endif

/* Default description for NAP role service */
#ifndef PAN_NAP_DEFAULT_DESCRIPTION
#define PAN_NAP_DEFAULT_DESCRIPTION     "NAP"
#endif

/* Default description for GN role service */
#ifndef PAN_GN_DEFAULT_DESCRIPTION
#define PAN_GN_DEFAULT_DESCRIPTION      "GN"
#endif

/* Default description for PANU role service */
#ifndef PAN_PANU_DEFAULT_DESCRIPTION
#define PAN_PANU_DEFAULT_DESCRIPTION    "PANU"
#endif

/* Default Security level for PANU role. */
#ifndef PAN_PANU_SECURITY_LEVEL
#define PAN_PANU_SECURITY_LEVEL          0
#endif

/* Default Security level for GN role. */
#ifndef PAN_GN_SECURITY_LEVEL
#define PAN_GN_SECURITY_LEVEL            0
#endif

/* Default Security level for NAP role. */
#ifndef PAN_NAP_SECURITY_LEVEL
#define PAN_NAP_SECURITY_LEVEL           0
#endif




/******************************************************************************
**
** GAP
**
******************************************************************************/

#ifndef GAP_INCLUDED
#define GAP_INCLUDED                FALSE
#endif

/* This is set to enable use of GAP L2CAP connections. */
#ifndef GAP_CONN_INCLUDED
#define GAP_CONN_INCLUDED           TRUE
#endif

/* This is set to enable posting event for data write */
#ifndef GAP_CONN_POST_EVT_INCLUDED
#define GAP_CONN_POST_EVT_INCLUDED  FALSE
#endif

/* The maximum number of simultaneous GAP L2CAP connections. */
#ifndef GAP_MAX_CONNECTIONS
#define GAP_MAX_CONNECTIONS         8
#endif

/******************************************************************************
**
** CTP
**
******************************************************************************/

#ifndef CTP_INCLUDED
#define CTP_INCLUDED                FALSE
#endif

/* To include CTP gateway functionality or not. */
#ifndef CTP_GW_INCLUDED
#define CTP_GW_INCLUDED             TRUE
#endif

/* The number of terminals supported. */
#ifndef CTP_MAX_NUM_TLS
#define CTP_MAX_NUM_TLS             7
#endif

/* If the controller can not support sniff mode when the SCO is up, set this to FALSE. */
#ifndef CTP_USE_SNIFF_ON_SCO
#define CTP_USE_SNIFF_ON_SCO        FALSE
#endif

/* When ACL link between TL and GW is idle for more than this amount of seconds, the ACL may be put to low power mode. */
#ifndef CTP_TL_IDLE_TIMEOUT
#define CTP_TL_IDLE_TIMEOUT         90
#endif

/* To include CTP terminal functionality or not. */
#ifndef CTP_TL_INCLUDED
#define CTP_TL_INCLUDED             TRUE
#endif

/* To include CTP device discovery functionality or not. */
#ifndef CTP_DISCOVERY_INCLUDED
#define CTP_DISCOVERY_INCLUDED      TRUE
#endif

/* set to TRUE for controllers that do not support multi-point */
#ifndef CTP_TL_WAIT_DISC
#define CTP_TL_WAIT_DISC            TRUE
#endif

/* The CTP inquiry database size. */
#ifndef CTP_INQ_DB_SIZE
#define CTP_INQ_DB_SIZE             CTP_DISC_REC_SIZE
#endif

/* The CTP discovery record size. */
#ifndef CTP_DISC_REC_SIZE
#define CTP_DISC_REC_SIZE           60
#endif

/* CTP TL would try to re-establish L2CAP channel after channel is disconnected for this amount of seconds. */
#ifndef CTP_GUARD_LINK_LOST
#define CTP_GUARD_LINK_LOST         1
#endif

/* The link policy bitmap. */
#ifndef CTP_DEFAULT_LINK_POLICY
#define CTP_DEFAULT_LINK_POLICY     0x000F
#endif

/* The minimum period interval used for the sniff and park modes. */
#ifndef CTP_DEF_LOWPWR_MIN_PERIOD
#define CTP_DEF_LOWPWR_MIN_PERIOD   0x100
#endif

/* The maximum period interval used for the sniff and park modes. */
#ifndef CTP_DEF_LOWPWR_MAX_PERIOD
#define CTP_DEF_LOWPWR_MAX_PERIOD   0x1E0
#endif

/* The number of baseband receive slot sniff attempts. */
#ifndef CTP_DEF_LOWPWR_ATTEMPT
#define CTP_DEF_LOWPWR_ATTEMPT      0x200
#endif

/* The number of baseband receive slots for sniff timeout. */
#ifndef CTP_DEF_LOWPWR_TIMEOUT
#define CTP_DEF_LOWPWR_TIMEOUT      0x200
#endif

/* This is set if CTP is to use park mode. */
#ifndef CTP_PARK_INCLUDED
#define CTP_PARK_INCLUDED           TRUE
#endif

/* This is set if CTP is to use sniff mode. */
#ifndef CTP_SNIFF_INCLUDED
#define CTP_SNIFF_INCLUDED          TRUE
#endif

/* To include CTP data exchange functionality or not. */
#ifndef CTP_DATA_EXCHG_FEATURE
#define CTP_DATA_EXCHG_FEATURE      FALSE
#endif

/* To include CTP GW intercom functionality or not. */
#ifndef CTP_GW_INTERCOM_FEATURE
#define CTP_GW_INTERCOM_FEATURE     FALSE
#endif

/* The MTU size for L2CAP channel. */
#ifndef CTP_MTU_SIZE
#define CTP_MTU_SIZE                200
#endif

/* The L2CAP PSM for the data exchange feature. */
#ifndef CTP_DATA_EXCHG_PSM
#define CTP_DATA_EXCHG_PSM          13
#endif

/* The flush timeout for L2CAP channels. */
#ifndef CTP_FLUSH_TO
#define CTP_FLUSH_TO                0xFFFF
#endif

/* The default service name for CTP. */
#ifndef CTP_DEFAULT_SERVICE_NAME
#define CTP_DEFAULT_SERVICE_NAME    "Cordless Telephony"
#endif

/* The CTP security level. */
#ifndef CTP_SECURITY_LEVEL
#define CTP_SECURITY_LEVEL          (BTM_SEC_IN_AUTHORIZE | BTM_SEC_IN_AUTHENTICATE | BTM_SEC_IN_ENCRYPT)
#endif

/* The number of lines to the external network. */
#ifndef CTP_MAX_LINES
#define CTP_MAX_LINES               1
#endif

/* Test if the number of resources in TCS is consistent with CTP setting. */
#ifndef CTP_TEST_FULL_TCS
#define CTP_TEST_FULL_TCS           TRUE
#endif

/* The default inquiry mode. */
#ifndef CTP_DEFAULT_INQUIRY_MODE
#define CTP_DEFAULT_INQUIRY_MODE    BTM_GENERAL_INQUIRY
#endif

/* The default inquiry duration. */
#ifndef CTP_DEFAULT_INQ_DURATION
#define CTP_DEFAULT_INQ_DURATION    4
#endif

/* The maximum number of inquiry responses. */
#ifndef CTP_DEFAULT_INQ_MAX_RESP
#define CTP_DEFAULT_INQ_MAX_RESP    3
#endif

/* When TL does not create another L2CAP channel within this period of time GW declares that it's "Connected Limited". */
#ifndef CTP_TL_CONN_TIMEOUT
#define CTP_TL_CONN_TIMEOUT         5
#endif

/* The delay for ACL to completely disconnect (for intercom) before sending the connect request to GW. */
#ifndef CTP_RECONNECT_DELAY
#define CTP_RECONNECT_DELAY         5
#endif

/* How many times to retry connection when it has failed. */
#ifndef CTP_RETRY_ON_CONN_ERR
#define CTP_RETRY_ON_CONN_ERR       5
#endif

/******************************************************************************
**
** ICP
**
******************************************************************************/

#ifndef ICP_INCLUDED
#define ICP_INCLUDED                FALSE
#endif

/* The ICP default MTU. */
#ifndef ICP_MTU_SIZE
#define ICP_MTU_SIZE                100
#endif

/* The ICP security level. */
#ifndef ICP_SECURITY_LEVEL
#define ICP_SECURITY_LEVEL          BTM_SEC_NONE
#endif

/* The default service name for ICP. */
#ifndef ICP_DEFAULT_SERVICE_NAME
#define ICP_DEFAULT_SERVICE_NAME    "Intercom"
#endif

/* The flush timeout for L2CAP channels. */
#ifndef ICP_FLUSH_TO
#define ICP_FLUSH_TO                0xFFFF
#endif

/******************************************************************************
**
** SPP
**
******************************************************************************/

#ifndef SPP_INCLUDED
#define SPP_INCLUDED                FALSE
#endif

/* The SPP default MTU. */
#ifndef SPP_DEFAULT_MTU
#define SPP_DEFAULT_MTU             127
#endif

/* The interval, in seconds, that a client tries to reconnect to a service. */
#ifndef SPP_RETRY_CONN_INTERVAL
#define SPP_RETRY_CONN_INTERVAL     1
#endif

/* The SPP discoverable mode: limited or general. */
#ifndef SPP_DISCOVERABLE_MODE
#define SPP_DISCOVERABLE_MODE       BTM_GENERAL_DISCOVERABLE
#endif

/* The maximum number of inquiry results returned in by inquiry procedure. */
#ifndef SPP_DEF_INQ_MAX_RESP
#define SPP_DEF_INQ_MAX_RESP        10
#endif

/* The SPP discovery record size. */
#ifndef SPP_DISC_REC_SIZE
#define SPP_DISC_REC_SIZE           60
#endif

#ifndef SPP_MAX_RECS_PER_DEVICE
#define SPP_MAX_RECS_PER_DEVICE     (SPP_DB_SIZE / SPP_DISC_REC_SIZE)
#endif

/* Inquiry duration in 1.28 second units. */
#ifndef SPP_DEF_INQ_DURATION
#define SPP_DEF_INQ_DURATION        9
#endif

/* keep the raw data received from SDP server in database. */
#ifndef SDP_RAW_DATA_INCLUDED
#define SDP_RAW_DATA_INCLUDED       TRUE
#endif

/* TRUE, to allow JV to create L2CAP connection on SDP PSM. */
#ifndef SDP_FOR_JV_INCLUDED
#define SDP_FOR_JV_INCLUDED         FALSE
#endif

/* Inquiry duration in 1.28 second units. */
#ifndef SDP_DEBUG
#define SDP_DEBUG                   TRUE
#endif

/******************************************************************************
**
** HSP2, HFP
**
******************************************************************************/

#ifndef HSP2_INCLUDED
#define HSP2_INCLUDED               FALSE
#endif

/* Include the ability to perform inquiry for peer devices. */
#ifndef HSP2_INQUIRY_INCLUDED
#define HSP2_INQUIRY_INCLUDED       TRUE
#endif

/* Include Audio Gateway specific code. */
#ifndef HSP2_AG_INCLUDED
#define HSP2_AG_INCLUDED            TRUE
#endif

/* Include Headset Specific Code. */
#ifndef HSP2_HS_INCLUDED
#define HSP2_HS_INCLUDED            TRUE
#endif

/* Include the ability to open an SCO connection for In-Band Ringing. */
#ifndef HSP2_IB_RING_INCLUDED
#define HSP2_IB_RING_INCLUDED       TRUE
#endif

/* Include the ability to repeat a ring. */
#ifndef HSP2_AG_REPEAT_RING
#define HSP2_AG_REPEAT_RING         TRUE
#endif

#ifndef HSP2_APP_CLOSES_ON_CKPD
#define HSP2_APP_CLOSES_ON_CKPD     FALSE
#endif


/* Include the ability to park a connection. */
#ifndef HSP2_PARK_INCLUDED
#define HSP2_PARK_INCLUDED          TRUE
#endif

/* Include HSP State Machine debug trace messages. */
#ifndef HSP2_FSM_DEBUG
#define HSP2_FSM_DEBUG              TRUE
#endif

/* The Module's Inquiry Scan Window. */
#ifndef HSP2_INQ_SCAN_WINDOW
#define HSP2_INQ_SCAN_WINDOW        0
#endif

/* The Module's Inquiry Scan Interval. */
#ifndef HSP2_INQ_SCAN_INTERVAL
#define HSP2_INQ_SCAN_INTERVAL      0
#endif

/* The Module's Page Scan Interval. */
#ifndef HSP2_PAGE_SCAN_INTERVAL
#define HSP2_PAGE_SCAN_INTERVAL     0
#endif

/* The Module's Page Scan Window. */
#ifndef HSP2_PAGE_SCAN_WINDOW
#define HSP2_PAGE_SCAN_WINDOW       0
#endif

/* The Park Mode's Minimum Beacon Period. */
#ifndef HSP2_BEACON_MIN_PERIOD
#define HSP2_BEACON_MIN_PERIOD      450
#endif

/* The Park Mode's Maximum Beacon Period. */
#ifndef HSP2_BEACON_MAX_PERIOD
#define HSP2_BEACON_MAX_PERIOD      500
#endif

/* The duration of the inquiry in seconds. */
#ifndef HSP2_INQ_DURATION
#define HSP2_INQ_DURATION           4
#endif

/* Maximum number of peer responses during an inquiry. */
#ifndef HSP2_INQ_MAX_NUM_RESPS
#define HSP2_INQ_MAX_NUM_RESPS      3
#endif

/* Maximum number of times to retry an inquiry prior to failure. */
#ifndef HSP2_MAX_INQ_RETRY
#define HSP2_MAX_INQ_RETRY          6
#endif

/* Maximum number of times to retry an RFCOMM connection prior to failure. */
#ifndef HSP2_MAX_CONN_RETRY
#define HSP2_MAX_CONN_RETRY         3
#endif

/* If the connect request failed for authentication reasons, do not retry */
#ifndef HSP2_NO_RETRY_ON_AUTH_FAIL
#define HSP2_NO_RETRY_ON_AUTH_FAIL  TRUE
#endif

/* Maximum number of characters in an HSP2 device name. */
#ifndef HSP2_MAX_NAME_LEN
#define HSP2_MAX_NAME_LEN           32
#endif

/* The minimum speaker and/or microphone gain setting. */
#ifndef HSP2_MIN_GAIN
#define HSP2_MIN_GAIN               0
#endif

/* The maximum speaker and/or microphone setting. */
#ifndef HSP2_MAX_GAIN
#define HSP2_MAX_GAIN               15
#endif

/* The default value to send on an AT+CKPD. */
#ifndef HSP2_KEYPRESS_DEFAULT
#define HSP2_KEYPRESS_DEFAULT       200
#endif

/* Maximum amount a data that can be received per RFCOMM frame. */
#ifndef HSP2_MAX_RFC_READ_LEN
#define HSP2_MAX_RFC_READ_LEN       128
#endif

/* The time in seconds to wait for completion of a partial AT command or response from the peer. */
#ifndef HSP2_AT_TO_INTERVAL
#define HSP2_AT_TO_INTERVAL         30
#endif

/* The time to wait before repeating a ring to a peer Headset. */
#ifndef HSP2_REPEAT_RING_TO
#define HSP2_REPEAT_RING_TO         4
#endif

/* Time to wait for a response for an AT command */
#ifndef HSP2_AT_RSP_TO
#define HSP2_AT_RSP_TO              20
#endif

/* SCO packet type(s) to use (bitmask: see spec), 0 - device default (recommended) */
#ifndef HSP2_SCO_PKT_TYPES
#define HSP2_SCO_PKT_TYPES          ((UINT16)0x0000)
#endif

/* The default settings of the SCO voice link. */
#ifndef HSP2_DEFAULT_VOICE_SETTINGS
#define HSP2_DEFAULT_VOICE_SETTINGS (HCI_INP_CODING_LINEAR | HCI_INP_DATA_FMT_2S_COMPLEMENT | HCI_INP_SAMPLE_SIZE_16BIT | HCI_AIR_CODING_FORMAT_CVSD)
#endif

#ifndef HSP2_MAX_AT_CMD_LENGTH
#define HSP2_MAX_AT_CMD_LENGTH       16
#endif

#ifndef HSP2_MAX_AT_VAL_LENGTH
#if (defined(HFP_INCLUDED) && HFP_INCLUDED == TRUE)
#define HSP2_MAX_AT_VAL_LENGTH       310
#else
#define HSP2_MAX_AT_VAL_LENGTH       5
#endif
#endif


#ifndef HSP2_SDP_DB_SIZE
#define HSP2_SDP_DB_SIZE             300
#endif


/******************************************************************************
**
** HFP
**
******************************************************************************/

#ifndef HFP_INCLUDED
#define HFP_INCLUDED                FALSE
#endif

/* Include Audio Gateway specific code. */
#ifndef HFP_AG_INCLUDED
#define HFP_AG_INCLUDED             TRUE
#endif

/* Include Hand Free Specific Code. */
#ifndef HFP_HF_INCLUDED
#define HFP_HF_INCLUDED             TRUE
#endif

/* Use AT interface instead of full blown API */
#ifndef AT_INTERFACE
#define AT_INTERFACE            FALSE
#endif

/* HFP Manages SCO establishement for various procedures */
#ifndef HFP_SCO_MGMT_INCLUDED
#define HFP_SCO_MGMT_INCLUDED             TRUE
#endif

/* CCAP compliant features and behavior desired */
#ifndef CCAP_COMPLIANCE
#define CCAP_COMPLIANCE             TRUE
#endif

/* Caller ID string, part of +CLIP result code */
#ifndef HFP_MAX_CLIP_INFO
#define HFP_MAX_CLIP_INFO             45
#endif

#ifndef HFP_RPT_PEER_INFO_INCLUDED
#define HFP_RPT_PEER_INFO_INCLUDED  TRUE  /* Reporting of peer features enabled */
#endif

/******************************************************************************
**
** HID
**
******************************************************************************/

/* HID Device Role Included */
#ifndef HID_DEV_INCLUDED
#define HID_DEV_INCLUDED             FALSE
#endif

#ifndef HID_DEV_PM_INCLUDED
#define HID_DEV_PM_INCLUDED         TRUE
#endif

/* The HID Device is a virtual cable */
#ifndef HID_DEV_VIRTUAL_CABLE
#define HID_DEV_VIRTUAL_CABLE       TRUE
#endif

/* The HID device initiates the reconnections */
#ifndef HID_DEV_RECONN_INITIATE
#define HID_DEV_RECONN_INITIATE     TRUE
#endif

/* THe HID device is normally connectable */
#ifndef HID_DEV_NORMALLY_CONN
#define HID_DEV_NORMALLY_CONN       FALSE
#endif

/* The device is battery powered */
#ifndef HID_DEV_BATTERY_POW
#define HID_DEV_BATTERY_POW         TRUE
#endif

/* Device is capable of waking up the host */
#ifndef HID_DEV_REMOTE_WAKE
#define HID_DEV_REMOTE_WAKE         TRUE
#endif

/* Device needs host to close SDP channel after SDP is over */
#ifndef HID_DEV_SDP_DISABLE
#define HID_DEV_SDP_DISABLE         TRUE
#endif

#ifndef HID_DEV_MTU_SIZE
#define HID_DEV_MTU_SIZE                 64
#endif

#ifndef HID_DEV_FLUSH_TO
#define HID_DEV_FLUSH_TO                 0xffff
#endif

#ifndef HID_DEV_PAGE_SCAN_WIN
#define HID_DEV_PAGE_SCAN_WIN       (0)
#endif

#ifndef HID_DEV_PAGE_SCAN_INT
#define HID_DEV_PAGE_SCAN_INT       (0)
#endif

#ifndef HID_DEV_MAX_CONN_RETRY
#define HID_DEV_MAX_CONN_RETRY      (15)
#endif

#ifndef HID_DEV_REPAGE_WIN
#define HID_DEV_REPAGE_WIN          (1)
#endif

#ifndef HID_DEV_SVC_NAME
#define HID_DEV_SVC_NAME            "HID"
#endif

#ifndef HID_DEV_SVC_DESCR
#define HID_DEV_SVC_DESCR           "3-button mouse and keyboard"
#endif

#ifndef HID_DEV_PROVIDER_NAME
#define HID_DEV_PROVIDER_NAME       "Widcomm"
#endif

#ifndef HID_DEV_REL_NUM
#define HID_DEV_REL_NUM             0x0100
#endif

#ifndef HID_DEV_PARSER_VER
#define HID_DEV_PARSER_VER          0x0111
#endif

#ifndef HID_DEV_SUBCLASS
#define HID_DEV_SUBCLASS            COD_MINOR_POINTING
#endif

#ifndef HID_DEV_COUNTRY_CODE
#define HID_DEV_COUNTRY_CODE        0x33
#endif

#ifndef HID_DEV_SUP_TOUT
#define HID_DEV_SUP_TOUT            0x8000
#endif

#ifndef HID_DEV_NUM_LANGS
#define HID_DEV_NUM_LANGS           1
#endif

#ifndef HID_DEV_INACT_TIMEOUT
#define HID_DEV_INACT_TIMEOUT       60
#endif

#ifndef HID_DEV_BUSY_MODE_PARAMS
#define HID_DEV_BUSY_MODE_PARAMS    { 320, 160, 10, 20, HCI_MODE_ACTIVE }
#endif

#ifndef HID_DEV_IDLE_MODE_PARAMS
#define HID_DEV_IDLE_MODE_PARAMS    { 320, 160, 10, 20, HCI_MODE_SNIFF }
#endif

#ifndef HID_DEV_SUSP_MODE_PARAMS
#define HID_DEV_SUSP_MODE_PARAMS    { 640, 320,  0,    0, HCI_MODE_PARK }
#endif

#ifndef HID_DEV_MAX_DESCRIPTOR_SIZE
#define HID_DEV_MAX_DESCRIPTOR_SIZE      128     /* Max descriptor size          */
#endif

#ifndef HID_DEV_LANGUAGELIST
#define HID_DEV_LANGUAGELIST             {0x35, 0x06, 0x09, 0x04, 0x09, 0x09, 0x01, 0x00}
#endif

#ifndef HID_DEV_LINK_SUPERVISION_TO
#define HID_DEV_LINK_SUPERVISION_TO      0x8000
#endif

#ifndef HID_CONTROL_POOL_ID
#define HID_CONTROL_POOL_ID             2
#endif

#ifndef HID_INTERRUPT_POOL_ID
#define HID_INTERRUPT_POOL_ID           2
#endif

/*************************************************************************
** Definitions for Both HID-Host & Device
*/
#ifndef HID_MAX_SVC_NAME_LEN
#define HID_MAX_SVC_NAME_LEN  32
#endif

#ifndef HID_MAX_SVC_DESCR_LEN
#define HID_MAX_SVC_DESCR_LEN 32
#endif

#ifndef HID_MAX_PROV_NAME_LEN
#define HID_MAX_PROV_NAME_LEN 32
#endif

/*************************************************************************
** Definitions for HID-Host
*/
#ifndef  HID_HOST_INCLUDED
#define HID_HOST_INCLUDED           TRUE
#endif

#ifndef HID_HOST_MAX_DEVICES
#define HID_HOST_MAX_DEVICES        7
#endif

#ifndef HID_HOST_MTU
#define HID_HOST_MTU                640
#endif

#ifndef HID_HOST_FLUSH_TO
#define HID_HOST_FLUSH_TO                 0xffff
#endif

#ifndef HID_HOST_MAX_CONN_RETRY
#define HID_HOST_MAX_CONN_RETRY     (3)
#endif

#ifndef HID_HOST_REPAGE_WIN
#define HID_HOST_REPAGE_WIN          (2)
#endif


/******************************************************************************
**
** DUN and FAX
**
******************************************************************************/

#ifndef DUN_INCLUDED
#define DUN_INCLUDED                FALSE
#endif


/******************************************************************************
**
** GOEP
**
******************************************************************************/

#ifndef GOEP_INCLUDED
#define GOEP_INCLUDED               FALSE
#endif

/* This is set to enable GOEP non-blocking file system access functions. */
#ifndef GOEP_FS_INCLUDED
#define GOEP_FS_INCLUDED        FALSE
#endif

/* GOEP authentication key size. */
#ifndef GOEP_MAX_AUTH_KEY_SIZE
#define GOEP_MAX_AUTH_KEY_SIZE      16
#endif

/* Maximum size of the realm authentication string. */
#ifndef GOEP_MAX_AUTH_REALM_SIZE
#define GOEP_MAX_AUTH_REALM_SIZE    16
#endif

/* Realm Character Set */
#ifndef GOEP_REALM_CHARSET
#define GOEP_REALM_CHARSET          0       /* ASCII */
#endif

/* This is set to the maximum length of path name allowed in the system (_MAX_PATH). */
#ifndef GOEP_MAX_PATH_SIZE
#define GOEP_MAX_PATH_SIZE          255
#endif

/* Specifies whether or not client's user id is required during obex authentication */
#ifndef GOEP_SERVER_USERID_REQUIRED
#define GOEP_SERVER_USERID_REQUIRED FALSE
#endif

/* This is set to the maximum length of file name allowed in the system (_MAX_FNAME). */
#ifndef GOEP_MAX_FILE_SIZE
#define GOEP_MAX_FILE_SIZE          128
#endif

/* Character used as path separator */
#ifndef GOEP_PATH_SEPARATOR
#define GOEP_PATH_SEPARATOR         ((char) 0x5c)   /* 0x2f ('/'), or 0x5c ('\') */
#endif

/******************************************************************************
**
** OPP
**
******************************************************************************/

#ifndef OPP_INCLUDED
#define OPP_INCLUDED                FALSE
#endif

/* This is set to enable OPP client capabilities. */
#ifndef OPP_CLIENT_INCLUDED
#define OPP_CLIENT_INCLUDED         FALSE
#endif

/* This is set to enable OPP server capabilities. */
#ifndef OPP_SERVER_INCLUDED
#define OPP_SERVER_INCLUDED         FALSE
#endif

/* if the optional formating functions are to be included or not */
#ifndef OPP_FORMAT_INCLUDED
#define OPP_FORMAT_INCLUDED         FALSE
#endif

/* Maximum number of client sessions allowed by server */
#ifndef OPP_MAX_SRVR_SESS
#define OPP_MAX_SRVR_SESS           3
#endif

/******************************************************************************
**
** FTP
**
******************************************************************************/

#ifndef FTP_INCLUDED
#define FTP_INCLUDED                FALSE
#endif

/* This is set to enable FTP client capabilities. */
#ifndef FTP_CLIENT_INCLUDED
#define FTP_CLIENT_INCLUDED         TRUE
#endif

/* This is set to enable FTP server capabilities. */
#ifndef FTP_SERVER_INCLUDED
#define FTP_SERVER_INCLUDED         TRUE
#endif

/******************************************************************************
**
** XML Parser
**
******************************************************************************/

#ifndef XML_STACK_SIZE
#define XML_STACK_SIZE             7
#endif

/******************************************************************************
**
** BPP Printer
**
******************************************************************************/
#ifndef BPP_DEBUG
#define BPP_DEBUG            FALSE
#endif

#ifndef BPP_INCLUDED
#define BPP_INCLUDED                FALSE
#endif

#ifndef BPP_SND_INCLUDED
#define BPP_SND_INCLUDED            FALSE
#endif

/* Maximum number of senders allowed to connect simultaneously
** The maximum is 6 or (OBX_NUM_SERVERS / 2), whichever is smaller
*/
#ifndef BPP_PR_MAX_CON
#define BPP_PR_MAX_CON         3
#endif

/* Service Name. maximum length: 248
#ifndef BPP_SERVICE_NAME
#define BPP_SERVICE_NAME            "Basic Printing"
#endif
 */
/* Document Format Supported. ASCII comma-delimited list of MIME type:version string
#ifndef BPP_DOC_FORMAT_SUPPORTED
#define BPP_DOC_FORMAT_SUPPORTED    "application/vnd.pwg-xhtml-print:1.0,application/vnd.hp-PCL:5E,application/PDF"
#endif

#ifndef BPP_DOC_FORMAT_SUPPORTED_LEN
#define BPP_DOC_FORMAT_SUPPORTED_LEN    77
#endif
 */
/* Character repertoires.
#ifndef BPP_CHARACTER_REPERTOIRES
#define BPP_CHARACTER_REPERTOIRES {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01}
#endif
 */
/* XHTML formats.
#ifndef BPP_XHTML_PRINT_FORMATS
#define BPP_XHTML_PRINT_FORMATS     "image/gif:89A,image/jpeg"
#endif

#ifndef BPP_XHTML_PRINT_FORMATS_LEN
#define BPP_XHTML_PRINT_FORMATS_LEN 24
#endif
 */
/* Color supported.
#ifndef BPP_COLOR_SUPORTED
#define BPP_COLOR_SUPORTED          FALSE
#endif
 */
/* 1284 ID string. First 2 bytes are the length.
#ifndef BPP_1284ID
#define BPP_1284ID                  "\x00\x48MANUFACTURER:ACME Manufacturing;COMMAND SET:PCL,MPL;MODEL:LaserBeam \?;"
#endif

#ifndef BPP_1284ID_LEN
#define BPP_1284ID_LEN              72
#endif
 */
/* Printer name.
#ifndef BPP_PRINTER_NAME
#define BPP_PRINTER_NAME            "My Printer"
#endif

#ifndef BPP_PRINTER_NAME_LEN
#define BPP_PRINTER_NAME_LEN        10
#endif
 */

/* Printer location.
#ifndef BPP_PRINTER_LOCATION
#define BPP_PRINTER_LOCATION        "Hotel Lobby"
#endif

#ifndef BPP_PRINTER_LOCATION_LEN
#define BPP_PRINTER_LOCATION_LEN    11
#endif
 */
/* Duplex printing supported.
#ifndef BPP_DUPLEX_SUPPORTED
#define BPP_DUPLEX_SUPPORTED        TRUE
#endif
 */

/* Media types supported.
#ifndef BPP_MEDIA_TYPES_SUPPORTED
#define BPP_MEDIA_TYPES_SUPPORTED   "stationary,continuous-long,photographic-high-gloss,cardstock"
#endif

#ifndef BPP_MEDIA_TYPES_SUPPORTED_LEN
#define BPP_MEDIA_TYPES_SUPPORTED_LEN   60
#endif
 */
/* Maximum media with supported.
#ifndef BPP_MAX_MEDIA_WIDTH
#define BPP_MAX_MEDIA_WIDTH         205
#endif
 */
/* Maximum media length supported.
#ifndef BPP_MAX_MEDIA_LENGTH
#define BPP_MAX_MEDIA_LENGTH        285
#endif
 */
/* the maximum string len for the media size of medium loaded */
#ifndef BPP_MEDIA_SIZE_LEN
#define BPP_MEDIA_SIZE_LEN          33
#endif

/* Debug Trace the SOAP object, if TRUE */
#ifndef BPP_TRACE_XML
#define BPP_TRACE_XML               TRUE
#endif

/* in case that the SOAP object does not all come in one OBEX packet,
 * this size of data may be kept in the BPP control block for continuing parsing.
 * The maximum is the size of the biggest GKI buffer (GKI_MAX_BUF_SIZE) */
#ifndef BPP_SOAP_KEEP_SIZE
#define BPP_SOAP_KEEP_SIZE          200
#endif


/******************************************************************************
**
** BIP
**
******************************************************************************/
#ifndef BIP_INCLUDED
#define BIP_INCLUDED                FALSE
#endif

/* TRUE to include imaging initiator */
#ifndef BIP_INITR_INCLUDED
#define BIP_INITR_INCLUDED          FALSE
#endif

/* TRUE to include imaging responder */
#ifndef BIP_RSPDR_INCLUDED
#define BIP_RSPDR_INCLUDED          FALSE
#endif

/* TRUE to include image push feature */
#ifndef BIP_PUSH_INCLUDED
#define BIP_PUSH_INCLUDED           TRUE
#endif

/* TRUE to include image pull feature */
#ifndef BIP_PULL_INCLUDED
#define BIP_PULL_INCLUDED           TRUE
#endif

/* TRUE to include advanced image printing feature */
#ifndef BIP_PRINTING_INCLUDED
#define BIP_PRINTING_INCLUDED       TRUE
#endif

/* TRUE to include automatic archive feature */
#ifndef BIP_ARCHIVE_INCLUDED
#define BIP_ARCHIVE_INCLUDED        TRUE
#endif

/* TRUE to include remote camera feature */
#ifndef BIP_CAMERA_INCLUDED
#define BIP_CAMERA_INCLUDED         TRUE
#endif

/* TRUE to include remote display feature */
#ifndef BIP_DISPLAY_INCLUDED
#define BIP_DISPLAY_INCLUDED        TRUE
#endif

/* TRUE to include sanity check code for API functions */
#ifndef BIP_SANITY_CHECKS
#define BIP_SANITY_CHECKS           TRUE
#endif

/* TRUE to show the received XML object in trace for conformance tests */
#ifndef BIP_TRACE_XML
#define BIP_TRACE_XML               TRUE
#endif

/* in case that the received XML object is not complete, the XML parser state machine needs
 * to keep a copy of the data from the last '<'
 * This macro specifies the maximun amount of data for this purpose */
#ifndef BIP_XML_CARRY_OVER_LEN
#define BIP_XML_CARRY_OVER_LEN      100
#endif

/* minimum 4, maximum is 255. The value should be set to the maximum size of encoding string + 1. JPEG2000.
 * If vendor specific format is supported, it might be bigger than 9 */
#ifndef BIP_IMG_ENCODE_SIZE
#define BIP_IMG_ENCODE_SIZE         9
#endif

/* MIME type: text/plain */
#ifndef BIP_TYPE_SIZE
#define BIP_TYPE_SIZE               20
#endif

/* example: iso-8895-1 */
#ifndef BIP_CHARSET_SIZE
#define BIP_CHARSET_SIZE            10
#endif

/* friendly name */
#ifndef BIP_FNAME_SIZE
#define BIP_FNAME_SIZE              20
#endif

/* service name */
#ifndef BIP_SNAME_SIZE
#define BIP_SNAME_SIZE              60
#endif

/* temporary storage file name(for file system access, may include path) */
#ifndef BIP_TEMP_NAME_SIZE
#define BIP_TEMP_NAME_SIZE          200
#endif

/* image file name */
#ifndef BIP_IMG_NAME_SIZE
#define BIP_IMG_NAME_SIZE           200
#endif

/* attachment file name */
#ifndef BIP_ATT_NAME_SIZE
#define BIP_ATT_NAME_SIZE           200
#endif

/* object (image, attachment, thumbnail) file name (may be used for file system) */
#ifndef BIP_OBJ_NAME_SIZE
#define BIP_OBJ_NAME_SIZE           200
#endif



/******************************************************************************
**
** HCRP
**
******************************************************************************/

#ifndef HCRP_INCLUDED
#define HCRP_INCLUDED               FALSE
#endif

/* This is set to enable server. */
#ifndef HCRP_SERVER_INCLUDED
#define HCRP_SERVER_INCLUDED       FALSE
#endif

/* This is set to enable client. */
#ifndef HCRP_CLIENT_INCLUDED
#define HCRP_CLIENT_INCLUDED        FALSE
#endif

/* TRUE enables the notification option of the profile. */
#ifndef HCRP_NOTIFICATION_INCLUDED
#define HCRP_NOTIFICATION_INCLUDED  TRUE
#endif

/* TRUE enables the vendor specific option of the profile. */
#ifndef HCRP_VENDOR_SPEC_INCLUDED
#define HCRP_VENDOR_SPEC_INCLUDED   TRUE
#endif

/* TRUE enables state machine traces. */
#ifndef HCRP_FSM_DEBUG
#define HCRP_FSM_DEBUG              FALSE
#endif

/* TRUE enables protocol message traces. */
#ifndef HCRP_PROTO_DEBUG
#define HCRP_PROTO_DEBUG            FALSE
#endif

/* Maximum length used to store the service name (Minimum 1). */
#ifndef HCRP_MAX_SERVICE_NAME_LEN
#define HCRP_MAX_SERVICE_NAME_LEN   32
#endif

/* Maximum length used to store the device name (Minimum 1). */
#ifndef HCRP_MAX_DEVICE_NAME_LEN
#define HCRP_MAX_DEVICE_NAME_LEN    32
#endif

/* Maximum length of device location (Minimum 1) */
#ifndef HCRP_MAX_DEVICE_LOC_LEN
#define HCRP_MAX_DEVICE_LOC_LEN     32
#endif

/* Maximum length used to store the friendly name (Minimum 1). */
#ifndef HCRP_MAX_FRIENDLY_NAME_LEN
#define HCRP_MAX_FRIENDLY_NAME_LEN  32
#endif

/* Maximum length used to store the 1284 id string (Minimum 2 byte length field). */
#ifndef HCRP_MAX_SDP_1284_ID_LEN
#define HCRP_MAX_SDP_1284_ID_LEN    128
#endif

/* Maximum length for parameters to be processed for vendor specific commands. */
#ifndef HCRP_MAX_VEND_SPEC_LEN
#define HCRP_MAX_VEND_SPEC_LEN      4
#endif

/* Number of seconds to wait for 2nd GAP to open. */
#ifndef HCRP_OPEN_CHAN_TOUT
#define HCRP_OPEN_CHAN_TOUT         5
#endif

/* Number of seconds to wait for 2nd GAP to close. */
#ifndef HCRP_CLOSE_CHAN_TOUT
#define HCRP_CLOSE_CHAN_TOUT        3
#endif

/* Number of seconds to wait for the application to respond to a protocol request. */
#ifndef HCRP_APPL_RSP_TOUT
#define HCRP_APPL_RSP_TOUT          5
#endif

/* Number of seconds to wait for the peer device to respond to a protocol request. */
#ifndef HCRP_CMD_RSP_TOUT
#define HCRP_CMD_RSP_TOUT           7
#endif

/* Number of seconds between subsequent credit requests to the server when the send watermark has been exceeded. */
#ifndef HCRP_CREDIT_REQ_UPDATES
#define HCRP_CREDIT_REQ_UPDATES     1
#endif

/* Maximum number of results to return in a HCRP_FindServices search. */
#ifndef HCRP_MAX_SEARCH_RESULTS
#define HCRP_MAX_SEARCH_RESULTS     1
#endif

/* Maximum number of bytes to be reserved for searching for the client's notification record. */
#ifndef HCRP_MAX_NOTIF_DISC_BUF
#define HCRP_MAX_NOTIF_DISC_BUF     300
#endif

/* Maximum number of clients the server will allow to be registered for notifications. */
#ifndef HCRP_MAX_NOTIF_CLIENTS
#define HCRP_MAX_NOTIF_CLIENTS      3
#endif

/* Spec says minimum of two notification retries. */
#ifndef HCRP_NOTIF_NUM_RETRIES
#define HCRP_NOTIF_NUM_RETRIES      4
#endif

/*************************************************************************
** Definitions for Multi-Client Server HCRP
** Note: Many of the above HCRP definitions are also used
** Maximum number of clients allowed to connect simultaneously
** Must be less than ((GAP_MAX_CONNECTIONS - 1) / 2)
*/
#ifndef HCRPM_MAX_CLIENTS
#define HCRPM_MAX_CLIENTS           3
#endif


/******************************************************************************
**
** PAN
**
******************************************************************************/

#ifndef PAN_INCLUDED
#define PAN_INCLUDED                FALSE
#endif


/******************************************************************************
**
** SAP
**
******************************************************************************/

#ifndef SAP_SERVER_INCLUDED
#define SAP_SERVER_INCLUDED         FALSE
#endif


/*************************************************************************
 * A2DP Definitions
 */
#ifndef A2D_INCLUDED
#define A2D_INCLUDED            TRUE
#endif

/* TRUE to include SBC utility functions */
#ifndef A2D_SBC_INCLUDED
#define A2D_SBC_INCLUDED        A2D_INCLUDED
#endif

/* TRUE to include MPEG-1,2 (mp3) utility functions */
#ifndef A2D_M12_INCLUDED
#define A2D_M12_INCLUDED        A2D_INCLUDED
#endif

/* TRUE to include MPEG-2,4 (aac) utility functions */
#ifndef A2D_M24_INCLUDED
#define A2D_M24_INCLUDED        A2D_INCLUDED
#endif

/******************************************************************************
**
** AVCTP
**
******************************************************************************/

#ifndef AVCT_INCLUDED
#define AVCT_INCLUDED               TRUE
#endif

/* Number of simultaneous ACL links to different peer devices. */
#ifndef AVCT_NUM_LINKS
#define AVCT_NUM_LINKS              2
#endif

/* Number of simultaneous AVCTP connections. */
#ifndef AVCT_NUM_CONN
#define AVCT_NUM_CONN               3
#endif

/* Pool ID where to reassemble the SDU.
   This Pool allows buffers to be used that are larger than
   the L2CAP_MAX_MTU. */
#ifndef AVCT_BR_USER_RX_POOL_ID
#define AVCT_BR_USER_RX_POOL_ID     HCI_ACL_POOL_ID
#endif

/* Pool ID where to hold the SDU.
   This Pool allows buffers to be used that are larger than
   the L2CAP_MAX_MTU. */
#ifndef AVCT_BR_USER_TX_POOL_ID
#define AVCT_BR_USER_TX_POOL_ID     HCI_ACL_POOL_ID
#endif

/*
GKI Buffer Pool ID used to hold MPS segments during SDU reassembly
*/
#ifndef AVCT_BR_FCR_RX_POOL_ID
#define AVCT_BR_FCR_RX_POOL_ID      HCI_ACL_POOL_ID
#endif

/*
GKI Buffer Pool ID used to hold MPS segments used in (re)transmissions.
L2CAP_DEFAULT_ERM_POOL_ID is specified to use the HCI ACL data pool.
Note:  This pool needs to have enough buffers to hold two times the window size negotiated
 in the tL2CAP_FCR_OPTIONS (2 * tx_win_size)  to allow for retransmissions.
 The size of each buffer must be able to hold the maximum MPS segment size passed in
 tL2CAP_FCR_OPTIONS plus BT_HDR (8) + HCI preamble (4) + L2CAP_MIN_OFFSET (11 - as of BT 2.1 + EDR Spec).
*/
#ifndef AVCT_BR_FCR_TX_POOL_ID
#define AVCT_BR_FCR_TX_POOL_ID      HCI_ACL_POOL_ID
#endif

/* AVCTP Browsing channel FCR Option:
Size of the transmission window when using enhanced retransmission mode. Not used
in basic and streaming modes. Range: 1 - 63
*/
#ifndef AVCT_BR_FCR_OPT_TX_WINDOW_SIZE
#define AVCT_BR_FCR_OPT_TX_WINDOW_SIZE      10
#endif

/* AVCTP Browsing channel FCR Option:
Number of transmission attempts for a single I-Frame before taking
Down the connection. Used In ERTM mode only. Value is Ignored in basic and
Streaming modes.
Range: 0, 1-0xFF
0 - infinite retransmissions
1 - single transmission
*/
#ifndef AVCT_BR_FCR_OPT_MAX_TX_B4_DISCNT
#define AVCT_BR_FCR_OPT_MAX_TX_B4_DISCNT    20
#endif

/* AVCTP Browsing channel FCR Option: Retransmission Timeout
The AVRCP specification set a value in the range of 300 - 2000 ms
Timeout (in msecs) to detect Lost I-Frames. Only used in Enhanced retransmission mode.
Range: Minimum 2000 (2 secs) when supporting PBF.
 */
#ifndef AVCT_BR_FCR_OPT_RETX_TOUT
#define AVCT_BR_FCR_OPT_RETX_TOUT           2000
#endif

/* AVCTP Browsing channel FCR Option: Monitor Timeout
The AVRCP specification set a value in the range of 300 - 2000 ms
Timeout (in msecs) to detect Lost S-Frames. Only used in Enhanced retransmission mode.
Range: Minimum 12000 (12 secs) when supporting PBF.
*/
#ifndef AVCT_BR_FCR_OPT_MONITOR_TOUT
#define AVCT_BR_FCR_OPT_MONITOR_TOUT        12000
#endif

/******************************************************************************
**
** AVRCP
**
******************************************************************************/

#ifndef AVRC_INCLUDED
#define AVRC_INCLUDED               TRUE
#endif

/******************************************************************************
**
** MCAP
**
******************************************************************************/
#ifndef MCA_INCLUDED
#define MCA_INCLUDED                FALSE
#endif

/* TRUE to support Clock Synchronization OpCodes */
#ifndef MCA_SYNC_INCLUDED
#define MCA_SYNC_INCLUDED           FALSE
#endif

/* The MTU size for the L2CAP configuration on control channel. 48 is the minimal */
#ifndef MCA_CTRL_MTU
#define MCA_CTRL_MTU    60
#endif

/* The maximum number of registered MCAP instances. */
#ifndef MCA_NUM_REGS
#define MCA_NUM_REGS    3
#endif

/* The maximum number of control channels (to difference devices) per registered MCAP instances. */
#ifndef MCA_NUM_LINKS
#define MCA_NUM_LINKS   3
#endif

/* The maximum number of MDEP (including HDP echo) per registered MCAP instances. */
#ifndef MCA_NUM_DEPS
#define MCA_NUM_DEPS    3
#endif

/* The maximum number of MDL link per control channel. */
#ifndef MCA_NUM_MDLS
#define MCA_NUM_MDLS    4
#endif

/* Pool ID where to reassemble the SDU. */
#ifndef MCA_USER_RX_POOL_ID
#define MCA_USER_RX_POOL_ID     HCI_ACL_POOL_ID
#endif

/* Pool ID where to hold the SDU. */
#ifndef MCA_USER_TX_POOL_ID
#define MCA_USER_TX_POOL_ID     HCI_ACL_POOL_ID
#endif

/*
GKI Buffer Pool ID used to hold MPS segments during SDU reassembly
*/
#ifndef MCA_FCR_RX_POOL_ID
#define MCA_FCR_RX_POOL_ID      HCI_ACL_POOL_ID
#endif

/*
GKI Buffer Pool ID used to hold MPS segments used in (re)transmissions.
L2CAP_DEFAULT_ERM_POOL_ID is specified to use the HCI ACL data pool.
Note:  This pool needs to have enough buffers to hold two times the window size negotiated
 in the tL2CAP_FCR_OPTIONS (2 * tx_win_size)  to allow for retransmissions.
 The size of each buffer must be able to hold the maximum MPS segment size passed in
 tL2CAP_FCR_OPTIONS plus BT_HDR (8) + HCI preamble (4) + L2CAP_MIN_OFFSET (11 - as of BT 2.1 + EDR Spec).
*/
#ifndef MCA_FCR_TX_POOL_ID
#define MCA_FCR_TX_POOL_ID      HCI_ACL_POOL_ID
#endif

/* MCAP control channel FCR Option:
Size of the transmission window when using enhanced retransmission mode.
1 is defined by HDP specification for control channel.
*/
#ifndef MCA_FCR_OPT_TX_WINDOW_SIZE
#define MCA_FCR_OPT_TX_WINDOW_SIZE      1
#endif

/* MCAP control channel FCR Option:
Number of transmission attempts for a single I-Frame before taking
Down the connection. Used In ERTM mode only. Value is Ignored in basic and
Streaming modes.
Range: 0, 1-0xFF
0 - infinite retransmissions
1 - single transmission
*/
#ifndef MCA_FCR_OPT_MAX_TX_B4_DISCNT
#define MCA_FCR_OPT_MAX_TX_B4_DISCNT    20
#endif

/* MCAP control channel FCR Option: Retransmission Timeout
The AVRCP specification set a value in the range of 300 - 2000 ms
Timeout (in msecs) to detect Lost I-Frames. Only used in Enhanced retransmission mode.
Range: Minimum 2000 (2 secs) when supporting PBF.
 */
#ifndef MCA_FCR_OPT_RETX_TOUT
#define MCA_FCR_OPT_RETX_TOUT           2000
#endif

/* MCAP control channel FCR Option: Monitor Timeout
The AVRCP specification set a value in the range of 300 - 2000 ms
Timeout (in msecs) to detect Lost S-Frames. Only used in Enhanced retransmission mode.
Range: Minimum 12000 (12 secs) when supporting PBF.
*/
#ifndef MCA_FCR_OPT_MONITOR_TOUT
#define MCA_FCR_OPT_MONITOR_TOUT        12000
#endif

/* MCAP control channel FCR Option: Maximum PDU payload size.
The maximum number of payload octets that the local device can receive in a single PDU.
*/
#ifndef MCA_FCR_OPT_MPS_SIZE
#define MCA_FCR_OPT_MPS_SIZE            1000
#endif

/* Shared transport */
#ifndef NFC_SHARED_TRANSPORT_ENABLED
#define NFC_SHARED_TRANSPORT_ENABLED    FALSE
#endif

/******************************************************************************
**
** SER
**
******************************************************************************/

#ifndef SER_INCLUDED
#define SER_INCLUDED                FALSE
#endif

/* Task which runs the serial application. */
#ifndef SER_TASK
#define SER_TASK                    BTE_APPL_TASK
#endif

/* Mailbox used by serial application. */
#ifndef SER_MBOX
#define SER_MBOX                    TASK_MBOX_1
#endif

/* Mailbox mask. */
#ifndef SER_MBOX_MASK
#define SER_MBOX_MASK               TASK_MBOX_1_EVT_MASK
#endif

/* TX path application event. */
#ifndef SER_TX_PATH_APPL_EVT
#define SER_TX_PATH_APPL_EVT        EVENT_MASK(APPL_EVT_3)
#endif

/* RX path application event. */
#ifndef SER_RX_PATH_APPL_EVT
#define SER_RX_PATH_APPL_EVT        EVENT_MASK(APPL_EVT_4)
#endif

/******************************************************************************
**
** Sleep Mode (Low Power Mode)
**
******************************************************************************/

#ifndef HCILP_INCLUDED
#define HCILP_INCLUDED                  TRUE
#endif

/******************************************************************************
**
** RPC
**
******************************************************************************/

#ifndef RPC_INCLUDED
#define RPC_INCLUDED                FALSE
#endif

/* RPCT task mailbox ID for messages coming from rpcgen code. */
#ifndef RPCT_MBOX
#define RPCT_MBOX                   TASK_MBOX_0
#endif

/* RPCT task event for mailbox. */
#ifndef RPCT_RPC_MBOX_EVT
#define RPCT_RPC_MBOX_EVT           TASK_MBOX_0_EVT_MASK
#endif

/* RPCT task event from driver indicating RX data is ready. */
#ifndef RPCT_RX_READY_EVT
#define RPCT_RX_READY_EVT           APPL_EVT_0
#endif

/* RPCT task event from driver indicating data TX is done. */
#ifndef RPCT_TX_DONE_EVT
#define RPCT_TX_DONE_EVT            APPL_EVT_1
#endif

/* RPCT task event indicating data is in the circular buffer. */
#ifndef RPCT_UCBUF_EVT
#define RPCT_UCBUF_EVT              APPL_EVT_2
#endif

/* Task ID of RPCGEN task. */
#ifndef RPCGEN_TASK
#define RPCGEN_TASK                 BTU_TASK
#endif

/* RPCGEN task event for messages coming from RPCT. */
#ifndef RPCGEN_MSG_EVT
#define RPCGEN_MSG_EVT              TASK_MBOX_1_EVT_MASK
#endif

#ifndef RPCGEN_MSG_MBOX
#define RPCGEN_MSG_MBOX             TASK_MBOX_1
#endif

/* Size of circular buffer used to store diagnostic messages. */
#ifndef RPCT_UCBUF_SIZE
#define RPCT_UCBUF_SIZE             2000
#endif

/******************************************************************************
**
** SAP - Sample applications
**
******************************************************************************/

#ifndef MMI_INCLUDED
#define MMI_INCLUDED                FALSE
#endif

/******************************************************************************
**
** APPL - Application Task
**
******************************************************************************/
/* When TRUE indicates that an application task is to be run */
#ifndef APPL_INCLUDED
#define APPL_INCLUDED                TRUE
#endif

/* When TRUE remote terminal code included (RPC MUST be included) */
#ifndef RSI_INCLUDED
#define RSI_INCLUDED                TRUE
#endif



#define L2CAP_FEATURE_REQ_ID      73
#define L2CAP_FEATURE_RSP_ID     173


#define L2CAP_ENHANCED_FEATURES   0


/******************************************************************************
**
** BTA
**
******************************************************************************/
/* BTA EIR canned UUID list (default is dynamic) */
#ifndef BTA_EIR_CANNED_UUID_LIST
#define BTA_EIR_CANNED_UUID_LIST FALSE
#endif

/* Number of supported customer UUID in EIR */
#ifndef BTA_EIR_SERVER_NUM_CUSTOM_UUID
#define BTA_EIR_SERVER_NUM_CUSTOM_UUID     8
#endif

/* CHLD override for bluedroid */
#ifndef BTA_AG_CHLD_VAL_ECC
#define BTA_AG_CHLD_VAL_ECC  "(0,1,1x,2,2x,3)"
#endif

#ifndef BTA_AG_CHLD_VAL
#define BTA_AG_CHLD_VAL  "(0,1,2,3)"
#endif

/* Set the CIND to match HFP 1.5 */
#ifndef BTA_AG_CIND_INFO
#define BTA_AG_CIND_INFO "(\"call\",(0,1)),(\"callsetup\",(0-3)),(\"service\",(0-1)),(\"signal\",(0-5)),(\"roam\",(0,1)),(\"battchg\",(0-5)),(\"callheld\",(0-2))"
#endif


/******************************************************************************
**
** BTE
**
******************************************************************************/
#ifndef BTE_PLATFORM_IDLE
#define BTE_PLATFORM_IDLE
#endif

#ifndef BTE_IDLE_TASK_INCLUDED
#define BTE_IDLE_TASK_INCLUDED FALSE
#endif

#ifndef BTE_PLATFORM_INITHW
#define BTE_PLATFORM_INITHW
#endif

#ifndef BTE_BTA_CODE_INCLUDED
#define BTE_BTA_CODE_INCLUDED FALSE
#endif

/******************************************************************************
**
** BTTRC
**
******************************************************************************/
/* Whether to parse and display traces-> Platform specific implementation */
#ifndef BTTRC_DISP
#define BTTRC_DISP        BTTRC_DispOnInsight
#endif

/******************************************************************************
**
** Tracing:  Include trace header file here.
**
******************************************************************************/

#include "bt_trace.h"

#endif /* BT_TARGET_H */
