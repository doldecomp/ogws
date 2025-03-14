/******************************************************************************
 *
 *  Copyright (C) 1999-2012 Broadcom Corporation
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
 *  This file contains functions for BLE device control utilities, and LE
 *  security functions.
 *
 ******************************************************************************/

#include <string.h>

#include "bt_types.h"
#include "hcimsgs.h"
#include "btu.h"
#include "btm_int.h"
#include "btm_ble_api.h"
#include "smp_api.h"

#if SMP_INCLUDED == TRUE
extern BOOLEAN AES_CMAC ( BT_OCTET16 key, UINT8 *input, UINT16 length, UINT16 tlen, UINT8 *p_signature);
extern void smp_link_encrypted(BD_ADDR bda, UINT8 encr_enable);
extern BOOLEAN smp_proc_ltk_request(BD_ADDR bda);
#endif

static void btm_ble_update_active_bgconn_scan_params(void);

/*******************************************************************************/
/* External Function to be called by other modules                             */
/*******************************************************************************/
/********************************************************
**
** Function         BTM_SecAddBleDevice
**
** Description      Add/modify device.  This function will be normally called
**                  during host startup to restore all required information
**                  for a LE device stored in the NVRAM.
**
** Parameters:      bd_addr          - BD address of the peer
**                  bd_name          - Name of the peer device.  NULL if unknown.
**                  dev_type         - Remote device's device type.
**                  addr_type        - LE device address type.
**
** Returns          TRUE if added OK, else FALSE
**
*******************************************************************************/
BOOLEAN BTM_SecAddBleDevice (BD_ADDR bd_addr, BD_NAME bd_name, tBT_DEVICE_TYPE dev_type,
                             tBLE_ADDR_TYPE addr_type)
{
#if BLE_INCLUDED == TRUE
    tBTM_SEC_DEV_REC  *p_dev_rec;
    UINT8               i = 0;
    tBTM_INQ_INFO      *p_info=NULL;

    BTM_TRACE_DEBUG1 ("BTM_SecAddBleDevice dev_type=0x%x", dev_type);
    p_dev_rec = btm_find_dev (bd_addr);

    if (!p_dev_rec)
    {
        BTM_TRACE_DEBUG0("Add a new device");

        /* There is no device record, allocate one.
         * If we can not find an empty spot for this one, let it fail. */
        for (i = 0; i < BTM_SEC_MAX_DEVICE_RECORDS; i++)
        {
            if (!(btm_cb.sec_dev_rec[i].sec_flags & BTM_SEC_IN_USE))
            {
                BTM_TRACE_DEBUG1 ("allocate a new dev rec idx=0x%x ", i );
                p_dev_rec = &btm_cb.sec_dev_rec[i];

                /* Mark this record as in use and initialize */
                memset (p_dev_rec, 0, sizeof (tBTM_SEC_DEV_REC));
                p_dev_rec->sec_flags = BTM_SEC_IN_USE;
                memcpy (p_dev_rec->bd_addr, bd_addr, BD_ADDR_LEN);
                p_dev_rec->hci_handle = BTM_GetHCIConnHandle (bd_addr);

                /* update conn params, use default value for background connection params */
                p_dev_rec->conn_params.min_conn_int     =
                p_dev_rec->conn_params.max_conn_int     =
                p_dev_rec->conn_params.supervision_tout =
                p_dev_rec->conn_params.slave_latency    = BTM_BLE_CONN_PARAM_UNDEF;

                BTM_TRACE_DEBUG1 ("hci_handl=0x%x ",  p_dev_rec->hci_handle );
                break;
            }
        }

        if (!p_dev_rec)
            return(FALSE);
    }
    else
    {
        BTM_TRACE_DEBUG0("Device already exist");
    }

    memset(p_dev_rec->sec_bd_name, 0, sizeof(tBTM_BD_NAME));

    if (bd_name && bd_name[0])
    {
        p_dev_rec->sec_flags |= BTM_SEC_NAME_KNOWN;
        BCM_STRNCPY_S ((char *)p_dev_rec->sec_bd_name, sizeof (p_dev_rec->sec_bd_name),
            (char *)bd_name, BTM_MAX_REM_BD_NAME_LEN);
    }
    p_dev_rec->device_type = dev_type;
    p_dev_rec->ble.ble_addr_type = addr_type;
    BTM_TRACE_DEBUG3 ("p_dev_rec->device_type =0x%x  addr_type=0x%x sec_flags=0x%x",
                      dev_type,  addr_type, p_dev_rec->sec_flags);

    /* sync up with the Inq Data base*/
    p_info = BTM_InqDbRead(bd_addr);
    if (p_info)
    {
        p_info->results.ble_addr_type = p_dev_rec->ble.ble_addr_type ;
        p_info->results.device_type = p_dev_rec->device_type;
        BTM_TRACE_DEBUG2 ("InqDb  device_type =0x%x  addr_type=0x%x",
                          p_info->results.device_type, p_info->results.ble_addr_type);
    }

#endif
    return(TRUE);
}

/*******************************************************************************
**
** Function         BTM_SecAddBleKey
**
** Description      Add/modify LE device information.  This function will be
**                  normally called during host startup to restore all required
**                  information stored in the NVRAM.
**
** Parameters:      bd_addr          - BD address of the peer
**                  p_le_key         - LE key values.
**                  key_type         - LE SMP key type.
*
** Returns          TRUE if added OK, else FALSE
**
*******************************************************************************/
BOOLEAN BTM_SecAddBleKey (BD_ADDR bd_addr, tBTM_LE_KEY_VALUE *p_le_key, tBTM_LE_KEY_TYPE key_type)
{
#if (BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE)
    tBTM_SEC_DEV_REC  *p_dev_rec;
    BTM_TRACE_DEBUG0 ("BTM_SecAddBleKey");
    p_dev_rec = btm_find_dev (bd_addr);
    if (!p_dev_rec || !p_le_key ||
        (key_type != BTM_LE_KEY_PENC && key_type != BTM_LE_KEY_PID &&
         key_type != BTM_LE_KEY_PCSRK && key_type != BTM_LE_KEY_LENC))
    {
        BTM_TRACE_WARNING3 ("BTM_SecAddLeKey()  No BT Link Key, Wrong Type, or No Device record \
                        for bdaddr: %08x%04x, Type: %d",
                            (bd_addr[0]<<24)+(bd_addr[1]<<16)+(bd_addr[2]<<8)+bd_addr[3],
                            (bd_addr[4]<<8)+bd_addr[5], key_type);
        return(FALSE);
    }

    BTM_TRACE_DEBUG3 ("BTM_SecAddLeKey()  BDA: %08x%04x, Type: 0x%02x",
                      (bd_addr[0]<<24)+(bd_addr[1]<<16)+(bd_addr[2]<<8)+bd_addr[3],
                      (bd_addr[4]<<8)+bd_addr[5], key_type);

    if (key_type == BTM_LE_KEY_PENC || key_type == BTM_LE_KEY_PID ||
        key_type == BTM_LE_KEY_PCSRK || key_type == BTM_LE_KEY_LENC ||
        key_type == BTM_LE_KEY_LCSRK)
    {
        btm_sec_save_le_key (bd_addr, key_type, p_le_key, FALSE);
    }

#endif

    return(TRUE);
}

/*******************************************************************************
**
** Function         BTM_BleLoadLocalKeys
**
** Description      Local local identity key, encryption root or sign counter.
**
** Parameters:      key_type: type of key, can be BTM_BLE_KEY_TYPE_ID, BTM_BLE_KEY_TYPE_ER
**                            or BTM_BLE_KEY_TYPE_COUNTER.
**                  p_key: pointer to the key.
*
** Returns          non2.
**
*******************************************************************************/
void BTM_BleLoadLocalKeys(UINT8 key_type, tBTM_BLE_LOCAL_KEYS *p_key)
{
#if BLE_INCLUDED == TRUE
    tBTM_DEVCB *p_devcb = &btm_cb.devcb;
    BTM_TRACE_DEBUG0 ("BTM_BleLoadLocalKeys");
    if (p_key != NULL)
    {
        switch (key_type)
        {
            case BTM_BLE_KEY_TYPE_ID:
                memcpy(&p_devcb->id_keys, &p_key->id_keys, sizeof(tBTM_BLE_LOCAL_ID_KEYS));
                break;

            case BTM_BLE_KEY_TYPE_ER:
                memcpy(p_devcb->er, p_key->er, sizeof(BT_OCTET16));
                break;

            default:
                BTM_TRACE_ERROR1("unknow local key type: %d", key_type);
                break;
        }
    }
#endif
}

/*******************************************************************************
**
** Function         BTM_GetDeviceEncRoot
**
** Description      This function is called to read the local device encryption
**                  root.
**
** Returns          void
**                  the local device ER is copied into er
**
*******************************************************************************/
void BTM_GetDeviceEncRoot (BT_OCTET16 er)
{
    BTM_TRACE_DEBUG0 ("BTM_GetDeviceEncRoot");

#if BLE_INCLUDED == TRUE
    memcpy (er, btm_cb.devcb.er, BT_OCTET16_LEN);
#endif
}

