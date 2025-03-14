/******************************************************************************
 *
 *  NOTICE OF CHANGES
 *  2024/03/26:
 *      - Add #defines to change configurations for RVL target
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
 *  This file contains compile-time configurable constants for the device
 *  manager.
 *
 ******************************************************************************/

#include "bt_target.h"
#include "bta_sys.h"
#include "bta_api.h"
#include "bta_dm_int.h"

#ifdef REVOLUTION

#define BTA_DM_LINK_TIMEOUT    5000

#endif

#ifndef BTA_DM_LINK_POLICY_SETTINGS
#define BTA_DM_LINK_POLICY_SETTINGS    (HCI_ENABLE_MASTER_SLAVE_SWITCH | HCI_ENABLE_HOLD_MODE | HCI_ENABLE_SNIFF_MODE | HCI_ENABLE_PARK_MODE)
#endif

/* page timeout in 625uS */
#ifndef BTA_DM_PAGE_TIMEOUT
#define BTA_DM_PAGE_TIMEOUT    8192
#endif

/* link supervision timeout in 625uS (5 secs) */
#ifndef BTA_DM_LINK_TIMEOUT
#define BTA_DM_LINK_TIMEOUT    8000
#endif

/* For Insight, PM cfg lookup tables are runtime configurable (to allow tweaking of params for power consumption measurements) */
#ifndef BTE_SIM_APP
#define tBTA_DM_PM_TYPE_QUALIFIER   const
#else
#define tBTA_DM_PM_TYPE_QUALIFIER
#endif


const tBTA_DM_CFG bta_dm_cfg =
{
    /* mobile phone COD */
    BTA_DM_COD,
    /* link policy settings */
    BTA_DM_LINK_POLICY_SETTINGS,
    /* page timeout in 625uS */
    BTA_DM_PAGE_TIMEOUT,
    /* link supervision timeout in 625uS*/
    BTA_DM_LINK_TIMEOUT,
#ifdef REVOLUTION
    /* FALSE to not avoid scatternet when av is streaming */
    FALSE
#else
    /* TRUE to avoid scatternet when av is streaming (be the master) */
    TRUE
#endif
};

#ifndef BTA_DM_SCATTERNET
/* By default, allow partial scatternet */
#define BTA_DM_SCATTERNET BTA_DM_PARTIAL_SCATTERNET
#endif

#ifndef BTA_HH_ROLE
/* By default, do not specify HH role (backward compatibility) */
#define BTA_HH_ROLE BTA_ANY_ROLE
#endif

#ifndef BTA_AV_ROLE
/* By default, AV role (backward BTA_MASTER_ROLE_PREF) */
#define BTA_AV_ROLE BTA_MASTER_ROLE_PREF
#endif

#ifdef REVOLUTION
#define BTA_DM_NUM_RM_ENTRY    2
#else
#define BTA_DM_NUM_RM_ENTRY    4
#endif

/* appids for PAN used by insight sample application
   these have to be same as defined in btui_int.h */
#define BTUI_PAN_ID_PANU         0
#define BTUI_PAN_ID_NAP          1
#define BTUI_PAN_ID_GN           2

/* First element is always for SYS:
   app_id = # of entries table, cfg is
   device scatternet support */
#ifdef REVOLUTION
const tBTA_DM_RM bta_dm_rm_cfg[] =
{
    {BTA_ID_SYS, BTA_DM_NUM_RM_ENTRY, BTA_DM_SCATTERNET},
    {BTA_ID_PAN, BTUI_PAN_ID_NAP, BTA_MASTER_ROLE_ONLY},
    {BTA_ID_PAN, BTUI_PAN_ID_GN, BTA_MASTER_ROLE_ONLY},
    {BTA_ID_AV,  BTA_ALL_APP_ID, BTA_AV_ROLE}
};
#else
const tBTA_DM_RM bta_dm_rm_cfg[] =
{
    {BTA_ID_SYS, BTA_DM_NUM_RM_ENTRY, BTA_DM_SCATTERNET},
    {BTA_ID_PAN, BTUI_PAN_ID_NAP, BTA_MASTER_ROLE_ONLY},
    {BTA_ID_PAN, BTUI_PAN_ID_GN, BTA_MASTER_ROLE_ONLY},
    {BTA_ID_HH,  BTA_ALL_APP_ID, BTA_HH_ROLE},
    {BTA_ID_AV,  BTA_ALL_APP_ID, BTA_AV_ROLE}
};
#endif

