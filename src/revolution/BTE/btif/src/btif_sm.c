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


/*****************************************************************************
 *
 *  Filename:      btif_sm.c
 *
 *  Description:   Generic BTIF state machine API
 *
 *****************************************************************************/
#include <hardware/bluetooth.h>

#define LOG_TAG "BTIF_SM"
#include "btif_common.h"
#include "btif_sm.h"
#include "gki.h"

/*****************************************************************************
**  Constants & Macros
******************************************************************************/


/*****************************************************************************
**  Local type definitions
******************************************************************************/
typedef struct {
    btif_sm_state_t         state;
    btif_sm_handler_t       *p_handlers;
} btif_sm_cb_t;

/*****************************************************************************
**  Static variables
******************************************************************************/

/*****************************************************************************
**  Static functions
******************************************************************************/

/*****************************************************************************
**  Externs
******************************************************************************/

/*****************************************************************************
**  Functions
******************************************************************************/

/*****************************************************************************
**
** Function     btif_sm_init
**
** Description  Initializes the state machine with the state handlers
**              The caller should ensure that the table and the corresponding
**              states match. The location that 'p_handlers' points to shall
**              be available until the btif_sm_shutdown API is invoked.
**
** Returns      Returns a pointer to the initialized state machine handle.
**
******************************************************************************/

btif_sm_handle_t btif_sm_init(const btif_sm_handler_t *p_handlers, btif_sm_state_t initial_state)
{
    btif_sm_cb_t *p_cb;

    if (p_handlers == NULL)
    {
        BTIF_TRACE_ERROR1("%s : p_handlers is NULL", __FUNCTION__);
        return NULL;
    }

    p_cb = (btif_sm_cb_t*) GKI_os_malloc(sizeof(btif_sm_cb_t));
    p_cb->state = initial_state;
    p_cb->p_handlers = (btif_sm_handler_t*)p_handlers;

    /* Send BTIF_SM_ENTER_EVT to the initial state */
    p_cb->p_handlers[initial_state](BTIF_SM_ENTER_EVT, NULL);

    return (btif_sm_handle_t)p_cb;
}

/*****************************************************************************
**
** Function     btif_sm_shutdown
**
** Description  Tears down the state machine
**
** Returns      None
**
******************************************************************************/
void btif_sm_shutdown(btif_sm_handle_t handle)
{
    btif_sm_cb_t *p_cb = (btif_sm_cb_t*)handle;

    if (p_cb == NULL)
    {
        BTIF_TRACE_ERROR1("%s : Invalid handle", __FUNCTION__);
        return;
    }
    GKI_os_free((void*)p_cb);
}

/*****************************************************************************
**
** Function     btif_sm_get_state
**
** Description  Fetches the current state of the state machine
**
** Returns      Current state
**
******************************************************************************/
btif_sm_state_t btif_sm_get_state(btif_sm_handle_t handle)
{
    btif_sm_cb_t *p_cb = (btif_sm_cb_t*)handle;

    if (p_cb == NULL)
    {
        BTIF_TRACE_ERROR1("%s : Invalid handle", __FUNCTION__);
        return 0;
    }

    return p_cb->state;
}

/*****************************************************************************
**
** Function     btif_sm_dispatch
**
** Description  Dispatches the 'event' along with 'data' to the current state handler
**
** Returns      BT_STATUS_SUCCESS on success
**              BT_STATUS_UNHANDLED if event was not processed
**              BT_STATUS_FAIL otherwise
**
******************************************************************************/
bt_status_t btif_sm_dispatch(btif_sm_handle_t handle, btif_sm_event_t event,
                                void *data)
{
    bt_status_t status = BT_STATUS_SUCCESS;

    btif_sm_cb_t *p_cb = (btif_sm_cb_t*)handle;

    if (p_cb == NULL)
    {
        BTIF_TRACE_ERROR1("%s : Invalid handle", __FUNCTION__);
        return BT_STATUS_FAIL;
    }

    if (p_cb->p_handlers[p_cb->state](event, data) == FALSE)
        return BT_STATUS_UNHANDLED;

    return status;
}

/*****************************************************************************
**
** Function     btif_sm_change_state
**
** Description  Make a transition to the new 'state'. The 'BTIF_SM_EXIT_EVT'
**              shall be invoked before exiting the current state. The
**              'BTIF_SM_ENTER_EVT' shall be invoked before entering the new state
**
** Returns      BT_STATUS_SUCCESS on success
**              BT_STATUS_UNHANDLED if event was not processed
**              BT_STATUS_FAIL otherwise
**
******************************************************************************/
bt_status_t btif_sm_change_state(btif_sm_handle_t handle, btif_sm_state_t state)
{
    bt_status_t status = BT_STATUS_SUCCESS;
    btif_sm_cb_t *p_cb = (btif_sm_cb_t*)handle;

    if (p_cb == NULL)
    {
        BTIF_TRACE_ERROR1("%s : Invalid handle", __FUNCTION__);
        return BT_STATUS_FAIL;
    }

    /* Send exit event to the current state */
    if (p_cb->p_handlers[p_cb->state](BTIF_SM_EXIT_EVT, NULL) == FALSE)
        status = BT_STATUS_UNHANDLED;

    /* Change to the new state */
    p_cb->state = state;

    /* Send enter event to the new state */
    if (p_cb->p_handlers[p_cb->state](BTIF_SM_ENTER_EVT, NULL) == FALSE)
        status = BT_STATUS_UNHANDLED;

    return status;
}
