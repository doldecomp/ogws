/******************************************************************************
 *
 *  NOTICE OF CHANGES
 *  2024/03/25:
 *      - Move from ulinux/ to platform/
 * 
 ******************************************************************************/



/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Broadcom Corporation
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

/****************************************************************************
**
**  Name        gki_linux_pthreads.c
**
**  Function    pthreads version of Linux GKI. This version is used for
**              settop projects that already use pthreads and not pth.
**
*****************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/times.h>

#include <pthread.h>  /* must be 1st header defined  */
#include <time.h>
#include "gki_int.h"
#include "bt_utils.h"

#define LOG_TAG "GKI_LINUX"

#include <utils/Log.h>

/*****************************************************************************
**  Constants & Macros
******************************************************************************/

#ifndef GKI_TICK_TIMER_DEBUG
#define GKI_TICK_TIMER_DEBUG FALSE
#endif

#define GKI_INFO(fmt, ...) ALOGI ("%s: " fmt, __FUNCTION__, ## __VA_ARGS__)

/* always log errors */
#define GKI_ERROR_LOG(fmt, ...)  ALOGE ("##### ERROR : %s: " fmt "#####", __FUNCTION__, ## __VA_ARGS__)

#if defined (GKI_TICK_TIMER_DEBUG) && (GKI_TICK_TIMER_DEBUG == TRUE)
#define GKI_TIMER_TRACE(fmt, ...) ALOGI ("%s: " fmt, __FUNCTION__, ## __VA_ARGS__)
#else
#define GKI_TIMER_TRACE(fmt, ...)
#endif


#define SCHED_NORMAL 0
#define SCHED_FIFO 1
#define SCHED_RR 2
#define SCHED_BATCH 3

#define NANOSEC_PER_MILLISEC (1000000)
#define NSEC_PER_SEC (1000*NANOSEC_PER_MILLISEC)

/* works only for 1ms to 1000ms heart beat ranges */
#define LINUX_SEC (1000/TICKS_PER_SEC)

#define LOCK(m)  pthread_mutex_lock(&m)
#define UNLOCK(m) pthread_mutex_unlock(&m)
#define INIT(m) pthread_mutex_init(&m, NULL)

#define WAKE_LOCK_ID "brcm_btld"
#define PARTIAL_WAKE_LOCK 1

#if GKI_DYNAMIC_MEMORY == FALSE
tGKI_CB   gki_cb;
#endif

#ifdef NO_GKI_RUN_RETURN
static pthread_t            timer_thread_id = 0;
static int                  shutdown_timer = 0;
#endif

#ifndef GKI_SHUTDOWN_EVT
#define GKI_SHUTDOWN_EVT    APPL_EVT_7
#endif

#define  __likely(cond)    __builtin_expect(!!(cond), 1)
#define  __unlikely(cond)  __builtin_expect(!!(cond), 0)

/*****************************************************************************
**  Local type definitions
******************************************************************************/

#define pthread_cond_timedwait_monotonic pthread_cond_timedwait

typedef struct
{
    UINT8 task_id;          /* GKI task id */
    TASKPTR task_entry;     /* Task entry function*/
    UINT32 params;          /* Extra params to pass to task entry function */
} gki_pthread_info_t;


/*****************************************************************************
**  Static variables
******************************************************************************/

int g_GkiTimerWakeLockOn = 0;
gki_pthread_info_t gki_pthread_info[GKI_MAX_TASKS];

/*****************************************************************************
**  Static functions
******************************************************************************/

/*****************************************************************************
**  Externs
******************************************************************************/

extern int acquire_wake_lock(int lock, const char* id);
extern int release_wake_lock(const char* id);

/*****************************************************************************
**  Functions
******************************************************************************/


/*****************************************************************************
**
** Function        gki_task_entry
**
** Description     GKI pthread callback
**
** Returns         void
**
*******************************************************************************/

void gki_task_entry(UINT32 params)
{
    gki_pthread_info_t *p_pthread_info = (gki_pthread_info_t *)params;
    gki_cb.os.thread_id[p_pthread_info->task_id] = pthread_self();

    prctl(PR_SET_NAME, (unsigned long)gki_cb.com.OSTName[p_pthread_info->task_id], 0, 0, 0);

    GKI_INFO("gki_task_entry task_id=%i [%s] starting\n", p_pthread_info->task_id,
                gki_cb.com.OSTName[p_pthread_info->task_id]);

    /* Call the actual thread entry point */
    (p_pthread_info->task_entry)(p_pthread_info->params);

    GKI_INFO("gki_task task_id=%i [%s] terminating\n", p_pthread_info->task_id,
                gki_cb.com.OSTName[p_pthread_info->task_id]);

    pthread_exit(0);    /* GKI tasks have no return value */
}
/* end android */

/*******************************************************************************
**
** Function         GKI_init
**
** Description      This function is called once at startup to initialize
**                  all the timer structures.
**
** Returns          void
**
*******************************************************************************/

void GKI_init(void)
{
    pthread_mutexattr_t attr;
    tGKI_OS             *p_os;

    memset (&gki_cb, 0, sizeof (gki_cb));

    gki_buffer_init();
    gki_timers_init();
    gki_cb.com.OSTicks = (UINT32) times(0);

    pthread_mutexattr_init(&attr);

#ifndef __CYGWIN__
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
#endif
    p_os = &gki_cb.os;
    pthread_mutex_init(&p_os->GKI_mutex, &attr);
    /* pthread_mutex_init(&GKI_sched_mutex, NULL); */
#if (GKI_DEBUG == TRUE)
    pthread_mutex_init(&p_os->GKI_trace_mutex, NULL);
#endif
    /* pthread_mutex_init(&thread_delay_mutex, NULL); */  /* used in GKI_delay */
    /* pthread_cond_init (&thread_delay_cond, NULL); */

    /* Initialiase GKI_timer_update suspend variables & mutexes to be in running state.
     * this works too even if GKI_NO_TICK_STOP is defined in btld.txt */
    p_os->no_timer_suspend = GKI_TIMER_TICK_RUN_COND;
    pthread_mutex_init(&p_os->gki_timer_mutex, NULL);
#ifndef NO_GKI_RUN_RETURN
    pthread_cond_init(&p_os->gki_timer_cond, NULL);
#endif
}


