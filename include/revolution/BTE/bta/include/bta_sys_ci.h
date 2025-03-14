/******************************************************************************
 *
 *  Copyright (C) 2010-2012 Broadcom Corporation
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
 *  This is the interface file for system call-in functions.
 *
 ******************************************************************************/
#ifndef BTA_SYS_CI_H
#define BTA_SYS_CI_H

#include "bta_api.h"

/*****************************************************************************
**  Function Declarations
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**
** Function         bta_sys_hw_ci_enabled
**
** Description      This function must be called in response to function
**                  bta_sys_hw_co_enable(), when HW is indeed enabled
**
**
** Returns          void
**
*******************************************************************************/
BTA_API  void bta_sys_hw_ci_enabled(tBTA_SYS_HW_MODULE module );


/*******************************************************************************
**
** Function         bta_sys_hw_ci_disabled
**
** Description      This function must be called in response to function
**                  bta_sys_hw_co_disable() when HW is really OFF
**
**
** Returns          void
**
*******************************************************************************/
BTA_API void bta_sys_hw_ci_disabled( tBTA_SYS_HW_MODULE module  );

#ifdef __cplusplus
}
#endif

#endif

