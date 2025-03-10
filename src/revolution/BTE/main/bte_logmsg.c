/******************************************************************************
 *
 *  NOTICE OF CHANGES
 *  2024/03/25:
 *      - Remove linux functionality for RVL target
 *      - Include necessary files for trace functions
 *      - Modify LogMsg_* family of functions to match RVL target
 *      - Supply LogMsg definition for RVL
 * 
 *  Compile with REVOLUTION defined to include these changes.
 * 
 ******************************************************************************/



/******************************************************************************
 *
 *  Copyright (C) 2001-2012 Broadcom Corporation
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
 *  Contains the LogMsg wrapper routines for BTE.  It routes calls the
 *  appropriate application's LogMsg equivalent.
 *
 ******************************************************************************/

#ifdef REVOLUTION
#include <revolution/OS.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "gki.h"
#include "bte.h"

#include "bte_appl.h"

#if MMI_INCLUDED == TRUE
#include "mmi.h"
#endif

/* always enable trace framework */

#include "btu.h"
#include "l2c_api.h"
#if (RFCOMM_INCLUDED==TRUE)
#include "port_api.h"
#endif
#if (OBX_INCLUDED==TRUE)
#include "obx_api.h"
#endif
#if (AVCT_INCLUDED==TRUE)
#include "avct_api.h"
#endif
#if (AVDT_INCLUDED==TRUE)
#include "avdt_api.h"
#endif
#if (AVRC_INCLUDED==TRUE)
#include "avrc_api.h"
#endif
#if (AVDT_INCLUDED==TRUE)
#include "avdt_api.h"
#endif
#if (A2D_INCLUDED==TRUE)
#include "a2d_api.h"
#endif
#if (BIP_INCLUDED==TRUE)
#include "bip_api.h"
#endif
#if (BNEP_INCLUDED==TRUE)
#include "bnep_api.h"
#endif
#if (BPP_INCLUDED==TRUE)
#include "bpp_api.h"
#endif
#include "btm_api.h"
#if (DUN_INCLUDED==TRUE)
#include "dun_api.h"
#endif
#if (GAP_INCLUDED==TRUE)
#include "gap_api.h"
#endif
#if (GOEP_INCLUDED==TRUE)
#include "goep_util.h"
#endif
#if (HCRP_INCLUDED==TRUE)
#include "hcrp_api.h"
#endif
#if (PAN_INCLUDED==TRUE)
#include "pan_api.h"
#endif
#include "sdp_api.h"

#if (BLE_INCLUDED==TRUE)
#include "gatt_api.h"
#endif

    /* LayerIDs for BTA, currently everything maps onto appl_trace_level */
#if (BTA_INCLUDED==TRUE)
#include "bta_api.h"
#endif


#if defined(__CYGWIN__) || defined(__linux__)
#undef RPC_INCLUDED
#define RPC_INCLUDED TRUE

#include <sys/time.h>
#include <time.h>

#if (defined(ANDROID_USE_LOGCAT) && (ANDROID_USE_LOGCAT==TRUE))
const char * const bt_layer_tags[] = {
    "bt-btif",
    "bt-usb",
    "bt-serial",
    "bt-socket",
    "bt-rs232",
    "bt-lc",
    "bt-lm",
    "bt-hci",
    "bt-l2cap",
    "bt-rfcomm",
    "bt-sdp",
    "bt-tcs",
    "bt-obex",
    "bt-btm",
    "bt-gap",
    "bt-dun",
    "bt-goep",
    "bt-icp",
    "bt-hsp2",
    "bt-spp",
    "bt-ctp",
    "bt-bpp",
    "bt-hcrp",
    "bt-ftp",
    "bt-opp",
    "bt-btu",
    "bt-gki",
    "bt-bnep",
    "bt-pan",
    "bt-hfp",
    "bt-hid",
    "bt-bip",
    "bt-avp",
    "bt-a2d",
    "bt-sap",
    "bt-amp",
    "bt-mca",
    "bt-att",
    "bt-smp",
    "bt-nfc",
    "bt-nci",
    "bt-idep",
    "bt-ndep",
    "bt-llcp",
    "bt-rw",
    "bt-ce",
    "bt-snep",
    "bt-ndef",
    "bt-nfa",
};