/*******************************************************************************
**
** Function         GKI_get_os_tick_count
**
** Description      This function is called to retrieve the native OS system tick.
**
** Returns          Tick count of native OS.
**
*******************************************************************************/
UINT32 GKI_get_os_tick_count(void)
{
     /* TODO - add any OS specific code here */
    return (gki_cb.com.OSTicks);
}

/*******************************************************************************
**
** Function         GKI_create_task
**
** Description      This function is called to create a new OSS task.
**
** Parameters:      task_entry  - (input) pointer to the entry function of the task
**                  task_id     - (input) Task id is mapped to priority
**                  taskname    - (input) name given to the task
**                  stack       - (input) pointer to the top of the stack (highest memory location)
**                  stacksize   - (input) size of the stack allocated for the task
**
** Returns          GKI_SUCCESS if all OK, GKI_FAILURE if any problem
**
** NOTE             This function take some parameters that may not be needed
**                  by your particular OS. They are here for compatability
**                  of the function prototype.
**
*******************************************************************************/
UINT8 GKI_create_task (TASKPTR task_entry, UINT8 task_id, INT8 *taskname, UINT16 *stack, UINT16 stacksize)
{
    UINT16  i;
    UINT8   *p;
    struct sched_param param;
    int policy, ret = 0;
    pthread_attr_t attr1;

    GKI_TRACE( "GKI_create_task %x %d %s %x %d", (int)task_entry, (int)task_id,
            (char*) taskname, (int) stack, (int)stacksize);

    if (task_id >= GKI_MAX_TASKS)
    {
        GKI_ERROR_LOG("Error! task ID > max task allowed");
        return (GKI_FAILURE);
    }


    gki_cb.com.OSRdyTbl[task_id]    = TASK_READY;
    gki_cb.com.OSTName[task_id]     = taskname;
    gki_cb.com.OSWaitTmr[task_id]   = 0;
    gki_cb.com.OSWaitEvt[task_id]   = 0;

    /* Initialize mutex and condition variable objects for events and timeouts */
    pthread_mutex_init(&gki_cb.os.thread_evt_mutex[task_id], NULL);
    pthread_cond_init (&gki_cb.os.thread_evt_cond[task_id], NULL);
    pthread_mutex_init(&gki_cb.os.thread_timeout_mutex[task_id], NULL);
    pthread_cond_init (&gki_cb.os.thread_timeout_cond[task_id], NULL);

    pthread_attr_init(&attr1);
    /* by default, pthread creates a joinable thread */
#if ( FALSE == GKI_PTHREAD_JOINABLE )
    pthread_attr_setdetachstate(&attr1, PTHREAD_CREATE_DETACHED);

    GKI_TRACE("GKI creating task %i\n", task_id);
#else
    GKI_TRACE("GKI creating JOINABLE task %i\n", task_id);
#endif

    /* On Android, the new tasks starts running before 'gki_cb.os.thread_id[task_id]' is initialized */
    /* Pass task_id to new task so it can initialize gki_cb.os.thread_id[task_id] for it calls GKI_wait */
    gki_pthread_info[task_id].task_id = task_id;
    gki_pthread_info[task_id].task_entry = task_entry;
    gki_pthread_info[task_id].params = 0;

    ret = pthread_create( &gki_cb.os.thread_id[task_id],
              &attr1,
              (void *)gki_task_entry,
              &gki_pthread_info[task_id]);

    if (ret != 0)
    {
         GKI_ERROR_LOG("pthread_create failed(%d), %s!\n\r", ret, taskname);
         return GKI_FAILURE;
    }

    if(pthread_getschedparam(gki_cb.os.thread_id[task_id], &policy, &param)==0)
     {
#if (GKI_LINUX_BASE_POLICY!=GKI_SCHED_NORMAL)
#if defined(PBS_SQL_TASK)
         if (task_id == PBS_SQL_TASK)
         {
             GKI_TRACE("PBS SQL lowest priority task");
             policy = SCHED_NORMAL;
         }
         else
#endif
#endif
         {
             /* check if define in gki_int.h is correct for this compile environment! */
             policy = GKI_LINUX_BASE_POLICY;
#if (GKI_LINUX_BASE_POLICY!=GKI_SCHED_NORMAL)
             param.sched_priority = GKI_LINUX_BASE_PRIORITY - task_id - 2;
#endif
         }
         pthread_setschedparam(gki_cb.os.thread_id[task_id], policy, &param);
     }

    GKI_TRACE( "Leaving GKI_create_task %x %d %x %s %x %d\n",
              (int)task_entry,
              (int)task_id,
              (int)gki_cb.os.thread_id[task_id],
              (char*)taskname,
              (int)stack,
              (int)stacksize);

    return (GKI_SUCCESS);
}

void GKI_destroy_task(UINT8 task_id)
{
#if ( FALSE == GKI_PTHREAD_JOINABLE )
        int i = 0;
#else
        int result;
#endif
    if (gki_cb.com.OSRdyTbl[task_id] != TASK_DEAD)
    {
        gki_cb.com.OSRdyTbl[task_id] = TASK_DEAD;

        /* paranoi settings, make sure that we do not execute any mailbox events */
        gki_cb.com.OSWaitEvt[task_id] &= ~(TASK_MBOX_0_EVT_MASK|TASK_MBOX_1_EVT_MASK|
                                            TASK_MBOX_2_EVT_MASK|TASK_MBOX_3_EVT_MASK);

#if (GKI_NUM_TIMERS > 0)
        gki_cb.com.OSTaskTmr0R[task_id] = 0;
        gki_cb.com.OSTaskTmr0 [task_id] = 0;
#endif

#if (GKI_NUM_TIMERS > 1)
        gki_cb.com.OSTaskTmr1R[task_id] = 0;
        gki_cb.com.OSTaskTmr1 [task_id] = 0;
#endif

#if (GKI_NUM_TIMERS > 2)
        gki_cb.com.OSTaskTmr2R[task_id] = 0;
        gki_cb.com.OSTaskTmr2 [task_id] = 0;
#endif

#if (GKI_NUM_TIMERS > 3)
        gki_cb.com.OSTaskTmr3R[task_id] = 0;
        gki_cb.com.OSTaskTmr3 [task_id] = 0;
#endif

        GKI_send_event(task_id, EVENT_MASK(GKI_SHUTDOWN_EVT));

#if ( FALSE == GKI_PTHREAD_JOINABLE )
        i = 0;

        while ((gki_cb.com.OSWaitEvt[task_id] != 0) && (++i < 10))
            usleep(100 * 1000);
#else
        result = pthread_join( gki_cb.os.thread_id[task_id], NULL );
        if ( result < 0 )
        {
            GKI_ERROR_LOG( "pthread_join() FAILED: result: %d", result );
        }
#endif
        GKI_exit_task(task_id);
        GKI_INFO( "GKI_shutdown(): task [%s] terminated\n", gki_cb.com.OSTName[task_id]);
    }
}


