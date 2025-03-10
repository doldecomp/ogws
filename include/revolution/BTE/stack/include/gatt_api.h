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
#ifndef GATT_API_H
#define GATT_API_H

#include "bt_target.h"
#include "gattdefs.h"

/*****************************************************************************
**  Constants
*****************************************************************************/
/* Success code and error codes */
#define  GATT_SUCCESS                        0x0000
#define  GATT_INVALID_HANDLE                 0x0001
#define  GATT_READ_NOT_PERMIT                0x0002
#define  GATT_WRITE_NOT_PERMIT               0x0003
#define  GATT_INVALID_PDU                    0x0004
#define  GATT_INSUF_AUTHENTICATION           0x0005
#define  GATT_REQ_NOT_SUPPORTED              0x0006
#define  GATT_INVALID_OFFSET                 0x0007
#define  GATT_INSUF_AUTHORIZATION            0x0008
#define  GATT_PREPARE_Q_FULL                 0x0009
#define  GATT_NOT_FOUND                      0x000a
#define  GATT_NOT_LONG                       0x000b
#define  GATT_INSUF_KEY_SIZE                 0x000c
#define  GATT_INVALID_ATTR_LEN               0x000d
#define  GATT_ERR_UNLIKELY                   0x000e
#define  GATT_INSUF_ENCRYPTION               0x000f
#define  GATT_UNSUPPORT_GRP_TYPE             0x0010
#define  GATT_INSUF_RESOURCE                 0x0011


#define  GATT_ILLEGAL_PARAMETER              0x0087
#define  GATT_NO_RESOURCES                   0x0080
#define  GATT_INTERNAL_ERROR                 0x0081
#define  GATT_WRONG_STATE                    0x0082
#define  GATT_DB_FULL                        0x0083
#define  GATT_BUSY                           0x0084
#define  GATT_ERROR                          0x0085
#define  GATT_CMD_STARTED                    0x0086
#define  GATT_PENDING                        0x0088
#define  GATT_AUTH_FAIL                      0x0089
#define  GATT_MORE                           0x008a
#define  GATT_INVALID_CFG                    0x008b
#define  GATT_SERVICE_STARTED                0x008c
#define  GATT_ENCRYPED_MITM                  GATT_SUCCESS
#define  GATT_ENCRYPED_NO_MITM               0x008d
#define  GATT_NOT_ENCRYPTED                  0x008e


typedef UINT8 tGATT_STATUS;


#define  GATT_RSP_ERROR                      0x01
#define  GATT_REQ_MTU                        0x02
#define  GATT_RSP_MTU                        0x03
#define  GATT_REQ_FIND_INFO                  0x04
#define  GATT_RSP_FIND_INFO                  0x05
#define  GATT_REQ_FIND_TYPE_VALUE            0x06
#define  GATT_RSP_FIND_TYPE_VALUE            0x07
#define  GATT_REQ_READ_BY_TYPE               0x08
#define  GATT_RSP_READ_BY_TYPE               0x09
#define  GATT_REQ_READ                       0x0A
#define  GATT_RSP_READ                       0x0B
#define  GATT_REQ_READ_BLOB                  0x0C
#define  GATT_RSP_READ_BLOB                  0x0D
#define  GATT_REQ_READ_MULTI                 0x0E
#define  GATT_RSP_READ_MULTI                 0x0F
#define  GATT_REQ_READ_BY_GRP_TYPE           0x10
#define  GATT_RSP_READ_BY_GRP_TYPE           0x11
#define  GATT_REQ_WRITE                      0x12 /*                 0001-0010 (write)*/
#define  GATT_RSP_WRITE                      0x13
#define  GATT_CMD_WRITE                      0x52 /* changed in V4.0 01001-0010(write cmd)*/
#define  GATT_REQ_PREPARE_WRITE              0x16
#define  GATT_RSP_PREPARE_WRITE              0x17
#define  GATT_REQ_EXEC_WRITE                 0x18
#define  GATT_RSP_EXEC_WRITE                 0x19
#define  GATT_HANDLE_VALUE_NOTIF             0x1B
#define  GATT_HANDLE_VALUE_IND               0x1D
#define  GATT_HANDLE_VALUE_CONF              0x1E
#define  GATT_SIGN_CMD_WRITE                 0xD2 /* changed in V4.0 1101-0010 (signed write)  see write cmd above*/
#define  GATT_OP_CODE_MAX                    GATT_HANDLE_VALUE_CONF + 1 /* 0x1E = 30 + 1 = 31*/


#define  GATT_HANDLE_IS_VALID(x) ((x) != 0)

#define GATT_CONN_UNKNOWN                   0
#define GATT_CONN_NO_RESOURCES              L2CAP_CONN_NO_RESOURCES         /* connection fail for l2cap resource failure */
#define GATT_CONN_TIMEOUT                   HCI_ERR_CONNECTION_TOUT         /* 0x08 connection timeout  */
#define GATT_CONN_TERMINATE_PEER_USER       HCI_ERR_PEER_USER               /* 0x13 connection terminate by peer user  */
#define GATT_CONN_TERMINATE_LOCAL_HOST      HCI_ERR_CONN_CAUSE_LOCAL_HOST   /* 0x16 connectionterminated by local host  */
#define GATT_CONN_FAIL_ESTABLISH            HCI_ERR_CONN_FAILED_ESTABLISHMENT/* 0x03E connection fail to establish  */
#define GATT_CONN_LMP_TIMEOUT               HCI_ERR_LMP_RESPONSE_TIMEOUT     /* 0x22 connection fail for LMP response tout */
#define GATT_CONN_CANCEL                    L2CAP_CONN_CANCEL                /* 0x0100 L2CAP connection cancelled  */
typedef UINT16 tGATT_DISCONN_REASON;

