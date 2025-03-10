/******************************************************************************
 *
 *  Copyright (C) 2006-2012 Broadcom Corporation
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
 *  This is the public interface file the BTA Java I/F
 *
 ******************************************************************************/
#ifndef BTA_JV_API_H
#define BTA_JV_API_H

#include "data_types.h"
#include "bt_target.h"
#include "bt_types.h"
#include "bta_api.h"
#include "btm_api.h"
/*****************************************************************************
**  Constants and data types
*****************************************************************************/
/* status values */
#define BTA_JV_SUCCESS             0            /* Successful operation. */
#define BTA_JV_FAILURE             1            /* Generic failure. */
#define BTA_JV_BUSY                2            /* Temporarily can not handle this request. */
#define BTA_JV_NO_DATA             3            /* no data. */

typedef UINT8 tBTA_JV_STATUS;
#define BTA_JV_INTERNAL_ERR        (-1) /* internal error. */

#define BTA_JV_MAX_UUIDS        SDP_MAX_UUID_FILTERS
#define BTA_JV_MAX_ATTRS        SDP_MAX_ATTR_FILTERS
#define BTA_JV_MAX_SDP_REC      SDP_MAX_RECORDS
#if SDP_FOR_JV_INCLUDED == TRUE
#define BTA_JV_MAX_L2C_CONN     (GAP_MAX_CONNECTIONS + 1)
#else
#define BTA_JV_MAX_L2C_CONN     GAP_MAX_CONNECTIONS
#endif
#define BTA_JV_MAX_SCN          PORT_MAX_RFC_PORTS /* same as BTM_MAX_SCN (in btm_int.h) */
#define BTA_JV_MAX_RFC_CONN     MAX_RFC_PORTS

#ifndef BTA_JV_DEF_RFC_MTU
#define BTA_JV_DEF_RFC_MTU      (3*330)
#endif

/* */
#ifndef BTA_JV_MAX_RFC_SR_SESSION
#define BTA_JV_MAX_RFC_SR_SESSION   3
#endif

/* BTA_JV_MAX_RFC_SR_SESSION can not be bigger than MAX_BD_CONNECTIONS */
#if (BTA_JV_MAX_RFC_SR_SESSION > MAX_BD_CONNECTIONS)
#undef BTA_JV_MAX_RFC_SR_SESSION
#define BTA_JV_MAX_RFC_SR_SESSION   MAX_BD_CONNECTIONS
#endif

#define BTA_JV_FIRST_SERVICE_ID BTA_FIRST_JV_SERVICE_ID
#define BTA_JV_LAST_SERVICE_ID  BTA_LAST_JV_SERVICE_ID
#define BTA_JV_NUM_SERVICE_ID   (BTA_LAST_JV_SERVICE_ID - BTA_FIRST_JV_SERVICE_ID + 1)

/* Discoverable modes */
enum
{
    BTA_JV_DISC_NONE,
    BTA_JV_DISC_LIMITED,
    BTA_JV_DISC_GENERAL
};
typedef UINT16 tBTA_JV_DISC;

/* Security Mode (BTA_JvGetSecurityMode) */
#define BTA_JV_SEC_MODE_UNDEFINED   BTM_SEC_MODE_UNDEFINED  /* 0 */
#define BTA_JV_SEC_MODE_NONE        BTM_SEC_MODE_NONE       /* 1 */
#define BTA_JV_SEC_MODE_SERVICE     BTM_SEC_MODE_SERVICE    /* 2 */
#define BTA_JV_SEC_MODE_LINK        BTM_SEC_MODE_LINK       /* 3 */
#define BTA_JV_SEC_MODE_SP          BTM_SEC_MODE_SP         /* 4 */
#define BTA_JV_SEC_MODE_SP_DEBUG    BTM_SEC_MODE_SP_DEBUG   /* 5 */
typedef UINT8 tBTA_JV_SEC_MODE;

#define BTA_JV_ROLE_SLAVE       BTM_ROLE_SLAVE
#define BTA_JV_ROLE_MASTER      BTM_ROLE_MASTER
typedef UINT32 tBTA_JV_ROLE;

#define BTA_JV_SERVICE_LMTD_DISCOVER    BTM_COD_SERVICE_LMTD_DISCOVER   /* 0x0020 */
#define BTA_JV_SERVICE_POSITIONING      BTM_COD_SERVICE_POSITIONING     /* 0x0100 */
#define BTA_JV_SERVICE_NETWORKING       BTM_COD_SERVICE_NETWORKING      /* 0x0200 */
#define BTA_JV_SERVICE_RENDERING        BTM_COD_SERVICE_RENDERING       /* 0x0400 */
#define BTA_JV_SERVICE_CAPTURING        BTM_COD_SERVICE_CAPTURING       /* 0x0800 */
#define BTA_JV_SERVICE_OBJ_TRANSFER     BTM_COD_SERVICE_OBJ_TRANSFER    /* 0x1000 */
#define BTA_JV_SERVICE_AUDIO            BTM_COD_SERVICE_AUDIO           /* 0x2000 */
#define BTA_JV_SERVICE_TELEPHONY        BTM_COD_SERVICE_TELEPHONY       /* 0x4000 */
#define BTA_JV_SERVICE_INFORMATION      BTM_COD_SERVICE_INFORMATION     /* 0x8000 */



