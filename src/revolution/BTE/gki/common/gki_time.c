/******************************************************************************
 *
 *  NOTICE OF CHANGES
 *  2024/03/25:
 *      - Modified gki_timers_init to match RVL version
 *      - Modified GKI_start_timer to match RVL version
 *      - Modified GKI_stop_timer to match RVL version
 *      - Modified GKI_add_to_timer_list to match RVL version
 *      - Modified GKI_remove_from_timer_list to match RVL version
 * 
 *  Compile with REVOLUTION defined to include these changes.
 * 
 ******************************************************************************/



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


#include "gki_int.h"

#ifndef BT_ERROR_TRACE_0
#define BT_ERROR_TRACE_0(l,m)
#endif

/* Make sure that this has been defined in target.h */
#ifndef GKI_NUM_TIMERS
#error  NO TIMERS: Must define at least 1 timer in the system!
#endif


#define GKI_NO_NEW_TMRS_STARTED (0x7fffffffL)   /* Largest signed positive timer count */
#define GKI_UNUSED_LIST_ENTRY   (0x80000000L)   /* Marks an unused timer list entry (initial value) */
#define GKI_MAX_INT32           (0x7fffffffL)

/*******************************************************************************
**
** Function         gki_timers_init
**
** Description      This internal function is called once at startup to initialize
**                  all the timer structures.
**
** Returns          void
**
*******************************************************************************/
void gki_timers_init(void)
{
    UINT8   tt;

    gki_cb.com.OSTicksTilExp = 0;       /* Remaining time (of OSTimeCurTimeout) before next timer expires */
    gki_cb.com.OSNumOrigTicks = 0;
#if (defined(GKI_DELAY_STOP_SYS_TICK) && (GKI_DELAY_STOP_SYS_TICK > 0))
    gki_cb.com.OSTicksTilStop = 0;      /* clear inactivity delay timer */
#endif

    for (tt = 0; tt < GKI_MAX_TASKS; tt++)
    {
        gki_cb.com.OSWaitTmr   [tt] = 0;

#if (GKI_NUM_TIMERS > 0)
        gki_cb.com.OSTaskTmr0  [tt] = 0;
        gki_cb.com.OSTaskTmr0R [tt] = 0;
#endif

#if (GKI_NUM_TIMERS > 1)
        gki_cb.com.OSTaskTmr1  [tt] = 0;
        gki_cb.com.OSTaskTmr1R [tt] = 0;
#endif

#if (GKI_NUM_TIMERS > 2)
        gki_cb.com.OSTaskTmr2  [tt] = 0;
        gki_cb.com.OSTaskTmr2R [tt] = 0;
#endif

#if (GKI_NUM_TIMERS > 3)
        gki_cb.com.OSTaskTmr3  [tt] = 0;
        gki_cb.com.OSTaskTmr3R [tt] = 0;
#endif
    }

#ifndef REVOLUTION
    for (tt = 0; tt < GKI_MAX_TIMER_QUEUES; tt++)
    {
        gki_cb.com.timer_queues[tt] = NULL;
    }

    gki_cb.com.p_tick_cb = NULL;
    gki_cb.com.system_tick_running = FALSE;
#endif

    return;
}

/*******************************************************************************
**
** Function         gki_timers_is_timer_running
**
** Description      This internal function is called to test if any gki timer are running
**
**
** Returns          TRUE if at least one time is running in the system, FALSE else.
**
*******************************************************************************/
BOOLEAN gki_timers_is_timer_running(void)
{
    UINT8   tt;
    for (tt = 0; tt < GKI_MAX_TASKS; tt++)
    {

#if (GKI_NUM_TIMERS > 0)
        if(gki_cb.com.OSTaskTmr0  [tt])
        {
            return TRUE;
        }
#endif

#if (GKI_NUM_TIMERS > 1)
        if(gki_cb.com.OSTaskTmr1  [tt] )
        {
            return TRUE;
        }
#endif

#if (GKI_NUM_TIMERS > 2)
        if(gki_cb.com.OSTaskTmr2  [tt] )
        {
            return TRUE;
        }
#endif

#if (GKI_NUM_TIMERS > 3)
        if(gki_cb.com.OSTaskTmr3  [tt] )
        {
            return TRUE;
        }
#endif
    }

    return FALSE;

}

