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
 *  Filename:      bte_main.c
 *
 *  Description:   Contains BTE core stack initialization and shutdown code
 *
 ******************************************************************************/
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>

#include "gki.h"
#include "bd.h"
#include "btu.h"
#include "bte.h"
#include "bta_api.h"
#include "bt_hci_lib.h"

/*******************************************************************************
**  Constants & Macros
*******************************************************************************/

/* Run-time configuration file */
#ifndef BTE_STACK_CONF_FILE
#define BTE_STACK_CONF_FILE "/etc/bluetooth/bt_stack.conf"
#endif

/* if not specified in .txt file then use this as default  */
#ifndef HCI_LOGGING_FILENAME
#define HCI_LOGGING_FILENAME  "/data/misc/bluedroid/btsnoop_hci.log"
#endif

/*******************************************************************************
**  Local type definitions
*******************************************************************************/

/******************************************************************************
**  Variables
******************************************************************************/
BOOLEAN hci_logging_enabled = FALSE;    /* by default, turn hci log off */
char hci_logfile[256] = HCI_LOGGING_FILENAME;


/*******************************************************************************
**  Static variables
*******************************************************************************/
static bt_hc_interface_t *bt_hc_if=NULL;
static const bt_hc_callbacks_t hc_callbacks;
static BOOLEAN lpm_enabled = FALSE;

/*******************************************************************************
**  Static functions
*******************************************************************************/
static void bte_main_in_hw_init(void);

/*******************************************************************************
**  Externs
*******************************************************************************/
BTU_API extern UINT32 btu_task (UINT32 param);
BTU_API extern void BTE_Init (void);
BT_API extern void BTE_LoadStack(void);
BT_API void BTE_UnloadStack(void);
extern void scru_flip_bda (BD_ADDR dst, const BD_ADDR src);
extern void bte_load_conf(const char *p_path);


/*******************************************************************************
**                        System Task Configuration
*******************************************************************************/

/* bluetooth protocol stack (BTU) task */
#ifndef BTE_BTU_STACK_SIZE
#define BTE_BTU_STACK_SIZE       0//0x2000         /* In bytes */
#endif
#define BTE_BTU_TASK_STR        ((INT8 *) "BTU")
UINT32 bte_btu_stack[(BTE_BTU_STACK_SIZE + 3) / 4];

/******************************************************************************
**
** Function         bte_main_in_hw_init
**
** Description      Internal helper function for chip hardware init
**
** Returns          None
**
******************************************************************************/
void bte_main_in_hw_init(void)
{
    if ( (bt_hc_if = (bt_hc_interface_t *) bt_hc_get_interface()) \
         == NULL)
    {
        APPL_TRACE_ERROR0("!!! Failed to get BtHostControllerInterface !!!");
    }
}

/******************************************************************************
**
** Function         bte_main_boot_entry
**
** Description      BTE MAIN API - Entry point for BTE chip/stack initialization
**
** Returns          None
**
******************************************************************************/
void bte_main_boot_entry(void)
{
    /* initialize OS */
    GKI_init();

    bte_main_in_hw_init();

    bte_load_conf(BTE_STACK_CONF_FILE);

#if (BTTRC_INCLUDED == TRUE)
    /* Initialize trace feature */
    BTTRC_TraceInit(MAX_TRACE_RAM_SIZE, &BTE_TraceLogBuf[0], BTTRC_METHOD_RAM);
#endif
}

/******************************************************************************
**
** Function         bte_main_shutdown
**
** Description      BTE MAIN API - Shutdown code for BTE chip/stack
**
** Returns          None
**
******************************************************************************/
void bte_main_shutdown()
{
    GKI_shutdown();
}

