/******************************************************************************
 *
 *  Copyright (C) 2008-2012 Broadcom Corporation
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
 *  This file contains the implementation of the SMP interface used by
 *  applications that can run over an SMP.
 *
 ******************************************************************************/
#include <string.h>

#include "bt_target.h"
#if SMP_INCLUDED == TRUE
    #include "smp_int.h"
    #include "smp_api.h"
    #include "l2cdefs.h"
    #include "l2c_int.h"
    #include "btm_int.h"
    #include "hcimsgs.h"

    #include "btu.h"


/*******************************************************************************
**
** Function         SMP_Init
**
** Description      This function initializes the SMP unit.
**
** Returns          void
**
*******************************************************************************/
void SMP_Init(void)
{

    SMP_TRACE_EVENT0 ("SMP_Init");
    memset(&smp_cb, 0, sizeof(tSMP_CB));

#if defined(SMP_INITIAL_TRACE_LEVEL)
    smp_cb.trace_level = SMP_INITIAL_TRACE_LEVEL;
#else
    smp_cb.trace_level = BT_TRACE_LEVEL_NONE;    /* No traces */
#endif

    smp_l2cap_if_init();
}


/*******************************************************************************
**
** Function         SMP_SetTraceLevel
**
** Description      This function sets the trace level for SMP.  If called with
**                  a value of 0xFF, it simply returns the current trace level.
**
**                  Input Parameters:
**                      level:  The level to set the GATT tracing to:
**                      0xff-returns the current setting.
**                      0-turns off tracing.
**                      >= 1-Errors.
**                      >= 2-Warnings.
**                      >= 3-APIs.
**                      >= 4-Events.
**                      >= 5-Debug.
**
** Returns          The new or current trace level
**
*******************************************************************************/
SMP_API extern UINT8 SMP_SetTraceLevel (UINT8 new_level)
{
    if (new_level != 0xFF)
        smp_cb.trace_level = new_level;

    return(smp_cb.trace_level);
}


/*******************************************************************************
**
** Function         SMP_Register
**
** Description      This function register for the SMP services callback.
**
** Returns          void
**
*******************************************************************************/
BOOLEAN SMP_Register (tSMP_CALLBACK *p_cback)
{
    SMP_TRACE_EVENT1 ("SMP_Register state=%d", smp_cb.state);

    if (smp_cb.p_callback != NULL)
    {
        SMP_TRACE_ERROR0 ("SMP_Register: duplicate registration, overwrite it");
    }
    smp_cb.p_callback = p_cback;

    return(TRUE);

}

/*******************************************************************************
**
** Function         SMP_Pair
**
** Description      This function call to perform a SMP pairing with peer device.
**                  Device support one SMP pairing at one time.
**
** Parameters       bd_addr - peer device bd address.
**
** Returns          None
**
*******************************************************************************/
tSMP_STATUS SMP_Pair (BD_ADDR bd_addr)
{
    tSMP_CB   *p_cb = &smp_cb;
    UINT8     status = SMP_PAIR_INTERNAL_ERR;

    BTM_TRACE_EVENT2 ("SMP_Pair state=%d flag=0x%x ", p_cb->state, p_cb->flags);
    if (p_cb->state != SMP_ST_IDLE || p_cb->flags & SMP_PAIR_FLAGS_WE_STARTED_DD)
    {
        /* pending security on going, reject this one */
        return SMP_BUSY;
    }
    else
    {
        p_cb->flags = SMP_PAIR_FLAGS_WE_STARTED_DD;

        memcpy (p_cb->pairing_bda, bd_addr, BD_ADDR_LEN);

        if (!L2CA_ConnectFixedChnl (L2CAP_SMP_CID, bd_addr))
        {
            SMP_TRACE_ERROR0("SMP_Pair: L2C connect fixed channel failed.");
            smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &status);
            return status;
        }

        return SMP_STARTED;
    }
}


/*******************************************************************************
**
** Function         SMP_PairCancel
**
** Description      This function call to cancel a SMP pairing with peer device.
**
** Parameters       bd_addr - peer device bd address.
**
** Returns          TRUE - Pairining is cancelled
**
*******************************************************************************/
BOOLEAN SMP_PairCancel (BD_ADDR bd_addr)
{
    tSMP_CB   *p_cb = &smp_cb;
    UINT8     err_code = SMP_PAIR_FAIL_UNKNOWN;
    BOOLEAN   status = FALSE;

    BTM_TRACE_EVENT2 ("SMP_CancelPair state=%d flag=0x%x ", p_cb->state, p_cb->flags);
    if ( (p_cb->state != SMP_ST_IDLE)  &&
         (!memcmp (p_cb->pairing_bda, bd_addr, BD_ADDR_LEN)) )
    {
        p_cb->is_pair_cancel = TRUE;
        SMP_TRACE_DEBUG0("Cancel Pairing: set fail reason Unknown");
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &err_code);
        status = TRUE;
    }

    return status;
}
/*******************************************************************************
**
** Function         SMP_SecurityGrant
**
** Description      This function is called to grant security process.
**
** Parameters       bd_addr - peer device bd address.
**                  res     - result of the operation SMP_SUCCESS if success.
**                            Otherwise, SMP_REPEATED_ATTEMPTS is too many attempts.
**
** Returns          None
**
*******************************************************************************/
void SMP_SecurityGrant(BD_ADDR bd_addr, UINT8 res)
{
    SMP_TRACE_EVENT0 ("SMP_SecurityGrant ");
    if (smp_cb.state != SMP_ST_WAIT_APP_RSP ||
        smp_cb.cb_evt != SMP_SEC_REQUEST_EVT ||
        memcmp (smp_cb.pairing_bda, bd_addr, BD_ADDR_LEN))
        return;

    smp_sm_event(&smp_cb, SMP_API_SEC_GRANT_EVT, &res);
}

