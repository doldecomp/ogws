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
 *  This file contains functions for BLE address management.
 *
 ******************************************************************************/

#include <string.h>

#include "bt_types.h"
#include "hcimsgs.h"
#include "btu.h"
#include "btm_int.h"


#if (defined BLE_INCLUDED && BLE_INCLUDED == TRUE)
    #include "smp_api.h"
    #define BTM_BLE_PRIVATE_ADDR_INT    900             /* 15 minutes minimum for random address refreshing */

/*******************************************************************************
**
** Function         btm_gen_resolve_paddr_cmpl
**
** Description      This is callback functioin when resolvable private address
**                  generation is complete.
**
** Returns          void
**
*******************************************************************************/
static void btm_gen_resolve_paddr_cmpl(tSMP_ENC *p)
{
    tBTM_LE_RANDOM_CB *p_cb = &btm_cb.ble_ctr_cb.addr_mgnt_cb;
    tBTM_BLE_INQ_CB  *p_inq_cb = &btm_cb.ble_ctr_cb.inq_var;
    BTM_TRACE_EVENT0 ("btm_gen_resolve_paddr_cmpl");
    if (p && p->param_buf)
    {
        /* get the high bytes of the random address */
        p_cb->private_addr[2] = p->param_buf[0];
        p_cb->private_addr[1] = p->param_buf[1];
        p_cb->private_addr[0] = p->param_buf[2];
        /* mask off the 1st MSB */
        p_cb->private_addr[0] &= 0xfe;
        /* set the 2nd MSB to be 1 */
        p_cb->private_addr[0] |= 0x02;
        /* set it to controller */
        btsnd_hcic_ble_set_random_addr(p_cb->private_addr);

        p_inq_cb->own_addr_type = BLE_ADDR_RANDOM;

        /* start a periodical timer to refresh random addr */
        btu_stop_timer(&p_cb->raddr_timer_ent);
        btu_start_timer (&p_cb->raddr_timer_ent, BTU_TTYPE_BLE_RANDOM_ADDR,
                         BTM_BLE_PRIVATE_ADDR_INT);

        /* if adv is active, restart adv with new private addr */
        if (p_inq_cb->adv_mode == BTM_BLE_ADV_ENABLE)
        {
            btsnd_hcic_ble_set_adv_enable (BTM_BLE_ADV_DISABLE);

            btsnd_hcic_ble_write_adv_params (p_inq_cb->adv_interval_min,
                                             p_inq_cb->adv_interval_max,
                                             p_inq_cb->evt_type,
                                             p_inq_cb->own_addr_type,
                                             p_inq_cb->direct_bda.type,
                                             p_inq_cb->direct_bda.bda,
                                             p_inq_cb->adv_chnl_map,
                                             p_inq_cb->afp);
        }
    }
    else
    {
        /* random address set failure */
        BTM_TRACE_DEBUG0("set random address failed");
    }
}
/*******************************************************************************
**
** Function         btm_gen_resolve_paddr_low
**
** Description      This function is called when random address has generate the
**                  random number base for low 3 byte bd address.
**
** Returns          void
**
*******************************************************************************/
static void btm_gen_resolve_paddr_low(tBTM_RAND_ENC *p)
{
#if (BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE)
    tBTM_LE_RANDOM_CB *p_cb = &btm_cb.ble_ctr_cb.addr_mgnt_cb;
    tSMP_ENC    output;

    BTM_TRACE_EVENT0 ("btm_gen_resolve_paddr_low");
    if (p && p->param_buf)
    {
        p_cb->private_addr[5] = p->param_buf[0];
        p_cb->private_addr[4] = p->param_buf[1];
        p_cb->private_addr[3] = p->param_buf[2];

        /* encrypt with ur IRK */
        if (!SMP_Encrypt(btm_cb.devcb.id_keys.irk, BT_OCTET16_LEN, p->param_buf, 3, &output))
        {
            btm_gen_resolve_paddr_cmpl(NULL);
        }
        else
        {
            btm_gen_resolve_paddr_cmpl(&output);
        }
    }
#endif
}
/*******************************************************************************
**
** Function         btm_gen_resolvable_private_addr
**
** Description      This function generate a resolvable private address.
**
** Returns          void
**
*******************************************************************************/
void btm_gen_resolvable_private_addr (void)
{
    BTM_TRACE_EVENT0 ("btm_gen_resolvable_private_addr");
    /* generate 3B rand as BD LSB, SRK with it, get BD MSB */
    if (!btsnd_hcic_ble_rand((void *)btm_gen_resolve_paddr_low))
        btm_gen_resolve_paddr_cmpl(NULL);
}
/*******************************************************************************
**
** Function         btm_gen_non_resolve_paddr_cmpl
**
** Description      This is the callback function when non-resolvable private
**                  function is generated and write to controller.
**
** Returns          void
**
*******************************************************************************/
static void btm_gen_non_resolve_paddr_cmpl(tBTM_RAND_ENC *p)
{
    tBTM_LE_RANDOM_CB *p_cb = &btm_cb.ble_ctr_cb.addr_mgnt_cb;
    UINT8   *pp;
    BTM_TRACE_EVENT0 ("btm_gen_non_resolve_paddr_cmpl");
    if (p && p->param_buf)
    {
        pp = p->param_buf;
        STREAM_TO_BDADDR(p_cb->private_addr, pp);
        /* mask off the 2 MSB */
        p_cb->private_addr[0] &= 0xfc;
        /* write to controller */
        btsnd_hcic_ble_set_random_addr(p_cb->private_addr);

        btm_cb.ble_ctr_cb.inq_var.own_addr_type = BLE_ADDR_RANDOM;
    }
    else
    {
        BTM_TRACE_DEBUG0("btm_gen_non_resolvable_private_addr failed");
    }
}
/*******************************************************************************
**
** Function         btm_gen_non_resolvable_private_addr
**
** Description      This function generate a non-resolvable private address.
**
**
** Returns          void
**
*******************************************************************************/
void btm_gen_non_resolvable_private_addr (void)
{
    BTM_TRACE_EVENT0 ("btm_gen_non_resolvable_private_addr");
    if (!btsnd_hcic_ble_rand((void *)btm_gen_non_resolve_paddr_cmpl))
    {
        btm_gen_non_resolve_paddr_cmpl(NULL);
    }
}
    #if SMP_INCLUDED == TRUE