/*******************************************************************************
**
** Function         GKI_task_self_cleanup
**
** Description      This function is used in the case when the calling thread
**                  is exiting itself. The GKI_destroy_task function can not be
**                  used in this case due to the pthread_join call. The function
**                  cleans up GKI control block associated to the terminating
**                  thread.
**
** Parameters:      task_id     - (input) Task id is used for sanity check to
**                                 make sure the calling thread is in the right
**                                 context.
**
** Returns          None
**
*******************************************************************************/
void GKI_task_self_cleanup(UINT8 task_id)
{
    UINT8 my_task_id = GKI_get_taskid();

    if (task_id != my_task_id)
    {
        GKI_ERROR_LOG("%s: Wrong context - current task %d is not the given task id %d",\
                      __FUNCTION__, my_task_id, task_id);
        return;
    }

    if (gki_cb.com.OSRdyTbl[task_id] != TASK_DEAD)
    {
        /* paranoi settings, make sure that we do not execute any mailbox events */
        gki_cb.com.OSWaitEvt[task_id] &= ~(TASK_MBOX_0_EVT_MASK|TASK_MBOX_1_EVT_MASK|
                                            TASK_MBOX_2_EVT_MASK|TASK_MBOX_3_EVT_MASK);

#if (GKI_NUM_TIMERS > 0)
        gki_cb.com.OSTaskTmr0R[task_id] = 0;
        gki_cb.com.OSTaskTmr0 [task_id] = 0;
#endif

#if (GKI_NUM_TIMERS > 1)
        gki_cb.com.OSTaskTmr1R[task_id] = 0;
        gki_cb.com.OSTaskTmr1 [task_id] = 0;
#endif

#if (GKI_NUM_TIMERS > 2)
        gki_cb.com.OSTaskTmr2R[task_id] = 0;
        gki_cb.com.OSTaskTmr2 [task_id] = 0;
#endif

#if (GKI_NUM_TIMERS > 3)
        gki_cb.com.OSTaskTmr3R[task_id] = 0;
        gki_cb.com.OSTaskTmr3 [task_id] = 0;
#endif

        GKI_exit_task(task_id);

        /* Calling pthread_detach here to mark the thread as detached.
           Once the thread terminates, the system can reclaim its resources
           without waiting for another thread to join with.
        */
        pthread_detach(gki_cb.os.thread_id[task_id]);
    }
}

/*******************************************************************************
**
** Function         GKI_shutdown
**
** Description      shutdowns the GKI tasks/threads in from max task id to 0 and frees
**                  pthread resources!
**                  IMPORTANT: in case of join method, GKI_shutdown must be called outside
**                  a GKI thread context!
**
** Returns          void
**
*******************************************************************************/

void GKI_shutdown(void)
{
    UINT8 task_id;
#if ( FALSE == GKI_PTHREAD_JOINABLE )
    int i = 0;
#else
    int result;
#endif

#ifdef GKI_USE_DEFERED_ALLOC_BUF_POOLS
    gki_dealloc_free_queue();
#endif

    /* release threads and set as TASK_DEAD. going from low to high priority fixes
     * GKI_exception problem due to btu->hci sleep request events  */
    for (task_id = GKI_MAX_TASKS; task_id > 0; task_id--)
    {
        if (gki_cb.com.OSRdyTbl[task_id - 1] != TASK_DEAD)
        {
            gki_cb.com.OSRdyTbl[task_id - 1] = TASK_DEAD;

            /* paranoi settings, make sure that we do not execute any mailbox events */
            gki_cb.com.OSWaitEvt[task_id-1] &= ~(TASK_MBOX_0_EVT_MASK|TASK_MBOX_1_EVT_MASK|
                                                TASK_MBOX_2_EVT_MASK|TASK_MBOX_3_EVT_MASK);
            GKI_send_event(task_id - 1, EVENT_MASK(GKI_SHUTDOWN_EVT));

#if ( FALSE == GKI_PTHREAD_JOINABLE )
            i = 0;

            while ((gki_cb.com.OSWaitEvt[task_id - 1] != 0) && (++i < 10))
                usleep(100 * 1000);
#else
            result = pthread_join( gki_cb.os.thread_id[task_id-1], NULL );

            if ( result < 0 )
            {
                ALOGE( "pthread_join() FAILED: result: %d", result );
            }
#endif
            // GKI_ERROR_LOG( "GKI_shutdown(): task %s dead\n", gki_cb.com.OSTName[task_id]);
            GKI_exit_task(task_id - 1);
        }
    }

    /* Destroy mutex and condition variable objects */
    pthread_mutex_destroy(&gki_cb.os.GKI_mutex);

    /*    pthread_mutex_destroy(&GKI_sched_mutex); */
#if (GKI_DEBUG == TRUE)
    pthread_mutex_destroy(&gki_cb.os.GKI_trace_mutex);
#endif
    /*    pthread_mutex_destroy(&thread_delay_mutex);
     pthread_cond_destroy (&thread_delay_cond); */
#if ( FALSE == GKI_PTHREAD_JOINABLE )
    i = 0;
#endif

#ifdef NO_GKI_RUN_RETURN
    shutdown_timer = 1;
#endif
    if (g_GkiTimerWakeLockOn)
    {
        GKI_TRACE("GKI_shutdown :  release_wake_lock(brcm_btld)");
        release_wake_lock(WAKE_LOCK_ID);
        g_GkiTimerWakeLockOn = 0;
    }
}

