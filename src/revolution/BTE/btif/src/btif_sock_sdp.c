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
 *  Filename:      btif_hf.c
 *
 *  Description:   Handsfree Profile Bluetooth Interface
 *
 *
 ***********************************************************************************/

#include <hardware/bluetooth.h>
#include <hardware/bt_sock.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

#define LOG_TAG "BTIF_SOCK_SDP"
#include "btif_common.h"
#include "btif_util.h"

#include "bd.h"

#include "bta_api.h"


#include "bt_target.h"
#include "gki.h"
#include "hcimsgs.h"
#include "sdp_api.h"
#include "btu.h"
#include "btm_api.h"
#include "btm_int.h"
#include "btif_sock_sdp.h"
#include "utl.h"
#include "../bta/pb/bta_pbs_int.h"
#include "../include/bta_op_api.h"
#include <cutils/log.h>

#define RESERVED_SCN_PBS 19
#define RESERVED_SCN_OPS 12

#define UUID_MAX_LENGTH 16


#define IS_UUID(u1,u2)  !memcmp(u1,u2,UUID_MAX_LENGTH)


#define BTM_NUM_PROTO_ELEMS 2
static int add_sdp_by_uuid(const char *name,  const uint8_t *service_uuid, UINT16 channel)
{

    UINT32 btm_sdp_handle;

    tSDP_PROTOCOL_ELEM  proto_elem_list[BTM_NUM_PROTO_ELEMS];

    /* register the service */
    if ((btm_sdp_handle = SDP_CreateRecord()) != FALSE)
    {
        /*** Fill out the protocol element sequence for SDP ***/
        proto_elem_list[0].protocol_uuid = UUID_PROTOCOL_L2CAP;
        proto_elem_list[0].num_params = 0;
        proto_elem_list[1].protocol_uuid = UUID_PROTOCOL_RFCOMM;
        proto_elem_list[1].num_params = 1;

        proto_elem_list[1].params[0] = channel;

        if (SDP_AddProtocolList(btm_sdp_handle, BTM_NUM_PROTO_ELEMS,
            proto_elem_list))
        {
            UINT8           buff[48];
            UINT8           *p, *type_buf[1];
            UINT8       type[1], type_len[1];
         p = type_buf[0] = buff;
         type[0] = UUID_DESC_TYPE;

//         UINT8_TO_BE_STREAM  (p, (UUID_DESC_TYPE << 3) | SIZE_SIXTEEN_BYTES);
         ARRAY_TO_BE_STREAM (p, service_uuid, 16);
            type_len[0] = 16;
            if( SDP_AddSequence(btm_sdp_handle, (UINT16) ATTR_ID_SERVICE_CLASS_ID_LIST,
                          1, type, type_len, type_buf) )
//            if (SDP_AddServiceClassIdList(btm_sdp_handle, 1, &service_uuid))
            {
                if ((SDP_AddAttribute(btm_sdp_handle, ATTR_ID_SERVICE_NAME,
                    TEXT_STR_DESC_TYPE, (UINT32)(strlen(name)+1),
                    (UINT8 *)name)) )
                {
                    UINT16  list[1];

                    /* Make the service browseable */
                    list[0] = UUID_SERVCLASS_PUBLIC_BROWSE_GROUP;
                    if ((SDP_AddUuidSequence (btm_sdp_handle,  ATTR_ID_BROWSE_GROUP_LIST,
                        1, list)) )

                        return btm_sdp_handle;
                }
            }
        }
    }

    return 0;
}


/* Realm Character Set */
#define BTA_PBS_REALM_CHARSET   0       /* ASCII */

/* Specifies whether or not client's user id is required during obex authentication */
#define BTA_PBS_USERID_REQ      FALSE
extern const tBTA_PBS_CFG bta_pbs_cfg;
const tBTA_PBS_CFG bta_pbs_cfg =
{
    BTA_PBS_REALM_CHARSET,      /* Server only */
    BTA_PBS_USERID_REQ,         /* Server only */
    (BTA_PBS_SUPF_DOWNLOAD | BTA_PBS_SURF_BROWSE),
    BTA_PBS_REPOSIT_LOCAL,
};

