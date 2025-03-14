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
 *  This file contains the action functions for device manager state
 *  machine.
 *
 ******************************************************************************/

#include "gki.h"
#include "bd.h"
#include "bta_sys.h"
#include "bta_api.h"
#include "bta_dm_int.h"
#include "btm_api.h"

#include <string.h>


static void bta_dm_pm_cback(tBTA_SYS_CONN_STATUS status, UINT8 id, UINT8 app_id, BD_ADDR peer_addr);
static void bta_dm_pm_set_mode(BD_ADDR peer_addr, BOOLEAN timed_out );
static void bta_dm_pm_timer_cback(void *p_tle);
static void bta_dm_pm_btm_cback(BD_ADDR bd_addr, tBTM_PM_STATUS status, UINT16 value, UINT8 hci_status);
static BOOLEAN bta_dm_pm_park(BD_ADDR peer_addr);
static BOOLEAN bta_dm_pm_sniff(tBTA_DM_PEER_DEVICE *p_peer_dev, UINT8 index);
static BOOLEAN bta_dm_pm_is_sco_active ();
static void bta_dm_pm_hid_check(BOOLEAN bScoActive);
static void bta_dm_pm_set_sniff_policy(tBTA_DM_PEER_DEVICE *p_dev, BOOLEAN bDisable);
#if (BTM_SSR_INCLUDED == TRUE)
static void bta_dm_pm_ssr(BD_ADDR peer_addr);
static void bta_dm_ssr_cfg_cback(UINT8 id, UINT8 app_id, UINT16 max_lat, UINT16 min_rmt_to);
#endif

tBTA_DM_CONNECTED_SRVCS bta_dm_conn_srvcs;


/*******************************************************************************
**
** Function         bta_dm_init_pm
**
** Description      Initialises the BT low power manager
**
**
** Returns          void
**
*******************************************************************************/
void bta_dm_init_pm(void)
{

    memset(&bta_dm_conn_srvcs, 0x00, sizeof(bta_dm_conn_srvcs));

    /* if there are no power manger entries, so not register */
    if(p_bta_dm_pm_cfg[0].app_id != 0)
    {
        bta_sys_pm_register((tBTA_SYS_CONN_CBACK*)bta_dm_pm_cback);

#if (BTM_SSR_INCLUDED == TRUE)
        bta_sys_ssr_cfg_register((tBTA_SYS_SSR_CFG_CBACK*)bta_dm_ssr_cfg_cback);
#endif
        BTM_PmRegister((BTM_PM_REG_SET | BTM_PM_REG_NOTIF), &bta_dm_cb.pm_id,
                       bta_dm_pm_btm_cback);
    }


}


/*******************************************************************************
**
** Function         bta_dm_disable_pm
**
** Description      Disable PM
**
**
** Returns          void
**
*******************************************************************************/
void bta_dm_disable_pm(void)
{
    UINT8 i;

    bta_sys_pm_register(NULL);
    BTM_PmRegister( BTM_PM_DEREG, &bta_dm_cb.pm_id, NULL);

    /* Need to stop all active timers. */
    for(i=0; i<BTA_DM_NUM_PM_TIMER; i++)
    {
        if(bta_dm_cb.pm_timer[i].in_use)
        {
            APPL_TRACE_DEBUG1("stop dm_pm_timer:%d", i);
            bta_sys_stop_timer(&bta_dm_cb.pm_timer[i].timer);
            bta_dm_cb.pm_timer[i].in_use = FALSE;
        }
    }
}

/*******************************************************************************
**
** Function         bta_dm_pm_stop_timer
**
** Description      stop a PM timer
**
**
** Returns          void
**
*******************************************************************************/
static void bta_dm_pm_stop_timer(BD_ADDR peer_addr)
{
    UINT8 i;

    for(i=0; i<BTA_DM_NUM_PM_TIMER; i++)
    {

        if(bta_dm_cb.pm_timer[i].in_use && !bdcmp(bta_dm_cb.pm_timer[i].peer_bdaddr, peer_addr))
        {
            APPL_TRACE_DEBUG1("stop dm_pm_timer:%d", i);
            bta_sys_stop_timer(&bta_dm_cb.pm_timer[i].timer);
            bta_dm_cb.pm_timer[i].in_use = FALSE;
            break;
        }

    }
}