#ifndef LINUX_NATIVE
#include <cutils/log.h>
#define LOGI0(t,s) __android_log_write(ANDROID_LOG_INFO, t, s)
#define LOGD0(t,s) __android_log_write(ANDROID_LOG_DEBUG, t, s)
#define LOGW0(t,s) __android_log_write(ANDROID_LOG_WARN, t, s)
#define LOGE0(t,s) __android_log_write(ANDROID_LOG_ERROR, t, s)

#else
#undef ANDROID_USE_LOGCAT
#endif

#endif


//#include "btl_cfg.h"
#define BTL_GLOBAL_PROP_TRC_FLAG "TRC_BTAPP"
#ifndef DEFAULT_CONF_TRACE_LEVEL
#define DEFAULT_CONF_TRACE_LEVEL BT_TRACE_LEVEL_WARNING
#endif

#ifndef BTE_LOG_BUF_SIZE
#define BTE_LOG_BUF_SIZE  1024
#endif
#define BTE_LOG_MAX_SIZE  (BTE_LOG_BUF_SIZE - 12)


//#define BTE_MAP_TRACE_LEVEL FALSE
/* map by default BTE trace levels onto android trace levels */
#ifndef BTE_MAP_TRACE_LEVEL
#define BTE_MAP_TRACE_LEVEL TRUE
#endif

// #define BTE_ANDROID_INTERNAL_TIMESTAMP TRUE
/* by default no internal timestamp. adb logcate -v time allows having timestamps */
#ifndef BTE_ANDROID_INTERNAL_TIMESTAMP
#define BTE_ANDROID_INTERNAL_TIMESTAMP FALSE
#endif
#if (BTE_ANDROID_INTERNAL_TIMESTAMP==TRUE)
#define MSG_BUFFER_OFFSET strlen(buffer)
#else
#define MSG_BUFFER_OFFSET 0
#endif

//#define DBG_TRACE

#if defined( DBG_TRACE )
#define DBG_TRACE_API0( m ) BT_TRACE_0( TRACE_LAYER_HCI, TRACE_TYPE_API, m )
#define DBG_TRACE_WARNING2( m, p0, p1 ) BT_TRACE_2( TRACE_LAYER_BTM, (TRACE_ORG_APPL|TRACE_TYPE_WARNING), m, p0, p1 )
#else
#define DBG_TRACE_API0( m )
#define DBG_TRACE_WARNING2( m, p0, p1 )
#endif
#define DBG_TRACE_DEBUG2( m, p0, p1 ) BT_TRACE_2( TRACE_LAYER_BTM, (TRACE_ORG_APPL|TRACE_TYPE_DEBUG), m, p0, p1 )

void
LogMsg(UINT32 trace_set_mask, const char *fmt_str, ...)
{
	static char buffer[BTE_LOG_BUF_SIZE];
    int trace_layer = TRACE_GET_LAYER(trace_set_mask);
    if (trace_layer >= TRACE_LAYER_MAX_NUM)
        trace_layer = 0;

	va_list ap;
#if (BTE_ANDROID_INTERNAL_TIMESTAMP==TRUE)
	struct timeval tv;
	struct timezone tz;
	struct tm *tm;
	time_t t;

	gettimeofday(&tv, &tz);
	time(&t);
	tm = localtime(&t);

    sprintf(buffer, "%02d:%02d:%02d.%03d ", tm->tm_hour, tm->tm_min, tm->tm_sec,
        tv.tv_usec / 1000);
#endif
	va_start(ap, fmt_str);
	vsnprintf(&buffer[MSG_BUFFER_OFFSET], BTE_LOG_MAX_SIZE, fmt_str, ap);
	va_end(ap);

#if (defined(ANDROID_USE_LOGCAT) && (ANDROID_USE_LOGCAT==TRUE))
#if (BTE_MAP_TRACE_LEVEL==TRUE)
    switch ( TRACE_GET_TYPE(trace_set_mask) )
    {
        case TRACE_TYPE_ERROR:
            LOGE0(bt_layer_tags[trace_layer], buffer);
            break;
        case TRACE_TYPE_WARNING:
            LOGW0(bt_layer_tags[trace_layer], buffer);
            break;
        case TRACE_TYPE_API:
        case TRACE_TYPE_EVENT:
            LOGI0(bt_layer_tags[trace_layer], buffer);
            break;
        case TRACE_TYPE_DEBUG:
            LOGD0(bt_layer_tags[trace_layer], buffer);
            break;
        default:
            LOGE0(bt_layer_tags[trace_layer], buffer);      /* we should never get this */
            break;
    }
#else
    LOGI0(bt_layer_tags[trace_layer], buffer);
#endif
#else
	write(2, buffer, strlen(buffer));
	write(2, "\n", 1);
#endif
}