tBTA_DM_CFG *p_bta_dm_cfg = (tBTA_DM_CFG *)&bta_dm_cfg;

tBTA_DM_RM *p_bta_dm_rm_cfg = (tBTA_DM_RM *)&bta_dm_rm_cfg;

#define BTA_DM_NUM_PM_ENTRY         (15+BTA_DM_NUM_JV_ID)  /* number of entries in bta_dm_pm_cfg except the first */

#ifdef REVOLUTION
tBTA_DM_PM_TYPE_QUALIFIER tBTA_DM_PM_CFG bta_dm_pm_cfg;
#else
tBTA_DM_PM_TYPE_QUALIFIER tBTA_DM_PM_CFG bta_dm_pm_cfg[] =
{
  {BTA_ID_SYS, BTA_DM_NUM_PM_ENTRY, 0},
  {BTA_ID_AG,  BTA_ALL_APP_ID,      0},  /* ag uses first spec table for app id 0 */
  {BTA_ID_CT,  1,                   1},  /* ct (BTA_ID_CT,APP ID=1) spec table */
  {BTA_ID_CG,  BTA_ALL_APP_ID,      1},  /* cg resue ct spec table */
  {BTA_ID_DG,  BTA_ALL_APP_ID,      2},  /* dg spec table */
  {BTA_ID_AV,  BTA_ALL_APP_ID,      4},  /* av spec table */
  {BTA_ID_FTC, BTA_ALL_APP_ID,      6},  /* ftc spec table */
  {BTA_ID_FTS, BTA_ALL_APP_ID,      7},  /* fts spec table */
  {BTA_ID_HD,  BTA_ALL_APP_ID,      3},  /* hd spec table */
  {BTA_ID_HH,  BTA_ALL_APP_ID,      5},  /* hh spec table */
  {BTA_ID_PBC, BTA_ALL_APP_ID,      2},  /* reuse dg spec table */
  {BTA_ID_PBS, BTA_ALL_APP_ID,      7},  /* reuse fts spec table */
  {BTA_ID_OPC, BTA_ALL_APP_ID,      6},  /* reuse ftc spec table */
  {BTA_ID_OPS, BTA_ALL_APP_ID,      7},  /* reuse fts spec table */
  {BTA_ID_MSE, BTA_ALL_APP_ID,      7},  /* reuse fts spec table */
  {BTA_ID_JV1, BTA_ALL_APP_ID,      7},  /* reuse fts spec table */
  {BTA_ID_JV2, BTA_ALL_APP_ID,      7},  /* reuse fts spec table */
  {BTA_ID_HL,  BTA_ALL_APP_ID,      8}   /* reuse fts spec table */
};
#endif


#ifdef REVOLUTION
#define BTA_DM_NUM_COMPRESS_ENTRY 5

tBTA_DM_PM_TYPE_QUALIFIER tBTA_DM_COMPRESS_CFG bta_dm_compress_cfg[] =
{
    {BTA_ID_SYS, BTA_DM_NUM_COMPRESS_ENTRY, 0},
    {BTA_ID_FTC, BTA_ALL_APP_ID,            1},
    {BTA_ID_FTS, BTA_ALL_APP_ID,            1},
    {BTA_ID_OPC, BTA_ALL_APP_ID,            1},
    {BTA_ID_OPS, BTA_ALL_APP_ID,            1},
    {BTA_ID_AV,  BTA_ALL_APP_ID,            2}
};

tBTA_DM_COMPRESS_CFG *p_bta_dm_compress_cfg = (tBTA_DM_COMPRESS_CFG *)&bta_dm_compress_cfg;
#endif

#ifdef BTE_SIM_APP      /* For Insight builds only, see the detail below */
#define BTA_DM_NUM_PM_SPEC      (9 + 2)  /* additional two */
#elif REVOLUTION
#define BTA_DM_NUM_PM_SPEC      1
#else
#define BTA_DM_NUM_PM_SPEC      9  /* additional JV*/
#endif