/*******************************************************************************
 **
 ** Function        gki_system_tick_start_stop_cback
 **
 ** Description     This function runs a task
 **
 ** Parameters:     start: TRUE start system tick (again), FALSE stop
 **
 ** Returns         void
 **
 *********************************************************************************/

void gki_system_tick_start_stop_cback(BOOLEAN start)
{
    tGKI_OS         *p_os = &gki_cb.os;
    int    *p_run_cond = &p_os->no_timer_suspend;
    static int wake_lock_count;

    if ( FALSE == start )
    {
        /* gki_system_tick_start_stop_cback() maybe called even so it was already stopped! */
        if (GKI_TIMER_TICK_RUN_COND == *p_run_cond)
        {
#ifdef NO_GKI_RUN_RETURN
            /* take free mutex to block timer thread */
            pthread_mutex_lock(&p_os->gki_timer_mutex);
#endif
            /* this can lead to a race condition. however as we only read this variable in the
             * timer loop we should be fine with this approach. otherwise uncomment below mutexes.
             */
            /* GKI_disable(); */
            *p_run_cond = GKI_TIMER_TICK_STOP_COND;
            /* GKI_enable(); */

            GKI_TIMER_TRACE(">>> STOP GKI_timer_update(), wake_lock_count:%d", --wake_lock_count);

            release_wake_lock(WAKE_LOCK_ID);
            g_GkiTimerWakeLockOn = 0;
        }
    }
    else
    {
        /* restart GKI_timer_update() loop */
        acquire_wake_lock(PARTIAL_WAKE_LOCK, WAKE_LOCK_ID);

        g_GkiTimerWakeLockOn = 1;
        *p_run_cond = GKI_TIMER_TICK_RUN_COND;

#ifdef NO_GKI_RUN_RETURN
        pthread_mutex_unlock( &p_os->gki_timer_mutex );
#else
        pthread_mutex_lock( &p_os->gki_timer_mutex );
        pthread_cond_signal( &p_os->gki_timer_cond );
        pthread_mutex_unlock( &p_os->gki_timer_mutex );
#endif

        GKI_TIMER_TRACE(">>> START GKI_timer_update(), wake_lock_count:%d", ++wake_lock_count );
    }
}


/*******************************************************************************
**
** Function         GKI_run
**
** Description      This function runs a task
****
** Returns          void
**
** NOTE             This function is only needed for operating systems where
**                  starting a task is a 2-step process. Most OS's do it in
**                  one step, If your OS does it in one step, this function
**                  should be empty.
*********************************************************************************/
#ifdef NO_GKI_RUN_RETURN
void* timer_thread(void *arg)
{
    int timeout_ns=0;
    struct timespec timeout;
    struct timespec previous = {0,0};
    struct timespec current;
    int err;
    int delta_ns;
    int restart;
    tGKI_OS         *p_os = &gki_cb.os;
    int  *p_run_cond = &p_os->no_timer_suspend;

    /* Indicate that tick is just starting */
    restart = 1;

    prctl(PR_SET_NAME, (unsigned long)"gki timer", 0, 0, 0);

    raise_priority_a2dp(TASK_HIGH_GKI_TIMER);

    while(!shutdown_timer)
    {
        /* If the timer has been stopped (no SW timer running) */
        if (*p_run_cond == GKI_TIMER_TICK_STOP_COND)
        {
            /*
             * We will lock/wait on GKI_timer_mutex.
             * This mutex will be unlocked when timer is re-started
             */
            GKI_TRACE("GKI_run lock mutex");
            pthread_mutex_lock(&p_os->gki_timer_mutex);

            /* We are here because the mutex has been released by timer cback */
            /* Let's release it for future use */
            GKI_TRACE("GKI_run unlock mutex");
            pthread_mutex_unlock(&p_os->gki_timer_mutex);

            /* Indicate that tick is just starting */
            restart = 1;
        }

        /* Get time */
        clock_gettime(CLOCK_MONOTONIC, &current);

        /* Check if tick was just restarted, indicating to the compiler that this is
         * unlikely to happen (to help branch prediction) */
        if (__unlikely(restart))
        {
            /* Clear the restart indication */
            restart = 0;

            timeout_ns = (GKI_TICKS_TO_MS(1) * 1000000);
        }
        else
        {
            /* Compute time elapsed since last sleep start */
            delta_ns = current.tv_nsec - previous.tv_nsec;
            delta_ns += (current.tv_sec - previous.tv_sec) * 1000000000;

            /* Compute next timeout:
             *    timeout = (next theoretical expiration) - current time
             *    timeout = (previous time + timeout + delay) - current time
             *    timeout = timeout + delay - (current time - previous time)
             *    timeout += delay - delta */
            timeout_ns += (GKI_TICKS_TO_MS(1) * 1000000) - delta_ns;
        }
        /* Save the current time for next iteration */
        previous = current;

        timeout.tv_sec = 0;

        /* Sleep until next theoretical tick time.  In case of excessive
           elapsed time since last theoretical tick expiration, it is
           possible that the timeout value is negative.  To protect
           against this error, we set minimum sleep time to 10% of the
           tick period.  We indicate to compiler that this is unlikely to
           happen (to help branch prediction) */

        if (__unlikely(timeout_ns < ((GKI_TICKS_TO_MS(1) * 1000000) * 0.1)))
        {
            timeout.tv_nsec = (GKI_TICKS_TO_MS(1) * 1000000) * 0.1;

            /* Print error message if tick really got delayed
               (more than 5 ticks) */
            if (timeout_ns < GKI_TICKS_TO_MS(-5) * 1000000)
            {
                GKI_ERROR_LOG("tick delayed > 5 slots (%d,%d) -- cpu overload ? ",
                        timeout_ns, GKI_TICKS_TO_MS(-5) * 1000000);
            }
        }
        else
        {
            timeout.tv_nsec = timeout_ns;
        }

        do
        {
            /* [u]sleep can't be used because it uses SIGALRM */
            err = nanosleep(&timeout, &timeout);
        } while (err < 0 && errno == EINTR);

        /* Increment the GKI time value by one tick and update internal timers */
        GKI_timer_update(1);
    }
    GKI_TRACE("gki_ulinux: Exiting timer_thread");
    pthread_exit(NULL);
    return NULL;
}
#endif


