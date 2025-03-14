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

/******************************************************************************
 *
 *  This file contains function of the HCIC unit to format and send HCI
 *  commands.
 *
 ******************************************************************************/

#include "bt_target.h"
#include "gki.h"
#include "hcidefs.h"
#include "hcimsgs.h"
#include "hcidefs.h"
#include "btu.h"

#include <stddef.h>
#include <string.h>

#if (defined BLE_INCLUDED) && (BLE_INCLUDED == TRUE)

BOOLEAN btsnd_hcic_ble_reset(void)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_READ_CMD)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_READ_CMD;
    p->offset = 0;

    UINT16_TO_STREAM (pp,  HCI_BLE_RESET);
    UINT8_TO_STREAM  (pp,  0);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);

}

BOOLEAN btsnd_hcic_ble_set_evt_mask (BT_EVENT_MASK event_mask)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_SET_EVENT_MASK)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_SET_EVENT_MASK;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_SET_EVENT_MASK);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_SET_EVENT_MASK);
    ARRAY8_TO_STREAM (pp, event_mask);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}


BOOLEAN btsnd_hcic_ble_read_buffer_size (void)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_READ_CMD)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_READ_CMD;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_READ_BUFFER_SIZE);
    UINT8_TO_STREAM  (pp,  HCIC_PARAM_SIZE_READ_CMD);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_read_local_spt_feat (void)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_READ_CMD)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_READ_CMD;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_READ_LOCAL_SPT_FEAT);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_READ_CMD);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_set_local_used_feat (UINT8 feat_set[8])
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_SET_USED_FEAT_CMD)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_SET_USED_FEAT_CMD;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_WRITE_LOCAL_SPT_FEAT);
    ARRAY_TO_STREAM (pp, feat_set, HCIC_PARAM_SIZE_SET_USED_FEAT_CMD);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_set_random_addr (BD_ADDR random_bda)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_WRITE_RANDOM_ADDR_CMD)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_WRITE_RANDOM_ADDR_CMD;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_WRITE_RANDOM_ADDR);
    UINT8_TO_STREAM  (pp,  HCIC_PARAM_SIZE_WRITE_RANDOM_ADDR_CMD);

    BDADDR_TO_STREAM (pp, random_bda);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_write_adv_params (UINT16 adv_int_min, UINT16 adv_int_max,
                                       UINT8 adv_type, UINT8 addr_type_own,
                                       UINT8 addr_type_dir, BD_ADDR direct_bda,
                                       UINT8 channel_map, UINT8 adv_filter_policy)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_BLE_WRITE_ADV_PARAMS)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_BLE_WRITE_ADV_PARAMS ;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_WRITE_ADV_PARAMS);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_BLE_WRITE_ADV_PARAMS );

    UINT16_TO_STREAM (pp, adv_int_min);
    UINT16_TO_STREAM (pp, adv_int_max);
    UINT8_TO_STREAM (pp, adv_type);
    UINT8_TO_STREAM (pp, addr_type_own);
    UINT8_TO_STREAM (pp, addr_type_dir);
    BDADDR_TO_STREAM (pp, direct_bda);
    UINT8_TO_STREAM (pp, channel_map);
    UINT8_TO_STREAM (pp, adv_filter_policy);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}
BOOLEAN btsnd_hcic_ble_read_adv_chnl_tx_power (void)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_READ_CMD)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_READ_CMD;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_READ_ADV_CHNL_TX_POWER);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_READ_CMD);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);

}

BOOLEAN btsnd_hcic_ble_set_adv_data (UINT8 data_len, UINT8 *p_data)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_BLE_WRITE_ADV_DATA + 1)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_BLE_WRITE_ADV_DATA + 1;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_WRITE_ADV_DATA);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_BLE_WRITE_ADV_DATA + 1);

    memset(pp, 0, HCIC_PARAM_SIZE_BLE_WRITE_ADV_DATA);

    if (p_data != NULL && data_len > 0)
    {
        if (data_len > HCIC_PARAM_SIZE_BLE_WRITE_ADV_DATA)
            data_len = HCIC_PARAM_SIZE_BLE_WRITE_ADV_DATA;

        UINT8_TO_STREAM (pp, data_len);

        ARRAY_TO_STREAM (pp, p_data, data_len);
    }
    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);

    return (TRUE);
}
BOOLEAN btsnd_hcic_ble_set_scan_rsp_data (UINT8 data_len, UINT8 *p_scan_rsp)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_BLE_WRITE_SCAN_RSP + 1)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_BLE_WRITE_SCAN_RSP + 1;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_WRITE_SCAN_RSP_DATA);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_BLE_WRITE_SCAN_RSP + 1);

    memset(pp, 0, HCIC_PARAM_SIZE_BLE_WRITE_SCAN_RSP);

    if (p_scan_rsp != NULL && data_len > 0)
    {

        if (data_len > HCIC_PARAM_SIZE_BLE_WRITE_SCAN_RSP )
            data_len = HCIC_PARAM_SIZE_BLE_WRITE_SCAN_RSP;

        UINT8_TO_STREAM (pp, data_len);

        ARRAY_TO_STREAM (pp, p_scan_rsp, data_len);
    }

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);

    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_set_adv_enable (UINT8 adv_enable)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_WRITE_ADV_ENABLE)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_WRITE_ADV_ENABLE;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_WRITE_ADV_ENABLE);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_WRITE_ADV_ENABLE);

    UINT8_TO_STREAM (pp, adv_enable);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}
