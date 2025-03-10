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
 *  This file contains definitions for implementing the
 *  diagnostic trace message service.
 *
 ******************************************************************************/

#ifndef BT_TRACE_H
#define BT_TRACE_H

#ifndef BTTRC_INCLUDED
#define BTTRC_INCLUDED  FALSE
#endif
#ifndef BTTRC_PARSER_INCLUDED
#define BTTRC_PARSER_INCLUDED FALSE
#endif
#ifndef MAX_TRACE_RAM_SIZE
#define MAX_TRACE_RAM_SIZE 10000
#endif

/* BTE tracing IDs for debug purposes */
/* LayerIDs for stack */
#define BTTRC_ID_STK_GKI                   1
#define BTTRC_ID_STK_BTU                   2
#define BTTRC_ID_STK_HCI                   3
#define BTTRC_ID_STK_L2CAP                 4
#define BTTRC_ID_STK_RFCM_MX               5
#define BTTRC_ID_STK_RFCM_PRT              6
#define BTTRC_ID_STK_OBEX_C                7
#define BTTRC_ID_STK_OBEX_S                8
#define BTTRC_ID_STK_AVCT                  9
#define BTTRC_ID_STK_AVDT                  10
#define BTTRC_ID_STK_AVRC                  11
#define BTTRC_ID_STK_BIC                   12
#define BTTRC_ID_STK_BIS                   13
#define BTTRC_ID_STK_BNEP                  14
#define BTTRC_ID_STK_BPP                   15
#define BTTRC_ID_STK_BTM_ACL               16
#define BTTRC_ID_STK_BTM_PM                17
#define BTTRC_ID_STK_BTM_DEV_CTRL          18
#define BTTRC_ID_STK_BTM_SVC_DSC           19
#define BTTRC_ID_STK_BTM_INQ               20
#define BTTRC_ID_STK_BTM_SCO               21
#define BTTRC_ID_STK_BTM_SEC               22
#define BTTRC_ID_STK_DUN                   23
#define BTTRC_ID_STK_HID                   24
#define BTTRC_ID_STK_HSP2                  25
#define BTTRC_ID_STK_CTP                   26
#define BTTRC_ID_STK_FTC                   27
#define BTTRC_ID_STK_FTS                   28
#define BTTRC_ID_STK_GAP                   29
#define BTTRC_ID_STK_GOEP                  30
#define BTTRC_ID_STK_HCRP                  31
#define BTTRC_ID_STK_ICP                   32
#define BTTRC_ID_STK_OPC                   33
#define BTTRC_ID_STK_OPS                   34
#define BTTRC_ID_STK_PAN                   35
#define BTTRC_ID_STK_SAP                   36
#define BTTRC_ID_STK_SDP                   37
#define BTTRC_ID_STK_SLIP                  38
#define BTTRC_ID_STK_SPP                   39
#define BTTRC_ID_STK_TCS                   40
#define BTTRC_ID_STK_VDP                   41
#define BTTRC_ID_STK_MCAP                  42
#define BTTRC_ID_STK_GATT                  43
#define BTTRC_ID_STK_SMP                   44
#define BTTRC_ID_STK_NFC                   45
#define BTTRC_ID_STK_NCI                   46
#define BTTRC_ID_STK_IDEP                  47
#define BTTRC_ID_STK_NDEP                  48
#define BTTRC_ID_STK_LLCP                  49
#define BTTRC_ID_STK_RW                    50
#define BTTRC_ID_STK_CE                    51
#define BTTRC_ID_STK_SNEP                  52
#define BTTRC_ID_STK_NDEF                  53


/* LayerIDs for BTA */
#define BTTRC_ID_BTA_ACC                   55         /* Advanced Camera Client */
#define BTTRC_ID_BTA_AG                    56         /* audio gateway */
#define BTTRC_ID_BTA_AV                    57         /* Advanced audio */
#define BTTRC_ID_BTA_BIC                   58         /* Basic Imaging Client */
#define BTTRC_ID_BTA_BIS                   59         /* Basic Imaging Server */
#define BTTRC_ID_BTA_BP                    60         /* Basic Printing Client */
#define BTTRC_ID_BTA_CG                    61
#define BTTRC_ID_BTA_CT                    62         /* cordless telephony terminal */
#define BTTRC_ID_BTA_DG                    63         /* data gateway */
#define BTTRC_ID_BTA_DM                    64         /* device manager */
#define BTTRC_ID_BTA_DM_SRCH               65         /* device manager search */
#define BTTRC_ID_BTA_DM_SEC                66         /* device manager security */
#define BTTRC_ID_BTA_FM                    67
#define BTTRC_ID_BTA_FTC                   68         /* file transfer client */
#define BTTRC_ID_BTA_FTS                   69         /* file transfer server */
#define BTTRC_ID_BTA_HIDH                  70
#define BTTRC_ID_BTA_HIDD                  71
#define BTTRC_ID_BTA_JV                    72
#define BTTRC_ID_BTA_OPC                   73         /* object push client */
#define BTTRC_ID_BTA_OPS                   74         /* object push server */
#define BTTRC_ID_BTA_PAN                   75         /* Personal Area Networking */
#define BTTRC_ID_BTA_PR                    76         /* Printer client */
#define BTTRC_ID_BTA_SC                    77         /* SIM Card Access server */
#define BTTRC_ID_BTA_SS                    78         /* synchronization server */
#define BTTRC_ID_BTA_SYS                   79         /* system manager */
#define BTTRC_ID_AVDT_SCB                  80         /* avdt scb */
#define BTTRC_ID_AVDT_CCB                  81         /* avdt ccb */

// btla-specific ++
/* LayerIDs added for BTL-A. Probably should modify bte_logmsg.c in future. */
#define BTTRC_ID_STK_RFCOMM                82
#define BTTRC_ID_STK_RFCOMM_DATA           83
#define BTTRC_ID_STK_OBEX                  84
#define BTTRC_ID_STK_A2D                   85
#define BTTRC_ID_STK_BIP                   86

/* LayerIDs for BT APP */
#define BTTRC_ID_BTAPP                     87
#define BTTRC_ID_BT_PROTOCOL               88         /* this is a temporary solution to allow dynamic
                                                         enable/disable of BT_PROTOCOL_TRACE */
#define BTTRC_ID_MAX_ID                    BTTRC_ID_BT_PROTOCOL
// btla-specific --
#define BTTRC_ID_ALL_LAYERS                0xFF       /* all trace layers */
typedef UINT8 tBTTRC_LAYER_ID;

/* Trace type definitions. Note that these are mutually exclusive in a trace. This
means that any trace can be either error,warning,api,event or dbg */
#define BTTRC_TYPE_ERROR                   0x01       /* Traces for error situation */
#define BTTRC_TYPE_WARNING	               0x02       /* Traces for warning situation */
#define BTTRC_TYPE_API                     0x04       /* Traces for API */
#define BTTRC_TYPE_EVENT                   0x08       /* Traces for EVENT */
#define BTTRC_TYPE_ACTION                  0x10       /* Traces for Action functions */
#define BTTRC_TYPE_DBG                     0x20       /* Traces for debugging purpose */
typedef UINT8 tBTTRC_TYPE;

/* Masks to identify the stack that originated the trace */
#define BTTRC_TRACE_LITE                   0x80       /* MM Lite stack */
#define BTTRC_TRACE_EMBD                   0x40       /* Embedded host stack */

/* Parameter datatypes used in Trace APIs */
#define BTTRC_PARAM_UINT8                  1
#define BTTRC_PARAM_UINT16                 2
#define BTTRC_PARAM_UINT32                 3
typedef UINT8 tBTTRC_PARAM_TYPE;

/* Special token definitions */
#define BTTRC_TOKEN_SM_STATE               0xFFFF     /* Token indicating the State of a State m/c */

// btla-specific ++
typedef struct {
    tBTTRC_LAYER_ID layer_id;
    tBTTRC_TYPE     type;      /* TODO: use tBTTRC_TYPE instead of "classical level 0-5" */
} tBTTRC_LEVEL;

typedef UINT8 (tBTTRC_SET_TRACE_LEVEL)( UINT8 );

typedef struct {
    const tBTTRC_LAYER_ID         layer_id_start;
    const tBTTRC_LAYER_ID         layer_id_end;
    tBTTRC_SET_TRACE_LEVEL        *p_f;
    const char                    *trc_name;
    UINT8                         trace_level;
} tBTTRC_FUNC_MAP;

extern tBTTRC_FUNC_MAP bttrc_set_level_map[];
extern const UINT16 bttrc_map_size;
extern BT_API tBTTRC_LEVEL * BTA_SysSetTraceLevel( tBTTRC_LEVEL * p_levels );
// btla-specific --


#ifdef __cplusplus
extern "C" {
#endif

/* External declaration for appl_trace_level here to avoid to add the declaration in all the files using APPL_TRACExxx macros */
extern UINT8 appl_trace_level ;

// btla-specific ++
EXPORT_API extern void BTE_InitTraceLevels( void );
// btla-specific --

/* Prototype for message logging function. */
EXPORT_API extern void LogMsg (UINT32 trace_set_mask, const char *fmt_str, ...);
extern void LogMsg_0 (UINT32 trace_set_mask, const char *p_str);
extern void LogMsg_1 (UINT32 trace_set_mask, const char *fmt_str, UINT32 p1);
extern void LogMsg_2 (UINT32 trace_set_mask, const char *fmt_str, UINT32 p1, UINT32 p2);
extern void LogMsg_3 (UINT32 trace_set_mask, const char *fmt_str, UINT32 p1, UINT32 p2,
                      UINT32 p3);
extern void LogMsg_4 (UINT32 trace_set_mask, const char *fmt_str, UINT32 p1, UINT32 p2,
                      UINT32 p3, UINT32 p4);
extern void LogMsg_5 (UINT32 trace_set_mask, const char *fmt_str, UINT32 p1, UINT32 p2,
                      UINT32 p3, UINT32 p4, UINT32 p5);
extern void LogMsg_6 (UINT32 trace_set_mask, const char *fmt_str, UINT32 p1, UINT32 p2,
                      UINT32 p3, UINT32 p4, UINT32 p5, UINT32 p6);

/* Prototype for stack tracing function. */
EXPORT_API extern void BTTRC_StackTrace0(tBTTRC_LAYER_ID layer_id,
                                   tBTTRC_TYPE type,
                                   UINT16 token);
EXPORT_API extern void BTTRC_StackTrace1(tBTTRC_LAYER_ID layer_id,
                                   tBTTRC_TYPE type,
                                   UINT16 token,
                                   tBTTRC_PARAM_TYPE p1_type, UINT32 p1_val);
EXPORT_API extern void BTTRC_StackTrace2(tBTTRC_LAYER_ID layer_id,
                                   tBTTRC_TYPE type,
                                   UINT16 token,
                                   tBTTRC_PARAM_TYPE p1_type, UINT32 p1_val,
                                   tBTTRC_PARAM_TYPE p2_type, UINT32 p2_val);
EXPORT_API extern void BTTRC_StackTrace3(tBTTRC_LAYER_ID layer_id,
                                   tBTTRC_TYPE type,
                                   UINT16 token,
                                   tBTTRC_PARAM_TYPE p1_type, UINT32 p1_val,
                                   tBTTRC_PARAM_TYPE p2_type, UINT32 p2_val,
                                   tBTTRC_PARAM_TYPE p3_type, UINT32 p3_val);
EXPORT_API extern void BTTRC_StackTrace4(tBTTRC_LAYER_ID layer_id,
                                   tBTTRC_TYPE type,
                                   UINT16 token,
                                   tBTTRC_PARAM_TYPE p1_type, UINT32 p1_val,
                                   tBTTRC_PARAM_TYPE p2_type, UINT32 p2_val,
                                   tBTTRC_PARAM_TYPE p3_type, UINT32 p3_val,
                                   tBTTRC_PARAM_TYPE p4_type, UINT32 p4_val);
EXPORT_API extern void BTTRC_StackTrace5(tBTTRC_LAYER_ID layer_id,
                                   tBTTRC_TYPE type,
                                   UINT16 token,
                                   tBTTRC_PARAM_TYPE p1_type, UINT32 p1_val,
                                   tBTTRC_PARAM_TYPE p2_type, UINT32 p2_val,
                                   tBTTRC_PARAM_TYPE p3_type, UINT32 p3_val,
                                   tBTTRC_PARAM_TYPE p4_type, UINT32 p4_val,
                                   tBTTRC_PARAM_TYPE p5_type, UINT32 p5_val);
EXPORT_API extern void BTTRC_StackTrace6(tBTTRC_LAYER_ID layer_id,
                                   tBTTRC_TYPE type,
                                   UINT16 token,
                                   tBTTRC_PARAM_TYPE p1_type, UINT32 p1_val,
                                   tBTTRC_PARAM_TYPE p2_type, UINT32 p2_val,
                                   tBTTRC_PARAM_TYPE p3_type, UINT32 p3_val,
                                   tBTTRC_PARAM_TYPE p4_type, UINT32 p4_val,
                                   tBTTRC_PARAM_TYPE p5_type, UINT32 p5_val,
                                   tBTTRC_PARAM_TYPE p6_type, UINT32 p6_val);

// btla-specific ++
/* p_levels must be a 0 terminated list ! */
//EXPORT_API extern tBTTRC_LEVEL * BTA_SysSetTraceLevel( tBTTRC_LEVEL * p_levels );
// btla-specific --

#ifdef __cplusplus
}
#endif

/******************************************************************************
**
** Trace configurable parameters
**
******************************************************************************/

/* Enables or disables verbose trace information. */
#ifndef BT_TRACE_VERBOSE
#define BT_TRACE_VERBOSE    FALSE
#endif

/* Enables or disables all trace messages. */
#ifndef BT_USE_TRACES
#define BT_USE_TRACES       TRUE
#endif


/******************************************************************************
**
** Trace Levels
**
** The following values may be used for different levels:
**      BT_TRACE_LEVEL_NONE    0        * No trace messages to be generated
**      BT_TRACE_LEVEL_ERROR   1        * Error condition trace messages
**      BT_TRACE_LEVEL_WARNING 2        * Warning condition trace messages
**      BT_TRACE_LEVEL_API     3        * API traces
**      BT_TRACE_LEVEL_EVENT   4        * Debug messages for events
**      BT_TRACE_LEVEL_DEBUG   5        * Debug messages (general)
******************************************************************************/

// btla-specific ++
/* Core Stack default trace levels */
#ifndef HCI_INITIAL_TRACE_LEVEL
#define HCI_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef BTM_INITIAL_TRACE_LEVEL
#define BTM_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef L2CAP_INITIAL_TRACE_LEVEL
#define L2CAP_INITIAL_TRACE_LEVEL           BT_TRACE_LEVEL_WARNING
#endif

#ifndef LLCP_INITIAL_TRACE_LEVEL
#define LLCP_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_WARNING
#endif

#ifndef AMP_INITIAL_TRACE_LEVEL
#define AMP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef RFCOMM_INITIAL_TRACE_LEVEL
#define RFCOMM_INITIAL_TRACE_LEVEL          BT_TRACE_LEVEL_WARNING
#endif

#ifndef OBX_INITIAL_TRACE_LEVEL
#define OBX_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef SDP_INITIAL_TRACE_LEVEL
#define SDP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef TCS_INITIAL_TRACE_LEVEL
#define TCS_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

/* Profile default trace levels */
#ifndef DUN_INITIAL_TRACE_LEVEL
#define DUN_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef GAP_INITIAL_TRACE_LEVEL
#define GAP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef GOEP_INITIAL_TRACE_LEVEL
#define GOEP_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_WARNING
#endif

#ifndef HSP2_INITIAL_TRACE_LEVEL
#define HSP2_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_WARNING
#endif

#ifndef SPP_INITIAL_TRACE_LEVEL
#define SPP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef ICP_INITIAL_TRACE_LEVEL
#define ICP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef CTP_INITIAL_TRACE_LEVEL
#define CTP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef HCRP_INITIAL_TRACE_LEVEL
#define HCRP_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_WARNING
#endif

#ifndef HCRPM_INITIAL_TRACE_LEVEL
#define HCRPM_INITIAL_TRACE_LEVEL           BT_TRACE_LEVEL_WARNING
#endif

#ifndef BPP_INITIAL_TRACE_LEVEL
#define BPP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef BIP_INITIAL_TRACE_LEVEL
#define BIP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef BNEP_INITIAL_TRACE_LEVEL
#define BNEP_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_WARNING
#endif

#ifndef PAN_INITIAL_TRACE_LEVEL
#define PAN_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef SAP_INITIAL_TRACE_LEVEL
#define SAP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef FTP_INITIAL_TRACE_LEVEL
#define FTP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef OPP_INITIAL_TRACE_LEVEL
#define OPP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef HFP_INITIAL_TRACE_LEVEL
#define HFP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef PAP_INITIAL_TRACE_LEVEL
#define PAP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef A2D_INITIAL_TRACE_LEVEL
#define A2D_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef VDP_INITIAL_TRACE_LEVEL
#define VDP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef AVDT_INITIAL_TRACE_LEVEL
#define AVDT_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_WARNING
#endif

#ifndef AVCT_INITIAL_TRACE_LEVEL
#define AVCT_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_WARNING
#endif

#ifndef AVRC_INITIAL_TRACE_LEVEL
#define AVRC_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_WARNING
#endif

#ifndef MCA_INITIAL_TRACE_LEVEL
#define MCA_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef HID_INITIAL_TRACE_LEVEL
#define HID_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

/* Application and other default trace levels */
#ifndef RPC_INITIAL_TRACE_LEVEL
#define RPC_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef APPL_INITIAL_TRACE_LEVEL
#define APPL_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_WARNING
#endif

#ifndef BT_TRACE_APPL
#define BT_TRACE_APPL   BT_USE_TRACES
#endif

#ifndef NFC_INITIAL_TRACE_LEVEL
#define NFC_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef GATT_INITIAL_TRACE_LEVEL
#define GATT_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif

#ifndef SMP_INITIAL_TRACE_LEVEL
#define SMP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_WARNING
#endif
// btla-specific --


#if (BTTRC_INCLUDED == TRUE)
/***************************************************************************************/
/* BTTRC MACROS */

#define BTTRC_EVENT(lid, event, state)   \
            {BTTRC_StackTrace1(lid, BTTRC_TYPE_EVENT, event, BTTRC_PARAM_UINT8, state);}
#define BTTRC_ACTION(lid, action)  \
            {BTTRC_StackTrace0(lid, BTTRC_TYPE_ACTION, action);}
#define BTTRC_STATE(lid, state)   \
            {BTTRC_StackTrace1(lid, BTTRC_TYPE_EVENT, BTTRC_TOKEN_SM_STATE, BTTRC_PARAM_UINT8, state);}

#define BTTRC_API0(lid, api)  \
            {BTTRC_StackTrace0(lid, BTTRC_TYPE_API, api);}
#define BTTRC_API1(lid, api, p1_t,p1_v)  \
            {BTTRC_StackTrace1(lid, BTTRC_TYPE_API, api, p1_t,p1_v);}
#define BTTRC_API2(lid, api, p1_t,p1_v,p2_t,p2_v)  \
            {BTTRC_StackTrace2(lid, BTTRC_TYPE_API, api, p1_t,p1_v,p2_t,p2_v);}
#define BTTRC_API3(lid, api, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v)  \
            {BTTRC_StackTrace3(lid, BTTRC_TYPE_API, api, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v);}
#define BTTRC_API4(lid, api, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v)  \
            {BTTRC_StackTrace4(lid, BTTRC_TYPE_API, api, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v);}
#define BTTRC_API5(lid, api, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v)  \
            {BTTRC_StackTrace5(lid, BTTRC_TYPE_API, api, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v);}
#define BTTRC_API6(lid, api, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v,p6_t,p6_v)  \
            {BTTRC_StackTrace6(lid, BTTRC_TYPE_API, api, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v,p6_t,p6_v);}


#define BTTRC_DBG0(lid, dbg)  \
            {BTTRC_StackTrace0(lid, BTTRC_TYPE_DBG, dbg);}
#define BTTRC_DBG1(lid, dbg, p1_t,p1_v)  \
            {BTTRC_StackTrace1(lid, BTTRC_TYPE_DBG, dbg, p1_t,p1_v);}
#define BTTRC_DBG2(lid, dbg, p1_t,p1_v,p2_t,p2_v)  \
            {BTTRC_StackTrace2(lid, BTTRC_TYPE_DBG, dbg, p1_t,p1_v,p2_t,p2_v);}
#define BTTRC_DBG3(lid, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v)  \
            {BTTRC_StackTrace3(lid, BTTRC_TYPE_DBG, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v);}
#define BTTRC_DBG4(lid, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v)  \
            {BTTRC_StackTrace4(lid, BTTRC_TYPE_DBG, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v);}
#define BTTRC_DBG5(lid, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v)  \
            {BTTRC_StackTrace5(lid, BTTRC_TYPE_DBG, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v);}
#define BTTRC_DBG6(lid, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v,p6_t,p6_v)  \
            {BTTRC_StackTrace6(lid, BTTRC_TYPE_DBG, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v,p6_t,p6_v);}

/***************************************************************************************/
/*AVDT MACROS */

#define BTTRC_AVDT_API0(api)   \
        BTTRC_API0(BTTRC_ID_STK_AVDT, api)
#define BTTRC_AVDT_API1(api, p1_t, p1_v) \
        BTTRC_API1(BTTRC_ID_STK_AVDT, api, p1_t, p1_v)
#define BTTRC_AVDT_API2(api, p1_t, p1_v, p2_t, p2_v) \
        BTTRC_API2(BTTRC_ID_STK_AVDT, api, p1_t, p1_v, p2_t, p2_v)
/***************************************************************************************/
/*AVDT_SCB MACROS */

#define BTTRC_AVDT_SCB_EVENT(event, state)   \
            BTTRC_EVENT(BTTRC_ID_AVDT_SCB, event, state)
#define BTTRC_AVDT_SCB_ACTION(action)  \
            BTTRC_ACTION(BTTRC_ID_AVDT_SCB, action)
#define BTTRC_AVDT_SCB_STATE(next_state)   \
            BTTRC_STATE(BTTRC_ID_AVDT_SCB, next_state)

#define BTTRC_AVDT_SCB_DBG0(dbg)  \
            BTTRC_DBG0(BTTRC_ID_AVDT_SCB, dbg)
#define BTTRC_AVDT_SCB_DBG1(dbg, p1_t,p1_v)  \
            BTTRC_DBG1(BTTRC_ID_AVDT_SCB, dbg, p1_t,p1_v)
#define BTTRC_AVDT_SCB_DBG2(dbg, p1_t,p1_v,p2_t,p2_v)  \
            BTTRC_DBG2(BTTRC_ID_AVDT_SCB, dbg, p1_t,p1_v,p2_t,p2_v)
#define BTTRC_AVDT_SCB_DBG3(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v)  \
            BTTRC_DBG3(BTTRC_ID_AVDT_SCB, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v)
#define BTTRC_AVDT_SCB_DBG4(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v)  \
            BTTRC_DBG4(BTTRC_ID_AVDT_SCB, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v)
#define BTTRC_AVDT_SCB_DBG5(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v)  \
            BTTRC_DBG5(BTTRC_ID_AVDT_SCB, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v)
#define BTTRC_AVDT_SCB_DBG6(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v,p6_t,p6_v)  \
            BTTRC_DBG6(BTTRC_ID_AVDT_SCB, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v,p6_t,p6_v)
/***************************************************************************************/
/*AVDT_CCB MACROS */

#define BTTRC_AVDT_CCB_EVENT(event, state)   \
            BTTRC_EVENT(BTTRC_ID_AVDT_CCB, event, state)
#define BTTRC_AVDT_CCB_ACTION(action)  \
            BTTRC_ACTION(BTTRC_ID_AVDT_CCB, action)
#define BTTRC_AVDT_CCB_STATE(next_state)   \
            BTTRC_STATE(BTTRC_ID_AVDT_CCB, next_state)

#define BTTRC_AVDT_CCB_DBG0(dbg)  \
            BTTRC_DBG0(BTTRC_ID_AVDT_CCB, dbg)
#define BTTRC_AVDT_CCB_DBG1(dbg, p1_t,p1_v)  \
            BTTRC_DBG1(BTTRC_ID_AVDT_CCB, dbg, p1_t,p1_v)
#define BTTRC_AVDT_CCB_DBG2(dbg, p1_t,p1_v,p2_t,p2_v)  \
            BTTRC_DBG2(BTTRC_ID_AVDT_CCB, dbg, p1_t,p1_v,p2_t,p2_v)
#define BTTRC_AVDT_CCB_DBG3(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v)  \
            BTTRC_DBG3(BTTRC_ID_AVDT_CCB, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v)
#define BTTRC_AVDT_CCB_DBG4(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v)  \
            BTTRC_DBG4(BTTRC_ID_AVDT_CCB, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v)
#define BTTRC_AVDT_CCB_DBG5(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v)  \
            BTTRC_DBG5(BTTRC_ID_AVDT_CCB, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v)
#define BTTRC_AVDT_CCB_DBG6(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v,p6_t,p6_v)  \
            BTTRC_DBG6(BTTRC_ID_AVDT_CCB, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v,p6_t,p6_v)
/***************************************************************************************/

#else /*BTTRC_INCLUDED*/

/***************************************************************************************/
/* BTTRC MACROS */

#define BTTRC_EVENT(lid, event, state)
#define BTTRC_ACTION(lid, action)
#define BTTRC_STATE(lid, state)

#define BTTRC_API0(lid, api)
#define BTTRC_API1(lid, api, p1_t, p1_v)
#define BTTRC_API2(lid, api, p1_t, p1_v, p2_t, p2_v)
#define BTTRC_API3(lid, api, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v)
#define BTTRC_API4(lid, api, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v)
#define BTTRC_API5(lid, api, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v)
#define BTTRC_API6(lid, api, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v,p6_t,p6_v)


#define BTTRC_DBG0(lid, dbg)
#define BTTRC_DBG1(lid, dbg, p1_t,p1_v)
#define BTTRC_DBG2(lid, dbg, p1_t,p1_v,p2_t,p2_v)
#define BTTRC_DBG3(lid, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v)
#define BTTRC_DBG4(lid, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v)
#define BTTRC_DBG5(lid, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v)
#define BTTRC_DBG6(lid, dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v,p6_t,p6_v)

/***************************************************************************************/
/*AVDT MACROS */
#define BTTRC_AVDT_API0(api)
#define BTTRC_AVDT_API1(api, p1_t,p1_v)
#define BTTRC_AVDT_API2(api, p1_t,p1_v,p2_t,p2_v)
/***************************************************************************************/
/*AVDT_SCB MACROS */

#define BTTRC_AVDT_SCB_EVENT(event, state)
#define BTTRC_AVDT_SCB_ACTION(action)
#define BTTRC_AVDT_SCB_STATE(next_state)

#define BTTRC_AVDT_SCB_DBG0(dbg)
#define BTTRC_AVDT_SCB_DBG1(dbg, p1_t,p1_v)
#define BTTRC_AVDT_SCB_DBG2(dbg, p1_t,p1_v,p2_t,p2_v)
#define BTTRC_AVDT_SCB_DBG3(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v)
#define BTTRC_AVDT_SCB_DBG4(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v)
#define BTTRC_AVDT_SCB_DBG5(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v)
#define BTTRC_AVDT_SCB_DBG6(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v,p6_t,p6_v)

/***************************************************************************************/
/*AVDT_CCB MACROS */

#define BTTRC_AVDT_CCB_EVENT(event, state)
#define BTTRC_AVDT_CCB_ACTION(action)
#define BTTRC_AVDT_CCB_STATE(next_state)

#define BTTRC_AVDT_CCB_DBG0(dbg)
#define BTTRC_AVDT_CCB_DBG1(dbg, p1_t,p1_v)
#define BTTRC_AVDT_CCB_DBG2(dbg, p1_t,p1_v,p2_t,p2_v)
#define BTTRC_AVDT_CCB_DBG3(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v)
#define BTTRC_AVDT_CCB_DBG4(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v)
#define BTTRC_AVDT_CCB_DBG5(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v)
#define BTTRC_AVDT_CCB_DBG6(dbg, p1_t,p1_v,p2_t,p2_v,p3_t,p3_v,p4_t,p4_v,p5_t,p5_v,p6_t,p6_v)

/***************************************************************************************/

#endif /*BTTRC_INCLUDED*/


#if (BT_USE_TRACES == TRUE)

#define BT_TRACE_0(l,t,m)                           LogMsg_0((TRACE_CTRL_GENERAL | (l) | TRACE_ORG_STACK | (t)),(m))
#define BT_TRACE_1(l,t,m,p1)                        LogMsg_1(TRACE_CTRL_GENERAL | (l) | TRACE_ORG_STACK | (t),(m),(UINT32)(p1))
#define BT_TRACE_2(l,t,m,p1,p2)                     LogMsg_2(TRACE_CTRL_GENERAL | (l) | TRACE_ORG_STACK | (t),(m),(UINT32)(p1),   \
                                                        (UINT32)(p2))
#define BT_TRACE_3(l,t,m,p1,p2,p3)                  LogMsg_3(TRACE_CTRL_GENERAL | (l) | TRACE_ORG_STACK | (t),(m),(UINT32)(p1),   \
                                                        (UINT32)(p2),(UINT32)(p3))
#define BT_TRACE_4(l,t,m,p1,p2,p3,p4)               LogMsg_4(TRACE_CTRL_GENERAL | (l) | TRACE_ORG_STACK | (t),(m),(UINT32)(p1),   \
                                                        (UINT32)(p2),(UINT32)(p3),(UINT32)(p4))
#define BT_TRACE_5(l,t,m,p1,p2,p3,p4,p5)            LogMsg_5(TRACE_CTRL_GENERAL | (l) | TRACE_ORG_STACK | (t),(m),(UINT32)(p1),   \
                                                        (UINT32)(p2),(UINT32)(p3),(UINT32)(p4), \
                                                        (UINT32)(p5))
#define BT_TRACE_6(l,t,m,p1,p2,p3,p4,p5,p6)         LogMsg_6(TRACE_CTRL_GENERAL | (l) | TRACE_ORG_STACK | (t),(m),(UINT32)(p1),   \
                                                        (UINT32)(p2),(UINT32)(p3),(UINT32)(p4), \
                                                        (UINT32)(p5),(UINT32)(p6))

#define BT_ERROR_TRACE_0(l,m)                     LogMsg_0(TRACE_CTRL_GENERAL | (l) | TRACE_ORG_STACK | TRACE_TYPE_ERROR,(m))
#define BT_ERROR_TRACE_1(l,m,p1)                  LogMsg_1(TRACE_CTRL_GENERAL | (l) | TRACE_ORG_STACK | TRACE_TYPE_ERROR,(m),(UINT32)(p1))
#define BT_ERROR_TRACE_2(l,m,p1,p2)               LogMsg_2(TRACE_CTRL_GENERAL | (l) | TRACE_ORG_STACK | TRACE_TYPE_ERROR,(m),(UINT32)(p1),(UINT32)(p2))
#define BT_ERROR_TRACE_3(l,m,p1,p2,p3)            LogMsg_3(TRACE_CTRL_GENERAL | (l) | TRACE_ORG_STACK | TRACE_TYPE_ERROR,(m),(UINT32)(p1),(UINT32)(p2),(UINT32)(p3))

/* Define tracing for the HCI unit
*/
#define HCI_TRACE_ERROR0(m)                     {if (btu_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_HCI, TRACE_TYPE_ERROR, m);}
#define HCI_TRACE_ERROR1(m,p1)                  {if (btu_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_HCI, TRACE_TYPE_ERROR, m,p1);}
#define HCI_TRACE_ERROR2(m,p1,p2)               {if (btu_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_HCI, TRACE_TYPE_ERROR, m,p1,p2);}
#define HCI_TRACE_ERROR3(m,p1,p2,p3)            {if (btu_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_HCI, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define HCI_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (btu_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_HCI, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define HCI_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (btu_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_HCI, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define HCI_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (btu_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_HCI, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define HCI_TRACE_WARNING0(m)                   {if (btu_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_HCI, TRACE_TYPE_WARNING, m);}
#define HCI_TRACE_WARNING1(m,p1)                {if (btu_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_HCI, TRACE_TYPE_WARNING, m,p1);}
#define HCI_TRACE_WARNING2(m,p1,p2)             {if (btu_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_HCI, TRACE_TYPE_WARNING, m,p1,p2);}
#define HCI_TRACE_WARNING3(m,p1,p2,p3)          {if (btu_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_HCI, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define HCI_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (btu_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_HCI, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define HCI_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (btu_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_HCI, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define HCI_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (btu_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_HCI, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define HCI_TRACE_EVENT0(m)                     {if (btu_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_HCI, TRACE_TYPE_EVENT, m);}
#define HCI_TRACE_EVENT1(m,p1)                  {if (btu_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_HCI, TRACE_TYPE_EVENT, m, p1);}
#define HCI_TRACE_EVENT2(m,p1,p2)               {if (btu_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_HCI, TRACE_TYPE_EVENT, m,p1,p2);}
#define HCI_TRACE_EVENT3(m,p1,p2,p3)            {if (btu_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_HCI, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define HCI_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (btu_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_HCI, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define HCI_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (btu_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_HCI, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define HCI_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (btu_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_HCI, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define HCI_TRACE_DEBUG0(m)                     {if (btu_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_HCI, TRACE_TYPE_DEBUG, m);}
#define HCI_TRACE_DEBUG1(m,p1)                  {if (btu_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_HCI, TRACE_TYPE_DEBUG, m,p1);}
#define HCI_TRACE_DEBUG2(m,p1,p2)               {if (btu_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_HCI, TRACE_TYPE_DEBUG, m,p1,p2);}
#define HCI_TRACE_DEBUG3(m,p1,p2,p3)            {if (btu_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_HCI, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define HCI_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (btu_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_HCI, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define HCI_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (btu_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_HCI, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define HCI_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (btu_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_HCI, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}