/*******************************************************************************
**
** Function         bta_dm_pm_cback
**
** Description      Conn change callback from sys for low power management
**
**
** Returns          void
**
*******************************************************************************/
static void bta_dm_pm_cback(tBTA_SYS_CONN_STATUS status, UINT8 id, UINT8 app_id, BD_ADDR peer_addr)
{

    UINT8 i,j;
    UINT16 policy_setting;
    tBTM_STATUS btm_status;
    tBTM_VERSION_INFO vers;
#if (BTM_SSR_INCLUDED == TRUE)
    int               index = BTA_DM_PM_SSR0;
#endif
    tBTA_DM_PEER_DEVICE *p_dev;

    APPL_TRACE_DEBUG3("bta_dm_pm_cback: st(%d), id(%d), app(%d)", status, id, app_id);

    btm_status = BTM_ReadLocalVersion (&vers);
    p_dev = bta_dm_find_peer_device(peer_addr);

	/* Disable/Enable sniff policy on the SCO link if sco Up/Down. Will be removed in 2.2*/
    if ((btm_status == BTM_SUCCESS) &&
        (vers.manufacturer == LMP_COMPID_BROADCOM) &&
        (vers.hci_version < HCI_PROTO_VERSION_2_0) &&
        ((status == BTA_SYS_SCO_OPEN) || (status == BTA_SYS_SCO_CLOSE)) )
        {
        bta_dm_pm_set_sniff_policy(p_dev, (status == BTA_SYS_SCO_OPEN));
    }

    /* find if there is an power mode entry for the service */
    for(i=1; i<=p_bta_dm_pm_cfg[0].app_id; i++)
    {

        if((p_bta_dm_pm_cfg[i].id == id)
            && ((p_bta_dm_pm_cfg[i].app_id == BTA_ALL_APP_ID ) || (p_bta_dm_pm_cfg[i].app_id == app_id )))
            break;

    }

    /* if no entries are there for the app_id and subystem in p_bta_dm_pm_spec*/
    if(i> p_bta_dm_pm_cfg[0].app_id)
        return;

    bta_dm_pm_stop_timer(peer_addr);
    /*p_dev = bta_dm_find_peer_device(peer_addr);*/

#if (BTM_SSR_INCLUDED == TRUE)
    /* set SSR parameters on SYS CONN OPEN */
    if((BTA_SYS_CONN_OPEN == status) && p_dev && (p_dev->info & BTA_DM_DI_USE_SSR))
    {
        index = p_bta_dm_pm_spec[p_bta_dm_pm_cfg[i].spec_idx].ssr;
    }
#endif

    /* if no action for the event */
    if(p_bta_dm_pm_spec[p_bta_dm_pm_cfg[i].spec_idx].actn_tbl[status][0].power_mode == BTA_DM_PM_NO_ACTION)
    {
#if (BTM_SSR_INCLUDED == TRUE)
        if(BTA_DM_PM_SSR0 == index) /* and do not need to set SSR, return. */
#endif
        return;
    }

    for(j=0; j<bta_dm_conn_srvcs.count ; j++)
    {
        /* check if an entry already present */
        if((bta_dm_conn_srvcs.conn_srvc[j].id == id)
            && (bta_dm_conn_srvcs.conn_srvc[j].app_id == app_id )
            && !bdcmp(bta_dm_conn_srvcs.conn_srvc[j].peer_bdaddr, peer_addr))
            break;

    }

        /* if subsystem has no more preference on the power mode remove
       the cb */
    if(p_bta_dm_pm_spec[p_bta_dm_pm_cfg[i].spec_idx].actn_tbl[status][0].power_mode == BTA_DM_PM_NO_PREF)
    {

        if(j != bta_dm_conn_srvcs.count)
        {
            bta_dm_conn_srvcs.count--;

            for(; j<bta_dm_conn_srvcs.count ; j++)
            {

                memcpy(&bta_dm_conn_srvcs.conn_srvc[j], &bta_dm_conn_srvcs.conn_srvc[j+1], sizeof(bta_dm_conn_srvcs.conn_srvc[j]));

            }
        }
        else
        {
            APPL_TRACE_WARNING0("bta_dm_act no entry for connected service cbs");
            return;
        }
    }
    else if(j == bta_dm_conn_srvcs.count )
    {
        /* check if we have more connected service that cbs */
        if(bta_dm_conn_srvcs.count == BTA_DM_NUM_CONN_SRVS)
        {
            APPL_TRACE_WARNING0("bta_dm_act no more connected service cbs");
            return;
        }

        /* fill in a new cb */
        bta_dm_conn_srvcs.conn_srvc[j].id = id;
        bta_dm_conn_srvcs.conn_srvc[j].app_id = app_id;
        bdcpy(bta_dm_conn_srvcs.conn_srvc[j].peer_bdaddr, peer_addr);

        APPL_TRACE_WARNING2("new conn_srvc id:%d, app_id:%d", id, app_id);

        bta_dm_conn_srvcs.count++;
        bta_dm_conn_srvcs.conn_srvc[j].state = status;
    }
    else
    {
        /* no service is added or removed. only updating status. */
        bta_dm_conn_srvcs.conn_srvc[j].state = status;
    }

    if(p_dev)
    {
        p_dev->pm_mode_attempted = 0;
        p_dev->pm_mode_failed = 0;
    }

#if (BTM_SSR_INCLUDED == TRUE)
    if(p_bta_dm_ssr_spec[index].max_lat)
    {
        bta_dm_pm_ssr(peer_addr);
    }
#endif

    bta_dm_pm_set_mode(peer_addr, FALSE);

    /* perform the HID link workaround if needed
    ** 1. If SCO up/down event is received OR
    ** 2. If HID connection open is received and SCO is already active.
    **     This will handle the case where HID connects when SCO already active
    */
    if ( (btm_status == BTM_SUCCESS) &&
         ( ((status == BTA_SYS_SCO_OPEN) || (status == BTA_SYS_SCO_CLOSE)) ||
           ((status == BTA_SYS_CONN_OPEN) && (id == BTA_ID_HH) && bta_dm_pm_is_sco_active()) ) )
    {
        BOOLEAN bScoActive;
        if (status == BTA_SYS_CONN_OPEN)
            bScoActive = TRUE;
        else
            bScoActive = (status == BTA_SYS_SCO_OPEN);

        bta_dm_pm_hid_check(bScoActive);
    }

}


