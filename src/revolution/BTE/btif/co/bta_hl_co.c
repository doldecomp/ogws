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
 *  This is the implementation file for the HeaLth device profile (HL)
 *  subsystem call-out functions.
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <fcntl.h>
#include <ctype.h>
#include <cutils/sockets.h>
#include <cutils/log.h>
#include "bta_api.h"
#include "btm_api.h"
#include "bta_sys.h"
#include "bta_hl_api.h"
#include "bta_hl_co.h"
#include "bta_hl_ci.h"
#include "btif_hl.h"



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
BOOLEAN bta_hl_co_get_num_of_mdep(UINT8 app_id, UINT8 *p_num_of_mdep)
{
    UINT8 app_idx;
    BOOLEAN success = FALSE;

    if (btif_hl_find_app_idx(app_id, &app_idx))
    {
        *p_num_of_mdep = p_btif_hl_cb->acb[app_idx].sup_feature.num_of_mdeps;
        success = TRUE;
    }


    BTIF_TRACE_DEBUG3("%s success=%d num_mdeps=%d",
                      __FUNCTION__, success, *p_num_of_mdep );
    return success;
}

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
BOOLEAN bta_hl_co_advrtise_source_sdp(UINT8 app_id)
{
    BOOLEAN     advertize_source_sdp=FALSE;
    UINT8       app_idx;

    if (btif_hl_find_app_idx(app_id, &app_idx))
    {
        advertize_source_sdp = p_btif_hl_cb->acb[app_idx].sup_feature.advertize_source_sdp;
    }


    BTIF_TRACE_DEBUG2("%s advertize_flag=%d", __FUNCTION__, advertize_source_sdp );

    return advertize_source_sdp;
}
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
BOOLEAN bta_hl_co_get_mdep_config(UINT8  app_id,
                                  UINT8 mdep_idx,
                                  tBTA_HL_MDEP_ID mdep_id,
                                  tBTA_HL_MDEP_CFG *p_mdep_cfg)
{
    UINT8       idx  ;
    UINT8       app_idx;
    BOOLEAN     success = FALSE;

    BTIF_TRACE_DEBUG4("%s app_id=%d mdep_idx=%d mdep_id=%d",
                      __FUNCTION__, app_id,mdep_idx,mdep_id );

    if (btif_hl_find_app_idx(app_id, &app_idx))
    {
        idx = mdep_idx -1;
        p_btif_hl_cb->acb[app_idx].sup_feature.mdep[idx].mdep_id = mdep_id;
        memcpy(p_mdep_cfg,
               &p_btif_hl_cb->acb[app_idx].sup_feature.mdep[idx].mdep_cfg,
               sizeof(tBTA_HL_MDEP_CFG));

        success = TRUE;
    }

    BTIF_TRACE_DEBUG4("%s success=%d mdep_idx=%d mdep_id=%d",
                      __FUNCTION__, success, mdep_idx, mdep_id );

    return success;
}


/*******************************************************************************
**
** Function        bta_hl_co_get_echo_config
**
** Description     This function is called to get the echo test
**                 maximum APDU size configurations
**
** Parameters      app_id - HDP application ID
**                 p_echo_cfg (output) - pointer to the Echo test maximum APDU size
**                                       configuration
**
** Returns         Bloolean - TRUE success
*******************************************************************************/
BOOLEAN bta_hl_co_get_echo_config(UINT8  app_id,
                                  tBTA_HL_ECHO_CFG *p_echo_cfg)
{
    UINT8               app_idx;
    BOOLEAN             success = FALSE;
    btif_hl_app_cb_t    *p_acb;
    tBTA_HL_SUP_FEATURE *p_sup;

    BTIF_TRACE_DEBUG2("%s app_id=%d",__FUNCTION__, app_id );

    if (btif_hl_find_app_idx(app_id, &app_idx))
    {
        p_acb = BTIF_HL_GET_APP_CB_PTR(app_idx);
        p_sup = &p_acb->sup_feature;
        p_echo_cfg->max_rx_apdu_size = p_sup->echo_cfg.max_rx_apdu_size;
        p_echo_cfg->max_tx_apdu_size = p_sup->echo_cfg.max_tx_apdu_size;
        success = TRUE;
    }

    BTIF_TRACE_DEBUG4("%s success=%d max tx_size=%d rx_size=%d",
                      __FUNCTION__, success, p_echo_cfg->max_tx_apdu_size,
                      p_echo_cfg->max_rx_apdu_size );

    return success;
}


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
** Returns        void
**
*******************************************************************************/
void bta_hl_co_save_mdl(UINT8 app_id, UINT8 item_idx, tBTA_HL_MDL_CFG *p_mdl_cfg )
{

    BTIF_TRACE_DEBUG6("%s app_id=%d, item_idx=%d active=%d mdl_id=%d time=%d",
                      __FUNCTION__, app_id, item_idx,
                      p_mdl_cfg->active,
                      p_mdl_cfg->mdl_id,
                      p_mdl_cfg->time);


    btif_hl_save_mdl_cfg(app_id, item_idx, p_mdl_cfg);

}

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
void bta_hl_co_delete_mdl(UINT8 app_id, UINT8 item_idx)
{


    BTIF_TRACE_DEBUG3("%s app_id=%d, item_idx=%d", __FUNCTION__, app_id, item_idx);

    btif_hl_delete_mdl_cfg(app_id, item_idx);


}