/* Define tracing for BTM
*/
#define BTM_TRACE_ERROR0(m)                     {if (btm_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_BTM, TRACE_TYPE_ERROR, m);}
#define BTM_TRACE_ERROR1(m,p1)                  {if (btm_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_BTM, TRACE_TYPE_ERROR, m,p1);}
#define BTM_TRACE_ERROR2(m,p1,p2)               {if (btm_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_BTM, TRACE_TYPE_ERROR, m,p1,p2);}
#define BTM_TRACE_ERROR3(m,p1,p2,p3)            {if (btm_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_BTM, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define BTM_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (btm_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_BTM, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define BTM_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (btm_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_BTM, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define BTM_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (btm_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_BTM, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define BTM_TRACE_WARNING0(m)                   {if (btm_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_BTM, TRACE_TYPE_WARNING, m);}
#define BTM_TRACE_WARNING1(m,p1)                {if (btm_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_BTM, TRACE_TYPE_WARNING, m,p1);}
#define BTM_TRACE_WARNING2(m,p1,p2)             {if (btm_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_BTM, TRACE_TYPE_WARNING, m,p1,p2);}
#define BTM_TRACE_WARNING3(m,p1,p2,p3)          {if (btm_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_BTM, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define BTM_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (btm_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_BTM, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define BTM_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (btm_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_BTM, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define BTM_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (btm_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_BTM, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define BTM_TRACE_API0(m)                       {if (btm_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_BTM, TRACE_TYPE_API, m);}
#define BTM_TRACE_API1(m,p1)                    {if (btm_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_BTM, TRACE_TYPE_API, m, p1);}
#define BTM_TRACE_API2(m,p1,p2)                 {if (btm_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_BTM, TRACE_TYPE_API, m,p1,p2);}
#define BTM_TRACE_API3(m,p1,p2,p3)              {if (btm_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_BTM, TRACE_TYPE_API, m,p1,p2,p3);}
#define BTM_TRACE_API4(m,p1,p2,p3,p4)           {if (btm_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_BTM, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define BTM_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (btm_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_BTM, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define BTM_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (btm_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_BTM, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define BTM_TRACE_EVENT0(m)                     {if (btm_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_BTM, TRACE_TYPE_EVENT, m);}
#define BTM_TRACE_EVENT1(m,p1)                  {if (btm_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_BTM, TRACE_TYPE_EVENT, m, p1);}
#define BTM_TRACE_EVENT2(m,p1,p2)               {if (btm_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_BTM, TRACE_TYPE_EVENT, m,p1,p2);}
#define BTM_TRACE_EVENT3(m,p1,p2,p3)            {if (btm_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_BTM, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define BTM_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (btm_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_BTM, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define BTM_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (btm_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_BTM, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define BTM_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (btm_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_BTM, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define BTM_TRACE_DEBUG0(m)                     {if (btm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_BTM, TRACE_TYPE_DEBUG, m);}
#define BTM_TRACE_DEBUG1(m,p1)                  {if (btm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_BTM, TRACE_TYPE_DEBUG, m,p1);}
#define BTM_TRACE_DEBUG2(m,p1,p2)               {if (btm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_BTM, TRACE_TYPE_DEBUG, m,p1,p2);}
#define BTM_TRACE_DEBUG3(m,p1,p2,p3)            {if (btm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_BTM, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define BTM_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (btm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_BTM, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define BTM_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (btm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_BTM, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define BTM_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (btm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_BTM, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}


/* Define tracing for the L2CAP unit
*/
#define L2CAP_TRACE_ERROR0(m)                     {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_L2CAP, TRACE_TYPE_ERROR, m);}
#define L2CAP_TRACE_ERROR1(m,p1)                  {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_L2CAP, TRACE_TYPE_ERROR, m,p1);}
#define L2CAP_TRACE_ERROR2(m,p1,p2)               {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_L2CAP, TRACE_TYPE_ERROR, m,p1,p2);}
#define L2CAP_TRACE_ERROR3(m,p1,p2,p3)            {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_L2CAP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define L2CAP_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_L2CAP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define L2CAP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_L2CAP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define L2CAP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_L2CAP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define L2CAP_TRACE_WARNING0(m)                   {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_L2CAP, TRACE_TYPE_WARNING, m);}
#define L2CAP_TRACE_WARNING1(m,p1)                {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_L2CAP, TRACE_TYPE_WARNING, m,p1);}
#define L2CAP_TRACE_WARNING2(m,p1,p2)             {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_L2CAP, TRACE_TYPE_WARNING, m,p1,p2);}
#define L2CAP_TRACE_WARNING3(m,p1,p2,p3)          {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_L2CAP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define L2CAP_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_L2CAP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define L2CAP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_L2CAP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define L2CAP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_L2CAP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define L2CAP_TRACE_API0(m)                       {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_L2CAP, TRACE_TYPE_API, m);}
#define L2CAP_TRACE_API1(m,p1)                    {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_L2CAP, TRACE_TYPE_API, m,p1);}
#define L2CAP_TRACE_API2(m,p1,p2)                 {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_L2CAP, TRACE_TYPE_API, m,p1,p2);}
#define L2CAP_TRACE_API3(m,p1,p2,p3)              {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_L2CAP, TRACE_TYPE_API, m,p1,p2,p3);}
#define L2CAP_TRACE_API4(m,p1,p2,p3,p4)           {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_L2CAP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define L2CAP_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_L2CAP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define L2CAP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_L2CAP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define L2CAP_TRACE_EVENT0(m)                     {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_L2CAP, TRACE_TYPE_EVENT, m);}
#define L2CAP_TRACE_EVENT1(m,p1)                  {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_L2CAP, TRACE_TYPE_EVENT, m, p1);}
#define L2CAP_TRACE_EVENT2(m,p1,p2)               {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_L2CAP, TRACE_TYPE_EVENT, m,p1,p2);}
#define L2CAP_TRACE_EVENT3(m,p1,p2,p3)            {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_L2CAP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define L2CAP_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_L2CAP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define L2CAP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_L2CAP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define L2CAP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_L2CAP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define L2CAP_TRACE_DEBUG0(m)                     {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_L2CAP, TRACE_TYPE_DEBUG, m);}
#define L2CAP_TRACE_DEBUG1(m,p1)                  {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_L2CAP, TRACE_TYPE_DEBUG, m,p1);}
#define L2CAP_TRACE_DEBUG2(m,p1,p2)               {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_L2CAP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define L2CAP_TRACE_DEBUG3(m,p1,p2,p3)            {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_L2CAP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define L2CAP_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_L2CAP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define L2CAP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_L2CAP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define L2CAP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (l2cb.l2cap_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_L2CAP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the LLCP unit
*/
#define LLCP_TRACE_ERROR0(m)                     {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_LLCP, TRACE_TYPE_ERROR, m);}
#define LLCP_TRACE_ERROR1(m,p1)                  {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_LLCP, TRACE_TYPE_ERROR, m,p1);}
#define LLCP_TRACE_ERROR2(m,p1,p2)               {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_LLCP, TRACE_TYPE_ERROR, m,p1,p2);}
#define LLCP_TRACE_ERROR3(m,p1,p2,p3)            {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_LLCP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define LLCP_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_LLCP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define LLCP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_LLCP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define LLCP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_LLCP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define LLCP_TRACE_WARNING0(m)                   {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_LLCP, TRACE_TYPE_WARNING, m);}
#define LLCP_TRACE_WARNING1(m,p1)                {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_LLCP, TRACE_TYPE_WARNING, m,p1);}
#define LLCP_TRACE_WARNING2(m,p1,p2)             {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_LLCP, TRACE_TYPE_WARNING, m,p1,p2);}
#define LLCP_TRACE_WARNING3(m,p1,p2,p3)          {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_LLCP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define LLCP_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_LLCP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define LLCP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_LLCP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define LLCP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_LLCP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define LLCP_TRACE_API0(m)                       {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_LLCP, TRACE_TYPE_API, m);}
#define LLCP_TRACE_API1(m,p1)                    {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_LLCP, TRACE_TYPE_API, m,p1);}
#define LLCP_TRACE_API2(m,p1,p2)                 {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_LLCP, TRACE_TYPE_API, m,p1,p2);}
#define LLCP_TRACE_API3(m,p1,p2,p3)              {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_LLCP, TRACE_TYPE_API, m,p1,p2,p3);}
#define LLCP_TRACE_API4(m,p1,p2,p3,p4)           {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_LLCP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define LLCP_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_LLCP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define LLCP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_LLCP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define LLCP_TRACE_EVENT0(m)                     {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_LLCP, TRACE_TYPE_EVENT, m);}
#define LLCP_TRACE_EVENT1(m,p1)                  {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_LLCP, TRACE_TYPE_EVENT, m, p1);}
#define LLCP_TRACE_EVENT2(m,p1,p2)               {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_LLCP, TRACE_TYPE_EVENT, m,p1,p2);}
#define LLCP_TRACE_EVENT3(m,p1,p2,p3)            {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_LLCP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define LLCP_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_LLCP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define LLCP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_LLCP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define LLCP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_LLCP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define LLCP_TRACE_DEBUG0(m)                     {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_LLCP, TRACE_TYPE_DEBUG, m);}
#define LLCP_TRACE_DEBUG1(m,p1)                  {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_LLCP, TRACE_TYPE_DEBUG, m,p1);}
#define LLCP_TRACE_DEBUG2(m,p1,p2)               {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_LLCP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define LLCP_TRACE_DEBUG3(m,p1,p2,p3)            {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_LLCP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define LLCP_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_LLCP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define LLCP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_LLCP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define LLCP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (llcp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_LLCP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the SDP unit
*/
#define SDP_TRACE_ERROR0(m)                     {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_SDP, TRACE_TYPE_ERROR, m);}
#define SDP_TRACE_ERROR1(m,p1)                  {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_SDP, TRACE_TYPE_ERROR, m,p1);}
#define SDP_TRACE_ERROR2(m,p1,p2)               {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_SDP, TRACE_TYPE_ERROR, m,p1,p2);}
#define SDP_TRACE_ERROR3(m,p1,p2,p3)            {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_SDP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define SDP_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_SDP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define SDP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_SDP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define SDP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_SDP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define SDP_TRACE_WARNING0(m)                   {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_SDP, TRACE_TYPE_WARNING, m);}
#define SDP_TRACE_WARNING1(m,p1)                {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_SDP, TRACE_TYPE_WARNING, m,p1);}
#define SDP_TRACE_WARNING2(m,p1,p2)             {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_SDP, TRACE_TYPE_WARNING, m,p1,p2);}
#define SDP_TRACE_WARNING3(m,p1,p2,p3)          {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_SDP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define SDP_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_SDP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define SDP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_SDP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define SDP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_SDP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define SDP_TRACE_API0(m)                       {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_SDP, TRACE_TYPE_API, m);}
#define SDP_TRACE_API1(m,p1)                    {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_SDP, TRACE_TYPE_API, m,p1);}
#define SDP_TRACE_API2(m,p1,p2)                 {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_SDP, TRACE_TYPE_API, m,p1,p2);}
#define SDP_TRACE_API3(m,p1,p2,p3)              {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_SDP, TRACE_TYPE_API, m,p1,p2,p3);}
#define SDP_TRACE_API4(m,p1,p2,p3,p4)           {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_SDP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define SDP_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_SDP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define SDP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_SDP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define SDP_TRACE_EVENT0(m)                     {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_SDP, TRACE_TYPE_EVENT, m);}
#define SDP_TRACE_EVENT1(m,p1)                  {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_SDP, TRACE_TYPE_EVENT, m, p1);}
#define SDP_TRACE_EVENT2(m,p1,p2)               {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_SDP, TRACE_TYPE_EVENT, m,p1,p2);}
#define SDP_TRACE_EVENT3(m,p1,p2,p3)            {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_SDP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define SDP_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_SDP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define SDP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_SDP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define SDP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_SDP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define SDP_TRACE_DEBUG0(m)                     {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_SDP, TRACE_TYPE_DEBUG, m);}
#define SDP_TRACE_DEBUG1(m,p1)                  {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_SDP, TRACE_TYPE_DEBUG, m,p1);}
#define SDP_TRACE_DEBUG2(m,p1,p2)               {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_SDP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define SDP_TRACE_DEBUG3(m,p1,p2,p3)            {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_SDP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define SDP_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_SDP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define SDP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_SDP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define SDP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (sdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_SDP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the RFCOMM unit
*/
#define RFCOMM_TRACE_ERROR0(m)                     {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_RFCOMM, TRACE_TYPE_ERROR, m);}
#define RFCOMM_TRACE_ERROR1(m,p1)                  {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_RFCOMM, TRACE_TYPE_ERROR, m,p1);}
#define RFCOMM_TRACE_ERROR2(m,p1,p2)               {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_RFCOMM, TRACE_TYPE_ERROR, m,p1,p2);}
#define RFCOMM_TRACE_ERROR3(m,p1,p2,p3)            {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_RFCOMM, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define RFCOMM_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_RFCOMM, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define RFCOMM_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_RFCOMM, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define RFCOMM_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_RFCOMM, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define RFCOMM_TRACE_WARNING0(m)                   {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_RFCOMM, TRACE_TYPE_WARNING, m);}
#define RFCOMM_TRACE_WARNING1(m,p1)                {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_RFCOMM, TRACE_TYPE_WARNING, m,p1);}
#define RFCOMM_TRACE_WARNING2(m,p1,p2)             {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_RFCOMM, TRACE_TYPE_WARNING, m,p1,p2);}
#define RFCOMM_TRACE_WARNING3(m,p1,p2,p3)          {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_RFCOMM, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define RFCOMM_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_RFCOMM, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define RFCOMM_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_RFCOMM, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define RFCOMM_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_RFCOMM, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define RFCOMM_TRACE_API0(m)                       {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_RFCOMM, TRACE_TYPE_API, m);}
#define RFCOMM_TRACE_API1(m,p1)                    {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_RFCOMM, TRACE_TYPE_API, m,p1);}
#define RFCOMM_TRACE_API2(m,p1,p2)                 {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_RFCOMM, TRACE_TYPE_API, m,p1,p2);}
#define RFCOMM_TRACE_API3(m,p1,p2,p3)              {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_RFCOMM, TRACE_TYPE_API, m,p1,p2,p3);}
#define RFCOMM_TRACE_API4(m,p1,p2,p3,p4)           {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_RFCOMM, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define RFCOMM_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_RFCOMM, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define RFCOMM_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_RFCOMM, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define RFCOMM_TRACE_EVENT0(m)                     {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_RFCOMM, TRACE_TYPE_EVENT, m);}
#define RFCOMM_TRACE_EVENT1(m,p1)                  {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_RFCOMM, TRACE_TYPE_EVENT, m, p1);}
#define RFCOMM_TRACE_EVENT2(m,p1,p2)               {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_RFCOMM, TRACE_TYPE_EVENT, m,p1,p2);}
#define RFCOMM_TRACE_EVENT3(m,p1,p2,p3)            {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_RFCOMM, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define RFCOMM_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_RFCOMM, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define RFCOMM_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_RFCOMM, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define RFCOMM_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_RFCOMM, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define RFCOMM_TRACE_DEBUG0(m)                     {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_RFCOMM, TRACE_TYPE_DEBUG, m);}
#define RFCOMM_TRACE_DEBUG1(m,p1)                  {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_RFCOMM, TRACE_TYPE_DEBUG, m,p1);}
#define RFCOMM_TRACE_DEBUG2(m,p1,p2)               {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_RFCOMM, TRACE_TYPE_DEBUG, m,p1,p2);}
#define RFCOMM_TRACE_DEBUG3(m,p1,p2,p3)            {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_RFCOMM, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define RFCOMM_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_RFCOMM, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define RFCOMM_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_RFCOMM, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define RFCOMM_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (rfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_RFCOMM, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for Serial Port Profile
*/
#define SPP_TRACE_ERROR0(m)                     {if (spp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_SPP, TRACE_TYPE_ERROR, m);}
#define SPP_TRACE_ERROR1(m,p1)                  {if (spp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_SPP, TRACE_TYPE_ERROR, m,p1);}
#define SPP_TRACE_ERROR2(m,p1,p2)               {if (spp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_SPP, TRACE_TYPE_ERROR, m,p1,p2);}
#define SPP_TRACE_ERROR3(m,p1,p2,p3)            {if (spp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_SPP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define SPP_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (spp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_SPP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define SPP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (spp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_SPP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define SPP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (spp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_SPP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define SPP_TRACE_WARNING0(m)                   {if (spp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_SPP, TRACE_TYPE_WARNING, m);}
#define SPP_TRACE_WARNING1(m,p1)                {if (spp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_SPP, TRACE_TYPE_WARNING, m,p1);}
#define SPP_TRACE_WARNING2(m,p1,p2)             {if (spp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_SPP, TRACE_TYPE_WARNING, m,p1,p2);}
#define SPP_TRACE_WARNING3(m,p1,p2,p3)          {if (spp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_SPP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define SPP_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (spp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_SPP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define SPP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (spp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_SPP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define SPP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (spp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_SPP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define SPP_TRACE_EVENT0(m)                     {if (spp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_SPP, TRACE_TYPE_EVENT, m);}
#define SPP_TRACE_EVENT1(m,p1)                  {if (spp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_SPP, TRACE_TYPE_EVENT, m, p1);}
#define SPP_TRACE_EVENT2(m,p1,p2)               {if (spp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_SPP, TRACE_TYPE_EVENT, m,p1,p2);}
#define SPP_TRACE_EVENT3(m,p1,p2,p3)            {if (spp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_SPP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define SPP_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (spp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_SPP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define SPP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (spp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_SPP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define SPP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (spp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_SPP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define SPP_TRACE_API0(m)                       {if (spp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_SPP, TRACE_TYPE_API, m);}
#define SPP_TRACE_API1(m,p1)                    {if (spp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_SPP, TRACE_TYPE_API, m, p1);}
#define SPP_TRACE_API2(m,p1,p2)                 {if (spp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_SPP, TRACE_TYPE_API, m,p1,p2);}
#define SPP_TRACE_API3(m,p1,p2,p3)              {if (spp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_SPP, TRACE_TYPE_API, m,p1,p2,p3);}
#define SPP_TRACE_API4(m,p1,p2,p3,p4)           {if (spp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_SPP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define SPP_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (spp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_SPP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define SPP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (spp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_SPP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define SPP_TRACE_DEBUG0(m)                     {if (spp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_SPP, TRACE_TYPE_DEBUG, m);}
#define SPP_TRACE_DEBUG1(m,p1)                  {if (spp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_SPP, TRACE_TYPE_DEBUG, m,p1);}
#define SPP_TRACE_DEBUG2(m,p1,p2)               {if (spp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_SPP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define SPP_TRACE_DEBUG3(m,p1,p2,p3)            {if (spp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_SPP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define SPP_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (spp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_SPP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define SPP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (spp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_SPP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define SPP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (spp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_SPP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* Generic Access Profile traces */
#define GAP_TRACE_ERROR0(m)                     {if (gap_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_GAP, TRACE_TYPE_ERROR, m);}
#define GAP_TRACE_ERROR1(m,p1)                  {if (gap_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_GAP, TRACE_TYPE_ERROR, m, p1);}
#define GAP_TRACE_ERROR2(m,p1,p2)               {if (gap_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_GAP, TRACE_TYPE_ERROR, m,p1,p2);}
#define GAP_TRACE_ERROR3(m,p1,p2,p3)            {if (gap_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_GAP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define GAP_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (gap_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_GAP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define GAP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (gap_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_GAP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define GAP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (gap_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_GAP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define GAP_TRACE_EVENT0(m)                     {if (gap_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_GAP, TRACE_TYPE_EVENT, m);}
#define GAP_TRACE_EVENT1(m,p1)                  {if (gap_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_GAP, TRACE_TYPE_EVENT, m, p1);}
#define GAP_TRACE_EVENT2(m,p1,p2)               {if (gap_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_GAP, TRACE_TYPE_EVENT, m,p1,p2);}
#define GAP_TRACE_EVENT3(m,p1,p2,p3)            {if (gap_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_GAP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define GAP_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (gap_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_GAP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define GAP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (gap_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_GAP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define GAP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (gap_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_GAP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define GAP_TRACE_API0(m)                       {if (gap_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_GAP, TRACE_TYPE_API, m);}
#define GAP_TRACE_API1(m,p1)                    {if (gap_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_GAP, TRACE_TYPE_API, m, p1);}
#define GAP_TRACE_API2(m,p1,p2)                 {if (gap_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_GAP, TRACE_TYPE_API, m,p1,p2);}
#define GAP_TRACE_API3(m,p1,p2,p3)              {if (gap_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_GAP, TRACE_TYPE_API, m,p1,p2,p3);}
#define GAP_TRACE_API4(m,p1,p2,p3,p4)           {if (gap_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_GAP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define GAP_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (gap_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_GAP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define GAP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (gap_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_GAP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define GAP_TRACE_WARNING0(m)                   {if (gap_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_GAP, TRACE_TYPE_WARNING, m);}
#define GAP_TRACE_WARNING1(m,p1)                {if (gap_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_GAP, TRACE_TYPE_WARNING, m, p1);}
#define GAP_TRACE_WARNING2(m,p1,p2)             {if (gap_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_GAP, TRACE_TYPE_WARNING, m,p1,p2);}
#define GAP_TRACE_WARNING3(m,p1,p2,p3)          {if (gap_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_GAP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define GAP_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (gap_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_GAP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define GAP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (gap_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_GAP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define GAP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (gap_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_GAP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}


/* Define tracing for OBX
*/
#define OBX_TRACE_ERROR0(m)                      {if (obx_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_OBEX, TRACE_TYPE_ERROR, m);}
#define OBX_TRACE_ERROR1(m,p1)                   {if (obx_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_OBEX, TRACE_TYPE_ERROR, m,p1);}
#define OBX_TRACE_ERROR2(m,p1,p2)                {if (obx_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_OBEX, TRACE_TYPE_ERROR, m,p1,p2);}
#define OBX_TRACE_ERROR3(m,p1,p2,p3)             {if (obx_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_OBEX, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define OBX_TRACE_ERROR4(m,p1,p2,p3,p4)          {if (obx_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_OBEX, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define OBX_TRACE_ERROR5(m,p1,p2,p3,p4,p5)       {if (obx_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_OBEX, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define OBX_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)    {if (obx_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_OBEX, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define OBX_TRACE_WARNING0(m)                    {if (obx_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_OBEX, TRACE_TYPE_WARNING, m);}
#define OBX_TRACE_WARNING1(m,p1)                 {if (obx_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_OBEX, TRACE_TYPE_WARNING, m,p1);}
#define OBX_TRACE_WARNING2(m,p1,p2)              {if (obx_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_OBEX, TRACE_TYPE_WARNING, m,p1,p2);}
#define OBX_TRACE_WARNING3(m,p1,p2,p3)           {if (obx_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_OBEX, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define OBX_TRACE_WARNING4(m,p1,p2,p3,p4)        {if (obx_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_OBEX, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define OBX_TRACE_WARNING5(m,p1,p2,p3,p4,p5)     {if (obx_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_OBEX, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define OBX_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)  {if (obx_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_OBEX, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define OBX_TRACE_EVENT0(m)                      {if (obx_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_OBEX, TRACE_TYPE_EVENT, m);}
#define OBX_TRACE_EVENT1(m,p1)                   {if (obx_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_OBEX, TRACE_TYPE_EVENT, m, p1);}
#define OBX_TRACE_EVENT2(m,p1,p2)                {if (obx_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_OBEX, TRACE_TYPE_EVENT, m,p1,p2);}
#define OBX_TRACE_EVENT3(m,p1,p2,p3)             {if (obx_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_OBEX, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define OBX_TRACE_EVENT4(m,p1,p2,p3,p4)          {if (obx_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_OBEX, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define OBX_TRACE_EVENT5(m,p1,p2,p3,p4,p5)       {if (obx_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_OBEX, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define OBX_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)    {if (obx_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_OBEX, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define OBX_TRACE_DEBUG0(m)                      {if (obx_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_OBEX, TRACE_TYPE_DEBUG, m);}
#define OBX_TRACE_DEBUG1(m,p1)                   {if (obx_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_OBEX, TRACE_TYPE_DEBUG, m,p1);}
#define OBX_TRACE_DEBUG2(m,p1,p2)                {if (obx_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_OBEX, TRACE_TYPE_DEBUG, m,p1,p2);}
#define OBX_TRACE_DEBUG3(m,p1,p2,p3)             {if (obx_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_OBEX, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define OBX_TRACE_DEBUG4(m,p1,p2,p3,p4)          {if (obx_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_OBEX, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define OBX_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)       {if (obx_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_OBEX, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define OBX_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)    {if (obx_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_OBEX, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

#define OBX_TRACE_API0(m)                        {if (obx_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_OBEX, TRACE_TYPE_API, m);}
#define OBX_TRACE_API1(m,p1)                     {if (obx_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_OBEX, TRACE_TYPE_API, m, p1);}
#define OBX_TRACE_API2(m,p1,p2)                  {if (obx_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_OBEX, TRACE_TYPE_API, m,p1,p2);}
#define OBX_TRACE_API3(m,p1,p2,p3)               {if (obx_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_OBEX, TRACE_TYPE_API, m,p1,p2,p3);}
#define OBX_TRACE_API4(m,p1,p2,p3,p4)            {if (obx_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_OBEX, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define OBX_TRACE_API5(m,p1,p2,p3,p4,p5)         {if (obx_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_OBEX, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define OBX_TRACE_API6(m,p1,p2,p3,p4,p5,p6)      {if (obx_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_OBEX, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for OBEX application profiles
*/
#define GOEP_TRACE_ERROR0(m)                     {if (goep_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_GOEP, TRACE_TYPE_ERROR, m);}
#define GOEP_TRACE_ERROR1(m,p1)                  {if (goep_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_GOEP, TRACE_TYPE_ERROR, m,p1);}
#define GOEP_TRACE_ERROR2(m,p1,p2)               {if (goep_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_GOEP, TRACE_TYPE_ERROR, m,p1,p2);}
#define GOEP_TRACE_ERROR3(m,p1,p2,p3)            {if (goep_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_GOEP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define GOEP_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (goep_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_GOEP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define GOEP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (goep_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_GOEP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define GOEP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (goep_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_GOEP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define GOEP_TRACE_WARNING0(m)                   {if (goep_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_GOEP, TRACE_TYPE_WARNING, m);}
#define GOEP_TRACE_WARNING1(m,p1)                {if (goep_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_GOEP, TRACE_TYPE_WARNING, m,p1);}
#define GOEP_TRACE_WARNING2(m,p1,p2)             {if (goep_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_GOEP, TRACE_TYPE_WARNING, m,p1,p2);}
#define GOEP_TRACE_WARNING3(m,p1,p2,p3)          {if (goep_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_GOEP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define GOEP_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (goep_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_GOEP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define GOEP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (goep_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_GOEP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define GOEP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (goep_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_GOEP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define GOEP_TRACE_EVENT0(m)                     {if (goep_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_GOEP, TRACE_TYPE_EVENT, m);}
#define GOEP_TRACE_EVENT1(m,p1)                  {if (goep_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_GOEP, TRACE_TYPE_EVENT, m, p1);}
#define GOEP_TRACE_EVENT2(m,p1,p2)               {if (goep_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_GOEP, TRACE_TYPE_EVENT, m,p1,p2);}
#define GOEP_TRACE_EVENT3(m,p1,p2,p3)            {if (goep_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_GOEP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define GOEP_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (goep_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_GOEP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define GOEP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (goep_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_GOEP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define GOEP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (goep_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_GOEP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define GOEP_TRACE_DEBUG0(m)                     {if (goep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_GOEP, TRACE_TYPE_DEBUG, m);}
#define GOEP_TRACE_DEBUG1(m,p1)                  {if (goep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_GOEP, TRACE_TYPE_DEBUG, m,p1);}
#define GOEP_TRACE_DEBUG2(m,p1,p2)               {if (goep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_GOEP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define GOEP_TRACE_DEBUG3(m,p1,p2,p3)            {if (goep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_GOEP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define GOEP_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (goep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_GOEP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define GOEP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (goep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_GOEP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define GOEP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (goep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_GOEP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

#define GOEP_TRACE_API0(m)                       {if (goep_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_GOEP, TRACE_TYPE_API, m);}
#define GOEP_TRACE_API1(m,p1)                    {if (goep_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_GOEP, TRACE_TYPE_API, m, p1);}
#define GOEP_TRACE_API2(m,p1,p2)                 {if (goep_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_GOEP, TRACE_TYPE_API, m,p1,p2);}
#define GOEP_TRACE_API3(m,p1,p2,p3)              {if (goep_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_GOEP, TRACE_TYPE_API, m,p1,p2,p3);}
#define GOEP_TRACE_API4(m,p1,p2,p3,p4)           {if (goep_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_GOEP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define GOEP_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (goep_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_GOEP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define GOEP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (goep_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_GOEP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the BPP profile
*/
#define BPP_TRACE_ERROR0(m)                      {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_BPP, TRACE_TYPE_ERROR, m);}
#define BPP_TRACE_ERROR1(m,p1)                   {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_BPP, TRACE_TYPE_ERROR, m,p1);}
#define BPP_TRACE_ERROR2(m,p1,p2)                {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_BPP, TRACE_TYPE_ERROR, m,p1,p2);}
#define BPP_TRACE_ERROR3(m,p1,p2,p3)             {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_BPP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define BPP_TRACE_ERROR4(m,p1,p2,p3,p4)          {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_BPP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define BPP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)       {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_BPP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define BPP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)    {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_BPP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define BPP_TRACE_WARNING0(m)                    {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_BPP, TRACE_TYPE_WARNING, m);}
#define BPP_TRACE_WARNING1(m,p1)                 {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_BPP, TRACE_TYPE_WARNING, m,p1);}
#define BPP_TRACE_WARNING2(m,p1,p2)              {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_BPP, TRACE_TYPE_WARNING, m,p1,p2);}
#define BPP_TRACE_WARNING3(m,p1,p2,p3)           {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_BPP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define BPP_TRACE_WARNING4(m,p1,p2,p3,p4)        {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_BPP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define BPP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)     {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_BPP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define BPP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)  {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_BPP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define BPP_TRACE_EVENT0(m)                      {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_BPP, TRACE_TYPE_EVENT, m);}
#define BPP_TRACE_EVENT1(m,p1)                   {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_BPP, TRACE_TYPE_EVENT, m, p1);}
#define BPP_TRACE_EVENT2(m,p1,p2)                {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_BPP, TRACE_TYPE_EVENT, m,p1,p2);}
#define BPP_TRACE_EVENT3(m,p1,p2,p3)             {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_BPP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define BPP_TRACE_EVENT4(m,p1,p2,p3,p4)          {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_BPP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define BPP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)       {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_BPP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define BPP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)    {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_BPP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define BPP_TRACE_DEBUG0(m)                      {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_BPP, TRACE_TYPE_DEBUG, m);}
#define BPP_TRACE_DEBUG1(m,p1)                   {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_BPP, TRACE_TYPE_DEBUG, m,p1);}
#define BPP_TRACE_DEBUG2(m,p1,p2)                {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_BPP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define BPP_TRACE_DEBUG3(m,p1,p2,p3)             {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_BPP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define BPP_TRACE_DEBUG4(m,p1,p2,p3,p4)          {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_BPP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define BPP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)       {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_BPP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define BPP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)    {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_BPP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

#define BPP_TRACE_API0(m)                        {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_BPP, TRACE_TYPE_API, m);}
#define BPP_TRACE_API1(m,p1)                     {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_BPP, TRACE_TYPE_API, m, p1);}
#define BPP_TRACE_API2(m,p1,p2)                  {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_BPP, TRACE_TYPE_API, m,p1,p2);}
#define BPP_TRACE_API3(m,p1,p2,p3)               {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_BPP, TRACE_TYPE_API, m,p1,p2,p3);}
#define BPP_TRACE_API4(m,p1,p2,p3,p4)            {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_BPP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define BPP_TRACE_API5(m,p1,p2,p3,p4,p5)         {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_BPP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define BPP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)      {if (bpp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_BPP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the BIP profile
*/
#define BIP_TRACE_ERROR0(m)                      {if (bip_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_BIP, TRACE_TYPE_ERROR, m);}
#define BIP_TRACE_ERROR1(m,p1)                   {if (bip_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_BIP, TRACE_TYPE_ERROR, m,p1);}
#define BIP_TRACE_ERROR2(m,p1,p2)                {if (bip_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_BIP, TRACE_TYPE_ERROR, m,p1,p2);}
#define BIP_TRACE_ERROR3(m,p1,p2,p3)             {if (bip_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_BIP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define BIP_TRACE_ERROR4(m,p1,p2,p3,p4)          {if (bip_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_BIP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define BIP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)       {if (bip_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_BIP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define BIP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)    {if (bip_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_BIP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define BIP_TRACE_WARNING0(m)                    {if (bip_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_BIP, TRACE_TYPE_WARNING, m);}
#define BIP_TRACE_WARNING1(m,p1)                 {if (bip_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_BIP, TRACE_TYPE_WARNING, m,p1);}
#define BIP_TRACE_WARNING2(m,p1,p2)              {if (bip_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_BIP, TRACE_TYPE_WARNING, m,p1,p2);}
#define BIP_TRACE_WARNING3(m,p1,p2,p3)           {if (bip_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_BIP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define BIP_TRACE_WARNING4(m,p1,p2,p3,p4)        {if (bip_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_BIP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define BIP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)     {if (bip_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_BIP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define BIP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)  {if (bip_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_BIP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define BIP_TRACE_EVENT0(m)                      {if (bip_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_BIP, TRACE_TYPE_EVENT, m);}
#define BIP_TRACE_EVENT1(m,p1)                   {if (bip_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_BIP, TRACE_TYPE_EVENT, m, p1);}
#define BIP_TRACE_EVENT2(m,p1,p2)                {if (bip_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_BIP, TRACE_TYPE_EVENT, m,p1,p2);}
#define BIP_TRACE_EVENT3(m,p1,p2,p3)             {if (bip_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_BIP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define BIP_TRACE_EVENT4(m,p1,p2,p3,p4)          {if (bip_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_BIP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define BIP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)       {if (bip_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_BIP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define BIP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)    {if (bip_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_BIP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define BIP_TRACE_DEBUG0(m)                      {if (bip_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_BIP, TRACE_TYPE_DEBUG, m);}
#define BIP_TRACE_DEBUG1(m,p1)                   {if (bip_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_BIP, TRACE_TYPE_DEBUG, m,p1);}
#define BIP_TRACE_DEBUG2(m,p1,p2)                {if (bip_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_BIP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define BIP_TRACE_DEBUG3(m,p1,p2,p3)             {if (bip_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_BIP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define BIP_TRACE_DEBUG4(m,p1,p2,p3,p4)          {if (bip_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_BIP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define BIP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)       {if (bip_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_BIP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define BIP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)    {if (bip_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_BIP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

