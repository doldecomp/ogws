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
 *  This file contains functions for the Bluetooth Security Manager
 *
 ******************************************************************************/

#include <string.h>
#include "bt_types.h"
#include "hcimsgs.h"
#include "btu.h"
#include "btm_int.h"
#include "l2c_int.h"

#if (BT_USE_TRACES == TRUE && BT_TRACE_VERBOSE == FALSE)
/* needed for sprintf() */
#include <stdio.h>
#endif

#if BLE_INCLUDED == TRUE
    #include "gatt_int.h"
#endif

#define BTM_SEC_MAX_COLLISION_DELAY     (GKI_SECS_TO_TICKS(5))

#ifdef APPL_AUTH_WRITE_EXCEPTION
BOOLEAN (APPL_AUTH_WRITE_EXCEPTION)(BD_ADDR bd_addr);
#endif

/********************************************************************************/
/*              L O C A L    F U N C T I O N     P R O T O T Y P E S            */
/********************************************************************************/
static tBTM_SEC_SERV_REC *btm_sec_find_first_serv (BOOLEAN is_originator, UINT16 psm);
static tBTM_SEC_SERV_REC *btm_sec_find_next_serv (tBTM_SEC_SERV_REC *p_cur);
static tBTM_SEC_SERV_REC *btm_sec_find_mx_serv (UINT8 is_originator, UINT16 psm,
                                                UINT32 mx_proto_id,
                                                UINT32 mx_chan_id);

static tBTM_STATUS btm_sec_execute_procedure (tBTM_SEC_DEV_REC *p_dev_rec);
static BOOLEAN  btm_sec_start_get_name (tBTM_SEC_DEV_REC *p_dev_rec);
static BOOLEAN  btm_sec_start_authentication (tBTM_SEC_DEV_REC *p_dev_rec);
static BOOLEAN  btm_sec_start_encryption (tBTM_SEC_DEV_REC *p_dev_rec);
static void     btm_sec_collision_timeout (TIMER_LIST_ENT *p_tle);
static void     btm_restore_mode(void);
static void     btm_sec_pairing_timeout (TIMER_LIST_ENT *p_tle);
static tBTM_STATUS btm_sec_dd_create_conn (tBTM_SEC_DEV_REC *p_dev_rec);
static void     btm_sec_change_pairing_state (tBTM_PAIRING_STATE new_state);

#if (BT_USE_TRACES == TRUE)
static char     *btm_pair_state_descr (tBTM_PAIRING_STATE state);
#endif

static void     btm_sec_check_pending_reqs(void);
static BOOLEAN  btm_sec_queue_mx_request (BD_ADDR bd_addr,  UINT16 psm,  BOOLEAN is_orig,
                                          UINT32 mx_proto_id, UINT32 mx_chan_id,
                                          tBTM_SEC_CALLBACK *p_callback, void *p_ref_data);
static void     btm_sec_bond_cancel_complete (void);
static void     btm_send_link_key_notif (tBTM_SEC_DEV_REC *p_dev_rec);
static BOOLEAN  btm_sec_check_prefetch_pin (tBTM_SEC_DEV_REC  *p_dev_rec);

static UINT8    btm_sec_start_authorization (tBTM_SEC_DEV_REC *p_dev_rec);
BOOLEAN         btm_sec_are_all_trusted(UINT32 p_mask[]);

static tBTM_STATUS btm_sec_send_hci_disconnect (tBTM_SEC_DEV_REC *p_dev_rec, UINT8 reason);
tBTM_SEC_DEV_REC *btm_sec_find_dev_by_sec_state (UINT8 state);

static BOOLEAN  btm_sec_set_security_level ( CONNECTION_TYPE conn_type, char *p_name, UINT8 service_id,
                                            UINT16 sec_level, UINT16 psm, UINT32 mx_proto_id,
                                            UINT32 mx_chan_id);

/* TRUE - authenticated link key is possible */
static const BOOLEAN btm_sec_io_map [BTM_IO_CAP_MAX][BTM_IO_CAP_MAX] =
{
    /*   OUT,    IO,     IN,     NONE */
/* OUT  */ {FALSE,  FALSE,  TRUE,   FALSE},
/* IO   */ {FALSE,  TRUE,   TRUE,   FALSE},
/* IN   */ {TRUE,   TRUE,   TRUE,   FALSE},
/* NONE */ {FALSE,  FALSE,  FALSE,  FALSE}
};
/*  BTM_IO_CAP_OUT      0   DisplayOnly */
/*  BTM_IO_CAP_IO       1   DisplayYesNo */
/*  BTM_IO_CAP_IN       2   KeyboardOnly */
/*  BTM_IO_CAP_NONE     3   NoInputNoOutput */

/*******************************************************************************
**
** Function         BTM_SecRegister
**
** Description      Application manager calls this function to register for
**                  security services.  There can be one and only one application
**                  saving link keys.  BTM allows only first registration.
**
** Returns          TRUE if registered OK, else FALSE
**
*******************************************************************************/
BOOLEAN  BTM_SecRegister (tBTM_APPL_INFO *p_cb_info)
{
#if BLE_INCLUDED == TRUE
    BT_OCTET16      temp_value = {0};
#endif

    BTM_TRACE_EVENT0 ("BTM_Sec: application registered");

#if BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE
    BTM_TRACE_ERROR1 ("BTM_SecRegister:p_cb_info->p_le_callback == 0x%x ", p_cb_info->p_le_callback);

    if (p_cb_info->p_le_callback)
    {
#if SMP_INCLUDED == TRUE
        BTM_TRACE_EVENT0 ("BTM_Sec: SMP_Register( btm_proc_smp_cback )");
        SMP_Register(btm_proc_smp_cback);
#endif
        /* if no IR is loaded, need to regenerate all the keys */
        if (memcmp(btm_cb.devcb.id_keys.ir, &temp_value, sizeof(BT_OCTET16)) == 0)
        {
            btm_ble_reset_id();
        }
    }
    else
    {
        BTM_TRACE_ERROR0 ("BTM_SecRegister:p_cb_info->p_le_callback == NULL ");
    }
#endif



    btm_cb.api = *p_cb_info;
#if BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE
     BTM_TRACE_ERROR1 ("BTM_SecRegister: btm_cb.api.p_le_callback = 0x%x ", btm_cb.api.p_le_callback);
#endif
    BTM_TRACE_EVENT0 ("BTM_Sec: application registered");
    return(TRUE);
}


/*******************************************************************************
**
** Function         BTM_SecRegisterLinkKeyNotificationCallback
**
** Description      Application manager calls this function to register for
**                  link key notification.  When there is nobody registered
**                  we should avoid changing link key
**
** Returns          TRUE if registered OK, else FALSE
**
*******************************************************************************/
BOOLEAN BTM_SecRegisterLinkKeyNotificationCallback (tBTM_LINK_KEY_CALLBACK *p_callback)
{
    btm_cb.api.p_link_key_callback = p_callback;
    return(TRUE);
}


/*******************************************************************************
**
** Function         BTM_SecAddRmtNameNotifyCallback
**
** Description      Any profile can register to be notified when name of the
**                  remote device is resolved.
**
** Returns          TRUE if registered OK, else FALSE
**
*******************************************************************************/
BOOLEAN  BTM_SecAddRmtNameNotifyCallback (tBTM_RMT_NAME_CALLBACK *p_callback)
{
    int i;

    for (i = 0; i < BTM_SEC_MAX_RMT_NAME_CALLBACKS; i++)
    {
        if (btm_cb.p_rmt_name_callback[i] == NULL)
        {
            btm_cb.p_rmt_name_callback[i] = p_callback;
            return(TRUE);
        }
    }

    return(FALSE);
}


/*******************************************************************************
**
** Function         BTM_SecDeleteRmtNameNotifyCallback
**
** Description      Any profile can deregister notification when a new Link Key
**                  is generated per connection.
**
** Returns          TRUE if OK, else FALSE
**
*******************************************************************************/
BOOLEAN  BTM_SecDeleteRmtNameNotifyCallback (tBTM_RMT_NAME_CALLBACK *p_callback)
{
    int i;

    for (i = 0; i < BTM_SEC_MAX_RMT_NAME_CALLBACKS; i++)
    {
        if (btm_cb.p_rmt_name_callback[i] == p_callback)
        {
            btm_cb.p_rmt_name_callback[i] = NULL;
            return(TRUE);
        }
    }

    return(FALSE);
}


/*******************************************************************************
**
** Function         BTM_SecSetConnectFilterCallback
**
** Description      Host can register to be asked whenever a HCI connection
**                  request is received.  In the registered function host
**                  suppose to check connectibility filters.  Yes/No result
**                  should be returned syncronously
**
** Returns          void
**
*******************************************************************************/
void BTM_SecSetConnectFilterCallback (tBTM_FILTER_CB *p_callback)
{
    btm_cb.p_conn_filter_cb = p_callback;
}

/*******************************************************************************
**
** Function         BTM_GetSecurityMode
**
** Description      Get security mode for the device
**
** Returns          void
**
*******************************************************************************/
UINT8 BTM_GetSecurityMode (void)
{
    return(btm_cb.security_mode);
}

/*******************************************************************************
**
** Function         BTM_GetSecurityFlags
**
** Description      Get security flags for the device
**
** Returns          BOOLEAN TRUE or FALSE is device found
**
*******************************************************************************/
BOOLEAN BTM_GetSecurityFlags (BD_ADDR bd_addr, UINT8 * p_sec_flags)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    if ((p_dev_rec = btm_find_dev (bd_addr)) != NULL)
    {
        *p_sec_flags = p_dev_rec->sec_flags;
        return(TRUE);
    }
    BTM_TRACE_ERROR0 ("BTM_GetSecurityFlags false");
    return(FALSE);
}

/*******************************************************************************
**
** Function         BTM_SetSecurityMode
**
** Description      Set security mode for the device
**
** Returns          void
**
*******************************************************************************/
void BTM_SetSecurityMode (UINT8 security_mode)
{
    UINT8   old_mode = btm_cb.security_mode;

    UINT8   sp_mode = HCI_SPD_MODE_ENABLED;
    UINT8   sp_debug_mode = HCI_SPD_MODE_DISABLED;

    switch (security_mode)
    {
#if (BTM_PRE_LISBON_INCLUDED == TRUE)
        case BTM_SEC_MODE_NONE:
        case BTM_SEC_MODE_SERVICE:
        case BTM_SEC_MODE_LINK:
            break;
#endif

        case BTM_SEC_MODE_SP_DEBUG:
            sp_debug_mode = HCI_SPD_MODE_ENABLED;
            break;
        case BTM_SEC_MODE_SP:
            /* the default is enabled */
            break;
        default:
            BTM_TRACE_ERROR1 ("BTM_SetSecurityMode: unknown mode:%d", security_mode);
            return;
    }
    btm_cb.security_mode = security_mode;

    if (HCI_SIMPLE_PAIRING_SUPPORTED(btm_cb.devcb.local_features))
    {
        /* Lisbon devices and only use BTM_SEC_MODE_SP */
        btm_cb.security_mode = BTM_SEC_MODE_SP;
        BTM_TRACE_DEBUG2("BTM_SetSecurityMode: SP:%d, debug:%d", sp_mode, sp_debug_mode);
        btsnd_hcic_write_simple_pairing_mode(sp_mode);
        btsnd_hcic_write_simp_pair_debug_mode(sp_debug_mode);
        return;
    }

    /* must be a pre-Lisbon device */
#if (BTM_PRE_LISBON_INCLUDED == TRUE)
    /* If previously security mode was Link Level and now lesser notify */
    /* controller not to perform authentication, encryption on startup  */
    if ((old_mode == BTM_SEC_MODE_LINK)
        && (       security_mode != BTM_SEC_MODE_LINK))
    {
        BTM_TRACE_DEBUG0("BTM_SetSecurityMode: Authen Enable -> FALSE");
        btsnd_hcic_write_auth_enable (FALSE);
        btsnd_hcic_write_encr_mode (HCI_ENCRYPT_MODE_DISABLED);
    }

    /* If previously security is increased to Link Level notify */
    /* controller to perform authentication, encryption on startup  */
    if ((old_mode != BTM_SEC_MODE_LINK)
        && (       security_mode == BTM_SEC_MODE_LINK))
    {
        BTM_TRACE_DEBUG0("BTM_SetSecurityMode: Authen Enable -> TRUE");
        btsnd_hcic_write_auth_enable (TRUE);
        btsnd_hcic_write_encr_mode (HCI_ENCRYPT_MODE_POINT_TO_POINT);
    }
#endif  /* BTM_PRE_LISBON_INCLUDED == TRUE */
}

/*******************************************************************************
**
** Function         BTM_SetPinType
**
** Description      Set PIN type for the device.
**
** Returns          void
**
*******************************************************************************/
void BTM_SetPinType (UINT8 pin_type, PIN_CODE pin_code, UINT8 pin_code_len)
{
    BTM_TRACE_API3 ("BTM_SetPinType: pin type %d [variable-0, fixed-1], code %s, length %d",
                    pin_type, (char *) pin_code, pin_code_len);

    /* If device is not up security mode will be set as a part of startup */
    if ( (btm_cb.cfg.pin_type != pin_type)
         && (btm_cb.devcb.state > BTM_DEV_STATE_WAIT_AFTER_RESET) )
    {
        btsnd_hcic_write_pin_type (pin_type);
    }

    btm_cb.cfg.pin_type     = pin_type;
    btm_cb.cfg.pin_code_len = pin_code_len;
    memcpy (btm_cb.cfg.pin_code, pin_code, pin_code_len);
}

/*******************************************************************************
**
** Function         BTM_SetPairableMode
**
** Description      Enable or disable pairing
**
** Parameters       allow_pairing - (TRUE or FALSE) whether or not the device
**                      allows pairing.
**                  connect_only_paired - (TRUE or FALSE) whether or not to
**                      only allow paired devices to connect.
**
** Returns          void
**
*******************************************************************************/
void BTM_SetPairableMode (BOOLEAN allow_pairing, BOOLEAN connect_only_paired)
{
    BTM_TRACE_API2 ("BTM_SetPairableMode()  allow_pairing: %u   connect_only_paired: %u", allow_pairing, connect_only_paired);

    btm_cb.pairing_disabled    = !allow_pairing;
    btm_cb.connect_only_paired = connect_only_paired;
}


#define BTM_NO_AVAIL_SEC_SERVICES   ((UINT16) 0xffff)

/*******************************************************************************
**
** Function         BTM_SetUCDSecurityLevel
**
** Description      Register UCD service security level with Security Manager
**
** Parameters:      is_originator - TRUE if originating the connection, FALSE if not
**                  p_name      - Name of the service relevant only if
**                                authorization will show this name to user. ignored
**                                if BTM_SEC_SERVICE_NAME_LEN is 0.
**                  service_id  - service ID for the service passed to authorization callback
**                  sec_level   - bit mask of the security features
**                  psm         - L2CAP PSM
**                  mx_proto_id - protocol ID of multiplexing proto below
**                  mx_chan_id  - channel ID of multiplexing proto below
**
** Returns          TRUE if registered OK, else FALSE
**
*******************************************************************************/
BOOLEAN BTM_SetUCDSecurityLevel (BOOLEAN is_originator, char *p_name, UINT8 service_id,
                                 UINT16 sec_level, UINT16 psm, UINT32 mx_proto_id,
                                 UINT32 mx_chan_id)
{
#if (L2CAP_UCD_INCLUDED == TRUE)
    CONNECTION_TYPE conn_type;

    if (is_originator)
        conn_type = CONNLESS_ORIG;
    else
        conn_type = CONNLESS_TERM;

    return(btm_sec_set_security_level (conn_type, p_name, service_id,
                                       sec_level, psm, mx_proto_id, mx_chan_id));
#else
    return FALSE;
#endif
}

/*******************************************************************************
**
** Function         BTM_SetSecurityLevel
**
** Description      Register service security level with Security Manager
**
** Parameters:      is_originator - TRUE if originating the connection, FALSE if not
**                  p_name      - Name of the service relevant only if
**                                authorization will show this name to user. ignored
**                                if BTM_SEC_SERVICE_NAME_LEN is 0.
**                  service_id  - service ID for the service passed to authorization callback
**                  sec_level   - bit mask of the security features
**                  psm         - L2CAP PSM
**                  mx_proto_id - protocol ID of multiplexing proto below
**                  mx_chan_id  - channel ID of multiplexing proto below
**
** Returns          TRUE if registered OK, else FALSE
**
*******************************************************************************/
BOOLEAN BTM_SetSecurityLevel (BOOLEAN is_originator, char *p_name, UINT8 service_id,
                              UINT16 sec_level, UINT16 psm, UINT32 mx_proto_id,
                              UINT32 mx_chan_id)
{
#if (L2CAP_UCD_INCLUDED == TRUE)
    CONNECTION_TYPE conn_type;

    if (is_originator)
        conn_type = CONN_ORIENT_ORIG;
    else
        conn_type = CONN_ORIENT_TERM;

    return(btm_sec_set_security_level (conn_type, p_name, service_id,
                                       sec_level, psm, mx_proto_id, mx_chan_id));
#else
    return(btm_sec_set_security_level (is_originator, p_name, service_id,
                                       sec_level, psm, mx_proto_id, mx_chan_id));
#endif
}

/*******************************************************************************
**
** Function         btm_sec_set_security_level
**
** Description      Register service security level with Security Manager
**
** Parameters:      conn_type   - TRUE if originating the connection, FALSE if not
**                  p_name      - Name of the service relevant only if
**                                authorization will show this name to user. ignored
**                                if BTM_SEC_SERVICE_NAME_LEN is 0.
**                  service_id  - service ID for the service passed to authorization callback
**                  sec_level   - bit mask of the security features
**                  psm         - L2CAP PSM
**                  mx_proto_id - protocol ID of multiplexing proto below
**                  mx_chan_id  - channel ID of multiplexing proto below
**
** Returns          TRUE if registered OK, else FALSE
**
*******************************************************************************/
static BOOLEAN btm_sec_set_security_level (CONNECTION_TYPE conn_type, char *p_name, UINT8 service_id,
                                           UINT16 sec_level, UINT16 psm, UINT32 mx_proto_id,
                                           UINT32 mx_chan_id)
{
    tBTM_SEC_SERV_REC   *p_srec;
    UINT16               index;
    UINT16               first_unused_record = BTM_NO_AVAIL_SEC_SERVICES;
    BOOLEAN              record_allocated = FALSE;
    BOOLEAN              is_originator;
#if (L2CAP_UCD_INCLUDED == TRUE)
    BOOLEAN              is_ucd;

    if (conn_type & CONNECTION_TYPE_ORIG_MASK)
        is_originator = TRUE;
    else
        is_originator = FALSE;

    if (conn_type & CONNECTION_TYPE_CONNLESS_MASK )
    {
        is_ucd = TRUE;
    }
    else
    {
        is_ucd = FALSE;
    }
#else
    is_originator = conn_type;
#endif

    /* See if the record can be reused (same service name, psm, mx_proto_id,
       service_id, and mx_chan_id), or obtain the next unused record */

    p_srec = &btm_cb.sec_serv_rec[0];


    for (index = 0; index < BTM_SEC_MAX_SERVICE_RECORDS; index++, p_srec++)
    {
        /* Check if there is already a record for this service */
        if (p_srec->security_flags & BTM_SEC_IN_USE)
        {
#if BTM_SEC_SERVICE_NAME_LEN > 0
            if (p_srec->psm == psm                  &&
                p_srec->mx_proto_id == mx_proto_id  &&
                service_id == p_srec->service_id    &&
                (!strncmp (p_name, (char *) p_srec->orig_service_name,
                           BTM_SEC_SERVICE_NAME_LEN) ||
                 !strncmp (p_name, (char *) p_srec->term_service_name,
                           BTM_SEC_SERVICE_NAME_LEN)))
#else
            if (p_srec->psm == psm                  &&
                p_srec->mx_proto_id == mx_proto_id  &&
                service_id == p_srec->service_id)
#endif
            {
                record_allocated = TRUE;
                break;
            }
        }
        /* Mark the first available service record */
        else if (!record_allocated)
        {
            memset (p_srec, 0, sizeof(tBTM_SEC_SERV_REC));
            record_allocated = TRUE;
            first_unused_record = index;
        }
    }

    if (!record_allocated)
    {
        BTM_TRACE_WARNING1("BTM_SEC_REG: Out of Service Records (%d)",  BTM_SEC_MAX_SERVICE_RECORDS);
        return(record_allocated);
    }

    /* Process the request if service record is valid */
    /* If a duplicate service wasn't found, use the first available */
    if (index >= BTM_SEC_MAX_SERVICE_RECORDS)
    {
        index = first_unused_record;
        p_srec = &btm_cb.sec_serv_rec[index];
    }

    p_srec->psm         = psm;
    p_srec->service_id  = service_id;
    p_srec->mx_proto_id = mx_proto_id;

    if (is_originator)
    {
        p_srec->orig_mx_chan_id = mx_chan_id;
#if BTM_SEC_SERVICE_NAME_LEN > 0
        BCM_STRNCPY_S ((char *)p_srec->orig_service_name, sizeof(p_srec->orig_service_name), p_name, BTM_SEC_SERVICE_NAME_LEN);
#endif
        /* clear out the old setting, just in case it exists */
#if (L2CAP_UCD_INCLUDED == TRUE)
        if ( is_ucd )
        {
            p_srec->ucd_security_flags &=
            ~(BTM_SEC_OUT_AUTHORIZE | BTM_SEC_OUT_ENCRYPT    | BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_OUT_MITM |
              BTM_SEC_FORCE_MASTER | BTM_SEC_ATTEMPT_MASTER | BTM_SEC_FORCE_SLAVE | BTM_SEC_ATTEMPT_SLAVE);
        }
        else
#endif
        {
            p_srec->security_flags &=
            ~(BTM_SEC_OUT_AUTHORIZE | BTM_SEC_OUT_ENCRYPT    | BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_OUT_MITM |
              BTM_SEC_FORCE_MASTER | BTM_SEC_ATTEMPT_MASTER | BTM_SEC_FORCE_SLAVE | BTM_SEC_ATTEMPT_SLAVE);
        }

        /* Parameter validation.  Originator should not set requirements for incoming connections */
        sec_level &= ~(BTM_SEC_IN_AUTHORIZE | BTM_SEC_IN_ENCRYPT | BTM_SEC_IN_AUTHENTICATE | BTM_SEC_IN_MITM);

        if (btm_cb.security_mode == BTM_SEC_MODE_SP)
        {
            if (sec_level & BTM_SEC_OUT_AUTHENTICATE)
                sec_level |= BTM_SEC_OUT_MITM;
        }

        /* Make sure the authenticate bit is set, when encrypt bit is set */
        if (sec_level & BTM_SEC_OUT_ENCRYPT)
            sec_level |= BTM_SEC_OUT_AUTHENTICATE;

        /* outgoing connections usually set the security level right before
         * the connection is initiated.
         * set it to be the outgoing service */
#if (L2CAP_UCD_INCLUDED == TRUE)
        if ( is_ucd == FALSE )
#endif
        {
            btm_cb.p_out_serv = p_srec;
        }
    }
    else
    {
        p_srec->term_mx_chan_id = mx_chan_id;
#if BTM_SEC_SERVICE_NAME_LEN > 0
        BCM_STRNCPY_S ((char *)p_srec->term_service_name, sizeof(p_srec->term_service_name), p_name, BTM_SEC_SERVICE_NAME_LEN);
#endif
        /* clear out the old setting, just in case it exists */
#if (L2CAP_UCD_INCLUDED == TRUE)
        if ( is_ucd )
        {
            p_srec->ucd_security_flags &=
            ~(BTM_SEC_IN_AUTHORIZE | BTM_SEC_IN_ENCRYPT     | BTM_SEC_IN_AUTHENTICATE | BTM_SEC_IN_MITM |
              BTM_SEC_FORCE_MASTER | BTM_SEC_ATTEMPT_MASTER | BTM_SEC_FORCE_SLAVE | BTM_SEC_ATTEMPT_SLAVE);
        }
        else
#endif
        {
            p_srec->security_flags &=
            ~(BTM_SEC_IN_AUTHORIZE | BTM_SEC_IN_ENCRYPT     | BTM_SEC_IN_AUTHENTICATE | BTM_SEC_IN_MITM |
              BTM_SEC_FORCE_MASTER | BTM_SEC_ATTEMPT_MASTER | BTM_SEC_FORCE_SLAVE | BTM_SEC_ATTEMPT_SLAVE);
        }

        /* Parameter validation.  Acceptor should not set requirements for outgoing connections */
        sec_level &= ~(BTM_SEC_OUT_AUTHORIZE | BTM_SEC_OUT_ENCRYPT | BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_OUT_MITM);

        if (btm_cb.security_mode == BTM_SEC_MODE_SP)
        {
            if (sec_level & BTM_SEC_IN_AUTHENTICATE)
                sec_level |= BTM_SEC_IN_MITM;
        }

        /* Make sure the authenticate bit is set, when encrypt bit is set */
        if (sec_level & BTM_SEC_IN_ENCRYPT)
            sec_level |= BTM_SEC_IN_AUTHENTICATE;
    }

#if (L2CAP_UCD_INCLUDED == TRUE)
    if ( is_ucd )
    {
        p_srec->security_flags     |= (UINT16)(BTM_SEC_IN_USE);
        p_srec->ucd_security_flags |= (UINT16)(sec_level | BTM_SEC_IN_USE);
    }
    else
    {
        p_srec->security_flags |= (UINT16)(sec_level | BTM_SEC_IN_USE);
    }

    BTM_TRACE_API6("BTM_SEC_REG[%d]: id %d, conn_type 0x%x, psm 0x%04x, proto_id %d, chan_id %d",
                   index, service_id, conn_type, psm, mx_proto_id, mx_chan_id);

    BTM_TRACE_API2("               : security_flags: 0x%04x, ucd_security_flags: 0x%04x",
                   p_srec->security_flags, p_srec->ucd_security_flags);

#if BTM_SEC_SERVICE_NAME_LEN > 0
    BTM_TRACE_API2("               : service name [%s] (up to %d chars saved)",
                   p_name, BTM_SEC_SERVICE_NAME_LEN);
#endif
#else
    p_srec->security_flags |= (UINT16)(sec_level | BTM_SEC_IN_USE);

    BTM_TRACE_API6("BTM_SEC_REG[%d]: id %d, is_orig %d, psm 0x%04x, proto_id %d, chan_id %d",
                   index, service_id, is_originator, psm, mx_proto_id, mx_chan_id);

#if BTM_SEC_SERVICE_NAME_LEN > 0
    BTM_TRACE_API3("               : sec: 0x%x, service name [%s] (up to %d chars saved)",
                   p_srec->security_flags, p_name, BTM_SEC_SERVICE_NAME_LEN);
#endif
#endif


    return(record_allocated);
}

/*******************************************************************************
**
** Function         BTM_SecClrService
**
** Description      Removes specified service record(s) from the security database.
**                  All service records with the specified name are removed.
**                  Typically used only by devices with limited RAM so that it can
**                  reuse an old security service record.
**
**                  Note: Unpredictable results may occur if a service is cleared
**                      that is still in use by an application/profile.
**
** Parameters       Service ID - Id of the service to remove. ('0' removes all service
**                          records (except SDP).
**
** Returns          Number of records that were freed.
**
*******************************************************************************/
UINT8 BTM_SecClrService (UINT8 service_id)
{
    tBTM_SEC_SERV_REC   *p_srec = &btm_cb.sec_serv_rec[0];
    UINT8   num_freed = 0;
    int     i;

    for (i = 0; i < BTM_SEC_MAX_SERVICE_RECORDS; i++, p_srec++)
    {
        /* Delete services with specified name (if in use and not SDP) */
        if ((p_srec->security_flags & BTM_SEC_IN_USE) && (p_srec->psm != BT_PSM_SDP) &&
            (!service_id || (service_id == p_srec->service_id)))
        {
            BTM_TRACE_API2("BTM_SEC_CLR[%d]: id %d", i, service_id);
            p_srec->security_flags = 0;
#if (L2CAP_UCD_INCLUDED == TRUE)
            p_srec->ucd_security_flags = 0;
#endif
            num_freed++;
        }
    }

    return(num_freed);
}

