/******************************************************************************
 *
 *  NOTICE OF CHANGES
 *  2024/03/26:
 *      - Added #defines for RVL target
 *      - Modify bta_sys_init to match RVL version
 *      - Modify bta_sys_event to match RVL version
 *      - Modify bta_sys_register to match RVL version
 *      - Modify bta_sys_disable to match RVL version
 * 
 *  Compile with REVOLUTION defined to include these changes.
 * 
 ******************************************************************************/



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
 *  This is the main implementation file for the BTA system manager.
 *
 ******************************************************************************/

#include "btm_api.h"
#include "bta_api.h"
#include "bta_sys.h"
#include "bta_sys_int.h"
#include "bta_sys_ci.h"
#include "bta_sys_co.h"
#if BTA_FM_INCLUDED == TRUE
#include "bta_fm_api.h"
#endif
#if BTA_FMTX_INCLUDED == TRUE
#include "bta_fmtx_api.h"
#endif
#if GPS_INCLUDED == TRUE
#include "bta_gps_api.h"
#endif

#include "gki.h"
#include "ptim.h"
#include <string.h>
#if( defined BTA_AR_INCLUDED ) && (BTA_AR_INCLUDED == TRUE)
#include "bta_ar_api.h"
#endif

#ifdef REVOLUTION
#include "bta_dm_int.h"
#endif

/* protocol timer update period, in milliseconds */
#ifndef BTA_SYS_TIMER_PERIOD
#define BTA_SYS_TIMER_PERIOD            1000
#endif

/* system manager control block definition */
#if BTA_DYNAMIC_MEMORY == FALSE
tBTA_SYS_CB bta_sys_cb;
#endif

/* trace level */

#ifdef REVOLUTION
UINT8 appl_trace_level = BT_TRACE_LEVEL_NONE;
#else
/* TODO Bluedroid - Hard-coded trace levels -  Needs to be configurable */
UINT8 appl_trace_level = BT_TRACE_LEVEL_DEBUG; //APPL_INITIAL_TRACE_LEVEL;
#endif

#ifndef REVOLUTION
UINT8 btif_trace_level = BT_TRACE_LEVEL_DEBUG;

static const tBTA_SYS_REG bta_sys_hw_reg =
{
    bta_sys_sm_execute,
    NULL
};


/* type for action functions */
typedef void (*tBTA_SYS_ACTION)(tBTA_SYS_HW_MSG *p_data);

/* action function list */
const tBTA_SYS_ACTION bta_sys_action[] =
{
    /* device manager local device API events - cf bta_sys.h for events */
    bta_sys_hw_api_enable,             /* 0  BTA_SYS_HW_API_ENABLE_EVT    */
    bta_sys_hw_evt_enabled,           /* 1  BTA_SYS_HW_EVT_ENABLED_EVT */
    bta_sys_hw_evt_stack_enabled,       /* 2  BTA_SYS_HW_EVT_STACK_ENABLED_EVT */
    bta_sys_hw_api_disable,             /* 3  BTA_SYS_HW_API_DISABLE_EVT     */
    bta_sys_hw_evt_disabled,           /* 4  BTA_SYS_HW_EVT_DISABLED_EVT  */
    bta_sys_hw_error                        /* 5   BTA_SYS_HW_ERROR_EVT  */
};

/* state machine action enumeration list */
enum
{
    /* device manager local device API events */
    BTA_SYS_HW_API_ENABLE,
    BTA_SYS_HW_EVT_ENABLED,
    BTA_SYS_HW_EVT_STACK_ENABLED,
    BTA_SYS_HW_API_DISABLE,
    BTA_SYS_HW_EVT_DISABLED,
    BTA_SYS_HW_ERROR
};

#define BTA_SYS_NUM_ACTIONS  (BTA_SYS_MAX_EVT & 0x00ff)
#define BTA_SYS_IGNORE       BTA_SYS_NUM_ACTIONS

/* state table information */
#define BTA_SYS_ACTIONS              2       /* number of actions */
#define BTA_SYS_NEXT_STATE           2       /* position of next state */
#define BTA_SYS_NUM_COLS             3       /* number of columns in state tables */