/*******************************************************************************
**
** Function         BTM_GetDeviceIDRoot
**
** Description      This function is called to read the local device identity
**                  root.
**
** Returns          void
**                  the local device IR is copied into irk
**
*******************************************************************************/
void BTM_GetDeviceIDRoot (BT_OCTET16 irk)
{
    BTM_TRACE_DEBUG0 ("BTM_GetDeviceIDRoot ");

#if BLE_INCLUDED == TRUE
    memcpy (irk, btm_cb.devcb.id_keys.irk, BT_OCTET16_LEN);
#endif
}

/*******************************************************************************
**
** Function         BTM_GetDeviceDHK
**
** Description      This function is called to read the local device DHK.
**
** Returns          void
**                  the local device DHK is copied into dhk
**
*******************************************************************************/
void BTM_GetDeviceDHK (BT_OCTET16 dhk)
{
#if BLE_INCLUDED == TRUE
    BTM_TRACE_DEBUG0 ("BTM_GetDeviceDHK");
    memcpy (dhk, btm_cb.devcb.id_keys.dhk, BT_OCTET16_LEN);
#endif
}

/*******************************************************************************
**
** Function         BTM_ReadConnectionAddr
**
** Description      This function is called to set the local device random address
**                  .
**
** Returns          void
**
*******************************************************************************/
void BTM_ReadConnectionAddr (BD_ADDR conn_addr)
{
#if BLE_INCLUDED == TRUE
    BTM_TRACE_DEBUG0 ("BTM_ReadConnectionAddr");
    if (btm_cb.ble_ctr_cb.inq_var.own_addr_type == BLE_ADDR_PUBLIC)
    {
        BTM_GetLocalDeviceAddr(conn_addr);
    }
    else
    {
        memcpy (conn_addr, btm_cb.ble_ctr_cb.addr_mgnt_cb.private_addr, BD_ADDR_LEN);
    }
#endif
}

/*******************************************************************************
**
** Function         BTM_SecurityGrant
**
** Description      This function is called to grant security process.
**
** Parameters       bd_addr - peer device bd address.
**                  res     - result of the operation BTM_SUCCESS if success.
**                            Otherwise, BTM_REPEATED_ATTEMPTS is too many attempts.
**
** Returns          None
**
*******************************************************************************/
void BTM_SecurityGrant(BD_ADDR bd_addr, UINT8 res)
{
#if (BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE)
    tSMP_STATUS res_smp = (res == BTM_SUCCESS) ? SMP_SUCCESS : SMP_REPEATED_ATTEMPTS;
    BTM_TRACE_DEBUG0 ("BTM_SecurityGrant");
    SMP_SecurityGrant(bd_addr, res_smp);
#endif
}

/*******************************************************************************
**
** Function         BTM_BlePasskeyReply
**
** Description      This function is called after Security Manager submitted
**                  passkey request to the application.
**
** Parameters:      bd_addr      - Address of the device for which passkey was requested
**                  res          - result of the operation BTM_SUCCESS if success
**                  key_len      - length in bytes of the Passkey
**                  p_passkey        - pointer to array with the passkey
**                  trusted_mask - bitwise OR of trusted services (array of UINT32)
**
*******************************************************************************/
void BTM_BlePasskeyReply (BD_ADDR bd_addr, UINT8 res, UINT32 passkey)
{
#if (BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE)
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev (bd_addr);
    tSMP_STATUS      res_smp = (res == BTM_SUCCESS) ? SMP_SUCCESS : SMP_PASSKEY_ENTRY_FAIL;

    p_dev_rec->sec_flags   |= BTM_SEC_LINK_KEY_AUTHED;
    BTM_TRACE_DEBUG0 ("BTM_BlePasskeyReply");
    SMP_PasskeyReply(bd_addr, res_smp, passkey);
#endif
}

/*******************************************************************************
**
** Function         BTM_BleOobDataReply
**
** Description      This function is called to provide the OOB data for
**                  SMP in response to BTM_LE_OOB_REQ_EVT
**
** Parameters:      bd_addr     - Address of the peer device
**                  res         - result of the operation SMP_SUCCESS if success
**                  p_data      - simple pairing Randomizer  C.
**
*******************************************************************************/
void BTM_BleOobDataReply(BD_ADDR bd_addr, UINT8 res, UINT8 len, UINT8 *p_data)
{
#if (BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE)
    tSMP_STATUS res_smp = (res == BTM_SUCCESS) ? SMP_SUCCESS : SMP_OOB_FAIL;
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev (bd_addr);

    BTM_TRACE_DEBUG0 ("BTM_BleOobDataReply");
    p_dev_rec->sec_flags |= BTM_SEC_LINK_KEY_AUTHED;
    SMP_OobDataReply(bd_addr, res_smp, len, p_data);
#endif
}

/******************************************************************************
**
** Function         BTM_BleSetConnScanParams
**
** Description      Set scan parameter used in BLE connection request
**
** Parameters:      scan_interval: scan interval
**                  scan_window: scan window
**
** Returns          void
**
*******************************************************************************/
void BTM_BleSetConnScanParams (UINT16 scan_interval, UINT16 scan_window)
{
#if (BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE)
    tBTM_BLE_CB *p_ble_cb = &btm_cb.ble_ctr_cb;
    BOOLEAN     new_param = FALSE;

    if (BTM_BLE_VALID_PRAM(scan_interval, BTM_BLE_SCAN_INT_MIN, BTM_BLE_SCAN_INT_MAX) &&
        BTM_BLE_VALID_PRAM(scan_window, BTM_BLE_SCAN_WIN_MIN, BTM_BLE_SCAN_WIN_MAX))
    {
        btu_stop_timer(&p_ble_cb->scan_param_idle_timer);

        if (p_ble_cb->scan_int != scan_interval)
        {
            p_ble_cb->scan_int = scan_interval;
            new_param = TRUE;
        }

        if (p_ble_cb->scan_win != scan_window)
        {
            p_ble_cb->scan_win = scan_window;
            new_param = TRUE;
        }

        if (new_param)
            btm_ble_update_active_bgconn_scan_params();
    }
    else
    {
        BTM_TRACE_ERROR0("Illegal Connection Scan Parameters");
    }
#endif
}

/********************************************************
**
** Function         BTM_BleSetPrefConnParams
**
** Description      Set a peripheral's preferred connection parameters
**
** Parameters:      bd_addr          - BD address of the peripheral
**                  scan_interval: scan interval
**                  scan_window: scan window
**                  min_conn_int     - minimum preferred connection interval
**                  max_conn_int     - maximum preferred connection interval
**                  slave_latency    - preferred slave latency
**                  supervision_tout - preferred supervision timeout
**
** Returns          void
**
*******************************************************************************/
void BTM_BleSetPrefConnParams (BD_ADDR bd_addr,
                               UINT16 min_conn_int, UINT16 max_conn_int,
                               UINT16 slave_latency, UINT16 supervision_tout)
{
#if BLE_INCLUDED == TRUE
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev (bd_addr);

    BTM_TRACE_API4 ("BTM_BleSetPrefConnParams min: %u  max: %u  latency: %u  \
                    tout: %u",
                    min_conn_int, max_conn_int, slave_latency, supervision_tout);

    if (BTM_BLE_VALID_PRAM(min_conn_int, BTM_BLE_CONN_INT_MIN, BTM_BLE_CONN_INT_MAX) &&
        BTM_BLE_VALID_PRAM(max_conn_int, BTM_BLE_CONN_INT_MIN, BTM_BLE_CONN_INT_MAX) &&
        BTM_BLE_VALID_PRAM(supervision_tout, BTM_BLE_CONN_SUP_TOUT_MIN, BTM_BLE_CONN_SUP_TOUT_MAX) &&
        slave_latency <= BTM_BLE_CONN_LATENCY_MAX)
    {
        if (p_dev_rec)
        {
            /* expect conn int and stout and slave latency to be updated all together */
            if (min_conn_int != BTM_BLE_CONN_PARAM_UNDEF || max_conn_int != BTM_BLE_CONN_PARAM_UNDEF)
            {
                if (min_conn_int != BTM_BLE_CONN_PARAM_UNDEF)
                    p_dev_rec->conn_params.min_conn_int = min_conn_int;
                else
                    p_dev_rec->conn_params.min_conn_int = max_conn_int;

                if (max_conn_int != BTM_BLE_CONN_PARAM_UNDEF)
                    p_dev_rec->conn_params.max_conn_int = max_conn_int;
                else
                    p_dev_rec->conn_params.max_conn_int = min_conn_int;

                if (slave_latency != BTM_BLE_CONN_PARAM_UNDEF)
                    p_dev_rec->conn_params.slave_latency = slave_latency;
                else
                    p_dev_rec->conn_params.slave_latency = BTM_BLE_CONN_SLAVE_LATENCY_DEF;

                if (supervision_tout != BTM_BLE_CONN_PARAM_UNDEF)
                    p_dev_rec->conn_params.supervision_tout = supervision_tout;
                else
                    p_dev_rec->conn_params.slave_latency = BTM_BLE_CONN_TIMEOUT_DEF;

            }

        }
        else
        {
            BTM_TRACE_ERROR0("Unknown Device, setting rejected");
        }
    }
    else
    {
        BTM_TRACE_ERROR0("Illegal Connection Parameters");
    }
#endif  /* BLE_INCLUDED */
}