void
ScrLog(UINT32 trace_set_mask, const char *fmt_str, ...)
{
	static char buffer[BTE_LOG_BUF_SIZE];

	va_list ap;
	struct timeval tv;
	struct timezone tz;
	struct tm *tm;
	time_t t;
    int trace_layer = TRACE_GET_LAYER(trace_set_mask);
    if (trace_layer >= TRACE_LAYER_MAX_NUM)
        trace_layer = 0;

	gettimeofday(&tv, &tz);
	time(&t);
	tm = localtime(&t);

        sprintf(buffer, "%02d:%02d:%02d.%03ld ", tm->tm_hour, tm->tm_min, tm->tm_sec,
        tv.tv_usec / 1000);

	va_start(ap, fmt_str);
	vsnprintf(&buffer[strlen(buffer)], BTE_LOG_MAX_SIZE, fmt_str, ap);
	va_end(ap);

#if (defined(ANDROID_USE_LOGCAT) && (ANDROID_USE_LOGCAT==TRUE))
    LOGI0(bt_layer_tags[trace_layer], buffer);
#else
	write(2, buffer, strlen(buffer));
	write(2, "\n", 1);
#endif
}

/* this function should go into BTAPP_DM for example */
BT_API UINT8 BTAPP_SetTraceLevel( UINT8 new_level )
{
    if (new_level != 0xFF)
        appl_trace_level = new_level;

    return (appl_trace_level);
}

BTU_API UINT8 BTU_SetTraceLevel( UINT8 new_level )
{
    if (new_level != 0xFF)
        btu_cb.trace_level = new_level;

    return (btu_cb.trace_level);
}

BOOLEAN trace_conf_enabled = FALSE;

void bte_trace_conf(char *p_conf_name, char *p_conf_value)
{
    tBTTRC_FUNC_MAP *p_f_map = (tBTTRC_FUNC_MAP *) &bttrc_set_level_map[0];

    while (p_f_map->trc_name != NULL)
    {
        if (strcmp(p_f_map->trc_name, (const char *)p_conf_name) == 0)
        {
            p_f_map->trace_level = (UINT8) atoi(p_conf_value);
            break;
        }
        p_f_map++;
    }
}

/********************************************************************************
 **
 **    Function Name:    BTA_SysSetTraceLevel
 **
 **    Purpose:          set or reads the different Trace Levels of layer IDs (see bt_trace.h,
 **                      BTTRC_ID_xxxx
 **
 **    Input Parameters: Array with trace layers to set to a given level or read. a layer ID of 0
 **                      defines the end of the list
 **                      WARNING: currently type should be 0-5! or FF for reading!!!!
 **
 **    Returns:
 **                      input array with trace levels for given layer id
 **
 *********************************************************************************/
BT_API tBTTRC_LEVEL * BTA_SysSetTraceLevel(tBTTRC_LEVEL * p_levels)
{
    const tBTTRC_FUNC_MAP *p_f_map;
    tBTTRC_LEVEL *p_l = p_levels;

    DBG_TRACE_API0( "BTA_SysSetTraceLevel()" );

    while (0 != p_l->layer_id)
    {
        p_f_map = &bttrc_set_level_map[0];

        while (0 != p_f_map->layer_id_start)
        {
            printf("BTA_SysSetTraceLevel - trace id in map start = %d end= %d,  paramter id = %d\r\n", p_f_map->layer_id_start, p_f_map->layer_id_end, p_l->layer_id );
            /* as p_f_map is ordered by increasing layer id, go to next map entry as long end id
             * is smaller */
            //if (p_f_map->layer_id_end < p_l->layer_id)
            //{
                //p_f_map++;
            //}
            //else
            {
                /* check if layer_id actually false into a range or if it is note existing in the  map */
                if ((NULL != p_f_map->p_f) && (p_f_map->layer_id_start <= p_l->layer_id) && (p_f_map->layer_id_end >= p_l->layer_id) )
                {
                    DBG_TRACE_DEBUG2( "BTA_SysSetTraceLevel( id:%d, level:%d ): setting/reading",
                            p_l->layer_id, p_l->type );
                    p_l->type = p_f_map->p_f(p_l->type);
                    break;
                }
                else
                {
                    DBG_TRACE_WARNING2( "BTA_SysSetTraceLevel( id:%d, level:%d ): MISSING Set function OR ID in map!",
                            p_l->layer_id, p_l->type );
                }
                /* set/read next trace level by getting out ot map loop */
                //p_l++;
                //break;
            }
            p_f_map++;
        }
        //if (0 == p_f_map->layer_id_start)
        {
            DBG_TRACE_WARNING2( "BTA_SysSetTraceLevel( id:%d, level:%d ): ID NOT FOUND in map. Skip to next",
                    p_l->layer_id, p_l->type );
            p_l++;
        }
    }

    return p_levels;
} /* BTA_SysSetTraceLevel() */