/*******************************************************************************
**
** Function         GKI_get_tick_count
**
** Description      This function returns the current system ticks
**
** Returns          The current number of system ticks
**
*******************************************************************************/
UINT32  GKI_get_tick_count(void)
{
    return gki_cb.com.OSTicks;
}


/*******************************************************************************
**
** Function         GKI_ready_to_sleep
**
** Description      This function returns the number of system ticks until the
**                  next timer will expire.  It is typically called by a power
**                  savings manager to find out how long it can have the system
**                  sleep before it needs to service the next entry.
**
** Parameters:      None
**
** Returns          Number of ticks til the next timer expires
**                  Note: the value is a signed  value.  This value should be
**                      compared to x > 0, to avoid misinterpreting negative tick
**                      values.
**
*******************************************************************************/
INT32    GKI_ready_to_sleep (void)
{
    return (gki_cb.com.OSTicksTilExp);
}


/*******************************************************************************
**
** Function         GKI_start_timer
**
** Description      An application can call this function to start one of
**                  it's four general purpose timers. Any of the four timers
**                  can be 1-shot or continuous. If a timer is already running,
**                  it will be reset to the new parameters.
**
** Parameters       tnum            - (input) timer number to be started (TIMER_0,
**                                              TIMER_1, TIMER_2, or TIMER_3)
**                  ticks           - (input) the number of system ticks til the
**                                              timer expires.
**                  is_continuous   - (input) TRUE if timer restarts automatically,
**                                              else FALSE if it is a 'one-shot'.
**
** Returns          void
**
*******************************************************************************/
void GKI_start_timer (UINT8 tnum, INT32 ticks, BOOLEAN is_continuous)
{
    INT32   reload;
    INT32   orig_ticks;
    UINT8   task_id = GKI_get_taskid();
    BOOLEAN bad_timer = FALSE;

    if (ticks <= 0)
        ticks = 1;

    orig_ticks = ticks;     /* save the ticks in case adjustment is necessary */


    /* If continuous timer, set reload, else set it to 0 */
    if (is_continuous)
        reload = ticks;
    else
        reload = 0;

    GKI_disable();

#ifndef REVOLUTION
    if(gki_timers_is_timer_running() == FALSE)
    {
#if (defined(GKI_DELAY_STOP_SYS_TICK) && (GKI_DELAY_STOP_SYS_TICK > 0))
        /* if inactivity delay timer is not running, start system tick */
        if(gki_cb.com.OSTicksTilStop == 0)
        {
#endif
            if(gki_cb.com.p_tick_cb)
            {
                /* start system tick */
                gki_cb.com.system_tick_running = TRUE;
                (gki_cb.com.p_tick_cb) (TRUE);
            }
#if (defined(GKI_DELAY_STOP_SYS_TICK) && (GKI_DELAY_STOP_SYS_TICK > 0))
        }
        else
        {
            /* clear inactivity delay timer */
            gki_cb.com.OSTicksTilStop = 0;
        }
#endif
    }
#endif

    /* Add the time since the last task timer update.
    ** Note that this works when no timers are active since
    ** both OSNumOrigTicks and OSTicksTilExp are 0.
    */
    if (GKI_MAX_INT32 - (gki_cb.com.OSNumOrigTicks - gki_cb.com.OSTicksTilExp) > ticks)
    {
        ticks += gki_cb.com.OSNumOrigTicks - gki_cb.com.OSTicksTilExp;
    }
    else
        ticks = GKI_MAX_INT32;

    switch (tnum)
    {
#if (GKI_NUM_TIMERS > 0)
        case TIMER_0:
            gki_cb.com.OSTaskTmr0R[task_id] = reload;
            gki_cb.com.OSTaskTmr0 [task_id] = ticks;
            break;
#endif

#if (GKI_NUM_TIMERS > 1)
        case TIMER_1:
            gki_cb.com.OSTaskTmr1R[task_id] = reload;
            gki_cb.com.OSTaskTmr1 [task_id] = ticks;
            break;
#endif

#if (GKI_NUM_TIMERS > 2)
        case TIMER_2:
            gki_cb.com.OSTaskTmr2R[task_id] = reload;
            gki_cb.com.OSTaskTmr2 [task_id] = ticks;
            break;
#endif

#if (GKI_NUM_TIMERS > 3)
        case TIMER_3:
            gki_cb.com.OSTaskTmr3R[task_id] = reload;
            gki_cb.com.OSTaskTmr3 [task_id] = ticks;
            break;
#endif
        default:
            bad_timer = TRUE;       /* Timer number is bad, so do not use */
    }

    /* Update the expiration timeout if a legitimate timer */
    if (!bad_timer)
    {
        /* Only update the timeout value if it is less than any other newly started timers */
        gki_adjust_timer_count (orig_ticks);
    }

    GKI_enable();

}