/*******************************************************************************
**
** Function         BTM_ReadDevInfo
**
** Description      This function is called to read the device/address type
**                  of BD address.
**
** Parameter        remote_bda: remote device address
**                  p_dev_type: output parameter to read the device type.
**                  p_addr_type: output parameter to read the address type.
**
*******************************************************************************/
void BTM_ReadDevInfo (BD_ADDR remote_bda, tBT_DEVICE_TYPE *p_dev_type, tBLE_ADDR_TYPE *p_addr_type)
{
#if BLE_INCLUDED == TRUE
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev (remote_bda);
    tBTM_INQ_INFO     *p_inq_info = BTM_InqDbRead(remote_bda);

    *p_dev_type = BT_DEVICE_TYPE_BREDR;
    *p_addr_type = BLE_ADDR_PUBLIC;

    if (!p_dev_rec)
    {
        /* Check with the BT manager if details about remote device are known */
        if (p_inq_info != NULL)
        {
            *p_dev_type = p_inq_info->results.device_type ;
            *p_addr_type = p_inq_info->results.ble_addr_type;
        }
        /* unknown device, assume BR/EDR */
    }
    else /* there is a security device record exisitng */
    {
        /* new inquiry result, overwrite device type in security device record */
        if (p_inq_info)
        {
            p_dev_rec->device_type          = p_inq_info->results.device_type;
            p_dev_rec->ble.ble_addr_type    = p_inq_info->results.ble_addr_type;
        }
        *p_dev_type = p_dev_rec->device_type;
        *p_addr_type = p_dev_rec->ble.ble_addr_type;

    }

    BTM_TRACE_DEBUG2 ("btm_find_dev_type - device_type = %d addr_type = %d", *p_dev_type , *p_addr_type);
#endif

    return;
}


/*******************************************************************************
** Internal Functions
*******************************************************************************/
#if BLE_INCLUDED == TRUE

/*******************************************************************************
**
** Function         btm_ble_update_active_bgconn_scan_params
**
** Description      This function is called to update the scan parameter if background
**                  connection has been active.
**
*******************************************************************************/
static void btm_ble_update_active_bgconn_scan_params(void)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    tBTM_BLE_SEL_CBACK   *p_select_cback;

    /* if active , cancel and restart and apply the params */
    if (p_cb->bg_conn_state == BLE_BG_CONN_ACTIVE)
    {
        if (p_cb->bg_conn_type == BTM_BLE_CONN_AUTO)
        {
            if (btm_ble_start_auto_conn(FALSE))
                btm_ble_start_auto_conn(TRUE);
        }
        else if (p_cb->bg_conn_type == BTM_BLE_CONN_SELECTIVE)
        {
            p_select_cback = p_cb->p_select_cback;
            if (btm_ble_start_select_conn(FALSE, NULL))
                btm_ble_start_select_conn(TRUE, p_select_cback);
        }
    }
    return;
}

/*******************************************************************************
**
** Function         btm_ble_check_link_type
**
** Description      This function is to check the link type is BLE or BR/EDR.
**
** Returns          TRUE if BLE link; FALSE if BR/EDR.
**
*******************************************************************************/
BOOLEAN btm_ble_check_link_type (BD_ADDR bd_addr)
{
    tACL_CONN         *p;
    BTM_TRACE_DEBUG0 ("btm_ble_check_link_type");
    if ((p = btm_bda_to_acl(bd_addr)) != NULL)
        return p->is_le_link;
    else
        return FALSE;
}

/*******************************************************************************
**
** Function         btm_ble_rand_enc_complete
**
** Description      This function is the callback functions for HCI_Rand command
**                  and HCI_Encrypt command is completed.
**                  This message is received from the HCI.
**
** Returns          void
**
*******************************************************************************/
void btm_ble_rand_enc_complete (UINT8 *p, UINT16 op_code, tBTM_RAND_ENC_CB *p_enc_cplt_cback)
{
    tBTM_RAND_ENC   params;
    UINT8           *p_dest = params.param_buf;

    BTM_TRACE_DEBUG0 ("btm_ble_rand_enc_complete");

    memset(&params, 0, sizeof(tBTM_RAND_ENC));

    /* If there was a callback address for vcs complete, call it */
    if (p_enc_cplt_cback && p)
    {
        /* Pass paramters to the callback function */
        STREAM_TO_UINT8(params.status, p); /* command status */

        if (params.status == HCI_SUCCESS)
        {
            params.opcode = op_code;

            if (op_code == HCI_BLE_RAND)
                params.param_len = BT_OCTET8_LEN;
            else
                params.param_len = BT_OCTET16_LEN;

            memcpy(p_dest, p, params.param_len);  /* Fetch return info from HCI event message */
        }
        if (p_enc_cplt_cback)
            (*p_enc_cplt_cback)(&params);  /* Call the Encryption complete callback function */
    }
}


#if (SMP_INCLUDED == TRUE)

/*******************************************************************************
**
** Function         btm_ble_get_enc_key_type
**
** Description      This function is to increment local sign counter
** Returns         None
**
*******************************************************************************/
void btm_ble_increment_sign_ctr(BD_ADDR bd_addr, BOOLEAN is_local )
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    BTM_TRACE_DEBUG1 ("btm_ble_increment_sign_ctr is_local=%d", is_local);

    if ((p_dev_rec = btm_find_dev (bd_addr)) != NULL)
    {
        if (is_local)
            p_dev_rec->ble.keys.local_counter++;
        else
            p_dev_rec->ble.keys.counter++;
        BTM_TRACE_DEBUG3 ("is_local=%d local sign counter=%d peer sign counter=%d",
                          is_local,
                          p_dev_rec->ble.keys.local_counter,
                          p_dev_rec->ble.keys.counter);
    }
}

/*******************************************************************************
**
** Function         btm_ble_get_enc_key_type
**
** Description      This function is to get the BLE key type that has been exchanged
**                  in betweem local device and peer device.
**
** Returns          p_key_type: output parameter to carry the key type value.
**
*******************************************************************************/
BOOLEAN btm_ble_get_enc_key_type(BD_ADDR bd_addr, UINT8 *p_key_types)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    BTM_TRACE_DEBUG0 ("btm_ble_get_enc_key_type");

    if ((p_dev_rec = btm_find_dev (bd_addr)) != NULL)
    {
        *p_key_types = p_dev_rec->ble.key_type;
        return TRUE;
    }
    return FALSE;
}

/*******************************************************************************
**
** Function         btm_get_local_div
**
** Description      This function is called to read the local DIV
**
** Returns          TURE - if a valid DIV is availavle
*******************************************************************************/
BOOLEAN btm_get_local_div (BD_ADDR bd_addr, UINT16 *p_div)
{
    tBTM_SEC_DEV_REC   *p_dev_rec;
    BOOLEAN            status = FALSE;
    BTM_TRACE_DEBUG0 ("btm_get_local_div");

    BTM_TRACE_DEBUG6("bd_addr:%02x-%02x-%02x-%02x-%02x-%02x",
                     bd_addr[0],bd_addr[1],
                     bd_addr[2],bd_addr[3],
                     bd_addr[4],bd_addr[5]);

    p_dev_rec = btm_find_dev (bd_addr);

    if (p_dev_rec && p_dev_rec->ble.keys.div)
    {
        status = TRUE;
        *p_div = p_dev_rec->ble.keys.div;
    }
    BTM_TRACE_DEBUG2 ("btm_get_local_div status=%d (1-OK) DIV=0x%x", status, *p_div);
    return status;
}