#define BIP_TRACE_API0(m)                        {if (bip_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_BIP, TRACE_TYPE_API, m);}
#define BIP_TRACE_API1(m,p1)                     {if (bip_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_BIP, TRACE_TYPE_API, m, p1);}
#define BIP_TRACE_API2(m,p1,p2)                  {if (bip_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_BIP, TRACE_TYPE_API, m,p1,p2);}
#define BIP_TRACE_API3(m,p1,p2,p3)               {if (bip_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_BIP, TRACE_TYPE_API, m,p1,p2,p3);}
#define BIP_TRACE_API4(m,p1,p2,p3,p4)            {if (bip_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_BIP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define BIP_TRACE_API5(m,p1,p2,p3,p4,p5)         {if (bip_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_BIP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define BIP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)      {if (bip_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_BIP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for TCS
*/
#define TCS_TRACE_ERROR0(m)                     {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_TCS, TRACE_TYPE_ERROR, m);}
#define TCS_TRACE_ERROR1(m,p1)                  {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_TCS, TRACE_TYPE_ERROR, m,p1);}
#define TCS_TRACE_ERROR2(m,p1,p2)               {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_TCS, TRACE_TYPE_ERROR, m,p1,p2);}
#define TCS_TRACE_ERROR3(m,p1,p2,p3)            {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_TCS, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define TCS_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_TCS, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define TCS_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_TCS, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define TCS_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_TCS, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define TCS_TRACE_WARNING0(m)                   {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_TCS, TRACE_TYPE_WARNING, m);}
#define TCS_TRACE_WARNING1(m,p1)                {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_TCS, TRACE_TYPE_WARNING, m,p1);}
#define TCS_TRACE_WARNING2(m,p1,p2)             {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_TCS, TRACE_TYPE_WARNING, m,p1,p2);}
#define TCS_TRACE_WARNING3(m,p1,p2,p3)          {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_TCS, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define TCS_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_TCS, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define TCS_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_TCS, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define TCS_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_TCS, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define TCS_TRACE_EVENT0(m)                     {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_TCS, TRACE_TYPE_EVENT, m);}
#define TCS_TRACE_EVENT1(m,p1)                  {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_TCS, TRACE_TYPE_EVENT, m, p1);}
#define TCS_TRACE_EVENT2(m,p1,p2)               {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_TCS, TRACE_TYPE_EVENT, m,p1,p2);}
#define TCS_TRACE_EVENT3(m,p1,p2,p3)            {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_TCS, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define TCS_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_TCS, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define TCS_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_TCS, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define TCS_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_TCS, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define TCS_TRACE_DEBUG0(m)                     {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_TCS, TRACE_TYPE_DEBUG, m);}
#define TCS_TRACE_DEBUG1(m,p1)                  {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_TCS, TRACE_TYPE_DEBUG, m,p1);}
#define TCS_TRACE_DEBUG2(m,p1,p2)               {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_TCS, TRACE_TYPE_DEBUG, m,p1,p2);}
#define TCS_TRACE_DEBUG3(m,p1,p2,p3)            {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_TCS, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define TCS_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_TCS, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define TCS_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_TCS, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define TCS_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_TCS, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

#define TCS_TRACE_API0(m)                       {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_TCS, TRACE_TYPE_API, m);}
#define TCS_TRACE_API1(m,p1)                    {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_TCS, TRACE_TYPE_API, m, p1);}
#define TCS_TRACE_API2(m,p1,p2)                 {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_TCS, TRACE_TYPE_API, m,p1,p2);}
#define TCS_TRACE_API3(m,p1,p2,p3)              {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_TCS, TRACE_TYPE_API, m,p1,p2,p3);}
#define TCS_TRACE_API4(m,p1,p2,p3,p4)           {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_TCS, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define TCS_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_TCS, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define TCS_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (tcs_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_TCS, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for ICP
*/
#define ICP_TRACE_ERROR0(m)                     {if (icp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_ICP, TRACE_TYPE_ERROR, m);}
#define ICP_TRACE_ERROR1(m,p1)                  {if (icp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_ICP, TRACE_TYPE_ERROR, m,p1);}
#define ICP_TRACE_ERROR2(m,p1,p2)               {if (icp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_ICP, TRACE_TYPE_ERROR, m,p1,p2);}
#define ICP_TRACE_ERROR3(m,p1,p2,p3)            {if (icp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_ICP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define ICP_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (icp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_ICP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define ICP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (icp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_ICP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define ICP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (icp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_ICP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define ICP_TRACE_WARNING0(m)                   {if (icp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_ICP, TRACE_TYPE_WARNING, m);}
#define ICP_TRACE_WARNING1(m,p1)                {if (icp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_ICP, TRACE_TYPE_WARNING, m,p1);}
#define ICP_TRACE_WARNING2(m,p1,p2)             {if (icp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_ICP, TRACE_TYPE_WARNING, m,p1,p2);}
#define ICP_TRACE_WARNING3(m,p1,p2,p3)          {if (icp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_ICP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define ICP_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (icp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_ICP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define ICP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (icp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_ICP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define ICP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (icp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_ICP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define ICP_TRACE_EVENT0(m)                     {if (icp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_ICP, TRACE_TYPE_EVENT, m);}
#define ICP_TRACE_EVENT1(m,p1)                  {if (icp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_ICP, TRACE_TYPE_EVENT, m, p1);}
#define ICP_TRACE_EVENT2(m,p1,p2)               {if (icp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_ICP, TRACE_TYPE_EVENT, m,p1,p2);}
#define ICP_TRACE_EVENT3(m,p1,p2,p3)            {if (icp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_ICP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define ICP_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (icp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_ICP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define ICP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (icp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_ICP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define ICP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (icp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_ICP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define ICP_TRACE_DEBUG0(m)                     {if (icp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_ICP, TRACE_TYPE_DEBUG, m);}
#define ICP_TRACE_DEBUG1(m,p1)                  {if (icp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_ICP, TRACE_TYPE_DEBUG, m,p1);}
#define ICP_TRACE_DEBUG2(m,p1,p2)               {if (icp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_ICP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define ICP_TRACE_DEBUG3(m,p1,p2,p3)            {if (icp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_ICP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define ICP_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (icp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_ICP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define ICP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (icp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_ICP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define ICP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (icp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_ICP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

#define ICP_TRACE_API0(m)                       {if (icp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_ICP, TRACE_TYPE_API, m);}
#define ICP_TRACE_API1(m,p1)                    {if (icp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_ICP, TRACE_TYPE_API, m, p1);}
#define ICP_TRACE_API2(m,p1,p2)                 {if (icp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_ICP, TRACE_TYPE_API, m,p1,p2);}
#define ICP_TRACE_API3(m,p1,p2,p3)              {if (icp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_ICP, TRACE_TYPE_API, m,p1,p2,p3);}
#define ICP_TRACE_API4(m,p1,p2,p3,p4)           {if (icp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_ICP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define ICP_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (icp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_ICP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define ICP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (icp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_ICP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

/* CTP */
#define CTP_TRACE_ERROR0(m)                     {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_CTP, TRACE_TYPE_ERROR, m);}
#define CTP_TRACE_ERROR1(m,p1)                  {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_CTP, TRACE_TYPE_ERROR, m,p1);}
#define CTP_TRACE_ERROR2(m,p1,p2)               {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_CTP, TRACE_TYPE_ERROR, m,p1,p2);}
#define CTP_TRACE_ERROR3(m,p1,p2,p3)            {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_CTP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define CTP_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_CTP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define CTP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_CTP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define CTP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_CTP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define CTP_TRACE_WARNING0(m)                   {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_CTP, TRACE_TYPE_WARNING, m);}
#define CTP_TRACE_WARNING1(m,p1)                {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_CTP, TRACE_TYPE_WARNING, m,p1);}
#define CTP_TRACE_WARNING2(m,p1,p2)             {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_CTP, TRACE_TYPE_WARNING, m,p1,p2);}
#define CTP_TRACE_WARNING3(m,p1,p2,p3)          {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_CTP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define CTP_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_CTP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define CTP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_CTP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define CTP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_CTP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define CTP_TRACE_EVENT0(m)                     {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_CTP, TRACE_TYPE_EVENT, m);}
#define CTP_TRACE_EVENT1(m,p1)                  {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_CTP, TRACE_TYPE_EVENT, m, p1);}
#define CTP_TRACE_EVENT2(m,p1,p2)               {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_CTP, TRACE_TYPE_EVENT, m,p1,p2);}
#define CTP_TRACE_EVENT3(m,p1,p2,p3)            {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_CTP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define CTP_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_CTP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define CTP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_CTP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define CTP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_CTP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define CTP_TRACE_DEBUG0(m)                     {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_CTP, TRACE_TYPE_DEBUG, m);}
#define CTP_TRACE_DEBUG1(m,p1)                  {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_CTP, TRACE_TYPE_DEBUG, m,p1);}
#define CTP_TRACE_DEBUG2(m,p1,p2)               {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_CTP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define CTP_TRACE_DEBUG3(m,p1,p2,p3)            {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_CTP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define CTP_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_CTP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define CTP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_CTP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define CTP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (ctp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_CTP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}


/* define traces for HID Host */
#define HIDH_TRACE_ERROR0(m)                     {if (hh_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m);}
#define HIDH_TRACE_ERROR1(m,p1)                  {if (hh_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m, p1);}
#define HIDH_TRACE_ERROR2(m,p1,p2)               {if (hh_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2);}
#define HIDH_TRACE_ERROR3(m,p1,p2,p3)            {if (hh_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define HIDH_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (hh_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define HIDH_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (hh_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define HIDH_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (hh_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define HIDH_TRACE_WARNING0(m)                   {if (hh_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m);}
#define HIDH_TRACE_WARNING1(m,p1)                {if (hh_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1);}
#define HIDH_TRACE_WARNING2(m,p1,p2)             {if (hh_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2);}
#define HIDH_TRACE_WARNING3(m,p1,p2,p3)          {if (hh_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define HIDH_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (hh_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define HIDH_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (hh_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define HIDH_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (hh_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define HIDH_TRACE_API0(m)                       {if (hh_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_HID, TRACE_TYPE_API, m);}
#define HIDH_TRACE_API1(m,p1)                    {if (hh_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_HID, TRACE_TYPE_API, m, p1);}
#define HIDH_TRACE_API2(m,p1,p2)                 {if (hh_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_HID, TRACE_TYPE_API, m,p1,p2);}
#define HIDH_TRACE_API3(m,p1,p2,p3)              {if (hh_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_HID, TRACE_TYPE_API, m,p1,p2,p3);}
#define HIDH_TRACE_API4(m,p1,p2,p3,p4)           {if (hh_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_HID, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define HIDH_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (hh_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_HID, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define HIDH_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (hh_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_HID, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define HIDH_TRACE_EVENT0(m)                     {if (hh_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_HID, TRACE_TYPE_EVENT, m);}
#define HIDH_TRACE_EVENT1(m,p1)                  {if (hh_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_HID, TRACE_TYPE_EVENT, m, p1);}
#define HIDH_TRACE_EVENT2(m,p1,p2)               {if (hh_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_HID, TRACE_TYPE_EVENT, m,p1,p2);}
#define HIDH_TRACE_EVENT3(m,p1,p2,p3)            {if (hh_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_HID, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define HIDH_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (hh_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_HID, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define HIDH_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (hh_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_HID, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define HIDH_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (hh_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_HID, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define HIDH_TRACE_DEBUG0(m)                     {if (hh_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m);}
#define HIDH_TRACE_DEBUG1(m,p1)                  {if (hh_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1);}
#define HIDH_TRACE_DEBUG2(m,p1,p2)               {if (hh_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2);}
#define HIDH_TRACE_DEBUG3(m,p1,p2,p3)            {if (hh_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define HIDH_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (hh_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define HIDH_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (hh_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define HIDH_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (hh_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* define traces for HID Device */
#define HIDD_TRACE_ERROR0(m)                     {if (hd_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m);}
#define HIDD_TRACE_ERROR1(m,p1)                  {if (hd_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m, p1);}
#define HIDD_TRACE_ERROR2(m,p1,p2)               {if (hd_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2);}
#define HIDD_TRACE_ERROR3(m,p1,p2,p3)            {if (hd_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define HIDD_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (hd_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define HIDD_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (hd_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define HIDD_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (hd_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define HIDD_TRACE_WARNING0(m)                   {if (hd_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m);}
#define HIDD_TRACE_WARNING1(m,p1)                {if (hd_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1);}
#define HIDD_TRACE_WARNING2(m,p1,p2)             {if (hd_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2);}
#define HIDD_TRACE_WARNING3(m,p1,p2,p3)          {if (hd_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define HIDD_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (hd_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define HIDD_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (hd_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define HIDD_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (hd_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define HIDD_TRACE_API0(m)                       {if (hd_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_HID, TRACE_TYPE_API, m);}
#define HIDD_TRACE_API1(m,p1)                    {if (hd_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_HID, TRACE_TYPE_API, m, p1);}
#define HIDD_TRACE_API2(m,p1,p2)                 {if (hd_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_HID, TRACE_TYPE_API, m,p1,p2);}
#define HIDD_TRACE_API3(m,p1,p2,p3)              {if (hd_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_HID, TRACE_TYPE_API, m,p1,p2,p3);}
#define HIDD_TRACE_API4(m,p1,p2,p3,p4)           {if (hd_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_HID, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define HIDD_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (hd_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_HID, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define HIDD_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (hd_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_HID, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define HIDD_TRACE_EVENT0(m)                     {if (hd_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_HID, TRACE_TYPE_EVENT, m);}
#define HIDD_TRACE_EVENT1(m,p1)                  {if (hd_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_HID, TRACE_TYPE_EVENT, m, p1);}
#define HIDD_TRACE_EVENT2(m,p1,p2)               {if (hd_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_HID, TRACE_TYPE_EVENT, m,p1,p2);}
#define HIDD_TRACE_EVENT3(m,p1,p2,p3)            {if (hd_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_HID, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define HIDD_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (hd_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_HID, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define HIDD_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (hd_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_HID, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define HIDD_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (hd_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_HID, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define HIDD_TRACE_DEBUG0(m)                     {if (hd_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m);}
#define HIDD_TRACE_DEBUG1(m,p1)                  {if (hd_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1);}
#define HIDD_TRACE_DEBUG2(m,p1,p2)               {if (hd_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2);}
#define HIDD_TRACE_DEBUG3(m,p1,p2,p3)            {if (hd_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define HIDD_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (hd_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define HIDD_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (hd_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define HIDD_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (hd_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* define traces for headset profile */
#define HSP2_TRACE_ERROR0(pcb,m)                     {if (pcb->trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_HSP2, TRACE_TYPE_ERROR, m);}
#define HSP2_TRACE_ERROR1(pcb,m,p1)                  {if (pcb->trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_HSP2, TRACE_TYPE_ERROR, m, p1);}
#define HSP2_TRACE_ERROR2(pcb,m,p1,p2)               {if (pcb->trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_HSP2, TRACE_TYPE_ERROR, m,p1,p2);}
#define HSP2_TRACE_ERROR3(pcb,m,p1,p2,p3)            {if (pcb->trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_HSP2, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define HSP2_TRACE_ERROR4(pcb,m,p1,p2,p3,p4)         {if (pcb->trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_HSP2, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define HSP2_TRACE_ERROR5(pcb,m,p1,p2,p3,p4,p5)      {if (pcb->trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_HSP2, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define HSP2_TRACE_ERROR6(pcb,m,p1,p2,p3,p4,p5,p6)   {if (pcb->trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_HSP2, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define HSP2_TRACE_WARNING0(pcb,m)                   {if (pcb->trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_HSP2, TRACE_TYPE_WARNING, m);}
#define HSP2_TRACE_WARNING1(pcb,m,p1)                {if (pcb->trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_HSP2, TRACE_TYPE_WARNING, m,p1);}
#define HSP2_TRACE_WARNING2(pcb,m,p1,p2)             {if (pcb->trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_HSP2, TRACE_TYPE_WARNING, m,p1,p2);}
#define HSP2_TRACE_WARNING3(pcb,m,p1,p2,p3)          {if (pcb->trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_HSP2, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define HSP2_TRACE_WARNING4(pcb,m,p1,p2,p3,p4)       {if (pcb->trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_HSP2, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define HSP2_TRACE_WARNING5(pcb,m,p1,p2,p3,p4,p5)    {if (pcb->trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_HSP2, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define HSP2_TRACE_WARNING6(pcb,m,p1,p2,p3,p4,p5,p6) {if (pcb->trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_HSP2, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define HSP2_TRACE_API0(pcb,m)                       {if (pcb->trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_HSP2, TRACE_TYPE_API, m);}
#define HSP2_TRACE_API1(pcb,m,p1)                    {if (pcb->trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_HSP2, TRACE_TYPE_API, m, p1);}
#define HSP2_TRACE_API2(pcb,m,p1,p2)                 {if (pcb->trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_HSP2, TRACE_TYPE_API, m,p1,p2);}
#define HSP2_TRACE_API3(pcb,m,p1,p2,p3)              {if (pcb->trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_HSP2, TRACE_TYPE_API, m,p1,p2,p3);}
#define HSP2_TRACE_API4(pcb,m,p1,p2,p3,p4)           {if (pcb->trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_HSP2, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define HSP2_TRACE_API5(pcb,m,p1,p2,p3,p4,p5)        {if (pcb->trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_HSP2, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define HSP2_TRACE_API6(pcb,m,p1,p2,p3,p4,p5,p6)     {if (pcb->trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_HSP2, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define HSP2_TRACE_EVENT0(pcb,m)                     {if (pcb->trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_HSP2, TRACE_TYPE_EVENT, m);}
#define HSP2_TRACE_EVENT1(pcb,m,p1)                  {if (pcb->trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_HSP2, TRACE_TYPE_EVENT, m, p1);}
#define HSP2_TRACE_EVENT2(pcb,m,p1,p2)               {if (pcb->trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_HSP2, TRACE_TYPE_EVENT, m,p1,p2);}
#define HSP2_TRACE_EVENT3(pcb,m,p1,p2,p3)            {if (pcb->trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_HSP2, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define HSP2_TRACE_EVENT4(pcb,m,p1,p2,p3,p4)         {if (pcb->trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_HSP2, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define HSP2_TRACE_EVENT5(pcb,m,p1,p2,p3,p4,p5)      {if (pcb->trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_HSP2, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define HSP2_TRACE_EVENT6(pcb,m,p1,p2,p3,p4,p5,p6)   {if (pcb->trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_HSP2, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define HSP2_TRACE_DEBUG0(pcb,m)                     {if (pcb->trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_HSP2, TRACE_TYPE_DEBUG, m);}
#define HSP2_TRACE_DEBUG1(pcb,m,p1)                  {if (pcb->trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_HSP2, TRACE_TYPE_DEBUG, m,p1);}
#define HSP2_TRACE_DEBUG2(pcb,m,p1,p2)               {if (pcb->trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_HSP2, TRACE_TYPE_DEBUG, m,p1,p2);}
#define HSP2_TRACE_DEBUG3(pcb,m,p1,p2,p3)            {if (pcb->trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_HSP2, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define HSP2_TRACE_DEBUG4(pcb,m,p1,p2,p3,p4)         {if (pcb->trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_HSP2, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define HSP2_TRACE_DEBUG5(pcb,m,p1,p2,p3,p4,p5)      {if (pcb->trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_HSP2, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define HSP2_TRACE_DEBUG6(pcb,m,p1,p2,p3,p4,p5,p6)   {if (pcb->trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_HSP2, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the NFC unit
*/
#define NFC_TRACE_ERROR0(m)                     {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_NFC, TRACE_TYPE_ERROR, m);}
#define NFC_TRACE_ERROR1(m,p1)                  {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_NFC, TRACE_TYPE_ERROR, m,p1);}
#define NFC_TRACE_ERROR2(m,p1,p2)               {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_NFC, TRACE_TYPE_ERROR, m,p1,p2);}
#define NFC_TRACE_ERROR3(m,p1,p2,p3)            {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_NFC, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define NFC_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_NFC, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define NFC_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_NFC, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define NFC_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_NFC, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define NFC_TRACE_WARNING0(m)                   {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_NFC, TRACE_TYPE_WARNING, m);}
#define NFC_TRACE_WARNING1(m,p1)                {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_NFC, TRACE_TYPE_WARNING, m,p1);}
#define NFC_TRACE_WARNING2(m,p1,p2)             {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_NFC, TRACE_TYPE_WARNING, m,p1,p2);}
#define NFC_TRACE_WARNING3(m,p1,p2,p3)          {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_NFC, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define NFC_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_NFC, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define NFC_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_NFC, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define NFC_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_NFC, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define NFC_TRACE_API0(m)                       {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_NFC, TRACE_TYPE_API, m);}
#define NFC_TRACE_API1(m,p1)                    {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_NFC, TRACE_TYPE_API, m,p1);}
#define NFC_TRACE_API2(m,p1,p2)                 {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_NFC, TRACE_TYPE_API, m,p1,p2);}
#define NFC_TRACE_API3(m,p1,p2,p3)              {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_NFC, TRACE_TYPE_API, m,p1,p2,p3);}
#define NFC_TRACE_API4(m,p1,p2,p3,p4)           {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_NFC, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define NFC_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_NFC, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define NFC_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_NFC, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define NFC_TRACE_EVENT0(m)                     {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_NFC, TRACE_TYPE_EVENT, m);}
#define NFC_TRACE_EVENT1(m,p1)                  {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_NFC, TRACE_TYPE_EVENT, m, p1);}
#define NFC_TRACE_EVENT2(m,p1,p2)               {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_NFC, TRACE_TYPE_EVENT, m,p1,p2);}
#define NFC_TRACE_EVENT3(m,p1,p2,p3)            {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_NFC, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define NFC_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_NFC, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define NFC_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_NFC, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define NFC_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_NFC, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define NFC_TRACE_DEBUG0(m)                     {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_NFC, TRACE_TYPE_DEBUG, m);}
#define NFC_TRACE_DEBUG1(m,p1)                  {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_NFC, TRACE_TYPE_DEBUG, m,p1);}
#define NFC_TRACE_DEBUG2(m,p1,p2)               {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_NFC, TRACE_TYPE_DEBUG, m,p1,p2);}
#define NFC_TRACE_DEBUG3(m,p1,p2,p3)            {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_NFC, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define NFC_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_NFC, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define NFC_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_NFC, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define NFC_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_NFC, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

#define NCI_TRACE_ERROR0(m)                     {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_NCI, TRACE_TYPE_ERROR, m);}
#define NCI_TRACE_ERROR1(m,p1)                  {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_NCI, TRACE_TYPE_ERROR, m,p1);}
#define NCI_TRACE_ERROR2(m,p1,p2)               {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_NCI, TRACE_TYPE_ERROR, m,p1,p2);}
#define NCI_TRACE_ERROR3(m,p1,p2,p3)            {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_NCI, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define NCI_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_NCI, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define NCI_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_NCI, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define NCI_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_NCI, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define NCI_TRACE_WARNING0(m)                   {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_NCI, TRACE_TYPE_WARNING, m);}
#define NCI_TRACE_WARNING1(m,p1)                {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_NCI, TRACE_TYPE_WARNING, m,p1);}
#define NCI_TRACE_WARNING2(m,p1,p2)             {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_NCI, TRACE_TYPE_WARNING, m,p1,p2);}
#define NCI_TRACE_WARNING3(m,p1,p2,p3)          {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_NCI, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define NCI_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_NCI, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define NCI_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_NCI, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define NCI_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_NCI, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define NCI_TRACE_API0(m)                       {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_NCI, TRACE_TYPE_API, m);}
#define NCI_TRACE_API1(m,p1)                    {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_NCI, TRACE_TYPE_API, m,p1);}
#define NCI_TRACE_API2(m,p1,p2)                 {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_NCI, TRACE_TYPE_API, m,p1,p2);}
#define NCI_TRACE_API3(m,p1,p2,p3)              {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_NCI, TRACE_TYPE_API, m,p1,p2,p3);}
#define NCI_TRACE_API4(m,p1,p2,p3,p4)           {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_NCI, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define NCI_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_NCI, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define NCI_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_NCI, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define NCI_TRACE_EVENT0(m)                     {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_NCI, TRACE_TYPE_EVENT, m);}
#define NCI_TRACE_EVENT1(m,p1)                  {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_NCI, TRACE_TYPE_EVENT, m, p1);}
#define NCI_TRACE_EVENT2(m,p1,p2)               {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_NCI, TRACE_TYPE_EVENT, m,p1,p2);}
#define NCI_TRACE_EVENT3(m,p1,p2,p3)            {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_NCI, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define NCI_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_NCI, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define NCI_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_NCI, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define NCI_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_NCI, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define NCI_TRACE_DEBUG0(m)                     {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_NCI, TRACE_TYPE_DEBUG, m);}
#define NCI_TRACE_DEBUG1(m,p1)                  {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_NCI, TRACE_TYPE_DEBUG, m,p1);}
#define NCI_TRACE_DEBUG2(m,p1,p2)               {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_NCI, TRACE_TYPE_DEBUG, m,p1,p2);}
#define NCI_TRACE_DEBUG3(m,p1,p2,p3)            {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_NCI, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define NCI_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_NCI, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define NCI_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_NCI, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define NCI_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (nfc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_NCI, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

#define RW_TRACE_ERROR0(m)                     {if (rw_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_RW, TRACE_TYPE_ERROR, m);}
#define RW_TRACE_ERROR1(m,p1)                  {if (rw_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_RW, TRACE_TYPE_ERROR, m,p1);}
#define RW_TRACE_ERROR2(m,p1,p2)               {if (rw_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_RW, TRACE_TYPE_ERROR, m,p1,p2);}
#define RW_TRACE_ERROR3(m,p1,p2,p3)            {if (rw_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_RW, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define RW_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (rw_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_RW, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define RW_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (rw_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_RW, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define RW_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (rw_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_RW, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define RW_TRACE_WARNING0(m)                   {if (rw_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_RW, TRACE_TYPE_WARNING, m);}
#define RW_TRACE_WARNING1(m,p1)                {if (rw_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_RW, TRACE_TYPE_WARNING, m,p1);}
#define RW_TRACE_WARNING2(m,p1,p2)             {if (rw_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_RW, TRACE_TYPE_WARNING, m,p1,p2);}
#define RW_TRACE_WARNING3(m,p1,p2,p3)          {if (rw_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_RW, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define RW_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (rw_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_RW, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define RW_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (rw_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_RW, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define RW_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (rw_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_RW, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define RW_TRACE_API0(m)                       {if (rw_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_RW, TRACE_TYPE_API, m);}
#define RW_TRACE_API1(m,p1)                    {if (rw_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_RW, TRACE_TYPE_API, m,p1);}
#define RW_TRACE_API2(m,p1,p2)                 {if (rw_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_RW, TRACE_TYPE_API, m,p1,p2);}
#define RW_TRACE_API3(m,p1,p2,p3)              {if (rw_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_RW, TRACE_TYPE_API, m,p1,p2,p3);}
#define RW_TRACE_API4(m,p1,p2,p3,p4)           {if (rw_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_RW, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define RW_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (rw_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_RW, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define RW_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (rw_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_RW, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define RW_TRACE_EVENT0(m)                     {if (rw_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_RW, TRACE_TYPE_EVENT, m);}
#define RW_TRACE_EVENT1(m,p1)                  {if (rw_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_RW, TRACE_TYPE_EVENT, m, p1);}
#define RW_TRACE_EVENT2(m,p1,p2)               {if (rw_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_RW, TRACE_TYPE_EVENT, m,p1,p2);}
#define RW_TRACE_EVENT3(m,p1,p2,p3)            {if (rw_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_RW, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define RW_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (rw_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_RW, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define RW_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (rw_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_RW, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define RW_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (rw_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_RW, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define RW_TRACE_DEBUG0(m)                     {if (rw_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_RW, TRACE_TYPE_DEBUG, m);}
#define RW_TRACE_DEBUG1(m,p1)                  {if (rw_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_RW, TRACE_TYPE_DEBUG, m,p1);}
#define RW_TRACE_DEBUG2(m,p1,p2)               {if (rw_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_RW, TRACE_TYPE_DEBUG, m,p1,p2);}
#define RW_TRACE_DEBUG3(m,p1,p2,p3)            {if (rw_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_RW, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define RW_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (rw_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_RW, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define RW_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (rw_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_RW, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define RW_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (rw_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_RW, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

#define CE_TRACE_ERROR0(m)                     {if (ce_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_CE, TRACE_TYPE_ERROR, m);}
#define CE_TRACE_ERROR1(m,p1)                  {if (ce_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_CE, TRACE_TYPE_ERROR, m,p1);}
#define CE_TRACE_ERROR2(m,p1,p2)               {if (ce_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_CE, TRACE_TYPE_ERROR, m,p1,p2);}
#define CE_TRACE_ERROR3(m,p1,p2,p3)            {if (ce_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_CE, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define CE_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (ce_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_CE, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define CE_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (ce_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_CE, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define CE_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (ce_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_CE, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define CE_TRACE_WARNING0(m)                   {if (ce_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_CE, TRACE_TYPE_WARNING, m);}
#define CE_TRACE_WARNING1(m,p1)                {if (ce_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_CE, TRACE_TYPE_WARNING, m,p1);}
#define CE_TRACE_WARNING2(m,p1,p2)             {if (ce_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_CE, TRACE_TYPE_WARNING, m,p1,p2);}
#define CE_TRACE_WARNING3(m,p1,p2,p3)          {if (ce_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_CE, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define CE_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (ce_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_CE, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define CE_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (ce_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_CE, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define CE_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (ce_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_CE, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define CE_TRACE_API0(m)                       {if (ce_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_CE, TRACE_TYPE_API, m);}
#define CE_TRACE_API1(m,p1)                    {if (ce_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_CE, TRACE_TYPE_API, m,p1);}
#define CE_TRACE_API2(m,p1,p2)                 {if (ce_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_CE, TRACE_TYPE_API, m,p1,p2);}
#define CE_TRACE_API3(m,p1,p2,p3)              {if (ce_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_CE, TRACE_TYPE_API, m,p1,p2,p3);}
#define CE_TRACE_API4(m,p1,p2,p3,p4)           {if (ce_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_CE, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define CE_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (ce_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_CE, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define CE_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (ce_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_CE, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define CE_TRACE_EVENT0(m)                     {if (ce_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_CE, TRACE_TYPE_EVENT, m);}
#define CE_TRACE_EVENT1(m,p1)                  {if (ce_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_CE, TRACE_TYPE_EVENT, m, p1);}
#define CE_TRACE_EVENT2(m,p1,p2)               {if (ce_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_CE, TRACE_TYPE_EVENT, m,p1,p2);}
#define CE_TRACE_EVENT3(m,p1,p2,p3)            {if (ce_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_CE, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define CE_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (ce_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_CE, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define CE_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (ce_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_CE, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define CE_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (ce_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_CE, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define CE_TRACE_DEBUG0(m)                     {if (ce_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_CE, TRACE_TYPE_DEBUG, m);}
#define CE_TRACE_DEBUG1(m,p1)                  {if (ce_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_CE, TRACE_TYPE_DEBUG, m,p1);}
#define CE_TRACE_DEBUG2(m,p1,p2)               {if (ce_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_CE, TRACE_TYPE_DEBUG, m,p1,p2);}
#define CE_TRACE_DEBUG3(m,p1,p2,p3)            {if (ce_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_CE, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define CE_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (ce_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_CE, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define CE_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (ce_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_CE, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define CE_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (ce_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_CE, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