/*****************************************************************************
**
** Function        gki_set_timer_scheduling
**
** Description     helper function to set scheduling policy and priority of btdl
**
** Returns         void
**
*******************************************************************************/

static void gki_set_timer_scheduling( void )
{
    pid_t               main_pid = getpid();
    struct sched_param  param;
    int                 policy;

    policy = sched_getscheduler(main_pid);

    if ( policy != -1 )
    {
        GKI_TRACE("gki_set_timer_scheduling(()::scheduler current policy: %d", policy);

        /* ensure highest priority in the system + 2 to allow space for read threads */
        param.sched_priority = GKI_LINUX_TIMER_TICK_PRIORITY;

        if ( 0!=sched_setscheduler(main_pid, GKI_LINUX_TIMER_POLICY, &param ) )
        {
            GKI_TRACE("sched_setscheduler() failed with error: %d", errno);
        }
    }
    else
    {
        GKI_TRACE( "getscheduler failed: %d", errno);
    }
}


/*****************************************************************************
**
** Function        GKI_freeze
**
** Description     Freeze GKI. Relevant only when NO_GKI_RUN_RETURN is defined
**
** Returns
**
*******************************************************************************/

void GKI_freeze()
{
#ifdef NO_GKI_RUN_RETURN
   shutdown_timer = 1;
   pthread_mutex_unlock( &gki_cb.os.gki_timer_mutex );
   /* Ensure that the timer thread exits */
   pthread_join(timer_thread_id, NULL);
#endif
}

/*****************************************************************************
**
** Function        GKI_run
**
** Description     Main GKI loop
**
** Returns
**
*******************************************************************************/

void GKI_run (void *p_task_id)
{
    struct timespec delay;
    int err;
    volatile int * p_run_cond = &gki_cb.os.no_timer_suspend;

#ifndef GKI_NO_TICK_STOP
    /* adjust btld scheduling scheme now */
    gki_set_timer_scheduling();

    /* register start stop function which disable timer loop in GKI_run() when no timers are
     * in any GKI/BTA/BTU this should save power when BTLD is idle! */
    GKI_timer_queue_register_callback( gki_system_tick_start_stop_cback );
    GKI_TRACE( "GKI_run(): Start/Stop GKI_timer_update_registered!" );
#endif

#ifdef NO_GKI_RUN_RETURN
    pthread_attr_t timer_attr;

    shutdown_timer = 0;

    pthread_attr_init(&timer_attr);
    if (pthread_create( &timer_thread_id,
              &timer_attr,
              timer_thread,
              NULL) != 0 )
    {
        GKI_ERROR_LOG("pthread_create failed to create timer_thread!\n\r");
        return;
    }

#else
    GKI_TRACE("GKI_run ");
    for (;;)
    {
        do
        {
            /* adjust hear bit tick in btld by changning TICKS_PER_SEC!!!!! this formula works only for
             * 1-1000ms heart beat units! */
            delay.tv_sec = LINUX_SEC / 1000;
            delay.tv_nsec = 1000 * 1000 * (LINUX_SEC % 1000);

            /* [u]sleep can't be used because it uses SIGALRM */
            do
            {
                err = nanosleep(&delay, &delay);
            } while (err < 0 && errno == EINTR);

            /* the unit should be alsways 1 (1 tick). only if you vary for some reason heart beat tick
             * e.g. power saving you may want to provide more ticks
             */
            GKI_timer_update( 1 );
            /* BT_TRACE_2( TRACE_LAYER_HCI, TRACE_TYPE_DEBUG, "update: tv_sec: %d, tv_nsec: %d", delay.tv_sec, delay.tv_nsec ); */
        } while ( GKI_TIMER_TICK_RUN_COND == *p_run_cond );

        /* currently on reason to exit above loop is no_timer_suspend == GKI_TIMER_TICK_STOP_COND
         * block timer main thread till re-armed by  */

        GKI_TIMER_TRACE(">>> SUSPENDED GKI_timer_update()" );

        pthread_mutex_lock( &gki_cb.os.gki_timer_mutex );
        pthread_cond_wait( &gki_cb.os.gki_timer_cond, &gki_cb.os.gki_timer_mutex );
        pthread_mutex_unlock( &gki_cb.os.gki_timer_mutex );

        /* potentially we need to adjust os gki_cb.com.OSTicks */
        GKI_TIMER_TRACE(">>> RESTARTED GKI_timer_update(): run_cond: %d",
                    *p_run_cond );

    }
#endif
    return;
}


/*******************************************************************************
**
** Function         GKI_stop
**
** Description      This function is called to stop
**                  the tasks and timers when the system is being stopped
**
** Returns          void
**
** NOTE             This function is NOT called by the Broadcom stack and
**                  profiles. If you want to use it in your own implementation,
**                  put specific code here.
**
*******************************************************************************/

void GKI_stop (void)
{
    UINT8 task_id;

    /*  gki_queue_timer_cback(FALSE); */
    /* TODO - add code here if needed*/

    for(task_id = 0; task_id<GKI_MAX_TASKS; task_id++)
    {
        if(gki_cb.com.OSRdyTbl[task_id] != TASK_DEAD)
        {
            GKI_exit_task(task_id);
        }
    }
}