/*******************************************************************************
**
** Function         SMP_PasskeyReply
**
** Description      This function is called after Security Manager submitted
**                  passkey request to the application.
**
** Parameters:      bd_addr      - Address of the device for which passkey was requested
**                  res          - result of the operation SMP_SUCCESS if success
**                  passkey - numeric value in the range of
**                  BTM_MIN_PASSKEY_VAL(0) - BTM_MAX_PASSKEY_VAL(999999(0xF423F)).
**
*******************************************************************************/
void SMP_PasskeyReply (BD_ADDR bd_addr, UINT8 res, UINT32 passkey)
{
    tSMP_CB *p_cb = & smp_cb;
    UINT8   failure = SMP_PASSKEY_ENTRY_FAIL;
    tBTM_SEC_DEV_REC *p_dev_rec;

    SMP_TRACE_EVENT2 ("SMP_PasskeyReply: Key: %d  Result:%d",
                      passkey, res);

    /* If timeout already expired or has been canceled, ignore the reply */
    if (p_cb->cb_evt != SMP_PASSKEY_REQ_EVT)
    {
        SMP_TRACE_WARNING1 ("SMP_PasskeyReply() - Wrong State: %d", p_cb->state);
        return;
    }

    if (memcmp (bd_addr, p_cb->pairing_bda, BD_ADDR_LEN) != 0)
    {
        SMP_TRACE_ERROR0 ("SMP_PasskeyReply() - Wrong BD Addr");
        return;
    }

    if ((p_dev_rec = btm_find_dev (bd_addr)) == NULL)
    {
        SMP_TRACE_ERROR0 ("SMP_PasskeyReply() - no dev CB");
        return;
    }


    if (passkey > BTM_MAX_PASSKEY_VAL || res != SMP_SUCCESS)
    {
        SMP_TRACE_WARNING1 ("SMP_PasskeyReply() - Wrong key len: %d or passkey entry fail", passkey);
        /* send pairing failure */
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &failure);

    }
    else
    {
        smp_convert_string_to_tk(p_cb->tk, passkey);
    }

    return;
}

/*******************************************************************************
**
** Function         SMP_OobDataReply
**
** Description      This function is called to provide the OOB data for
**                  SMP in response to SMP_OOB_REQ_EVT
**
** Parameters:      bd_addr     - Address of the peer device
**                  res         - result of the operation SMP_SUCCESS if success
**                  p_data      - simple pairing Randomizer  C.
**
*******************************************************************************/
void SMP_OobDataReply(BD_ADDR bd_addr, tSMP_STATUS res, UINT8 len, UINT8 *p_data)
{
    tSMP_CB *p_cb = & smp_cb;
    UINT8   failure = SMP_OOB_FAIL;
    tSMP_KEY        key;

    SMP_TRACE_EVENT2 ("SMP_OobDataReply State: %d  res:%d",
                      smp_cb.state, res);

    /* If timeout already expired or has been canceled, ignore the reply */
    if (p_cb->state != SMP_ST_WAIT_APP_RSP || p_cb->cb_evt != SMP_OOB_REQ_EVT)
        return;

    if (res != SMP_SUCCESS || len == 0 || !p_data)
    {
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &failure);
    }
    else
    {
        if (len > BT_OCTET16_LEN)
            len = BT_OCTET16_LEN;

        memcpy(p_cb->tk, p_data, len);

        key.key_type    = SMP_KEY_TYPE_TK;
        key.p_data      = p_cb->tk;

        smp_sm_event(&smp_cb, SMP_KEY_READY_EVT, &key);
    }
}

/*******************************************************************************
**
** Function         SMP_Encrypt
**
** Description      This function is called to encrypt the data with the specified
**                  key
**
** Parameters:      key                 - Pointer to key key[0] conatins the MSB
**                  key_len             - key length
**                  plain_text          - Pointer to data to be encrypted
**                                        plain_text[0] conatins the MSB
**                  pt_len              - plain text length
**                  p_out                - output of the encrypted texts
**
**  Returns         Boolean - request is successful
*******************************************************************************/
BOOLEAN SMP_Encrypt (UINT8 *key, UINT8 key_len,
                     UINT8 *plain_text, UINT8 pt_len,
                     tSMP_ENC *p_out)

{
    BOOLEAN status=FALSE;
    status = smp_encrypt_data(key, key_len, plain_text, pt_len, p_out);
    return status;
}
#endif /* SMP_INCLUDED */