/*******************************************************************************
**
** Function         btm_sec_clr_service_by_psm
**
** Description      Removes specified service record from the security database.
**                  All service records with the specified psm are removed.
**                  Typically used by L2CAP to free up the service record used
**                  by dynamic PSM clients when the channel is closed.
**                  The given psm must be a virtual psm.
**
** Parameters       Service ID - Id of the service to remove. ('0' removes all service
**                          records (except SDP).
**
** Returns          Number of records that were freed.
**
*******************************************************************************/
UINT8 btm_sec_clr_service_by_psm (UINT16 psm)
{
    tBTM_SEC_SERV_REC   *p_srec = &btm_cb.sec_serv_rec[0];
    UINT8   num_freed = 0;
    int     i;

    for (i = 0; i < BTM_SEC_MAX_SERVICE_RECORDS; i++, p_srec++)
    {
        /* Delete services with specified name (if in use and not SDP) */
        if ((p_srec->security_flags & BTM_SEC_IN_USE) && (p_srec->psm == psm) )
        {
            BTM_TRACE_API2("BTM_SEC_CLR[%d]: id %d ", i, p_srec->service_id);
            p_srec->security_flags = 0;
            num_freed++;
        }
    }
    BTM_TRACE_API2("btm_sec_clr_service_by_psm psm:0x%x num_freed:%d", psm, num_freed);

    return(num_freed);
}

/*******************************************************************************
**
** Function         BTM_SecClrUCDService
**
** Description
**
** Parameters       Service ID - Id of the service to remove.
**                               ('0' removes all service records )
**
** Returns          Number of records that were cleared.
**
*******************************************************************************/
UINT8 BTM_SecClrUCDService (UINT8 service_id)
{
#if (L2CAP_UCD_INCLUDED == TRUE)
    tBTM_SEC_SERV_REC   *p_srec = &btm_cb.sec_serv_rec[0];
    UINT8   num_cleared = 0;
    int     i;

    for (i = 0; i < BTM_SEC_MAX_SERVICE_RECORDS; i++, p_srec++)
    {
        /* Delete services with specified name (if in use and not SDP) */
        if ((p_srec->security_flags & BTM_SEC_IN_USE) &&
            (!service_id || (service_id == (UINT32)p_srec->service_id)))
        {
            BTM_TRACE_API2("BTM_UCD_SEC_CLR[%d]: id %d", i, service_id);
            p_srec->ucd_security_flags = 0;
            num_cleared++;
        }
    }

    return(num_cleared);
#else
    return(0);
#endif
}

/*******************************************************************************
**
** Function         BTM_PINCodeReply
**
** Description      This function is called after Security Manager submitted
**                  PIN code request to the UI.
**
** Parameters:      bd_addr      - Address of the device for which PIN was requested
**                  res          - result of the operation BTM_SUCCESS if success
**                  pin_len      - length in bytes of the PIN Code
**                  p_pin        - pointer to array with the PIN Code
**                  trusted_mask - bitwise OR of trusted services (array of UINT32)
**
*******************************************************************************/
void BTM_PINCodeReply (BD_ADDR bd_addr, UINT8 res, UINT8 pin_len, UINT8 *p_pin, UINT32 trusted_mask[])
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    BTM_TRACE_API4 ("BTM_PINCodeReply(): PairState: %s   PairFlags: 0x%02x  PinLen:%d  Result:%d",
                    btm_pair_state_descr(btm_cb.pairing_state), btm_cb.pairing_flags, pin_len, res);

    /* If timeout already expired or has been canceled, ignore the reply */
    if (btm_cb.pairing_state != BTM_PAIR_STATE_WAIT_LOCAL_PIN)
    {
        BTM_TRACE_WARNING1 ("BTM_PINCodeReply() - Wrong State: %d", btm_cb.pairing_state);
        return;
    }

    if (memcmp (bd_addr, btm_cb.pairing_bda, BD_ADDR_LEN) != 0)
    {
        BTM_TRACE_ERROR0 ("BTM_PINCodeReply() - Wrong BD Addr");
        return;
    }

    if ((p_dev_rec = btm_find_dev (bd_addr)) == NULL)
    {
        BTM_TRACE_ERROR0 ("BTM_PINCodeReply() - no dev CB");
        return;
    }

    if ( (pin_len > PIN_CODE_LEN) || (pin_len == 0) || (p_pin == NULL) )
        res = BTM_ILLEGAL_VALUE;

    if (res != BTM_SUCCESS)
    {
        /* if peer started dd OR we started dd and pre-fetch pin was not used send negative reply */
        if ((btm_cb.pairing_flags & BTM_PAIR_FLAGS_PEER_STARTED_DD) ||
            ((btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD) &&
            (btm_cb.pairing_flags & BTM_PAIR_FLAGS_DISC_WHEN_DONE)) )
        {
            /* use BTM_PAIR_STATE_WAIT_AUTH_COMPLETE to report authentication failed event */
            btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);
            btm_cb.acl_disc_reason = HCI_ERR_HOST_REJECT_SECURITY;

            btsnd_hcic_pin_code_neg_reply (bd_addr);
        }
        else
        {
            p_dev_rec->security_required = BTM_SEC_NONE;
            btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
        }
        return;
    }
    if (trusted_mask)
        BTM_SEC_COPY_TRUSTED_DEVICE(trusted_mask, p_dev_rec->trusted_mask);
    p_dev_rec->sec_flags   |= BTM_SEC_LINK_KEY_AUTHED;

    if ( (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD)
         &&  (p_dev_rec->hci_handle == BTM_SEC_INVALID_HANDLE)
         &&  (btm_cb.security_mode_changed == FALSE) )
    {
        /* This is start of the dedicated bonding if local device is 2.0 */
        btm_cb.pin_code_len = pin_len;
        memcpy (btm_cb.pin_code, p_pin, pin_len);

        btm_cb.security_mode_changed = TRUE;
#ifdef APPL_AUTH_WRITE_EXCEPTION
        if(!(APPL_AUTH_WRITE_EXCEPTION)(p_dev_rec->bd_addr))
#endif
        btsnd_hcic_write_auth_enable (TRUE);

        btm_cb.acl_disc_reason = 0xff ;

        /* if we rejected incoming connection request, we have to wait HCI_Connection_Complete event */
        /*  before originating  */
        if (btm_cb.pairing_flags & BTM_PAIR_FLAGS_REJECTED_CONNECT)
        {
            BTM_TRACE_WARNING0 ("BTM_PINCodeReply(): waiting HCI_Connection_Complete after rejected incoming connection");
            /* we change state little bit early so btm_sec_connected() will originate connection */
            /*   when existing ACL link is down completely */
            btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_PIN_REQ);
        }
        /* if we already accepted incoming connection from pairing device */
        else if (p_dev_rec->sm4 & BTM_SM4_CONN_PEND)
        {
            BTM_TRACE_WARNING0 ("BTM_PINCodeReply(): link is connecting so wait pin code request from peer");
            btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_PIN_REQ);
        }
        else if (btm_sec_dd_create_conn(p_dev_rec) != BTM_CMD_STARTED)
        {
            btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
            p_dev_rec->sec_flags &= ~BTM_SEC_LINK_KEY_AUTHED;

            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,  p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, HCI_ERR_AUTH_FAILURE);
        }
        return;
    }

    btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);
    btm_cb.acl_disc_reason = HCI_SUCCESS;

#ifdef PORCHE_PAIRING_CONFLICT
    BTM_TRACE_EVENT2("BTM_PINCodeReply(): Saving pin_len: %d btm_cb.pin_code_len: %d", pin_len, btm_cb.pin_code_len);
    /* if this was not pre-fetched, save the PIN */
    if (btm_cb.pin_code_len == 0)
        memcpy (btm_cb.pin_code, p_pin, pin_len);
    btm_cb.pin_code_len_saved = pin_len;
#endif
    btsnd_hcic_pin_code_req_reply (bd_addr, pin_len, p_pin);
}


/*******************************************************************************
**
** Function         BTM_DeviceAuthorized
**
** Description      This function is called after Security Manager submitted
**                  authorization request to the UI.
**
** Parameters:      bd_addr     - Address of the device for which PIN was requested
**                  res         - result of the operation BTM_SUCCESS if success
**
*******************************************************************************/
void BTM_DeviceAuthorized (BD_ADDR bd_addr, UINT8 res, UINT32 trusted_mask[])
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    if ((p_dev_rec = btm_find_dev (bd_addr)) == NULL)
    {
        BTM_TRACE_WARNING6 ("Security Manager: Attempting Authorization of Unknown Device Address [%02x%02x%02x%02x%02x%02x]",
                            bd_addr[0], bd_addr[1], bd_addr[2], bd_addr[3], bd_addr[4], bd_addr[5]);
        return;
    }

    BTM_TRACE_EVENT4 ("Security Manager: authorized status:%d State:%d Trusted:%08x %08x",
                      res, (p_dev_rec) ? p_dev_rec->sec_state : 0, trusted_mask[0], trusted_mask[1]);

    if (res == BTM_SUCCESS)
    {
        p_dev_rec->sec_flags   |= BTM_SEC_AUTHORIZED;
        if (trusted_mask)
            BTM_SEC_COPY_TRUSTED_DEVICE(trusted_mask, p_dev_rec->trusted_mask);
    }

    if (p_dev_rec->sec_state != BTM_SEC_STATE_AUTHORIZING)
        return;

    p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;

    if (res != BTM_SUCCESS)
    {
        btm_sec_dev_rec_cback_event (p_dev_rec, res);
        return;
    }

    if ((res = (UINT8)btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED)
    {
        btm_sec_dev_rec_cback_event (p_dev_rec, res);
    }
}



/*******************************************************************************
**
** Function         BTM_SecBond
**
** Description      This function is called to perform bonding with peer device.
**                  If the connection is already up, but not secure, pairing
**                  is attempted.  If already paired BTM_SUCCESS is returned.
**
** Parameters:      bd_addr      - Address of the device to bond
**                  pin_len      - length in bytes of the PIN Code
**                  p_pin        - pointer to array with the PIN Code
**                  trusted_mask - bitwise OR of trusted services (array of UINT32)
**
**  Note: After 2.1 parameters are not used and preserved here not to change API
*******************************************************************************/
tBTM_STATUS BTM_SecBond (BD_ADDR bd_addr, UINT8 pin_len, UINT8 *p_pin, UINT32 trusted_mask[])
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    tBTM_STATUS      status;
#if SMP_INCLUDED == TRUE
    tACL_CONN   *p=NULL;
    BOOLEAN     is_le_slave_role=FALSE;
#endif
    BTM_TRACE_API6 ("BTM_SecBond BDA: %02x:%02x:%02x:%02x:%02x:%02x",
                    bd_addr[0], bd_addr[1], bd_addr[2], bd_addr[3], bd_addr[4], bd_addr[5]);

    /* Other security process is in progress */
    if (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
    {
        BTM_TRACE_ERROR1 ("BTM_SecBond: already busy in state: %s", btm_pair_state_descr(btm_cb.pairing_state));
        return(BTM_WRONG_MODE);
    }


    p_dev_rec = btm_find_or_alloc_dev (bd_addr);
    BTM_TRACE_DEBUG1 ("before update sec_flags=0x%x", p_dev_rec->sec_flags);


#if SMP_INCLUDED == TRUE
    p = btm_bda_to_acl(bd_addr);
    if (p && p->is_le_link )
    {
        if (p_dev_rec->sec_state == BTM_SEC_STATE_AUTHENTICATING)
        {
            BTM_TRACE_ERROR1 ("BTM_SecBond: LE already busy in state: %x", p_dev_rec->sec_state );
            return(BTM_WRONG_MODE);
        }

        if (p->link_role == BTM_ROLE_SLAVE)
        {
            is_le_slave_role = TRUE;
            BTM_TRACE_DEBUG0 ("LE Link Slave" );
        }
        else
        {
            BTM_TRACE_DEBUG0 ("LE Link Maste" );
        }
    }
    else
    {
        BTM_TRACE_DEBUG0 ("No LE Link" );
    }

    if (!is_le_slave_role)
    {
        /* Finished if connection is active and already paired */
        if ( (p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE)
             &&  (p_dev_rec->sec_flags & BTM_SEC_AUTHENTICATED) )
        {
            BTM_TRACE_WARNING0("BTM_SecBond -> Already Paired");
            return(BTM_SUCCESS);
        }
    }
#else
    /* Finished if connection is active and already paired */
    if ( (p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE)
         &&  (p_dev_rec->sec_flags & BTM_SEC_AUTHENTICATED) )
    {
        BTM_TRACE_WARNING0("BTM_SecBond -> Already Paired");
        return(BTM_SUCCESS);
    }
#endif

    /* Tell controller to get rid of the link key if it has one stored */
    if ((BTM_DeleteStoredLinkKey (bd_addr, NULL)) != BTM_SUCCESS)
        return(BTM_NO_RESOURCES);

    /* Save the PIN code if we got a valid one */
    if (p_pin && (pin_len <= PIN_CODE_LEN) && (pin_len != 0))
    {
        btm_cb.pin_code_len = pin_len;
        memcpy (btm_cb.pin_code, p_pin, PIN_CODE_LEN);
    }

    memcpy (btm_cb.pairing_bda, bd_addr, BD_ADDR_LEN);

    btm_cb.pairing_flags = BTM_PAIR_FLAGS_WE_STARTED_DD;

    p_dev_rec->security_required = BTM_SEC_OUT_AUTHENTICATE;
    p_dev_rec->is_originator     = TRUE;
    if (trusted_mask)
        BTM_SEC_COPY_TRUSTED_DEVICE(trusted_mask, p_dev_rec->trusted_mask);



#if SMP_INCLUDED == TRUE

    if (!is_le_slave_role)
    {
        p_dev_rec->sec_flags &= ~(BTM_SEC_LINK_KEY_KNOWN | BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED
                                  | BTM_SEC_ROLE_SWITCHED  | BTM_SEC_LINK_KEY_AUTHED);

    }

    /* LE device, do SMP pairing */
    if (p_dev_rec->device_type == BT_DEVICE_TYPE_BLE)
    {
        if (SMP_Pair(p_dev_rec->bd_addr) == SMP_STARTED)
        {
            p_dev_rec->sec_state = BTM_SEC_STATE_AUTHENTICATING;
            return BTM_CMD_STARTED;
        }
        else
            return(BTM_NO_RESOURCES);
    }
#else
    p_dev_rec->sec_flags &= ~(BTM_SEC_LINK_KEY_KNOWN | BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED
                              | BTM_SEC_ROLE_SWITCHED  | BTM_SEC_LINK_KEY_AUTHED);
#endif

    BTM_TRACE_DEBUG1 ("after update sec_flags=0x%x", p_dev_rec->sec_flags);
    if (!HCI_SIMPLE_PAIRING_SUPPORTED(btm_cb.devcb.local_features))
    {
        /* The special case when we authenticate keyboard.  Set pin type to fixed */
        /* It would be probably better to do it from the application, but it is */
        /* complicated */
        if (((p_dev_rec->dev_class[1] & BTM_COD_MAJOR_CLASS_MASK) == BTM_COD_MAJOR_PERIPHERAL)
            && (p_dev_rec->dev_class[2] & BTM_COD_MINOR_KEYBOARD)
            && (btm_cb.cfg.pin_type != HCI_PIN_TYPE_FIXED))
        {
            btm_cb.pin_type_changed = TRUE;
            btsnd_hcic_write_pin_type (HCI_PIN_TYPE_FIXED);
        }
    }

    BTM_TRACE_EVENT1("BTM_SecBond: Local device supports SSP=%d", HCI_SIMPLE_PAIRING_SUPPORTED(btm_cb.devcb.local_features));

    BTM_TRACE_EVENT4("  remote_features=%02x-%02x-%02x-%02x",
                     p_dev_rec->features[0], p_dev_rec->features[1], p_dev_rec->features[2], p_dev_rec->features[3]);
    BTM_TRACE_EVENT4("                  %02x-%02x-%02x-%02x",
                     p_dev_rec->features[4], p_dev_rec->features[5], p_dev_rec->features[6], p_dev_rec->features[7]);

    BTM_TRACE_EVENT2 ("BTM_SecBond: Remote sm4: 0x%x  HCI Handle: 0x%04x", p_dev_rec->sm4, p_dev_rec->hci_handle);

#if BTM_SEC_FORCE_RNR_FOR_DBOND == TRUE
    p_dev_rec->sec_flags &= ~BTM_SEC_NAME_KNOWN;
#endif

    /* If connection already exists... */
    if (p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE)
    {
        if (!btm_sec_start_authentication (p_dev_rec))
            return(BTM_NO_RESOURCES);

        btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_PIN_REQ);

        /* Mark lcb as bonding */
        l2cu_update_lcb_4_bonding (bd_addr, TRUE);
        return(BTM_CMD_STARTED);
    }

    BTM_TRACE_DEBUG2 ("sec mode: %d sm4:x%x", btm_cb.security_mode, p_dev_rec->sm4);
    if (!HCI_SIMPLE_PAIRING_SUPPORTED(btm_cb.devcb.local_features)
        || (p_dev_rec->sm4 == BTM_SM4_KNOWN))
    {
        if ( btm_sec_check_prefetch_pin (p_dev_rec) )
	        return(BTM_CMD_STARTED);
    }
    if (BTM_SEC_MODE_SP == btm_cb.security_mode && BTM_SEC_IS_SM4_UNKNOWN(p_dev_rec->sm4))
    {
        /* local is 2.1 and peer is unknown */
        if ((p_dev_rec->sm4 & BTM_SM4_CONN_PEND) == 0)
        {
            /* we are not accepting connection request from peer
             * -> RNR (to learn if peer is 2.1)
             * RNR when no ACL causes HCI_RMT_HOST_SUP_FEAT_NOTIFY_EVT */
            btm_sec_change_pairing_state (BTM_PAIR_STATE_GET_REM_NAME);
            BTM_ReadRemoteDeviceName(bd_addr, NULL);
        }
        else
        {
            /* We are accepting connection request from peer */
            btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_PIN_REQ);
        }
        BTM_TRACE_DEBUG3 ("State:%s sm4: 0x%x sec_state:%d", btm_pair_state_descr (btm_cb.pairing_state), p_dev_rec->sm4, p_dev_rec->sec_state);
        return BTM_CMD_STARTED;
    }

    /* both local and peer are 2.1  */
    status = btm_sec_dd_create_conn(p_dev_rec);

    if (status != BTM_CMD_STARTED)
    {
        btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
    }

    return status;
}


/*******************************************************************************
**
** Function         BTM_SecBondCancel
**
** Description      This function is called to cancel ongoing bonding process
**                  with peer device.
**
** Parameters:      bd_addr      - Address of the peer device
**
*******************************************************************************/
tBTM_STATUS BTM_SecBondCancel (BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
#if SMP_INCLUDED == TRUE
    tACL_CONN   *p=NULL;
#endif

    BTM_TRACE_API2 ("BTM_SecBondCancel()  State: %s flags:0x%x",
                    btm_pair_state_descr (btm_cb.pairing_state), btm_cb.pairing_flags);

    if (((p_dev_rec = btm_find_dev (bd_addr)) == NULL)
        ||  (memcmp (btm_cb.pairing_bda, bd_addr, BD_ADDR_LEN) != 0) )
        return BTM_UNKNOWN_ADDR;

#if SMP_INCLUDED == TRUE
    p = btm_bda_to_acl(bd_addr);
    if (p && p->is_le_link &&
        (p_dev_rec->sec_state == BTM_SEC_STATE_AUTHENTICATING))
    {
        BTM_TRACE_DEBUG0 ("Cancel LE pairing");
        if (SMP_PairCancel(bd_addr))
        {
            return BTM_CMD_STARTED;
        }
        else
        {
            return BTM_WRONG_MODE;
        }
    }

#endif
    BTM_TRACE_DEBUG2 ("hci_handle:0x%x sec_state:%d", p_dev_rec->hci_handle, p_dev_rec->sec_state );
    if (BTM_PAIR_STATE_WAIT_LOCAL_PIN == btm_cb.pairing_state &&
        BTM_PAIR_FLAGS_WE_STARTED_DD & btm_cb.pairing_flags)
    {
        /* pre-fetching pin for dedicated bonding */
        btm_sec_bond_cancel_complete();
        return BTM_SUCCESS;
    }

    /* If this BDA is in a bonding procedure */
    if ( (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
         &&  (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD))
    {
        /* If the HCI link is up */
        if (p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE)
        {
            /* If some other thread disconnecting, we do not send second command */
            if (p_dev_rec->sec_state == BTM_SEC_STATE_DISCONNECTING)
                return(BTM_CMD_STARTED);

            /* If the HCI link was set up by Bonding process */
            if (btm_cb.pairing_flags & BTM_PAIR_FLAGS_DISC_WHEN_DONE)
                return btm_sec_send_hci_disconnect(p_dev_rec, HCI_ERR_PEER_USER);
            else
                l2cu_update_lcb_4_bonding(bd_addr, FALSE);

            return BTM_NOT_AUTHORIZED;
        }
        else /*HCI link is not up */
        {
            /* If the HCI link creation was started by Bonding process */
            if (btm_cb.pairing_flags & BTM_PAIR_FLAGS_DISC_WHEN_DONE)
            {
                if (btsnd_hcic_create_conn_cancel(bd_addr))
                    return BTM_CMD_STARTED;

                return BTM_NO_RESOURCES;
            }

            return BTM_NOT_AUTHORIZED;
        }
    }

    return BTM_WRONG_MODE;
}

/*******************************************************************************
**
** Function         BTM_SecUseMasterLinkKey
**
** Description      This function is called to tell master of the piconet to
**                  switch to master link key
**
** Parameters:      use_master_key - If true Master Link Key shoul be used
**
*******************************************************************************/
tBTM_STATUS BTM_SecUseMasterLinkKey (BOOLEAN use_master_key)
{
    return(btsnd_hcic_master_link_key (use_master_key) ?  BTM_SUCCESS :
           BTM_NO_RESOURCES);
}

/*******************************************************************************
**
** Function         BTM_SetMasterKeyCompCback
**
** Description      This function is called to register for the master key complete
**                  status event.
**
** Parameters:      mkey_cback - callback registered with the security manager
**
*******************************************************************************/
void BTM_SetMasterKeyCompCback( tBTM_MKEY_CALLBACK *mkey_cback )
{
    btm_cb.mkey_cback = mkey_cback;
}

/*******************************************************************************
**
** Function         BTM_SecGetDeviceLinkKey
**
** Description      This function is called to obtain link key for the device
**                  it returns BTM_SUCCESS if link key is available, or
**                  BTM_UNKNOWN_ADDR if Security Manager does not know about
**                  the device or device record does not contain link key info
**
** Parameters:      bd_addr      - Address of the device
**                  link_key     - Link Key is copied into this array
**
*******************************************************************************/
tBTM_STATUS BTM_SecGetDeviceLinkKey (BD_ADDR bd_addr, LINK_KEY link_key)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    if (((p_dev_rec = btm_find_dev (bd_addr)) != NULL)
        && (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN))
    {
        memcpy (link_key, p_dev_rec->link_key, LINK_KEY_LEN);
        return(BTM_SUCCESS);
    }
    return(BTM_UNKNOWN_ADDR);
}


/*******************************************************************************
**
** Function         BTM_SetEncryption
**
** Description      This function is called to ensure that connection is
**                  encrypted.  Should be called only on an open connection.
**                  Typically only needed for connections that first want to
**                  bring up unencrypted links, then later encrypt them.
**
** Parameters:      bd_addr       - Address of the peer device
**                  p_callback    - Pointer to callback function called if
**                                  this function returns PENDING after required
**                                  procedures are completed.  Can be set to NULL
**                                  if status is not desired.
**                  p_ref_data    - pointer to any data the caller wishes to receive
**                                  in the callback function upon completion.
*                                   can be set to NULL if not used.
**
** Returns          BTM_SUCCESS   - already encrypted
**                  BTM_PENDING   - command will be returned in the callback
**                  BTM_WRONG_MODE- connection not up.
**                  BTM_BUSY      - security procedures are currently active
**                  BTM_MODE_UNSUPPORTED - if security manager not linked in.
**
*******************************************************************************/
tBTM_STATUS BTM_SetEncryption (BD_ADDR bd_addr, tBTM_SEC_CBACK *p_callback,
                               void *p_ref_data)
{
    tBTM_SEC_DEV_REC  *p_dev_rec;
    tBTM_STATUS       rc;

#if BLE_INCLUDED == TRUE
    tACL_CONN         *p;
    p = btm_bda_to_acl(bd_addr);
#endif

    p_dev_rec = btm_find_dev (bd_addr);
    if (!p_dev_rec || (p_dev_rec->hci_handle == BTM_SEC_INVALID_HANDLE))
    {
        /* Connection should be up and runnning */
        BTM_TRACE_WARNING0 ("Security Manager: BTM_SetEncryption not connected");

        if (p_callback)
            (*p_callback) (bd_addr, p_ref_data, BTM_WRONG_MODE);

        return(BTM_WRONG_MODE);
    }


    if (
#if BLE_INCLUDED == TRUE
       !p->is_le_link &&
#endif
       (p_dev_rec->sec_flags & (BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED))
       == (BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED))
    {
        BTM_TRACE_EVENT0 ("Security Manager: BTM_SetEncryption already encrypted");

        if (p_callback)
            (*p_callback) (bd_addr, p_ref_data, BTM_SUCCESS);

        return(BTM_SUCCESS);
    }

    if (p_dev_rec->p_callback)
    {
        /* Connection should be up and runnning */
        BTM_TRACE_WARNING0 ("Security Manager: BTM_SetEncryption busy");

        if (p_callback)
            (*p_callback) (bd_addr, p_ref_data, BTM_BUSY);

        return(BTM_BUSY);
    }

    p_dev_rec->p_callback        = p_callback;
    p_dev_rec->p_ref_data        = p_ref_data;
    p_dev_rec->security_required |= (BTM_SEC_IN_AUTHENTICATE | BTM_SEC_IN_ENCRYPT);
    p_dev_rec->is_originator     = FALSE;

    BTM_TRACE_API4 ("Security Manager: BTM_SetEncryption Handle:%d State:%d Flags:0x%x Required:0x%x",
                    p_dev_rec->hci_handle, p_dev_rec->sec_state, p_dev_rec->sec_flags,
                    p_dev_rec->security_required);
#if BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE
    if (p->is_le_link)
    {
        rc = btm_ble_set_encryption(bd_addr, p_ref_data, p->link_role);
    }
    else
#endif

        rc = btm_sec_execute_procedure (p_dev_rec);

    if ( rc != BTM_CMD_STARTED)
    {
        if (p_callback)
        {
            p_dev_rec->p_callback = NULL;
            (*p_callback) (bd_addr, p_dev_rec->p_ref_data, rc);
        }
    }
    return(rc);
}

