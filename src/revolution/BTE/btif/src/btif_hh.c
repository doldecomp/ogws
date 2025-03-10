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
 *  Filename:      btif_hh.c
 *
 *  Description:   HID Host Profile Bluetooth Interface
 *
 *
 ***********************************************************************************/
#include <hardware/bluetooth.h>
#include <hardware/bt_hh.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LOG_TAG "BTIF_HH"

#include "bta_api.h"
#include "bta_hh_api.h"
#include "bd.h"
#include "btif_storage.h"

#include "btif_common.h"
#include "btif_util.h"
#include "btif_hh.h"
#include "gki.h"
#include "l2c_api.h"


#define BTIF_HH_APP_ID_MI       0x01
#define BTIF_HH_APP_ID_KB       0x02

#define COD_HID_KEYBOARD  0x0540
#define COD_HID_POINTING  0x0580
#define COD_HID_COMBO     0x05C0

#define KEYSTATE_FILEPATH "/data/misc/bluedroid/bt_hh_ks" //keep this in sync with HID host jni

#define HID_REPORT_CAPSLOCK   0x39
#define HID_REPORT_NUMLOCK    0x53
#define HID_REPORT_SCROLLLOCK 0x47

//For Apple Magic Mouse
#define MAGICMOUSE_VENDOR_ID 0x05ac
#define MAGICMOUSE_PRODUCT_ID 0x030d

#define LOGITECH_KB_MX5500_VENDOR_ID  0x046D
#define LOGITECH_KB_MX5500_PRODUCT_ID 0xB30B

extern const int BT_UID;
extern const int BT_GID;
static int btif_hh_prev_keyevents=0; //The previous key events
static int btif_hh_keylockstates=0; //The current key state of each key

#define BTIF_HH_ID_1        0
#define BTIF_HH_DEV_DISCONNECTED 3


#ifndef BTUI_HH_SECURITY
#define BTUI_HH_SECURITY (BTA_SEC_AUTHENTICATE | BTA_SEC_ENCRYPT)
#endif

#ifndef BTUI_HH_MOUSE_SECURITY
#define BTUI_HH_MOUSE_SECURITY (BTA_SEC_NONE)
#endif

/* HH request events */
typedef enum
{
    BTIF_HH_CONNECT_REQ_EVT = 0,
    BTIF_HH_DISCONNECT_REQ_EVT,
    BTIF_HH_VUP_REQ_EVT
} btif_hh_req_evt_t;


/************************************************************************************
**  Constants & Macros
************************************************************************************/
#define BTIF_HH_SERVICES    (BTA_HID_SERVICE_MASK)



/************************************************************************************
**  Local type definitions
************************************************************************************/

typedef struct hid_kb_list
{
    UINT16 product_id;
    UINT16 version_id;
    char*  kb_name;
} tHID_KB_LIST;

/************************************************************************************
**  Static variables
************************************************************************************/
btif_hh_cb_t btif_hh_cb;

static bthh_callbacks_t *bt_hh_callbacks = NULL;

/* List of HID keyboards for which the NUMLOCK state needs to be
 * turned ON by default. Add devices to this list to apply the
 * NUMLOCK state toggle on fpr first connect.*/
static tHID_KB_LIST hid_kb_numlock_on_list[] =
{
    {LOGITECH_KB_MX5500_PRODUCT_ID,
    LOGITECH_KB_MX5500_VENDOR_ID,
    "Logitech MX5500 Keyboard"}
};


#define CHECK_BTHH_INIT() if (bt_hh_callbacks == NULL)\
    {\
        BTIF_TRACE_WARNING1("BTHH: %s: BTHH not initialized", __FUNCTION__);\
        return BT_STATUS_NOT_READY;\
    }\
    else\
    {\
        BTIF_TRACE_EVENT1("BTHH: %s", __FUNCTION__);\
    }



/************************************************************************************
**  Static functions
************************************************************************************/

/************************************************************************************
**  Externs
************************************************************************************/
extern void bta_hh_co_destroy(int fd);
extern void bta_hh_co_write(int fd, UINT8* rpt, UINT16 len);
extern bt_status_t btif_dm_remove_bond(const bt_bdaddr_t *bd_addr);
extern void bta_hh_co_send_hid_info(btif_hh_device_t *p_dev, char *dev_name, UINT16 vendor_id,
                                    UINT16 product_id, UINT16 version, UINT8 ctry_code,
                                    int dscp_len, UINT8 *p_dscp);
extern BOOLEAN check_cod(const bt_bdaddr_t *remote_bdaddr, uint32_t cod);
extern void btif_dm_cb_remove_bond(bt_bdaddr_t *bd_addr);
extern int  scru_ascii_2_hex(char *p_ascii, int len, UINT8 *p_hex);

/*****************************************************************************
**  Local Function prototypes
*****************************************************************************/
static void set_keylockstate(int keymask, BOOLEAN isSet);
static void toggle_os_keylockstates(int fd, int changedkeystates);
static void sync_lockstate_on_connect(btif_hh_device_t *p_dev);
//static void hh_update_keyboard_lockstates(btif_hh_device_t *p_dev);


/************************************************************************************
**  Functions
************************************************************************************/

static int get_keylockstates()
{
    return btif_hh_keylockstates;
}

static void set_keylockstate(int keymask, BOOLEAN isSet)
{
    if(isSet)
        btif_hh_keylockstates |= keymask;
}

/*******************************************************************************
**
** Function         toggle_os_keylockstates
**
** Description      Function to toggle the keyboard lock states managed by the linux.
**                  This function is used in by two call paths
**                  (1) if the lock state change occurred from an onscreen keyboard,
**                  this function is called to update the lock state maintained
                    for the HID keyboard(s)
**                  (2) if a HID keyboard is disconnected and reconnected,
**                  this function is called to update the lock state maintained
                    for the HID keyboard(s)
** Returns          void
*******************************************************************************/

static void toggle_os_keylockstates(int fd, int changedlockstates)
{
    BTIF_TRACE_EVENT3("%s: fd = %d, changedlockstates = 0x%x",
        __FUNCTION__, fd, changedlockstates);
    UINT8 hidreport[9];
    int reportIndex;
    memset(hidreport,0,9);
    hidreport[0]=1;
    reportIndex=4;

    if (changedlockstates & BTIF_HH_KEYSTATE_MASK_CAPSLOCK) {
        BTIF_TRACE_DEBUG1("%s Setting CAPSLOCK", __FUNCTION__);
        hidreport[reportIndex++] = (UINT8)HID_REPORT_CAPSLOCK;
    }

    if (changedlockstates & BTIF_HH_KEYSTATE_MASK_NUMLOCK)  {
        BTIF_TRACE_DEBUG1("%s Setting NUMLOCK", __FUNCTION__);
        hidreport[reportIndex++] = (UINT8)HID_REPORT_NUMLOCK;
    }

    if (changedlockstates & BTIF_HH_KEYSTATE_MASK_SCROLLLOCK) {
        BTIF_TRACE_DEBUG1("%s Setting SCROLLLOCK", __FUNCTION__);
        hidreport[reportIndex++] = (UINT8) HID_REPORT_SCROLLLOCK;
    }

     BTIF_TRACE_DEBUG4("Writing hidreport #1 to os: "\
        "%s:  %x %x %x", __FUNCTION__,
         hidreport[0], hidreport[1], hidreport[2]);
    BTIF_TRACE_DEBUG4("%s:  %x %x %x", __FUNCTION__,
         hidreport[3], hidreport[4], hidreport[5]);
    BTIF_TRACE_DEBUG4("%s:  %x %x %x", __FUNCTION__,
         hidreport[6], hidreport[7], hidreport[8]);
    bta_hh_co_write(fd , hidreport, sizeof(hidreport));
    usleep(200000);
    memset(hidreport,0,9);
    hidreport[0]=1;
    BTIF_TRACE_DEBUG4("Writing hidreport #2 to os: "\
       "%s:  %x %x %x", __FUNCTION__,
         hidreport[0], hidreport[1], hidreport[2]);
    BTIF_TRACE_DEBUG4("%s:  %x %x %x", __FUNCTION__,
         hidreport[3], hidreport[4], hidreport[5]);
    BTIF_TRACE_DEBUG4("%s:  %x %x %x ", __FUNCTION__,
         hidreport[6], hidreport[7], hidreport[8]);
    bta_hh_co_write(fd , hidreport, sizeof(hidreport));
}

