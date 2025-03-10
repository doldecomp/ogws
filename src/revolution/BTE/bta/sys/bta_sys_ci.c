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
 *  This is the implementation file for BTA system call-in functions.
 *
 ******************************************************************************/

#include "bta_sys.h"
#include "bta_sys_ci.h"


/*******************************************************************************
**
** Function         bta_sys_hw_ci_enabled
**
** Description      This function must be called in response to function
**                  bta_sys_hw_enable_co(), when HW is indeed enabled
**
**
** Returns          void
**
*******************************************************************************/
  void bta_sys_hw_ci_enabled(tBTA_SYS_HW_MODULE module )

{
    tBTA_SYS_HW_MSG *p_msg;

    if ((p_msg = (tBTA_SYS_HW_MSG *) GKI_getbuf(sizeof(tBTA_SYS_HW_MSG))) != NULL)
    {
        p_msg->hdr.event = BTA_SYS_EVT_ENABLED_EVT;
        p_msg->hw_module = module;

        bta_sys_sendmsg(p_msg);
    }
}

/*******************************************************************************
**
** Function         bta_sys_hw_ci_disabled
**
** Description      This function must be called in response to function
**                  bta_sys_hw_disable_co() when HW is really OFF
**
**
** Returns          void
**
*******************************************************************************/
void bta_sys_hw_ci_disabled( tBTA_SYS_HW_MODULE module  )
{
    tBTA_SYS_HW_MSG *p_msg;

    if ((p_msg = (tBTA_SYS_HW_MSG *) GKI_getbuf(sizeof(tBTA_SYS_HW_MSG))) != NULL)
    {
        p_msg->hdr.event = BTA_SYS_EVT_DISABLED_EVT;
        p_msg->hw_module = module;

        bta_sys_sendmsg(p_msg);
    }
}