/*******************************************************************************
 * disconnect the ACL link, if it's not done yet.
*******************************************************************************/
static tBTM_STATUS btm_sec_send_hci_disconnect (tBTM_SEC_DEV_REC *p_dev_rec, UINT8 reason)
{
    UINT8 old_state = p_dev_rec->sec_state;

    BTM_TRACE_EVENT2 ("btm_sec_send_hci_disconnect:  handle:0x%x, reason=0x%x",
                      p_dev_rec->hci_handle, reason);

    /* if some other thread disconnecting, we do not send second command */
    if (BTM_SEC_STATE_DISCONNECTING != old_state)
    {
        p_dev_rec->sec_state = BTM_SEC_STATE_DISCONNECTING;

#if BTM_DISC_DURING_RS == TRUE
        /* If a Role Switch is in progress, delay the HCI Disconnect to avoid controller problem (4329B1) */
        if (p_dev_rec->rs_disc_pending == BTM_SEC_RS_PENDING)
        {
                 BTM_TRACE_ERROR0("RS in progress - Set DISC Pending flag in btm_sec_send_hci_disconnect to delay disconnect");
                 p_dev_rec->rs_disc_pending = BTM_SEC_DISC_PENDING;
                 return BTM_SUCCESS;
        }
#endif
        /* Tear down the HCI link */
        if (!btsnd_hcic_disconnect (p_dev_rec->hci_handle, reason))
        {
            /* could not send disconnect. restore old state */
            p_dev_rec->sec_state = old_state;
            return(BTM_NO_RESOURCES);
        }
    }
    return(BTM_CMD_STARTED);
}

/*******************************************************************************
**
** Function         BTM_ConfirmReqReply
**
** Description      This function is called to confirm the numeric value for
**                  Simple Pairing in response to BTM_SP_CFM_REQ_EVT
**
** Parameters:      res           - result of the operation BTM_SUCCESS if success
**                  bd_addr       - Address of the peer device
**
*******************************************************************************/
void BTM_ConfirmReqReply(tBTM_STATUS res, BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    BTM_TRACE_EVENT2 ("BTM_ConfirmReqReply() State: %s  Res: %u",
                      btm_pair_state_descr(btm_cb.pairing_state), res);

    /* If timeout already expired or has been canceled, ignore the reply */
    if ( (btm_cb.pairing_state != BTM_PAIR_STATE_WAIT_NUMERIC_CONFIRM)
         ||  (memcmp (btm_cb.pairing_bda, bd_addr, BD_ADDR_LEN) != 0) )
        return;

    btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);

    if ( (res == BTM_SUCCESS) || (res == BTM_SUCCESS_NO_SECURITY) )
    {
        btm_cb.acl_disc_reason = HCI_SUCCESS;

        if (res == BTM_SUCCESS)
        {
            if ((p_dev_rec = btm_find_dev (bd_addr)) != NULL)
                p_dev_rec->sec_flags |= BTM_SEC_LINK_KEY_AUTHED;
        }

        btsnd_hcic_user_conf_reply (bd_addr, TRUE);
    }
    else
    {
        /* Report authentication failed event from state BTM_PAIR_STATE_WAIT_AUTH_COMPLETE */
        btm_cb.acl_disc_reason = HCI_ERR_HOST_REJECT_SECURITY;
        btsnd_hcic_user_conf_reply (bd_addr, FALSE);
    }
}

/*******************************************************************************
**
** Function         BTM_PasskeyReqReply
**
** Description      This function is called to provide the passkey for
**                  Simple Pairing in response to BTM_SP_KEY_REQ_EVT
**
** Parameters:      res     - result of the operation BTM_SUCCESS if success
**                  bd_addr - Address of the peer device
**                  passkey - numeric value in the range of
**                  BTM_MIN_PASSKEY_VAL(0) - BTM_MAX_PASSKEY_VAL(999999(0xF423F)).
**
*******************************************************************************/
#if (BTM_LOCAL_IO_CAPS != BTM_IO_CAP_NONE)
void BTM_PasskeyReqReply(tBTM_STATUS res, BD_ADDR bd_addr, UINT32 passkey)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    BTM_TRACE_API2 ("BTM_PasskeyReqReply: State: %s  res:%d",
                    btm_pair_state_descr(btm_cb.pairing_state), res);

    if ( (btm_cb.pairing_state == BTM_PAIR_STATE_IDLE)
         ||  (memcmp (btm_cb.pairing_bda, bd_addr, BD_ADDR_LEN) != 0) )
    {
        return;
    }

    /* If timeout already expired or has been canceled, ignore the reply */
    if ( (btm_cb.pairing_state == BTM_PAIR_STATE_WAIT_AUTH_COMPLETE) && (res != BTM_SUCCESS) )
    {
        if ((p_dev_rec = btm_find_dev (bd_addr)) != NULL)
        {
            btm_cb.acl_disc_reason = HCI_ERR_HOST_REJECT_SECURITY;

            if (p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE)
                btm_sec_send_hci_disconnect (p_dev_rec, HCI_ERR_AUTH_FAILURE);
            else
                BTM_SecBondCancel(bd_addr);

            p_dev_rec->sec_flags &= ~(BTM_SEC_LINK_KEY_AUTHED | BTM_SEC_LINK_KEY_KNOWN);

            btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
            return;
        }
    }
    else if (btm_cb.pairing_state != BTM_PAIR_STATE_KEY_ENTRY)
        return;

    if (passkey > BTM_MAX_PASSKEY_VAL)
        res = BTM_ILLEGAL_VALUE;

    btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);

    if (res != BTM_SUCCESS)
    {
        /* use BTM_PAIR_STATE_WAIT_AUTH_COMPLETE to report authentication failed event */
        btm_cb.acl_disc_reason = HCI_ERR_HOST_REJECT_SECURITY;
        btsnd_hcic_user_passkey_neg_reply (bd_addr);
    }
    else
    {
        btm_cb.acl_disc_reason = HCI_SUCCESS;
        btsnd_hcic_user_passkey_reply (bd_addr, passkey);
    }
}
#endif

/*******************************************************************************
**
** Function         BTM_SendKeypressNotif
**
** Description      This function is used during the passkey entry model
**                  by a device with KeyboardOnly IO capabilities
**                  (very likely to be a HID Device).
**                  It is called by a HID Device to inform the remote device when
**                  a key has been entered or erased.
**
** Parameters:      bd_addr - Address of the peer device
**                  type - notification type
**
*******************************************************************************/
#if (BTM_LOCAL_IO_CAPS != BTM_IO_CAP_NONE)
void BTM_SendKeypressNotif(BD_ADDR bd_addr, tBTM_SP_KEY_TYPE type)
{
    /* This API only make sense between PASSKEY_REQ and SP complete */
    if (btm_cb.pairing_state == BTM_PAIR_STATE_KEY_ENTRY)
        btsnd_hcic_send_keypress_notif (bd_addr, type);
}
#endif

#if BTM_OOB_INCLUDED == TRUE
/*******************************************************************************
**
** Function         BTM_IoCapRsp
**
** Description      This function is called in response to BTM_SP_IO_REQ_EVT
**                  When the event data io_req.oob_data is set to BTM_OOB_UNKNOWN
**                  by the tBTM_SP_CALLBACK implementation, this function is
**                  called to provide the actual response
**
** Parameters:      bd_addr - Address of the peer device
**                  io_cap  - The IO capability of local device.
**                  oob     - BTM_OOB_NONE or BTM_OOB_PRESENT.
**                  auth_req- MITM protection required or not.
**
*******************************************************************************/
void BTM_IoCapRsp(BD_ADDR bd_addr, tBTM_IO_CAP io_cap, tBTM_OOB_DATA oob, tBTM_AUTH_REQ auth_req)
{
    BTM_TRACE_EVENT3 ("BTM_IoCapRsp: state: %s  oob: %d io_cap: %d",
                      btm_pair_state_descr(btm_cb.pairing_state), oob, io_cap);

    if ( (btm_cb.pairing_state != BTM_PAIR_STATE_WAIT_LOCAL_IOCAPS)
         ||  (memcmp (btm_cb.pairing_bda, bd_addr, BD_ADDR_LEN) != 0) )
        return;

    if (oob < BTM_OOB_UNKNOWN && io_cap < BTM_IO_CAP_MAX)
    {
        btm_cb.devcb.loc_auth_req   = auth_req;
        btm_cb.devcb.loc_io_caps    = io_cap;

        if (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD)
            auth_req = (BTM_AUTH_DD_BOND | (auth_req&BTM_AUTH_YN_BIT));

        btsnd_hcic_io_cap_req_reply (bd_addr, io_cap, oob, auth_req);
    }
}

/*******************************************************************************
**
** Function         BTM_ReadLocalOobData
**
** Description      This function is called to read the local OOB data from
**                  LM
**
*******************************************************************************/
tBTM_STATUS BTM_ReadLocalOobData(void)
{
    tBTM_STATUS status = BTM_SUCCESS;

    if (btsnd_hcic_read_local_oob_data() == FALSE)
        status = BTM_NO_RESOURCES;

    return status;
}

/*******************************************************************************
**
** Function         BTM_RemoteOobDataReply
**
** Description      This function is called to provide the remote OOB data for
**                  Simple Pairing in response to BTM_SP_RMT_OOB_EVT
**
** Parameters:      bd_addr     - Address of the peer device
**                  c           - simple pairing Hash C.
**                  r           - simple pairing Randomizer  C.
**
*******************************************************************************/
void BTM_RemoteOobDataReply(tBTM_STATUS res, BD_ADDR bd_addr, BT_OCTET16 c, BT_OCTET16 r)
{
    BTM_TRACE_EVENT2 ("BTM_RemoteOobDataReply():  State: %s  res:%d",
                      btm_pair_state_descr(btm_cb.pairing_state), res);

    /* If timeout already expired or has been canceled, ignore the reply */
    if (btm_cb.pairing_state != BTM_PAIR_STATE_WAIT_LOCAL_OOB_RSP)
        return;

    btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);

    if (res != BTM_SUCCESS)
    {
        /* use BTM_PAIR_STATE_WAIT_AUTH_COMPLETE to report authentication failed event */
        btm_cb.acl_disc_reason = HCI_ERR_HOST_REJECT_SECURITY;
        btsnd_hcic_rem_oob_neg_reply (bd_addr);
    }
    else
    {
        btm_cb.acl_disc_reason = HCI_SUCCESS;
        btsnd_hcic_rem_oob_reply (bd_addr, c, r);
    }
}

/*******************************************************************************
**
** Function         BTM_BuildOobData
**
** Description      This function is called to build the OOB data payload to
**                  be sent over OOB (non-Bluetooth) link
**
** Parameters:      p_data  - the location for OOB data
**                  max_len - p_data size.
**                  c       - simple pairing Hash C.
**                  r       - simple pairing Randomizer  C.
**                  name_len- 0, local device name would not be included.
**                            otherwise, the local device name is included for
**                            up to this specified length
**
** Returns          Number of bytes in p_data.
**
*******************************************************************************/
UINT16 BTM_BuildOobData(UINT8 *p_data, UINT16 max_len, BT_OCTET16 c,
                        BT_OCTET16 r, UINT8 name_len)
{
    UINT8   *p = p_data;
    UINT16  len = 0;
    UINT16  delta;
#if BTM_MAX_LOC_BD_NAME_LEN > 0
    UINT16  name_size;
    UINT8   name_type = BTM_EIR_SHORTENED_LOCAL_NAME_TYPE;
#endif

    if (p_data && max_len >= BTM_OOB_MANDATORY_SIZE)
    {
        /* add mandatory part */
        UINT16_TO_STREAM(p, len);
        BDADDR_TO_STREAM(p, btm_cb.devcb.local_addr);

        len = BTM_OOB_MANDATORY_SIZE;
        max_len -= len;

        /* now optional part */

        /* add Hash C */
        delta = BTM_OOB_HASH_C_SIZE + 2;
        if (max_len >= delta)
        {
            *p++ = BTM_OOB_HASH_C_SIZE + 1;
            *p++ = BTM_EIR_OOB_SSP_HASH_C_TYPE;
            ARRAY_TO_STREAM(p, c, BTM_OOB_HASH_C_SIZE);
            len     += delta;
            max_len -= delta;
        }

        /* add Rand R */
        delta = BTM_OOB_RAND_R_SIZE + 2;
        if (max_len >= delta)
        {
            *p++ = BTM_OOB_RAND_R_SIZE + 1;
            *p++ = BTM_EIR_OOB_SSP_RAND_R_TYPE;
            ARRAY_TO_STREAM(p, r, BTM_OOB_RAND_R_SIZE);
            len     += delta;
            max_len -= delta;
        }

        /* add class of device */
        delta = BTM_OOB_COD_SIZE + 2;
        if (max_len >= delta)
        {
            *p++ = BTM_OOB_COD_SIZE + 1;
            *p++ = BTM_EIR_OOB_COD_TYPE;
            DEVCLASS_TO_STREAM(p, btm_cb.devcb.dev_class);
            len     += delta;
            max_len -= delta;
        }
#if BTM_MAX_LOC_BD_NAME_LEN > 0
        name_size = name_len;
        if (name_size > strlen(btm_cb.cfg.bd_name))
        {
            name_type = BTM_EIR_COMPLETE_LOCAL_NAME_TYPE;
            name_size = (UINT16)strlen(btm_cb.cfg.bd_name);
        }
        delta = name_size + 2;
        if (max_len >= delta)
        {
            *p++ = name_size + 1;
            *p++ = name_type;
            ARRAY_TO_STREAM (p, btm_cb.cfg.bd_name, name_size);
            len     += delta;
            max_len -= delta;
        }
#endif
        /* update len */
        p = p_data;
        UINT16_TO_STREAM(p, len);
    }
    return len;
}

/*******************************************************************************
**
** Function         BTM_ReadOobData
**
** Description      This function is called to parse the OOB data payload
**                  received over OOB (non-Bluetooth) link
**
** Parameters:      p_data  - the location for OOB data
**                  eir_tag - The associated EIR tag to read the data.
**                  *p_len(output) - the length of the data with the given tag.
**
** Returns          the beginning of the data with the given tag.
**                  NULL, if the tag is not found.
**
*******************************************************************************/
UINT8 * BTM_ReadOobData(UINT8 *p_data, UINT8 eir_tag, UINT8 *p_len)
{
    UINT8   *p = p_data;
    UINT16  max_len;
    UINT8   len, type;
    UINT8   *p_ret = NULL;
    UINT8   ret_len = 0;

    if (p_data)
    {
        STREAM_TO_UINT16(max_len, p);
        if (max_len >= BTM_OOB_MANDATORY_SIZE)
        {
            if (BTM_EIR_OOB_BD_ADDR_TYPE == eir_tag)
            {
                p_ret = p; /* the location for bd_addr */
                ret_len = BTM_OOB_BD_ADDR_SIZE;
            }
            else
            {
                p += BD_ADDR_LEN;
                max_len -= BTM_OOB_MANDATORY_SIZE;
                /* now the optional data in EIR format */
                while (max_len > 0)
                {
                    len     = *p++; /* tag data len + 1 */
                    type    = *p++;
                    if (eir_tag == type)
                    {
                        p_ret = p;
                        ret_len = len - 1;
                        break;
                    }
                    /* the data size of this tag is len + 1 (tag data len + 2) */
                    if (max_len > len)
                    {
                        max_len -= len;
                        max_len--;
                        len--;
                        p += len;
                    }
                    else
                        max_len = 0;
                }
            }
        }
    }

    if (p_len)
        *p_len = ret_len;

    return p_ret;
}
#endif

/*******************************************************************************
**
** Function         BTM_SetOutService
**
** Description      This function is called to set the service for
**                  outgoing connections.
**
**                  If the profile/application calls BTM_SetSecurityLevel
**                  before initiating a connection, this function does not
**                  need to be called.
**
** Returns          void
**
*******************************************************************************/
void BTM_SetOutService(BD_ADDR bd_addr, UINT8 service_id, UINT32 mx_chan_id)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    tBTM_SEC_SERV_REC *p_serv_rec = &btm_cb.sec_serv_rec[0];
    int i;

    btm_cb.p_out_serv = p_serv_rec;
    p_dev_rec = btm_find_dev (bd_addr);

    for (i = 0; i < BTM_SEC_MAX_SERVICE_RECORDS; i++, p_serv_rec++)
    {
        if ((p_serv_rec->security_flags & BTM_SEC_IN_USE)
            && (p_serv_rec->service_id == service_id)
            && (p_serv_rec->orig_mx_chan_id == mx_chan_id))
        {
            BTM_TRACE_API4("BTM_SetOutService p_out_serv id %d, psm 0x%04x, proto_id %d, chan_id %d",
                           p_serv_rec->service_id, p_serv_rec->psm, p_serv_rec->mx_proto_id, p_serv_rec->orig_mx_chan_id);
            btm_cb.p_out_serv = p_serv_rec;
            if (p_dev_rec)
                p_dev_rec->p_cur_service = p_serv_rec;
            break;
        }
    }
}

/************************************************************************
**              I N T E R N A L     F U N C T I O N S
*************************************************************************/
/*******************************************************************************
**
** Function         btm_sec_check_upgrade
**
** Description      This function is called to check if the existing link key
**                  needs to be upgraded.
**
** Returns          void
**
*******************************************************************************/
static void btm_sec_check_upgrade(tBTM_SEC_DEV_REC  *p_dev_rec, BOOLEAN is_originator)
{
    tBTM_SP_UPGRADE     evt_data;
    UINT16              mtm_check = is_originator ? BTM_SEC_OUT_MITM : BTM_SEC_IN_MITM;

    if (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN)
    {

        BTM_TRACE_DEBUG5 ("btm_sec_check_upgrade id:%d, link_key_typet:%d, rmt_io_caps:%d, chk flags:x%x, flags:x%x",
                          p_dev_rec->p_cur_service->service_id, p_dev_rec->link_key_type, p_dev_rec->rmt_io_caps,
                          mtm_check, p_dev_rec->p_cur_service->security_flags);
        /* Already have a link key to the connected peer. Is the link key secure enough?
        ** Is a link key upgrade even possible?
        */
        if ((p_dev_rec->security_required & mtm_check)                          /* needs MITM */
            && (p_dev_rec->link_key_type == BTM_LKEY_TYPE_UNAUTH_COMB) /* has unauthenticated link key */
            && (p_dev_rec->rmt_io_caps < BTM_IO_CAP_MAX)                           /* a valid peer IO cap */
            && (btm_sec_io_map[p_dev_rec->rmt_io_caps][btm_cb.devcb.loc_io_caps])) /* authenticated link key is possible */
        {
            BTM_TRACE_DEBUG1 ("need upgrade!! sec_flags:0x%x", p_dev_rec->sec_flags);
            /* upgrade is possible: check if the application wants the upgrade.
             * If the application is configured to use a global MITM flag,
             * it probably would not want to upgrade the link key based on the security level database */
            memcpy (evt_data.bd_addr, p_dev_rec->bd_addr, BD_ADDR_LEN);
            evt_data.upgrade = TRUE;
            if (btm_cb.api.p_sp_callback)
                (*btm_cb.api.p_sp_callback) (BTM_SP_UPGRADE_EVT, (tBTM_SP_EVT_DATA *)&evt_data);

            BTM_TRACE_DEBUG1 ("evt_data.upgrade:0x%x", evt_data.upgrade);
            if (evt_data.upgrade)
            {
                /* if the application confirms the upgrade, set the upgrade bit */
                p_dev_rec->sm4 |= BTM_SM4_UPGRADE;

                /* Clear the link key known to go through authentication/pairing again */
                p_dev_rec->sec_flags &= ~(BTM_SEC_LINK_KEY_KNOWN | BTM_SEC_LINK_KEY_AUTHED);
                p_dev_rec->sec_flags &= ~BTM_SEC_AUTHENTICATED;
                BTM_TRACE_DEBUG1 ("sec_flags:0x%x", p_dev_rec->sec_flags);
            }
        }
    }
}

/*******************************************************************************
**
** Function         btm_sec_l2cap_access_req
**
** Description      This function is called by the L2CAP to grant permission to
**                  establish L2CAP connection to or from the peer device.
**
** Parameters:      bd_addr       - Address of the peer device
**                  psm           - L2CAP PSM
**                  is_originator - TRUE if protocol above L2CAP originates
**                                  connection
**                  p_callback    - Pointer to callback function called if
**                                  this function returns PENDING after required
**                                  procedures are complete. MUST NOT BE NULL.
**
** Returns          tBTM_STATUS
**
*******************************************************************************/
#define BTM_SEC_OUT_FLAGS   (BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_OUT_ENCRYPT | BTM_SEC_OUT_AUTHORIZE)
#define BTM_SEC_IN_FLAGS    (BTM_SEC_IN_AUTHENTICATE | BTM_SEC_IN_ENCRYPT | BTM_SEC_IN_AUTHORIZE)