/*******************************************************************************
**
** Function         update_keyboard_lockstates
**
** Description      Sends a report to the keyboard to set the lock states of keys
**
*******************************************************************************/
static void update_keyboard_lockstates(btif_hh_device_t *p_dev)
{
    UINT8 len = 2;  /* reportid + 1 byte report*/
    BD_ADDR* bda;

    /* Set report for other keyboards */
    BTIF_TRACE_EVENT3("%s: setting report on dev_handle %d to 0x%x",
         __FUNCTION__, p_dev->dev_handle, btif_hh_keylockstates);

    if (p_dev->p_buf != NULL) {
        GKI_freebuf(p_dev->p_buf);
    }
    /* Get SetReport buffer */
    p_dev->p_buf = GKI_getbuf((UINT16) (len + BTA_HH_MIN_OFFSET +
        sizeof(BT_HDR)));
    if (p_dev->p_buf != NULL) {
        p_dev->p_buf->len = len;
        p_dev->p_buf->offset = BTA_HH_MIN_OFFSET;

        /* LED status updated by data event */
        UINT8 *pbuf_data  = (UINT8 *)(p_dev->p_buf + 1)
            + p_dev->p_buf->offset;
        pbuf_data[0]=0x01; /*report id */
        pbuf_data[1]=btif_hh_keylockstates; /*keystate*/
        bda = (BD_ADDR*) (&p_dev->bd_addr);
        BTA_HhSendData(p_dev->dev_handle, *bda,
            p_dev->p_buf);
    }
}

/*******************************************************************************
**
** Function         sync_lockstate_on_connect
**
** Description      Function to update the keyboard lock states managed by the OS
**                  when a HID keyboard is connected or disconnected and reconnected
** Returns          void
*******************************************************************************/
static void sync_lockstate_on_connect(btif_hh_device_t *p_dev)
{
    int keylockstates;

    BTIF_TRACE_EVENT1("%s: Syncing keyboard lock states after "\
        "reconnect...",__FUNCTION__);
    /*If the device is connected, update keyboard state */
    update_keyboard_lockstates(p_dev);

    /*Check if the lockstate of caps,scroll,num is set.
     If so, send a report to the kernel
    so the lockstate is in sync */
    keylockstates = get_keylockstates();
    if (keylockstates)
    {
        BTIF_TRACE_DEBUG2("%s: Sending hid report to kernel "\
            "indicating lock key state 0x%x",__FUNCTION__,
            keylockstates);
        usleep(200000);
        toggle_os_keylockstates(p_dev->fd, keylockstates);
    }
    else
    {
        BTIF_TRACE_DEBUG2("%s: NOT sending hid report to kernel "\
            "indicating lock key state 0x%x",__FUNCTION__,
            keylockstates);
    }
}

/*******************************************************************************
**
** Function         btif_hh_find_dev_by_handle
**
** Description      Return the device pointer of the specified device handle
**
** Returns          Device entry pointer in the device table
*******************************************************************************/
static btif_hh_device_t *btif_hh_find_dev_by_handle(UINT8 handle)
{
    UINT32 i;
    // LOGV("%s: handle = %d", __FUNCTION__, handle);
    for (i = 0; i < BTIF_HH_MAX_HID; i++) {
        if (btif_hh_cb.devices[i].dev_status != BTHH_CONN_STATE_UNKNOWN &&
            btif_hh_cb.devices[i].dev_handle == handle)
        {
            return &btif_hh_cb.devices[i];
        }
    }
    return NULL;
}


/*******************************************************************************
**
** Function         btif_hh_find_connected_dev_by_handle
**
** Description      Return the connected device pointer of the specified device handle
**
** Returns          Device entry pointer in the device table
*******************************************************************************/
btif_hh_device_t *btif_hh_find_connected_dev_by_handle(UINT8 handle)
{
    UINT32 i;
    for (i = 0; i < BTIF_HH_MAX_HID; i++) {
        if (btif_hh_cb.devices[i].dev_status == BTHH_CONN_STATE_CONNECTED &&
            btif_hh_cb.devices[i].dev_handle == handle)
        {
            return &btif_hh_cb.devices[i];
        }
    }
    return NULL;
}

/*******************************************************************************
**
** Function         btif_hh_find_dev_by_bda
**
** Description      Return the device pointer of the specified bt_bdaddr_t.
**
** Returns          Device entry pointer in the device table
*******************************************************************************/
static btif_hh_device_t *btif_hh_find_dev_by_bda(bt_bdaddr_t *bd_addr)
{
    UINT32 i;
    for (i = 0; i < BTIF_HH_MAX_HID; i++) {
        if (btif_hh_cb.devices[i].dev_status != BTHH_CONN_STATE_UNKNOWN &&
            memcmp(&(btif_hh_cb.devices[i].bd_addr), bd_addr, BD_ADDR_LEN) == 0)
        {
            return &btif_hh_cb.devices[i];
        }
    }
    return NULL;
}

/*******************************************************************************
**
** Function         btif_hh_find_connected_dev_by_bda
**
** Description      Return the connected device pointer of the specified bt_bdaddr_t.
**
** Returns          Device entry pointer in the device table
*******************************************************************************/
static btif_hh_device_t *btif_hh_find_connected_dev_by_bda(bt_bdaddr_t *bd_addr)
{
    UINT32 i;
    for (i = 0; i < BTIF_HH_MAX_HID; i++) {
        if (btif_hh_cb.devices[i].dev_status == BTHH_CONN_STATE_CONNECTED &&
            memcmp(&(btif_hh_cb.devices[i].bd_addr), bd_addr, BD_ADDR_LEN) == 0)
        {
            return &btif_hh_cb.devices[i];
        }
    }
    return NULL;
}

/*******************************************************************************
**
** Function         btif_hh_add_added_dev
**
** Description      Add a new device to the added device list.
**
** Returns          TRUE if add successfully, otherwise FALSE.
*******************************************************************************/
BOOLEAN btif_hh_add_added_dev(bt_bdaddr_t bda, tBTA_HH_ATTR_MASK attr_mask)
{
    int i;
    for (i = 0; i < BTIF_HH_MAX_ADDED_DEV; i++) {
        if (memcmp(&(btif_hh_cb.added_devices[i].bd_addr), &bda, BD_ADDR_LEN) == 0) {
            BTIF_TRACE_WARNING6(" Device %02X:%02X:%02X:%02X:%02X:%02X already added",
                  bda.address[0], bda.address[1], bda.address[2], bda.address[3], bda.address[4], bda.address[5]);
            return FALSE;
        }
    }
    for (i = 0; i < BTIF_HH_MAX_ADDED_DEV; i++) {
        if (btif_hh_cb.added_devices[i].bd_addr.address[0] == 0 &&
            btif_hh_cb.added_devices[i].bd_addr.address[1] == 0 &&
            btif_hh_cb.added_devices[i].bd_addr.address[2] == 0 &&
            btif_hh_cb.added_devices[i].bd_addr.address[3] == 0 &&
            btif_hh_cb.added_devices[i].bd_addr.address[4] == 0 &&
            btif_hh_cb.added_devices[i].bd_addr.address[5] == 0)
        {
            BTIF_TRACE_WARNING6(" Added device %02X:%02X:%02X:%02X:%02X:%02X",
                  bda.address[0], bda.address[1], bda.address[2], bda.address[3], bda.address[4], bda.address[5]);
            memcpy(&(btif_hh_cb.added_devices[i].bd_addr), &bda, BD_ADDR_LEN);
            btif_hh_cb.added_devices[i].dev_handle = BTA_HH_INVALID_HANDLE;
            btif_hh_cb.added_devices[i].attr_mask  = attr_mask;
            return TRUE;
        }
    }

    BTIF_TRACE_WARNING1("%s: Error, out of space to add device",__FUNCTION__);
    return FALSE;
}

/*******************************************************************************
 **
 ** Function         btif_hh_remove_device
 **
 ** Description      Remove an added device from the stack.
 **
 ** Returns          void
 *******************************************************************************/