static int add_pbap_sdp(const char* p_service_name, int scn)
{

    tSDP_PROTOCOL_ELEM  protoList [3];
    UINT16              pbs_service = UUID_SERVCLASS_PBAP_PSE;
    UINT16              browse = UUID_SERVCLASS_PUBLIC_BROWSE_GROUP;
    BOOLEAN             status = FALSE;
    UINT32              sdp_handle = 0;
    tBTA_PBS_CFG *p_bta_pbs_cfg = (tBTA_PBS_CFG *)&bta_pbs_cfg;

    APPL_TRACE_DEBUG2("scn %d, service name %s", scn, p_service_name);

    if ((sdp_handle = SDP_CreateRecord()) == 0)
    {
        APPL_TRACE_ERROR0("PBS SDP: Unable to register PBS Service");
        return sdp_handle;
    }

    /* add service class */
    if (SDP_AddServiceClassIdList(sdp_handle, 1, &pbs_service))
    {
        memset( protoList, 0 , 3*sizeof(tSDP_PROTOCOL_ELEM) );
        /* add protocol list, including RFCOMM scn */
        protoList[0].protocol_uuid = UUID_PROTOCOL_L2CAP;
        protoList[0].num_params = 0;
        protoList[1].protocol_uuid = UUID_PROTOCOL_RFCOMM;
        protoList[1].num_params = 1;
        protoList[1].params[0] = scn;
        protoList[2].protocol_uuid = UUID_PROTOCOL_OBEX;
        protoList[2].num_params = 0;

        if (SDP_AddProtocolList(sdp_handle, 3, protoList))
        {
            status = TRUE;  /* All mandatory fields were successful */

            /* optional:  if name is not "", add a name entry */
            if (*p_service_name != '\0')
                SDP_AddAttribute(sdp_handle,
                                 (UINT16)ATTR_ID_SERVICE_NAME,
                                 (UINT8)TEXT_STR_DESC_TYPE,
                                 (UINT32)(strlen(p_service_name) + 1),
                                 (UINT8 *)p_service_name);

            /* Add in the Bluetooth Profile Descriptor List */
            SDP_AddProfileDescriptorList(sdp_handle,
                                             UUID_SERVCLASS_PHONE_ACCESS,
                                             BTA_PBS_DEFAULT_VERSION);

        } /* end of setting mandatory protocol list */
    } /* end of setting mandatory service class */

    /* add supported feature and repositories */
    if (status)
    {
        SDP_AddAttribute(sdp_handle, ATTR_ID_SUPPORTED_FEATURES, UINT_DESC_TYPE,
                  (UINT32)1, (UINT8*)&p_bta_pbs_cfg->supported_features);
        SDP_AddAttribute(sdp_handle, ATTR_ID_SUPPORTED_REPOSITORIES, UINT_DESC_TYPE,
                  (UINT32)1, (UINT8*)&p_bta_pbs_cfg->supported_repositories);

        /* Make the service browseable */
        SDP_AddUuidSequence (sdp_handle, ATTR_ID_BROWSE_GROUP_LIST, 1, &browse);
    }

    if (!status)
    {
        SDP_DeleteRecord(sdp_handle);
        sdp_handle = 0;
        APPL_TRACE_ERROR0("bta_pbs_sdp_register FAILED");
    }
    else
    {
        bta_sys_add_uuid(pbs_service);  /* UUID_SERVCLASS_PBAP_PSE */
        APPL_TRACE_DEBUG1("PBS:  SDP Registered (handle 0x%08x)", sdp_handle);
    }

    return sdp_handle;
}


/* object format lookup table */
static const tBTA_OP_FMT bta_ops_obj_fmt[] =
{
    BTA_OP_VCARD21_FMT,
    BTA_OP_VCARD30_FMT,
    BTA_OP_VCAL_FMT,
    BTA_OP_ICAL_FMT,
    BTA_OP_VNOTE_FMT,
    BTA_OP_VMSG_FMT,
    BTA_OP_OTHER_FMT
};

#define BTA_OPS_NUM_FMTS        7
#define BTA_OPS_PROTOCOL_COUNT  3