/*******************************************************************************
**  Utility functions for Random address resolving
*******************************************************************************/
/*******************************************************************************
**
** Function         btm_ble_resolve_address_cmpl
**
** Description      This function sends the random address resolving complete
**                  callback.
**
** Returns          None.
**
*******************************************************************************/
static void btm_ble_resolve_address_cmpl(void)
{
    tBTM_LE_RANDOM_CB   *p_mgnt_cb = &btm_cb.ble_ctr_cb.addr_mgnt_cb;
    tBTM_SEC_DEV_REC    *p_dev_rec = NULL;

    BTM_TRACE_EVENT0 ("btm_ble_resolve_address_cmpl");
    if (p_mgnt_cb->index < BTM_SEC_MAX_DEVICE_RECORDS)
        p_dev_rec = &btm_cb.sec_dev_rec[p_mgnt_cb->index];

    p_mgnt_cb->busy = FALSE;

    (* p_mgnt_cb->p_resolve_cback)(p_dev_rec, p_mgnt_cb->p);
}
/*******************************************************************************
**
** Function         btm_ble_proc_resolve_x
**
** Description      This function compares the X with random address 3 MSO bytes
**                  to find a match, if not match, continue for next record.
**
** Returns          None.
**
*******************************************************************************/
static BOOLEAN btm_ble_proc_resolve_x(tSMP_ENC *p)
{
    tBTM_LE_RANDOM_CB   *p_mgnt_cb = &btm_cb.ble_ctr_cb.addr_mgnt_cb;
    UINT8    comp[3];
    BTM_TRACE_EVENT0 ("btm_ble_proc_resolve_x");
    /* compare the hash with 3 LSB of bd address */
    comp[0] = p_mgnt_cb->random_bda[5];
    comp[1] = p_mgnt_cb->random_bda[4];
    comp[2] = p_mgnt_cb->random_bda[3];

    if (p && p->param_buf)
    {
        if (!memcmp(p->param_buf, &comp[0], 3))
        {
            /* match is found */
            BTM_TRACE_EVENT0 ("match is found");
            btm_ble_resolve_address_cmpl();
            return TRUE;
        }
    }
    return FALSE;
}
/*******************************************************************************
**
** Function         btm_ble_match_random_bda
**
** Description      This function match the random address to the appointed device
**                  record, starting from calculating IRK. If record index exceed
**                  the maximum record number, matching failed and send callback.
**
** Returns          None.
**
*******************************************************************************/
static BOOLEAN btm_ble_match_random_bda(UINT16 rec_index)
{
#if (BLE_INCLUDED == TRUE && SMP_INCLUDED == TRUE)
    tBTM_SEC_DEV_REC    *p_dev_rec;
    tBTM_LE_RANDOM_CB   *p_mgnt_cb = &btm_cb.ble_ctr_cb.addr_mgnt_cb;
    UINT8       rand[3];
    tSMP_ENC    output;

    /* use the 3 MSB of bd address as prand */
    rand[0] = p_mgnt_cb->random_bda[2];
    rand[1] = p_mgnt_cb->random_bda[1];
    rand[2] = p_mgnt_cb->random_bda[0];

    BTM_TRACE_EVENT1("btm_ble_match_random_bda rec_index = %d", rec_index);

    if (rec_index < BTM_SEC_MAX_DEVICE_RECORDS)
    {
        p_dev_rec = &btm_cb.sec_dev_rec[rec_index];

        BTM_TRACE_ERROR2("sec_flags = %02x device_type = %d", p_dev_rec->sec_flags, p_dev_rec->device_type);

        if ((p_dev_rec->device_type == BT_DEVICE_TYPE_BLE) &&
            (p_dev_rec->ble.key_type & BTM_LE_KEY_PID))
        {
            /* generate X = E irk(R0, R1, R2) and R is random address 3 LSO */
            SMP_Encrypt(p_dev_rec->ble.keys.irk, BT_OCTET16_LEN,
                        &rand[0], 3, &output);
            return btm_ble_proc_resolve_x(&output);
        }
        else
        {
            // not completed
            return FALSE;
        }
    }
    else /* no  match found */
    {
        btm_ble_resolve_address_cmpl();
        return TRUE;
    }
#endif
}

