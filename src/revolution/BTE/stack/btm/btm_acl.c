/******************************************************************************
 *
 *  Copyright (C) 2000-2012 Broadcom Corporation
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
 *  This file contains functions that handle ACL connections. This includes
 *  operations such as hold and sniff modes, supported packet types.
 *
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>

#include "bt_types.h"
#include "bt_target.h"
#include "gki.h"
#include "hcimsgs.h"
#include "btu.h"
#include "btm_api.h"
#include "btm_int.h"
#include "l2c_int.h"
#include "hcidefs.h"
static void btm_establish_continue (tACL_CONN *p_acl_cb);

#define BTM_DEV_REPLY_TIMEOUT   3       /* 3 second timeout waiting for responses */

/*******************************************************************************
**
** Function         btm_acl_init
**
** Description      This function is called at BTM startup to initialize
**
** Returns          void
**
*******************************************************************************/
void btm_acl_init (void)
{
    BTM_TRACE_DEBUG0 ("btm_acl_init");
#if 0  /* cleared in btm_init; put back in if called from anywhere else! */
    memset (&btm_cb.acl_db, 0, sizeof (btm_cb.acl_db));
#if RFCOMM_INCLUDED == TRUE
    memset (btm_cb.btm_scn, 0, BTM_MAX_SCN);          /* Initialize the SCN usage to FALSE */
#endif
    btm_cb.btm_def_link_policy     = 0;
#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
    btm_cb.p_bl_changed_cb         = NULL;
#else
    btm_cb.p_acl_changed_cb        = NULL;
#endif
#endif

    /* Initialize nonzero defaults */
    btm_cb.btm_def_link_super_tout = HCI_DEFAULT_INACT_TOUT;
    btm_cb.acl_disc_reason         = 0xff ;
}

/*******************************************************************************
**
** Function         btm_bda_to_acl
**
** Description      This function returns the FIRST acl_db entry for the passed BDA.
**
** Returns          Returns pointer to the ACL DB for the requested BDA if found.
**                  NULL if not found.
**
*******************************************************************************/
tACL_CONN *btm_bda_to_acl (BD_ADDR bda)
{
    tACL_CONN   *p = &btm_cb.acl_db[0];
    UINT16       xx;
    if (bda)
    {
        for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p++)
        {
            if ((p->in_use) && (!memcmp (p->remote_addr, bda, BD_ADDR_LEN)))
            {
                BTM_TRACE_DEBUG0 ("btm_bda_to_acl found");
                return(p);
            }
        }
    }
    BTM_TRACE_DEBUG0 ("btm_bda_to_acl Not found");

    /* If here, no BD Addr found */
    return((tACL_CONN *)NULL);
}

/*******************************************************************************
**
** Function         btm_handle_to_acl_index
**
** Description      This function returns the FIRST acl_db entry for the passed hci_handle.
**
** Returns          index to the acl_db or MAX_L2CAP_LINKS.
**
*******************************************************************************/
UINT8 btm_handle_to_acl_index (UINT16 hci_handle)
{
    tACL_CONN   *p = &btm_cb.acl_db[0];
    UINT8       xx;
    BTM_TRACE_DEBUG0 ("btm_handle_to_acl_index");
    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p++)
    {
        if ((p->in_use) && (p->hci_handle == hci_handle))
        {
            break;
        }
    }

    /* If here, no BD Addr found */
    return(xx);
}


/*******************************************************************************
**
** Function         btm_acl_created
**
** Description      This function is called by L2CAP when an ACL connection
**                  is created.
**
** Returns          void
**
*******************************************************************************/
void btm_acl_created (BD_ADDR bda, DEV_CLASS dc, BD_NAME bdn,
                      UINT16 hci_handle, UINT8 link_role, UINT8 is_le_link)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    UINT8             yy;
    tACL_CONN        *p;
    UINT8             xx;

    BTM_TRACE_DEBUG3 ("btm_acl_created hci_handle=%d link_role=%d  is_le_link=%d",
                      hci_handle,link_role, is_le_link);
    /* Ensure we don't have duplicates */
    p = btm_bda_to_acl(bda);
    if (p != (tACL_CONN *)NULL)
    {
        p->hci_handle = hci_handle;
        p->link_role  = link_role;
#if BLE_INCLUDED == TRUE
        p->is_le_link = is_le_link;
#endif
        BTM_TRACE_DEBUG6 ("Duplicate btm_acl_created: RemBdAddr: %02x%02x%02x%02x%02x%02x",
                          bda[0], bda[1], bda[2], bda[3], bda[4], bda[5]);
        BTM_SetLinkPolicy(p->remote_addr, &btm_cb.btm_def_link_policy);
        return;
    }

    /* Allocate acl_db entry */
    for (xx = 0, p = &btm_cb.acl_db[0]; xx < MAX_L2CAP_LINKS; xx++, p++)
    {
        if (!p->in_use)
        {
            p->in_use            = TRUE;
            p->hci_handle        = hci_handle;
            p->link_role         = link_role;
            p->link_up_issued    = FALSE;
#if BLE_INCLUDED == TRUE
            p->is_le_link        = is_le_link;
#endif
            p->restore_pkt_types = 0;   /* Only exists while SCO is active */
            p->switch_role_state = BTM_ACL_SWKEY_STATE_IDLE;

#if BTM_PWR_MGR_INCLUDED == FALSE
            p->mode             = BTM_ACL_MODE_NORMAL;
#else
            btm_pm_sm_alloc(xx);
#endif /* BTM_PWR_MGR_INCLUDED == FALSE */

            memcpy (p->remote_addr, bda, BD_ADDR_LEN);

            if (dc)
                memcpy (p->remote_dc, dc, DEV_CLASS_LEN);

            if (bdn)
                memcpy (p->remote_name, bdn, BTM_MAX_REM_BD_NAME_LEN);


            /* Check if we already know features for this device */
            p_dev_rec = btm_find_dev_by_handle (hci_handle);

#if (BLE_INCLUDED == TRUE)
            if (p_dev_rec )
            {
                BTM_TRACE_DEBUG1 ("device_type=0x%x", p_dev_rec->device_type);
            }
#endif


            if (p_dev_rec
#if (BLE_INCLUDED == TRUE)
                && p_dev_rec->device_type != BT_DEVICE_TYPE_BLE
#endif
               )
            {

                /* if BR/EDR do something more */
                btsnd_hcic_read_rmt_clk_offset (p->hci_handle);
                btsnd_hcic_rmt_ver_req (p->hci_handle);

                for (yy = 0; yy < BD_FEATURES_LEN; yy++)
                {
                    if (p_dev_rec->features[yy])
                    {
                        memcpy (p->features, p_dev_rec->features, BD_FEATURES_LEN);
                        if (BTM_SEC_MODE_SP == btm_cb.security_mode &&
                            HCI_SIMPLE_PAIRING_SUPPORTED(p->features))
                        {
                            /* if SM4 supported, check peer support for SM4
                             * The remote controller supports SSP according to saved remote features
                             * read the extended feature page 1 for the host support for SSP */
                            if (btsnd_hcic_rmt_ext_features (p_dev_rec->hci_handle, 1))
                                return;
                        }
                        /* peer does not support SSP */
                        p_dev_rec->sm4 |= BTM_SM4_KNOWN;

                        btm_establish_continue (p);
                        return;
                    }
                }
            }
#if (BLE_INCLUDED == TRUE)
            /* If here, features are not known yet */
            if (p_dev_rec && p_dev_rec->device_type == BT_DEVICE_TYPE_BLE)
            {
                btm_establish_continue(p);

                if (link_role == HCI_ROLE_MASTER)
                {
                    btm_ble_update_bg_state();
                    btm_ble_resume_bg_conn (NULL, FALSE);

                    btsnd_hcic_ble_read_remote_feat(p->hci_handle);
                }
            }
            else
#endif
            {
                btsnd_hcic_rmt_features_req (p->hci_handle);
            }

            /* read page 1 - on rmt feature event for buffer reasons */
            return;
        }
    }
}


/*******************************************************************************
**
** Function         btm_acl_report_role_change
**
** Description      This function is called when the local device is deemed
**                  to be down. It notifies L2CAP of the failure.
**
** Returns          void
**
*******************************************************************************/
void btm_acl_report_role_change (UINT8 hci_status, BD_ADDR bda)
{
    tBTM_ROLE_SWITCH_CMPL   ref_data;
    BTM_TRACE_DEBUG0 ("btm_acl_report_role_change");
    if (btm_cb.devcb.p_switch_role_cb && (bda &&
                                          (0 == memcmp(btm_cb.devcb.switch_role_ref_data.remote_bd_addr, bda, BD_ADDR_LEN))))
    {
        memset (&btm_cb.devcb.switch_role_ref_data, 0, sizeof(tBTM_ROLE_SWITCH_CMPL));
        ref_data.hci_status = hci_status;
        memcpy (&ref_data, &btm_cb.devcb.switch_role_ref_data, sizeof(tBTM_ROLE_SWITCH_CMPL));
        (*btm_cb.devcb.p_switch_role_cb)(&ref_data);
        btm_cb.devcb.p_switch_role_cb = NULL;
    }
}

/*******************************************************************************
**
** Function         btm_acl_removed
**
** Description      This function is called by L2CAP when an ACL connection
**                  is removed. Since only L2CAP creates ACL links, we use
**                  the L2CAP link index as our index into the control blocks.
**
** Returns          void
**
*******************************************************************************/
void btm_acl_removed (BD_ADDR bda)
{
    tACL_CONN   *p;
#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
    tBTM_BL_EVENT_DATA  evt_data;
#endif
#if (defined BLE_INCLUDED && BLE_INCLUDED == TRUE)
    tBTM_SEC_DEV_REC *p_dev_rec=NULL;
    UINT16 combined_mode;
#endif

    BTM_TRACE_DEBUG0 ("btm_acl_removed");
    p = btm_bda_to_acl(bda);
    if (p != (tACL_CONN *)NULL)
    {
        p->in_use = FALSE;

        /* if the disconnected channel has a pending role switch, clear it now */
        btm_acl_report_role_change(HCI_ERR_NO_CONNECTION, bda);

        /* Only notify if link up has had a chance to be issued */
        if (p->link_up_issued)
        {
            p->link_up_issued = FALSE;

            /* If anyone cares, tell him database changed */
#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
            if (btm_cb.p_bl_changed_cb)
            {
                evt_data.event = BTM_BL_DISCN_EVT;
                evt_data.discn.p_bda = bda;

                (*btm_cb.p_bl_changed_cb)(&evt_data);
            }

            btm_acl_update_busy_level (BTM_BLI_ACL_DOWN_EVT);
#else
            if (btm_cb.p_acl_changed_cb)
                (*btm_cb.p_acl_changed_cb) (bda, NULL, NULL, NULL, FALSE);
#endif
        }

#if (defined BLE_INCLUDED && BLE_INCLUDED == TRUE)

        BTM_TRACE_DEBUG4 ("acl hci_handle=%d is_le_link=%d connectable_mode=0x%0x link_role=%d",
                          p->hci_handle,
                          p->is_le_link,
                          btm_cb.ble_ctr_cb.inq_var.connectable_mode,
                          p->link_role);


        /* If we are LE connectable, check if we need to start advertising again */
        if ( p->is_le_link && (btm_cb.ble_ctr_cb.inq_var.connectable_mode != BTM_BLE_NON_CONNECTABLE) )
        {
            tACL_CONN   *pa = &btm_cb.acl_db[0];
            UINT16       xx;

            for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, pa++)
            {
                /* If any other LE link is up, we are still not connectable */
                if (pa->in_use && pa->is_le_link)
                    return;
            }
            combined_mode = (btm_cb.ble_ctr_cb.inq_var.connectable_mode | btm_cb.btm_inq_vars.connectable_mode);
            btm_ble_set_connectability ( combined_mode );
        }

        p_dev_rec = btm_find_dev(bda);
        if ( p_dev_rec)
        {
            BTM_TRACE_DEBUG1("before update p_dev_rec->sec_flags=0x%x", p_dev_rec->sec_flags);
            if (p->is_le_link)
            {
                BTM_TRACE_DEBUG0("LE link down");
                p_dev_rec->sec_flags &= ~(BTM_SEC_ENCRYPTED | BTM_SEC_ROLE_SWITCHED);
                if ( (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN) == 0)
                {
                    BTM_TRACE_DEBUG0("Not Bonded");
                    p_dev_rec->sec_flags &= ~(BTM_SEC_AUTHENTICATED | BTM_SEC_LINK_KEY_AUTHED);
                }
                else
                {
                    BTM_TRACE_DEBUG0("Bonded");
                }
            }
            else
            {
                BTM_TRACE_DEBUG0("Bletooth link down");
                p_dev_rec->sec_flags &= ~(BTM_SEC_AUTHORIZED | BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED | BTM_SEC_ROLE_SWITCHED);
            }
            BTM_TRACE_DEBUG1("after update p_dev_rec->sec_flags=0x%x", p_dev_rec->sec_flags);
        }
        else
        {
            BTM_TRACE_ERROR0("Device not found");

        }
#endif

        return;
    }
}


/*******************************************************************************
**
** Function         btm_acl_device_down
**
** Description      This function is called when the local device is deemed
**                  to be down. It notifies L2CAP of the failure.
**
** Returns          void
**
*******************************************************************************/
void btm_acl_device_down (void)
{
    tACL_CONN   *p = &btm_cb.acl_db[0];
    UINT16      xx;
    BTM_TRACE_DEBUG0 ("btm_acl_device_down");
    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p++)
    {
        if (p->in_use)
        {
            BTM_TRACE_DEBUG1 ("hci_handle=%d HCI_ERR_HW_FAILURE ",p->hci_handle );
            l2c_link_hci_disc_comp (p->hci_handle, HCI_ERR_HW_FAILURE);
        }
    }
}