/* state table for OFF state */
const UINT8 bta_sys_hw_off[][BTA_SYS_NUM_COLS] =
{
/* Event                    Action 1               Action 2             Next State */
/* API_ENABLE    */  {BTA_SYS_HW_API_ENABLE,    BTA_SYS_IGNORE,     BTA_SYS_HW_STARTING},
/* EVT_ENABLED   */  {BTA_SYS_IGNORE,           BTA_SYS_IGNORE,     BTA_SYS_HW_STARTING},
/* STACK_ENABLED */  {BTA_SYS_IGNORE,           BTA_SYS_IGNORE,     BTA_SYS_HW_ON},
/* API_DISABLE   */  {BTA_SYS_HW_EVT_DISABLED,  BTA_SYS_IGNORE,     BTA_SYS_HW_OFF},
/* EVT_DISABLED  */  {BTA_SYS_IGNORE,           BTA_SYS_IGNORE,     BTA_SYS_HW_OFF},
/* EVT_ERROR     */  {BTA_SYS_IGNORE,           BTA_SYS_IGNORE,     BTA_SYS_HW_OFF}
};

const UINT8 bta_sys_hw_starting[][BTA_SYS_NUM_COLS] =
{
/* Event                    Action 1                   Action 2               Next State */
/* API_ENABLE    */  {BTA_SYS_IGNORE,               BTA_SYS_IGNORE,         BTA_SYS_HW_STARTING}, /* wait for completion event */
/* EVT_ENABLED   */  {BTA_SYS_HW_EVT_ENABLED,       BTA_SYS_IGNORE,         BTA_SYS_HW_STARTING},
/* STACK_ENABLED */  {BTA_SYS_HW_EVT_STACK_ENABLED, BTA_SYS_IGNORE,         BTA_SYS_HW_ON},
/* API_DISABLE   */  {BTA_SYS_IGNORE,               BTA_SYS_IGNORE,         BTA_SYS_HW_STOPPING}, /* successive disable/enable: change state wait for completion to disable */
/* EVT_DISABLED  */  {BTA_SYS_HW_EVT_DISABLED,      BTA_SYS_HW_API_ENABLE,  BTA_SYS_HW_STARTING}, /* successive enable/disable: notify, then restart HW */
/* EVT_ERROR */      {BTA_SYS_HW_ERROR,             BTA_SYS_IGNORE,         BTA_SYS_HW_ON}
};

const UINT8 bta_sys_hw_on[][BTA_SYS_NUM_COLS] =
{
/* Event                    Action 1                   Action 2               Next State */
/* API_ENABLE    */  {BTA_SYS_HW_API_ENABLE,        BTA_SYS_IGNORE,         BTA_SYS_HW_ON},
/* EVT_ENABLED   */  {BTA_SYS_IGNORE,               BTA_SYS_IGNORE,         BTA_SYS_HW_ON},
/* STACK_ENABLED */  {BTA_SYS_IGNORE,               BTA_SYS_IGNORE,         BTA_SYS_HW_ON},
/* API_DISABLE   */  {BTA_SYS_HW_API_DISABLE,       BTA_SYS_IGNORE,         BTA_SYS_HW_ON}, /* don't change the state here, as some other modules might be active */
/* EVT_DISABLED */   {BTA_SYS_HW_ERROR,             BTA_SYS_IGNORE,         BTA_SYS_HW_ON},
/* EVT_ERROR */      {BTA_SYS_HW_ERROR,             BTA_SYS_IGNORE,         BTA_SYS_HW_ON}
};

const UINT8 bta_sys_hw_stopping[][BTA_SYS_NUM_COLS] =
{
/* Event                    Action 1                   Action 2               Next State */
/* API_ENABLE    */  {BTA_SYS_IGNORE,               BTA_SYS_IGNORE,         BTA_SYS_HW_STARTING}, /* change state, and wait for completion event to enable */
/* EVT_ENABLED   */  {BTA_SYS_HW_EVT_ENABLED,       BTA_SYS_IGNORE,         BTA_SYS_HW_STOPPING}, /* successive enable/disable: finish the enable before disabling */
/* STACK_ENABLED */  {BTA_SYS_HW_EVT_STACK_ENABLED, BTA_SYS_HW_API_DISABLE, BTA_SYS_HW_STOPPING}, /* successive enable/disable: notify, then stop */
/* API_DISABLE   */  {BTA_SYS_IGNORE,               BTA_SYS_IGNORE,         BTA_SYS_HW_STOPPING}, /* wait for completion event */
/* EVT_DISABLED  */  {BTA_SYS_HW_EVT_DISABLED,      BTA_SYS_IGNORE,         BTA_SYS_HW_OFF},
/* EVT_ERROR     */  {BTA_SYS_HW_API_DISABLE,       BTA_SYS_IGNORE,         BTA_SYS_HW_STOPPING}
};