/* MAX GATT MTU size
*/
#ifndef GATT_MAX_MTU_SIZE
    #define GATT_MAX_MTU_SIZE     517
#endif

/* max legth of an attribute value
*/
#ifndef GATT_MAX_ATTR_LEN
    #define GATT_MAX_ATTR_LEN     600
#endif

/* default GATT MTU size over LE link
*/
#define GATT_DEF_BLE_MTU_SIZE       23

/* invalid connection ID
*/
#define GATT_INVALID_CONN_ID        0xFFFF

#ifndef GATT_CL_MAX_LCB
    #define GATT_CL_MAX_LCB     22
#endif

#ifndef GATT_MAX_SCCB
    #define GATT_MAX_SCCB       10
#endif



/* GATT notification caching timer, default to be three seconds
*/
#ifndef GATTC_NOTIF_TIMEOUT
    #define GATTC_NOTIF_TIMEOUT   3
#endif

/*****************************************************************************
** GATT Structure Definition
*****************************************************************************/

/* Attribute permissions
*/
#define GATT_PERM_READ              (1 << 0) /* bit 0 */
#define GATT_PERM_READ_ENCRYPTED    (1 << 1) /* bit 1 */
#define GATT_PERM_READ_ENC_MITM     (1 << 2) /* bit 2 */
#define GATT_PERM_WRITE             (1 << 4) /* bit 4 */
#define GATT_PERM_WRITE_ENCRYPTED   (1 << 5) /* bit 5 */
#define GATT_PERM_WRITE_ENC_MITM    (1 << 6) /* bit 6 */
#define GATT_PERM_WRITE_SIGNED      (1 << 7) /* bit 7 */
#define GATT_PERM_WRITE_SIGNED_MITM (1 << 8) /* bit 8 */
typedef UINT16 tGATT_PERM;

#define GATT_ENCRYPT_KEY_SIZE_MASK  (0xF000) /* the MS nibble of tGATT_PERM; key size 7=0; size 16=9 */

#define GATT_READ_ALLOWED           (GATT_PERM_READ | GATT_PERM_READ_ENCRYPTED | GATT_PERM_READ_ENC_MITM)
#define GATT_READ_AUTH_REQUIRED     (GATT_PERM_READ_ENC_MITM)
#define GATT_READ_MITM_REQUIRED     (GATT_PERM_READ_ENC_MITM)
#define GATT_READ_ENCRYPTED_REQUIRED   (GATT_PERM_READ_ENCRYPTED | GATT_PERM_READ_ENC_MITM)


#define GATT_WRITE_ALLOWED          (GATT_PERM_WRITE | GATT_PERM_WRITE_ENCRYPTED | GATT_PERM_WRITE_ENC_MITM | \
                                     GATT_PERM_WRITE_SIGNED | GATT_PERM_WRITE_SIGNED_MITM)

#define GATT_WRITE_AUTH_REQUIRED    (GATT_PERM_WRITE_ENCRYPTED | GATT_PERM_WRITE_SIGNED)

#define GATT_WRITE_MITM_REQUIRED    (GATT_PERM_WRITE_ENC_MITM | GATT_PERM_WRITE_SIGNED_MITM)

#define GATT_WRITE_ENCRYPTED_PERM   (GATT_PERM_WRITE_ENCRYPTED | GATT_PERM_WRITE_ENC_MITM)

#define GATT_WRITE_SIGNED_PERM      (GATT_PERM_WRITE_SIGNED | GATT_PERM_WRITE_SIGNED_MITM)


/* Characteristic properties
*/
#define GATT_CHAR_PROP_BIT_BROADCAST    (1 << 0)
#define GATT_CHAR_PROP_BIT_READ         (1 << 1)
#define GATT_CHAR_PROP_BIT_WRITE_NR     (1 << 2)
#define GATT_CHAR_PROP_BIT_WRITE        (1 << 3)
#define GATT_CHAR_PROP_BIT_NOTIFY       (1 << 4)
#define GATT_CHAR_PROP_BIT_INDICATE     (1 << 5)
#define GATT_CHAR_PROP_BIT_AUTH         (1 << 6)
#define GATT_CHAR_PROP_BIT_EXT_PROP     (1 << 7)
typedef UINT8 tGATT_CHAR_PROP;


