/******************************************************************************
 *
 *  NOTICE OF CHANGES
 *  2024/03/25:
 *      - Remove linux functionality for RVL target
 * 
 *  Compile with REVOLUTION defined to include these changes.
 * 
 ******************************************************************************/



/******************************************************************************
 *
 *  Copyright (C) 2002-2012 Broadcom Corporation
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
 *  This is the interface file for the bte application task
 *
 ******************************************************************************/

#ifndef BTE_APPL_H
#define BTE_APPL_H

#include "btm_int.h"
#include "bta_api.h"
#include "bta_sys.h"
#include "bte.h"

/* Maximum length for serial port device name */
#ifndef BTE_APPL_MAX_USERIAL_DEV_NAME
#define BTE_APPL_MAX_USERIAL_DEV_NAME       (256)
#endif
#ifndef BTAPP_AHF_API_SUPPORT
#define BTAPP_AHF_API_SUPPORT FALSE
#endif

/* BTA APP_IDs */
#define UI_DM_ID    1
#define UI_PRM_ID   20
/* this defines the enabled BTA modules. client may not be defined as those are enabled at run time.
 * they are defined for completeness. please check with bta_sys.h for new modules.
 * BTA_ID_DM serves as flag for BTA_EnableBluetooth()
 * BTA_ID_RES can be used to fs ID in bte_appl.
 */

#define BTAPP_NUM_ID_BLOCKS ((BTA_ID_MAX/32)+1)        /* number of 32 bit required to store one bit per
                                                            btapp id */

#define BTAPP_APPL_MAIL_EVENT(x)  (x<<8)    /* define bte_appl task mail box event. LSB contains
                                                BTA_ID_xxx (see bta_sys.h) */
#define BTAPP_APPL_MAIL_EVT       0xff00    /* high byte contains bitmap of application module event */

/* helper macro to copy BTA callack data y into message buffer x, for event data structure z */
#define MEMCPY_APPL_MSG(x, y, z)  memcpy( (void *)(((UINT8 *)x)+sizeof(BT_HDR)), (void *)y, sizeof(z) )

/* Event masks for BTE_APPL_TASK */
#define BTE_APPL_STARTUP_EVT    EVENT_MASK(APPL_EVT_0)      /* Bluetooth has started */
#define BTE_APPL_SHUTDOWN_EVT   EVENT_MASK(APPL_EVT_1)      /* Bluetooth is shutting down */
#define BTE_APPL_SOCKET_RX_EVT  EVENT_MASK(APPL_EVT_2)      /* Socket data ready to be read */
#define BTE_APPL_DBUS_RX_EVT    EVENT_MASK(APPL_EVT_3)      /* DBUS message ready to be read */
#define BTE_APPL_BTA_ENABLE_EVT EVENT_MASK(APPL_EVT_4)      /* BTA Enabled event */


/* Application configuration */
#define BTE_APPL_PATCHRAM_PATH_MAXLEN   128
#define BTE_APPL_CONTACTS_DB_PATH       256

typedef struct {
    char    patchram_path[BTE_APPL_PATCHRAM_PATH_MAXLEN+1];
    UINT32  patchram_addr;
    UINT32  reconfig_baud;
    UINT32  clock_rate;             /* clock rate (for uart baud calculation) */
    BD_ADDR local_addr;             /* local bd addr */
    BD_ADDR rem_addr;
    UINT8   lpm_enabled;
    UINT8   bt_wake_polarity;
    UINT8   host_wake_polarity;
    BOOLEAN ag_enable_3way_conf;
    UINT16  ag_voice_settings;
    UINT8   ag_vsc_pcm_config[5];
    UINT8   ag_vsc_sco_pcm[5];
    /*tBTM_CMPL_CB*/ tBTM_DEV_STATUS_CB *p_reset_cplt_cb;  /* Current reset_cplt_cb */
    char    contacts_db[BTE_APPL_CONTACTS_DB_PATH+1];
    UINT32  bta_module_state[BTAPP_NUM_ID_BLOCKS]; /* state of enabled bta modules */
#if (BTAPP_AHF_API_SUPPORT==TRUE)
    UINT8   afh_first;
    UINT8   afh_last;
#endif
} tBTE_APPL_CFG;

extern tBTE_APPL_CFG bte_appl_cfg;

#ifndef REVOLUTION
typedef struct {
    pthread_mutex_t     mutex;  /* mutex to protect below signal condition */
    pthread_cond_t      cond;   /* signal event */
} tBTAPP_SEMAPHORE;

/* helper functions to handle pthread conditions event from outside GKI */
extern void bte_create_semaphore( tBTAPP_SEMAPHORE * p_sema );
extern void bte_wait_semaphore( tBTAPP_SEMAPHORE * p_sema, unsigned msecs_to );
extern void bte_signal_semaphore( tBTAPP_SEMAPHORE * p_sema );
extern void bte_destroy_semaphore( tBTAPP_SEMAPHORE * p_sema );