#ifndef BTUI_OPS_FORMATS
#define BTUI_OPS_FORMATS            (BTA_OP_VCARD21_MASK | BTA_OP_VCARD30_MASK | \
                                         BTA_OP_VCAL_MASK | BTA_OP_ICAL_MASK | \
                                         BTA_OP_VNOTE_MASK | BTA_OP_VMSG_MASK | \
                                         BTA_OP_ANY_MASK )
#endif

static int add_ops_sdp(const char *p_service_name,int scn)
{


    tSDP_PROTOCOL_ELEM  protoList [BTA_OPS_PROTOCOL_COUNT];
    UINT16      servclass = UUID_SERVCLASS_OBEX_OBJECT_PUSH;
    int         i, j;
    tBTA_UTL_COD cod;
    UINT8       desc_type[BTA_OPS_NUM_FMTS];
    UINT8       type_len[BTA_OPS_NUM_FMTS];
    UINT8       *type_value[BTA_OPS_NUM_FMTS];
    UINT16      browse;
    UINT32 sdp_handle;
    tBTA_OP_FMT_MASK    formats = BTUI_OPS_FORMATS;

    APPL_TRACE_DEBUG2("scn %d, service name %s", scn, p_service_name);

    sdp_handle = SDP_CreateRecord();

    /* add service class */
    if (SDP_AddServiceClassIdList(sdp_handle, 1, &servclass))
    {
        /* add protocol list, including RFCOMM scn */
        protoList[0].protocol_uuid = UUID_PROTOCOL_L2CAP;
        protoList[0].num_params = 0;
        protoList[1].protocol_uuid = UUID_PROTOCOL_RFCOMM;
        protoList[1].num_params = 1;
        protoList[1].params[0] = scn;
        protoList[2].protocol_uuid = UUID_PROTOCOL_OBEX;
        protoList[2].num_params = 0;

        if (SDP_AddProtocolList(sdp_handle, BTA_OPS_PROTOCOL_COUNT, protoList))
        {
            SDP_AddAttribute(sdp_handle,
               (UINT16)ATTR_ID_SERVICE_NAME,
                (UINT8)TEXT_STR_DESC_TYPE,
                (UINT32)(strlen(p_service_name) + 1),
                (UINT8 *)p_service_name);

            SDP_AddProfileDescriptorList(sdp_handle,
                UUID_SERVCLASS_OBEX_OBJECT_PUSH,
                0x0100);
        }
    }

    /* Make the service browseable */
    browse = UUID_SERVCLASS_PUBLIC_BROWSE_GROUP;
    SDP_AddUuidSequence (sdp_handle, ATTR_ID_BROWSE_GROUP_LIST, 1, &browse);

    /* add sequence for supported types */
    for (i = 0, j = 0; i < BTA_OPS_NUM_FMTS; i++)
    {
        if ((formats >> i) & 1)
        {
            type_value[j] = (UINT8 *) &bta_ops_obj_fmt[i];
            desc_type[j] = UINT_DESC_TYPE;
            type_len[j++] = 1;
        }
    }

    SDP_AddSequence(sdp_handle, (UINT16) ATTR_ID_SUPPORTED_FORMATS_LIST,
        (UINT8) j, desc_type, type_len, type_value);

    /* set class of device */
    cod.service = BTM_COD_SERVICE_OBJ_TRANSFER;
    utl_set_device_class(&cod, BTA_UTL_SET_COD_SERVICE_CLASS);

    bta_sys_add_uuid(servclass); /* UUID_SERVCLASS_OBEX_OBJECT_PUSH */

    return sdp_handle;
}
#define SPP_NUM_PROTO_ELEMS 2
static int add_spp_sdp(const char *service_name, int scn)
{
    UINT16 serviceclassid = UUID_SERVCLASS_SERIAL_PORT;
    tSDP_PROTOCOL_ELEM  proto_elem_list[SPP_NUM_PROTO_ELEMS];
    int              sdp_handle;

    APPL_TRACE_DEBUG2("scn %d, service name %s", scn, service_name);

    /* register the service */
    if ((sdp_handle = SDP_CreateRecord()) != FALSE)
    {
        /*** Fill out the protocol element sequence for SDP ***/
        proto_elem_list[0].protocol_uuid = UUID_PROTOCOL_L2CAP;
        proto_elem_list[0].num_params = 0;
        proto_elem_list[1].protocol_uuid = UUID_PROTOCOL_RFCOMM;
        proto_elem_list[1].num_params = 1;

        proto_elem_list[1].params[0] = scn;

        if (SDP_AddProtocolList(sdp_handle, SPP_NUM_PROTO_ELEMS, proto_elem_list))
        {
            if (SDP_AddServiceClassIdList(sdp_handle, 1, &serviceclassid))
            {
                if ((SDP_AddAttribute(sdp_handle, ATTR_ID_SERVICE_NAME,
                                TEXT_STR_DESC_TYPE, (UINT32)(strlen(service_name)+1),
                                (UINT8 *)service_name)))
                {
                    UINT16  list[1];
                    /* Make the service browseable */
                    list[0] = UUID_SERVCLASS_PUBLIC_BROWSE_GROUP;
                    SDP_AddUuidSequence (sdp_handle,  ATTR_ID_BROWSE_GROUP_LIST,
                                    1, list);
                }
            }
        }
    }
    return sdp_handle;
}



