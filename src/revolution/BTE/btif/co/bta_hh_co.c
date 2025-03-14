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

//#if (defined(BTA_HH_INCLUDED) && (BTA_HH_INCLUDED == TRUE))

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <linux/uhid.h>
#include "btif_hh.h"
#include "bta_api.h"
#include "bta_hh_api.h"



const char *dev_path = "/dev/uhid";


/*Internal function to perform UHID write and error checking*/
static int uhid_write(int fd, const struct uhid_event *ev)
{
    ssize_t ret;
    ret = write(fd, ev, sizeof(*ev));
    if (ret < 0){
        int rtn = -errno;
        APPL_TRACE_ERROR2("%s: Cannot write to uhid:%s",__FUNCTION__,strerror(errno));
        return rtn;
    } else if (ret != sizeof(*ev)) {
        APPL_TRACE_ERROR3("%s: Wrong size written to uhid: %ld != %lu",
                                                    __FUNCTION__, ret, sizeof(*ev));
        return -EFAULT;
    } else {
        return 0;
    }
}

void bta_hh_co_destroy(int fd)
{
    struct uhid_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.type = UHID_DESTROY;
    uhid_write(fd, &ev);
    close(fd);
}

int bta_hh_co_write(int fd, UINT8* rpt, UINT16 len)
{
    APPL_TRACE_DEBUG0("bta_hh_co_data: UHID write");
    struct uhid_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.type = UHID_INPUT;
    ev.u.input.size = len;
    if(len > sizeof(ev.u.input.data)){
        APPL_TRACE_WARNING1("%s:report size greater than allowed size",__FUNCTION__);
        return -1;
    }
    memcpy(ev.u.input.data, rpt, len);
    return uhid_write(fd, &ev);

}


/*******************************************************************************
**
** Function      bta_hh_co_open
**
** Description   When connection is opened, this call-out function is executed
**               by HH to do platform specific initialization.
**
** Returns       void.
*******************************************************************************/
void bta_hh_co_open(UINT8 dev_handle, UINT8 sub_class, tBTA_HH_ATTR_MASK attr_mask,
                    UINT8 app_id)
{
    UINT32 i;
    btif_hh_device_t *p_dev = NULL;

    if (dev_handle == BTA_HH_INVALID_HANDLE) {
        APPL_TRACE_WARNING2("%s: Oops, dev_handle (%d) is invalid...", __FUNCTION__, dev_handle);
        return;
    }

    for (i = 0; i < BTIF_HH_MAX_HID; i++) {
        p_dev = &btif_hh_cb.devices[i];
        if (p_dev->dev_status != BTHH_CONN_STATE_UNKNOWN && p_dev->dev_handle == dev_handle) {
            // We found a device with the same handle. Must be a device reconnected.
            APPL_TRACE_WARNING2("%s: Found an existing device with the same handle "
                                                                "dev_status = %d",__FUNCTION__,
                                                                p_dev->dev_status);
            APPL_TRACE_WARNING6("%s:     bd_addr = [%02X:%02X:%02X:%02X:%02X:]", __FUNCTION__,
                 p_dev->bd_addr.address[0], p_dev->bd_addr.address[1], p_dev->bd_addr.address[2],
                 p_dev->bd_addr.address[3], p_dev->bd_addr.address[4]);
                 APPL_TRACE_WARNING4("%s:     attr_mask = 0x%04x, sub_class = 0x%02x, app_id = %d",
                                  __FUNCTION__, p_dev->attr_mask, p_dev->sub_class, p_dev->app_id);

            if(p_dev->fd<0) {
                p_dev->fd = open(dev_path, O_RDWR | O_CLOEXEC);
                if (p_dev->fd < 0){
                    APPL_TRACE_ERROR2("%s: Error: failed to open uhid, err:%s",
                                                                    __FUNCTION__,strerror(errno));
                }else
                    APPL_TRACE_DEBUG2("%s: uhid fd = %d", __FUNCTION__, p_dev->fd);
            }

            break;
        }
        p_dev = NULL;
    }

    if (p_dev == NULL) {
        // Did not find a device reconnection case. Find an empty slot now.
        for (i = 0; i < BTIF_HH_MAX_HID; i++) {
            if (btif_hh_cb.devices[i].dev_status == BTHH_CONN_STATE_UNKNOWN) {
                p_dev = &btif_hh_cb.devices[i];
                p_dev->dev_handle = dev_handle;
                p_dev->attr_mask  = attr_mask;
                p_dev->sub_class  = sub_class;
                p_dev->app_id     = app_id;

                btif_hh_cb.device_num++;
                // This is a new device,open the uhid driver now.
                p_dev->fd = open(dev_path, O_RDWR | O_CLOEXEC);
                if (p_dev->fd < 0){
                    APPL_TRACE_ERROR2("%s: Error: failed to open uhid, err:%s",
                                                                    __FUNCTION__,strerror(errno));
                }else
                    APPL_TRACE_DEBUG2("%s: uhid fd = %d", __FUNCTION__, p_dev->fd);


                break;
            }
        }
    }

    if (p_dev == NULL) {
        APPL_TRACE_ERROR1("%s: Error: too many HID devices are connected", __FUNCTION__);
        return;
    }

    p_dev->dev_status = BTHH_CONN_STATE_CONNECTED;
    APPL_TRACE_DEBUG2("%s: Return device status %d", __FUNCTION__, p_dev->dev_status);
}