#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
/*******************************************************************************
**
** Function         btm_acl_update_busy_level
**
** Description      This function is called to update the busy level of the system
**                  .
**
** Returns          void
**
*******************************************************************************/
void btm_acl_update_busy_level (tBTM_BLI_EVENT event)
{
    tBTM_BL_UPDATE_DATA  evt;
    UINT8 busy_level;
    BTM_TRACE_DEBUG0 ("btm_acl_update_busy_level");
    switch (event)
    {
        case BTM_BLI_ACL_UP_EVT:
            BTM_TRACE_DEBUG0 ("BTM_BLI_ACL_UP_EVT");
            btm_cb.num_acl++;
            busy_level = (UINT8)btm_cb.num_acl;
            break;
        case BTM_BLI_ACL_DOWN_EVT:
            if (btm_cb.num_acl)
            {
                btm_cb.num_acl--;
                BTM_TRACE_DEBUG1 ("BTM_BLI_ACL_DOWN_EVT", btm_cb.num_acl);
            }
            else
            {
                BTM_TRACE_ERROR0 ("BTM_BLI_ACL_DOWN_EVT issued, but num_acl already zero !!!");
            }
            busy_level = (UINT8)btm_cb.num_acl;
            break;
        case BTM_BLI_PAGE_EVT:
            BTM_TRACE_DEBUG0 ("BTM_BLI_PAGE_EVT");
            btm_cb.is_paging = TRUE;
            busy_level = BTM_BL_PAGING_STARTED;
            break;
        case BTM_BLI_PAGE_DONE_EVT:
            BTM_TRACE_DEBUG0 ("BTM_BLI_PAGE_DONE_EVT");
            btm_cb.is_paging = FALSE;
            busy_level = BTM_BL_PAGING_COMPLETE;
            break;
        case BTM_BLI_INQ_EVT:
            BTM_TRACE_DEBUG0 ("BTM_BLI_INQ_EVT");
            btm_cb.is_inquiry = TRUE;
            busy_level = BTM_BL_INQUIRY_STARTED;
            break;
        case BTM_BLI_INQ_CANCEL_EVT:
            BTM_TRACE_DEBUG0 ("BTM_BLI_INQ_CANCEL_EVT");
            btm_cb.is_inquiry = FALSE;
            busy_level = BTM_BL_INQUIRY_CANCELLED;
            break;
        case BTM_BLI_INQ_DONE_EVT:
            BTM_TRACE_DEBUG0 ("BTM_BLI_INQ_DONE_EVT");
            btm_cb.is_inquiry = FALSE;
            busy_level = BTM_BL_INQUIRY_COMPLETE;
            break;
    }

    if (busy_level != btm_cb.busy_level)
    {
        evt.event         = BTM_BL_UPDATE_EVT;
        evt.busy_level    = busy_level;
        btm_cb.busy_level = busy_level;
        if (btm_cb.p_bl_changed_cb && (btm_cb.bl_evt_mask & BTM_BL_UPDATE_MASK))
        {
            (*btm_cb.p_bl_changed_cb)((tBTM_BL_EVENT_DATA *)&evt);
        }
    }
}
#endif


/*******************************************************************************
**
** Function         BTM_GetRole
**
** Description      This function is called to get the role of the local device
**                  for the ACL connection with the specified remote device
**
** Returns          BTM_SUCCESS if connection exists.
**                  BTM_UNKNOWN_ADDR if no active link with bd addr specified
**
*******************************************************************************/
tBTM_STATUS BTM_GetRole (BD_ADDR remote_bd_addr, UINT8 *p_role)
{
    tACL_CONN   *p;
    BTM_TRACE_DEBUG0 ("BTM_GetRole");
    if ((p = btm_bda_to_acl(remote_bd_addr)) == NULL)
    {
        *p_role = BTM_ROLE_UNDEFINED;
        return(BTM_UNKNOWN_ADDR);
    }

    /* Get the current role */
    *p_role = p->link_role;
    return(BTM_SUCCESS);
}


/*******************************************************************************
**
** Function         BTM_SwitchRole
**
** Description      This function is called to switch role between master and
**                  slave.  If role is already set it will do nothing.  If the
**                  command was initiated, the callback function is called upon
**                  completion.
**
** Returns          BTM_SUCCESS if already in specified role.
**                  BTM_CMD_STARTED if command issued to controller.
**                  BTM_NO_RESOURCES if couldn't allocate memory to issue command
**                  BTM_UNKNOWN_ADDR if no active link with bd addr specified
**                  BTM_MODE_UNSUPPORTED if local device does not support role switching
**                  BTM_BUSY if the previous command is not completed
**
*******************************************************************************/
tBTM_STATUS BTM_SwitchRole (BD_ADDR remote_bd_addr, UINT8 new_role, tBTM_CMPL_CB *p_cb)
{
    tACL_CONN   *p;
    tBTM_SEC_DEV_REC  *p_dev_rec = NULL;
#if BTM_SCO_INCLUDED == TRUE
    BOOLEAN    is_sco_active;
#endif
#if BTM_PWR_MGR_INCLUDED == TRUE
    tBTM_STATUS  status;
    tBTM_PM_MODE pwr_mode;
    tBTM_PM_PWR_MD settings;
#endif
#if (BT_USE_TRACES == TRUE)
    BD_ADDR_PTR  p_bda;
#endif
    BTM_TRACE_API6 ("BTM_SwitchRole BDA: %02x-%02x-%02x-%02x-%02x-%02x",
                    remote_bd_addr[0], remote_bd_addr[1], remote_bd_addr[2],
                    remote_bd_addr[3], remote_bd_addr[4], remote_bd_addr[5]);

    /* Make sure the local device supports switching */
    if (!(HCI_SWITCH_SUPPORTED(btm_cb.devcb.local_features)))
        return(BTM_MODE_UNSUPPORTED);

    if (btm_cb.devcb.p_switch_role_cb && p_cb)
    {
#if (BT_USE_TRACES == TRUE)
        p_bda = btm_cb.devcb.switch_role_ref_data.remote_bd_addr;
        BTM_TRACE_DEBUG6 ("Role switch on other device is in progress 0x%02x%02x%02x%02x%02x%02x",
                          p_bda[0], p_bda[1], p_bda[2],
                          p_bda[3], p_bda[4], p_bda[5]);
#endif
        return(BTM_BUSY);
    }

    if ((p = btm_bda_to_acl(remote_bd_addr)) == NULL)
        return(BTM_UNKNOWN_ADDR);

    /* Finished if already in desired role */
    if (p->link_role == new_role)
        return(BTM_SUCCESS);

#if BTM_SCO_INCLUDED == TRUE
    /* Check if there is any SCO Active on this BD Address */
    is_sco_active = btm_is_sco_active_by_bdaddr(remote_bd_addr);

    if (is_sco_active == TRUE)
        return(BTM_NO_RESOURCES);
#endif

    /* Ignore role switch request if the previous request was not completed */
    if (p->switch_role_state != BTM_ACL_SWKEY_STATE_IDLE)
    {
        BTM_TRACE_DEBUG1 ("BTM_SwitchRole busy: %d",
                          p->switch_role_state);
        return(BTM_BUSY);
    }

    /* Cannot switch role while parked or sniffing */
#if BTM_PWR_MGR_INCLUDED == FALSE
    if (p->mode == HCI_MODE_PARK)
    {
        if (!btsnd_hcic_exit_park_mode (p->hci_handle))
            return(BTM_NO_RESOURCES);

        p->switch_role_state = BTM_ACL_SWKEY_STATE_MODE_CHANGE;
    }
    else if (p->mode == HCI_MODE_SNIFF)
    {
        if (!btsnd_hcic_exit_sniff_mode (p->hci_handle))
            return(BTM_NO_RESOURCES);

        p->switch_role_state = BTM_ACL_SWKEY_STATE_MODE_CHANGE;
    }
#else   /* power manager is in use */

    if ((status = BTM_ReadPowerMode(p->remote_addr, &pwr_mode)) != BTM_SUCCESS)
        return(status);

    /* Wake up the link if in sniff or park before attempting switch */
    if (pwr_mode == BTM_PM_MD_PARK || pwr_mode == BTM_PM_MD_SNIFF)
    {
/* Coverity FALSE-POSITIVE error from Coverity tool. Please do NOT remove following comment.     */
/* coverity[uninit_use_in_call] False-positive: setting the mode to BTM_PM_MD_ACTIVE only uses settings.mode
                                the other data members of tBTM_PM_PWR_MD are ignored
*/
        settings.mode = BTM_PM_MD_ACTIVE;
        status = BTM_SetPowerMode (BTM_PM_SET_ONLY_ID, p->remote_addr, &settings);
        if (status != BTM_CMD_STARTED)
            return(BTM_WRONG_MODE);

        p->switch_role_state = BTM_ACL_SWKEY_STATE_MODE_CHANGE;
    }
#endif
    /* some devices do not support switch while encryption is on */
    else
    {
        if (((p_dev_rec = btm_find_dev (remote_bd_addr)) != NULL)
            && ((p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED) != 0)
            && !BTM_EPR_AVAILABLE(p))
        {
            /* bypass turning off encryption if change link key is already doing it */
            if (p->encrypt_state != BTM_ACL_ENCRYPT_STATE_ENCRYPT_OFF)
            {
                if (!btsnd_hcic_set_conn_encrypt (p->hci_handle, FALSE))
                    return(BTM_NO_RESOURCES);
                else
                    p->encrypt_state = BTM_ACL_ENCRYPT_STATE_ENCRYPT_OFF;
            }

            p->switch_role_state = BTM_ACL_SWKEY_STATE_ENCRYPTION_OFF;
        }
        else
        {
            if (!btsnd_hcic_switch_role (remote_bd_addr, new_role))
                return(BTM_NO_RESOURCES);

            p->switch_role_state = BTM_ACL_SWKEY_STATE_IN_PROGRESS;

#if BTM_DISC_DURING_RS == TRUE
            if (p_dev_rec)
                p_dev_rec->rs_disc_pending = BTM_SEC_RS_PENDING;
#endif
        }
    }

    /* Initialize return structure in case request fails */
    if (p_cb)
    {
        memcpy (btm_cb.devcb.switch_role_ref_data.remote_bd_addr, remote_bd_addr,
                BD_ADDR_LEN);
        btm_cb.devcb.switch_role_ref_data.role = new_role;
        /* initialized to an error code */
        btm_cb.devcb.switch_role_ref_data.hci_status = HCI_ERR_UNSUPPORTED_VALUE;
        btm_cb.devcb.p_switch_role_cb = p_cb;
    }
    return(BTM_CMD_STARTED);
}

/*******************************************************************************
**
** Function         BTM_ChangeLinkKey
**
** Description      This function is called to change the link key of the
**                  connection.
**
** Returns          BTM_CMD_STARTED if command issued to controller.
**                  BTM_NO_RESOURCES if couldn't allocate memory to issue command
**                  BTM_UNKNOWN_ADDR if no active link with bd addr specified
**                  BTM_BUSY if the previous command is not completed
**
*******************************************************************************/
tBTM_STATUS BTM_ChangeLinkKey (BD_ADDR remote_bd_addr, tBTM_CMPL_CB *p_cb)
{
    tACL_CONN   *p;
    tBTM_SEC_DEV_REC  *p_dev_rec = NULL;
#if BTM_PWR_MGR_INCLUDED == TRUE
    tBTM_STATUS  status;
    tBTM_PM_MODE pwr_mode;
    tBTM_PM_PWR_MD settings;
#endif
    BTM_TRACE_DEBUG0 ("BTM_ChangeLinkKey");
    if ((p = btm_bda_to_acl(remote_bd_addr)) == NULL)
        return(BTM_UNKNOWN_ADDR);

    /* Ignore change link key request if the previsous request has not completed */
    if (p->change_key_state != BTM_ACL_SWKEY_STATE_IDLE)
    {
        BTM_TRACE_DEBUG0 ("Link key change request declined since the previous request for this device has not completed ");
        return(BTM_BUSY);
    }

    memset (&btm_cb.devcb.chg_link_key_ref_data, 0, sizeof(tBTM_CHANGE_KEY_CMPL));

    /* Cannot change key while parked */
#if BTM_PWR_MGR_INCLUDED == FALSE
    if (p->mode == HCI_MODE_PARK)
    {
        if (!btsnd_hcic_exit_park_mode (p->hci_handle))
            return(BTM_NO_RESOURCES);

        p->change_key_state = BTM_ACL_SWKEY_STATE_MODE_CHANGE;
    }
#else   /* power manager is in use */


    if ((status = BTM_ReadPowerMode(p->remote_addr, &pwr_mode)) != BTM_SUCCESS)
        return(status);

    /* Wake up the link if in park before attempting to change link keys */
    if (pwr_mode == BTM_PM_MD_PARK)
    {
/* Coverity: FALSE-POSITIVE error from Coverity tool. Please do NOT remove following comment. */
/* coverity[uninit_use_in_call] False-positive: setting the mode to BTM_PM_MD_ACTIVE only uses settings.mode
                                the other data members of tBTM_PM_PWR_MD are ignored
*/
        settings.mode = BTM_PM_MD_ACTIVE;
        status = BTM_SetPowerMode (BTM_PM_SET_ONLY_ID, p->remote_addr, &settings);
        if (status != BTM_CMD_STARTED)
            return(BTM_WRONG_MODE);

        p->change_key_state = BTM_ACL_SWKEY_STATE_MODE_CHANGE;
    }
#endif
    /* some devices do not support change of link key while encryption is on */
    else if (((p_dev_rec = btm_find_dev (remote_bd_addr)) != NULL)
             && ((p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED) != 0) && !BTM_EPR_AVAILABLE(p))
    {
        /* bypass turning off encryption if switch role is already doing it */
        if (p->encrypt_state != BTM_ACL_ENCRYPT_STATE_ENCRYPT_OFF)
        {
            if (!btsnd_hcic_set_conn_encrypt (p->hci_handle, FALSE))
                return(BTM_NO_RESOURCES);
            else
                p->encrypt_state = BTM_ACL_ENCRYPT_STATE_ENCRYPT_OFF;
        }

        p->change_key_state = BTM_ACL_SWKEY_STATE_ENCRYPTION_OFF;
    }
    else    /* Ok to initiate change of link key */
    {
        if (!btsnd_hcic_change_link_key (p->hci_handle))
            return(BTM_NO_RESOURCES);

        p->change_key_state = BTM_ACL_SWKEY_STATE_IN_PROGRESS;
    }

    /* Initialize return structure in case request fails */
    memcpy (btm_cb.devcb.chg_link_key_ref_data.remote_bd_addr, remote_bd_addr,
            BD_ADDR_LEN);
    btm_cb.devcb.p_chg_link_key_cb = p_cb;
    return(BTM_CMD_STARTED);
}

