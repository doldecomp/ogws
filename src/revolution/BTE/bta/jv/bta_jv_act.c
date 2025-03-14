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
 *  This file contains action functions for advanced audio.
 *
 ******************************************************************************/

#include <hardware/bluetooth.h>
#include <arpa/inet.h>

#include "bt_types.h"
#include "gki.h"
#include "bd.h"
#include "utl.h"
#include "bta_sys.h"
#include "bta_api.h"
#include "bta_jv_api.h"
#include "bta_jv_int.h"
#include "bta_jv_co.h"
#include "btm_api.h"
#include "btm_int.h"
#include "sdp_api.h"
#include "l2c_api.h"
#include "port_api.h"
#include <string.h>
#include "rfcdefs.h"
#include "avct_api.h"
#include "avdt_api.h"


#include <cutils/log.h>
#define info(fmt, ...)  ALOGI ("%s: " fmt,__FUNCTION__,  ## __VA_ARGS__)
#define debug(fmt, ...) ALOGD ("%s: " fmt,__FUNCTION__,  ## __VA_ARGS__)
#define error(fmt, ...) ALOGE ("## ERROR : %s: " fmt "##",__FUNCTION__,  ## __VA_ARGS__)
#define asrt(s) if(!(s)) ALOGE ("## %s assert %s failed at line:%d ##",__FUNCTION__, #s, __LINE__)



#define HDL2CB(handle) \
    UINT32  __hi = ((handle) & BTA_JV_RFC_HDL_MASK) - 1; \
    UINT32  __si = BTA_JV_RFC_HDL_TO_SIDX(handle); \
    tBTA_JV_RFC_CB  *p_cb = &bta_jv_cb.rfc_cb[__hi]; \
    tBTA_JV_PCB   *p_pcb = &bta_jv_cb.port_cb[p_cb->rfc_hdl[__si] - 1]

extern void uuid_to_string(bt_uuid_t *p_uuid, char *str);
static inline void logu(const char* title, const uint8_t * p_uuid)
{
    char uuids[128];
    uuid_to_string((bt_uuid_t*)p_uuid, uuids);
    ALOGD("%s: %s", title, uuids);
}


static tBTA_JV_PCB * bta_jv_add_rfc_port(tBTA_JV_RFC_CB *p_cb);

/*******************************************************************************
**
** Function     bta_jv_get_local_device_addr_cback
**
** Description  Callback from btm after local bdaddr is read
**
** Returns      void
**
*******************************************************************************/
static void bta_jv_get_local_device_addr_cback(BD_ADDR bd_addr)
{
    if(bta_jv_cb.p_dm_cback)
        bta_jv_cb.p_dm_cback(BTA_JV_LOCAL_ADDR_EVT, (tBTA_JV *)bd_addr, 0);
}

/*******************************************************************************
**
** Function     bta_jv_get_remote_device_name_cback
**
** Description  Callback from btm after remote name is read
**
** Returns      void
**
*******************************************************************************/
static void bta_jv_get_remote_device_name_cback(tBTM_REMOTE_DEV_NAME *p_name)
{
    tBTA_JV evt_data;
    evt_data.p_name = p_name->remote_bd_name;
    if(bta_jv_cb.p_dm_cback)
        bta_jv_cb.p_dm_cback(BTA_JV_REMOTE_NAME_EVT, &evt_data, 0);
}

/*******************************************************************************
**
** Function     bta_jv_alloc_sec_id
**
** Description  allocate a security id
**
** Returns
**
*******************************************************************************/
UINT8 bta_jv_alloc_sec_id(void)
{
    UINT8 ret = 0;
    int i;
    for(i=0; i<BTA_JV_NUM_SERVICE_ID; i++)
    {
        if(0 == bta_jv_cb.sec_id[i])
        {
            bta_jv_cb.sec_id[i] = BTA_JV_FIRST_SERVICE_ID + i;
            ret = bta_jv_cb.sec_id[i];
            break;
        }
    }
    return ret;

}

/*******************************************************************************
**
** Function     bta_jv_free_sec_id
**
** Description  free the given security id
**
** Returns
**
*******************************************************************************/
static void bta_jv_free_sec_id(UINT8 *p_sec_id)
{
    UINT8 sec_id = *p_sec_id;
    *p_sec_id = 0;
    if(sec_id >= BTA_JV_FIRST_SERVICE_ID && sec_id <= BTA_JV_LAST_SERVICE_ID)
    {
        BTM_SecClrService(sec_id);
        bta_jv_cb.sec_id[sec_id - BTA_JV_FIRST_SERVICE_ID] = 0;
    }
}

/*******************************************************************************
**
** Function     bta_jv_alloc_rfc_cb
**
** Description  allocate a control block for the given port handle
**
** Returns
**
*******************************************************************************/
tBTA_JV_RFC_CB * bta_jv_alloc_rfc_cb(UINT16 port_handle, tBTA_JV_PCB **pp_pcb)
{
    tBTA_JV_RFC_CB *p_cb = NULL;
    tBTA_JV_PCB *p_pcb;
    int i;
    for(i=0; i<BTA_JV_MAX_RFC_CONN; i++)
    {
        if(0 == bta_jv_cb.rfc_cb[i].handle )
        {
            p_cb = &bta_jv_cb.rfc_cb[i];
            p_cb->handle            = i + 1;
            p_cb->max_sess          = 1;
            p_cb->rfc_hdl[0]        = port_handle;
            APPL_TRACE_DEBUG2( "bta_jv_alloc_rfc_cb port_handle:%d handle:%d",
                port_handle, p_cb->handle);
            p_pcb = &bta_jv_cb.port_cb[port_handle - 1];
            p_pcb->handle = p_cb->handle;
            p_pcb->port_handle = port_handle;
            *pp_pcb = p_pcb;
            break;
        }
    }
    return p_cb;
}

/*******************************************************************************
**
** Function     bta_jv_rfc_port_to_pcb
**
** Description  find the port control block associated with the given port handle
**
** Returns
**
*******************************************************************************/
tBTA_JV_PCB * bta_jv_rfc_port_to_pcb(UINT16 port_handle)
{
    tBTA_JV_PCB *p_pcb = NULL;

    if ((port_handle > 0) && (port_handle <= MAX_RFC_PORTS) && bta_jv_cb.port_cb[port_handle - 1].handle)
    {
        p_pcb = &bta_jv_cb.port_cb[port_handle - 1];
    }

    return p_pcb;
}

/*******************************************************************************
**
** Function     bta_jv_rfc_port_to_cb
**
** Description  find the RFCOMM control block associated with the given port handle
**
** Returns
**
*******************************************************************************/
tBTA_JV_RFC_CB * bta_jv_rfc_port_to_cb(UINT16 port_handle)
{
    tBTA_JV_RFC_CB *p_cb = NULL;
    UINT32 handle;

    if ((port_handle > 0) && (port_handle <= MAX_RFC_PORTS) && bta_jv_cb.port_cb[port_handle - 1].handle)
    {
        handle = bta_jv_cb.port_cb[port_handle - 1].handle;
        handle &= BTA_JV_RFC_HDL_MASK;
        if (handle)
            p_cb = &bta_jv_cb.rfc_cb[handle - 1];
    }
    return p_cb;
}

/*******************************************************************************
**
** Function     bta_jv_free_rfc_pcb
**
** Description  free the given port control block
**
** Returns
**
*******************************************************************************/
tBTA_JV_STATUS bta_jv_free_rfc_pcb(tBTA_JV_PCB *p_pcb)
{
    tBTA_JV_STATUS status = BTA_JV_SUCCESS;
    BOOLEAN         remove = FALSE;
    BOOLEAN         is_server = TRUE;
    UINT16          port_handle;

    APPL_TRACE_DEBUG2( "bta_jv_free_rfc_pcb handle:%d s:%d", p_pcb->port_handle, p_pcb->state);

    if (p_pcb->port_handle)
    {
        if(BTA_JV_ST_NONE != p_pcb->state)
        {
            remove = TRUE;
            if(p_pcb->state <= BTA_JV_ST_CL_MAX)
                is_server = FALSE;
            port_handle = p_pcb->port_handle;
        }
        p_pcb->port_handle = 0;
        p_pcb->state = BTA_JV_ST_NONE;

        //Initialize congestion flags
        p_pcb->cong = FALSE;

        if(remove)
        {
            if(is_server)
            {
                if(RFCOMM_RemoveServer(port_handle) != PORT_SUCCESS)
                    status = BTA_JV_FAILURE;
            }
            else
            {
                if(RFCOMM_RemoveConnection(port_handle) != PORT_SUCCESS)
                    status = BTA_JV_FAILURE;
            }
        }
    }
    return status;
}

/*******************************************************************************
**
** Function     bta_jv_free_rfc_cb
**
** Description  free the given RFCOMM control block
**
** Returns
**
*******************************************************************************/
tBTA_JV_STATUS bta_jv_free_rfc_cb(tBTA_JV_RFC_CB *p_cb)
{
    tBTA_JV_STATUS status = BTA_JV_SUCCESS;
    UINT8           i;
    APPL_TRACE_DEBUG1( "bta_jv_free_rfc_cb max_sess:%d", p_cb->max_sess);
    for (i=0; i<p_cb->max_sess; i++)
    {
        APPL_TRACE_DEBUG2( "[%d]: port=%d", i, p_cb->rfc_hdl[i]);
        if (p_cb->rfc_hdl[i])
            bta_jv_free_rfc_pcb (&bta_jv_cb.port_cb[p_cb->rfc_hdl[i] - 1]);
    }

    p_cb->scn = 0;
    bta_jv_free_sec_id(&p_cb->sec_id);
    p_cb->p_cback = NULL;
    p_cb->handle = 0;

    return status;
}
static tBTA_JV_STATUS bta_jv_free_rfc_listen_cb(tBTA_JV_RFC_CB *p_cb)
{
    tBTA_JV_STATUS status = BTA_JV_SUCCESS;
    UINT8           i;
    debug( "max_sess:%d", p_cb->max_sess);
    for (i=0; i<p_cb->max_sess; i++)
    {
        APPL_TRACE_DEBUG2( "[%d]: port=%d", i, p_cb->rfc_hdl[i]);
        if (p_cb->rfc_hdl[i])
        {
            tBTA_JV_PCB *p_pcb = &bta_jv_cb.port_cb[p_cb->rfc_hdl[i] - 1];
            if(p_pcb->state == BTA_JV_ST_SR_LISTEN)
            {
                debug( "free listen pcb: scn:%d, ueser_data:%d", p_cb->scn, (int)p_pcb->user_data);
                p_pcb->user_data = 0;
                bta_jv_free_rfc_pcb (p_pcb);
                p_cb->max_sess = 1;
                break;
            }
        }
    }
    //p_cb->scn = 0;
    bta_jv_free_sec_id(&p_cb->sec_id);
    //p_cb->p_cback = NULL;
    //p_cb->handle = 0;
    return status;
}

