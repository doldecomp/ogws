/******************************************************************************
 *
 *  Copyright (C) 2006-2012 Broadcom Corporation
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
 *  This is the implementation of the JAVA API for Bluetooth Wireless
 *  Technology (JABWT) as specified by the JSR82 specificiation
 *
 ******************************************************************************/

#include "bta_api.h"
#include "bd.h"
#include "bta_sys.h"
#include "bta_jv_api.h"
#include "bta_jv_int.h"
#include "gki.h"
#include <string.h>
#include "port_api.h"
#include "sdp_api.h"

/*****************************************************************************
**  Constants
*****************************************************************************/

static const tBTA_SYS_REG bta_jv_reg =
{
    bta_jv_sm_execute,
    NULL
};

/*******************************************************************************
**
** Function         BTA_JvEnable
**
** Description      Enable the Java I/F service. When the enable
**                  operation is complete the callback function will be
**                  called with a BTA_JV_ENABLE_EVT. This function must
**                  be called before other function in the JV API are
**                  called.
**
** Returns          BTA_JV_SUCCESS if successful.
**                  BTA_JV_FAIL if internal failure.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvEnable(tBTA_JV_DM_CBACK *p_cback)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_ENABLE  *p_buf;

    APPL_TRACE_API0( "BTA_JvEnable");
    if(p_cback && FALSE == bta_sys_is_register(BTA_ID_JV))
    {
        memset(&bta_jv_cb, 0, sizeof(tBTA_JV_CB));

        /* register with BTA system manager */
        GKI_sched_lock();
        bta_sys_register(BTA_ID_JV, &bta_jv_reg);
        GKI_sched_unlock();

        if (p_cback && (p_buf = (tBTA_JV_API_ENABLE *) GKI_getbuf(sizeof(tBTA_JV_API_ENABLE))) != NULL)
        {
            p_buf->hdr.event = BTA_JV_API_ENABLE_EVT;
            p_buf->p_cback = p_cback;
            bta_sys_sendmsg(p_buf);
            status = BTA_JV_SUCCESS;
        }
    }
    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvDisable
**
** Description      Disable the Java I/F
**
** Returns          void
**
*******************************************************************************/
void BTA_JvDisable(void)
{
    BT_HDR  *p_buf;

    APPL_TRACE_API0( "BTA_JvDisable");
    bta_sys_deregister(BTA_ID_JV);
    if ((p_buf = (BT_HDR *) GKI_getbuf(sizeof(BT_HDR))) != NULL)
    {
        p_buf->event = BTA_JV_API_DISABLE_EVT;
        bta_sys_sendmsg(p_buf);
    }
}

/*******************************************************************************
**
** Function         BTA_JvIsEnable
**
** Description      Get the JV registration status.
**
** Returns          TRUE, if registered
**
*******************************************************************************/
BOOLEAN BTA_JvIsEnable(void)
{
    return bta_sys_is_register(BTA_ID_JV);
}

/*******************************************************************************
**
** Function         BTA_JvSetDiscoverability
**
** Description      This function sets the Bluetooth  discoverable modes
**                  of the local device.  This controls whether other
**                  Bluetooth devices can find the local device.
**
**                  When the operation is complete the tBTA_JV_DM_CBACK callback
**                  function will be called with a BTA_JV_SET_DISCOVER_EVT.
**
** Returns          BTA_JV_SUCCESS if successful.
**                  BTA_JV_FAIL if internal failure.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvSetDiscoverability(tBTA_JV_DISC disc_mode)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_SET_DISCOVERABILITY *p_msg;

    APPL_TRACE_API0( "BTA_JvSetDiscoverability");
    if ((p_msg = (tBTA_JV_API_SET_DISCOVERABILITY *)GKI_getbuf(sizeof(tBTA_JV_MSG))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_SET_DISCOVERABILITY_EVT;
        p_msg->disc_mode = disc_mode;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvGetDiscoverability
**
** Description      This function gets the Bluetooth
**                  discoverable modes of local device
**
** Returns          The current Bluetooth discoverable mode.
**
*******************************************************************************/
tBTA_JV_DISC BTA_JvGetDiscoverability(void)
{
    APPL_TRACE_API0( "BTA_JvGetDiscoverability");
    return BTM_ReadDiscoverability(0, 0);
}