/* global application control block storing global application states and variables */
typedef struct tBTE_APPL_CB_tag {
    sigset_t            signal_handler_set;        /* signal handler set used by signal handler thread */
#if ( TRUE == BTE_RESET_BAUD_ON_BT_DISABLE )
    tBTAPP_SEMAPHORE    shutdown_semaphore;   /* used to sync with  terminate handler initated ops */
#endif
    BOOLEAN amp_enabled;                        /* TRUE if AMP is in use */
} tBTE_APPL_CB;

extern tBTE_APPL_CB bte_appl_cb;
#endif

/* Exports the application task */
extern void BTE_appl_task(UINT32 params);
extern int BTAPP_enable_bta( const UINT32 bta_module_state[BTAPP_NUM_ID_BLOCKS], int includingFM );
extern int BTAPP_disable_bta( const UINT32 bta_module_state[BTAPP_NUM_ID_BLOCKS], int includingFM );

extern UINT8 appl_trace_level;
#define BT_PCM_CLK_IDX 1
#ifndef BT_PCM_DEF_CLK
#define BT_PCM_DEF_CLK 4       /* defaults to 2048khz PCM clk */
#endif
#define BT_PCM_SYNC_MS_ROLE_IDX 3
#define BT_PCM_CLK_MS_ROLE_IDX  4
#ifndef BT_PCM_DEF_ROLE
#define BT_PCM_DEF_ROLE    0x00     /* assume slave as default */
#endif

/* helper macros to set, clear and get current BTA module id in a 32bit ARRAY!! */
/* set bit id to 1 in UINT32 a[] NO RANGE CHECK!*/
#define BTAPP_SET_BTA_MOD(id, a)    { a[id/32] |= (UINT32)(1<<(id % 32)); }

/* set bit id to 0 (cleared) in UINT32 a[] NO RANGE CHECK */
#define BTAPP_CLEAR_BTA_MOD(id, a)  { a[id/32] &= (UINT32)!(1<<(id % 32)); }

/* tests if bit id is 1 in UINT32 a[] NO RANGE CHECK */
#define BTAPP_BTA_MOD_IS_SET(id, a) (a[id/32] & (UINT32)(1<<(id % 32)))

/* update this list either via btld.txt or directly here by adding the new profiles as per bta_sys.h.
 * each xxx_LISTx may only contain 32 bits */
#ifndef BTAPP_BTA_MODULES_LIST0
#define BTAPP_BTA_MODULES_LIST0 (\
        ( 1<<BTA_ID_DM ) | \
        ( 1<<BTA_ID_DG ) | \
        ( 1<<BTA_ID_AG ) | \
        ( 1<<BTA_ID_OPC )| \
        ( 1<<BTA_ID_OPS )| \
        ( 1<<BTA_ID_FTS )| \
        ( 1<<BTA_ID_PAN )| \
        ( 1<<BTA_ID_PR ) | \
        ( 1<<BTA_ID_SC)  | \
        ( 1<<BTA_ID_AV ) | \
        ( 1<<BTA_ID_HH ) | \
        ( 1<<BTA_ID_PBS) | \
        ( 1<<BTA_ID_FMTX)| \
        ( 1<<BTA_ID_JV) | \
        ( 1<<BTA_ID_MSE) \
        )
#endif

#define BTAPP_LIST1_BLOCK 32    /* next 32 bit block */
#ifndef BTAPP_BTA_MODULES_LIST1
#define BTAPP_BTA_MODULES_LIST1 (\
        ( 1<<(BTA_ID_MAX-BTAPP_LIST1_BLOCK) ) | \
        ( 1<<(BTA_ID_MSE-BTAPP_LIST1_BLOCK) ) | \
        0 \
        )
#endif
/* for future GPS etc support. goes int LIST1 above */
#if 0
    ( 1<<(BTA_ID_SSR-BTAPP_LIST1_BLOCK) ) \
    ( 1<<(BTA_ID_MSE-BTAPP_LIST1_BLOCK) ) \
    ( 1<<(BTA_ID_MCE-BTAPP_LIST1_BLOCK) )
#endif

/* used application init default in bte_main.c, bte_appl_cfg */
#ifndef BTAPP_DEFAULT_MODULES
#if (1==BTAPP_NUM_ID_BLOCKS)
#define BTAPP_DEFAULT_MODULES {BTAPP_BTA_MODULES_LIST0} /* max 32 modules IDs */
#elif (2==BTAPP_NUM_ID_BLOCKS)
#define BTAPP_DEFAULT_MODULES {BTAPP_BTA_MODULES_LIST0, BTAPP_BTA_MODULES_LIST1} /* 64 module IDs max */
#else
#error "Define more BTAPP_BTA_MODULES_LISTx"
#endif
#endif

#endif  /* BTE_APPL_H */