#define NDEF_TRACE_ERROR0(m)                     {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_NDEF, TRACE_TYPE_ERROR, m);}
#define NDEF_TRACE_ERROR1(m,p1)                  {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_NDEF, TRACE_TYPE_ERROR, m,p1);}
#define NDEF_TRACE_ERROR2(m,p1,p2)               {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_NDEF, TRACE_TYPE_ERROR, m,p1,p2);}
#define NDEF_TRACE_ERROR3(m,p1,p2,p3)            {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_NDEF, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define NDEF_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_NDEF, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define NDEF_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_NDEF, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define NDEF_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_NDEF, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define NDEF_TRACE_WARNING0(m)                   {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_NDEF, TRACE_TYPE_WARNING, m);}
#define NDEF_TRACE_WARNING1(m,p1)                {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_NDEF, TRACE_TYPE_WARNING, m,p1);}
#define NDEF_TRACE_WARNING2(m,p1,p2)             {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_NDEF, TRACE_TYPE_WARNING, m,p1,p2);}
#define NDEF_TRACE_WARNING3(m,p1,p2,p3)          {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_NDEF, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define NDEF_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_NDEF, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define NDEF_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_NDEF, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define NDEF_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_NDEF, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define NDEF_TRACE_API0(m)                       {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_NDEF, TRACE_TYPE_API, m);}
#define NDEF_TRACE_API1(m,p1)                    {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_NDEF, TRACE_TYPE_API, m,p1);}
#define NDEF_TRACE_API2(m,p1,p2)                 {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_NDEF, TRACE_TYPE_API, m,p1,p2);}
#define NDEF_TRACE_API3(m,p1,p2,p3)              {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_NDEF, TRACE_TYPE_API, m,p1,p2,p3);}
#define NDEF_TRACE_API4(m,p1,p2,p3,p4)           {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_NDEF, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define NDEF_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_NDEF, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define NDEF_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_NDEF, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define NDEF_TRACE_EVENT0(m)                     {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_NDEF, TRACE_TYPE_EVENT, m);}
#define NDEF_TRACE_EVENT1(m,p1)                  {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_NDEF, TRACE_TYPE_EVENT, m, p1);}
#define NDEF_TRACE_EVENT2(m,p1,p2)               {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_NDEF, TRACE_TYPE_EVENT, m,p1,p2);}
#define NDEF_TRACE_EVENT3(m,p1,p2,p3)            {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_NDEF, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define NDEF_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_NDEF, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define NDEF_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_NDEF, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define NDEF_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_NDEF, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define NDEF_TRACE_DEBUG0(m)                     {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_NDEF, TRACE_TYPE_DEBUG, m);}
#define NDEF_TRACE_DEBUG1(m,p1)                  {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_NDEF, TRACE_TYPE_DEBUG, m,p1);}
#define NDEF_TRACE_DEBUG2(m,p1,p2)               {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_NDEF, TRACE_TYPE_DEBUG, m,p1,p2);}
#define NDEF_TRACE_DEBUG3(m,p1,p2,p3)            {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_NDEF, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define NDEF_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_NDEF, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define NDEF_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_NDEF, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define NDEF_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (ndef_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_NDEF, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the NFA unit
*/
#define NFA_TRACE_ERROR0(m)                     {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_NFA, TRACE_TYPE_ERROR, m);}
#define NFA_TRACE_ERROR1(m,p1)                  {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_NFA, TRACE_TYPE_ERROR, m,p1);}
#define NFA_TRACE_ERROR2(m,p1,p2)               {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_NFA, TRACE_TYPE_ERROR, m,p1,p2);}
#define NFA_TRACE_ERROR3(m,p1,p2,p3)            {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_NFA, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define NFA_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_NFA, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define NFA_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_NFA, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define NFA_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_NFA, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define NFA_TRACE_WARNING0(m)                   {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_NFA, TRACE_TYPE_WARNING, m);}
#define NFA_TRACE_WARNING1(m,p1)                {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_NFA, TRACE_TYPE_WARNING, m,p1);}
#define NFA_TRACE_WARNING2(m,p1,p2)             {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_NFA, TRACE_TYPE_WARNING, m,p1,p2);}
#define NFA_TRACE_WARNING3(m,p1,p2,p3)          {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_NFA, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define NFA_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_NFA, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define NFA_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_NFA, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define NFA_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_NFA, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define NFA_TRACE_API0(m)                       {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_NFA, TRACE_TYPE_API, m);}
#define NFA_TRACE_API1(m,p1)                    {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_NFA, TRACE_TYPE_API, m,p1);}
#define NFA_TRACE_API2(m,p1,p2)                 {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_NFA, TRACE_TYPE_API, m,p1,p2);}
#define NFA_TRACE_API3(m,p1,p2,p3)              {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_NFA, TRACE_TYPE_API, m,p1,p2,p3);}
#define NFA_TRACE_API4(m,p1,p2,p3,p4)           {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_NFA, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define NFA_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_NFA, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define NFA_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_NFA, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define NFA_TRACE_EVENT0(m)                     {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_NFA, TRACE_TYPE_EVENT, m);}
#define NFA_TRACE_EVENT1(m,p1)                  {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_NFA, TRACE_TYPE_EVENT, m, p1);}
#define NFA_TRACE_EVENT2(m,p1,p2)               {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_NFA, TRACE_TYPE_EVENT, m,p1,p2);}
#define NFA_TRACE_EVENT3(m,p1,p2,p3)            {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_NFA, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define NFA_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_NFA, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define NFA_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_NFA, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define NFA_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_NFA, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define NFA_TRACE_DEBUG0(m)                     {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_NFA, TRACE_TYPE_DEBUG, m);}
#define NFA_TRACE_DEBUG1(m,p1)                  {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_NFA, TRACE_TYPE_DEBUG, m,p1);}
#define NFA_TRACE_DEBUG2(m,p1,p2)               {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_NFA, TRACE_TYPE_DEBUG, m,p1,p2);}
#define NFA_TRACE_DEBUG3(m,p1,p2,p3)            {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_NFA, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define NFA_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_NFA, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define NFA_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_NFA, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define NFA_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (nfa_sys_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_NFA, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

#define MMI_TRACE_0(m)
#define MMI_TRACE_1(m,p1)
#define MMI_TRACE_2(m,p1,p2)
#define MMI_TRACE_3(m,p1,p2,p3)
#define MMI_TRACE_4(m,p1,p2,p3,p4)
#define MMI_TRACE_5(m,p1,p2,p3,p4,p5)
#define MMI_TRACE_6(m,p1,p2,p3,p4,p5,p6)

#define MMI_DEBUG_0(m)                           BT_TRACE_0(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m)
#define MMI_DEBUG_1(m,p1)                        BT_TRACE_1(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1)
#define MMI_DEBUG_2(m,p1,p2)                     BT_TRACE_2(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2)
#define MMI_DEBUG_3(m,p1,p2,p3)                  BT_TRACE_3(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2,p3)
#define MMI_DEBUG_4(m,p1,p2,p3,p4)               BT_TRACE_4(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4)
#define MMI_DEBUG_5(m,p1,p2,p3,p4,p5)            BT_TRACE_5(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5)
#define MMI_DEBUG_6(m,p1,p2,p3,p4,p5,p6)         BT_TRACE_6(TRACE_LAYER_HID, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6)

#define MMI_WARNING_0(m)                         BT_TRACE_0(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m)
#define MMI_WARNING_1(m,p1)                      BT_TRACE_1(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1)
#define MMI_WARNING_2(m,p1,p2)                   BT_TRACE_2(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2)
#define MMI_WARNING_3(m,p1,p2,p3)                BT_TRACE_3(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2,p3)
#define MMI_WARNING_4(m,p1,p2,p3,p4)             BT_TRACE_4(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2,p3,p4)
#define MMI_WARNING_5(m,p1,p2,p3,p4,p5)          BT_TRACE_5(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5)
#define MMI_WARNING_6(m,p1,p2,p3,p4,p5,p6)       BT_TRACE_6(TRACE_LAYER_HID, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6)

#define MMI_ERROR_0(m)                           BT_TRACE_0(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m)
#define MMI_ERROR_1(m,p1)                        BT_TRACE_1(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1)
#define MMI_ERROR_2(m,p1,p2)                     BT_TRACE_2(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2)
#define MMI_ERROR_3(m,p1,p2,p3)                  BT_TRACE_3(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2,p3)
#define MMI_ERROR_4(m,p1,p2,p3,p4)               BT_TRACE_4(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2,p3,p4)
#define MMI_ERROR_5(m,p1,p2,p3,p4,p5)            BT_TRACE_5(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5)
#define MMI_ERROR_6(m,p1,p2,p3,p4,p5,p6)         BT_TRACE_6(TRACE_LAYER_HID, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6)

#define TAK_TRACE_0(m)                            MMI_Echo(m)

/* hid mouse module traces */

#define MSKB_TRACE_0(m)                         MMI_Echo(m)
#define MSKB_TRACE_1(m,p1)                      MMI_Echo(m,p1)
#define MSKB_TRACE_2(m,p1,p2)                   MMI_Echo(m,p1,p2)
#define MSKB_TRACE_3(m,p1,p2,p3)                MMI_Echo(m,p1,p2,p3)
#define MSKB_TRACE_4(m,p1,p2,p3,p4)             MMI_Echo(m,p1,p2,p3,p4)
#define MSKB_TRACE_5(m,p1,p2,p3,p4,p5)          MMI_Echo(m,p1,p2,p3,p4,p5)
#define MSKB_TRACE_6(m,p1,p2,p3,p4,p5,p6)       MMI_Echo(m,p1,p2,p3,p4,p5,p6)

#define MSKB_DEBUG_0(m)                         MMI_Echo(m)
#define MSKB_DEBUG_1(m,p1)                      MMI_Echo(m,p1)
#define MSKB_DEBUG_2(m,p1,p2)                   MMI_Echo(m,p1,p2)
#define MSKB_DEBUG_3(m,p1,p2,p3)                MMI_Echo(m,p1,p2,p3)
#define MSKB_DEBUG_4(m,p1,p2,p3,p4)             MMI_Echo(m,p1,p2,p3,p4)
#define MSKB_DEBUG_5(m,p1,p2,p3,p4,p5)          MMI_Echo(m,p1,p2,p3,p4,p5)
#define MSKB_DEBUG_6(m,p1,p2,p3,p4,p5,p6)       MMI_Echo(m,p1,p2,p3,p4,p5,p6)

#define MSKB_ERROR_0(m)                         MMI_Echo(m)
#define MSKB_ERROR_1(m,p1)                      MMI_Echo(m,p1)
#define MSKB_ERROR_2(m,p1,p2)                   MMI_Echo(m,p1,p2)
#define MSKB_ERROR_3(m,p1,p2,p3)                MMI_Echo(m,p1,p2,p3)
#define MSKB_ERROR_4(m,p1,p2,p3,p4)             MMI_Echo(m,p1,p2,p3,p4)
#define MSKB_ERROR_5(m,p1,p2,p3,p4,p5)          MMI_Echo(m,p1,p2,p3,p4,p5)
#define MSKB_ERROR_6(m,p1,p2,p3,p4,p5,p6)       MMI_Echo(m,p1,p2,p3,p4,p5,p6)

/* define traces for DUN */

#define DUN_TRACE_ERROR0(m)                     {if (dun_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_DUN, TRACE_TYPE_ERROR, m);}
#define DUN_TRACE_ERROR1(m,p1)                  {if (dun_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_DUN, TRACE_TYPE_ERROR, m, p1);}
#define DUN_TRACE_ERROR2(m,p1,p2)               {if (dun_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_DUN, TRACE_TYPE_ERROR, m,p1,p2);}
#define DUN_TRACE_ERROR3(m,p1,p2,p3)            {if (dun_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_DUN, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define DUN_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (dun_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_DUN, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define DUN_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (dun_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_DUN, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define DUN_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (dun_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_DUN, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define DUN_TRACE_WARNING0(m)                   {if (dun_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_DUN, TRACE_TYPE_WARNING, m);}
#define DUN_TRACE_WARNING1(m,p1)                {if (dun_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_DUN, TRACE_TYPE_WARNING, m,p1);}
#define DUN_TRACE_WARNING2(m,p1,p2)             {if (dun_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_DUN, TRACE_TYPE_WARNING, m,p1,p2);}
#define DUN_TRACE_WARNING3(m,p1,p2,p3)          {if (dun_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_DUN, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define DUN_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (dun_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_DUN, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define DUN_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (dun_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_DUN, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define DUN_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (dun_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_DUN, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define DUN_TRACE_API0(m)                       {if (dun_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_DUN, TRACE_TYPE_API, m);}
#define DUN_TRACE_API1(m,p1)                    {if (dun_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_DUN, TRACE_TYPE_API, m, p1);}
#define DUN_TRACE_API2(m,p1,p2)                 {if (dun_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_DUN, TRACE_TYPE_API, m,p1,p2);}
#define DUN_TRACE_API3(m,p1,p2,p3)              {if (dun_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_DUN, TRACE_TYPE_API, m,p1,p2,p3);}
#define DUN_TRACE_API4(m,p1,p2,p3,p4)           {if (dun_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_DUN, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define DUN_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (dun_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_DUN, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define DUN_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (dun_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_DUN, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define DUN_TRACE_EVENT0(m)                     {if (dun_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_DUN, TRACE_TYPE_EVENT, m);}
#define DUN_TRACE_EVENT1(m,p1)                  {if (dun_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_DUN, TRACE_TYPE_EVENT, m, p1);}
#define DUN_TRACE_EVENT2(m,p1,p2)               {if (dun_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_DUN, TRACE_TYPE_EVENT, m,p1,p2);}
#define DUN_TRACE_EVENT3(m,p1,p2,p3)            {if (dun_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_DUN, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define DUN_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (dun_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_DUN, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define DUN_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (dun_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_DUN, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define DUN_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (dun_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_DUN, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define DUN_TRACE_DEBUG0(m)                     {if (dun_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_DUN, TRACE_TYPE_DEBUG, m);}
#define DUN_TRACE_DEBUG1(m,p1)                  {if (dun_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_DUN, TRACE_TYPE_DEBUG, m,p1);}
#define DUN_TRACE_DEBUG2(m,p1,p2)               {if (dun_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_DUN, TRACE_TYPE_DEBUG, m,p1,p2);}
#define DUN_TRACE_DEBUG3(m,p1,p2,p3)            {if (dun_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_DUN, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define DUN_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (dun_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_DUN, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define DUN_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (dun_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_DUN, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define DUN_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (dun_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_DUN, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* define traces for hardcopy cable replacement profile */

#define HCRP_TRACE_ERROR0(m)                     {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_HCRP, TRACE_TYPE_ERROR, m);}
#define HCRP_TRACE_ERROR1(m,p1)                  {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_HCRP, TRACE_TYPE_ERROR, m, p1);}
#define HCRP_TRACE_ERROR2(m,p1,p2)               {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_HCRP, TRACE_TYPE_ERROR, m,p1,p2);}
#define HCRP_TRACE_ERROR3(m,p1,p2,p3)            {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_HCRP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define HCRP_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_HCRP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define HCRP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_HCRP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define HCRP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_HCRP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define HCRP_TRACE_WARNING0(m)                   {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_HCRP, TRACE_TYPE_WARNING, m);}
#define HCRP_TRACE_WARNING1(m,p1)                {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_HCRP, TRACE_TYPE_WARNING, m,p1);}
#define HCRP_TRACE_WARNING2(m,p1,p2)             {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_HCRP, TRACE_TYPE_WARNING, m,p1,p2);}
#define HCRP_TRACE_WARNING3(m,p1,p2,p3)          {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_HCRP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define HCRP_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_HCRP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define HCRP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_HCRP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define HCRP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_HCRP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define HCRP_TRACE_API0(m)                       {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_HCRP, TRACE_TYPE_API, m);}
#define HCRP_TRACE_API1(m,p1)                    {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_HCRP, TRACE_TYPE_API, m, p1);}
#define HCRP_TRACE_API2(m,p1,p2)                 {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_HCRP, TRACE_TYPE_API, m,p1,p2);}
#define HCRP_TRACE_API3(m,p1,p2,p3)              {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_HCRP, TRACE_TYPE_API, m,p1,p2,p3);}
#define HCRP_TRACE_API4(m,p1,p2,p3,p4)           {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_HCRP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define HCRP_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_HCRP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define HCRP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_HCRP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define HCRP_TRACE_EVENT0(m)                     {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_HCRP, TRACE_TYPE_EVENT, m);}
#define HCRP_TRACE_EVENT1(m,p1)                  {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_HCRP, TRACE_TYPE_EVENT, m, p1);}
#define HCRP_TRACE_EVENT2(m,p1,p2)               {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_HCRP, TRACE_TYPE_EVENT, m,p1,p2);}
#define HCRP_TRACE_EVENT3(m,p1,p2,p3)            {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_HCRP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define HCRP_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_HCRP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define HCRP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_HCRP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define HCRP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_HCRP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define HCRP_TRACE_DEBUG0(m)                     {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_HCRP, TRACE_TYPE_DEBUG, m);}
#define HCRP_TRACE_DEBUG1(m,p1)                  {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_HCRP, TRACE_TYPE_DEBUG, m,p1);}
#define HCRP_TRACE_DEBUG2(m,p1,p2)               {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_HCRP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define HCRP_TRACE_DEBUG3(m,p1,p2,p3)            {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_HCRP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define HCRP_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_HCRP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define HCRP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_HCRP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define HCRP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (hcrp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_HCRP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* define traces for multi-client server hardcopy cable replacement profile */

#define HCRPM_TRACE_ERROR0(m)                     {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_HCRP, TRACE_TYPE_ERROR, m);}
#define HCRPM_TRACE_ERROR1(m,p1)                  {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_HCRP, TRACE_TYPE_ERROR, m, p1);}
#define HCRPM_TRACE_ERROR2(m,p1,p2)               {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_HCRP, TRACE_TYPE_ERROR, m,p1,p2);}
#define HCRPM_TRACE_ERROR3(m,p1,p2,p3)            {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_HCRP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define HCRPM_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_HCRP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define HCRPM_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_HCRP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define HCRPM_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_HCRP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define HCRPM_TRACE_WARNING0(m)                   {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_HCRP, TRACE_TYPE_WARNING, m);}
#define HCRPM_TRACE_WARNING1(m,p1)                {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_HCRP, TRACE_TYPE_WARNING, m,p1);}
#define HCRPM_TRACE_WARNING2(m,p1,p2)             {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_HCRP, TRACE_TYPE_WARNING, m,p1,p2);}
#define HCRPM_TRACE_WARNING3(m,p1,p2,p3)          {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_HCRP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define HCRPM_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_HCRP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define HCRPM_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_HCRP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define HCRPM_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_HCRP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define HCRPM_TRACE_API0(m)                       {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_HCRP, TRACE_TYPE_API, m);}
#define HCRPM_TRACE_API1(m,p1)                    {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_HCRP, TRACE_TYPE_API, m, p1);}
#define HCRPM_TRACE_API2(m,p1,p2)                 {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_HCRP, TRACE_TYPE_API, m,p1,p2);}
#define HCRPM_TRACE_API3(m,p1,p2,p3)              {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_HCRP, TRACE_TYPE_API, m,p1,p2,p3);}
#define HCRPM_TRACE_API4(m,p1,p2,p3,p4)           {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_HCRP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define HCRPM_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_HCRP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define HCRPM_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_HCRP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define HCRPM_TRACE_EVENT0(m)                     {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_HCRP, TRACE_TYPE_EVENT, m);}
#define HCRPM_TRACE_EVENT1(m,p1)                  {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_HCRP, TRACE_TYPE_EVENT, m, p1);}
#define HCRPM_TRACE_EVENT2(m,p1,p2)               {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_HCRP, TRACE_TYPE_EVENT, m,p1,p2);}
#define HCRPM_TRACE_EVENT3(m,p1,p2,p3)            {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_HCRP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define HCRPM_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_HCRP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define HCRPM_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_HCRP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define HCRPM_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_HCRP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define HCRPM_TRACE_DEBUG0(m)                     {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_HCRP, TRACE_TYPE_DEBUG, m);}
#define HCRPM_TRACE_DEBUG1(m,p1)                  {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_HCRP, TRACE_TYPE_DEBUG, m,p1);}
#define HCRPM_TRACE_DEBUG2(m,p1,p2)               {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_HCRP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define HCRPM_TRACE_DEBUG3(m,p1,p2,p3)            {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_HCRP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define HCRPM_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_HCRP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define HCRPM_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_HCRP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define HCRPM_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (hcrpm_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_HCRP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* define traces for RPC */

#define RPC_TRACE_ERROR0(m)                      {if (rpc_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_ERROR, (m));}
#define RPC_TRACE_ERROR1(m,p1)                   {if (rpc_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1));}
#define RPC_TRACE_ERROR2(m,p1,p2)                {if (rpc_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define RPC_TRACE_ERROR3(m,p1,p2,p3)             {if (rpc_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define RPC_TRACE_ERROR4(m,p1,p2,p3,p4)          {if (rpc_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define RPC_TRACE_ERROR5(m,p1,p2,p3,p4,p5)       {if (rpc_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define RPC_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)    {if (rpc_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

#define RPC_TRACE_WARNING0(m)                    {if (rpc_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_WARNING, (m));}
#define RPC_TRACE_WARNING1(m,p1)                 {if (rpc_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1));}
#define RPC_TRACE_WARNING2(m,p1,p2)              {if (rpc_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define RPC_TRACE_WARNING3(m,p1,p2,p3)           {if (rpc_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define RPC_TRACE_WARNING4(m,p1,p2,p3,p4)        {if (rpc_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define RPC_TRACE_WARNING5(m,p1,p2,p3,p4,p5)     {if (rpc_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define RPC_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)  {if (rpc_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

#define RPC_TRACE_API0(m)                        {if (rpc_trace_level >= BT_TRACE_LEVEL_API) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_API, (m));}
#define RPC_TRACE_API1(m,p1)                     {if (rpc_trace_level >= BT_TRACE_LEVEL_API) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1));}
#define RPC_TRACE_API2(m,p1,p2)                  {if (rpc_trace_level >= BT_TRACE_LEVEL_API) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define RPC_TRACE_API3(m,p1,p2,p3)               {if (rpc_trace_level >= BT_TRACE_LEVEL_API) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define RPC_TRACE_API4(m,p1,p2,p3,p4)            {if (rpc_trace_level >= BT_TRACE_LEVEL_API) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define RPC_TRACE_API5(m,p1,p2,p3,p4,p5)         {if (rpc_trace_level >= BT_TRACE_LEVEL_API) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define RPC_TRACE_API6(m,p1,p2,p3,p4,p5,p6)      {if (rpc_trace_level >= BT_TRACE_LEVEL_API) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

#define RPC_TRACE_EVENT0(m)                      {if (rpc_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_EVENT, (m));}
#define RPC_TRACE_EVENT1(m,p1)                   {if (rpc_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1));}
#define RPC_TRACE_EVENT2(m,p1,p2)                {if (rpc_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define RPC_TRACE_EVENT3(m,p1,p2,p3)             {if (rpc_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define RPC_TRACE_EVENT4(m,p1,p2,p3,p4)          {if (rpc_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define RPC_TRACE_EVENT5(m,p1,p2,p3,p4,p5)       {if (rpc_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define RPC_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)    {if (rpc_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

#define RPC_TRACE_DEBUG0(m)                      {if (rpc_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_DEBUG, (m));}
#define RPC_TRACE_DEBUG1(m,p1)                   {if (rpc_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1));}
#define RPC_TRACE_DEBUG2(m,p1,p2)                {if (rpc_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define RPC_TRACE_DEBUG3(m,p1,p2,p3)             {if (rpc_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define RPC_TRACE_DEBUG4(m,p1,p2,p3,p4)          {if (rpc_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define RPC_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)       {if (rpc_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define RPC_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)    {if (rpc_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_RPC | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

/* define traces for BNEP */

#define BNEP_TRACE_ERROR0(m)                     {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_BNEP, TRACE_TYPE_ERROR, m);}
#define BNEP_TRACE_ERROR1(m,p1)                  {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_BNEP, TRACE_TYPE_ERROR, m, p1);}
#define BNEP_TRACE_ERROR2(m,p1,p2)               {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_BNEP, TRACE_TYPE_ERROR, m,p1,p2);}
#define BNEP_TRACE_ERROR3(m,p1,p2,p3)            {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_BNEP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define BNEP_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_BNEP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define BNEP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_BNEP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define BNEP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_BNEP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define BNEP_TRACE_WARNING0(m)                   {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_BNEP, TRACE_TYPE_WARNING, m);}
#define BNEP_TRACE_WARNING1(m,p1)                {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_BNEP, TRACE_TYPE_WARNING, m,p1);}
#define BNEP_TRACE_WARNING2(m,p1,p2)             {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_BNEP, TRACE_TYPE_WARNING, m,p1,p2);}
#define BNEP_TRACE_WARNING3(m,p1,p2,p3)          {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_BNEP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define BNEP_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_BNEP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define BNEP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_BNEP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define BNEP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_BNEP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define BNEP_TRACE_API0(m)                       {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_BNEP, TRACE_TYPE_API, m);}
#define BNEP_TRACE_API1(m,p1)                    {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_BNEP, TRACE_TYPE_API, m, p1);}
#define BNEP_TRACE_API2(m,p1,p2)                 {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_BNEP, TRACE_TYPE_API, m,p1,p2);}
#define BNEP_TRACE_API3(m,p1,p2,p3)              {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_BNEP, TRACE_TYPE_API, m,p1,p2,p3);}
#define BNEP_TRACE_API4(m,p1,p2,p3,p4)           {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_BNEP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define BNEP_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_BNEP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define BNEP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_BNEP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define BNEP_TRACE_EVENT0(m)                     {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_BNEP, TRACE_TYPE_EVENT, m);}
#define BNEP_TRACE_EVENT1(m,p1)                  {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_BNEP, TRACE_TYPE_EVENT, m, p1);}
#define BNEP_TRACE_EVENT2(m,p1,p2)               {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_BNEP, TRACE_TYPE_EVENT, m,p1,p2);}
#define BNEP_TRACE_EVENT3(m,p1,p2,p3)            {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_BNEP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define BNEP_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_BNEP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define BNEP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_BNEP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define BNEP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_BNEP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define BNEP_TRACE_DEBUG0(m)                     {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_BNEP, TRACE_TYPE_DEBUG, m);}
#define BNEP_TRACE_DEBUG1(m,p1)                  {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_BNEP, TRACE_TYPE_DEBUG, m,p1);}
#define BNEP_TRACE_DEBUG2(m,p1,p2)               {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_BNEP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define BNEP_TRACE_DEBUG3(m,p1,p2,p3)            {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_BNEP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define BNEP_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_BNEP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define BNEP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_BNEP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define BNEP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (bnep_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_BNEP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* define traces for PAN */

#define PAN_TRACE_ERROR0(m)                     {if (pan_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_PAN, TRACE_TYPE_ERROR, m);}
#define PAN_TRACE_ERROR1(m,p1)                  {if (pan_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_PAN, TRACE_TYPE_ERROR, m, p1);}
#define PAN_TRACE_ERROR2(m,p1,p2)               {if (pan_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_PAN, TRACE_TYPE_ERROR, m,p1,p2);}
#define PAN_TRACE_ERROR3(m,p1,p2,p3)            {if (pan_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_PAN, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define PAN_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (pan_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_PAN, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define PAN_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (pan_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_PAN, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define PAN_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (pan_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_PAN, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define PAN_TRACE_WARNING0(m)                   {if (pan_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_PAN, TRACE_TYPE_WARNING, m);}
#define PAN_TRACE_WARNING1(m,p1)                {if (pan_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_PAN, TRACE_TYPE_WARNING, m,p1);}
#define PAN_TRACE_WARNING2(m,p1,p2)             {if (pan_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_PAN, TRACE_TYPE_WARNING, m,p1,p2);}
#define PAN_TRACE_WARNING3(m,p1,p2,p3)          {if (pan_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_PAN, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define PAN_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (pan_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_PAN, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define PAN_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (pan_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_PAN, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define PAN_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (pan_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_PAN, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define PAN_TRACE_API0(m)                       {if (pan_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_PAN, TRACE_TYPE_API, m);}
#define PAN_TRACE_API1(m,p1)                    {if (pan_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_PAN, TRACE_TYPE_API, m, p1);}
#define PAN_TRACE_API2(m,p1,p2)                 {if (pan_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_PAN, TRACE_TYPE_API, m,p1,p2);}
#define PAN_TRACE_API3(m,p1,p2,p3)              {if (pan_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_PAN, TRACE_TYPE_API, m,p1,p2,p3);}
#define PAN_TRACE_API4(m,p1,p2,p3,p4)           {if (pan_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_PAN, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define PAN_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (pan_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_PAN, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define PAN_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (pan_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_PAN, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define PAN_TRACE_EVENT0(m)                     {if (pan_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_PAN, TRACE_TYPE_EVENT, m);}
#define PAN_TRACE_EVENT1(m,p1)                  {if (pan_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_PAN, TRACE_TYPE_EVENT, m, p1);}
#define PAN_TRACE_EVENT2(m,p1,p2)               {if (pan_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_PAN, TRACE_TYPE_EVENT, m,p1,p2);}
#define PAN_TRACE_EVENT3(m,p1,p2,p3)            {if (pan_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_PAN, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define PAN_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (pan_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_PAN, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define PAN_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (pan_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_PAN, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define PAN_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (pan_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_PAN, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define PAN_TRACE_DEBUG0(m)                     {if (pan_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_PAN, TRACE_TYPE_DEBUG, m);}
#define PAN_TRACE_DEBUG1(m,p1)                  {if (pan_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_PAN, TRACE_TYPE_DEBUG, m,p1);}
#define PAN_TRACE_DEBUG2(m,p1,p2)               {if (pan_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_PAN, TRACE_TYPE_DEBUG, m,p1,p2);}
#define PAN_TRACE_DEBUG3(m,p1,p2,p3)            {if (pan_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_PAN, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define PAN_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (pan_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_PAN, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define PAN_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (pan_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_PAN, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define PAN_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (pan_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_PAN, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* define traces for SIM */

#define SAP_TRACE_ERROR0(m)                     {if (sap_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_SAP, TRACE_TYPE_ERROR, m);}
#define SAP_TRACE_ERROR1(m,p1)                  {if (sap_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_SAP, TRACE_TYPE_ERROR, m, p1);}
#define SAP_TRACE_ERROR2(m,p1,p2)               {if (sap_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_SAP, TRACE_TYPE_ERROR, m,p1,p2);}
#define SAP_TRACE_ERROR3(m,p1,p2,p3)            {if (sap_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_SAP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define SAP_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (sap_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_SAP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define SAP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (sap_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_SAP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define SAP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (sap_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_SAP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define SAP_TRACE_WARNING0(m)                   {if (sap_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_SAP, TRACE_TYPE_WARNING, m);}
#define SAP_TRACE_WARNING1(m,p1)                {if (sap_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_SAP, TRACE_TYPE_WARNING, m,p1);}
#define SAP_TRACE_WARNING2(m,p1,p2)             {if (sap_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_SAP, TRACE_TYPE_WARNING, m,p1,p2);}
#define SAP_TRACE_WARNING3(m,p1,p2,p3)          {if (sap_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_SAP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define SAP_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (sap_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_SAP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define SAP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (sap_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_SAP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define SAP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (sap_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_SAP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define SAP_TRACE_API0(m)                       {if (sap_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_SAP, TRACE_TYPE_API, m);}
#define SAP_TRACE_API1(m,p1)                    {if (sap_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_SAP, TRACE_TYPE_API, m, p1);}
#define SAP_TRACE_API2(m,p1,p2)                 {if (sap_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_SAP, TRACE_TYPE_API, m,p1,p2);}
#define SAP_TRACE_API3(m,p1,p2,p3)              {if (sap_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_SAP, TRACE_TYPE_API, m,p1,p2,p3);}
#define SAP_TRACE_API4(m,p1,p2,p3,p4)           {if (sap_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_SAP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define SAP_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (sap_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_SAP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define SAP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (sap_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_SAP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define SAP_TRACE_EVENT0(m)                     {if (sap_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_SAP, TRACE_TYPE_EVENT, m);}
#define SAP_TRACE_EVENT1(m,p1)                  {if (sap_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_SAP, TRACE_TYPE_EVENT, m, p1);}
#define SAP_TRACE_EVENT2(m,p1,p2)               {if (sap_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_SAP, TRACE_TYPE_EVENT, m,p1,p2);}
#define SAP_TRACE_EVENT3(m,p1,p2,p3)            {if (sap_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_SAP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define SAP_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (sap_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_SAP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define SAP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (sap_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_SAP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define SAP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (sap_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_SAP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define SAP_TRACE_DEBUG0(m)                     {if (sap_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_SAP, TRACE_TYPE_DEBUG, m);}
#define SAP_TRACE_DEBUG1(m,p1)                  {if (sap_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_SAP, TRACE_TYPE_DEBUG, m,p1);}
#define SAP_TRACE_DEBUG2(m,p1,p2)               {if (sap_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_SAP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define SAP_TRACE_DEBUG3(m,p1,p2,p3)            {if (sap_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_SAP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define SAP_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (sap_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_SAP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define SAP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (sap_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_SAP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define SAP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (sap_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_SAP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for OPP profile
*/
#define OPP_TRACE_ERROR0(m)                      {if (opp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_OPP, TRACE_TYPE_ERROR, m);}
#define OPP_TRACE_ERROR1(m,p1)                   {if (opp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_OPP, TRACE_TYPE_ERROR, m,p1);}
#define OPP_TRACE_ERROR2(m,p1,p2)                {if (opp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_OPP, TRACE_TYPE_ERROR, m,p1,p2);}
#define OPP_TRACE_ERROR3(m,p1,p2,p3)             {if (opp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_OPP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define OPP_TRACE_ERROR4(m,p1,p2,p3,p4)          {if (opp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_OPP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define OPP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)       {if (opp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_OPP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define OPP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)    {if (opp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_OPP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define OPP_TRACE_WARNING0(m)                    {if (opp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_OPP, TRACE_TYPE_WARNING, m);}
#define OPP_TRACE_WARNING1(m,p1)                 {if (opp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_OPP, TRACE_TYPE_WARNING, m,p1);}
#define OPP_TRACE_WARNING2(m,p1,p2)              {if (opp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_OPP, TRACE_TYPE_WARNING, m,p1,p2);}
#define OPP_TRACE_WARNING3(m,p1,p2,p3)           {if (opp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_OPP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define OPP_TRACE_WARNING4(m,p1,p2,p3,p4)        {if (opp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_OPP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define OPP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)     {if (opp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_OPP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define OPP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)  {if (opp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_OPP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define OPP_TRACE_EVENT0(m)                      {if (opp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_OPP, TRACE_TYPE_EVENT, m);}
#define OPP_TRACE_EVENT1(m,p1)                   {if (opp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_OPP, TRACE_TYPE_EVENT, m, p1);}
#define OPP_TRACE_EVENT2(m,p1,p2)                {if (opp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_OPP, TRACE_TYPE_EVENT, m,p1,p2);}
#define OPP_TRACE_EVENT3(m,p1,p2,p3)             {if (opp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_OPP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define OPP_TRACE_EVENT4(m,p1,p2,p3,p4)          {if (opp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_OPP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define OPP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)       {if (opp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_OPP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define OPP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)    {if (opp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_OPP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define OPP_TRACE_DEBUG0(m)                      {if (opp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_OPP, TRACE_TYPE_DEBUG, m);}
#define OPP_TRACE_DEBUG1(m,p1)                   {if (opp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_OPP, TRACE_TYPE_DEBUG, m,p1);}
#define OPP_TRACE_DEBUG2(m,p1,p2)                {if (opp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_OPP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define OPP_TRACE_DEBUG3(m,p1,p2,p3)             {if (opp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_OPP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define OPP_TRACE_DEBUG4(m,p1,p2,p3,p4)          {if (opp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_OPP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define OPP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)       {if (opp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_OPP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define OPP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)    {if (opp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_OPP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for FTP profile
*/
#define FTP_TRACE_ERROR0(m)                      {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_FTP, TRACE_TYPE_ERROR, m);}
#define FTP_TRACE_ERROR1(m,p1)                   {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_FTP, TRACE_TYPE_ERROR, m,p1);}
#define FTP_TRACE_ERROR2(m,p1,p2)                {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_FTP, TRACE_TYPE_ERROR, m,p1,p2);}
#define FTP_TRACE_ERROR3(m,p1,p2,p3)             {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_FTP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define FTP_TRACE_ERROR4(m,p1,p2,p3,p4)          {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_FTP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define FTP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)       {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_FTP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define FTP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)    {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_FTP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define FTP_TRACE_WARNING0(m)                    {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_FTP, TRACE_TYPE_WARNING, m);}
#define FTP_TRACE_WARNING1(m,p1)                 {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_FTP, TRACE_TYPE_WARNING, m,p1);}
#define FTP_TRACE_WARNING2(m,p1,p2)              {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_FTP, TRACE_TYPE_WARNING, m,p1,p2);}
#define FTP_TRACE_WARNING3(m,p1,p2,p3)           {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_FTP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define FTP_TRACE_WARNING4(m,p1,p2,p3,p4)        {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_FTP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define FTP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)     {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_FTP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define FTP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)  {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_FTP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define FTP_TRACE_EVENT0(m)                      {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_FTP, TRACE_TYPE_EVENT, m);}
#define FTP_TRACE_EVENT1(m,p1)                   {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_FTP, TRACE_TYPE_EVENT, m, p1);}
#define FTP_TRACE_EVENT2(m,p1,p2)                {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_FTP, TRACE_TYPE_EVENT, m,p1,p2);}
#define FTP_TRACE_EVENT3(m,p1,p2,p3)             {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_FTP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define FTP_TRACE_EVENT4(m,p1,p2,p3,p4)          {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_FTP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define FTP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)       {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_FTP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define FTP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)    {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_FTP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define FTP_TRACE_DEBUG0(m)                      {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_FTP, TRACE_TYPE_DEBUG, m);}
#define FTP_TRACE_DEBUG1(m,p1)                   {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_FTP, TRACE_TYPE_DEBUG, m,p1);}
#define FTP_TRACE_DEBUG2(m,p1,p2)                {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_FTP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define FTP_TRACE_DEBUG3(m,p1,p2,p3)             {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_FTP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define FTP_TRACE_DEBUG4(m,p1,p2,p3,p4)          {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_FTP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define FTP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)       {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_FTP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define FTP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)    {if (ftp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_FTP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the A2DP profile
*/
#define A2D_TRACE_ERROR0(m)                      {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_A2D, TRACE_TYPE_ERROR,m);}
#define A2D_TRACE_ERROR1(m,p1)                   {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_A2D, TRACE_TYPE_ERROR,m,p1);}
#define A2D_TRACE_ERROR2(m,p1,p2)                {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_A2D, TRACE_TYPE_ERROR,m,p1,p2);}
#define A2D_TRACE_ERROR3(m,p1,p2,p3)             {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_A2D, TRACE_TYPE_ERROR,m,p1,p2,p3);}
#define A2D_TRACE_ERROR4(m,p1,p2,p3,p4)          {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_A2D, TRACE_TYPE_ERROR,m,p1,p2,p3,p4);}
#define A2D_TRACE_ERROR5(m,p1,p2,p3,p4,p5)       {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_A2D, TRACE_TYPE_ERROR,m,p1,p2,p3,p4,p5);}
#define A2D_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)    {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_A2D, TRACE_TYPE_ERROR,m,p1,p2,p3,p4,p5,p6);}