/*******************************************************************************
**
** Function         GKI_stop_timer
**
** Description      An application can call this function to stop one of
**                  it's four general purpose timers. There is no harm in
**                  stopping a timer that is already stopped.
**
** Parameters       tnum            - (input) timer number to be started (TIMER_0,
**                                              TIMER_1, TIMER_2, or TIMER_3)
** Returns          void
**
*******************************************************************************/
void GKI_stop_timer (UINT8 tnum)
{
    UINT8  task_id = GKI_get_taskid();

    switch (tnum)
    {
#if (GKI_NUM_TIMERS > 0)
        case TIMER_0:
            gki_cb.com.OSTaskTmr0R[task_id] = 0;
            gki_cb.com.OSTaskTmr0 [task_id] = 0;
            break;
#endif

#if (GKI_NUM_TIMERS > 1)
        case TIMER_1:
            gki_cb.com.OSTaskTmr1R[task_id] = 0;
            gki_cb.com.OSTaskTmr1 [task_id] = 0;
            break;
#endif

#if (GKI_NUM_TIMERS > 2)
        case TIMER_2:
            gki_cb.com.OSTaskTmr2R[task_id] = 0;
            gki_cb.com.OSTaskTmr2 [task_id] = 0;
            break;
#endif

#if (GKI_NUM_TIMERS > 3)
        case TIMER_3:
            gki_cb.com.OSTaskTmr3R[task_id] = 0;
            gki_cb.com.OSTaskTmr3 [task_id] = 0;
            break;
#endif
    }

#ifndef REVOLUTION
    GKI_disable();

    if (gki_timers_is_timer_running() == FALSE)
    {
        if (gki_cb.com.p_tick_cb)
        {
#if (defined(GKI_DELAY_STOP_SYS_TICK) && (GKI_DELAY_STOP_SYS_TICK > 0))
            /* if inactivity delay timer is not running */
            if ((gki_cb.com.system_tick_running)&&(gki_cb.com.OSTicksTilStop == 0))
            {
                /* set inactivity delay timer */
                /* when timer expires, system tick will be stopped */
                gki_cb.com.OSTicksTilStop = GKI_DELAY_STOP_SYS_TICK;
            }
#else
            gki_cb.com.system_tick_running = FALSE;
            gki_cb.com.p_tick_cb(FALSE); /* stop system tick */
#endif
        }
    }

    GKI_enable();
#endif


}