tBTA_DM_PM_TYPE_QUALIFIER tBTA_DM_PM_SPEC bta_dm_pm_spec[BTA_DM_NUM_PM_SPEC] =
{
#ifdef REVOLUTION

 {
  (BTA_DM_PM_SNIFF_RVL | BTA_DM_PM_NO_PREF),                       /* allow park & sniff */
#if (BTM_SSR_INCLUDED == TRUE)
  (BTA_DM_PM_SSR0),                                                /* the SSR entry */
#endif
  {
      {{BTA_DM_PM_SNIFF_RVL, 5000},   {BTA_DM_PM_NO_ACTION, 0}},   /* conn open sniff  */
      {{BTA_DM_PM_PARK,         0},   {BTA_DM_PM_NO_ACTION, 0}},   /* conn close  */
      {{BTA_DM_PM_NO_ACTION,    0},   {BTA_DM_PM_NO_ACTION, 0}},   /* app open */
      {{BTA_DM_PM_NO_ACTION,    0},   {BTA_DM_PM_NO_ACTION, 0}},   /* app close */
      {{BTA_DM_PM_NO_ACTION,    0},   {BTA_DM_PM_NO_ACTION, 0}},   /* sco open, active */
      {{BTA_DM_PM_SNIFF_RVL, 5000},   {BTA_DM_PM_NO_ACTION, 0}},   /* sco close sniff  */
      {{BTA_DM_PM_NO_ACTION, 0},      {BTA_DM_PM_NO_ACTION, 0}},   /* idle */
      {{BTA_DM_PM_NO_ACTION, 0},      {BTA_DM_PM_NO_ACTION, 0}},   /* busy */
      {{BTA_DM_PM_RETRY_RVL, 5000},   {BTA_DM_PM_NO_ACTION, 0}}    /* mode change retry */
  }
 },

#else
  /* AG */
 {
  (BTA_DM_PM_SNIFF | BTA_DM_PM_PARK),                           /* allow park & sniff */
#if (BTM_SSR_INCLUDED == TRUE)
  (BTA_DM_PM_SSR2),                                              /* the SSR entry */
#endif
  {
      {{BTA_DM_PM_SNIFF,  5000},   {BTA_DM_PM_NO_ACTION, 0}},   /* conn open sniff  */
      {{BTA_DM_PM_NO_PREF,   0},   {BTA_DM_PM_NO_ACTION, 0}},   /* conn close  */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},   /* app open */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},   /* app close */
      {{BTA_DM_PM_SNIFF3, 5000},   {BTA_DM_PM_NO_ACTION, 0}},   /* sco open, active */
      {{BTA_DM_PM_SNIFF,  5000},   {BTA_DM_PM_NO_ACTION, 0}},   /* sco close sniff  */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},   /* idle */
      {{BTA_DM_PM_ACTIVE,    0},   {BTA_DM_PM_NO_ACTION, 0}},   /* busy */
      {{BTA_DM_PM_RETRY,  5000},   {BTA_DM_PM_NO_ACTION, 0}}    /* mode change retry */
  }
 },

  /* CT */
 {
  (BTA_DM_PM_SNIFF | BTA_DM_PM_PARK),                           /* allow park & sniff */
#if (BTM_SSR_INCLUDED == TRUE)
  (BTA_DM_PM_SSR2),                                              /* the SSR entry */
#endif
  {
      {{BTA_DM_PM_PARK,   5000},  {BTA_DM_PM_NO_ACTION, 0}},    /* conn open  park */
      {{BTA_DM_PM_NO_PREF,   0},  {BTA_DM_PM_NO_ACTION, 0}},    /* conn close  */
      {{BTA_DM_PM_NO_ACTION, 0},  {BTA_DM_PM_NO_ACTION, 0}},    /* app open */
      {{BTA_DM_PM_NO_ACTION, 0},  {BTA_DM_PM_NO_ACTION, 0}},    /* app close */
      {{BTA_DM_PM_SNIFF,  5000},  {BTA_DM_PM_NO_ACTION, 0}},    /* sco open sniff */
      {{BTA_DM_PM_PARK,   5000},  {BTA_DM_PM_NO_ACTION, 0}},    /* sco close  park */
      {{BTA_DM_PM_NO_ACTION, 0},  {BTA_DM_PM_NO_ACTION, 0}},    /* idle */
      {{BTA_DM_PM_NO_ACTION, 0},  {BTA_DM_PM_NO_ACTION, 0}},    /* busy */
      {{BTA_DM_PM_RETRY,  5000},  {BTA_DM_PM_NO_ACTION, 0}}     /* mode change retry */
  }
 },

  /* DG */
 {
  (BTA_DM_PM_ACTIVE),                                             /* no power saving mode allowed */
#if (BTM_SSR_INCLUDED == TRUE)
  (BTA_DM_PM_SSR2),                                              /* the SSR entry */
#endif
  {
      {{BTA_DM_PM_ACTIVE,    0},   {BTA_DM_PM_NO_ACTION, 0}},    /* conn open  active */
      {{BTA_DM_PM_NO_PREF,   0},   {BTA_DM_PM_NO_ACTION, 0}},    /* conn close  */
      {{BTA_DM_PM_ACTIVE,    0},   {BTA_DM_PM_NO_ACTION, 0}},    /* app open */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* app close */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* sco open  */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* sco close   */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* idle */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* busy */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}}     /* mode change retry */
  }
 },

   /* HD */
 {
  (BTA_DM_PM_SNIFF | BTA_DM_PM_PARK),                            /* allow park & sniff */
#if (BTM_SSR_INCLUDED == TRUE)
  (BTA_DM_PM_SSR3),                                              /* the SSR entry */
#endif
  {
      {{BTA_DM_PM_SNIFF4, 5000},   {BTA_DM_PM_NO_ACTION, 0}},    /* conn open  sniff */
      {{BTA_DM_PM_NO_PREF,   0},   {BTA_DM_PM_NO_ACTION, 0}},    /* conn close  */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* app open */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* app close */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* sco open  */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* sco close   */
      {{BTA_DM_PM_SNIFF2, 5000},   {BTA_DM_PM_NO_ACTION, 0}},    /* idle */
      {{BTA_DM_PM_SNIFF4,    0},   {BTA_DM_PM_NO_ACTION, 0}},    /* busy */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}}     /* mode change retry */
  }
 },

   /* AV */
 {
  (BTA_DM_PM_SNIFF),                                             /* allow sniff */
#if (BTM_SSR_INCLUDED == TRUE)
  (BTA_DM_PM_SSR2),                                              /* the SSR entry */
#endif
  {
      {{BTA_DM_PM_SNIFF,  5000},   {BTA_DM_PM_NO_ACTION, 0}},    /* conn open  sniff */
      {{BTA_DM_PM_NO_PREF,   0},   {BTA_DM_PM_NO_ACTION, 0}},    /* conn close  */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* app open */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* app close */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* sco open  */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* sco close   */
      {{BTA_DM_PM_SNIFF,  5000},   {BTA_DM_PM_NO_ACTION, 0}},    /* idle */
      {{BTA_DM_PM_ACTIVE,    0},   {BTA_DM_PM_NO_ACTION, 0}},    /* busy */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}}     /* mode change retry */
  }
 },

  /* HH */
 {
  (BTA_DM_PM_SNIFF | BTA_DM_PM_PARK),                            /* allow park & sniff */
#if (BTM_SSR_INCLUDED == TRUE)
  (BTA_DM_PM_SSR1),                                              /* the SSR entry */
#endif
  {
      {{BTA_DM_PM_SNIFF2, 7000},   {BTA_DM_PM_NO_ACTION, 0}},    /* conn open  sniff */
      {{BTA_DM_PM_NO_PREF,   0},   {BTA_DM_PM_NO_ACTION, 0}},    /* conn close  */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* app open */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* app close */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* sco open  */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* sco close, used for HH suspend   */
      {{BTA_DM_PM_SNIFF2, 7000},   {BTA_DM_PM_NO_ACTION, 0}},    /* idle */
      {{BTA_DM_PM_SNIFF2, 7000},   {BTA_DM_PM_NO_ACTION, 0}},    /* busy */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}}     /* mode change retry */
  }
 },

  /* FTC, OPC */
 {
  (BTA_DM_PM_SNIFF),                                             /* allow sniff */
#if (BTM_SSR_INCLUDED == TRUE)
  (BTA_DM_PM_SSR2),                                              /* the SSR entry */
#endif
  {
      {{BTA_DM_PM_ACTIVE,    0},   {BTA_DM_PM_NO_ACTION, 0}},    /* conn open  active */
      {{BTA_DM_PM_NO_PREF,   0},   {BTA_DM_PM_NO_ACTION, 0}},    /* conn close  */
      {{BTA_DM_PM_ACTIVE,    0},   {BTA_DM_PM_NO_ACTION, 0}},    /* app open */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* app close */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* sco open  */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* sco close   */
      {{BTA_DM_PM_SNIFF,  5000},   {BTA_DM_PM_NO_ACTION, 0}},    /* idle */
      {{BTA_DM_PM_ACTIVE,    0},   {BTA_DM_PM_NO_ACTION, 0}},    /* busy */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}}     /* mode change retry */
  }
 },

  /* FTS, OPS */
 {
  (BTA_DM_PM_SNIFF),                                             /* allow sniff */
#if (BTM_SSR_INCLUDED == TRUE)
  (BTA_DM_PM_SSR2),                                              /* the SSR entry */
#endif
  {
      {{BTA_DM_PM_ACTIVE,    0},   {BTA_DM_PM_NO_ACTION, 0}},    /* conn open  active */
      {{BTA_DM_PM_NO_PREF,   0},   {BTA_DM_PM_NO_ACTION, 0}},    /* conn close  */
      {{BTA_DM_PM_ACTIVE,    0},   {BTA_DM_PM_NO_ACTION, 0}},    /* app open */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* app close */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* sco open  */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},    /* sco close   */
      {{BTA_DM_PM_SNIFF,  7000},   {BTA_DM_PM_NO_ACTION, 0}},    /* idle */
      {{BTA_DM_PM_ACTIVE,    0},   {BTA_DM_PM_NO_ACTION, 0}},    /* busy */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}}     /* mode change retry */
  }
 },

   /* HL */
 {
  (BTA_DM_PM_SNIFF),                                             /* allow sniff */
#if (BTM_SSR_INCLUDED == TRUE)
  (BTA_DM_PM_SSR2),                                              /* the SSR entry */
#endif
  {
      {{BTA_DM_PM_SNIFF,  5000},   {BTA_DM_PM_NO_ACTION, 0}},   /* conn open sniff  */
      {{BTA_DM_PM_NO_PREF,   0},   {BTA_DM_PM_NO_ACTION, 0}},   /* conn close  */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},   /* app open */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},   /* app close */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},   /* sco open, active */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},   /* sco close sniff  */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}},   /* idle */
      {{BTA_DM_PM_ACTIVE,    0},   {BTA_DM_PM_NO_ACTION, 0}},   /* busy */
      {{BTA_DM_PM_NO_ACTION, 0},   {BTA_DM_PM_NO_ACTION, 0}}    /* mode change retry */
  }
 }
