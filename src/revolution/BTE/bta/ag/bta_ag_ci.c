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
 *  This is the implementation file for audio gateway call-in functions.
 *
 ******************************************************************************/

#include <string.h>
#include "bta_api.h"
#include "bta_ag_api.h"
#include "bta_ag_int.h"
#include "bta_ag_ci.h"
#include "gki.h"

/******************************************************************************
**
** Function         bta_ag_ci_rx_write
**
** Description      This function is called to send data to the AG when the AG
**                  is configured for AT command pass-through.  The function
**                  copies data to an event buffer and sends it.
**
** Returns          void
**
******************************************************************************/
void bta_ag_ci_rx_write(UINT16 handle, char *p_data, UINT16 len)
{
    tBTA_AG_CI_RX_WRITE *p_buf;
    UINT16 len_remaining = len;
    char *p_data_area;

    if (len > (RFCOMM_DATA_POOL_BUF_SIZE - sizeof(tBTA_AG_CI_RX_WRITE) - 1))
        len = RFCOMM_DATA_POOL_BUF_SIZE - sizeof(tBTA_AG_CI_RX_WRITE) - 1;

    while (len_remaining)
    {
        if (len_remaining < len)
            len = len_remaining;

        if ((p_buf = (tBTA_AG_CI_RX_WRITE *) GKI_getbuf((UINT16)(sizeof(tBTA_AG_CI_RX_WRITE) + len + 1))) != NULL)
    {
        p_buf->hdr.event = BTA_AG_CI_RX_WRITE_EVT;
        p_buf->hdr.layer_specific = handle;

        p_data_area = (char *)(p_buf+1);        /* Point to data area after header */
        strncpy(p_data_area, p_data, len);
        p_data_area[len] = 0;

        bta_sys_sendmsg(p_buf);
        } else {
        APPL_TRACE_ERROR1("ERROR: Unable to allocate buffer to hold AT response code. len=%i", len);
            break;
        }

        len_remaining-=len;
        p_data+=len;
    }
}

/******************************************************************************
**
** Function         bta_ag_ci_slc_ready
**
** Description      This function is called to notify AG that SLC is up at
**                  the application. This funcion is only used when the app
**                  is running in pass-through mode.
**
** Returns          void
**
******************************************************************************/
void bta_ag_ci_slc_ready(UINT16 handle)
{
    tBTA_AG_DATA *p_buf;

    if ((p_buf = (tBTA_AG_DATA *)GKI_getbuf(sizeof(tBTA_AG_DATA))) != NULL)
    {
        p_buf->hdr.event = BTA_AG_CI_SLC_READY_EVT;
        p_buf->hdr.layer_specific = handle;
        bta_sys_sendmsg(p_buf);
    }
}