/*******************************************************************************
**
** Function         btm_ble_resolve_random_addr
**
** Description      This function is called to resolve a random address.
**
** Returns          pointer to the security record of the device whom a random
**                  address is matched to.
**
*******************************************************************************/
void btm_ble_resolve_random_addr(BD_ADDR random_bda, tBTM_BLE_RESOLVE_CBACK * p_cback, void *p)
{
    tBTM_LE_RANDOM_CB   *p_mgnt_cb = &btm_cb.ble_ctr_cb.addr_mgnt_cb;

    BTM_TRACE_EVENT0 ("btm_ble_resolve_random_addr");
    if ( !p_mgnt_cb->busy)
    {
        p_mgnt_cb->p = p;
        p_mgnt_cb->busy = TRUE;
        p_mgnt_cb->index = 0;
        p_mgnt_cb->p_resolve_cback = p_cback;
        memcpy(p_mgnt_cb->random_bda, random_bda, BD_ADDR_LEN);
        /* start to resolve random address */
        /* check for next security record */
        while (TRUE)
        {
            if (btm_ble_match_random_bda(p_mgnt_cb->index++))
            {
                // match found or went through the list
                break;
            }
        }
    }
    else
        (*p_cback)(NULL, p);
}
    #endif
/*******************************************************************************
**  address mapping between pseudo address and real connection address
*******************************************************************************/
/*******************************************************************************
**
** Function         btm_ble_map_bda_to_conn_bda
**
** Description      This function map a BD address to the real connection address
**                  and return the connection address type.
*******************************************************************************/
tBLE_ADDR_TYPE btm_ble_map_bda_to_conn_bda(BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC    *p_dev_rec = NULL;
    BTM_TRACE_EVENT0 ("btm_ble_map_bda_to_conn_bda");
    if ((p_dev_rec = btm_find_dev (bd_addr)) != NULL &&
        p_dev_rec->device_type == BT_DEVICE_TYPE_BLE)
    {
        if (p_dev_rec->ble.ble_addr_type != BLE_ADDR_PUBLIC)
        {
            memcpy(bd_addr, p_dev_rec->ble.static_addr, BD_ADDR_LEN);
        }
        return p_dev_rec->ble.ble_addr_type;
    }
    else
        return BLE_ADDR_PUBLIC;
}
/*******************************************************************************
**
** Function         btm_ble_map_bda_to_pseudo_bda
**
** Description      This function map a BD address to a pseudo address when the
**                  address given is a random address.
**
*******************************************************************************/
void btm_ble_map_bda_to_pseudo_bda(BD_ADDR bd_addr)
{
    BTM_TRACE_EVENT0 ("btm_ble_map_bda_to_pseudo_bda");
}
#endif