tBTM_STATUS btm_sec_l2cap_access_req (BD_ADDR bd_addr, UINT16 psm, UINT16 handle,
                                      CONNECTION_TYPE conn_type,
                                      tBTM_SEC_CALLBACK *p_callback,
                                      void *p_ref_data)
{
    tBTM_SEC_DEV_REC  *p_dev_rec;
    tBTM_SEC_SERV_REC *p_serv_rec;
    UINT16         security_required;
    UINT16         old_security_required;
    BOOLEAN       old_is_originator;
    tBTM_STATUS   rc = BTM_SUCCESS;
    BOOLEAN       chk_acp_auth_done = FALSE;
    BOOLEAN is_originator;

#if (L2CAP_UCD_INCLUDED == TRUE)
    if (conn_type & CONNECTION_TYPE_ORIG_MASK)
        is_originator = TRUE;
    else
        is_originator = FALSE;

    BTM_TRACE_DEBUG2 ("btm_sec_l2cap_access_req conn_type:0x%x, 0x%x", conn_type, p_ref_data);
#else
    is_originator = conn_type;

    BTM_TRACE_DEBUG2 ("btm_sec_l2cap_access_req is_originator:%d, 0x%x", is_originator, p_ref_data);
#endif

    /* Find or get oldest record */
    p_dev_rec = btm_find_or_alloc_dev (bd_addr);

    p_dev_rec->hci_handle = handle;

    /* Find the service record for the PSM */
    p_serv_rec = btm_sec_find_first_serv (conn_type, psm);

    /* If there is no application registered with this PSM do not allow connection */
    if (!p_serv_rec)
    {
        BTM_TRACE_WARNING1 ("btm_sec_l2cap_access_req()  PSM:%d no application registerd", psm);

        (*p_callback) (bd_addr, p_ref_data, BTM_MODE_UNSUPPORTED);

        return(BTM_MODE_UNSUPPORTED);
    }

    /* SDP connection we will always let through */
    if (BT_PSM_SDP == psm)
    {
        (*p_callback) (bd_addr, p_ref_data, BTM_SUCCESS_NO_SECURITY);

        return(BTM_SUCCESS);
    }
#if (L2CAP_UCD_INCLUDED == TRUE)
    if ( conn_type & CONNECTION_TYPE_CONNLESS_MASK )
    {
        security_required = p_serv_rec->ucd_security_flags;

        rc = BTM_CMD_STARTED;
        if (is_originator)
        {
            if (((security_required & BTM_SEC_OUT_FLAGS) == 0) ||
                ((((security_required & BTM_SEC_OUT_FLAGS) == BTM_SEC_OUT_AUTHENTICATE) && (p_dev_rec->sec_flags & BTM_SEC_AUTHENTICATED))) ||
                ((((security_required & BTM_SEC_OUT_FLAGS) == (BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_OUT_ENCRYPT)) && (p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED))) ||
                ((((security_required & BTM_SEC_OUT_FLAGS) == BTM_SEC_OUT_FLAGS) && (p_dev_rec->sec_flags & BTM_SEC_AUTHORIZED))) )
            {
                rc = BTM_SUCCESS;
            }
        }
        else
        {
            if (((security_required & BTM_SEC_IN_FLAGS) == 0) ||
                ((((security_required & BTM_SEC_IN_FLAGS) == BTM_SEC_IN_AUTHENTICATE) && (p_dev_rec->sec_flags & BTM_SEC_AUTHENTICATED))) ||
                ((((security_required & BTM_SEC_IN_FLAGS) == (BTM_SEC_IN_AUTHENTICATE | BTM_SEC_IN_ENCRYPT)) && (p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED))) ||
                ((((security_required & BTM_SEC_IN_FLAGS) == BTM_SEC_IN_FLAGS) && (p_dev_rec->sec_flags & BTM_SEC_AUTHORIZED))) )
            {
                rc = BTM_SUCCESS;
            }
        }

        if (rc == BTM_SUCCESS)
        {
            if (p_callback)
                (*p_callback) (bd_addr, (void *)p_ref_data, BTM_SUCCESS);

            return(BTM_SUCCESS);
        }
    }
    else
#endif
    {
        security_required = p_serv_rec->security_flags;
    }

    /* there are some devices (moto KRZR) which connects to several services at the same time */
    /* we will process one after another */
    if ( (p_dev_rec->p_callback) || (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE) )
    {
        BTM_TRACE_EVENT2 ("btm_sec_l2cap_access_req() - busy - PSM:%d delayed  state: %s",
                          psm, btm_pair_state_descr(btm_cb.pairing_state));
        rc = BTM_CMD_STARTED;
        if ((BTM_SEC_MODE_SP != btm_cb.security_mode)
            || ((BTM_SEC_MODE_SP == btm_cb.security_mode) && (BTM_SM4_KNOWN == p_dev_rec->sm4))
           )
        {
            BTM_TRACE_EVENT2 ("security_flags:x%x, sec_flags:x%x", security_required, p_dev_rec->sec_flags);
            /* legacy mode - local is legacy or local is lisbon/peer is legacy */
            if (is_originator)
            {
                if (((security_required & BTM_SEC_OUT_FLAGS) == 0) ||
                    ((((security_required & BTM_SEC_OUT_FLAGS) == BTM_SEC_OUT_AUTHENTICATE) && (p_dev_rec->sec_flags & BTM_SEC_AUTHENTICATED))) ||
                    ((((security_required & BTM_SEC_OUT_FLAGS) == (BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_OUT_ENCRYPT)) && (p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED))) ||
                    ((((security_required & BTM_SEC_OUT_FLAGS) == BTM_SEC_OUT_FLAGS) && (p_dev_rec->sec_flags & BTM_SEC_AUTHORIZED))) )
                {
                    rc = BTM_SUCCESS;
                }
            }
            else
            {
                if (((security_required & BTM_SEC_IN_FLAGS) == 0) ||
                    ((((security_required & BTM_SEC_IN_FLAGS) == BTM_SEC_IN_AUTHENTICATE) && (p_dev_rec->sec_flags & BTM_SEC_AUTHENTICATED))) ||
                    ((((security_required & BTM_SEC_IN_FLAGS) == (BTM_SEC_IN_AUTHENTICATE | BTM_SEC_IN_ENCRYPT)) && (p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED))) ||
                    ((((security_required & BTM_SEC_IN_FLAGS) == BTM_SEC_IN_FLAGS) && (p_dev_rec->sec_flags & BTM_SEC_AUTHORIZED))) )
                {
                    rc = BTM_SUCCESS;
                }
            }

            if (rc == BTM_SUCCESS)
            {
                if (p_callback)
                    (*p_callback) (bd_addr, (void *)p_ref_data, BTM_SUCCESS);

                return(BTM_SUCCESS);
            }
        }

        btm_cb.sec_req_pending = TRUE;
        return(BTM_CMD_STARTED);
    }

    /* Save pointer to service record */
    p_dev_rec->p_cur_service = p_serv_rec;


    /* mess /w security_required in btm_sec_l2cap_access_req for Lisbon */
    if (btm_cb.security_mode == BTM_SEC_MODE_SP)
    {
        if (is_originator)
        {
            if (BTM_SEC_IS_SM4(p_dev_rec->sm4))
            {
                /* SM4 to SM4 -> always authenticate & encrypt */
                security_required |= (BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_OUT_ENCRYPT);
            }
            else
            {
                if ( !(BTM_SM4_KNOWN & p_dev_rec->sm4))
                {
                    BTM_TRACE_DEBUG1 ("remote features unknown!!sec_flags:0x%x", p_dev_rec->sec_flags);
                    /* the remote features are not known yet */
                    p_dev_rec->sm4          |= BTM_SM4_REQ_PEND;

                    return(BTM_CMD_STARTED);
                }
            }
        }
        else
        {
            /* responder */
            if (BTM_SEC_IS_SM4(p_dev_rec->sm4))
            {
                /* SM4 to SM4: the acceptor needs to make sure the authentication is already done */
                chk_acp_auth_done = TRUE;
                /* SM4 to SM4 -> always authenticate & encrypt */
                security_required |= (BTM_SEC_IN_AUTHENTICATE | BTM_SEC_IN_ENCRYPT);
            }
            else
            {
                if ( !(BTM_SM4_KNOWN & p_dev_rec->sm4))
                {
                    BTM_TRACE_DEBUG1 ("(rsp) remote features unknown!!sec_flags:0x%x", p_dev_rec->sec_flags);
                    /* the remote features are not known yet */
                    p_dev_rec->sm4          |= BTM_SM4_REQ_PEND;

                    return(BTM_CMD_STARTED);
                }
            }
        }
    }

    BTM_TRACE_DEBUG4 ("btm_sec_l2cap_access_req()  sm4:0x%x, sec_flags:0x%x, security_required:0x%x chk:%d",
                      p_dev_rec->sm4, p_dev_rec->sec_flags, security_required, chk_acp_auth_done);

    old_security_required        = p_dev_rec->security_required;
    old_is_originator            = p_dev_rec->is_originator;
    p_dev_rec->security_required = security_required;
    p_dev_rec->p_ref_data        = p_ref_data;
    p_dev_rec->is_originator     = is_originator;

#if (L2CAP_UCD_INCLUDED == TRUE)
    if ( conn_type & CONNECTION_TYPE_CONNLESS_MASK )
        p_dev_rec->is_ucd = TRUE;
    else
        p_dev_rec->is_ucd = FALSE;
#endif

    /* If there are multiple service records used through the same PSM */
    /* leave security decision for the multiplexor on the top */
#if (L2CAP_UCD_INCLUDED == TRUE)
    if (((btm_sec_find_next_serv (p_serv_rec)) != NULL)
        &&(!( conn_type & CONNECTION_TYPE_CONNLESS_MASK ))) /* if not UCD */
#else
    if ((btm_sec_find_next_serv (p_serv_rec)) != NULL)
#endif
    {
        BTM_TRACE_DEBUG2 ("no next_serv sm4:0x%x, chk:%d", p_dev_rec->sm4, chk_acp_auth_done);
        if (!BTM_SEC_IS_SM4(p_dev_rec->sm4))
        {
            BTM_TRACE_EVENT1 ("Security Manager: l2cap_access_req PSM:%d postponed for multiplexer", psm);
            /* pre-Lisbon: restore the old settings */
            p_dev_rec->security_required = old_security_required;
            p_dev_rec->is_originator     = old_is_originator;

            (*p_callback) (bd_addr, p_ref_data, BTM_SUCCESS);

            return(BTM_SUCCESS);
        }
    }

    /* if the originator is using dynamic PSM in legacy mode, do not start any security process now.
     * The layer above L2CAP needs to carry out the security requirement after L2CAP connect response is received*/
    if (is_originator && (btm_cb.security_mode != BTM_SEC_MODE_SP || !BTM_SEC_IS_SM4(p_dev_rec->sm4)) && (psm >= 0x1001))
    {
        BTM_TRACE_EVENT1 ("dynamic PSM:0x%x in legacy mode - postponed for upper layer", psm);
        /* restore the old settings */
        p_dev_rec->security_required = old_security_required;
        p_dev_rec->is_originator     = old_is_originator;

        (*p_callback) (bd_addr, p_ref_data, BTM_SUCCESS);

        return(BTM_SUCCESS);
    }

    if (chk_acp_auth_done)
    {
        BTM_TRACE_DEBUG2 ("(SM4 to SM4) btm_sec_l2cap_access_req rspd. authenticated: x%x, enc: x%x",
                          (p_dev_rec->sec_flags & BTM_SEC_AUTHENTICATED), (p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED));
        /* SM4, but we do not know for sure which level of security we need.
         * as long as we have a link key, it's OK */
        if ((0 == (p_dev_rec->sec_flags & BTM_SEC_AUTHENTICATED))
            ||(0 == (p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED)))
        {
            rc = BTM_DELAY_CHECK;
            /*
            2046 may report HCI_Encryption_Change and L2C Connection Request out of sequence
            because of data path issues. Delay this disconnect a little bit
            */
            BTM_TRACE_ERROR0 ("peer should have initiated security process by now (SM4 to SM4)");
            p_dev_rec->p_callback        = p_callback;
            p_dev_rec->sec_state         = BTM_SEC_STATE_DELAY_FOR_ENC;
            (*p_callback) (bd_addr, p_ref_data, rc);

            return(BTM_SUCCESS);
        }
    }

    p_dev_rec->p_callback        = p_callback;

    /* Although authentication and encryption are per connection */
    /* authorization is per access request.  For example when serial connection */
    /* is up and authorized and client requests to read file (access to other */
    /* scn, we need to request user's permission again. */
    p_dev_rec->sec_flags &= ~BTM_SEC_AUTHORIZED;

    if (BTM_SEC_IS_SM4(p_dev_rec->sm4))
    {
        /* If we already have a link key to the connected peer, is the link key secure enough ? */
        btm_sec_check_upgrade(p_dev_rec, is_originator);
    }

    BTM_TRACE_EVENT6 ("Security Manager: l2cap_access_req PSM:%d Handle:%d State:%d Flags:0x%x Required:0x%x Service ID:%d",
                      psm, handle, p_dev_rec->sec_state, p_dev_rec->sec_flags, p_dev_rec->security_required, p_dev_rec->p_cur_service->service_id);

    if ((rc = btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED)
    {
        p_dev_rec->p_callback = NULL;
        (*p_callback) (bd_addr, p_dev_rec->p_ref_data, (UINT8)rc);
    }

    return(rc);
}

/*******************************************************************************
**
** Function         btm_sec_mx_access_request
**
** Description      This function is called by all Multiplexing Protocols during
**                  establishing connection to or from peer device to grant
**                  permission to establish application connection.
**
** Parameters:      bd_addr       - Address of the peer device
**                  psm           - L2CAP PSM
**                  is_originator - TRUE if protocol above L2CAP originates
**                                  connection
**                  mx_proto_id   - protocol ID of the multiplexer
**                  mx_chan_id    - multiplexer channel to reach application
**                  p_callback    - Pointer to callback function called if
**                                  this function returns PENDING after required
**                                  procedures are completed
**                  p_ref_data    - Pointer to any reference data needed by the
**                                  the callback function.
**
** Returns          BTM_CMD_STARTED
**
*******************************************************************************/
tBTM_STATUS btm_sec_mx_access_request (BD_ADDR bd_addr, UINT16 psm, BOOLEAN is_originator,
                                       UINT32 mx_proto_id, UINT32 mx_chan_id,
                                       tBTM_SEC_CALLBACK *p_callback, void *p_ref_data)

{
    tBTM_SEC_DEV_REC  *p_dev_rec;
    tBTM_SEC_SERV_REC *p_serv_rec;
    tBTM_STATUS        rc;

    BTM_TRACE_DEBUG1 ("btm_sec_mx_access_request is_originator:%d", is_originator);
    /* Find or get oldest record */
    p_dev_rec = btm_find_or_alloc_dev (bd_addr);

    /* Find the service record for the PSM */
    p_serv_rec = btm_sec_find_mx_serv (is_originator, psm, mx_proto_id, mx_chan_id);

    /* If there is no application registered with this PSM do not allow connection */
    if (!p_serv_rec)
    {
        if (p_callback)
            (*p_callback) (bd_addr, p_ref_data, BTM_MODE_UNSUPPORTED);

        BTM_TRACE_ERROR3 ("Security Manager: MX service not found PSM:%d Proto:%d SCN:%d",
                          psm, mx_proto_id, mx_chan_id);
        return BTM_NO_RESOURCES;
    }

    /* there are some devices (moto phone) which connects to several services at the same time */
    /* we will process one after another */
    if ( (p_dev_rec->p_callback) || (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE) )
    {
        BTM_TRACE_EVENT4 ("btm_sec_mx_access_request service PSM:%d Proto:%d SCN:%d delayed  state: %s",
                          psm, mx_proto_id, mx_chan_id, btm_pair_state_descr(btm_cb.pairing_state));

        btm_sec_queue_mx_request (bd_addr, psm,  is_originator, mx_proto_id, mx_chan_id, p_callback, p_ref_data);
        return BTM_CMD_STARTED;
    }

    p_dev_rec->p_cur_service     = p_serv_rec;
    p_dev_rec->security_required = p_serv_rec->security_flags;

    if (BTM_SEC_MODE_SP == btm_cb.security_mode)
    {
        if (BTM_SEC_IS_SM4(p_dev_rec->sm4))
        {
            /* If we already have a link key, check if that link key is good enough */
            btm_sec_check_upgrade(p_dev_rec, is_originator);
        }
    }

    p_dev_rec->is_originator     = is_originator;
    p_dev_rec->p_callback        = p_callback;
    p_dev_rec->p_ref_data        = p_ref_data;

    /* Although authentication and encryption are per connection */
    /* authorization is per access request.  For example when serial connection */
    /* is up and authorized and client requests to read file (access to other */
    /* scn, we need to request user's permission again. */
    p_dev_rec->sec_flags &= ~(BTM_SEC_AUTHORIZED);

    BTM_TRACE_EVENT6 ("Security Manager: mx_access_req proto_id:%d chan_id:%d State:%d Flags:0x%x Required:0x%x Service ID:%d",
                      mx_proto_id, mx_chan_id, p_dev_rec->sec_state, p_dev_rec->sec_flags, p_dev_rec->security_required, p_dev_rec->p_cur_service->service_id);

    if ((rc = btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED)
    {
        if (p_callback)
        {
            p_dev_rec->p_callback = NULL;

            (*p_callback) (bd_addr, p_ref_data, (UINT8)rc);
        }
    }

    return rc;
}

/*******************************************************************************
**
** Function         btm_sec_conn_req
**
** Description      This function is when the peer device is requesting
**                  connection
**
** Returns          void
**
*******************************************************************************/
void btm_sec_conn_req (UINT8 *bda, UINT8 *dc)
{
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev (bda);

    /* Some device may request a connection before we are done with the HCI_Reset sequence */
    if (btm_cb.devcb.state != BTM_DEV_STATE_READY)
    {
        BTM_TRACE_EVENT0 ("Security Manager: connect request when device not ready");
        btsnd_hcic_reject_conn (bda, HCI_ERR_HOST_REJECT_DEVICE);
        return;
    }

    /* Security guys wants us not to allow connection from not paired devices */

    /* Check if connection is allowed for only paired devices */
    if (btm_cb.connect_only_paired)
    {
        if (!p_dev_rec || !(p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_AUTHED))
        {
            BTM_TRACE_EVENT0 ("Security Manager: connect request from non-paired device");
            btsnd_hcic_reject_conn (bda, HCI_ERR_HOST_REJECT_DEVICE);
            return;
        }
    }

#if BTM_ALLOW_CONN_IF_NONDISCOVER == FALSE
    /* If non-discoverable, only allow known devices to connect */
    if (btm_cb.btm_inq_vars.discoverable_mode == BTM_NON_DISCOVERABLE)
    {
        if (!p_dev_rec)
        {
            BTM_TRACE_EVENT0 ("Security Manager: connect request from not paired device");
            btsnd_hcic_reject_conn (bda, HCI_ERR_HOST_REJECT_DEVICE);
            return;
        }
    }
#endif

    /* Host can be registered to verify comming BDA or DC */
    if (btm_cb.p_conn_filter_cb)
    {
        if (!(* btm_cb.p_conn_filter_cb) (bda, dc))
        {
            BTM_TRACE_EVENT0 ("Security Manager: connect request did not pass filter");

            /* incomming call did not pass connection filters.  Reject */
            btsnd_hcic_reject_conn (bda, HCI_ERR_HOST_REJECT_DEVICE);
            return;
        }
    }

    if ((btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
        &&(btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD)
        &&(!memcmp (btm_cb.pairing_bda, bda, BD_ADDR_LEN)))
    {
        BTM_TRACE_EVENT0 ("Security Manager: reject connect request from bonding device");

        /* incoming connection from bonding device is rejected */
        btm_cb.pairing_flags |= BTM_PAIR_FLAGS_REJECTED_CONNECT;
        btsnd_hcic_reject_conn (bda, HCI_ERR_HOST_REJECT_DEVICE);
        return;
    }

    /* Host is not interested or approved connection.  Save BDA and DC and */
    /* pass request to L2CAP */
    memcpy (btm_cb.connecting_bda, bda, BD_ADDR_LEN);
    memcpy (btm_cb.connecting_dc,  dc,  DEV_CLASS_LEN);

    if (l2c_link_hci_conn_req (bda))
    {
        if (!p_dev_rec)
        {
            /* accept the connection -> allocate a device record */
            p_dev_rec = btm_sec_alloc_dev (bda);
        }
        if (p_dev_rec)
        {
            p_dev_rec->sm4 |= BTM_SM4_CONN_PEND;
        }
    }
}

/*******************************************************************************
**
** Function         btm_sec_bond_cancel_complete
**
** Description      This function is called to report bond cancel complete
**                  event.
**
** Returns          void
**
*******************************************************************************/
static void btm_sec_bond_cancel_complete (void)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    if ((btm_cb.pairing_flags & BTM_PAIR_FLAGS_DISC_WHEN_DONE) ||
        (BTM_PAIR_STATE_WAIT_LOCAL_PIN == btm_cb.pairing_state &&
         BTM_PAIR_FLAGS_WE_STARTED_DD & btm_cb.pairing_flags))
    {
        /* for dedicated bonding in legacy mode, authentication happens at "link level"
         * btm_sec_connected is called with failed status.
         * In theory, the code that handles is_pairing_device/TRUE should clean out security related code.
         * However, this function may clean out the security related flags and btm_sec_connected would not know
         * this function also needs to do proper clean up.
         */
        if ((p_dev_rec = btm_find_dev (btm_cb.pairing_bda)) != NULL)
            p_dev_rec->security_required = BTM_SEC_NONE;
        btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);

        /* Notify application that the cancel succeeded */
        if (btm_cb.api.p_bond_cancel_cmpl_callback)
            btm_cb.api.p_bond_cancel_cmpl_callback(BTM_SUCCESS);
    }
}

/*******************************************************************************
**
** Function         btm_create_conn_cancel_complete
**
** Description      This function is called when the command complete message
**                  is received from the HCI for the create connection cancel
**                  command.
**
** Returns          void
**
*******************************************************************************/
void btm_create_conn_cancel_complete (UINT8 *p)
{
    UINT8       status;

    STREAM_TO_UINT8 (status, p);
    BTM_TRACE_EVENT2 ("btm_create_conn_cancel_complete(): in State: %s  status:%d",
                      btm_pair_state_descr(btm_cb.pairing_state), status);

    /* if the create conn cancel cmd was issued by the bond cancel,
    ** the application needs to be notified that bond cancel succeeded
    */
    switch (status)
    {
        case HCI_SUCCESS:
            btm_sec_bond_cancel_complete();
            break;
        case HCI_ERR_CONNECTION_EXISTS:
        case HCI_ERR_NO_CONNECTION:
        default:
            /* Notify application of the error */
            if (btm_cb.api.p_bond_cancel_cmpl_callback)
                btm_cb.api.p_bond_cancel_cmpl_callback(BTM_ERR_PROCESSING);
            break;
    }
}

/*******************************************************************************
**
** Function         btm_sec_check_pending_reqs
**
** Description      This function is called at the end of the security procedure
**                  to let L2CAP and RFCOMM know to re-submit any pending requests
**
** Returns          void
**
*******************************************************************************/
void btm_sec_check_pending_reqs (void)
{
    tBTM_SEC_QUEUE_ENTRY    *p_e;
    BUFFER_Q                bq;

    if (btm_cb.pairing_state == BTM_PAIR_STATE_IDLE)
    {
        /* First, resubmit L2CAP requests */
        if (btm_cb.sec_req_pending)
        {
            btm_cb.sec_req_pending = FALSE;
            l2cu_resubmit_pending_sec_req (NULL);
        }

        /* Now, re-submit anything in the mux queue */
        bq = btm_cb.sec_pending_q;

        GKI_init_q (&btm_cb.sec_pending_q);

        while ((p_e = (tBTM_SEC_QUEUE_ENTRY *)GKI_dequeue (&bq)) != NULL)
        {
            /* Check that the ACL is still up before starting security procedures */
            if (btm_bda_to_acl(p_e->bd_addr) != NULL)
            {
                BTM_TRACE_EVENT4 ("btm_sec_check_pending_reqs() submitting  PSM: 0x%04x  Is_Orig: %u  mx_proto_id: %u  mx_chan_id: %u",
                                  p_e->psm, p_e->is_orig, p_e->mx_proto_id, p_e->mx_chan_id);

                btm_sec_mx_access_request (p_e->bd_addr, p_e->psm, p_e->is_orig,
                                           p_e->mx_proto_id, p_e->mx_chan_id,
                                           p_e->p_callback, p_e->p_ref_data);
            }

            GKI_freebuf (p_e);
        }
    }
}

/*******************************************************************************
**
** Function         btm_sec_init
**
** Description      This function is on the SEC startup
**
** Returns          void
**
*******************************************************************************/
void btm_sec_init (UINT8 sec_mode)
{
#if 0  /* cleared in btm_init; put back in if calling from anywhere else! */
    int i;

    memset (btm_cb.sec_serv_rec, 0, sizeof (btm_cb.sec_serv_rec));
    memset (btm_cb.sec_dev_rec, 0, sizeof (btm_cb.sec_dev_rec));
    memset (&btm_cb.pairing_tle, 0, sizeof(TIMER_LIST_ENT));

#endif
    btm_cb.security_mode = sec_mode;
    memset (btm_cb.pairing_bda, 0xff, BD_ADDR_LEN);
    btm_cb.max_collision_delay = BTM_SEC_MAX_COLLISION_DELAY;
}

/*******************************************************************************
**
** Function         btm_sec_device_down
**
** Description      This function should be called when device is disabled or
**                  turned off
**
** Returns          void
**
*******************************************************************************/
void btm_sec_device_down (void)
{
    BTM_TRACE_EVENT1 ("btm_sec_device_down()  State: %s", btm_pair_state_descr(btm_cb.pairing_state));

    btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
}

/*******************************************************************************
**
** Function         btm_sec_dev_reset
**
** Description      This function should be called after device reset
**
** Returns          void
**
*******************************************************************************/
void btm_sec_dev_reset (void)
{
#if (BTM_PRE_LISBON_INCLUDED == TRUE)
    if (btm_cb.security_mode == BTM_SEC_MODE_LINK)
    {
        btsnd_hcic_write_auth_enable (TRUE);
        btsnd_hcic_write_encr_mode (HCI_ENCRYPT_MODE_POINT_TO_POINT);
    }
#endif
#if (BTM_PRE_LISBON_INCLUDED == TRUE)
    else
#endif
        /* this function is only called from btm_read_local_features_complete()
         * right now. */
        if (HCI_SIMPLE_PAIRING_SUPPORTED(btm_cb.devcb.local_features))
    {
        btsnd_hcic_write_simple_pairing_mode(HCI_SP_MODE_ENABLED);
#if BLE_INCLUDED == TRUE
        btsnd_hcic_set_event_mask(LOCAL_BR_EDR_CONTROLLER_ID,
                                  (UINT8 *)HCI_DUMO_EVENT_MASK_EXT);
#else
        btsnd_hcic_set_event_mask(LOCAL_BR_EDR_CONTROLLER_ID,
                                  (UINT8 *)HCI_LISBON_EVENT_MASK_EXT);
#endif
        /* set the default IO capabilities */
        btm_cb.devcb.loc_io_caps = BTM_LOCAL_IO_CAPS;
        /* add mx service to use no security */
#if (RFCOMM_INCLUDED == TRUE)
        BTM_SetSecurityLevel(FALSE, "RFC_MUX", BTM_SEC_SERVICE_RFC_MUX,
                             BTM_SEC_NONE, BT_PSM_RFCOMM, BTM_SEC_PROTO_RFCOMM, 0);
#endif
    }
    else
    {
        btm_cb.security_mode = BTM_SEC_MODE_SERVICE;
    }

    BTM_TRACE_DEBUG1 ("btm_sec_dev_reset sec mode: %d", btm_cb.security_mode);
}

/*******************************************************************************
**
** Function         btm_sec_abort_access_req
**
** Description      This function is called by the L2CAP or RFCOMM to abort
**                  the pending operation.
**
** Parameters:      bd_addr       - Address of the peer device
**
** Returns          void
**
*******************************************************************************/
void btm_sec_abort_access_req (BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev (bd_addr);

    if (!p_dev_rec)
        return;

    if (btm_cb.api.p_abort_callback)
        (*btm_cb.api.p_abort_callback)(bd_addr, p_dev_rec->dev_class, p_dev_rec->sec_bd_name);

    if ((p_dev_rec->sec_state != BTM_SEC_STATE_AUTHORIZING)
        && (p_dev_rec->sec_state != BTM_SEC_STATE_AUTHENTICATING))
        return;

    p_dev_rec->sec_state  = BTM_SEC_STATE_IDLE;
    p_dev_rec->p_callback = NULL;
}

/*******************************************************************************
**
** Function         btm_sec_dd_create_conn
**
** Description      This function is called to create the ACL connection for
**                  the dedicated boding process
**
** Returns          void
**
*******************************************************************************/
static tBTM_STATUS btm_sec_dd_create_conn (tBTM_SEC_DEV_REC *p_dev_rec)
{
    tL2C_LCB         *p_lcb;

    /* Make sure an L2cap link control block is available */
    if ((p_lcb = l2cu_allocate_lcb (p_dev_rec->bd_addr, TRUE)) == NULL)
    {
        BTM_TRACE_WARNING6 ("Security Manager: failed allocate LCB [%02x%02x%02x%02x%02x%02x]",
                            p_dev_rec->bd_addr[0], p_dev_rec->bd_addr[1], p_dev_rec->bd_addr[2],
                            p_dev_rec->bd_addr[3], p_dev_rec->bd_addr[4], p_dev_rec->bd_addr[5]);

        return(BTM_NO_RESOURCES);
    }

    /* set up the control block to indicated dedicated bonding */
    btm_cb.pairing_flags |= BTM_PAIR_FLAGS_DISC_WHEN_DONE;

    if (l2cu_create_conn(p_lcb) == FALSE)
    {
        BTM_TRACE_WARNING6 ("Security Manager: failed create  [%02x%02x%02x%02x%02x%02x]",
                            p_dev_rec->bd_addr[0], p_dev_rec->bd_addr[1], p_dev_rec->bd_addr[2],
                            p_dev_rec->bd_addr[3], p_dev_rec->bd_addr[4], p_dev_rec->bd_addr[5]);

        l2cu_release_lcb(p_lcb);
        return(BTM_NO_RESOURCES);
    }

#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
    btm_acl_update_busy_level (BTM_BLI_PAGE_EVT);
#endif

    BTM_TRACE_DEBUG6 ("Security Manager: btm_sec_dd_create_conn [%02x%02x%02x%02x%02x%02x]",
                      p_dev_rec->bd_addr[0], p_dev_rec->bd_addr[1], p_dev_rec->bd_addr[2],
                      p_dev_rec->bd_addr[3], p_dev_rec->bd_addr[4], p_dev_rec->bd_addr[5]);

    btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_PIN_REQ);

    return(BTM_CMD_STARTED);
}

/*******************************************************************************
**
** Function         btm_sec_rmt_name_request_complete
**
** Description      This function is called when remote name was obtained from
**                  the peer device
**
** Returns          void
**
*******************************************************************************/
void btm_sec_rmt_name_request_complete (UINT8 *p_bd_addr, UINT8 *p_bd_name, UINT8 status)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    int              i;
    DEV_CLASS        dev_class;
    UINT8            old_sec_state;

    BTM_TRACE_EVENT0 ("btm_sec_rmt_name_request_complete");
    if (((p_bd_addr == NULL) && !BTM_ACL_IS_CONNECTED(btm_cb.connecting_bda))
        || ((p_bd_addr != NULL) && !BTM_ACL_IS_CONNECTED(p_bd_addr)))
    {
        btm_acl_resubmit_page();
    }

    /* If remote name request failed, p_bd_addr is null and we need to search */
    /* based on state assuming that we are doing 1 at a time */
    if (p_bd_addr)
        p_dev_rec = btm_find_dev (p_bd_addr);
    else
    {
        p_dev_rec = &btm_cb.sec_dev_rec[0];

        for (i = 0; i < BTM_SEC_MAX_DEVICE_RECORDS; i++, p_dev_rec++)
        {
            if ((p_dev_rec->sec_flags & BTM_SEC_IN_USE)
                && (p_dev_rec->sec_state == BTM_SEC_STATE_GETTING_NAME))
            {
                p_bd_addr = p_dev_rec->bd_addr;
                break;
            }
        }

        if (i == BTM_SEC_MAX_DEVICE_RECORDS)
            p_dev_rec = NULL;
    }


    /* Commenting out trace due to obf/compilation problems.
    */
#if (BT_USE_TRACES == TRUE)
    if (!p_bd_name)
        p_bd_name = (UINT8 *)"";

    if (p_dev_rec)
    {
        BTM_TRACE_EVENT5 ("Security Manager: rmt_name_complete PairState: %s  RemName: %s  status: %d State:%d  p_dev_rec: 0x%08x ",
                          btm_pair_state_descr (btm_cb.pairing_state), p_bd_name,
                          status, p_dev_rec->sec_state, p_dev_rec);
    }
    else
    {
        BTM_TRACE_EVENT3 ("Security Manager: rmt_name_complete PairState: %s  RemName: %s  status: %d",
                          btm_pair_state_descr (btm_cb.pairing_state), p_bd_name,
                          status);
    }