/*******************************************************************************
**
** Function         bta_hl_co_get_mdl_config
**
** Description     This function is called to get the MDL configuration
**                 from the persistent memory. This function shall only be called
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
BOOLEAN bta_hl_co_load_mdl_config (UINT8 app_id, UINT8 buffer_size,
                                   tBTA_HL_MDL_CFG *p_mdl_buf )
{
    BOOLEAN result = TRUE;
    UINT8 i;
    tBTA_HL_MDL_CFG *p;

    BTIF_TRACE_DEBUG3("%s app_id=%d, num_items=%d",
                      __FUNCTION__, app_id, buffer_size);

    if (buffer_size > BTA_HL_NUM_MDL_CFGS)
    {
        result = FALSE;
        return result;
    }
    result = btif_hl_load_mdl_config(app_id, buffer_size, p_mdl_buf);

    if (result)
    {
        for (i=0, p=p_mdl_buf; i<buffer_size; i++, p++ )
        {
            if (p->active)
            {
                BTIF_TRACE_DEBUG6("i=%d mdl_id=0x%x dch_mode=%d local mdep_role=%d mdep_id=%d mtu=%d",
                                  i, p->mdl_id, p->dch_mode, p->local_mdep_role, p->local_mdep_role, p->mtu);
            }
        }
    }

    BTIF_TRACE_DEBUG3("%s success=%d num_items=%d", __FUNCTION__, result, buffer_size);

    return result;
}

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
void bta_hl_co_get_tx_data (UINT8 app_id, tBTA_HL_MDL_HANDLE mdl_handle,
                            UINT16 buf_size, UINT8 *p_buf,  UINT16 evt)
{
    UINT8 app_idx, mcl_idx, mdl_idx;
    btif_hl_mdl_cb_t *p_dcb;
    tBTA_HL_STATUS status = BTA_HL_STATUS_FAIL;

    BTIF_TRACE_DEBUG4("%s app_id=%d mdl_handle=0x%x buf_size=%d",
                      __FUNCTION__, app_id, mdl_handle, buf_size);

    if (btif_hl_find_mdl_idx_using_handle(mdl_handle, &app_idx, &mcl_idx, &mdl_idx))
    {
        p_dcb = BTIF_HL_GET_MDL_CB_PTR(app_idx, mcl_idx, mdl_idx);

        if (p_dcb->tx_size <= buf_size )
        {
            memcpy(p_buf, p_dcb->p_tx_pkt, p_dcb->tx_size);
            btif_hl_free_buf((void **) &p_dcb->p_tx_pkt);
            p_dcb->tx_size = 0;
            status = BTA_HL_STATUS_OK;
        }
    }


    bta_hl_ci_get_tx_data(mdl_handle,  status, evt);

}


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
void bta_hl_co_put_rx_data (UINT8 app_id, tBTA_HL_MDL_HANDLE mdl_handle,
                            UINT16 data_size, UINT8 *p_data, UINT16 evt)
{
    UINT8 app_idx, mcl_idx, mdl_idx;
    btif_hl_mdl_cb_t *p_dcb;
    tBTA_HL_STATUS status = BTA_HL_STATUS_FAIL;
    int            r;
    BTIF_TRACE_DEBUG4("%s app_id=%d mdl_handle=0x%x data_size=%d",
                      __FUNCTION__,app_id, mdl_handle, data_size);

    if (btif_hl_find_mdl_idx_using_handle(mdl_handle, &app_idx, &mcl_idx, &mdl_idx))
    {
        p_dcb = BTIF_HL_GET_MDL_CB_PTR(app_idx, mcl_idx, mdl_idx);

        if ((p_dcb->p_rx_pkt = (UINT8 *)btif_hl_get_buf(data_size)) != NULL)
        {
            memcpy(p_dcb->p_rx_pkt, p_data, data_size);
            if (p_dcb->p_scb)
            {
                BTIF_TRACE_DEBUG4("app_idx=%d mcl_idx=0x%x mdl_idx=0x%x data_size=%d",
                                  app_idx, mcl_idx, mdl_idx, data_size);
                r = send(p_dcb->p_scb->socket_id[1], p_dcb->p_rx_pkt, data_size, 0);

                if (r == data_size)
                {
                    BTIF_TRACE_DEBUG1("socket send success data_size=%d",  data_size);
                    status = BTA_HL_STATUS_OK;
                }
                else
                {
                    BTIF_TRACE_ERROR2("socket send failed r=%d data_size=%d",r, data_size);
                }


            }
            btif_hl_free_buf((void **) &p_dcb->p_rx_pkt);
        }
    }

    bta_hl_ci_put_rx_data(mdl_handle,  status, evt);
}


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
void bta_hl_co_get_echo_data (UINT8 app_id, tBTA_HL_MCL_HANDLE mcl_handle,
                              UINT16 buf_size, UINT8 *p_buf,  UINT16 evt)
{
    tBTA_HL_STATUS status = BTA_HL_STATUS_FAIL;

    BTIF_TRACE_ERROR1("%s not supported",__FUNCTION__);
    bta_hl_ci_get_echo_data(mcl_handle,  status, evt);
}


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
void bta_hl_co_put_echo_data (UINT8 app_id, tBTA_HL_MCL_HANDLE mcl_handle,
                              UINT16 data_size, UINT8 *p_data, UINT16 evt)
{
    tBTA_HL_STATUS status = BTA_HL_STATUS_FAIL;

    BTIF_TRACE_ERROR1("%s not supported",__FUNCTION__);
    bta_hl_ci_put_echo_data(mcl_handle,  status, evt);
}