#define A2D_TRACE_WARNING0(m)                    {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_A2D, TRACE_TYPE_WARNING,m);}
#define A2D_TRACE_WARNING1(m,p1)                 {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_A2D, TRACE_TYPE_WARNING,m,p1);}
#define A2D_TRACE_WARNING2(m,p1,p2)              {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_A2D, TRACE_TYPE_WARNING,m,p1,p2);}
#define A2D_TRACE_WARNING3(m,p1,p2,p3)           {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_A2D, TRACE_TYPE_WARNING,m,p1,p2,p3);}
#define A2D_TRACE_WARNING4(m,p1,p2,p3,p4)        {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_A2D, TRACE_TYPE_WARNING,m,p1,p2,p3,p4);}
#define A2D_TRACE_WARNING5(m,p1,p2,p3,p4,p5)     {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_A2D, TRACE_TYPE_WARNING,m,p1,p2,p3,p4,p5);}
#define A2D_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)  {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_A2D, TRACE_TYPE_WARNING,m,p1,p2,p3,p4,p5,p6);}

#define A2D_TRACE_EVENT0(m)                      {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_A2D, TRACE_TYPE_EVENT,m);}
#define A2D_TRACE_EVENT1(m,p1)                   {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_A2D, TRACE_TYPE_EVENT,m, p1);}
#define A2D_TRACE_EVENT2(m,p1,p2)                {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_A2D, TRACE_TYPE_EVENT,m,p1,p2);}
#define A2D_TRACE_EVENT3(m,p1,p2,p3)             {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_A2D, TRACE_TYPE_EVENT,m,p1,p2,p3);}
#define A2D_TRACE_EVENT4(m,p1,p2,p3,p4)          {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_A2D, TRACE_TYPE_EVENT,m,p1,p2,p3,p4);}
#define A2D_TRACE_EVENT5(m,p1,p2,p3,p4,p5)       {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_A2D, TRACE_TYPE_EVENT,m,p1,p2,p3,p4,p5);}
#define A2D_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)    {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_A2D, TRACE_TYPE_EVENT,m,p1,p2,p3,p4,p5,p6);}

#define A2D_TRACE_DEBUG0(m)                      {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_A2D, TRACE_TYPE_DEBUG,m);}
#define A2D_TRACE_DEBUG1(m,p1)                   {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_A2D, TRACE_TYPE_DEBUG,m,p1);}
#define A2D_TRACE_DEBUG2(m,p1,p2)                {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_A2D, TRACE_TYPE_DEBUG,m,p1,p2);}
#define A2D_TRACE_DEBUG3(m,p1,p2,p3)             {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_A2D, TRACE_TYPE_DEBUG,m,p1,p2,p3);}
#define A2D_TRACE_DEBUG4(m,p1,p2,p3,p4)          {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_A2D, TRACE_TYPE_DEBUG,m,p1,p2,p3,p4);}
#define A2D_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)       {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_A2D, TRACE_TYPE_DEBUG,m,p1,p2,p3,p4,p5);}
#define A2D_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)    {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_A2D, TRACE_TYPE_DEBUG,m,p1,p2,p3,p4,p5,p6);}

#define A2D_TRACE_API0(m)                        {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_A2D, TRACE_TYPE_API,m);}
#define A2D_TRACE_API1(m,p1)                     {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_A2D, TRACE_TYPE_API,m, p1);}
#define A2D_TRACE_API2(m,p1,p2)                  {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_A2D, TRACE_TYPE_API,m,p1,p2);}
#define A2D_TRACE_API3(m,p1,p2,p3)               {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_A2D, TRACE_TYPE_API,m,p1,p2,p3);}
#define A2D_TRACE_API4(m,p1,p2,p3,p4)            {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_A2D, TRACE_TYPE_API,m,p1,p2,p3,p4);}
#define A2D_TRACE_API5(m,p1,p2,p3,p4,p5)         {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_A2D, TRACE_TYPE_API,m,p1,p2,p3,p4,p5);}
#define A2D_TRACE_API6(m,p1,p2,p3,p4,p5,p6)      {if (a2d_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_A2D, TRACE_TYPE_API,m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the VDP profile
*/
#define VDP_TRACE_ERROR0(m)                      {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_ERROR,m);}
#define VDP_TRACE_ERROR1(m,p1)                   {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_ERROR,m,p1);}
#define VDP_TRACE_ERROR2(m,p1,p2)                {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_ERROR,m,p1,p2);}
#define VDP_TRACE_ERROR3(m,p1,p2,p3)             {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_ERROR,m,p1,p2,p3);}
#define VDP_TRACE_ERROR4(m,p1,p2,p3,p4)          {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_ERROR,m,p1,p2,p3,p4);}
#define VDP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)       {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_ERROR,m,p1,p2,p3,p4,p5);}
#define VDP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)    {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_ERROR,m,p1,p2,p3,p4,p5,p6);}

#define VDP_TRACE_WARNING0(m)                    {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_WARNING,m);}
#define VDP_TRACE_WARNING1(m,p1)                 {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_WARNING,m,p1);}
#define VDP_TRACE_WARNING2(m,p1,p2)              {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_WARNING,m,p1,p2);}
#define VDP_TRACE_WARNING3(m,p1,p2,p3)           {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_WARNING,m,p1,p2,p3);}
#define VDP_TRACE_WARNING4(m,p1,p2,p3,p4)        {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_WARNING,m,p1,p2,p3,p4);}
#define VDP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)     {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_WARNING,m,p1,p2,p3,p4,p5);}
#define VDP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)  {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_WARNING,m,p1,p2,p3,p4,p5,p6);}

#define VDP_TRACE_EVENT0(m)                      {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_EVENT,m);}
#define VDP_TRACE_EVENT1(m,p1)                   {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_EVENT,m, p1);}
#define VDP_TRACE_EVENT2(m,p1,p2)                {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_EVENT,m,p1,p2);}
#define VDP_TRACE_EVENT3(m,p1,p2,p3)             {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_EVENT,m,p1,p2,p3);}
#define VDP_TRACE_EVENT4(m,p1,p2,p3,p4)          {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_EVENT,m,p1,p2,p3,p4);}
#define VDP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)       {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_EVENT,m,p1,p2,p3,p4,p5);}
#define VDP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)    {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_EVENT,m,p1,p2,p3,p4,p5,p6);}

#define VDP_TRACE_DEBUG0(m)                      {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG,m);}
#define VDP_TRACE_DEBUG1(m,p1)                   {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG,m,p1);}
#define VDP_TRACE_DEBUG2(m,p1,p2)                {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG,m,p1,p2);}
#define VDP_TRACE_DEBUG3(m,p1,p2,p3)             {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG,m,p1,p2,p3);}
#define VDP_TRACE_DEBUG4(m,p1,p2,p3,p4)          {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG,m,p1,p2,p3,p4);}
#define VDP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)       {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG,m,p1,p2,p3,p4,p5);}
#define VDP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)    {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG,m,p1,p2,p3,p4,p5,p6);}

#define VDP_TRACE_API0(m)                        {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_API,m);}
#define VDP_TRACE_API1(m,p1)                     {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_API,m, p1);}
#define VDP_TRACE_API2(m,p1,p2)                  {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_API,m,p1,p2);}
#define VDP_TRACE_API3(m,p1,p2,p3)               {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_API,m,p1,p2,p3);}
#define VDP_TRACE_API4(m,p1,p2,p3,p4)            {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_API,m,p1,p2,p3,p4);}
#define VDP_TRACE_API5(m,p1,p2,p3,p4,p5)         {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_API,m,p1,p2,p3,p4,p5);}
#define VDP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)      {if (vdp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_API,m,p1,p2,p3,p4,p5,p6);}


/* Define tracing for the LM unit
*/
#define LMP_TRACE_ERROR0(m)                     {if (lmp_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_LM, TRACE_TYPE_ERROR, m);}
#define LMP_TRACE_ERROR1(m,p1)                  {if (lmp_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_LM, TRACE_TYPE_ERROR, m,p1);}
#define LMP_TRACE_ERROR2(m,p1,p2)               {if (lmp_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_LM, TRACE_TYPE_ERROR, m,p1,p2);}
#define LMP_TRACE_ERROR3(m,p1,p2,p3)            {if (lmp_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_LM, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define LMP_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (lmp_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_LM, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define LMP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (lmp_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_LM, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define LMP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (lmp_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_LM, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define LMP_TRACE_WARNING0(m)                   {if (lmp_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_LM, TRACE_TYPE_WARNING, m);}
#define LMP_TRACE_WARNING1(m,p1)                {if (lmp_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_LM, TRACE_TYPE_WARNING, m,p1);}
#define LMP_TRACE_WARNING2(m,p1,p2)             {if (lmp_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_LM, TRACE_TYPE_WARNING, m,p1,p2);}
#define LMP_TRACE_WARNING3(m,p1,p2,p3)          {if (lmp_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_LM, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define LMP_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (lmp_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_LM, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define LMP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (lmp_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_LM, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define LMP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (lmp_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_LM, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define LMP_TRACE_EVENT0(m)                     {if (lmp_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_LM, TRACE_TYPE_EVENT, m);}
#define LMP_TRACE_EVENT1(m,p1)                  {if (lmp_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_LM, TRACE_TYPE_EVENT, m, p1);}
#define LMP_TRACE_EVENT2(m,p1,p2)               {if (lmp_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_LM, TRACE_TYPE_EVENT, m,p1,p2);}
#define LMP_TRACE_EVENT3(m,p1,p2,p3)            {if (lmp_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_LM, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define LMP_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (lmp_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_LM, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define LMP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (lmp_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_LM, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define LMP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (lmp_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_LM, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define LMP_TRACE_DEBUG0(m)                     {if (lmp_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_LM, TRACE_TYPE_DEBUG, m);}
#define LMP_TRACE_DEBUG1(m,p1)                  {if (lmp_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_LM, TRACE_TYPE_DEBUG, m,p1);}
#define LMP_TRACE_DEBUG2(m,p1,p2)               {if (lmp_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_LM, TRACE_TYPE_DEBUG, m,p1,p2);}
#define LMP_TRACE_DEBUG3(m,p1,p2,p3)            {if (lmp_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_LM, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define LMP_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (lmp_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_LM, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define LMP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (lmp_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_LM, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define LMP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (lmp_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_LM, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the LC unit
*/
#define LC_TRACE_ERROR0(m)                     {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_ERROR]) BT_TRACE_0(TRACE_LAYER_LC, TRACE_TYPE_ERROR, m);}
#define LC_TRACE_ERROR1(m,p1)                  {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_ERROR]) BT_TRACE_1(TRACE_LAYER_LC, TRACE_TYPE_ERROR, m,p1);}
#define LC_TRACE_ERROR2(m,p1,p2)               {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_ERROR]) BT_TRACE_2(TRACE_LAYER_LC, TRACE_TYPE_ERROR, m,p1,p2);}
#define LC_TRACE_ERROR3(m,p1,p2,p3)            {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_ERROR]) BT_TRACE_3(TRACE_LAYER_LC, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define LC_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_ERROR]) BT_TRACE_4(TRACE_LAYER_LC, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define LC_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_ERROR]) BT_TRACE_5(TRACE_LAYER_LC, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define LC_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_ERROR]) BT_TRACE_6(TRACE_LAYER_LC, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define LC_TRACE_WARNING0(m)                   {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_WARNING]) BT_TRACE_0(TRACE_LAYER_LC, TRACE_TYPE_WARNING, m);}
#define LC_TRACE_WARNING1(m,p1)                {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_WARNING]) BT_TRACE_1(TRACE_LAYER_LC, TRACE_TYPE_WARNING, m,p1);}
#define LC_TRACE_WARNING2(m,p1,p2)             {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_WARNING]) BT_TRACE_2(TRACE_LAYER_LC, TRACE_TYPE_WARNING, m,p1,p2);}
#define LC_TRACE_WARNING3(m,p1,p2,p3)          {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_WARNING]) BT_TRACE_3(TRACE_LAYER_LC, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define LC_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_WARNING]) BT_TRACE_4(TRACE_LAYER_LC, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define LC_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_WARNING]) BT_TRACE_5(TRACE_LAYER_LC, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define LC_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_WARNING]) BT_TRACE_6(TRACE_LAYER_LC, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define LC_TRACE_EVENT0(m)                     {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_EVENT]) BT_TRACE_0(TRACE_LAYER_LC, TRACE_TYPE_EVENT, m);}
#define LC_TRACE_EVENT1(m,p1)                  {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_EVENT]) BT_TRACE_1(TRACE_LAYER_LC, TRACE_TYPE_EVENT, m, p1);}
#define LC_TRACE_EVENT2(m,p1,p2)               {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_EVENT]) BT_TRACE_2(TRACE_LAYER_LC, TRACE_TYPE_EVENT, m,p1,p2);}
#define LC_TRACE_EVENT3(m,p1,p2,p3)            {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_EVENT]) BT_TRACE_3(TRACE_LAYER_LC, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define LC_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_EVENT]) BT_TRACE_4(TRACE_LAYER_LC, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define LC_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_EVENT]) BT_TRACE_5(TRACE_LAYER_LC, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define LC_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_EVENT]) BT_TRACE_6(TRACE_LAYER_LC, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define LC_TRACE_DEBUG0(m)                     {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_DEBUG]) BT_TRACE_0(TRACE_LAYER_LC, TRACE_TYPE_DEBUG, m);}
#define LC_TRACE_DEBUG1(m,p1)                  {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_DEBUG]) BT_TRACE_1(TRACE_LAYER_LC, TRACE_TYPE_DEBUG, m,p1);}
#define LC_TRACE_DEBUG2(m,p1,p2)               {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_DEBUG]) BT_TRACE_2(TRACE_LAYER_LC, TRACE_TYPE_DEBUG, m,p1,p2);}
#define LC_TRACE_DEBUG3(m,p1,p2,p3)            {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_DEBUG]) BT_TRACE_3(TRACE_LAYER_LC, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define LC_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_DEBUG]) BT_TRACE_5(TRACE_LAYER_LC, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define LC_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (lc_trace_level & trace_map[BT_TRACE_LEVEL_DEBUG]) BT_TRACE_6(TRACE_LAYER_LC, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the Serial Dongle Application SDA
*/
#define SDA_TRACE_ERROR0(m)                     {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(m);}
#define SDA_TRACE_ERROR1(m,p1)                  {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(m,p1);}
#define SDA_TRACE_ERROR2(m,p1,p2)               {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(m,p1,p2);}
#define SDA_TRACE_ERROR3(m,p1,p2,p3)            {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(m,p1,p2,p3);}
#define SDA_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(m,p1,p2,p3,p4);}
#define SDA_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(m,p1,p2,p3,p4,p5);}
#define SDA_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(m,p1,p2,p3,p4,p5,p6);}

#define SDA_TRACE_WARNING0(m)                   {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(m);}
#define SDA_TRACE_WARNING1(m,p1)                {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(m,p1);}
#define SDA_TRACE_WARNING2(m,p1,p2)             {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(m,p1,p2);}
#define SDA_TRACE_WARNING3(m,p1,p2,p3)          {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(m,p1,p2,p3);}
#define SDA_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(m,p1,p2,p3,p4);}
#define SDA_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(m,p1,p2,p3,p4,p5);}
#define SDA_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(m,p1,p2,p3,p4,p5,p6);}

#define SDA_TRACE_EVENT0(m)                     {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(m);}
#define SDA_TRACE_EVENT1(m,p1)                  {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(m, p1);}
#define SDA_TRACE_EVENT2(m,p1,p2)               {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(m,p1,p2);}
#define SDA_TRACE_EVENT3(m,p1,p2,p3)            {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(m,p1,p2,p3);}
#define SDA_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(m,p1,p2,p3,p4);}
#define SDA_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(m,p1,p2,p3,p4,p5);}
#define SDA_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(m,p1,p2,p3,p4,p5,p6);}

#define SDA_TRACE_DEBUG0(m)                     {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(m);}
#define SDA_TRACE_DEBUG1(m,p1)                  {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(m,p1);}
#define SDA_TRACE_DEBUG2(m,p1,p2)               {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(m,p1,p2);}
#define SDA_TRACE_DEBUG3(m,p1,p2,p3)            {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(m,p1,p2,p3);}
#define SDA_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(m,p1,p2,p3,p4);}
#define SDA_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(m,p1,p2,p3,p4,p5);}
#define SDA_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (sda_config_cb.sda_trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(m,p1,p2,p3,p4,p5,p6);}

/* AVDTP
*/
#define AVDT_TRACE_ERROR0(m)                     {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_ERROR, m);}
#define AVDT_TRACE_ERROR1(m,p1)                  {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_ERROR, m,p1);}
#define AVDT_TRACE_ERROR2(m,p1,p2)               {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_ERROR, m,p1,p2);}
#define AVDT_TRACE_ERROR3(m,p1,p2,p3)            {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define AVDT_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define AVDT_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define AVDT_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define AVDT_TRACE_WARNING0(m)                   {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_WARNING, m);}
#define AVDT_TRACE_WARNING1(m,p1)                {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_WARNING, m,p1);}
#define AVDT_TRACE_WARNING2(m,p1,p2)             {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_WARNING, m,p1,p2);}
#define AVDT_TRACE_WARNING3(m,p1,p2,p3)          {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define AVDT_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define AVDT_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define AVDT_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define AVDT_TRACE_EVENT0(m)                     {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_EVENT, m);}
#define AVDT_TRACE_EVENT1(m,p1)                  {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_EVENT, m, p1);}
#define AVDT_TRACE_EVENT2(m,p1,p2)               {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_EVENT, m,p1,p2);}
#define AVDT_TRACE_EVENT3(m,p1,p2,p3)            {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define AVDT_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define AVDT_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define AVDT_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define AVDT_TRACE_DEBUG0(m)                     {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG, m);}
#define AVDT_TRACE_DEBUG1(m,p1)                  {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG, m,p1);}
#define AVDT_TRACE_DEBUG2(m,p1,p2)               {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define AVDT_TRACE_DEBUG3(m,p1,p2,p3)            {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define AVDT_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define AVDT_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define AVDT_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

#define AVDT_TRACE_API0(m)                     {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_API, m);}
#define AVDT_TRACE_API1(m,p1)                  {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_API, m,p1);}
#define AVDT_TRACE_API2(m,p1,p2)               {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_API, m,p1,p2);}
#define AVDT_TRACE_API3(m,p1,p2,p3)            {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_API, m,p1,p2,p3);}
#define AVDT_TRACE_API4(m,p1,p2,p3,p4)         {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define AVDT_TRACE_API5(m,p1,p2,p3,p4,p5)      {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define AVDT_TRACE_API6(m,p1,p2,p3,p4,p5,p6)   {if (avdt_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the AVCTP protocol
*/
#define AVCT_TRACE_ERROR0(m)                     {if (avct_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_ERROR, m);}
#define AVCT_TRACE_ERROR1(m,p1)                  {if (avct_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_ERROR, m,p1);}
#define AVCT_TRACE_ERROR2(m,p1,p2)               {if (avct_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_ERROR, m,p1,p2);}
#define AVCT_TRACE_ERROR3(m,p1,p2,p3)            {if (avct_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define AVCT_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (avct_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define AVCT_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (avct_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define AVCT_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (avct_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define AVCT_TRACE_WARNING0(m)                   {if (avct_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_WARNING, m);}
#define AVCT_TRACE_WARNING1(m,p1)                {if (avct_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_WARNING, m,p1);}
#define AVCT_TRACE_WARNING2(m,p1,p2)             {if (avct_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_WARNING, m,p1,p2);}
#define AVCT_TRACE_WARNING3(m,p1,p2,p3)          {if (avct_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define AVCT_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (avct_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define AVCT_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (avct_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define AVCT_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (avct_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define AVCT_TRACE_EVENT0(m)                     {if (avct_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_EVENT, m);}
#define AVCT_TRACE_EVENT1(m,p1)                  {if (avct_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_EVENT, m, p1);}
#define AVCT_TRACE_EVENT2(m,p1,p2)               {if (avct_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_EVENT, m,p1,p2);}
#define AVCT_TRACE_EVENT3(m,p1,p2,p3)            {if (avct_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define AVCT_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (avct_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define AVCT_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (avct_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define AVCT_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (avct_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define AVCT_TRACE_DEBUG0(m)                     {if (avct_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG, m);}
#define AVCT_TRACE_DEBUG1(m,p1)                  {if (avct_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG, m,p1);}
#define AVCT_TRACE_DEBUG2(m,p1,p2)               {if (avct_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define AVCT_TRACE_DEBUG3(m,p1,p2,p3)            {if (avct_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define AVCT_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (avct_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define AVCT_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (avct_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define AVCT_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (avct_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

#define AVCT_TRACE_API0(m)                     {if (avct_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_API, m);}
#define AVCT_TRACE_API1(m,p1)                  {if (avct_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_API, m,p1);}
#define AVCT_TRACE_API2(m,p1,p2)               {if (avct_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_API, m,p1,p2);}
#define AVCT_TRACE_API3(m,p1,p2,p3)            {if (avct_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_API, m,p1,p2,p3);}
#define AVCT_TRACE_API4(m,p1,p2,p3,p4)         {if (avct_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define AVCT_TRACE_API5(m,p1,p2,p3,p4,p5)      {if (avct_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define AVCT_TRACE_API6(m,p1,p2,p3,p4,p5,p6)   {if (avct_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}


/* Define tracing for the AVRCP profile
*/
#define AVRC_TRACE_ERROR0(m)                      {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_ERROR,m);}
#define AVRC_TRACE_ERROR1(m,p1)                   {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_ERROR,m,p1);}
#define AVRC_TRACE_ERROR2(m,p1,p2)                {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_ERROR,m,p1,p2);}
#define AVRC_TRACE_ERROR3(m,p1,p2,p3)             {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_ERROR,m,p1,p2,p3);}
#define AVRC_TRACE_ERROR4(m,p1,p2,p3,p4)          {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_ERROR,m,p1,p2,p3,p4);}
#define AVRC_TRACE_ERROR5(m,p1,p2,p3,p4,p5)       {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_ERROR,m,p1,p2,p3,p4,p5);}
#define AVRC_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)    {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_ERROR,m,p1,p2,p3,p4,p5,p6);}

#define AVRC_TRACE_WARNING0(m)                    {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_WARNING,m);}
#define AVRC_TRACE_WARNING1(m,p1)                 {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_WARNING,m,p1);}
#define AVRC_TRACE_WARNING2(m,p1,p2)              {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_WARNING,m,p1,p2);}
#define AVRC_TRACE_WARNING3(m,p1,p2,p3)           {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_WARNING,m,p1,p2,p3);}
#define AVRC_TRACE_WARNING4(m,p1,p2,p3,p4)        {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_WARNING,m,p1,p2,p3,p4);}
#define AVRC_TRACE_WARNING5(m,p1,p2,p3,p4,p5)     {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_WARNING,m,p1,p2,p3,p4,p5);}
#define AVRC_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)  {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_WARNING,m,p1,p2,p3,p4,p5,p6);}

#define AVRC_TRACE_EVENT0(m)                      {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_EVENT,m);}
#define AVRC_TRACE_EVENT1(m,p1)                   {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_EVENT,m, p1);}
#define AVRC_TRACE_EVENT2(m,p1,p2)                {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_EVENT,m,p1,p2);}
#define AVRC_TRACE_EVENT3(m,p1,p2,p3)             {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_EVENT,m,p1,p2,p3);}
#define AVRC_TRACE_EVENT4(m,p1,p2,p3,p4)          {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_EVENT,m,p1,p2,p3,p4);}
#define AVRC_TRACE_EVENT5(m,p1,p2,p3,p4,p5)       {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_EVENT,m,p1,p2,p3,p4,p5);}
#define AVRC_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)    {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_EVENT,m,p1,p2,p3,p4,p5,p6);}

#define AVRC_TRACE_DEBUG0(m)                      {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG,m);}
#define AVRC_TRACE_DEBUG1(m,p1)                   {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG,m,p1);}
#define AVRC_TRACE_DEBUG2(m,p1,p2)                {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG,m,p1,p2);}
#define AVRC_TRACE_DEBUG3(m,p1,p2,p3)             {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG,m,p1,p2,p3);}
#define AVRC_TRACE_DEBUG4(m,p1,p2,p3,p4)          {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG,m,p1,p2,p3,p4);}
#define AVRC_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)       {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG,m,p1,p2,p3,p4,p5);}
#define AVRC_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)    {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_DEBUG,m,p1,p2,p3,p4,p5,p6);}

#define AVRC_TRACE_API0(m)                        {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_AVP, TRACE_TYPE_API,m);}
#define AVRC_TRACE_API1(m,p1)                     {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_AVP, TRACE_TYPE_API,m, p1);}
#define AVRC_TRACE_API2(m,p1,p2)                  {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_AVP, TRACE_TYPE_API,m,p1,p2);}
#define AVRC_TRACE_API3(m,p1,p2,p3)               {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_AVP, TRACE_TYPE_API,m,p1,p2,p3);}
#define AVRC_TRACE_API4(m,p1,p2,p3,p4)            {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_AVP, TRACE_TYPE_API,m,p1,p2,p3,p4);}
#define AVRC_TRACE_API5(m,p1,p2,p3,p4,p5)         {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_AVP, TRACE_TYPE_API,m,p1,p2,p3,p4,p5);}
#define AVRC_TRACE_API6(m,p1,p2,p3,p4,p5,p6)      {if (avrc_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_AVP, TRACE_TYPE_API,m,p1,p2,p3,p4,p5,p6);}

/* MCAP
*/
#define MCA_TRACE_ERROR0(m)                     {if (mca_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_MCA, TRACE_TYPE_ERROR, m);}
#define MCA_TRACE_ERROR1(m,p1)                  {if (mca_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_MCA, TRACE_TYPE_ERROR, m,p1);}
#define MCA_TRACE_ERROR2(m,p1,p2)               {if (mca_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_MCA, TRACE_TYPE_ERROR, m,p1,p2);}
#define MCA_TRACE_ERROR3(m,p1,p2,p3)            {if (mca_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_MCA, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define MCA_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (mca_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_MCA, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define MCA_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (mca_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_MCA, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define MCA_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (mca_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_MCA, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define MCA_TRACE_WARNING0(m)                   {if (mca_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_MCA, TRACE_TYPE_WARNING, m);}
#define MCA_TRACE_WARNING1(m,p1)                {if (mca_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_MCA, TRACE_TYPE_WARNING, m,p1);}
#define MCA_TRACE_WARNING2(m,p1,p2)             {if (mca_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_MCA, TRACE_TYPE_WARNING, m,p1,p2);}
#define MCA_TRACE_WARNING3(m,p1,p2,p3)          {if (mca_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_MCA, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define MCA_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (mca_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_MCA, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define MCA_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (mca_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_MCA, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define MCA_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (mca_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_MCA, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define MCA_TRACE_EVENT0(m)                     {if (mca_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_MCA, TRACE_TYPE_EVENT, m);}
#define MCA_TRACE_EVENT1(m,p1)                  {if (mca_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_MCA, TRACE_TYPE_EVENT, m, p1);}
#define MCA_TRACE_EVENT2(m,p1,p2)               {if (mca_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_MCA, TRACE_TYPE_EVENT, m,p1,p2);}
#define MCA_TRACE_EVENT3(m,p1,p2,p3)            {if (mca_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_MCA, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define MCA_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (mca_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_MCA, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define MCA_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (mca_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_MCA, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define MCA_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (mca_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_MCA, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define MCA_TRACE_DEBUG0(m)                     {if (mca_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_MCA, TRACE_TYPE_DEBUG, m);}
#define MCA_TRACE_DEBUG1(m,p1)                  {if (mca_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_MCA, TRACE_TYPE_DEBUG, m,p1);}
#define MCA_TRACE_DEBUG2(m,p1,p2)               {if (mca_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_MCA, TRACE_TYPE_DEBUG, m,p1,p2);}
#define MCA_TRACE_DEBUG3(m,p1,p2,p3)            {if (mca_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_MCA, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define MCA_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (mca_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_MCA, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define MCA_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (mca_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_MCA, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define MCA_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (mca_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_MCA, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