#endif

    if (p_dev_rec)
    {
        old_sec_state = p_dev_rec->sec_state;
        if (status == HCI_SUCCESS)
        {
            BCM_STRNCPY_S ((char *)p_dev_rec->sec_bd_name, sizeof (p_dev_rec->sec_bd_name), (char *)p_bd_name, BTM_MAX_REM_BD_NAME_LEN);
            p_dev_rec->sec_flags |= BTM_SEC_NAME_KNOWN;
            BTM_TRACE_EVENT1 ("setting BTM_SEC_NAME_KNOWN sec_flags:0x%x", p_dev_rec->sec_flags);
        }
        else
        {
            /* Notify all clients waiting for name to be resolved even if it failed so clients can continue */
            p_dev_rec->sec_bd_name[0] = 0;
        }

        if (p_dev_rec->sec_state == BTM_SEC_STATE_GETTING_NAME)
            p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;

        /* Notify all clients waiting for name to be resolved */
        for (i = 0;i < BTM_SEC_MAX_RMT_NAME_CALLBACKS; i++)
        {
            if (btm_cb.p_rmt_name_callback[i])
                (*btm_cb.p_rmt_name_callback[i])(p_bd_addr, p_dev_rec->dev_class,
                                                 p_dev_rec->sec_bd_name);
        }
    }
    else
    {
        dev_class[0] = 0;
        dev_class[1] = 0;
        dev_class[2] = 0;

        /* Notify all clients waiting for name to be resolved even if not found so clients can continue */
        for (i = 0;i < BTM_SEC_MAX_RMT_NAME_CALLBACKS; i++)
        {
            if (btm_cb.p_rmt_name_callback[i])
                (*btm_cb.p_rmt_name_callback[i])(p_bd_addr, dev_class, (UINT8 *)"");
        }

        return;
    }

    /* If we were delaying asking UI for a PIN because name was not resolved, ask now */
    if ( (btm_cb.pairing_state == BTM_PAIR_STATE_WAIT_LOCAL_PIN) && p_bd_addr
         &&  (memcmp (btm_cb.pairing_bda, p_bd_addr, BD_ADDR_LEN) == 0) )
    {
        BTM_TRACE_EVENT2 ("btm_sec_rmt_name_request_complete() delayed pin now being requested flags:0x%x, (p_pin_callback=0x%p)", btm_cb.pairing_flags, btm_cb.api.p_pin_callback);

        if (((btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD) == 0) &&
            ((btm_cb.pairing_flags & BTM_PAIR_FLAGS_PIN_REQD) == 0) &&
            btm_cb.api.p_pin_callback)
        {
            BTM_TRACE_EVENT0 ("btm_sec_rmt_name_request_complete() calling pin_callback");
            btm_cb.pairing_flags |= BTM_PAIR_FLAGS_PIN_REQD;
            (*btm_cb.api.p_pin_callback) (p_dev_rec->bd_addr, p_dev_rec->dev_class, p_bd_name);
        }

        /* Set the same state again to force the timer to be restarted */
        btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_LOCAL_PIN);
        return;
    }

    /* Check if we were delaying bonding because name was not resolved */
    if ( btm_cb.pairing_state == BTM_PAIR_STATE_GET_REM_NAME)
    {
        if (p_bd_addr && memcmp (btm_cb.pairing_bda, p_bd_addr, BD_ADDR_LEN) == 0)
        {
            BTM_TRACE_EVENT2 ("btm_sec_rmt_name_request_complete() continue bonding sm4: 0x%04x, status:0x%x", p_dev_rec->sm4, status);
            if (status != HCI_SUCCESS)
            {
                btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);

                (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,  p_dev_rec->dev_class,
                                                        p_dev_rec->sec_bd_name, status);
                return;
            }

            /* if peer is very old legacy devices, HCI_RMT_HOST_SUP_FEAT_NOTIFY_EVT is not reported */
            if (BTM_SEC_IS_SM4_UNKNOWN(p_dev_rec->sm4))
            {
                /* set the KNOWN flag only if BTM_PAIR_FLAGS_REJECTED_CONNECT is not set.
                 * If it is set, there may be a race condition */
				BTM_TRACE_EVENT1 ("btm_sec_rmt_name_request_complete  IS_SM4_UNKNOWN Flags:0x%04x", btm_cb.pairing_flags);
                if ((btm_cb.pairing_flags & BTM_PAIR_FLAGS_REJECTED_CONNECT) == 0)
                {
                    p_dev_rec->sm4 |= BTM_SM4_KNOWN;
                }
            }

            /* BT 2.1 or carkit, bring up the connection to force the peer to request PIN.
            ** Else prefetch (btm_sec_check_prefetch_pin will do the prefetching if needed)
            */
            if ((p_dev_rec->sm4 != BTM_SM4_KNOWN) || !btm_sec_check_prefetch_pin(p_dev_rec))
            {
                /* if we rejected incoming connection request, we have to wait HCI_Connection_Complete event */
                /*  before originating  */
                if (btm_cb.pairing_flags & BTM_PAIR_FLAGS_REJECTED_CONNECT)
                {
                    BTM_TRACE_WARNING0 ("btm_sec_rmt_name_request_complete: waiting HCI_Connection_Complete after rejecting connection");
                }
                /* Both we and the peer are 2.1 - continue to create connection */
                else if (btm_sec_dd_create_conn(p_dev_rec) != BTM_CMD_STARTED)
                {
                    BTM_TRACE_WARNING0 ("btm_sec_rmt_name_request_complete: failed to start connection");

                    btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);

                    (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,  p_dev_rec->dev_class,
                                                            p_dev_rec->sec_bd_name, HCI_ERR_MEMORY_FULL);
                }
            }
            return;
        }
        else
        {
            BTM_TRACE_WARNING0 ("btm_sec_rmt_name_request_complete: wrong BDA, retry with pairing BDA");

            BTM_ReadRemoteDeviceName (btm_cb.pairing_bda, NULL);
            return;
        }
    }

    /* check if we were delaying link_key_callback because name was not resolved */
    if (p_dev_rec->link_key_not_sent)
    {
        /* If HCI connection complete has not arrived, wait for it */
        if (p_dev_rec->hci_handle == BTM_SEC_INVALID_HANDLE)
            return;

        p_dev_rec->link_key_not_sent = FALSE;
        btm_send_link_key_notif(p_dev_rec);

        /* If its not us who perform authentication, we should tell stackserver */
        /* that some authentication has been completed                          */
        /* This is required when different entities receive link notification and auth complete */
        if (!(p_dev_rec->security_required & BTM_SEC_OUT_AUTHENTICATE))
        {
            if (btm_cb.api.p_auth_complete_callback)
                (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,
                                                        p_dev_rec->dev_class,
                                                        p_dev_rec->sec_bd_name, HCI_SUCCESS);

        }
    }

    /* If this is a bonding procedure can disconnect the link now */
    if ((btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD)
        && (p_dev_rec->sec_flags & BTM_SEC_AUTHENTICATED))
    {
        BTM_TRACE_WARNING0 ("btm_sec_rmt_name_request_complete (none/ce)");
        p_dev_rec->security_required &= ~(BTM_SEC_OUT_AUTHENTICATE);
        l2cu_start_post_bond_timer(p_dev_rec->hci_handle);
        return;
    }

    if (old_sec_state != BTM_SEC_STATE_GETTING_NAME)
        return;

    /* If get name failed, notify the waiting layer */
    if (status != HCI_SUCCESS)
    {
        btm_sec_dev_rec_cback_event  (p_dev_rec, BTM_ERR_PROCESSING);
        return;
    }

    if (p_dev_rec->sm4 & BTM_SM4_REQ_PEND)
    {
        BTM_TRACE_EVENT0 ("waiting for remote features!!");
        return;
    }

    /* Remote Name succeeded, execute the next security procedure, if any */
    status = (UINT8)btm_sec_execute_procedure (p_dev_rec);

    /* If result is pending reply from the user or from the device is pending */
    if (status == BTM_CMD_STARTED)
        return;

    /* There is no next procedure or start of procedure failed, notify the waiting layer */
    btm_sec_dev_rec_cback_event  (p_dev_rec, status);
}

/*******************************************************************************
**
** Function         btm_sec_rmt_host_support_feat_evt
**
** Description      This function is called when the
**                  HCI_RMT_HOST_SUP_FEAT_NOTIFY_EVT is received
**
** Returns          void
**
*******************************************************************************/
void btm_sec_rmt_host_support_feat_evt (UINT8 *p)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    BD_ADDR         bd_addr;        /* peer address */
    BD_FEATURES     features;

    STREAM_TO_BDADDR (bd_addr, p);
    p_dev_rec = btm_find_or_alloc_dev (bd_addr);

    BTM_TRACE_EVENT2 ("btm_sec_rmt_host_support_feat_evt  sm4: 0x%x  p[0]: 0x%x", p_dev_rec->sm4, p[0]);

    if (BTM_SEC_IS_SM4_UNKNOWN(p_dev_rec->sm4))
    {
        p_dev_rec->sm4 = BTM_SM4_KNOWN;
        STREAM_TO_ARRAY(features, p, BD_FEATURES_LEN);
        if (HCI_SSP_HOST_SUPPORTED(features))
        {
            p_dev_rec->sm4 = BTM_SM4_TRUE;
        }
        BTM_TRACE_EVENT2 ("btm_sec_rmt_host_support_feat_evt sm4: 0x%x features[0]: 0x%x", p_dev_rec->sm4, features[0]);
    }
}

/*******************************************************************************
**
** Function         btm_io_capabilities_req
**
** Description      This function is called when LM request for the IO
**                  capability of the local device and
**                  if the OOB data is present for the device in the event
**
** Returns          void
**
*******************************************************************************/
void btm_io_capabilities_req (UINT8 *p)
{
    tBTM_SP_IO_REQ  evt_data;
    UINT8           err_code = 0;
    tBTM_SEC_DEV_REC *p_dev_rec;
    BOOLEAN         is_orig = TRUE;
    UINT8           callback_rc = BTM_SUCCESS;

    STREAM_TO_BDADDR (evt_data.bd_addr, p);

    /* setup the default response according to compile options */
    /* assume that the local IO capability does not change
     * loc_io_caps is initialized with the default value */
    evt_data.io_cap = btm_cb.devcb.loc_io_caps;
    evt_data.oob_data = BTM_OOB_NONE;
    evt_data.auth_req = BTM_DEFAULT_AUTH_REQ;

    BTM_TRACE_EVENT1 ("btm_io_capabilities_req() State: %s", btm_pair_state_descr(btm_cb.pairing_state));

    p_dev_rec = btm_find_or_alloc_dev (evt_data.bd_addr);
    p_dev_rec->sm4 |= BTM_SM4_TRUE;

    BTM_TRACE_EVENT3 ("btm_io_capabilities_req() State: %s  Flags: 0x%04x  p_cur_service: 0x%08x",
                      btm_pair_state_descr(btm_cb.pairing_state), btm_cb.pairing_flags, p_dev_rec->p_cur_service);

    if (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
    {
        if (btm_cb.pairing_state == BTM_PAIR_STATE_INCOMING_SSP)
        {
            /* received IO capability response already-> not the originator of SSP */
            is_orig = FALSE;

            if (btm_cb.pairing_flags & BTM_PAIR_FLAGS_PEER_STARTED_DD)
                evt_data.auth_req = BTM_DEFAULT_DD_AUTH_REQ;
        }
        /* security is already in progress */
        else if (btm_cb.pairing_state == BTM_PAIR_STATE_WAIT_PIN_REQ)
        {
/* coverity[uninit_use_in_call]
Event uninit_use_in_call: Using uninitialized element of array "evt_data.bd_addr" in call to function "memcmp"
False-positive: evt_data.bd_addr is set at the beginning with:     STREAM_TO_BDADDR (evt_data.bd_addr, p);
*/
            if (memcmp (evt_data.bd_addr, btm_cb.pairing_bda, BD_ADDR_LEN))
            {
                /* and it's not the device in bonding -> reject it */
                err_code = HCI_ERR_HOST_BUSY_PAIRING;
            }
            else
            {
                /* local device initiated dedicated bonding */
                evt_data.auth_req = BTM_DEFAULT_DD_AUTH_REQ;
            }
        }
        else
        {
            err_code = HCI_ERR_HOST_BUSY_PAIRING;
        }
    }

    /* paring is not allowed */
    if (btm_cb.pairing_disabled)
        err_code = HCI_ERR_PAIRING_NOT_ALLOWED;

    if (err_code != 0)
    {
/* coverity[uninit_use_in_call]
Event uninit_use_in_call: Using uninitialized element of array "evt_data.bd_addr" in call to function "memcmp"
False-positive: evt_data.bd_addr is set at the beginning with:     STREAM_TO_BDADDR (evt_data.bd_addr, p);
*/
        btsnd_hcic_io_cap_req_neg_reply(evt_data.bd_addr, err_code);
        return;
    }

    evt_data.is_orig = is_orig;

    if (is_orig)
    {
        /* local device initiated the pairing non-bonding -> use p_cur_service */
        if (!(btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD) &&
            p_dev_rec->p_cur_service &&
            (p_dev_rec->p_cur_service->security_flags & BTM_SEC_OUT_AUTHENTICATE))
        {
            evt_data.auth_req = (p_dev_rec->p_cur_service->security_flags & BTM_SEC_OUT_MITM) ? BTM_AUTH_SP_YES : BTM_AUTH_SP_NO;
        }
    }

    /* Notify L2CAP to increase timeout */
    l2c_pin_code_request (evt_data.bd_addr);

    memcpy (btm_cb.pairing_bda, evt_data.bd_addr, BD_ADDR_LEN);

/* coverity[uninit_use_in_call]
Event uninit_use_in_call: Using uninitialized element of array "evt_data.bd_addr" in call to function "memcmp"
False-positive: False-positive: evt_data.bd_addr is set at the beginning with:     STREAM_TO_BDADDR (evt_data.bd_addr, p);
*/
    if (!memcmp (evt_data.bd_addr, btm_cb.connecting_bda, BD_ADDR_LEN))
        memcpy (p_dev_rec->dev_class, btm_cb.connecting_dc, DEV_CLASS_LEN);

    btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_LOCAL_IOCAPS);

    callback_rc = BTM_SUCCESS;
    if (p_dev_rec->sm4 & BTM_SM4_UPGRADE)
    {
        p_dev_rec->sm4 &= ~BTM_SM4_UPGRADE;

        /* link key upgrade: always use SPGB_YES - assuming we want to save the link key */
        evt_data.auth_req = BTM_AUTH_SPGB_YES;
    }
    else if (btm_cb.api.p_sp_callback)
    {
        /* the callback function implementation may change the IO capability... */
        callback_rc = (*btm_cb.api.p_sp_callback) (BTM_SP_IO_REQ_EVT, (tBTM_SP_EVT_DATA *)&evt_data);
    }

#if BTM_OOB_INCLUDED == TRUE
    if ((callback_rc == BTM_SUCCESS) || (BTM_OOB_UNKNOWN != evt_data.oob_data))
#else
    if (callback_rc == BTM_SUCCESS)
#endif
    {
        if ((btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD))
        {
            evt_data.auth_req = (BTM_AUTH_DD_BOND | (evt_data.auth_req & BTM_AUTH_YN_BIT));
        }

        /* if the user does not indicate "reply later" by setting the oob_data to unknown
         * send the response right now. Save the current IO capability in the control block */
        btm_cb.devcb.loc_auth_req   = evt_data.auth_req;
        btm_cb.devcb.loc_io_caps    = evt_data.io_cap;

        BTM_TRACE_EVENT4 ("btm_io_capabilities_req: State: %s  IO_CAP:%d oob_data:%d auth_req:%d",
                          btm_pair_state_descr(btm_cb.pairing_state), evt_data.io_cap,
                          evt_data.oob_data, evt_data.auth_req);

        btsnd_hcic_io_cap_req_reply(evt_data.bd_addr, evt_data.io_cap,
                                    evt_data.oob_data, evt_data.auth_req);
    }
}

/*******************************************************************************
**
** Function         btm_io_capabilities_rsp
**
** Description      This function is called when the IO capability of the
**                  specified device is received
**
** Returns          void
**
*******************************************************************************/
void btm_io_capabilities_rsp (UINT8 *p)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    tBTM_SP_IO_RSP evt_data;

    STREAM_TO_BDADDR (evt_data.bd_addr, p);
    STREAM_TO_UINT8 (evt_data.io_cap, p);
    STREAM_TO_UINT8 (evt_data.oob_data, p);
    STREAM_TO_UINT8 (evt_data.auth_req, p);

    /* Allocate a new device record or reuse the oldest one */
    p_dev_rec = btm_find_or_alloc_dev (evt_data.bd_addr);

    /* If no security is in progress, this indicates incoming security */
    if (btm_cb.pairing_state == BTM_PAIR_STATE_IDLE)
    {
        memcpy (btm_cb.pairing_bda, evt_data.bd_addr, BD_ADDR_LEN);

        btm_sec_change_pairing_state (BTM_PAIR_STATE_INCOMING_SSP);

        /* Make sure we reset the trusted mask to help against attacks */
        BTM_SEC_CLR_TRUSTED_DEVICE(p_dev_rec->trusted_mask);

        /* work around for FW bug */
        btm_inq_stop_on_ssp();
    }

    /* Notify L2CAP to increase timeout */
    l2c_pin_code_request (evt_data.bd_addr);

    /* We must have a device record here.
     * Use the connecting device's CoD for the connection */
/* coverity[uninit_use_in_call]
Event uninit_use_in_call: Using uninitialized element of array "evt_data.bd_addr" in call to function "memcmp"
FALSE-POSITIVE error from Coverity test-tool. evt_data.bd_addr is set at the beginning with:     STREAM_TO_BDADDR (evt_data.bd_addr, p);
*/
    if (!memcmp (evt_data.bd_addr, btm_cb.connecting_bda, BD_ADDR_LEN))
        memcpy (p_dev_rec->dev_class, btm_cb.connecting_dc, DEV_CLASS_LEN);

    /* peer sets dedicated bonding bit and we did not initiate dedicated bonding */
    if (btm_cb.pairing_state == BTM_PAIR_STATE_INCOMING_SSP /* peer initiated bonding */
        && (evt_data.auth_req & BTM_AUTH_DD_BOND) )            /* and dedicated bonding bit is set */
    {
        btm_cb.pairing_flags |= BTM_PAIR_FLAGS_PEER_STARTED_DD;
    }

    /* save the IO capability in the device record */
    p_dev_rec->rmt_io_caps  = evt_data.io_cap;
    p_dev_rec->rmt_auth_req = evt_data.auth_req;

    if (btm_cb.api.p_sp_callback)
        (*btm_cb.api.p_sp_callback) (BTM_SP_IO_RSP_EVT, (tBTM_SP_EVT_DATA *)&evt_data);
}

/*******************************************************************************
**
** Function         btm_proc_sp_req_evt
**
** Description      This function is called to process/report
**                  HCI_USER_CONFIRMATION_REQUEST_EVT
**                  or HCI_USER_PASSKEY_REQUEST_EVT
**                  or HCI_USER_PASSKEY_NOTIFY_EVT
**
** Returns          void
**
*******************************************************************************/
void btm_proc_sp_req_evt (tBTM_SP_EVT event, UINT8 *p)
{
    tBTM_STATUS status = BTM_ERR_PROCESSING;
    tBTM_SP_EVT_DATA evt_data;
    UINT8               *p_bda = evt_data.cfm_req.bd_addr;
    tBTM_SEC_DEV_REC *p_dev_rec;

    /* All events start with bd_addr */
    STREAM_TO_BDADDR (p_bda, p);

    BTM_TRACE_EVENT4 ("btm_proc_sp_req_evt() BDA: %08x%04x event: 0x%x, State: %s",
                      (p_bda[0]<<24) + (p_bda[1]<<16) + (p_bda[2]<<8) + p_bda[3], (p_bda[4] << 8) + p_bda[5],
                      event, btm_pair_state_descr(btm_cb.pairing_state));

    if ( ((p_dev_rec = btm_find_dev (p_bda)) != NULL)
         &&  (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
         &&  (memcmp (btm_cb.pairing_bda, p_bda, BD_ADDR_LEN) == 0) )
    {
        memcpy (evt_data.cfm_req.bd_addr, p_dev_rec->bd_addr, BD_ADDR_LEN);
        memcpy (evt_data.cfm_req.dev_class, p_dev_rec->dev_class, DEV_CLASS_LEN);

        BCM_STRNCPY_S ((char *)evt_data.cfm_req.bd_name, sizeof(evt_data.cfm_req.bd_name), (char *)p_dev_rec->sec_bd_name, BTM_MAX_REM_BD_NAME_LEN);

        switch (event)
        {
            case BTM_SP_CFM_REQ_EVT:
                /* Numeric confirmation. Need user to conf the passkey */
                btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_NUMERIC_CONFIRM);

                /* The device record must be allocated in the "IO cap exchange" step */
                STREAM_TO_UINT32 (evt_data.cfm_req.num_val, p);

                evt_data.cfm_req.just_works = TRUE;

                /* process user confirm req in association with the auth_req param */
#if (BTM_LOCAL_IO_CAPS == BTM_IO_CAP_IO)
                if ( (p_dev_rec->rmt_io_caps == BTM_IO_CAP_IO)
                     &&  (btm_cb.devcb.loc_io_caps == BTM_IO_CAP_IO)
                     &&  ((p_dev_rec->rmt_auth_req & BTM_AUTH_SP_YES) || (btm_cb.devcb.loc_auth_req & BTM_AUTH_SP_YES)) )
                {
                    /* Both devices are DisplayYesNo and one or both devices want to authenticate
                       -> use authenticated link key */
                    evt_data.cfm_req.just_works = FALSE;
                }
#endif
                BTM_TRACE_DEBUG5 ("btm_proc_sp_req_evt()  just_works:%d, io loc:%d, rmt:%d, auth loc:%d, rmt:%d",
                                  evt_data.cfm_req.just_works, btm_cb.devcb.loc_io_caps, p_dev_rec->rmt_io_caps,
                                  btm_cb.devcb.loc_auth_req, p_dev_rec->rmt_auth_req);

                evt_data.cfm_req.loc_auth_req   = btm_cb.devcb.loc_auth_req;
                evt_data.cfm_req.rmt_auth_req   = p_dev_rec->rmt_auth_req;
                evt_data.cfm_req.loc_io_caps    = btm_cb.devcb.loc_io_caps;
                evt_data.cfm_req.rmt_io_caps    = p_dev_rec->rmt_io_caps;
                break;

            case BTM_SP_KEY_NOTIF_EVT:
                /* Passkey notification (other side is a keyboard) */
                STREAM_TO_UINT32 (evt_data.key_notif.passkey, p);

                BTM_TRACE_DEBUG1 ("BTM_SP_KEY_NOTIF_EVT:  passkey: %u", evt_data.key_notif.passkey);

                btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);
                break;

#if (BTM_LOCAL_IO_CAPS != BTM_IO_CAP_NONE)
            case BTM_SP_KEY_REQ_EVT:
                /* HCI_USER_PASSKEY_REQUEST_EVT */
                btm_sec_change_pairing_state (BTM_PAIR_STATE_KEY_ENTRY);
                break;
#endif
        }

        if (btm_cb.api.p_sp_callback)
        {
            status = (*btm_cb.api.p_sp_callback) (event, (tBTM_SP_EVT_DATA *)&evt_data);
            if (status != BTM_NOT_AUTHORIZED)
            {
                return;
            }
            /* else BTM_NOT_AUTHORIZED means when the app wants to reject the req right now */
        }
        else if ( (event == BTM_SP_CFM_REQ_EVT) && (evt_data.cfm_req.just_works == TRUE) )
        {
            /* automatically reply with just works if no sp_cback */
            status = BTM_SUCCESS;
        }

        if (event == BTM_SP_CFM_REQ_EVT)
        {
            BTM_TRACE_DEBUG1 ("calling BTM_ConfirmReqReply with status: %d", status);
            BTM_ConfirmReqReply (status, p_bda);
        }
#if (BTM_LOCAL_IO_CAPS != BTM_IO_CAP_NONE)
        else if (event == BTM_SP_KEY_REQ_EVT)
        {
            BTM_PasskeyReqReply(status, p_bda, 0);
        }
#endif
        return;
    }

    /* Something bad. we can only fail this connection */
    btm_cb.acl_disc_reason = HCI_ERR_HOST_REJECT_SECURITY;

    if (BTM_SP_CFM_REQ_EVT == event)
    {
        btsnd_hcic_user_conf_reply (p_bda, FALSE);
    }
    else if (BTM_SP_KEY_NOTIF_EVT == event)
    {
        /* do nothing -> it very unlikely to happen.
        This event is most likely to be received by a HID host when it first connects to a HID device.
        Usually the Host initiated the connection in this case.
        On Mobile platforms, if there's a security process happening,
        the host probably can not initiate another connection.
        BTW (PC) is another story.  */
        if (NULL != (p_dev_rec = btm_find_dev (p_bda)) )
        {
            btm_sec_disconnect (p_dev_rec->hci_handle, HCI_ERR_AUTH_FAILURE);
        }
    }
#if (BTM_LOCAL_IO_CAPS != BTM_IO_CAP_NONE)
    else
    {
        btsnd_hcic_user_passkey_neg_reply(p_bda);
    }
#endif
}

/*******************************************************************************
**
** Function         btm_keypress_notif_evt
**
** Description      This function is called when a key press notification is
**                  received
**
** Returns          void
**
*******************************************************************************/
void  btm_keypress_notif_evt (UINT8 *p)
{
    tBTM_SP_KEYPRESS    evt_data;
    UINT8 *p_bda;

    /* parse & report BTM_SP_KEYPRESS_EVT */
    if (btm_cb.api.p_sp_callback)
    {
        p_bda = evt_data.bd_addr;

        STREAM_TO_BDADDR (p_bda, p);
        evt_data.notif_type = *p;

        (*btm_cb.api.p_sp_callback) (BTM_SP_KEYPRESS_EVT, (tBTM_SP_EVT_DATA *)&evt_data);
    }
}

/*******************************************************************************
**
** Function         btm_simple_pair_complete
**
** Description      This function is called when simple pairing process is
**                  complete
**
** Returns          void
**
*******************************************************************************/
void btm_simple_pair_complete (UINT8 *p)
{
    tBTM_SP_COMPLT  evt_data;
    tBTM_SEC_DEV_REC *p_dev_rec;
    UINT8           status;
    BOOLEAN         disc = FALSE;

    status = *p++;
    STREAM_TO_BDADDR (evt_data.bd_addr, p);

    if ((p_dev_rec = btm_find_dev (evt_data.bd_addr)) == NULL)
    {
        BTM_TRACE_ERROR2 ("btm_simple_pair_complete() with unknown BDA: %08x%04x",
                          (evt_data.bd_addr[0]<<24) + (evt_data.bd_addr[1]<<16) + (evt_data.bd_addr[2]<<8) + evt_data.bd_addr[3],
                          (evt_data.bd_addr[4] << 8) + evt_data.bd_addr[5]);
        return;
    }

    BTM_TRACE_EVENT3 ("btm_simple_pair_complete()  Pair State: %s  Status:%d  sec_state: %u",
                      btm_pair_state_descr(btm_cb.pairing_state),  status, p_dev_rec->sec_state);

    evt_data.status = BTM_ERR_PROCESSING;
    if (status == HCI_SUCCESS)
    {
        evt_data.status = BTM_SUCCESS;
        p_dev_rec->sec_flags |= BTM_SEC_AUTHENTICATED;
    }
    else
    {
        if (status == HCI_ERR_PAIRING_NOT_ALLOWED)
        {
            /* The test spec wants the peer device to get this failure code. */
            btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_DISCONNECT);

            /* Change the timer to 1 second */
            btu_start_timer (&btm_cb.pairing_tle, BTU_TTYPE_USER_FUNC, BT_1SEC_TIMEOUT);
        }
        else if (memcmp (btm_cb.pairing_bda, evt_data.bd_addr, BD_ADDR_LEN) == 0)
        {
            /* stop the timer */
            btu_stop_timer (&btm_cb.pairing_tle);

            if (p_dev_rec->sec_state != BTM_SEC_STATE_AUTHENTICATING)
            {
                /* the initiating side: will receive auth complete event. disconnect ACL at that time */
                disc = TRUE;
            }
        }
        else
            disc = TRUE;
    }

    /* Let the pairing state stay active, p_auth_complete_callback will report the failure */
    memcpy (evt_data.bd_addr, p_dev_rec->bd_addr, BD_ADDR_LEN);
    memcpy (evt_data.dev_class, p_dev_rec->dev_class, DEV_CLASS_LEN);

    if (btm_cb.api.p_sp_callback)
        (*btm_cb.api.p_sp_callback) (BTM_SP_COMPLT_EVT, (tBTM_SP_EVT_DATA *)&evt_data);

    if (disc)
    {
        /* simple pairing failed */
        btm_sec_send_hci_disconnect (p_dev_rec, HCI_ERR_AUTH_FAILURE);
    }
}