/* make sure list is order by increasing layer id!!! */
tBTTRC_FUNC_MAP bttrc_set_level_map[] = {
    {BTTRC_ID_STK_BTU, BTTRC_ID_STK_HCI, BTU_SetTraceLevel, "TRC_HCI", DEFAULT_CONF_TRACE_LEVEL},
    {BTTRC_ID_STK_L2CAP, BTTRC_ID_STK_L2CAP, L2CA_SetTraceLevel, "TRC_L2CAP", DEFAULT_CONF_TRACE_LEVEL},
#if (RFCOMM_INCLUDED==TRUE)
    {BTTRC_ID_STK_RFCOMM, BTTRC_ID_STK_RFCOMM_DATA, PORT_SetTraceLevel, "TRC_RFCOMM", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (OBX_INCLUDED==TRUE)
    {BTTRC_ID_STK_OBEX, BTTRC_ID_STK_OBEX, OBX_SetTraceLevel, "TRC_OBEX", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (AVCT_INCLUDED==TRUE)
    //{BTTRC_ID_STK_AVCT, BTTRC_ID_STK_AVCT, NULL, "TRC_AVCT", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (AVDT_INCLUDED==TRUE)
    {BTTRC_ID_STK_AVDT, BTTRC_ID_STK_AVDT, AVDT_SetTraceLevel, "TRC_AVDT", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (AVRC_INCLUDED==TRUE)
    {BTTRC_ID_STK_AVRC, BTTRC_ID_STK_AVRC, AVRC_SetTraceLevel, "TRC_AVRC", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (AVDT_INCLUDED==TRUE)
    //{BTTRC_ID_AVDT_SCB, BTTRC_ID_AVDT_CCB, NULL, "TRC_AVDT_SCB", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (A2D_INCLUDED==TRUE)
    {BTTRC_ID_STK_A2D, BTTRC_ID_STK_A2D, A2D_SetTraceLevel, "TRC_A2D", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (BIP_INCLUDED==TRUE)
    {BTTRC_ID_STK_BIP, BTTRC_ID_STK_BIP, BIP_SetTraceLevel, "TRC_BIP", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (BNEP_INCLUDED==TRUE)
    {BTTRC_ID_STK_BNEP, BTTRC_ID_STK_BNEP, BNEP_SetTraceLevel, "TRC_BNEP", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (BPP_INCLUDED==TRUE)
    {BTTRC_ID_STK_BPP, BTTRC_ID_STK_BPP, BPP_SetTraceLevel, "TRC_BPP", DEFAULT_CONF_TRACE_LEVEL},
#endif
    {BTTRC_ID_STK_BTM_ACL, BTTRC_ID_STK_BTM_SEC, BTM_SetTraceLevel, "TRC_BTM", DEFAULT_CONF_TRACE_LEVEL},
#if (DUN_INCLUDED==TRUE)
    {BTTRC_ID_STK_DUN, BTTRC_ID_STK_DUN, DUN_SetTraceLevel, "TRC_DUN", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (GAP_INCLUDED==TRUE)
    {BTTRC_ID_STK_GAP, BTTRC_ID_STK_GAP, GAP_SetTraceLevel, "TRC_GAP", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (GOEP_INCLUDED==TRUE)
    {BTTRC_ID_STK_GOEP, BTTRC_ID_STK_GOEP, GOEP_SetTraceLevel, "TRC_GOEP", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (HCRP_INCLUDED==TRUE)
    {BTTRC_ID_STK_HCRP, BTTRC_ID_STK_HCRP, HCRP_SetTraceLevel, "TRC_HCRP", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (PAN_INCLUDED==TRUE)
    {BTTRC_ID_STK_PAN, BTTRC_ID_STK_PAN, PAN_SetTraceLevel, "TRC_PAN", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (SAP_SERVER_INCLUDED==TRUE)
    {BTTRC_ID_STK_SAP, BTTRC_ID_STK_SAP, NULL, "TRC_SAP", DEFAULT_CONF_TRACE_LEVEL},
#endif
    {BTTRC_ID_STK_SDP, BTTRC_ID_STK_SDP, SDP_SetTraceLevel, "TRC_SDP", DEFAULT_CONF_TRACE_LEVEL},
#if (BLE_INCLUDED==TRUE)
    {BTTRC_ID_STK_GATT, BTTRC_ID_STK_GATT, GATT_SetTraceLevel, "TRC_GATT", DEFAULT_CONF_TRACE_LEVEL},
#endif
#if (BLE_INCLUDED==TRUE)
    {BTTRC_ID_STK_SMP, BTTRC_ID_STK_SMP, SMP_SetTraceLevel, "TRC_SMP", DEFAULT_CONF_TRACE_LEVEL},
#endif

#if (BTA_INCLUDED==TRUE)
    /* LayerIDs for BTA, currently everything maps onto appl_trace_level.
     * BTL_GLOBAL_PROP_TRC_FLAG serves as flag in conf.
     */
    {BTTRC_ID_BTA_ACC, BTTRC_ID_BTAPP, BTAPP_SetTraceLevel, BTL_GLOBAL_PROP_TRC_FLAG, DEFAULT_CONF_TRACE_LEVEL},
#endif

    {0, 0, NULL, NULL, DEFAULT_CONF_TRACE_LEVEL}
};

const UINT16 bttrc_map_size = sizeof(bttrc_set_level_map)/sizeof(tBTTRC_FUNC_MAP);
#endif

#ifndef REVOLUTION
/********************************************************************************
 **
 **    Function Name:     BTE_InitTraceLevels
 **
 **    Purpose:           This function can be used to set the boot time reading it from the
 **                       platform.
 **                       WARNING: it is called under BTU context and it blocks the BTU task
 **                       till it returns (sync call)
 **
 **    Input Parameters:  None, platform to provide levels
 **    Returns:
 **                       Newly set levels, if any!
 **
 *********************************************************************************/
BT_API void BTE_InitTraceLevels( void )
{
    /* read and set trace levels by calling the different XXX_SetTraceLevel().
     */
#if ( BT_USE_TRACES==TRUE )
    if (trace_conf_enabled == TRUE)
    {
        tBTTRC_FUNC_MAP *p_f_map = (tBTTRC_FUNC_MAP *) &bttrc_set_level_map[0];

        while (p_f_map->trc_name != NULL)
        {
            ALOGI("BTE_InitTraceLevels -- %s", p_f_map->trc_name);

            if (p_f_map->p_f)
                p_f_map->p_f(p_f_map->trace_level);

            p_f_map++;
        }
    }
    else
    {
        ALOGI("[bttrc] using compile default trace settings");
    }
#endif
}
#endif

#ifdef REVOLUTION
/********************************************************************************
 **
 **    Function Name:   LogMsg
 **
 **    Purpose:  Encodes a trace message that has multiple parameter arguments
 **
 **    Input Parameters:  trace_set_mask: tester trace type.
 **                       fmt_str: displayable string.
 **    Returns:
 **                      Nothing.
 **
 *********************************************************************************/
void LogMsg(UINT32 trace_set_mask, const char *fmt_str, ...) {
    static char tmp[2000];
    
    va_list list;
    va_start(list, fmt_str);
    vsprintf(tmp, fmt_str, list);
    va_end(list);

    sprintf(tmp, "%s\n", tmp);
    OSReport(tmp);
}
#endif

/********************************************************************************
 **
 **    Function Name:   LogMsg_0
 **
 **    Purpose:  Encodes a trace message that has no parameter arguments
 **
 **    Input Parameters:  trace_set_mask: tester trace type.
 **                       fmt_str: displayable string.
 **    Returns:
 **                      Nothing.
 **
 *********************************************************************************/
void LogMsg_0(UINT32 trace_set_mask, const char *fmt_str) {
#ifdef REVOLUTION
    if (bte_target_mode == BTE_MODE_SERIAL_APP) {
#endif
        LogMsg(trace_set_mask, fmt_str);
#ifdef REVOLUTION
    }
#endif
}

/********************************************************************************
 **
 **    Function Name:   LogMsg_1
 **
 **    Purpose:  Encodes a trace message that has one parameter argument
 **
 **    Input Parameters:  trace_set_mask: tester trace type.
 **                       fmt_str: displayable string.
 **    Returns:
 **                      Nothing.
 **
 *********************************************************************************/
void LogMsg_1(UINT32 trace_set_mask, const char *fmt_str, UINT32 p1) {
#ifdef REVOLUTION
    if (bte_target_mode == BTE_MODE_SERIAL_APP) {
#endif
        LogMsg(trace_set_mask, fmt_str, p1);
#ifdef REVOLUTION
    }
#endif
}

/********************************************************************************
 **
 **    Function Name:   LogMsg_2
 **
 **    Purpose:  Encodes a trace message that has two parameter arguments
 **
 **    Input Parameters:  trace_set_mask: tester trace type.
 **                       fmt_str: displayable string.
 **    Returns:
 **                      Nothing.
 **
 *********************************************************************************/
void LogMsg_2(UINT32 trace_set_mask, const char *fmt_str, UINT32 p1, UINT32 p2) {
#ifdef REVOLUTION
    if (bte_target_mode == BTE_MODE_SERIAL_APP) {
#endif
        LogMsg(trace_set_mask, fmt_str, p1, p2);
#ifdef REVOLUTION
    }
#endif
}

/********************************************************************************
 **
 **    Function Name:   LogMsg_3
 **
 **    Purpose:  Encodes a trace message that has three parameter arguments
 **
 **    Input Parameters:  trace_set_mask: tester trace type.
 **                       fmt_str: displayable string.
 **    Returns:
 **                      Nothing.
 **
 *********************************************************************************/
void LogMsg_3(UINT32 trace_set_mask, const char *fmt_str, UINT32 p1, UINT32 p2,
        UINT32 p3) {
#ifdef REVOLUTION
    if (bte_target_mode == BTE_MODE_SERIAL_APP) {
#endif
        LogMsg(trace_set_mask, fmt_str, p1, p2, p3);
#ifdef REVOLUTION
    }
#endif
}

/********************************************************************************
 **
 **    Function Name:   LogMsg_4
 **
 **    Purpose:  Encodes a trace message that has four parameter arguments
 **
 **    Input Parameters:  trace_set_mask: tester trace type.
 **                       fmt_str: displayable string.
 **    Returns:
 **                      Nothing.
 **
 *********************************************************************************/
void LogMsg_4(UINT32 trace_set_mask, const char *fmt_str, UINT32 p1, UINT32 p2,
        UINT32 p3, UINT32 p4) {
#ifdef REVOLUTION
    if (bte_target_mode == BTE_MODE_SERIAL_APP) {
#endif
        LogMsg(trace_set_mask, fmt_str, p1, p2, p3, p4);
#ifdef REVOLUTION
    }
#endif
}

/********************************************************************************
 **
 **    Function Name:   LogMsg_5
 **
 **    Purpose:  Encodes a trace message that has five parameter arguments
 **
 **    Input Parameters:  trace_set_mask: tester trace type.
 **                       fmt_str: displayable string.
 **    Returns:
 **                      Nothing.
 **
 *********************************************************************************/
void LogMsg_5(UINT32 trace_set_mask, const char *fmt_str, UINT32 p1, UINT32 p2,
        UINT32 p3, UINT32 p4, UINT32 p5) {
#ifdef REVOLUTION
    if (bte_target_mode == BTE_MODE_SERIAL_APP) {
#endif
        LogMsg(trace_set_mask, fmt_str, p1, p2, p3, p4, p5);
#ifdef REVOLUTION
    }
#endif
}

/********************************************************************************
 **
 **    Function Name:   LogMsg_6
 **
 **    Purpose:  Encodes a trace message that has six parameter arguments
 **
 **    Input Parameters:  trace_set_mask: tester trace type.
 **                       fmt_str: displayable string.
 **    Returns:
 **                      Nothing.
 **
 *********************************************************************************/
void LogMsg_6(UINT32 trace_set_mask, const char *fmt_str, UINT32 p1, UINT32 p2,
        UINT32 p3, UINT32 p4, UINT32 p5, UINT32 p6) {
#ifdef REVOLUTION
    if (bte_target_mode == BTE_MODE_SERIAL_APP) {
#endif
        LogMsg(trace_set_mask, fmt_str, p1, p2, p3, p4, p5, p6);
#ifdef REVOLUTION
    }
#endif
}
