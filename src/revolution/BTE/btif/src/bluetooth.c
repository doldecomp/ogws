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

/************************************************************************************
 *
 *  Filename:      bluetooth.c
 *
 *  Description:   Bluetooth HAL implementation
 *
 ***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <hardware/bluetooth.h>
#include <hardware/bt_hf.h>
#include <hardware/bt_av.h>
#include <hardware/bt_sock.h>
#include <hardware/bt_hh.h>
#include <hardware/bt_hl.h>
#include <hardware/bt_pan.h>

#define LOG_NDDEBUG 0
#define LOG_TAG "bluedroid"

#include "btif_api.h"
#include "bt_utils.h"

/************************************************************************************
**  Constants & Macros
************************************************************************************/

#define is_profile(profile, str) ((strlen(str) == strlen(profile)) && strncmp((const char *)profile, str, strlen(str)) == 0)

/************************************************************************************
**  Local type definitions
************************************************************************************/

/************************************************************************************
**  Static variables
************************************************************************************/

bt_callbacks_t *bt_hal_cbacks = NULL;

/************************************************************************************
**  Static functions
************************************************************************************/

/************************************************************************************
**  Externs
************************************************************************************/

/* list all extended interfaces here */

/* handsfree profile */
extern bthf_interface_t *btif_hf_get_interface();
/* advanced audio profile */
extern btav_interface_t *btif_av_get_interface();
/*rfc l2cap*/
extern btsock_interface_t *btif_sock_get_interface();
/* hid host profile */
extern bthh_interface_t *btif_hh_get_interface();
/* health device profile */
extern bthl_interface_t *btif_hl_get_interface();
/*pan*/
extern btpan_interface_t *btif_pan_get_interface();

/************************************************************************************
**  Functions
************************************************************************************/

static uint8_t interface_ready(void)
{
    /* add checks here that would prevent API calls other than init to be executed */
    if (bt_hal_cbacks == NULL)
        return FALSE;

    return TRUE;
}


/*****************************************************************************
**
**   BLUETOOTH HAL INTERFACE FUNCTIONS
**
*****************************************************************************/

static int init(bt_callbacks_t* callbacks )
{
    ALOGI("init");

    /* sanity check */
    if (interface_ready() == TRUE)
        return BT_STATUS_DONE;

    /* store reference to user callbacks */
    bt_hal_cbacks = callbacks;

    /* add checks for individual callbacks ? */

    bt_utils_init();

    /* init btif */
    btif_init_bluetooth();

    return BT_STATUS_SUCCESS;
}

static int enable( void )
{
    ALOGI("enable");

    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_enable_bluetooth();
}

static int disable(void)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_disable_bluetooth();
}

static void cleanup( void )
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return;

    btif_shutdown_bluetooth();
    bt_utils_cleanup();

    /* hal callbacks reset upon shutdown complete callback */

    return;
}

static int get_adapter_properties(void)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_get_adapter_properties();
}

static int get_adapter_property(bt_property_type_t type)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_get_adapter_property(type);
}

static int set_adapter_property(const bt_property_t *property)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_set_adapter_property(property);
}

int get_remote_device_properties(bt_bdaddr_t *remote_addr)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_get_remote_device_properties(remote_addr);
}

int get_remote_device_property(bt_bdaddr_t *remote_addr, bt_property_type_t type)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_get_remote_device_property(remote_addr, type);
}

int set_remote_device_property(bt_bdaddr_t *remote_addr, const bt_property_t *property)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_set_remote_device_property(remote_addr, property);
}

int get_remote_service_record(bt_bdaddr_t *remote_addr, bt_uuid_t *uuid)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_get_remote_service_record(remote_addr, uuid);
}

int get_remote_services(bt_bdaddr_t *remote_addr)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_get_remote_services(remote_addr);
}

static int start_discovery(void)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_start_discovery();
}

static int cancel_discovery(void)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_cancel_discovery();
}

