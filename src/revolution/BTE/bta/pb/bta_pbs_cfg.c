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
 *  This file contains compile-time configurable constants for the BTA Phone
 *  Book Access Server.
 *
 ******************************************************************************/

#include "bt_target.h"

#if defined(BTA_PBS_INCLUDED) && (BTA_PBS_INCLUDED == TRUE)

#include "bta_pbs_int.h"

/* Realm Character Set */
#ifndef BTA_PBS_REALM_CHARSET
#define BTA_PBS_REALM_CHARSET   0       /* ASCII */
#endif

/* Specifies whether or not client's user id is required during obex authentication */
#ifndef BTA_PBS_USERID_REQ
#define BTA_PBS_USERID_REQ      FALSE
#endif

const tBTA_PBS_CFG bta_pbs_cfg =
{
    BTA_PBS_REALM_CHARSET,      /* Server only */
    BTA_PBS_USERID_REQ,         /* Server only */
    (BTA_PBS_SUPF_DOWNLOAD | BTA_PBS_SURF_BROWSE),
    BTA_PBS_REPOSIT_LOCAL,
};

tBTA_PBS_CFG *p_bta_pbs_cfg = (tBTA_PBS_CFG *)&bta_pbs_cfg;
#endif /* BTA_PBS_INCLUDED */