/*******************************************************************************
**
** Function         btm_sec_save_le_key
**
** Description      This function is called by the SMP to update
**                  an  BLE key.  SMP is internal, whereas all the keys shall
**                  be sent to the application.  The function is also called
**                  when application passes ble key stored in NVRAM to the btm_sec.
**                  pass_to_application parameter is false in this case.
**
** Returns          void
**
*******************************************************************************/
void btm_sec_save_le_key(BD_ADDR bd_addr, tBTM_LE_KEY_TYPE key_type, tBTM_LE_KEY_VALUE *p_keys,
                         BOOLEAN pass_to_application)
{
    tBTM_SEC_DEV_REC *p_rec;
    tBTM_LE_EVT_DATA    cb_data;

    BTM_TRACE_DEBUG2 ("btm_sec_save_le_key key_type=0x%x pass_to_application=%d",key_type, pass_to_application);
    /* Store the updated key in the device database */

    BTM_TRACE_DEBUG6("bd_addr:%02x-%02x-%02x-%02x-%02x-%02x",
                     bd_addr[0],bd_addr[1],
                     bd_addr[2],bd_addr[3],
                     bd_addr[4],bd_addr[5]);

    if ((p_rec = btm_find_dev (bd_addr)) != NULL && p_keys)
    {
        switch (key_type)
        {
            case BTM_LE_KEY_PENC:
                memcpy(p_rec->ble.keys.ltk, p_keys->penc_key.ltk, BT_OCTET16_LEN);
                memcpy(p_rec->ble.keys.rand, p_keys->penc_key.rand, BT_OCTET8_LEN);
                p_rec->ble.keys.sec_level = p_keys->penc_key.sec_level;
                p_rec->ble.keys.ediv = p_keys->penc_key.ediv;
                p_rec->ble.keys.key_size = p_keys->penc_key.key_size;
                p_rec->ble.key_type |= BTM_LE_KEY_PENC;
                p_rec->sec_flags |= BTM_SEC_LINK_KEY_KNOWN;
                if (p_keys->penc_key.sec_level == SMP_SEC_AUTHENTICATED)
                    p_rec->sec_flags |= BTM_SEC_LINK_KEY_AUTHED;
                else
                    p_rec->sec_flags &= ~BTM_SEC_LINK_KEY_AUTHED;
                BTM_TRACE_DEBUG3("BTM_LE_KEY_PENC key_type=0x%x sec_flags=0x%x sec_leve=0x%x",
                                 p_rec->ble.key_type,
                                 p_rec->sec_flags,
                                 p_rec->ble.keys.sec_level);
                break;

            case BTM_LE_KEY_PID:
                memcpy(p_rec->ble.keys.irk, p_keys->pid_key, BT_OCTET16_LEN);
                p_rec->ble.key_type |= BTM_LE_KEY_PID;
                BTM_TRACE_DEBUG1("BTM_LE_KEY_PID key_type=0x%x save peer IRK",  p_rec->ble.key_type);
                break;

            case BTM_LE_KEY_PCSRK:
                memcpy(p_rec->ble.keys.csrk, p_keys->pcsrk_key.csrk, BT_OCTET16_LEN);
                p_rec->ble.keys.srk_sec_level = p_keys->pcsrk_key.sec_level;
                p_rec->ble.keys.counter  = p_keys->pcsrk_key.counter;
                p_rec->ble.key_type |= BTM_LE_KEY_PCSRK;
                p_rec->sec_flags |=  BTM_SEC_LINK_KEY_KNOWN;
                if ( p_keys->pcsrk_key.sec_level== SMP_SEC_AUTHENTICATED)
                    p_rec->sec_flags |= BTM_SEC_LINK_KEY_AUTHED;
                else
                    p_rec->sec_flags &= ~BTM_SEC_LINK_KEY_AUTHED;

                BTM_TRACE_DEBUG4("BTM_LE_KEY_PCSRK key_type=0x%x sec_flags=0x%x sec_level=0x%x peer_counter=%d",
                                 p_rec->ble.key_type,
                                 p_rec->sec_flags,
                                 p_rec->ble.keys.srk_sec_level,
                                 p_rec->ble.keys.counter );
                break;

            case BTM_LE_KEY_LENC:
                p_rec->ble.keys.div = p_keys->lenc_key.div; /* update DIV */
                p_rec->ble.keys.sec_level = p_keys->lenc_key.sec_level;
                p_rec->ble.keys.key_size = p_keys->lenc_key.key_size;
                p_rec->ble.key_type |= BTM_LE_KEY_LENC;

                BTM_TRACE_DEBUG4("BTM_LE_KEY_LENC key_type=0x%x DIV=0x%x key_size=0x%x sec_level=0x%x",
                                 p_rec->ble.key_type,
                                 p_rec->ble.keys.div,
                                 p_rec->ble.keys.key_size,
                                 p_rec->ble.keys.sec_level );
                break;

            case BTM_LE_KEY_LCSRK:/* local CSRK has been delivered */
                p_rec->ble.keys.div = p_keys->lcsrk_key.div; /* update DIV */
                p_rec->ble.keys.local_csrk_sec_level = p_keys->lcsrk_key.sec_level;
                p_rec->ble.keys.local_counter  = p_keys->lcsrk_key.counter;
                p_rec->ble.key_type |= BTM_LE_KEY_LCSRK;
                BTM_TRACE_DEBUG4("BTM_LE_KEY_LCSRK key_type=0x%x DIV=0x%x scrk_sec_level=0x%x local_counter=%d",
                                 p_rec->ble.key_type,
                                 p_rec->ble.keys.div,
                                 p_rec->ble.keys.local_csrk_sec_level,
                                 p_rec->ble.keys.local_counter );
                break;

            default:
                BTM_TRACE_WARNING1("btm_sec_save_le_key (Bad key_type 0x%02x)", key_type);
                return;
        }

        BTM_TRACE_DEBUG3 ("BLE key type 0x%02x updated for BDA: %08x%04x (btm_sec_save_le_key)", key_type,
                          (bd_addr[0]<<24)+(bd_addr[1]<<16)+(bd_addr[2]<<8)+bd_addr[3],
                          (bd_addr[4]<<8)+bd_addr[5]);

        /* Notify the application that one of the BLE keys has been updated
           If link key is in progress, it will get sent later.*/
        if (pass_to_application && btm_cb.api.p_le_callback)
        {
            cb_data.key.p_key_value = p_keys;
            cb_data.key.key_type = key_type;

            (*btm_cb.api.p_le_callback) (BTM_LE_KEY_EVT, bd_addr, &cb_data);
        }
        return;
    }

    BTM_TRACE_WARNING3 ("BLE key type 0x%02x called for Unknown BDA or type: %08x%04x !! (btm_sec_save_le_key)", key_type,
                        (bd_addr[0]<<24)+(bd_addr[1]<<16)+(bd_addr[2]<<8)+bd_addr[3],
                        (bd_addr[4]<<8)+bd_addr[5]);

    if (p_rec)
    {
        BTM_TRACE_DEBUG1 ("sec_flags=0x%x", p_rec->sec_flags);
    }
}

/*******************************************************************************
**
** Function         btm_ble_update_sec_key_size
**
** Description      update the current lin kencryption key size
**
** Returns          void
**
*******************************************************************************/
void btm_ble_update_sec_key_size(BD_ADDR bd_addr, UINT8 enc_key_size)
{
    tBTM_SEC_DEV_REC *p_rec;

    BTM_TRACE_DEBUG1("btm_ble_update_sec_key_size enc_key_size = %d", enc_key_size);

    if ((p_rec = btm_find_dev (bd_addr)) != NULL )
    {
        p_rec->enc_key_size = enc_key_size;
    }
}

/*******************************************************************************
**
** Function         btm_ble_read_sec_key_size
**
** Description      update the current lin kencryption key size
**
** Returns          void
**
*******************************************************************************/
UINT8 btm_ble_read_sec_key_size(BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_rec;

    if ((p_rec = btm_find_dev (bd_addr)) != NULL )
    {
        return p_rec->enc_key_size;
    }
    else
        return 0;
}