/*******************************************************************************
**
** Function         GKI_timer_update
**
** Description      This function is called by an OS to drive the GKI's timers.
**                  It is typically called at every system tick to
**                  update the timers for all tasks, and check for timeouts.
**
**                  Note: It has been designed to also allow for variable tick updates
**                      so that systems with strict power savings requirements can
**                      have the update occur at variable intervals.
**
** Parameters:      ticks_since_last_update - (input) This is the number of TICKS that have
**                          occurred since the last time GKI_timer_update was called.
**
** Returns          void
**
*******************************************************************************/
void GKI_timer_update (INT32 ticks_since_last_update)
{
    UINT8   task_id;
    long    next_expiration;        /* Holds the next soonest expiration time after this update */

    /* Increment the number of ticks used for time stamps */
    gki_cb.com.OSTicks += ticks_since_last_update;

    /* If any timers are running in any tasks, decrement the remaining time til
     * the timer updates need to take place (next expiration occurs)
     */
    gki_cb.com.OSTicksTilExp -= ticks_since_last_update;

    /* Don't allow timer interrupt nesting */
    if (gki_cb.com.timer_nesting)
        return;

    gki_cb.com.timer_nesting = 1;

#if (defined(GKI_DELAY_STOP_SYS_TICK) && (GKI_DELAY_STOP_SYS_TICK > 0))
    /* if inactivity delay timer is set and expired */
    if (gki_cb.com.OSTicksTilStop)
    {
        if( gki_cb.com.OSTicksTilStop <= (UINT32)ticks_since_last_update )
        {
            if(gki_cb.com.p_tick_cb)
            {
                gki_cb.com.system_tick_running = FALSE;
                (gki_cb.com.p_tick_cb) (FALSE); /* stop system tick */
            }
            gki_cb.com.OSTicksTilStop = 0;      /* clear inactivity delay timer */
            gki_cb.com.timer_nesting = 0;
            return;
        }
        else
            gki_cb.com.OSTicksTilStop -= ticks_since_last_update;
    }
#endif

    /* No need to update the ticks if no timeout has occurred */
    if (gki_cb.com.OSTicksTilExp > 0)
    {
        gki_cb.com.timer_nesting = 0;
        return;
    }

    next_expiration = GKI_NO_NEW_TMRS_STARTED;

    /* If here then gki_cb.com.OSTicksTilExp <= 0. If negative, then increase gki_cb.com.OSNumOrigTicks
       to account for the difference so timer updates below are decremented by the full number
       of ticks. gki_cb.com.OSNumOrigTicks is reset at the bottom of this function so changing this
       value only affects the timer updates below
     */
    gki_cb.com.OSNumOrigTicks -= gki_cb.com.OSTicksTilExp;

#if GKI_TIMER_LIST_NOPREEMPT == TRUE
    /* Protect this section because if a GKI_timer_stop happens between:
     *   - gki_cb.com.OSTaskTmr0[task_id] -= gki_cb.com.OSNumOrigTicks;
     *   - gki_cb.com.OSTaskTmr0[task_id] = gki_cb.com.OSTaskTmr0R[task_id];
     * then the timer may appear stopped while it is about to be reloaded.
     * Note: Not needed if this function cannot be preempted (typical).
     */
    GKI_disable();
#endif

    /* Check for OS Task Timers */
    for (task_id = 0; task_id < GKI_MAX_TASKS; task_id++)
    {
        if (gki_cb.com.OSWaitTmr[task_id] > 0) /* If timer is running */
        {
            gki_cb.com.OSWaitTmr[task_id] -= gki_cb.com.OSNumOrigTicks;
            if (gki_cb.com.OSWaitTmr[task_id] <= 0)
            {
                /* Timer Expired */
                gki_cb.com.OSRdyTbl[task_id] = TASK_READY;
            }
        }

#if (GKI_NUM_TIMERS > 0)
         /* If any timer is running, decrement */
        if (gki_cb.com.OSTaskTmr0[task_id] > 0)
        {
            gki_cb.com.OSTaskTmr0[task_id] -= gki_cb.com.OSNumOrigTicks;

            if (gki_cb.com.OSTaskTmr0[task_id] <= 0)
            {
                /* Reload timer and set Timer 0 Expired event mask */
                gki_cb.com.OSTaskTmr0[task_id] = gki_cb.com.OSTaskTmr0R[task_id];

#if (defined(GKI_TIMER_UPDATES_FROM_ISR) &&  GKI_TIMER_UPDATES_FROM_ISR == TRUE)
                GKI_isend_event (task_id, TIMER_0_EVT_MASK);
#else
                GKI_send_event (task_id, TIMER_0_EVT_MASK);
#endif
            }
        }

        /* Check to see if this timer is the next one to expire */
        if (gki_cb.com.OSTaskTmr0[task_id] > 0 && gki_cb.com.OSTaskTmr0[task_id] < next_expiration)
            next_expiration = gki_cb.com.OSTaskTmr0[task_id];
#endif

#if (GKI_NUM_TIMERS > 1)
         /* If any timer is running, decrement */
        if (gki_cb.com.OSTaskTmr1[task_id] > 0)
        {
            gki_cb.com.OSTaskTmr1[task_id] -= gki_cb.com.OSNumOrigTicks;

            if (gki_cb.com.OSTaskTmr1[task_id] <= 0)
            {
                /* Reload timer and set Timer 1 Expired event mask */
                gki_cb.com.OSTaskTmr1[task_id] = gki_cb.com.OSTaskTmr1R[task_id];

#if (defined(GKI_TIMER_UPDATES_FROM_ISR) &&  GKI_TIMER_UPDATES_FROM_ISR == TRUE)
                GKI_isend_event (task_id, TIMER_1_EVT_MASK);
#else
                GKI_send_event (task_id, TIMER_1_EVT_MASK);
#endif
            }
        }

        /* Check to see if this timer is the next one to expire */
        if (gki_cb.com.OSTaskTmr1[task_id] > 0 && gki_cb.com.OSTaskTmr1[task_id] < next_expiration)
            next_expiration = gki_cb.com.OSTaskTmr1[task_id];
#endif

#if (GKI_NUM_TIMERS > 2)
         /* If any timer is running, decrement */
        if (gki_cb.com.OSTaskTmr2[task_id] > 0)
        {
            gki_cb.com.OSTaskTmr2[task_id] -= gki_cb.com.OSNumOrigTicks;

            if (gki_cb.com.OSTaskTmr2[task_id] <= 0)
            {
                /* Reload timer and set Timer 2 Expired event mask */
                gki_cb.com.OSTaskTmr2[task_id] = gki_cb.com.OSTaskTmr2R[task_id];

#if (defined(GKI_TIMER_UPDATES_FROM_ISR) &&  GKI_TIMER_UPDATES_FROM_ISR == TRUE)
                GKI_isend_event (task_id, TIMER_2_EVT_MASK);
#else
                GKI_send_event (task_id, TIMER_2_EVT_MASK);
#endif
            }
        }

        /* Check to see if this timer is the next one to expire */
        if (gki_cb.com.OSTaskTmr2[task_id] > 0 && gki_cb.com.OSTaskTmr2[task_id] < next_expiration)
            next_expiration = gki_cb.com.OSTaskTmr2[task_id];
#endif

#if (GKI_NUM_TIMERS > 3)
         /* If any timer is running, decrement */
        if (gki_cb.com.OSTaskTmr3[task_id] > 0)
        {
            gki_cb.com.OSTaskTmr3[task_id] -= gki_cb.com.OSNumOrigTicks;

            if (gki_cb.com.OSTaskTmr3[task_id] <= 0)
            {
                /* Reload timer and set Timer 3 Expired event mask */
                gki_cb.com.OSTaskTmr3[task_id] = gki_cb.com.OSTaskTmr3R[task_id];

#if (defined(GKI_TIMER_UPDATES_FROM_ISR) &&  GKI_TIMER_UPDATES_FROM_ISR == TRUE)
                GKI_isend_event (task_id, TIMER_3_EVT_MASK);
#else
                GKI_send_event (task_id, TIMER_3_EVT_MASK);
#endif
            }
        }

        /* Check to see if this timer is the next one to expire */
        if (gki_cb.com.OSTaskTmr3[task_id] > 0 && gki_cb.com.OSTaskTmr3[task_id] < next_expiration)
            next_expiration = gki_cb.com.OSTaskTmr3[task_id];
#endif

    }

#if GKI_TIMER_LIST_NOPREEMPT == TRUE
    /* End the critical section */
    GKI_enable();
#endif

    /* Set the next timer experation value if there is one to start */
    if (next_expiration < GKI_NO_NEW_TMRS_STARTED)
    {
        gki_cb.com.OSTicksTilExp = gki_cb.com.OSNumOrigTicks = next_expiration;
    }
    else
    {
        gki_cb.com.OSTicksTilExp = gki_cb.com.OSNumOrigTicks = 0;
    }

    gki_cb.com.timer_nesting = 0;

    return;
}