/*******************************************************************************
**
** Function         BTA_JvGetLocalDeviceAddr
**
** Description      This function obtains the local Bluetooth device address.
**                  The local Bluetooth device address is reported by the
**                  tBTA_JV_DM_CBACK callback with a BTA_JV_LOCAL_ADDR_EVT.
**
** Returns          BTA_JV_SUCCESS if successful.
**                  BTA_JV_FAIL if internal failure.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvGetLocalDeviceAddr(void)
{
    tBTA_JV_STATUS ret = BTA_JV_FAILURE;
    BT_HDR *p_msg;

    APPL_TRACE_API0( "BTA_JvGetLocalDeviceAddr");
    if ((p_msg = (BT_HDR *)GKI_getbuf(sizeof(BT_HDR))) != NULL)
    {
        p_msg->event = BTA_JV_API_GET_LOCAL_DEVICE_ADDR_EVT;
        bta_sys_sendmsg(p_msg);
        ret = BTA_JV_SUCCESS;
    }

    return(ret);
}

/*******************************************************************************
**
** Function         BTA_JvGetLocalDeviceName
**
** Description      This function obtains the name of the local device
**                  The local Bluetooth device name is reported by the
**                  tBTA_JV_DM_CBACK callback with a BTA_JV_LOCAL_NAME_EVT.
**
** Returns          BTA_JV_SUCCESS if successful.
**                  BTA_JV_FAIL if internal failure.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvGetLocalDeviceName(void)
{
    tBTA_JV_STATUS ret = BTA_JV_FAILURE;
    BT_HDR *p_msg;

    APPL_TRACE_API0( "BTA_JvGetLocalDeviceName");
    if ((p_msg = (BT_HDR *)GKI_getbuf(sizeof(BT_HDR))) != NULL)
    {
        p_msg->event = BTA_JV_API_GET_LOCAL_DEVICE_NAME_EVT;
        bta_sys_sendmsg(p_msg);
        ret = BTA_JV_SUCCESS;
    }

    return(ret);
}

/*******************************************************************************
**
** Function         BTA_JvGetRemoteDeviceName
**
** Description      This function obtains the name of the specified device.
**                  The Bluetooth device name is reported by the
**                  tBTA_JV_DM_CBACK callback with a BTA_JV_REMOTE_NAME_EVT.
**
** Returns          BTA_JV_SUCCESS if successful.
**                  BTA_JV_FAIL if internal failure.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvGetRemoteDeviceName(BD_ADDR bd_addr)
{
    tBTA_JV_STATUS ret = BTA_JV_FAILURE;
    tBTA_JV_API_GET_REMOTE_NAME *p_msg;

    APPL_TRACE_API0( "BTA_JvGetRemoteDeviceName");
    if ((p_msg = (tBTA_JV_API_GET_REMOTE_NAME *)GKI_getbuf(sizeof(tBTA_JV_API_GET_REMOTE_NAME))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_GET_REMOTE_DEVICE_NAME_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        bta_sys_sendmsg(p_msg);
        ret = BTA_JV_SUCCESS;
    }

    return(ret);
}

/*******************************************************************************
**
** Function         BTA_JvGetPreknownDevice
**
** Description      This function obtains the Bluetooth address in the inquiry
**                  database collected via the previous call to BTA_DmSearch().
**
** Returns          The number of preknown devices if p_bd_addr is NULL
**                  BTA_JV_SUCCESS if successful.
**                  BTA_JV_INTERNAL_ERR(-1) if internal failure.
**
*******************************************************************************/
INT32 BTA_JvGetPreknownDevice(UINT8 * p_bd_addr, UINT32 index)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTM_INQ_INFO *p_info;
    UINT32  count = 0;
    INT32   ret = BTA_JV_INTERNAL_ERR;

    APPL_TRACE_API0( "BTA_JvGetPreknownDevice");
    p_info = BTM_InqFirstResult();
    if(p_info)
    {
        status = BTA_JV_SUCCESS;
        /* the database is valid */
        if(NULL == p_bd_addr)
        {
            /* p_bd_addr is NULL: count the number of preknown devices */
            /* set the index to an invalid size (too big) */
            index = BTM_INQ_DB_SIZE;
        }
        else if(index >= BTM_INQ_DB_SIZE)
        {
            /* invalid index - error */
            status = (tBTA_JV_STATUS)BTA_JV_INTERNAL_ERR;
        }

        if(BTA_JV_SUCCESS == status)
        {
            while(p_info && index > count)
            {
                count++;
                p_info = BTM_InqNextResult(p_info);
            }

            if(p_bd_addr)
            {
                if(index == count && p_info)
                {
                    count = BTA_JV_SUCCESS;
                    bdcpy(p_bd_addr, p_info->results.remote_bd_addr);
                }
                else
                    status = (tBTA_JV_STATUS)BTA_JV_INTERNAL_ERR;
            }
            /*
            else report the count
            */
        }
        /*
        else error had happened.
        */
    }

    if(BTA_JV_SUCCESS == status)
    {
        ret = count;
    }
    return ret;
}


/*******************************************************************************
**
** Function         BTA_JvGetDeviceClass
**
** Description      This function obtains the local Class of Device. This
**                  function executes in place. The result is returned right away.
**
** Returns          DEV_CLASS, A three-byte array of UINT8 that contains the
**                  Class of Device information. The definitions are in the
**                  "Bluetooth Assigned Numbers".
**
*******************************************************************************/
UINT8 * BTA_JvGetDeviceClass(void)
{
    APPL_TRACE_API0( "BTA_JvGetDeviceClass");
    return BTM_ReadDeviceClass();
}

/*******************************************************************************
**
** Function         BTA_JvSetServiceClass
**
** Description      This function sets the service class of local Class of Device
**
** Returns          BTA_JV_SUCCESS if successful.
**                  BTA_JV_FAIL if internal failure.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvSetServiceClass(UINT32 service)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_SET_SERVICE_CLASS *p_msg;

    APPL_TRACE_API0( "BTA_JvSetServiceClass");
    if ((p_msg = (tBTA_JV_API_SET_SERVICE_CLASS *)GKI_getbuf(sizeof(tBTA_JV_API_SET_SERVICE_CLASS))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_SET_SERVICE_CLASS_EVT;
        p_msg->service = service;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvSetEncryption
**
** Description      This function ensures that the connection to the given device
**                  is encrypted.
**                  When the operation is complete the tBTA_JV_DM_CBACK callback
**                  function will be called with a BTA_JV_SET_ENCRYPTION_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvSetEncryption(BD_ADDR bd_addr)
{
    tBTA_JV_STATUS ret = BTA_JV_FAILURE;
    tBTA_JV_API_SET_ENCRYPTION *p_msg;

    APPL_TRACE_API0( "BTA_JvSetEncryption");
    if ((p_msg = (tBTA_JV_API_SET_ENCRYPTION *)GKI_getbuf(sizeof(tBTA_JV_API_SET_ENCRYPTION))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_SET_ENCRYPTION_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        bta_sys_sendmsg(p_msg);
        ret = BTA_JV_SUCCESS;
    }

    return(ret);
}

/*******************************************************************************
**
** Function         BTA_JvIsAuthenticated
**
** Description      This function checks if the peer device is authenticated
**
** Returns          TRUE if authenticated.
**                  FALSE if not.
**
*******************************************************************************/
BOOLEAN BTA_JvIsAuthenticated(BD_ADDR bd_addr)
{
    BOOLEAN is_authenticated = FALSE;
    UINT8 sec_flags;

    if(BTM_GetSecurityFlags(bd_addr, &sec_flags))
    {
        if(sec_flags&BTM_SEC_FLAG_AUTHENTICATED)
            is_authenticated = TRUE;
    }
    return is_authenticated;
}