/******************************************************************************
**
** Function         bte_main_enable
**
** Description      BTE MAIN API - Creates all the BTE tasks. Should be called
**                  part of the Bluetooth stack enable sequence
**
** Returns          None
**
******************************************************************************/
void bte_main_enable(uint8_t *local_addr)
{
    APPL_TRACE_DEBUG1("%s", __FUNCTION__);

    /* Initialize BTE control block */
    BTE_Init();

    lpm_enabled = FALSE;

    if (bt_hc_if)
    {
        int result = bt_hc_if->init(&hc_callbacks, local_addr);
        APPL_TRACE_EVENT1("libbt-hci init returns %d", result);

        assert(result == BT_HC_STATUS_SUCCESS);

        if (hci_logging_enabled == TRUE)
            bt_hc_if->logging(BT_HC_LOGGING_ON, hci_logfile);

#if (defined (BT_CLEAN_TURN_ON_DISABLED) && BT_CLEAN_TURN_ON_DISABLED == TRUE)
        APPL_TRACE_DEBUG1("%s  Not Turninig Off the BT before Turninig ON", __FUNCTION__);

        /* Do not power off the chip before powering on  if BT_CLEAN_TURN_ON_DISABLED flag
         is defined and set to TRUE to avoid below mentioned issue.

         Wingray kernel driver maintains a combined  counter to keep track of
         BT-Wifi state. Invoking  set_power(BT_HC_CHIP_PWR_OFF) when the BT is already
         in OFF state causes this counter to be incorrectly decremented and results in undesired
         behavior of the chip.

         This is only a workaround and when the issue is fixed in the kernel this work around
         should be removed. */
#else
        /* toggle chip power to ensure we will reset chip in case
           a previous stack shutdown wasn't completed gracefully */
        bt_hc_if->set_power(BT_HC_CHIP_PWR_OFF);
#endif
        bt_hc_if->set_power(BT_HC_CHIP_PWR_ON);

        bt_hc_if->preload(NULL);
    }

    GKI_create_task((TASKPTR)btu_task, BTU_TASK, BTE_BTU_TASK_STR,
                    (UINT16 *) ((UINT8 *)bte_btu_stack + BTE_BTU_STACK_SIZE),
                    sizeof(bte_btu_stack));

    GKI_run(0);
}

/******************************************************************************
**
** Function         bte_main_disable
**
** Description      BTE MAIN API - Destroys all the BTE tasks. Should be called
**                  part of the Bluetooth stack disable sequence
**
** Returns          None
**
******************************************************************************/
void bte_main_disable(void)
{
    APPL_TRACE_DEBUG1("%s", __FUNCTION__);

    if (bt_hc_if)
    {
        bt_hc_if->cleanup();
        bt_hc_if->set_power(BT_HC_CHIP_PWR_OFF);
    }

    GKI_destroy_task(BTU_TASK);

    GKI_freeze();
}

/******************************************************************************
**
** Function         bte_main_postload_cfg
**
** Description      BTE MAIN API - Stack postload configuration
**
** Returns          None
**
******************************************************************************/
void bte_main_postload_cfg(void)
{
    if (bt_hc_if)
        bt_hc_if->postload(NULL);
}

#if (defined(HCILP_INCLUDED) && HCILP_INCLUDED == TRUE)
/******************************************************************************
**
** Function         bte_main_enable_lpm
**
** Description      BTE MAIN API - Enable/Disable low power mode operation
**
** Returns          None
**
******************************************************************************/
void bte_main_enable_lpm(BOOLEAN enable)
{
    int result = -1;

    if (bt_hc_if)
        result = bt_hc_if->lpm( \
        (enable == TRUE) ? BT_HC_LPM_ENABLE : BT_HC_LPM_DISABLE \
        );

    APPL_TRACE_EVENT2("HC lib lpm enable=%d return %d", enable, result);
}

/******************************************************************************
**
** Function         bte_main_lpm_allow_bt_device_sleep
**
** Description      BTE MAIN API - Allow BT controller goest to sleep
**
** Returns          None
**
******************************************************************************/
void bte_main_lpm_allow_bt_device_sleep()
{
    int result = -1;

    if ((bt_hc_if) && (lpm_enabled == TRUE))
        result = bt_hc_if->lpm(BT_HC_LPM_WAKE_DEASSERT);

    APPL_TRACE_DEBUG1("HC lib lpm deassertion return %d", result);
}