/* Format of the value of a characteristic. enumeration type
*/
enum
{
    GATT_FORMAT_RES,            /* rfu */
    GATT_FORMAT_BOOL,           /* 0x01 boolean */
    GATT_FORMAT_2BITS,           /* 0x02 2 bit */
    GATT_FORMAT_NIBBLE,         /* 0x03 nibble */
    GATT_FORMAT_UINT8,          /* 0x04 uint8 */
    GATT_FORMAT_UINT12,         /* 0x05 uint12 */
    GATT_FORMAT_UINT16,         /* 0x06 uint16 */
    GATT_FORMAT_UINT24,         /* 0x07 uint24 */
    GATT_FORMAT_UINT32,         /* 0x08 uint32 */
    GATT_FORMAT_UINT48,         /* 0x09 uint48 */
    GATT_FORMAT_UINT64,         /* 0x0a uint64 */
    GATT_FORMAT_UINT128,        /* 0x0B uint128 */
    GATT_FORMAT_SINT8,          /* 0x0C signed 8 bit integer */
    GATT_FORMAT_SINT12,         /* 0x0D signed 12 bit integer */
    GATT_FORMAT_SINT16,         /* 0x0E signed 16 bit integer */
    GATT_FORMAT_SINT24,         /* 0x0F signed 24 bit integer */
    GATT_FORMAT_SINT32,         /* 0x10 signed 32 bit integer */
    GATT_FORMAT_SINT48,         /* 0x11 signed 48 bit integer */
    GATT_FORMAT_SINT64,         /* 0x12 signed 64 bit integer */
    GATT_FORMAT_SINT128,        /* 0x13 signed 128 bit integer */
    GATT_FORMAT_FLOAT32,        /* 0x14 float 32 */
    GATT_FORMAT_FLOAT64,        /* 0x15 float 64*/
    GATT_FORMAT_SFLOAT,         /* 0x16 IEEE-11073 16 bit SFLOAT */
    GATT_FORMAT_FLOAT,          /* 0x17 IEEE-11073 32 bit SFLOAT */
    GATT_FORMAT_DUINT16,        /* 0x18 IEEE-20601 format */
    GATT_FORMAT_UTF8S,          /* 0x19 UTF-8 string */
    GATT_FORMAT_UTF16S,         /* 0x1a UTF-16 string */
    GATT_FORMAT_STRUCT,         /* 0x1b Opaque structure*/
    GATT_FORMAT_MAX             /* 0x1c or above reserved */
};
typedef UINT8 tGATT_FORMAT;

/* Characteristic Presentation Format Descriptor value
*/
typedef struct
{
    UINT16              unit;       /* as UUIUD defined by SIG */
    UINT16              descr;       /* as UUID as defined by SIG */
    tGATT_FORMAT        format;
    INT8                exp;
    UINT8               name_spc;   /* The name space of the description */
} tGATT_CHAR_PRES;

#define GATT_VALID_RANGE_MAX_SIZE       16
typedef struct
{
    UINT8                   format;
    UINT16                  len;
    UINT8                   lower_range[GATT_VALID_RANGE_MAX_SIZE]; /* in little endian format */
    UINT8                   upper_range[GATT_VALID_RANGE_MAX_SIZE];
} tGATT_VALID_RANGE;

/* Characteristic Aggregate Format attribute value
*/
#define GATT_AGGR_HANDLE_NUM_MAX        10
typedef struct
{
    UINT8                   num_handle;
    UINT16                  handle_list[GATT_AGGR_HANDLE_NUM_MAX];
} tGATT_CHAR_AGGRE;

/* Characteristic descriptor: Extended Properties value
*/
#define GATT_CHAR_BIT_REL_WRITE    0x0001       /* permits reliable writes of the Characteristic Value */
#define GATT_CHAR_BIT_WRITE_AUX    0x0002       /* permits writes to the characteristic descriptor */


/* characteristic descriptor: client configuration value
*/
#define GATT_CLT_CONFIG_NONE               0x0000
#define GATT_CLT_CONFIG_NOTIFICATION       0x0001
#define GATT_CLT_CONFIG_INDICATION         0x0002
typedef UINT16 tGATT_CLT_CHAR_CONFIG;


/* characteristic descriptor: server configuration value
*/
#define GATT_SVR_CONFIG_NONE                     0x0000
#define GATT_SVR_CONFIG_BROADCAST                0x0001
typedef UINT16 tGATT_SVR_CHAR_CONFIG;

/* Characteristic descriptor: Extended Properties value
*/
#define GATT_CHAR_BIT_REL_WRITE    0x0001       /* permits reliable writes of the Characteristic Value */
#define GATT_CHAR_BIT_WRITE_AUX    0x0002       /* permits writes to the characteristic descriptor */

/* authentication requirement
*/
#define GATT_AUTH_REQ_NONE              0
#define GATT_AUTH_REQ_NO_MITM           1   /* unauthenticated encryption */
#define GATT_AUTH_REQ_MITM              2   /* authenticated encryption */
#define GATT_AUTH_REQ_SIGNED_NO_MITM    3
#define GATT_AUTH_REQ_SIGNED_MITM       4
typedef UINT8 tGATT_AUTH_REQ;

/* Attribute Value structure
*/
typedef struct
{
    UINT16          conn_id;
    UINT16          handle;     /* attribute handle */
    UINT16          offset;     /* attribute value offset, if no offfset is needed for the command, ignore it */
    UINT16          len;        /* length of attribute value */
    tGATT_AUTH_REQ  auth_req;   /*  authentication request */
    UINT8           value[GATT_MAX_ATTR_LEN];  /* the actual attribute value */
} tGATT_VALUE;

/* Union of the event data which is used in the server respond API to carry the server response information
*/
typedef union
{
    /* data type            member          event   */
    tGATT_VALUE             attr_value;     /* READ, HANDLE_VALUE_IND, PREPARE_WRITE */
                                            /* READ_BLOB, READ_BY_TYPE */
    UINT16                  handle;         /* WRITE, WRITE_BLOB */

} tGATTS_RSP;

