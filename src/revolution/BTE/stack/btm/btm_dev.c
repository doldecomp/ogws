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
 *  This file contains functions for the Bluetooth Device Manager
 *
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>

#include "bt_types.h"
#include "gki.h"
#include "hcimsgs.h"
#include "btu.h"
#include "btm_api.h"
#include "btm_int.h"
#include "hcidefs.h"
#include "l2c_api.h"
static tBTM_SEC_DEV_REC *btm_find_oldest_dev (void);

/*******************************************************************************
**
** Function         BTM_SecAddDevice
**
** Description      Add/modify device.  This function will be normally called
**                  during host startup to restore all required information
**                  stored in the NVRAM.
**
** Parameters:      bd_addr          - BD address of the peer
**                  dev_class        - Device Class
**                  bd_name          - Name of the peer device.  NULL if unknown.
**                  features         - Remote device's supported features. NULL if not known
**                  trusted_mask     - Bitwise OR of services that do not
**                                     require authorization. (array of UINT32)
**                  link_key         - Connection link key. NULL if unknown.
**
** Returns          TRUE if added OK, else FALSE
**
*******************************************************************************/
BOOLEAN BTM_SecAddDevice (BD_ADDR bd_addr, DEV_CLASS dev_class, BD_NAME bd_name,
                          BD_FEATURES features, UINT32 trusted_mask[],
                          LINK_KEY link_key, UINT8 key_type, tBTM_IO_CAP io_cap)
{
    tBTM_SEC_DEV_REC  *p_dev_rec;
    int               i;

    p_dev_rec = btm_find_dev (bd_addr);
    if (!p_dev_rec)
    {
        /* There is no device record, allocate one.
         * If we can not find an empty spot for this one, let it fail. */
        for (i = 0; i < BTM_SEC_MAX_DEVICE_RECORDS; i++)
        {
            if (!(btm_cb.sec_dev_rec[i].sec_flags & BTM_SEC_IN_USE))
            {
                p_dev_rec = &btm_cb.sec_dev_rec[i];

                /* Mark this record as in use and initialize */
                memset (p_dev_rec, 0, sizeof (tBTM_SEC_DEV_REC));
                p_dev_rec->sec_flags = BTM_SEC_IN_USE;
                memcpy (p_dev_rec->bd_addr, bd_addr, BD_ADDR_LEN);
                p_dev_rec->hci_handle = BTM_GetHCIConnHandle (bd_addr);

#if BLE_INCLUDED == TRUE
                /* use default value for background connection params */
                /* update conn params, use default value for background connection params */
                memset(&p_dev_rec->conn_params, 0xff, sizeof(tBTM_LE_CONN_PRAMS));
#endif
                break;
            }
        }

        if (!p_dev_rec)
            return(FALSE);
    }

    p_dev_rec->timestamp = btm_cb.dev_rec_count++;

    if (dev_class)
        memcpy (p_dev_rec->dev_class, dev_class, DEV_CLASS_LEN);

    memset(p_dev_rec->sec_bd_name, 0, sizeof(tBTM_BD_NAME));

    if (bd_name && bd_name[0])
    {
        p_dev_rec->sec_flags |= BTM_SEC_NAME_KNOWN;
        BCM_STRNCPY_S ((char *)p_dev_rec->sec_bd_name, sizeof (p_dev_rec->sec_bd_name),
            (char *)bd_name, BTM_MAX_REM_BD_NAME_LEN);
    }

    if (features)
        memcpy (p_dev_rec->features, features, sizeof (BD_FEATURES));
    else
        memset (p_dev_rec->features, 0, sizeof (BD_FEATURES));

    BTM_SEC_COPY_TRUSTED_DEVICE(trusted_mask, p_dev_rec->trusted_mask);

    if (link_key)
    {
        BTM_TRACE_EVENT6 ("BTM_SecAddDevice()  BDA: %02x:%02x:%02x:%02x:%02x:%02x",
                          bd_addr[0], bd_addr[1], bd_addr[2],
                          bd_addr[3], bd_addr[4], bd_addr[5]);
        p_dev_rec->sec_flags |= BTM_SEC_LINK_KEY_KNOWN;
        memcpy (p_dev_rec->link_key, link_key, LINK_KEY_LEN);
        p_dev_rec->link_key_type = key_type;
    }

#if defined(BTIF_MIXED_MODE_INCLUDED) && (BTIF_MIXED_MODE_INCLUDED == TRUE)
    p_dev_rec->sm4 = BTM_SM4_KNOWN;
#endif

    p_dev_rec->rmt_io_caps = io_cap;

    return(TRUE);
}


