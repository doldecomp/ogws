/******************************************************************************
 *
 *  NOTICE OF CHANGES
 *  2024/03/25:
 *      - Move from ulinux/ to platform/
 *      - Modify tGKI_OS structure to match RVL target
 *      - Add #define for MAX_INT_STATE
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
#ifndef GKI_INT_H
#define GKI_INT_H
#include "gki_common.h"

/**********************************************************************
** OS specific definitions
*/

#ifdef REVOLUTION
#define MAX_INT_STATE 16
#endif

/* The base priority used for pthread based GKI task. below value is to keep it retro compatible.
 * It is recommended to use (GKI_MAX_TASKS+3), this will assign real time priorities GKI_MAX_TASKS-
 * task_id -2 to the thread */
#ifndef GKI_LINUX_BASE_PRIORITY
#define GKI_LINUX_BASE_PRIORITY 30
#endif

/* The base policy used for pthread based GKI task. the sched defines are defined here to avoid undefined values due
 * to missing header file, see pthread functions! Overall it is recommend however to use SCHED_NOMRAL */
#define GKI_SCHED_NORMAL    0
#define GKI_SCHED_FIFO      1
#define GKI_SCHED_RR        2
#ifndef GKI_LINUX_BASE_POLICY
#define GKI_LINUX_BASE_POLICY GKI_SCHED_NORMAL
#endif

/* GKI timer bases should use GKI_SCHED_FIFO to ensure the least jitter possible */
#ifndef GKI_LINUX_TIMER_POLICY
#define GKI_LINUX_TIMER_POLICY GKI_SCHED_FIFO
#endif

/* the GKI_timer_update() thread should have the highest real time priority to ensue correct
 * timer expiry.
 */
#ifndef GKI_LINUX_TIMER_TICK_PRIORITY
#define GKI_LINUX_TIMER_TICK_PRIORITY GKI_LINUX_BASE_PRIORITY+2
#endif

/* the AV timer should preferably run above the gki timer tick to ensure precise AV timing
 * If you observe AV jitter under have load you may increase this one */
#ifndef GKI_LINUX_AV_TIMER_PRIORITY
#define GKI_LINUX_AV_TIMER_PRIORITY GKI_LINUX_BASE_PRIORITY+3
#endif

/* defines by how much the nice value of the PROCESS should be changed. Values allowed:
 * -19 to +19. a negative value give higher priority to btld compared to the default nice value
 * of 20. in case of SCHED_NORMAL, a level of -5 should give a good btld/bt performance.
 * In case of real time scheduling, leave default value.
 */
#ifndef GKI_LINUX_DEFAULT_NICE_INC
#define GKI_LINUX_DEFAULT_NICE_INC -7
#endif

typedef struct
{
#ifdef REVOLUTION
    UINT8               int_index;
    BOOL                int_state[MAX_INT_STATE];
    char _pad[0x10];
#else
    pthread_mutex_t     GKI_mutex;
    pthread_t           thread_id[GKI_MAX_TASKS];
    pthread_mutex_t     thread_evt_mutex[GKI_MAX_TASKS];
    pthread_cond_t      thread_evt_cond[GKI_MAX_TASKS];
    pthread_mutex_t     thread_timeout_mutex[GKI_MAX_TASKS];
    pthread_cond_t      thread_timeout_cond[GKI_MAX_TASKS];
    int                 no_timer_suspend;   /* 1: no suspend, 0 stop calling GKI_timer_update() */
    pthread_mutex_t     gki_timer_mutex;
    pthread_cond_t      gki_timer_cond;
#if (GKI_DEBUG == TRUE)
    pthread_mutex_t     GKI_trace_mutex;
#endif
#endif
} tGKI_OS;

/* condition to exit or continue GKI_run() timer loop */
#define GKI_TIMER_TICK_RUN_COND 1
#define GKI_TIMER_TICK_STOP_COND 0

extern void gki_system_tick_start_stop_cback(BOOLEAN start);

/* Contains common control block as well as OS specific variables */
typedef struct
{
    tGKI_OS     os;
    tGKI_COM_CB com;
} tGKI_CB;


#ifdef __cplusplus
extern "C" {
#endif

#if GKI_DYNAMIC_MEMORY == FALSE
GKI_API extern tGKI_CB  gki_cb;
#else
GKI_API extern tGKI_CB *gki_cb_ptr;
#define gki_cb (*gki_cb_ptr)
#endif

#ifdef __cplusplus
}
#endif

#endif