/* Transports for the primary service  */
enum
{
    GATT_TRANSPORT_LE,
    GATT_TRANSPORT_BR_EDR,
    GATT_TRANSPORT_LE_BR_EDR
};
typedef UINT8 tGATT_TRANSPORT;

#define GATT_PREP_WRITE_CANCEL   0x00
#define GATT_PREP_WRITE_EXEC     0x01
typedef UINT8   tGATT_EXEC_FLAG;

/* read request always based on UUID */
typedef struct
{
    UINT16        handle;
    UINT16        offset;
    BOOLEAN       is_long;
} tGATT_READ_REQ;

/* write request data */
typedef struct
{
    UINT16          handle;     /* attribute handle */
    UINT16          offset;     /* attribute value offset, if no offfset is needed for the command, ignore it */
    UINT16          len;        /* length of attribute value */
    UINT8           value[GATT_MAX_ATTR_LEN];  /* the actual attribute value */
    BOOLEAN         need_rsp;   /* need write response */
    BOOLEAN         is_prep;    /* is prepare write */
} tGATT_WRITE_REQ;

/* callback data for server access request from client */
typedef union
{
    tGATT_READ_REQ         read_req;       /* read request, read by Type, read blob */

    tGATT_WRITE_REQ        write_req;    /* write */
                                         /* prepare write */
                                         /* write blob */
    UINT16                 handle;       /* handle value confirmation */
    UINT16                 mtu;          /* MTU exchange request */
    tGATT_EXEC_FLAG        exec_write;    /* execute write */
} tGATTS_DATA;

typedef UINT8 tGATT_SERV_IF;               /* GATT Service Interface */

enum
{
    GATTS_REQ_TYPE_READ = 1,        /* Attribute read request */
    GATTS_REQ_TYPE_WRITE,           /* Attribute write request */
    GATTS_REQ_TYPE_WRITE_EXEC,      /* Execute write */
    GATTS_REQ_TYPE_MTU,             /* MTU exchange information */
    GATTS_REQ_TYPE_CONF             /* handle value confirmation */
};
typedef UINT8   tGATTS_REQ_TYPE;



/* Client Used Data Structure
*/
/* definition of different discovery types */
enum
{
    GATT_DISC_SRVC_ALL = 1,     /* discover all services */
    GATT_DISC_SRVC_BY_UUID,     /* discover service of a special type */
    GATT_DISC_INC_SRVC,         /* discover the included service within a service */
    GATT_DISC_CHAR,             /* discover characteristics of a service with/without type requirement */
    GATT_DISC_CHAR_DSCPT,       /* discover characteristic descriptors of a character */
    GATT_DISC_MAX               /* maximnun discover type */
};
typedef UINT8   tGATT_DISC_TYPE;

/* Discover parameters of different discovery types
*/
typedef struct
{
    tBT_UUID    service;
    UINT16      s_handle;
    UINT16      e_handle;
}tGATT_DISC_PARAM;

/* GATT read type enumeration
*/
enum
{
    GATT_READ_BY_TYPE =        1,
    GATT_READ_BY_HANDLE,
    GATT_READ_MULTIPLE,
    GATT_READ_CHAR_VALUE,
    GATT_READ_PARTIAL,
    GATT_READ_MAX
};
typedef UINT8 tGATT_READ_TYPE;

/* Read By Type Request (GATT_READ_BY_TYPE) Data
*/
typedef struct
{
    tGATT_AUTH_REQ      auth_req;
    UINT16              s_handle;
    UINT16              e_handle;
    tBT_UUID            uuid;
} tGATT_READ_BY_TYPE;

/*   GATT_READ_MULTIPLE request data
*/
#define GATT_MAX_READ_MULTI_HANDLES      10           /* Max attributes to read in one request */
typedef struct
{
    tGATT_AUTH_REQ          auth_req;
    UINT16                  num_handles;                            /* number of handles to read */
    UINT16                  handles[GATT_MAX_READ_MULTI_HANDLES];   /* handles list to be read */
} tGATT_READ_MULTI;

/*   Read By Handle Request (GATT_READ_BY_HANDLE) data */
typedef struct
{
    tGATT_AUTH_REQ         auth_req;
    UINT16                 handle;
} tGATT_READ_BY_HANDLE;

/*   READ_BT_HANDLE_Request data */
typedef struct
{
    tGATT_AUTH_REQ         auth_req;
    UINT16                 handle;
    UINT16                 offset;
} tGATT_READ_PARTIAL;

/* Read Request Data
*/
typedef union
{
    tGATT_READ_BY_TYPE   service;
    tGATT_READ_BY_TYPE   char_type;        /* characterisitc type */
    tGATT_READ_MULTI     read_multiple;
    tGATT_READ_BY_HANDLE by_handle;
    tGATT_READ_PARTIAL   partial;
} tGATT_READ_PARAM;

/* GATT write type enumeration */
enum
{
    GATT_WRITE_NO_RSP = 1,
    GATT_WRITE ,
    GATT_WRITE_PREPARE
};
typedef UINT8 tGATT_WRITE_TYPE;

/* Client Operation Complete Callback Data
*/
typedef union
{
    tGATT_VALUE          att_value;
    UINT16               mtu;
    UINT16               handle;
} tGATT_CL_COMPLETE;