#endif

#ifdef BTE_SIM_APP      /* For Insight builds only */
 /* Entries at the end of the pm_spec table are user-defined (runtime configurable),
    for power consumption experiments.
    Insight finds the first user-defined entry by looking for the first BTA_DM_PM_NO_PREF.
    The number of user_defined specs is defined by BTA_SWRAP_UD_PM_SPEC_COUNT */
 ,
 {BTA_DM_PM_NO_PREF},               /* pm_spec USER_DEFINED_0 */
 {BTA_DM_PM_NO_PREF}                /* pm_spec USER_DEFINED_1 */
#endif  /* BTE_SIM_APP */
};

tBTA_DM_PM_TYPE_QUALIFIER tBTM_PM_PWR_MD bta_dm_pm_md[] =
{
/* more sniff parameter entries can be added for BTA_DM_PM_SNIFF3 - BTA_DM_PM_SNIFF7, if needed
When entries are added or removed, BTA_DM_PM_PARK_IDX needs to be updated to reflect the actual index
BTA_DM_PM_PARK_IDX is defined in bta_api.h and can be override by the bdroid_buildcfg.h settings.
The SNIFF table entries must be in the order from highest latency (biggest interval) to lowest latency.
If there's a conflict among the connected services, the setting with lowest latency wins.
*/
/* sniff modes: max interval, min interval, attempt, timeout */
#ifdef REVOLUTION
  {400, 200,    4, 4, BTM_PM_MD_SNIFF},
  {800, 400,    0, 0, BTM_PM_MD_PARK}
#else
  {800, 400, 4, 1, BTM_PM_MD_SNIFF}, /*for BTA_DM_PM_SNIFF - A2DP */
  {400, 200, 4, 1, BTM_PM_MD_SNIFF}, /*for BTA_DM_PM_SNIFF1 */
  {180, 150, 4, 1, BTM_PM_MD_SNIFF}, /*for BTA_DM_PM_SNIFF2- HD idle */
  {150,  50, 4, 1, BTM_PM_MD_SNIFF}, /*for BTA_DM_PM_SNIFF3- SCO open */
  { 54,  30, 4, 1, BTM_PM_MD_SNIFF}, /*for BTA_DM_PM_SNIFF4- HD active*/
  {800, 400, 0, 0, BTM_PM_MD_PARK}
#endif

#ifdef BTE_SIM_APP      /* For Insight builds only */
  /* Entries at the end of the bta_dm_pm_md table are user-defined (runtime configurable),
     for power consumption experiments.
     Insight finds the first user-defined entry by looking for the first 'max=0'.
     The number of user_defined specs is defined by BTA_SWRAP_UD_PM_DM_COUNT */
  ,
  {0},           /* CONN_OPEN/SCO_CLOSE power mode settings for pm_spec USER_DEFINED_0 */
  {0},           /* SCO_OPEN power mode settings for pm_spec USER_DEFINED_0 */

  {0},           /* CONN_OPEN/SCO_CLOSE power mode settings for pm_spec USER_DEFINED_1 */
  {0}            /* SCO_OPEN power mode settings for pm_spec USER_DEFINED_1 */
#endif  /* BTE_SIM_APP */
};