#if BTM_OOB_INCLUDED == TRUE
/*******************************************************************************
**
** Function         btm_rem_oob_req
**
** Description      This function is called to process/report
**                  HCI_REMOTE_OOB_DATA_REQUEST_EVT
**
** Returns          void
**
*******************************************************************************/
void btm_rem_oob_req (UINT8 *p)
{
    UINT8 *p_bda;
    tBTM_SP_RMT_OOB  evt_data;
    tBTM_SEC_DEV_REC *p_dev_rec;
    BT_OCTET16      c;
    BT_OCTET16      r;

    p_bda = evt_data.bd_addr;

    STREAM_TO_BDADDR (p_bda, p);

    BTM_TRACE_EVENT6 ("btm_rem_oob_req() BDA: %02x:%02x:%02x:%02x:%02x:%02x",
                      p_bda[0], p_bda[1], p_bda[2], p_bda[3], p_bda[4], p_bda[5]);

    if ( (NULL != (p_dev_rec = btm_find_dev (p_bda))) &&
         btm_cb.api.p_sp_callback)
    {
        memcpy (evt_data.bd_addr, p_dev_rec->bd_addr, BD_ADDR_LEN);
        memcpy (evt_data.dev_class, p_dev_rec->dev_class, DEV_CLASS_LEN);
        BCM_STRNCPY_S((char *)evt_data.bd_name, sizeof(evt_data.bd_name), (char *)p_dev_rec->sec_bd_name, BTM_MAX_REM_BD_NAME_LEN+1);

        btm_sec_change_pairing_state(BTM_PAIR_STATE_WAIT_LOCAL_OOB_RSP);
        if ((*btm_cb.api.p_sp_callback) (BTM_SP_RMT_OOB_EVT, (tBTM_SP_EVT_DATA *)&evt_data) == BTM_NOT_AUTHORIZED)
        {
            BTM_RemoteOobDataReply(TRUE, p_bda, c, r);
        }
        return;
    }

    /* something bad. we can only fail this connection */
    btm_cb.acl_disc_reason = HCI_ERR_HOST_REJECT_SECURITY;
    btsnd_hcic_rem_oob_neg_reply (p_bda);
}

/*******************************************************************************
**
** Function         btm_read_local_oob_complete
**
** Description      This function is called when read local oob data is
**                  completed by the LM
**
** Returns          void
**
*******************************************************************************/
void btm_read_local_oob_complete (UINT8 *p)
{
    tBTM_SP_LOC_OOB evt_data;
    UINT8           status = *p++;

    BTM_TRACE_EVENT1 ("btm_read_local_oob_complete:%d", status);
    if (status == HCI_SUCCESS)
    {
        evt_data.status = BTM_SUCCESS;
        STREAM_TO_ARRAY16(evt_data.c, p);
        STREAM_TO_ARRAY16(evt_data.r, p);
    }
    else
        evt_data.status = BTM_ERR_PROCESSING;

    if (btm_cb.api.p_sp_callback)
        (*btm_cb.api.p_sp_callback) (BTM_SP_LOC_OOB_EVT, (tBTM_SP_EVT_DATA *)&evt_data);
}
#endif /* BTM_OOB_INCLUDED */

/*******************************************************************************
**
** Function         btm_sec_auth_collision
**
** Description      This function is called when authentication or encryption
**                  needs to be retried at a later time.
**
** Returns          void
**
*******************************************************************************/
static void btm_sec_auth_collision (UINT16 handle)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    if (!btm_cb.collision_start_time)
        btm_cb.collision_start_time = GKI_get_tick_count ();

    if ((GKI_get_tick_count () - btm_cb.collision_start_time) < btm_cb.max_collision_delay)
    {
        if (handle == BTM_SEC_INVALID_HANDLE)
        {
            if ((p_dev_rec = btm_sec_find_dev_by_sec_state (BTM_SEC_STATE_AUTHENTICATING)) == NULL)
                p_dev_rec = btm_sec_find_dev_by_sec_state (BTM_SEC_STATE_ENCRYPTING);
        }
        else
            p_dev_rec = btm_find_dev_by_handle (handle);

        if (p_dev_rec != NULL)
        {
            BTM_TRACE_DEBUG1 ("btm_sec_auth_collision: state %d (retrying in a moment...)", p_dev_rec->sec_state);
            /* We will restart authentication after timeout */
            if (p_dev_rec->sec_state == BTM_SEC_STATE_AUTHENTICATING || p_dev_rec->sec_state == BTM_SEC_STATE_ENCRYPTING)
                p_dev_rec->sec_state = 0;

            btm_cb.p_collided_dev_rec = p_dev_rec;
            btm_cb.sec_collision_tle.param = (UINT32) btm_sec_collision_timeout;
            btu_start_timer (&btm_cb.sec_collision_tle, BTU_TTYPE_USER_FUNC, BT_1SEC_TIMEOUT);
        }
    }
}

/*******************************************************************************
**
** Function         btm_sec_auth_complete
**
** Description      This function is when authentication of the connection is
**                  completed by the LM
**
** Returns          void
**
*******************************************************************************/
void btm_sec_auth_complete (UINT16 handle, UINT8 status)
{
    UINT8            old_sm4;
    tBTM_PAIRING_STATE  old_state   = btm_cb.pairing_state;
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev_by_handle (handle);
    BOOLEAN             are_bonding = FALSE;

    /* Commenting out trace due to obf/compilation problems.
    */
#if (BT_USE_TRACES == TRUE)
    if (p_dev_rec)
    {
        BTM_TRACE_EVENT6 ("Security Manager: auth_complete PairState: %s  handle:%u  status:%d  dev->sec_state: %u  Bda:%08x, RName:%s",
                          btm_pair_state_descr (btm_cb.pairing_state),
                          handle, status,
                          p_dev_rec->sec_state,
                          (p_dev_rec->bd_addr[2]<<24)+(p_dev_rec->bd_addr[3]<<16)+(p_dev_rec->bd_addr[4]<<8)+p_dev_rec->bd_addr[5],
                          p_dev_rec->sec_bd_name);
    }
    else
    {
        BTM_TRACE_EVENT3 ("Security Manager: auth_complete PairState: %s  handle:%u  status:%d",
                          btm_pair_state_descr (btm_cb.pairing_state),
                          handle, status);
    }
#endif

    /* For transaction collision we need to wait and repeat.  There is no need */
    /* for random timeout because only slave should receive the result */
    if ((status == HCI_ERR_LMP_ERR_TRANS_COLLISION) || (status == HCI_ERR_DIFF_TRANSACTION_COLLISION))
    {
        btm_sec_auth_collision(handle);
        return;
    }
    btm_cb.collision_start_time = 0;

    btm_restore_mode();

    /* Check if connection was made just to do bonding.  If we authenticate
       the connection that is up, this is the last event received.
    */
    if (p_dev_rec
        && (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD)
        && !(btm_cb.pairing_flags & BTM_PAIR_FLAGS_DISC_WHEN_DONE))
    {
        p_dev_rec->security_required &= ~BTM_SEC_OUT_AUTHENTICATE;

        l2cu_start_post_bond_timer (p_dev_rec->hci_handle);
    }

    if (!p_dev_rec)
        return;

    /* keep the old sm4 flag and clear the retry bit in control block */
    old_sm4 = p_dev_rec->sm4;
    p_dev_rec->sm4 &= ~BTM_SM4_RETRY;

    if ( (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
         &&  (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD)
         &&  (memcmp (p_dev_rec->bd_addr, btm_cb.pairing_bda, BD_ADDR_LEN) == 0) )
        are_bonding = TRUE;

    btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);

    if (p_dev_rec->sec_state != BTM_SEC_STATE_AUTHENTICATING)
    {
        if ( (btm_cb.api.p_auth_complete_callback && status != HCI_SUCCESS)
             &&  (old_state != BTM_PAIR_STATE_IDLE) )
        {
            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,
                                                    p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, status);
        }
        return;
    }

    /* There can be a race condition, when we are starting authentication and
    ** the peer device is doing encryption.
    ** If first we receive encryption change up, then initiated authentication
    ** can not be performed.  According to the spec we can not do authentication
    ** on the encrypted link, so device is correct.
    */
    if ((status == HCI_ERR_COMMAND_DISALLOWED)
        && ((p_dev_rec->sec_flags & (BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED)) ==
            (BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED)))
    {
        status = HCI_SUCCESS;
    }
    /* Currently we do not notify user if it is a keyboard which connects */
    /* User probably Disabled the keyboard while it was asleap.  Let her try */
    if (btm_cb.api.p_auth_complete_callback)
    {
        /* report the suthentication status */
        if (old_state != BTM_PAIR_STATE_IDLE)
            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,
                                                    p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, status);
    }

    p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;

    /* If this is a bonding procedure can disconnect the link now */
    if (are_bonding)
    {
        p_dev_rec->security_required &= ~BTM_SEC_OUT_AUTHENTICATE;

        if (status != HCI_SUCCESS)
            btm_sec_send_hci_disconnect (p_dev_rec, HCI_ERR_PEER_USER);
        else
            l2cu_start_post_bond_timer (p_dev_rec->hci_handle);

        return;
    }

    /* If authentication failed, notify the waiting layer */
    if (status != HCI_SUCCESS)
    {
        if ((old_sm4 & BTM_SM4_RETRY) == 0)
        {
            /* allow retry only once */
            if (status == HCI_ERR_LMP_ERR_TRANS_COLLISION)
            {
                /* not retried yet. set the retry bit */
                p_dev_rec->sm4 |= BTM_SM4_RETRY;
                BTM_TRACE_DEBUG2 ("Collision retry sm4:x%x sec_flags:0x%x", p_dev_rec->sm4, p_dev_rec->sec_flags);
            }
            /* this retry for missing key is for Lisbon or later only.
             * Legacy device do not need this. the controller will drive the retry automatically */
            else if (HCI_ERR_KEY_MISSING == status && BTM_SEC_IS_SM4(p_dev_rec->sm4))
            {
                /* not retried yet. set the retry bit */
                p_dev_rec->sm4 |= BTM_SM4_RETRY;
                p_dev_rec->sec_flags &= ~BTM_SEC_LINK_KEY_KNOWN;
                BTM_TRACE_DEBUG2 ("Retry for missing key sm4:x%x sec_flags:0x%x", p_dev_rec->sm4, p_dev_rec->sec_flags);

                /* With BRCM controller, we do not need to delete the stored link key in controller.
                If the stack may sit on top of other controller, we may need this
                BTM_DeleteStoredLinkKey (bd_addr, NULL); */
            }

            if (p_dev_rec->sm4 & BTM_SM4_RETRY)
            {
                btm_sec_execute_procedure (p_dev_rec);
                return;
            }
        }

        btm_sec_dev_rec_cback_event (p_dev_rec, BTM_ERR_PROCESSING);

        if (btm_cb.pairing_flags & BTM_PAIR_FLAGS_DISC_WHEN_DONE)
        {
            btm_sec_send_hci_disconnect (p_dev_rec, HCI_ERR_AUTH_FAILURE);
        }
        return;
    }

    p_dev_rec->sec_flags |= BTM_SEC_AUTHENTICATED;

    /* Authentication succeeded, execute the next security procedure, if any */
    status = btm_sec_execute_procedure (p_dev_rec);

    /* If there is no next procedure, or procedure failed to start, notify the caller */
    if (status != BTM_CMD_STARTED)
        btm_sec_dev_rec_cback_event (p_dev_rec, status);
}

/*******************************************************************************
**
** Function         btm_sec_mkey_comp_event
**
** Description      This function is when encryption of the connection is
**                  completed by the LM
**
** Returns          void
**
*******************************************************************************/
void btm_sec_mkey_comp_event (UINT16 handle, UINT8 status, UINT8 key_flg)
{
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev_by_handle (handle);
    UINT8 bd_addr[BD_ADDR_LEN] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff} ;

    BTM_TRACE_EVENT2 ("Security Manager: mkey comp status:%d State:%d",
                      status, (p_dev_rec) ? p_dev_rec->sec_state : 0);

    /* If encryption setup failed, notify the waiting layer */
    /* There is no next procedure or start of procedure failed, notify the waiting layer */
    if (btm_cb.mkey_cback)
    {
        if (!p_dev_rec)
            (btm_cb.mkey_cback)(bd_addr, status, key_flg );
        else
            (btm_cb.mkey_cback)(p_dev_rec->bd_addr, status, key_flg );
    }
}

/*******************************************************************************
**
** Function         btm_sec_encrypt_change
**
** Description      This function is when encryption of the connection is
**                  completed by the LM
**
** Returns          void
**
*******************************************************************************/
void btm_sec_encrypt_change (UINT16 handle, UINT8 status, UINT8 encr_enable)
{
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev_by_handle (handle);

    BTM_TRACE_EVENT3 ("Security Manager: encrypt_change status:%d State:%d, encr_enable = %d",
                      status, (p_dev_rec) ? p_dev_rec->sec_state : 0, encr_enable);
    BTM_TRACE_DEBUG1 ("before update p_dev_rec->sec_flags=0x%x", p_dev_rec->sec_flags );

    /* For transaction collision we need to wait and repeat.  There is no need */
    /* for random timeout because only slave should receive the result */
    if ((status == HCI_ERR_LMP_ERR_TRANS_COLLISION) || (status == HCI_ERR_DIFF_TRANSACTION_COLLISION))
    {
        btm_sec_auth_collision(handle);
        return;
    }
    btm_cb.collision_start_time = 0;

    if (!p_dev_rec)
        return;

    if ((status == HCI_SUCCESS) && encr_enable)
        p_dev_rec->sec_flags |= (BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED);

    /* It is possible that we decrypted the link to perform role switch */
    /* mark link not to be encrypted, so that when we execute security next time it will kick in again */
    if ((status == HCI_SUCCESS) && !encr_enable)
        p_dev_rec->sec_flags &= ~BTM_SEC_ENCRYPTED;

    BTM_TRACE_DEBUG1 ("after update p_dev_rec->sec_flags=0x%x", p_dev_rec->sec_flags );
#if BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE
    if (p_dev_rec->device_type  == BT_DEVICE_TYPE_BLE)
    {
        btm_ble_link_encrypted(p_dev_rec->bd_addr, encr_enable);
        return;
    }
    else
        /* BR/EDR connection, update the encryption key size to be 16 as always */
        p_dev_rec->enc_key_size = 16;
#endif

    /* If this encryption was started by peer do not need to do anything */
    if (p_dev_rec->sec_state != BTM_SEC_STATE_ENCRYPTING)
    {
        if (BTM_SEC_STATE_DELAY_FOR_ENC == p_dev_rec->sec_state)
        {
            p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;
            p_dev_rec->p_callback = NULL;
            l2cu_resubmit_pending_sec_req (p_dev_rec->bd_addr);
        }
        return;
    }

    p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;

    /* If encryption setup failed, notify the waiting layer */
    if (status != HCI_SUCCESS)
    {
        btm_sec_dev_rec_cback_event (p_dev_rec, BTM_ERR_PROCESSING);
        return;
    }

    /* Encryption setup succeeded, execute the next security procedure, if any */
    status = (UINT8)btm_sec_execute_procedure (p_dev_rec);

    /* If there is no next procedure, or procedure failed to start, notify the caller */
    if (status != BTM_CMD_STARTED)
        btm_sec_dev_rec_cback_event (p_dev_rec, status);
}

/*******************************************************************************
**
** Function         btm_sec_create_conn
**
** Description      This function records current role and forwards request to
**                  HCI
**
** Returns          void
**
*******************************************************************************/
BOOLEAN btm_sec_create_conn (BD_ADDR bda, UINT16 packet_types,
                             UINT8 page_scan_rep_mode, UINT8 page_scan_mode,
                             UINT16 clock_offset, UINT8 allow_switch)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_or_alloc_dev (bda);

    memcpy (btm_cb.connecting_bda, p_dev_rec->bd_addr,   BD_ADDR_LEN);
    memcpy (btm_cb.connecting_dc,  p_dev_rec->dev_class, DEV_CLASS_LEN);

    btm_cb.acl_disc_reason = 0xff ;

    p_dev_rec->sec_state   = BTM_SEC_STATE_IDLE;
    p_dev_rec->role_master = TRUE;

    /* If any SCO link up, do not allow a switch */
    if (BTM_GetNumScoLinks() != 0)
        allow_switch = HCI_CR_CONN_NOT_ALLOW_SWITCH;

    return(btsnd_hcic_create_conn (bda, packet_types, page_scan_rep_mode,
                                   page_scan_mode, clock_offset, allow_switch));
}

/*******************************************************************************
**
** Function         btm_sec_connect_after_reject_timeout
**
** Description      Connection for bonding could not start because of the collision
**                  Initiate outgoing connection
**
** Returns          Pointer to the TLE struct
**
*******************************************************************************/
static void btm_sec_connect_after_reject_timeout (TIMER_LIST_ENT *p_tle)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_cb.p_collided_dev_rec;

    BTM_TRACE_EVENT0 ("btm_sec_connect_after_reject_timeout()");
    btm_cb.sec_collision_tle.param = 0;
    btm_cb.p_collided_dev_rec = 0;

    if (btm_sec_dd_create_conn(p_dev_rec) != BTM_CMD_STARTED)
    {
        BTM_TRACE_WARNING0 ("Security Manager: btm_sec_connect_after_reject_timeout: failed to start connection");

        btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);

        (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,  p_dev_rec->dev_class,
                                                p_dev_rec->sec_bd_name, HCI_ERR_MEMORY_FULL);
    }
}

/*******************************************************************************
**
** Function         btm_sec_connected
**
** Description      This function is when a connection to the peer device is
**                  establsihed
**
** Returns          void
**
*******************************************************************************/
void btm_sec_connected (UINT8 *bda, UINT16 handle, UINT8 status, UINT8 enc_mode)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev (bda);
    UINT8            res;
    BOOLEAN          is_pairing_device = FALSE;
    tACL_CONN        *p_acl_cb;

    btm_acl_resubmit_page();

    /* Commenting out trace due to obf/compilation problems.
    */
#if (BT_USE_TRACES == TRUE)
    if (p_dev_rec)
    {
        BTM_TRACE_EVENT6 ("Security Manager: btm_sec_connected in state: %s  handle:%d status:%d enc_mode:%d  bda:%x RName:%s",
                          btm_pair_state_descr(btm_cb.pairing_state), handle, status, enc_mode,
                          (bda[2]<<24)+(bda[3]<<16)+(bda[4]<<8)+bda[5],
                          p_dev_rec->sec_bd_name);
    }
    else
    {
        BTM_TRACE_EVENT5 ("Security Manager: btm_sec_connected in state: %s  handle:%d status:%d enc_mode:%d  bda:%x ",
                          btm_pair_state_descr(btm_cb.pairing_state), handle, status, enc_mode,
                          (bda[2]<<24)+(bda[3]<<16)+(bda[4]<<8)+bda[5]);
    }
#endif

    if (!p_dev_rec)
    {
        /* There is no device record for new connection.  Allocate one */
        if (status == HCI_SUCCESS)
        {
            p_dev_rec = btm_sec_alloc_dev (bda);
        }
        else
        {
            /* can not find the device record and the status is error,
             * just ignore it */
            return;
        }
    }
    else    /* Update the timestamp for this device */
    {
        p_dev_rec->timestamp = btm_cb.dev_rec_count++;
        if (p_dev_rec->sm4 & BTM_SM4_CONN_PEND)
        {
            /* tell L2CAP it's a bonding connection. */
            if ( (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
                 &&  (memcmp (btm_cb.pairing_bda, p_dev_rec->bd_addr, BD_ADDR_LEN) == 0)
                 &&  (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD) )
            {
                /* if incoming connection failed while pairing, then try to connect and continue */
                /* Motorola S9 disconnects without asking pin code */
                if ((status != HCI_SUCCESS)&&(btm_cb.pairing_state == BTM_PAIR_STATE_WAIT_PIN_REQ))
                {
                    BTM_TRACE_WARNING0 ("Security Manager: btm_sec_connected: incoming connection failed without asking PIN");

                    p_dev_rec->sm4 &= ~BTM_SM4_CONN_PEND;
                    if (p_dev_rec->sec_flags & BTM_SEC_NAME_KNOWN)
                    {
                        /* Start timer with 0 to initiate connection with new LCB */
                        /* because L2CAP will delete current LCB with this event  */
                        btm_cb.p_collided_dev_rec = p_dev_rec;
                        btm_cb.sec_collision_tle.param = (UINT32) btm_sec_connect_after_reject_timeout;
                        btu_start_timer (&btm_cb.sec_collision_tle, BTU_TTYPE_USER_FUNC, 0);
                    }
                    else
                    {
                        btm_sec_change_pairing_state (BTM_PAIR_STATE_GET_REM_NAME);
                        BTM_ReadRemoteDeviceName(p_dev_rec->bd_addr, NULL);
                    }
#if BTM_DISC_DURING_RS == TRUE
                    p_dev_rec->rs_disc_pending   = BTM_SEC_RS_NOT_PENDING;     /* reset flag */
#endif
                    return;
                }
                else
                {
                    l2cu_update_lcb_4_bonding(p_dev_rec->bd_addr, TRUE);
                }
            }
            /* always clear the pending flag */
            p_dev_rec->sm4 &= ~BTM_SM4_CONN_PEND;
        }
    }

#if BTM_DISC_DURING_RS == TRUE
    p_dev_rec->rs_disc_pending   = BTM_SEC_RS_NOT_PENDING;     /* reset flag */
#endif

    if ( (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
         && (memcmp (btm_cb.pairing_bda, bda, BD_ADDR_LEN) == 0) )
    {
        /* if we rejected incoming connection from bonding device */
        if ((status == HCI_ERR_HOST_REJECT_DEVICE)
            &&(btm_cb.pairing_flags & BTM_PAIR_FLAGS_REJECTED_CONNECT))
        {
            BTM_TRACE_WARNING2 ("Security Manager: btm_sec_connected: HCI_Conn_Comp Flags:0x%04x, sm4: 0x%x",
                btm_cb.pairing_flags, p_dev_rec->sm4);

            btm_cb.pairing_flags &= ~BTM_PAIR_FLAGS_REJECTED_CONNECT;
            if (BTM_SEC_IS_SM4_UNKNOWN(p_dev_rec->sm4))
            {
                /* Try again: RNR when no ACL causes HCI_RMT_HOST_SUP_FEAT_NOTIFY_EVT */
                btm_sec_change_pairing_state (BTM_PAIR_STATE_GET_REM_NAME);
                BTM_ReadRemoteDeviceName(bda, NULL);
                return;
            }

            /* if we already have pin code */
            if (btm_cb.pairing_state != BTM_PAIR_STATE_WAIT_LOCAL_PIN)
            {
                /* Start timer with 0 to initiate connection with new LCB */
                /* because L2CAP will delete current LCB with this event  */
                btm_cb.p_collided_dev_rec = p_dev_rec;
                btm_cb.sec_collision_tle.param = (UINT32) btm_sec_connect_after_reject_timeout;
                btu_start_timer (&btm_cb.sec_collision_tle, BTU_TTYPE_USER_FUNC, 0);
            }

            return;
        }
        /* wait for incoming connection without resetting pairing state */
        else if (status == HCI_ERR_CONNECTION_EXISTS)
        {
            BTM_TRACE_WARNING0 ("Security Manager: btm_sec_connected: Wait for incoming connection");
            return;
        }

        is_pairing_device = TRUE;
    }

    /* If connection was made to do bonding restore link security if changed */
    btm_restore_mode();

    /* if connection fails during pin request, notify application */
    if (status != HCI_SUCCESS)
    {
        /* If connection failed because of during pairing, need to tell user */
        if (is_pairing_device)
        {
            p_dev_rec->security_required &= ~BTM_SEC_OUT_AUTHENTICATE;
            p_dev_rec->sec_flags &= ~(BTM_SEC_LINK_KEY_KNOWN | BTM_SEC_LINK_KEY_AUTHED);
            BTM_TRACE_DEBUG1 ("security_required:%x ", p_dev_rec->security_required );

            btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);

            /* We need to notify host that the key is not known any more */
            if (btm_cb.api.p_auth_complete_callback)
            {
                (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,
                                                        p_dev_rec->dev_class,
                                                        p_dev_rec->sec_bd_name, status);
            }
        }
        else if ((status == HCI_ERR_AUTH_FAILURE)                   ||
                 (status == HCI_ERR_KEY_MISSING)                         ||
                 (status == HCI_ERR_HOST_REJECT_SECURITY)                ||
                 (status == HCI_ERR_PAIRING_NOT_ALLOWED)                 ||
                 (status == HCI_ERR_UNIT_KEY_USED)                       ||
                 (status == HCI_ERR_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED) ||
                 (status == HCI_ERR_ENCRY_MODE_NOT_ACCEPTABLE)           ||
                 (status == HCI_ERR_REPEATED_ATTEMPTS))
        {
            p_dev_rec->security_required &= ~BTM_SEC_OUT_AUTHENTICATE;
            p_dev_rec->sec_flags &= ~BTM_SEC_LINK_KEY_KNOWN;

            /* We need to notify host that the key is not known any more */
            if (btm_cb.api.p_auth_complete_callback)
            {
                (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,
                                                        p_dev_rec->dev_class,
                                                        p_dev_rec->sec_bd_name, status);
            }
        }

        if (status == HCI_ERR_CONNECTION_TOUT || status == HCI_ERR_LMP_RESPONSE_TIMEOUT  ||
            status == HCI_ERR_UNSPECIFIED     || status == HCI_ERR_PAGE_TIMEOUT)
            btm_sec_dev_rec_cback_event (p_dev_rec, BTM_DEVICE_TIMEOUT);
        else
            btm_sec_dev_rec_cback_event (p_dev_rec, BTM_ERR_PROCESSING);

        return;
    }

    /* If initiated dedicated bonding, return the link key now, and initiate disconnect */
    /* If dedicated bonding, and we now have a link key, we are all done */
    if ( is_pairing_device
         && (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN) )
    {
        if (p_dev_rec->link_key_not_sent)
        {
            p_dev_rec->link_key_not_sent = FALSE;
            btm_send_link_key_notif(p_dev_rec);
        }

        p_dev_rec->security_required &= ~BTM_SEC_OUT_AUTHENTICATE;

        /* remember flag before it is initialized */
        if (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD)
            res = TRUE;
        else
            res = FALSE;

        if (btm_cb.api.p_auth_complete_callback)
            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,
                                                    p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, HCI_SUCCESS);

        btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);

        if ( res )
        {
            /* Let l2cap start bond timer */
            l2cu_update_lcb_4_bonding (p_dev_rec->bd_addr, TRUE);
        }

        return;
    }

    p_dev_rec->hci_handle = handle;

    /* role may not be correct here, it will be updated by l2cap, but we need to */
    /* notify btm_acl that link is up, so starting of rmt name request will not */
    /* set paging flag up */
    p_acl_cb = btm_bda_to_acl(bda);
    if (p_acl_cb)
    {
        /* whatever is in btm_establish_continue() without reporting the BTM_BL_CONN_EVT event */
#if (!defined(BTM_BYPASS_EXTRA_ACL_SETUP) || BTM_BYPASS_EXTRA_ACL_SETUP == FALSE)
        /* For now there are a some devices that do not like sending */
        /* commands events and data at the same time. */
        /* Set the packet types to the default allowed by the device */
        btm_set_packet_types (p_acl_cb, btm_cb.btm_acl_pkt_types_supported);

        if (btm_cb.btm_def_link_policy)
            BTM_SetLinkPolicy (p_acl_cb->remote_addr, &btm_cb.btm_def_link_policy);
#endif

        BTM_SetLinkSuperTout (p_acl_cb->remote_addr, btm_cb.btm_def_link_super_tout);
    }
    btm_acl_created (bda, p_dev_rec->dev_class, p_dev_rec->sec_bd_name, handle, HCI_ROLE_SLAVE, FALSE);

    /* Initialize security flags.  We need to do that because some            */
    /* authorization complete could have come after the connection is dropped */
    /* and that would set wrong flag that link has been authorized already    */
    p_dev_rec->sec_flags &= ~(BTM_SEC_AUTHORIZED | BTM_SEC_AUTHENTICATED |
                              BTM_SEC_ENCRYPTED | BTM_SEC_ROLE_SWITCHED);

    if (enc_mode != HCI_ENCRYPT_MODE_DISABLED)
        p_dev_rec->sec_flags |= (BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED);

    if (btm_cb.security_mode == BTM_SEC_MODE_LINK)
        p_dev_rec->sec_flags |= BTM_SEC_AUTHENTICATED;

    p_dev_rec->link_key_changed = FALSE;

    /* After connection is established we perform security if we do not know */
    /* the name, or if we are originator because some procedure can have */
    /* been scheduled while connection was down */
    BTM_TRACE_DEBUG1 ("is_originator:%d ", p_dev_rec->is_originator);
    if (!(p_dev_rec->sec_flags & BTM_SEC_NAME_KNOWN) || p_dev_rec->is_originator)
    {
        if ((res = btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED)
            btm_sec_dev_rec_cback_event (p_dev_rec, res);
    }
    return;
}