/*******************************************************************************
**
** Function         bta_dm_pm_set_mode
**
** Description      Set the power mode for the device
**
**
** Returns          void
**
*******************************************************************************/
static void bta_dm_pm_set_mode(BD_ADDR peer_addr, BOOLEAN timed_out )
{

    tBTA_DM_PM_ACTTION  pm_action = BTA_DM_PM_NO_ACTION;
    UINT16              timeout = 0;
    UINT8               i,j;
    tBTA_DM_PM_ACTTION  failed_pm = 0;
    tBTA_DM_PEER_DEVICE *p_peer_device = NULL;
    tBTA_DM_PM_ACTTION   allowed_modes = 0;
    tBTA_DM_PM_ACTTION   pref_modes = 0;
    tBTA_DM_PM_CFG      *p_pm_cfg;
    tBTA_DM_PM_SPEC     *p_pm_spec;
    tBTA_DM_PM_ACTN     *p_act0, *p_act1;
    tBTA_DM_SRVCS       *p_srvcs;


    if(!bta_dm_cb.device_list.count)
        return;

    /* see if any attempt to put device in low power mode failed */
    p_peer_device = bta_dm_find_peer_device(peer_addr);
    /* if no peer device found return */
    if (p_peer_device == NULL)
        return;

    failed_pm = p_peer_device->pm_mode_failed;

    for(i=0; i<bta_dm_conn_srvcs.count ; i++)
    {

        p_srvcs = &bta_dm_conn_srvcs.conn_srvc[i];
        if(!bdcmp(p_srvcs->peer_bdaddr, peer_addr))
        {

            /* p_bta_dm_pm_cfg[0].app_id is the number of entries */
            for(j=1; j<=p_bta_dm_pm_cfg[0].app_id; j++)
            {
                if((p_bta_dm_pm_cfg[j].id == p_srvcs->id)
                    && ((p_bta_dm_pm_cfg[j].app_id == BTA_ALL_APP_ID ) ||
                    (p_bta_dm_pm_cfg[j].app_id == p_srvcs->app_id)))
                    break;
            }

            p_pm_cfg = &p_bta_dm_pm_cfg[j];
            p_pm_spec = &p_bta_dm_pm_spec[p_pm_cfg->spec_idx];
            p_act0 = &p_pm_spec->actn_tbl[p_srvcs->state][0];
            p_act1 = &p_pm_spec->actn_tbl[p_srvcs->state][1];

            APPL_TRACE_DEBUG3("bta_dm_pm_set_mode: srvcsid: %d, state: %d, j: %d", p_srvcs->id, p_srvcs->state, j);
            allowed_modes |= p_pm_spec->allow_mask;

            /* PM actions are in the order of strictness */

            /* first check if the first preference is ok */
            if(!(failed_pm & p_act0->power_mode))
            {
                pref_modes |= p_act0->power_mode;

                if(p_act0->power_mode > pm_action)
                {
                    pm_action = p_act0->power_mode;
                    timeout =  p_act0->timeout;

                }
            }
            /* if first preference has already failed, try second preference */
            else if(!(failed_pm & p_act1->power_mode))
            {
                pref_modes |= p_act1->power_mode;

                if(p_act1->power_mode > pm_action)
                {
                    pm_action = p_act1->power_mode;
                    timeout =  p_act1->timeout;

                }
            }
        }
    }

    if(pm_action & (BTA_DM_PM_PARK | BTA_DM_PM_SNIFF))
    {

        /* some service don't like the mode */
        if(!(allowed_modes & pm_action))
        {

            /* select the other mode if its allowed and preferred, otherwise 0 which is BTA_DM_PM_NO_ACTION */
            pm_action =  (allowed_modes & (BTA_DM_PM_PARK | BTA_DM_PM_SNIFF) & pref_modes);

            /* no timeout needed if no action is required */
            if(pm_action == BTA_DM_PM_NO_ACTION)
            {
                timeout = 0;
            }

        }


    }

    if(!timed_out && timeout)
    {

        for(i=0; i<BTA_DM_NUM_PM_TIMER; i++)
        {

            if(!bta_dm_cb.pm_timer[i].in_use)
            {
                bta_dm_cb.pm_timer[i].in_use = TRUE;
                bdcpy(bta_dm_cb.pm_timer[i].peer_bdaddr, peer_addr);
                bta_dm_cb.pm_timer[i].timer.p_cback = bta_dm_pm_timer_cback;
                bta_sys_start_timer(&bta_dm_cb.pm_timer[i].timer, 0, timeout);
                APPL_TRACE_DEBUG2("start dm_pm_timer:%d, %d", i, timeout);
                return;

            }

        }

        /* no more timers */
        if(i==BTA_DM_NUM_PM_TIMER)
        {
            APPL_TRACE_WARNING0("bta_dm_act dm_pm_timer no more");
            return;
        }
    }

    if(pm_action == BTA_DM_PM_NO_ACTION)
    {


    }
    else if(pm_action == BTA_DM_PM_PARK)
    {
        p_peer_device->pm_mode_attempted = BTA_DM_PM_PARK;
        bta_dm_pm_park(peer_addr);

    }
    else if(pm_action & BTA_DM_PM_SNIFF)
    {
        /* dont initiate SNIFF, if link_policy has it disabled */
        if (p_peer_device->link_policy & HCI_ENABLE_SNIFF_MODE)
        {
	        p_peer_device->pm_mode_attempted = BTA_DM_PM_SNIFF;
    	    bta_dm_pm_sniff(p_peer_device, (UINT8)(pm_action & 0x0F) );
        }
        else
        {
            APPL_TRACE_DEBUG0("bta_dm_pm_set_mode: Link policy disallows SNIFF, ignore request");
        }
    }
    else if(pm_action == BTA_DM_PM_ACTIVE)
    {

        bta_dm_pm_active(peer_addr);

    }


}