#ifndef REVOLUTION

/*******************************************************************************
**
** Function         GKI_timer_queue_empty
**
** Description      This function is called by applications to see whether the timer
**                  queue is empty
**
** Parameters
**
** Returns          BOOLEAN
**
*******************************************************************************/
BOOLEAN GKI_timer_queue_empty (void)
{
    UINT8 tt;

    for (tt = 0; tt < GKI_MAX_TIMER_QUEUES; tt++)
    {
        if (gki_cb.com.timer_queues[tt])
            return FALSE;
    }

    return TRUE;
}

/*******************************************************************************
**
** Function         GKI_timer_queue_register_callback
**
** Description      This function is called by applications to register system tick
**                  start/stop callback for time queues
**
**
** Parameters       p_callback - (input) pointer to the system tick callback
**
** Returns          BOOLEAN
**
*******************************************************************************/
void GKI_timer_queue_register_callback (SYSTEM_TICK_CBACK *p_callback)
{
    gki_cb.com.p_tick_cb = p_callback;

    return;
}

#endif

/*******************************************************************************
**
** Function         GKI_init_timer_list
**
** Description      This function is called by applications when they
**                  want to initialize a timer list.
**
** Parameters       p_timer_listq   - (input) pointer to the timer list queue object
**
** Returns          void
**
*******************************************************************************/
void GKI_init_timer_list (TIMER_LIST_Q *p_timer_listq)
{
    p_timer_listq->p_first    = NULL;
    p_timer_listq->p_last     = NULL;
    p_timer_listq->last_ticks = 0;

    return;
}