/*******************************************************************************
**
** Function         GKI_wait
**
** Description      This function is called by tasks to wait for a specific
**                  event or set of events. The task may specify the duration
**                  that it wants to wait for, or 0 if infinite.
**
** Parameters:      flag -    (input) the event or set of events to wait for
**                  timeout - (input) the duration that the task wants to wait
**                                    for the specific events (in system ticks)
**
**
** Returns          the event mask of received events or zero if timeout
**
*******************************************************************************/
UINT16 GKI_wait (UINT16 flag, UINT32 timeout)
{
    UINT16 evt;
    UINT8 rtask;
    struct timespec abstime = { 0, 0 };

    int sec;
    int nano_sec;

    rtask = GKI_get_taskid();

    GKI_TRACE("GKI_wait %d %x %d", (int)rtask, (int)flag, (int)timeout);

    gki_cb.com.OSWaitForEvt[rtask] = flag;

    /* protect OSWaitEvt[rtask] from modification from an other thread */
    pthread_mutex_lock(&gki_cb.os.thread_evt_mutex[rtask]);

    if (!(gki_cb.com.OSWaitEvt[rtask] & flag))
    {
        if (timeout)
        {
            clock_gettime(CLOCK_MONOTONIC, &abstime);

            /* add timeout */
            sec = timeout / 1000;
            nano_sec = (timeout % 1000) * NANOSEC_PER_MILLISEC;
            abstime.tv_nsec += nano_sec;
            if (abstime.tv_nsec > NSEC_PER_SEC)
            {
                abstime.tv_sec += (abstime.tv_nsec / NSEC_PER_SEC);
                abstime.tv_nsec = abstime.tv_nsec % NSEC_PER_SEC;
            }
            abstime.tv_sec += sec;

            pthread_cond_timedwait_monotonic(&gki_cb.os.thread_evt_cond[rtask],
                    &gki_cb.os.thread_evt_mutex[rtask], &abstime);

        }
        else
        {
            pthread_cond_wait(&gki_cb.os.thread_evt_cond[rtask], &gki_cb.os.thread_evt_mutex[rtask]);
        }

        /* TODO: check, this is probably neither not needed depending on phtread_cond_wait() implmentation,
         e.g. it looks like it is implemented as a counter in which case multiple cond_signal
         should NOT be lost! */

        /* we are waking up after waiting for some events, so refresh variables
           no need to call GKI_disable() here as we know that we will have some events as we've been waking
           up after condition pending or timeout */

        if (gki_cb.com.OSTaskQFirst[rtask][0])
            gki_cb.com.OSWaitEvt[rtask] |= TASK_MBOX_0_EVT_MASK;
        if (gki_cb.com.OSTaskQFirst[rtask][1])
            gki_cb.com.OSWaitEvt[rtask] |= TASK_MBOX_1_EVT_MASK;
        if (gki_cb.com.OSTaskQFirst[rtask][2])
            gki_cb.com.OSWaitEvt[rtask] |= TASK_MBOX_2_EVT_MASK;
        if (gki_cb.com.OSTaskQFirst[rtask][3])
            gki_cb.com.OSWaitEvt[rtask] |= TASK_MBOX_3_EVT_MASK;

        if (gki_cb.com.OSRdyTbl[rtask] == TASK_DEAD)
        {
            gki_cb.com.OSWaitEvt[rtask] = 0;
            /* unlock thread_evt_mutex as pthread_cond_wait() does auto lock when cond is met */
            pthread_mutex_unlock(&gki_cb.os.thread_evt_mutex[rtask]);
            return (EVENT_MASK(GKI_SHUTDOWN_EVT));
        }
    }

    /* Clear the wait for event mask */
    gki_cb.com.OSWaitForEvt[rtask] = 0;

    /* Return only those bits which user wants... */
    evt = gki_cb.com.OSWaitEvt[rtask] & flag;

    /* Clear only those bits which user wants... */
    gki_cb.com.OSWaitEvt[rtask] &= ~flag;

    /* unlock thread_evt_mutex as pthread_cond_wait() does auto lock mutex when cond is met */
    pthread_mutex_unlock(&gki_cb.os.thread_evt_mutex[rtask]);

    GKI_TRACE("GKI_wait %d %x %d %x done", (int)rtask, (int)flag, (int)timeout, (int)evt);
    return (evt);
}


/*******************************************************************************
**
** Function         GKI_delay
**
** Description      This function is called by tasks to sleep unconditionally
**                  for a specified amount of time. The duration is in milliseconds
**
** Parameters:      timeout -    (input) the duration in milliseconds
**
** Returns          void
**
*******************************************************************************/

void GKI_delay (UINT32 timeout)
{
    UINT8 rtask = GKI_get_taskid();
    struct timespec delay;
    int err;

    GKI_TRACE("GKI_delay %d %d", (int)rtask, (int)timeout);

    delay.tv_sec = timeout / 1000;
    delay.tv_nsec = 1000 * 1000 * (timeout%1000);

    /* [u]sleep can't be used because it uses SIGALRM */

    do {
        err = nanosleep(&delay, &delay);
    } while (err < 0 && errno ==EINTR);

    /* Check if task was killed while sleeping */

     /* NOTE : if you do not implement task killing, you do not need this check */

    if (rtask && gki_cb.com.OSRdyTbl[rtask] == TASK_DEAD)
    {
    }

    GKI_TRACE("GKI_delay %d %d done", (int)rtask, (int)timeout);

    return;
}


/*******************************************************************************
**
** Function         GKI_send_event
**
** Description      This function is called by tasks to send events to other
**                  tasks. Tasks can also send events to themselves.
**
** Parameters:      task_id -  (input) The id of the task to which the event has to
**                  be sent
**                  event   -  (input) The event that has to be sent
**
**
** Returns          GKI_SUCCESS if all OK, else GKI_FAILURE
**
*******************************************************************************/

UINT8 GKI_send_event (UINT8 task_id, UINT16 event)
{
    GKI_TRACE("GKI_send_event %d %x", task_id, event);

    /* use efficient coding to avoid pipeline stalls */
    if (task_id < GKI_MAX_TASKS)
    {
        /* protect OSWaitEvt[task_id] from manipulation in GKI_wait() */
        pthread_mutex_lock(&gki_cb.os.thread_evt_mutex[task_id]);

        /* Set the event bit */
        gki_cb.com.OSWaitEvt[task_id] |= event;

        pthread_cond_signal(&gki_cb.os.thread_evt_cond[task_id]);

        pthread_mutex_unlock(&gki_cb.os.thread_evt_mutex[task_id]);

        GKI_TRACE("GKI_send_event %d %x done", task_id, event);
        return ( GKI_SUCCESS );
    }
    GKI_TRACE("############## GKI_send_event FAILED!! ##################");
    return (GKI_FAILURE);
}