/*******************************************************************************
**
** Function         btm_acl_link_key_change
**
** Description      This function is called to when a change link key event
**                  is received.
**
*******************************************************************************/
void btm_acl_link_key_change (UINT16 handle, UINT8 status)
{
    tBTM_CHANGE_KEY_CMPL *p_data;
    tACL_CONN            *p;
    UINT8                xx;
    BTM_TRACE_DEBUG0 ("btm_acl_link_key_change");
    /* Look up the connection by handle and set the current mode */
    xx = btm_handle_to_acl_index(handle);

    /* don't assume that we can never get a bad hci_handle */
    if (xx >= MAX_L2CAP_LINKS)
        return;

    p_data = &btm_cb.devcb.chg_link_key_ref_data;
    p = &btm_cb.acl_db[xx];
    p_data->hci_status = status;

    /* if switching state is switching we need to turn encryption on */
    /* if idle, we did not change encryption */
    if (p->change_key_state == BTM_ACL_SWKEY_STATE_SWITCHING)
    {
        /* Make sure there's not also a role switch going on before re-enabling */
        if (p->switch_role_state != BTM_ACL_SWKEY_STATE_SWITCHING)
        {
            if (btsnd_hcic_set_conn_encrypt (p->hci_handle, TRUE))
            {
                p->encrypt_state = BTM_ACL_ENCRYPT_STATE_ENCRYPT_ON;
                p->change_key_state = BTM_ACL_SWKEY_STATE_ENCRYPTION_ON;
                return;
            }
        }
        else    /* Set the state and wait for change link key */
        {
            p->change_key_state = BTM_ACL_SWKEY_STATE_ENCRYPTION_ON;
            return;
        }
    }

    /* Set the switch_role_state to IDLE since the reply received from HCI */
    /* regardless of its result either success or failed. */
    if (p->change_key_state == BTM_ACL_SWKEY_STATE_IN_PROGRESS)
    {
        p->change_key_state = BTM_ACL_SWKEY_STATE_IDLE;
        p->encrypt_state = BTM_ACL_ENCRYPT_STATE_IDLE;
    }

    if (btm_cb.devcb.p_chg_link_key_cb)
    {
        (*btm_cb.devcb.p_chg_link_key_cb)((void *)p_data);
        btm_cb.devcb.p_chg_link_key_cb = NULL;
    }

    BTM_TRACE_ERROR2("Change Link Key Complete Event: Handle 0x%02x, HCI Status 0x%02x",
                     handle, p_data->hci_status);
}

/*******************************************************************************
**
** Function         btm_acl_encrypt_change
**
** Description      This function is when encryption of the connection is
**                  completed by the LM.  Checks to see if a role switch or
**                  change of link key was active and initiates or continues
**                  process if needed.
**
** Returns          void
**
*******************************************************************************/
void btm_acl_encrypt_change (UINT16 handle, UINT8 status, UINT8 encr_enable)
{
    tACL_CONN *p;
    UINT8     xx;
#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
    tBTM_BL_ROLE_CHG_DATA   evt;
#endif
#if BTM_DISC_DURING_RS == TRUE
    tBTM_SEC_DEV_REC  *p_dev_rec;
#endif
    BTM_TRACE_DEBUG3 ("btm_acl_encrypt_change handle=%d status=%d encr_enabl=%d", handle, status, encr_enable);
    xx = btm_handle_to_acl_index(handle);
    /* don't assume that we can never get a bad hci_handle */
    if (xx < MAX_L2CAP_LINKS)
        p = &btm_cb.acl_db[xx];
    else
        return;

    /* Process Role Switch if active */
    if (p->switch_role_state == BTM_ACL_SWKEY_STATE_ENCRYPTION_OFF)
    {
        /* if encryption turn off failed we still will try to switch role */
        if (encr_enable)
        {
            p->switch_role_state = BTM_ACL_SWKEY_STATE_IDLE;
            p->encrypt_state = BTM_ACL_ENCRYPT_STATE_IDLE;
        }
        else
        {
            p->switch_role_state = BTM_ACL_SWKEY_STATE_SWITCHING;
            p->encrypt_state = BTM_ACL_ENCRYPT_STATE_TEMP_FUNC;
        }

        if (!btsnd_hcic_switch_role (p->remote_addr, (UINT8)!p->link_role))
        {
            p->switch_role_state = BTM_ACL_SWKEY_STATE_IDLE;
            p->encrypt_state = BTM_ACL_ENCRYPT_STATE_IDLE;
            btm_acl_report_role_change(btm_cb.devcb.switch_role_ref_data.hci_status, p->remote_addr);
        }
#if BTM_DISC_DURING_RS == TRUE
        else
        {
            if ((p_dev_rec = btm_find_dev (p->remote_addr)) != NULL)
                p_dev_rec->rs_disc_pending = BTM_SEC_RS_PENDING;
        }
#endif

    }
    /* Finished enabling Encryption after role switch */
    else if (p->switch_role_state == BTM_ACL_SWKEY_STATE_ENCRYPTION_ON)
    {
        p->switch_role_state = BTM_ACL_SWKEY_STATE_IDLE;
        p->encrypt_state = BTM_ACL_ENCRYPT_STATE_IDLE;
        btm_acl_report_role_change(btm_cb.devcb.switch_role_ref_data.hci_status, p->remote_addr);

#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
        /* if role change event is registered, report it now */
        if (btm_cb.p_bl_changed_cb && (btm_cb.bl_evt_mask & BTM_BL_ROLE_CHG_MASK))
        {
            evt.event       = BTM_BL_ROLE_CHG_EVT;
            evt.new_role    = btm_cb.devcb.switch_role_ref_data.role;
            evt.p_bda       = btm_cb.devcb.switch_role_ref_data.remote_bd_addr;
            evt.hci_status  = btm_cb.devcb.switch_role_ref_data.hci_status;
            (*btm_cb.p_bl_changed_cb)((tBTM_BL_EVENT_DATA *)&evt);

            BTM_TRACE_DEBUG3("Role Switch Event: new_role 0x%02x, HCI Status 0x%02x, rs_st:%d",
                             evt.new_role, evt.hci_status, p->switch_role_state);
        }
#endif

#if BTM_DISC_DURING_RS == TRUE
        /* If a disconnect is pending, issue it now that role switch has completed */
        if ((p_dev_rec = btm_find_dev (p->remote_addr)) != NULL)
        {
            if (p_dev_rec->rs_disc_pending == BTM_SEC_DISC_PENDING)
            {
                BTM_TRACE_WARNING0("btm_acl_encrypt_change -> Issuing delayed HCI_Disconnect!!!");
                btsnd_hcic_disconnect(p_dev_rec->hci_handle, HCI_ERR_PEER_USER);
            }
            BTM_TRACE_ERROR2("btm_acl_encrypt_change: tBTM_SEC_DEV:0x%x rs_disc_pending=%d",
                (UINT32)p_dev_rec, p_dev_rec->rs_disc_pending);
            p_dev_rec->rs_disc_pending = BTM_SEC_RS_NOT_PENDING;     /* reset flag */
        }
#endif
    }


    /* Process Change Link Key if active */
    if (p->change_key_state == BTM_ACL_SWKEY_STATE_ENCRYPTION_OFF)
    {
        /* if encryption turn off failed we still will try to change link key */
        if (encr_enable)
        {
            p->change_key_state = BTM_ACL_SWKEY_STATE_IDLE;
            p->encrypt_state = BTM_ACL_ENCRYPT_STATE_IDLE;
        }
        else
        {
            p->encrypt_state = BTM_ACL_ENCRYPT_STATE_TEMP_FUNC;
            p->change_key_state = BTM_ACL_SWKEY_STATE_SWITCHING;
        }

        if (!btsnd_hcic_change_link_key (p->hci_handle))
        {
            p->encrypt_state = BTM_ACL_ENCRYPT_STATE_IDLE;
            p->change_key_state = BTM_ACL_SWKEY_STATE_IDLE;
            if (btm_cb.devcb.p_chg_link_key_cb)
            {
                (*btm_cb.devcb.p_chg_link_key_cb)(&btm_cb.devcb.chg_link_key_ref_data);
                btm_cb.devcb.p_chg_link_key_cb = NULL;
            }
        }
    }
    /* Finished enabling Encryption after changing link key */
    else if (p->change_key_state == BTM_ACL_SWKEY_STATE_ENCRYPTION_ON)
    {
        p->encrypt_state = BTM_ACL_ENCRYPT_STATE_IDLE;
        p->change_key_state = BTM_ACL_SWKEY_STATE_IDLE;
        if (btm_cb.devcb.p_chg_link_key_cb)
        {
            (*btm_cb.devcb.p_chg_link_key_cb)(&btm_cb.devcb.chg_link_key_ref_data);
            btm_cb.devcb.p_chg_link_key_cb = NULL;
        }
    }
}
/*******************************************************************************
**
** Function         BTM_SetLinkPolicy
**
** Description      Create and send HCI "Write Policy Set" command
**
** Returns          status of the operation
**
*******************************************************************************/
tBTM_STATUS BTM_SetLinkPolicy (BD_ADDR remote_bda, UINT16 *settings)
{
    tACL_CONN   *p;
    UINT8       *localFeatures = BTM_ReadLocalFeatures();
    BTM_TRACE_DEBUG0 ("BTM_SetLinkPolicy");
/*    BTM_TRACE_API1 ("BTM_SetLinkPolicy: requested settings: 0x%04x", *settings ); */

    /* First, check if hold mode is supported */
    if (*settings != HCI_DISABLE_ALL_LM_MODES)
    {
        if ( (*settings & HCI_ENABLE_MASTER_SLAVE_SWITCH) && (!HCI_SWITCH_SUPPORTED(localFeatures)) )
        {
            *settings &= (~HCI_ENABLE_MASTER_SLAVE_SWITCH);
            BTM_TRACE_API1 ("BTM_SetLinkPolicy switch not supported (settings: 0x%04x)", *settings );
        }
        if ( (*settings & HCI_ENABLE_HOLD_MODE) && (!HCI_HOLD_MODE_SUPPORTED(localFeatures)) )
        {
            *settings &= (~HCI_ENABLE_HOLD_MODE);
            BTM_TRACE_API1 ("BTM_SetLinkPolicy hold not supported (settings: 0x%04x)", *settings );
        }
        if ( (*settings & HCI_ENABLE_SNIFF_MODE) && (!HCI_SNIFF_MODE_SUPPORTED(localFeatures)) )
        {
            *settings &= (~HCI_ENABLE_SNIFF_MODE);
            BTM_TRACE_API1 ("BTM_SetLinkPolicy sniff not supported (settings: 0x%04x)", *settings );
        }
        if ( (*settings & HCI_ENABLE_PARK_MODE) && (!HCI_PARK_MODE_SUPPORTED(localFeatures)) )
        {
            *settings &= (~HCI_ENABLE_PARK_MODE);
            BTM_TRACE_API1 ("BTM_SetLinkPolicy park not supported (settings: 0x%04x)", *settings );
        }
    }

    if ((p = btm_bda_to_acl(remote_bda)) != NULL)
        return(btsnd_hcic_write_policy_set (p->hci_handle, *settings) ? BTM_CMD_STARTED : BTM_NO_RESOURCES);

    /* If here, no BD Addr found */
    return(BTM_UNKNOWN_ADDR);
}

/*******************************************************************************
**
** Function         BTM_SetDefaultLinkPolicy
**
** Description      Set the default value for HCI "Write Policy Set" command
**                  to use when an ACL link is created.
**
** Returns          void
**
*******************************************************************************/
void BTM_SetDefaultLinkPolicy (UINT16 settings)
{
    BTM_TRACE_DEBUG0 ("BTM_SetDefaultLinkPolicy");
    btm_cb.btm_def_link_policy = settings;
}


/*******************************************************************************
**
** Function         BTM_ReadLinkPolicy
**
** Description      This function is called to read the link policy settings.
**                  The address of link policy results are returned in the callback.
**                  (tBTM_LNK_POLICY_RESULTS)
**
** Returns          status of the operation
**
*******************************************************************************/
tBTM_STATUS BTM_ReadLinkPolicy (BD_ADDR remote_bda, tBTM_CMPL_CB *p_cb)
{
    tACL_CONN   *p;

    BTM_TRACE_API6 ("BTM_ReadLinkPolicy: RemBdAddr: %02x%02x%02x%02x%02x%02x",
                    remote_bda[0], remote_bda[1], remote_bda[2],
                    remote_bda[3], remote_bda[4], remote_bda[5]);

    /* If someone already waiting on the version, do not allow another */
    if (btm_cb.devcb.p_rlinkp_cmpl_cb)
        return(BTM_BUSY);

    p = btm_bda_to_acl(remote_bda);
    if (p != (tACL_CONN *)NULL)
    {
        btu_start_timer (&btm_cb.devcb.rlinkp_timer, BTU_TTYPE_BTM_ACL, BTM_DEV_REPLY_TIMEOUT);
        btm_cb.devcb.p_rlinkp_cmpl_cb = p_cb;

        if (!btsnd_hcic_read_policy_set (p->hci_handle))
        {
            btu_stop_timer (&btm_cb.devcb.rlinkp_timer);
            btm_cb.devcb.p_rlinkp_cmpl_cb = NULL;
            return(BTM_NO_RESOURCES);
        }

        return(BTM_CMD_STARTED);
    }

    /* If here, no BD Addr found */
    return(BTM_UNKNOWN_ADDR);
}