/*******************************************************************************
**
** Function         BTA_JvIsTrusted
**
** Description      This function checks if the peer device is trusted
**                  (previously paired)
**
** Returns          TRUE if trusted.
**                  FALSE if not.
**
*******************************************************************************/
BOOLEAN BTA_JvIsTrusted(BD_ADDR bd_addr)
{
    BOOLEAN is_trusted = FALSE;
    UINT8 sec_flags;

    if(BTM_GetSecurityFlags(bd_addr, &sec_flags))
    {
        if ((sec_flags&BTM_SEC_FLAG_AUTHENTICATED) ||
            (sec_flags&BTM_SEC_FLAG_LKEY_KNOWN))
        {
            is_trusted = TRUE;
        }
    }
    return is_trusted;
}

/*******************************************************************************
**
** Function         BTA_JvIsAuthorized
**
** Description      This function checks if the peer device is authorized
**
** Returns          TRUE if authorized.
**                  FALSE if not.
**
*******************************************************************************/
BOOLEAN BTA_JvIsAuthorized(BD_ADDR bd_addr)
{
    BOOLEAN is_authorized = FALSE;
    UINT8 sec_flags;

    if(BTM_GetSecurityFlags(bd_addr, &sec_flags))
    {
        if(sec_flags&BTM_SEC_FLAG_AUTHORIZED)
            is_authorized = TRUE;
    }
    return is_authorized;
}

/*******************************************************************************
**
** Function         BTA_JvIsEncrypted
**
** Description      This function checks if the link to peer device is encrypted
**
** Returns          TRUE if encrypted.
**                  FALSE if not.
**
*******************************************************************************/
BOOLEAN BTA_JvIsEncrypted(BD_ADDR bd_addr)
{
    BOOLEAN is_encrypted = FALSE;
    UINT8 sec_flags;

    if(BTM_GetSecurityFlags(bd_addr, &sec_flags))
    {
        if(sec_flags&BTM_SEC_FLAG_ENCRYPTED)
            is_encrypted = TRUE;
    }
    return is_encrypted;
}

/*******************************************************************************
**
** Function         BTA_JvGetSecurityMode
**
** Description      This function returns the current Bluetooth security mode
**                  of the local device
**
** Returns          The current Bluetooth security mode.
**
*******************************************************************************/
tBTA_JV_SEC_MODE BTA_JvGetSecurityMode(void)
{
   return BTM_GetSecurityMode();
}

/*******************************************************************************
**
** Function         BTA_JvGetSCN
**
** Description      This function reserves a SCN (server channel number) for
**                  applications running over RFCOMM. It is primarily called by
**                  server profiles/applications to register their SCN into the
**                  SDP database. The SCN is reported by the tBTA_JV_DM_CBACK
**                  callback with a BTA_JV_GET_SCN_EVT.
**                  If the SCN reported is 0, that means all SCN resources are
**                  exhausted.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvGetSCN(void)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    BT_HDR *p_msg;

    APPL_TRACE_API0( "BTA_JvGetSCN");
    if ((p_msg = (BT_HDR *)GKI_getbuf(sizeof(BT_HDR))) != NULL)
    {
        p_msg->event = BTA_JV_API_GET_SCN_EVT;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvFreeSCN
**
** Description      This function frees a server channel number that was used
**                  by an application running over RFCOMM.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvFreeSCN(UINT8 scn)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_FREE_SCN *p_msg;

    APPL_TRACE_API0( "BTA_JvFreeSCN");
    if ((p_msg = (tBTA_JV_API_FREE_SCN *)GKI_getbuf(sizeof(tBTA_JV_API_FREE_SCN))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_FREE_SCN_EVT;
        p_msg->scn       = scn;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvGetPSM
**
** Description      This function reserves a PSM (Protocol Service Multiplexer)
**                  applications running over L2CAP. It is primarily called by
**                  server profiles/applications to register their PSM into the
**                  SDP database.
**
** Returns          The next free PSM
**
*******************************************************************************/
UINT16 BTA_JvGetPSM(void)
{
#if 0
    APPL_TRACE_API0( "BTA_JvGetPSM");

    return (L2CA_AllocatePSM());
#endif
    return 0;
}


