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
 *  This is the API implementation file for the BTA device manager.
 *
 ******************************************************************************/

#include "gki.h"
#include "bd.h"
#include "bta_sys.h"
#include "bta_api.h"
#include "bta_dm_int.h"
#include "bta_sys_int.h"
#include "btm_api.h"
#include "btm_int.h"
#include <string.h>

/*****************************************************************************
**  Constants
*****************************************************************************/

static const tBTA_SYS_REG bta_dm_reg =
{
    bta_dm_sm_execute,
    bta_dm_sm_disable
};

static const tBTA_SYS_REG bta_dm_search_reg =
{
    bta_dm_search_sm_execute,
    bta_dm_search_sm_disable
};

/*******************************************************************************
**
** Function         BTA_EnableBluetooth
**
** Description      Enables bluetooth service.  This function must be
**                  called before any other functions in the BTA API are called.
**
**
** Returns          tBTA_STATUS
**
*******************************************************************************/
tBTA_STATUS BTA_EnableBluetooth(tBTA_DM_SEC_CBACK *p_cback)
{

    tBTA_DM_API_ENABLE    *p_msg;

    /* Bluetooth disabling is in progress */
    if (bta_dm_cb.disabling)
        return BTA_FAILURE;

    memset(&bta_dm_cb, 0, sizeof(bta_dm_cb));

    GKI_sched_lock();
    bta_sys_register (BTA_ID_DM, &bta_dm_reg );
    bta_sys_register (BTA_ID_DM_SEARCH, &bta_dm_search_reg );

    /* if UUID list is not provided as static data */
    bta_sys_eir_register(bta_dm_eir_update_uuid);

    GKI_sched_unlock();

    if ((p_msg = (tBTA_DM_API_ENABLE *) GKI_getbuf(sizeof(tBTA_DM_API_ENABLE))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_ENABLE_EVT;
        p_msg->p_sec_cback = p_cback;
        bta_sys_sendmsg(p_msg);
        return BTA_SUCCESS;
    }
    return BTA_FAILURE;

}

/*******************************************************************************
**
** Function         BTA_DisableBluetooth
**
** Description      Disables bluetooth service.  This function is called when
**                  the application no longer needs bluetooth service
**
** Returns          void
**
*******************************************************************************/
tBTA_STATUS BTA_DisableBluetooth(void)
{

    BT_HDR    *p_msg;

    if ((p_msg = (BT_HDR *) GKI_getbuf(sizeof(BT_HDR))) != NULL)
    {
        p_msg->event = BTA_DM_API_DISABLE_EVT;
        bta_sys_sendmsg(p_msg);
    }
    else
    {
        return BTA_FAILURE;
    }

    return BTA_SUCCESS;
}

/*******************************************************************************
**
** Function         BTA_EnableTestMode
**
** Description      Enables bluetooth device under test mode
**
**
** Returns          tBTA_STATUS
**
*******************************************************************************/
tBTA_STATUS BTA_EnableTestMode(void)
{
    BT_HDR    *p_msg;

    APPL_TRACE_API0("BTA_EnableTestMode");

    if ((p_msg = (BT_HDR *) GKI_getbuf(sizeof(BT_HDR))) != NULL)
    {
        p_msg->event = BTA_DM_API_ENABLE_TEST_MODE_EVT;
        bta_sys_sendmsg(p_msg);
        return BTA_SUCCESS;
    }
    return BTA_FAILURE;
}

/*******************************************************************************
**
** Function         BTA_DisableTestMode
**
** Description      Disable bluetooth device under test mode
**
**
** Returns          None
**
*******************************************************************************/
void BTA_DisableTestMode(void)
{
    BT_HDR    *p_msg;

    APPL_TRACE_API0("BTA_DisableTestMode");

    if ((p_msg = (BT_HDR *) GKI_getbuf(sizeof(BT_HDR))) != NULL)
    {
        p_msg->event = BTA_DM_API_DISABLE_TEST_MODE_EVT;
        bta_sys_sendmsg(p_msg);
    }
}

/*******************************************************************************
**
** Function         BTA_DmIsDeviceUp
**
** Description      Called during startup to check whether the bluetooth module
**                  is up and ready
**
** Returns          BOOLEAN
**
*******************************************************************************/
BOOLEAN BTA_DmIsDeviceUp(void)
{

    BOOLEAN status;

    GKI_sched_lock();
    status = BTM_IsDeviceUp();
    GKI_sched_unlock();
    return status;

}

/*******************************************************************************
**
** Function         BTA_DmSetDeviceName
**
** Description      This function sets the Bluetooth name of local device
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmSetDeviceName(char *p_name)
{

    tBTA_DM_API_SET_NAME    *p_msg;

    if ((p_msg = (tBTA_DM_API_SET_NAME *) GKI_getbuf(sizeof(tBTA_DM_API_SET_NAME))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_SET_NAME_EVT;
        /* truncate the name if needed */
        BCM_STRNCPY_S(p_msg->name, sizeof(p_msg->name), p_name, BD_NAME_LEN-1);
        p_msg->name[BD_NAME_LEN-1]=0;

        bta_sys_sendmsg(p_msg);
    }


}