void btif_hh_remove_device(bt_bdaddr_t bd_addr)
{
    int                    i;
    btif_hh_device_t       *p_dev;
    btif_hh_added_device_t *p_added_dev;

    ALOGI("%s: bda = %02x:%02x:%02x:%02x:%02x:%02x", __FUNCTION__,
         bd_addr.address[0], bd_addr.address[1], bd_addr.address[2], bd_addr.address[3], bd_addr.address[4], bd_addr.address[5]);

    for (i = 0; i < BTIF_HH_MAX_ADDED_DEV; i++) {
        p_added_dev = &btif_hh_cb.added_devices[i];
        if (memcmp(&(p_added_dev->bd_addr),&bd_addr, 6) == 0) {
            BTA_HhRemoveDev(p_added_dev->dev_handle);
            btif_storage_remove_hid_info(&(p_added_dev->bd_addr));
            memset(&(p_added_dev->bd_addr), 0, 6);
            p_added_dev->dev_handle = BTA_HH_INVALID_HANDLE;
            break;
        }
    }

    p_dev = btif_hh_find_dev_by_bda(&bd_addr);
    if (p_dev == NULL) {
        BTIF_TRACE_WARNING6(" Oops, can't find device [%02x:%02x:%02x:%02x:%02x:%02x]",
             bd_addr.address[0], bd_addr.address[1], bd_addr.address[2], bd_addr.address[3], bd_addr.address[4], bd_addr.address[5]);
        return;
    }

    p_dev->dev_status = BTHH_CONN_STATE_UNKNOWN;
    p_dev->dev_handle = BTA_HH_INVALID_HANDLE;
    if (btif_hh_cb.device_num > 0) {
        btif_hh_cb.device_num--;
    }
    else {
        BTIF_TRACE_WARNING1("%s: device_num = 0", __FUNCTION__);
    }
    if (p_dev->p_buf != NULL) {
        GKI_freebuf(p_dev->p_buf);
        p_dev->p_buf = NULL;
    }
    BTIF_TRACE_DEBUG2("%s: uhid fd = %d", __FUNCTION__, p_dev->fd);
    if (p_dev->fd >= 0) {
        bta_hh_co_destroy(p_dev->fd);
        p_dev->fd = -1;
    }
}


BOOLEAN btif_hh_copy_hid_info(tBTA_HH_DEV_DSCP_INFO* dest , tBTA_HH_DEV_DSCP_INFO* src)
{
    dest->descriptor.dl_len = 0;
    if (src->descriptor.dl_len >0)
    {
        dest->descriptor.dsc_list = (UINT8 *) GKI_getbuf(src->descriptor.dl_len);
        if (dest->descriptor.dsc_list == NULL)
        {
            BTIF_TRACE_WARNING1("%s: Failed to allocate DSCP for CB", __FUNCTION__);
            return FALSE;
        }
    }
    memcpy(dest->descriptor.dsc_list, src->descriptor.dsc_list, src->descriptor.dl_len);
    dest->descriptor.dl_len = src->descriptor.dl_len;
    dest->vendor_id  = src->vendor_id;
    dest->product_id = src->product_id;
    dest->version    = src->version;
    dest->ctry_code  = src->ctry_code;
    return TRUE;
}


/*******************************************************************************
**
** Function         btif_hh_virtual_unplug
**
** Description      Virtual unplug initiated from the BTIF thread context
**                  Special handling for HID mouse-
**
** Returns          void
**
*******************************************************************************/

bt_status_t btif_hh_virtual_unplug(bt_bdaddr_t *bd_addr)
{
    BTIF_TRACE_DEBUG1("%s", __FUNCTION__);
    btif_hh_device_t *p_dev;
    char bd_str[18];
    sprintf(bd_str, "%02X:%02X:%02X:%02X:%02X:%02X",
            bd_addr->address[0],  bd_addr->address[1],  bd_addr->address[2],  bd_addr->address[3],
            bd_addr->address[4], bd_addr->address[5]);
    p_dev = btif_hh_find_dev_by_bda(bd_addr);
    if ((p_dev != NULL) && (p_dev->dev_status == BTHH_CONN_STATE_CONNECTED)
        && (p_dev->attr_mask & HID_VIRTUAL_CABLE))
    {
        BTIF_TRACE_DEBUG1("%s Sending BTA_HH_CTRL_VIRTUAL_CABLE_UNPLUG", __FUNCTION__);
        BTA_HhSendCtrl(p_dev->dev_handle, BTA_HH_CTRL_VIRTUAL_CABLE_UNPLUG);
        return BT_STATUS_SUCCESS;
    }
    else
    {
        BTIF_TRACE_ERROR2("%s: Error, device %s not opened.", __FUNCTION__, bd_str);
        return BT_STATUS_FAIL;
    }
}

/*******************************************************************************
**
** Function         btif_hh_connect
**
** Description      connection initiated from the BTIF thread context
**
** Returns          int status
**
*******************************************************************************/