/*******************************************************************************
**
** Function         GKI_isend_event
**
** Description      This function is called from ISRs to send events to other
**                  tasks. The only difference between this function and GKI_send_event
**                  is that this function assumes interrupts are already disabled.
**
** Parameters:      task_id -  (input) The destination task Id for the event.
**                  event   -  (input) The event flag
**
** Returns          GKI_SUCCESS if all OK, else GKI_FAILURE
**
** NOTE             This function is NOT called by the Broadcom stack and
**                  profiles. If you want to use it in your own implementation,
**                  put your code here, otherwise you can delete the entire
**                  body of the function.
**
*******************************************************************************/
UINT8 GKI_isend_event (UINT8 task_id, UINT16 event)
{
    GKI_TRACE("GKI_isend_event %d %x", task_id, event);
    GKI_TRACE("GKI_isend_event %d %x done", task_id, event);
    return    GKI_send_event(task_id, event);
}


/*******************************************************************************
**
** Function         GKI_get_taskid
**
** Description      This function gets the currently running task ID.
**
** Returns          task ID
**
** NOTE             The Broadcom upper stack and profiles may run as a single task.
**                  If you only have one GKI task, then you can hard-code this
**                  function to return a '1'. Otherwise, you should have some
**                  OS-specific method to determine the current task.
**
*******************************************************************************/
UINT8 GKI_get_taskid (void)
{
    int i;

    pthread_t thread_id = pthread_self( );

    GKI_TRACE("GKI_get_taskid %x", (int)thread_id);

    for (i = 0; i < GKI_MAX_TASKS; i++) {
        if (gki_cb.os.thread_id[i] == thread_id) {
            //GKI_TRACE("GKI_get_taskid %x %d done", thread_id, i);
            return(i);
        }
    }

    GKI_TRACE("GKI_get_taskid: task id = -1");

    return(-1);
}


/*******************************************************************************
**
** Function         GKI_map_taskname
**
** Description      This function gets the task name of the taskid passed as arg.
**                  If GKI_MAX_TASKS is passed as arg the currently running task
**                  name is returned
**
** Parameters:      task_id -  (input) The id of the task whose name is being
**                  sought. GKI_MAX_TASKS is passed to get the name of the
**                  currently running task.
**
** Returns          pointer to task name
**
** NOTE             this function needs no customization
**
*******************************************************************************/

INT8 *GKI_map_taskname (UINT8 task_id)
{
    GKI_TRACE("GKI_map_taskname %d", task_id);

    if (task_id < GKI_MAX_TASKS)
    {
        GKI_TRACE("GKI_map_taskname %d %s done", task_id, gki_cb.com.OSTName[task_id]);
         return (gki_cb.com.OSTName[task_id]);
    }
    else if (task_id == GKI_MAX_TASKS )
    {
        return (gki_cb.com.OSTName[GKI_get_taskid()]);
    }
    else
    {
        return (INT8*)"BAD";
    }
}


/*******************************************************************************
**
** Function         GKI_enable
**
** Description      This function enables interrupts.
**
** Returns          void
**
*******************************************************************************/
void GKI_enable (void)
{
    //GKI_TRACE("GKI_enable");
    pthread_mutex_unlock(&gki_cb.os.GKI_mutex);
    //GKI_TRACE("Leaving GKI_enable");
    return;
}


/*******************************************************************************
**
** Function         GKI_disable
**
** Description      This function disables interrupts.
**
** Returns          void
**
*******************************************************************************/

void GKI_disable (void)
{
    //GKI_TRACE("GKI_disable");

    pthread_mutex_lock(&gki_cb.os.GKI_mutex);

    //GKI_TRACE("Leaving GKI_disable");
    return;
}


/*******************************************************************************
**
** Function         GKI_exception
**
** Description      This function throws an exception.
**                  This is normally only called for a nonrecoverable error.
**
** Parameters:      code    -  (input) The code for the error
**                  msg     -  (input) The message that has to be logged
**
** Returns          void
**
*******************************************************************************/

void GKI_exception (UINT16 code, char *msg)
{
    UINT8 task_id;
    int i = 0;

    GKI_ERROR_LOG( "GKI_exception(): Task State Table\n");

    for(task_id = 0; task_id < GKI_MAX_TASKS; task_id++)
    {
        GKI_ERROR_LOG( "TASK ID [%d] task name [%s] state [%d]\n",
                         task_id,
                         gki_cb.com.OSTName[task_id],
                         gki_cb.com.OSRdyTbl[task_id]);
    }

    GKI_ERROR_LOG("GKI_exception %d %s", code, msg);
    GKI_ERROR_LOG( "\n********************************************************************\n");
    GKI_ERROR_LOG( "* GKI_exception(): %d %s\n", code, msg);
    GKI_ERROR_LOG( "********************************************************************\n");

#if 0//(GKI_DEBUG == TRUE)
    GKI_disable();

    if (gki_cb.com.ExceptionCnt < GKI_MAX_EXCEPTION)
    {
        EXCEPTION_T *pExp;

        pExp =  &gki_cb.com.Exception[gki_cb.com.ExceptionCnt++];
        pExp->type = code;
        pExp->taskid = GKI_get_taskid();
        strncpy((char *)pExp->msg, msg, GKI_MAX_EXCEPTION_MSGLEN - 1);
    }

    GKI_enable();
#endif

    GKI_TRACE("GKI_exception %d %s done", code, msg);
    return;
}