/*******************************************************************************
**
** Function         bta_ag_pm_park
**
** Description      Switch to park mode.
**
**
** Returns          TRUE if park attempted, FALSE otherwise.
**
*******************************************************************************/
static BOOLEAN bta_dm_pm_park(BD_ADDR peer_addr)
{

    tBTM_PM_MODE    mode = BTM_PM_STS_ACTIVE;

    /* if not in park mode, switch to park */
    BTM_ReadPowerMode(peer_addr, &mode);

    if(mode != BTM_PM_MD_PARK)
    {
        BTM_SetPowerMode (bta_dm_cb.pm_id, peer_addr, &p_bta_dm_pm_md[BTA_DM_PM_PARK_IDX]);
    }
    return TRUE;

}


/*******************************************************************************
**
** Function         bta_ag_pm_sniff
**
** Description      Switch to sniff mode.
**
**
** Returns          TRUE if sniff attempted, FALSE otherwise.
**
*******************************************************************************/
static BOOLEAN bta_dm_pm_sniff(tBTA_DM_PEER_DEVICE *p_peer_dev, UINT8 index)
{
    tBTM_PM_MODE    mode = BTM_PM_STS_ACTIVE;
    tBTM_PM_PWR_MD  pwr_md;
    tBTM_STATUS     status;

    BTM_ReadPowerMode(p_peer_dev->peer_bdaddr, &mode);

#if (BTM_SSR_INCLUDED == TRUE)
    APPL_TRACE_DEBUG3("bta_dm_pm_sniff cur:%d, idx:%d, info:x%x", mode, index, p_peer_dev->info);
    if (mode != BTM_PM_MD_SNIFF ||
        (HCI_SNIFF_SUB_RATE_SUPPORTED(BTM_ReadLocalFeatures ()) &&
         HCI_SNIFF_SUB_RATE_SUPPORTED(BTM_ReadRemoteFeatures (p_peer_dev->peer_bdaddr)) &&
         !(p_peer_dev->info & BTA_DM_DI_USE_SSR)))
#else
    APPL_TRACE_DEBUG2("bta_dm_pm_sniff cur:%d, idx:%d", mode, index);
    if(mode != BTM_PM_MD_SNIFF)
#endif
    {
        /* if the current mode is not sniff, issue the sniff command.
         * If sniff, but SSR is not used in this link, still issue the command */
        memcpy(&pwr_md, &p_bta_dm_pm_md[index], sizeof (tBTM_PM_PWR_MD));
        if (p_peer_dev->info & BTA_DM_DI_INT_SNIFF)
        {
            pwr_md.mode |= BTM_PM_MD_FORCE;
        }
        status = BTM_SetPowerMode (bta_dm_cb.pm_id, p_peer_dev->peer_bdaddr, &pwr_md);
        if (status == BTM_CMD_STORED|| status == BTM_CMD_STARTED)
        {
            p_peer_dev->info &= ~(BTA_DM_DI_INT_SNIFF|BTA_DM_DI_ACP_SNIFF);
            p_peer_dev->info |= BTA_DM_DI_SET_SNIFF;
        }
        else if (status == BTM_SUCCESS)
        {
            APPL_TRACE_DEBUG0("bta_dm_pm_sniff BTM_SetPowerMode() returns BTM_SUCCESS");
            p_peer_dev->info &= ~(BTA_DM_DI_INT_SNIFF|BTA_DM_DI_ACP_SNIFF|BTA_DM_DI_SET_SNIFF);
        }
        else /* error */
        {
            APPL_TRACE_ERROR1("bta_dm_pm_sniff BTM_SetPowerMode() returns ERROR status=%d", status);
            p_peer_dev->info &= ~(BTA_DM_DI_INT_SNIFF|BTA_DM_DI_ACP_SNIFF|BTA_DM_DI_SET_SNIFF);
        }
    }
    /* else already in sniff and is using SSR, do nothing */

    return TRUE;

}

