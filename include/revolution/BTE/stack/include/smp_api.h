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
 *  This file contains the SMP API function external definitions.
 *
 ******************************************************************************/
#ifndef SMP_API_H
#define SMP_API_H

#include "bt_target.h"

#define SMP_PIN_CODE_LEN_MAX    PIN_CODE_LEN
#define SMP_PIN_CODE_LEN_MIN    6

/* SMP event type */
#define SMP_IO_CAP_REQ_EVT      1       /* IO capability request event */
#define SMP_SEC_REQUEST_EVT     2       /* SMP pairing request */
#define SMP_PASSKEY_NOTIF_EVT   3       /* passkey notification event */
#define SMP_PASSKEY_REQ_EVT     4       /* passkey request event */
#define SMP_OOB_REQ_EVT         5       /* OOB request event */
#define SMP_COMPLT_EVT          6       /* SMP complete event */
typedef UINT8   tSMP_EVT;


/* pairing failure reason code */
#define SMP_PASSKEY_ENTRY_FAIL      0x01
#define SMP_OOB_FAIL                0x02
#define SMP_PAIR_AUTH_FAIL          0x03
#define SMP_CONFIRM_VALUE_ERR       0x04
#define SMP_PAIR_NOT_SUPPORT        0x05
#define SMP_ENC_KEY_SIZE            0x06
#define SMP_INVALID_CMD             0x07
#define SMP_PAIR_FAIL_UNKNOWN       0x08
#define SMP_REPEATED_ATTEMPTS       0x09
#define SMP_PAIR_FAILURE_MAX        SMP_REPEATED_ATTEMPTS
/* self defined error code */
#define SMP_PAIR_INTERNAL_ERR       0x0A
#define SMP_UNKNOWN_IO_CAP          0x0B    /* unknown IO capability, unable to decide associatino model */
#define SMP_INIT_FAIL               0x0C
#define SMP_CONFIRM_FAIL            0x0D
#define SMP_BUSY                    0x0E
#define SMP_ENC_FAIL                0x0F
#define SMP_STARTED                 0x10
#define SMP_RSP_TIMEOUT             0x11
#define SMP_DIV_NOT_AVAIL           0x12
#define SMP_FAIL                    0x13 /* unspecified failed reason */
#define SMP_SUCCESS                 0

typedef UINT8 tSMP_STATUS;


/* Device IO capability */
#define SMP_IO_CAP_OUT      BTM_IO_CAP_OUT   /* DisplayOnly */
#define SMP_IO_CAP_IO       BTM_IO_CAP_IO   /* DisplayYesNo */
#define SMP_IO_CAP_IN       BTM_IO_CAP_IN   /* KeyboardOnly */
#define SMP_IO_CAP_NONE     BTM_IO_CAP_NONE   /* NoInputNoOutput */
#define SMP_IO_CAP_KBDISP   BTM_IO_CAP_KBDISP   /* Keyboard Display */
#define SMP_IO_CAP_MAX      BTM_IO_CAP_MAX
typedef UINT8  tSMP_IO_CAP;

#ifndef SMP_DEFAULT_IO_CAPS
    #define SMP_DEFAULT_IO_CAPS     SMP_IO_CAP_KBDISP
#endif

/* OOB data present or not */
enum
{
    SMP_OOB_NONE,
    SMP_OOB_PRESENT,
    SMP_OOB_UNKNOWN
};
typedef UINT8  tSMP_OOB_FLAG;

#define SMP_AUTH_NO_BOND        0x00
#define SMP_AUTH_GEN_BOND       0x01 //todo sdh change GEN_BOND to BOND

/* SMP Authentication requirement */
#define SMP_AUTH_YN_BIT           (1 << 2)
#define SMP_AUTH_MASK           (SMP_AUTH_GEN_BOND|SMP_AUTH_YN_BIT)


#define SMP_AUTH_BOND           SMP_AUTH_GEN_BOND

#define SMP_AUTH_NB_ENC_ONLY    0x00 //(SMP_AUTH_MASK | BTM_AUTH_SP_NO)   /* no MITM, No Bonding, Encryptino only */
#define SMP_AUTH_NB_IOCAP       (SMP_AUTH_NO_BOND | SMP_AUTH_YN_BIT)   /* MITM, No Bonding, Use IO Capability
                                        to detrermine authenticaion procedure */
#define SMP_AUTH_GB_ENC_ONLY    (SMP_AUTH_GEN_BOND )   /* no MITM, General Bonding, Encryptino only */
#define SMP_AUTH_GB_IOCAP       (SMP_AUTH_GEN_BOND | SMP_AUTH_YN_BIT)  /* MITM, General Bonding, Use IO Capability
                                        to detrermine authenticaion procedure   */
typedef UINT8 tSMP_AUTH_REQ;

#define SMP_SEC_NONE                 0
#define SMP_SEC_UNAUTHENTICATE      (1 << 0)
#define SMP_SEC_AUTHENTICATED       (1 << 2)
typedef UINT8 tSMP_SEC_LEVEL;

/* SMP key types */
#define SMP_SEC_KEY_TYPE_ENC                (1 << 0)    /* encryption key */
#define SMP_SEC_KEY_TYPE_ID                 (1 << 1)    /* identity key */
#define SMP_SEC_KEY_TYPE_CSRK               (1 << 2)    /* slave CSRK */
typedef UINT8 tSMP_KEYS;

