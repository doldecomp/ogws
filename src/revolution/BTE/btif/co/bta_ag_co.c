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
#include "gki.h"
#include "bta_api.h"
#include "bta_sys.h"
#include "bta_ag_api.h"
#include "bta_ag_co.h"
#include "bte_appl.h"

#define LOG_TAG "BTA_AG_CO: "

#ifndef LINUX_NATIVE
#include <cutils/properties.h>
#include <cutils/log.h>
#else
#include <stdio.h>
#define LOGI(format, ...)  fprintf (stdout, LOG_TAG format"\n", ## __VA_ARGS__)
#define LOGD(format, ...)  fprintf (stdout, LOG_TAG format"\n", ## __VA_ARGS__)
#define LOGV(format, ...)  fprintf (stdout, LOG_TAG format"\n", ## __VA_ARGS__)
#define LOGE(format, ...)  fprintf (stderr, LOG_TAG format"\n", ## __VA_ARGS__)
#endif


/*******************************************************************************
**
** Function         bta_ag_co_init
**
** Description      This callout function is executed by AG when it is
**                  started by calling BTA_AgEnable().  This function can be
**                  used by the phone to initialize audio paths or for other
**                  initialization purposes.
**
**
** Returns          Void.
**
*******************************************************************************/
void bta_ag_co_init(void)
{
    BTM_WriteVoiceSettings(AG_VOICE_SETTINGS);
}


/*******************************************************************************
**
** Function         bta_ag_co_audio_state
**
** Description      This function is called by the AG before the audio connection
**                  is brought up, after it comes up, and after it goes down.
**
** Parameters       handle - handle of the AG instance
**                  state - Audio state
**                      BTA_AG_CO_AUD_STATE_OFF     - Audio has been turned off
**                      BTA_AG_CO_AUD_STATE_OFF_XFER - Audio has been turned off (xfer)
**                      BTA_AG_CO_AUD_STATE_ON      - Audio has been turned on
**                      BTA_AG_CO_AUD_STATE_SETUP   - Audio is about to be turned on
**
** Returns          void
**
*******************************************************************************/
void bta_ag_co_audio_state(UINT16 handle, UINT8 app_id, UINT8 state)
{
    BTIF_TRACE_DEBUG2("bta_ag_co_audio_state: handle %d, state %d", handle, state);
}


/*******************************************************************************
**
** Function         bta_ag_co_data_open
**
** Description      This function is executed by AG when a service level connection
**                  is opened.  The phone can use this function to set
**                  up data paths or perform any required initialization or
**                  set up particular to the connected service.
**
**
** Returns          void
**
*******************************************************************************/
void bta_ag_co_data_open(UINT16 handle, tBTA_SERVICE_ID service)
{
    BTIF_TRACE_DEBUG2("bta_ag_co_data_open handle:%d service:%d", handle, service);
}

/*******************************************************************************
**
** Function         bta_ag_co_data_close
**
** Description      This function is called by AG when a service level
**                  connection is closed
**
**
** Returns          void
**
*******************************************************************************/
void bta_ag_co_data_close(UINT16 handle)
{
    BTIF_TRACE_DEBUG1("bta_ag_co_data_close handle:%d", handle);
}


/*******************************************************************************
 **
 ** Function         bta_ag_co_tx_write
 **
 ** Description      This function is called by the AG to send data to the
 **                  phone when the AG is configured for AT command pass-through.
 **                  The implementation of this function must copy the data to
 **                  the phones memory.
 **
 ** Returns          void
 **
 *******************************************************************************/
void bta_ag_co_tx_write(UINT16 handle, UINT8 * p_data, UINT16 len)
{
   BTIF_TRACE_DEBUG2( "bta_ag_co_tx_write: handle: %d, len: %d", handle, len );
}

