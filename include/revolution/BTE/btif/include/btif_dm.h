/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Broadcom Corporation
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

#ifndef BTIF_DM_H
#define BTIF_DM_H

/*******************************************************************************
**  Functions
********************************************************************************/

/**
 * BTIF callback to switch context from bte to btif
 */
void bte_dm_evt(tBTA_DM_SEC_EVT event, tBTA_DM_SEC *p_data);

/**
 * Notify BT disable being initiated. DM may chose to abort
 * pending commands, like pairing
 */
void btif_dm_on_disable(void);

/**
 * Out-of-band functions
 */
#if (BTM_OOB_INCLUDED == TRUE)
void btif_dm_set_oob_for_io_req(tBTA_OOB_DATA  *p_oob_data);
#ifdef BTIF_DM_OOB_TEST
void btif_dm_load_local_oob(void);
void btif_dm_proc_loc_oob(BOOLEAN valid, BT_OCTET16 c, BT_OCTET16 r);
BOOLEAN btif_dm_proc_rmt_oob(BD_ADDR bd_addr,  BT_OCTET16 p_c, BT_OCTET16 p_r);
#endif /* BTIF_DM_OOB_TEST */
#endif /* BTM_OOB_INCLUDED */

#endif