static int add_rfc_sdp_by_uuid(const char* name, const uint8_t* uuid, int scn)
{
    int handle = 0;

    APPL_TRACE_DEBUG2("name:%s, scn:%d", name, scn);

    /*
        Bluetooth Socket API relies on having preregistered bluez sdp records for HSAG, HFAG, OPP & PBAP
        that are mapped to rc chan 10, 11,12 & 19. Today HSAG and HFAG is routed to BRCM AG and are not
        using BT socket API so for now we will need to support OPP and PBAP to enable 3rd party developer
        apps running on BRCM Android.

        To do this we will check the UUID for the requested service and mimic the SDP records of bluez
        upon reception.  See functions add_opush() and add_pbap() in sdptool.c for actual records
    */

    /* special handling for preregistered bluez services (OPP, PBAP) that we need to mimic */

    int final_scn = get_reserved_rfc_channel(uuid);
    if (final_scn == -1)
    {
        final_scn=scn;
    }
    if (IS_UUID(UUID_OBEX_OBJECT_PUSH,uuid))
    {
        handle = add_ops_sdp(name,final_scn);
    }
    else if (IS_UUID(UUID_PBAP_PSE,uuid))
    {
        handle = add_pbap_sdp(name, final_scn); //PBAP Server is always 19
    }
    else if (IS_UUID(UUID_SPP, uuid))
    {
        handle = add_spp_sdp(name, final_scn);
    }
    else
    {
        handle = add_sdp_by_uuid(name, uuid, final_scn);
    }
    return handle;
}

BOOLEAN is_reserved_rfc_channel(int scn)
{
    switch(scn)
    {
        case RESERVED_SCN_PBS:
        case RESERVED_SCN_OPS:
            return TRUE;
    }
    return FALSE;
}


int get_reserved_rfc_channel (const uint8_t* uuid)
{
    if (IS_UUID(UUID_PBAP_PSE,uuid))
    {
      return RESERVED_SCN_PBS;
    }
    else if (IS_UUID(UUID_OBEX_OBJECT_PUSH,uuid))
    {
      return RESERVED_SCN_OPS;
    }
    return -1;
}

int add_rfc_sdp_rec(const char* name, const uint8_t* uuid, int scn)
{
    int sdp_handle = 0;
    if(is_uuid_empty(uuid))
    {
        switch(scn)
        {
            case RESERVED_SCN_PBS: // PBAP Reserved port
                uuid = UUID_PBAP_PSE;
                break;
             case RESERVED_SCN_OPS:
                uuid = UUID_OBEX_OBJECT_PUSH;
                break;
            default:
                uuid = UUID_SPP;
                break;
        }
    }
    sdp_handle = add_rfc_sdp_by_uuid(name, uuid, scn);
    return sdp_handle;
}

void del_rfc_sdp_rec(int handle)
{
    if(handle != -1 && handle != 0)
        SDP_DeleteRecord( handle );
}