typedef const UINT8 (*tBTA_SYS_ST_TBL)[BTA_SYS_NUM_COLS];

/* state table */
const tBTA_SYS_ST_TBL bta_sys_st_tbl[] = {
    bta_sys_hw_off,
    bta_sys_hw_starting,
    bta_sys_hw_on,
    bta_sys_hw_stopping
};
#endif

/*******************************************************************************
**
** Function         bta_sys_init
**
** Description      BTA initialization; called from task initialization.
**
**
** Returns          void
**
*******************************************************************************/
BTA_API void bta_sys_init(void)
{
    memset(&bta_sys_cb, 0, sizeof(tBTA_SYS_CB));
    ptim_init(&bta_sys_cb.ptim_cb, BTA_SYS_TIMER_PERIOD, p_bta_sys_cfg->timer);
    bta_sys_cb.task_id = GKI_get_taskid();
    appl_trace_level = p_bta_sys_cfg->trace_level;

#ifndef REVOLUTION
    /* register BTA SYS message handler */
    bta_sys_register( BTA_ID_SYS,  &bta_sys_hw_reg);

    /* register for BTM notifications */
    BTM_RegisterForDeviceStatusNotif ((tBTM_DEV_STATUS_CB*)&bta_sys_hw_btm_cback );

#if( defined BTA_AR_INCLUDED ) && (BTA_AR_INCLUDED == TRUE)
    bta_ar_init();
#endif
#endif
}

#ifndef REVOLUTION
/*******************************************************************************
**
** Function         bta_dm_sm_execute
**
** Description      State machine event handling function for DM
**
**
** Returns          void
**
*******************************************************************************/
BOOLEAN bta_sys_sm_execute(BT_HDR *p_msg)
{
    BOOLEAN freebuf = TRUE;
    tBTA_SYS_ST_TBL      state_table;
    UINT8               action;
    int                 i;

    APPL_TRACE_EVENT2("bta_sys_sm_execute state:%d, event:0x%x",  bta_sys_cb.state, p_msg->event);

    /* look up the state table for the current state */
    state_table = bta_sys_st_tbl[bta_sys_cb.state];
    /* update state */
    bta_sys_cb.state = state_table[p_msg->event & 0x00ff][BTA_SYS_NEXT_STATE];

    /* execute action functions */
    for (i = 0; i < BTA_SYS_ACTIONS; i++)
    {
        if ((action = state_table[p_msg->event & 0x00ff][i]) != BTA_SYS_IGNORE)
        {
            (*bta_sys_action[action])( (tBTA_SYS_HW_MSG*) p_msg);
        }
        else
        {
            break;
        }
    }
    return freebuf;

}


void bta_sys_hw_register( tBTA_SYS_HW_MODULE module, tBTA_SYS_HW_CBACK *cback)
{
    bta_sys_cb.sys_hw_cback[module]=cback;
}


void bta_sys_hw_unregister( tBTA_SYS_HW_MODULE module )
{
    bta_sys_cb.sys_hw_cback[module]=NULL;
}

/*******************************************************************************
**
** Function         bta_sys_hw_btm_cback
**
** Description     This function is registered by BTA SYS to BTM in order to get status notifications
**
**
** Returns
**
*******************************************************************************/
void bta_sys_hw_btm_cback( tBTM_DEV_STATUS status )
{

    tBTA_SYS_HW_MSG *sys_event;

    APPL_TRACE_DEBUG1(" bta_sys_hw_btm_cback was called with parameter: %i" , status );

    /* send a message to BTA SYS */
    if ((sys_event = (tBTA_SYS_HW_MSG *) GKI_getbuf(sizeof(tBTA_SYS_HW_MSG))) != NULL)
    {
        if (status == BTM_DEV_STATUS_UP)
            sys_event->hdr.event = BTA_SYS_EVT_STACK_ENABLED_EVT;
        else if (status == BTM_DEV_STATUS_DOWN)
            sys_event->hdr.event = BTA_SYS_ERROR_EVT;
        else
        {
            /* BTM_DEV_STATUS_CMD_TOUT is ignored for now. */
            GKI_freebuf (sys_event);
            sys_event = NULL;
        }

        if (sys_event)
        {
            bta_sys_sendmsg(sys_event);
        }
    }
    else
    {
        APPL_TRACE_DEBUG0("ERROR bta_sys_hw_btm_cback couldn't send msg" );
    }
}