/*******************************************************************************
**
** Function         GKI_get_time_stamp
**
** Description      This function formats the time into a user area
**
** Parameters:      tbuf -  (output) the address to the memory containing the
**                  formatted time
**
** Returns          the address of the user area containing the formatted time
**                  The format of the time is ????
**
** NOTE             This function is only called by OBEX.
**
*******************************************************************************/
INT8 *GKI_get_time_stamp (INT8 *tbuf)
{
    UINT32 ms_time;
    UINT32 s_time;
    UINT32 m_time;
    UINT32 h_time;
    INT8   *p_out = tbuf;

    gki_cb.com.OSTicks = times(0);
    ms_time = GKI_TICKS_TO_MS(gki_cb.com.OSTicks);
    s_time  = ms_time/100;   /* 100 Ticks per second */
    m_time  = s_time/60;
    h_time  = m_time/60;

    ms_time -= s_time*100;
    s_time  -= m_time*60;
    m_time  -= h_time*60;

    *p_out++ = (INT8)((h_time / 10) + '0');
    *p_out++ = (INT8)((h_time % 10) + '0');
    *p_out++ = ':';
    *p_out++ = (INT8)((m_time / 10) + '0');
    *p_out++ = (INT8)((m_time % 10) + '0');
    *p_out++ = ':';
    *p_out++ = (INT8)((s_time / 10) + '0');
    *p_out++ = (INT8)((s_time % 10) + '0');
    *p_out++ = ':';
    *p_out++ = (INT8)((ms_time / 10) + '0');
    *p_out++ = (INT8)((ms_time % 10) + '0');
    *p_out++ = ':';
    *p_out   = 0;

    return (tbuf);
}


/*******************************************************************************
**
** Function         GKI_register_mempool
**
** Description      This function registers a specific memory pool.
**
** Parameters:      p_mem -  (input) pointer to the memory pool
**
** Returns          void
**
** NOTE             This function is NOT called by the Broadcom stack and
**                  profiles. If your OS has different memory pools, you
**                  can tell GKI the pool to use by calling this function.
**
*******************************************************************************/
void GKI_register_mempool (void *p_mem)
{
    gki_cb.com.p_user_mempool = p_mem;

    return;
}

/*******************************************************************************
**
** Function         GKI_os_malloc
**
** Description      This function allocates memory
**
** Parameters:      size -  (input) The size of the memory that has to be
**                  allocated
**
** Returns          the address of the memory allocated, or NULL if failed
**
** NOTE             This function is called by the Broadcom stack when
**                  dynamic memory allocation is used. (see dyn_mem.h)
**
*******************************************************************************/
void *GKI_os_malloc (UINT32 size)
{
    return (malloc(size));
}

/*******************************************************************************
**
** Function         GKI_os_free
**
** Description      This function frees memory
**
** Parameters:      size -  (input) The address of the memory that has to be
**                  freed
**
** Returns          void
**
** NOTE             This function is NOT called by the Broadcom stack and
**                  profiles. It is only called from within GKI if dynamic
**
*******************************************************************************/
void GKI_os_free (void *p_mem)
{
    if(p_mem != NULL)
        free(p_mem);
    return;
}


/*******************************************************************************
**
** Function         GKI_suspend_task()
**
** Description      This function suspends the task specified in the argument.
**
** Parameters:      task_id  - (input) the id of the task that has to suspended
**
** Returns          GKI_SUCCESS if all OK, else GKI_FAILURE
**
** NOTE             This function is NOT called by the Broadcom stack and
**                  profiles. If you want to implement task suspension capability,
**                  put specific code here.
**
*******************************************************************************/
UINT8 GKI_suspend_task (UINT8 task_id)
{
    GKI_TRACE("GKI_suspend_task %d - NOT implemented", task_id);


    GKI_TRACE("GKI_suspend_task %d done", task_id);

    return (GKI_SUCCESS);
}


/*******************************************************************************
**
** Function         GKI_resume_task()
**
** Description      This function resumes the task specified in the argument.
**
** Parameters:      task_id  - (input) the id of the task that has to resumed
**
** Returns          GKI_SUCCESS if all OK
**
** NOTE             This function is NOT called by the Broadcom stack and
**                  profiles. If you want to implement task suspension capability,
**                  put specific code here.
**
*******************************************************************************/
UINT8 GKI_resume_task (UINT8 task_id)
{
    GKI_TRACE("GKI_resume_task %d - NOT implemented", task_id);


    GKI_TRACE("GKI_resume_task %d done", task_id);

    return (GKI_SUCCESS);
}


/*******************************************************************************
**
** Function         GKI_exit_task
**
** Description      This function is called to stop a GKI task.
**
** Parameters:      task_id  - (input) the id of the task that has to be stopped
**
** Returns          void
**
** NOTE             This function is NOT called by the Broadcom stack and
**                  profiles. If you want to use it in your own implementation,
**                  put specific code here to kill a task.
**
*******************************************************************************/
void GKI_exit_task (UINT8 task_id)
{
    GKI_disable();
    gki_cb.com.OSRdyTbl[task_id] = TASK_DEAD;

    /* Destroy mutex and condition variable objects */
    pthread_mutex_destroy(&gki_cb.os.thread_evt_mutex[task_id]);
    pthread_cond_destroy (&gki_cb.os.thread_evt_cond[task_id]);
    pthread_mutex_destroy(&gki_cb.os.thread_timeout_mutex[task_id]);
    pthread_cond_destroy (&gki_cb.os.thread_timeout_cond[task_id]);

    GKI_enable();

    //GKI_send_event(task_id, EVENT_MASK(GKI_SHUTDOWN_EVT));

    GKI_INFO("GKI_exit_task %d done", task_id);
    return;
}


/*******************************************************************************
**
** Function         GKI_sched_lock
**
** Description      This function is called by tasks to disable scheduler
**                  task context switching.
**
** Returns          void
**
** NOTE             This function is NOT called by the Broadcom stack and
**                  profiles. If you want to use it in your own implementation,
**                  put code here to tell the OS to disable context switching.
**
*******************************************************************************/
void GKI_sched_lock(void)
{
    GKI_TRACE("GKI_sched_lock");
    return;
}


/*******************************************************************************
**
** Function         GKI_sched_unlock
**
** Description      This function is called by tasks to enable scheduler switching.
**
** Returns          void
**
** NOTE             This function is NOT called by the Broadcom stack and
**                  profiles. If you want to use it in your own implementation,
**                  put code here to tell the OS to re-enable context switching.
**
*******************************************************************************/
void GKI_sched_unlock(void)
{
    GKI_TRACE("GKI_sched_unlock");
}