/*******************************************************************************
**
** Function         bta_dm_pm_ssr
**
** Description      checks and sends SSR parameters
**
** Returns          void
**
*******************************************************************************/
#if (BTM_SSR_INCLUDED == TRUE)
static void bta_dm_pm_ssr(BD_ADDR peer_addr)
{
    tBTA_DM_SSR_SPEC *p_spec, *p_spec_cur;
    UINT8   i,j;
    int     ssr = BTA_DM_PM_SSR0;

    /* go through the connected services */
    for(i=0; i<bta_dm_conn_srvcs.count ; i++)
    {
        if(!bdcmp(bta_dm_conn_srvcs.conn_srvc[i].peer_bdaddr, peer_addr))
        {
            /* p_bta_dm_pm_cfg[0].app_id is the number of entries */
            for(j=1; j<=p_bta_dm_pm_cfg[0].app_id; j++)
            {
                /* find the associated p_bta_dm_pm_cfg */
                if((p_bta_dm_pm_cfg[j].id == bta_dm_conn_srvcs.conn_srvc[i].id)
                    && ((p_bta_dm_pm_cfg[j].app_id == BTA_ALL_APP_ID )
                    || (p_bta_dm_pm_cfg[j].app_id == bta_dm_conn_srvcs.conn_srvc[i].app_id)))
                {
                    APPL_TRACE_WARNING2("bta_dm_pm_ssr conn_srvc id:%d, app_id:%d",
                        bta_dm_conn_srvcs.conn_srvc[i].id, bta_dm_conn_srvcs.conn_srvc[i].app_id);
                    break;
                }
            }

            /* find the ssr index with the smallest max latency. */
            p_spec_cur = &p_bta_dm_ssr_spec[p_bta_dm_pm_spec[p_bta_dm_pm_cfg[j].spec_idx].ssr];
            p_spec = &p_bta_dm_ssr_spec[ssr];

            if (p_spec_cur->max_lat < p_spec->max_lat ||
                (ssr == BTA_DM_PM_SSR0 && p_bta_dm_pm_spec[p_bta_dm_pm_cfg[j].spec_idx].ssr != BTA_DM_PM_SSR0))
            {
                ssr = p_bta_dm_pm_spec[p_bta_dm_pm_cfg[j].spec_idx].ssr;
            }

        }
    }

    p_spec = &p_bta_dm_ssr_spec[ssr];
    APPL_TRACE_WARNING2("bta_dm_pm_ssr:%d, lat:%d", ssr, p_spec->max_lat);
    if(p_spec->max_lat)
    {
        /* set the SSR parameters. */
        BTM_SetSsrParams (peer_addr, p_spec->max_lat,
            p_spec->min_rmt_to, p_spec->min_loc_to);
    }
}
/*******************************************************************************
**
** Function         bta_dm_ssr_cfg_cback
**
** Description      Conn change callback from sys for low power management
**
**
** Returns          void
**
*******************************************************************************/
static void bta_dm_ssr_cfg_cback(UINT8 id, UINT8 app_id,
                                 UINT16 max_lat, UINT16 min_rmt_to)
{
    tBTA_DM_SSR_SPEC *p_spec;
    UINT8   i, index;
    /* find if there is an power mode entry for the service */
    for(i=1; i<=p_bta_dm_pm_cfg[0].app_id; i++)
    {

        if((p_bta_dm_pm_cfg[i].id == id)
            && ((p_bta_dm_pm_cfg[i].app_id == BTA_ALL_APP_ID ) || (p_bta_dm_pm_cfg[i].app_id == app_id )))
            break;

    }
    /* if no entries are there for the app_id and subystem in p_bta_dm_pm_spec*/
    if(i> p_bta_dm_pm_cfg[0].app_id)
        return;

    index = p_bta_dm_pm_spec[p_bta_dm_pm_cfg[i].spec_idx].ssr;

    APPL_TRACE_DEBUG2("SSR parameter changed to: max_latency: %d min_tout: %d", max_lat, min_rmt_to);

    p_spec = &p_bta_dm_ssr_spec[index];
    p_spec->max_lat = max_lat;
    p_spec->min_rmt_to = min_rmt_to;
}