/*******************************************************************************
**
** Function         BTA_DmSetVisibility
**
** Description      This function sets the Bluetooth connectable,
**                  discoverable, pairable and conn paired only modes of local device
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmSetVisibility(tBTA_DM_DISC disc_mode, tBTA_DM_CONN conn_mode, UINT8 pairable_mode, UINT8 conn_filter )
{

    tBTA_DM_API_SET_VISIBILITY    *p_msg;

    if ((p_msg = (tBTA_DM_API_SET_VISIBILITY *) GKI_getbuf(sizeof(tBTA_DM_MSG))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_SET_VISIBILITY_EVT;
        p_msg->disc_mode = disc_mode;
        p_msg->conn_mode = conn_mode;
        p_msg->pair_mode = pairable_mode;
        p_msg->conn_paired_only = conn_filter;


        bta_sys_sendmsg(p_msg);
    }


}

/*******************************************************************************
**
** Function         BTA_DmSetScanParam
**
** Description      This function sets the parameters for page scan and
**                  inquiry scan.
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmSetScanParam (UINT16 page_scan_interval, UINT16 page_scan_window,
                                  UINT16 inquiry_scan_interval, UINT16 inquiry_scan_window)
{
    APPL_TRACE_API4 ("BTA_DmSetScanParam: %d, %d, %d, %d",
            page_scan_interval, page_scan_window,
            inquiry_scan_interval, inquiry_scan_window);

    bta_dm_cb.page_scan_interval = page_scan_interval;
    bta_dm_cb.page_scan_window = page_scan_window;
    bta_dm_cb.inquiry_scan_interval = inquiry_scan_interval;
    bta_dm_cb.inquiry_scan_window = inquiry_scan_window;
}

/*******************************************************************************
**
** Function         BTA_DmSetAfhChannels
**
** Description      This function sets the AFH first and
**                  last disable channel, so channels within
**                  that range are disabled.
**
** Returns          void
**
*******************************************************************************/
void BTA_DmSetAfhChannels(UINT8 first, UINT8 last)
{

    tBTA_DM_API_SET_AFH_CHANNELS_EVT    *p_msg;

    if ((p_msg = (tBTA_DM_API_SET_AFH_CHANNELS_EVT *) GKI_getbuf(sizeof(tBTA_DM_MSG))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_SET_AFH_CHANNELS_EVT;
        p_msg->first = first;
        p_msg->last = last;
        bta_sys_sendmsg(p_msg);
    }


}

/*******************************************************************************
**
** Function         BTA_SetAfhChannelAssessment
**
** Description      This function is called to set the channel assessment mode on or off
**
** Returns          status
**
*******************************************************************************/
void BTA_DmSetAfhChannelAssessment (BOOLEAN enable_or_disable)
{
    tBTA_DM_API_SET_AFH_CHANNEL_ASSESSMENT *p_msg;

    if ((p_msg = (tBTA_DM_API_SET_AFH_CHANNEL_ASSESSMENT *) GKI_getbuf(sizeof(tBTA_DM_API_SET_AFH_CHANNEL_ASSESSMENT))) != NULL)
    {
        p_msg->hdr.event    = BTA_DM_API_SET_AFH_CHANNEL_ASSESMENT_EVT;
        p_msg->enable_or_disable = enable_or_disable;
        bta_sys_sendmsg(p_msg);
    }
}

/*******************************************************************************
**
** Function         BTA_DmVendorSpecificCommand
**
** Description      This function sends the vendor specific command
**                  to the controller
**
**
** Returns          tBTA_STATUS
**
*******************************************************************************/
tBTA_STATUS BTA_DmVendorSpecificCommand (UINT16 opcode, UINT8 param_len,
                                         UINT8 *p_param_buf,
                                         tBTA_VENDOR_CMPL_CBACK *p_cback)
{

    tBTA_DM_API_VENDOR_SPECIFIC_COMMAND    *p_msg;
    UINT16 size;

    /* If p_cback is NULL, Notify application */
    if (p_cback == NULL)
    {
        return (BTA_FAILURE);
    }
    else
    {
        size = sizeof (tBTA_DM_API_VENDOR_SPECIFIC_COMMAND) + param_len;
        if ((p_msg = (tBTA_DM_API_VENDOR_SPECIFIC_COMMAND *) GKI_getbuf(size)) != NULL)
        {
            p_msg->hdr.event = BTA_DM_API_VENDOR_SPECIFIC_COMMAND_EVT;
            p_msg->opcode = opcode;
            p_msg->param_len = param_len;
            p_msg->p_param_buf = (UINT8 *)(p_msg + 1);
            p_msg->p_cback = p_cback;

            memcpy (p_msg->p_param_buf, p_param_buf, param_len);

            bta_sys_sendmsg(p_msg);
        }
        return (BTA_SUCCESS);
    }
}
/*******************************************************************************
**
** Function         BTA_DmSearch
**
** Description      This function searches for peer Bluetooth devices. It performs
**                  an inquiry and gets the remote name for devices. Service
**                  discovery is done if services is non zero
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmSearch(tBTA_DM_INQ *p_dm_inq, tBTA_SERVICE_MASK services, tBTA_DM_SEARCH_CBACK *p_cback)
{

    tBTA_DM_API_SEARCH    *p_msg;

    if ((p_msg = (tBTA_DM_API_SEARCH *) GKI_getbuf(sizeof(tBTA_DM_API_SEARCH))) != NULL)
    {
        memset(p_msg, 0, sizeof(tBTA_DM_API_SEARCH));

        p_msg->hdr.event = BTA_DM_API_SEARCH_EVT;
        memcpy(&p_msg->inq_params, p_dm_inq, sizeof(tBTA_DM_INQ));
        p_msg->services = services;
        p_msg->p_cback = p_cback;
        p_msg->rs_res  = BTA_DM_RS_NONE;
        bta_sys_sendmsg(p_msg);
    }

}


/*******************************************************************************
**
** Function         BTA_DmSearchCancel
**
** Description      This function  cancels a search initiated by BTA_DmSearch
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmSearchCancel(void)
{
    BT_HDR    *p_msg;

    if ((p_msg = (BT_HDR *) GKI_getbuf(sizeof(BT_HDR))) != NULL)
    {
        p_msg->event = BTA_DM_API_SEARCH_CANCEL_EVT;
        bta_sys_sendmsg(p_msg);
    }

}

/*******************************************************************************
**
** Function         BTA_DmDiscover
**
** Description      This function does service discovery for services of a
**                  peer device
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmDiscover(BD_ADDR bd_addr, tBTA_SERVICE_MASK services,
                    tBTA_DM_SEARCH_CBACK *p_cback, BOOLEAN sdp_search)
{
    tBTA_DM_API_DISCOVER    *p_msg;

    if ((p_msg = (tBTA_DM_API_DISCOVER *) GKI_getbuf(sizeof(tBTA_DM_API_DISCOVER))) != NULL)
    {
        memset(p_msg, 0, sizeof(tBTA_DM_API_DISCOVER));

        p_msg->hdr.event = BTA_DM_API_DISCOVER_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->services = services;
        p_msg->p_cback = p_cback;
        p_msg->sdp_search = sdp_search;
        bta_sys_sendmsg(p_msg);
    }

}

/*******************************************************************************
**
** Function         BTA_DmDiscoverUUID
**
** Description      This function does service discovery for services of a
**                  peer device
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmDiscoverUUID(BD_ADDR bd_addr, tSDP_UUID *uuid,
                    tBTA_DM_SEARCH_CBACK *p_cback, BOOLEAN sdp_search)
{
    tBTA_DM_API_DISCOVER    *p_msg;

    if ((p_msg = (tBTA_DM_API_DISCOVER *) GKI_getbuf(sizeof(tBTA_DM_API_DISCOVER))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_DISCOVER_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->services = BTA_USER_SERVICE_MASK; //Not exposed at API level
        p_msg->p_cback = p_cback;
        p_msg->sdp_search = sdp_search;

#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
        p_msg->num_uuid = 0;
        p_msg->p_uuid = NULL;
#endif
        memcpy( &p_msg->uuid, uuid, sizeof(tSDP_UUID) );
        bta_sys_sendmsg(p_msg);
    }

}
/*******************************************************************************
**
** Function         BTA_DmIsMaster
**
** Description      This function checks if the local device is the master of
**                  the link to the given device
**
** Returns          TRUE if master.
**                  FALSE if not.
**
*******************************************************************************/
BOOLEAN BTA_DmIsMaster(BD_ADDR bd_addr)
{
    BOOLEAN is_master = FALSE;
    UINT8 link_role;

    BTM_GetRole(bd_addr, &link_role);
    APPL_TRACE_API1("BTA_DmIsMaster role:x%x", link_role);
    if(link_role == BTM_ROLE_MASTER)
    {
        is_master = TRUE;
    }
    return is_master;
}

/*******************************************************************************
**
** Function         BTA_DmBond
**
** Description      This function initiates a bonding procedure with a peer
**                  device
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmBond(BD_ADDR bd_addr)
{
    tBTA_DM_API_BOND    *p_msg;

    if ((p_msg = (tBTA_DM_API_BOND *) GKI_getbuf(sizeof(tBTA_DM_API_BOND))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_BOND_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        bta_sys_sendmsg(p_msg);
    }


}

/*******************************************************************************
**
** Function         BTA_DmBondCancel
**
** Description      This function cancels the bonding procedure with a peer
**                  device
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmBondCancel(BD_ADDR bd_addr)
{
    tBTA_DM_API_BOND_CANCEL    *p_msg;

    if ((p_msg = (tBTA_DM_API_BOND_CANCEL *) GKI_getbuf(sizeof(tBTA_DM_API_BOND_CANCEL))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_BOND_CANCEL_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        bta_sys_sendmsg(p_msg);
    }


}

/*******************************************************************************
**
** Function         BTA_DmPinReply
**
** Description      This function provides a pincode for a remote device when
**                  one is requested by DM through BTA_DM_PIN_REQ_EVT
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmPinReply(BD_ADDR bd_addr, BOOLEAN accept, UINT8 pin_len, UINT8 *p_pin)

{
    tBTA_DM_API_PIN_REPLY    *p_msg;

    if ((p_msg = (tBTA_DM_API_PIN_REPLY *) GKI_getbuf(sizeof(tBTA_DM_API_PIN_REPLY))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_PIN_REPLY_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->accept = accept;
        if(accept)
        {
            p_msg->pin_len = pin_len;
            memcpy(p_msg->p_pin, p_pin, pin_len);
        }
        bta_sys_sendmsg(p_msg);
    }

}

/*******************************************************************************
**
** Function         BTA_DmLinkPolicy
**
** Description      This function sets/clears the link policy mask to the given
**                  bd_addr.
**                  If clearing the sniff or park mode mask, the link is put
**                  in active mode.
**
** Returns          void
**
*******************************************************************************/
void BTA_DmLinkPolicy(BD_ADDR bd_addr, tBTA_DM_LP_MASK policy_mask,
                      BOOLEAN set)
{
    tBTA_DM_API_LINK_POLICY    *p_msg;

    if ((p_msg = (tBTA_DM_API_LINK_POLICY *) GKI_getbuf(sizeof(tBTA_DM_API_LINK_POLICY))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_LINK_POLICY_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->policy_mask = policy_mask;
        p_msg->set = set;
        bta_sys_sendmsg(p_msg);
    }
}


#if (BTM_OOB_INCLUDED == TRUE)
/*******************************************************************************
**
** Function         BTA_DmLocalOob
**
** Description      This function retrieves the OOB data from local controller.
**                  The result is reported by bta_dm_co_loc_oob().
**
** Returns          void
**
*******************************************************************************/
void BTA_DmLocalOob(void)
{
    tBTA_DM_API_LOC_OOB    *p_msg;

    if ((p_msg = (tBTA_DM_API_LOC_OOB *) GKI_getbuf(sizeof(tBTA_DM_API_LOC_OOB))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_LOC_OOB_EVT;
        bta_sys_sendmsg(p_msg);
    }
}
#endif /* BTM_OOB_INCLUDED */
/*******************************************************************************
**
** Function         BTA_DmConfirm
**
** Description      This function accepts or rejects the numerical value of the
**                  Simple Pairing process on BTA_DM_SP_CFM_REQ_EVT
**
** Returns          void
**
*******************************************************************************/
void BTA_DmConfirm(BD_ADDR bd_addr, BOOLEAN accept)
{
    tBTA_DM_API_CONFIRM    *p_msg;

    if ((p_msg = (tBTA_DM_API_CONFIRM *) GKI_getbuf(sizeof(tBTA_DM_API_CONFIRM))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_CONFIRM_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->accept = accept;
        bta_sys_sendmsg(p_msg);
    }
}

/*******************************************************************************
**
** Function         BTA_DmPasskeyCancel
**
** Description      This function is called to cancel the simple pairing process
**                  reported by BTA_DM_SP_KEY_NOTIF_EVT
**
** Returns          void
**
*******************************************************************************/
#if (BTM_LOCAL_IO_CAPS != BTM_IO_CAP_NONE)
void BTA_DmPasskeyCancel(BD_ADDR bd_addr)
{
    tBTA_DM_API_PASKY_CANCEL    *p_msg;

    if ((p_msg = (tBTA_DM_API_PASKY_CANCEL *) \
        GKI_getbuf(sizeof(tBTA_DM_API_PASKY_CANCEL))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_PASKY_CANCEL_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        bta_sys_sendmsg(p_msg);
    }
}
#endif


/*******************************************************************************
**
** Function         BTA_DmAddDevice
**
** Description      This function adds a device to the security database list of
**                  peer device
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmAddDevice(BD_ADDR bd_addr, DEV_CLASS dev_class, LINK_KEY link_key,
                     tBTA_SERVICE_MASK trusted_mask, BOOLEAN is_trusted,
                     UINT8 key_type, tBTA_IO_CAP io_cap)
{

    tBTA_DM_API_ADD_DEVICE *p_msg;

    if ((p_msg = (tBTA_DM_API_ADD_DEVICE *) GKI_getbuf(sizeof(tBTA_DM_API_ADD_DEVICE))) != NULL)
    {
        memset (p_msg, 0, sizeof(tBTA_DM_API_ADD_DEVICE));

        p_msg->hdr.event = BTA_DM_API_ADD_DEVICE_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->tm = trusted_mask;
        p_msg->is_trusted = is_trusted;
        p_msg->io_cap = io_cap;

        if (link_key)
        {
            p_msg->link_key_known = TRUE;
            p_msg->key_type = key_type;
            memcpy(p_msg->link_key, link_key, LINK_KEY_LEN);
        }

        /* Load device class if specified */
        if (dev_class)
        {
            p_msg->dc_known = TRUE;
            memcpy (p_msg->dc, dev_class, DEV_CLASS_LEN);
        }

        memset (p_msg->bd_name, 0, BD_NAME_LEN);
        memset (p_msg->features, 0, BD_FEATURES_LEN);

        bta_sys_sendmsg(p_msg);
    }
}


/*******************************************************************************
**
** Function         BTA_DmRemoveDevice
**
** Description      This function removes a device fromthe security database list of
**                  peer device
**
**
** Returns          void
**
*******************************************************************************/
tBTA_STATUS BTA_DmRemoveDevice(BD_ADDR bd_addr)
{
    tBTA_DM_API_REMOVE_DEVICE *p_msg;

    if ((p_msg = (tBTA_DM_API_REMOVE_DEVICE *) GKI_getbuf(sizeof(tBTA_DM_API_REMOVE_DEVICE))) != NULL)
    {
        memset (p_msg, 0, sizeof(tBTA_DM_API_REMOVE_DEVICE));

        p_msg->hdr.event = BTA_DM_API_REMOVE_DEVICE_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        bta_sys_sendmsg(p_msg);
    }
    else
    {
        return BTA_FAILURE;
    }

    return BTA_SUCCESS;
}

/*******************************************************************************
**
** Function         BTA_DmAddDevWithName
**
** Description      This function is newer version of  BTA_DmAddDevice()
**                  which added bd_name and features as input parameters.
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmAddDevWithName (BD_ADDR bd_addr, DEV_CLASS dev_class,
                                      BD_NAME bd_name, BD_FEATURES features,
                                      LINK_KEY link_key, tBTA_SERVICE_MASK trusted_mask,
                                      BOOLEAN is_trusted, UINT8 key_type, tBTA_IO_CAP io_cap)
{
    tBTA_DM_API_ADD_DEVICE *p_msg;

    if ((p_msg = (tBTA_DM_API_ADD_DEVICE *) GKI_getbuf(sizeof(tBTA_DM_API_ADD_DEVICE))) != NULL)
    {
        memset (p_msg, 0, sizeof(tBTA_DM_API_ADD_DEVICE));

        p_msg->hdr.event = BTA_DM_API_ADD_DEVICE_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->tm = trusted_mask;
        p_msg->is_trusted = is_trusted;
        p_msg->io_cap = io_cap;

        if (link_key)
        {
            p_msg->link_key_known = TRUE;
            p_msg->key_type = key_type;
            memcpy(p_msg->link_key, link_key, LINK_KEY_LEN);
        }

        /* Load device class if specified */
        if (dev_class)
        {
            p_msg->dc_known = TRUE;
            memcpy (p_msg->dc, dev_class, DEV_CLASS_LEN);
        }

        if (bd_name)
            memcpy(p_msg->bd_name, bd_name, BD_NAME_LEN);

        if (features)
            memcpy(p_msg->features, features, BD_FEATURES_LEN);

        bta_sys_sendmsg(p_msg);
    }
}

/*******************************************************************************
**
** Function         BTA_DmAuthorizeReply
**
** Description      This function provides an authorization reply when authorization
**                  is requested by BTA through BTA_DM_AUTHORIZE_EVT
**
**
** Returns          tBTA_STATUS
**
*******************************************************************************/
void BTA_DmAuthorizeReply(BD_ADDR bd_addr, tBTA_SERVICE_ID service, tBTA_AUTH_RESP response)
{

    tBTA_DM_API_AUTH_REPLY    *p_msg;

    if ((p_msg = (tBTA_DM_API_AUTH_REPLY *) GKI_getbuf(sizeof(tBTA_DM_API_AUTH_REPLY))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_AUTH_REPLY_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->service = service;
        p_msg->response = response;

        bta_sys_sendmsg(p_msg);
    }

}

/*******************************************************************************
**
** Function         BTA_DmSignalStrength
**
** Description      This function initiates RSSI and channnel quality
**                  measurments. BTA_DM_SIG_STRENGTH_EVT is sent to
**                  application with the values of RSSI and channel
**                  quality
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmSignalStrength(tBTA_SIG_STRENGTH_MASK mask, UINT16 period, BOOLEAN start)
{

    tBTA_API_DM_SIG_STRENGTH    *p_msg;

    if ((p_msg = (tBTA_API_DM_SIG_STRENGTH *) GKI_getbuf(sizeof(tBTA_API_DM_SIG_STRENGTH))) != NULL)
    {
        p_msg->hdr.event = BTA_API_DM_SIG_STRENGTH_EVT;
        p_msg->mask = mask;
        p_msg->period = period;
        p_msg->start = start;

        bta_sys_sendmsg(p_msg);
    }


}

/*******************************************************************************
**
** Function         BTA_DmWriteInqTxPower
**
** Description      This command is used to write the inquiry transmit power level
**                  used to transmit the inquiry (ID) data packets.
**
** Parameters       tx_power - tx inquiry power to use, valid value is -70 ~ 20

** Returns          void
**
*******************************************************************************/
void BTA_DmWriteInqTxPower(INT8 tx_power)
{

    tBTA_API_DM_TX_INQPWR    *p_msg;

    if ((p_msg = (tBTA_API_DM_TX_INQPWR *) GKI_getbuf(sizeof(tBTA_API_DM_TX_INQPWR))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_TX_INQPWR_EVT;
        p_msg->tx_power = tx_power;

        bta_sys_sendmsg(p_msg);
    }
}


/*******************************************************************************
**
** Function         BTA_DmEirAddUUID
**
** Description      This function is called to add UUID into EIR.
**
** Parameters       tBT_UUID - UUID
**
** Returns          None
**
*******************************************************************************/
void BTA_DmEirAddUUID (tBT_UUID *p_uuid)
{
#if ( BTM_EIR_SERVER_INCLUDED == TRUE )&&( BTA_EIR_CANNED_UUID_LIST != TRUE )&&(BTA_EIR_SERVER_NUM_CUSTOM_UUID > 0)
    tBTA_DM_API_UPDATE_EIR_UUID    *p_msg;

    if ((p_msg = (tBTA_DM_API_UPDATE_EIR_UUID *) GKI_getbuf(sizeof(tBTA_DM_API_UPDATE_EIR_UUID))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_UPDATE_EIR_UUID_EVT;
        p_msg->is_add    = TRUE;
        memcpy (&(p_msg->uuid), p_uuid, sizeof(tBT_UUID));

        bta_sys_sendmsg(p_msg);
    }
#endif
}

/*******************************************************************************
**
** Function         BTA_DmEirRemoveUUID
**
** Description      This function is called to remove UUID from EIR.
**
** Parameters       tBT_UUID - UUID
**
** Returns          None
**
*******************************************************************************/
void BTA_DmEirRemoveUUID (tBT_UUID *p_uuid)
{
#if ( BTM_EIR_SERVER_INCLUDED == TRUE )&&( BTA_EIR_CANNED_UUID_LIST != TRUE )&&(BTA_EIR_SERVER_NUM_CUSTOM_UUID > 0)
    tBTA_DM_API_UPDATE_EIR_UUID    *p_msg;

    if ((p_msg = (tBTA_DM_API_UPDATE_EIR_UUID *) GKI_getbuf(sizeof(tBTA_DM_API_UPDATE_EIR_UUID))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_UPDATE_EIR_UUID_EVT;
        p_msg->is_add    = FALSE;
        memcpy (&(p_msg->uuid), p_uuid, sizeof(tBT_UUID));

        bta_sys_sendmsg(p_msg);
    }
#endif
}

/*******************************************************************************
**
** Function         BTA_DmSetEIRConfig
**
** Description      This function is called to override the BTA default EIR parameters.
**                  This funciton is only valid in a system where BTU & App task
**                  are in the same memory space.
**
** Parameters       Pointer to User defined EIR config
**
** Returns          None
**
*******************************************************************************/
void BTA_DmSetEIRConfig (tBTA_DM_EIR_CONF *p_eir_cfg)
{
#if (BTM_EIR_SERVER_INCLUDED == TRUE)
    tBTA_DM_API_SET_EIR_CONFIG  *p_msg;

    if ((p_msg = (tBTA_DM_API_SET_EIR_CONFIG *) GKI_getbuf(sizeof(tBTA_DM_API_SET_EIR_CONFIG))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_SET_EIR_CONFIG_EVT;
        p_msg->p_eir_cfg = p_eir_cfg;

        bta_sys_sendmsg(p_msg);
    }
#endif
}

/*******************************************************************************
**
** Function         BTA_CheckEirData
**
** Description      This function is called to get EIR data from significant part.
**
** Parameters       p_eir - pointer of EIR significant part
**                  type   - finding EIR data type
**                  p_length - return the length of EIR data
**
** Returns          pointer of EIR data
**
*******************************************************************************/
UINT8 *BTA_CheckEirData( UINT8 *p_eir, UINT8 type, UINT8 *p_length )
{
#if ( BTM_EIR_CLIENT_INCLUDED == TRUE )
    return BTM_CheckEirData( p_eir, type, p_length );
#else
    return NULL;
#endif
}

/*******************************************************************************
**
** Function         BTA_GetEirService
**
** Description      This function is called to get BTA service mask from EIR.
**
** Parameters       p_eir - pointer of EIR significant part
**                  p_services - return the BTA service mask
**
** Returns          None
**
*******************************************************************************/
extern const UINT16 bta_service_id_to_uuid_lkup_tbl [];
void BTA_GetEirService( UINT8 *p_eir, tBTA_SERVICE_MASK *p_services )
{
#if ( BTM_EIR_CLIENT_INCLUDED == TRUE )
    UINT8 xx, yy;
    UINT8 num_uuid, max_num_uuid = 32;
    UINT8 uuid_list[32*LEN_UUID_16];
    UINT16 *p_uuid16 = (UINT16 *)uuid_list;
    tBTA_SERVICE_MASK mask;

    BTM_GetEirUuidList( p_eir, LEN_UUID_16, &num_uuid, uuid_list, max_num_uuid);
    for( xx = 0; xx < num_uuid; xx++ )
    {
        mask = 1;
        for( yy = 0; yy < BTA_MAX_SERVICE_ID; yy++ )
        {
            if( *(p_uuid16 + xx) == bta_service_id_to_uuid_lkup_tbl[yy] )
            {
                *p_services |= mask;
                break;
            }
            mask <<= 1;
        }

        /* for HSP v1.2 only device */
        if (*(p_uuid16 + xx) == UUID_SERVCLASS_HEADSET_HS)
            *p_services |= BTA_HSP_SERVICE_MASK;

       if (*(p_uuid16 + xx) == UUID_SERVCLASS_HDP_SOURCE)
            *p_services |= BTA_HL_SERVICE_MASK;

        if (*(p_uuid16 + xx) == UUID_SERVCLASS_HDP_SINK)
            *p_services |= BTA_HL_SERVICE_MASK;
    }
#endif
}

/*******************************************************************************
**
** Function         BTA_DmUseSsr
**
** Description      This function is called to check if the connected peer device
**                  supports SSR or not.
**
** Returns          TRUE, if SSR is supported
**
*******************************************************************************/
BOOLEAN BTA_DmUseSsr( BD_ADDR bd_addr )
{
    BOOLEAN use_ssr = FALSE;
    tBTA_DM_PEER_DEVICE * p_dev = bta_dm_find_peer_device(bd_addr);
    if(p_dev && (p_dev->info & BTA_DM_DI_USE_SSR) )
        use_ssr = TRUE;
    return use_ssr;
}

/*******************************************************************************
**                   Device Identification (DI) Server Functions
*******************************************************************************/
/*******************************************************************************
**
** Function         BTA_DmSetLocalDiRecord
**
** Description      This function adds a DI record to the local SDP database.
**
** Returns          BTA_SUCCESS if record set sucessfully, otherwise error code.
**
*******************************************************************************/
tBTA_STATUS BTA_DmSetLocalDiRecord( tBTA_DI_RECORD *p_device_info,
                              UINT32 *p_handle )
{
    tBTA_STATUS  status = BTA_FAILURE;

    if(bta_dm_di_cb.di_num < BTA_DI_NUM_MAX)
    {
        if(SDP_SetLocalDiRecord((tSDP_DI_RECORD *)p_device_info, p_handle) == SDP_SUCCESS)
        {
            if(!p_device_info->primary_record)
            {
                bta_dm_di_cb.di_handle[bta_dm_di_cb.di_num] = *p_handle;
                bta_dm_di_cb.di_num ++;
            }

            bta_sys_add_uuid(UUID_SERVCLASS_PNP_INFORMATION);
            status =  BTA_SUCCESS;
        }
    }

    return status;
}

/*******************************************************************************
**
** Function         BTA_DmGetLocalDiRecord
**
** Description      Get a specified DI record to the local SDP database. If no
**                  record handle is provided, the primary DI record will be
**                  returned.
**
**                  Fills in the device information of the record
**                  p_handle - if p_handle == 0, the primary record is returned
**
** Returns          BTA_SUCCESS if record set sucessfully, otherwise error code.
**
*******************************************************************************/
tBTA_STATUS BTA_DmGetLocalDiRecord( tBTA_DI_GET_RECORD *p_device_info,
                              UINT32 *p_handle )
{
    UINT16  status;

    status = SDP_GetLocalDiRecord(p_device_info, p_handle);

    if (status == SDP_SUCCESS)
        return BTA_SUCCESS;
    else
        return BTA_FAILURE;

}

/*******************************************************************************
**                   Device Identification (DI) Client Functions
*******************************************************************************/
/*******************************************************************************
**
** Function         BTA_DmDiDiscover
**
** Description      This function queries a remote device for DI information.
**
**
** Returns          None.
**
*******************************************************************************/
void BTA_DmDiDiscover( BD_ADDR remote_device, tBTA_DISCOVERY_DB *p_db,
                       UINT32 len, tBTA_DM_SEARCH_CBACK *p_cback )
{
    tBTA_DM_API_DI_DISC    *p_msg;

    if ((p_msg = (tBTA_DM_API_DI_DISC *) GKI_getbuf(sizeof(tBTA_DM_API_DI_DISC))) != NULL)
    {
        bdcpy(p_msg->bd_addr, remote_device);
        p_msg->hdr.event    = BTA_DM_API_DI_DISCOVER_EVT;
        p_msg->p_sdp_db     = p_db;
        p_msg->len          = len;
        p_msg->p_cback      = p_cback;

        bta_sys_sendmsg(p_msg);
    }
}

/*******************************************************************************
**
** Function         BTA_DmGetDiRecord
**
** Description      This function retrieves a remote device's DI record from
**                  the specified database.
**
** Returns          BTA_SUCCESS if Get DI record is succeed.
**                  BTA_FAILURE if Get DI record failed.
**
*******************************************************************************/
tBTA_STATUS BTA_DmGetDiRecord( UINT8 get_record_index, tBTA_DI_GET_RECORD *p_device_info,
                        tBTA_DISCOVERY_DB *p_db )
{
    if (SDP_GetDiRecord(get_record_index, p_device_info, p_db) != SDP_SUCCESS)
        return BTA_FAILURE;
    else
        return BTA_SUCCESS;
}

/*******************************************************************************
**
** Function         BTA_SysFeatures
**
** Description      This function is called to set system features.
**
** Returns          void
**
*******************************************************************************/
void BTA_SysFeatures (UINT16 sys_features)
{
    bta_sys_cb.sys_features = sys_features;

    APPL_TRACE_API1("BTA_SysFeatures: sys_features = %d", sys_features);
}

/*******************************************************************************
**
** Function         bta_dmexecutecallback
**
** Description      This function will request BTA to execute a call back in the context of BTU task
**                  This API was named in lower case because it is only intended
**                  for the internal customers(like BTIF).
**
** Returns          void
**
*******************************************************************************/
void bta_dmexecutecallback (tBTA_DM_EXEC_CBACK* p_callback, void * p_param)
{
    tBTA_DM_API_EXECUTE_CBACK *p_msg;

    if ((p_msg = (tBTA_DM_API_EXECUTE_CBACK *) GKI_getbuf(sizeof(tBTA_DM_MSG))) != NULL)
    {
        p_msg->hdr.event = BTA_DM_API_EXECUTE_CBACK_EVT;
        p_msg->p_param= p_param;
        p_msg->p_exec_cback= p_callback;
        bta_sys_sendmsg(p_msg);
    }
}

/*******************************************************************************
**
** Function         BTA_DmAddBleKey
**
** Description      Add/modify LE device information.  This function will be
**                  normally called during host startup to restore all required
**                  information stored in the NVRAM.
**
** Parameters:      bd_addr          - BD address of the peer
**                  p_le_key         - LE key values.
**                  key_type         - LE SMP key type.
**
** Returns          void
**
*******************************************************************************/
void BTA_DmAddBleKey (BD_ADDR bd_addr, tBTA_LE_KEY_VALUE *p_le_key, tBTA_LE_KEY_TYPE key_type)
{
#if BLE_INCLUDED == TRUE

    tBTA_DM_API_ADD_BLEKEY *p_msg;

    if ((p_msg = (tBTA_DM_API_ADD_BLEKEY *) GKI_getbuf(sizeof(tBTA_DM_API_ADD_BLEKEY))) != NULL)
    {
        memset (p_msg, 0, sizeof(tBTA_DM_API_ADD_BLEKEY));

        p_msg->hdr.event = BTA_DM_API_ADD_BLEKEY_EVT;
        p_msg->key_type = key_type;
        bdcpy(p_msg->bd_addr, bd_addr);
        memcpy(&p_msg->blekey, p_le_key, sizeof(tBTA_LE_KEY_VALUE));

        bta_sys_sendmsg(p_msg);
    }

#endif
}

/*******************************************************************************
**
** Function         BTA_DmAddBleDevice
**
** Description      Add a BLE device.  This function will be normally called
**                  during host startup to restore all required information
**                  for a LE device stored in the NVRAM.
**
** Parameters:      bd_addr          - BD address of the peer
**                  dev_type         - Remote device's device type.
**                  addr_type        - LE device address type.
**
** Returns          void
**
*******************************************************************************/
void BTA_DmAddBleDevice(BD_ADDR bd_addr, tBLE_ADDR_TYPE addr_type, tBT_DEVICE_TYPE dev_type)
{
#if BLE_INCLUDED == TRUE
    tBTA_DM_API_ADD_BLE_DEVICE *p_msg;

    if ((p_msg = (tBTA_DM_API_ADD_BLE_DEVICE *) GKI_getbuf(sizeof(tBTA_DM_API_ADD_BLE_DEVICE))) != NULL)
    {
        memset (p_msg, 0, sizeof(tBTA_DM_API_ADD_BLE_DEVICE));

        p_msg->hdr.event = BTA_DM_API_ADD_BLEDEVICE_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->addr_type = addr_type;
        p_msg->dev_type = dev_type;

        bta_sys_sendmsg(p_msg);
    }
#endif
}
/*******************************************************************************
**
** Function         BTA_DmBlePasskeyReply
**
** Description      Send BLE SMP passkey reply.
**
** Parameters:      bd_addr          - BD address of the peer
**                  accept           - passkey entry sucessful or declined.
**                  passkey          - passkey value, must be a 6 digit number,
**                                     can be lead by 0.
**
** Returns          void
**
*******************************************************************************/
void BTA_DmBlePasskeyReply(BD_ADDR bd_addr, BOOLEAN accept, UINT32 passkey)
{
#if BLE_INCLUDED == TRUE
    tBTA_DM_API_PASSKEY_REPLY    *p_msg;

    if ((p_msg = (tBTA_DM_API_PASSKEY_REPLY *) GKI_getbuf(sizeof(tBTA_DM_API_PASSKEY_REPLY))) != NULL)
    {
        memset(p_msg, 0, sizeof(tBTA_DM_API_PASSKEY_REPLY));

        p_msg->hdr.event = BTA_DM_API_BLE_PASSKEY_REPLY_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->accept = accept;

        if(accept)
        {
            p_msg->passkey = passkey;
        }
        bta_sys_sendmsg(p_msg);
    }
#endif
}
/*******************************************************************************
**
** Function         BTA_DmBleSecurityGrant
**
** Description      Grant security request access.
**
** Parameters:      bd_addr          - BD address of the peer
**                  res              - security grant status.
**
** Returns          void
**
*******************************************************************************/
void BTA_DmBleSecurityGrant(BD_ADDR bd_addr, tBTA_DM_BLE_SEC_GRANT res)
{
#if BLE_INCLUDED == TRUE
    tBTA_DM_API_BLE_SEC_GRANT    *p_msg;

    if ((p_msg = (tBTA_DM_API_BLE_SEC_GRANT *) GKI_getbuf(sizeof(tBTA_DM_API_BLE_SEC_GRANT))) != NULL)
    {
        memset(p_msg, 0, sizeof(tBTA_DM_API_BLE_SEC_GRANT));

        p_msg->hdr.event = BTA_DM_API_BLE_SEC_GRANT_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->res = res;

        bta_sys_sendmsg(p_msg);
    }
#endif
}
/*******************************************************************************
**
** Function         BTA_DmSetBlePrefConnParams
**
** Description      This function is called to set the preferred connection
**                  parameters when default connection parameter is not desired.
**
** Parameters:      bd_addr          - BD address of the peripheral
**                  scan_interval    - scan interval
**                  scan_window      - scan window
**                  min_conn_int     - minimum preferred connection interval
**                  max_conn_int     - maximum preferred connection interval
**                  slave_latency    - preferred slave latency
**                  supervision_tout - preferred supervision timeout
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmSetBlePrefConnParams(BD_ADDR bd_addr,
                               UINT16 min_conn_int, UINT16 max_conn_int,
                               UINT16 slave_latency, UINT16 supervision_tout )
{
#if BLE_INCLUDED == TRUE
    tBTA_DM_API_BLE_CONN_PARAMS    *p_msg;

    if ((p_msg = (tBTA_DM_API_BLE_CONN_PARAMS *) GKI_getbuf(sizeof(tBTA_DM_API_BLE_CONN_PARAMS))) != NULL)
    {
        memset(p_msg, 0, sizeof(tBTA_DM_API_BLE_CONN_PARAMS));

        p_msg->hdr.event = BTA_DM_API_BLE_CONN_PARAM_EVT;

        memcpy(p_msg->peer_bda, bd_addr, BD_ADDR_LEN);

        p_msg->conn_int_max     = max_conn_int;
        p_msg->conn_int_min     = min_conn_int;
        p_msg->slave_latency    = slave_latency;
        p_msg->supervision_tout = supervision_tout;

        bta_sys_sendmsg(p_msg);
    }
#endif
}

/*******************************************************************************
**
** Function         BTA_DmSetBleConnScanParams
**
** Description      This function is called to set scan parameters used in
**                  BLE connection request
**
** Parameters:      scan_interval    - scan interval
**                  scan_window      - scan window
**
** Returns          void
**
*******************************************************************************/
void BTA_DmSetBleConnScanParams(UINT16 scan_interval, UINT16 scan_window )
{
#if BLE_INCLUDED == TRUE
    tBTA_DM_API_BLE_SCAN_PARAMS    *p_msg;

    if ((p_msg = (tBTA_DM_API_BLE_SCAN_PARAMS *) GKI_getbuf(sizeof(tBTA_DM_API_BLE_SCAN_PARAMS))) != NULL)
    {
        memset(p_msg, 0, sizeof(tBTA_DM_API_BLE_SCAN_PARAMS));

        p_msg->hdr.event = BTA_DM_API_BLE_SCAN_PARAM_EVT;

        p_msg->scan_int         = scan_interval;
        p_msg->scan_window      = scan_window;

        bta_sys_sendmsg(p_msg);
    }
#endif
}

/*******************************************************************************
**
** Function         BTA_DmBleSetBgConnType
**
** Description      This function is called to set BLE connectable mode for a
**                  peripheral device.
**
** Parameters       bg_conn_type: it can be auto connection, or selective connection.
**                  p_select_cback: callback function when selective connection procedure
**                              is being used.
**
** Returns          void
**
*******************************************************************************/
void BTA_DmBleSetBgConnType(tBTA_DM_BLE_CONN_TYPE bg_conn_type, tBTA_DM_BLE_SEL_CBACK *p_select_cback)
{
#if BLE_INCLUDED == TRUE
    tBTA_DM_API_BLE_SET_BG_CONN_TYPE    *p_msg;

    if ((p_msg = (tBTA_DM_API_BLE_SET_BG_CONN_TYPE *) GKI_getbuf(sizeof(tBTA_DM_API_BLE_SET_BG_CONN_TYPE))) != NULL)
    {
        memset(p_msg, 0, sizeof(tBTA_DM_API_BLE_SET_BG_CONN_TYPE));

        p_msg->hdr.event        = BTA_DM_API_BLE_SET_BG_CONN_TYPE;
        p_msg->bg_conn_type     = bg_conn_type;
        p_msg->p_select_cback   = p_select_cback;

        bta_sys_sendmsg(p_msg);
    }
#endif
}
/*******************************************************************************
**
** Function         BTA_DmDiscoverExt
**
** Description      This function does service discovery for services of a
**                  peer device. When services.num_uuid is 0, it indicates all
**                  GATT based services are to be searched; other wise a list of
**                  UUID of interested services should be provided through
**                  p_services->p_uuid.
**
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmDiscoverExt(BD_ADDR bd_addr, tBTA_SERVICE_MASK_EXT *p_services,
                    tBTA_DM_SEARCH_CBACK *p_cback, BOOLEAN sdp_search)
{
#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
    tBTA_DM_API_DISCOVER    *p_msg;
    UINT16  len = p_services ? (sizeof(tBTA_DM_API_DISCOVER) + sizeof(tBT_UUID) * p_services->num_uuid) :
                    sizeof(tBTA_DM_API_DISCOVER);

    if ((p_msg = (tBTA_DM_API_DISCOVER *) GKI_getbuf(len)) != NULL)
    {
        memset(p_msg, 0, len);

        p_msg->hdr.event = BTA_DM_API_DISCOVER_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->p_cback = p_cback;
        p_msg->sdp_search = sdp_search;

        if (p_services != NULL)
        {
            p_msg->services = p_services->srvc_mask;
            p_msg->num_uuid = p_services->num_uuid;

            if (p_services->num_uuid != 0)
            {
                p_msg->p_uuid = (tBT_UUID *)(p_msg + 1);
                memcpy(p_msg->p_uuid, p_services->p_uuid, sizeof(tBT_UUID) * p_services->num_uuid);
            }
        }

        bta_sys_sendmsg(p_msg);
    }
#endif

}

/*******************************************************************************
**
** Function         BTA_DmSearchExt
**
** Description      This function searches for peer Bluetooth devices. It performs
**                  an inquiry and gets the remote name for devices. Service
**                  discovery is done if services is non zero
**
** Parameters       p_dm_inq: inquiry conditions
**                  p_services: if service is not empty, service discovery will be done.
**                            for all GATT based service condition, put num_uuid, and
**                            p_uuid is the pointer to the list of UUID values.
**                  p_cback: callback functino when search is completed.
**
**
**
** Returns          void
**
*******************************************************************************/
void BTA_DmSearchExt(tBTA_DM_INQ *p_dm_inq, tBTA_SERVICE_MASK_EXT *p_services, tBTA_DM_SEARCH_CBACK *p_cback)
{
#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
    tBTA_DM_API_SEARCH    *p_msg;
    UINT16  len = p_services ? (sizeof(tBTA_DM_API_SEARCH) + sizeof(tBT_UUID) * p_services->num_uuid) :
                    sizeof(tBTA_DM_API_SEARCH);

    if ((p_msg = (tBTA_DM_API_SEARCH *) GKI_getbuf(len)) != NULL)
    {
        memset(p_msg, 0, len);

        p_msg->hdr.event = BTA_DM_API_SEARCH_EVT;
        memcpy(&p_msg->inq_params, p_dm_inq, sizeof(tBTA_DM_INQ));
        p_msg->p_cback = p_cback;
        p_msg->rs_res  = BTA_DM_RS_NONE;


        if (p_services != NULL)
        {
            p_msg->services = p_services->srvc_mask;
            p_msg->num_uuid = p_services->num_uuid;

            if (p_services->num_uuid != 0)
            {
                p_msg->p_uuid = (tBT_UUID *)(p_msg + 1);
                memcpy(p_msg->p_uuid, p_services->p_uuid, sizeof(tBT_UUID) * p_services->num_uuid);
            }
            else
                p_msg->p_uuid = NULL;
        }

        bta_sys_sendmsg(p_msg);
    }
#endif
}


/*******************************************************************************
**
** Function         BTA_DmSetEncryption
**
** Description      This function is called to ensure that connection is
**                  encrypted.  Should be called only on an open connection.
**                  Typically only needed for connections that first want to
**                  bring up unencrypted links, then later encrypt them.
**
** Parameters:      bd_addr       - Address of the peer device
**                  p_callback    - Pointer to callback function to indicat the
**                                  link encryption status
**                  sec_act       - This is the security action to indicate
**                                  what knid of BLE security level is required for
**                                  the BLE link if the BLE is supported
**                                  Note: This parameter is ignored for the BR/EDR link
**                                        or the BLE is not supported
**
** Returns          void
**
*******************************************************************************/
void BTA_DmSetEncryption(BD_ADDR bd_addr, tBTA_DM_ENCRYPT_CBACK *p_callback,
                            tBTA_DM_BLE_SEC_ACT sec_act)
{
    tBTA_DM_API_SET_ENCRYPTION   *p_msg;

    APPL_TRACE_API0("BTA_DmSetEncryption"); //todo
    if ((p_msg = (tBTA_DM_API_SET_ENCRYPTION *) GKI_getbuf(sizeof(tBTA_DM_API_SET_ENCRYPTION))) != NULL)
    {
        memset(p_msg, 0, sizeof(tBTA_DM_API_SET_ENCRYPTION));

        p_msg->hdr.event = BTA_DM_API_SET_ENCRYPTION_EVT;

        memcpy(p_msg->bd_addr, bd_addr, BD_ADDR_LEN);
        p_msg->p_callback      = p_callback;
        p_msg->sec_act         = sec_act;

        bta_sys_sendmsg(p_msg);
    }
}

