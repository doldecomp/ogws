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
 *  This is the interface file for hid host call-out functions.
 *
 ******************************************************************************/
#ifndef BTA_HH_CO_H
#define BTA_HH_CO_H

#include "bta_hh_api.h"


/*******************************************************************************
**
** Function         bta_hh_co_data
**
** Description      This callout function is executed by HH when data is received
**                  in interupt channel.
**
**
** Returns          void.
**
*******************************************************************************/
BTA_API extern void bta_hh_co_data(UINT8 dev_handle, UINT8 *p_rpt, UINT16 len,
                                   tBTA_HH_PROTO_MODE  mode, UINT8 sub_class,
                                   UINT8 ctry_code, BD_ADDR peer_addr, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_hh_co_open
**
** Description      This callout function is executed by HH when connection is
**                  opened, and application may do some device specific
**                  initialization.
**
** Returns          void.
**
*******************************************************************************/
BTA_API extern void bta_hh_co_open(UINT8 dev_handle, UINT8 sub_class,
                                   UINT16 attr_mask, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_hh_co_close
**
** Description      This callout function is executed by HH when connection is
**                  closed, and device specific finalizatio nmay be needed.
**
** Returns          void.
**
*******************************************************************************/
BTA_API extern void bta_hh_co_close(UINT8 dev_handle, UINT8 app_id);

#endif /* BTA_HH_CO_H */