/*******************************************************************************
**
** Function     bta_jv_free_l2c_cb
**
** Description  free the given L2CAP control block
**
** Returns
**
*******************************************************************************/
tBTA_JV_STATUS bta_jv_free_l2c_cb(tBTA_JV_L2C_CB *p_cb)
{
#if 0
    tBTA_JV_STATUS status = BTA_JV_SUCCESS;

    if(BTA_JV_ST_NONE != p_cb->state)
    {
#if SDP_FOR_JV_INCLUDED == TRUE
        if(BTA_JV_L2C_FOR_SDP_HDL == p_cb->handle)
        {
            bta_jv_cb.sdp_data_size = 0;
            if(SDP_ConnClose(bta_jv_cb.sdp_for_jv))
            {
                bta_jv_cb.sdp_for_jv = 0;
            }
            else
                status = BTA_JV_FAILURE;
        }
        else
#endif
        if(GAP_ConnClose(p_cb->handle) != BT_PASS)
            status = BTA_JV_FAILURE;
    }
    p_cb->psm = 0;
    p_cb->state = BTA_JV_ST_NONE;
    bta_jv_free_sec_id(&p_cb->sec_id);
    p_cb->p_cback = NULL;
    return status;
#endif
    return 0;
}

/*******************************************************************************
**
** Function     bta_jv_alloc_sdp_id
**
** Description  allocate a SDP id for the given SDP record handle
**
** Returns
**
*******************************************************************************/
UINT32 bta_jv_alloc_sdp_id(UINT32 sdp_handle)
{
    int j;
    UINT32 id = 0;

    /* find a free entry */
    for (j = 0; j < BTA_JV_MAX_SDP_REC; j++)
    {
        if (bta_jv_cb.sdp_handle[j] == 0)
        {
            bta_jv_cb.sdp_handle[j] = sdp_handle;
            id = (UINT32)(j + 1);
            break;
        }
    }
    /* the SDP record handle reported is the (index + 1) to control block */
    return id;
}

/*******************************************************************************
**
** Function     bta_jv_free_sdp_id
**
** Description  free the sdp id
**
** Returns
**
*******************************************************************************/
void bta_jv_free_sdp_id(UINT32 sdp_id)
{
    if(sdp_id > 0 && sdp_id <= BTA_JV_MAX_SDP_REC)
    {
        bta_jv_cb.sdp_handle[sdp_id - 1] = 0;
    }
}

/*******************************************************************************
**
** Function     bta_jv_get_sdp_handle
**
** Description  find the SDP handle associated with the given sdp id
**
** Returns
**
*******************************************************************************/
UINT32 bta_jv_get_sdp_handle(UINT32 sdp_id)
{
    UINT32 sdp_handle = 0;

    if(sdp_id > 0 && sdp_id <= BTA_JV_MAX_SDP_REC)
    {
        sdp_handle = bta_jv_cb.sdp_handle[sdp_id - 1];
    }
    return sdp_handle;
}

/*******************************************************************************
**
** Function     bta_jv_check_psm
**
** Description  for now use only the legal PSM per JSR82 spec
**
** Returns      TRUE, if allowed
**
*******************************************************************************/
BOOLEAN bta_jv_check_psm(UINT16 psm)
{
    BOOLEAN ret = FALSE;

    if(L2C_IS_VALID_PSM(psm) )
    {
        if(psm < 0x1001)
        {
            /* see if this is defined by spec */
            switch(psm)
            {
            case SDP_PSM:           /* 1 */
            case BT_PSM_RFCOMM:     /* 3 */
                /* do not allow java app to use these 2 PSMs */
                break;

            case TCS_PSM_INTERCOM:  /* 5 */
            case TCS_PSM_CORDLESS:  /* 7 */
                if( FALSE == bta_sys_is_register(BTA_ID_CT) &&
                    FALSE == bta_sys_is_register(BTA_ID_CG) )
                    ret = TRUE;
                break;

            case BT_PSM_BNEP:       /* F */
                if(FALSE == bta_sys_is_register(BTA_ID_PAN))
                    ret = TRUE;
                break;

            case HID_PSM_CONTROL:   /* 0x11 */
            case HID_PSM_INTERRUPT: /* 0x13 */
                //FIX: allow HID Device and HID Host to coexist
                if( FALSE == bta_sys_is_register(BTA_ID_HD) ||
                    FALSE == bta_sys_is_register(BTA_ID_HH) )
                    ret = TRUE;
                break;

            case AVCT_PSM:          /* 0x17 */
            case AVDT_PSM:          /* 0x19 */
                if ((FALSE == bta_sys_is_register(BTA_ID_AV)) &&
                   (FALSE == bta_sys_is_register(BTA_ID_AVK)))
                    ret = TRUE;
                break;

            default:
                ret = TRUE;
                break;
            }
        }
        else
            ret = TRUE;
    }
    return ret;

}

/*******************************************************************************
**
** Function     bta_jv_enable
**
** Description  Initialises the JAVA I/F
**
** Returns      void
**
*******************************************************************************/
void bta_jv_enable(tBTA_JV_MSG *p_data)
{
    tBTA_JV_STATUS status = BTA_JV_SUCCESS;
    bta_jv_cb.p_dm_cback = p_data->enable.p_cback;
    bta_jv_cb.p_dm_cback(BTA_JV_ENABLE_EVT, (tBTA_JV *)&status, 0);
}

/*******************************************************************************
**
** Function     bta_jv_disable
**
** Description  Disables the BT device manager
**              free the resources used by java
**
** Returns      void
**
*******************************************************************************/
void bta_jv_disable (tBTA_JV_MSG *p_data)
{
    int i;

    bta_jv_cb.p_dm_cback = NULL;
    /* delete the SDP records created by java apps */
    for(i=0; i<BTA_JV_MAX_SDP_REC; i++)
    {
        if(bta_jv_cb.sdp_handle[i])
        {
            APPL_TRACE_DEBUG1( "delete SDP record: %d", bta_jv_cb.sdp_handle[i]);
            SDP_DeleteRecord(bta_jv_cb.sdp_handle[i]);
            bta_jv_cb.sdp_handle[i] = 0;
        }
    }

    /* free the SCNs allocated by java apps */
    for(i=0; i<BTA_JV_MAX_SCN; i++)
    {
        if(bta_jv_cb.scn[i])
        {
            APPL_TRACE_DEBUG1( "free scn: %d", (i+1));
            BTM_FreeSCN((UINT8)(i+1));
            bta_jv_cb.scn[i] = FALSE;
        }
    }

    /* disconnect L2CAP connections */
    for(i=0; i<BTA_JV_MAX_L2C_CONN; i++)
    {
        bta_jv_free_l2c_cb(&bta_jv_cb.l2c_cb[i]);
    }

    /* disconnect RFCOMM connections */
    for(i=0; i<BTA_JV_MAX_RFC_CONN; i++)
    {
        bta_jv_free_rfc_cb(&bta_jv_cb.rfc_cb[i]);
    }

    /* free the service records allocated by java apps */
    for(i=0; i<BTA_JV_NUM_SERVICE_ID; i++)
    {
        if(bta_jv_cb.sec_id[i])
        {
            BTM_SecClrService(bta_jv_cb.sec_id[i]);
            bta_jv_cb.sec_id[i] = 0;
        }
    }
}

/*******************************************************************************
**
** Function     bta_jv_set_discoverability
**
** Description  Sets discoverability
**
** Returns      void
**
*******************************************************************************/
void bta_jv_set_discoverability (tBTA_JV_MSG *p_data)
{
    tBTA_JV     evt_data;

    evt_data.set_discover.status = BTA_JV_FAILURE;
    /* initialize the default value for the event as the current mode */
    evt_data.set_discover.disc_mode = BTM_ReadDiscoverability(NULL, NULL);

    if(BTM_SUCCESS == BTM_SetDiscoverability((UINT8)p_data->set_discoverability.disc_mode, 0, 0))
    {
        evt_data.set_discover.status     = BTA_JV_SUCCESS;
        /* update the mode, after BTM_SetDiscoverability() is successful */
        evt_data.set_discover.disc_mode  = p_data->set_discoverability.disc_mode;
    }

    if(bta_jv_cb.p_dm_cback)
        bta_jv_cb.p_dm_cback(BTA_JV_SET_DISCOVER_EVT, &evt_data, 0);
}

/*******************************************************************************
**
** Function     bta_jv_get_local_device_addr
**
** Description  Reads the local Bluetooth device address
**
** Returns      void
**
*******************************************************************************/
void bta_jv_get_local_device_addr(tBTA_JV_MSG *p_data)
{
    BTM_ReadLocalDeviceAddr((tBTM_CMPL_CB *)bta_jv_get_local_device_addr_cback);
}

/*******************************************************************************
**
** Function     bta_jv_get_local_device_name
**
** Description  Reads the local Bluetooth device name
**
** Returns      void
**
*******************************************************************************/
void bta_jv_get_local_device_name(tBTA_JV_MSG *p_data)
{
    tBTA_JV evt_data;
    char *name;

    BTM_ReadLocalDeviceName(&name);
    evt_data.p_name = (UINT8*)name;
    if(bta_jv_cb.p_dm_cback)
        bta_jv_cb.p_dm_cback(BTA_JV_LOCAL_NAME_EVT, &evt_data, 0);
}

/*******************************************************************************
**
** Function     bta_jv_get_remote_device_name
**
** Description  Reads the local Bluetooth device name
**
** Returns      void
**
*******************************************************************************/
void bta_jv_get_remote_device_name(tBTA_JV_MSG *p_data)
{

    BTM_ReadRemoteDeviceName(p_data->get_rmt_name.bd_addr,
        (tBTM_CMPL_CB *)bta_jv_get_remote_device_name_cback);
}