/*******************************************************************************
**
** Function         GKI_init_timer_list_entry
**
** Description      This function is called by the applications when they
**                  want to initialize a timer list entry. This must be
**                  done prior to first use of the entry.
**
** Parameters       p_tle           - (input) pointer to a timer list queue entry
**
** Returns          void
**
*******************************************************************************/
void GKI_init_timer_list_entry (TIMER_LIST_ENT  *p_tle)
{
    p_tle->p_next  = NULL;
    p_tle->p_prev  = NULL;
    p_tle->ticks   = GKI_UNUSED_LIST_ENTRY;
    p_tle->in_use  = FALSE;
}


/*******************************************************************************
**
** Function         GKI_update_timer_list
**
** Description      This function is called by the applications when they
**                  want to update a timer list. This should be at every
**                  timer list unit tick, e.g. once per sec, once per minute etc.
**
** Parameters       p_timer_listq   - (input) pointer to the timer list queue object
**                  num_units_since_last_update - (input) number of units since the last update
**                                  (allows for variable unit update)
**
**      NOTE: The following timer list update routines should not be used for exact time
**            critical purposes.  The timer tasks should be used when exact timing is needed.
**
** Returns          the number of timers that have expired
**
*******************************************************************************/
UINT16 GKI_update_timer_list (TIMER_LIST_Q *p_timer_listq, INT32 num_units_since_last_update)
{
    TIMER_LIST_ENT  *p_tle;
    UINT16           num_time_out = 0;
    INT32            rem_ticks;
    INT32            temp_ticks;

    p_tle = p_timer_listq->p_first;

    /* First, get the guys who have previously timed out */
    /* Note that the tick value of the timers should always be '0' */
    while ((p_tle) && (p_tle->ticks <= 0))
    {
        num_time_out++;
        p_tle = p_tle->p_next;
    }

    /* Timer entriy tick values are relative to the preceeding entry */
    rem_ticks = num_units_since_last_update;

    /* Now, adjust remaining timer entries */
    while ((p_tle != NULL) && (rem_ticks > 0))
    {
        temp_ticks = p_tle->ticks;
        p_tle->ticks -= rem_ticks;

        /* See if this timer has just timed out */
        if (p_tle->ticks <= 0)
        {
            /* We set the number of ticks to '0' so that the legacy code
             * that assumes a '0' or nonzero value will still work as coded. */
            p_tle->ticks = 0;

            num_time_out++;
        }

        rem_ticks -= temp_ticks;  /* Decrement the remaining ticks to process */
        p_tle = p_tle->p_next;
    }

    if (p_timer_listq->last_ticks > 0)
    {
        p_timer_listq->last_ticks -= num_units_since_last_update;

        /* If the last timer has expired set last_ticks to 0 so that other list update
        * functions will calculate correctly
        */
        if (p_timer_listq->last_ticks < 0)
            p_timer_listq->last_ticks = 0;
    }

    return (num_time_out);
}