/*******************************************************************************
**
** Function         btm_sec_role_changed
**
** Description      This function is colled when controller reports role
**                  changed, or failed command status for Role Change request
**
** Returns          void
**
*******************************************************************************/
void btm_sec_role_changed (void *p_ref_data)
{
    tBTM_SEC_DEV_REC *p_dev_rec = (tBTM_SEC_DEV_REC *)p_ref_data;
    UINT8 res;

    BTM_TRACE_EVENT0 ("Security Manager: role changed");

    /* If this role switch was started by peer do not need to do anything */
    if (p_dev_rec->sec_state != BTM_SEC_STATE_SWITCHING_ROLE)
        return;

    /* If serurity required was to FORCE switch and it failed, notify the waiting layer */
    if (((p_dev_rec->security_required & BTM_SEC_FORCE_MASTER) && !p_dev_rec->role_master)
        || ((p_dev_rec->security_required & BTM_SEC_FORCE_SLAVE)  &&  p_dev_rec->role_master))
    {
        btm_sec_dev_rec_cback_event (p_dev_rec, BTM_ERR_PROCESSING);
        return;
    }

    p_dev_rec->sec_flags |= BTM_SEC_ROLE_SWITCHED;

    p_dev_rec->security_required &= ~(BTM_SEC_FORCE_MASTER | BTM_SEC_ATTEMPT_MASTER |
                                      BTM_SEC_FORCE_SLAVE  | BTM_SEC_ATTEMPT_SLAVE);

    p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;

    if ((res = (UINT8)btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED)
    {
        btm_sec_dev_rec_cback_event (p_dev_rec, res);
    }
}

/*******************************************************************************
**
** Function         btm_sec_disconnect
**
** Description      This function is called to disconnect HCI link
**
** Returns          btm status
**
*******************************************************************************/
tBTM_STATUS btm_sec_disconnect (UINT16 handle, UINT8 reason)
{
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev_by_handle (handle);

    /* In some weird race condition we may not have a record */
    if (!p_dev_rec)
    {
        btsnd_hcic_disconnect (handle, reason);
        return(BTM_SUCCESS);
    }

    /* If we are in the process of bonding we need to tell client that auth failed */
    if ( (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
         &&  (memcmp (btm_cb.pairing_bda, p_dev_rec->bd_addr, BD_ADDR_LEN) == 0)
         &&  (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD) )
    {
        /* we are currently doing bonding.  Link will be disconnected when done */
        btm_cb.pairing_flags |= BTM_PAIR_FLAGS_DISC_WHEN_DONE;
        return(BTM_BUSY);
    }

    return(btm_sec_send_hci_disconnect(p_dev_rec, reason));
}

/*******************************************************************************
**
** Function         btm_sec_disconnected
**
** Description      This function is when a connection to the peer device is
**                  dropped
**
** Returns          void
**
*******************************************************************************/
void btm_sec_disconnected (UINT16 handle, UINT8 reason)
{
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev_by_handle (handle);
    UINT8             old_pairing_flags = btm_cb.pairing_flags;
    int               result = HCI_ERR_AUTH_FAILURE;

    /* If page was delayed for disc complete, can do it now */
    btm_cb.discing = FALSE;

    btm_acl_resubmit_page();

    if (!p_dev_rec)
        return;

#if BTM_DISC_DURING_RS == TRUE
    BTM_TRACE_ERROR0("btm_sec_disconnected - Clearing Pending flag");
    p_dev_rec->rs_disc_pending = BTM_SEC_RS_NOT_PENDING;     /* reset flag */
#endif

    /* clear unused flags */
    p_dev_rec->sm4 &= BTM_SM4_TRUE;

    BTM_TRACE_EVENT6("btm_sec_disconnected() sec_req:x%x  State: %s   reason:%d bda:%04x%08x RName:%s",
                     p_dev_rec->security_required, btm_pair_state_descr(btm_cb.pairing_state), reason,  (p_dev_rec->bd_addr[0]<<8)+p_dev_rec->bd_addr[1],
                     (p_dev_rec->bd_addr[2]<<24)+(p_dev_rec->bd_addr[3]<<16)+(p_dev_rec->bd_addr[4]<<8)+p_dev_rec->bd_addr[5], p_dev_rec->sec_bd_name);

    BTM_TRACE_EVENT1("before Update sec_flags=0x%x", p_dev_rec->sec_flags);

    /* If we are in the process of bonding we need to tell client that auth failed */
    if ( (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
         && (memcmp (btm_cb.pairing_bda, p_dev_rec->bd_addr, BD_ADDR_LEN) == 0))
    {
        btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
        p_dev_rec->sec_flags &= ~BTM_SEC_LINK_KEY_KNOWN;
        if (btm_cb.api.p_auth_complete_callback)
        {
            /* If the disconnection reason is REPEATED_ATTEMPTS,
               send this error message to complete callback function
               to display the error message of Repeated attempts.
               All others, send HCI_ERR_AUTH_FAILURE. */
            if (reason == HCI_ERR_REPEATED_ATTEMPTS)
            {
                result = HCI_ERR_REPEATED_ATTEMPTS;
            }
            else if (old_pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD)
            {
                result = HCI_ERR_HOST_REJECT_SECURITY;
            }
            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,     p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, result);
        }
    }

    p_dev_rec->hci_handle = BTM_SEC_INVALID_HANDLE;
    p_dev_rec->sec_state  = BTM_SEC_STATE_IDLE;

#if BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE
    p_dev_rec->enc_key_size = 0;
    btm_ble_resume_bg_conn(NULL, TRUE);
    /* see sec_flags processing in btm_acl_removed */
#endif
    p_dev_rec->sec_flags &= ~(BTM_SEC_AUTHORIZED | BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED | BTM_SEC_ROLE_SWITCHED);

    p_dev_rec->security_required = BTM_SEC_NONE;
    p_dev_rec->p_callback = NULL; /* when the peer device time out the authentication before we do, this call back must be reset here */
    BTM_TRACE_EVENT1("after Update sec_flags=0x%x", p_dev_rec->sec_flags);
}

/*******************************************************************************
**
** Function         btm_sec_link_key_notification
**
** Description      This function is called when a new connection link key is
**                  generated
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
void btm_sec_link_key_notification (UINT8 *p_bda, UINT8 *p_link_key, UINT8 key_type)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_or_alloc_dev (p_bda);
    BOOLEAN          we_are_bonding = FALSE;

    BTM_TRACE_EVENT3 ("btm_sec_link_key_notification()  BDA:%04x%08x, TYPE: %d",
                      (p_bda[0]<<8)+p_bda[1], (p_bda[2]<<24)+(p_bda[3]<<16)+(p_bda[4]<<8)+p_bda[5],
                      key_type);

    /* If connection was made to do bonding restore link security if changed */
    btm_restore_mode();

    /* Override the key type if version is pre-1.1 */
    if (btm_cb.devcb.local_version.hci_version < HCI_VERSION_1_1)
        p_dev_rec->link_key_type = BTM_LKEY_TYPE_IGNORE;
    if (key_type != BTM_LKEY_TYPE_CHANGED_COMB)
        p_dev_rec->link_key_type = key_type;

    p_dev_rec->sec_flags |= BTM_SEC_LINK_KEY_KNOWN;

    memcpy (p_dev_rec->link_key, p_link_key, LINK_KEY_LEN);

    if ( (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
         && (memcmp (btm_cb.pairing_bda, p_bda, BD_ADDR_LEN) == 0) )
    {
        if (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD)
            we_are_bonding = TRUE;
        else
            btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
    }

    /* If name is not known at this point delay calling callback until the name is   */
    /* resolved. Unless it is a HID Device and we really need to send all link keys. */
    if ((!(p_dev_rec->sec_flags & BTM_SEC_NAME_KNOWN)
        &&  ((p_dev_rec->dev_class[1] & BTM_COD_MAJOR_CLASS_MASK) != BTM_COD_MAJOR_PERIPHERAL)) )
    {
        BTM_TRACE_EVENT3 ("btm_sec_link_key_notification()  Delayed BDA: %08x%04x Type:%d",
                          (p_bda[0]<<24) + (p_bda[1]<<16) + (p_bda[2]<<8) + p_bda[3], (p_bda[4] << 8) + p_bda[5], key_type);

        p_dev_rec->link_key_not_sent = TRUE;

        /* If it is for bonding nothing else will follow, so we need to start name resolution */
        if (we_are_bonding)
        {
            if (!(btsnd_hcic_rmt_name_req (p_bda, HCI_PAGE_SCAN_REP_MODE_R1, HCI_MANDATARY_PAGE_SCAN_MODE, 0)))
                btm_inq_rmt_name_failed();
        }

        BTM_TRACE_EVENT3 ("rmt_io_caps:%d, sec_flags:x%x, dev_class[1]:x%02x", p_dev_rec->rmt_io_caps, p_dev_rec->sec_flags, p_dev_rec->dev_class[1])
        return;
    }

    /* If its not us who perform authentication, we should tell stackserver */
    /* that some authentication has been completed                          */
    /* This is required when different entities receive link notification and auth complete */
    if (!(p_dev_rec->security_required & BTM_SEC_OUT_AUTHENTICATE))
    {
        if (btm_cb.api.p_auth_complete_callback)
            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr, p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, HCI_SUCCESS);
    }

    /* We will save link key only if the user authorized it - BTE report link key in all cases */
#ifdef BRCM_NONE_BTE
    if (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_AUTHED)
#endif
    {
        if (btm_cb.api.p_link_key_callback)
        {
            (*btm_cb.api.p_link_key_callback) (p_bda, p_dev_rec->dev_class,  p_dev_rec->sec_bd_name,
                                               p_link_key, p_dev_rec->link_key_type);
        }
    }
}

/*******************************************************************************
**
** Function         btm_sec_link_key_request
**
** Description      This function is called when controller requests link key
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
void btm_sec_link_key_request (UINT8 *p_bda)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_or_alloc_dev (p_bda);

    BTM_TRACE_EVENT6 ("btm_sec_link_key_request()  BDA: %02x:%02x:%02x:%02x:%02x:%02x",
                      p_bda[0], p_bda[1], p_bda[2], p_bda[3], p_bda[4], p_bda[5]);

    if (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN)
    {
        btsnd_hcic_link_key_req_reply (p_bda, p_dev_rec->link_key);
        return;
    }

    /* Notify L2CAP to increase timeout */
    l2c_pin_code_request (p_bda);

    /* Only ask the host for a key if this guy is not already bonding */
    if ( (btm_cb.pairing_state == BTM_PAIR_STATE_IDLE)
         || (memcmp (p_bda, btm_cb.pairing_bda, BD_ADDR_LEN) != 0) )
    {
        if (btm_cb.api.p_link_key_req_callback)
        {
            if ((*btm_cb.api.p_link_key_req_callback)(p_bda, p_dev_rec->link_key) == BTM_SUCCESS)
            {
                btsnd_hcic_link_key_req_reply (p_bda, p_dev_rec->link_key);
                return;
            }
        }
    }

    /* The link key is not in the database and it is not known to the manager */
    btsnd_hcic_link_key_neg_reply (p_bda);
}

/*******************************************************************************
**
** Function         btm_sec_pairing_timeout
**
** Description      This function is called when host does not provide PIN
**                  within requested time
**
** Returns          Pointer to the TLE struct
**
*******************************************************************************/
static void btm_sec_pairing_timeout (TIMER_LIST_ENT *p_tle)
{
    tBTM_CB *p_cb = &btm_cb;
    tBTM_SEC_DEV_REC *p_dev_rec;
#if BTM_OOB_INCLUDED == TRUE
#if (BTM_LOCAL_IO_CAPS == BTM_IO_CAP_NONE)
    tBTM_AUTH_REQ   auth_req = BTM_AUTH_AP_NO;
#else
    tBTM_AUTH_REQ   auth_req = BTM_AUTH_AP_YES;
#endif
#endif
    UINT8   name[2];

    p_cb->pairing_tle.param = 0;
/* Coverity: FALSE-POSITIVE error from Coverity tool. Please do NOT remove following comment. */
/* coverity[UNUSED_VALUE] pointer p_dev_rec is actually used several times... This is a Coverity false-positive, i.e. a fake issue.
*/
    p_dev_rec = btm_find_dev (p_cb->pairing_bda);

    BTM_TRACE_EVENT2 ("btm_sec_pairing_timeout()  State: %s   Flags: %u",
                      btm_pair_state_descr(p_cb->pairing_state), p_cb->pairing_flags);

    switch (p_cb->pairing_state)
    {
        case BTM_PAIR_STATE_WAIT_PIN_REQ:
            btm_sec_bond_cancel_complete();
            break;

        case BTM_PAIR_STATE_WAIT_LOCAL_PIN:
            if ( (btm_cb.pairing_flags & BTM_PAIR_FLAGS_PRE_FETCH_PIN) == 0)
                btsnd_hcic_pin_code_neg_reply (p_cb->pairing_bda);
            btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
            /* We need to notify the UI that no longer need the PIN */
            if (btm_cb.api.p_auth_complete_callback)
            {
                if (p_dev_rec == NULL)
                {
                    name[0] = 0;
                    (*btm_cb.api.p_auth_complete_callback) (p_cb->pairing_bda,
                                                            NULL,
                                                            name, HCI_ERR_CONNECTION_TOUT);
                }
                else
                    (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,
                                                            p_dev_rec->dev_class,
                                                            p_dev_rec->sec_bd_name, HCI_ERR_CONNECTION_TOUT);
            }
            break;

        case BTM_PAIR_STATE_WAIT_NUMERIC_CONFIRM:
            btsnd_hcic_user_conf_reply (p_cb->pairing_bda, FALSE);
            /* btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE); */
            break;

#if (BTM_LOCAL_IO_CAPS != BTM_IO_CAP_NONE)
        case BTM_PAIR_STATE_KEY_ENTRY:
            btsnd_hcic_user_passkey_neg_reply(p_cb->pairing_bda);
            /* btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE); */
            break;
#endif /* !BTM_IO_CAP_NONE */

#if BTM_OOB_INCLUDED == TRUE
        case BTM_PAIR_STATE_WAIT_LOCAL_IOCAPS:
            if (btm_cb.pairing_flags & BTM_PAIR_FLAGS_WE_STARTED_DD)
                auth_req |= BTM_AUTH_DD_BOND;

            btsnd_hcic_io_cap_req_reply (p_cb->pairing_bda, btm_cb.devcb.loc_io_caps,
                                         BTM_OOB_NONE, auth_req);
            btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
            break;

        case BTM_PAIR_STATE_WAIT_LOCAL_OOB_RSP:
            btsnd_hcic_rem_oob_neg_reply (p_cb->pairing_bda);
            btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
            break;
#endif /* BTM_OOB_INCLUDED */

        case BTM_PAIR_STATE_WAIT_DISCONNECT:
            /* simple pairing failed. Started a 1-sec timer at simple pairing complete.
             * now it's time to tear down the ACL link*/
            if (p_dev_rec == NULL)
            {
                BTM_TRACE_ERROR2 ("btm_sec_pairing_timeout() BTM_PAIR_STATE_WAIT_DISCONNECT unknown BDA: %08x%04x",
                                  (p_cb->pairing_bda[0]<<24) + (p_cb->pairing_bda[1]<<16) + (p_cb->pairing_bda[2]<<8) + p_cb->pairing_bda[3],
                                  (p_cb->pairing_bda[4] << 8) + p_cb->pairing_bda[5]);
                break;
            }
            btm_sec_send_hci_disconnect (p_dev_rec, HCI_ERR_AUTH_FAILURE);
            btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
            break;

        case BTM_PAIR_STATE_WAIT_AUTH_COMPLETE:
            /* We need to notify the UI that timeout has happened while waiting for authentication*/
            btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
            if (btm_cb.api.p_auth_complete_callback)
            {
                if (p_dev_rec == NULL)
                {
                    name[0] = 0;
                    (*btm_cb.api.p_auth_complete_callback) (p_cb->pairing_bda,
                                                            NULL,
                                                            name, HCI_ERR_CONNECTION_TOUT);
                }
                else
                    (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,
                                                            p_dev_rec->dev_class,
                                                            p_dev_rec->sec_bd_name, HCI_ERR_CONNECTION_TOUT);
            }
            break;

        default:
            BTM_TRACE_WARNING1 ("btm_sec_pairing_timeout() not processed state: %s", btm_pair_state_descr(btm_cb.pairing_state));
            btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);
            break;
    }
}

/*******************************************************************************
**
** Function         btm_sec_pin_code_request
**
** Description      This function is called when controller requests PIN code
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
void btm_sec_pin_code_request (UINT8 *p_bda)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    tBTM_CB          *p_cb = &btm_cb;

    BTM_TRACE_EVENT3 ("btm_sec_pin_code_request()  State: %s, BDA:%04x%08x",
                      btm_pair_state_descr(btm_cb.pairing_state),
                      (p_bda[0]<<8)+p_bda[1], (p_bda[2]<<24)+(p_bda[3]<<16)+(p_bda[4]<<8)+p_bda[5] );

    if (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE)
    {
        if ( (memcmp (p_bda, btm_cb.pairing_bda, BD_ADDR_LEN) == 0)  &&
             (btm_cb.pairing_state == BTM_PAIR_STATE_WAIT_AUTH_COMPLETE) )
        {
             /* fake this out - porshe carkit issue - */
//            btm_cb.pairing_state = BTM_PAIR_STATE_IDLE;
             if(! btm_cb.pin_code_len_saved)
             {
                 btsnd_hcic_pin_code_neg_reply (p_bda);
                 return;
             }
             else
             {
                 btsnd_hcic_pin_code_req_reply (p_bda, btm_cb.pin_code_len_saved, p_cb->pin_code);
      	         return;
             }
        }
        else if ((btm_cb.pairing_state != BTM_PAIR_STATE_WAIT_PIN_REQ)
                 || memcmp (p_bda, btm_cb.pairing_bda, BD_ADDR_LEN) != 0)
        {
            BTM_TRACE_WARNING1 ("btm_sec_pin_code_request() rejected - state: %s",
                                btm_pair_state_descr(btm_cb.pairing_state));

#ifdef PORCHE_PAIRING_CONFLICT
            /* reply pin code again due to counter in_rand when local initiates pairing */
            BTM_TRACE_EVENT0 ("btm_sec_pin_code_request from remote dev. for local initiated pairing");
            if(! btm_cb.pin_code_len_saved)
            {
                btsnd_hcic_pin_code_neg_reply (p_bda);
            }
            else
            {
                btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);
                btsnd_hcic_pin_code_req_reply (p_bda, btm_cb.pin_code_len_saved, p_cb->pin_code);
            }
#else
            btsnd_hcic_pin_code_neg_reply (p_bda);
#endif
            return;
        }
    }

    p_dev_rec = btm_find_or_alloc_dev (p_bda);
    /* received PIN code request. must be non-sm4 */
    p_dev_rec->sm4 = BTM_SM4_KNOWN;

    if (btm_cb.pairing_state == BTM_PAIR_STATE_IDLE)
    {
        memcpy (btm_cb.pairing_bda, p_bda, BD_ADDR_LEN);

        btm_cb.pairing_flags = BTM_PAIR_FLAGS_PEER_STARTED_DD;
        /* Make sure we reset the trusted mask to help against attacks */
        BTM_SEC_CLR_TRUSTED_DEVICE(p_dev_rec->trusted_mask);
    }

    if (!p_cb->pairing_disabled && (p_cb->cfg.pin_type == HCI_PIN_TYPE_FIXED))
    {
        BTM_TRACE_EVENT0 ("btm_sec_pin_code_request fixed pin replying");
        btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);
        btsnd_hcic_pin_code_req_reply (p_bda, p_cb->cfg.pin_code_len, p_cb->cfg.pin_code);
        return;
    }

    /* Use the connecting device's CoD for the connection */
    if ( (!memcmp (p_bda, p_cb->connecting_bda, BD_ADDR_LEN))
         &&  (p_cb->connecting_dc[0] || p_cb->connecting_dc[1] || p_cb->connecting_dc[2]) )
        memcpy (p_dev_rec->dev_class, p_cb->connecting_dc, DEV_CLASS_LEN);

    /* We could have started connection after asking user for the PIN code */
    if (btm_cb.pin_code_len != 0)
    {
        BTM_TRACE_EVENT0 ("btm_sec_pin_code_request bonding sending reply");
        btsnd_hcic_pin_code_req_reply (p_bda, btm_cb.pin_code_len, p_cb->pin_code);

#ifdef PORCHE_PAIRING_CONFLICT
        btm_cb.pin_code_len_saved = btm_cb.pin_code_len;
#endif

        /* Mark that we forwarded received from the user PIN code */
        btm_cb.pin_code_len = 0;

        /* We can change mode back right away, that other connection being established */
        /* is not forced to be secure - found a FW issue, so we can not do this
        btm_restore_mode(); */

        btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);
    }

    /* If pairing disabled OR (no PIN callback and not bonding) */
    /* OR we could not allocate entry in the database reject pairing request */
    else if (p_cb->pairing_disabled
             || (p_cb->api.p_pin_callback == NULL)

             /* OR Microsoft keyboard can for some reason try to establish connection */
             /*  the only thing we can do here is to shut it up.  Normally we will be originator */
             /*  for keyboard bonding */
             || (!p_dev_rec->is_originator
                 && ((p_dev_rec->dev_class[1] & BTM_COD_MAJOR_CLASS_MASK) == BTM_COD_MAJOR_PERIPHERAL)
                 &&  (p_dev_rec->dev_class[2] & BTM_COD_MINOR_KEYBOARD)) )
    {
        BTM_TRACE_WARNING3("btm_sec_pin_code_request(): Pairing disabled:%d; PIN callback:%x, Dev Rec:%x!",
                           p_cb->pairing_disabled, p_cb->api.p_pin_callback, p_dev_rec);

        btsnd_hcic_pin_code_neg_reply (p_bda);
    }
    /* Notify upper layer of PIN request and start expiration timer */
    else
    {
        btm_cb.pin_code_len_saved = 0;
        btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_LOCAL_PIN);
        /* Pin code request can not come at the same time as connection request */
        memcpy (p_cb->connecting_bda, p_bda, BD_ADDR_LEN);
        memcpy (p_cb->connecting_dc,  p_dev_rec->dev_class, DEV_CLASS_LEN);

        /* Check if the name is known */
        /* Even if name is not known we might not be able to get one */
        /* this is the case when we are already getting something from the */
        /* device, so HCI level is flow controlled */
        /* Also cannot send remote name request while paging, i.e. connection is not completed */
        if (p_dev_rec->sec_flags & BTM_SEC_NAME_KNOWN)
        {
            BTM_TRACE_EVENT0 ("btm_sec_pin_code_request going for callback");

            btm_cb.pairing_flags |= BTM_PAIR_FLAGS_PIN_REQD;
            if (p_cb->api.p_pin_callback)
                (*p_cb->api.p_pin_callback) (p_bda, p_dev_rec->dev_class, p_dev_rec->sec_bd_name);
        }
        else
        {
            BTM_TRACE_EVENT0 ("btm_sec_pin_code_request going for remote name");

            /* We received PIN code request for the device with unknown name */
            /* it is not user friendly just to ask for the PIN without name */
            /* try to get name at first */
            if (!btsnd_hcic_rmt_name_req (p_dev_rec->bd_addr,
                                          HCI_PAGE_SCAN_REP_MODE_R1,
                                          HCI_MANDATARY_PAGE_SCAN_MODE, 0))
            {
                p_dev_rec->sec_flags |= BTM_SEC_NAME_KNOWN;
                p_dev_rec->sec_bd_name[0] = 'f';
                p_dev_rec->sec_bd_name[1] = '0';
                BTM_TRACE_ERROR0 ("can not send rmt_name_req?? fake a name and call callback");

                btm_cb.pairing_flags |= BTM_PAIR_FLAGS_PIN_REQD;
                if (p_cb->api.p_pin_callback)
                    (*p_cb->api.p_pin_callback) (p_bda, p_dev_rec->dev_class, p_dev_rec->sec_bd_name);
            }
        }
    }

    return;
}

/*******************************************************************************
**
** Function         btm_sec_update_clock_offset
**
** Description      This function is called to update clock offset
**
** Returns          void
**
*******************************************************************************/
void btm_sec_update_clock_offset (UINT16 handle, UINT16 clock_offset)
{
    tBTM_SEC_DEV_REC  *p_dev_rec;
    tBTM_INQ_INFO     *p_inq_info;

    if ((p_dev_rec = btm_find_dev_by_handle (handle)) == NULL)
        return;

    p_dev_rec->clock_offset = clock_offset | BTM_CLOCK_OFFSET_VALID;

    if ((p_inq_info = BTM_InqDbRead(p_dev_rec->bd_addr)) == NULL)
        return;

    p_inq_info->results.clock_offset = clock_offset | BTM_CLOCK_OFFSET_VALID;
}


/******************************************************************
** S T A T I C     F U N C T I O N S
*******************************************************************/