/*******************************************************************************
**
** Function         btm_read_link_policy_complete
**
** Description      This function is called when the command complete message
**                  is received from the HCI for the read local link policy request.
**
** Returns          void
**
*******************************************************************************/
void btm_read_link_policy_complete (UINT8 *p)
{
    tBTM_CMPL_CB            *p_cb = btm_cb.devcb.p_rlinkp_cmpl_cb;
    tBTM_LNK_POLICY_RESULTS  lnkpol;
    UINT16                   handle;
    tACL_CONN               *p_acl_cb = &btm_cb.acl_db[0];
    UINT16                   index;
    BTM_TRACE_DEBUG0 ("btm_read_link_policy_complete");
    btu_stop_timer (&btm_cb.devcb.rlinkp_timer);

    /* If there was a callback address for read local version, call it */
    btm_cb.devcb.p_rlinkp_cmpl_cb = NULL;

    if (p_cb)
    {
        STREAM_TO_UINT8  (lnkpol.hci_status, p);

        if (lnkpol.hci_status == HCI_SUCCESS)
        {
            lnkpol.status = BTM_SUCCESS;

            STREAM_TO_UINT16 (handle, p);

            STREAM_TO_UINT16 (lnkpol.settings, p);

            /* Search through the list of active channels for the correct BD Addr */
            for (index = 0; index < MAX_L2CAP_LINKS; index++, p_acl_cb++)
            {
                if ((p_acl_cb->in_use) && (handle == p_acl_cb->hci_handle))
                {
                    memcpy (lnkpol.rem_bda, p_acl_cb->remote_addr, BD_ADDR_LEN);
                    break;
                }
            }
        }
        else
            lnkpol.status = BTM_ERR_PROCESSING;

        (*p_cb)(&lnkpol);
    }
}


/*******************************************************************************
**
** Function         btm_read_remote_version_complete
**
** Description      This function is called when the command complete message
**                  is received from the HCI for the remote version info.
**
** Returns          void
**
*******************************************************************************/
void btm_read_remote_version_complete (UINT8 *p)
{
    tACL_CONN        *p_acl_cb = &btm_cb.acl_db[0];
    UINT8             status;
    UINT16            handle;
    int               xx;
    BTM_TRACE_DEBUG0 ("btm_read_remote_version_complete");
    STREAM_TO_UINT8  (status, p);
    if (status == HCI_SUCCESS)
    {
        STREAM_TO_UINT16 (handle, p);

        /* Look up the connection by handle and copy features */
        for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_acl_cb++)
        {
            if ((p_acl_cb->in_use) && (p_acl_cb->hci_handle == handle))
            {
                STREAM_TO_UINT8  (p_acl_cb->lmp_version, p);
                STREAM_TO_UINT16 (p_acl_cb->manufacturer, p);
                STREAM_TO_UINT16 (p_acl_cb->lmp_subversion, p);
                break;
            }
        }
    }
}


/*******************************************************************************
**
** Function         btm_read_remote_features_complete
**
** Description      This function is called when the remote extended features
**                  complete event is received from the HCI.
**
** Returns          void
**
*******************************************************************************/
void btm_read_remote_features_complete (UINT8 *p)
{
    tACL_CONN        *p_acl_cb = &btm_cb.acl_db[0];
    UINT8             status;
    UINT16            handle;
    int               xx, yy;
    UINT8             req_pend;
    tBTM_SEC_DEV_REC *p_dev_rec;
    BTM_TRACE_DEBUG0 ("btm_read_remote_features_complete");
    STREAM_TO_UINT8  (status, p);
    if (status == HCI_SUCCESS)
    {
        STREAM_TO_UINT16 (handle, p);

        /* Look up the connection by handle and copy features */
        for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_acl_cb++)
        {
            if ((p_acl_cb->in_use) && (p_acl_cb->hci_handle == handle))
            {
                for (yy = 0; yy < BD_FEATURES_LEN; yy++)
                    STREAM_TO_UINT8 (p_acl_cb->features[yy], p);

                p_dev_rec = btm_find_dev_by_handle (handle);
                if (!p_dev_rec)
                {
                    /* Get a new device; might be doing dedicated bonding */
                    p_dev_rec = btm_find_or_alloc_dev (p_acl_cb->remote_addr);
                }

                memcpy (p_dev_rec->features, p_acl_cb->features, BD_FEATURES_LEN);

                if (BTM_SEC_MODE_SP == btm_cb.security_mode &&
                    HCI_SIMPLE_PAIRING_SUPPORTED(p_acl_cb->features))
                {
                    /* if SM4 supported, check peer support for SM4
                     * The remote controller supports SSP
                     * read the extended feature page 1 for the host support for SSP */
                    if (btsnd_hcic_rmt_ext_features (handle, 1))
                        break;
                }
                else
                {
                    req_pend = (p_dev_rec->sm4 & BTM_SM4_REQ_PEND);
                    p_dev_rec->sm4 = BTM_SM4_KNOWN;
                    if (req_pend)
                    {
                        l2cu_resubmit_pending_sec_req (p_dev_rec->bd_addr);
                    }
                }

                btm_establish_continue (p_acl_cb);
                break;
            }
        }
    }
}

/*******************************************************************************
**
** Function         btm_read_remote_ext_features_complete
**
** Description      This function is called when the remote extended features
**                  complete event is received from the HCI.
**
** Returns          void
**
*******************************************************************************/
void btm_read_remote_ext_features_complete (UINT8 *p)
{
    tACL_CONN        *p_acl_cb = &btm_cb.acl_db[0];
    tBTM_SEC_DEV_REC *p_dev_rec;
    UINT8             status, page_num, max_page;
    UINT16            handle;
    int               xx;
    BD_FEATURES       ext_features;       /* extended Features suported by the device    */
    UINT8             req_pend;
    BTM_TRACE_DEBUG0 ("btm_read_remote_ext_features_complete");
    STREAM_TO_UINT8  (status, p);
    if (status == HCI_SUCCESS)
    {
        STREAM_TO_UINT16 (handle, p);

        /* Look up the connection by handle and copy features */
        for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_acl_cb++)
        {
            if ((p_acl_cb->in_use) && (p_acl_cb->hci_handle == handle))
            {
                STREAM_TO_UINT8  (page_num, p);
                STREAM_TO_UINT8  (max_page, p);
                p_dev_rec = btm_find_dev_by_handle (handle);
                if (!p_dev_rec)
                    p_dev_rec = btm_find_or_alloc_dev (p_acl_cb->remote_addr);

                req_pend = (p_dev_rec->sm4 & BTM_SM4_REQ_PEND);

                if (page_num == 1 && max_page >= 1)
                {
                    /* only the byte 0 of page 1 is used right now */
                    STREAM_TO_UINT8 (ext_features[0], p);

                    if (HCI_SSP_HOST_SUPPORTED(ext_features))
                    {
                        p_dev_rec->sm4 = BTM_SM4_TRUE;
                    }
                }

                BTM_TRACE_API5 ("ext_features_complt page_num:%d max_page:%d f[0]:x%02x, sm4:%x, pend:%d",
                                page_num, max_page, *p, p_dev_rec->sm4, req_pend);

                if (!BTM_SEC_IS_SM4(p_dev_rec->sm4))
                {
                    p_dev_rec->sm4 = BTM_SM4_KNOWN;
                }

                if (req_pend)
                    l2cu_resubmit_pending_sec_req (p_dev_rec->bd_addr);

                btm_establish_continue (p_acl_cb);

                break;
            }
        }
    }
}

/*******************************************************************************
**
** Function         btm_read_remote_ext_features_failed
**
** Description      This function is called when the remote extended features
**                  complete event returns a failed status.
**
** Returns          void
**
*******************************************************************************/
void btm_read_remote_ext_features_failed (UINT8 status)
{
    BTM_TRACE_ERROR1 ("btm_read_remote_ext_features_failed (status 0x%02x)", status);
}

/*******************************************************************************
**
** Function         btm_establish_continue
**
** Description      This function is called when the command complete message
**                  is received from the HCI for the read local link policy request.
**
** Returns          void
**
*******************************************************************************/
static void btm_establish_continue (tACL_CONN *p_acl_cb)
{
#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
    tBTM_BL_EVENT_DATA  evt_data;
#endif
    BTM_TRACE_DEBUG0 ("btm_establish_continue");
#if (!defined(BTM_BYPASS_EXTRA_ACL_SETUP) || BTM_BYPASS_EXTRA_ACL_SETUP == FALSE)
#if (defined BLE_INCLUDED && BLE_INCLUDED == TRUE)
    if (!p_acl_cb->is_le_link)
#endif
    {
        /* For now there are a some devices that do not like sending */
        /* commands events and data at the same time. */
        /* Set the packet types to the default allowed by the device */
        btm_set_packet_types (p_acl_cb, btm_cb.btm_acl_pkt_types_supported);

        if (btm_cb.btm_def_link_policy)
            BTM_SetLinkPolicy (p_acl_cb->remote_addr, &btm_cb.btm_def_link_policy);

        BTM_SetLinkSuperTout (p_acl_cb->remote_addr, btm_cb.btm_def_link_super_tout);
    }
#endif
    p_acl_cb->link_up_issued = TRUE;

    /* If anyone cares, tell him database changed */
#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
    if (btm_cb.p_bl_changed_cb)
    {
        evt_data.event = BTM_BL_CONN_EVT;
        evt_data.conn.p_bda = p_acl_cb->remote_addr;
        evt_data.conn.p_bdn = p_acl_cb->remote_name;
        evt_data.conn.p_dc  = p_acl_cb->remote_dc;
        evt_data.conn.p_features = p_acl_cb->features;


        (*btm_cb.p_bl_changed_cb)(&evt_data);
    }
    btm_acl_update_busy_level (BTM_BLI_ACL_UP_EVT);
#else
    if (btm_cb.p_acl_changed_cb)
        (*btm_cb.p_acl_changed_cb) (p_acl_cb->remote_addr,
                                    p_acl_cb->remote_dc,
                                    p_acl_cb->remote_name,
                                    p_acl_cb->features,
                                    TRUE);
#endif
}


/*******************************************************************************
**
** Function         BTM_SetDefaultLinkSuperTout
**
** Description      Set the default value for HCI "Write Link Supervision Timeout"
**                  command to use when an ACL link is created.
**
** Returns          void
**
*******************************************************************************/
void BTM_SetDefaultLinkSuperTout (UINT16 timeout)
{
    BTM_TRACE_DEBUG0 ("BTM_SetDefaultLinkSuperTout");
    btm_cb.btm_def_link_super_tout = timeout;
}

/*******************************************************************************
**
** Function         BTM_SetLinkSuperTout
**
** Description      Create and send HCI "Write Link Supervision Timeout" command
**
** Returns          status of the operation
**
*******************************************************************************/
tBTM_STATUS BTM_SetLinkSuperTout (BD_ADDR remote_bda, UINT16 timeout)
{
    tACL_CONN   *p = btm_bda_to_acl(remote_bda);

    BTM_TRACE_DEBUG0 ("BTM_SetLinkSuperTout");
    if (p != (tACL_CONN *)NULL)
    {
        p->link_super_tout = timeout;

        /* Only send if current role is Master; 2.0 spec requires this */
        if (p->link_role == BTM_ROLE_MASTER)
        {
            if (!btsnd_hcic_write_link_super_tout (LOCAL_BR_EDR_CONTROLLER_ID,
                                                   p->hci_handle, timeout))
                return(BTM_NO_RESOURCES);

            return(BTM_CMD_STARTED);
        }
        else
            return(BTM_SUCCESS);
    }

    /* If here, no BD Addr found */
    return(BTM_UNKNOWN_ADDR);
}

/*******************************************************************************
**
** Function         BTM_RegForLstoEvt
**
** Description      register for the HCI "Link Supervision Timeout Change" event
**
** Returns          void
**
*******************************************************************************/
void BTM_RegForLstoEvt (tBTM_LSTO_CBACK *p_cback)
{
    BTM_TRACE_DEBUG0 ("BTM_RegForLstoEvt");
    btm_cb.p_lsto_cback = p_cback;
}

/*******************************************************************************
**
** Function         btm_proc_lsto_evt
**
** Description      process the HCI "Link Supervision Timeout Change" event
**
** Returns          void
**
*******************************************************************************/
void btm_proc_lsto_evt(UINT16 handle, UINT16 timeout)
{
    UINT8 xx;

    BTM_TRACE_DEBUG0 ("btm_proc_lsto_evt");
    if (btm_cb.p_lsto_cback)
    {
        /* Look up the connection by handle and set the current mode */
        xx = btm_handle_to_acl_index(handle);

        /* don't assume that we can never get a bad hci_handle */
        if (xx < MAX_L2CAP_LINKS)
        {
            (*btm_cb.p_lsto_cback)(btm_cb.acl_db[xx].remote_addr, timeout);
        }
    }
}

#if BTM_PWR_MGR_INCLUDED == FALSE
/*******************************************************************************
**
** Function         BTM_SetHoldMode
**
** Description      This function is called to set a connection into hold mode.
**                  A check is made if the connection is in sniff or park mode,
**                  and if yes, the hold mode is ignored.
**
** Returns          status of the operation
**
*******************************************************************************/
tBTM_STATUS BTM_SetHoldMode (BD_ADDR remote_bda, UINT16 min_interval, UINT16 max_interval)
{
    tACL_CONN   *p;

    BTM_TRACE_DEBUG0 ("BTM_SetHoldMode");
    /* First, check if hold mode is supported */
    if (!HCI_HOLD_MODE_SUPPORTED(BTM_ReadLocalFeatures()))
        return(BTM_MODE_UNSUPPORTED);

    p = btm_bda_to_acl(remote_bda);
    if (p != (tACL_CONN *)NULL)
    {
        /* If the connection is in park or sniff mode, forget about holding it */
        if (p->mode != BTM_ACL_MODE_NORMAL)
            return(BTM_SUCCESS);

        if (!btsnd_hcic_hold_mode (p->hci_handle, max_interval, min_interval))
            return(BTM_NO_RESOURCES);

        return(BTM_CMD_STARTED);
    }

    /* If here, no BD Addr found */
    return(BTM_UNKNOWN_ADDR);
}