/*******************************************************************************
**
** Function         bta_sys_hw_error
**
** Description     In case the HW device stops answering... Try to turn it off, then re-enable all
**                      previously active SW modules.
**
** Returns          success or failure
**
*******************************************************************************/
void bta_sys_hw_error(tBTA_SYS_HW_MSG *p_sys_hw_msg)
{

    UINT8 module_index;

    APPL_TRACE_DEBUG1("%s", __FUNCTION__);

    for (module_index = 0; module_index < BTA_SYS_MAX_HW_MODULES; module_index++)
    {
        if( bta_sys_cb.sys_hw_module_active &  ((UINT32)1 << module_index )) {
            switch( module_index)
                {
                case BTA_SYS_HW_BLUETOOTH:
                   /* Send BTA_SYS_HW_ERROR_EVT to DM */
                   if (bta_sys_cb.sys_hw_cback[module_index] != NULL)
                       bta_sys_cb.sys_hw_cback[module_index] (BTA_SYS_HW_ERROR_EVT);
                    break;
                default:
                    /* not yet supported */
                    break;
                }
        }
    }
}



/*******************************************************************************
**
** Function         bta_sys_hw_enable
**
** Description     this function is called after API enable and HW has been turned on
**
**
** Returns          success or failure
**
*******************************************************************************/

void bta_sys_hw_api_enable( tBTA_SYS_HW_MSG *p_sys_hw_msg )
{
    if ((!bta_sys_cb.sys_hw_module_active) && (bta_sys_cb.state != BTA_SYS_HW_ON))
    {
        /* register which HW module was turned on */
        bta_sys_cb.sys_hw_module_active |=  ((UINT32)1 << p_sys_hw_msg->hw_module );

        /* use call-out to power-up HW */
        bta_sys_hw_co_enable(p_sys_hw_msg->hw_module);
    }
    else
    {
        /* register which HW module was turned on */
        bta_sys_cb.sys_hw_module_active |=  ((UINT32)1 << p_sys_hw_msg->hw_module );

        /* HW already in use, so directly notify the caller */
        if (bta_sys_cb.sys_hw_cback[p_sys_hw_msg->hw_module ]!= NULL )
            bta_sys_cb.sys_hw_cback[p_sys_hw_msg->hw_module ](  BTA_SYS_HW_ON_EVT   );
    }

    APPL_TRACE_EVENT2 ("bta_sys_hw_api_enable for %d, active modules 0x%04X",
                    p_sys_hw_msg->hw_module, bta_sys_cb.sys_hw_module_active);

}

/*******************************************************************************
**
** Function         bta_sys_hw_disable
**
** Description     if no other module is using the HW, this function will call ( if defined ) a user-macro to turn off the HW
**
**
** Returns          success or failure
**
*******************************************************************************/
void bta_sys_hw_api_disable(tBTA_SYS_HW_MSG *p_sys_hw_msg)
{
    APPL_TRACE_DEBUG2("bta_sys_hw_api_disable for %d, active modules: 0x%04X",
        p_sys_hw_msg->hw_module, bta_sys_cb.sys_hw_module_active );

    /* make sure the related SW blocks were stopped */
    bta_sys_disable( p_sys_hw_msg->hw_module );


    /* register which module we turn off */
    bta_sys_cb.sys_hw_module_active &=  ~((UINT32)1 << p_sys_hw_msg->hw_module );


    /* if there are still some SW modules using the HW, just provide an answer to the calling */
    if( bta_sys_cb.sys_hw_module_active != 0  )
    {
        /*  if there are still some SW modules using the HW,  directly notify the caller */
        if( bta_sys_cb.sys_hw_cback[p_sys_hw_msg->hw_module ]!= NULL )
            bta_sys_cb.sys_hw_cback[p_sys_hw_msg->hw_module ](  BTA_SYS_HW_OFF_EVT   );
    }
    else
    {
        /* manually update the state of our system */
        bta_sys_cb.state = BTA_SYS_HW_STOPPING;
        /* and use the call-out to disable HW */
        bta_sys_hw_co_disable(p_sys_hw_msg->hw_module);
    }

}