#endif
/*******************************************************************************
**
** Function         bta_dm_pm_active
**
** Description      Brings connection to active mode
**
**
** Returns          void
**
*******************************************************************************/
void bta_dm_pm_active(BD_ADDR peer_addr)
{
    tBTM_PM_PWR_MD  pm;

    memset( (void*)&pm, 0, sizeof(pm));

    /* switch to active mode */
    pm.mode = BTM_PM_MD_ACTIVE;
    BTM_SetPowerMode (bta_dm_cb.pm_id, peer_addr, &pm);


}


/*******************************************************************************
**
** Function         bta_dm_pm_btm_cback
**
** Description      BTM power manager callback.
**
**
** Returns          void
**
*******************************************************************************/
static void bta_dm_pm_btm_cback(BD_ADDR bd_addr, tBTM_PM_STATUS status, UINT16 value, UINT8 hci_status)
{
   tBTA_DM_PM_BTM_STATUS  *p_buf;

   if ((p_buf = (tBTA_DM_PM_BTM_STATUS *) GKI_getbuf(sizeof(tBTA_DM_PM_BTM_STATUS))) != NULL)
    {
        p_buf->hdr.event = BTA_DM_PM_BTM_STATUS_EVT;
        p_buf->status = status;
        p_buf->value = value;
        p_buf->hci_status = hci_status;
        bdcpy(p_buf->bd_addr, bd_addr);
        bta_sys_sendmsg(p_buf);
    }
}