/* GATT client operation type, used in client callback function
*/
#define GATTC_OPTYPE_NONE                 0
#define GATTC_OPTYPE_DISCOVERY            1
#define GATTC_OPTYPE_READ                 2
#define GATTC_OPTYPE_WRITE                3
#define GATTC_OPTYPE_EXE_WRITE            4
#define GATTC_OPTYPE_CONFIG               5
#define GATTC_OPTYPE_NOTIFICATION         6
#define GATTC_OPTYPE_INDICATION           7
typedef UINT8 tGATTC_OPTYPE;

/* characteristic declaration
*/
typedef struct
{
    tGATT_CHAR_PROP       char_prop;   /* characterisitc properties */
    UINT16                val_handle;  /* characteristic value attribute handle */
    tBT_UUID              char_uuid;   /* characteristic UUID type */
} tGATT_CHAR_DCLR_VAL;

/* primary service group data
*/
typedef struct
{
    UINT16          e_handle;       /* ending handle of the group */
    tBT_UUID        service_type;   /* group type */
} tGATT_GROUP_VALUE;


/* included service attribute value
*/
typedef struct
{
    tBT_UUID    service_type;       /* included service UUID */
    UINT16      s_handle;           /* starting handle */
    UINT16      e_handle;           /* ending handle */
} tGATT_INCL_SRVC;

typedef union
{
    tGATT_INCL_SRVC     incl_service;  /* include service value */
    tGATT_GROUP_VALUE   group_value;   /* Service UUID type.
                                          This field is used with GATT_DISC_SRVC_ALL
                                          type of discovery result callback. */

    UINT16              handle;        /* When used with GATT_DISC_SRVC_BY_UUID type
                                          discovery result, it is the ending handle of a
                                          known service to be discovered. When used with
                                          GATT_DISC_INC_SRVC type discovery result,
                                          it is the included service starting handle.*/

    tGATT_CHAR_DCLR_VAL dclr_value;    /* Characteristic declaration value.
                                          This field is used with GATT_DISC_CHAR type discovery.*/
} tGATT_DISC_VALUE;

/* discover result record
*/
typedef struct
{
    tBT_UUID            type;
    UINT16              handle;
    tGATT_DISC_VALUE    value;
} tGATT_DISC_RES;


typedef UINT8 tGATT_IF;
#define GATT_LINK_IDLE_TIMEOUT_WHEN_NO_APP    0 /* start a idle timer for this duration when no application
                                              need to use the link */

#define GATT_LINK_NO_IDLE_TIMEOUT            0xFFFF

#define GATT_INVALID_ACL_HANDLE              0xFFFF
/* discover result callback function */
typedef void (tGATT_DISC_RES_CB) (UINT16 conn_id, tGATT_DISC_TYPE disc_type, tGATT_DISC_RES *p_data);

/* discover complete callback function */
typedef void (tGATT_DISC_CMPL_CB) (UINT16 conn_id, tGATT_DISC_TYPE disc_type, tGATT_STATUS status);

/* Define a callback function for when read/write/disc/config operation is completed. */
typedef void (tGATT_CMPL_CBACK) (UINT16 conn_id, tGATTC_OPTYPE op, tGATT_STATUS status, tGATT_CL_COMPLETE *p_data);

/* Define a callback function when an initialized connection is established. */
typedef void (tGATT_CONN_CBACK) (tGATT_IF gatt_if, BD_ADDR bda, UINT16 conn_id, BOOLEAN connected, tGATT_DISCONN_REASON reason);

/* attribute request callback for ATT server */
typedef void  (tGATT_REQ_CBACK )(UINT16 conn_id, UINT32 trans_id, tGATTS_REQ_TYPE type, tGATTS_DATA *p_data);




/* Define the structure that applications use to register with
** GATT. This structure includes callback functions. All functions
** MUST be provided.
*/
typedef struct
{
    tGATT_CONN_CBACK                *p_conn_cb;
    tGATT_CMPL_CBACK                *p_cmpl_cb;
    tGATT_DISC_RES_CB               *p_disc_res_cb;
    tGATT_DISC_CMPL_CB              *p_disc_cmpl_cb;
    tGATT_REQ_CBACK                 *p_req_cb;
} tGATT_CBACK;

/***********************  Start Handle Management Definitions   **********************
*/


typedef struct
{
    tBT_UUID app_uuid128;
    tBT_UUID svc_uuid;
    UINT16   svc_inst;
    UINT16   s_handle;
    UINT16   e_handle;
    BOOLEAN  is_primary;      /* primary service or secondary */
} tGATTS_HNDL_RANGE;



#define GATTS_SRV_CHG_CMD_ADD_CLIENT       1
#define GATTS_SRV_CHG_CMD_UPDATE_CLIENT    2
#define GATTS_SRV_CHG_CMD_REMOVE_CLIENT    3
#define GATTS_SRV_CHG_CMD_READ_NUM_CLENTS  4
#define GATTS_SRV_CHG_CMD_READ_CLENT       5
typedef UINT8 tGATTS_SRV_CHG_CMD;

typedef struct
{
    BD_ADDR         bda;
    BOOLEAN         srv_changed;
} tGATTS_SRV_CHG;


typedef union
{
    tGATTS_SRV_CHG  srv_chg;
    UINT8           client_read_index; /* only used for sequential reading client srv chg info */
} tGATTS_SRV_CHG_REQ;