/*******************************************************************************
**
** Function         btm_ble_link_sec_check
**
** Description      Check BLE link security level match.
**
** Returns          TRUE: check is OK and the *p_sec_req_act contain the action
**
*******************************************************************************/
void btm_ble_link_sec_check(BD_ADDR bd_addr, tBTM_LE_AUTH_REQ auth_req, tBTM_BLE_SEC_REQ_ACT *p_sec_req_act)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev (bd_addr);
    UINT8 req_sec_level, cur_sec_level;

    BTM_TRACE_DEBUG1 ("btm_ble_link_sec_check auth_req =0x%x", auth_req);

    if (p_dev_rec == NULL)
    {
        BTM_TRACE_ERROR0 ("btm_ble_link_sec_check received for unknown device");
        return;
    }

    if (p_dev_rec->sec_state == BTM_SEC_STATE_ENCRYPTING)
    {
        /* race condition: discard the security request while master is encrypting the link */
        *p_sec_req_act = BTM_BLE_SEC_REQ_ACT_DISCARD;
    }
    else
    {
        req_sec_level = BTM_LE_SEC_UNAUTHENTICATE;
        if ((auth_req == (BTM_LE_AUTH_REQ_BOND|BTM_LE_AUTH_REQ_MITM)) ||
            (auth_req == (BTM_LE_AUTH_REQ_MITM)) )
        {
            req_sec_level = BTM_LE_SEC_AUTHENTICATED;
        }

        BTM_TRACE_DEBUG1 ("dev_rec sec_flags=0x%x", p_dev_rec->sec_flags);

        /* currently encrpted  */
        if (p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED)
        {
            if (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_AUTHED)
                cur_sec_level = BTM_LE_SEC_AUTHENTICATED;
            else
                cur_sec_level = BTM_LE_SEC_UNAUTHENTICATE;
        }
        else /* unencrypted link */
        {
            /* if bonded, get the key security level */
            if (p_dev_rec->ble.key_type & BTM_LE_KEY_PENC)
                cur_sec_level = p_dev_rec->ble.keys.sec_level;
            else
                cur_sec_level = BTM_LE_SEC_NONE;
        }

        if (cur_sec_level >= req_sec_level)
        {
            if (cur_sec_level == BTM_LE_SEC_NONE)
            {
                *p_sec_req_act = BTM_BLE_SEC_REQ_ACT_NONE;
            }
            else
            {
                /* To avoid re-encryption on an encrypted link for an equal condition encryption
                if (p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED)
                    *p_sec_req_act = BTM_BLE_SEC_REQ_ACT_DISCARD;
                else
                */
                    *p_sec_req_act = BTM_BLE_SEC_REQ_ACT_ENCRYPT;
            }
        }
        else
        {
            *p_sec_req_act =  BTM_BLE_SEC_REQ_ACT_PAIR; /* start the pariring process to upgrade the keys*/
        }
    }

    BTM_TRACE_DEBUG3("cur_sec_level=%d req_sec_level=%d sec_req_act=%d",
                     cur_sec_level,
                     req_sec_level,
                     *p_sec_req_act);

}

/*******************************************************************************
**
** Function         btm_ble_set_encryption
**
** Description      This function is called to ensure that LE connection is
**                  encrypted.  Should be called only on an open connection.
**                  Typically only needed for connections that first want to
**                  bring up unencrypted links, then later encrypt them.
**
** Returns          void
**                  the local device ER is copied into er
**
*******************************************************************************/
tBTM_STATUS btm_ble_set_encryption (BD_ADDR bd_addr, void *p_ref_data, UINT8 link_role)
{
    tBTM_STATUS         cmd = BTM_NO_RESOURCES;
    tBTM_BLE_SEC_ACT    sec_act = *(tBTM_BLE_SEC_ACT *)p_ref_data ;
    tBTM_SEC_DEV_REC    *p_rec = btm_find_dev (bd_addr);

    BTM_TRACE_DEBUG2 ("btm_ble_set_encryption sec_act=0x%x role_master=%d", sec_act, p_rec->role_master);

    if (p_rec == NULL)
    {
        return(BTM_WRONG_MODE);
    }

    if (sec_act == BTM_BLE_SEC_ENCRYPT_MITM)
    {
        p_rec->security_required |= BTM_SEC_IN_MITM;
    }

    switch (sec_act)
    {
        case BTM_BLE_SEC_ENCRYPT:
            if (link_role == BTM_ROLE_MASTER)
            {
                /* start link layer encryption using the security info stored */
                btm_ble_start_encrypt(bd_addr, FALSE, NULL);
                p_rec->sec_state = BTM_SEC_STATE_ENCRYPTING;
                cmd = BTM_CMD_STARTED;
                break;
            }
            /* if salve role then fall through to call SMP_Pair below which will send a
               sec_request to request the master to encrypt the link */
        case BTM_BLE_SEC_ENCRYPT_NO_MITM:
        case BTM_BLE_SEC_ENCRYPT_MITM:

            if (SMP_Pair(bd_addr) == SMP_STARTED)
            {
                cmd = BTM_CMD_STARTED;
                p_rec->sec_state = BTM_SEC_STATE_AUTHENTICATING;
            }
            break;

        default:
            cmd = BTM_SUCCESS;
            break;
    }
    return cmd;
}

/*******************************************************************************
**
** Function         btm_ble_ltk_request
**
** Description      This function is called when encryption request is received
**                  on a slave device.
**
**
** Returns          void
**
*******************************************************************************/
void btm_ble_ltk_request(UINT16 handle, UINT8 rand[8], UINT16 ediv)
{
    tBTM_CB *p_cb = &btm_cb;
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev_by_handle (handle);
    BT_OCTET8 dummy_stk = {0};

    BTM_TRACE_DEBUG0 ("btm_ble_ltk_request");

    p_cb->ediv = ediv;

    memcpy(p_cb->enc_rand, rand, BT_OCTET8_LEN);

    if (!smp_proc_ltk_request(p_dev_rec->bd_addr))
        btm_ble_ltk_request_reply(p_dev_rec->bd_addr, FALSE, dummy_stk);


}

/*******************************************************************************
**
** Function         btm_ble_start_encrypt
**
** Description      This function is called to start LE encryption.
**
**
** Returns          void
**
*******************************************************************************/
BOOLEAN btm_ble_start_encrypt(BD_ADDR bda, BOOLEAN use_stk, BT_OCTET16 stk)
{
    tBTM_CB *p_cb = &btm_cb;
    tBTM_SEC_DEV_REC    *p_rec = btm_find_dev (bda);
    BT_OCTET8    dummy_rand = {0};

    BTM_TRACE_DEBUG0 ("btm_ble_start_encrypt");

    if (!p_rec ||
        (p_rec && p_rec->sec_state == BTM_SEC_STATE_ENCRYPTING))
        return FALSE;

    if (p_rec->sec_state == BTM_SEC_STATE_IDLE)
        p_rec->sec_state = BTM_SEC_STATE_ENCRYPTING;
    p_cb->enc_handle = p_rec->hci_handle;

    if (use_stk)
    {
        if (!btsnd_hcic_ble_start_enc(p_rec->hci_handle, dummy_rand, 0, stk))
            return FALSE;
    }
    else
    {
        if (!btsnd_hcic_ble_start_enc(p_rec->hci_handle, p_rec->ble.keys.rand,
                                      p_rec->ble.keys.ediv, p_rec->ble.keys.ltk))
            return FALSE;
    }
    return TRUE;
}

/*******************************************************************************
**
** Function         btm_ble_link_encrypted
**
** Description      This function is called when LE link encrption status is changed.
**
** Returns          void
**
*******************************************************************************/
void btm_ble_link_encrypted(BD_ADDR bd_addr, UINT8 encr_enable)
{
    tBTM_SEC_DEV_REC    *p_dev_rec = btm_find_dev (bd_addr);

    BTM_TRACE_DEBUG1 ("btm_ble_link_encrypted encr_enable=%d", encr_enable);

    smp_link_encrypted(bd_addr, encr_enable);

    if (p_dev_rec)
    {
        BTM_TRACE_DEBUG1(" p_dev_rec->sec_flags=0x%x", p_dev_rec->sec_flags);

        if (encr_enable && p_dev_rec->enc_key_size == 0)
            p_dev_rec->enc_key_size = p_dev_rec->ble.keys.key_size;

        if (p_dev_rec->p_callback)
        {
            if (p_dev_rec->sec_state == BTM_SEC_STATE_ENCRYPTING)
            {
                if (encr_enable)
                    btm_sec_dev_rec_cback_event(p_dev_rec, BTM_SUCCESS);
                else if (p_dev_rec->role_master)
                    btm_sec_dev_rec_cback_event(p_dev_rec, BTM_ERR_PROCESSING);
            }
        }
        p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;
    }
}

/*******************************************************************************
** Function         btm_enc_proc_ltk
** Description      send LTK reply when it's ready.
*******************************************************************************/
static void btm_enc_proc_ltk(tSMP_ENC *p)
{
    UINT8   i;
    BTM_TRACE_DEBUG0 ("btm_enc_proc_ltk");
    if (p && p->param_len == BT_OCTET16_LEN)
    {
        for (i = 0; i < (BT_OCTET16_LEN - btm_cb.key_size); i ++)
            p->param_buf[BT_OCTET16_LEN - i - 1] = 0;
        btsnd_hcic_ble_ltk_req_reply(btm_cb.enc_handle, p->param_buf);
    }
}

/*******************************************************************************
** Function         btm_enc_proc_slave_y
** Description      calculate LTK when Y is ready
*******************************************************************************/
static void btm_enc_proc_slave_y(tSMP_ENC *p)
{
    UINT16  div, y;
    UINT8   *pp = p->param_buf;
    tBTM_CB *p_cb = &btm_cb;
    tSMP_ENC output;
    tBTM_SEC_DEV_REC *p_dev_rec;

    BTM_TRACE_DEBUG0 ("btm_enc_proc_slave_y");
    if (p != NULL)
    {
        STREAM_TO_UINT16(y, pp);

        div = p_cb->ediv ^ y;
        p_dev_rec = btm_find_dev_by_handle (p_cb->enc_handle);

        if ( p_dev_rec &&
            p_dev_rec->ble.keys.div == div )
        {
            BTM_TRACE_DEBUG0 ("LTK request OK");
            /* calculating LTK , LTK = E er(div) */
            SMP_Encrypt(p_cb->devcb.er, BT_OCTET16_LEN, (UINT8 *)&div, 2, &output);
            btm_enc_proc_ltk(&output);
        }
        else
        {
            BTM_TRACE_DEBUG0 ("LTK request failed - send negative reply");
            btsnd_hcic_ble_ltk_req_neg_reply(p_cb->enc_handle);
            if (p_dev_rec)
                btm_ble_link_encrypted(p_dev_rec->bd_addr, 0);

        }
    }
}