/*******************************************************************************
**
** Function         bta_dm_pm_timer_cback
**
** Description      Power management timer callback.
**
**
** Returns          void
**
*******************************************************************************/
static void bta_dm_pm_timer_cback(void *p_tle)
{
    tBTA_DM_PM_TIMER  *p_buf;
    UINT8 i;

    APPL_TRACE_WARNING0("dm_pm_timer expires");

    for(i=0; i<BTA_DM_NUM_PM_TIMER; i++)
    {

        if(bta_dm_cb.pm_timer[i].in_use)
        {

            if(&bta_dm_cb.pm_timer[i].timer == (TIMER_LIST_ENT*) p_tle)
            {
                APPL_TRACE_WARNING1("dm_pm_timer expires %d", i);
                bta_dm_cb.pm_timer[i].in_use = FALSE;
                break;
            }

        }

    }


    /* no more timers */
    if(i==BTA_DM_NUM_PM_TIMER)
    {
        return;
    }

    if ((p_buf = (tBTA_DM_PM_TIMER *) GKI_getbuf(sizeof(tBTA_DM_PM_TIMER))) != NULL)
    {
        p_buf->hdr.event = BTA_DM_PM_TIMER_EVT;
        bdcpy(p_buf->bd_addr, bta_dm_cb.pm_timer[i].peer_bdaddr);
        bta_sys_sendmsg(p_buf);
    }
}

/*******************************************************************************
**
** Function         bta_dm_pm_btm_status
**
** Description      Process pm status event from btm
**
**
** Returns          void
**
*******************************************************************************/
void bta_dm_pm_btm_status(tBTA_DM_MSG *p_data)
{

    tBTA_DM_PEER_DEVICE *p_dev;
    tBTA_DM_DEV_INFO    info;

    APPL_TRACE_DEBUG1("bta_dm_pm_btm_status:%d", p_data->pm_status.status);
    p_dev = bta_dm_find_peer_device(p_data->pm_status.bd_addr);
    if(NULL == p_dev)
        return;

    info = p_dev->info;
    /* check new mode */
    switch (p_data->pm_status.status)
    {
        case BTM_PM_STS_ACTIVE:
            /* if our sniff or park attempt failed
            we should not try it again*/
            if (p_data->pm_status.hci_status != 0)
            {
                APPL_TRACE_ERROR1("bta_dm_pm_btm_status  hci_status=%d", p_data->pm_status.hci_status);
                p_dev->info &= ~(BTA_DM_DI_INT_SNIFF|BTA_DM_DI_ACP_SNIFF|BTA_DM_DI_SET_SNIFF);

                if(p_dev->pm_mode_attempted &(BTA_DM_PM_PARK | BTA_DM_PM_SNIFF))
                {
                    p_dev->pm_mode_failed
                        |= ((BTA_DM_PM_PARK | BTA_DM_PM_SNIFF) & p_dev->pm_mode_attempted);
                    bta_dm_pm_stop_timer(p_data->pm_status.bd_addr);
                    bta_dm_pm_set_mode(p_data->pm_status.bd_addr, FALSE);
                }
            }
            else
            {
#if (BTM_SSR_INCLUDED == TRUE)
                if(p_dev->prev_low)
                {
                    /* need to send the SSR paramaters to controller again */
                    bta_dm_pm_ssr(p_dev->peer_bdaddr);
                }
                p_dev->prev_low = BTM_PM_STS_ACTIVE;
#endif
                bta_dm_pm_stop_timer(p_data->pm_status.bd_addr);
                bta_dm_pm_set_mode(p_data->pm_status.bd_addr, FALSE);
            }
            break;

#if (BTM_SSR_INCLUDED == TRUE)
        case BTM_PM_STS_PARK:
        case BTM_PM_STS_HOLD:
            /* save the previous low power mode - for SSR.
             * SSR parameters are sent to controller on "conn open".
             * the numbers stay good until park/hold/detach */
            if(p_dev->info & BTA_DM_DI_USE_SSR)
                p_dev->prev_low = p_data->pm_status.status;
            break;

        case BTM_PM_STS_SSR:
            if(p_data->pm_status.value)
                p_dev->info |= BTA_DM_DI_USE_SSR;
            else
                p_dev->info &= ~BTA_DM_DI_USE_SSR;
            break;
#endif
        case BTM_PM_STS_SNIFF:
            p_dev->info &= ~(BTA_DM_DI_SET_SNIFF|BTA_DM_DI_INT_SNIFF|BTA_DM_DI_ACP_SNIFF);
            if (info & BTA_DM_DI_SET_SNIFF)
                p_dev->info |= BTA_DM_DI_INT_SNIFF;
            else
                p_dev->info |= BTA_DM_DI_ACP_SNIFF;
            break;

        case BTM_PM_STS_ERROR:
            p_dev->info &= ~BTA_DM_DI_SET_SNIFF;
            break;

        default:
            break;
    }



}