/*******************************************************************************
**
** Function         GKI_get_remaining_ticks
**
** Description      This function is called by an application to get remaining
**                  ticks to expire
**
** Parameters       p_timer_listq   - (input) pointer to the timer list queue object
**                  p_target_tle    - (input) pointer to a timer list queue entry
**
** Returns          0 if timer is not used or timer is not in the list
**                  remaining ticks if success
**
*******************************************************************************/
UINT32 GKI_get_remaining_ticks (TIMER_LIST_Q *p_timer_listq, TIMER_LIST_ENT  *p_target_tle)
{
    TIMER_LIST_ENT  *p_tle;
    UINT32           rem_ticks = 0;

    if (p_target_tle->in_use)
    {
        p_tle = p_timer_listq->p_first;

        /* adding up all of ticks in previous entries */
        while ((p_tle)&&(p_tle != p_target_tle))
        {
            rem_ticks += p_tle->ticks;
            p_tle = p_tle->p_next;
        }

        /* if found target entry */
        if (p_tle == p_target_tle)
        {
            rem_ticks += p_tle->ticks;
        }
        else
        {
            BT_ERROR_TRACE_0(TRACE_LAYER_GKI, "GKI_get_remaining_ticks: No timer entry in the list");
            return(0);
        }
    }
    else
    {
        BT_ERROR_TRACE_0(TRACE_LAYER_GKI, "GKI_get_remaining_ticks: timer entry is not active");
    }

    return (rem_ticks);
}

/*******************************************************************************
**
** Function         GKI_add_to_timer_list
**
** Description      This function is called by an application to add a timer
**                  entry to a timer list.
**
**                  Note: A timer value of '0' will effectively insert an already
**                      expired event.  Negative tick values will be ignored.
**
** Parameters       p_timer_listq   - (input) pointer to the timer list queue object
**                  p_tle           - (input) pointer to a timer list queue entry
**
** Returns          void
**
*******************************************************************************/
void GKI_add_to_timer_list (TIMER_LIST_Q *p_timer_listq, TIMER_LIST_ENT  *p_tle)
{
    UINT32           nr_ticks_total;
    UINT8 tt;
    TIMER_LIST_ENT  *p_temp;

    /* Only process valid tick values */
    if (p_tle->ticks >= 0)
    {
        /* If this entry is the last in the list */
        if (p_tle->ticks >= p_timer_listq->last_ticks)
        {
            /* If this entry is the only entry in the list */
            if (p_timer_listq->p_first == NULL)
                p_timer_listq->p_first = p_tle;
            else
            {
                /* Insert the entry onto the end of the list */
                if (p_timer_listq->p_last != NULL)
                    p_timer_listq->p_last->p_next = p_tle;

                p_tle->p_prev = p_timer_listq->p_last;
            }

            p_tle->p_next = NULL;
            p_timer_listq->p_last = p_tle;
            nr_ticks_total = p_tle->ticks;
            p_tle->ticks -= p_timer_listq->last_ticks;

            p_timer_listq->last_ticks = nr_ticks_total;
        }
        else    /* This entry needs to be inserted before the last entry */
        {
            /* Find the entry that the new one needs to be inserted in front of */
            p_temp = p_timer_listq->p_first;
            while (p_tle->ticks > p_temp->ticks)
            {
                /* Update the tick value if looking at an unexpired entry */
                if (p_temp->ticks > 0)
                    p_tle->ticks -= p_temp->ticks;

                p_temp = p_temp->p_next;
            }

            /* The new entry is the first in the list */
            if (p_temp == p_timer_listq->p_first)
            {
                p_tle->p_next = p_timer_listq->p_first;
                p_timer_listq->p_first->p_prev = p_tle;
                p_timer_listq->p_first = p_tle;
            }
            else
            {
                p_temp->p_prev->p_next = p_tle;
                p_tle->p_prev = p_temp->p_prev;
                p_temp->p_prev = p_tle;
                p_tle->p_next = p_temp;
            }
            p_temp->ticks -= p_tle->ticks;
        }

        p_tle->in_use = TRUE;

#ifndef REVOLUTION
        /* if we already add this timer queue to the array */
        for (tt = 0; tt < GKI_MAX_TIMER_QUEUES; tt++)
        {
             if (gki_cb.com.timer_queues[tt] == p_timer_listq)
                 return;
        }
        /* add this timer queue to the array */
        for (tt = 0; tt < GKI_MAX_TIMER_QUEUES; tt++)
        {
             if (gki_cb.com.timer_queues[tt] == NULL)
                 break;
        }
        if (tt < GKI_MAX_TIMER_QUEUES)
        {
            gki_cb.com.timer_queues[tt] = p_timer_listq;
        }
#endif
    }

    return;
}