/* 0=max_lat -> no SSR */
/* the smaller of the SSR max latency wins.
 * the entries in this table must be from highest latency (biggest interval) to lowest latency */
#if (BTM_SSR_INCLUDED == TRUE)
tBTA_DM_SSR_SPEC bta_dm_ssr_spec[] =
{
    /*max_lat, min_rmt_to, min_loc_to*/
    {0,      0, 0},     /* BTA_DM_PM_SSR0 - do not use SSR */
    {1600,   2, 2},     /* BTA_DM_PM_SSR1 - HH */
    {1200,   2, 2},     /* BTA_DM_PM_SSR2 - others (as long as sniff is allowed)*/
    {360,  160, 2}      /* BTA_DM_PM_SSR3 - HD */
};

tBTA_DM_SSR_SPEC *p_bta_dm_ssr_spec = (tBTA_DM_SSR_SPEC *)&bta_dm_ssr_spec;
#endif

tBTA_DM_PM_CFG *p_bta_dm_pm_cfg = (tBTA_DM_PM_CFG *)&bta_dm_pm_cfg;
tBTA_DM_PM_SPEC *p_bta_dm_pm_spec = (tBTA_DM_PM_SPEC *)&bta_dm_pm_spec;
tBTM_PM_PWR_MD *p_bta_dm_pm_md = (tBTM_PM_PWR_MD *)&bta_dm_pm_md;