/*******************************************************************************
**
** Function     bta_jv_set_service_class
**
** Description  update the service class field of device class
**
** Returns      void
**
*******************************************************************************/
void bta_jv_set_service_class (tBTA_JV_MSG *p_data)
{
    tBTA_UTL_COD cod;

    /* set class of device */
    /* BTA_JvSetServiceClass(UINT32 service) assumes that the service class passed to the API function as defined in the assigned number page.
    For example: the object transfer bit is bit 20 of the 24-bit Class of device; the value of this bit is 0x00100000 (value 1)
    Our btm_api.h defines this bit as #define BTM_COD_SERVICE_OBJ_TRANSFER        0x1000 // (value 2)
    This reflects that the service class defined at btm is UINT16, which starts at bit 8 of the 24 bit Class of Device
    The following statement converts from (value 1) into (value 2) */
    cod.service = (p_data->set_service.service >> 8);
    utl_set_device_class(&cod, BTA_UTL_SET_COD_SERVICE_CLASS);
}

/*******************************************************************************
**
** Function     bta_jv_sec_cback
**
** Description  callback function to handle set encryption complete event
**
** Returns      void
**
*******************************************************************************/
static void bta_jv_sec_cback (BD_ADDR bd_addr, void *p_ref_data, tBTM_STATUS result)
{
    tBTA_JV_SET_ENCRYPTION  set_enc;
    if(bta_jv_cb.p_dm_cback)
    {
        bdcpy(set_enc.bd_addr, bd_addr);
        set_enc.status = result;
        if (result > BTA_JV_BUSY)
            set_enc.status = BTA_JV_FAILURE;
        bta_jv_cb.p_dm_cback(BTA_JV_SET_ENCRYPTION_EVT, (tBTA_JV *)&set_enc, 0);
    }
}

/*******************************************************************************
**
** Function     bta_jv_set_encryption
**
** Description  Reads the local Bluetooth device name
**
** Returns      void
**
*******************************************************************************/
void bta_jv_set_encryption(tBTA_JV_MSG *p_data)
{
    BTM_SetEncryption(p_data->set_encrypt.bd_addr, bta_jv_sec_cback, NULL);
}

/*******************************************************************************
**
** Function     bta_jv_get_scn
**
** Description  obtain a free SCN
**
** Returns      void
**
*******************************************************************************/
void bta_jv_get_scn(tBTA_JV_MSG *p_data)
{
#if 0
    UINT8   scn;
    scn = BTM_AllocateSCN();
    if(scn)
        bta_jv_cb.scn[scn-1] = TRUE;
    if(bta_jv_cb.p_dm_cback)
        bta_jv_cb.p_dm_cback(BTA_JV_GET_SCN_EVT, (tBTA_JV *)&scn);
#endif
}

/*******************************************************************************
**
** Function     bta_jv_free_scn
**
** Description  free a SCN
**
** Returns      void
**
*******************************************************************************/
void bta_jv_free_scn(tBTA_JV_MSG *p_data)
{
    UINT8   scn = p_data->free_scn.scn;

    if (scn > 0 && scn <= BTA_JV_MAX_SCN && bta_jv_cb.scn[scn-1])
    {
        /* this scn is used by JV */
        bta_jv_cb.scn[scn-1] = FALSE;
        BTM_FreeSCN(scn);
    }
}
static inline tBT_UUID shorten_sdp_uuid(const tBT_UUID* u)
{
    static uint8_t bt_base_uuid[] =
       {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };

    logu("in, uuid:", u);
    debug("uuid len:%d", u->len);
    if(u->len == 16)
    {
        if(memcmp(&u->uu.uuid128[4], &bt_base_uuid[4], 12) == 0)
        {
            tBT_UUID su;
            memset(&su, 0, sizeof(su));
            if(u->uu.uuid128[0] == 0 && u->uu.uuid128[1] == 0)
            {
                su.len = 2;
                uint16_t u16;
                memcpy(&u16, &u->uu.uuid128[2], sizeof(u16));
                su.uu.uuid16 = ntohs(u16);
                debug("shorten to 16 bits uuid: %x", su.uu.uuid16);
            }
            else
            {
                su.len = 4;
                uint32_t u32;
                memcpy(&u32, &u->uu.uuid128[0], sizeof(u32));
                su.uu.uuid32 = ntohl(u32);
                debug("shorten to 32 bits uuid: %x", su.uu.uuid32);
            }
            return su;
        }
    }
    debug("cannot shorten none-reserved 128 bits uuid");
    return *u;
}

/*******************************************************************************
**
** Function     bta_jv_start_discovery_cback
**
** Description  Callback for Start Discovery
**
** Returns      void
**
*******************************************************************************/
static void bta_jv_start_discovery_cback(UINT16 result, void * user_data)
{
    tBTA_JV_STATUS status;
    UINT8          old_sdp_act = bta_jv_cb.sdp_active;

    debug( "bta_jv_start_discovery_cback res: 0x%x", result);

    bta_jv_cb.sdp_active = BTA_JV_SDP_ACT_NONE;
    if(bta_jv_cb.p_dm_cback)
    {
        if (old_sdp_act == BTA_JV_SDP_ACT_CANCEL)
        {
            debug("BTA_JV_SDP_ACT_CANCEL");
            status = BTA_JV_SUCCESS;
            bta_jv_cb.p_dm_cback(BTA_JV_CANCEL_DISCVRY_EVT, (tBTA_JV *)&status, user_data);
        }
        else
        {
            tBTA_JV_DISCOVERY_COMP dcomp;
            dcomp.scn = 0;
            status = BTA_JV_FAILURE;
            if (result == SDP_SUCCESS || result == SDP_DB_FULL)
            {
                tSDP_DISC_REC       *p_sdp_rec = NULL;
                tSDP_PROTOCOL_ELEM  pe;
                logu("bta_jv_cb.uuid", bta_jv_cb.uuid.uu.uuid128);
                tBT_UUID su = shorten_sdp_uuid(&bta_jv_cb.uuid);
                logu("shorten uuid:", su.uu.uuid128);
                p_sdp_rec = SDP_FindServiceUUIDInDb(p_bta_jv_cfg->p_sdp_db, &su, p_sdp_rec);
                debug("p_sdp_rec:%p", p_sdp_rec);
                if(p_sdp_rec && SDP_FindProtocolListElemInRec(p_sdp_rec, UUID_PROTOCOL_RFCOMM, &pe))
                {
                    dcomp.scn = (UINT8) pe.params[0];
                    status = BTA_JV_SUCCESS;
                }
            }

            dcomp.status = status;
            bta_jv_cb.p_dm_cback(BTA_JV_DISCOVERY_COMP_EVT, (tBTA_JV *)&dcomp, user_data);
        }
        //free sdp db
        //utl_freebuf(&(p_bta_jv_cfg->p_sdp_db));
    }
}

/*******************************************************************************
**
** Function     bta_jv_start_discovery
**
** Description  Discovers services on a remote device
**
** Returns      void
**
*******************************************************************************/
void bta_jv_start_discovery(tBTA_JV_MSG *p_data)
{
    tBTA_JV_STATUS status = BTA_JV_FAILURE;
    debug("in, sdp_active:%d", bta_jv_cb.sdp_active);
    if (bta_jv_cb.sdp_active != BTA_JV_SDP_ACT_NONE)
    {
        /* SDP is still in progress */
        status = BTA_JV_BUSY;
        if(bta_jv_cb.p_dm_cback)
            bta_jv_cb.p_dm_cback(BTA_JV_DISCOVERY_COMP_EVT, (tBTA_JV *)&status, p_data->start_discovery.user_data);
        return;
    }
/*
    if(p_data->start_discovery.num_uuid == 0)
    {
        p_data->start_discovery.num_uuid = 1;
        p_data->start_discovery.uuid_list[0].len       = 2;
        p_data->start_discovery.uuid_list[0].uu.uuid16 = UUID_SERVCLASS_PUBLIC_BROWSE_GROUP;
    }
*/
    /* init the database/set up the filter */
    debug("call SDP_InitDiscoveryDb, p_data->start_discovery.num_uuid:%d",
        p_data->start_discovery.num_uuid);
    SDP_InitDiscoveryDb (p_bta_jv_cfg->p_sdp_db, p_bta_jv_cfg->sdp_db_size,
                    p_data->start_discovery.num_uuid, p_data->start_discovery.uuid_list, 0, NULL);

    /* tell SDP to keep the raw data */
    p_bta_jv_cfg->p_sdp_db->raw_data = p_bta_jv_cfg->p_sdp_raw_data;
    p_bta_jv_cfg->p_sdp_db->raw_size = p_bta_jv_cfg->sdp_raw_size;

    bta_jv_cb.p_sel_raw_data     = 0;
    bta_jv_cb.uuid = p_data->start_discovery.uuid_list[0];

    bta_jv_cb.sdp_active = BTA_JV_SDP_ACT_YES;
    if (!SDP_ServiceSearchAttributeRequest2(p_data->start_discovery.bd_addr,
                                   p_bta_jv_cfg->p_sdp_db,
                                   bta_jv_start_discovery_cback, p_data->start_discovery.user_data))
    {
        bta_jv_cb.sdp_active = BTA_JV_SDP_ACT_NONE;
        /* failed to start SDP. report the failure right away */
        if(bta_jv_cb.p_dm_cback)
            bta_jv_cb.p_dm_cback(BTA_JV_DISCOVERY_COMP_EVT, (tBTA_JV *)&status, p_data->start_discovery.user_data);
    }
    /*
    else report the result when the cback is called
    */
}

/*******************************************************************************
**
** Function     bta_jv_cancel_discovery
**
** Description  Cancels an active discovery
**
** Returns      void
**
*******************************************************************************/
void bta_jv_cancel_discovery(tBTA_JV_MSG *p_data)
{
    tBTA_JV_STATUS status = BTA_JV_SUCCESS;
    if (bta_jv_cb.sdp_active == BTA_JV_SDP_ACT_YES)
    {
        if (SDP_CancelServiceSearch (p_bta_jv_cfg->p_sdp_db))
        {
            bta_jv_cb.sdp_active = BTA_JV_SDP_ACT_CANCEL;
            return;
        }
    }
    if(bta_jv_cb.p_dm_cback)
        bta_jv_cb.p_dm_cback(BTA_JV_CANCEL_DISCVRY_EVT, (tBTA_JV *)&status, p_data->cancel_discovery.user_data);
}

