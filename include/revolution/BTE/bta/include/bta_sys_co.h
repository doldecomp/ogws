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
 *  This is the interface file for system callout functions.
 *
 ******************************************************************************/
#ifndef BTA_SYS_CO_H
#define BTA_SYS_CO_H

#include "bta_sys.h"



/*****************************************************************************
**  Function Declarations
*****************************************************************************/


/*******************************************************************************
**
** Function         bta_sys_hw_co_enable
**
** Description      This function is called by the stack to power up the HW
**
** Returns          void
**
*******************************************************************************/
BTA_API void bta_sys_hw_co_enable( tBTA_SYS_HW_MODULE module );

/*******************************************************************************
**
** Function         bta_sys_hw_co_disable
**
** Description     This function is called by the stack to power down the HW
**
** Returns          void
**
*******************************************************************************/
BTA_API void bta_sys_hw_co_disable( tBTA_SYS_HW_MODULE module );


#endif