/*******************************************************************************
**
** Function         BTA_JvStartDiscovery
**
** Description      This function performs service discovery for the services
**                  provided by the given peer device. When the operation is
**                  complete the tBTA_JV_DM_CBACK callback function will be
**                  called with a BTA_JV_DISCOVERY_COMP_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvStartDiscovery(BD_ADDR bd_addr, UINT16 num_uuid,
            tSDP_UUID *p_uuid_list, void * user_data)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_START_DISCOVERY *p_msg;

    APPL_TRACE_API0( "BTA_JvStartDiscovery");
    if ((p_msg = (tBTA_JV_API_START_DISCOVERY *)GKI_getbuf(sizeof(tBTA_JV_API_START_DISCOVERY))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_START_DISCOVERY_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->num_uuid = num_uuid;
        memcpy(p_msg->uuid_list, p_uuid_list, num_uuid * sizeof(tSDP_UUID));
        p_msg->num_attr = 0;
        p_msg->user_data = user_data;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvCancelDiscovery
**
** Description      This function cancels an active service discovery.
**                  When the operation is
**                  complete the tBTA_JV_DM_CBACK callback function will be
**                  called with a BTA_JV_CANCEL_DISCVRY_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvCancelDiscovery(void * user_data)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_CANCEL_DISCOVERY *p_msg;

    APPL_TRACE_API0( "BTA_JvCancelDiscovery");
    if ((p_msg = (tBTA_JV_API_CANCEL_DISCOVERY *)GKI_getbuf(sizeof(tBTA_JV_API_CANCEL_DISCOVERY))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_CANCEL_DISCOVERY_EVT;
        p_msg->user_data = user_data;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvGetServicesLength
**
** Description      This function obtains the number of services and the length
**                  of each service found in the SDP database (result of last
**                  BTA_JvStartDiscovery().When the operation is complete the
**                  tBTA_JV_DM_CBACK callback function will be called with a
**                  BTA_JV_SERVICES_LEN_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvGetServicesLength(BOOLEAN inc_hdr, UINT16 *p_services_len)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_GET_SERVICES_LENGTH *p_msg;

    APPL_TRACE_API0( "BTA_JvGetServicesLength");
    if ((p_msg = (tBTA_JV_API_GET_SERVICES_LENGTH *)GKI_getbuf(sizeof(tBTA_JV_API_GET_SERVICES_LENGTH))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_GET_SERVICES_LENGTH_EVT;
        p_msg->p_services_len = p_services_len;
        p_msg->inc_hdr = inc_hdr;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}
/*******************************************************************************
**
** Function         BTA_JvGetServicesResult
**
** Description      This function returns a number of service records found
**                  during current service search, equals to the number returned
**                  by previous call to BTA_JvGetServicesLength.
**                  The contents of each SDP record will be returned under a
**                  TLV (type, len, value) representation in the data buffer
**                  provided by the caller.
**
** Returns          -1, if error. Otherwise, the number of services
**
*******************************************************************************/
INT32 BTA_JvGetServicesResult(BOOLEAN inc_hdr, UINT8 **TLVs)
{
#if 0
    INT32 num_services = -1;
    UINT8   *p, *np, *op, type;
    UINT32  raw_used, raw_cur;
    UINT32  len;
    UINT32  hdr_len;

    APPL_TRACE_API0( "BTA_JvGetServicesResult");
    if(p_bta_jv_cfg->p_sdp_db->p_first_rec)
    {
        /* the database is valid */
        num_services = 0;
        p = p_bta_jv_cfg->p_sdp_db->raw_data;
        raw_used = p_bta_jv_cfg->p_sdp_db->raw_used;
        while(raw_used && p)
        {
            op = p;
            type = *p++;
            np = sdpu_get_len_from_type(p, type, &len);
            p = np + len;
            raw_cur = p - op;
            if(raw_used >= raw_cur)
            {
                raw_used -= raw_cur;
            }
            else
            {
                /* error. can not continue */
                break;
            }
            if(inc_hdr)
            {
                hdr_len = np - op;
                memcpy(TLVs[num_services++], op, len+hdr_len);
            }
            else
            {
                memcpy(TLVs[num_services++], np, len);
            }
        } /* end of while */
    }
    return(num_services);
#endif
    return 0;
}
/*******************************************************************************
**
** Function         BTA_JvServiceSelect
**
** Description      This function checks if the SDP database contains the given
**                  service UUID. When the operation is complete the
**                  tBTA_JV_DM_CBACK callback function will be called with a
**                  BTA_JV_SERVICE_SEL_EVT with the length of the service record.
**                  If the service is not found or error, -1 is reported.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvServiceSelect(UINT16 uuid)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_SERVICE_SELECT *p_msg;

    APPL_TRACE_API0( "BTA_JvServiceSelect");
    if ((p_msg = (tBTA_JV_API_SERVICE_SELECT *)GKI_getbuf(sizeof(tBTA_JV_API_SERVICE_SELECT))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_SERVICE_SELECT_EVT;
        p_msg->uuid = uuid;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }
    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvServiceResult
**
** Description      This function returns the contents of the SDP record from
**                  last BTA_JvServiceSelect. The contents will be returned under
**                  a TLV (type, len, value) representation in the data buffer
**                  provided by the caller.
**
** Returns          -1, if error. Otherwise, the length of service record.
**
*******************************************************************************/
INT32 BTA_JvServiceResult(UINT8 *TLV)
{
    INT32   serv_sel = -1;

    APPL_TRACE_API0( "BTA_JvServiceResult");
    if(bta_jv_cb.p_sel_raw_data)
    {
        serv_sel = bta_jv_cb.sel_len;
        memcpy(TLV, bta_jv_cb.p_sel_raw_data, serv_sel);
    }

    return serv_sel;
}