/*******************************************************************************
**
** Function     bta_jv_get_services_length
**
** Description  Obtain the length of each record in the SDP DB.
**
** Returns      void
**
*******************************************************************************/
void bta_jv_get_services_length(tBTA_JV_MSG *p_data)
{
#if 0
    tBTA_JV_SERVICES_LEN    evt_data;
    UINT8   *p, *np, *op, type;
    UINT32  raw_used, raw_cur;
    UINT32  len;

    evt_data.num_services = -1;
    evt_data.p_services_len = p_data->get_services_length.p_services_len;
    if(p_bta_jv_cfg->p_sdp_db->p_first_rec)
    {
        /* the database is valid */
        evt_data.num_services = 0;
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
            if(p_data->get_services_length.inc_hdr)
            {
                evt_data.p_services_len[evt_data.num_services++] = len + np - op;
            }
            else
            {
                evt_data.p_services_len[evt_data.num_services++] = len;
            }
        } /* end of while */
    }

    if(bta_jv_cb.p_dm_cback)
        bta_jv_cb.p_dm_cback(BTA_JV_SERVICES_LEN_EVT, (tBTA_JV *)&evt_data);
#endif
}

/*******************************************************************************
**
** Function     bta_jv_service_select
**
** Description  Obtain the length of given UUID in the SDP DB.
**
** Returns      void
**
*******************************************************************************/
void bta_jv_service_select(tBTA_JV_MSG *p_data)
{
#if 0
    tBTA_JV_SERVICE_SEL     serv_sel;
    tSDP_DISC_REC *p_rec, *p_tmp;
    UINT8   *p, *np, *op, type;
    UINT32  raw_used, raw_cur;
    UINT32  len;

    serv_sel.service_len = 0;
    bta_jv_cb.p_sel_raw_data     = 0;
    p_rec = SDP_FindServiceInDb (p_bta_jv_cfg->p_sdp_db, p_data->service_select.uuid, NULL);
    if(p_rec)
    {
        /* found the record in the database */
        /* the database must be valid */
        p = p_bta_jv_cfg->p_sdp_db->raw_data;
        raw_used = p_bta_jv_cfg->p_sdp_db->raw_used;
        p_tmp = p_bta_jv_cfg->p_sdp_db->p_first_rec;
        while(raw_used && p && p_tmp)
        {
            op = p;
            type = *p++;
            np = sdpu_get_len_from_type(p, type, &len);
            if(p_tmp == p_rec)
            {
                bta_jv_cb.p_sel_raw_data = op;
                bta_jv_cb.sel_len = len;
                serv_sel.service_len = len;
                bdcpy(serv_sel.bd_addr, p_rec->remote_bd_addr);
                APPL_TRACE_DEBUG1( "bta_jv_service_select found uuid: 0x%x",
                    p_data->service_select.uuid);
                break;
            }
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
            p_tmp = p_tmp->p_next_rec;
        } /* end of while */
    }
    APPL_TRACE_DEBUG1( "service_len: %d", serv_sel.service_len);
    if(bta_jv_cb.p_dm_cback)
        bta_jv_cb.p_dm_cback(BTA_JV_SERVICE_SEL_EVT, (tBTA_JV *)&serv_sel);
#endif
}

/*******************************************************************************
**
** Function     bta_jv_create_record
**
** Description  Create an SDP record with the given attributes
**
** Returns      void
**
*******************************************************************************/
void bta_jv_create_record(tBTA_JV_MSG *p_data)
{
    tBTA_JV_API_CREATE_RECORD *cr = &(p_data->create_record);
    tBTA_JV_CREATE_RECORD   evt_data;
    evt_data.status = BTA_JV_SUCCESS;
    if(bta_jv_cb.p_dm_cback)
        //callback user immediately to create his own sdp record in stack thread context
        bta_jv_cb.p_dm_cback(BTA_JV_CREATE_RECORD_EVT, (tBTA_JV *)&evt_data, cr->user_data);
}

/*******************************************************************************
**
** Function     bta_jv_update_record
**
** Description  Update an SDP record with the given attributes
**
** Returns      void
**
*******************************************************************************/
void bta_jv_update_record(tBTA_JV_MSG *p_data)
{
#if 0
    tBTA_JV_API_UPDATE_RECORD *ur = &(p_data->update_record);
    tBTA_JV_UPDATE_RECORD   evt_data;
    UINT32 handle;
    INT32 i;
    UINT8 *ptr;
    UINT8 *next_ptr;
    UINT8 *end;
    UINT32 len;
    UINT8 type;

    evt_data.status = BTA_JV_FAILURE;
    evt_data.handle = ur->handle;

    handle = bta_jv_get_sdp_handle(ur->handle);

    if(handle)
    {
        /* this is a record created by JV */
        for (i = 0; i < ur->array_len; i++)
        {
            ptr = ur->p_values[i];
            end = ptr + ur->p_value_sizes[i];

            while (ptr < end)
            {
                type = *ptr;
                next_ptr = sdpu_get_len_from_type(ptr + 1, *ptr, &len);

                if(ATTR_ID_SERVICE_RECORD_HDL != ur->p_ids[i])
                {
                if (!SDP_AddAttribute(handle, ur->p_ids[i], (UINT8)((type >> 3) & 0x1f),
                    len, next_ptr))
                {
                    /* failed on updating attributes.  */
                    if(bta_jv_cb.p_dm_cback)
                        bta_jv_cb.p_dm_cback(BTA_JV_UPDATE_RECORD_EVT, (tBTA_JV *)&evt_data);
                    return;
                }
                }

                ptr = next_ptr + len;
            } /* end of while */
        } /* end of for */
        evt_data.status = BTA_JV_SUCCESS;
    }

    if(bta_jv_cb.p_dm_cback)
        bta_jv_cb.p_dm_cback(BTA_JV_UPDATE_RECORD_EVT, (tBTA_JV *)&evt_data);
#endif
}

/*******************************************************************************
**
** Function     bta_jv_add_attribute
**
** Description  Add an attribute to an SDP record
**
** Returns      void
**
*******************************************************************************/
void bta_jv_add_attribute(tBTA_JV_MSG *p_data)
{
#if 0
    tBTA_JV_API_ADD_ATTRIBUTE *aa = &(p_data->add_attr);
    tBTA_JV_ADD_ATTR   evt_data;
    UINT32 handle;
    UINT8 type;
    UINT32 len;
    UINT8 *ptr;
    UINT8 *next_ptr;

    evt_data.status = BTA_JV_FAILURE;
    evt_data.handle = aa->handle;
    handle = bta_jv_get_sdp_handle(aa->handle);

    if(handle)
    {
        /* this is a record created by JV */
        ptr = aa->p_value;
        type = *ptr;
        next_ptr = sdpu_get_len_from_type(ptr + 1, *ptr, &len);
        APPL_TRACE_DEBUG3( "bta_jv_add_attribute: ptr chg:%d len:%d, size:%d",
            (next_ptr - ptr), len, aa->value_size);
        if(ATTR_ID_SERVICE_RECORD_HDL != aa->attr_id && /* do not allow the SDP record handle to be updated */
            ((INT32)(next_ptr - ptr + len) == aa->value_size) && /* double check data size */
            SDP_AddAttribute(handle, aa->attr_id, (UINT8)((type >> 3) & 0x1f),
                    len, next_ptr))
        {
            evt_data.status = BTA_JV_SUCCESS;
        }
    }

    if(bta_jv_cb.p_dm_cback)
        bta_jv_cb.p_dm_cback(BTA_JV_ADD_ATTR_EVT, (tBTA_JV *)&evt_data);
#endif
}

/*******************************************************************************
**
** Function     bta_jv_delete_attribute
**
** Description  Delete an attribute from the given SDP record
**
** Returns      void
**
*******************************************************************************/
void bta_jv_delete_attribute(tBTA_JV_MSG *p_data)
{
#if 0
    tBTA_JV_API_ADD_ATTRIBUTE *da = &(p_data->add_attr);
    tBTA_JV_DELETE_ATTR   evt_data;
    UINT32 handle;

    evt_data.status = BTA_JV_FAILURE;
    evt_data.handle = da->handle;
    handle = bta_jv_get_sdp_handle(da->handle);

    if(handle)
    {
        /* this is a record created by JV */
        if(SDP_DeleteAttribute(handle, da->attr_id))
            evt_data.status = BTA_JV_SUCCESS;
    }

    if(bta_jv_cb.p_dm_cback)
        bta_jv_cb.p_dm_cback(BTA_JV_DELETE_ATTR_EVT, (tBTA_JV *)&evt_data);
#endif
}

/*******************************************************************************
**
** Function     bta_jv_delete_record
**
** Description  Delete an SDP record
**
**
** Returns      void
**
*******************************************************************************/
void bta_jv_delete_record(tBTA_JV_MSG *p_data)
{
    tBTA_JV_API_ADD_ATTRIBUTE *dr = &(p_data->add_attr);
    UINT32 handle;

    handle = bta_jv_get_sdp_handle(dr->handle);

    if(handle)
    {
        /* this is a record created by JV */
        SDP_DeleteRecord(handle);
        bta_jv_free_sdp_id(dr->handle);
    }
}

/*******************************************************************************
**
** Function     bta_jv_l2cap_client_cback
**
** Description  handles the l2cap client events
**
** Returns      void
**
*******************************************************************************/
static void bta_jv_l2cap_client_cback(UINT16 gap_handle, UINT16 event)
{
#if 0
    tBTA_JV_L2C_CB  *p_cb = &bta_jv_cb.l2c_cb[gap_handle];
    tBTA_JV     evt_data;

    if(gap_handle >= BTA_JV_MAX_L2C_CONN && !p_cb->p_cback)
        return;

    APPL_TRACE_DEBUG2( "bta_jv_l2cap_client_cback: %d evt:x%x",
        gap_handle, event);
    evt_data.l2c_open.status = BTA_JV_SUCCESS;
    evt_data.l2c_open.handle = gap_handle;
    switch (event)
    {
    case GAP_EVT_CONN_OPENED:
        bdcpy(evt_data.l2c_open.rem_bda, GAP_ConnGetRemoteAddr(gap_handle));
        evt_data.l2c_open.tx_mtu = GAP_ConnGetRemMtuSize(gap_handle);
        p_cb->state = BTA_JV_ST_CL_OPEN;
        p_cb->p_cback(BTA_JV_L2CAP_OPEN_EVT, &evt_data);
        break;

    case GAP_EVT_CONN_CLOSED:
        p_cb->state = BTA_JV_ST_NONE;
        bta_jv_free_sec_id(&p_cb->sec_id);
        evt_data.l2c_close.async = TRUE;
        p_cb->p_cback(BTA_JV_L2CAP_CLOSE_EVT, &evt_data);
        p_cb->p_cback = NULL;
        break;

    case GAP_EVT_CONN_DATA_AVAIL:
        evt_data.handle = gap_handle;
        p_cb->p_cback(BTA_JV_L2CAP_DATA_IND_EVT, &evt_data);
        break;

    case GAP_EVT_CONN_CONGESTED:
    case GAP_EVT_CONN_UNCONGESTED:
        p_cb->cong = (event == GAP_EVT_CONN_CONGESTED) ? TRUE : FALSE;
        evt_data.l2c_cong.cong = p_cb->cong;
        p_cb->p_cback(BTA_JV_L2CAP_CONG_EVT, &evt_data);
        break;

    default:
        break;
    }
#endif
}