/*******************************************************************************
**
** Function      bta_hh_co_close
**
** Description   When connection is closed, this call-out function is executed
**               by HH to do platform specific finalization.
**
** Parameters    dev_handle  - device handle
**                  app_id      - application id
**
** Returns          void.
*******************************************************************************/
void bta_hh_co_close(UINT8 dev_handle, UINT8 app_id)
{
    APPL_TRACE_WARNING3("%s: dev_handle = %d, app_id = %d", __FUNCTION__, dev_handle, app_id);
}


/*******************************************************************************
**
** Function         bta_hh_co_data
**
** Description      This function is executed by BTA when HID host receive a data
**                  report.
**
** Parameters       dev_handle  - device handle
**                  *p_rpt      - pointer to the report data
**                  len         - length of report data
**                  mode        - Hid host Protocol Mode
**                  sub_clas    - Device Subclass
**                  app_id      - application id
**
** Returns          void
*******************************************************************************/
void bta_hh_co_data(UINT8 dev_handle, UINT8 *p_rpt, UINT16 len, tBTA_HH_PROTO_MODE mode,
                    UINT8 sub_class, UINT8 ctry_code, BD_ADDR peer_addr, UINT8 app_id)
{
    btif_hh_device_t *p_dev;

    APPL_TRACE_DEBUG6("%s: dev_handle = %d, subclass = 0x%02X, mode = %d, "
         "ctry_code = %d, app_id = %d",
         __FUNCTION__, dev_handle, sub_class, mode, ctry_code, app_id);

    p_dev = btif_hh_find_connected_dev_by_handle(dev_handle);
    if (p_dev == NULL) {
        APPL_TRACE_WARNING2("%s: Error: unknown HID device handle %d", __FUNCTION__, dev_handle);
        return;
    }
    // Send the HID report to the kernel.
    if (p_dev->fd >= 0) {
        bta_hh_co_write(p_dev->fd, p_rpt, len);
    }else {
        APPL_TRACE_WARNING3("%s: Error: fd = %d, len = %d", __FUNCTION__, p_dev->fd, len);
    }
}


/*******************************************************************************
**
** Function         bta_hh_co_send_hid_info
**
** Description      This function is called in btif_hh.c to process DSCP received.
**
** Parameters       dev_handle  - device handle
**                  dscp_len    - report descriptor length
**                  *p_dscp     - report descriptor
**
** Returns          void
*******************************************************************************/
void bta_hh_co_send_hid_info(btif_hh_device_t *p_dev, char *dev_name, UINT16 vendor_id,
                             UINT16 product_id, UINT16 version, UINT8 ctry_code,
                             int dscp_len, UINT8 *p_dscp)
{
    int result;
    struct uhid_event ev;

    if (p_dev->fd < 0) {
        APPL_TRACE_WARNING3("%s: Error: fd = %d, dscp_len = %d", __FUNCTION__, p_dev->fd, dscp_len);
        return;
    }

    APPL_TRACE_WARNING4("%s: fd = %d, name = [%s], dscp_len = %d", __FUNCTION__,
                                                                    p_dev->fd, dev_name, dscp_len);
    APPL_TRACE_WARNING5("%s: vendor_id = 0x%04x, product_id = 0x%04x, version= 0x%04x,"
                                                                    "ctry_code=0x%02x",__FUNCTION__,
                                                                    vendor_id, product_id,
                                                                    version, ctry_code);

//Create and send hid descriptor to kernel
    memset(&ev, 0, sizeof(ev));
    ev.type = UHID_CREATE;
    strncpy((char*)ev.u.create.name, dev_name, sizeof(ev.u.create.name) - 1);
    ev.u.create.rd_size = dscp_len;
    ev.u.create.rd_data = p_dscp;
    ev.u.create.bus = BUS_BLUETOOTH;
    ev.u.create.vendor = vendor_id;
    ev.u.create.product = product_id;
    ev.u.create.version = version;
    ev.u.create.country = ctry_code;
    result = uhid_write(p_dev->fd, &ev);

    APPL_TRACE_WARNING4("%s: fd = %d, dscp_len = %d, result = %d", __FUNCTION__,
                                                                    p_dev->fd, dscp_len, result);

    if (result) {
        APPL_TRACE_WARNING2("%s: Error: failed to send DSCP, result = %d", __FUNCTION__, result);

        /* The HID report descriptor is corrupted. Close the driver. */
        close(p_dev->fd);
        p_dev->fd = -1;
    }
}