/*******************************************************************************
**
** Function         BTM_SecDeleteDevice
**
** Description      Free resources associated with the device.
**
** Parameters:      bd_addr          - BD address of the peer
**
** Returns          TRUE if removed OK, FALSE if not found or ACL link is active
**
*******************************************************************************/
BOOLEAN BTM_SecDeleteDevice (BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC  *p_dev_rec;

    if (BTM_IsAclConnectionUp(bd_addr))
    {
        BTM_TRACE_WARNING0("BTM_SecDeleteDevice FAILED: Cannot Delete when connection is active");
        return(FALSE);
    }

    if ((p_dev_rec = btm_find_dev (bd_addr)) == NULL)
        return(FALSE);

    btm_sec_free_dev (p_dev_rec);

    /* Tell controller to get rid of the link key if it has one stored */
    BTM_DeleteStoredLinkKey (bd_addr, NULL);

    return(TRUE);
}

/*******************************************************************************
**
** Function         BTM_SecReadDevName
**
** Description      Looks for the device name in the security database for the
**                  specified BD address.
**
** Returns          Pointer to the name or NULL
**
*******************************************************************************/
char *BTM_SecReadDevName (BD_ADDR bd_addr)
{
    char *p_name = NULL;
    tBTM_SEC_DEV_REC *p_srec;

    if ((p_srec = btm_find_dev(bd_addr)) != NULL)
        p_name = (char *)p_srec->sec_bd_name;

    return(p_name);
}

/*******************************************************************************
**
** Function         btm_sec_alloc_dev
**
** Description      Look for the record in the device database for the record
**                  with specified handle
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
tBTM_SEC_DEV_REC *btm_sec_alloc_dev (BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_dev_rec = NULL;
    tBTM_INQ_INFO    *p_inq_info;
    int               i;
    BTM_TRACE_EVENT0 ("btm_sec_alloc_dev");
    for (i = 0; i < BTM_SEC_MAX_DEVICE_RECORDS; i++)
    {
        if (!(btm_cb.sec_dev_rec[i].sec_flags & BTM_SEC_IN_USE))
        {
            p_dev_rec = &btm_cb.sec_dev_rec[i];
            break;
        }
    }

    if (!p_dev_rec)
        p_dev_rec = btm_find_oldest_dev();

    memset (p_dev_rec, 0, sizeof (tBTM_SEC_DEV_REC));

    p_dev_rec->sec_flags = BTM_SEC_IN_USE;

    /* Check with the BT manager if details about remote device are known */
    /* outgoing connection */
    if ((p_inq_info = BTM_InqDbRead(bd_addr)) != NULL)
    {
        memcpy (p_dev_rec->dev_class, p_inq_info->results.dev_class, DEV_CLASS_LEN);

#if BLE_INCLUDED == TRUE
        p_dev_rec->device_type = p_inq_info->results.device_type;
        p_dev_rec->ble.ble_addr_type = p_inq_info->results.ble_addr_type;

        /* update conn params, use default value for background connection params */
        memset(&p_dev_rec->conn_params, 0xff, sizeof(tBTM_LE_CONN_PRAMS));
#endif

#if BTM_INQ_GET_REMOTE_NAME == TRUE
        if (p_inq_info->remote_name_state == BTM_INQ_RMT_NAME_DONE)
        {
            BCM_STRNCPY_S ((char *)p_dev_rec->sec_bd_name, sizeof (p_dev_rec->sec_bd_name),
                     (char *)p_inq_info->remote_name, BTM_MAX_REM_BD_NAME_LEN);
            p_dev_rec->sec_flags |= BTM_SEC_NAME_KNOWN;
        }
#endif
    }
    else
    {
#if BLE_INCLUDED == TRUE
        p_dev_rec->device_type = BT_DEVICE_TYPE_BREDR;  /* initialize it as BR/EDR device */
        /* update conn params, use default value for background connection params */
        memset(&p_dev_rec->conn_params, 0xff, sizeof(tBTM_LE_CONN_PRAMS));
#endif

        if (!memcmp (bd_addr, btm_cb.connecting_bda, BD_ADDR_LEN))
            memcpy (p_dev_rec->dev_class, btm_cb.connecting_dc, DEV_CLASS_LEN);
    }

    memcpy (p_dev_rec->bd_addr, bd_addr, BD_ADDR_LEN);

    p_dev_rec->hci_handle = BTM_GetHCIConnHandle (bd_addr);
    p_dev_rec->timestamp = btm_cb.dev_rec_count++;

    return(p_dev_rec);
}


/*******************************************************************************
**
** Function         btm_sec_free_dev
**
** Description      Mark device record as not used
**
*******************************************************************************/
void btm_sec_free_dev (tBTM_SEC_DEV_REC *p_dev_rec)
{
    p_dev_rec->sec_flags = 0;

#if BLE_INCLUDED == TRUE
    /* Clear out any saved BLE keys */
    btm_sec_clear_ble_keys (p_dev_rec);
#endif


}