/******************************************************************************
**
** Function         bte_main_lpm_wake_bt_device
**
** Description      BTE MAIN API - Wake BT controller up if it is in sleep mode
**
** Returns          None
**
******************************************************************************/
void bte_main_lpm_wake_bt_device()
{
    int result = -1;

    if ((bt_hc_if) && (lpm_enabled == TRUE))
        result = bt_hc_if->lpm(BT_HC_LPM_WAKE_ASSERT);

    APPL_TRACE_DEBUG1("HC lib lpm assertion return %d", result);
}
#endif  // HCILP_INCLUDED

/******************************************************************************
**
** Function         bte_main_hci_send
**
** Description      BTE MAIN API - This function is called by the upper stack to
**                  send an HCI message. The function displays a protocol trace
**                  message (if enabled), and then calls the 'transmit' function
**                  associated with the currently selected HCI transport
**
** Returns          None
**
******************************************************************************/
void bte_main_hci_send (BT_HDR *p_msg, UINT16 event)
{
    UINT16 sub_event = event & BT_SUB_EVT_MASK;  /* local controller ID */

    p_msg->event = event;


    if((sub_event == LOCAL_BR_EDR_CONTROLLER_ID) || \
       (sub_event == LOCAL_BLE_CONTROLLER_ID))
    {
        if (bt_hc_if)
            bt_hc_if->transmit_buf((TRANSAC)p_msg, \
                                       (char *) (p_msg + 1), \
                                        p_msg->len);
        else
            GKI_freebuf(p_msg);
    }
    else
    {
        APPL_TRACE_ERROR0("Invalid Controller ID. Discarding message.");
        GKI_freebuf(p_msg);
    }
}

/******************************************************************************
**
** Function         bte_main_post_reset_init
**
** Description      BTE MAIN API - This function is mapped to BTM_APP_DEV_INIT
**                  and shall be automatically called from BTE after HCI_Reset
**
** Returns          None
**
******************************************************************************/
void bte_main_post_reset_init()
{
    BTM_ContinueReset();
}

/*****************************************************************************
**
**   libbt-hci Callback Functions
**
*****************************************************************************/

/******************************************************************************
**
** Function         preload_cb
**
** Description      HOST/CONTROLLER LIB CALLBACK API - This function is called
**                  when the libbt-hci completed stack preload process
**
** Returns          None
**
******************************************************************************/
static void preload_cb(TRANSAC transac, bt_hc_preload_result_t result)
{
    APPL_TRACE_EVENT1("HC preload_cb %d [0:SUCCESS 1:FAIL]", result);

    /* notify BTU task that libbt-hci is ready */
    /* even if PRELOAD process failed */
    GKI_send_event(BTU_TASK, TASK_MBOX_0_EVT_MASK);
}

/******************************************************************************
**
** Function         postload_cb
**
** Description      HOST/CONTROLLER LIB CALLBACK API - This function is called
**                  when the libbt-hci lib completed stack postload process
**
** Returns          None
**
******************************************************************************/
static void postload_cb(TRANSAC transac, bt_hc_postload_result_t result)
{
    APPL_TRACE_EVENT1("HC postload_cb %d", result);
}

/******************************************************************************
**
** Function         lpm_cb
**
** Description      HOST/CONTROLLER LIB CALLBACK API - This function is called
**                  back from the libbt-hci to indicate the current LPM state
**
** Returns          None
**
******************************************************************************/
static void lpm_cb(bt_hc_lpm_request_result_t result)
{
    APPL_TRACE_EVENT1("HC lpm_result_cb %d", result);
    lpm_enabled = (result == BT_HC_LPM_ENABLED) ? TRUE : FALSE;
}

/******************************************************************************
**
** Function         hostwake_ind
**
** Description      HOST/CONTROLLER LIB CALLOUT API - This function is called
**                  from the libbt-hci to indicate the HostWake event
**
** Returns          None
**
******************************************************************************/
static void hostwake_ind(bt_hc_low_power_event_t event)
{
    APPL_TRACE_EVENT1("HC hostwake_ind %d", event);
}

