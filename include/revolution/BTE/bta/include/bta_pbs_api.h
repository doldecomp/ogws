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
 *  This is the public interface file for the phone book access (PB) server
 *  subsystem of BTA, Broadcom's Bluetooth application layer for mobile
 *  phones.
 *
 ******************************************************************************/
#ifndef BTA_PB_API_H
#define BTA_PB_API_H

#include "bta_api.h"
#include "btm_api.h"
#include "bta_sys.h"

/*****************************************************************************
**  Constants and data types
*****************************************************************************/

/**************************
**  Common Definitions
***************************/

/* Profile supported features */
#define BTA_PBS_SUPF_DOWNLOAD     0x0001
#define BTA_PBS_SURF_BROWSE       0x0002

/* Profile supported repositories */
#define BTA_PBS_REPOSIT_LOCAL      0x01    /* Local PhoneBook */
#define BTA_PBS_REPOSIT_SIM        0x02    /* SIM card PhoneBook */

#endif