/* Java I/F callback events */
/* events received by tBTA_JV_DM_CBACK */
#define BTA_JV_ENABLE_EVT           0  /* JV enabled */
#define BTA_JV_SET_DISCOVER_EVT     1  /* the result for BTA_JvSetDiscoverability */
#define BTA_JV_LOCAL_ADDR_EVT       2  /* Local device address */
#define BTA_JV_LOCAL_NAME_EVT       3  /* Local device name */
#define BTA_JV_REMOTE_NAME_EVT      4  /* Remote device name */
#define BTA_JV_SET_ENCRYPTION_EVT   5  /* Set Encryption */
#define BTA_JV_GET_SCN_EVT          6  /* Reserved an SCN */
#define BTA_JV_GET_PSM_EVT          7  /* Reserved a PSM */
#define BTA_JV_DISCOVERY_COMP_EVT   8  /* SDP discovery complete */
#define BTA_JV_SERVICES_LEN_EVT     9  /* the result for BTA_JvGetServicesLength */
#define BTA_JV_SERVICE_SEL_EVT      10 /* the result for BTA_JvServiceSelect */
#define BTA_JV_CREATE_RECORD_EVT    11 /* the result for BTA_JvCreateRecord */
#define BTA_JV_UPDATE_RECORD_EVT    12 /* the result for BTA_JvUpdateRecord */
#define BTA_JV_ADD_ATTR_EVT         13 /* the result for BTA_JvAddAttribute */
#define BTA_JV_DELETE_ATTR_EVT      14 /* the result for BTA_JvDeleteAttribute */
#define BTA_JV_CANCEL_DISCVRY_EVT   15 /* the result for BTA_JvCancelDiscovery */

/* events received by tBTA_JV_L2CAP_CBACK */
#define BTA_JV_L2CAP_OPEN_EVT       16 /* open status of L2CAP connection */
#define BTA_JV_L2CAP_CLOSE_EVT      17 /* L2CAP connection closed */
#define BTA_JV_L2CAP_START_EVT      18 /* L2CAP server started */
#define BTA_JV_L2CAP_CL_INIT_EVT    19 /* L2CAP client initiated a connection */
#define BTA_JV_L2CAP_DATA_IND_EVT   20 /* L2CAP connection received data */
#define BTA_JV_L2CAP_CONG_EVT       21 /* L2CAP connection congestion status changed */
#define BTA_JV_L2CAP_READ_EVT       22 /* the result for BTA_JvL2capRead */
#define BTA_JV_L2CAP_RECEIVE_EVT    23 /* the result for BTA_JvL2capReceive*/
#define BTA_JV_L2CAP_WRITE_EVT      24 /* the result for BTA_JvL2capWrite*/

/* events received by tBTA_JV_RFCOMM_CBACK */
#define BTA_JV_RFCOMM_OPEN_EVT      25 /* open status of RFCOMM Client connection */
#define BTA_JV_RFCOMM_CLOSE_EVT     26 /* RFCOMM connection closed */
#define BTA_JV_RFCOMM_START_EVT     27 /* RFCOMM server started */
#define BTA_JV_RFCOMM_CL_INIT_EVT   28 /* RFCOMM client initiated a connection */
#define BTA_JV_RFCOMM_DATA_IND_EVT  29 /* RFCOMM connection received data */
#define BTA_JV_RFCOMM_CONG_EVT      30 /* RFCOMM connection congestion status changed */
#define BTA_JV_RFCOMM_READ_EVT      31 /* the result for BTA_JvRfcommRead */
#define BTA_JV_RFCOMM_WRITE_EVT     32 /* the result for BTA_JvRfcommWrite*/
#define BTA_JV_RFCOMM_SRV_OPEN_EVT  33 /* open status of Server RFCOMM connection */
#define BTA_JV_MAX_EVT              34 /* max number of JV events */

typedef UINT16 tBTA_JV_EVT;

/* data associated with BTA_JV_SET_DISCOVER_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    tBTA_JV_DISC    disc_mode;  /* The current discoverable mode */
} tBTA_JV_SET_DISCOVER;

/* data associated with BTA_JV_DISCOVERY_COMP_EVT_ */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    int scn;                    /* channel # */
} tBTA_JV_DISCOVERY_COMP;

/* data associated with BTA_JV_SET_ENCRYPTION_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    BD_ADDR     bd_addr;        /* The peer address */
} tBTA_JV_SET_ENCRYPTION;