/*******************************************************************************
**
** Function         bta_sys_hw_event_enabled
**
** Description
**
**
** Returns          success or failure
**
*******************************************************************************/
void bta_sys_hw_evt_enabled(tBTA_SYS_HW_MSG *p_sys_hw_msg)
{
    APPL_TRACE_EVENT1("bta_sys_hw_evt_enabled for %i", p_sys_hw_msg->hw_module);

#if ( defined BTM_AUTOMATIC_HCI_RESET && BTM_AUTOMATIC_HCI_RESET == TRUE )
    /* If device is already up, send a fake "BTM DEVICE UP" using BTA SYS state machine */
    /* If we are in the middle device initialization, BTM_DEVICE_UP will be issued      */
    /* by BTM once initialization is done.                                              */
    if (BTA_DmIsDeviceUp())
    {
        bta_sys_hw_btm_cback (BTM_DEV_STATUS_UP);
    }
#else

    /* if HCI reset was not sent during stack start-up */
    BTM_DeviceReset( NULL );

#endif
}


/*******************************************************************************
**
** Function         bta_sys_hw_event_disabled
**
** Description
**
**
** Returns          success or failure
**
*******************************************************************************/
void bta_sys_hw_evt_disabled(tBTA_SYS_HW_MSG *p_sys_hw_msg)
{
    UINT8 hw_module_index;

    APPL_TRACE_DEBUG1("bta_sys_hw_evt_disabled - module 0x%X", p_sys_hw_msg->hw_module);

    for (hw_module_index = 0; hw_module_index < BTA_SYS_MAX_HW_MODULES; hw_module_index++)
    {
        if (bta_sys_cb.sys_hw_cback[hw_module_index] != NULL)
            bta_sys_cb.sys_hw_cback[hw_module_index] (BTA_SYS_HW_OFF_EVT);
    }
}

/*******************************************************************************
**
** Function         bta_sys_hw_event_stack_enabled
**
** Description     we receive this event from once the SW side is ready ( stack, FW download,... ),
**                       i.e. we can really start using the device. So notify the app.
**
** Returns          success or failure
**
*******************************************************************************/
void bta_sys_hw_evt_stack_enabled(tBTA_SYS_HW_MSG *p_sys_hw_msg)
{
    UINT8 hw_module_index;

    APPL_TRACE_DEBUG0(" bta_sys_hw_evt_stack_enabled!notify the callers");

    for (hw_module_index = 0; hw_module_index < BTA_SYS_MAX_HW_MODULES; hw_module_index++ )
    {
        if (bta_sys_cb.sys_hw_cback[hw_module_index] != NULL)
            bta_sys_cb.sys_hw_cback[hw_module_index] (BTA_SYS_HW_ON_EVT);
    }
}
#endif



/*******************************************************************************
**
** Function         bta_sys_event
**
** Description      BTA event handler; called from task event handler.
**
**
** Returns          void
**
*******************************************************************************/
BTA_API void bta_sys_event(BT_HDR *p_msg)
{
    UINT8       id;
    BOOLEAN     freebuf = TRUE;

    APPL_TRACE_EVENT1("BTA got event 0x%x", p_msg->event);

    /* get subsystem id from event */
    id = (UINT8) (p_msg->event >> 8);

#ifdef REVOLUTION
    if (bta_sys_cb.events_disabled)
    {
        if (p_msg->event == 0x0101)
        {
            bta_dm_immediate_disable();
        }

        GKI_freebuf(p_msg);
        return;
    }
#endif

    /* verify id and call subsystem event handler */
    if ((id < BTA_ID_MAX) && (bta_sys_cb.reg[id] != NULL))
    {
        freebuf = (*bta_sys_cb.reg[id]->evt_hdlr)(p_msg);
    }
    else
    {
        APPL_TRACE_WARNING1("BTA got unregistered event id %d", id);
    }

    if (freebuf)
    {
        GKI_freebuf(p_msg);
    }

}

/*******************************************************************************
**
** Function         bta_sys_timer_update
**
** Description      Update the BTA timer list and handle expired timers.
**
** Returns          void
**
*******************************************************************************/
BTA_API void bta_sys_timer_update(void)
{
    if (!bta_sys_cb.timers_disabled)
    {
        ptim_timer_update(&bta_sys_cb.ptim_cb);
    }
}

/*******************************************************************************
**
** Function         bta_sys_register
**
** Description      Called by other BTA subsystems to register their event
**                  handler.
**
**
** Returns          void
**
*******************************************************************************/
void bta_sys_register(UINT8 id, const tBTA_SYS_REG *p_reg)
{
    bta_sys_cb.reg[id] = (tBTA_SYS_REG *) p_reg;
#ifndef REVOLUTION
    bta_sys_cb.is_reg[id] = TRUE;
#endif
}