#if SDP_FOR_JV_INCLUDED == TRUE
/*******************************************************************************
**
** Function     bta_jv_sdp_res_cback
**
** Description  Callback for Start Discovery
**
** Returns      void
**
*******************************************************************************/
void bta_jv_sdp_res_cback (UINT16 event, tSDP_DATA *p_data)
{
    tBTA_JV evt_data;
    tBTA_JV_L2C_CB  *p_cb = &bta_jv_cb.l2c_cb[BTA_JV_L2C_FOR_SDP_HDL];

    APPL_TRACE_DEBUG2( "bta_jv_sdp_res_cback: %d evt:x%x",
        bta_jv_cb.sdp_for_jv, event);

    if(!bta_jv_cb.sdp_for_jv)
        return;

    evt_data.l2c_open.status = BTA_JV_SUCCESS;
    evt_data.l2c_open.handle = BTA_JV_L2C_FOR_SDP_HDL;

    switch(event)
    {
    case SDP_EVT_OPEN:
        bdcpy(evt_data.l2c_open.rem_bda, p_data->open.peer_addr);
        evt_data.l2c_open.tx_mtu = p_data->open.peer_mtu;
        p_cb->state = BTA_JV_ST_SR_OPEN;
        p_cb->p_cback(BTA_JV_L2CAP_OPEN_EVT, &evt_data);
        break;
    case SDP_EVT_DATA_IND:
        evt_data.handle = BTA_JV_L2C_FOR_SDP_HDL;
        memcpy(p_bta_jv_cfg->p_sdp_raw_data, p_data->data.p_data, p_data->data.data_len);
        APPL_TRACE_DEBUG2( "data size: %d/%d ", bta_jv_cb.sdp_data_size, p_data->data.data_len);
        bta_jv_cb.sdp_data_size = p_data->data.data_len;
        p_cb->p_cback(BTA_JV_L2CAP_DATA_IND_EVT, &evt_data);
        break;
    }
}

/*******************************************************************************
**
** Function     bta_jv_sdp_cback
**
** Description  Callback for Start Discovery
**
** Returns      void
**
*******************************************************************************/
static void bta_jv_sdp_cback(UINT16 result)
{
    tBTA_JV_L2CAP_CLOSE close;
    tBTA_JV_L2C_CB  *p_cb = &bta_jv_cb.l2c_cb[BTA_JV_L2C_FOR_SDP_HDL];
    APPL_TRACE_DEBUG1( "bta_jv_sdp_cback: result:x%x", result);

    if(p_cb->p_cback)
    {
        close.handle    = BTA_JV_L2C_FOR_SDP_HDL;
        close.async     = FALSE;
        close.status    = BTA_JV_SUCCESS;
        bta_jv_free_sec_id(&p_cb->sec_id);
        p_cb->p_cback(BTA_JV_L2CAP_CLOSE_EVT, (tBTA_JV *)&close);
    }

    bta_jv_cb.sdp_for_jv = 0;
    p_cb->p_cback = NULL;

}
#endif

/*******************************************************************************
**
** Function     bta_jv_l2cap_connect
**
** Description  makes an l2cap client connection
**
** Returns      void
**
*******************************************************************************/
void bta_jv_l2cap_connect(tBTA_JV_MSG *p_data)
{
#if 0
    tBTA_JV_L2C_CB      *p_cb;
    tBTA_JV_L2CAP_CL_INIT  evt_data;
    UINT16  handle=GAP_INVALID_HANDLE;
    UINT8   sec_id;
    tL2CAP_CFG_INFO cfg;
    tBTA_JV_API_L2CAP_CONNECT *cc = &(p_data->l2cap_connect);

    memset(&cfg, 0, sizeof(tL2CAP_CFG_INFO));
    cfg.mtu_present = TRUE;
    cfg.mtu = cc->rx_mtu;
    /* TODO: DM role manager
    L2CA_SetDesireRole(cc->role);
    */

    sec_id = bta_jv_alloc_sec_id();
    evt_data.sec_id = sec_id;
    evt_data.status = BTA_JV_FAILURE;
    if (sec_id)
    {
#if SDP_FOR_JV_INCLUDED == TRUE
        if(SDP_PSM == cc->remote_psm && 0 == bta_jv_cb.sdp_for_jv)
        {
            bta_jv_cb.sdp_for_jv = SDP_ConnOpen(cc->peer_bd_addr,
                                       bta_jv_sdp_res_cback,
                                       bta_jv_sdp_cback);
            if(bta_jv_cb.sdp_for_jv)
            {
                bta_jv_cb.sdp_data_size = 0;
                handle = BTA_JV_L2C_FOR_SDP_HDL;
                evt_data.status = BTA_JV_SUCCESS;
            }
        }
        else
#endif
        if(bta_jv_check_psm(cc->remote_psm)) /* allowed */
        {
            if( (handle = GAP_ConnOpen("", sec_id, 0, cc->peer_bd_addr, cc->remote_psm,
                &cfg, cc->sec_mask, GAP_FCR_CHAN_OPT_BASIC,
                bta_jv_l2cap_client_cback)) != GAP_INVALID_HANDLE )
            {
                evt_data.status = BTA_JV_SUCCESS;
            }
        }
    }

    if (evt_data.status == BTA_JV_SUCCESS)
    {
        p_cb = &bta_jv_cb.l2c_cb[handle];
        p_cb->handle = handle;
        p_cb->p_cback = cc->p_cback;
        p_cb->psm = 0;  /* not a server */
        p_cb->sec_id = sec_id;
        p_cb->state = BTA_JV_ST_CL_OPENING;
    }
    else
    {
        bta_jv_free_sec_id(&sec_id);
    }
    evt_data.handle = handle;
    cc->p_cback(BTA_JV_L2CAP_CL_INIT_EVT, (tBTA_JV *)&evt_data);
#endif
}

/*******************************************************************************
**
** Function     bta_jv_l2cap_close
**
** Description  Close an L2CAP client connection
**
** Returns      void
**
*******************************************************************************/
void bta_jv_l2cap_close(tBTA_JV_MSG *p_data)
{
#if 0
    tBTA_JV_L2CAP_CLOSE  evt_data;
    tBTA_JV_API_L2CAP_CLOSE *cc = &(p_data->l2cap_close);
    tBTA_JV_L2CAP_CBACK *p_cback = cc->p_cb->p_cback;

    evt_data.handle = cc->handle;
    evt_data.status = bta_jv_free_l2c_cb(cc->p_cb);
    evt_data.async = FALSE;

    if (p_cback)
        p_cback(BTA_JV_L2CAP_CLOSE_EVT, (tBTA_JV *)&evt_data);
    else
        APPL_TRACE_ERROR0("### NO CALLBACK SET !!! ###");
#endif
}

/*******************************************************************************
**
** Function         bta_jv_l2cap_server_cback
**
** Description      handles the l2cap server callback
**
** Returns          void
**
*******************************************************************************/
static void bta_jv_l2cap_server_cback(UINT16 gap_handle, UINT16 event)
{
#if 0
    tBTA_JV_L2C_CB  *p_cb = &bta_jv_cb.l2c_cb[gap_handle];
    tBTA_JV evt_data;
    tBTA_JV_L2CAP_CBACK *p_cback;

    if(gap_handle >= BTA_JV_MAX_L2C_CONN && !p_cb->p_cback)
        return;

    APPL_TRACE_DEBUG2( "bta_jv_l2cap_server_cback: %d evt:x%x",
        gap_handle, event);
    evt_data.l2c_open.status = BTA_JV_SUCCESS;
    evt_data.l2c_open.handle = gap_handle;

    switch (event)
    {
    case GAP_EVT_CONN_OPENED:
        bdcpy(evt_data.l2c_open.rem_bda, GAP_ConnGetRemoteAddr(gap_handle));
        evt_data.l2c_open.tx_mtu = GAP_ConnGetRemMtuSize(gap_handle);
        p_cb->state = BTA_JV_ST_SR_OPEN;
        p_cb->p_cback(BTA_JV_L2CAP_OPEN_EVT, &evt_data);
        break;

    case GAP_EVT_CONN_CLOSED:
        evt_data.l2c_close.async = TRUE;
        evt_data.l2c_close.handle = p_cb->handle;
        p_cback = p_cb->p_cback;
        evt_data.l2c_close.status = bta_jv_free_l2c_cb(p_cb);
        p_cback(BTA_JV_L2CAP_CLOSE_EVT, &evt_data);
        break;

    case GAP_EVT_CONN_DATA_AVAIL:
        evt_data.handle = gap_handle;
        p_cb->p_cback(BTA_JV_L2CAP_DATA_IND_EVT, &evt_data);
        break;

    case GAP_EVT_CONN_CONGESTED:
    case GAP_EVT_CONN_UNCONGESTED:
        p_cb->cong = (event == GAP_EVT_CONN_CONGESTED) ? TRUE : FALSE;
        evt_data.l2c_cong.cong = p_cb->cong;
        p_cb->p_cback(BTA_JV_L2CAP_CONG_EVT, &evt_data);
        break;

    default:
        break;
    }
#endif
}