/* data associated with BTA_JV_SERVICES_LEN_EVT */
typedef struct
{
    INT32       num_services;       /* -1, if error. Otherwise, the number of
                                     * services collected from peer */
    UINT16      *p_services_len;    /* this points the same location as the
                                     * parameter in BTA_JvGetServicesLength() */
} tBTA_JV_SERVICES_LEN;

/* data associated with BTA_JV_SERVICE_SEL_EVT */
typedef struct
{
    BD_ADDR     bd_addr;            /* The peer address */
    UINT16      service_len;        /* the length of this record */
} tBTA_JV_SERVICE_SEL;

/* data associated with BTA_JV_CREATE_RECORD_EVT */
typedef struct
{
   tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
} tBTA_JV_CREATE_RECORD;

/* data associated with BTA_JV_UPDATE_RECORD_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The SDP record handle was updated */
} tBTA_JV_UPDATE_RECORD;

/* data associated with BTA_JV_ADD_ATTR_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The SDP record handle was updated */
} tBTA_JV_ADD_ATTR;

/* data associated with BTA_JV_DELETE_ATTR_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The SDP record handle was updated */
} tBTA_JV_DELETE_ATTR;

/* data associated with BTA_JV_L2CAP_OPEN_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The connection handle */
    BD_ADDR         rem_bda;    /* The peer address */
    INT32           tx_mtu;     /* The transmit MTU */
} tBTA_JV_L2CAP_OPEN;

/* data associated with BTA_JV_L2CAP_CLOSE_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The connection handle */
    BOOLEAN         async;      /* FALSE, if local initiates disconnect */
} tBTA_JV_L2CAP_CLOSE;

/* data associated with BTA_JV_L2CAP_START_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The connection handle */
    UINT8           sec_id;     /* security ID used by this server */
} tBTA_JV_L2CAP_START;

/* data associated with BTA_JV_L2CAP_CL_INIT_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The connection handle */
    UINT8           sec_id;     /* security ID used by this client */
} tBTA_JV_L2CAP_CL_INIT;

/* data associated with BTA_JV_L2CAP_CONG_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The connection handle */
    BOOLEAN         cong;       /* TRUE, congested. FALSE, uncongested */
} tBTA_JV_L2CAP_CONG;

/* data associated with BTA_JV_L2CAP_READ_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The connection handle */
    UINT32          req_id;     /* The req_id in the associated BTA_JvL2capRead() */
    UINT8           *p_data;    /* This points the same location as the p_data
                                 * parameter in BTA_JvL2capRead () */
    UINT16          len;        /* The length of the data read. */
} tBTA_JV_L2CAP_READ;

/* data associated with BTA_JV_L2CAP_RECEIVE_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The connection handle */
    UINT32          req_id;     /* The req_id in the associated BTA_JvL2capReceive() */
    UINT8           *p_data;    /* This points the same location as the p_data
                                 * parameter in BTA_JvL2capReceive () */
    UINT16          len;        /* The length of the data read. */
} tBTA_JV_L2CAP_RECEIVE;

/* data associated with BTA_JV_L2CAP_WRITE_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The connection handle */
    UINT32          req_id;     /* The req_id in the associated BTA_JvL2capWrite() */
    UINT16          len;        /* The length of the data written. */
    BOOLEAN         cong;       /* congestion status */
} tBTA_JV_L2CAP_WRITE;

/* data associated with BTA_JV_RFCOMM_OPEN_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The connection handle */
    BD_ADDR         rem_bda;    /* The peer address */
} tBTA_JV_RFCOMM_OPEN;
/* data associated with BTA_JV_RFCOMM_SRV_OPEN_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;             /* Whether the operation succeeded or failed. */
    UINT32          handle;             /* The connection handle */
    UINT32          new_listen_handle;  /* The new listen handle */
    BD_ADDR         rem_bda;            /* The peer address */
} tBTA_JV_RFCOMM_SRV_OPEN;


/* data associated with BTA_JV_RFCOMM_CLOSE_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;      /* Whether the operation succeeded or failed. */
    UINT32          port_status; /* PORT status */
    UINT32          handle;      /* The connection handle */
    BOOLEAN         async;       /* FALSE, if local initiates disconnect */
} tBTA_JV_RFCOMM_CLOSE;

/* data associated with BTA_JV_RFCOMM_START_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The connection handle */
    UINT8           sec_id;     /* security ID used by this server */
    BOOLEAN         use_co;     /* TRUE to use co_rfc_data */
} tBTA_JV_RFCOMM_START;

/* data associated with BTA_JV_RFCOMM_CL_INIT_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The connection handle */
    UINT8           sec_id;     /* security ID used by this client */
    BOOLEAN         use_co;     /* TRUE to use co_rfc_data */
} tBTA_JV_RFCOMM_CL_INIT;
/*data associated with BTA_JV_L2CAP_DATA_IND_EVT & BTA_JV_RFCOMM_DATA_IND_EVT */
typedef struct
{
    UINT32          handle;     /* The connection handle */
} tBTA_JV_DATA_IND;