/*******************************************************************************
**
** Function         BTA_JvCreateRecord
**
** Description      Create a service record in the local SDP database.
**                  When the operation is complete the tBTA_JV_DM_CBACK callback
**                  function will be called with a BTA_JV_CREATE_RECORD_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvCreateRecordByUser(void *user_data)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_CREATE_RECORD *p_msg;

    APPL_TRACE_API0( "BTA_JvCreateRecordByUser");
    if ((p_msg = (tBTA_JV_API_CREATE_RECORD *)GKI_getbuf(sizeof(tBTA_JV_API_CREATE_RECORD))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_CREATE_RECORD_EVT;
        p_msg->user_data = user_data;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvUpdateRecord
**
** Description      Update a service record in the local SDP database.
**                  When the operation is complete the tBTA_JV_DM_CBACK callback
**                  function will be called with a BTA_JV_UPDATE_RECORD_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvUpdateRecord(UINT32 handle, UINT16 *p_ids,
    UINT8 **p_values, INT32 *p_value_sizes, INT32 array_len)
{
#if 0
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_UPDATE_RECORD *p_msg;

    APPL_TRACE_API0( "BTA_JvUpdateRecord");
    if ((p_msg = (tBTA_JV_API_UPDATE_RECORD *)GKI_getbuf(sizeof(tBTA_JV_API_UPDATE_RECORD))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_UPDATE_RECORD_EVT;
        p_msg->handle = handle;
        p_msg->p_ids = p_ids;
        p_msg->p_values = p_values;
        p_msg->p_value_sizes = p_value_sizes;
        p_msg->array_len = array_len;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }
    return(status);
#endif
    return -1;
}

/*******************************************************************************
**
** Function         BTA_JvAddAttribute
**
** Description      Add an attribute to a service record in the local SDP database.
**                  When the operation is complete the tBTA_JV_DM_CBACK callback
**                  function will be called with a BTA_JV_ADD_ATTR_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvAddAttribute(UINT32 handle, UINT16 attr_id,
    UINT8 *p_value, INT32 value_size)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_ADD_ATTRIBUTE *p_msg;

    APPL_TRACE_API0( "BTA_JvAddAttribute");
    if ((p_msg = (tBTA_JV_API_ADD_ATTRIBUTE *)GKI_getbuf(sizeof(tBTA_JV_API_ADD_ATTRIBUTE))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_ADD_ATTRIBUTE_EVT;
        p_msg->handle = handle;
        p_msg->attr_id = attr_id;
        p_msg->p_value = p_value;
        p_msg->value_size = value_size;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }
    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvDeleteAttribute
**
** Description      Delete an attribute from a service record in the local SDP database.
**                  When the operation is complete the tBTA_JV_DM_CBACK callback
**                  function will be called with a BTA_JV_DELETE_ATTR_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvDeleteAttribute(UINT32 handle, UINT16 attr_id)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_ADD_ATTRIBUTE *p_msg;

    APPL_TRACE_API0( "BTA_JvDeleteAttribute");
    if ((p_msg = (tBTA_JV_API_ADD_ATTRIBUTE *)GKI_getbuf(sizeof(tBTA_JV_API_ADD_ATTRIBUTE))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_DELETE_ATTRIBUTE_EVT;
        p_msg->handle = handle;
        p_msg->attr_id = attr_id;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }
    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvDeleteRecord
**
** Description      Delete a service record in the local SDP database.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvDeleteRecord(UINT32 handle)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_ADD_ATTRIBUTE *p_msg;

    APPL_TRACE_API0( "BTA_JvDeleteRecord");
    if ((p_msg = (tBTA_JV_API_ADD_ATTRIBUTE *)GKI_getbuf(sizeof(tBTA_JV_API_ADD_ATTRIBUTE))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_DELETE_RECORD_EVT;
        p_msg->handle = handle;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }
    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvReadRecord
**
** Description      Read a service record in the local SDP database.
**
** Returns          -1, if the record is not found.
**                  Otherwise, the offset (0 or 1) to start of data in p_data.
**
**                  The size of data copied into p_data is in *p_data_len.
**
*******************************************************************************/
INT32 BTA_JvReadRecord(UINT32 handle, UINT8 *p_data, INT32 *p_data_len)
{
    UINT32 sdp_handle;

    sdp_handle = bta_jv_get_sdp_handle(handle);

    if(sdp_handle)
    {
        return SDP_ReadRecord(sdp_handle, p_data, p_data_len);
    }

    return -1;
}

