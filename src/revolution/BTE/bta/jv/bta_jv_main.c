/******************************************************************************
 *
 *  Copyright (C) 2012 Broadcom Corporation
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
 *  This is the main implementation file for the BTA Java I/F
 *
 ******************************************************************************/

#include "bta_api.h"
#include "bta_sys.h"
#include "bta_jv_api.h"
#include "bta_jv_int.h"

/*****************************************************************************
** Constants and types
*****************************************************************************/

#if BTA_DYNAMIC_MEMORY == FALSE
tBTA_JV_CB bta_jv_cb;
#endif

/* state machine action enumeration list */
#define BTA_JV_NUM_ACTIONS  (BTA_JV_MAX_INT_EVT & 0x00ff)

/* type for action functions */
typedef void (*tBTA_JV_ACTION)(tBTA_JV_MSG *p_data);

/* action function list */
const tBTA_JV_ACTION bta_jv_action[] =
{
    bta_jv_enable,                  /* BTA_JV_API_ENABLE_EVT */
    bta_jv_disable,                 /* BTA_JV_API_DISABLE_EVT */
    bta_jv_set_discoverability,     /* BTA_JV_API_SET_DISCOVERABILITY_EVT */
    bta_jv_get_local_device_addr,   /* BTA_JV_API_GET_LOCAL_DEVICE_ADDR_EVT */
    bta_jv_get_local_device_name,   /* BTA_JV_API_GET_LOCAL_DEVICE_NAME_EVT */
    bta_jv_get_remote_device_name,  /* BTA_JV_API_GET_REMOTE_DEVICE_NAME_EVT */
    bta_jv_set_service_class,       /* BTA_JV_API_SET_SERVICE_CLASS_EVT */
    bta_jv_set_encryption,          /* BTA_JV_API_SET_ENCRYPTION_EVT */
    bta_jv_get_scn,                 /* BTA_JV_API_GET_SCN_EVT */
    bta_jv_free_scn,                /* BTA_JV_API_FREE_SCN_EVT */
    bta_jv_start_discovery,         /* BTA_JV_API_START_DISCOVERY_EVT */
    bta_jv_cancel_discovery,        /* BTA_JV_API_CANCEL_DISCOVERY_EVT */
    bta_jv_get_services_length,     /* BTA_JV_API_GET_SERVICES_LENGTH_EVT */
    bta_jv_service_select,          /* BTA_JV_API_SERVICE_SELECT_EVT */
    bta_jv_create_record,           /* BTA_JV_API_CREATE_RECORD_EVT */
    bta_jv_update_record,           /* BTA_JV_API_UPDATE_RECORD_EVT */
    bta_jv_add_attribute,           /* BTA_JV_API_ADD_ATTRIBUTE_EVT */
    bta_jv_delete_attribute,        /* BTA_JV_API_DELETE_ATTRIBUTE_EVT */
    bta_jv_delete_record,           /* BTA_JV_API_DELETE_RECORD_EVT */
    bta_jv_l2cap_connect,           /* BTA_JV_API_L2CAP_CONNECT_EVT */
    bta_jv_l2cap_close,             /* BTA_JV_API_L2CAP_CLOSE_EVT */
    bta_jv_l2cap_start_server,      /* BTA_JV_API_L2CAP_START_SERVER_EVT */
    bta_jv_l2cap_stop_server,       /* BTA_JV_API_L2CAP_STOP_SERVER_EVT */
    bta_jv_l2cap_read,              /* BTA_JV_API_L2CAP_READ_EVT */
    bta_jv_l2cap_write,             /* BTA_JV_API_L2CAP_WRITE_EVT */
    bta_jv_rfcomm_connect,          /* BTA_JV_API_RFCOMM_CONNECT_EVT */
    bta_jv_rfcomm_close,            /* BTA_JV_API_RFCOMM_CLOSE_EVT */
    bta_jv_rfcomm_start_server,     /* BTA_JV_API_RFCOMM_START_SERVER_EVT */
    bta_jv_rfcomm_stop_server,      /* BTA_JV_API_RFCOMM_STOP_SERVER_EVT */
    bta_jv_rfcomm_read,             /* BTA_JV_API_RFCOMM_READ_EVT */
    bta_jv_rfcomm_write             /* BTA_JV_API_RFCOMM_WRITE_EVT */
};

/*******************************************************************************
**
** Function         bta_jv_sm_execute
**
** Description      State machine event handling function for JV
**
**
** Returns          void
**
*******************************************************************************/
BOOLEAN bta_jv_sm_execute(BT_HDR *p_msg)
{
    BOOLEAN ret = FALSE;
    UINT16 action = (p_msg->event & 0x00ff);
    /* execute action functions */

    if(action < BTA_JV_NUM_ACTIONS)
    {
        (*bta_jv_action[action])((tBTA_JV_MSG*)p_msg);
        ret = TRUE;
    }

    return(ret);
}