/*******************************************************************************
**
** Function         btm_dev_support_switch
**
** Description      This function is called by the L2CAP to check if remote
**                  device supports role switch
**
** Parameters:      bd_addr       - Address of the peer device
**
** Returns          TRUE if device is known and role switch is supported
**
*******************************************************************************/
BOOLEAN btm_dev_support_switch (BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC  *p_dev_rec;
    UINT8   xx;
    BOOLEAN feature_empty = TRUE;

#if BTM_SCO_INCLUDED == TRUE
    /* Role switch is not allowed if a SCO is up */
    if (btm_is_sco_active_by_bdaddr(bd_addr))
        return(FALSE);
#endif
    p_dev_rec = btm_find_dev (bd_addr);
    if (p_dev_rec && HCI_SWITCH_SUPPORTED(btm_cb.devcb.local_features))
    {
        if (HCI_SWITCH_SUPPORTED(p_dev_rec->features))
        {
            BTM_TRACE_DEBUG0("btm_dev_support_switch return TRUE (feature found)");
            return (TRUE);
        }

        /* If the feature field is all zero, we never received them */
        for (xx = 0 ; xx < BD_FEATURES_LEN ; xx++)
        {
            if (p_dev_rec->features[xx] != 0x00)
            {
                feature_empty = FALSE; /* at least one is != 0 */
                break;
            }
        }

        /* If we don't know peer's capabilities, assume it supports Role-switch */
        if (feature_empty)
        {
            BTM_TRACE_DEBUG0("btm_dev_support_switch return TRUE (feature empty)");
            return (TRUE);
        }
    }

    BTM_TRACE_DEBUG0("btm_dev_support_switch return FALSE");
    return(FALSE);
}

/*******************************************************************************
**
** Function         btm_find_dev_by_handle
**
** Description      Look for the record in the device database for the record
**                  with specified handle
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
tBTM_SEC_DEV_REC *btm_find_dev_by_handle (UINT16 handle)
{
    tBTM_SEC_DEV_REC *p_dev_rec = &btm_cb.sec_dev_rec[0];
    int i;

    for (i = 0; i < BTM_SEC_MAX_DEVICE_RECORDS; i++, p_dev_rec++)
    {
        if ((p_dev_rec->sec_flags & BTM_SEC_IN_USE)
            && (p_dev_rec->hci_handle == handle))
            return(p_dev_rec);
    }
    return(NULL);
}

/*******************************************************************************
**
** Function         btm_find_dev
**
** Description      Look for the record in the device database for the record
**                  with specified BD address
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
tBTM_SEC_DEV_REC *btm_find_dev (BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_dev_rec = &btm_cb.sec_dev_rec[0];
    int i;

    if (bd_addr)
    {
        for (i = 0; i < BTM_SEC_MAX_DEVICE_RECORDS; i++, p_dev_rec++)
        {
            if ((p_dev_rec->sec_flags & BTM_SEC_IN_USE)
                && (!memcmp (p_dev_rec->bd_addr, bd_addr, BD_ADDR_LEN)))
                return(p_dev_rec);
        }
    }
    return(NULL);
}

/*******************************************************************************
**
** Function         btm_find_or_alloc_dev
**
** Description      Look for the record in the device database for the record
**                  with specified BD address
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
tBTM_SEC_DEV_REC *btm_find_or_alloc_dev (BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    BTM_TRACE_EVENT0 ("btm_find_or_alloc_dev");
    if ((p_dev_rec = btm_find_dev (bd_addr)) == NULL)
    {

        /* Allocate a new device record or reuse the oldest one */
        p_dev_rec = btm_sec_alloc_dev (bd_addr);
    }
    return(p_dev_rec);
}

/*******************************************************************************
**
** Function         btm_find_oldest_dev
**
** Description      Locates the oldest device in use. It first looks for
**                  the oldest non-paired device.  If all devices are paired it
**                  deletes the oldest paired device.
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
tBTM_SEC_DEV_REC *btm_find_oldest_dev (void)
{
    tBTM_SEC_DEV_REC *p_dev_rec = &btm_cb.sec_dev_rec[0];
    tBTM_SEC_DEV_REC *p_oldest = p_dev_rec;
    UINT32       ot = 0xFFFFFFFF;
    int i;

    /* First look for the non-paired devices for the oldest entry */
    for (i = 0; i < BTM_SEC_MAX_DEVICE_RECORDS; i++, p_dev_rec++)
    {
        if (((p_dev_rec->sec_flags & BTM_SEC_IN_USE) == 0)
            || ((p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN) != 0))
            continue; /* Device is paired so skip it */

        if (p_dev_rec->timestamp < ot)
        {
            p_oldest = p_dev_rec;
            ot       = p_dev_rec->timestamp;
        }
    }

    if (ot != 0xFFFFFFFF)
        return(p_oldest);

    /* All devices are paired; find the oldest */
    p_dev_rec = &btm_cb.sec_dev_rec[0];
    for (i = 0; i < BTM_SEC_MAX_DEVICE_RECORDS; i++, p_dev_rec++)
    {
        if ((p_dev_rec->sec_flags & BTM_SEC_IN_USE) == 0)
            continue;

        if (p_dev_rec->timestamp < ot)
        {
            p_oldest = p_dev_rec;
            ot       = p_dev_rec->timestamp;
        }
    }
    return(p_oldest);
}