typedef union
{
    tGATTS_SRV_CHG srv_chg;
    UINT8 num_clients;
} tGATTS_SRV_CHG_RSP;



typedef struct
{
    tGATTS_HNDL_RANGE   *p_new_srv_start;
} tGATTS_PENDING_NEW_SRV_START;

/* Attibute server handle ranges NV storage callback functions
*/
typedef void  (tGATTS_NV_SAVE_CBACK)(BOOLEAN is_saved, tGATTS_HNDL_RANGE *p_hndl_range);
typedef BOOLEAN  (tGATTS_NV_SRV_CHG_CBACK)(tGATTS_SRV_CHG_CMD cmd, tGATTS_SRV_CHG_REQ *p_req, tGATTS_SRV_CHG_RSP *p_rsp);

typedef struct
{
    tGATTS_NV_SAVE_CBACK       *p_nv_save_callback;
    tGATTS_NV_SRV_CHG_CBACK    *p_srv_chg_callback;
} tGATT_APPL_INFO;

/*
***********************  End Handle Management Definitions   **********************/

/*****************************************************************************
**  External Function Declarations
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**
** Function         GATT_SetTraceLevel
**
** Description      This function sets the trace level.  If called with
**                  a value of 0xFF, it simply returns the current trace level.
**
** Returns          The new or current trace level
**
*******************************************************************************/
    GATT_API extern UINT8 GATT_SetTraceLevel (UINT8 new_level);


/*******************************************************************************/
/* GATT Profile API Functions */
/*******************************************************************************/
/* GATT Profile Server Functions */
/*******************************************************************************/
/*******************************************************************************
**
** Function         GATTS_AddHandleRange
**
** Description      This function add the allocated handles range for the specifed
**                  application UUID, service UUID and service instance
**
** Parameter        p_hndl_range:   pointer to allocated handles information
**
** Returns          TRUE if handle range is added sucessfully; otherwise FALSE.
**
*******************************************************************************/

    GATT_API extern BOOLEAN GATTS_AddHandleRange(tGATTS_HNDL_RANGE *p_hndl_range);

/*******************************************************************************
**
** Function         GATTS_NVRegister
**
** Description      Application manager calls this function to register for
**                  NV save callback function.  There can be one and only one
**                  NV save callback function.
**
** Parameter        p_cb_info : callback informaiton
**
** Returns          TRUE if registered OK, else FALSE
**
*******************************************************************************/
    GATT_API extern BOOLEAN  GATTS_NVRegister (tGATT_APPL_INFO *p_cb_info);


/*******************************************************************************
**
** Function         GATTS_CreateService
**
** Description      This function is called to reserve a block of handles for a service.
**
**                  *** It should be called only once per service instance  ***
**
** Parameter        gatt_if       : application if
**                  p_svc_uuid    : service UUID
**                  svc_inst      : instance of the service inside the application
**                  num_handles   : number of handles needed by the service.
**                  is_pri        : is a primary service or not.
**
** Returns          service handle if sucessful, otherwise 0.
**
*******************************************************************************/
    GATT_API extern UINT16 GATTS_CreateService (tGATT_IF gatt_if, tBT_UUID *p_svc_uuid,
                                                UINT16 svc_inst, UINT16 num_handles, BOOLEAN is_pri);


/*******************************************************************************
**
** Function         GATTS_AddIncludeService
**
** Description      This function is called to add an included service.
**
** Parameter        service_handle : To which service this included service is added to.
**                  include_svc_handle    : included service handle.
**
** Returns          included service attribute handle. If 0, add included service
**                  fail.
**
*******************************************************************************/
    GATT_API extern UINT16 GATTS_AddIncludeService (UINT16 service_handle,
                                                    UINT16 include_svc_handle);


/*******************************************************************************
**
** Function         GATTS_AddCharacteristic
**
** Description      This function is called to add a characteristic into a service.
**                  It will add a characteristic declaration and characteristic
**                  value declaration into the service database identified by the
**                  service handle.
**
** Parameter        service_handle : To which service this included service is added to.
**                  char_uuid : Characteristic UUID.
**                  perm      : Characteristic value declaration attribute permission.
**                  property  : Characteristic Properties
**
** Returns          Characteristic value declaration attribute handle. 0 if add
**                  characteristic failed.
**
*******************************************************************************/
    GATT_API extern UINT16 GATTS_AddCharacteristic (UINT16 service_handle, tBT_UUID *char_uuid,
                                                    tGATT_PERM perm,tGATT_CHAR_PROP property);

/*******************************************************************************
**
** Function         GATTS_AddCharDescriptor
**
** Description      This function is called to add a characteristic descriptor
**                  into a service database. Add descriptor should follow add char
**                  to which it belongs, and next add char should be done only
**                  after all add descriptors for the previous char.
**
** Parameter        service_handle  : To which service this characteristic descriptor
**                                    is added to.
**                  perm            : Characteristic value declaration attribute
**                                    permission.
**                  p_descr_uuid    : Characteristic descriptor UUID.
**
** Returns         Characteristic descriptor attribute handle. 0 if add
**                 characteristic descriptor failed.
**
*******************************************************************************/
    GATT_API extern UINT16 GATTS_AddCharDescriptor (UINT16 service_handle, tGATT_PERM perm,
                                                     tBT_UUID * p_descr_uuid);