/*******************************************************************************
**
** Function         BTM_SetSniffMode
**
** Description      This function is called to set a connection into sniff mode.
**                  A check is made if the connection is already in sniff or park
**                  mode, and if yes, the sniff mode is ignored.
**
** Returns          status of the operation
**
*******************************************************************************/
tBTM_STATUS BTM_SetSniffMode (BD_ADDR remote_bda, UINT16 min_period, UINT16 max_period,
                              UINT16 attempt, UINT16 timeout)
{
    tACL_CONN   *p;
    BTM_TRACE_DEBUG0 ("BTM_SetSniffMode");
    /* First, check if sniff mode is supported */
    if (!HCI_SNIFF_MODE_SUPPORTED(BTM_ReadLocalFeatures()))
        return(BTM_MODE_UNSUPPORTED);

    p = btm_bda_to_acl(remote_bda);
    if (p != (tACL_CONN *)NULL)
    {
        /* If the connection is in park mode, forget about sniffing it */
        if (p->mode != BTM_ACL_MODE_NORMAL)
            return(BTM_WRONG_MODE);

        if (!btsnd_hcic_sniff_mode (p->hci_handle, max_period,
                                    min_period, attempt, timeout))
            return(BTM_NO_RESOURCES);

        return(BTM_CMD_STARTED);
    }

    /* If here, no BD Addr found */
    return(BTM_UNKNOWN_ADDR);
}




/*******************************************************************************
**
** Function         BTM_CancelSniffMode
**
** Description      This function is called to put a connection out of sniff mode.
**                  A check is made if the connection is already in sniff mode,
**                  and if not, the cancel sniff mode is ignored.
**
** Returns          status of the operation
**
*******************************************************************************/
tBTM_STATUS BTM_CancelSniffMode (BD_ADDR remote_bda)
{
    tACL_CONN   *p = btm_bda_to_acl(remote_bda);
    BTM_TRACE_DEBUG0 ("BTM_CancelSniffMode ");
    if (p == (tACL_CONN *)NULL)
        return(BTM_UNKNOWN_ADDR);

    /* If the connection is not in sniff mode, cannot cancel */
    if (p->mode != BTM_ACL_MODE_SNIFF)
        return(BTM_WRONG_MODE);

    if (!btsnd_hcic_exit_sniff_mode (p->hci_handle))
        return(BTM_NO_RESOURCES);

    return(BTM_CMD_STARTED);
}


/*******************************************************************************
**
** Function         BTM_SetParkMode
**
** Description      This function is called to set a connection into park mode.
**                  A check is made if the connection is already in sniff or park
**                  mode, and if yes, the park mode is ignored.
**
** Returns          status of the operation
**
*******************************************************************************/
tBTM_STATUS BTM_SetParkMode (BD_ADDR remote_bda, UINT16 beacon_min_period, UINT16 beacon_max_period)
{
    tACL_CONN   *p;

    BTM_TRACE_DEBUG0 ("BTM_SetParkMode");
    /* First, check if park mode is supported */
    if (!HCI_PARK_MODE_SUPPORTED(BTM_ReadLocalFeatures()))
        return(BTM_MODE_UNSUPPORTED);

    p = btm_bda_to_acl(remote_bda);
    if (p != (tACL_CONN *)NULL)
    {
        /* If the connection is in sniff mode, forget about parking it */
        if (p->mode != BTM_ACL_MODE_NORMAL)
            return(BTM_WRONG_MODE);

        /* no park mode if SCO exists -- CR#1982, 1.1 errata 1124
           command status event should be returned /w error code 0x0C "Command Disallowed"
           Let LM do this.
        */
        if (!btsnd_hcic_park_mode (p->hci_handle,
                                   beacon_max_period, beacon_min_period))
            return(BTM_NO_RESOURCES);

        return(BTM_CMD_STARTED);
    }

    /* If here, no BD Addr found */
    return(BTM_UNKNOWN_ADDR);
}

/*******************************************************************************
**
** Function         BTM_CancelParkMode
**
** Description      This function is called to put a connection out of park mode.
**                  A check is made if the connection is already in park mode,
**                  and if not, the cancel sniff mode is ignored.
**
** Returns          status of the operation
**
*******************************************************************************/
tBTM_STATUS BTM_CancelParkMode (BD_ADDR remote_bda)
{
    tACL_CONN   *p;

    BTM_TRACE_DEBUG0 ("BTM_CancelParkMode");
    p = btm_bda_to_acl(remote_bda);
    if (p != (tACL_CONN *)NULL)
    {
        /* If the connection is not in park mode, cannot cancel */
        if (p->mode != BTM_ACL_MODE_PARK)
            return(BTM_WRONG_MODE);

        if (!btsnd_hcic_exit_park_mode (p->hci_handle))
            return(BTM_NO_RESOURCES);

        return(BTM_CMD_STARTED);
    }

    /* If here, no BD Addr found */
    return(BTM_UNKNOWN_ADDR);
}
#endif /* BTM_PWR_MGR_INCLUDED == FALSE */


/*******************************************************************************
**
** Function         BTM_SetPacketTypes
**
** Description      This function is set the packet types used for a specific
**                  ACL connection,
**
** Returns          status of the operation
**
*******************************************************************************/
tBTM_STATUS BTM_SetPacketTypes (BD_ADDR remote_bda, UINT16 pkt_types)
{
    tACL_CONN   *p;
    BTM_TRACE_DEBUG0 ("BTM_SetPacketTypes");

    if ((p = btm_bda_to_acl(remote_bda)) != NULL)
        return(btm_set_packet_types (p, pkt_types));

    /* If here, no BD Addr found */
    return(BTM_UNKNOWN_ADDR);
}


/*******************************************************************************
**
** Function         BTM_ReadPacketTypes
**
** Description      This function is set the packet types used for a specific
**                  ACL connection,
**
** Returns          packet types supported for the connection, or 0 if no BD address
**
*******************************************************************************/
UINT16 BTM_ReadPacketTypes (BD_ADDR remote_bda)
{
    tACL_CONN   *p;

    BTM_TRACE_DEBUG0 ("BTM_ReadPacketTypes");
    p = btm_bda_to_acl(remote_bda);
    if (p != (tACL_CONN *)NULL)
    {
        return(p->pkt_types_mask);
    }

    /* If here, no BD Addr found */
    return(0);
}


/*******************************************************************************
**
** Function         BTM_ReadAclMode
**
** Description      This returns the current mode for a specific
**                  ACL connection.
**
** Input Param      remote_bda - device address of desired ACL connection
**
** Output Param     p_mode - address where the current mode is copied into.
**                          BTM_ACL_MODE_NORMAL
**                          BTM_ACL_MODE_HOLD
**                          BTM_ACL_MODE_SNIFF
**                          BTM_ACL_MODE_PARK
**                          (valid only if return code is BTM_SUCCESS)
**
** Returns          BTM_SUCCESS if successful,
**                  BTM_UNKNOWN_ADDR if bd addr is not active or bad
**
*******************************************************************************/
#if BTM_PWR_MGR_INCLUDED == FALSE
tBTM_STATUS BTM_ReadAclMode (BD_ADDR remote_bda, UINT8 *p_mode)
{
    tACL_CONN   *p;

    BTM_TRACE_API6 ("BTM_ReadAclMode: RemBdAddr: %02x%02x%02x%02x%02x%02x",
                    remote_bda[0], remote_bda[1], remote_bda[2],
                    remote_bda[3], remote_bda[4], remote_bda[5]);

    p = btm_bda_to_acl(remote_bda);
    if (p != (tACL_CONN *)NULL)
    {
        *p_mode = p->mode;
        return(BTM_SUCCESS);
    }

    /* If here, no BD Addr found */
    return(BTM_UNKNOWN_ADDR);
}
#endif /* BTM_PWR_MGR_INCLUDED == FALSE */

/*******************************************************************************
**
** Function         BTM_ReadClockOffset
**
** Description      This returns the clock offset for a specific
**                  ACL connection.
**
** Input Param      remote_bda - device address of desired ACL connection
**
** Returns          clock-offset or 0 if unknown
**
*******************************************************************************/
UINT16 BTM_ReadClockOffset (BD_ADDR remote_bda)
{
    tACL_CONN   *p;

    BTM_TRACE_API6 ("BTM_ReadClockOffset: RemBdAddr: %02x%02x%02x%02x%02x%02x",
                    remote_bda[0], remote_bda[1], remote_bda[2],
                    remote_bda[3], remote_bda[4], remote_bda[5]);

    if ( (p = btm_bda_to_acl(remote_bda)) != NULL)
        return(p->clock_offset);

    /* If here, no BD Addr found */
    return(0);
}

/*******************************************************************************
**
** Function         BTM_IsAclConnectionUp
**
** Description      This function is called to check if an ACL connection exists
**                  to a specific remote BD Address.
**
** Returns          TRUE if connection is up, else FALSE.
**
*******************************************************************************/
BOOLEAN BTM_IsAclConnectionUp (BD_ADDR remote_bda)
{
    tACL_CONN   *p;

    BTM_TRACE_API6 ("BTM_ReadClockOffset: RemBdAddr: %02x%02x%02x%02x%02x%02x",
                    remote_bda[0], remote_bda[1], remote_bda[2],
                    remote_bda[3], remote_bda[4], remote_bda[5]);

    p = btm_bda_to_acl(remote_bda);
    if (p != (tACL_CONN *)NULL)
    {
        return(TRUE);
    }

    /* If here, no BD Addr found */
    return(FALSE);
}

/*******************************************************************************
**
** Function         BTM_GetNumAclLinks
**
** Description      This function is called to count the number of
**                  ACL links that are active.
**
** Returns          UINT16  Number of active ACL links
**
*******************************************************************************/
UINT16 BTM_GetNumAclLinks (void)
{
#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
    return(UINT16)btm_cb.num_acl;
#else
    tACL_CONN   *p = &btm_cb.acl_db[0];
    UINT16      xx, yy;
    BTM_TRACE_DEBUG0 ("BTM_GetNumAclLinks");
    for (xx = yy = 0; xx < MAX_L2CAP_LINKS; xx++, p++)
    {
        if (p->in_use)
            yy++;
    }

    return(yy);
#endif
}

/*******************************************************************************
**
** Function         btm_get_acl_disc_reason_code
**
** Description      This function is called to get the disconnection reason code
**                  returned by the HCI at disconnection complete event.
**
** Returns          TRUE if connection is up, else FALSE.
**
*******************************************************************************/
UINT16 btm_get_acl_disc_reason_code (void)
{
    UINT8 res = btm_cb.acl_disc_reason;
    BTM_TRACE_DEBUG0 ("btm_get_acl_disc_reason_code");
    return(res);
}


/*******************************************************************************
**
** Function         BTM_GetHCIConnHandle
**
** Description      This function is called to get the handle for an ACL connection
**                  to a specific remote BD Address.
**
** Returns          the handle of the connection, or 0xFFFF if none.
**
*******************************************************************************/
UINT16 BTM_GetHCIConnHandle (BD_ADDR remote_bda)
{
    tACL_CONN   *p;
    BTM_TRACE_DEBUG0 ("BTM_GetHCIConnHandle");
    p = btm_bda_to_acl(remote_bda);
    if (p != (tACL_CONN *)NULL)
    {
        return(p->hci_handle);
    }

    /* If here, no BD Addr found */
    return(0xFFFF);
}

#if BTM_PWR_MGR_INCLUDED == FALSE
/*******************************************************************************
**
** Function         btm_process_mode_change
**
** Description      This function is called when an HCI mode change event occurs.
**
** Input Parms      hci_status - status of the event (HCI_SUCCESS if no errors)
**                  hci_handle - connection handle associated with the change
**                  mode - HCI_MODE_ACTIVE, HCI_MODE_HOLD, HCI_MODE_SNIFF, or HCI_MODE_PARK
**                  interval - number of baseband slots (meaning depends on mode)
**
** Returns          void
**
*******************************************************************************/
void btm_process_mode_change (UINT8 hci_status, UINT16 hci_handle, UINT8 mode, UINT16 interval)
{
    tACL_CONN        *p;
    UINT8             xx;
    BTM_TRACE_DEBUG0 ("btm_process_mode_change");
    if (hci_status != HCI_SUCCESS)
    {
        BTM_TRACE_WARNING1 ("BTM: HCI Mode Change Error Status: 0x%02x", hci_status);
    }

    /* Look up the connection by handle and set the current mode */
    xx = btm_handle_to_acl_index(hci_handle);

    /* don't assume that we can never get a bad hci_handle */
    if (xx >= MAX_L2CAP_LINKS)
        return;

    p = &btm_cb.acl_db[xx];

    /* If status is not success mode does not mean anything */
    if (hci_status == HCI_SUCCESS)
        p->mode = mode;

    /* If mode change was because of an active role switch or change link key */
    btm_cont_rswitch_or_chglinkkey(p, btm_find_dev(p->remote_addr), hci_status);
}
#endif /* BTM_PWR_MGR_INCLUDED == FALSE */

/*******************************************************************************
**
** Function         btm_process_clk_off_comp_evt
**
** Description      This function is called when clock offset command completes.
**
** Input Parms      hci_handle - connection handle associated with the change
**                  clock offset
**
** Returns          void
**
*******************************************************************************/
void btm_process_clk_off_comp_evt (UINT16 hci_handle, UINT16 clock_offset)
{
    UINT8      xx;
    BTM_TRACE_DEBUG0 ("btm_process_clk_off_comp_evt");
    /* Look up the connection by handle and set the current mode */
    if ((xx = btm_handle_to_acl_index(hci_handle)) < MAX_L2CAP_LINKS)
        btm_cb.acl_db[xx].clock_offset = clock_offset;
}