/* data associated with BTA_JV_RFCOMM_CONG_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The connection handle */
    BOOLEAN         cong;       /* TRUE, congested. FALSE, uncongested */
} tBTA_JV_RFCOMM_CONG;

/* data associated with BTA_JV_RFCOMM_READ_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The connection handle */
    UINT32          req_id;     /* The req_id in the associated BTA_JvRfcommRead() */
    UINT8           *p_data;    /* This points the same location as the p_data
                                 * parameter in BTA_JvRfcommRead () */
    UINT16          len;        /* The length of the data read. */
} tBTA_JV_RFCOMM_READ;

/* data associated with BTA_JV_RFCOMM_WRITE_EVT */
typedef struct
{
    tBTA_JV_STATUS  status;     /* Whether the operation succeeded or failed. */
    UINT32          handle;     /* The connection handle */
    UINT32          req_id;     /* The req_id in the associated BTA_JvRfcommWrite() */
    int             len;        /* The length of the data written. */
    BOOLEAN         cong;       /* congestion status */
} tBTA_JV_RFCOMM_WRITE;


/* union of data associated with JV callback */
typedef union
{
    tBTA_JV_STATUS          status;         /* BTA_JV_ENABLE_EVT */
    tBTA_JV_DISCOVERY_COMP  disc_comp;      /* BTA_JV_DISCOVERY_COMP_EVT */
    tBTA_JV_SET_DISCOVER    set_discover;   /* BTA_JV_SET_DISCOVER_EVT */
    tBTA_JV_SET_ENCRYPTION  set_encrypt;    /* BTA_JV_SET_ENCRYPTION_EVT */
    BD_ADDR                 bd_addr;        /* BTA_JV_LOCAL_ADDR_EVT */
    UINT8                   *p_name;        /* BTA_JV_LOCAL_NAME_EVT,
                                               BTA_JV_REMOTE_NAME_EVT */
    UINT8                   scn;            /* BTA_JV_GET_SCN_EVT */
    UINT16                  psm;            /* BTA_JV_GET_PSM_EVT */
    tBTA_JV_SERVICES_LEN    servs_len;      /* BTA_JV_SERVICES_LEN_EVT */
    tBTA_JV_SERVICE_SEL     serv_sel;       /* BTA_JV_SERVICE_SEL_EVT */
    tBTA_JV_CREATE_RECORD   create_rec;     /* BTA_JV_CREATE_RECORD_EVT */
    tBTA_JV_UPDATE_RECORD   update_rec;     /* BTA_JV_UPDATE_RECORD_EVT */
    tBTA_JV_ADD_ATTR        add_attr;       /* BTA_JV_ADD_ATTR_EVT */
    tBTA_JV_DELETE_ATTR     del_attr;       /* BTA_JV_DELETE_ATTR_EVT */
    tBTA_JV_L2CAP_OPEN      l2c_open;       /* BTA_JV_L2CAP_OPEN_EVT */
    tBTA_JV_L2CAP_CLOSE     l2c_close;      /* BTA_JV_L2CAP_CLOSE_EVT */
    tBTA_JV_L2CAP_START     l2c_start;      /* BTA_JV_L2CAP_START_EVT */
    tBTA_JV_L2CAP_CL_INIT   l2c_cl_init;    /* BTA_JV_L2CAP_CL_INIT_EVT */
    tBTA_JV_L2CAP_CONG      l2c_cong;       /* BTA_JV_L2CAP_CONG_EVT */
    tBTA_JV_L2CAP_READ      l2c_read;       /* BTA_JV_L2CAP_READ_EVT */
    tBTA_JV_L2CAP_WRITE     l2c_write;      /* BTA_JV_L2CAP_WRITE_EVT */
    tBTA_JV_RFCOMM_OPEN     rfc_open;       /* BTA_JV_RFCOMM_OPEN_EVT */
    tBTA_JV_RFCOMM_SRV_OPEN rfc_srv_open;   /* BTA_JV_RFCOMM_SRV_OPEN_EVT */
    tBTA_JV_RFCOMM_CLOSE    rfc_close;      /* BTA_JV_RFCOMM_CLOSE_EVT */
    tBTA_JV_RFCOMM_START    rfc_start;      /* BTA_JV_RFCOMM_START_EVT */
    tBTA_JV_RFCOMM_CL_INIT  rfc_cl_init;    /* BTA_JV_RFCOMM_CL_INIT_EVT */
    tBTA_JV_RFCOMM_CONG     rfc_cong;       /* BTA_JV_RFCOMM_CONG_EVT */
    tBTA_JV_RFCOMM_READ     rfc_read;       /* BTA_JV_RFCOMM_READ_EVT */
    tBTA_JV_RFCOMM_WRITE    rfc_write;      /* BTA_JV_RFCOMM_WRITE_EVT */
    tBTA_JV_DATA_IND        data_ind;    /* BTA_JV_L2CAP_DATA_IND_EVT
                                               BTA_JV_RFCOMM_DATA_IND_EVT */
} tBTA_JV;