BOOLEAN btsnd_hcic_ble_set_scan_params (UINT8 scan_type,
                                          UINT16 scan_int, UINT16 scan_win,
                                          UINT8 addr_type_own, UINT8 scan_filter_policy)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_BLE_WRITE_SCAN_PARAM)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_BLE_WRITE_SCAN_PARAM;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_WRITE_SCAN_PARAMS);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_BLE_WRITE_SCAN_PARAM);

    UINT8_TO_STREAM (pp, scan_type);
    UINT16_TO_STREAM (pp, scan_int);
    UINT16_TO_STREAM (pp, scan_win);
    UINT8_TO_STREAM (pp, addr_type_own);
    UINT8_TO_STREAM (pp, scan_filter_policy);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_set_scan_enable (UINT8 scan_enable, UINT8 duplicate)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_BLE_WRITE_SCAN_ENABLE)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_BLE_WRITE_SCAN_ENABLE;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_WRITE_SCAN_ENABLE);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_BLE_WRITE_SCAN_ENABLE);

    UINT8_TO_STREAM (pp, scan_enable);
    UINT8_TO_STREAM (pp, duplicate);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

/* link layer connection management commands */
BOOLEAN btsnd_hcic_ble_create_ll_conn (UINT16 scan_int, UINT16 scan_win,
                                       UINT8 init_filter_policy,
                                       UINT8 addr_type_peer, BD_ADDR bda_peer,
                                       UINT8 addr_type_own,
                                       UINT16 conn_int_min, UINT16 conn_int_max,
                                       UINT16 conn_latency, UINT16 conn_timeout,
                                       UINT16 min_ce_len, UINT16 max_ce_len)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_BLE_CREATE_LL_CONN)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_BLE_CREATE_LL_CONN;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_CREATE_LL_CONN);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_BLE_CREATE_LL_CONN);

    UINT16_TO_STREAM (pp, scan_int);
    UINT16_TO_STREAM (pp, scan_win);
    UINT8_TO_STREAM (pp, init_filter_policy);

    UINT8_TO_STREAM (pp, addr_type_peer);
    BDADDR_TO_STREAM (pp, bda_peer);
    UINT8_TO_STREAM (pp, addr_type_own);

    UINT16_TO_STREAM (pp, conn_int_min);
    UINT16_TO_STREAM (pp, conn_int_max);
    UINT16_TO_STREAM (pp, conn_latency);
    UINT16_TO_STREAM (pp, conn_timeout);

    UINT16_TO_STREAM (pp, min_ce_len);
    UINT16_TO_STREAM (pp, max_ce_len);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_create_conn_cancel (void)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_BLE_CREATE_CONN_CANCEL)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_BLE_CREATE_CONN_CANCEL;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_CREATE_CONN_CANCEL);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_BLE_CREATE_CONN_CANCEL);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_read_white_list_size (void)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_READ_CMD)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_READ_CMD;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_READ_WHITE_LIST_SIZE);
    UINT8_TO_STREAM  (pp,  HCIC_PARAM_SIZE_READ_CMD);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_clear_white_list (void)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_CLEAR_WHITE_LIST)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_CLEAR_WHITE_LIST;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_CLEAR_WHITE_LIST);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_CLEAR_WHITE_LIST);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_add_white_list (UINT8 addr_type, BD_ADDR bda)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_ADD_WHITE_LIST)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_ADD_WHITE_LIST;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_ADD_WHITE_LIST);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_ADD_WHITE_LIST);

    UINT8_TO_STREAM (pp, addr_type);
    BDADDR_TO_STREAM (pp, bda);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_remove_from_white_list (UINT8 addr_type, BD_ADDR bda)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_REMOVE_WHITE_LIST)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_REMOVE_WHITE_LIST;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_REMOVE_WHITE_LIST);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_REMOVE_WHITE_LIST);

    UINT8_TO_STREAM (pp, addr_type);
    BDADDR_TO_STREAM (pp, bda);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_upd_ll_conn_params (UINT16 handle,
                                           UINT16 conn_int_min, UINT16 conn_int_max,
                                           UINT16 conn_latency, UINT16 conn_timeout,
                                           UINT16 min_ce_len, UINT16 max_ce_len)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_BLE_UPD_LL_CONN_PARAMS)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_BLE_UPD_LL_CONN_PARAMS;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_UPD_LL_CONN_PARAMS);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_BLE_UPD_LL_CONN_PARAMS);

    UINT16_TO_STREAM (pp, handle);

    UINT16_TO_STREAM (pp, conn_int_min);
    UINT16_TO_STREAM (pp, conn_int_max);
    UINT16_TO_STREAM (pp, conn_latency);
    UINT16_TO_STREAM (pp, conn_timeout);
    UINT16_TO_STREAM (pp, min_ce_len);
    UINT16_TO_STREAM (pp, max_ce_len);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_set_host_chnl_class (UINT8  chnl_map[HCIC_BLE_CHNL_MAP_SIZE])
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_SET_HOST_CHNL_CLASS)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_SET_HOST_CHNL_CLASS;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_SET_HOST_CHNL_CLASS);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_SET_HOST_CHNL_CLASS);

    ARRAY_TO_STREAM (pp, chnl_map, HCIC_BLE_CHNL_MAP_SIZE);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_read_chnl_map (UINT16 handle)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_READ_CHNL_MAP)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_READ_CHNL_MAP;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_READ_CHNL_MAP);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_READ_CHNL_MAP);

    UINT16_TO_STREAM (pp, handle);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_read_remote_feat (UINT16 handle)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_BLE_READ_REMOTE_FEAT)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_BLE_READ_REMOTE_FEAT;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_READ_REMOTE_FEAT);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_BLE_READ_REMOTE_FEAT);

    UINT16_TO_STREAM (pp, handle);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