/*******************************************************************************
**
** Function         GATTS_DeleteService
**
** Description      This function is called to delete a service.
**
** Parameter        gatt_if       : application interface
**                  p_svc_uuid    : service UUID
**                  svc_inst      : instance of the service inside the application
**
** Returns          TRUE if operation succeed, FALSE if handle block was not found.
**
*******************************************************************************/
    GATT_API extern BOOLEAN GATTS_DeleteService (tGATT_IF gatt_if, tBT_UUID *p_svc_uuid, UINT16 svc_inst);

/*******************************************************************************
**
** Function         GATTS_StartService
**
** Description      This function is called to start a service with GATT
**
** Parameter        gatt_if : service handle.
**                  p_cback       : application service callback functions.
**                  sup_transport : supported transport(s) for this primary service
**
** return           GATT_SUCCESS if sucessfully started; otherwise error code.
**
*******************************************************************************/
    GATT_API extern tGATT_STATUS GATTS_StartService (tGATT_IF gatt_if, UINT16 service_handle,
                                                     tGATT_TRANSPORT sup_transport);


/*******************************************************************************
**
** Function         GATTS_StopService
**
** Description      This function is called to stop a service
**
** Parameter         service_handle : this is the start handle of a service
**
** Returns          None.
**
*******************************************************************************/
    GATT_API extern void GATTS_StopService (UINT16 service_handle);


/*******************************************************************************
**
** Function         GATTs_HandleValueIndication
**
** Description      This function sends a handle value indication to a client.
**
** Parameter        conn_id: connection identifier.
**                  attr_handle: Attribute handle of this handle value indication.
**                  val_len: Length of the indicated attribute value.
**                  p_val: Pointer to the indicated attribute value data.
**
** Returns          GATT_SUCCESS if sucessfully sent or queued; otherwise error code.
**
*******************************************************************************/
    GATT_API extern  tGATT_STATUS GATTS_HandleValueIndication (UINT16 conn_id,
                                                               UINT16 attr_handle,
                                                               UINT16 val_len, UINT8 *p_val);

/*******************************************************************************
**
** Function         GATTS_HandleValueNotification
**
** Description      This function sends a handle value notification to a client.
**
** Parameter       conn_id: connection identifier.
**                  attr_handle: Attribute handle of this handle value indication.
**                  val_len: Length of the indicated attribute value.
**                  p_val: Pointer to the indicated attribute value data.
**
** Returns          GATT_SUCCESS if sucessfully sent; otherwise error code.
**
*******************************************************************************/
    GATT_API extern  tGATT_STATUS GATTS_HandleValueNotification (UINT16 conn_id, UINT16 attr_handle,
                                                                 UINT16 val_len, UINT8 *p_val);


/*******************************************************************************
**
** Function         GATTS_SendRsp
**
** Description      This function sends the server response to client.
**
** Parameter        conn_id: connection identifier.
**                  trans_id: transaction id
**                  status: response status
**                  p_msg: pointer to message parameters structure.
**
** Returns          GATT_SUCCESS if sucessfully sent; otherwise error code.
**
*******************************************************************************/
    GATT_API extern  tGATT_STATUS GATTS_SendRsp (UINT16 conn_id,  UINT32 trans_id,
                                                 tGATT_STATUS status, tGATTS_RSP *p_msg);


/*******************************************************************************/
/* GATT Profile Client Functions */
/*******************************************************************************/

/*******************************************************************************
**
** Function         GATTC_ConfigureMTU
**
** Description      This function is called to configure the ATT MTU size for
**                  a connection on an LE transport.
**
** Parameters       conn_id: connection identifier.
**                  mtu    - attribute MTU size..
**
** Returns          GATT_SUCCESS if command started successfully.
**
*******************************************************************************/
    GATT_API extern tGATT_STATUS GATTC_ConfigureMTU (UINT16 conn_id, UINT16  mtu);

/*******************************************************************************
**
** Function         GATTC_Discover
**
** Description      This function is called to do a discovery procedure on ATT server.
**
** Parameters       conn_id: connection identifier.
**                  disc_type:discovery type.
**                  p_param: parameters of discovery requirement.
**
** Returns          GATT_SUCCESS if command received/sent successfully.
**
*******************************************************************************/
    GATT_API extern tGATT_STATUS GATTC_Discover (UINT16 conn_id,
                                                 tGATT_DISC_TYPE disc_type,
                                                 tGATT_DISC_PARAM *p_param );
/*******************************************************************************
**
** Function         GATTC_Read
**
** Description      This function is called to read the value of an attribute from
**                  the server.
**
** Parameters       conn_id: connection identifier.
**                  type    - attribute read type.
**                  p_read  - read operation parameters.
**
** Returns          GATT_SUCCESS if command started successfully.
**
*******************************************************************************/
    GATT_API extern tGATT_STATUS GATTC_Read (UINT16 conn_id, tGATT_READ_TYPE type,
                                             tGATT_READ_PARAM *p_read);

/*******************************************************************************
**
** Function         GATTC_Write
**
** Description      This function is called to read the value of an attribute from
**                  the server.
**
** Parameters       conn_id: connection identifier.
**                  type    - attribute write type.
**                  p_write  - write operation parameters.
**
** Returns          GATT_SUCCESS if command started successfully.
**
*******************************************************************************/
    GATT_API extern tGATT_STATUS GATTC_Write (UINT16 conn_id, tGATT_WRITE_TYPE type,
                                              tGATT_VALUE *p_write);


