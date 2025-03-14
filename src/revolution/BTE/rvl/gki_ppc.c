/******************************************************************************
 *
 *  NOTICE OF CHANGES
 *  2024/03/25:
 *      - Move from ulinux/ to platform/
 * 
 *  2025/03/11:
 *      - Add declarations for "App" allocator hooks
 * 
 *  Compile with REVOLUTION defined to include these changes.
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

#ifndef REVOLUTION
#error Please compile the BTE library with REVOLUTION!
#endif

#include "gki_int.h"
#include <revolution/OS.h>
#include <revolution/WUD.h>

#ifdef REVOLUTION
/*****************************************************************************
**  Function prototypes
*****************************************************************************/
extern void *App_MEMalloc(UINT32 size);
extern int App_MEMfree(void* p_mem);
#endif

/*****************************************************************************
**  Static variables
******************************************************************************/

tGKI_CB gki_cb;

/*****************************************************************************
**  Static functions
******************************************************************************/

static BOOLEAN GKI_init_btu_task(INT32 task);

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
    memset(&gki_cb, 0, sizeof(gki_cb));

    gki_buffer_init();
    gki_timers_init();
    GKI_init_btu_task(GKI_PPC_TASK);

    gki_cb.os.int_index = 0;
    gki_cb.os.int_state[gki_cb.os.int_index] = OSEnableInterrupts();
    gki_cb.os.int_index++;
    
    return;
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
    GKI_exit_task(GKI_PPC_TASK);

    while (gki_cb.os.int_index > 0)
    {
        GKI_enable();
    }

    return;
}

/*******************************************************************************
**
** Function         GKI_init_btu_task
**
** Description      None
**
** Parameters       task_id  - (input) task ID
**
** Returns          GKI_SUCCESS if all OK, else GKI_FAILURE
**
*******************************************************************************/

static UINT8 GKI_init_btu_task(INT32 task_id) {
    if (task_id >= GKI_MAX_TASKS)
    {
        return GKI_FAILURE;
    }

    gki_cb.com.OSRdyTbl[task_id] = TASK_READY;
    gki_cb.com.OSTName[task_id] = NULL;
    gki_cb.com.OSWaitTmr[task_id] = 0;
    gki_cb.com.OSWaitEvt[task_id] = 0;
 
    return GKI_SUCCESS;
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

void GKI_run(void *p_task_id)
{
#pragma unused(p_task_id)
    return;
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

void GKI_exit_task(UINT8 task_id)
{
    GKI_disable();
    gki_cb.com.OSRdyTbl[task_id] = TASK_DEAD;
    GKI_enable();

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
    return;
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

void GKI_delay(UINT32 timeout)
{
#pragma unused(timeout)
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

UINT8 GKI_send_event(UINT8 task_id, UINT16 event)
{
    if (task_id >= GKI_MAX_TASKS)
    {
        return GKI_FAILURE;
    }

    GKI_disable();
    gki_cb.com.OSWaitEvt[task_id] |= event;
    GKI_enable();

    return GKI_SUCCESS;
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

UINT8 GKI_get_taskid(void)
{
    return GKI_PPC_TASK;
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

void GKI_enable(void)
{
    gki_cb.os.int_index--;
    OSRestoreInterrupts(gki_cb.os.int_state[gki_cb.os.int_index]);

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

void GKI_disable(void)
{
    gki_cb.os.int_state[gki_cb.os.int_index] = OSDisableInterrupts();
    gki_cb.os.int_index++;

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

void GKI_exception(UINT16 code, char *msg)
{
#pragma unused(code)
#pragma unused(msg)
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

void *GKI_os_malloc(UINT32 size)
{
    void *block = App_MEMalloc(size);
    if (block == NULL) {
        return NULL;
    }

    return block;
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

void GKI_os_free(void *p_mem)
{
    App_MEMfree(p_mem);
    return;
}