/*******************************************************************************
**
** Function         btm_sec_execute_procedure
**
** Description      This function is called to start required security
**                  procedure.  There is a case when multiplexing protocol
**                  calls this function on the originating side, connection to
**                  the peer will not be established.  This function in this
**                  case performs only authorization.
**
** Returns          BTM_SUCCESS     - permission is granted
**                  BTM_CMD_STARTED - in process
**                  BTM_NO_RESOURCES  - permission declined
**
*******************************************************************************/
static tBTM_STATUS btm_sec_execute_procedure (tBTM_SEC_DEV_REC *p_dev_rec)
{
    BTM_TRACE_EVENT3 ("btm_sec_execute_procedure: Required:0x%x Flags:0x%x State:%d",
                      p_dev_rec->security_required, p_dev_rec->sec_flags, p_dev_rec->sec_state);

    /* There is a chance that we are getting name.  Wait until done. */
    if (p_dev_rec->sec_state != 0)
        return(BTM_CMD_STARTED);

    /* If any security is required, get the name first */
    if (!(p_dev_rec->sec_flags & BTM_SEC_NAME_KNOWN)
        && (p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE))
    {
        BTM_TRACE_EVENT0 ("Security Manager: Start get name");
        if (!btm_sec_start_get_name (p_dev_rec))
        {
            return(BTM_NO_RESOURCES);
        }
        return(BTM_CMD_STARTED);
    }

    /* If connection is not authenticated and authentication is required */
    /* start authentication and return PENDING to the caller */
    if ((!(p_dev_rec->sec_flags & BTM_SEC_AUTHENTICATED))
        && (( p_dev_rec->is_originator && (p_dev_rec->security_required & BTM_SEC_OUT_AUTHENTICATE))
            || (!p_dev_rec->is_originator && (p_dev_rec->security_required & BTM_SEC_IN_AUTHENTICATE)))
        && (p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE))
    {
#if (L2CAP_UCD_INCLUDED == TRUE)
        /* if incoming UCD packet, discard it */
        if ( !p_dev_rec->is_originator && (p_dev_rec->is_ucd == TRUE ))
            return(BTM_FAILED_ON_SECURITY);
#endif

        BTM_TRACE_EVENT0 ("Security Manager: Start authentication");

        if (!btm_sec_start_authentication (p_dev_rec))
        {
            return(BTM_NO_RESOURCES);
        }
        return(BTM_CMD_STARTED);
    }

    /* If connection is not encrypted and encryption is required */
    /* start encryption and return PENDING to the caller */
    if (!(p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED)
        && (( p_dev_rec->is_originator && (p_dev_rec->security_required & BTM_SEC_OUT_ENCRYPT))
            || (!p_dev_rec->is_originator && (p_dev_rec->security_required & BTM_SEC_IN_ENCRYPT)))
        && (p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE))
    {
#if (L2CAP_UCD_INCLUDED == TRUE)
        /* if incoming UCD packet, discard it */
        if ( !p_dev_rec->is_originator && (p_dev_rec->is_ucd == TRUE ))
            return(BTM_FAILED_ON_SECURITY);
#endif

        BTM_TRACE_EVENT0 ("Security Manager: Start encryption");

        if (!btm_sec_start_encryption (p_dev_rec))
        {
            return(BTM_NO_RESOURCES);
        }
        return(BTM_CMD_STARTED);
    }

    /* If connection is not authorized and authorization is required */
    /* start authorization and return PENDING to the caller */
    if (!(p_dev_rec->sec_flags & BTM_SEC_AUTHORIZED)
        && (( p_dev_rec->is_originator && (p_dev_rec->security_required & BTM_SEC_OUT_AUTHORIZE))
            || (!p_dev_rec->is_originator && (p_dev_rec->security_required & BTM_SEC_IN_AUTHORIZE))))
    {
        BTM_TRACE_EVENT2 ("service id:%d, is trusted:%d",
                          p_dev_rec->p_cur_service->service_id,
                          (BTM_SEC_IS_SERVICE_TRUSTED(p_dev_rec->trusted_mask,
                                                      p_dev_rec->p_cur_service->service_id)));
        if ((btm_sec_are_all_trusted(p_dev_rec->trusted_mask) == FALSE) &&
            (p_dev_rec->p_cur_service->service_id < BTM_SEC_MAX_SERVICES) &&
            (BTM_SEC_IS_SERVICE_TRUSTED(p_dev_rec->trusted_mask,
                                        p_dev_rec->p_cur_service->service_id) == FALSE))
        {
            BTM_TRACE_EVENT0 ("Security Manager: Start authorization");
            return(btm_sec_start_authorization (p_dev_rec));
        }
    }

    /* All required  security procedures already established */
    p_dev_rec->security_required &= ~(BTM_SEC_OUT_AUTHORIZE | BTM_SEC_IN_AUTHORIZE |
                                      BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_IN_AUTHENTICATE |
                                      BTM_SEC_OUT_ENCRYPT | BTM_SEC_IN_ENCRYPT |
                                      BTM_SEC_FORCE_MASTER | BTM_SEC_ATTEMPT_MASTER |
                                      BTM_SEC_FORCE_SLAVE | BTM_SEC_ATTEMPT_SLAVE);

    BTM_TRACE_EVENT2 ("Security Manager: trusted:0x%04x%04x", p_dev_rec->trusted_mask[1], p_dev_rec->trusted_mask[0]);
    BTM_TRACE_EVENT0 ("Security Manager: access granted");

    return(BTM_SUCCESS);
}


/*******************************************************************************
**
** Function         btm_sec_start_get_name
**
** Description      This function is called to start get name procedure
**
** Returns          TRUE if started
**
*******************************************************************************/
static BOOLEAN btm_sec_start_get_name (tBTM_SEC_DEV_REC *p_dev_rec)
{
    UINT8 tempstate = p_dev_rec->sec_state;

    p_dev_rec->sec_state = BTM_SEC_STATE_GETTING_NAME;

    /* Device should be connected, no need to provide correct page params */
    /* 0 and NULL are as timeout and callback params because they are not used in security get name case */
    if ((btm_initiate_rem_name (p_dev_rec->bd_addr, NULL, BTM_RMT_NAME_SEC,
                                0, NULL)) != BTM_CMD_STARTED)
    {
        p_dev_rec->sec_state = tempstate;
        return(FALSE);
    }

    return(TRUE);
}

/*******************************************************************************
**
** Function         btm_sec_start_authentication
**
** Description      This function is called to start authentication
**
** Returns          TRUE if started
**
*******************************************************************************/
static BOOLEAN btm_sec_start_authentication (tBTM_SEC_DEV_REC *p_dev_rec)
{
    p_dev_rec->sec_state = BTM_SEC_STATE_AUTHENTICATING;

    return(btsnd_hcic_auth_request (p_dev_rec->hci_handle));
}

/*******************************************************************************
**
** Function         btm_sec_start_encryption
**
** Description      This function is called to start encryption
**
** Returns          TRUE if started
**
*******************************************************************************/
static BOOLEAN btm_sec_start_encryption (tBTM_SEC_DEV_REC *p_dev_rec)
{
    if (!btsnd_hcic_set_conn_encrypt (p_dev_rec->hci_handle, TRUE))
        return(FALSE);

    p_dev_rec->sec_state = BTM_SEC_STATE_ENCRYPTING;
    return(TRUE);
}


/*******************************************************************************
**
** Function         btm_sec_start_authorization
**
** Description      This function is called to start authorization
**
** Returns          TRUE if started
**
*******************************************************************************/
static UINT8 btm_sec_start_authorization (tBTM_SEC_DEV_REC *p_dev_rec)
{
    UINT8    result;
    UINT8   *p_service_name = NULL;
    UINT8    service_id;

    if ((p_dev_rec->sec_flags & BTM_SEC_NAME_KNOWN)
        || (p_dev_rec->hci_handle == BTM_SEC_INVALID_HANDLE))
    {
        if (!btm_cb.api.p_authorize_callback)
            return(BTM_MODE_UNSUPPORTED);

        if (p_dev_rec->p_cur_service)
        {
#if BTM_SEC_SERVICE_NAME_LEN > 0
            if (p_dev_rec->is_originator)
                p_service_name = p_dev_rec->p_cur_service->orig_service_name;
            else
                p_service_name = p_dev_rec->p_cur_service->term_service_name;
#endif
            service_id = p_dev_rec->p_cur_service->service_id;
        }
        else
            service_id = 0;

        p_dev_rec->sec_state = BTM_SEC_STATE_AUTHORIZING;
        result = (*btm_cb.api.p_authorize_callback) (p_dev_rec->bd_addr,
                                                     p_dev_rec->dev_class,
                                                     p_dev_rec->sec_bd_name,
                                                     p_service_name,
                                                     service_id,
                                                     p_dev_rec->is_originator);
        if (result == BTM_SUCCESS)
        {
            p_dev_rec->sec_flags |= BTM_SEC_AUTHORIZED;
            p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;
        }
        return(result);
    }
    btm_sec_start_get_name (p_dev_rec);
    return(BTM_CMD_STARTED);
}

/*******************************************************************************
**
** Function         btm_sec_are_all_trusted
**
** Description      This function is called check if all services are trusted
**
** Returns          TRUE if all are trusted, otherwise FALSE
**
*******************************************************************************/
BOOLEAN btm_sec_are_all_trusted(UINT32 p_mask[])
{
    int trusted_inx;
    for (trusted_inx = 0; trusted_inx < BTM_SEC_SERVICE_ARRAY_SIZE; trusted_inx++)
    {
        if (p_mask[trusted_inx] != BTM_SEC_TRUST_ALL)
            return(FALSE);
    }

    return(TRUE);
}

/*******************************************************************************
**
** Function         btm_sec_find_first_serv
**
** Description      Look for the first record in the service database
**                  with specified PSM
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
static tBTM_SEC_SERV_REC *btm_sec_find_first_serv (CONNECTION_TYPE conn_type, UINT16 psm)
{
    tBTM_SEC_SERV_REC *p_serv_rec = &btm_cb.sec_serv_rec[0];
    int i;
    BOOLEAN is_originator;

#if (L2CAP_UCD_INCLUDED == TRUE)

    if ( conn_type & CONNECTION_TYPE_ORIG_MASK )
        is_originator = TRUE;
    else
        is_originator = FALSE;
#else
    is_originator = conn_type;
#endif

    if (is_originator && btm_cb.p_out_serv && btm_cb.p_out_serv->psm == psm)
    {
        /* If this is outgoing connection and the PSM matches p_out_serv,
         * use it as the current service */
        return btm_cb.p_out_serv;
    }

    /* otherwise, just find the first record with the specified PSM */
    for (i = 0; i < BTM_SEC_MAX_SERVICE_RECORDS; i++, p_serv_rec++)
    {
        if ( (p_serv_rec->security_flags & BTM_SEC_IN_USE) && (p_serv_rec->psm == psm) )
            return(p_serv_rec);
    }
    return(NULL);
}


/*******************************************************************************
**
** Function         btm_sec_find_next_serv
**
** Description      Look for the next record in the service database
**                  with specified PSM
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
static tBTM_SEC_SERV_REC *btm_sec_find_next_serv (tBTM_SEC_SERV_REC *p_cur)
{
    tBTM_SEC_SERV_REC *p_serv_rec   = &btm_cb.sec_serv_rec[0];
    int               i;

    for (i = 0; i < BTM_SEC_MAX_SERVICE_RECORDS; i++, p_serv_rec++)
    {
        if ((p_serv_rec->security_flags & BTM_SEC_IN_USE)
            && (p_serv_rec->psm == p_cur->psm) )
        {
            if (p_cur != p_serv_rec)
            {
                return(p_serv_rec);
            }
        }
    }
    return(NULL);
}


/*******************************************************************************
**
** Function         btm_sec_find_mx_serv
**
** Description      Look for the record in the service database with specified
**                  PSM and multiplexor channel information
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
static tBTM_SEC_SERV_REC *btm_sec_find_mx_serv (UINT8 is_originator, UINT16 psm,
                                                UINT32 mx_proto_id, UINT32 mx_chan_id)
{
    tBTM_SEC_SERV_REC *p_out_serv = btm_cb.p_out_serv;
    tBTM_SEC_SERV_REC *p_serv_rec = &btm_cb.sec_serv_rec[0];
    int i;

    BTM_TRACE_DEBUG0 ("btm_sec_find_mx_serv");
    if (is_originator && p_out_serv && p_out_serv->psm == psm
        && p_out_serv->mx_proto_id == mx_proto_id
        && p_out_serv->orig_mx_chan_id == mx_chan_id)
    {
        /* If this is outgoing connection and the parameters match p_out_serv,
         * use it as the current service */
        return btm_cb.p_out_serv;
    }

    /* otherwise, the old way */
    for (i = 0; i < BTM_SEC_MAX_SERVICE_RECORDS; i++, p_serv_rec++)
    {
        if ((p_serv_rec->security_flags & BTM_SEC_IN_USE)
            && (p_serv_rec->psm == psm)
            && (p_serv_rec->mx_proto_id == mx_proto_id)
            && (( is_originator && (p_serv_rec->orig_mx_chan_id  == mx_chan_id))
                || (!is_originator && (p_serv_rec->term_mx_chan_id  == mx_chan_id))))
        {
            return(p_serv_rec);
        }
    }
    return(NULL);
}


/*******************************************************************************
**
** Function         btm_sec_collision_timeout
**
** Description      Encryption could not start because of the collision
**                  try to do it again
**
** Returns          Pointer to the TLE struct
**
*******************************************************************************/
static void btm_sec_collision_timeout (TIMER_LIST_ENT *p_tle)
{
    tBTM_STATUS status;

    BTM_TRACE_EVENT0 ("btm_sec_collision_timeout()");
    btm_cb.sec_collision_tle.param = 0;

    status = btm_sec_execute_procedure (btm_cb.p_collided_dev_rec);

    /* If result is pending reply from the user or from the device is pending */
    if (status != BTM_CMD_STARTED)
    {
        /* There is no next procedure or start of procedure failed, notify the waiting layer */
        btm_sec_dev_rec_cback_event (btm_cb.p_collided_dev_rec, status);
    }
}

/*******************************************************************************
**
** Function         btm_sec_link_key_request
**
** Description      This function is called when controller requests link key
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
static void btm_send_link_key_notif (tBTM_SEC_DEV_REC *p_dev_rec)
{
    if (btm_cb.api.p_link_key_callback)
        (*btm_cb.api.p_link_key_callback) (p_dev_rec->bd_addr, p_dev_rec->dev_class,
                                           p_dev_rec->sec_bd_name, p_dev_rec->link_key,
                                           p_dev_rec->link_key_type);
}

/*******************************************************************************
**
** Function         BTM_ReadTrustedMask
**
** Description      Get trusted mask for the peer device
**
** Parameters:      bd_addr   - Address of the device
**
** Returns          NULL, if the device record is not found.
**                  otherwise, the trusted mask
**
*******************************************************************************/
UINT32 * BTM_ReadTrustedMask (BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    if ((p_dev_rec = btm_find_dev (bd_addr)) != NULL)
    {
        return(p_dev_rec->trusted_mask);
    }
    else
    {
        return NULL;
    }
}

/*******************************************************************************
**
** Function         btm_restore_mode
**
** Description      This function returns the security mode to previous setting
**                  if it was changed during bonding.
**
**
** Parameters:      void
**
*******************************************************************************/
static void btm_restore_mode(void)
{
    if (btm_cb.security_mode_changed)
    {
        btm_cb.security_mode_changed = FALSE;
        BTM_TRACE_DEBUG1("btm_restore_mode: Authen Enable -> %d", (btm_cb.security_mode == BTM_SEC_MODE_LINK));
        btsnd_hcic_write_auth_enable ((UINT8)(btm_cb.security_mode == BTM_SEC_MODE_LINK));
    }

    if (btm_cb.pin_type_changed)
    {
        btm_cb.pin_type_changed = FALSE;
        btsnd_hcic_write_pin_type (btm_cb.cfg.pin_type);
    }
}


/*******************************************************************************
**
** Function         btm_sec_find_dev_by_sec_state
**
** Description      Look for the record in the device database for the device
**                  which is being authenticated or encrypted
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
tBTM_SEC_DEV_REC *btm_sec_find_dev_by_sec_state (UINT8 state)
{
    tBTM_SEC_DEV_REC *p_dev_rec = &btm_cb.sec_dev_rec[0];
    int i;

    for (i = 0; i < BTM_SEC_MAX_DEVICE_RECORDS; i++, p_dev_rec++)
    {
        if ((p_dev_rec->sec_flags & BTM_SEC_IN_USE)
            && (p_dev_rec->sec_state == state))
            return(p_dev_rec);
    }
    return(NULL);
}

/*******************************************************************************
**
** Function         BTM_snd_conn_encrypt
**
** Description      This function is called to start/stop encryption
**                  Used by JSR-82
**
** Returns          TRUE if request started
**
*******************************************************************************/
BOOLEAN BTM_snd_conn_encrypt (UINT16  handle, BOOLEAN enable)
{
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev_by_handle (handle);

    BTM_TRACE_EVENT2 ("BTM_snd_conn_encrypt Security Manager: encrypt_change p_dev_rec : 0x%x, enable = %s", p_dev_rec, (enable == TRUE) ? "TRUE" : "FALSE");

    if (!p_dev_rec)
    {
        BTM_TRACE_EVENT1 ("BTM_snd_conn_encrypt Error no  p_dev_rec : 0x%x\n", p_dev_rec);
        return(FALSE);
    }

    if ( p_dev_rec->sec_state == BTM_SEC_STATE_IDLE)
    {
        if (!btsnd_hcic_set_conn_encrypt (handle, enable))
            return(FALSE);

        p_dev_rec->sec_state = BTM_SEC_STATE_ENCRYPTING;

        return(TRUE);
    }
    else
        return(FALSE);
}

/*******************************************************************************
**
** Function         btm_sec_change_pairing_state
**
** Description      This function is called to change pairing state
**
*******************************************************************************/
static void btm_sec_change_pairing_state (tBTM_PAIRING_STATE new_state)
{
    tBTM_PAIRING_STATE  old_state = btm_cb.pairing_state;

    BTM_TRACE_EVENT1 ("btm_sec_change_pairing_state  Old: %s",  btm_pair_state_descr(btm_cb.pairing_state));
    BTM_TRACE_EVENT2 ("btm_sec_change_pairing_state  New: %s pairing_flags:0x%x",btm_pair_state_descr(new_state), btm_cb.pairing_flags);

    btm_cb.pairing_state = new_state;

    if (new_state == BTM_PAIR_STATE_IDLE)
    {
        btu_stop_timer (&btm_cb.pairing_tle);

        btm_cb.pairing_flags = 0;
        btm_cb.pin_code_len  = 0;

        /* Make sure the the lcb shows we are not bonding */
        l2cu_update_lcb_4_bonding (btm_cb.pairing_bda, FALSE);

        btm_restore_mode();
        btm_sec_check_pending_reqs();
        btm_inq_clear_ssp();

        memset (btm_cb.pairing_bda, 0xFF, BD_ADDR_LEN);
    }
    else
    {
        /* If transitionng out of idle, mark the lcb as bonding */
        if (old_state == BTM_PAIR_STATE_IDLE)
            l2cu_update_lcb_4_bonding (btm_cb.pairing_bda, TRUE);

        btm_cb.pairing_tle.param = (TIMER_PARAM_TYPE)btm_sec_pairing_timeout;

        btu_start_timer (&btm_cb.pairing_tle, BTU_TTYPE_USER_FUNC, BTM_SEC_TIMEOUT_VALUE);
    }
}


/*******************************************************************************
**
** Function         btm_pair_state_descr
**
** Description      Return state description for tracing
**
*******************************************************************************/
#if (BT_USE_TRACES == TRUE)
static char *btm_pair_state_descr (tBTM_PAIRING_STATE state)
{
#if (BT_TRACE_VERBOSE == TRUE)
    switch (state)
    {
        case BTM_PAIR_STATE_IDLE:                   return("IDLE");
        case BTM_PAIR_STATE_GET_REM_NAME:           return("GET_REM_NAME");
        case BTM_PAIR_STATE_WAIT_PIN_REQ:           return("WAIT_PIN_REQ");
        case BTM_PAIR_STATE_WAIT_LOCAL_PIN:         return("WAIT_LOCAL_PIN");
        case BTM_PAIR_STATE_WAIT_NUMERIC_CONFIRM:   return("WAIT_NUM_CONFIRM");
        case BTM_PAIR_STATE_KEY_ENTRY:              return("KEY_ENTRY");
        case BTM_PAIR_STATE_WAIT_LOCAL_OOB_RSP:     return("WAIT_LOCAL_OOB_RSP");
        case BTM_PAIR_STATE_WAIT_LOCAL_IOCAPS:      return("WAIT_LOCAL_IOCAPS");
        case BTM_PAIR_STATE_INCOMING_SSP:           return("INCOMING_SSP");
        case BTM_PAIR_STATE_WAIT_AUTH_COMPLETE:     return("WAIT_AUTH_COMPLETE");
        case BTM_PAIR_STATE_WAIT_DISCONNECT:        return("WAIT_DISCONNECT");
    }

    return("???");
#else
    sprintf(btm_cb.state_temp_buffer,"%hu",state);

    return(btm_cb.state_temp_buffer);
#endif
}
#endif


/*******************************************************************************
**
** Function         btm_sec_dev_rec_cback_event
**
** Description      This function calls the callback function with the given
**                  result and clear the callback function.
**
** Parameters:      void
**
*******************************************************************************/
void btm_sec_dev_rec_cback_event (tBTM_SEC_DEV_REC *p_dev_rec, UINT8 res)
{
    tBTM_SEC_CALLBACK   *p_callback = p_dev_rec->p_callback;

    if (p_dev_rec->p_callback)
    {
        p_dev_rec->p_callback = NULL;

        (*p_callback) (p_dev_rec->bd_addr, p_dev_rec->p_ref_data, res);

    }
    btm_sec_check_pending_reqs();
}

/*******************************************************************************
**
** Function         btm_sec_queue_mx_request
**
** Description      Return state description for tracing
**
*******************************************************************************/
static BOOLEAN btm_sec_queue_mx_request (BD_ADDR bd_addr,  UINT16 psm,  BOOLEAN is_orig,
                                         UINT32 mx_proto_id, UINT32 mx_chan_id,
                                         tBTM_SEC_CALLBACK *p_callback, void *p_ref_data)
{
    tBTM_SEC_QUEUE_ENTRY    *p_e;

    p_e = (tBTM_SEC_QUEUE_ENTRY *)GKI_getbuf (sizeof(tBTM_SEC_QUEUE_ENTRY));

    if (p_e)
    {
        p_e->psm            = psm;
        p_e->is_orig        = is_orig;
        p_e->p_callback     = p_callback;
        p_e->p_ref_data     = p_ref_data;
        p_e->mx_proto_id    = mx_proto_id;
        p_e->mx_chan_id     = mx_chan_id;

        memcpy (p_e->bd_addr, bd_addr, BD_ADDR_LEN);

        BTM_TRACE_EVENT4 ("btm_sec_queue_mx_request() PSM: 0x%04x  Is_Orig: %u  mx_proto_id: %u  mx_chan_id: %u",
                          psm, is_orig, mx_proto_id, mx_chan_id);

        GKI_enqueue (&btm_cb.sec_pending_q, p_e);

        return(TRUE);
    }

    return(FALSE);
}

static BOOLEAN btm_sec_check_prefetch_pin (tBTM_SEC_DEV_REC  *p_dev_rec)
{
    UINT8 major = (UINT8)(p_dev_rec->dev_class[1] & BTM_COD_MAJOR_CLASS_MASK);
    UINT8 minor = (UINT8)(p_dev_rec->dev_class[2] & BTM_COD_MINOR_CLASS_MASK);
    BOOLEAN rv = FALSE;

    if ((major == BTM_COD_MAJOR_AUDIO)
        &&  ((minor == BTM_COD_MINOR_CONFM_HANDSFREE) || (minor == BTM_COD_MINOR_CAR_AUDIO)) )
    {
        BTM_TRACE_EVENT2 ("btm_sec_check_prefetch_pin: Skipping pre-fetch PIN for carkit COD Major: 0x%02x Minor: 0x%02x", major, minor);

        if (btm_cb.security_mode_changed == FALSE)
        {
            btm_cb.security_mode_changed = TRUE;
#ifdef APPL_AUTH_WRITE_EXCEPTION
            if(!(APPL_AUTH_WRITE_EXCEPTION)(p_dev_rec->bd_addr))
#endif
                btsnd_hcic_write_auth_enable (TRUE);
        }
    }
    else
    {
        btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_LOCAL_PIN);

        /* If we got a PIN, use that, else try to get one */
        if (btm_cb.pin_code_len)
        {
            BTM_PINCodeReply (p_dev_rec->bd_addr, BTM_SUCCESS, btm_cb.pin_code_len, btm_cb.pin_code, p_dev_rec->trusted_mask);
        }
        else
        {
            /* pin was not supplied - pre-fetch pin code now */
            if (btm_cb.api.p_pin_callback && ((btm_cb.pairing_flags & BTM_PAIR_FLAGS_PIN_REQD) == 0))
            {
                BTM_TRACE_DEBUG0("btm_sec_check_prefetch_pin: PIN code callback called");
                if (btm_bda_to_acl(p_dev_rec->bd_addr) == NULL)
                btm_cb.pairing_flags |= BTM_PAIR_FLAGS_PIN_REQD;
                (btm_cb.api.p_pin_callback) (p_dev_rec->bd_addr, p_dev_rec->dev_class, p_dev_rec->sec_bd_name);
            }
        }

        rv = TRUE;
    }

    return rv;
}

#if (BLE_INCLUDED == TRUE)
/*******************************************************************************
**
** Function         btm_sec_clear_ble_keys
**
** Description      This function is called to clear out the BLE keys.
**                  Typically when devices are removed in BTM_SecDeleteDevice,
**                  or when a new BT Link key is generated.
**
** Returns          void
**
*******************************************************************************/
void btm_sec_clear_ble_keys (tBTM_SEC_DEV_REC  *p_dev_rec)
{

    BTM_TRACE_DEBUG0 ("btm_sec_clear_ble_keys: Clearing BLE Keys");
#if (SMP_INCLUDED== TRUE)
    p_dev_rec->ble.key_type = 0;
    memset (&p_dev_rec->ble.keys, 0, sizeof(tBTM_SEC_BLE_KEYS));
#endif
    gatt_delete_dev_from_srv_chg_clt_list(p_dev_rec->bd_addr);
}


/*******************************************************************************
**
** Function         btm_sec_is_a_bonded_dev
**
** Description       Is the specified device is a bonded device
**
** Returns          TRUE - dev is bonded
**
*******************************************************************************/
BOOLEAN btm_sec_is_a_bonded_dev (BD_ADDR bda)
{

    tBTM_SEC_DEV_REC *p_dev_rec= btm_find_dev (bda);
    BOOLEAN is_bonded= FALSE;

#if (SMP_INCLUDED== TRUE)
    if (p_dev_rec && (p_dev_rec->ble.key_type || (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN)))
    {
        is_bonded = TRUE;
    }
#endif
    BTM_TRACE_DEBUG1 ("btm_sec_is_a_bonded_dev is_bonded=%d", is_bonded);
    return(is_bonded);
}

/*******************************************************************************
**
** Function         btm_sec_find_bonded_dev
**
** Description      Find a bonded device starting from the specified index
**
** Returns          TRUE - found a bonded device
**
*******************************************************************************/
BOOLEAN btm_sec_find_bonded_dev (UINT8 start_idx, UINT8 *p_found_idx, tBTM_SEC_DEV_REC *p_rec)
{
    BOOLEAN found= FALSE;

#if (SMP_INCLUDED== TRUE)
    tBTM_SEC_DEV_REC *p_dev_rec;
    int i;
    if (start_idx >= BTM_SEC_MAX_DEVICE_RECORDS)
    {
        BTM_TRACE_DEBUG0 ("LE bonded device not found");
        return found;
    }

    p_dev_rec = &btm_cb.sec_dev_rec[start_idx];
    for (i = start_idx; i < BTM_SEC_MAX_DEVICE_RECORDS; i++, p_dev_rec++)
    {
        if (p_dev_rec->ble.key_type || (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN))
        {
            *p_found_idx = i;
            p_rec = p_dev_rec;
            break;
        }
    }
    BTM_TRACE_DEBUG1 ("btm_sec_find_bonded_dev=%d", found);
#endif
    return(found);
}
#endif /* BLE_INCLUDED */