/*******************************************************************************
**
** Function         btm_acl_role_changed
**
** Description      This function is called whan a link's master/slave role change
**                  event or command status event (with error) is received.
**                  It updates the link control block, and calls
**                  the registered callback with status and role (if registered).
**
** Returns          void
**
*******************************************************************************/
void btm_acl_role_changed (UINT8 hci_status, BD_ADDR bd_addr, UINT8 new_role)
{
    UINT8                   *p_bda = (bd_addr) ? bd_addr : btm_cb.devcb.switch_role_ref_data.remote_bd_addr;
    tACL_CONN               *p = btm_bda_to_acl(p_bda);
    tBTM_ROLE_SWITCH_CMPL   *p_data = &btm_cb.devcb.switch_role_ref_data;
#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
    tBTM_BL_ROLE_CHG_DATA   evt;
#endif
#if BTM_DISC_DURING_RS == TRUE
    tBTM_SEC_DEV_REC  *p_dev_rec;
#endif
    BTM_TRACE_DEBUG0 ("btm_acl_role_changed");
    /* Ignore any stray events */
    if (p == NULL)
    {
        /* it could be a failure */
        if (hci_status != HCI_SUCCESS)
            btm_acl_report_role_change(hci_status, bd_addr);
        return;
    }

    p_data->hci_status = hci_status;

    if (hci_status == HCI_SUCCESS)
    {
        p_data->role = new_role;
        memcpy(p_data->remote_bd_addr, p_bda, BD_ADDR_LEN);

        /* Update cached value */
        p->link_role = new_role;

        /* Reload LSTO: link supervision timeout is reset in the LM after a role switch */
        if (new_role == BTM_ROLE_MASTER)
        {
            BTM_SetLinkSuperTout (p->remote_addr, p->link_super_tout);
        }
    }
    else
    {
        /* so the BTM_BL_ROLE_CHG_EVT uses the old role */
        new_role = p->link_role;
    }

    /* Check if any SCO req is pending for role change */
    btm_sco_chk_pend_rolechange (p->hci_handle);

    /* if switching state is switching we need to turn encryption on */
    /* if idle, we did not change encryption */
    if (p->switch_role_state == BTM_ACL_SWKEY_STATE_SWITCHING)
    {
        /* Make sure there's not also a change link key going on before re-enabling */
        if (p->change_key_state != BTM_ACL_SWKEY_STATE_SWITCHING)
        {
            if (btsnd_hcic_set_conn_encrypt (p->hci_handle, TRUE))
            {
                p->encrypt_state = BTM_ACL_ENCRYPT_STATE_ENCRYPT_ON;
                p->switch_role_state = BTM_ACL_SWKEY_STATE_ENCRYPTION_ON;
                return;
            }
        }
        else    /* Set the state and wait for change link key */
        {
            p->switch_role_state = BTM_ACL_SWKEY_STATE_ENCRYPTION_ON;
            return;
        }
    }

    /* Set the switch_role_state to IDLE since the reply received from HCI */
    /* regardless of its result either success or failed. */
    if (p->switch_role_state == BTM_ACL_SWKEY_STATE_IN_PROGRESS)
    {
        p->switch_role_state = BTM_ACL_SWKEY_STATE_IDLE;
        p->encrypt_state = BTM_ACL_ENCRYPT_STATE_IDLE;
    }

    /* if role switch complete is needed, report it now */
    btm_acl_report_role_change(hci_status, bd_addr);

#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
    /* if role change event is registered, report it now */
    if (btm_cb.p_bl_changed_cb && (btm_cb.bl_evt_mask & BTM_BL_ROLE_CHG_MASK))
    {
        evt.event       = BTM_BL_ROLE_CHG_EVT;
        evt.new_role    = new_role;
        evt.p_bda       = p_bda;
        evt.hci_status  = hci_status;
        (*btm_cb.p_bl_changed_cb)((tBTM_BL_EVENT_DATA *)&evt);
    }

    BTM_TRACE_DEBUG3("Role Switch Event: new_role 0x%02x, HCI Status 0x%02x, rs_st:%d",
                     p_data->role, p_data->hci_status, p->switch_role_state);
#endif

#if BTM_DISC_DURING_RS == TRUE
    /* If a disconnect is pending, issue it now that role switch has completed */
    if ((p_dev_rec = btm_find_dev (p_bda)) != NULL)
    {
        if (p_dev_rec->rs_disc_pending == BTM_SEC_DISC_PENDING)
        {
            BTM_TRACE_WARNING0("btm_acl_role_changed -> Issuing delayed HCI_Disconnect!!!");
            btsnd_hcic_disconnect(p_dev_rec->hci_handle, HCI_ERR_PEER_USER);
        }
        BTM_TRACE_ERROR2("tBTM_SEC_DEV:0x%x rs_disc_pending=%d", (UINT32)p_dev_rec, p_dev_rec->rs_disc_pending);
        p_dev_rec->rs_disc_pending = BTM_SEC_RS_NOT_PENDING;     /* reset flag */
    }

#endif

}

#if (RFCOMM_INCLUDED==TRUE)
/*******************************************************************************
**
** Function         BTM_AllocateSCN
**
** Description      Look through the Server Channel Numbers for a free one.
**
** Returns          Allocated SCN number or 0 if none.
**
*******************************************************************************/

UINT8 BTM_AllocateSCN(void)
{
    UINT8   x;
    BTM_TRACE_DEBUG0 ("BTM_AllocateSCN");

    // stack reserves scn 1 for HFP, HSP we still do the correct way
    for (x = 1; x < BTM_MAX_SCN; x++)
    {
        if (!btm_cb.btm_scn[x])
        {
            btm_cb.btm_scn[x] = TRUE;
            return(x+1);
        }
    }

    return(0);     /* No free ports */
}

/*******************************************************************************
**
** Function         BTM_TryAllocateSCN
**
** Description      Try to allocate a fixed server channel
**
** Returns          Returns TRUE if server channel was available
**
*******************************************************************************/

BOOLEAN BTM_TryAllocateSCN(UINT8 scn)
{
    UINT8   x;

    /* Make sure we don't exceed max port range.
     * Stack reserves scn 1 for HFP, HSP we still do the correct way.
     */
    if ( (scn>=BTM_MAX_SCN) || (scn == 1) )
        return FALSE;

    /* check if this port is available */
    if (!btm_cb.btm_scn[scn-1])
    {
        btm_cb.btm_scn[scn-1] = TRUE;
        return TRUE;
    }

    return (FALSE);     /* Port was busy */
}

/*******************************************************************************
**
** Function         BTM_FreeSCN
**
** Description      Free the specified SCN.
**
** Returns          TRUE or FALSE
**
*******************************************************************************/
BOOLEAN BTM_FreeSCN(UINT8 scn)
{
    BTM_TRACE_DEBUG0 ("BTM_FreeSCN ");
    if (scn <= BTM_MAX_SCN)
    {
        btm_cb.btm_scn[scn-1] = FALSE;
        return(TRUE);
    }
    else
        return(FALSE);      /* Illegal SCN passed in */
}

#else

/* Make dummy functions for the RPC to link against */
UINT8 BTM_AllocateSCN(void)
{
    return(0);
}

BOOLEAN BTM_FreeSCN(UINT8 scn)
{
    return(FALSE);
}

#endif


/*******************************************************************************
**
** Function         btm_acl_timeout
**
** Description      This function is called when a timer list entry expires.
**
** Returns          void
**
*******************************************************************************/
void btm_acl_timeout (TIMER_LIST_ENT  *p_tle)
{
    UINT32 timer_type = p_tle->param;

    BTM_TRACE_DEBUG0 ("btm_acl_timeout");
    if (timer_type == TT_DEV_RLNKP)
    {
        tBTM_CMPL_CB            *p_cb = btm_cb.devcb.p_rlinkp_cmpl_cb;
        tBTM_LNK_POLICY_RESULTS  lnkpol;

        lnkpol.status = BTM_ERR_PROCESSING;
        lnkpol.settings = 0;

        btm_cb.devcb.p_rlinkp_cmpl_cb = NULL;

        if (p_cb)
            (*p_cb)(&lnkpol);
    }
}

/*******************************************************************************
**
** Function         btm_set_packet_types
**
** Description      This function sets the packet types used for a specific
**                  ACL connection. It is called internally by btm_acl_created
**                  or by an application/profile by BTM_SetPacketTypes.
**
** Returns          status of the operation
**
*******************************************************************************/
tBTM_STATUS btm_set_packet_types (tACL_CONN *p, UINT16 pkt_types)
{
    UINT16 temp_pkt_types;
    BTM_TRACE_DEBUG0 ("btm_set_packet_types");
    /* Save in the ACL control blocks, types that we support */
    temp_pkt_types = (pkt_types & BTM_ACL_SUPPORTED_PKTS_MASK &
                      btm_cb.btm_acl_pkt_types_supported);

    /* OR in any exception packet types if at least 2.0 version of spec */
    if (btm_cb.devcb.local_version.hci_version >= HCI_PROTO_VERSION_2_0)
    {
        temp_pkt_types |= ((pkt_types & BTM_ACL_EXCEPTION_PKTS_MASK) |
                           (btm_cb.btm_acl_pkt_types_supported & BTM_ACL_EXCEPTION_PKTS_MASK));
    }
    else
    {
        temp_pkt_types &= (~BTM_ACL_EXCEPTION_PKTS_MASK);
    }

    /* Exclude packet types not supported by the peer */
    btm_acl_chk_peer_pkt_type_support (p, &temp_pkt_types);

    BTM_TRACE_DEBUG1 ("SetPacketType Mask -> 0x%04x", temp_pkt_types);

    if (!btsnd_hcic_change_conn_type (p->hci_handle, temp_pkt_types))
    {
        return(BTM_NO_RESOURCES);
    }

    p->pkt_types_mask = temp_pkt_types;

    return(BTM_CMD_STARTED);
}

/*******************************************************************************
**
** Function         btm_get_max_packet_size
**
** Returns          Returns maximum packet size that can be used for current
**                  connection, 0 if connection is not established
**
*******************************************************************************/
UINT16 btm_get_max_packet_size (BD_ADDR addr)
{
    tACL_CONN   *p = btm_bda_to_acl(addr);
    UINT16      pkt_types = 0;
    UINT16      pkt_size = 0;
    BTM_TRACE_DEBUG0 ("btm_get_max_packet_size");
    if (p != NULL)
    {
        pkt_types = p->pkt_types_mask;
    }
    else
    {
        /* Special case for when info for the local device is requested */
        if (memcmp (btm_cb.devcb.local_addr, addr, BD_ADDR_LEN) == 0)
        {
            pkt_types = btm_cb.btm_acl_pkt_types_supported;
        }
    }

    if (pkt_types)
    {
        if (!(pkt_types & BTM_ACL_PKT_TYPES_MASK_NO_3_DH5))
            pkt_size = HCI_EDR3_DH5_PACKET_SIZE;
        else if (!(pkt_types & BTM_ACL_PKT_TYPES_MASK_NO_2_DH5))
            pkt_size = HCI_EDR2_DH5_PACKET_SIZE;
        else if (!(pkt_types & BTM_ACL_PKT_TYPES_MASK_NO_3_DH3))
            pkt_size = HCI_EDR3_DH3_PACKET_SIZE;
        else if (pkt_types & BTM_ACL_PKT_TYPES_MASK_DH5)
            pkt_size = HCI_DH5_PACKET_SIZE;
        else if (!(pkt_types & BTM_ACL_PKT_TYPES_MASK_NO_2_DH3))
            pkt_size = HCI_EDR2_DH3_PACKET_SIZE;
        else if (pkt_types & BTM_ACL_PKT_TYPES_MASK_DM5)
            pkt_size = HCI_DM5_PACKET_SIZE;
        else if (pkt_types & BTM_ACL_PKT_TYPES_MASK_DH3)
            pkt_size = HCI_DH3_PACKET_SIZE;
        else if (pkt_types & BTM_ACL_PKT_TYPES_MASK_DM3)
            pkt_size = HCI_DM3_PACKET_SIZE;
        else if (!(pkt_types & BTM_ACL_PKT_TYPES_MASK_NO_3_DH1))
            pkt_size = HCI_EDR3_DH1_PACKET_SIZE;
        else if (!(pkt_types & BTM_ACL_PKT_TYPES_MASK_NO_2_DH1))
            pkt_size = HCI_EDR2_DH1_PACKET_SIZE;
        else if (pkt_types & BTM_ACL_PKT_TYPES_MASK_DH1)
            pkt_size = HCI_DH1_PACKET_SIZE;
        else if (pkt_types & BTM_ACL_PKT_TYPES_MASK_DM1)
            pkt_size = HCI_DM1_PACKET_SIZE;
    }

#ifdef BRCM_VS
    /* Using HCI size 1017 instead of 1021 */
    if ((pkt_size == HCI_EDR3_DH5_PACKET_SIZE)
        && (btu_cb.hcit_acl_data_size == 1017))
        pkt_size = 1017;
#endif

    return(pkt_size);
}

/*******************************************************************************
**
** Function         BTM_ReadRemoteVersion
**
** Returns          If connected report peer device info
**
*******************************************************************************/
tBTM_STATUS BTM_ReadRemoteVersion (BD_ADDR addr, UINT8 *lmp_version,
                                   UINT16 *manufacturer, UINT16 *lmp_sub_version)
{
    tACL_CONN        *p = btm_bda_to_acl(addr);
    BTM_TRACE_DEBUG0 ("BTM_ReadRemoteVersion");
    if (p == NULL)
        return(BTM_UNKNOWN_ADDR);

    if (lmp_version)
        *lmp_version = p->lmp_version;

    if (manufacturer)
        *manufacturer = p->manufacturer;

    if (lmp_sub_version)
        *lmp_sub_version = p->lmp_subversion;

    return(BTM_SUCCESS);
}

/*******************************************************************************
**
** Function         BTM_ReadRemoteFeatures
**
** Returns          pointer to the features string
**
*******************************************************************************/
UINT8 *BTM_ReadRemoteFeatures (BD_ADDR addr)
{
    tACL_CONN        *p = btm_bda_to_acl(addr);
    BTM_TRACE_DEBUG0 ("BTM_ReadRemoteFeatures");
    if (p == NULL)
    {
        return(NULL);
    }

    return(p->features);
}

/*******************************************************************************
**
** Function         BTM_RegBusyLevelNotif
**
** Description      This function is called to register a callback to receive
**                  busy level change events.
**
** Returns          BTM_SUCCESS if successfully registered, otherwise error
**
*******************************************************************************/
#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
tBTM_STATUS BTM_RegBusyLevelNotif (tBTM_BL_CHANGE_CB *p_cb, UINT8 *p_level,
                                   tBTM_BL_EVENT_MASK evt_mask)
{
    BTM_TRACE_DEBUG0 ("BTM_RegBusyLevelNotif");
    if (p_level)
        *p_level = btm_cb.busy_level;

    btm_cb.bl_evt_mask = evt_mask;

    if (!p_cb)
        btm_cb.p_bl_changed_cb = NULL;
    else if (btm_cb.p_bl_changed_cb)
        return(BTM_BUSY);
    else
        btm_cb.p_bl_changed_cb = p_cb;

    return(BTM_SUCCESS);
}
#else
/*******************************************************************************
**
** Function         BTM_AclRegisterForChanges
**
** Returns          This function is called to register a callback for when the
**                  ACL database changes, i.e. new entry or entry deleted.
**
*******************************************************************************/
tBTM_STATUS BTM_AclRegisterForChanges (tBTM_ACL_DB_CHANGE_CB *p_cb)
{
    BTM_TRACE_DEBUG0 ("BTM_AclRegisterForChanges");
    if (!p_cb)
        btm_cb.p_acl_changed_cb = NULL;
    else if (btm_cb.p_acl_changed_cb)
        return(BTM_BUSY);
    else
        btm_cb.p_acl_changed_cb = p_cb;

    return(BTM_SUCCESS);
}
#endif

