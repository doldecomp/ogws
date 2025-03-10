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

/******************************************************************************
 *
 *  This is the interface file for the HL (HeaLth device profile) subsystem
 *  call-out functions.
 *
 ******************************************************************************/
#ifndef BTA_HL_CO_H
#define BTA_HL_CO_H

#include "bta_api.h"
#include "bta_hl_api.h"

/*****************************************************************************
**  Constants and Data Types
*****************************************************************************/
/**************************
**  Common Definitions
***************************/


/*******************************************************************************
**
** Function        bta_hl_co_get_num_of_mdep
**
** Description     This function is called to get the number of MDEPs for this
**                 application ID
**
** Parameters      app_id - application ID
**                 p_num_of_mdep (output) - number of MDEP configurations supported
**                                          by the application
**
** Returns         Bloolean - TRUE success
**
*******************************************************************************/
BTA_API extern BOOLEAN bta_hl_co_get_num_of_mdep(UINT8 app_id, UINT8 *p_num_of_mdep);
/*******************************************************************************
**
** Function        bta_hl_co_advrtise_source_sdp
**
** Description     This function is called to find out whether the SOURCE MDEP
**                 configuration information should be advertize in the SDP or nopt
**
** Parameters      app_id - application ID
**
** Returns         Bloolean - TRUE advertise the SOURCE MDEP configuration
**                            information
**
*******************************************************************************/
BTA_API extern BOOLEAN bta_hl_co_advrtise_source_sdp(UINT8 app_id);
/*******************************************************************************
**
** Function        bta_hl_co_get_mdep_config
**
** Description     This function is called to get the supported feature
**                 configuration for the specified mdep index and it also assigns
**                 the MDEP ID for the specified mdep index
**
** Parameters      app_id - HDP application ID
**                 mdep_idx - the mdep index
**                 mdep_id  - the assigned MDEP ID for the specified medp_idx
**                 p_mdl_cfg (output) - pointer to the MDEP configuration
**
**
** Returns         Bloolean - TRUE success
*******************************************************************************/
BTA_API extern BOOLEAN bta_hl_co_get_mdep_config(UINT8 app_id,
                                                 UINT8 mdep_idx,
                                                 tBTA_HL_MDEP_ID mdep_id,
                                                 tBTA_HL_MDEP_CFG *p_mdep_cfg);


/*******************************************************************************
**
** Function        bta_hl_co_get_echo_config
**
** Description     This function is called to get the echo test
**                 maximum APDU size configuration
**
** Parameters      app_id - HDP application ID
**                 p_echo_cfg (output) - pointer to the Echo test maximum APDU size
**                                       configuration
**
** Returns         Bloolean - TRUE success
*******************************************************************************/
BTA_API extern BOOLEAN bta_hl_co_get_echo_config(UINT8  app_id,
                                                 tBTA_HL_ECHO_CFG *p_echo_cfg);


/*******************************************************************************
**
** Function        bta_hl_co_save_mdl
**
** Description     This function is called to save a MDL configuration item in persistent
**                 storage
**
** Parameters      app_id - HDP application ID
**                 item_idx - the MDL configuration storage index
**                 p_mdl_cfg - pointer to the MDL configuration data
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_hl_co_save_mdl(UINT8 app_id, UINT8 item_idx, tBTA_HL_MDL_CFG *p_mdl_cfg );
/*******************************************************************************
**
** Function        bta_hl_co_delete_mdl
**
** Description     This function is called to delete a MDL configuration item in persistent
**                 storage
**
** Parameters      app_id - HDP application ID
**                 item_idx - the MDL configuration storage index
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_hl_co_delete_mdl(UINT8 app_id, UINT8 item_idx);
/*******************************************************************************
**
** Function         bta_hl_co_get_mdl_config
**
** Description     This function is called to get the MDL configuration
**                 from teh persistent memory. This function shall only be called
*8                 once after the device is powered up
**
** Parameters      app_id - HDP application ID
**                 buffer_size - the unit of the buffer size is sizeof(tBTA_HL_MDL_CFG)
**                 p_mdl_buf - Point to the starting location of the buffer
**
** Returns         BOOLEAN
**
**
*******************************************************************************/
BTA_API extern BOOLEAN bta_hl_co_load_mdl_config (UINT8 app_id, UINT8 buffer_size,
                                                  tBTA_HL_MDL_CFG *p_mdl_buf );


/*******************************************************************************
**
** Function         bta_hl_co_get_tx_data
**
** Description     Get the data to be sent
**
** Parameters      app_id - HDP application ID
**                 mdl_handle - MDL handle
**                 buf_size - the size of the buffer
**                 p_buf - the buffer pointer
**                 evt - the evt to be passed back to the HL in the
**                       bta_hl_ci_get_tx_data call-in function
**
** Returns        Void
**
*******************************************************************************/
BTA_API extern void bta_hl_co_get_tx_data (UINT8 app_id, tBTA_HL_MDL_HANDLE mdl_handle,
                                           UINT16 buf_size, UINT8 *p_buf, UINT16 evt);


/*******************************************************************************
**
** Function        bta_hl_co_put_rx_data
**
** Description     Put the received data
**
** Parameters      app_id - HDP application ID
**                 mdl_handle - MDL handle
**                 data_size - the size of the data
**                 p_data - the data pointer
**                 evt - the evt to be passed back to the HL in the
**                       bta_hl_ci_put_rx_data call-in function
**
** Returns        Void
**
*******************************************************************************/
BTA_API extern void bta_hl_co_put_rx_data (UINT8 app_id, tBTA_HL_MDL_HANDLE mdl_handle,
                                           UINT16 data_size, UINT8 *p_data, UINT16 evt);
/*******************************************************************************
**
** Function         bta_hl_co_get_tx_data
**
** Description     Get the Echo data to be sent
**
** Parameters      app_id - HDP application ID
**                 mcl_handle - MCL handle
**                 buf_size - the size of the buffer
**                 p_buf - the buffer pointer
**                 evt - the evt to be passed back to the HL in the
**                       bta_hl_ci_get_tx_data call-in function
**
** Returns        Void
**
*******************************************************************************/
BTA_API extern void bta_hl_co_get_echo_data (UINT8 app_id, tBTA_HL_MCL_HANDLE mcl_handle,
                                             UINT16 buf_size, UINT8 *p_buf, UINT16 evt);

/*******************************************************************************
**
** Function        bta_hl_co_put_echo_data
**
** Description     Put the received loopback echo data
**
** Parameters      app_id - HDP application ID
**                 mcl_handle - MCL handle
**                 data_size - the size of the data
**                 p_data - the data pointer
**                 evt - the evt to be passed back to the HL in the
**                       bta_hl_ci_put_echo_data call-in function
**
** Returns        Void
**
*******************************************************************************/
BTA_API extern void bta_hl_co_put_echo_data (UINT8 app_id, tBTA_HL_MCL_HANDLE mcl_handle,
                                             UINT16 data_size, UINT8 *p_data, UINT16 evt);

#endif /* BTA_HL_CO_H */