bt_status_t btif_hh_connect(bt_bdaddr_t *bd_addr)
{
    btif_hh_device_t *dev;
    btif_hh_added_device_t *added_dev = NULL;
    char bda_str[20];
    int i;
    BD_ADDR *bda = (BD_ADDR*)bd_addr;
    tBTA_HH_CONN conn;
    CHECK_BTHH_INIT();
    dev = btif_hh_find_dev_by_bda(bd_addr);
    BTIF_TRACE_DEBUG0("Connect _hh");
    sprintf(bda_str, "%02X:%02X:%02X:%02X:%02X:%02X",
            (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);
    if (dev == NULL && btif_hh_cb.device_num >= BTIF_HH_MAX_HID) {
        // No space for more HID device now.
         BTIF_TRACE_WARNING2("%s: Error, exceeded the maximum supported HID device number %d",
             __FUNCTION__, BTIF_HH_MAX_HID);
        return BT_STATUS_FAIL;
    }

    for (i = 0; i < BTIF_HH_MAX_ADDED_DEV; i++) {
        if (memcmp(&(btif_hh_cb.added_devices[i].bd_addr), bd_addr, BD_ADDR_LEN) == 0) {
            added_dev = &btif_hh_cb.added_devices[i];
             BTIF_TRACE_WARNING3("%s: Device %s already added, attr_mask = 0x%x",
                 __FUNCTION__, bda_str, added_dev->attr_mask);
        }
    }

    if (added_dev != NULL) {
        if (added_dev->dev_handle == BTA_HH_INVALID_HANDLE) {
            // No space for more HID device now.
            BTIF_TRACE_ERROR2("%s: Error, device %s added but addition failed", __FUNCTION__, bda_str);
            memset(&(added_dev->bd_addr), 0, 6);
            added_dev->dev_handle = BTA_HH_INVALID_HANDLE;
            return BT_STATUS_FAIL;
        }
    }
    if (added_dev == NULL ||
        (added_dev->attr_mask & HID_NORMALLY_CONNECTABLE) != 0 ||
        (added_dev->attr_mask & HID_RECONN_INIT) == 0)
    {
        tBTA_SEC sec_mask = BTUI_HH_SECURITY;
        btif_hh_cb.status = BTIF_HH_DEV_CONNECTING;
        BD_ADDR *bda = (BD_ADDR*)bd_addr;
        BTA_HhOpen(*bda, BTA_HH_PROTO_RPT_MODE, sec_mask);
    }
    else {
        // This device shall be connected from the host side.
        BTIF_TRACE_ERROR2("%s: Error, device %s can only be reconnected from device side",
             __FUNCTION__, bda_str);
        //TODO
       /* if ((remote_class & BT_DEV_CLASS_MASK) == BT_DEV_CLASS_HID_POINTING) {
            //SIG_HH_CONNECTION, *bda, HH_CONN_STATUS_FAILED_MOUSE_FROM_HOST);
        }
        else {
           // SIG_HH_CONNECTION, *bda, HH_CONN_STATUS_FAILED_KBD_FROM_HOST);
        }*/
        return BT_STATUS_FAIL;

    }
    HAL_CBACK(bt_hh_callbacks, connection_state_cb, bd_addr, BTHH_CONN_STATE_CONNECTING);
    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_hh_disconnect
**
** Description      disconnection initiated from the BTIF thread context
**
** Returns          void
**
*******************************************************************************/

void btif_hh_disconnect(bt_bdaddr_t *bd_addr)
{
    BD_ADDR *bda = (BD_ADDR*)bd_addr;
    btif_hh_device_t *p_dev;
    p_dev = btif_hh_find_connected_dev_by_bda(bd_addr);
    if (p_dev != NULL)
    {
        BTA_HhClose(p_dev->dev_handle);
    }
    else
        BTIF_TRACE_DEBUG1("%s-- Error: device not connected:",__FUNCTION__);
}

/*****************************************************************************
**   Section name (Group of functions)
*****************************************************************************/

/*****************************************************************************
**
**   btif hh api functions (no context switch)
**
*****************************************************************************/


/*******************************************************************************
**
** Function         btif_hh_upstreams_evt
**
** Description      Executes HH UPSTREAMS events in btif context
**
** Returns          void
**
*******************************************************************************/
static void btif_hh_upstreams_evt(UINT16 event, char* p_param)
{
    tBTA_HH *p_data = (tBTA_HH *)p_param;
    bdstr_t bdstr;
    btif_hh_device_t *p_dev = NULL;
    int i;
    int len, tmplen;

    BTIF_TRACE_DEBUG2("%s: event=%s", __FUNCTION__, dump_hh_event(event));

    switch (event)
    {
        case BTA_HH_ENABLE_EVT:
            BTIF_TRACE_DEBUG2("%s: BTA_HH_ENABLE_EVT: status =%d",__FUNCTION__, p_data->status);
            if (p_data->status == BTA_HH_OK) {
                btif_hh_cb.status = BTIF_HH_ENABLED;
                BTIF_TRACE_DEBUG1("%s--Loading added devices",__FUNCTION__);
                /* Add hid descriptors for already bonded hid devices*/
                btif_storage_load_bonded_hid_info();
            }
            else {
                btif_hh_cb.status = BTIF_HH_DISABLED;
                BTIF_TRACE_WARNING1("BTA_HH_ENABLE_EVT: Error, HH enabling failed, status = %d", p_data->status);
            }
            break;

        case BTA_HH_DISABLE_EVT:
            btif_hh_cb.status = BTIF_HH_DISABLED;
            if (p_data->status == BTA_HH_OK) {
                int i;
                //Clear the control block
                memset(&btif_hh_cb, 0, sizeof(btif_hh_cb));
                for (i = 0; i < BTIF_HH_MAX_HID; i++){
                    btif_hh_cb.devices[i].dev_status = BTHH_CONN_STATE_UNKNOWN;
                }
            }
            else
                BTIF_TRACE_WARNING1("BTA_HH_DISABLE_EVT: Error, HH disabling failed, status = %d", p_data->status);
            break;

        case BTA_HH_OPEN_EVT:
            BTIF_TRACE_WARNING3("%s: BTA_HH_OPN_EVT: handle=%d, status =%d",__FUNCTION__, p_data->conn.handle, p_data->conn.status);
            if (p_data->conn.status == BTA_HH_OK) {
                p_dev = btif_hh_find_connected_dev_by_handle(p_data->conn.handle);
                if (p_dev == NULL) {
                    BTIF_TRACE_WARNING1("BTA_HH_OPEN_EVT: Error, cannot find device with handle %d", p_data->conn.handle);
                    btif_hh_cb.status = BTIF_HH_DEV_DISCONNECTED;
                    // The connect request must come from device side and exceeded the connected
                                   // HID device number.
                    BTA_HhClose(p_data->conn.handle);
                    HAL_CBACK(bt_hh_callbacks, connection_state_cb, (bt_bdaddr_t*) &p_data->conn.bda,BTHH_CONN_STATE_DISCONNECTED);
                }
                else if (p_dev->fd < 0) {
                    BTIF_TRACE_WARNING0("BTA_HH_OPEN_EVT: Error, failed to find the uhid driver...");
                    memcpy(&(p_dev->bd_addr), p_data->conn.bda, BD_ADDR_LEN);
                    //remove the connection  and then try again to reconnect from the mouse side to recover
                    btif_hh_cb.status = BTIF_HH_DEV_DISCONNECTED;
                    BTA_HhClose(p_data->conn.handle);
                }
                else {
                    BTIF_TRACE_WARNING1("BTA_HH_OPEN_EVT: Found device...Getting dscp info for handle ... %d",p_data->conn.handle);
                    memcpy(&(p_dev->bd_addr), p_data->conn.bda, BD_ADDR_LEN);
                    btif_hh_cb.status = BTIF_HH_DEV_CONNECTED;
                    BTA_HhSetIdle(p_data->conn.handle, 0);
                    btif_hh_cb.p_curr_dev = btif_hh_find_connected_dev_by_handle(p_data->conn.handle);
                    BTA_HhGetDscpInfo(p_data->conn.handle);
                    p_dev->dev_status = BTHH_CONN_STATE_CONNECTED;
                    HAL_CBACK(bt_hh_callbacks, connection_state_cb,&(p_dev->bd_addr), p_dev->dev_status);
                }
            }
            else {
                bt_bdaddr_t *bdaddr = (bt_bdaddr_t*)p_data->conn.bda;
                HAL_CBACK(bt_hh_callbacks, connection_state_cb, (bt_bdaddr_t*) &p_data->conn.bda,BTHH_CONN_STATE_DISCONNECTED);
                btif_hh_cb.status = BTIF_HH_DEV_DISCONNECTED;
            }
            break;
        case BTA_HH_CLOSE_EVT:
            BTIF_TRACE_DEBUG2("BTA_HH_CLOSE_EVT: status = %d, handle = %d",
            p_data->dev_status.status, p_data->dev_status.handle);
            p_dev = btif_hh_find_connected_dev_by_handle(p_data->dev_status.handle);
            if (p_dev != NULL) {
                BTIF_TRACE_DEBUG2("%s: uhid fd = %d", __FUNCTION__, p_dev->fd);
                if (p_dev->fd >= 0){
                    UINT8 hidreport[9];
                    memset(hidreport,0,9);
                    hidreport[0]=1;
                    bta_hh_co_write(p_dev->fd , hidreport, sizeof(hidreport));
                }
                btif_hh_cb.status = BTIF_HH_DEV_DISCONNECTED;
                p_dev->dev_status = BTHH_CONN_STATE_DISCONNECTED;
                HAL_CBACK(bt_hh_callbacks, connection_state_cb,&(p_dev->bd_addr), p_dev->dev_status);
                BTIF_TRACE_DEBUG2("%s: Closing uhid fd = %d", __FUNCTION__, p_dev->fd);
                bta_hh_co_destroy(p_dev->fd);
                p_dev->fd = -1;
            }
            else {
                BTIF_TRACE_WARNING1("Error: cannot find device with handle %d", p_data->dev_status.handle);
            }
            break;
        case BTA_HH_GET_RPT_EVT:
            BTIF_TRACE_DEBUG2("BTA_HH_GET_RPT_EVT: status = %d, handle = %d",
                 p_data->hs_data.status, p_data->hs_data.handle);
            p_dev = btif_hh_find_connected_dev_by_handle(p_data->conn.handle);
            HAL_CBACK(bt_hh_callbacks, get_report_cb,(bt_bdaddr_t*) &(p_dev->bd_addr), (bthh_status_t) p_data->hs_data.status,
                (uint8_t*) p_data->hs_data.rsp_data.p_rpt_data, BT_HDR_SIZE);
            break;

        case BTA_HH_SET_RPT_EVT:
            BTIF_TRACE_DEBUG2("BTA_HH_SET_RPT_EVT: status = %d, handle = %d",
            p_data->dev_status.status, p_data->dev_status.handle);
            p_dev = btif_hh_find_connected_dev_by_handle(p_data->dev_status.handle);
            if (p_dev != NULL && p_dev->p_buf != NULL) {
                BTIF_TRACE_DEBUG0("Freeing buffer..." );
                GKI_freebuf(p_dev->p_buf);
                p_dev->p_buf = NULL;
            }
            break;

        case BTA_HH_GET_PROTO_EVT:
            p_dev = btif_hh_find_connected_dev_by_handle(p_data->dev_status.handle);
            BTIF_TRACE_WARNING4("BTA_HH_GET_PROTO_EVT: status = %d, handle = %d, proto = [%d], %s",
                 p_data->hs_data.status, p_data->hs_data.handle,
                 p_data->hs_data.rsp_data.proto_mode,
                 (p_data->hs_data.rsp_data.proto_mode == BTA_HH_PROTO_RPT_MODE) ? "Report Mode" :
                 (p_data->hs_data.rsp_data.proto_mode == BTA_HH_PROTO_BOOT_MODE) ? "Boot Mode" : "Unsupported");
            HAL_CBACK(bt_hh_callbacks, protocol_mode_cb,(bt_bdaddr_t*) &(p_dev->bd_addr), (bthh_status_t)p_data->hs_data.status,
                             (bthh_protocol_mode_t) p_data->hs_data.rsp_data.proto_mode);
            break;

        case BTA_HH_SET_PROTO_EVT:
            BTIF_TRACE_DEBUG2("BTA_HH_SET_PROTO_EVT: status = %d, handle = %d",
                 p_data->dev_status.status, p_data->dev_status.handle);
            break;

        case BTA_HH_GET_IDLE_EVT:
            BTIF_TRACE_DEBUG3("BTA_HH_GET_IDLE_EVT: handle = %d, status = %d, rate = %d",
                 p_data->hs_data.handle, p_data->hs_data.status,
                 p_data->hs_data.rsp_data.idle_rate);
            break;

        case BTA_HH_SET_IDLE_EVT:
            BTIF_TRACE_DEBUG2("BTA_HH_SET_IDLE_EVT: status = %d, handle = %d",
            p_data->dev_status.status, p_data->dev_status.handle);
            break;

        case BTA_HH_GET_DSCP_EVT:
            BTIF_TRACE_WARNING2("BTA_HH_GET_DSCP_EVT: status = %d, handle = %d",
                p_data->dev_status.status, p_data->dev_status.handle);
                len = p_data->dscp_info.descriptor.dl_len;
                BTIF_TRACE_DEBUG1("BTA_HH_GET_DSCP_EVT: len = %d", len);
            p_dev = btif_hh_cb.p_curr_dev;
            if (p_dev == NULL) {
                BTIF_TRACE_ERROR0("BTA_HH_GET_DSCP_EVT: No HID device is currently connected");
                return;
            }
            if (p_dev->fd < 0) {
                ALOGE("BTA_HH_GET_DSCP_EVT: Error, failed to find the uhid driver...");
                return;
            }
            {
                char *cached_name = NULL;
                char name[] = "Broadcom Bluetooth HID";
                if (cached_name == NULL) {
                    cached_name = name;
                }

                BTIF_TRACE_WARNING2("%s: name = %s", __FUNCTION__, cached_name);
                bta_hh_co_send_hid_info(p_dev, cached_name,
                    p_data->dscp_info.vendor_id, p_data->dscp_info.product_id,
                    p_data->dscp_info.version,   p_data->dscp_info.ctry_code,
                    len, p_data->dscp_info.descriptor.dsc_list);
                if (btif_hh_add_added_dev(p_dev->bd_addr, p_dev->attr_mask)) {
                    BD_ADDR bda;
                    bdcpy(bda, p_dev->bd_addr.address);
                    tBTA_HH_DEV_DSCP_INFO dscp_info;
                    bt_status_t ret;
                    bdcpy(bda, p_dev->bd_addr.address);
                    btif_hh_copy_hid_info(&dscp_info, &p_data->dscp_info);
                    BTIF_TRACE_DEBUG6("BTA_HH_GET_DSCP_EVT:bda = %02x:%02x:%02x:%02x:%02x:%02x",
                              p_dev->bd_addr.address[0], p_dev->bd_addr.address[1], p_dev->bd_addr.address[2],
                              p_dev->bd_addr.address[3], p_dev->bd_addr.address[4], p_dev->bd_addr.address[5]);
                    BTA_HhAddDev(bda, p_dev->attr_mask,p_dev->sub_class,p_dev->app_id, dscp_info);
                    // write hid info to nvram
                    ret = btif_storage_add_hid_device_info(&(p_dev->bd_addr), p_dev->attr_mask,p_dev->sub_class,p_dev->app_id,
                                                        p_data->dscp_info.vendor_id, p_data->dscp_info.product_id,
                                                        p_data->dscp_info.version,   p_data->dscp_info.ctry_code,
                                                        len, p_data->dscp_info.descriptor.dsc_list);

                    ASSERTC(ret == BT_STATUS_SUCCESS, "storing hid info failed", ret);
                    BTIF_TRACE_WARNING0("BTA_HH_GET_DSCP_EVT: Called add device");

                    //Free buffer created for dscp_info;
                    if (dscp_info.descriptor.dl_len >0 && dscp_info.descriptor.dsc_list != NULL)
                    {
                      GKI_freebuf(dscp_info.descriptor.dsc_list);
                      dscp_info.descriptor.dsc_list = NULL;
                      dscp_info.descriptor.dl_len=0;
                    }
                }
                else {
                    //Device already added.
                    BTIF_TRACE_WARNING1("%s: Device already added ",__FUNCTION__);
                }
                /*Sync HID Keyboard lockstates */
                tmplen = sizeof(hid_kb_numlock_on_list)
                            / sizeof(tHID_KB_LIST);
                for(i = 0; i< tmplen; i++)
                {
                    if(p_data->dscp_info.vendor_id
                        == hid_kb_numlock_on_list[i].version_id &&
                        p_data->dscp_info.product_id
                        == hid_kb_numlock_on_list[i].product_id)
                    {
                        BTIF_TRACE_DEBUG3("%s() idx[%d] Enabling "\
                            "NUMLOCK for device :: %s", __FUNCTION__,
                            i, hid_kb_numlock_on_list[i].kb_name);
                        /* Enable NUMLOCK by default so that numeric
                            keys work from first keyboard connect */
                        set_keylockstate(BTIF_HH_KEYSTATE_MASK_NUMLOCK,
                                        TRUE);
                        sync_lockstate_on_connect(p_dev);
                        /* End Sync HID Keyboard lockstates */
                        break;
                    }
                }
            }
            break;

        case BTA_HH_ADD_DEV_EVT:
            BTIF_TRACE_WARNING2("BTA_HH_ADD_DEV_EVT: status = %d, handle = %d",p_data->dev_info.status, p_data->dev_info.handle);
            int i;
            for (i = 0; i < BTIF_HH_MAX_ADDED_DEV; i++) {
                if (memcmp(btif_hh_cb.added_devices[i].bd_addr.address, p_data->dev_info.bda, 6) == 0) {
                    if (p_data->dev_info.status == BTA_HH_OK) {
                        btif_hh_cb.added_devices[i].dev_handle = p_data->dev_info.handle;
                    }
                    else {
                        memset(btif_hh_cb.added_devices[i].bd_addr.address, 0, 6);
                        btif_hh_cb.added_devices[i].dev_handle = BTA_HH_INVALID_HANDLE;
                    }
                    break;
                }
            }
            break;
        case BTA_HH_RMV_DEV_EVT:
                BTIF_TRACE_DEBUG2("BTA_HH_RMV_DEV_EVT: status = %d, handle = %d",
                     p_data->dev_info.status, p_data->dev_info.handle);
                BTIF_TRACE_DEBUG6("BTA_HH_RMV_DEV_EVT:bda = %02x:%02x:%02x:%02x:%02x:%02x",
                     p_data->dev_info.bda[0], p_data->dev_info.bda[1], p_data->dev_info.bda[2],
                     p_data->dev_info.bda[3], p_data->dev_info.bda[4], p_data->dev_info.bda[5]);
                break;


        case BTA_HH_VC_UNPLUG_EVT:
                BTIF_TRACE_DEBUG2("BTA_HH_VC_UNPLUG_EVT: status = %d, handle = %d",
                     p_data->dev_status.status, p_data->dev_status.handle);
                p_dev = btif_hh_find_connected_dev_by_handle(p_data->dev_status.handle);
                btif_hh_cb.status = BTIF_HH_DEV_DISCONNECTED;
                if (p_dev != NULL) {
                    BTIF_TRACE_DEBUG6("BTA_HH_VC_UNPLUG_EVT:bda = %02x:%02x:%02x:%02x:%02x:%02x",
                         p_dev->bd_addr.address[0], p_dev->bd_addr.address[1], p_dev->bd_addr.address[2],
                         p_dev->bd_addr.address[3], p_dev->bd_addr.address[4], p_dev->bd_addr.address[5]);
                    p_dev->dev_status = BTHH_CONN_STATE_DISCONNECTED;
                    BTIF_TRACE_DEBUG1("%s---Sending connection state change", __FUNCTION__);
                    HAL_CBACK(bt_hh_callbacks, connection_state_cb,&(p_dev->bd_addr), p_dev->dev_status);
                    BTIF_TRACE_DEBUG1("%s---Removing HID mouse bond", __FUNCTION__);
                    BTA_DmRemoveDevice((UINT8 *)p_dev->bd_addr.address);
                    HAL_CBACK(bt_hh_callbacks, virtual_unplug_cb,&(p_dev->bd_addr),p_data->dev_status.status);
                }
                break;

        case BTA_HH_API_ERR_EVT  :
                ALOGI("BTA_HH API_ERR");
                break;



            default:
                BTIF_TRACE_WARNING2("%s: Unhandled event: %d", __FUNCTION__, event);
                break;
        }
}

/*******************************************************************************
**
** Function         bte_hh_evt
**
** Description      Switches context from BTE to BTIF for all HH events
**
** Returns          void
**
*******************************************************************************/

static void bte_hh_evt(tBTA_HH_EVT event, tBTA_HH *p_data)
{
    bt_status_t status;
    int param_len = 0;

    if (BTA_HH_ENABLE_EVT == event)
        param_len = sizeof(tBTA_HH_STATUS);
    else if (BTA_HH_OPEN_EVT == event)
        param_len = sizeof(tBTA_HH_CONN);
    else if (BTA_HH_DISABLE_EVT == event)
        param_len = sizeof(tBTA_HH_STATUS);
    else if (BTA_HH_CLOSE_EVT == event)
        param_len = sizeof(tBTA_HH_CBDATA);
    else if (BTA_HH_GET_DSCP_EVT == event)
        param_len = sizeof(tBTA_HH_DEV_DSCP_INFO);
    else if ((BTA_HH_GET_PROTO_EVT == event) || (BTA_HH_GET_RPT_EVT == event)|| (BTA_HH_GET_IDLE_EVT == event))
        param_len = sizeof(tBTA_HH_HSDATA);
    else if ((BTA_HH_SET_PROTO_EVT == event) || (BTA_HH_SET_RPT_EVT == event) || (BTA_HH_VC_UNPLUG_EVT == event) || (BTA_HH_SET_IDLE_EVT == event))
        param_len = sizeof(tBTA_HH_CBDATA);
    else if ((BTA_HH_ADD_DEV_EVT == event) || (BTA_HH_RMV_DEV_EVT == event) )
        param_len = sizeof(tBTA_HH_DEV_INFO);
    else if (BTA_HH_API_ERR_EVT == event)
        param_len = 0;
    /* switch context to btif task context (copy full union size for convenience) */
    status = btif_transfer_context(btif_hh_upstreams_evt, (uint16_t)event, (void*)p_data, param_len, NULL);

    /* catch any failed context transfers */
    ASSERTC(status == BT_STATUS_SUCCESS, "context transfer failed", status);
}

/*******************************************************************************
**
** Function         btif_hh_handle_evt
**
** Description      Switches context for immediate callback
**
** Returns          void
**
*******************************************************************************/

static void btif_hh_handle_evt(UINT16 event, char *p_param)
{
    bt_bdaddr_t *bd_addr = (bt_bdaddr_t*)p_param;
    BTIF_TRACE_EVENT2("%s: event=%d", __FUNCTION__, event);
    int ret;
    switch(event)
    {
        case BTIF_HH_CONNECT_REQ_EVT:
        {
            ret = btif_hh_connect(bd_addr);
            if(ret == BT_STATUS_SUCCESS)
            {
                HAL_CBACK(bt_hh_callbacks, connection_state_cb,bd_addr,BTHH_CONN_STATE_CONNECTING);
            }
            else
                HAL_CBACK(bt_hh_callbacks, connection_state_cb,bd_addr,BTHH_CONN_STATE_DISCONNECTED);
        }
        break;

        case BTIF_HH_DISCONNECT_REQ_EVT:
        {
            BTIF_TRACE_EVENT2("%s: event=%d", __FUNCTION__, event);
            btif_hh_disconnect(bd_addr);
            HAL_CBACK(bt_hh_callbacks, connection_state_cb,bd_addr,BTHH_CONN_STATE_DISCONNECTING);
        }
        break;

        case BTIF_HH_VUP_REQ_EVT:
        {
            BTIF_TRACE_EVENT2("%s: event=%d", __FUNCTION__, event);
            ret = btif_hh_virtual_unplug(bd_addr);
        }
        break;

        default:
        {
            BTIF_TRACE_WARNING2("%s : Unknown event 0x%x", __FUNCTION__, event);
        }
        break;
    }
}


/*******************************************************************************
**
** Function         btif_hh_init
**
** Description     initializes the hh interface
**
** Returns         bt_status_t
**
*******************************************************************************/
static bt_status_t init( bthh_callbacks_t* callbacks )
{
    UINT32 i;
    BTIF_TRACE_EVENT1("%s", __FUNCTION__);

    bt_hh_callbacks = callbacks;
    memset(&btif_hh_cb, 0, sizeof(btif_hh_cb));
    for (i = 0; i < BTIF_HH_MAX_HID; i++){
        btif_hh_cb.devices[i].dev_status = BTHH_CONN_STATE_UNKNOWN;
    }
    /* Invoke the enable service API to the core to set the appropriate service_id */
    btif_enable_service(BTA_HID_SERVICE_ID);
    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function        connect
**
** Description     connect to hid device
**
** Returns         bt_status_t
**
*******************************************************************************/
static bt_status_t connect( bt_bdaddr_t *bd_addr)
{
    if(btif_hh_cb.status != BTIF_HH_DEV_CONNECTING)
    {
        btif_transfer_context(btif_hh_handle_evt, BTIF_HH_CONNECT_REQ_EVT,
                                 (char*)bd_addr, sizeof(bt_bdaddr_t), NULL);
        return BT_STATUS_SUCCESS;
    }
    else
        return BT_STATUS_BUSY;
}

/*******************************************************************************
**
** Function         disconnect
**
** Description      disconnect from hid device
**
** Returns         bt_status_t
**
*******************************************************************************/
static bt_status_t disconnect( bt_bdaddr_t *bd_addr )
{
    CHECK_BTHH_INIT();
    btif_hh_device_t *p_dev;

    if (btif_hh_cb.status == BTIF_HH_DISABLED)
    {
        BTIF_TRACE_WARNING2("%s: Error, HH status = %d", __FUNCTION__, btif_hh_cb.status);
        return BT_STATUS_FAIL;
    }
    p_dev = btif_hh_find_connected_dev_by_bda(bd_addr);
    if (p_dev != NULL)
    {
        return btif_transfer_context(btif_hh_handle_evt, BTIF_HH_DISCONNECT_REQ_EVT,
                     (char*)bd_addr, sizeof(bt_bdaddr_t), NULL);
    }
    else
    {
        BTIF_TRACE_WARNING1("%s: Error, device  not opened.", __FUNCTION__);
        return BT_STATUS_FAIL;
    }
}

/*******************************************************************************
**
** Function         virtual_unplug
**
** Description      Virtual UnPlug (VUP) the specified HID device.
**
** Returns         bt_status_t
**
*******************************************************************************/
static bt_status_t virtual_unplug (bt_bdaddr_t *bd_addr)
{
    CHECK_BTHH_INIT();
    btif_hh_device_t *p_dev;
    char bd_str[18];
    sprintf(bd_str, "%02X:%02X:%02X:%02X:%02X:%02X",
            bd_addr->address[0],  bd_addr->address[1],  bd_addr->address[2],  bd_addr->address[3],
            bd_addr->address[4], bd_addr->address[5]);
    if (btif_hh_cb.status == BTIF_HH_DISABLED)
    {
        BTIF_TRACE_ERROR2("%s: Error, HH status = %d", __FUNCTION__, btif_hh_cb.status);
        return BT_STATUS_FAIL;
    }
    p_dev = btif_hh_find_dev_by_bda(bd_addr);
    if (!p_dev)
    {
        BTIF_TRACE_ERROR2("%s: Error, device %s not opened.", __FUNCTION__, bd_str);
        return BT_STATUS_FAIL;
    }
    btif_transfer_context(btif_hh_handle_evt, BTIF_HH_VUP_REQ_EVT,
                                 (char*)bd_addr, sizeof(bt_bdaddr_t), NULL);
    return BT_STATUS_SUCCESS;
}


/*******************************************************************************
**
** Function         set_info
**
** Description      Set the HID device descriptor for the specified HID device.
**
** Returns         bt_status_t
**
*******************************************************************************/
static bt_status_t set_info (bt_bdaddr_t *bd_addr, bthh_hid_info_t hid_info )
{
    CHECK_BTHH_INIT();
    tBTA_HH_DEV_DSCP_INFO dscp_info;
    BD_ADDR* bda = (BD_ADDR*) bd_addr;

    BTIF_TRACE_DEBUG6("addr = %02X:%02X:%02X:%02X:%02X:%02X",
         (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);
    BTIF_TRACE_DEBUG6("%s: sub_class = 0x%02x, app_id = %d, vendor_id = 0x%04x, "
         "product_id = 0x%04x, version= 0x%04x",
         __FUNCTION__, hid_info.sub_class,
         hid_info.app_id, hid_info.vendor_id, hid_info.product_id,
         hid_info.version);

    if (btif_hh_cb.status == BTIF_HH_DISABLED)
    {
        BTIF_TRACE_ERROR2("%s: Error, HH status = %d", __FUNCTION__, btif_hh_cb.status);
        return BT_STATUS_FAIL;
    }

    dscp_info.vendor_id  = hid_info.vendor_id;
    dscp_info.product_id = hid_info.product_id;
    dscp_info.version    = hid_info.version;
    dscp_info.ctry_code  = hid_info.ctry_code;

    dscp_info.descriptor.dl_len = hid_info.dl_len;
    dscp_info.descriptor.dsc_list = (UINT8 *) GKI_getbuf(dscp_info.descriptor.dl_len);
    if (dscp_info.descriptor.dsc_list == NULL)
    {
        ALOGE("%s: Failed to allocate DSCP for CB", __FUNCTION__);
        return BT_STATUS_FAIL;
    }
    memcpy(dscp_info.descriptor.dsc_list, &(hid_info.dsc_list), hid_info.dl_len);

    if (btif_hh_add_added_dev(*bd_addr, hid_info.attr_mask))
    {
        BTA_HhAddDev(*bda, hid_info.attr_mask, hid_info.sub_class,
                     hid_info.app_id, dscp_info);
    }

    GKI_freebuf(dscp_info.descriptor.dsc_list);

    return BT_STATUS_SUCCESS;
}
/*******************************************************************************
**
** Function         get_idle_time
**
** Description      Get the HID idle time
**
** Returns         bt_status_t
**
*******************************************************************************/
static bt_status_t get_idle_time(bt_bdaddr_t *bd_addr)
{
    CHECK_BTHH_INIT();
    btif_hh_device_t *p_dev;
    BD_ADDR* bda = (BD_ADDR*) bd_addr;

    BTIF_TRACE_DEBUG6(" addr = %02X:%02X:%02X:%02X:%02X:%02X",
         (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);

    if (btif_hh_cb.status == BTIF_HH_DISABLED) {
        BTIF_TRACE_ERROR2("%s: Error, HH status = %d", __FUNCTION__, btif_hh_cb.status);
        return BT_STATUS_FAIL;
    }

    p_dev = btif_hh_find_connected_dev_by_bda(bd_addr);
    if (p_dev != NULL) {
        //BTA_HhGetIdle(p_dev->dev_handle);
    }
    else {
        return BT_STATUS_FAIL;
    }
    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         set_idle_time
**
** Description      Set the HID idle time
**
** Returns         bt_status_t
**
*******************************************************************************/
static bt_status_t set_idle_time (bt_bdaddr_t *bd_addr, uint8_t idle_time)
{
    CHECK_BTHH_INIT();
    btif_hh_device_t *p_dev;
    BD_ADDR* bda = (BD_ADDR*) bd_addr;

    BTIF_TRACE_DEBUG6("addr = %02X:%02X:%02X:%02X:%02X:%02X",
         (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);

    if (btif_hh_cb.status == BTIF_HH_DISABLED) {
        BTIF_TRACE_ERROR2("%s: Error, HH status = %d", __FUNCTION__, btif_hh_cb.status);
        return BT_STATUS_FAIL;
    }

    p_dev = btif_hh_find_connected_dev_by_bda(bd_addr);
    if (p_dev == NULL) {
        BTIF_TRACE_WARNING6(" Error, device %02X:%02X:%02X:%02X:%02X:%02X not opened.",
             (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);
        return BT_STATUS_FAIL;
    }
    else {
        //BTA_HhSetIdle(p_dev->dev_handle, idle_time);
    }
    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         get_protocol
**
** Description      Get the HID proto mode.
**
** Returns         bt_status_t
**
*******************************************************************************/
static bt_status_t get_protocol (bt_bdaddr_t *bd_addr, bthh_protocol_mode_t protocolMode)
{
    CHECK_BTHH_INIT();
    btif_hh_device_t *p_dev;
    BD_ADDR* bda = (BD_ADDR*) bd_addr;

    BTIF_TRACE_DEBUG6(" addr = %02X:%02X:%02X:%02X:%02X:%02X",
         (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);

    if (btif_hh_cb.status == BTIF_HH_DISABLED) {
        BTIF_TRACE_ERROR2("%s: Error, HH status = %d", __FUNCTION__, btif_hh_cb.status);
        return BT_STATUS_FAIL;
    }

    p_dev = btif_hh_find_connected_dev_by_bda(bd_addr);
    if (p_dev != NULL) {
        BTA_HhGetProtoMode(p_dev->dev_handle);
    }
    else {
        return BT_STATUS_FAIL;
    }
    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         set_protocol
**
** Description      Set the HID proto mode.
**
** Returns         bt_status_t
**
*******************************************************************************/
static bt_status_t set_protocol (bt_bdaddr_t *bd_addr, bthh_protocol_mode_t protocolMode)
{
    CHECK_BTHH_INIT();
    btif_hh_device_t *p_dev;
    UINT8 proto_mode = protocolMode;
    BD_ADDR* bda = (BD_ADDR*) bd_addr;

    BTIF_TRACE_DEBUG2("%s:proto_mode = %d", __FUNCTION__,protocolMode);

    BTIF_TRACE_DEBUG6("addr = %02X:%02X:%02X:%02X:%02X:%02X",
         (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);

    if (btif_hh_cb.status == BTIF_HH_DISABLED) {
        BTIF_TRACE_ERROR2("%s: Error, HH status = %d", __FUNCTION__, btif_hh_cb.status);
        return BT_STATUS_FAIL;
    }

    p_dev = btif_hh_find_connected_dev_by_bda(bd_addr);
    if (p_dev == NULL) {
        BTIF_TRACE_WARNING6(" Error, device %02X:%02X:%02X:%02X:%02X:%02X not opened.",
             (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);
        return BT_STATUS_FAIL;
    }
    else if (protocolMode != BTA_HH_PROTO_RPT_MODE && protocolMode != BTA_HH_PROTO_BOOT_MODE) {
        BTIF_TRACE_WARNING2("s: Error, device proto_mode = %d.", __FUNCTION__, proto_mode);
        return BT_STATUS_FAIL;
    }
    else {
        BTA_HhSetProtoMode(p_dev->dev_handle, protocolMode);
    }


    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         get_report
**
** Description      Send a GET_REPORT to HID device.
**
** Returns         bt_status_t
**
*******************************************************************************/
static bt_status_t get_report (bt_bdaddr_t *bd_addr, bthh_report_type_t reportType, uint8_t reportId, int bufferSize)
{
    CHECK_BTHH_INIT();
    btif_hh_device_t *p_dev;
    BD_ADDR* bda = (BD_ADDR*) bd_addr;

    BTIF_TRACE_DEBUG4("%s:proto_mode = %dr_type = %d, rpt_id = %d, buf_size = %d", __FUNCTION__,
          reportType, reportId, bufferSize);

    BTIF_TRACE_DEBUG6("addr = %02X:%02X:%02X:%02X:%02X:%02X",
         (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);

    if (btif_hh_cb.status == BTIF_HH_DISABLED) {
        BTIF_TRACE_ERROR2("%s: Error, HH status = %d", __FUNCTION__, btif_hh_cb.status);
        return BT_STATUS_FAIL;
    }


    p_dev = btif_hh_find_connected_dev_by_bda(bd_addr);
    if (p_dev == NULL) {
        BTIF_TRACE_ERROR6("%s: Error, device %02X:%02X:%02X:%02X:%02X:%02X not opened.",
             (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);
        return BT_STATUS_FAIL;
    }
    else if ( ((int) reportType) <= BTA_HH_RPTT_RESRV || ((int) reportType) > BTA_HH_RPTT_FEATURE) {
        BTIF_TRACE_ERROR6(" Error, device %02X:%02X:%02X:%02X:%02X:%02X not opened.",
             (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);
        return BT_STATUS_FAIL;
    }
    else {
        BTA_HhGetReport(p_dev->dev_handle, reportType,
                        reportId, bufferSize);
    }

    return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         set_report
**
** Description      Send a SET_REPORT to HID device.
**
** Returns         bt_status_t
**
*******************************************************************************/
static bt_status_t set_report (bt_bdaddr_t *bd_addr, bthh_report_type_t reportType, char* report)
{
    CHECK_BTHH_INIT();
    btif_hh_device_t *p_dev;
    BD_ADDR* bda = (BD_ADDR*) bd_addr;

    BTIF_TRACE_DEBUG2("%s:reportType = %d", __FUNCTION__,reportType);

    BTIF_TRACE_DEBUG6("addr = %02X:%02X:%02X:%02X:%02X:%02X",
         (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);


    if (btif_hh_cb.status == BTIF_HH_DISABLED) {
        BTIF_TRACE_ERROR2("%s: Error, HH status = %d", __FUNCTION__, btif_hh_cb.status);
        return BT_STATUS_FAIL;
    }

    p_dev = btif_hh_find_connected_dev_by_bda(bd_addr);
    if (p_dev == NULL) {
        BTIF_TRACE_ERROR6("%s: Error, device %02X:%02X:%02X:%02X:%02X:%02X not opened.",
             (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);
        return BT_STATUS_FAIL;
    }
    else if ( ( (int) reportType) <= BTA_HH_RPTT_RESRV || ( (int) reportType) > BTA_HH_RPTT_FEATURE) {
        BTIF_TRACE_ERROR6(" Error, device %02X:%02X:%02X:%02X:%02X:%02X not opened.",
             (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);
        return BT_STATUS_FAIL;
    }
    else {
        int    hex_bytes_filled;
        UINT8  hexbuf[200];
        UINT16 len = (strlen(report) + 1) / 2;

        if (p_dev->p_buf != NULL) {
            GKI_freebuf(p_dev->p_buf);
        }
        p_dev->p_buf = GKI_getbuf((UINT16) (len + BTA_HH_MIN_OFFSET + sizeof(BT_HDR)));
        if (p_dev->p_buf == NULL) {
            BTIF_TRACE_ERROR2("%s: Error, failed to allocate RPT buffer, len = %d", __FUNCTION__, len);
            return BT_STATUS_FAIL;
        }

        p_dev->p_buf->len = len;
        p_dev->p_buf->offset = BTA_HH_MIN_OFFSET;

        /* Build a SetReport data buffer */
        memset(hexbuf, 0, 200);
        //TODO
        hex_bytes_filled = ascii_2_hex(report, len, hexbuf);
        ALOGI("Hex bytes filled, hex value: %d", hex_bytes_filled);

        if (hex_bytes_filled) {
            UINT8* pbuf_data;
            pbuf_data = (UINT8*) (p_dev->p_buf + 1) + p_dev->p_buf->offset;
            memcpy(pbuf_data, hexbuf, hex_bytes_filled);
            BTA_HhSetReport(p_dev->dev_handle, reportType, p_dev->p_buf);
        }
        return BT_STATUS_SUCCESS;
    }


}

/*******************************************************************************
**
** Function         send_data
**
** Description      Send a SEND_DATA to HID device.
**
** Returns         bt_status_t
**
*******************************************************************************/
static bt_status_t send_data (bt_bdaddr_t *bd_addr, char* data)
{
    CHECK_BTHH_INIT();
    btif_hh_device_t *p_dev;
    BD_ADDR* bda = (BD_ADDR*) bd_addr;

    BTIF_TRACE_DEBUG1("%s", __FUNCTION__);

    BTIF_TRACE_DEBUG6("addr = %02X:%02X:%02X:%02X:%02X:%02X",
         (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);

    if (btif_hh_cb.status == BTIF_HH_DISABLED) {
        BTIF_TRACE_ERROR2("%s: Error, HH status = %d", __FUNCTION__, btif_hh_cb.status);
        return BT_STATUS_FAIL;
    }

    p_dev = btif_hh_find_connected_dev_by_bda(bd_addr);
    if (p_dev == NULL) {
        BTIF_TRACE_ERROR6("%s: Error, device %02X:%02X:%02X:%02X:%02X:%02X not opened.",
             (*bda)[0], (*bda)[1], (*bda)[2], (*bda)[3], (*bda)[4], (*bda)[5]);
        return BT_STATUS_FAIL;
    }

    else {
        int    hex_bytes_filled;
        UINT8  hexbuf[200];
        UINT16 len = (strlen(data) + 1) / 2;

        if (p_dev->p_buf != NULL) {
            GKI_freebuf(p_dev->p_buf);
        }
        p_dev->p_buf = GKI_getbuf((UINT16) (len + BTA_HH_MIN_OFFSET + sizeof(BT_HDR)));
        if (p_dev->p_buf == NULL) {
            BTIF_TRACE_ERROR2("%s: Error, failed to allocate RPT buffer, len = %d", __FUNCTION__, len);
            return BT_STATUS_FAIL;
        }

        p_dev->p_buf->len = len;
        p_dev->p_buf->offset = BTA_HH_MIN_OFFSET;

        /* Build a SetReport data buffer */
        memset(hexbuf, 0, 200);
        hex_bytes_filled = ascii_2_hex(data, len, hexbuf);
        BTIF_TRACE_ERROR2("Hex bytes filled, hex value: %d, %d", hex_bytes_filled, len);

        if (hex_bytes_filled) {
            UINT8* pbuf_data;
            pbuf_data = (UINT8*) (p_dev->p_buf + 1) + p_dev->p_buf->offset;
            memcpy(pbuf_data, hexbuf, hex_bytes_filled);
            BTA_HhSendData(p_dev->dev_handle, *bda, p_dev->p_buf);
            return BT_STATUS_SUCCESS;
        }

    }
    return BT_STATUS_FAIL;
}


/*******************************************************************************
**
** Function         cleanup
**
** Description      Closes the HH interface
**
** Returns          bt_status_t
**
*******************************************************************************/
static void  cleanup( void )
{
    BTIF_TRACE_EVENT1("%s", __FUNCTION__);
    btif_hh_device_t *p_dev;
    int i;
    if (btif_hh_cb.status == BTIF_HH_DISABLED) {
        BTIF_TRACE_WARNING2("%s: HH disabling or disabled already, status = %d", __FUNCTION__, btif_hh_cb.status);
        return;
    }
    btif_hh_cb.status = BTIF_HH_DISABLING;
    for (i = 0; i < BTIF_HH_MAX_HID; i++) {
         p_dev = &btif_hh_cb.devices[i];
         if (p_dev->dev_status != BTHH_CONN_STATE_UNKNOWN && p_dev->fd >= 0) {
             BTIF_TRACE_DEBUG2("%s: Closing uhid fd = %d", __FUNCTION__, p_dev->fd);
             bta_hh_co_destroy(p_dev->fd);
             p_dev->fd = -1;
         }
     }

    if (bt_hh_callbacks)
    {
        btif_disable_service(BTA_HID_SERVICE_ID);
        bt_hh_callbacks = NULL;
    }

}

static const bthh_interface_t bthhInterface = {
    sizeof(bt_interface_t),
    init,
    connect,
    disconnect,
    virtual_unplug,
    set_info,
    get_protocol,
    set_protocol,
//    get_idle_time,
//    set_idle_time,
    get_report,
    set_report,
    send_data,
    cleanup,
};

/*******************************************************************************
**
** Function         btif_hh_execute_service
**
** Description      Initializes/Shuts down the service
**
** Returns          BT_STATUS_SUCCESS on success, BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_hh_execute_service(BOOLEAN b_enable)
{
     if (b_enable)
     {
          /* Enable and register with BTA-HH */
          BTA_HhEnable(BTA_SEC_NONE, FALSE, bte_hh_evt);
     }
     else {
         /* Disable HH */
         BTA_HhDisable();
     }
     return BT_STATUS_SUCCESS;
}

/*******************************************************************************
**
** Function         btif_hh_get_interface
**
** Description      Get the hh callback interface
**
** Returns          bthh_interface_t
**
*******************************************************************************/
const bthh_interface_t *btif_hh_get_interface()
{
    BTIF_TRACE_EVENT1("%s", __FUNCTION__);
    return &bthhInterface;
}