/* The performance impact of EIR packet size
**
** When BTM_EIR_DEFAULT_FEC_REQUIRED is TRUE,
** 1 to 17 bytes,    DM1 is used and most robust.
** 18 to 121 bytes,  DM3 is used but impacts inquiry scan time with large number
**                    of devices.(almost double with 150 users)
** 122 to 224 bytes, DM5 is used but cause quite big performance loss even with
**                    small number of users. so it is not recommended.
** 225 to 240 bytes, DH5 is used without FEC but it not recommended.
**                    (same reason of DM5)
**
** When BTM_EIR_DEFAULT_FEC_REQUIRED is FALSE,
** 1 to 27 bytes,    DH1 is used but only robust at short range.
** 28 to 183 bytes,  DH3 is used but only robust at short range and impacts inquiry
**                    scan time with large number of devices.
** 184 to 240 bytes, DH5 is used but it not recommended.
*/

#if ( BTM_EIR_SERVER_INCLUDED == TRUE )
#if (BTA_EIR_CANNED_UUID_LIST == TRUE)
                                            /* for example */
const UINT8 bta_dm_eir_uuid16_list[] = {    0x08, 0x11, /* Headset */
                                            0x1E, 0x11, /* Handsfree */
                                            0x0E, 0x11, /* AV Remote Control */
                                            0x0B, 0x11, /* Audio Sink */
};
#endif

/* Extended Inquiry Response */
const tBTA_DM_EIR_CONF bta_dm_eir_cfg =
{
    50,    /* minimum length of local name when it is shortened */
           /* if length of local name is longer than this and EIR has not enough */
           /* room for all UUID list then local name is shortened to this length */
#if (BTA_EIR_CANNED_UUID_LIST == TRUE)
    8,
    (UINT8 *)bta_dm_eir_uuid16_list,
#else
    {   /* mask of UUID list in EIR */
        0xFFFFFFFF, /* LSB is the first UUID of the first 32 UUIDs in BTM_EIR_UUID_LKUP_TBL */
        0xFFFFFFFF  /* LSB is the first UUID of the next 32 UUIDs in BTM_EIR_UUID_LKUP_TBL */
        /* BTM_EIR_UUID_LKUP_TBL can be overrided */
    },
#endif
    NULL,   /* Inquiry TX power         */
    0,      /* length of flags in bytes */
    NULL,   /* flags for EIR */
    0,      /* length of manufacturer specific in bytes */
    NULL,   /* manufacturer specific */
};
tBTA_DM_EIR_CONF *p_bta_dm_eir_cfg = (tBTA_DM_EIR_CONF*)&bta_dm_eir_cfg;
#endif