/*******************************************************************************
**
** Function     bta_jv_l2cap_start_server
**
** Description  starts an L2CAP server
**
** Returns      void
**
*******************************************************************************/
void bta_jv_l2cap_start_server(tBTA_JV_MSG *p_data)
{
#if 0
    tBTA_JV_L2C_CB      *p_cb;
    UINT8   sec_id;
    UINT16  handle;
    tL2CAP_CFG_INFO cfg;
    tBTA_JV_L2CAP_START evt_data;
    tBTA_JV_API_L2CAP_SERVER *ls = &(p_data->l2cap_server);

    memset(&cfg, 0, sizeof(tL2CAP_CFG_INFO));

    //FIX: MTU=0 means not present
    if (ls->rx_mtu >0)
    {
        cfg.mtu_present = TRUE;
        cfg.mtu = ls->rx_mtu;
    }
    else
    {
        cfg.mtu_present = FALSE;
        cfg.mtu = 0;
    }

    /* TODO DM role manager
    L2CA_SetDesireRole(ls->role);
    */

    sec_id = bta_jv_alloc_sec_id();
    if (0 == sec_id || (FALSE == bta_jv_check_psm(ls->local_psm)) ||
        (handle = GAP_ConnOpen("JV L2CAP", sec_id, 1, 0, ls->local_psm, &cfg,
            ls->sec_mask, GAP_FCR_CHAN_OPT_BASIC, bta_jv_l2cap_server_cback)) == GAP_INVALID_HANDLE)
    {
        bta_jv_free_sec_id(&sec_id);
        evt_data.status = BTA_JV_FAILURE;
    }
    else
    {
        /* default JV implementation requires explicit call
           to allow incoming connections when ready*/

        GAP_SetAcceptReady(handle, FALSE);

        p_cb = &bta_jv_cb.l2c_cb[handle];
        evt_data.status = BTA_JV_SUCCESS;
        evt_data.handle = handle;
        evt_data.sec_id = sec_id;
        p_cb->p_cback = ls->p_cback;
        p_cb->handle = handle;
        p_cb->sec_id = sec_id;
        p_cb->state = BTA_JV_ST_SR_LISTEN;
        p_cb->psm = ls->local_psm;
    }
    ls->p_cback(BTA_JV_L2CAP_START_EVT, (tBTA_JV *)&evt_data);
#endif
}

/*******************************************************************************
**
** Function     bta_jv_l2cap_stop_server
**
** Description  stops an L2CAP server
**
** Returns      void
**
*******************************************************************************/
void bta_jv_l2cap_stop_server(tBTA_JV_MSG *p_data)
{
#if 0
    tBTA_JV_L2C_CB      *p_cb;
    tBTA_JV_L2CAP_CLOSE  evt_data;
    tBTA_JV_API_L2CAP_SERVER *ls = &(p_data->l2cap_server);
    tBTA_JV_L2CAP_CBACK *p_cback;
    int i;

    for(i=0; i<BTA_JV_MAX_L2C_CONN; i++)
    {
        if(bta_jv_cb.l2c_cb[i].psm == ls->local_psm)
        {
            p_cb = &bta_jv_cb.l2c_cb[i];
            p_cback = p_cb->p_cback;
            evt_data.handle = p_cb->handle;
            evt_data.status = bta_jv_free_l2c_cb(p_cb);
            evt_data.async = FALSE;
            p_cback(BTA_JV_L2CAP_CLOSE_EVT, (tBTA_JV *)&evt_data);
            break;
        }
    }
#endif
}

/*******************************************************************************
**
** Function     bta_jv_l2cap_read
**
** Description  Read data from an L2CAP connection
**
** Returns      void
**
*******************************************************************************/
void bta_jv_l2cap_read(tBTA_JV_MSG *p_data)
{
#if 0
    tBTA_JV_L2CAP_READ evt_data;
    tBTA_JV_API_L2CAP_READ *rc = &(p_data->l2cap_read);

    evt_data.status = BTA_JV_FAILURE;
    evt_data.handle = rc->handle;
    evt_data.req_id = rc->req_id;
    evt_data.p_data = rc->p_data;
    evt_data.len    = 0;
#if SDP_FOR_JV_INCLUDED == TRUE
    if(BTA_JV_L2C_FOR_SDP_HDL == rc->handle)
    {
        evt_data.len = rc->len;
        if(evt_data.len > bta_jv_cb.sdp_data_size)
            evt_data.len = bta_jv_cb.sdp_data_size;

        memcpy(rc->p_data, p_bta_jv_cfg->p_sdp_raw_data, evt_data.len);
        bta_jv_cb.sdp_data_size = 0;
        evt_data.status = BTA_JV_SUCCESS;
    }
    else
#endif
    if (BT_PASS == GAP_ConnReadData(rc->handle, rc->p_data, rc->len, &evt_data.len))
    {
        evt_data.status = BTA_JV_SUCCESS;
    }

    rc->p_cback(BTA_JV_L2CAP_READ_EVT, (tBTA_JV *)&evt_data);
#endif
}


/*******************************************************************************
**
** Function     bta_jv_l2cap_write
**
** Description  Write data to an L2CAP connection
**
** Returns      void
**
*******************************************************************************/
void bta_jv_l2cap_write(tBTA_JV_MSG *p_data)
{
#if 0
    tBTA_JV_L2CAP_WRITE evt_data;
    tBTA_JV_API_L2CAP_WRITE *ls = &(p_data->l2cap_write);

    evt_data.status = BTA_JV_FAILURE;
    evt_data.handle = ls->handle;
    evt_data.req_id = ls->req_id;
    evt_data.cong   = ls->p_cb->cong;
    evt_data.len    = 0;
#if SDP_FOR_JV_INCLUDED == TRUE
    if(BTA_JV_L2C_FOR_SDP_HDL == ls->handle)
    {
        UINT8   *p;
        BT_HDR  *p_msg = (BT_HDR *) GKI_getbuf ((UINT16)(ls->len + BT_HDR_SIZE + L2CAP_MIN_OFFSET));
        if(p_msg)
        {
            p_msg->offset = L2CAP_MIN_OFFSET;
            p = (UINT8 *)(p_msg + 1) + L2CAP_MIN_OFFSET;
            p_msg->len = ls->len;
            memcpy(p, ls->p_data, p_msg->len);
            if(SDP_WriteData (bta_jv_cb.sdp_for_jv, p_msg))
            {
                evt_data.len    = ls->len;
                evt_data.status = BTA_JV_SUCCESS;
            }
        }
    }
    else
#endif
    if (!evt_data.cong &&
        BT_PASS == GAP_ConnWriteData(ls->handle, ls->p_data, ls->len, &evt_data.len))
    {
        evt_data.status = BTA_JV_SUCCESS;
    }

    ls->p_cb->p_cback(BTA_JV_L2CAP_WRITE_EVT, (tBTA_JV *)&evt_data);
#endif
}

/*******************************************************************************
**
** Function     bta_jv_port_data_co_cback
**
** Description  port data callback function of rfcomm
**              connections
**
** Returns      void
**
*******************************************************************************/
/*
#define DATA_CO_CALLBACK_TYPE_INCOMING          1
#define DATA_CO_CALLBACK_TYPE_OUTGOING_SIZE     2
#define DATA_CO_CALLBACK_TYPE_OUTGOING          3
*/
static int bta_jv_port_data_co_cback(UINT16 port_handle, UINT8 *buf, UINT16 len, int type)
{
    tBTA_JV_RFC_CB  *p_cb = bta_jv_rfc_port_to_cb(port_handle);
    tBTA_JV_PCB     *p_pcb = bta_jv_rfc_port_to_pcb(port_handle);

    if (p_cb != NULL)
    {
        switch(type)
        {
            case DATA_CO_CALLBACK_TYPE_INCOMING:
                return bta_co_rfc_data_incoming(p_pcb->user_data, (BT_HDR*)buf);
            case DATA_CO_CALLBACK_TYPE_OUTGOING_SIZE:
                return bta_co_rfc_data_outgoing_size(p_pcb->user_data, (int*)buf);
            case DATA_CO_CALLBACK_TYPE_OUTGOING:
                return bta_co_rfc_data_outgoing(p_pcb->user_data, buf, len);
            default:
                APPL_TRACE_ERROR1("unknown callout type:%d", type);
                break;
        }
    }
    return 0;
}

/*******************************************************************************
**
** Function     bta_jv_port_mgmt_cl_cback
**
** Description  callback for port mamangement function of rfcomm
**              client connections
**
** Returns      void
**
*******************************************************************************/
static void bta_jv_port_mgmt_cl_cback(UINT32 code, UINT16 port_handle)
{
    tBTA_JV_RFC_CB  *p_cb = bta_jv_rfc_port_to_cb(port_handle);
    tBTA_JV_PCB     *p_pcb = bta_jv_rfc_port_to_pcb(port_handle);
    tBTA_JV evt_data;
    BD_ADDR rem_bda;
    UINT16 lcid;
    tBTA_JV_RFCOMM_CBACK *p_cback;  /* the callback function */

    APPL_TRACE_DEBUG1( "bta_jv_port_mgmt_cl_cback:%d", port_handle);
    if(NULL == p_cb || NULL == p_cb->p_cback)
        return;

    APPL_TRACE_DEBUG3( "bta_jv_port_mgmt_cl_cback code=%d port_handle:%d handle:%d",
        code, port_handle, p_cb->handle);

    PORT_CheckConnection(port_handle, rem_bda, &lcid);

    if(code == PORT_SUCCESS)
    {
        evt_data.rfc_open.handle = p_cb->handle;
        evt_data.rfc_open.status = BTA_JV_SUCCESS;
        bdcpy(evt_data.rfc_open.rem_bda, rem_bda);
        p_pcb->state = BTA_JV_ST_CL_OPEN;
        p_cb->p_cback(BTA_JV_RFCOMM_OPEN_EVT, &evt_data, p_pcb->user_data);
    }
    else
    {
        evt_data.rfc_close.handle = p_cb->handle;
        evt_data.rfc_close.status = BTA_JV_FAILURE;
        evt_data.rfc_close.port_status = code;
        evt_data.rfc_close.async = TRUE;
        if (p_pcb->state == BTA_JV_ST_CL_CLOSING)
        {
            evt_data.rfc_close.async = FALSE;
        }
        p_pcb->state = BTA_JV_ST_NONE;
        p_pcb->cong = FALSE;
        p_cback = p_cb->p_cback;
        bta_jv_free_rfc_cb(p_cb);

        p_cback(BTA_JV_RFCOMM_CLOSE_EVT, &evt_data, p_pcb->user_data);
    }

}

/*******************************************************************************
**
** Function     bta_jv_port_event_cl_cback
**
** Description  Callback for RFCOMM client port events
**
** Returns      void
**
*******************************************************************************/
static void bta_jv_port_event_cl_cback(UINT32 code, UINT16 port_handle)
{
    tBTA_JV_RFC_CB  *p_cb = bta_jv_rfc_port_to_cb(port_handle);
    tBTA_JV_PCB     *p_pcb = bta_jv_rfc_port_to_pcb(port_handle);
    tBTA_JV evt_data;

    APPL_TRACE_DEBUG1( "bta_jv_port_event_cl_cback:%d", port_handle);
    if(NULL == p_cb || NULL == p_cb->p_cback)
        return;

    APPL_TRACE_DEBUG3( "bta_jv_port_event_cl_cback code=x%x port_handle:%d handle:%d",
        code, port_handle, p_cb->handle);
    if (code & PORT_EV_RXCHAR)
    {
        evt_data.data_ind.handle = p_cb->handle;
        p_cb->p_cback(BTA_JV_RFCOMM_DATA_IND_EVT, &evt_data, p_pcb->user_data);
    }

    if (code & PORT_EV_FC)
    {
        p_pcb->cong = (code & PORT_EV_FCS) ? FALSE : TRUE;
        evt_data.rfc_cong.cong = p_pcb->cong;
        evt_data.rfc_cong.handle = p_cb->handle;
        evt_data.rfc_cong.status = BTA_JV_SUCCESS;
        p_cb->p_cback(BTA_JV_RFCOMM_CONG_EVT, &evt_data, p_pcb->user_data);
    }
}