/*******************************************************************************
**
** Function         btm_ble_ltk_request_reply
**
** Description      This function is called to send a LTK request reply on a slave
**                  device.
**
** Returns          void
**
*******************************************************************************/
void btm_ble_ltk_request_reply(BD_ADDR bda,  BOOLEAN use_stk, BT_OCTET16 stk)
{
    tBTM_SEC_DEV_REC    *p_rec = btm_find_dev (bda);
    tBTM_CB *p_cb = &btm_cb;
    tSMP_ENC output;

    if (p_rec == NULL)
    {
        BTM_TRACE_ERROR0("btm_ble_ltk_request_reply received for unknown device");
        return;
    }

    BTM_TRACE_DEBUG0 ("btm_ble_ltk_request_reply");
    p_cb->enc_handle = p_rec->hci_handle;
    p_cb->key_size = p_rec->ble.keys.key_size;

    BTM_TRACE_ERROR1("key size = %d", p_rec->ble.keys.key_size);
    if (use_stk)
    {
        btsnd_hcic_ble_ltk_req_reply(btm_cb.enc_handle, stk);
    }
    else /* calculate LTK using peer device  */
    {
        /* generate Y= Encrypt(DHK, Rand) received from encrypt request  */
        SMP_Encrypt(p_cb->devcb.id_keys.dhk, BT_OCTET16_LEN, p_cb->enc_rand,
                    BT_OCTET8_LEN, &output);
        btm_enc_proc_slave_y(&output);
    }
}

/*******************************************************************************
**
** Function         btm_ble_io_capabilities_req
**
** Description      This function is called to handle SMP get IO capability request.
**
** Returns          void
**
*******************************************************************************/
UINT8 btm_ble_io_capabilities_req(tBTM_SEC_DEV_REC *p_dev_rec, tBTM_LE_IO_REQ *p_data)
{
    UINT8           callback_rc = BTM_SUCCESS;
    BTM_TRACE_DEBUG0 ("btm_ble_io_capabilities_req");
    if (btm_cb.api.p_le_callback)
    {
        /* the callback function implementation may change the IO capability... */
        callback_rc = (*btm_cb.api.p_le_callback) (BTM_LE_IO_REQ_EVT, p_dev_rec->bd_addr, (tBTM_LE_EVT_DATA *)p_data);
    }
#if BTM_OOB_INCLUDED == TRUE
    if ((callback_rc == BTM_SUCCESS) || (BTM_OOB_UNKNOWN != p_data->oob_data))
#else
    if (callback_rc == BTM_SUCCESS)
#endif
    {
        p_data->auth_req &= BTM_LE_AUTH_REQ_MASK;

        BTM_TRACE_DEBUG2 ("btm_ble_io_capabilities_req 1: p_dev_rec->security_required = %d auth_req:%d",
                          p_dev_rec->security_required, p_data->auth_req);
        BTM_TRACE_DEBUG2 ("btm_ble_io_capabilities_req 2: i_keys=0x%x r_keys=0x%x (bit 0-LTK 1-IRK 2-CSRK)",
                          p_data->init_keys,
                          p_data->resp_keys);

        /* if authentication requires MITM protection, put on the mask */
        if (p_dev_rec->security_required & BTM_SEC_IN_MITM)
            p_data->auth_req |= BTM_LE_AUTH_REQ_MITM;

        if (!(p_data->auth_req & SMP_AUTH_BOND))
        {
            BTM_TRACE_DEBUG0("Non bonding: No keys should be exchanged");
            p_data->init_keys = 0;
            p_data->resp_keys = 0;
        }

        BTM_TRACE_DEBUG1 ("btm_ble_io_capabilities_req 3: auth_req:%d", p_data->auth_req);
        BTM_TRACE_DEBUG2 ("btm_ble_io_capabilities_req 4: i_keys=0x%x r_keys=0x%x",
                          p_data->init_keys,
                          p_data->resp_keys);

        BTM_TRACE_DEBUG2 ("btm_ble_io_capabilities_req 5: p_data->io_cap = %d auth_req:%d",
                          p_data->io_cap, p_data->auth_req);

        /* remove MITM protection requirement if IO cap does not allow it */
        if ((p_data->io_cap == BTM_IO_CAP_NONE) && p_data->oob_data == SMP_OOB_NONE)
            p_data->auth_req &= ~BTM_LE_AUTH_REQ_MITM;

        BTM_TRACE_DEBUG3 ("btm_ble_io_capabilities_req 6: IO_CAP:%d oob_data:%d auth_req:%d",
                          p_data->io_cap, p_data->oob_data, p_data->auth_req);
    }
    return callback_rc;
}

/*****************************************************************************
**  Function        btm_proc_smp_cback
**
**  Description     This function is the SMP callback handler.
**
******************************************************************************/
UINT8 btm_proc_smp_cback(tSMP_EVT event, BD_ADDR bd_addr, tSMP_EVT_DATA *p_data)
{
    tBTM_SEC_DEV_REC    *p_dev_rec = btm_find_dev (bd_addr);
    UINT8 res;

    BTM_TRACE_DEBUG1 ("btm_proc_smp_cback event = %d", event);

    if (p_dev_rec != NULL)
    {
        switch (event)
        {
            case SMP_IO_CAP_REQ_EVT:
                btm_ble_io_capabilities_req(p_dev_rec, (tBTM_LE_IO_REQ *)&p_data->io_req);
                break;

            case SMP_PASSKEY_REQ_EVT:
            case SMP_PASSKEY_NOTIF_EVT:
            case SMP_OOB_REQ_EVT:
                p_dev_rec->sec_flags |= BTM_SEC_LINK_KEY_AUTHED;
            case SMP_SEC_REQUEST_EVT:
            case SMP_COMPLT_EVT:
                if (btm_cb.api.p_le_callback)
                {
                    /* the callback function implementation may change the IO capability... */
                    BTM_TRACE_DEBUG1 ("btm_cb.api.p_le_callback=0x%x", btm_cb.api.p_le_callback );
                    (*btm_cb.api.p_le_callback) (event, bd_addr, (tBTM_LE_EVT_DATA *)p_data);
                }
                else
                {
                    BTM_TRACE_ERROR0 ("btm_proc_smp_cback: btm_cb.api.p_le_callback ==NULL");
                }

                if (event == SMP_COMPLT_EVT)
                {
                    BTM_TRACE_DEBUG2 ("evt=SMP_COMPLT_EVT before update sec_level=0x%x sec_flags=0x%x", p_data->cmplt.sec_level , p_dev_rec->sec_flags );

                    res = (p_data->cmplt.reason == SMP_SUCCESS) ? BTM_SUCCESS : BTM_ERR_PROCESSING;

                    BTM_TRACE_DEBUG3 ("after update result=%d sec_level=0x%x sec_flags=0x%x",
                                      res, p_data->cmplt.sec_level , p_dev_rec->sec_flags );

                    btm_sec_dev_rec_cback_event(p_dev_rec, res);

                    if (p_data->cmplt.is_pair_cancel && btm_cb.api.p_bond_cancel_cmpl_callback )
                    {
                        BTM_TRACE_DEBUG0 ("Pairing Cancel completed");
                        (*btm_cb.api.p_bond_cancel_cmpl_callback)(BTM_SUCCESS);
                    }
#if BTM_BLE_CONFORMANCE_TESTING == TRUE
                    if (res != BTM_SUCCESS)
                    {
                        if (!btm_cb.devcb.no_disc_if_pair_fail)
                        {
                            BTM_TRACE_DEBUG0 ("Pairing failed - Remove ACL");
                            btm_remove_acl(bd_addr);
                        }
                        else
                        {
                            BTM_TRACE_DEBUG0 ("Pairing failed - Not Removing ACL");
	                        p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;
                        }
                    }
#else
                    if (res != BTM_SUCCESS)
                        btm_remove_acl(bd_addr);
#endif

                    BTM_TRACE_DEBUG3 ("btm_cb pairing_state=%x pairing_flags=%x pin_code_len=%x",
                                      btm_cb.pairing_state,
                                      btm_cb.pairing_flags,
                                      btm_cb.pin_code_len  );
                    BTM_TRACE_DEBUG6 ("btm_cb.pairing_bda %02x:%02x:%02x:%02x:%02x:%02x",
                                      btm_cb.pairing_bda[0], btm_cb.pairing_bda[1], btm_cb.pairing_bda[2],
                                      btm_cb.pairing_bda[3], btm_cb.pairing_bda[4], btm_cb.pairing_bda[5]);

                    memset (btm_cb.pairing_bda, 0xff, BD_ADDR_LEN);
                    btm_cb.pairing_flags = 0;
                }
                break;

            default:
                BTM_TRACE_DEBUG1 ("unknown event = %d", event);
                break;


        }
    }
    else
    {
        BTM_TRACE_ERROR0("btm_proc_smp_cback received for unknown device");
    }

    return 0;
}