/******************************************************************************
**
** Function         alloc
**
** Description      HOST/CONTROLLER LIB CALLOUT API - This function is called
**                  from the libbt-hci to request for data buffer allocation
**
** Returns          NULL / pointer to allocated buffer
**
******************************************************************************/
static char *alloc(int size)
{
    BT_HDR *p_hdr = NULL;

    /*
    APPL_TRACE_DEBUG1("HC alloc size=%d", size);
    */

    p_hdr = (BT_HDR *) GKI_getbuf ((UINT16) size);

    if (p_hdr == NULL)
    {
        APPL_TRACE_WARNING0("alloc returns NO BUFFER!");
    }

    return ((char *) p_hdr);
}

/******************************************************************************
**
** Function         dealloc
**
** Description      HOST/CONTROLLER LIB CALLOUT API - This function is called
**                  from the libbt-hci to release the data buffer allocated
**                  through the alloc call earlier
**
**                  Bluedroid libbt-hci library uses 'transac' parameter to
**                  pass data-path buffer/packet across bt_hci_lib interface
**                  boundary. The 'p_buf' is not intended to be used here
**                  but might point to data portion of data-path buffer.
**
** Returns          bt_hc_status_t
**
******************************************************************************/
static int dealloc(TRANSAC transac, char *p_buf)
{
    GKI_freebuf(transac);
    return BT_HC_STATUS_SUCCESS;
}

/******************************************************************************
**
** Function         data_ind
**
** Description      HOST/CONTROLLER LIB CALLOUT API - This function is called
**                  from the libbt-hci to pass in the received HCI packets
**
**                  The core stack is responsible for releasing the data buffer
**                  passed in from the libbt-hci once the core stack has done
**                  with it.
**
**                  Bluedroid libbt-hci library uses 'transac' parameter to
**                  pass data-path buffer/packet across bt_hci_lib interface
**                  boundary. The 'p_buf' and 'len' parameters are not intended
**                  to be used here but might point to data portion in data-
**                  path buffer and length of valid data respectively.
**
** Returns          bt_hc_status_t
**
******************************************************************************/
static int data_ind(TRANSAC transac, char *p_buf, int len)
{
    BT_HDR *p_msg = (BT_HDR *) transac;

    /*
    APPL_TRACE_DEBUG2("HC data_ind event=0x%04X (len=%d)", p_msg->event, len);
    */

    GKI_send_msg (BTU_TASK, BTU_HCI_RCV_MBOX, transac);
    return BT_HC_STATUS_SUCCESS;
}

/******************************************************************************
**
** Function         tx_result
**
** Description      HOST/CONTROLLER LIB CALLBACK API - This function is called
**                  from the libbt-hci once it has processed/sent the prior data
**                  buffer which core stack passed to it through transmit_buf
**                  call earlier.
**
**                  The core stack is responsible for releasing the data buffer
**                  if it has been completedly processed.
**
**                  Bluedroid libbt-hci library uses 'transac' parameter to
**                  pass data-path buffer/packet across bt_hci_lib interface
**                  boundary. The 'p_buf' is not intended to be used here
**                  but might point to data portion in data-path buffer.
**
** Returns          bt_hc_status_t
**
******************************************************************************/
static int tx_result(TRANSAC transac, char *p_buf, \
                      bt_hc_transmit_result_t result)
{
    /*
    APPL_TRACE_DEBUG2("HC tx_result %d (event=%04X)", result, \
                      ((BT_HDR *)transac)->event);
    */

    if (result == BT_HC_TX_FRAGMENT)
    {
        GKI_send_msg (BTU_TASK, BTU_HCI_RCV_MBOX, transac);
    }
    else
    {
        GKI_freebuf(transac);
    }

    return BT_HC_STATUS_SUCCESS;
}

/*****************************************************************************
**   The libbt-hci Callback Functions Table
*****************************************************************************/
static const bt_hc_callbacks_t hc_callbacks = {
    sizeof(bt_hc_callbacks_t),
    preload_cb,
    postload_cb,
    lpm_cb,
    hostwake_ind,
    alloc,
    dealloc,
    data_ind,
    tx_result
};