/*******************************************************************************
**
** Function         bta_dm_pm_timer
**
** Description      Process pm timer event from btm
**
**
** Returns          void
**
*******************************************************************************/
void bta_dm_pm_timer(tBTA_DM_MSG *p_data)
{

    APPL_TRACE_WARNING0("proc dm_pm_timer expires");
    bta_dm_pm_set_mode(p_data->pm_status.bd_addr, TRUE);


}

/*******************************************************************************
**
** Function         bta_dm_find_peer_device
**
** Description      Given an address, find the associated control block.
**
** Returns          tBTA_DM_PEER_DEVICE
**
*******************************************************************************/
tBTA_DM_PEER_DEVICE * bta_dm_find_peer_device(BD_ADDR peer_addr)
{
    tBTA_DM_PEER_DEVICE *p_dev = NULL;
    int i;

    for(i=0; i<bta_dm_cb.device_list.count; i++)
    {
        if(!bdcmp( bta_dm_cb.device_list.peer_device[i].peer_bdaddr, peer_addr))
        {
            p_dev = &bta_dm_cb.device_list.peer_device[i];
            break;
        }

    }
    return p_dev;
}

/*******************************************************************************
**
** Function         bta_dm_is_sco_active
**
** Description      Loop through connected services for HFP+State=SCO
**
** Returns          BOOLEAN. TRUE if SCO active, else FALSE
**
*******************************************************************************/
static BOOLEAN bta_dm_pm_is_sco_active ()
{
    int j;
    BOOLEAN bScoActive = FALSE;

    for(j=0; j<bta_dm_conn_srvcs.count ; j++)
    {
        /* check if an entry already present */
        if ( (bta_dm_conn_srvcs.conn_srvc[j].id == BTA_ID_AG )  && (bta_dm_conn_srvcs.conn_srvc[j].state == BTA_SYS_SCO_OPEN) )
        {
            bScoActive = TRUE;
            break;
        }
    }

    APPL_TRACE_DEBUG1("bta_dm_is_sco_active: SCO active: %d", bScoActive);
    return bScoActive;
}


/*******************************************************************************
**
** Function         bta_dm_pm_hid_check
**
** Description      Disables/Enables sniff in link policy based on SCO Up/Down
**
** Returns          None
**
*******************************************************************************/

static void bta_dm_pm_hid_check(BOOLEAN bScoActive)
{
    int j;

    /* if HID is active, disable the link policy */
    for(j=0; j<bta_dm_conn_srvcs.count ; j++)
    {
        /* check if an entry already present */
        if(bta_dm_conn_srvcs.conn_srvc[j].id == BTA_ID_HH )
        {
            APPL_TRACE_DEBUG2 ("SCO status change(Active: %d), modify HID link policy. state: %d",
                bScoActive, bta_dm_conn_srvcs.conn_srvc[j].state);
            bta_dm_pm_set_sniff_policy( bta_dm_find_peer_device(bta_dm_conn_srvcs.conn_srvc[j].peer_bdaddr), bScoActive);

            /* if we had disabled link policy, seems like the hid device stop retrying SNIFF after a few tries. force sniff if needed */
            if (!bScoActive)
                bta_dm_pm_set_mode(bta_dm_conn_srvcs.conn_srvc[j].peer_bdaddr, FALSE);
        }
    }

}

/*******************************************************************************
**
** Function         bta_dm_pm_set_sniff_policy
**
** Description      Disables/Enables sniff in link policy for the give device
**
** Returns          None
**
*******************************************************************************/
static void bta_dm_pm_set_sniff_policy(tBTA_DM_PEER_DEVICE *p_dev, BOOLEAN bDisable)
{
    UINT16 policy_setting;

    if (!p_dev)
        return;

    if (bDisable)
    {
        policy_setting = bta_dm_cb.cur_policy &
            (HCI_ENABLE_MASTER_SLAVE_SWITCH |
             HCI_ENABLE_HOLD_MODE  |
             HCI_ENABLE_PARK_MODE);

    }
    else
    {
        /*  allow sniff after sco is closed */
         policy_setting= bta_dm_cb.cur_policy;
    }

    /* if disabling SNIFF, make sure link is Active */
    if (bDisable)
        bta_dm_pm_active(p_dev->peer_bdaddr);

    /* update device record and set link policy */
    p_dev->link_policy = policy_setting;
    BTM_SetLinkPolicy(p_dev->peer_bdaddr, &policy_setting);

}