#define MCA_TRACE_API0(m)                     {if (mca_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_MCA, TRACE_TYPE_API, m);}
#define MCA_TRACE_API1(m,p1)                  {if (mca_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_MCA, TRACE_TYPE_API, m,p1);}
#define MCA_TRACE_API2(m,p1,p2)               {if (mca_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_MCA, TRACE_TYPE_API, m,p1,p2);}
#define MCA_TRACE_API3(m,p1,p2,p3)            {if (mca_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_MCA, TRACE_TYPE_API, m,p1,p2,p3);}
#define MCA_TRACE_API4(m,p1,p2,p3,p4)         {if (mca_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_MCA, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define MCA_TRACE_API5(m,p1,p2,p3,p4,p5)      {if (mca_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_MCA, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define MCA_TRACE_API6(m,p1,p2,p3,p4,p5,p6)   {if (mca_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_MCA, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the AMP unit
*/
#define AMP_TRACE_ERROR0(m)                     {if (amp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_AMP, TRACE_TYPE_ERROR, m);}
#define AMP_TRACE_ERROR1(m,p1)                  {if (amp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_AMP, TRACE_TYPE_ERROR, m,p1);}
#define AMP_TRACE_ERROR2(m,p1,p2)               {if (amp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_AMP, TRACE_TYPE_ERROR, m,p1,p2);}
#define AMP_TRACE_ERROR3(m,p1,p2,p3)            {if (amp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_AMP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define AMP_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (amp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_AMP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define AMP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (amp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_AMP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define AMP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (amp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_AMP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define AMP_TRACE_WARNING0(m)                   {if (amp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_AMP, TRACE_TYPE_WARNING, m);}
#define AMP_TRACE_WARNING1(m,p1)                {if (amp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_AMP, TRACE_TYPE_WARNING, m,p1);}
#define AMP_TRACE_WARNING2(m,p1,p2)             {if (amp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_AMP, TRACE_TYPE_WARNING, m,p1,p2);}
#define AMP_TRACE_WARNING3(m,p1,p2,p3)          {if (amp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_AMP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define AMP_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (amp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_AMP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define AMP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (amp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_AMP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define AMP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (amp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_AMP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define AMP_TRACE_API0(m)                       {if (amp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_AMP, TRACE_TYPE_API, m);}
#define AMP_TRACE_API1(m,p1)                    {if (amp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_AMP, TRACE_TYPE_API, m,p1);}
#define AMP_TRACE_API2(m,p1,p2)                 {if (amp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_AMP, TRACE_TYPE_API, m,p1,p2);}
#define AMP_TRACE_API3(m,p1,p2,p3)              {if (amp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_AMP, TRACE_TYPE_API, m,p1,p2,p3);}
#define AMP_TRACE_API4(m,p1,p2,p3,p4)           {if (amp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_AMP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define AMP_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (amp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_AMP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define AMP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (amp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_AMP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define AMP_TRACE_EVENT0(m)                     {if (amp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_AMP, TRACE_TYPE_EVENT, m);}
#define AMP_TRACE_EVENT1(m,p1)                  {if (amp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_AMP, TRACE_TYPE_EVENT, m, p1);}
#define AMP_TRACE_EVENT2(m,p1,p2)               {if (amp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_AMP, TRACE_TYPE_EVENT, m,p1,p2);}
#define AMP_TRACE_EVENT3(m,p1,p2,p3)            {if (amp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_AMP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define AMP_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (amp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_AMP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define AMP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (amp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_AMP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define AMP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (amp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_AMP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define AMP_TRACE_DEBUG0(m)                     {if (amp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_AMP, TRACE_TYPE_DEBUG, m);}
#define AMP_TRACE_DEBUG1(m,p1)                  {if (amp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_AMP, TRACE_TYPE_DEBUG, m,p1);}
#define AMP_TRACE_DEBUG2(m,p1,p2)               {if (amp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_AMP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define AMP_TRACE_DEBUG3(m,p1,p2,p3)            {if (amp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_AMP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define AMP_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (amp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_AMP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define AMP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (amp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_AMP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define AMP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (amp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_AMP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the ATT/GATT unit
*/
#define GATT_TRACE_ERROR0(m)                     {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_ATT, TRACE_TYPE_ERROR, m);}
#define GATT_TRACE_ERROR1(m,p1)                  {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_ATT, TRACE_TYPE_ERROR, m,p1);}
#define GATT_TRACE_ERROR2(m,p1,p2)               {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_ATT, TRACE_TYPE_ERROR, m,p1,p2);}
#define GATT_TRACE_ERROR3(m,p1,p2,p3)            {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_ATT, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define GATT_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_ATT, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define GATT_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_ATT, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define GATT_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_ATT, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define GATT_TRACE_WARNING0(m)                   {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_ATT, TRACE_TYPE_WARNING, m);}
#define GATT_TRACE_WARNING1(m,p1)                {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_ATT, TRACE_TYPE_WARNING, m,p1);}
#define GATT_TRACE_WARNING2(m,p1,p2)             {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_ATT, TRACE_TYPE_WARNING, m,p1,p2);}
#define GATT_TRACE_WARNING3(m,p1,p2,p3)          {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_ATT, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define GATT_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_ATT, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define GATT_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_ATT, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define GATT_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_ATT, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define GATT_TRACE_API0(m)                       {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_ATT, TRACE_TYPE_API, m);}
#define GATT_TRACE_API1(m,p1)                    {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_ATT, TRACE_TYPE_API, m,p1);}
#define GATT_TRACE_API2(m,p1,p2)                 {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_ATT, TRACE_TYPE_API, m,p1,p2);}
#define GATT_TRACE_API3(m,p1,p2,p3)              {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_ATT, TRACE_TYPE_API, m,p1,p2,p3);}
#define GATT_TRACE_API4(m,p1,p2,p3,p4)           {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_ATT, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define GATT_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_ATT, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define GATT_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_ATT, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define GATT_TRACE_EVENT0(m)                     {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_ATT, TRACE_TYPE_EVENT, m);}
#define GATT_TRACE_EVENT1(m,p1)                  {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_ATT, TRACE_TYPE_EVENT, m, p1);}
#define GATT_TRACE_EVENT2(m,p1,p2)               {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_ATT, TRACE_TYPE_EVENT, m,p1,p2);}
#define GATT_TRACE_EVENT3(m,p1,p2,p3)            {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_ATT, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define GATT_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_ATT, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define GATT_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_ATT, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define GATT_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_ATT, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define GATT_TRACE_DEBUG0(m)                     {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_ATT, TRACE_TYPE_DEBUG, m);}
#define GATT_TRACE_DEBUG1(m,p1)                  {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_ATT, TRACE_TYPE_DEBUG, m,p1);}
#define GATT_TRACE_DEBUG2(m,p1,p2)               {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_ATT, TRACE_TYPE_DEBUG, m,p1,p2);}
#define GATT_TRACE_DEBUG3(m,p1,p2,p3)            {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_ATT, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define GATT_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_ATT, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define GATT_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_ATT, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define GATT_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (gatt_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_ATT, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* Define tracing for the SMP unit
*/
#define SMP_TRACE_ERROR0(m)                     {if (smp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_0(TRACE_LAYER_SMP, TRACE_TYPE_ERROR, m);}
#define SMP_TRACE_ERROR1(m,p1)                  {if (smp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_1(TRACE_LAYER_SMP, TRACE_TYPE_ERROR, m,p1);}
#define SMP_TRACE_ERROR2(m,p1,p2)               {if (smp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_2(TRACE_LAYER_SMP, TRACE_TYPE_ERROR, m,p1,p2);}
#define SMP_TRACE_ERROR3(m,p1,p2,p3)            {if (smp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_3(TRACE_LAYER_SMP, TRACE_TYPE_ERROR, m,p1,p2,p3);}
#define SMP_TRACE_ERROR4(m,p1,p2,p3,p4)         {if (smp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_4(TRACE_LAYER_SMP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4);}
#define SMP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)      {if (smp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_5(TRACE_LAYER_SMP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5);}
#define SMP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)   {if (smp_cb.trace_level >= BT_TRACE_LEVEL_ERROR) BT_TRACE_6(TRACE_LAYER_SMP, TRACE_TYPE_ERROR, m,p1,p2,p3,p4,p5,p6);}

#define SMP_TRACE_WARNING0(m)                   {if (smp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_0(TRACE_LAYER_SMP, TRACE_TYPE_WARNING, m);}
#define SMP_TRACE_WARNING1(m,p1)                {if (smp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_1(TRACE_LAYER_SMP, TRACE_TYPE_WARNING, m,p1);}
#define SMP_TRACE_WARNING2(m,p1,p2)             {if (smp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_2(TRACE_LAYER_SMP, TRACE_TYPE_WARNING, m,p1,p2);}
#define SMP_TRACE_WARNING3(m,p1,p2,p3)          {if (smp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_3(TRACE_LAYER_SMP, TRACE_TYPE_WARNING, m,p1,p2,p3);}
#define SMP_TRACE_WARNING4(m,p1,p2,p3,p4)       {if (smp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_4(TRACE_LAYER_SMP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4);}
#define SMP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)    {if (smp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_5(TRACE_LAYER_SMP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5);}
#define SMP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (smp_cb.trace_level >= BT_TRACE_LEVEL_WARNING) BT_TRACE_6(TRACE_LAYER_SMP, TRACE_TYPE_WARNING, m,p1,p2,p3,p4,p5,p6);}

#define SMP_TRACE_API0(m)                       {if (smp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_0(TRACE_LAYER_SMP, TRACE_TYPE_API, m);}
#define SMP_TRACE_API1(m,p1)                    {if (smp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_1(TRACE_LAYER_SMP, TRACE_TYPE_API, m,p1);}
#define SMP_TRACE_API2(m,p1,p2)                 {if (smp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_2(TRACE_LAYER_SMP, TRACE_TYPE_API, m,p1,p2);}
#define SMP_TRACE_API3(m,p1,p2,p3)              {if (smp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_3(TRACE_LAYER_SMP, TRACE_TYPE_API, m,p1,p2,p3);}
#define SMP_TRACE_API4(m,p1,p2,p3,p4)           {if (smp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_4(TRACE_LAYER_SMP, TRACE_TYPE_API, m,p1,p2,p3,p4);}
#define SMP_TRACE_API5(m,p1,p2,p3,p4,p5)        {if (smp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_5(TRACE_LAYER_SMP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5);}
#define SMP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)     {if (smp_cb.trace_level >= BT_TRACE_LEVEL_API) BT_TRACE_6(TRACE_LAYER_SMP, TRACE_TYPE_API, m,p1,p2,p3,p4,p5,p6);}

#define SMP_TRACE_EVENT0(m)                     {if (smp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_0(TRACE_LAYER_SMP, TRACE_TYPE_EVENT, m);}
#define SMP_TRACE_EVENT1(m,p1)                  {if (smp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_1(TRACE_LAYER_SMP, TRACE_TYPE_EVENT, m, p1);}
#define SMP_TRACE_EVENT2(m,p1,p2)               {if (smp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_2(TRACE_LAYER_SMP, TRACE_TYPE_EVENT, m,p1,p2);}
#define SMP_TRACE_EVENT3(m,p1,p2,p3)            {if (smp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_3(TRACE_LAYER_SMP, TRACE_TYPE_EVENT, m,p1,p2,p3);}
#define SMP_TRACE_EVENT4(m,p1,p2,p3,p4)         {if (smp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_4(TRACE_LAYER_SMP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4);}
#define SMP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)      {if (smp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_5(TRACE_LAYER_SMP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5);}
#define SMP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)   {if (smp_cb.trace_level >= BT_TRACE_LEVEL_EVENT) BT_TRACE_6(TRACE_LAYER_SMP, TRACE_TYPE_EVENT, m,p1,p2,p3,p4,p5,p6);}

#define SMP_TRACE_DEBUG0(m)                     {if (smp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_0(TRACE_LAYER_SMP, TRACE_TYPE_DEBUG, m);}
#define SMP_TRACE_DEBUG1(m,p1)                  {if (smp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_1(TRACE_LAYER_SMP, TRACE_TYPE_DEBUG, m,p1);}
#define SMP_TRACE_DEBUG2(m,p1,p2)               {if (smp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_2(TRACE_LAYER_SMP, TRACE_TYPE_DEBUG, m,p1,p2);}
#define SMP_TRACE_DEBUG3(m,p1,p2,p3)            {if (smp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_3(TRACE_LAYER_SMP, TRACE_TYPE_DEBUG, m,p1,p2,p3);}
#define SMP_TRACE_DEBUG4(m,p1,p2,p3,p4)         {if (smp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_4(TRACE_LAYER_SMP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4);}
#define SMP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)      {if (smp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_5(TRACE_LAYER_SMP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5);}
#define SMP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)   {if (smp_cb.trace_level >= BT_TRACE_LEVEL_DEBUG) BT_TRACE_6(TRACE_LAYER_SMP, TRACE_TYPE_DEBUG, m,p1,p2,p3,p4,p5,p6);}

/* END OF USE TRACES */
#else

#define BT_TRACE_0(l,t,m)
#define BT_TRACE_1(l,t,m,p1)
#define BT_TRACE_2(l,t,m,p1,p2)
#define BT_TRACE_3(l,t,m,p1,p2,p3)
#define BT_TRACE_4(l,t,m,p1,p2,p3,p4)
#define BT_TRACE_5(l,t,m,p1,p2,p3,p4,p5)
#define BT_TRACE_6(l,t,m,p1,p2,p3,p4,p5,p6)

#define BT_ERROR_TRACE_0(l,m)
#define BT_ERROR_TRACE_1(l,m,p1)
#define BT_ERROR_TRACE_2(l,m,p1,p2)
#define BT_ERROR_TRACE_3(l,m,p1,p2,p3)

/* Define tracing for the HCI unit
*/
#define HCI_TRACE_ERROR0(m)
#define HCI_TRACE_ERROR1(m,p1)
#define HCI_TRACE_ERROR2(m,p1,p2)
#define HCI_TRACE_ERROR3(m,p1,p2,p3)
#define HCI_TRACE_ERROR4(m,p1,p2,p3,p4)
#define HCI_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define HCI_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define HCI_TRACE_WARNING0(m)
#define HCI_TRACE_WARNING1(m,p1)
#define HCI_TRACE_WARNING2(m,p1,p2)
#define HCI_TRACE_WARNING3(m,p1,p2,p3)
#define HCI_TRACE_WARNING4(m,p1,p2,p3,p4)
#define HCI_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define HCI_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define HCI_TRACE_EVENT0(m)
#define HCI_TRACE_EVENT1(m,p1)
#define HCI_TRACE_EVENT2(m,p1,p2)
#define HCI_TRACE_EVENT3(m,p1,p2,p3)
#define HCI_TRACE_EVENT4(m,p1,p2,p3,p4)
#define HCI_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define HCI_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define HCI_TRACE_DEBUG0(m)
#define HCI_TRACE_DEBUG1(m,p1)
#define HCI_TRACE_DEBUG2(m,p1,p2)
#define HCI_TRACE_DEBUG3(m,p1,p2,p3)
#define HCI_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define HCI_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define HCI_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)


/* Define tracing for BTM
*/
#define BTM_TRACE_ERROR0(m)
#define BTM_TRACE_ERROR1(m,p1)
#define BTM_TRACE_ERROR2(m,p1,p2)
#define BTM_TRACE_ERROR3(m,p1,p2,p3)
#define BTM_TRACE_ERROR4(m,p1,p2,p3,p4)
#define BTM_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define BTM_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define BTM_TRACE_WARNING0(m)
#define BTM_TRACE_WARNING1(m,p1)
#define BTM_TRACE_WARNING2(m,p1,p2)
#define BTM_TRACE_WARNING3(m,p1,p2,p3)
#define BTM_TRACE_WARNING4(m,p1,p2,p3,p4)
#define BTM_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define BTM_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define BTM_TRACE_API0(m)
#define BTM_TRACE_API1(m,p1)
#define BTM_TRACE_API2(m,p1,p2)
#define BTM_TRACE_API3(m,p1,p2,p3)
#define BTM_TRACE_API4(m,p1,p2,p3,p4)
#define BTM_TRACE_API5(m,p1,p2,p3,p4,p5)
#define BTM_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define BTM_TRACE_EVENT0(m)
#define BTM_TRACE_EVENT1(m,p1)
#define BTM_TRACE_EVENT2(m,p1,p2)
#define BTM_TRACE_EVENT3(m,p1,p2,p3)
#define BTM_TRACE_EVENT4(m,p1,p2,p3,p4)
#define BTM_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define BTM_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define BTM_TRACE_DEBUG0(m)
#define BTM_TRACE_DEBUG1(m,p1)
#define BTM_TRACE_DEBUG2(m,p1,p2)
#define BTM_TRACE_DEBUG3(m,p1,p2,p3)
#define BTM_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define BTM_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define BTM_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)


/* Define tracing for the L2CAP unit
*/
#define L2CAP_TRACE_ERROR0(m)
#define L2CAP_TRACE_ERROR1(m,p1)
#define L2CAP_TRACE_ERROR2(m,p1,p2)
#define L2CAP_TRACE_ERROR3(m,p1,p2,p3)
#define L2CAP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define L2CAP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define L2CAP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define L2CAP_TRACE_WARNING0(m)
#define L2CAP_TRACE_WARNING1(m,p1)
#define L2CAP_TRACE_WARNING2(m,p1,p2)
#define L2CAP_TRACE_WARNING3(m,p1,p2,p3)
#define L2CAP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define L2CAP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define L2CAP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define L2CAP_TRACE_API0(m)
#define L2CAP_TRACE_API1(m,p1)
#define L2CAP_TRACE_API2(m,p1,p2)
#define L2CAP_TRACE_API3(m,p1,p2,p3)
#define L2CAP_TRACE_API4(m,p1,p2,p3,p4)
#define L2CAP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define L2CAP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define L2CAP_TRACE_EVENT0(m)
#define L2CAP_TRACE_EVENT1(m,p1)
#define L2CAP_TRACE_EVENT2(m,p1,p2)
#define L2CAP_TRACE_EVENT3(m,p1,p2,p3)
#define L2CAP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define L2CAP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define L2CAP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define L2CAP_TRACE_DEBUG0(m)
#define L2CAP_TRACE_DEBUG1(m,p1)
#define L2CAP_TRACE_DEBUG2(m,p1,p2)
#define L2CAP_TRACE_DEBUG3(m,p1,p2,p3)
#define L2CAP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define L2CAP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define L2CAP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the LLCP unit
*/
#define LLCP_TRACE_ERROR0(m)
#define LLCP_TRACE_ERROR1(m,p1)
#define LLCP_TRACE_ERROR2(m,p1,p2)
#define LLCP_TRACE_ERROR3(m,p1,p2,p3)
#define LLCP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define LLCP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define LLCP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define LLCP_TRACE_WARNING0(m)
#define LLCP_TRACE_WARNING1(m,p1)
#define LLCP_TRACE_WARNING2(m,p1,p2)
#define LLCP_TRACE_WARNING3(m,p1,p2,p3)
#define LLCP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define LLCP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define LLCP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define LLCP_TRACE_API0(m)
#define LLCP_TRACE_API1(m,p1)
#define LLCP_TRACE_API2(m,p1,p2)
#define LLCP_TRACE_API3(m,p1,p2,p3)
#define LLCP_TRACE_API4(m,p1,p2,p3,p4)
#define LLCP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define LLCP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define LLCP_TRACE_EVENT0(m)
#define LLCP_TRACE_EVENT1(m,p1)
#define LLCP_TRACE_EVENT2(m,p1,p2)
#define LLCP_TRACE_EVENT3(m,p1,p2,p3)
#define LLCP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define LLCP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define LLCP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define LLCP_TRACE_DEBUG0(m)
#define LLCP_TRACE_DEBUG1(m,p1)
#define LLCP_TRACE_DEBUG2(m,p1,p2)
#define LLCP_TRACE_DEBUG3(m,p1,p2,p3)
#define LLCP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define LLCP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define LLCP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the SDP unit
*/
#define SDP_TRACE_ERROR0(m)
#define SDP_TRACE_ERROR1(m,p1)
#define SDP_TRACE_ERROR2(m,p1,p2)
#define SDP_TRACE_ERROR3(m,p1,p2,p3)
#define SDP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define SDP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define SDP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define SDP_TRACE_WARNING0(m)
#define SDP_TRACE_WARNING1(m,p1)
#define SDP_TRACE_WARNING2(m,p1,p2)
#define SDP_TRACE_WARNING3(m,p1,p2,p3)
#define SDP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define SDP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define SDP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define SDP_TRACE_API0(m)
#define SDP_TRACE_API1(m,p1)
#define SDP_TRACE_API2(m,p1,p2)
#define SDP_TRACE_API3(m,p1,p2,p3)
#define SDP_TRACE_API4(m,p1,p2,p3,p4)
#define SDP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define SDP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define SDP_TRACE_EVENT0(m)
#define SDP_TRACE_EVENT1(m,p1)
#define SDP_TRACE_EVENT2(m,p1,p2)
#define SDP_TRACE_EVENT3(m,p1,p2,p3)
#define SDP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define SDP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define SDP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define SDP_TRACE_DEBUG0(m)
#define SDP_TRACE_DEBUG1(m,p1)
#define SDP_TRACE_DEBUG2(m,p1,p2)
#define SDP_TRACE_DEBUG3(m,p1,p2,p3)
#define SDP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define SDP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define SDP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the RFCOMM unit
*/
#define RFCOMM_TRACE_ERROR0(m)
#define RFCOMM_TRACE_ERROR1(m,p1)
#define RFCOMM_TRACE_ERROR2(m,p1,p2)
#define RFCOMM_TRACE_ERROR3(m,p1,p2,p3)
#define RFCOMM_TRACE_ERROR4(m,p1,p2,p3,p4)
#define RFCOMM_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define RFCOMM_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define RFCOMM_TRACE_WARNING0(m)
#define RFCOMM_TRACE_WARNING1(m,p1)
#define RFCOMM_TRACE_WARNING2(m,p1,p2)
#define RFCOMM_TRACE_WARNING3(m,p1,p2,p3)
#define RFCOMM_TRACE_WARNING4(m,p1,p2,p3,p4)
#define RFCOMM_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define RFCOMM_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define RFCOMM_TRACE_API0(m)
#define RFCOMM_TRACE_API1(m,p1)
#define RFCOMM_TRACE_API2(m,p1,p2)
#define RFCOMM_TRACE_API3(m,p1,p2,p3)
#define RFCOMM_TRACE_API4(m,p1,p2,p3,p4)
#define RFCOMM_TRACE_API5(m,p1,p2,p3,p4,p5)
#define RFCOMM_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define RFCOMM_TRACE_EVENT0(m)
#define RFCOMM_TRACE_EVENT1(m,p1)
#define RFCOMM_TRACE_EVENT2(m,p1,p2)
#define RFCOMM_TRACE_EVENT3(m,p1,p2,p3)
#define RFCOMM_TRACE_EVENT4(m,p1,p2,p3,p4)
#define RFCOMM_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define RFCOMM_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define RFCOMM_TRACE_DEBUG0(m)
#define RFCOMM_TRACE_DEBUG1(m,p1)
#define RFCOMM_TRACE_DEBUG2(m,p1,p2)
#define RFCOMM_TRACE_DEBUG3(m,p1,p2,p3)
#define RFCOMM_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define RFCOMM_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define RFCOMM_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for Serial Port Profile
*/
#define SPP_TRACE_ERROR0(m)
#define SPP_TRACE_ERROR1(m,p1)
#define SPP_TRACE_ERROR2(m,p1,p2)
#define SPP_TRACE_ERROR3(m,p1,p2,p3)
#define SPP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define SPP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define SPP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define SPP_TRACE_WARNING0(m)
#define SPP_TRACE_WARNING1(m,p1)
#define SPP_TRACE_WARNING2(m,p1,p2)
#define SPP_TRACE_WARNING3(m,p1,p2,p3)
#define SPP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define SPP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define SPP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define SPP_TRACE_EVENT0(m)
#define SPP_TRACE_EVENT1(m,p1)
#define SPP_TRACE_EVENT2(m,p1,p2)
#define SPP_TRACE_EVENT3(m,p1,p2,p3)
#define SPP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define SPP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define SPP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define SPP_TRACE_API0(m)
#define SPP_TRACE_API1(m,p1)
#define SPP_TRACE_API2(m,p1,p2)
#define SPP_TRACE_API3(m,p1,p2,p3)
#define SPP_TRACE_API4(m,p1,p2,p3,p4)
#define SPP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define SPP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define SPP_TRACE_DEBUG0(m)
#define SPP_TRACE_DEBUG1(m,p1)
#define SPP_TRACE_DEBUG2(m,p1,p2)
#define SPP_TRACE_DEBUG3(m,p1,p2,p3)
#define SPP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define SPP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define SPP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)


/* Generic Access Profile traces */
#define GAP_TRACE_ERROR0(m)
#define GAP_TRACE_ERROR1(m,p1)
#define GAP_TRACE_ERROR2(m,p1,p2)
#define GAP_TRACE_ERROR3(m,p1,p2,p3)
#define GAP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define GAP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define GAP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define GAP_TRACE_EVENT0(m)
#define GAP_TRACE_EVENT1(m,p1)
#define GAP_TRACE_EVENT2(m,p1,p2)
#define GAP_TRACE_EVENT3(m,p1,p2,p3)
#define GAP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define GAP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define GAP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define GAP_TRACE_API0(m)
#define GAP_TRACE_API1(m,p1)
#define GAP_TRACE_API2(m,p1,p2)
#define GAP_TRACE_API3(m,p1,p2,p3)
#define GAP_TRACE_API4(m,p1,p2,p3,p4)
#define GAP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define GAP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define GAP_TRACE_WARNING0(m)
#define GAP_TRACE_WARNING1(m,p1)
#define GAP_TRACE_WARNING2(m,p1,p2)
#define GAP_TRACE_WARNING3(m,p1,p2,p3)
#define GAP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define GAP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define GAP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)


/* Define tracing for OBX
*/
#define OBX_TRACE_ERROR0(m)
#define OBX_TRACE_ERROR1(m,p1)
#define OBX_TRACE_ERROR2(m,p1,p2)
#define OBX_TRACE_ERROR3(m,p1,p2,p3)
#define OBX_TRACE_ERROR4(m,p1,p2,p3,p4)
#define OBX_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define OBX_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define OBX_TRACE_WARNING0(m)
#define OBX_TRACE_WARNING1(m,p1)
#define OBX_TRACE_WARNING2(m,p1,p2)
#define OBX_TRACE_WARNING3(m,p1,p2,p3)
#define OBX_TRACE_WARNING4(m,p1,p2,p3,p4)
#define OBX_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define OBX_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define OBX_TRACE_EVENT0(m)
#define OBX_TRACE_EVENT1(m,p1)
#define OBX_TRACE_EVENT2(m,p1,p2)
#define OBX_TRACE_EVENT3(m,p1,p2,p3)
#define OBX_TRACE_EVENT4(m,p1,p2,p3,p4)
#define OBX_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define OBX_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define OBX_TRACE_DEBUG0(m)
#define OBX_TRACE_DEBUG1(m,p1)
#define OBX_TRACE_DEBUG2(m,p1,p2)
#define OBX_TRACE_DEBUG3(m,p1,p2,p3)
#define OBX_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define OBX_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define OBX_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define OBX_TRACE_API0(m)
#define OBX_TRACE_API1(m,p1)
#define OBX_TRACE_API2(m,p1,p2)
#define OBX_TRACE_API3(m,p1,p2,p3)
#define OBX_TRACE_API4(m,p1,p2,p3,p4)
#define OBX_TRACE_API5(m,p1,p2,p3,p4,p5)
#define OBX_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for GOEP application profiles
*/
#define GOEP_TRACE_ERROR0(m)
#define GOEP_TRACE_ERROR1(m,p1)
#define GOEP_TRACE_ERROR2(m,p1,p2)
#define GOEP_TRACE_ERROR3(m,p1,p2,p3)
#define GOEP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define GOEP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define GOEP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define GOEP_TRACE_WARNING0(m)
#define GOEP_TRACE_WARNING1(m,p1)
#define GOEP_TRACE_WARNING2(m,p1,p2)
#define GOEP_TRACE_WARNING3(m,p1,p2,p3)
#define GOEP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define GOEP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define GOEP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define GOEP_TRACE_EVENT0(m)
#define GOEP_TRACE_EVENT1(m,p1)
#define GOEP_TRACE_EVENT2(m,p1,p2)
#define GOEP_TRACE_EVENT3(m,p1,p2,p3)
#define GOEP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define GOEP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define GOEP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define GOEP_TRACE_DEBUG0(m)
#define GOEP_TRACE_DEBUG1(m,p1)
#define GOEP_TRACE_DEBUG2(m,p1,p2)
#define GOEP_TRACE_DEBUG3(m,p1,p2,p3)
#define GOEP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define GOEP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define GOEP_TRACE_API0(m)
#define GOEP_TRACE_API1(m,p1)
#define GOEP_TRACE_API2(m,p1,p2)
#define GOEP_TRACE_API3(m,p1,p2,p3)
#define GOEP_TRACE_API4(m,p1,p2,p3,p4)
#define GOEP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define GOEP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the BPP profile
*/
#define BPP_TRACE_ERROR0(m)
#define BPP_TRACE_ERROR1(m,p1)
#define BPP_TRACE_ERROR2(m,p1,p2)
#define BPP_TRACE_ERROR3(m,p1,p2,p3)
#define BPP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define BPP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define BPP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define BPP_TRACE_WARNING0(m)
#define BPP_TRACE_WARNING1(m,p1)
#define BPP_TRACE_WARNING2(m,p1,p2)
#define BPP_TRACE_WARNING3(m,p1,p2,p3)
#define BPP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define BPP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define BPP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define BPP_TRACE_EVENT0(m)
#define BPP_TRACE_EVENT1(m,p1)
#define BPP_TRACE_EVENT2(m,p1,p2)
#define BPP_TRACE_EVENT3(m,p1,p2,p3)
#define BPP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define BPP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define BPP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define BPP_TRACE_DEBUG0(m)
#define BPP_TRACE_DEBUG1(m,p1)
#define BPP_TRACE_DEBUG2(m,p1,p2)
#define BPP_TRACE_DEBUG3(m,p1,p2,p3)
#define BPP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define BPP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define BPP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define BPP_TRACE_API0(m)
#define BPP_TRACE_API1(m,p1)
#define BPP_TRACE_API2(m,p1,p2)
#define BPP_TRACE_API3(m,p1,p2,p3)
#define BPP_TRACE_API4(m,p1,p2,p3,p4)
#define BPP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define BPP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the BIP profile
*/
#define BIP_TRACE_ERROR0(m)
#define BIP_TRACE_ERROR1(m,p1)
#define BIP_TRACE_ERROR2(m,p1,p2)
#define BIP_TRACE_ERROR3(m,p1,p2,p3)
#define BIP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define BIP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define BIP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define BIP_TRACE_WARNING0(m)
#define BIP_TRACE_WARNING1(m,p1)
#define BIP_TRACE_WARNING2(m,p1,p2)
#define BIP_TRACE_WARNING3(m,p1,p2,p3)
#define BIP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define BIP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define BIP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define BIP_TRACE_EVENT0(m)
#define BIP_TRACE_EVENT1(m,p1)
#define BIP_TRACE_EVENT2(m,p1,p2)
#define BIP_TRACE_EVENT3(m,p1,p2,p3)
#define BIP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define BIP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define BIP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define BIP_TRACE_DEBUG0(m)
#define BIP_TRACE_DEBUG1(m,p1)
#define BIP_TRACE_DEBUG2(m,p1,p2)
#define BIP_TRACE_DEBUG3(m,p1,p2,p3)
#define BIP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define BIP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define BIP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define BIP_TRACE_API0(m)
#define BIP_TRACE_API1(m,p1)
#define BIP_TRACE_API2(m,p1,p2)
#define BIP_TRACE_API3(m,p1,p2,p3)
#define BIP_TRACE_API4(m,p1,p2,p3,p4)
#define BIP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define BIP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for TCS
*/
#define TCS_TRACE_ERROR0(m)
#define TCS_TRACE_ERROR1(m,p1)
#define TCS_TRACE_ERROR2(m,p1,p2)
#define TCS_TRACE_ERROR3(m,p1,p2,p3)
#define TCS_TRACE_ERROR4(m,p1,p2,p3,p4)
#define TCS_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define TCS_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define TCS_TRACE_WARNING0(m)
#define TCS_TRACE_WARNING1(m,p1)
#define TCS_TRACE_WARNING2(m,p1,p2)
#define TCS_TRACE_WARNING3(m,p1,p2,p3)
#define TCS_TRACE_WARNING4(m,p1,p2,p3,p4)
#define TCS_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define TCS_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define TCS_TRACE_EVENT0(m)
#define TCS_TRACE_EVENT1(m,p1)
#define TCS_TRACE_EVENT2(m,p1,p2)
#define TCS_TRACE_EVENT3(m,p1,p2,p3)
#define TCS_TRACE_EVENT4(m,p1,p2,p3,p4)
#define TCS_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define TCS_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define TCS_TRACE_DEBUG0(m)
#define TCS_TRACE_DEBUG1(m,p1)
#define TCS_TRACE_DEBUG2(m,p1,p2)
#define TCS_TRACE_DEBUG3(m,p1,p2,p3)
#define TCS_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define TCS_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define TCS_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define TCS_TRACE_API0(m)
#define TCS_TRACE_API1(m,p1)
#define TCS_TRACE_API2(m,p1,p2)
#define TCS_TRACE_API3(m,p1,p2,p3)
#define TCS_TRACE_API4(m,p1,p2,p3,p4)
#define TCS_TRACE_API5(m,p1,p2,p3,p4,p5)
#define TCS_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for ICP
*/
#define ICP_TRACE_ERROR0(m)
#define ICP_TRACE_ERROR1(m,p1)
#define ICP_TRACE_ERROR2(m,p1,p2)
#define ICP_TRACE_ERROR3(m,p1,p2,p3)
#define ICP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define ICP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define ICP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define ICP_TRACE_WARNING0(m)
#define ICP_TRACE_WARNING1(m,p1)
#define ICP_TRACE_WARNING2(m,p1,p2)
#define ICP_TRACE_WARNING3(m,p1,p2,p3)
#define ICP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define ICP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define ICP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define ICP_TRACE_EVENT0(m)
#define ICP_TRACE_EVENT1(m,p1)
#define ICP_TRACE_EVENT2(m,p1,p2)
#define ICP_TRACE_EVENT3(m,p1,p2,p3)
#define ICP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define ICP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define ICP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define ICP_TRACE_DEBUG0(m)
#define ICP_TRACE_DEBUG1(m,p1)
#define ICP_TRACE_DEBUG2(m,p1,p2)
#define ICP_TRACE_DEBUG3(m,p1,p2,p3)
#define ICP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define ICP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define ICP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define ICP_TRACE_API0(m)
#define ICP_TRACE_API1(m,p1)
#define ICP_TRACE_API2(m,p1,p2)
#define ICP_TRACE_API3(m,p1,p2,p3)
#define ICP_TRACE_API4(m,p1,p2,p3,p4)
#define ICP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define ICP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for CTP
*/
#define CTP_TRACE_ERROR0(m)
#define CTP_TRACE_ERROR1(m,p1)
#define CTP_TRACE_ERROR2(m,p1,p2)
#define CTP_TRACE_ERROR3(m,p1,p2,p3)
#define CTP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define CTP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define CTP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define CTP_TRACE_WARNING0(m)
#define CTP_TRACE_WARNING1(m,p1)
#define CTP_TRACE_WARNING2(m,p1,p2)
#define CTP_TRACE_WARNING3(m,p1,p2,p3)
#define CTP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define CTP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define CTP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define CTP_TRACE_EVENT0(m)
#define CTP_TRACE_EVENT1(m,p1)
#define CTP_TRACE_EVENT2(m,p1,p2)
#define CTP_TRACE_EVENT3(m,p1,p2,p3)
#define CTP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define CTP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define CTP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define CTP_TRACE_DEBUG0(m)
#define CTP_TRACE_DEBUG1(m,p1)
#define CTP_TRACE_DEBUG2(m,p1,p2)
#define CTP_TRACE_DEBUG3(m,p1,p2,p3)
#define CTP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define CTP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define CTP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define CTP_TRACE_API0(m)
#define CTP_TRACE_API1(m,p1)
#define CTP_TRACE_API2(m,p1,p2)
#define CTP_TRACE_API3(m,p1,p2,p3)
#define CTP_TRACE_API4(m,p1,p2,p3,p4)
#define CTP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define CTP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

/* define traces for headset profile */

#define HSP2_TRACE_ERROR0(pcb,m)
#define HSP2_TRACE_ERROR1(pcb,m,p1)
#define HSP2_TRACE_ERROR2(pcb,m,p1,p2)
#define HSP2_TRACE_ERROR3(pcb,m,p1,p2,p3)
#define HSP2_TRACE_ERROR4(pcb,m,p1,p2,p3,p4)
#define HSP2_TRACE_ERROR5(pcb,m,p1,p2,p3,p4,p5)
#define HSP2_TRACE_ERROR6(pcb,m,p1,p2,p3,p4,p5,p6)

#define HSP2_TRACE_WARNING0(pcb,m)
#define HSP2_TRACE_WARNING1(pcb,m,p1)
#define HSP2_TRACE_WARNING2(pcb,m,p1,p2)
#define HSP2_TRACE_WARNING3(pcb,m,p1,p2,p3)
#define HSP2_TRACE_WARNING4(pcb,m,p1,p2,p3,p4)
#define HSP2_TRACE_WARNING5(pcb,m,p1,p2,p3,p4,p5)
#define HSP2_TRACE_WARNING6(pcb,m,p1,p2,p3,p4,p5,p6)