/*******************************************************************************
**
** Function         BTM_SetQoS
**
** Description      This function is called to setup QoS
**
** Returns          status of the operation
**
*******************************************************************************/
tBTM_STATUS BTM_SetQoS (BD_ADDR bd, FLOW_SPEC *p_flow, tBTM_CMPL_CB *p_cb)
{
    tACL_CONN   *p = &btm_cb.acl_db[0];

    BTM_TRACE_API6 ("BTM_SetQoS: BdAddr: %02x%02x%02x%02x%02x%02x",
                    bd[0], bd[1], bd[2],
                    bd[3], bd[4], bd[5]);

    /* If someone already waiting on the version, do not allow another */
    if (btm_cb.devcb.p_qossu_cmpl_cb)
        return(BTM_BUSY);

    if ( (p = btm_bda_to_acl(bd)) != NULL)
    {
        btu_start_timer (&btm_cb.devcb.qossu_timer, BTU_TTYPE_BTM_ACL, BTM_DEV_REPLY_TIMEOUT);
        btm_cb.devcb.p_qossu_cmpl_cb = p_cb;

        if (!btsnd_hcic_qos_setup (p->hci_handle, p_flow->qos_flags, p_flow->service_type,
                                   p_flow->token_rate, p_flow->peak_bandwidth, p_flow->latency,p_flow->delay_variation))
        {
            btm_cb.devcb.p_qossu_cmpl_cb = NULL;
            btu_stop_timer(&btm_cb.devcb.qossu_timer);
            return(BTM_NO_RESOURCES);
        }
        else
            return(BTM_CMD_STARTED);
    }

    /* If here, no BD Addr found */
    return(BTM_UNKNOWN_ADDR);
}

/*******************************************************************************
**
** Function         btm_qos_setup_complete
**
** Description      This function is called when the command complete message
**                  is received from the HCI for the qos setup request.
**
** Returns          void
**
*******************************************************************************/
void btm_qos_setup_complete (UINT8 status, UINT16 handle, FLOW_SPEC *p_flow)
{
    tBTM_CMPL_CB            *p_cb = btm_cb.devcb.p_qossu_cmpl_cb;
    tBTM_QOS_SETUP_CMPL     qossu;
    BTM_TRACE_DEBUG0 ("btm_qos_setup_complete");
    btu_stop_timer (&btm_cb.devcb.qossu_timer);

    btm_cb.devcb.p_qossu_cmpl_cb = NULL;

    if (p_cb)
    {
        memset(&qossu, 0, sizeof(tBTM_QOS_SETUP_CMPL));
        qossu.status = status;
        qossu.handle = handle;
        if (p_flow != NULL)
        {
            qossu.flow.qos_flags = p_flow->qos_flags;
            qossu.flow.service_type = p_flow->service_type;
            qossu.flow.token_rate = p_flow->token_rate;
            qossu.flow.peak_bandwidth = p_flow->peak_bandwidth;
            qossu.flow.latency = p_flow->latency;
            qossu.flow.delay_variation = p_flow->delay_variation;
        }
        BTM_TRACE_DEBUG1 ("BTM: p_flow->delay_variation: 0x%02x",
                          qossu.flow.delay_variation);
        (*p_cb)(&qossu);
    }
}


/*******************************************************************************
**
** Function         BTM_ReadRSSI
**
** Description      This function is called to read the link policy settings.
**                  The address of link policy results are returned in the callback.
**                  (tBTM_RSSI_RESULTS)
**
** Returns          BTM_CMD_STARTED if successfully initiated or error code
**
*******************************************************************************/
tBTM_STATUS BTM_ReadRSSI (BD_ADDR remote_bda, tBTM_CMPL_CB *p_cb)
{
    tACL_CONN   *p;

    BTM_TRACE_API6 ("BTM_ReadRSSI: RemBdAddr: %02x%02x%02x%02x%02x%02x",
                    remote_bda[0], remote_bda[1], remote_bda[2],
                    remote_bda[3], remote_bda[4], remote_bda[5]);

    /* If someone already waiting on the version, do not allow another */
    if (btm_cb.devcb.p_rssi_cmpl_cb)
        return(BTM_BUSY);

    p = btm_bda_to_acl(remote_bda);
    if (p != (tACL_CONN *)NULL)
    {
        btu_start_timer (&btm_cb.devcb.rssi_timer, BTU_TTYPE_BTM_ACL,
                         BTM_DEV_REPLY_TIMEOUT);

        btm_cb.devcb.p_rssi_cmpl_cb = p_cb;

        if (!btsnd_hcic_read_rssi (p->hci_handle))
        {
            btm_cb.devcb.p_rssi_cmpl_cb = NULL;
            btu_stop_timer (&btm_cb.devcb.rssi_timer);
            return(BTM_NO_RESOURCES);
        }
        else
            return(BTM_CMD_STARTED);
    }

    /* If here, no BD Addr found */
    return(BTM_UNKNOWN_ADDR);
}

/*******************************************************************************
**
** Function         BTM_ReadLinkQuality
**
** Description      This function is called to read the link qulaity.
**                  The value of the link quality is returned in the callback.
**                  (tBTM_LINK_QUALITY_RESULTS)
**
** Returns          BTM_CMD_STARTED if successfully initiated or error code
**
*******************************************************************************/
tBTM_STATUS BTM_ReadLinkQuality (BD_ADDR remote_bda, tBTM_CMPL_CB *p_cb)
{
    tACL_CONN   *p;

    BTM_TRACE_API6 ("BTM_ReadLinkQuality: RemBdAddr: %02x%02x%02x%02x%02x%02x",
                    remote_bda[0], remote_bda[1], remote_bda[2],
                    remote_bda[3], remote_bda[4], remote_bda[5]);

    /* If someone already waiting on the version, do not allow another */
    if (btm_cb.devcb.p_lnk_qual_cmpl_cb)
        return(BTM_BUSY);

    p = btm_bda_to_acl(remote_bda);
    if (p != (tACL_CONN *)NULL)
    {
        btu_start_timer (&btm_cb.devcb.lnk_quality_timer, BTU_TTYPE_BTM_ACL,
                         BTM_DEV_REPLY_TIMEOUT);
        btm_cb.devcb.p_lnk_qual_cmpl_cb = p_cb;

        if (!btsnd_hcic_get_link_quality (p->hci_handle))
        {
            btu_stop_timer (&btm_cb.devcb.lnk_quality_timer);
            btm_cb.devcb.p_lnk_qual_cmpl_cb = NULL;
            return(BTM_NO_RESOURCES);
        }
        else
            return(BTM_CMD_STARTED);
    }

    /* If here, no BD Addr found */
    return(BTM_UNKNOWN_ADDR);
}

/*******************************************************************************
**
** Function         BTM_ReadTxPower
**
** Description      This function is called to read the current
**                  TX power of the connection. The tx power level results
**                  are returned in the callback.
**                  (tBTM_RSSI_RESULTS)
**
** Returns          BTM_CMD_STARTED if successfully initiated or error code
**
*******************************************************************************/
tBTM_STATUS BTM_ReadTxPower (BD_ADDR remote_bda, tBTM_CMPL_CB *p_cb)
{
    tACL_CONN   *p;
    BOOLEAN     ret;
#define BTM_READ_RSSI_TYPE_CUR  0x00
#define BTM_READ_RSSI_TYPE_MAX  0X01

    BTM_TRACE_API6 ("BTM_ReadTxPower: RemBdAddr: %02x%02x%02x%02x%02x%02x",
                    remote_bda[0], remote_bda[1], remote_bda[2],
                    remote_bda[3], remote_bda[4], remote_bda[5]);

    /* If someone already waiting on the version, do not allow another */
    if (btm_cb.devcb.p_tx_power_cmpl_cb)
        return(BTM_BUSY);

    p = btm_bda_to_acl(remote_bda);
    if (p != (tACL_CONN *)NULL)
    {
        btu_start_timer (&btm_cb.devcb.tx_power_timer, BTU_TTYPE_BTM_ACL,
                         BTM_DEV_REPLY_TIMEOUT);

        btm_cb.devcb.p_tx_power_cmpl_cb = p_cb;

#if BLE_INCLUDED == TRUE
        if (p->is_le_link)
        {
            memcpy(btm_cb.devcb.read_tx_pwr_addr, remote_bda, BD_ADDR_LEN);
            ret = btsnd_hcic_ble_read_adv_chnl_tx_power();
        }
        else
#endif
        {
            ret = btsnd_hcic_read_tx_power (p->hci_handle, BTM_READ_RSSI_TYPE_CUR);
        }
        if (!ret)
        {
            btm_cb.devcb.p_tx_power_cmpl_cb = NULL;
            btu_stop_timer (&btm_cb.devcb.tx_power_timer);
            return(BTM_NO_RESOURCES);
        }
        else
            return(BTM_CMD_STARTED);
    }

    /* If here, no BD Addr found */
    return (BTM_UNKNOWN_ADDR);
}
/*******************************************************************************
**
** Function         btm_read_tx_power_complete
**
** Description      This function is called when the command complete message
**                  is received from the HCI for the read tx power request.
**
** Returns          void
**
*******************************************************************************/
void btm_read_tx_power_complete (UINT8 *p, BOOLEAN is_ble)
{
    tBTM_CMPL_CB            *p_cb = btm_cb.devcb.p_tx_power_cmpl_cb;
    tBTM_TX_POWER_RESULTS   results;
    UINT16                   handle;
    tACL_CONN               *p_acl_cb = &btm_cb.acl_db[0];
    UINT16                   index;
    BTM_TRACE_DEBUG0 ("btm_read_tx_power_complete");
    btu_stop_timer (&btm_cb.devcb.tx_power_timer);

    /* If there was a callback registered for read rssi, call it */
    btm_cb.devcb.p_tx_power_cmpl_cb = NULL;

    if (p_cb)
    {
        STREAM_TO_UINT8  (results.hci_status, p);

        if (results.hci_status == HCI_SUCCESS)
        {
            results.status = BTM_SUCCESS;

            if (!is_ble)
            {
                STREAM_TO_UINT16 (handle, p);
                STREAM_TO_UINT8 (results.tx_power, p);

                /* Search through the list of active channels for the correct BD Addr */
                for (index = 0; index < MAX_L2CAP_LINKS; index++, p_acl_cb++)
                {
                    if ((p_acl_cb->in_use) && (handle == p_acl_cb->hci_handle))
                    {
                        memcpy (results.rem_bda, p_acl_cb->remote_addr, BD_ADDR_LEN);
                        break;
                    }
                }
            }
#if BLE_INCLUDED == TRUE
            else
            {
                STREAM_TO_UINT8 (results.tx_power, p);
                memcpy(results.rem_bda, btm_cb.devcb.read_tx_pwr_addr, BD_ADDR_LEN);
            }
#endif
            BTM_TRACE_DEBUG2 ("BTM TX power Complete: tx_power %d, hci status 0x%02x",
                                  results.tx_power, results.hci_status);
        }
        else
            results.status = BTM_ERR_PROCESSING;

        (*p_cb)(&results);
    }
}

/*******************************************************************************
**
** Function         btm_read_rssi_complete
**
** Description      This function is called when the command complete message
**                  is received from the HCI for the read rssi request.
**
** Returns          void
**
*******************************************************************************/
void btm_read_rssi_complete (UINT8 *p)
{
    tBTM_CMPL_CB            *p_cb = btm_cb.devcb.p_rssi_cmpl_cb;
    tBTM_RSSI_RESULTS        results;
    UINT16                   handle;
    tACL_CONN               *p_acl_cb = &btm_cb.acl_db[0];
    UINT16                   index;
    BTM_TRACE_DEBUG0 ("btm_read_rssi_complete");
    btu_stop_timer (&btm_cb.devcb.rssi_timer);

    /* If there was a callback registered for read rssi, call it */
    btm_cb.devcb.p_rssi_cmpl_cb = NULL;

    if (p_cb)
    {
        STREAM_TO_UINT8  (results.hci_status, p);

        if (results.hci_status == HCI_SUCCESS)
        {
            results.status = BTM_SUCCESS;

            STREAM_TO_UINT16 (handle, p);

            STREAM_TO_UINT8 (results.rssi, p);
            BTM_TRACE_DEBUG2 ("BTM RSSI Complete: rssi %d, hci status 0x%02x",
                              results.rssi, results.hci_status);

            /* Search through the list of active channels for the correct BD Addr */
            for (index = 0; index < MAX_L2CAP_LINKS; index++, p_acl_cb++)
            {
                if ((p_acl_cb->in_use) && (handle == p_acl_cb->hci_handle))
                {
                    memcpy (results.rem_bda, p_acl_cb->remote_addr, BD_ADDR_LEN);
                    break;
                }
            }
        }
        else
            results.status = BTM_ERR_PROCESSING;

        (*p_cb)(&results);
    }
}