/*******************************************************************************
**
** Function         GATTC_ExecuteWrite
**
** Description      This function is called to send an Execute write request to
**                  the server.
**
** Parameters       conn_id: connection identifier.
**                  is_execute - to execute or cancel the prepare write requet(s)
**
** Returns          GATT_SUCCESS if command started successfully.
**
*******************************************************************************/
    GATT_API extern tGATT_STATUS GATTC_ExecuteWrite (UINT16 conn_id, BOOLEAN is_execute);

/*******************************************************************************
**
** Function         GATTC_SendHandleValueConfirm
**
** Description      This function is called to send a handle value confirmation
**                  as response to a handle value notification from server.
**
** Parameters       conn_id: connection identifier.
**                  handle: the handle of the attribute confirmation.
**
** Returns          GATT_SUCCESS if command started successfully.
**
*******************************************************************************/
    GATT_API extern tGATT_STATUS GATTC_SendHandleValueConfirm (UINT16 conn_id, UINT16 handle);


/*******************************************************************************
**
** Function         GATT_SetIdleTimeout
**
** Description      This function (common to both client and server) sets the idle
**                  timeout for a tansport connection
**
** Parameter        bd_addr:   target device bd address.
**                  idle_tout: timeout value in seconds.
**
** Returns          void
**
*******************************************************************************/
    GATT_API extern void GATT_SetIdleTimeout (BD_ADDR bd_addr, UINT16 idle_tout);


/*******************************************************************************
**
** Function         GATT_Register
**
** Description      This function is called to register an  application
**                  with GATT
**
** Parameter        p_app_uuid128: Application UUID
**                  p_cb_info: callback functions.
**
** Returns          0 for error, otherwise the index of the client registered with GATT
**
*******************************************************************************/
    GATT_API extern  tGATT_IF GATT_Register (tBT_UUID *p_app_uuid128, tGATT_CBACK *p_cb_info);

/*******************************************************************************
**
** Function         GATT_Deregister
**
** Description      This function deregistered the application from GATT.
**
** Parameters       gatt_if: applicaiton interface.
**
** Returns          None.
**
*******************************************************************************/
    GATT_API extern void GATT_Deregister (tGATT_IF gatt_if);

/*******************************************************************************
**
** Function         GATT_StartIf
**
** Description      This function is called after registration to start receiving
**                  callbacks for registered interface.  Function may call back
**                  with connection status and queued notifications
**
** Parameter        gatt_if: applicaiton interface.
**
** Returns          None
**
*******************************************************************************/
    GATT_API extern  void GATT_StartIf (tGATT_IF gatt_if);

/*******************************************************************************
**
** Function         GATT_Connect
**
** Description      This function initiate a connecttion to a ATT server.
**
** Parameters       gatt_if: applicaiton interface
**                  bd_addr: peer device address.
**                  is_direct: is a direct conenection or a background auto connection
**
** Returns          TRUE if connection started; FALSE if connection start failure.
**
*******************************************************************************/
    GATT_API extern BOOLEAN GATT_Connect (tGATT_IF gatt_if, BD_ADDR bd_addr, BOOLEAN is_direct);


/*******************************************************************************
**
** Function         GATT_CancelConnect
**
** Description      This function initiate a cancel connecttion to a ATT server.
**
** Parameters       gatt_if: client interface. If 0 used as unconditionally disconnect,
**                          typically used for direct connection cancellation.
**                  bd_addr: peer device address.
**                  is_direct: is a direct conenection or a background auto connection
**
** Returns          TRUE if connection started; FALSE if connection start failure.
**
*******************************************************************************/
    GATT_API extern BOOLEAN GATT_CancelConnect (tGATT_IF gatt_if, BD_ADDR bd_addr, BOOLEAN is_direct);

/*******************************************************************************
**
** Function         GATT_Disconnect
**
** Description      This function disconnect a logic channel.
**
** Parameters       conn_id: connection identifier.
**
** Returns          GATT_SUCCESS if disconnected.
**
*******************************************************************************/
    GATT_API extern tGATT_STATUS GATT_Disconnect (UINT16 conn_id);



/*******************************************************************************
**
** Function         GATT_GetConnectionInfor
**
** Description      This function use conn_id to find its associated BD address and applciation
**                  interface
**
** Parameters        conn_id: connection id  (input)
**                   p_gatt_if: applicaiton interface (output)
**                   bd_addr: peer device address. (output)
**
** Returns          TRUE the ligical link information is found for conn_id
**
*******************************************************************************/
    GATT_API extern BOOLEAN GATT_GetConnectionInfor(UINT16 conn_id, tGATT_IF *p_gatt_if, BD_ADDR bd_addr);


/*******************************************************************************
**
** Function         GATT_GetConnIdIfConnected
**
** Description      This function find the conn_id if the logical link for BD address
**                  and applciation interface is connected
**
** Parameters        gatt_if: applicaiton interface (input)
**                   bd_addr: peer device address. (input)
**                   p_conn_id: connection id  (output)
**
** Returns          TRUE the ligical link is connected
**
*******************************************************************************/
    GATT_API extern BOOLEAN GATT_GetConnIdIfConnected(tGATT_IF gatt_if, BD_ADDR bd_addr, UINT16 *p_conn_id);

#ifdef __cplusplus

}
#endif

#endif  /* GATT_API_H */