#define HSP2_TRACE_API0(pcb,m)
#define HSP2_TRACE_API1(pcb,m,p1)
#define HSP2_TRACE_API2(pcb,m,p1,p2)
#define HSP2_TRACE_API3(pcb,m,p1,p2,p3)
#define HSP2_TRACE_API4(pcb,m,p1,p2,p3,p4)
#define HSP2_TRACE_API5(pcb,m,p1,p2,p3,p4,p5)
#define HSP2_TRACE_API6(pcb,m,p1,p2,p3,p4,p5,p6)

#define HSP2_TRACE_EVENT0(pcb,m)
#define HSP2_TRACE_EVENT1(pcb,m,p1)
#define HSP2_TRACE_EVENT2(pcb,m,p1,p2)
#define HSP2_TRACE_EVENT3(pcb,m,p1,p2,p3)
#define HSP2_TRACE_EVENT4(pcb,m,p1,p2,p3,p4)
#define HSP2_TRACE_EVENT5(pcb,m,p1,p2,p3,p4,p5)
#define HSP2_TRACE_EVENT6(pcb,m,p1,p2,p3,p4,p5,p6)

#define HSP2_TRACE_DEBUG0(pcb,m)
#define HSP2_TRACE_DEBUG1(pcb,m,p1)
#define HSP2_TRACE_DEBUG2(pcb,m,p1,p2)
#define HSP2_TRACE_DEBUG3(pcb,m,p1,p2,p3)
#define HSP2_TRACE_DEBUG4(pcb,m,p1,p2,p3,p4)
#define HSP2_TRACE_DEBUG5(pcb,m,p1,p2,p3,p4,p5)
#define HSP2_TRACE_DEBUG6(pcb,m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the NFC unit
*/
#define NFC_TRACE_ERROR0(m)
#define NFC_TRACE_ERROR1(m,p1)
#define NFC_TRACE_ERROR2(m,p1,p2)
#define NFC_TRACE_ERROR3(m,p1,p2,p3)
#define NFC_TRACE_ERROR4(m,p1,p2,p3,p4)
#define NFC_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define NFC_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define NFC_TRACE_WARNING0(m)
#define NFC_TRACE_WARNING1(m,p1)
#define NFC_TRACE_WARNING2(m,p1,p2)
#define NFC_TRACE_WARNING3(m,p1,p2,p3)
#define NFC_TRACE_WARNING4(m,p1,p2,p3,p4)
#define NFC_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define NFC_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define NFC_TRACE_API0(m)
#define NFC_TRACE_API1(m,p1)
#define NFC_TRACE_API2(m,p1,p2)
#define NFC_TRACE_API3(m,p1,p2,p3)
#define NFC_TRACE_API4(m,p1,p2,p3,p4)
#define NFC_TRACE_API5(m,p1,p2,p3,p4,p5)
#define NFC_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define NFC_TRACE_EVENT0(m)
#define NFC_TRACE_EVENT1(m,p1)
#define NFC_TRACE_EVENT2(m,p1,p2)
#define NFC_TRACE_EVENT3(m,p1,p2,p3)
#define NFC_TRACE_EVENT4(m,p1,p2,p3,p4)
#define NFC_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define NFC_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define NFC_TRACE_DEBUG0(m)
#define NFC_TRACE_DEBUG1(m,p1)
#define NFC_TRACE_DEBUG2(m,p1,p2)
#define NFC_TRACE_DEBUG3(m,p1,p2,p3)
#define NFC_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define NFC_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define NFC_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define NCI_TRACE_ERROR0(m)
#define NCI_TRACE_ERROR1(m,p1)
#define NCI_TRACE_ERROR2(m,p1,p2)
#define NCI_TRACE_ERROR3(m,p1,p2,p3)
#define NCI_TRACE_ERROR4(m,p1,p2,p3,p4)
#define NCI_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define NCI_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define NCI_TRACE_WARNING0(m)
#define NCI_TRACE_WARNING1(m,p1)
#define NCI_TRACE_WARNING2(m,p1,p2)
#define NCI_TRACE_WARNING3(m,p1,p2,p3)
#define NCI_TRACE_WARNING4(m,p1,p2,p3,p4)
#define NCI_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define NCI_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define NCI_TRACE_API0(m)
#define NCI_TRACE_API1(m,p1)
#define NCI_TRACE_API2(m,p1,p2)
#define NCI_TRACE_API3(m,p1,p2,p3)
#define NCI_TRACE_API4(m,p1,p2,p3,p4)
#define NCI_TRACE_API5(m,p1,p2,p3,p4,p5)
#define NCI_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define NCI_TRACE_EVENT0(m)
#define NCI_TRACE_EVENT1(m,p1)
#define NCI_TRACE_EVENT2(m,p1,p2)
#define NCI_TRACE_EVENT3(m,p1,p2,p3)
#define NCI_TRACE_EVENT4(m,p1,p2,p3,p4)
#define NCI_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define NCI_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define NCI_TRACE_DEBUG0(m)
#define NCI_TRACE_DEBUG1(m,p1)
#define NCI_TRACE_DEBUG2(m,p1,p2)
#define NCI_TRACE_DEBUG3(m,p1,p2,p3)
#define NCI_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define NCI_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define NCI_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define RW_TRACE_ERROR0(m)
#define RW_TRACE_ERROR1(m,p1)
#define RW_TRACE_ERROR2(m,p1,p2)
#define RW_TRACE_ERROR3(m,p1,p2,p3)
#define RW_TRACE_ERROR4(m,p1,p2,p3,p4)
#define RW_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define RW_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define RW_TRACE_WARNING0(m)
#define RW_TRACE_WARNING1(m,p1)
#define RW_TRACE_WARNING2(m,p1,p2)
#define RW_TRACE_WARNING3(m,p1,p2,p3)
#define RW_TRACE_WARNING4(m,p1,p2,p3,p4)
#define RW_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define RW_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) }

#define RW_TRACE_API0(m)
#define RW_TRACE_API1(m,p1)
#define RW_TRACE_API2(m,p1,p2)
#define RW_TRACE_API3(m,p1,p2,p3)
#define RW_TRACE_API4(m,p1,p2,p3,p4)
#define RW_TRACE_API5(m,p1,p2,p3,p4,p5)
#define RW_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define RW_TRACE_EVENT0(m)
#define RW_TRACE_EVENT1(m,p1)
#define RW_TRACE_EVENT2(m,p1,p2)
#define RW_TRACE_EVENT3(m,p1,p2,p3)
#define RW_TRACE_EVENT4(m,p1,p2,p3,p4)
#define RW_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define RW_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define RW_TRACE_DEBUG0(m)
#define RW_TRACE_DEBUG1(m,p1)
#define RW_TRACE_DEBUG2(m,p1,p2)
#define RW_TRACE_DEBUG3(m,p1,p2,p3)
#define RW_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define RW_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define RW_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define CE_TRACE_ERROR0(m)
#define CE_TRACE_ERROR1(m,p1)
#define CE_TRACE_ERROR2(m,p1,p2)
#define CE_TRACE_ERROR3(m,p1,p2,p3)
#define CE_TRACE_ERROR4(m,p1,p2,p3,p4)
#define CE_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define CE_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define CE_TRACE_WARNING0(m)
#define CE_TRACE_WARNING1(m,p1)
#define CE_TRACE_WARNING2(m,p1,p2)
#define CE_TRACE_WARNING3(m,p1,p2,p3)
#define CE_TRACE_WARNING4(m,p1,p2,p3,p4)
#define CE_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define CE_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define CE_TRACE_API0(m)
#define CE_TRACE_API1(m,p1)
#define CE_TRACE_API2(m,p1,p2)
#define CE_TRACE_API3(m,p1,p2,p3)
#define CE_TRACE_API4(m,p1,p2,p3,p4)
#define CE_TRACE_API5(m,p1,p2,p3,p4,p5)
#define CE_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define CE_TRACE_EVENT0(m)
#define CE_TRACE_EVENT1(m,p1)
#define CE_TRACE_EVENT2(m,p1,p2)
#define CE_TRACE_EVENT3(m,p1,p2,p3)
#define CE_TRACE_EVENT4(m,p1,p2,p3,p4)
#define CE_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define CE_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define CE_TRACE_DEBUG0(m)
#define CE_TRACE_DEBUG1(m,p1)
#define CE_TRACE_DEBUG2(m,p1,p2)
#define CE_TRACE_DEBUG3(m,p1,p2,p3)
#define CE_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define CE_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define CE_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define NDEF_TRACE_ERROR0(m)
#define NDEF_TRACE_ERROR1(m,p1)
#define NDEF_TRACE_ERROR2(m,p1,p2)
#define NDEF_TRACE_ERROR3(m,p1,p2,p3)
#define NDEF_TRACE_ERROR4(m,p1,p2,p3,p4)
#define NDEF_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define NDEF_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define NDEF_TRACE_WARNING0(m)
#define NDEF_TRACE_WARNING1(m,p1)
#define NDEF_TRACE_WARNING2(m,p1,p2)
#define NDEF_TRACE_WARNING3(m,p1,p2,p3)
#define NDEF_TRACE_WARNING4(m,p1,p2,p3,p4)
#define NDEF_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define NDEF_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define NDEF_TRACE_API0(m)
#define NDEF_TRACE_API1(m,p1)
#define NDEF_TRACE_API2(m,p1,p2)
#define NDEF_TRACE_API3(m,p1,p2,p3)
#define NDEF_TRACE_API4(m,p1,p2,p3,p4)
#define NDEF_TRACE_API5(m,p1,p2,p3,p4,p5)
#define NDEF_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define NDEF_TRACE_EVENT0(m)
#define NDEF_TRACE_EVENT1(m,p1)
#define NDEF_TRACE_EVENT2(m,p1,p2)
#define NDEF_TRACE_EVENT3(m,p1,p2,p3)
#define NDEF_TRACE_EVENT4(m,p1,p2,p3,p4)
#define NDEF_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define NDEF_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define NDEF_TRACE_DEBUG0(m)
#define NDEF_TRACE_DEBUG1(m,p1)
#define NDEF_TRACE_DEBUG2(m,p1,p2)
#define NDEF_TRACE_DEBUG3(m,p1,p2,p3)
#define NDEF_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define NDEF_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define NDEF_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the NFA unit
*/
#define NFA_TRACE_ERROR0(m)
#define NFA_TRACE_ERROR1(m,p1)
#define NFA_TRACE_ERROR2(m,p1,p2)
#define NFA_TRACE_ERROR3(m,p1,p2,p3)
#define NFA_TRACE_ERROR4(m,p1,p2,p3,p4)
#define NFA_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define NFA_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define NFA_TRACE_WARNING0(m)
#define NFA_TRACE_WARNING1(m,p1)
#define NFA_TRACE_WARNING2(m,p1,p2)
#define NFA_TRACE_WARNING3(m,p1,p2,p3)
#define NFA_TRACE_WARNING4(m,p1,p2,p3,p4)
#define NFA_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define NFA_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define NFA_TRACE_API0(m)
#define NFA_TRACE_API1(m,p1)
#define NFA_TRACE_API2(m,p1,p2)
#define NFA_TRACE_API3(m,p1,p2,p3)
#define NFA_TRACE_API4(m,p1,p2,p3,p4)
#define NFA_TRACE_API5(m,p1,p2,p3,p4,p5)
#define NFA_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define NFA_TRACE_EVENT0(m)
#define NFA_TRACE_EVENT1(m,p1)
#define NFA_TRACE_EVENT2(m,p1,p2)
#define NFA_TRACE_EVENT3(m,p1,p2,p3)
#define NFA_TRACE_EVENT4(m,p1,p2,p3,p4)
#define NFA_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define NFA_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define NFA_TRACE_DEBUG0(m)
#define NFA_TRACE_DEBUG1(m,p1)
#define NFA_TRACE_DEBUG2(m,p1,p2)
#define NFA_TRACE_DEBUG3(m,p1,p2,p3)
#define NFA_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define NFA_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define NFA_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)


/* define traces for HID Host */
#define HIDH_TRACE_ERROR0(m)
#define HIDH_TRACE_ERROR1(m,p1)
#define HIDH_TRACE_ERROR2(m,p1,p2)
#define HIDH_TRACE_ERROR3(m,p1,p2,p3)
#define HIDH_TRACE_ERROR4(m,p1,p2,p3,p4)
#define HIDH_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define HIDH_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define HIDH_TRACE_WARNING0(m)
#define HIDH_TRACE_WARNING1(m,p1)
#define HIDH_TRACE_WARNING2(m,p1,p2)
#define HIDH_TRACE_WARNING3(m,p1,p2,p3)
#define HIDH_TRACE_WARNING4(m,p1,p2,p3,p4)
#define HIDH_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define HIDH_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define HIDH_TRACE_API0(m)
#define HIDH_TRACE_API1(m,p1)
#define HIDH_TRACE_API2(m,p1,p2)
#define HIDH_TRACE_API3(m,p1,p2,p3)
#define HIDH_TRACE_API4(m,p1,p2,p3,p4)
#define HIDH_TRACE_API5(m,p1,p2,p3,p4,p5)
#define HIDH_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define HIDH_TRACE_EVENT0(m)
#define HIDH_TRACE_EVENT1(m,p1)
#define HIDH_TRACE_EVENT2(m,p1,p2)
#define HIDH_TRACE_EVENT3(m,p1,p2,p3)
#define HIDH_TRACE_EVENT4(m,p1,p2,p3,p4)
#define HIDH_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define HIDH_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define HIDH_TRACE_DEBUG0(m)
#define HIDH_TRACE_DEBUG1(m,p1)
#define HIDH_TRACE_DEBUG2(m,p1,p2)
#define HIDH_TRACE_DEBUG3(m,p1,p2,p3)
#define HIDH_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define HIDH_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define HIDH_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* define traces for HID Device */
#define HIDD_TRACE_ERROR0(m)
#define HIDD_TRACE_ERROR1(m,p1)
#define HIDD_TRACE_ERROR2(m,p1,p2)
#define HIDD_TRACE_ERROR3(m,p1,p2,p3)
#define HIDD_TRACE_ERROR4(m,p1,p2,p3,p4)
#define HIDD_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define HIDD_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define HIDD_TRACE_WARNING0(m)
#define HIDD_TRACE_WARNING1(m,p1)
#define HIDD_TRACE_WARNING2(m,p1,p2)
#define HIDD_TRACE_WARNING3(m,p1,p2,p3)
#define HIDD_TRACE_WARNING4(m,p1,p2,p3,p4)
#define HIDD_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define HIDD_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define HIDD_TRACE_API0(m)
#define HIDD_TRACE_API1(m,p1)
#define HIDD_TRACE_API2(m,p1,p2)
#define HIDD_TRACE_API3(m,p1,p2,p3)
#define HIDD_TRACE_API4(m,p1,p2,p3,p4)
#define HIDD_TRACE_API5(m,p1,p2,p3,p4,p5)
#define HIDD_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define HIDD_TRACE_EVENT0(m)
#define HIDD_TRACE_EVENT1(m,p1)
#define HIDD_TRACE_EVENT2(m,p1,p2)
#define HIDD_TRACE_EVENT3(m,p1,p2,p3)
#define HIDD_TRACE_EVENT4(m,p1,p2,p3,p4)
#define HIDD_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define HIDD_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define HIDD_TRACE_DEBUG0(m)
#define HIDD_TRACE_DEBUG1(m,p1)
#define HIDD_TRACE_DEBUG2(m,p1,p2)
#define HIDD_TRACE_DEBUG3(m,p1,p2,p3)
#define HIDD_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define HIDD_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define HIDD_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* define traces for DUN */

#define DUN_TRACE_ERROR0(m)
#define DUN_TRACE_ERROR1(m,p1)
#define DUN_TRACE_ERROR2(m,p1,p2)
#define DUN_TRACE_ERROR3(m,p1,p2,p3)
#define DUN_TRACE_ERROR4(m,p1,p2,p3,p4)
#define DUN_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define DUN_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define DUN_TRACE_WARNING0(m)
#define DUN_TRACE_WARNING1(m,p1)
#define DUN_TRACE_WARNING2(m,p1,p2)
#define DUN_TRACE_WARNING3(m,p1,p2,p3)
#define DUN_TRACE_WARNING4(m,p1,p2,p3,p4)
#define DUN_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define DUN_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define DUN_TRACE_API0(m)
#define DUN_TRACE_API1(m,p1)
#define DUN_TRACE_API2(m,p1,p2)
#define DUN_TRACE_API3(m,p1,p2,p3)
#define DUN_TRACE_API4(m,p1,p2,p3,p4)
#define DUN_TRACE_API5(m,p1,p2,p3,p4,p5)
#define DUN_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define DUN_TRACE_EVENT0(m)
#define DUN_TRACE_EVENT1(m,p1)
#define DUN_TRACE_EVENT2(m,p1,p2)
#define DUN_TRACE_EVENT3(m,p1,p2,p3)
#define DUN_TRACE_EVENT4(m,p1,p2,p3,p4)
#define DUN_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define DUN_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define DUN_TRACE_DEBUG0(m)
#define DUN_TRACE_DEBUG1(m,p1)
#define DUN_TRACE_DEBUG2(m,p1,p2)
#define DUN_TRACE_DEBUG3(m,p1,p2,p3)
#define DUN_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define DUN_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define DUN_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* define traces for HCRP */

#define HCRP_TRACE_ERROR0(m)
#define HCRP_TRACE_ERROR1(m,p1)
#define HCRP_TRACE_ERROR2(m,p1,p2)
#define HCRP_TRACE_ERROR3(m,p1,p2,p3)
#define HCRP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define HCRP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define HCRP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define HCRP_TRACE_WARNING0(m)
#define HCRP_TRACE_WARNING1(m,p1)
#define HCRP_TRACE_WARNING2(m,p1,p2)
#define HCRP_TRACE_WARNING3(m,p1,p2,p3)
#define HCRP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define HCRP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define HCRP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define HCRP_TRACE_API0(m)
#define HCRP_TRACE_API1(m,p1)
#define HCRP_TRACE_API2(m,p1,p2)
#define HCRP_TRACE_API3(m,p1,p2,p3)
#define HCRP_TRACE_API4(m,p1,p2,p3,p4)
#define HCRP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define HCRP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define HCRP_TRACE_EVENT0(m)
#define HCRP_TRACE_EVENT1(m,p1)
#define HCRP_TRACE_EVENT2(m,p1,p2)
#define HCRP_TRACE_EVENT3(m,p1,p2,p3)
#define HCRP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define HCRP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define HCRP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define HCRP_TRACE_DEBUG0(m)
#define HCRP_TRACE_DEBUG1(m,p1)
#define HCRP_TRACE_DEBUG2(m,p1,p2)
#define HCRP_TRACE_DEBUG3(m,p1,p2,p3)
#define HCRP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define HCRP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define HCRP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)


/* define traces for HCRP */

#define HCRPM_TRACE_ERROR0(m)
#define HCRPM_TRACE_ERROR1(m,p1)
#define HCRPM_TRACE_ERROR2(m,p1,p2)
#define HCRPM_TRACE_ERROR3(m,p1,p2,p3)
#define HCRPM_TRACE_ERROR4(m,p1,p2,p3,p4)
#define HCRPM_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define HCRPM_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define HCRPM_TRACE_WARNING0(m)
#define HCRPM_TRACE_WARNING1(m,p1)
#define HCRPM_TRACE_WARNING2(m,p1,p2)
#define HCRPM_TRACE_WARNING3(m,p1,p2,p3)
#define HCRPM_TRACE_WARNING4(m,p1,p2,p3,p4)
#define HCRPM_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define HCRPM_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define HCRPM_TRACE_API0(m)
#define HCRPM_TRACE_API1(m,p1)
#define HCRPM_TRACE_API2(m,p1,p2)
#define HCRPM_TRACE_API3(m,p1,p2,p3)
#define HCRPM_TRACE_API4(m,p1,p2,p3,p4)
#define HCRPM_TRACE_API5(m,p1,p2,p3,p4,p5)
#define HCRPM_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define HCRPM_TRACE_EVENT0(m)
#define HCRPM_TRACE_EVENT1(m,p1)
#define HCRPM_TRACE_EVENT2(m,p1,p2)
#define HCRPM_TRACE_EVENT3(m,p1,p2,p3)
#define HCRPM_TRACE_EVENT4(m,p1,p2,p3,p4)
#define HCRPM_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define HCRPM_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define HCRPM_TRACE_DEBUG0(m)
#define HCRPM_TRACE_DEBUG1(m,p1)
#define HCRPM_TRACE_DEBUG2(m,p1,p2)
#define HCRPM_TRACE_DEBUG3(m,p1,p2,p3)
#define HCRPM_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define HCRPM_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define HCRPM_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* define traces for RPC */

#define RPC_TRACE_ERROR0(m)
#define RPC_TRACE_ERROR1(m,p1)
#define RPC_TRACE_ERROR2(m,p1,p2)
#define RPC_TRACE_ERROR3(m,p1,p2,p3)
#define RPC_TRACE_ERROR4(m,p1,p2,p3,p4)
#define RPC_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define RPC_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define RPC_TRACE_WARNING0(m)
#define RPC_TRACE_WARNING1(m,p1)
#define RPC_TRACE_WARNING2(m,p1,p2)
#define RPC_TRACE_WARNING3(m,p1,p2,p3)
#define RPC_TRACE_WARNING4(m,p1,p2,p3,p4)
#define RPC_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define RPC_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define RPC_TRACE_API0(m)
#define RPC_TRACE_API1(m,p1)
#define RPC_TRACE_API2(m,p1,p2)
#define RPC_TRACE_API3(m,p1,p2,p3)
#define RPC_TRACE_API4(m,p1,p2,p3,p4)
#define RPC_TRACE_API5(m,p1,p2,p3,p4,p5)
#define RPC_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define RPC_TRACE_EVENT0(m)
#define RPC_TRACE_EVENT1(m,p1)
#define RPC_TRACE_EVENT2(m,p1,p2)
#define RPC_TRACE_EVENT3(m,p1,p2,p3)
#define RPC_TRACE_EVENT4(m,p1,p2,p3,p4)
#define RPC_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define RPC_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define RPC_TRACE_DEBUG0(m)
#define RPC_TRACE_DEBUG1(m,p1)
#define RPC_TRACE_DEBUG2(m,p1,p2)
#define RPC_TRACE_DEBUG3(m,p1,p2,p3)
#define RPC_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define RPC_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define RPC_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* define traces for BNEP */

#define BNEP_TRACE_ERROR0(m)
#define BNEP_TRACE_ERROR1(m,p1)
#define BNEP_TRACE_ERROR2(m,p1,p2)
#define BNEP_TRACE_ERROR3(m,p1,p2,p3)
#define BNEP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define BNEP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define BNEP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define BNEP_TRACE_WARNING0(m)
#define BNEP_TRACE_WARNING1(m,p1)
#define BNEP_TRACE_WARNING2(m,p1,p2)
#define BNEP_TRACE_WARNING3(m,p1,p2,p3)
#define BNEP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define BNEP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define BNEP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define BNEP_TRACE_API0(m)
#define BNEP_TRACE_API1(m,p1)
#define BNEP_TRACE_API2(m,p1,p2)
#define BNEP_TRACE_API3(m,p1,p2,p3)
#define BNEP_TRACE_API4(m,p1,p2,p3,p4)
#define BNEP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define BNEP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define BNEP_TRACE_EVENT0(m)
#define BNEP_TRACE_EVENT1(m,p1)
#define BNEP_TRACE_EVENT2(m,p1,p2)
#define BNEP_TRACE_EVENT3(m,p1,p2,p3)
#define BNEP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define BNEP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define BNEP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define BNEP_TRACE_DEBUG0(m)
#define BNEP_TRACE_DEBUG1(m,p1)
#define BNEP_TRACE_DEBUG2(m,p1,p2)
#define BNEP_TRACE_DEBUG3(m,p1,p2,p3)
#define BNEP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define BNEP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define BNEP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* hid module traces */

#define MSKB_TRACE_0(m)
#define MSKB_TRACE_1(m,p1)
#define MSKB_TRACE_2(m,p1,p2)
#define MSKB_TRACE_3(m,p1,p2,p3)
#define MSKB_TRACE_4(m,p1,p2,p3,p4)
#define MSKB_TRACE_5(m,p1,p2,p3,p4,p5)
#define MSKB_TRACE_6(m,p1,p2,p3,p4,p5,p6)

#define MSKB_DEBUG_0(m)
#define MSKB_DEBUG_1(m,p1)
#define MSKB_DEBUG_2(m,p1,p2)
#define MSKB_DEBUG_3(m,p1,p2,p3)
#define MSKB_DEBUG_4(m,p1,p2,p3,p4)
#define MSKB_DEBUG_5(m,p1,p2,p3,p4,p5)
#define MSKB_DEBUG_6(m,p1,p2,p3,p4,p5,p6)

#define MSKB_ERROR_0(m)
#define MSKB_ERROR_1(m,p1)
#define MSKB_ERROR_2(m,p1,p2)
#define MSKB_ERROR_3(m,p1,p2,p3)
#define MSKB_ERROR_4(m,p1,p2,p3,p4)
#define MSKB_ERROR_5(m,p1,p2,p3,p4,p5)
#define MSKB_ERROR_6(m,p1,p2,p3,p4,p5,p6)

/* define traces for PAN */

#define PAN_TRACE_ERROR0(m)
#define PAN_TRACE_ERROR1(m,p1)
#define PAN_TRACE_ERROR2(m,p1,p2)
#define PAN_TRACE_ERROR3(m,p1,p2,p3)
#define PAN_TRACE_ERROR4(m,p1,p2,p3,p4)
#define PAN_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define PAN_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define PAN_TRACE_WARNING0(m)
#define PAN_TRACE_WARNING1(m,p1)
#define PAN_TRACE_WARNING2(m,p1,p2)
#define PAN_TRACE_WARNING3(m,p1,p2,p3)
#define PAN_TRACE_WARNING4(m,p1,p2,p3,p4)
#define PAN_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define PAN_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define PAN_TRACE_API0(m)
#define PAN_TRACE_API1(m,p1)
#define PAN_TRACE_API2(m,p1,p2)
#define PAN_TRACE_API3(m,p1,p2,p3)
#define PAN_TRACE_API4(m,p1,p2,p3,p4)
#define PAN_TRACE_API5(m,p1,p2,p3,p4,p5)
#define PAN_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define PAN_TRACE_EVENT0(m)
#define PAN_TRACE_EVENT1(m,p1)
#define PAN_TRACE_EVENT2(m,p1,p2)
#define PAN_TRACE_EVENT3(m,p1,p2,p3)
#define PAN_TRACE_EVENT4(m,p1,p2,p3,p4)
#define PAN_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define PAN_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define PAN_TRACE_DEBUG0(m)
#define PAN_TRACE_DEBUG1(m,p1)
#define PAN_TRACE_DEBUG2(m,p1,p2)
#define PAN_TRACE_DEBUG3(m,p1,p2,p3)
#define PAN_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define PAN_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define PAN_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* define traces for SIM */

#define SAP_TRACE_ERROR0(m)
#define SAP_TRACE_ERROR1(m,p1)
#define SAP_TRACE_ERROR2(m,p1,p2)
#define SAP_TRACE_ERROR3(m,p1,p2,p3)
#define SAP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define SAP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define SAP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define SAP_TRACE_WARNING0(m)
#define SAP_TRACE_WARNING1(m,p1)
#define SAP_TRACE_WARNING2(m,p1,p2)
#define SAP_TRACE_WARNING3(m,p1,p2,p3)
#define SAP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define SAP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define SAP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define SAP_TRACE_API0(m)
#define SAP_TRACE_API1(m,p1)
#define SAP_TRACE_API2(m,p1,p2)
#define SAP_TRACE_API3(m,p1,p2,p3)
#define SAP_TRACE_API4(m,p1,p2,p3,p4)
#define SAP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define SAP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define SAP_TRACE_EVENT0(m)
#define SAP_TRACE_EVENT1(m,p1)
#define SAP_TRACE_EVENT2(m,p1,p2)
#define SAP_TRACE_EVENT3(m,p1,p2,p3)
#define SAP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define SAP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define SAP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define SAP_TRACE_DEBUG0(m)
#define SAP_TRACE_DEBUG1(m,p1)
#define SAP_TRACE_DEBUG2(m,p1,p2)
#define SAP_TRACE_DEBUG3(m,p1,p2,p3)
#define SAP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define SAP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define SAP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the OPP profile
*/
#define OPP_TRACE_ERROR0(m)
#define OPP_TRACE_ERROR1(m,p1)
#define OPP_TRACE_ERROR2(m,p1,p2)
#define OPP_TRACE_ERROR3(m,p1,p2,p3)
#define OPP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define OPP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define OPP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define OPP_TRACE_WARNING0(m)
#define OPP_TRACE_WARNING1(m,p1)
#define OPP_TRACE_WARNING2(m,p1,p2)
#define OPP_TRACE_WARNING3(m,p1,p2,p3)
#define OPP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define OPP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define OPP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define OPP_TRACE_EVENT0(m)
#define OPP_TRACE_EVENT1(m,p1)
#define OPP_TRACE_EVENT2(m,p1,p2)
#define OPP_TRACE_EVENT3(m,p1,p2,p3)
#define OPP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define OPP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define OPP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define OPP_TRACE_DEBUG0(m)
#define OPP_TRACE_DEBUG1(m,p1)
#define OPP_TRACE_DEBUG2(m,p1,p2)
#define OPP_TRACE_DEBUG3(m,p1,p2,p3)
#define OPP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define OPP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define OPP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define OPP_TRACE_API0(m)
#define OPP_TRACE_API1(m,p1)
#define OPP_TRACE_API2(m,p1,p2)
#define OPP_TRACE_API3(m,p1,p2,p3)
#define OPP_TRACE_API4(m,p1,p2,p3,p4)
#define OPP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define OPP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the FTP profile
*/
#define FTP_TRACE_ERROR0(m)
#define FTP_TRACE_ERROR1(m,p1)
#define FTP_TRACE_ERROR2(m,p1,p2)
#define FTP_TRACE_ERROR3(m,p1,p2,p3)
#define FTP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define FTP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define FTP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define FTP_TRACE_WARNING0(m)
#define FTP_TRACE_WARNING1(m,p1)
#define FTP_TRACE_WARNING2(m,p1,p2)
#define FTP_TRACE_WARNING3(m,p1,p2,p3)
#define FTP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define FTP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define FTP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define FTP_TRACE_EVENT0(m)
#define FTP_TRACE_EVENT1(m,p1)
#define FTP_TRACE_EVENT2(m,p1,p2)
#define FTP_TRACE_EVENT3(m,p1,p2,p3)
#define FTP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define FTP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define FTP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define FTP_TRACE_DEBUG0(m)
#define FTP_TRACE_DEBUG1(m,p1)
#define FTP_TRACE_DEBUG2(m,p1,p2)
#define FTP_TRACE_DEBUG3(m,p1,p2,p3)
#define FTP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define FTP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define FTP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define FTP_TRACE_API0(m)
#define FTP_TRACE_API1(m,p1)
#define FTP_TRACE_API2(m,p1,p2)
#define FTP_TRACE_API3(m,p1,p2,p3)
#define FTP_TRACE_API4(m,p1,p2,p3,p4)
#define FTP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define FTP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)


/* Define tracing for the A2DP profile
*/
#define A2D_TRACE_ERROR0(m)
#define A2D_TRACE_ERROR1(m,p1)
#define A2D_TRACE_ERROR2(m,p1,p2)
#define A2D_TRACE_ERROR3(m,p1,p2,p3)
#define A2D_TRACE_ERROR4(m,p1,p2,p3,p4)
#define A2D_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define A2D_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define A2D_TRACE_WARNING0(m)
#define A2D_TRACE_WARNING1(m,p1)
#define A2D_TRACE_WARNING2(m,p1,p2)
#define A2D_TRACE_WARNING3(m,p1,p2,p3)
#define A2D_TRACE_WARNING4(m,p1,p2,p3,p4)
#define A2D_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define A2D_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define A2D_TRACE_EVENT0(m)
#define A2D_TRACE_EVENT1(m,p1)
#define A2D_TRACE_EVENT2(m,p1,p2)
#define A2D_TRACE_EVENT3(m,p1,p2,p3)
#define A2D_TRACE_EVENT4(m,p1,p2,p3,p4)
#define A2D_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define A2D_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define A2D_TRACE_DEBUG0(m)
#define A2D_TRACE_DEBUG1(m,p1)
#define A2D_TRACE_DEBUG2(m,p1,p2)
#define A2D_TRACE_DEBUG3(m,p1,p2,p3)
#define A2D_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define A2D_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define A2D_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define A2D_TRACE_API0(m)
#define A2D_TRACE_API1(m,p1)
#define A2D_TRACE_API2(m,p1,p2)
#define A2D_TRACE_API3(m,p1,p2,p3)
#define A2D_TRACE_API4(m,p1,p2,p3,p4)
#define A2D_TRACE_API5(m,p1,p2,p3,p4,p5)
#define A2D_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the VDP profile
*/
#define VDP_TRACE_ERROR0(m)
#define VDP_TRACE_ERROR1(m,p1)
#define VDP_TRACE_ERROR2(m,p1,p2)
#define VDP_TRACE_ERROR3(m,p1,p2,p3)
#define VDP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define VDP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define VDP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define VDP_TRACE_WARNING0(m)
#define VDP_TRACE_WARNING1(m,p1)
#define VDP_TRACE_WARNING2(m,p1,p2)
#define VDP_TRACE_WARNING3(m,p1,p2,p3)
#define VDP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define VDP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define VDP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define VDP_TRACE_EVENT0(m)
#define VDP_TRACE_EVENT1(m,p1)
#define VDP_TRACE_EVENT2(m,p1,p2)
#define VDP_TRACE_EVENT3(m,p1,p2,p3)
#define VDP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define VDP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define VDP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define VDP_TRACE_DEBUG0(m)
#define VDP_TRACE_DEBUG1(m,p1)
#define VDP_TRACE_DEBUG2(m,p1,p2)
#define VDP_TRACE_DEBUG3(m,p1,p2,p3)
#define VDP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define VDP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define VDP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define VDP_TRACE_API0(m)
#define VDP_TRACE_API1(m,p1)
#define VDP_TRACE_API2(m,p1,p2)
#define VDP_TRACE_API3(m,p1,p2,p3)
#define VDP_TRACE_API4(m,p1,p2,p3,p4)
#define VDP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define VDP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)