/*******************************************************************************
**
** Function         BTA_JvL2capConnect
**
** Description      Initiate a connection as a L2CAP client to the given BD
**                  Address.
**                  When the connection is initiated or failed to initiate,
**                  tBTA_JV_L2CAP_CBACK is called with BTA_JV_L2CAP_CL_INIT_EVT
**                  When the connection is established or failed,
**                  tBTA_JV_L2CAP_CBACK is called with BTA_JV_L2CAP_OPEN_EVT
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvL2capConnect(tBTA_SEC sec_mask,
                           tBTA_JV_ROLE role, UINT16 remote_psm, UINT16 rx_mtu,
                           BD_ADDR peer_bd_addr, tBTA_JV_L2CAP_CBACK *p_cback)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_L2CAP_CONNECT *p_msg;

    APPL_TRACE_API0( "BTA_JvL2capConnect");
    if (p_cback &&
        (p_msg = (tBTA_JV_API_L2CAP_CONNECT *)GKI_getbuf(sizeof(tBTA_JV_API_L2CAP_CONNECT))) != NULL)
    {
        p_msg->hdr.event    = BTA_JV_API_L2CAP_CONNECT_EVT;
        p_msg->sec_mask     = sec_mask;
        p_msg->role         = role;
        p_msg->remote_psm   = remote_psm;
        p_msg->rx_mtu       = rx_mtu;
        memcpy(p_msg->peer_bd_addr, peer_bd_addr, sizeof(BD_ADDR));
        p_msg->p_cback      = p_cback;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvL2capClose
**
** Description      This function closes an L2CAP client connection
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvL2capClose(UINT32 handle)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_L2CAP_CLOSE *p_msg;

    APPL_TRACE_API0( "BTA_JvL2capClose");
    if (handle < BTA_JV_MAX_L2C_CONN && bta_jv_cb.l2c_cb[handle].p_cback &&
        (p_msg = (tBTA_JV_API_L2CAP_CLOSE *)GKI_getbuf(sizeof(tBTA_JV_API_L2CAP_CLOSE))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_L2CAP_CLOSE_EVT;
        p_msg->handle = handle;
        p_msg->p_cb = &bta_jv_cb.l2c_cb[handle];
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvL2capStartServer
**
** Description      This function starts an L2CAP server and listens for an L2CAP
**                  connection from a remote Bluetooth device.  When the server
**                  is started successfully, tBTA_JV_L2CAP_CBACK is called with
**                  BTA_JV_L2CAP_START_EVT.  When the connection is established,
**                  tBTA_JV_L2CAP_CBACK is called with BTA_JV_L2CAP_OPEN_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvL2capStartServer(tBTA_SEC sec_mask, tBTA_JV_ROLE role,
                           UINT16 local_psm, UINT16 rx_mtu,
                           tBTA_JV_L2CAP_CBACK *p_cback)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_L2CAP_SERVER *p_msg;

    APPL_TRACE_API0( "BTA_JvL2capStartServer");
    if (p_cback &&
        (p_msg = (tBTA_JV_API_L2CAP_SERVER *)GKI_getbuf(sizeof(tBTA_JV_API_L2CAP_SERVER))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_L2CAP_START_SERVER_EVT;
        p_msg->sec_mask = sec_mask;
        p_msg->role = role;
        p_msg->local_psm = local_psm;
        p_msg->rx_mtu = rx_mtu;
        p_msg->p_cback = p_cback;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvL2capStopServer
**
** Description      This function stops the L2CAP server. If the server has an
**                  active connection, it would be closed.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvL2capStopServer(UINT16 local_psm)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_L2CAP_SERVER *p_msg;

    APPL_TRACE_API0( "BTA_JvL2capStopServer");
    if ((p_msg = (tBTA_JV_API_L2CAP_SERVER *)GKI_getbuf(sizeof(tBTA_JV_API_L2CAP_SERVER))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_L2CAP_STOP_SERVER_EVT;
        p_msg->local_psm = local_psm;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvL2capRead
**
** Description      This function reads data from an L2CAP connecti;
    tBTA_JV_RFC_CB  *p_cb = rc->p_cb;
on
**                  When the operation is complete, tBTA_JV_L2CAP_CBACK is
**                  called with BTA_JV_L2CAP_READ_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvL2capRead(UINT32 handle, UINT32 req_id, UINT8 *p_data, UINT16 len)
{
#if 0
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
#if SDP_FOR_JV_INCLUDED == TRUE
    tBTA_JV_API_L2CAP_READ *p_msg;
#endif
    tBTA_JV_L2CAP_READ evt_data;

    APPL_TRACE_API0( "BTA_JvL2capRead");

#if SDP_FOR_JV_INCLUDED == TRUE
    if(BTA_JV_L2C_FOR_SDP_HDL == handle)
    {
        if (bta_jv_cb.l2c_cb[handle].p_cback &&
            (p_msg = (tBTA_JV_API_L2CAP_READ *)GKI_getbuf(sizeof(tBTA_JV_API_L2CAP_READ))) != NULL)
        {
            p_msg->hdr.event = BTA_JV_API_L2CAP_READ_EVT;
            p_msg->handle = handle;
            p_msg->req_id = req_id;
            p_msg->p_data = p_data;
            p_msg->len = len;
            p_msg->p_cback = bta_jv_cb.l2c_cb[handle].p_cback;
            bta_sys_sendmsg(p_msg);
            status = BTA_JV_SUCCESS;
        }
    }
    else
#endif
    if (handle < BTA_JV_MAX_L2C_CONN && bta_jv_cb.l2c_cb[handle].p_cback)
    {
        status = BTA_JV_SUCCESS;
        evt_data.status = BTA_JV_FAILURE;
        evt_data.handle = handle;
        evt_data.req_id = req_id;
        evt_data.p_data = p_data;
        evt_data.len    = 0;

        if (BT_PASS == GAP_ConnReadData((UINT16)handle, p_data, len, &evt_data.len))
        {
            evt_data.status = BTA_JV_SUCCESS;
        }
        bta_jv_cb.l2c_cb[handle].p_cback(BTA_JV_L2CAP_READ_EVT, (tBTA_JV *)&evt_data);
    }

    return(status);
#endif
    return -1;
}

/*******************************************************************************
**
** Function         BTA_JvL2capReceive
**
** Description      This function reads data from an L2CAP connection
**                  When the operation is complete, tBTA_JV_L2CAP_CBACK is
**                  called with BTA_JV_L2CAP_RECEIVE_EVT.
**                  If there are more data queued in L2CAP than len, the extra data will be discarded.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvL2capReceive(UINT32 handle, UINT32 req_id, UINT8 *p_data, UINT16 len)
{
#if 0
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_L2CAP_RECEIVE evt_data;
    UINT32  left_over = 0;
    UINT16  max_len, read_len;

    APPL_TRACE_API0( "BTA_JvL2capReceive");

    if (handle < BTA_JV_MAX_L2C_CONN && bta_jv_cb.l2c_cb[handle].p_cback)
    {
        status = BTA_JV_SUCCESS;
        evt_data.status = BTA_JV_FAILURE;
        evt_data.handle = handle;
        evt_data.req_id = req_id;
        evt_data.p_data = p_data;
        evt_data.len    = 0;

        if (BT_PASS == GAP_ConnReadData((UINT16)handle, p_data, len, &evt_data.len))
        {
            evt_data.status = BTA_JV_SUCCESS;
            GAP_GetRxQueueCnt ((UINT16)handle, &left_over);
            while (left_over)
            {
                max_len = (left_over > 0xFFFF)?0xFFFF:left_over;
                GAP_ConnReadData ((UINT16)handle, NULL, max_len, &read_len);
                left_over -= read_len;
            }
        }
        bta_jv_cb.l2c_cb[handle].p_cback(BTA_JV_L2CAP_RECEIVE_EVT, (tBTA_JV *)&evt_data);
    }

    return(status);
#endif
    return -1;
}
/*******************************************************************************
**
** Function         BTA_JvL2capReady
**
** Description      This function determined if there is data to read from
**                    an L2CAP connection
**
** Returns          BTA_JV_SUCCESS, if data queue size is in *p_data_size.
**                  BTA_JV_FAILURE, if error.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvL2capReady(UINT32 handle, UINT32 *p_data_size)
{
#if 0
    tBTA_JV_STATUS status = BTA_JV_FAILURE;

    APPL_TRACE_API1( "BTA_JvL2capReady: %d", handle);
    if (p_data_size && handle < BTA_JV_MAX_L2C_CONN && bta_jv_cb.l2c_cb[handle].p_cback)
    {
        *p_data_size = 0;
#if SDP_FOR_JV_INCLUDED == TRUE
        if(BTA_JV_L2C_FOR_SDP_HDL == handle)
        {
            *p_data_size = bta_jv_cb.sdp_data_size;
            status = BTA_JV_SUCCESS;
        }
        else
#endif
        if(BT_PASS == GAP_GetRxQueueCnt((UINT16)handle, p_data_size) )
        {
            status = BTA_JV_SUCCESS;
        }
    }

    return(status);
#endif
    return -1;
}


/*******************************************************************************
**
** Function         BTA_JvL2capWrite
**
** Description      This function writes data to an L2CAP connection
**                  When the operation is complete, tBTA_JV_L2CAP_CBACK is
**                  called with BTA_JV_L2CAP_WRITE_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvL2capWrite(UINT32 handle, UINT32 req_id, UINT8 *p_data, UINT16 len)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_L2CAP_WRITE *p_msg;

    APPL_TRACE_API0( "BTA_JvL2capWrite");
    if (handle < BTA_JV_MAX_L2C_CONN && bta_jv_cb.l2c_cb[handle].p_cback &&
        (p_msg = (tBTA_JV_API_L2CAP_WRITE *)GKI_getbuf(sizeof(tBTA_JV_API_L2CAP_WRITE))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_L2CAP_WRITE_EVT;
        p_msg->handle = handle;
        p_msg->req_id = req_id;
        p_msg->p_data = p_data;
        p_msg->p_cb = &bta_jv_cb.l2c_cb[handle];
        p_msg->len = len;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvRfcommConnect
**
** Description      This function makes an RFCOMM conection to a remote BD
**                  Address.
**                  When the connection is initiated or failed to initiate,
**                  tBTA_JV_RFCOMM_CBACK is called with BTA_JV_RFCOMM_CL_INIT_EVT
**                  When the connection is established or failed,
**                  tBTA_JV_RFCOMM_CBACK is called with BTA_JV_RFCOMM_OPEN_EVT
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvRfcommConnect(tBTA_SEC sec_mask,
                           tBTA_JV_ROLE role, UINT8 remote_scn, BD_ADDR peer_bd_addr,
                           tBTA_JV_RFCOMM_CBACK *p_cback, void* user_data)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_RFCOMM_CONNECT *p_msg;

    APPL_TRACE_API0( "BTA_JvRfcommConnect");
    if (p_cback &&
        (p_msg = (tBTA_JV_API_RFCOMM_CONNECT *)GKI_getbuf(sizeof(tBTA_JV_API_RFCOMM_CONNECT))) != NULL)
    {
        p_msg->hdr.event    = BTA_JV_API_RFCOMM_CONNECT_EVT;
        p_msg->sec_mask     = sec_mask;
        p_msg->role         = role;
        p_msg->remote_scn   = remote_scn;
        memcpy(p_msg->peer_bd_addr, peer_bd_addr, sizeof(BD_ADDR));
        p_msg->p_cback      = p_cback;
        p_msg->user_data    = user_data;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvRfcommClose
**
** Description      This function closes an RFCOMM connection
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvRfcommClose(UINT32 handle)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_RFCOMM_CLOSE *p_msg;
    UINT32  hi = (handle & BTA_JV_RFC_HDL_MASK) - 1;
    UINT32  si = BTA_JV_RFC_HDL_TO_SIDX(handle);

    APPL_TRACE_API0( "BTA_JvRfcommClose");
    if (hi < BTA_JV_MAX_RFC_CONN && bta_jv_cb.rfc_cb[hi].p_cback &&
        si < BTA_JV_MAX_RFC_SR_SESSION && bta_jv_cb.rfc_cb[hi].rfc_hdl[si] &&
        (p_msg = (tBTA_JV_API_RFCOMM_CLOSE *)GKI_getbuf(sizeof(tBTA_JV_API_RFCOMM_CLOSE))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_RFCOMM_CLOSE_EVT;
        p_msg->handle = handle;
        p_msg->p_cb = &bta_jv_cb.rfc_cb[hi];
        p_msg->p_pcb = &bta_jv_cb.port_cb[p_msg->p_cb->rfc_hdl[si] - 1];
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvRfcommStartServer
**
** Description      This function starts listening for an RFCOMM connection
**                  request from a remote Bluetooth device.  When the server is
**                  started successfully, tBTA_JV_RFCOMM_CBACK is called
**                  with BTA_JV_RFCOMM_START_EVT.
**                  When the connection is established, tBTA_JV_RFCOMM_CBACK
**                  is called with BTA_JV_RFCOMM_OPEN_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvRfcommStartServer(tBTA_SEC sec_mask,
                           tBTA_JV_ROLE role, UINT8 local_scn, UINT8 max_session,
                           tBTA_JV_RFCOMM_CBACK *p_cback, void* user_data)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_RFCOMM_SERVER *p_msg;

    APPL_TRACE_API0( "BTA_JvRfcommStartServer");
    if (p_cback &&
        (p_msg = (tBTA_JV_API_RFCOMM_SERVER *)GKI_getbuf(sizeof(tBTA_JV_API_RFCOMM_SERVER))) != NULL)
    {
        if (max_session == 0)
            max_session = 1;
        if (max_session > BTA_JV_MAX_RFC_SR_SESSION)
        {
            APPL_TRACE_DEBUG2( "max_session is too big. use max (%d)", max_session, BTA_JV_MAX_RFC_SR_SESSION);
            max_session = BTA_JV_MAX_RFC_SR_SESSION;
        }
        p_msg->hdr.event = BTA_JV_API_RFCOMM_START_SERVER_EVT;
        p_msg->sec_mask = sec_mask;
        p_msg->role = role;
        p_msg->local_scn = local_scn;
        p_msg->max_session = max_session;
        p_msg->p_cback = p_cback;
        p_msg->user_data = user_data; //caller's private data
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvRfcommStopServer
**
** Description      This function stops the RFCOMM server. If the server has an
**                  active connection, it would be closed.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvRfcommStopServer(UINT32 handle)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_RFCOMM_SERVER *p_msg;
    APPL_TRACE_API0( "BTA_JvRfcommStopServer");
    if ((p_msg = (tBTA_JV_API_RFCOMM_SERVER *)GKI_getbuf(sizeof(tBTA_JV_API_RFCOMM_SERVER))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_RFCOMM_STOP_SERVER_EVT;
        p_msg->rfc_handle = handle;
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvRfcommRead
**
** Description      This function reads data from an RFCOMM connection
**                  The actual size of data read is returned in p_len.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvRfcommRead(UINT32 handle, UINT32 req_id, UINT8 *p_data, UINT16 len)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_RFCOMM_READ *p_msg;
    UINT32  hi = (handle & BTA_JV_RFC_HDL_MASK) - 1;
    UINT32  si = BTA_JV_RFC_HDL_TO_SIDX(handle);

    APPL_TRACE_API0( "BTA_JvRfcommRead");
    if (hi < BTA_JV_MAX_RFC_CONN && bta_jv_cb.rfc_cb[hi].p_cback &&
        si < BTA_JV_MAX_RFC_SR_SESSION && bta_jv_cb.rfc_cb[hi].rfc_hdl[si] &&
        (p_msg = (tBTA_JV_API_RFCOMM_READ *)GKI_getbuf(sizeof(tBTA_JV_API_RFCOMM_READ))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_RFCOMM_READ_EVT;
        p_msg->handle = handle;
        p_msg->req_id = req_id;
        p_msg->p_data = p_data;
        p_msg->len = len;
        p_msg->p_cb = &bta_jv_cb.rfc_cb[hi];
        p_msg->p_pcb = &bta_jv_cb.port_cb[p_msg->p_cb->rfc_hdl[si] - 1];
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvRfcommGetPortHdl
**
** Description    This function fetches the rfcomm port handle
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
UINT16 BTA_JvRfcommGetPortHdl(UINT32 handle)
{
    UINT32  hi = (handle & BTA_JV_RFC_HDL_MASK) - 1;
    UINT32  si = BTA_JV_RFC_HDL_TO_SIDX(handle);

    if (hi < BTA_JV_MAX_RFC_CONN &&
        si < BTA_JV_MAX_RFC_SR_SESSION && bta_jv_cb.rfc_cb[hi].rfc_hdl[si])
        return bta_jv_cb.port_cb[bta_jv_cb.rfc_cb[hi].rfc_hdl[si] - 1].port_handle;
    else
        return 0xffff;
}


/*******************************************************************************
**
** Function         BTA_JvRfcommReady
**
** Description      This function determined if there is data to read from
**                  an RFCOMM connection
**
** Returns          BTA_JV_SUCCESS, if data queue size is in *p_data_size.
**                  BTA_JV_FAILURE, if error.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvRfcommReady(UINT32 handle, UINT32 *p_data_size)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    UINT16          size = 0;
    UINT32  hi = (handle & BTA_JV_RFC_HDL_MASK) - 1;
    UINT32  si = BTA_JV_RFC_HDL_TO_SIDX(handle);

    APPL_TRACE_API0( "BTA_JvRfcommReady");
    if (hi < BTA_JV_MAX_RFC_CONN && bta_jv_cb.rfc_cb[hi].p_cback &&
        si < BTA_JV_MAX_RFC_SR_SESSION && bta_jv_cb.rfc_cb[hi].rfc_hdl[si])
    {
        if(PORT_GetRxQueueCnt(bta_jv_cb.rfc_cb[hi].rfc_hdl[si], &size) == PORT_SUCCESS)
        {
            status = BTA_JV_SUCCESS;
        }
    }
    *p_data_size = size;
    return(status);
}

/*******************************************************************************
**
** Function         BTA_JvRfcommWrite
**
** Description      This function writes data to an RFCOMM connection
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
tBTA_JV_STATUS BTA_JvRfcommWrite(UINT32 handle, UINT32 req_id)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    tBTA_JV_API_RFCOMM_WRITE *p_msg;
    UINT32  hi = (handle & BTA_JV_RFC_HDL_MASK) - 1;
    UINT32  si = BTA_JV_RFC_HDL_TO_SIDX(handle);

    APPL_TRACE_API0( "BTA_JvRfcommWrite");
    APPL_TRACE_DEBUG3( "handle:0x%x, hi:%d, si:%d", handle, hi, si);
    if (hi < BTA_JV_MAX_RFC_CONN && bta_jv_cb.rfc_cb[hi].p_cback &&
        si < BTA_JV_MAX_RFC_SR_SESSION && bta_jv_cb.rfc_cb[hi].rfc_hdl[si] &&
        (p_msg = (tBTA_JV_API_RFCOMM_WRITE *)GKI_getbuf(sizeof(tBTA_JV_API_RFCOMM_WRITE))) != NULL)
    {
        p_msg->hdr.event = BTA_JV_API_RFCOMM_WRITE_EVT;
        p_msg->handle = handle;
        p_msg->req_id = req_id;
        p_msg->p_cb = &bta_jv_cb.rfc_cb[hi];
        p_msg->p_pcb = &bta_jv_cb.port_cb[p_msg->p_cb->rfc_hdl[si] - 1];
        APPL_TRACE_API0( "write ok");
        bta_sys_sendmsg(p_msg);
        status = BTA_JV_SUCCESS;
    }

    return(status);
}