#endif  /* SMP_INCLUDED */
#endif  /* BLE_INCLUDED */


/*******************************************************************************
**
** Function         BTM_BleDataSignature
**
** Description      This function is called to sign the data using AES128 CMAC
**                  algorith.
**
** Parameter        bd_addr: target device the data to be signed for.
**                  p_text: singing data
**                  len: length of the data to be signed.
**                  signature: output parameter where data signature is going to
**                             be stored.
**
** Returns          TRUE if signing sucessul, otherwise FALSE.
**
*******************************************************************************/
BOOLEAN BTM_BleDataSignature (BD_ADDR bd_addr, UINT8 *p_text, UINT16 len,
                              BLE_SIGNATURE signature)
{
    BOOLEAN     ret = FALSE;
#if (BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE)
    tBTM_SEC_DEV_REC    *p_rec = btm_find_dev (bd_addr);
    UINT8   *p_buf, *pp;

    BT_OCTET16  er;
    UINT16      div;
    UINT8       temp[4]; /* for (r || DIV)  r=1*/
    UINT16      r=1;
    UINT8       *p=temp, *p_mac = (UINT8 *)signature;
    tSMP_ENC    output;
    BT_OCTET16  local_csrk;

    BTM_TRACE_DEBUG0 ("BTM_BleDataSignature");
    if (p_rec == NULL)
    {
        BTM_TRACE_ERROR0("data signing can not be done from unknow device");
    }
    else
    {
        if ((p_buf = (UINT8 *)GKI_getbuf((UINT16)(len + 4))) != NULL)
        {
            BTM_TRACE_DEBUG0("Start to generate Local CSRK");
            /* prepare plain text */
            if (p_text)
            {
                memcpy(p_buf, p_text, len);
                pp = (p_buf + len);
            }

#if BTM_BLE_CONFORMANCE_TESTING == TRUE
            if ( btm_cb.devcb.enable_test_local_sign_cntr)
            {
                BTM_TRACE_DEBUG1 ("Use Test local counter value from script counter_val=%d", btm_cb.devcb.test_local_sign_cntr);
                UINT32_TO_STREAM(pp, btm_cb.devcb.test_local_sign_cntr);
            }
            else
            {
                UINT32_TO_STREAM(pp, p_rec->ble.keys.local_counter);
            }
#else
            UINT32_TO_STREAM(pp, p_rec->ble.keys.local_counter);
#endif
            /* compute local csrk */
            if (btm_get_local_div(bd_addr, &div))
            {
                BTM_TRACE_DEBUG1 ("compute_csrk div=%x", div);
                BTM_GetDeviceEncRoot(er);

                /* CSRK = d1(ER, DIV, 1) */
                UINT16_TO_STREAM(p, div);
                UINT16_TO_STREAM(p, r);

                if (!SMP_Encrypt(er, BT_OCTET16_LEN, temp, 4, &output))
                {
                    BTM_TRACE_ERROR0("Local CSRK generation failed ");
                }
                else
                {
                    BTM_TRACE_DEBUG0("local CSRK generation success");
                    memcpy((void *)local_csrk, output.param_buf, BT_OCTET16_LEN);


#if BTM_BLE_CONFORMANCE_TESTING == TRUE
                    if (btm_cb.devcb.enable_test_local_sign_cntr)
                    {
                        UINT32_TO_STREAM(p_mac, btm_cb.devcb.test_local_sign_cntr);
                    }
                    else
                    {
                        UINT32_TO_STREAM(p_mac, p_rec->ble.keys.local_counter);
                    }
#else
                    UINT32_TO_STREAM(p_mac, p_rec->ble.keys.local_counter);
#endif

                    if ((ret = AES_CMAC(local_csrk, p_buf, (UINT16)(len + 4), BTM_CMAC_TLEN_SIZE, p_mac)) == TRUE)
                    {
                        btm_ble_increment_sign_ctr(bd_addr, TRUE);

#if BTM_BLE_CONFORMANCE_TESTING == TRUE
                        if ( btm_cb.devcb.enable_test_mac_val)
                        {
                            BTM_TRACE_DEBUG0 ("Use MAC value from script");
                            memcpy(p_mac, btm_cb.devcb.test_mac, BTM_CMAC_TLEN_SIZE);
                        }
#endif
                    }
                    BTM_TRACE_DEBUG1("BTM_BleDataSignature p_mac = %d", p_mac);
                    BTM_TRACE_DEBUG4("p_mac[0] = 0x%02x p_mac[1] = 0x%02x p_mac[2] = 0x%02x p_mac[3] = 0x%02x",
                                     *p_mac, *(p_mac + 1), *(p_mac + 2), *(p_mac + 3));
                    BTM_TRACE_DEBUG4("p_mac[4] = 0x%02x p_mac[5] = 0x%02x p_mac[6] = 0x%02x p_mac[7] = 0x%02x",
                                     *(p_mac + 4), *(p_mac + 5), *(p_mac + 6), *(p_mac + 7));

                    GKI_freebuf(p_buf);
                }
            }
        }
    }
#endif  /* BLE_INCLUDED */
    return ret;
}

/*******************************************************************************
**
** Function         BTM_BleVerifySignature
**
** Description      This function is called to verify the data signature
**
** Parameter        bd_addr: target device the data to be signed for.
**                  p_orig:  original data before signature.
**                  len: length of the signing data
**                  counter: counter used when doing data signing
**                  p_comp: signature to be compared against.

** Returns          TRUE if signature verified correctly; otherwise FALSE.
**
*******************************************************************************/
BOOLEAN BTM_BleVerifySignature (BD_ADDR bd_addr, UINT8 *p_orig, UINT16 len, UINT32 counter,
                             UINT8 *p_comp)
{
    BOOLEAN             verified = FALSE;
#if (BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE)
    tBTM_SEC_DEV_REC    *p_rec = btm_find_dev (bd_addr);
    UINT8               p_mac[BTM_CMAC_TLEN_SIZE];

    if (p_rec == NULL || (p_rec && !(p_rec->ble.key_type & BTM_LE_KEY_PCSRK)))
    {
        BTM_TRACE_ERROR0("can not verify signature for unknown device");
    }
    else if (counter < p_rec->ble.keys.counter)
    {
        BTM_TRACE_ERROR0("signature received with out dated sign counter");
    }
    else if (p_orig == NULL)
    {
        BTM_TRACE_ERROR0("No signature to verify");
    }
    else
    {
        BTM_TRACE_DEBUG2 ("BTM_BleVerifySignature rcv_cnt=%d >= expected_cnt=%d", counter, p_rec->ble.keys.counter);

        if (AES_CMAC(p_rec->ble.keys.csrk, p_orig, len, BTM_CMAC_TLEN_SIZE, p_mac))
        {
            if (memcmp(p_mac, p_comp, BTM_CMAC_TLEN_SIZE) == 0)
            {
                btm_ble_increment_sign_ctr(bd_addr, FALSE);
                verified = TRUE;
            }
        }
    }
#endif  /* BLE_INCLUDED */
    return verified;
}

#if BLE_INCLUDED == TRUE
/*******************************************************************************
**  Utility functions for LE device IR/ER generation
*******************************************************************************/
/*******************************************************************************
**
** Function         btm_notify_new_key
**
** Description      This function is to notify application new keys have been
**                  generated.
**
** Returns          void
**
*******************************************************************************/
static void btm_notify_new_key(UINT8 key_type)
{
    tBTM_BLE_LOCAL_KEYS *p_locak_keys = NULL;

    BTM_TRACE_DEBUG1 ("btm_notify_new_key key_type=%d", key_type);

    if (btm_cb.api.p_le_key_callback)
    {
        switch (key_type)
        {
            case BTM_BLE_KEY_TYPE_ID:
                BTM_TRACE_DEBUG0 ("BTM_BLE_KEY_TYPE_ID");
                p_locak_keys = (tBTM_BLE_LOCAL_KEYS *)&btm_cb.devcb.id_keys;
                break;

            case BTM_BLE_KEY_TYPE_ER:
                BTM_TRACE_DEBUG0 ("BTM_BLE_KEY_TYPE_ER");
                p_locak_keys = (tBTM_BLE_LOCAL_KEYS *)&btm_cb.devcb.er;
                break;

            default:
                BTM_TRACE_ERROR1("unknown key type: %d", key_type);
                break;
        }
        if (p_locak_keys != NULL)
            (*btm_cb.api.p_le_key_callback) (key_type, p_locak_keys);
    }
}