/*******************************************************************************
**
** Function         btm_read_link_quality_complete
**
** Description      This function is called when the command complete message
**                  is received from the HCI for the read link quality.
**
** Returns          void
**
*******************************************************************************/
void btm_read_link_quality_complete (UINT8 *p)
{
    tBTM_CMPL_CB            *p_cb = btm_cb.devcb.p_lnk_qual_cmpl_cb;
    tBTM_LINK_QUALITY_RESULTS results;
    UINT16                   handle;
    tACL_CONN               *p_acl_cb = &btm_cb.acl_db[0];
    UINT16                   index;
    BTM_TRACE_DEBUG0 ("btm_read_link_quality_complete");
    btu_stop_timer (&btm_cb.devcb.rssi_timer);

    /* If there was a callback registered for read rssi, call it */
    btm_cb.devcb.p_lnk_qual_cmpl_cb = NULL;

    if (p_cb)
    {
        STREAM_TO_UINT8  (results.hci_status, p);

        if (results.hci_status == HCI_SUCCESS)
        {
            results.status = BTM_SUCCESS;

            STREAM_TO_UINT16 (handle, p);

            STREAM_TO_UINT8 (results.link_quality, p);
            BTM_TRACE_DEBUG2 ("BTM Link Quality Complete: Link Quality %d, hci status 0x%02x",
                              results.link_quality, results.hci_status);

            /* Search through the list of active channels for the correct BD Addr */
            for (index = 0; index < MAX_L2CAP_LINKS; index++, p_acl_cb++)
            {
                if ((p_acl_cb->in_use) && (handle == p_acl_cb->hci_handle))
                {
                    memcpy (results.rem_bda, p_acl_cb->remote_addr, BD_ADDR_LEN);
                    break;
                }
            }
        }
        else
            results.status = BTM_ERR_PROCESSING;

        (*p_cb)(&results);
    }
}

/*******************************************************************************
**
** Function         btm_remove_acl
**
** Description      This function is called to disconnect an ACL connection
**
** Returns          BTM_SUCCESS if successfully initiated, otherwise BTM_NO_RESOURCES.
**
*******************************************************************************/
tBTM_STATUS btm_remove_acl (BD_ADDR bd_addr)
{
    UINT16  hci_handle = BTM_GetHCIConnHandle(bd_addr);
    tBTM_STATUS status = BTM_SUCCESS;

    BTM_TRACE_DEBUG0 ("btm_remove_acl");
#if BTM_DISC_DURING_RS == TRUE
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev (bd_addr);

    /* Role Switch is pending, postpone until completed */
    if (p_dev_rec && (p_dev_rec->rs_disc_pending == BTM_SEC_RS_PENDING))
    {
        p_dev_rec->rs_disc_pending = BTM_SEC_DISC_PENDING;
    }
    else    /* otherwise can disconnect right away */
#endif

    if (hci_handle != 0xFFFF)
    {
        if (!btsnd_hcic_disconnect (hci_handle, HCI_ERR_PEER_USER))
            status = BTM_NO_RESOURCES;
    }
    else
        status = BTM_UNKNOWN_ADDR;

    return status;
}


/*******************************************************************************
**
** Function         BTM_SetTraceLevel
**
** Description      This function sets the trace level for BTM.  If called with
**                  a value of 0xFF, it simply returns the current trace level.
**
** Returns          The new or current trace level
**
*******************************************************************************/
UINT8 BTM_SetTraceLevel (UINT8 new_level)
{
    BTM_TRACE_DEBUG0 ("BTM_SetTraceLevel");
    if (new_level != 0xFF)
        btm_cb.trace_level = new_level;

    return(btm_cb.trace_level);
}

/*******************************************************************************
**
** Function         btm_cont_rswitch_or_chglinkkey
**
** Description      This function is called to continue processing an active
**                  role switch or change of link key procedure.  It first
**                  disables encryption if enabled and EPR is not supported
**
** Returns          void
**
*******************************************************************************/
void btm_cont_rswitch_or_chglinkkey (tACL_CONN *p, tBTM_SEC_DEV_REC *p_dev_rec,
                                     UINT8 hci_status)
{
    BOOLEAN sw_ok = TRUE;
    BOOLEAN chlk_ok = TRUE;
    BTM_TRACE_DEBUG0 ("btm_cont_rswitch_or_chglinkkey ");
    /* Check to see if encryption needs to be turned off if pending
       change of link key or role switch */
    if (p->switch_role_state == BTM_ACL_SWKEY_STATE_MODE_CHANGE ||
        p->change_key_state == BTM_ACL_SWKEY_STATE_MODE_CHANGE)
    {
        /* Must turn off Encryption first if necessary */
        /* Some devices do not support switch or change of link key while encryption is on */
        if (p_dev_rec != NULL && ((p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED) != 0)
            && !BTM_EPR_AVAILABLE(p))
        {
            if (btsnd_hcic_set_conn_encrypt (p->hci_handle, FALSE))
            {
                p->encrypt_state = BTM_ACL_ENCRYPT_STATE_ENCRYPT_OFF;
                if (p->switch_role_state == BTM_ACL_SWKEY_STATE_MODE_CHANGE)
                    p->switch_role_state = BTM_ACL_SWKEY_STATE_ENCRYPTION_OFF;

                if (p->change_key_state == BTM_ACL_SWKEY_STATE_MODE_CHANGE)
                    p->change_key_state = BTM_ACL_SWKEY_STATE_ENCRYPTION_OFF;
            }
            else
            {
                /* Error occurred; set states back to Idle */
                if (p->switch_role_state == BTM_ACL_SWKEY_STATE_MODE_CHANGE)
                    sw_ok = FALSE;

                if (p->change_key_state == BTM_ACL_SWKEY_STATE_MODE_CHANGE)
                    chlk_ok = FALSE;
            }
        }
        else    /* Encryption not used or EPR supported, continue with switch
                   and/or change of link key */
        {
            if (p->switch_role_state == BTM_ACL_SWKEY_STATE_MODE_CHANGE)
            {
                p->switch_role_state = BTM_ACL_SWKEY_STATE_IN_PROGRESS;
#if BTM_DISC_DURING_RS == TRUE
                if (p_dev_rec)
                    p_dev_rec->rs_disc_pending = BTM_SEC_RS_PENDING;
#endif
                sw_ok = btsnd_hcic_switch_role (p->remote_addr, (UINT8)!p->link_role);
            }

            if (p->change_key_state == BTM_ACL_SWKEY_STATE_MODE_CHANGE)
            {
                p->switch_role_state = BTM_ACL_SWKEY_STATE_IN_PROGRESS;
                chlk_ok = btsnd_hcic_change_link_key (p->hci_handle);
            }
        }

        if (!sw_ok)
        {
            p->switch_role_state = BTM_ACL_SWKEY_STATE_IDLE;
            btm_acl_report_role_change(hci_status, p->remote_addr);
        }

        if (!chlk_ok)
        {
            p->change_key_state = BTM_ACL_SWKEY_STATE_IDLE;
            if (btm_cb.devcb.p_chg_link_key_cb)
            {
                btm_cb.devcb.chg_link_key_ref_data.hci_status = hci_status;
                (*btm_cb.devcb.p_chg_link_key_cb)(&btm_cb.devcb.chg_link_key_ref_data);
                btm_cb.devcb.p_chg_link_key_cb = NULL;
            }
        }
    }
}

/*******************************************************************************
**
** Function         btm_acl_resubmit_page
**
** Description      send pending page request
**
*******************************************************************************/
void btm_acl_resubmit_page (void)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    BT_HDR  *p_buf;
    UINT8   *pp;
    BD_ADDR bda;
    BTM_TRACE_DEBUG0 ("btm_acl_resubmit_page");
    /* If there were other page request schedule can start the next one */
    if ((p_buf = (BT_HDR *)GKI_dequeue (&btm_cb.page_queue)) != NULL)
    {
        /* skip 3 (2 bytes opcode and 1 byte len) to get to the bd_addr
         * for both create_conn and rmt_name */
        pp = (UINT8 *)(p_buf + 1) + p_buf->offset + 3;

        STREAM_TO_BDADDR (bda, pp);

        p_dev_rec = btm_find_or_alloc_dev (bda);

        memcpy (btm_cb.connecting_bda, p_dev_rec->bd_addr,   BD_ADDR_LEN);
        memcpy (btm_cb.connecting_dc,  p_dev_rec->dev_class, DEV_CLASS_LEN);

        btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID, p_buf);
    }
    else
        btm_cb.paging = FALSE;
}

/*******************************************************************************
**
** Function         btm_acl_reset_paging
**
** Description      set paging to FALSE and free the page queue - called at hci_reset
**
*******************************************************************************/
void  btm_acl_reset_paging (void)
{
    BT_HDR *p;
    BTM_TRACE_DEBUG0 ("btm_acl_reset_paging");
    /* If we sent reset we are definitely not paging any more */
    while ((p = (BT_HDR *)GKI_dequeue(&btm_cb.page_queue)) != NULL)
        GKI_freebuf (p);

    btm_cb.paging = FALSE;
}

/*******************************************************************************
**
** Function         btm_acl_set_discing
**
** Description      set discing to the given value
**
*******************************************************************************/
void  btm_acl_set_discing (BOOLEAN discing)
{
    BTM_TRACE_DEBUG0 ("btm_acl_set_discing");
    btm_cb.discing = discing;
}

/*******************************************************************************
**
** Function         btm_acl_paging
**
** Description      send a paging command or queue it in btm_cb
**
*******************************************************************************/
void  btm_acl_paging (BT_HDR *p, BD_ADDR bda)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    BTM_TRACE_DEBUG4 ("btm_acl_paging discing:%d, paging:%d BDA: %06x%06x",
                      btm_cb.discing, btm_cb.paging,
                      (bda[0]<<16) + (bda[1]<<8) + bda[2], (bda[3]<<16) + (bda[4] << 8) + bda[5]);
    if (btm_cb.discing)
    {
        btm_cb.paging = TRUE;
        GKI_enqueue (&btm_cb.page_queue, p);
    }
    else
    {
        if (!BTM_ACL_IS_CONNECTED (bda))
        {
            BTM_TRACE_DEBUG2 ("connecting_bda: %06x%06x",
                              (btm_cb.connecting_bda[0]<<16) + (btm_cb.connecting_bda[1]<<8) + btm_cb.connecting_bda[2],
                              (btm_cb.connecting_bda[3]<<16) + (btm_cb.connecting_bda[4] << 8) + btm_cb.connecting_bda[5]);
            if (btm_cb.paging &&
                memcmp (bda, btm_cb.connecting_bda, BD_ADDR_LEN) != 0)
            {
                GKI_enqueue (&btm_cb.page_queue, p);
            }
            else
            {
                p_dev_rec = btm_find_or_alloc_dev (bda);
                memcpy (btm_cb.connecting_bda, p_dev_rec->bd_addr,   BD_ADDR_LEN);
                memcpy (btm_cb.connecting_dc,  p_dev_rec->dev_class, DEV_CLASS_LEN);

                btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID, p);
            }

            btm_cb.paging = TRUE;
        }
        else /* ACL is already up */
        {
            btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID, p);
        }
    }
}

/*******************************************************************************
**
** Function         btm_acl_notif_conn_collision
**
** Description      Send connection collision event to upper layer if registered
**
** Returns          TRUE if sent out to upper layer,
**                  FALSE if BTM_BUSY_LEVEL_CHANGE_INCLUDED == FALSE, or no one
**                  needs the notification.
**
**          Note: Function only used if BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE
**
*******************************************************************************/
BOOLEAN  btm_acl_notif_conn_collision (BD_ADDR bda)
{
#if (BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
    tBTM_BL_EVENT_DATA  evt_data;

    /* Report possible collision to the upper layer. */
    if (btm_cb.p_bl_changed_cb)
    {
        BTM_TRACE_DEBUG6 ("btm_acl_notif_conn_collision: RemBdAddr: %02x%02x%02x%02x%02x%02x",
                          bda[0], bda[1], bda[2], bda[3], bda[4], bda[5]);

        evt_data.event = BTM_BL_COLLISION_EVT;
        evt_data.conn.p_bda = bda;
        (*btm_cb.p_bl_changed_cb)(&evt_data);
        return TRUE;
    }
    else
        return FALSE;
#else
    return FALSE;
#endif
}


/*******************************************************************************
**
** Function         btm_acl_chk_peer_pkt_type_support
**
** Description      Check if peer supports requested packets
**
*******************************************************************************/
void btm_acl_chk_peer_pkt_type_support (tACL_CONN *p, UINT16 *p_pkt_type)
{
    /* 3 and 5 slot packets? */
    if (!HCI_3_SLOT_PACKETS_SUPPORTED(p->features))
        *p_pkt_type &= ~(BTM_ACL_PKT_TYPES_MASK_DH3 +BTM_ACL_PKT_TYPES_MASK_DM3);

    if (!HCI_5_SLOT_PACKETS_SUPPORTED(p->features))
        *p_pkt_type &= ~(BTM_ACL_PKT_TYPES_MASK_DH5 + BTM_ACL_PKT_TYPES_MASK_DM5);

    /* If HCI version > 2.0, then also check EDR packet types */
    if (btm_cb.devcb.local_version.hci_version >= HCI_PROTO_VERSION_2_0)
    {
        /* 2 and 3 MPS support? */
        if (!HCI_EDR_ACL_2MPS_SUPPORTED(p->features))
            /* Not supported. Add 'not_supported' mask for all 2MPS packet types */
            *p_pkt_type |= (BTM_ACL_PKT_TYPES_MASK_NO_2_DH1 + BTM_ACL_PKT_TYPES_MASK_NO_2_DH3 + BTM_ACL_PKT_TYPES_MASK_NO_2_DH5);

        if (!HCI_EDR_ACL_3MPS_SUPPORTED(p->features))
            /* Not supported. Add 'not_supported' mask for all 3MPS packet types */
            *p_pkt_type |= (BTM_ACL_PKT_TYPES_MASK_NO_3_DH1 + BTM_ACL_PKT_TYPES_MASK_NO_3_DH3 + BTM_ACL_PKT_TYPES_MASK_NO_3_DH5);

        /* EDR 3 and 5 slot support? */
        if (HCI_EDR_ACL_2MPS_SUPPORTED(p->features) || HCI_EDR_ACL_3MPS_SUPPORTED(p->features))
        {
            if (!HCI_3_SLOT_EDR_ACL_SUPPORTED(p->features))
                /* Not supported. Add 'not_supported' mask for all 3-slot EDR packet types */
                *p_pkt_type |= (BTM_ACL_PKT_TYPES_MASK_NO_2_DH3 + BTM_ACL_PKT_TYPES_MASK_NO_3_DH3);

            if (!HCI_5_SLOT_EDR_ACL_SUPPORTED(p->features))
                /* Not supported. Add 'not_supported' mask for all 5-slot EDR packet types */
                *p_pkt_type |= (BTM_ACL_PKT_TYPES_MASK_NO_2_DH5 + BTM_ACL_PKT_TYPES_MASK_NO_3_DH5);
        }
    }
}