/*******************************************************************************
**
** Function     bta_jv_rfcomm_connect
**
** Description  Client initiates an RFCOMM connection
**
** Returns      void
**
*******************************************************************************/
void bta_jv_rfcomm_connect(tBTA_JV_MSG *p_data)
{
    UINT16 handle = 0;
    UINT32 event_mask = (PORT_EV_RXCHAR | PORT_EV_FC | PORT_EV_FCS);
    tPORT_STATE port_state;
    UINT8   sec_id;
    tBTA_JV_RFC_CB  *p_cb = NULL;
    tBTA_JV_PCB     *p_pcb;
    tBTA_JV_API_RFCOMM_CONNECT *cc = &(p_data->rfcomm_connect);
    tBTA_JV_RFCOMM_CL_INIT      evt_data;

    /* TODO DM role manager
    L2CA_SetDesireRole(cc->role);
    */

    sec_id = bta_jv_alloc_sec_id();
    evt_data.sec_id = sec_id;
    evt_data.status = BTA_JV_SUCCESS;
    if (0 == sec_id ||
        BTM_SetSecurityLevel(TRUE, "", sec_id,  cc->sec_mask, BT_PSM_RFCOMM,
                BTM_SEC_PROTO_RFCOMM, cc->remote_scn) == FALSE)
    {
        evt_data.status = BTA_JV_FAILURE;
        error("sec_id:%d is zero or BTM_SetSecurityLevel failed, remote_scn:%d", sec_id, cc->remote_scn);
    }

    if (evt_data.status == BTA_JV_SUCCESS &&
        RFCOMM_CreateConnection(UUID_SERVCLASS_SERIAL_PORT, cc->remote_scn, FALSE,
        BTA_JV_DEF_RFC_MTU, cc->peer_bd_addr, &handle, bta_jv_port_mgmt_cl_cback) != PORT_SUCCESS)
    {
        evt_data.status = BTA_JV_FAILURE;
    }
    if (evt_data.status == BTA_JV_SUCCESS)
    {
        p_cb = bta_jv_alloc_rfc_cb(handle, &p_pcb);
        if(p_cb)
        {
            p_cb->p_cback = cc->p_cback;
            p_cb->sec_id = sec_id;
            p_cb->scn = 0;
            p_pcb->state = BTA_JV_ST_CL_OPENING;
            p_pcb->user_data = cc->user_data;
            evt_data.use_co = TRUE;

            PORT_SetEventCallback(handle, bta_jv_port_event_cl_cback);
            PORT_SetEventMask(handle, event_mask);
            PORT_SetDataCOCallback (handle, bta_jv_port_data_co_cback);

            PORT_GetState(handle, &port_state);

            port_state.fc_type = (PORT_FC_CTS_ON_INPUT | PORT_FC_CTS_ON_OUTPUT);

            /* coverity[uninit_use_in_call]
               FALSE-POSITIVE: port_state is initialized at PORT_GetState() */
            PORT_SetState(handle, &port_state);

            evt_data.handle = p_cb->handle;
        }
        else
        {
            evt_data.status = BTA_JV_FAILURE;
            APPL_TRACE_ERROR0("run out of rfc control block");
        }
    }
    cc->p_cback(BTA_JV_RFCOMM_CL_INIT_EVT, (tBTA_JV *)&evt_data, cc->user_data);
 }

/*******************************************************************************
**
** Function     bta_jv_rfcomm_close
**
** Description  Close an RFCOMM connection
**
** Returns      void
**
*******************************************************************************/
void bta_jv_rfcomm_close(tBTA_JV_MSG *p_data)
{
    tBTA_JV_RFCOMM_CLOSE     evt_data;
    tBTA_JV_API_RFCOMM_CLOSE *cc = &(p_data->rfcomm_close);
    tBTA_JV_RFC_CB           *p_cb = cc->p_cb;
    tBTA_JV_PCB              *p_pcb = cc->p_pcb;
    tBTA_JV_RFCOMM_CBACK     *p_cback = p_cb->p_cback;

    evt_data.handle = p_cb->handle;
    evt_data.status = BTA_JV_FAILURE;

    void* user_data = p_pcb->user_data;
    p_pcb->cong = FALSE;
    if(p_pcb->state <= BTA_JV_ST_CL_MAX)
    {
        if(p_pcb->state == BTA_JV_ST_CL_OPEN)
        {
            if(PORT_SUCCESS == RFCOMM_RemoveConnection(p_pcb->port_handle))
            {
                p_pcb->state = BTA_JV_ST_CL_CLOSING;
                return;
            }
        }
        evt_data.status = bta_jv_free_rfc_cb(p_cb);
    }
    else if(BTA_JV_ST_SR_OPEN == p_pcb->state)
    {
        /* server is connected */
        if(PORT_SUCCESS == RFCOMM_RemoveConnection(p_pcb->port_handle))
        {
            p_pcb->state = BTA_JV_ST_SR_CLOSING;
            return;
        }
    }

    evt_data.async = FALSE;

    if (p_cback)
        p_cback(BTA_JV_RFCOMM_CLOSE_EVT, (tBTA_JV *)&evt_data, user_data);
    else
        error("### NO CALLBACK SET !!! ###");
}

/*******************************************************************************
**
** Function     bta_jv_get_num_rfc_listen
**
** Description  when a RFCOMM connection goes down, make sure that there's only
**              one port stays listening on this scn.
**
** Returns
**
*******************************************************************************/
static UINT8 bta_jv_get_num_rfc_listen(tBTA_JV_RFC_CB *p_cb)
{
    UINT8   i, listen=1;
    tBTA_JV_PCB *p_pcb;

    if (p_cb->max_sess > 1)
    {
        listen = 0;
        for (i=0; i<p_cb->max_sess; i++)
        {
            if (p_cb->rfc_hdl[i] != 0)
            {
                p_pcb = &bta_jv_cb.port_cb[p_cb->rfc_hdl[i] - 1];
                if (BTA_JV_ST_SR_LISTEN == p_pcb->state)
                {
                    listen++;
                }
            }
        }
    }
    return listen;
}

/*******************************************************************************
**
** Function     bta_jv_port_mgmt_sr_cback
**
** Description  callback for port mamangement function of rfcomm
**              server connections
**
** Returns      void
**
*******************************************************************************/
static void bta_jv_port_mgmt_sr_cback(UINT32 code, UINT16 port_handle)
{
    tBTA_JV_PCB     *p_pcb = bta_jv_rfc_port_to_pcb(port_handle);
    tBTA_JV_RFC_CB  *p_cb = bta_jv_rfc_port_to_cb(port_handle);
    tBTA_JV evt_data;
    BD_ADDR rem_bda;
    UINT16 lcid;
    UINT8  num;
    tBTA_JV_RFCOMM_CBACK    *p_cback;
    UINT32  si;

    if(NULL == p_cb || NULL == p_cb->p_cback)
        return;
    void *user_data = p_pcb->user_data;
    APPL_TRACE_DEBUG4( "bta_jv_port_mgmt_sr_cback code=%d port_handle:%d handle:%d/0x%x",
        code, port_handle, p_cb->handle, p_pcb->handle);

    PORT_CheckConnection(port_handle, rem_bda, &lcid);
    int failed = TRUE;
    if(code == PORT_SUCCESS)
    {
        evt_data.rfc_srv_open.handle = p_pcb->handle;
        evt_data.rfc_srv_open.status = BTA_JV_SUCCESS;
        bdcpy(evt_data.rfc_srv_open.rem_bda, rem_bda);
        p_pcb->state = BTA_JV_ST_SR_OPEN;
        tBTA_JV_PCB *p_pcb_new_listen  = bta_jv_add_rfc_port(p_cb);
        if(p_pcb_new_listen)
        {
            evt_data.rfc_srv_open.new_listen_handle = p_pcb_new_listen->handle;
            p_pcb_new_listen->user_data = p_cb->p_cback(BTA_JV_RFCOMM_SRV_OPEN_EVT, &evt_data, user_data);
            failed = FALSE;
        }
        else error("bta_jv_add_rfc_port failed to create new listen port");
    }
    if(failed)
    {
        evt_data.rfc_close.handle = p_cb->handle;
        evt_data.rfc_close.status = BTA_JV_SUCCESS;
        evt_data.rfc_close.async = TRUE;
        if(BTA_JV_ST_SR_CLOSING == p_pcb->state)
        {
            evt_data.rfc_close.async = FALSE;
        }
        p_pcb->cong = FALSE;
        p_cback = p_cb->p_cback;
        APPL_TRACE_DEBUG1( "removing rfc handle:0x%x", p_pcb->handle);
        si = BTA_JV_RFC_HDL_TO_SIDX(p_pcb->handle);
        p_cb->rfc_hdl[si] = 0;
        p_pcb->state = BTA_JV_ST_NONE;
        p_pcb->handle = 0;
        RFCOMM_RemoveServer(port_handle);
        evt_data.rfc_close.port_status = code;
        p_cback(BTA_JV_RFCOMM_CLOSE_EVT, &evt_data, user_data);
    }
}

