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

/******************************************************************************
 *
 *  Filename:      bt_hw.c
 *
 *  Description:   Bluedroid libbt-vendor callback functions
 *
 ******************************************************************************/

#define LOG_TAG "bt_hw"

#include <dlfcn.h>
#include <utils/Log.h>
#include <pthread.h>
#include "bt_vendor_lib.h"
#include "bt_hci_bdroid.h"
#include "hci.h"
#include "userial.h"

/******************************************************************************
**  Externs
******************************************************************************/

extern tHCI_IF *p_hci_if;
void lpm_vnd_cback(uint8_t vnd_result);

/******************************************************************************
**  Variables
******************************************************************************/

bt_vendor_interface_t *bt_vnd_if=NULL;

/******************************************************************************
**  Functions
******************************************************************************/

/******************************************************************************
**
** Function         fwcfg_cb
**
** Description      HOST/CONTROLLER VENDOR LIB CALLBACK API - This function is
**                  called when the libbt-vendor completed firmware
**                  configuration process
**
** Returns          None
**
******************************************************************************/
static void fwcfg_cb(bt_vendor_op_result_t result)
{
    bt_hc_postload_result_t status = (result == BT_VND_OP_RESULT_SUCCESS) ? \
                                     BT_HC_PRELOAD_SUCCESS : BT_HC_PRELOAD_FAIL;

    if (bt_hc_cbacks)
        bt_hc_cbacks->preload_cb(NULL, status);
}

/******************************************************************************
**
** Function         scocfg_cb
**
** Description      HOST/CONTROLLER VENDOR LIB CALLBACK API - This function is
**                  called when the libbt-vendor completed vendor specific SCO
**                  configuration process
**
** Returns          None
**
******************************************************************************/
static void scocfg_cb(bt_vendor_op_result_t result)
{
    /* Continue rest of postload process*/
    p_hci_if->get_acl_max_len();
}

/******************************************************************************
**
** Function         lpm_vnd_cb
**
** Description      HOST/CONTROLLER VENDOR LIB CALLBACK API - This function is
**                  called back from the libbt-vendor to indicate the result of
**                  previous LPM enable/disable request
**
** Returns          None
**
******************************************************************************/
static void lpm_vnd_cb(bt_vendor_op_result_t result)
{
    uint8_t status = (result == BT_VND_OP_RESULT_SUCCESS) ? 0 : 1;

    lpm_vnd_cback(status);
}

/******************************************************************************
**
** Function         alloc
**
** Description      HOST/CONTROLLER VENDOR LIB CALLOUT API - This function is
**                  called from the libbt-vendor to request for data buffer
**                  allocation
**
** Returns          NULL / pointer to allocated buffer
**
******************************************************************************/
static void *alloc(int size)
{
    HC_BT_HDR *p_hdr = NULL;

    if (bt_hc_cbacks)
        p_hdr = (HC_BT_HDR *) bt_hc_cbacks->alloc(size);

    return (p_hdr);
}

/******************************************************************************
**
** Function         dealloc
**
** Description      HOST/CONTROLLER VENDOR LIB CALLOUT API - This function is
**                  called from the libbt-vendor to release the data buffer
**                  allocated through the alloc call earlier
**
** Returns          None
**
******************************************************************************/
static void dealloc(void *p_buf)
{
    HC_BT_HDR *p_hdr = (HC_BT_HDR *) p_buf;

    if (bt_hc_cbacks)
        bt_hc_cbacks->dealloc((TRANSAC) p_buf, (char *) (p_hdr+1));
}

/******************************************************************************
**
** Function         xmit_cb
**
** Description      HOST/CONTROLLER VEDNOR LIB CALLOUT API - This function is
**                  called from the libbt-vendor in order to send a prepared
**                  HCI command packet through HCI transport TX function.
**
** Returns          TRUE/FALSE
**
******************************************************************************/
static uint8_t xmit_cb(uint16_t opcode, void *p_buf, tINT_CMD_CBACK p_cback)
{
    return p_hci_if->send_int_cmd(opcode, (HC_BT_HDR *)p_buf, p_cback);
}

/*****************************************************************************
**   The libbt-vendor Callback Functions Table
*****************************************************************************/
static const bt_vendor_callbacks_t vnd_callbacks = {
    sizeof(bt_vendor_callbacks_t),
    fwcfg_cb,
    scocfg_cb,
    lpm_vnd_cb,
    alloc,
    dealloc,
    xmit_cb
};

/******************************************************************************
**
** Function         init_vnd_if
**
** Description      Initialize vendor lib interface
**
** Returns          None
**
******************************************************************************/
void init_vnd_if(unsigned char *local_bdaddr)
{
    void *dlhandle;

    dlhandle = dlopen("libbt-vendor.so", RTLD_NOW);
    if (!dlhandle)
    {
        ALOGE("!!! Failed to load libbt-vendor.so !!!");
        return;
    }

    bt_vnd_if = (bt_vendor_interface_t *) dlsym(dlhandle, "BLUETOOTH_VENDOR_LIB_INTERFACE");
    if (!bt_vnd_if)
    {
        ALOGE("!!! Failed to get bt vendor interface !!!");
        return;
    }

    bt_vnd_if->init(&vnd_callbacks, local_bdaddr);
}