/* JAVA DM Interface callback */
typedef void (tBTA_JV_DM_CBACK)(tBTA_JV_EVT event, tBTA_JV *p_data, void * user_data);

/* JAVA RFCOMM interface callback */
typedef void* (tBTA_JV_RFCOMM_CBACK)(tBTA_JV_EVT event, tBTA_JV *p_data, void *user_data);

/* JAVA L2CAP interface callback */
typedef void (tBTA_JV_L2CAP_CBACK)(tBTA_JV_EVT event, tBTA_JV *p_data);

/* JV configuration structure */
typedef struct
{
    UINT16  sdp_raw_size;           /* The size of p_sdp_raw_data */
    UINT16  sdp_db_size;            /* The size of p_sdp_db */
    UINT8   *p_sdp_raw_data;        /* The data buffer to keep raw data */
    tSDP_DISCOVERY_DB   *p_sdp_db;  /* The data buffer to keep SDP database */
} tBTA_JV_CFG;

/*****************************************************************************
**  External Function Declarations
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**
** Function         BTA_JvEnable
**
** Description      Enable the Java I/F service. When the enable
**                  operation is complete the callback function will be
**                  called with a BTA_JV_ENABLE_EVT. This function must
**                  be called before other functions in the JV API are
**                  called.
**
** Returns          BTA_JV_SUCCESS if successful.
**                  BTA_JV_FAIL if internal failure.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvEnable(tBTA_JV_DM_CBACK *p_cback);

/*******************************************************************************
**
** Function         BTA_JvDisable
**
** Description      Disable the Java I/F
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void BTA_JvDisable(void);

/*******************************************************************************
**
** Function         BTA_JvIsEnable
**
** Description      Get the JV registration status.
**
** Returns          TRUE, if registered
**
*******************************************************************************/
BTA_API extern BOOLEAN BTA_JvIsEnable(void);

/*******************************************************************************
**
** Function         BTA_JvSetDiscoverability
**
** Description      This function sets the Bluetooth  discoverable modes
**                  of the local device.  This controls whether other
**                  Bluetooth devices can find the local device.
**
**                  When the operation is complete the tBTA_JV_DM_CBACK callback
**                  function will be called with a BTA_JV_SET_DISCOVER_EVT.
**
** Returns          BTA_JV_SUCCESS if successful.
**                  BTA_JV_FAIL if internal failure.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvSetDiscoverability(tBTA_JV_DISC disc_mode);

/*******************************************************************************
**
** Function         BTA_JvGetDiscoverability
**
** Description      This function gets the Bluetooth
**                  discoverable modes of local device
**
** Returns          The current Bluetooth discoverable mode.
**
*******************************************************************************/
BTA_API extern tBTA_JV_DISC BTA_JvGetDiscoverability(void);

/*******************************************************************************
**
** Function         BTA_JvGetLocalDeviceAddr
**
** Description      This function obtains the local Bluetooth device address.
**                  The local Bluetooth device address is reported by the
**                  tBTA_JV_DM_CBACK callback with a BTA_JV_LOCAL_ADDR_EVT.
**
** Returns          BTA_JV_SUCCESS if successful.
**                  BTA_JV_FAIL if internal failure.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvGetLocalDeviceAddr(void);

/*******************************************************************************
**
** Function         BTA_JvGetLocalDeviceName
**
** Description      This function obtains the name of the local device
**                  The local Bluetooth device name is reported by the
**                  tBTA_JV_DM_CBACK callback with a BTA_JV_LOCAL_NAME_EVT.
**
** Returns          BTA_JV_SUCCESS if successful.
**                  BTA_JV_FAIL if internal failure.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvGetLocalDeviceName(void);

/*******************************************************************************
**
** Function         BTA_JvGetRemoteDeviceName
**
** Description      This function obtains the name of the specified device.
**                  The Bluetooth device name is reported by the
**                  tBTA_JV_DM_CBACK callback with a BTA_JV_REMOTE_NAME_EVT.
**
** Returns          BTA_JV_SUCCESS if successful.
**                  BTA_JV_FAIL if internal failure.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvGetRemoteDeviceName(BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         BTA_JvGetPreknownDevice
**
** Description      This function obtains the Bluetooth address in the inquiry
**                  database collected via the previous call to BTA_DmSearch().
**
** Returns          The number of preknown devices if p_bd_addr is NULL
**                  BTA_JV_SUCCESS if successful.
**                  BTA_JV_INTERNAL_ERR(-1) if internal failure.
**
*******************************************************************************/
BTA_API extern INT32 BTA_JvGetPreknownDevice(UINT8 * p_bd_addr, UINT32 index);

/*******************************************************************************
**
** Function         BTA_JvGetDeviceClass
**
** Description      This function obtains the local Class of Device.
**
** Returns          DEV_CLASS, A three-byte array of UINT8 that contains the
**                  Class of Device information. The definitions are in the
**                  "Bluetooth Assigned Numbers".
**
*******************************************************************************/
BTA_API extern UINT8 * BTA_JvGetDeviceClass(void);