static int create_bond(const bt_bdaddr_t *bd_addr)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_create_bond(bd_addr);
}

static int cancel_bond(const bt_bdaddr_t *bd_addr)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_cancel_bond(bd_addr);
}

static int remove_bond(const bt_bdaddr_t *bd_addr)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_remove_bond(bd_addr);
}

static int pin_reply(const bt_bdaddr_t *bd_addr, uint8_t accept,
                 uint8_t pin_len, bt_pin_code_t *pin_code)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_pin_reply(bd_addr, accept, pin_len, pin_code);
}

static int ssp_reply(const bt_bdaddr_t *bd_addr, bt_ssp_variant_t variant,
                       uint8_t accept, uint32_t passkey)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_ssp_reply(bd_addr, variant, accept, passkey);
}

static const void* get_profile_interface (const char *profile_id)
{
    ALOGI("get_profile_interface %s", profile_id);

    /* sanity check */
    if (interface_ready() == FALSE)
        return NULL;

    /* check for supported profile interfaces */
    if (is_profile(profile_id, BT_PROFILE_HANDSFREE_ID))
        return btif_hf_get_interface();

    if (is_profile(profile_id, BT_PROFILE_SOCKETS_ID))
        return btif_sock_get_interface();

    if (is_profile(profile_id, BT_PROFILE_PAN_ID))
        return btif_pan_get_interface();

    if (is_profile(profile_id, BT_PROFILE_ADVANCED_AUDIO_ID))
        return btif_av_get_interface();

    if (is_profile(profile_id, BT_PROFILE_HIDHOST_ID))
        return btif_hh_get_interface();

    if (is_profile(profile_id, BT_PROFILE_HEALTH_ID))
        return btif_hl_get_interface();
    return NULL;
}

int dut_mode_configure(uint8_t enable)
{
    ALOGI("dut_mode_configure");

    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dut_mode_configure(enable);
}

int dut_mode_send(uint16_t opcode, uint8_t* buf, uint8_t len)
{
    ALOGI("dut_mode_send");

    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dut_mode_send(opcode, buf, len);
}
static const bt_interface_t bluetoothInterface = {
    sizeof(bt_interface_t),
    init,
    enable,
    disable,
    cleanup,
    get_adapter_properties,
    get_adapter_property,
    set_adapter_property,
    get_remote_device_properties,
    get_remote_device_property,
    set_remote_device_property,
    get_remote_service_record,
    get_remote_services,
    start_discovery,
    cancel_discovery,
    create_bond,
    remove_bond,
    cancel_bond,
    pin_reply,
    ssp_reply,
    get_profile_interface,
    dut_mode_configure,
    dut_mode_send
};

const bt_interface_t* bluetooth__get_bluetooth_interface ()
{
    /* fixme -- add property to disable bt interface ? */

    return &bluetoothInterface;
}

static int close_bluetooth_stack(struct hw_device_t* device)
{
    cleanup();
    return 0;
}

static int open_bluetooth_stack (const struct hw_module_t* module, char const* name,
struct hw_device_t** abstraction)
{
    bluetooth_device_t *stack = malloc(sizeof(bluetooth_device_t) );
    memset(stack, 0, sizeof(bluetooth_device_t) );
    stack->common.tag = HARDWARE_DEVICE_TAG;
    stack->common.version = 0;
    stack->common.module = (struct hw_module_t*)module;
    stack->common.close = close_bluetooth_stack;
    stack->get_bluetooth_interface = bluetooth__get_bluetooth_interface;
    *abstraction = (struct hw_device_t*)stack;
    return 0;
}


static struct hw_module_methods_t bt_stack_module_methods = {
    .open = open_bluetooth_stack,
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = BT_HARDWARE_MODULE_ID,
    .name = "Bluetooth Stack",
    .author = "The Android Open Source Project",
    .methods = &bt_stack_module_methods
};