/*******************************************************************************
**
** Function         btm_ble_process_er2
**
** Description      This function is called when ER is generated, store it in
**                  local control block.
**
** Returns          void
**
*******************************************************************************/
static void btm_ble_process_er2(tBTM_RAND_ENC *p)
{
    BTM_TRACE_DEBUG0 ("btm_ble_process_er2");

    if (p &&p->opcode == HCI_BLE_RAND)
    {
        memcpy(&btm_cb.devcb.er[8], p->param_buf, BT_OCTET8_LEN);
        btm_notify_new_key(BTM_BLE_KEY_TYPE_ER);
    }
    else
    {
        BTM_TRACE_ERROR0("Generating ER2 exception.");
        memset(&btm_cb.devcb.er, 0, sizeof(BT_OCTET16));
    }
}

/*******************************************************************************
**
** Function         btm_ble_process_er
**
** Description      This function is called when ER is generated, store it in
**                  local control block.
**
** Returns          void
**
*******************************************************************************/
static void btm_ble_process_er(tBTM_RAND_ENC *p)
{
    BTM_TRACE_DEBUG0 ("btm_ble_process_er");

    if (p &&p->opcode == HCI_BLE_RAND)
    {
        memcpy(&btm_cb.devcb.er[0], p->param_buf, BT_OCTET8_LEN);

        if (!btsnd_hcic_ble_rand((void *)btm_ble_process_er2))
        {
            memset(&btm_cb.devcb.er, 0, sizeof(BT_OCTET16));
            BTM_TRACE_ERROR0("Generating ER2 failed.");
        }
    }
    else
    {
        BTM_TRACE_ERROR0("Generating ER1 exception.");
    }
}

/*******************************************************************************
**
** Function         btm_ble_process_irk
**
** Description      This function is called when IRK is generated, store it in
**                  local control block.
**
** Returns          void
**
*******************************************************************************/
static void btm_ble_process_irk(tSMP_ENC *p)
{
    BTM_TRACE_DEBUG0 ("btm_ble_process_irk");
    if (p &&p->opcode == HCI_BLE_ENCRYPT)
    {
        memcpy(btm_cb.devcb.id_keys.irk, p->param_buf, BT_OCTET16_LEN);
        btm_notify_new_key(BTM_BLE_KEY_TYPE_ID);
    }
    else
    {
        BTM_TRACE_ERROR0("Generating IRK exception.");
    }

    /* proceed generate ER */
    if (!btsnd_hcic_ble_rand((void *)btm_ble_process_er))
    {
        BTM_TRACE_ERROR0("Generating ER failed.");
    }
}

/*******************************************************************************
**
** Function         btm_ble_process_dhk
**
** Description      This function is called when DHK is calculated, store it in
**                  local control block, and proceed to generate ER, a 128-bits
**                  random number.
**
** Returns          void
**
*******************************************************************************/
static void btm_ble_process_dhk(tSMP_ENC *p)
{
#if SMP_INCLUDED == TRUE
    UINT8 btm_ble_irk_pt = 0x01;
    tSMP_ENC output;

    BTM_TRACE_DEBUG0 ("btm_ble_process_dhk");

    if (p && p->opcode == HCI_BLE_ENCRYPT)
    {
        memcpy(btm_cb.devcb.id_keys.dhk, p->param_buf, BT_OCTET16_LEN);
        BTM_TRACE_DEBUG0("BLE DHK generated.");

        /* IRK = D1(IR, 1) */
        if (!SMP_Encrypt(btm_cb.devcb.id_keys.ir, BT_OCTET16_LEN, &btm_ble_irk_pt,
                         1,   &output))
        {
            /* reset all identity root related key */
            memset(&btm_cb.devcb.id_keys, 0, sizeof(tBTM_BLE_LOCAL_ID_KEYS));
        }
        else
        {
            btm_ble_process_irk(&output);
        }
    }
    else
    {
        /* reset all identity root related key */
        memset(&btm_cb.devcb.id_keys, 0, sizeof(tBTM_BLE_LOCAL_ID_KEYS));
    }
#endif
}

/*******************************************************************************
**
** Function         btm_ble_process_ir2
**
** Description      This function is called when IR is generated, proceed to calculate
**                  DHK = Eir({0x03, 0, 0 ...})
**
**
** Returns          void
**
*******************************************************************************/
static void btm_ble_process_ir2(tBTM_RAND_ENC *p)
{
#if SMP_INCLUDED == TRUE
    UINT8 btm_ble_dhk_pt = 0x03;
    tSMP_ENC output;

    BTM_TRACE_DEBUG0 ("btm_ble_process_ir2");

    if (p && p->opcode == HCI_BLE_RAND)
    {
        /* remembering in control block */
        memcpy(&btm_cb.devcb.id_keys.ir[8], p->param_buf, BT_OCTET8_LEN);
        /* generate DHK= Eir({0x03, 0x00, 0x00 ...}) */


        SMP_Encrypt(btm_cb.devcb.id_keys.ir, BT_OCTET16_LEN, &btm_ble_dhk_pt,
                    1, &output);
        btm_ble_process_dhk(&output);

        BTM_TRACE_DEBUG0("BLE IR generated.");
    }
    else
    {
        memset(&btm_cb.devcb.id_keys, 0, sizeof(tBTM_BLE_LOCAL_ID_KEYS));
    }
#endif
}

/*******************************************************************************
**
** Function         btm_ble_process_ir
**
** Description      This function is called when IR is generated, proceed to calculate
**                  DHK = Eir({0x02, 0, 0 ...})
**
**
** Returns          void
**
*******************************************************************************/
static void btm_ble_process_ir(tBTM_RAND_ENC *p)
{
    BTM_TRACE_DEBUG0 ("btm_ble_process_ir");

    if (p && p->opcode == HCI_BLE_RAND)
    {
        /* remembering in control block */
        memcpy(btm_cb.devcb.id_keys.ir, p->param_buf, BT_OCTET8_LEN);

        if (!btsnd_hcic_ble_rand((void *)btm_ble_process_ir2))
        {
            BTM_TRACE_ERROR0("Generating IR2 failed.");
            memset(&btm_cb.devcb.id_keys, 0, sizeof(tBTM_BLE_LOCAL_ID_KEYS));
        }
    }
}

/*******************************************************************************
**
** Function         btm_ble_reset_id
**
** Description      This function is called to reset LE device identity.
**
** Returns          void
**
*******************************************************************************/
void btm_ble_reset_id( void )
{
    BTM_TRACE_DEBUG0 ("btm_ble_reset_id");

    /* regenrate Identity Root*/
    if (!btsnd_hcic_ble_rand((void *)btm_ble_process_ir))
    {
        BTM_TRACE_DEBUG0("Generating IR failed.");
    }
}

#if BTM_BLE_CONFORMANCE_TESTING == TRUE
/*******************************************************************************
**
** Function         btm_ble_set_no_disc_if_pair_fail
**
** Description      This function indicates that whether no disconnect of the ACL
**                  should be used if pairing failed
**
** Returns          void
**
*******************************************************************************/
void btm_ble_set_no_disc_if_pair_fail(BOOLEAN disable_disc )
{
    BTM_TRACE_DEBUG1 ("btm_ble_set_disc_enable_if_pair_fail disable_disc=%d", disable_disc);
    btm_cb.devcb.no_disc_if_pair_fail = disable_disc;
}

/*******************************************************************************
**
** Function         btm_ble_set_test_mac_value
**
** Description      This function set test MAC value
**
** Returns          void
**
*******************************************************************************/
void btm_ble_set_test_mac_value(BOOLEAN enable, UINT8 *p_test_mac_val )
{
    BTM_TRACE_DEBUG1 ("btm_ble_set_test_mac_value enable=%d", enable);
    btm_cb.devcb.enable_test_mac_val = enable;
    memcpy(btm_cb.devcb.test_mac, p_test_mac_val, BT_OCTET8_LEN);
}

/*******************************************************************************
**
** Function         btm_ble_set_test_local_sign_cntr_value
**
** Description      This function set test local sign counter value
**
** Returns          void
**
*******************************************************************************/
void btm_ble_set_test_local_sign_cntr_value(BOOLEAN enable, UINT32 test_local_sign_cntr )
{
    BTM_TRACE_DEBUG2 ("btm_ble_set_test_local_sign_cntr_value enable=%d local_sign_cntr=%d",
                      enable, test_local_sign_cntr);
    btm_cb.devcb.enable_test_local_sign_cntr = enable;
    btm_cb.devcb.test_local_sign_cntr =  test_local_sign_cntr;
}

#endif /* BTM_BLE_CONFORMANCE_TESTING */


#endif /* BLE_INCLUDED */