/* security management commands */
BOOLEAN btsnd_hcic_ble_encrypt (UINT8 *key, UINT8 key_len,
                                UINT8 *plain_text, UINT8 pt_len,
                                void *p_cmd_cplt_cback)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(sizeof(BT_HDR) + sizeof (void *) +
                            HCIC_PARAM_SIZE_BLE_ENCRYPT)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_BLE_ENCRYPT;
    p->offset = sizeof(void *);

    *((void **)pp) = p_cmd_cplt_cback;  /* Store command complete callback in buffer */
    pp += sizeof(void *);               /* Skip over callback pointer */


    UINT16_TO_STREAM (pp, HCI_BLE_ENCRYPT);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_BLE_ENCRYPT);

    memset(pp, 0, HCIC_PARAM_SIZE_BLE_ENCRYPT);

    if (key_len > HCIC_BLE_ENCRYT_KEY_SIZE) key_len = HCIC_BLE_ENCRYT_KEY_SIZE;
    if (pt_len > HCIC_BLE_ENCRYT_KEY_SIZE) pt_len = HCIC_BLE_ENCRYT_KEY_SIZE;

    ARRAY_TO_STREAM (pp, key, key_len);
    pp += (HCIC_BLE_ENCRYT_KEY_SIZE - key_len);
    ARRAY_TO_STREAM (pp, plain_text, pt_len);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_rand (void *p_cmd_cplt_cback)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(sizeof(BT_HDR) + sizeof (void *) +
                        HCIC_PARAM_SIZE_BLE_RAND)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_BLE_RAND;
    p->offset = sizeof(void *);

    *((void **)pp) = p_cmd_cplt_cback;  /* Store command complete callback in buffer */
    pp += sizeof(void *);               /* Skip over callback pointer */

    UINT16_TO_STREAM (pp, HCI_BLE_RAND);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_BLE_RAND);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_start_enc (UINT16 handle, UINT8 rand[HCIC_BLE_RAND_DI_SIZE],
                                UINT16 ediv, UINT8 ltk[HCIC_BLE_ENCRYT_KEY_SIZE])
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_BLE_START_ENC)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_BLE_START_ENC;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_START_ENC);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_BLE_START_ENC);

    UINT16_TO_STREAM (pp, handle);
    ARRAY_TO_STREAM (pp, rand, HCIC_BLE_RAND_DI_SIZE);
    UINT16_TO_STREAM (pp, ediv);
    ARRAY_TO_STREAM (pp, ltk, HCIC_BLE_ENCRYT_KEY_SIZE);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_ltk_req_reply (UINT16 handle, UINT8 ltk[HCIC_BLE_ENCRYT_KEY_SIZE])
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_LTK_REQ_REPLY)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_LTK_REQ_REPLY;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_LTK_REQ_REPLY);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_LTK_REQ_REPLY);

    UINT16_TO_STREAM (pp, handle);
    ARRAY_TO_STREAM (pp, ltk, HCIC_BLE_ENCRYT_KEY_SIZE);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_ltk_req_neg_reply (UINT16 handle)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_LTK_REQ_NEG_REPLY)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_LTK_REQ_NEG_REPLY;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_LTK_REQ_NEG_REPLY);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_LTK_REQ_NEG_REPLY);

    UINT16_TO_STREAM (pp, handle);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

BOOLEAN btsnd_hcic_ble_read_supported_states (void)
{
    BT_HDR *p;
    UINT8 *pp;

    if ((p = HCI_GET_CMD_BUF(HCIC_PARAM_SIZE_READ_CMD)) == NULL)
        return (FALSE);

    pp = (UINT8 *)(p + 1);

    p->len    = HCIC_PREAMBLE_SIZE + HCIC_PARAM_SIZE_READ_CMD;
    p->offset = 0;

    UINT16_TO_STREAM (pp, HCI_BLE_READ_SUPPORTED_STATES);
    UINT8_TO_STREAM  (pp, HCIC_PARAM_SIZE_READ_CMD);

    btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID,  p);
    return (TRUE);
}

#endif