/* Define tracing for the LM unit
*/
#define LMP_TRACE_ERROR0(m)
#define LMP_TRACE_ERROR1(m,p1)
#define LMP_TRACE_ERROR2(m,p1,p2)
#define LMP_TRACE_ERROR3(m,p1,p2,p3)
#define LMP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define LMP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define LMP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define LMP_TRACE_WARNING0(m)
#define LMP_TRACE_WARNING1(m,p1)
#define LMP_TRACE_WARNING2(m,p1,p2)
#define LMP_TRACE_WARNING3(m,p1,p2,p3)
#define LMP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define LMP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define LMP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define LMP_TRACE_EVENT0(m)
#define LMP_TRACE_EVENT1(m,p1)
#define LMP_TRACE_EVENT2(m,p1,p2)
#define LMP_TRACE_EVENT3(m,p1,p2,p3)
#define LMP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define LMP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define LMP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define LMP_TRACE_DEBUG0(m)
#define LMP_TRACE_DEBUG1(m,p1)
#define LMP_TRACE_DEBUG2(m,p1,p2)
#define LMP_TRACE_DEBUG3(m,p1,p2,p3)
#define LMP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define LMP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define LMP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the LC unit
*/
#define LC_TRACE_ERROR0(m)
#define LC_TRACE_ERROR1(m,p1)
#define LC_TRACE_ERROR2(m,p1,p2)
#define LC_TRACE_ERROR3(m,p1,p2,p3)
#define LC_TRACE_ERROR4(m,p1,p2,p3,p4)
#define LC_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define LC_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define LC_TRACE_WARNING0(m)
#define LC_TRACE_WARNING1(m,p1)
#define LC_TRACE_WARNING2(m,p1,p2)
#define LC_TRACE_WARNING3(m,p1,p2,p3)
#define LC_TRACE_WARNING4(m,p1,p2,p3,p4)
#define LC_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define LC_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define LC_TRACE_EVENT0(m)
#define LC_TRACE_EVENT1(m,p1)
#define LC_TRACE_EVENT2(m,p1,p2)
#define LC_TRACE_EVENT3(m,p1,p2,p3)
#define LC_TRACE_EVENT4(m,p1,p2,p3,p4)
#define LC_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define LC_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define LC_TRACE_DEBUG0(m)
#define LC_TRACE_DEBUG1(m,p1)
#define LC_TRACE_DEBUG2(m,p1,p2)
#define LC_TRACE_DEBUG3(m,p1,p2,p3)
#define LC_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define LC_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define LC_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define SDA_TRACE_ERROR0(m)
#define SDA_TRACE_ERROR1(m,p1)
#define SDA_TRACE_ERROR2(m,p1,p2)
#define SDA_TRACE_ERROR3(m,p1,p2,p3)
#define SDA_TRACE_ERROR4(m,p1,p2,p3,p4)
#define SDA_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define SDA_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define SDA_TRACE_WARNING0(m)
#define SDA_TRACE_WARNING1(m,p1)
#define SDA_TRACE_WARNING2(m,p1,p2)
#define SDA_TRACE_WARNING3(m,p1,p2,p3)
#define SDA_TRACE_WARNING4(m,p1,p2,p3,p4)
#define SDA_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define SDA_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define SDA_TRACE_EVENT0(m)
#define SDA_TRACE_EVENT1(m,p1)
#define SDA_TRACE_EVENT2(m,p1,p2)
#define SDA_TRACE_EVENT3(m,p1,p2,p3)
#define SDA_TRACE_EVENT4(m,p1,p2,p3,p4)
#define SDA_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define SDA_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define SDA_TRACE_DEBUG0(m)
#define SDA_TRACE_DEBUG1(m,p1)
#define SDA_TRACE_DEBUG2(m,p1,p2)
#define SDA_TRACE_DEBUG3(m,p1,p2,p3)
#define SDA_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define SDA_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define SDA_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* AVDTP
*/
#define AVDT_TRACE_ERROR0(m)
#define AVDT_TRACE_ERROR1(m,p1)
#define AVDT_TRACE_ERROR2(m,p1,p2)
#define AVDT_TRACE_ERROR3(m,p1,p2,p3)
#define AVDT_TRACE_ERROR4(m,p1,p2,p3,p4)
#define AVDT_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define AVDT_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define AVDT_TRACE_WARNING0(m)
#define AVDT_TRACE_WARNING1(m,p1)
#define AVDT_TRACE_WARNING2(m,p1,p2)
#define AVDT_TRACE_WARNING3(m,p1,p2,p3)
#define AVDT_TRACE_WARNING4(m,p1,p2,p3,p4)
#define AVDT_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define AVDT_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define AVDT_TRACE_EVENT0(m)
#define AVDT_TRACE_EVENT1(m,p1)
#define AVDT_TRACE_EVENT2(m,p1,p2)
#define AVDT_TRACE_EVENT3(m,p1,p2,p3)
#define AVDT_TRACE_EVENT4(m,p1,p2,p3,p4)
#define AVDT_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define AVDT_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define AVDT_TRACE_DEBUG0(m)
#define AVDT_TRACE_DEBUG1(m,p1)
#define AVDT_TRACE_DEBUG2(m,p1,p2)
#define AVDT_TRACE_DEBUG3(m,p1,p2,p3)
#define AVDT_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define AVDT_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define AVDT_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define AVDT_TRACE_API0(m)
#define AVDT_TRACE_API1(m,p1)
#define AVDT_TRACE_API2(m,p1,p2)
#define AVDT_TRACE_API3(m,p1,p2,p3)
#define AVDT_TRACE_API4(m,p1,p2,p3,p4)
#define AVDT_TRACE_API5(m,p1,p2,p3,p4,p5)
#define AVDT_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the AVCTP protocol
*/
#define AVCT_TRACE_ERROR0(m)
#define AVCT_TRACE_ERROR1(m,p1)
#define AVCT_TRACE_ERROR2(m,p1,p2)
#define AVCT_TRACE_ERROR3(m,p1,p2,p3)
#define AVCT_TRACE_ERROR4(m,p1,p2,p3,p4)
#define AVCT_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define AVCT_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define AVCT_TRACE_WARNING0(m)
#define AVCT_TRACE_WARNING1(m,p1)
#define AVCT_TRACE_WARNING2(m,p1,p2)
#define AVCT_TRACE_WARNING3(m,p1,p2,p3)
#define AVCT_TRACE_WARNING4(m,p1,p2,p3,p4)
#define AVCT_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define AVCT_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define AVCT_TRACE_EVENT0(m)
#define AVCT_TRACE_EVENT1(m,p1)
#define AVCT_TRACE_EVENT2(m,p1,p2)
#define AVCT_TRACE_EVENT3(m,p1,p2,p3)
#define AVCT_TRACE_EVENT4(m,p1,p2,p3,p4)
#define AVCT_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define AVCT_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define AVCT_TRACE_DEBUG0(m)
#define AVCT_TRACE_DEBUG1(m,p1)
#define AVCT_TRACE_DEBUG2(m,p1,p2)
#define AVCT_TRACE_DEBUG3(m,p1,p2,p3)
#define AVCT_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define AVCT_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define AVCT_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define AVCT_TRACE_API0(m)
#define AVCT_TRACE_API1(m,p1)
#define AVCT_TRACE_API2(m,p1,p2)
#define AVCT_TRACE_API3(m,p1,p2,p3)
#define AVCT_TRACE_API4(m,p1,p2,p3,p4)
#define AVCT_TRACE_API5(m,p1,p2,p3,p4,p5)
#define AVCT_TRACE_API6(m,p1,p2,p3,p4,p5,p6)


/* Define tracing for the AVRCP profile
*/
#define AVRC_TRACE_ERROR0(m)
#define AVRC_TRACE_ERROR1(m,p1)
#define AVRC_TRACE_ERROR2(m,p1,p2)
#define AVRC_TRACE_ERROR3(m,p1,p2,p3)
#define AVRC_TRACE_ERROR4(m,p1,p2,p3,p4)
#define AVRC_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define AVRC_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define AVRC_TRACE_WARNING0(m)
#define AVRC_TRACE_WARNING1(m,p1)
#define AVRC_TRACE_WARNING2(m,p1,p2)
#define AVRC_TRACE_WARNING3(m,p1,p2,p3)
#define AVRC_TRACE_WARNING4(m,p1,p2,p3,p4)
#define AVRC_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define AVRC_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define AVRC_TRACE_EVENT0(m)
#define AVRC_TRACE_EVENT1(m,p1)
#define AVRC_TRACE_EVENT2(m,p1,p2)
#define AVRC_TRACE_EVENT3(m,p1,p2,p3)
#define AVRC_TRACE_EVENT4(m,p1,p2,p3,p4)
#define AVRC_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define AVRC_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define AVRC_TRACE_DEBUG0(m)
#define AVRC_TRACE_DEBUG1(m,p1)
#define AVRC_TRACE_DEBUG2(m,p1,p2)
#define AVRC_TRACE_DEBUG3(m,p1,p2,p3)
#define AVRC_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define AVRC_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define AVRC_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define AVRC_TRACE_API0(m)
#define AVRC_TRACE_API1(m,p1)
#define AVRC_TRACE_API2(m,p1,p2)
#define AVRC_TRACE_API3(m,p1,p2,p3)
#define AVRC_TRACE_API4(m,p1,p2,p3,p4)
#define AVRC_TRACE_API5(m,p1,p2,p3,p4,p5)
#define AVRC_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

/* MCAP
*/
#define MCA_TRACE_ERROR0(m)
#define MCA_TRACE_ERROR1(m,p1)
#define MCA_TRACE_ERROR2(m,p1,p2)
#define MCA_TRACE_ERROR3(m,p1,p2,p3)
#define MCA_TRACE_ERROR4(m,p1,p2,p3,p4)
#define MCA_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define MCA_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define MCA_TRACE_WARNING0(m)
#define MCA_TRACE_WARNING1(m,p1)
#define MCA_TRACE_WARNING2(m,p1,p2)
#define MCA_TRACE_WARNING3(m,p1,p2,p3)
#define MCA_TRACE_WARNING4(m,p1,p2,p3,p4)
#define MCA_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define MCA_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define MCA_TRACE_EVENT0(m)
#define MCA_TRACE_EVENT1(m,p1)
#define MCA_TRACE_EVENT2(m,p1,p2)
#define MCA_TRACE_EVENT3(m,p1,p2,p3)
#define MCA_TRACE_EVENT4(m,p1,p2,p3,p4)
#define MCA_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define MCA_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define MCA_TRACE_DEBUG0(m)
#define MCA_TRACE_DEBUG1(m,p1)
#define MCA_TRACE_DEBUG2(m,p1,p2)
#define MCA_TRACE_DEBUG3(m,p1,p2,p3)
#define MCA_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define MCA_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define MCA_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#define MCA_TRACE_API0(m)
#define MCA_TRACE_API1(m,p1)
#define MCA_TRACE_API2(m,p1,p2)
#define MCA_TRACE_API3(m,p1,p2,p3)
#define MCA_TRACE_API4(m,p1,p2,p3,p4)
#define MCA_TRACE_API5(m,p1,p2,p3,p4,p5)
#define MCA_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the AMP unit
*/
#define AMP_TRACE_ERROR0(m)
#define AMP_TRACE_ERROR1(m,p1)
#define AMP_TRACE_ERROR2(m,p1,p2)
#define AMP_TRACE_ERROR3(m,p1,p2,p3)
#define AMP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define AMP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define AMP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define AMP_TRACE_WARNING0(m)
#define AMP_TRACE_WARNING1(m,p1)
#define AMP_TRACE_WARNING2(m,p1,p2)
#define AMP_TRACE_WARNING3(m,p1,p2,p3)
#define AMP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define AMP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define AMP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define AMP_TRACE_API0(m)
#define AMP_TRACE_API1(m,p1)
#define AMP_TRACE_API2(m,p1,p2)
#define AMP_TRACE_API3(m,p1,p2,p3)
#define AMP_TRACE_API4(m,p1,p2,p3,p4)
#define AMP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define AMP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define AMP_TRACE_EVENT0(m)
#define AMP_TRACE_EVENT1(m,p1)
#define AMP_TRACE_EVENT2(m,p1,p2)
#define AMP_TRACE_EVENT3(m,p1,p2,p3)
#define AMP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define AMP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define AMP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define AMP_TRACE_DEBUG0(m)
#define AMP_TRACE_DEBUG1(m,p1)
#define AMP_TRACE_DEBUG2(m,p1,p2)
#define AMP_TRACE_DEBUG3(m,p1,p2,p3)
#define AMP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define AMP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define AMP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the GATT
*/
#define GATT_TRACE_ERROR0(m)
#define GATT_TRACE_ERROR1(m,p1)
#define GATT_TRACE_ERROR2(m,p1,p2)
#define GATT_TRACE_ERROR3(m,p1,p2,p3)
#define GATT_TRACE_ERROR4(m,p1,p2,p3,p4)
#define GATT_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define GATT_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define GATT_TRACE_WARNING0(m)
#define GATT_TRACE_WARNING1(m,p1)
#define GATT_TRACE_WARNING2(m,p1,p2)
#define GATT_TRACE_WARNING3(m,p1,p2,p3)
#define GATT_TRACE_WARNING4(m,p1,p2,p3,p4)
#define GATT_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define GATT_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define GATT_TRACE_API0(m)
#define GATT_TRACE_API1(m,p1)
#define GATT_TRACE_API2(m,p1,p2)
#define GATT_TRACE_API3(m,p1,p2,p3)
#define GATT_TRACE_API4(m,p1,p2,p3,p4)
#define GATT_TRACE_API5(m,p1,p2,p3,p4,p5)
#define GATT_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define GATT_TRACE_EVENT0(m)
#define GATT_TRACE_EVENT1(m,p1)
#define GATT_TRACE_EVENT2(m,p1,p2)
#define GATT_TRACE_EVENT3(m,p1,p2,p3)
#define GATT_TRACE_EVENT4(m,p1,p2,p3,p4)
#define GATT_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define GATT_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define GATT_TRACE_DEBUG0(m)
#define GATT_TRACE_DEBUG1(m,p1)
#define GATT_TRACE_DEBUG2(m,p1,p2)
#define GATT_TRACE_DEBUG3(m,p1,p2,p3)
#define GATT_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define GATT_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define GATT_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

/* Define tracing for the SMP unit
*/
#define SMP_TRACE_ERROR0(m)
#define SMP_TRACE_ERROR1(m,p1)
#define SMP_TRACE_ERROR2(m,p1,p2)
#define SMP_TRACE_ERROR3(m,p1,p2,p3)
#define SMP_TRACE_ERROR4(m,p1,p2,p3,p4)
#define SMP_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define SMP_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define SMP_TRACE_WARNING0(m)
#define SMP_TRACE_WARNING1(m,p1)
#define SMP_TRACE_WARNING2(m,p1,p2)
#define SMP_TRACE_WARNING3(m,p1,p2,p3)
#define SMP_TRACE_WARNING4(m,p1,p2,p3,p4)
#define SMP_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define SMP_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define SMP_TRACE_API0(m)
#define SMP_TRACE_API1(m,p1)
#define SMP_TRACE_API2(m,p1,p2)
#define SMP_TRACE_API3(m,p1,p2,p3)
#define SMP_TRACE_API4(m,p1,p2,p3,p4)
#define SMP_TRACE_API5(m,p1,p2,p3,p4,p5)
#define SMP_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define SMP_TRACE_EVENT0(m)
#define SMP_TRACE_EVENT1(m,p1)
#define SMP_TRACE_EVENT2(m,p1,p2)
#define SMP_TRACE_EVENT3(m,p1,p2,p3)
#define SMP_TRACE_EVENT4(m,p1,p2,p3,p4)
#define SMP_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define SMP_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define SMP_TRACE_DEBUG0(m)
#define SMP_TRACE_DEBUG1(m,p1)
#define SMP_TRACE_DEBUG2(m,p1,p2)
#define SMP_TRACE_DEBUG3(m,p1,p2,p3)
#define SMP_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define SMP_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define SMP_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#endif

#if (BT_TRACE_BTIF == TRUE)

extern UINT8 btif_trace_level;

/* define traces for application */
#define BTIF_TRACE_ERROR0(m)                    {if (btif_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_ERROR, (m));}
#define BTIF_TRACE_ERROR1(m,p1)                 {if (btif_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1));}
#define BTIF_TRACE_ERROR2(m,p1,p2)              {if (btif_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define BTIF_TRACE_ERROR3(m,p1,p2,p3)           {if (btif_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define BTIF_TRACE_ERROR4(m,p1,p2,p3,p4)        {if (btif_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define BTIF_TRACE_ERROR5(m,p1,p2,p3,p4,p5)     {if (btif_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define BTIF_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)  {if (btif_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

#define BTIF_TRACE_WARNING0(m)                  {if (btif_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_WARNING, (m));}
#define BTIF_TRACE_WARNING1(m,p1)               {if (btif_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1));}
#define BTIF_TRACE_WARNING2(m,p1,p2)            {if (btif_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define BTIF_TRACE_WARNING3(m,p1,p2,p3)         {if (btif_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define BTIF_TRACE_WARNING4(m,p1,p2,p3,p4)      {if (btif_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define BTIF_TRACE_WARNING5(m,p1,p2,p3,p4,p5)   {if (btif_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define BTIF_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (btif_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

#define BTIF_TRACE_API0(m)                      {if (btif_trace_level >= BT_TRACE_LEVEL_API) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_API, (m));}
#define BTIF_TRACE_API1(m,p1)                   {if (btif_trace_level >= BT_TRACE_LEVEL_API) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1));}
#define BTIF_TRACE_API2(m,p1,p2)                {if (btif_trace_level >= BT_TRACE_LEVEL_API) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define BTIF_TRACE_API3(m,p1,p2,p3)             {if (btif_trace_level >= BT_TRACE_LEVEL_API) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define BTIF_TRACE_API4(m,p1,p2,p3,p4)          {if (btif_trace_level >= BT_TRACE_LEVEL_API) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define BTIF_TRACE_API5(m,p1,p2,p3,p4,p5)       {if (btif_trace_level >= BT_TRACE_LEVEL_API) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define BTIF_TRACE_API6(m,p1,p2,p3,p4,p5,p6)    {if (btif_trace_level >= BT_TRACE_LEVEL_API) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

#define BTIF_TRACE_EVENT0(m)                    {if (btif_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_EVENT, (m));}
#define BTIF_TRACE_EVENT1(m,p1)                 {if (btif_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1));}
#define BTIF_TRACE_EVENT2(m,p1,p2)              {if (btif_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define BTIF_TRACE_EVENT3(m,p1,p2,p3)           {if (btif_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define BTIF_TRACE_EVENT4(m,p1,p2,p3,p4)        {if (btif_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define BTIF_TRACE_EVENT5(m,p1,p2,p3,p4,p5)     {if (btif_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define BTIF_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)  {if (btif_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

#define BTIF_TRACE_DEBUG0(m)                    {if (btif_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, (m));}
#define BTIF_TRACE_DEBUG1(m,p1)                 {if (btif_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1));}
#define BTIF_TRACE_DEBUG2(m,p1,p2)              {if (btif_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define BTIF_TRACE_DEBUG3(m,p1,p2,p3)           {if (btif_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define BTIF_TRACE_DEBUG4(m,p1,p2,p3,p4)        {if (btif_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define BTIF_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)     {if (btif_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define BTIF_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)  {if (btif_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

#define BTIF_TRACE_VERBOSE0(m)                    {if (btif_trace_level >= BT_TRACE_LEVEL_VERBOSE) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, (m));}
#define BTIF_TRACE_VERBOSE1(m,p1)                 {if (btif_trace_level >= BT_TRACE_LEVEL_VERBOSE) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1));}
#define BTIF_TRACE_VERBOSE2(m,p1,p2)              {if (btif_trace_level >= BT_TRACE_LEVEL_VERBOSE) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define BTIF_TRACE_VERBOSE3(m,p1,p2,p3)           {if (btif_trace_level >= BT_TRACE_LEVEL_VERBOSE) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define BTIF_TRACE_VERBOSE4(m,p1,p2,p3,p4)        {if (btif_trace_level >= BT_TRACE_LEVEL_VERBOSE) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define BTIF_TRACE_VERBOSE5(m,p1,p2,p3,p4,p5)     {if (btif_trace_level >= BT_TRACE_LEVEL_VERBOSE) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define BTIF_TRACE_VERBOSE6(m,p1,p2,p3,p4,p5,p6)  {if (btif_trace_level >= BT_TRACE_LEVEL_VERBOSE) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

#else
/* define traces for Application */

#define BTIF_TRACE_ERROR0(m)
#define BTIF_TRACE_ERROR1(m,p1)
#define BTIF_TRACE_ERROR2(m,p1,p2)
#define BTIF_TRACE_ERROR3(m,p1,p2,p3)
#define BTIF_TRACE_ERROR4(m,p1,p2,p3,p4)
#define BTIF_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define BTIF_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)
#define BTIF_TRACE_ERROR7(m,p1,p2,p3,p4,p5,p6,p7)


#define BTIF_TRACE_WARNING0(m)
#define BTIF_TRACE_WARNING1(m,p1)
#define BTIF_TRACE_WARNING2(m,p1,p2)
#define BTIF_TRACE_WARNING3(m,p1,p2,p3)
#define BTIF_TRACE_WARNING4(m,p1,p2,p3,p4)
#define BTIF_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define BTIF_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)
#define BTIF_TRACE_WARNING7(m,p1,p2,p3,p4,p5,p6,p7)


#define BTIF_TRACE_API0(m)
#define BTIF_TRACE_API1(m,p1)
#define BTIF_TRACE_API2(m,p1,p2)
#define BTIF_TRACE_API3(m,p1,p2,p3)
#define BTIF_TRACE_API4(m,p1,p2,p3,p4)
#define BTIF_TRACE_API5(m,p1,p2,p3,p4,p5)
#define BTIF_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define BTIF_TRACE_EVENT0(m)
#define BTIF_TRACE_EVENT1(m,p1)
#define BTIF_TRACE_EVENT2(m,p1,p2)
#define BTIF_TRACE_EVENT3(m,p1,p2,p3)
#define BTIF_TRACE_EVENT4(m,p1,p2,p3,p4)
#define BTIF_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define BTIF_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define BTIF_TRACE_DEBUG0(m)
#define BTIF_TRACE_DEBUG1(m,p1)
#define BTIF_TRACE_DEBUG2(m,p1,p2)
#define BTIF_TRACE_DEBUG3(m,p1,p2,p3)
#define BTIF_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define BTIF_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define BTIF_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)
#define BTIF_TRACE_DEBUG7(m,p1,p2,p3,p4,p5,p6,p7)
#define BTIF_TRACE_DEBUG8(m,p1,p2,p3,p4,p5,p6,p7,p8)




#define BTIF_TRACE_VERBOSE0(m)
#define BTIF_TRACE_VERBOSE1(m,p1)
#define BTIF_TRACE_VERBOSE2(m,p1,p2)
#define BTIF_TRACE_VERBOSE3(m,p1,p2,p3)
#define BTIF_TRACE_VERBOSE4(m,p1,p2,p3,p4)
#define BTIF_TRACE_VERBOSE5(m,p1,p2,p3,p4,p5)
#define BTIF_TRACE_VERBOSE6(m,p1,p2,p3,p4,p5,p6)

#endif


#if (BT_USE_TRACES == TRUE || BT_TRACE_APPL == TRUE)

/* define traces for application */
#define APPL_TRACE_ERROR0(m)                    {if (appl_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_ERROR, (m));}
#define APPL_TRACE_ERROR1(m,p1)                 {if (appl_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1));}
#define APPL_TRACE_ERROR2(m,p1,p2)              {if (appl_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define APPL_TRACE_ERROR3(m,p1,p2,p3)           {if (appl_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define APPL_TRACE_ERROR4(m,p1,p2,p3,p4)        {if (appl_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define APPL_TRACE_ERROR5(m,p1,p2,p3,p4,p5)     {if (appl_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define APPL_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)  {if (appl_trace_level >= BT_TRACE_LEVEL_ERROR) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_ERROR, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

#define APPL_TRACE_WARNING0(m)                  {if (appl_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_WARNING, (m));}
#define APPL_TRACE_WARNING1(m,p1)               {if (appl_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1));}
#define APPL_TRACE_WARNING2(m,p1,p2)            {if (appl_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define APPL_TRACE_WARNING3(m,p1,p2,p3)         {if (appl_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define APPL_TRACE_WARNING4(m,p1,p2,p3,p4)      {if (appl_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define APPL_TRACE_WARNING5(m,p1,p2,p3,p4,p5)   {if (appl_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define APPL_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6) {if (appl_trace_level >= BT_TRACE_LEVEL_WARNING) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_WARNING, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

#define APPL_TRACE_API0(m)                      {if (appl_trace_level >= BT_TRACE_LEVEL_API) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_API, (m));}
#define APPL_TRACE_API1(m,p1)                   {if (appl_trace_level >= BT_TRACE_LEVEL_API) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1));}
#define APPL_TRACE_API2(m,p1,p2)                {if (appl_trace_level >= BT_TRACE_LEVEL_API) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define APPL_TRACE_API3(m,p1,p2,p3)             {if (appl_trace_level >= BT_TRACE_LEVEL_API) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define APPL_TRACE_API4(m,p1,p2,p3,p4)          {if (appl_trace_level >= BT_TRACE_LEVEL_API) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define APPL_TRACE_API5(m,p1,p2,p3,p4,p5)       {if (appl_trace_level >= BT_TRACE_LEVEL_API) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define APPL_TRACE_API6(m,p1,p2,p3,p4,p5,p6)    {if (appl_trace_level >= BT_TRACE_LEVEL_API) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_API, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

#define APPL_TRACE_EVENT0(m)                    {if (appl_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_EVENT, (m));}
#define APPL_TRACE_EVENT1(m,p1)                 {if (appl_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1));}
#define APPL_TRACE_EVENT2(m,p1,p2)              {if (appl_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define APPL_TRACE_EVENT3(m,p1,p2,p3)           {if (appl_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define APPL_TRACE_EVENT4(m,p1,p2,p3,p4)        {if (appl_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define APPL_TRACE_EVENT5(m,p1,p2,p3,p4,p5)     {if (appl_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define APPL_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)  {if (appl_trace_level >= BT_TRACE_LEVEL_EVENT) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_EVENT, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}

#define APPL_TRACE_DEBUG0(m)                    {if (appl_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_0(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, (m));}
#define APPL_TRACE_DEBUG1(m,p1)                 {if (appl_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_1(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1));}
#define APPL_TRACE_DEBUG2(m,p1,p2)              {if (appl_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_2(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2));}
#define APPL_TRACE_DEBUG3(m,p1,p2,p3)           {if (appl_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_3(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3));}
#define APPL_TRACE_DEBUG4(m,p1,p2,p3,p4)        {if (appl_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_4(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4));}
#define APPL_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)     {if (appl_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_5(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5));}
#define APPL_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)  {if (appl_trace_level >= BT_TRACE_LEVEL_DEBUG) LogMsg_6(TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | TRACE_TYPE_DEBUG, \
                                                        (m), (UINT32)(p1), (UINT32)(p2), (UINT32)(p3), (UINT32)(p4), (UINT32)(p5), (UINT32)(p6));}
#else
/* define traces for Application */

#define APPL_TRACE_ERROR0(m)
#define APPL_TRACE_ERROR1(m,p1)
#define APPL_TRACE_ERROR2(m,p1,p2)
#define APPL_TRACE_ERROR3(m,p1,p2,p3)
#define APPL_TRACE_ERROR4(m,p1,p2,p3,p4)
#define APPL_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define APPL_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

#define APPL_TRACE_WARNING0(m)
#define APPL_TRACE_WARNING1(m,p1)
#define APPL_TRACE_WARNING2(m,p1,p2)
#define APPL_TRACE_WARNING3(m,p1,p2,p3)
#define APPL_TRACE_WARNING4(m,p1,p2,p3,p4)
#define APPL_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define APPL_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)

#define APPL_TRACE_API0(m)
#define APPL_TRACE_API1(m,p1)
#define APPL_TRACE_API2(m,p1,p2)
#define APPL_TRACE_API3(m,p1,p2,p3)
#define APPL_TRACE_API4(m,p1,p2,p3,p4)
#define APPL_TRACE_API5(m,p1,p2,p3,p4,p5)
#define APPL_TRACE_API6(m,p1,p2,p3,p4,p5,p6)

#define APPL_TRACE_EVENT0(m)
#define APPL_TRACE_EVENT1(m,p1)
#define APPL_TRACE_EVENT2(m,p1,p2)
#define APPL_TRACE_EVENT3(m,p1,p2,p3)
#define APPL_TRACE_EVENT4(m,p1,p2,p3,p4)
#define APPL_TRACE_EVENT5(m,p1,p2,p3,p4,p5)
#define APPL_TRACE_EVENT6(m,p1,p2,p3,p4,p5,p6)

#define APPL_TRACE_DEBUG0(m)
#define APPL_TRACE_DEBUG1(m,p1)
#define APPL_TRACE_DEBUG2(m,p1,p2)
#define APPL_TRACE_DEBUG3(m,p1,p2,p3)
#define APPL_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define APPL_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define APPL_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)

#endif

#if ((MMI_INCLUDED == TRUE) && (!defined(HID_MSKB_INCLUDED) || (HID_MSKB_INCLUDED == FALSE)))
/* UI for sample applications */
#define SAP_TRACE_0(m)                            MMI_Echo(m)
#define SAP_TRACE_1(m,p1)                         MMI_Echo(m,p1)
#define SAP_TRACE_2(m,p1,p2)                      MMI_Echo(m,p1,p2)
#define SAP_TRACE_3(m,p1,p2,p3)                   MMI_Echo(m,p1,p2,p3)
#define SAP_TRACE_4(m,p1,p2,p3,p4)                MMI_Echo(m,p1,p2,p3,p4)
#define SAP_TRACE_5(m,p1,p2,p3,p4,p5)             MMI_Echo(m,p1,p2,p3,p4,p5)
#define SAP_TRACE_6(m,p1,p2,p3,p4,p5,p6)          MMI_Echo(m,p1,p2,p3,p4,p5,p6)
#else
#define SAP_TRACE_0(m)
#define SAP_TRACE_1(m,p1)
#define SAP_TRACE_2(m,p1,p2)
#define SAP_TRACE_3(m,p1,p2,p3)
#define SAP_TRACE_4(m,p1,p2,p3,p4)
#define SAP_TRACE_5(m,p1,p2,p3,p4,p5)
#define SAP_TRACE_6(m,p1,p2,p3,p4,p5,p6)

#endif  /* End of MMI_INCLUDED */
#if defined(DRV_DEBUG_MSG) && (DRV_DEBUG_MSG == TRUE)
/* Driver Trace macros
*/
#define DRV_TRACE_WARNING0(m)                      APPL_TRACE_WARNING0(m)
#define DRV_TRACE_WARNING1(m,p1)                   APPL_TRACE_WARNING1(m,p1)
#define DRV_TRACE_WARNING2(m,p1,p2)                APPL_TRACE_WARNING2(m,p1,p2)
#define DRV_TRACE_WARNING3(m,p1,p2,p3)             APPL_TRACE_WARNING3(m,p1,p2,p3)
#define DRV_TRACE_WARNING4(m,p1,p2,p3,p4)          APPL_TRACE_WARNING4(m,p1,p2,p3,p4)
#define DRV_TRACE_WARNING5(m,p1,p2,p3,p4,p5)       APPL_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define DRV_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)    APPL_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)
#else
/* Driver Trace macros
*/
#define DRV_TRACE_WARNING0(m)
#define DRV_TRACE_WARNING1(m,p1)
#define DRV_TRACE_WARNING2(m,p1,p2)
#define DRV_TRACE_WARNING3(m,p1,p2,p3)
#define DRV_TRACE_WARNING4(m,p1,p2,p3,p4)
#define DRV_TRACE_WARNING5(m,p1,p2,p3,p4,p5)
#define DRV_TRACE_WARNING6(m,p1,p2,p3,p4,p5,p6)
#endif

#define DRV_TRACE_ERROR0(m)                      APPL_TRACE_ERROR0(m)
#define DRV_TRACE_ERROR1(m,p1)                   APPL_TRACE_ERROR1(m,p1)
#define DRV_TRACE_ERROR2(m,p1,p2)                APPL_TRACE_ERROR2(m,p1,p2)
#define DRV_TRACE_ERROR3(m,p1,p2,p3)             APPL_TRACE_ERROR3(m,p1,p2,p3)
#define DRV_TRACE_ERROR4(m,p1,p2,p3,p4)          APPL_TRACE_ERROR4(m,p1,p2,p3,p4)
#define DRV_TRACE_ERROR5(m,p1,p2,p3,p4,p5)       APPL_TRACE_ERROR5(m,p1,p2,p3,p4,p5)
#define DRV_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)    APPL_TRACE_ERROR6(m,p1,p2,p3,p4,p5,p6)

/* Driver Trace macros
*/
#define DRV_TRACE_DEBUG0(m)                    APPL_TRACE_DEBUG0(m)
#define DRV_TRACE_DEBUG1(m,p1)                 APPL_TRACE_DEBUG1(m,p1)
#define DRV_TRACE_DEBUG2(m,p1,p2)              APPL_TRACE_DEBUG2(m,p1,p2)
#define DRV_TRACE_DEBUG3(m,p1,p2,p3)           APPL_TRACE_DEBUG3(m,p1,p2,p3)
#define DRV_TRACE_DEBUG4(m,p1,p2,p3,p4)        APPL_TRACE_DEBUG4(m,p1,p2,p3,p4)
#define DRV_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)     APPL_TRACE_DEBUG5(m,p1,p2,p3,p4,p5)
#define DRV_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)  APPL_TRACE_DEBUG6(m,p1,p2,p3,p4,p5,p6)


#endif /* BT_TRACE_H */