#ifndef REVOLUTION
/*******************************************************************************
**
** Function         bta_sys_deregister
**
** Description      Called by other BTA subsystems to de-register
**                  handler.
**
**
** Returns          void
**
*******************************************************************************/
void bta_sys_deregister(UINT8 id)
{
    bta_sys_cb.is_reg[id] = FALSE;
}

/*******************************************************************************
**
** Function         bta_sys_is_register
**
** Description      Called by other BTA subsystems to get registeration
**                  status.
**
**
** Returns          void
**
*******************************************************************************/
BOOLEAN bta_sys_is_register(UINT8 id)
{
    return bta_sys_cb.is_reg[id];
}
#endif

/*******************************************************************************
**
** Function         bta_sys_sendmsg
**
** Description      Send a GKI message to BTA.  This function is designed to
**                  optimize sending of messages to BTA.  It is called by BTA
**                  API functions and call-in functions.
**
**
** Returns          void
**
*******************************************************************************/
void bta_sys_sendmsg(void *p_msg)
{
    GKI_send_msg(bta_sys_cb.task_id, p_bta_sys_cfg->mbox, p_msg);
}

/*******************************************************************************
**
** Function         bta_sys_start_timer
**
** Description      Start a protocol timer for the specified amount
**                  of time in milliseconds.
**
** Returns          void
**
*******************************************************************************/
void bta_sys_start_timer(TIMER_LIST_ENT *p_tle, UINT16 type, INT32 timeout)
{
    ptim_start_timer(&bta_sys_cb.ptim_cb, p_tle, type, timeout);
}

/*******************************************************************************
**
** Function         bta_sys_stop_timer
**
** Description      Stop a BTA timer.
**
** Returns          void
**
*******************************************************************************/
void bta_sys_stop_timer(TIMER_LIST_ENT *p_tle)
{
    ptim_stop_timer(&bta_sys_cb.ptim_cb, p_tle);
}

/*******************************************************************************
**
** Function         bta_sys_disable
**
** Description      For each registered subsystem execute its disable function.
**
** Returns          void
**
*******************************************************************************/
void bta_sys_disable(tBTA_SYS_HW_MODULE module)
{
    int bta_id = 0;
    int bta_id_max = 0;

#ifndef REVOLUTION
    APPL_TRACE_DEBUG1("bta_sys_disable: module %i", module);

    switch( module )
    {
        case BTA_SYS_HW_BLUETOOTH:
            bta_id = BTA_ID_DM;
            bta_id_max = BTA_ID_BLUETOOTH_MAX;
            break;
        case BTA_SYS_HW_FMRX:
            bta_id = BTA_ID_FM;
            bta_id_max = BTA_ID_FM;
            break;
        case BTA_SYS_HW_FMTX:
            bta_id = BTA_ID_FMTX;
            bta_id_max = BTA_ID_FMTX;
            break;
        case BTA_SYS_HW_GPS:
            bta_id = BTA_ID_GPS;
            bta_id_max = BTA_ID_GPS;
            break;
        default:
            APPL_TRACE_WARNING0("bta_sys_disable: unkown module");
            return;
    }
#endif

#ifdef REVOLUTION
    for ( ; bta_id < BTA_ID_BLUETOOTH_MAX; bta_id++)
#else
    for ( ; bta_id <= bta_id_max; bta_id++)
#endif
    {
        if (bta_sys_cb.reg[bta_id] != NULL)
        {
#ifdef REVOLUTION
            if (bta_sys_cb.reg[bta_id]->disable != NULL)
#else
            if (bta_sys_cb.is_reg[bta_id] == TRUE  &&  bta_sys_cb.reg[bta_id]->disable != NULL)
#endif
            {
                (*bta_sys_cb.reg[bta_id]->disable)();
            }
        }
    }
}

/*******************************************************************************
**
** Function         bta_sys_disable_timers
**
** Description      Disable sys timer event handling
**
** Returns          void
**
*******************************************************************************/
void bta_sys_disable_timers(void)
{
    bta_sys_cb.timers_disabled = TRUE;
}

/*******************************************************************************
**
** Function         bta_sys_set_trace_level
**
** Description      Set trace level for BTA
**
** Returns          void
**
*******************************************************************************/
void bta_sys_set_trace_level(UINT8 level)
{
    appl_trace_level = level;
}

#ifndef REVOLUTION
/*******************************************************************************
**
** Function         bta_sys_get_sys_features
**
** Description      Returns sys_features to other BTA modules.
**
** Returns          sys_features
**
*******************************************************************************/
UINT16 bta_sys_get_sys_features (void)
{
    return bta_sys_cb.sys_features;
}
#endif


