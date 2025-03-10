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

#ifndef BTIF_HH_H
#define BTIF_HH_H

#include <hardware/bluetooth.h>
#include <hardware/bt_hh.h>
#include <stdint.h>
#include "bta_hh_api.h"

/*******************************************************************************
**  Constants & Macros
********************************************************************************/

#define BTIF_HH_MAX_HID         8
#define BTIF_HH_MAX_ADDED_DEV   32

#define BTIF_HH_MAX_KEYSTATES            3
#define BTIF_HH_KEYSTATE_MASK_NUMLOCK    0x01
#define BTIF_HH_KEYSTATE_MASK_CAPSLOCK   0x02
#define BTIF_HH_KEYSTATE_MASK_SCROLLLOCK 0x04


/*******************************************************************************
**  Type definitions and return values
********************************************************************************/

typedef enum
{
    BTIF_HH_DISABLED =   0,
    BTIF_HH_ENABLED,
    BTIF_HH_DISABLING,
    BTIF_HH_DEV_UNKNOWN,
    BTIF_HH_DEV_CONNECTING,
    BTIF_HH_DEV_CONNECTED,
    BTIF_HH_DEV_DISCONNECTED
} BTIF_HH_STATUS;

typedef struct
{
    bthh_connection_state_t       dev_status;
    UINT8                         dev_handle;
    bt_bdaddr_t                   bd_addr;
    tBTA_HH_ATTR_MASK             attr_mask;
    UINT8                         sub_class;
    UINT8                         app_id;
    int                           fd;
    BT_HDR                        *p_buf;
} btif_hh_device_t;

/* Control block to maintain properties of devices */
typedef struct
{
    UINT8             dev_handle;
    bt_bdaddr_t       bd_addr;
    tBTA_HH_ATTR_MASK attr_mask;
} btif_hh_added_device_t;

/**
 * BTIF-HH control block to maintain added devices and currently
 * connected hid devices
 */
typedef struct
{
    BTIF_HH_STATUS          status;
    btif_hh_device_t        devices[BTIF_HH_MAX_HID];
    UINT32                  device_num;
    btif_hh_added_device_t  added_devices[BTIF_HH_MAX_ADDED_DEV];
    btif_hh_device_t        *p_curr_dev;
} btif_hh_cb_t;


/*******************************************************************************
**  Functions
********************************************************************************/

extern btif_hh_cb_t btif_hh_cb;

extern btif_hh_device_t *btif_hh_find_connected_dev_by_handle(UINT8 handle);
extern void btif_hh_remove_device(bt_bdaddr_t bd_addr);
extern bt_status_t btif_hh_virtual_unplug(bt_bdaddr_t *bd_addr);
extern void btif_hh_disconnect(bt_bdaddr_t *bd_addr);

BOOLEAN btif_hh_add_added_dev(bt_bdaddr_t bd_addr, tBTA_HH_ATTR_MASK attr_mask);

#endif
