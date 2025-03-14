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
 *  This file contains compile-time configurable constants for the BTA Hid
 *  Host.
 *
 ******************************************************************************/

#include "bt_target.h"
#include "bta_hh_api.h"

/* max number of device types supported by BTA */
#ifdef REVOLUTION
#define BTA_HH_MAX_DEVT_SPT 4
#else
#define BTA_HH_MAX_DEVT_SPT         7
#endif

/* size of database for service discovery */
#ifndef BTA_HH_DISC_BUF_SIZE
#ifdef REVOLUTION
#define BTA_HH_DISC_BUF_SIZE        1024
#else
#define BTA_HH_DISC_BUF_SIZE        GKI_MAX_BUF_SIZE
#endif
#endif

/* application ID(none-zero) for each type of device */
#define BTA_HH_APP_ID_MI            1
#define BTA_HH_APP_ID_KB            2
#define BTA_HH_APP_ID_RMC           3
#define BTA_HH_APP_ID_3DSG          4


/* The type of devices supported by BTA HH and corresponding application ID */
tBTA_HH_SPT_TOD p_devt_list[BTA_HH_MAX_DEVT_SPT] =
{
#ifdef REVOLUTION
    {BTA_HH_DEVT_MIC,                 BTA_HH_APP_ID_MI},
    {BTA_HH_DEVT_KBD,                 BTA_HH_APP_ID_KB},
    {BTA_HH_DEVT_JOS,                 BTA_HH_APP_ID_RMC},
    {BTA_HH_DEVT_COM|BTA_HH_DEVT_JOS, BTA_HH_APP_ID_KB}
#else
    {BTA_HH_DEVT_MIC, BTA_HH_APP_ID_MI},
    {BTA_HH_DEVT_KBD, BTA_HH_APP_ID_KB},
    {BTA_HH_DEVT_KBD|BTA_HH_DEVT_MIC, BTA_HH_APP_ID_KB},
    {BTA_HH_DEVT_RMC, BTA_HH_APP_ID_RMC},
    {BTA_HH_DEVT_RMC | BTA_HH_DEVT_KBD, BTA_HH_APP_ID_RMC},
    {BTA_HH_DEVT_MIC | BTA_HH_DEVT_DGT, BTA_HH_APP_ID_MI},
    {BTA_HH_DEVT_UNKNOWN, BTA_HH_APP_ID_3DSG}
#endif
};


const tBTA_HH_CFG bta_hh_cfg =
{
    BTA_HH_MAX_DEVT_SPT,            /* number of supported type of devices */
    p_devt_list,                    /* ToD & AppID list */
    BTA_HH_DISC_BUF_SIZE            /* HH SDP discovery database size */
};


tBTA_HH_CFG *p_bta_hh_cfg = (tBTA_HH_CFG *)&bta_hh_cfg;