/* default security key distribution value */
#define SMP_SEC_DEFAULT_KEY                  (SMP_SEC_KEY_TYPE_ENC | SMP_SEC_KEY_TYPE_ID | SMP_SEC_KEY_TYPE_CSRK)

/* data type for BTM_SP_IO_REQ_EVT */
typedef struct
{
    tSMP_IO_CAP     io_cap;         /* local IO capabilities */
    tSMP_OOB_FLAG   oob_data;       /* OOB data present (locally) for the peer device */
    tSMP_AUTH_REQ   auth_req;       /* Authentication required (for local device) */
    UINT8           max_key_size;   /* max encryption key size */
    tSMP_KEYS       init_keys;      /* initiator keys to be distributed */
    tSMP_KEYS       resp_keys;      /* responder keys */
} tSMP_IO_REQ;

typedef struct
{
    UINT8       reason;
    UINT8       sec_level;
    BOOLEAN     is_pair_cancel;
} tSMP_CMPL;

typedef union
{
    UINT32          passkey;
    tSMP_IO_REQ     io_req;     /* IO request */
    tSMP_CMPL       cmplt;

}tSMP_EVT_DATA;


/* AES Encryption output */
typedef struct
{
    UINT8   status;
    UINT8   param_len;
    UINT16  opcode;
    UINT8   param_buf[BT_OCTET16_LEN];
} tSMP_ENC;

/* Simple Pairing Events.  Called by the stack when Simple Pairing related
** events occur.
*/
typedef UINT8 (tSMP_CALLBACK) (tSMP_EVT event, BD_ADDR bd_addr, tSMP_EVT_DATA *p_data);

/* callback function for CMAC algorithm
*/
typedef void (tCMAC_CMPL_CBACK)(UINT8 *p_mac, UINT16 tlen, UINT32 sign_counter);

/*****************************************************************************
**  External Function Declarations
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
/* API of SMP */

/*******************************************************************************
**
** Function         SMP_Init
**
** Description      This function initializes the SMP unit.
**
** Returns          void
**
*******************************************************************************/
    SMP_API extern void SMP_Init(void);

/*******************************************************************************
**
** Function         SMP_SetTraceLevel
**
** Description      This function sets the trace level for SMP.  If called with
**                  a value of 0xFF, it simply returns the current trace level.
**
** Returns          The new or current trace level
**
*******************************************************************************/
    SMP_API extern UINT8 SMP_SetTraceLevel (UINT8 new_level);

/*******************************************************************************
**
** Function         SMP_Register
**
** Description      This function register for the SMP service callback.
**
** Returns          void
**
*******************************************************************************/
    SMP_API extern BOOLEAN SMP_Register (tSMP_CALLBACK *p_cback);

/*******************************************************************************
**
** Function         SMP_Pair
**
** Description      This function is called to start a SMP pairing.
**
** Returns          SMP_STARTED if bond started, else otherwise exception.
**
*******************************************************************************/
    SMP_API extern tSMP_STATUS SMP_Pair (BD_ADDR bd_addr);
/*******************************************************************************
**
** Function         SMP_PairCancel
**
** Description      This function is called to cancel a SMP pairing.
**
** Returns          TRUE - pairing cancelled
**
*******************************************************************************/
    SMP_API extern  BOOLEAN SMP_PairCancel (BD_ADDR bd_addr);

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
    SMP_API extern void SMP_SecurityGrant(BD_ADDR bd_addr, UINT8 res);

/*******************************************************************************
**
** Function         SMP_PasskeyReply
**
** Description      This function is called after Security Manager submitted
**                  Passkey request to the application.
**
** Parameters:      bd_addr      - Address of the device for which PIN was requested
**                  res          - result of the operation BTM_SUCCESS if success
**                  passkey      - numeric value in the range of
**                  BTM_MIN_PASSKEY_VAL(0) - BTM_MAX_PASSKEY_VAL(999999(0xF423F)).
**
*******************************************************************************/
    SMP_API extern void SMP_PasskeyReply (BD_ADDR bd_addr, UINT8 res, UINT32 passkey);

/*******************************************************************************
**
** Function         SMP_OobDataReply
**
** Description      This function is called to provide the OOB data for
**                  Simple Pairing in response to BTM_SP_RMT_OOB_EVT
**
** Parameters:      bd_addr     - Address of the peer device
**                  res         - result of the operation SMP_SUCCESS if success
**                  p_data      - simple pairing Randomizer  C.
**
*******************************************************************************/
    SMP_API extern void SMP_OobDataReply(BD_ADDR bd_addr, tSMP_STATUS res, UINT8 len,
                                         UINT8 *p_data);

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
**                  p_out               - pointer to the encrypted outputs
**
**  Returns         Boolean - TRUE: encryption is successful
*******************************************************************************/
    SMP_API extern BOOLEAN SMP_Encrypt (UINT8 *key, UINT8 key_len,
                                        UINT8 *plain_text, UINT8 pt_len,
                                        tSMP_ENC *p_out);

#ifdef __cplusplus
}
#endif
#endif /* SMP_API_H */