/*******************************************************************************
**
** Function     bta_jv_port_event_sr_cback
**
** Description  Callback for RFCOMM server port events
**
** Returns      void
**
*******************************************************************************/
static void bta_jv_port_event_sr_cback(UINT32 code, UINT16 port_handle)
{
    tBTA_JV_PCB     *p_pcb = bta_jv_rfc_port_to_pcb(port_handle);
    tBTA_JV_RFC_CB  *p_cb = bta_jv_rfc_port_to_cb(port_handle);
    tBTA_JV evt_data;

    if(NULL == p_cb || NULL == p_cb->p_cback)
        return;

    APPL_TRACE_DEBUG3( "bta_jv_port_event_sr_cback code=x%x port_handle:%d handle:%d",
        code, port_handle, p_cb->handle);

    void *user_data = p_pcb->user_data;
    if (code & PORT_EV_RXCHAR)
    {
        evt_data.data_ind.handle = p_cb->handle;
        p_cb->p_cback(BTA_JV_RFCOMM_DATA_IND_EVT, &evt_data, user_data);
    }

    if (code & PORT_EV_FC)
    {
        p_pcb->cong = (code & PORT_EV_FCS) ? FALSE : TRUE;
        evt_data.rfc_cong.cong = p_pcb->cong;
        evt_data.rfc_cong.handle = p_cb->handle;
        evt_data.rfc_cong.status = BTA_JV_SUCCESS;
        p_cb->p_cback(BTA_JV_RFCOMM_CONG_EVT, &evt_data, user_data);
    }
}

/*******************************************************************************
**
** Function     bta_jv_add_rfc_port
**
** Description  add a port for server when the existing posts is open
**
** Returns   return a pointer to tBTA_JV_PCB just added
**
*******************************************************************************/
static tBTA_JV_PCB * bta_jv_add_rfc_port(tBTA_JV_RFC_CB *p_cb)
{
    UINT8   used = 0, i, listen=0;
    UINT32  si = 0;
    tBTA_JV_PCB *p_pcb = NULL;
    tPORT_STATE port_state;
    UINT32 event_mask = (PORT_EV_RXCHAR | PORT_EV_FC | PORT_EV_FCS);

    if (p_cb->max_sess > 1)
    {
        for (i=0; i<p_cb->max_sess; i++)
        {
            if (p_cb->rfc_hdl[i] != 0)
            {
                p_pcb = &bta_jv_cb.port_cb[p_cb->rfc_hdl[i] - 1];
                if (p_pcb->state == BTA_JV_ST_SR_LISTEN)
                    listen++;
                used++;
            }
            else if (si==0)
            {
                si = (UINT32)(i + 1);
            }
        }

        debug("bta_jv_add_rfc_port max_sess=%d used:%d listen:%d si:%d",
                    p_cb->max_sess, used, listen, si);
        if (used <p_cb->max_sess && listen==0 && si)
        {
            si--;
            if (RFCOMM_CreateConnection(p_cb->sec_id, p_cb->scn, TRUE,
                BTA_JV_DEF_RFC_MTU, (UINT8 *) bd_addr_any, &(p_cb->rfc_hdl[si]), bta_jv_port_mgmt_sr_cback) == PORT_SUCCESS)
            {
                p_pcb = &bta_jv_cb.port_cb[p_cb->rfc_hdl[si] - 1];
                p_pcb->state = BTA_JV_ST_SR_LISTEN;
                p_pcb->port_handle = p_cb->rfc_hdl[si];
                PORT_SetEventCallback(p_pcb->port_handle, bta_jv_port_event_sr_cback);
                PORT_SetDataCOCallback (p_pcb->port_handle, bta_jv_port_data_co_cback);
                PORT_SetEventMask(p_pcb->port_handle, event_mask);
                PORT_GetState(p_pcb->port_handle, &port_state);

                port_state.fc_type = (PORT_FC_CTS_ON_INPUT | PORT_FC_CTS_ON_OUTPUT);

/* coverity[uninit_use_in_call]
FALSE-POSITIVE: port_state is initialized at PORT_GetState() */
                PORT_SetState(p_pcb->port_handle, &port_state);
                p_pcb->handle = BTA_JV_RFC_H_S_TO_HDL(p_cb->handle, si);
                APPL_TRACE_DEBUG1( "new rfc handle:0x%x", p_pcb->handle);
            }
        }
    }
    return p_pcb;
}

/*******************************************************************************
**
** Function     bta_jv_rfcomm_start_server
**
** Description  waits for an RFCOMM client to connect
**
**
** Returns      void
**
*******************************************************************************/
void bta_jv_rfcomm_start_server(tBTA_JV_MSG *p_data)
{
    UINT16 handle = 0;
    UINT32 event_mask = (PORT_EV_RXCHAR | PORT_EV_FC | PORT_EV_FCS);
    tPORT_STATE port_state;
    UINT8   sec_id;
    tBTA_JV_RFC_CB  *p_cb = NULL;
    tBTA_JV_PCB     *p_pcb;
    tBTA_JV_API_RFCOMM_SERVER *rs = &(p_data->rfcomm_server);
    tBTA_JV_RFCOMM_START        evt_data;

    /* TODO DM role manager
    L2CA_SetDesireRole(rs->role);
    */
    evt_data.status = BTA_JV_FAILURE;
    do
    {
        sec_id = bta_jv_alloc_sec_id();

        if (0 == sec_id ||
            BTM_SetSecurityLevel(FALSE, "JV PORT", sec_id,  rs->sec_mask,
                BT_PSM_RFCOMM, BTM_SEC_PROTO_RFCOMM, rs->local_scn) == FALSE)
        {
            break;
        }

        if (RFCOMM_CreateConnection(sec_id, rs->local_scn, TRUE,
            BTA_JV_DEF_RFC_MTU, (UINT8 *) bd_addr_any, &handle, bta_jv_port_mgmt_sr_cback) != PORT_SUCCESS)
        {
            break;
        }

        p_cb = bta_jv_alloc_rfc_cb(handle, &p_pcb);
        if(!p_cb)
        {
            APPL_TRACE_ERROR0("run out of rfc control block");
            break;
        }

        p_cb->max_sess = rs->max_session;
        p_cb->p_cback = rs->p_cback;
        p_cb->sec_id = sec_id;
        p_cb->scn = rs->local_scn;
        p_pcb->state = BTA_JV_ST_SR_LISTEN;
        p_pcb->user_data = rs->user_data;
        evt_data.status = BTA_JV_SUCCESS;
        evt_data.handle = p_cb->handle;
        evt_data.sec_id = sec_id;
        evt_data.use_co = TRUE; //FALSE;

        PORT_SetEventCallback(handle, bta_jv_port_event_sr_cback);
        PORT_SetEventMask(handle, event_mask);
        PORT_GetState(handle, &port_state);

        port_state.fc_type = (PORT_FC_CTS_ON_INPUT | PORT_FC_CTS_ON_OUTPUT);

/* coverity[uninit_use_in_call]
FALSE-POSITIVE: port_state is initialized at PORT_GetState() */
        PORT_SetState(handle, &port_state);
    } while (0);

    rs->p_cback(BTA_JV_RFCOMM_START_EVT, (tBTA_JV *)&evt_data, rs->user_data);
    if(evt_data.status == BTA_JV_SUCCESS)
    {
        PORT_SetDataCOCallback (handle, bta_jv_port_data_co_cback);
    }
}

/*******************************************************************************
**
** Function     bta_jv_rfcomm_stop_server
**
** Description  stops an RFCOMM server
**
** Returns      void
**
*******************************************************************************/

void bta_jv_rfcomm_stop_server(tBTA_JV_MSG *p_data)
{
    tBTA_JV_RFCOMM_CLOSE  evt_data;
    int i;
    tBTA_JV_API_RFCOMM_SERVER *ls = &(p_data->rfcomm_server);
    HDL2CB(ls->rfc_handle);
    evt_data.status = BTA_JV_FAILURE;
    if(p_cb && p_pcb)
    {
        evt_data.handle = p_cb->handle;
        void* user_data = p_pcb->user_data;
        evt_data.status = bta_jv_free_rfc_listen_cb(p_cb);
        evt_data.async = FALSE;

        /* occasionally when shutting down stack the callback is already
           freed, hence make sure we check for this condition (pending investigatation
           of rootcause) */
        debug("send BTA_JV_RFCOMM_CLOSE_EVT");
        if( p_cb->p_cback)
             p_cb->p_cback(BTA_JV_RFCOMM_CLOSE_EVT, (tBTA_JV *)&evt_data, user_data);
    }
    else
    {
        debug("warning, no jv callback set");
    }
}

/*******************************************************************************
**
** Function     bta_jv_rfcomm_read
**
** Description  Read data from an RFCOMM connection
**
** Returns      void
**
*******************************************************************************/
void bta_jv_rfcomm_read(tBTA_JV_MSG *p_data)
{
    tBTA_JV_API_RFCOMM_READ *rc = &(p_data->rfcomm_read);
    tBTA_JV_RFC_CB  *p_cb = rc->p_cb;
    tBTA_JV_PCB     *p_pcb = rc->p_pcb;
    tBTA_JV_RFCOMM_READ    evt_data;

    evt_data.status = BTA_JV_FAILURE;
    evt_data.handle = p_cb->handle;
    evt_data.req_id = rc->req_id;
    evt_data.p_data = rc->p_data;
    if (PORT_ReadData(rc->p_pcb->port_handle, (char *)rc->p_data, rc->len, &evt_data.len) ==
        PORT_SUCCESS)
    {
        evt_data.status = BTA_JV_SUCCESS;
    }

    p_cb->p_cback(BTA_JV_RFCOMM_READ_EVT, (tBTA_JV *)&evt_data, p_pcb->user_data);
}

/*******************************************************************************
**
** Function     bta_jv_rfcomm_write
**
** Description  write data to an RFCOMM connection
**
** Returns      void
**
*******************************************************************************/
void bta_jv_rfcomm_write(tBTA_JV_MSG *p_data)
{
    tBTA_JV_API_RFCOMM_WRITE *wc = &(p_data->rfcomm_write);
    tBTA_JV_RFC_CB  *p_cb = wc->p_cb;
    tBTA_JV_PCB     *p_pcb = wc->p_pcb;
    tBTA_JV_RFCOMM_WRITE    evt_data;

    evt_data.status = BTA_JV_FAILURE;
    evt_data.handle = p_cb->handle;
    evt_data.req_id = wc->req_id;
    evt_data.cong   = p_pcb->cong;
    evt_data.len    = 0;
    if (!evt_data.cong &&
        PORT_WriteDataCO(p_pcb->port_handle, &evt_data.len) ==
        PORT_SUCCESS)
    {
        evt_data.status = BTA_JV_SUCCESS;
    }
    //update congestion flag
    evt_data.cong   = p_pcb->cong;
    if (p_cb->p_cback)
    {
        p_cb->p_cback(BTA_JV_RFCOMM_WRITE_EVT, (tBTA_JV *)&evt_data, p_pcb->user_data);
    }
    else
    {
        APPL_TRACE_ERROR0("bta_jv_rfcomm_write :: WARNING ! No JV callback set");
    }
}