/*******************************************************************************
**
** Function         GKI_remove_from_timer_list
**
** Description      This function is called by an application to remove a timer
**                  entry from a timer list.
**
** Parameters       p_timer_listq   - (input) pointer to the timer list queue object
**                  p_tle           - (input) pointer to a timer list queue entry
**
** Returns          void
**
*******************************************************************************/
void GKI_remove_from_timer_list (TIMER_LIST_Q *p_timer_listq, TIMER_LIST_ENT  *p_tle)
{
    UINT8 tt;

    /* Verify that the entry is valid */
    if (p_tle == NULL || p_tle->in_use == FALSE || p_timer_listq->p_first == NULL)
    {
        return;
    }

    /* Add the ticks remaining in this timer (if any) to the next guy in the list.
    ** Note: Expired timers have a tick value of '0'.
    */
    if (p_tle->p_next != NULL)
    {
        p_tle->p_next->ticks += p_tle->ticks;
    }
    else
    {
        p_timer_listq->last_ticks -= p_tle->ticks;
    }

    /* Unlink timer from the list.
    */
    if (p_timer_listq->p_first == p_tle)
    {
        p_timer_listq->p_first = p_tle->p_next;

        if (p_timer_listq->p_first != NULL)
            p_timer_listq->p_first->p_prev = NULL;

        if (p_timer_listq->p_last == p_tle)
            p_timer_listq->p_last = NULL;
    }
    else
    {
        if (p_timer_listq->p_last == p_tle)
        {
            p_timer_listq->p_last = p_tle->p_prev;

            if (p_timer_listq->p_last != NULL)
                p_timer_listq->p_last->p_next = NULL;
        }
        else
        {
            if (p_tle->p_next != NULL && p_tle->p_next->p_prev == p_tle)
                p_tle->p_next->p_prev = p_tle->p_prev;
            else
            {
                /* Error case - chain messed up ?? */
                return;
            }

            if (p_tle->p_prev != NULL && p_tle->p_prev->p_next == p_tle)
                p_tle->p_prev->p_next = p_tle->p_next;
            else
            {
                /* Error case - chain messed up ?? */
                return;
            }
        }
    }

    p_tle->p_next = p_tle->p_prev = NULL;
    p_tle->ticks = GKI_UNUSED_LIST_ENTRY;
    p_tle->in_use = FALSE;

#ifndef REVOLUTION
    /* if timer queue is empty */
    if (p_timer_listq->p_first == NULL && p_timer_listq->p_last == NULL)
    {
        for (tt = 0; tt < GKI_MAX_TIMER_QUEUES; tt++)
        {
            if (gki_cb.com.timer_queues[tt] == p_timer_listq)
            {
                gki_cb.com.timer_queues[tt] = NULL;
                break;
            }
        }
    }
#endif

    return;
}


/*******************************************************************************
**
** Function         gki_adjust_timer_count
**
** Description      This function is called whenever a new timer or GKI_wait occurs
**                  to adjust (if necessary) the current time til the first expiration.
**                  This only needs to make an adjustment if the new timer (in ticks) is
**                  less than the number of ticks remaining on the current timer.
**
** Parameters:      ticks - (input) number of system ticks of the new timer entry
**
**                  NOTE:  This routine MUST be called while interrupts are disabled to
**                          avoid updates while adjusting the timer variables.
**
** Returns          void
**
*******************************************************************************/
void gki_adjust_timer_count (INT32 ticks)
{
    if (ticks > 0)
    {
        /* See if the new timer expires before the current first expiration */
        if (gki_cb.com.OSNumOrigTicks == 0 || (ticks < gki_cb.com.OSTicksTilExp && gki_cb.com.OSTicksTilExp > 0))
        {
            gki_cb.com.OSNumOrigTicks = (gki_cb.com.OSNumOrigTicks - gki_cb.com.OSTicksTilExp) + ticks;
            gki_cb.com.OSTicksTilExp = ticks;
        }
    }

    return;
}