/*******************************************************************************
**
** Function         BTA_JvSetServiceClass
**
** Description      This function sets the service class of local Class of Device
**
** Returns          BTA_JV_SUCCESS if successful.
**                  BTA_JV_FAIL if internal failure.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvSetServiceClass(UINT32 service);

/*******************************************************************************
**
** Function         BTA_JvSetEncryption
**
** Description      This function ensures that the connection to the given device
**                  is encrypted.
**                  When the operation is complete the tBTA_JV_DM_CBACK callback
**                  function will be called with a BTA_JV_SET_ENCRYPTION_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvSetEncryption(BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         BTA_JvIsAuthenticated
**
** Description      This function checks if the peer device is authenticated
**
** Returns          TRUE if authenticated.
**                  FALSE if not.
**
*******************************************************************************/
BTA_API extern BOOLEAN BTA_JvIsAuthenticated(BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         BTA_JvIsTrusted
**
** Description      This function checks if the peer device is trusted
**                  (previously paired)
**
** Returns          TRUE if trusted.
**                  FALSE if not.
**
*******************************************************************************/
BTA_API extern BOOLEAN BTA_JvIsTrusted(BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         BTA_JvIsAuthorized
**
** Description      This function checks if the peer device is authorized
**
** Returns          TRUE if authorized.
**                  FALSE if not.
**
*******************************************************************************/
BTA_API extern BOOLEAN BTA_JvIsAuthorized(BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         BTA_JvIsEncrypted
**
** Description      This function checks if the link to peer device is encrypted
**
** Returns          TRUE if encrypted.
**                  FALSE if not.
**
*******************************************************************************/
BTA_API extern BOOLEAN BTA_JvIsEncrypted(BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         BTA_JvGetSecurityMode
**
** Description      This function returns the current Bluetooth security mode
**                  of the local device
**
** Returns          The current Bluetooth security mode.
**
*******************************************************************************/
BTA_API extern tBTA_JV_SEC_MODE BTA_JvGetSecurityMode(void);

/* BTA_JvIsMaster is replaced by BTA_DmIsMaster */

/*******************************************************************************
**
** Function         BTA_JvGetSCN
**
** Description      This function reserves a SCN (server channel number) for
**                  applications running over RFCOMM. It is primarily called by
**                  server profiles/applications to register their SCN into the
**                  SDP database. The SCN is reported by the tBTA_JV_DM_CBACK
**                  callback with a BTA_JV_GET_SCN_EVT.
**                  If the SCN reported is 0, that means all SCN resources are
**                  exhausted.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvGetSCN(void);

/*******************************************************************************
**
** Function         BTA_JvFreeSCN
**
** Description      This function frees a server channel number that was used
**                  by an application running over RFCOMM.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvFreeSCN(UINT8 scn);

/*******************************************************************************
**
** Function         BTA_JvGetPSM
**
** Description      This function reserves a PSM (Protocol Service Multiplexer)
**                  applications running over L2CAP. It is primarily called by
**                  server profiles/applications to register their PSM into the
**                  SDP database.
**
** Returns          The next free PSM
**
*******************************************************************************/
BTA_API extern UINT16 BTA_JvGetPSM(void);

/*******************************************************************************
**
** Function         BTA_JvStartDiscovery
**
** Description      This function performs service discovery for the services
**                  provided by the given peer device. When the operation is
**                  complete the tBTA_JV_DM_CBACK callback function will be
**                  called with a BTA_JV_DISCOVERY_COMP_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvStartDiscovery(BD_ADDR bd_addr, UINT16 num_uuid,
                           tSDP_UUID *p_uuid_list, void* user_data);

/*******************************************************************************
**
** Function         BTA_JvCancelDiscovery
**
** Description      This function cancels an active service discovery.
**                  When the operation is
**                  complete the tBTA_JV_DM_CBACK callback function will be
**                  called with a BTA_JV_CANCEL_DISCVRY_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvCancelDiscovery(void * user_data);

/*******************************************************************************
**
** Function         BTA_JvGetServicesLength
**
** Description      This function obtains the number of services and the length
**                  of each service found in the SDP database (result of last
**                  BTA_JvStartDiscovery().When the operation is complete the
**                  tBTA_JV_DM_CBACK callback function will be called with a
**                  BTA_JV_SERVICES_LEN_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvGetServicesLength(BOOLEAN inc_hdr, UINT16 *p_services_len);

/*******************************************************************************
**
** Function         BTA_JvGetServicesResult
**
** Description      This function returns a number of service records found
**                  during current service search, equals to the number returned
**                  by previous call to BTA_JvGetServicesLength.
**                  The contents of each SDP record will be returned under a
**                  TLV (type, len, value) representation in the data buffer
**                  provided by the caller.
**
** Returns          -1, if error. Otherwise, the number of services
**
*******************************************************************************/
BTA_API extern INT32 BTA_JvGetServicesResult(BOOLEAN inc_hdr, UINT8 **TLVs);

/*******************************************************************************
**
** Function         BTA_JvServiceSelect
**
** Description      This function checks if the SDP database contains the given
**                  service UUID. When the operation is complete the
**                  tBTA_JV_DM_CBACK callback function will be called with a
**                  BTA_JV_SERVICE_SEL_EVT with the length of the service record.
**                  If the service is not found or error, -1 is reported.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvServiceSelect(UINT16 uuid);

/*******************************************************************************
**
** Function         BTA_JvServiceResult
**
** Description      This function returns the contents of the SDP record from
**                  last BTA_JvServiceSelect. The contents will be returned under
**                  a TLV (type, len, value) representation in the data buffer
**                  provided by the caller.
**
** Returns          -1, if error. Otherwise, the length of service record.
**
*******************************************************************************/
BTA_API extern INT32 BTA_JvServiceResult(UINT8 *TLV);

/*******************************************************************************
**
** Function         BTA_JvCreateRecord
**
** Description      Create a service record in the local SDP database by user in
**                  tBTA_JV_DM_CBACK callback with a BTA_JV_CREATE_RECORD_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvCreateRecordByUser(void* user_data);

/*******************************************************************************
**
** Function         BTA_JvUpdateRecord
**
** Description      Update a service record in the local SDP database.
**                  When the operation is complete the tBTA_JV_DM_CBACK callback
**                  function will be called with a BTA_JV_UPDATE_RECORD_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvUpdateRecord(UINT32 handle, UINT16 *p_ids,
                           UINT8 **p_values, INT32 *p_value_sizes, INT32 array_len);

/*******************************************************************************
**
** Function         BTA_JvAddAttribute
**
** Description      Add an attribute to a service record in the local SDP database.
**                  When the operation is complete the tBTA_JV_DM_CBACK callback
**                  function will be called with a BTA_JV_ADD_ATTR_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvAddAttribute(UINT32 handle, UINT16 attr_id,
                           UINT8 *p_value, INT32 value_size);

/*******************************************************************************
**
** Function         BTA_JvDeleteAttribute
**
** Description      Delete an attribute from a service record in the local SDP database.
**                  When the operation is complete the tBTA_JV_DM_CBACK callback
**                  function will be called with a BTA_JV_DELETE_ATTR_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvDeleteAttribute(UINT32 handle, UINT16 attr_id);

/*******************************************************************************
**
** Function         BTA_JvDeleteRecord
**
** Description      Delete a service record in the local SDP database.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvDeleteRecord(UINT32 handle);

/*******************************************************************************
**
** Function         BTA_JvReadRecord
**
** Description      Read a service record in the local SDP database.
**
** Returns          -1, if the record is not found.
**                  Otherwise, the offset (0 or 1) to start of data in p_data.
**
**                  The size of data copied into p_data is in *p_data_len.
**
*******************************************************************************/
BTA_API extern INT32 BTA_JvReadRecord(UINT32 handle, UINT8 *p_data, INT32 *p_data_len);

/*******************************************************************************
**
** Function         BTA_JvL2capConnect
**
** Description      Initiate a connection as a L2CAP client to the given BD
**                  Address.
**                  When the connection is initiated or failed to initiate,
**                  tBTA_JV_L2CAP_CBACK is called with BTA_JV_L2CAP_CL_INIT_EVT
**                  When the connection is established or failed,
**                  tBTA_JV_L2CAP_CBACK is called with BTA_JV_L2CAP_OPEN_EVT
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvL2capConnect(tBTA_SEC sec_mask,
                           tBTA_JV_ROLE role,  UINT16 remote_psm, UINT16 rx_mtu,
                           BD_ADDR peer_bd_addr, tBTA_JV_L2CAP_CBACK *p_cback);

/*******************************************************************************
**
** Function         BTA_JvL2capClose
**
** Description      This function closes an L2CAP client connection
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvL2capClose(UINT32 handle);

/*******************************************************************************
**
** Function         BTA_JvL2capStartServer
**
** Description      This function starts an L2CAP server and listens for an L2CAP
**                  connection from a remote Bluetooth device.  When the server
**                  is started successfully, tBTA_JV_L2CAP_CBACK is called with
**                  BTA_JV_L2CAP_START_EVT.  When the connection is established,
**                  tBTA_JV_L2CAP_CBACK is called with BTA_JV_L2CAP_OPEN_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvL2capStartServer(tBTA_SEC sec_mask, tBTA_JV_ROLE role,
                           UINT16 local_psm, UINT16 rx_mtu,
                           tBTA_JV_L2CAP_CBACK *p_cback);

/*******************************************************************************
**
** Function         BTA_JvL2capStopServer
**
** Description      This function stops the L2CAP server. If the server has an
**                  active connection, it would be closed.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvL2capStopServer(UINT16 local_psm);

/*******************************************************************************
**
** Function         BTA_JvL2capRead
**
** Description      This function reads data from an L2CAP connection
**                  When the operation is complete, tBTA_JV_L2CAP_CBACK is
**                  called with BTA_JV_L2CAP_READ_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvL2capRead(UINT32 handle, UINT32 req_id,
                                              UINT8 *p_data, UINT16 len);

/*******************************************************************************
**
** Function         BTA_JvL2capReceive
**
** Description      This function reads data from an L2CAP connection
**                  When the operation is complete, tBTA_JV_L2CAP_CBACK is
**                  called with BTA_JV_L2CAP_RECEIVE_EVT.
**                  If there are more data queued in L2CAP than len, the extra data will be discarded.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvL2capReceive(UINT32 handle, UINT32 req_id,
                                              UINT8 *p_data, UINT16 len);

/*******************************************************************************
**
** Function         BTA_JvL2capReady
**
** Description      This function determined if there is data to read from
**                  an L2CAP connection
**
** Returns          BTA_JV_SUCCESS, if data queue size is in *p_data_size.
**                  BTA_JV_FAILURE, if error.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvL2capReady(UINT32 handle, UINT32 *p_data_size);

/*******************************************************************************
**
** Function         BTA_JvL2capWrite
**
** Description      This function writes data to an L2CAP connection
**                  When the operation is complete, tBTA_JV_L2CAP_CBACK is
**                  called with BTA_JV_L2CAP_WRITE_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvL2capWrite(UINT32 handle, UINT32 req_id,
                                               UINT8 *p_data, UINT16 len);

/*******************************************************************************
**
** Function         BTA_JvRfcommConnect
**
** Description      This function makes an RFCOMM conection to a remote BD
**                  Address.
**                  When the connection is initiated or failed to initiate,
**                  tBTA_JV_RFCOMM_CBACK is called with BTA_JV_RFCOMM_CL_INIT_EVT
**                  When the connection is established or failed,
**                  tBTA_JV_RFCOMM_CBACK is called with BTA_JV_RFCOMM_OPEN_EVT
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvRfcommConnect(tBTA_SEC sec_mask,
                           tBTA_JV_ROLE role, UINT8 remote_scn, BD_ADDR peer_bd_addr,
                           tBTA_JV_RFCOMM_CBACK *p_cback, void *user_data);

/*******************************************************************************
**
** Function         BTA_JvRfcommClose
**
** Description      This function closes an RFCOMM connection
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvRfcommClose(UINT32 handle);

/*******************************************************************************
**
** Function         BTA_JvRfcommStartServer
**
** Description      This function starts listening for an RFCOMM connection
**                  request from a remote Bluetooth device.  When the server is
**                  started successfully, tBTA_JV_RFCOMM_CBACK is called
**                  with BTA_JV_RFCOMM_START_EVT.
**                  When the connection is established, tBTA_JV_RFCOMM_CBACK
**                  is called with BTA_JV_RFCOMM_OPEN_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvRfcommStartServer(tBTA_SEC sec_mask,
                           tBTA_JV_ROLE role, UINT8 local_scn, UINT8 max_session,
                           tBTA_JV_RFCOMM_CBACK *p_cback, void *user_data);

/*******************************************************************************
**
** Function         BTA_JvRfcommStopServer
**
** Description      This function stops the RFCOMM server. If the server has an
**                  active connection, it would be closed.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvRfcommStopServer(UINT32 handle);

/*******************************************************************************
**
** Function         BTA_JvRfcommRead
**
** Description      This function reads data from an RFCOMM connection
**                  When the operation is complete, tBTA_JV_RFCOMM_CBACK is
**                  called with BTA_JV_RFCOMM_READ_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvRfcommRead(UINT32 handle, UINT32 req_id,
                                               UINT8 *p_data, UINT16 len);

/*******************************************************************************
**
** Function         BTA_JvRfcommReady
**
** Description      This function determined if there is data to read from
**                  an RFCOMM connection
**
** Returns          BTA_JV_SUCCESS, if data queue size is in *p_data_size.
**                  BTA_JV_FAILURE, if error.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvRfcommReady(UINT32 handle, UINT32 *p_data_size);

/*******************************************************************************
**
** Function         BTA_JvRfcommWrite
**
** Description      This function writes data to an RFCOMM connection
**                  When the operation is complete, tBTA_JV_RFCOMM_CBACK is
**                  called with BTA_JV_RFCOMM_WRITE_EVT.
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
BTA_API extern tBTA_JV_STATUS BTA_JvRfcommWrite(UINT32 handle, UINT32 req_id);


/*******************************************************************************
**
** Function         BTA_JvRfcommGetPortHdl
**
** Description    This function fetches the rfcomm port handle
**
** Returns          BTA_JV_SUCCESS, if the request is being processed.
**                  BTA_JV_FAILURE, otherwise.
**
*******************************************************************************/
UINT16 BTA_JvRfcommGetPortHdl(UINT32 handle);

#ifdef __cplusplus
}
#endif

#endif /* BTA_JV_API_H */

