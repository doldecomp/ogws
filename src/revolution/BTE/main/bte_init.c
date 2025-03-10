/******************************************************************************
 *
 *  Copyright (C) 2000-2012 Broadcom Corporation
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
 *  This module contains the routines that initialize the stack components. 
 *  It must be called before the BTU task is started.
 *
 ******************************************************************************/

#include "bt_target.h"
#include <string.h>

#ifndef BTA_INCLUDED
#define BTA_INCLUDED FALSE
#endif

/* Include initialization functions definitions */
#if (defined(RFCOMM_INCLUDED) && RFCOMM_INCLUDED == TRUE)
#include "port_api.h"
#endif

#if (defined(TCS_INCLUDED) && TCS_INCLUDED == TRUE)
#include "tcs_api.h"
#endif

#if (defined(OBX_INCLUDED) && OBX_INCLUDED == TRUE)
#include "obx_api.h"
#endif

#if (defined(BNEP_INCLUDED) && BNEP_INCLUDED == TRUE)
#include "bnep_api.h"
#endif

#if (defined(GAP_INCLUDED) && GAP_INCLUDED == TRUE)
#include "gap_api.h"
#endif

#if ((defined(CTP_INCLUDED) && CTP_INCLUDED == TRUE))
#include "ctp_api.h"
#endif

#if ((defined(ICP_INCLUDED) && ICP_INCLUDED == TRUE))
#include "icp_api.h"
#endif

#if (defined(SPP_INCLUDED) && SPP_INCLUDED == TRUE)
#include "spp_api.h"
#endif

#if (defined(DUN_INCLUDED) && DUN_INCLUDED == TRUE)
#include "dun_api.h"
#endif

#if (defined(GOEP_INCLUDED) &&  GOEP_INCLUDED == TRUE)
#include "goep_util.h"
#endif /* GOEP included */

#if (defined(FTP_INCLUDED) && FTP_INCLUDED == TRUE)
#include "ftp_api.h"
#endif /* FTP */

#if (defined(OPP_INCLUDED) && OPP_INCLUDED == TRUE)
#include "opp_api.h"
#endif /* OPP */

#if (defined(BIP_INCLUDED) && BIP_INCLUDED == TRUE)
#include "bip_api.h"
#endif

#if (defined(BTU_BTA_INCLUDED) && BTU_BTA_INCLUDED == TRUE)
#if (defined(BTA_BI_INCLUDED) && BTA_BI_INCLUDED == TRUE)
#include "bta_bi_api.h"
#endif
#endif

#if (defined(HFP_INCLUDED) && HFP_INCLUDED == TRUE)
#include "hfp_api.h"
#endif

#if ((defined(HSP2_INCLUDED) && HSP2_INCLUDED == TRUE)) || \
    ((defined(HFP_INCLUDED) && HFP_INCLUDED == TRUE))
#include "hsp2_api.h"
#endif

#if (defined(HCRP_INCLUDED) && HCRP_INCLUDED == TRUE)
#if (defined(HCRP_CLIENT_INCLUDED) && HCRP_CLIENT_INCLUDED == TRUE)
#include "hcrp_api.h"
#endif
#if (defined(HCRP_SERVER_INCLUDED) && HCRP_SERVER_INCLUDED == TRUE)
#include "hcrpm_api.h"
#endif
#endif

#if (defined(BPP_INCLUDED) && BPP_INCLUDED == TRUE)
#include "bpp_api.h"
#endif

#if (defined(PAN_INCLUDED) && PAN_INCLUDED == TRUE)
#include "pan_api.h"
#endif

#if (defined(AVRC_INCLUDED) && AVRC_INCLUDED == TRUE)
#include "avrc_api.h"
#endif

#if (defined(A2D_INCLUDED) && A2D_INCLUDED == TRUE)
#include "a2d_api.h"
#endif


#if (defined(HID_DEV_INCLUDED) && HID_DEV_INCLUDED == TRUE)
#include "hidd_api.h"
#endif

#if (defined(HID_HOST_INCLUDED) && HID_HOST_INCLUDED == TRUE)
#include "hidh_api.h"
#endif

#if (defined(SAP_SERVER_INCLUDED) && SAP_SERVER_INCLUDED == TRUE)
#include "sap_api.h"
#endif  /* SAP_SERVER_INCLUDED */

#if (defined(MCA_INCLUDED) && MCA_INCLUDED == TRUE)
#include "mca_api.h"
#endif

#if (defined(BLE_INCLUDED) && BLE_INCLUDED == TRUE)
#include "gatt_api.h"
#if (defined(SMP_INCLUDED) && SMP_INCLUDED == TRUE)
#include "smp_api.h"
#endif
#endif

// btla-specific ++
/***** BTA Modules ******/
#if BTA_INCLUDED == TRUE && BTA_DYNAMIC_MEMORY == TRUE
#include "bta_api.h"
#include "bta_sys.h"

#if BTA_AC_INCLUDED == TRUE
#include "bta_acs_int.h"
#include "bta_acc_int.h"
#endif

#if BTA_AG_INCLUDED == TRUE
#include "bta_ag_int.h"
#endif

#if BTA_HS_INCLUDED == TRUE
#include "bta_hs_int.h"
#endif

#include "bta_dm_int.h"

#if BTA_DG_INCLUDED == TRUE
#include "bta_dg_api.h"
#include "bta_dg_int.h"
#endif

#if BTA_FT_INCLUDED == TRUE
#include "bta_ftc_int.h"
#include "bta_fts_int.h"
#endif

#if BTA_PBC_INCLUDED == TRUE
#include "bta_pbc_int.h"
#endif

#if BTA_PBS_INCLUDED == TRUE
#include "bta_pbs_int.h"
#endif

#if BTA_OP_INCLUDED == TRUE
#include "bta_opc_int.h"
#include "bta_ops_int.h"
#endif

#if BTA_SS_INCLUDED==TRUE
#include "bta_ss_int.h"
#endif

#if BTA_CT_INCLUDED==TRUE
#include "bta_ct_int.h"
#endif

#if BTA_CG_INCLUDED==TRUE
#include "bta_cg_int.h"
#endif

#if BTA_BI_INCLUDED==TRUE
#include "bta_bic_int.h"
#include "bta_bis_int.h"
#endif

#if BTA_PR_INCLUDED==TRUE
#include "bta_pr_int.h"
#endif

#if BTA_AR_INCLUDED==TRUE
#include "bta_ar_int.h"
#endif
#if BTA_AV_INCLUDED==TRUE
#include "bta_av_int.h"
#endif

#if BTA_SC_INCLUDED==TRUE
#include "bta_sc_int.h"
#endif

#if BTA_HD_INCLUDED==TRUE
#include "bta_hd_int.h"
#endif

#if BTA_HH_INCLUDED==TRUE
#include "bta_hh_int.h"
#endif

#if BTA_FM_INCLUDED==TRUE
#include "bta_fm_int.h"
#endif

#if BTA_FMTX_INCLUDED==TRUE
#include "bta_fmtx_int.h"
#endif

#if BTA_JV_INCLUDED==TRUE
#include "bta_jv_int.h"
tBTA_JV_CB *bta_jv_cb_ptr = NULL;
#endif

#if BTA_MCE_INCLUDED == TRUE
#include "bta_mce_int.h"
#endif

#if BTA_MSE_INCLUDED == TRUE
#include "bta_mse_int.h"
#endif

#if BTA_HL_INCLUDED == TRUE
#include "bta_hl_int.h"
#endif

#if BTA_GATT_INCLUDED == TRUE
#include "bta_gattc_int.h"
#include "bta_gatts_int.h"
#endif

#if BTA_PAN_INCLUDED==TRUE
#include "bta_pan_int.h"
#endif

#include "bta_sys_int.h"

/* control block for patch ram downloading */
#include "bta_prm_int.h"

#endif /* BTA_INCLUDED */
// btla-specific --

/*****************************************************************************
**                          F U N C T I O N S                                *
******************************************************************************/

/*****************************************************************************
**
** Function         BTE_InitStack
**
** Description      Initialize control block memory for each component.
**
**                  Note: The core stack components must be called
**                      before creating the BTU Task.  The rest of the
**                      components can be initialized at a later time if desired
**                      as long as the component's init function is called
**                      before accessing any of its functions.
**
** Returns          void
**
******************************************************************************/
BT_API void BTE_InitStack(void)
{
/* Initialize the optional stack components */

/****************************
** RFCOMM and its profiles **
*****************************/
#if (defined(RFCOMM_INCLUDED) && RFCOMM_INCLUDED == TRUE)
    RFCOMM_Init();

#if (defined(SPP_INCLUDED) && SPP_INCLUDED == TRUE)
    SPP_Init();
#endif  /* SPP */

#if (defined(DUN_INCLUDED) && DUN_INCLUDED == TRUE)
    DUN_Init();
#endif  /* DUN */

#if (defined(HSP2_INCLUDED) && HSP2_INCLUDED == TRUE)
    HSP2_Init();
#endif  /* HSP2 */

#if (defined(HFP_INCLUDED) && HFP_INCLUDED == TRUE)
    HFP_Init();
#endif  /* HFP */

/**************************
** OBEX and its profiles **
***************************/
#if (defined(OBX_INCLUDED) && OBX_INCLUDED == TRUE)
    OBX_Init();
#if (defined(BIP_INCLUDED) && BIP_INCLUDED == TRUE)
    BIP_Init();
#if (defined(BTU_BTA_INCLUDED) && BTU_BTA_INCLUDED == TRUE)
#if (defined(BTA_BI_INCLUDED) && BTA_BI_INCLUDED == TRUE)
    BTA_BicInit();
#endif  /* BTA BI */
#endif
#endif  /* BIP */

#if (defined(GOEP_INCLUDED) && GOEP_INCLUDED == TRUE)
    GOEP_Init();
#endif /* GOEP */


#if (defined(FTP_INCLUDED) && FTP_INCLUDED == TRUE)
    FTP_Init();
#endif
#if (defined(OPP_INCLUDED) && OPP_INCLUDED == TRUE)
    OPP_Init();
#endif

#if (defined(BPP_INCLUDED) && BPP_INCLUDED == TRUE)
    BPP_Init();
#endif  /* BPP */
#endif  /* OBX */


#endif  /* RFCOMM Included */

/*************************
** TCS and its profiles **
**************************/
#if (defined(TCS_INCLUDED) && TCS_INCLUDED == TRUE)
    TCS_Init();

#if (defined(CTP_INCLUDED) && CTP_INCLUDED == TRUE)
    CTP_Init();
#endif /* CTP_INCLUDED */

#if (defined(ICP_INCLUDED) && ICP_INCLUDED == TRUE)
    ICP_Init();
#endif /* ICP_INCLUDED */

#endif /* TCS_INCLUDED */


/**************************
** BNEP and its profiles **
***************************/
#if (defined(BNEP_INCLUDED) && BNEP_INCLUDED == TRUE)
    BNEP_Init();

#if (defined(PAN_INCLUDED) && PAN_INCLUDED == TRUE)
    PAN_Init();
#endif  /* PAN */
#endif  /* BNEP Included */


/**************************
** AVDT and its profiles **
***************************/
#if (defined(A2D_INCLUDED) && A2D_INCLUDED == TRUE)
    A2D_Init();
#endif  /* AADP */


#if (defined(AVRC_INCLUDED) && AVRC_INCLUDED == TRUE)
    AVRC_Init();
#endif


/***********
** Others **
************/
#if (defined(GAP_INCLUDED) && GAP_INCLUDED == TRUE)
    GAP_Init();
#endif  /* GAP Included */

#if (defined(HCRP_INCLUDED) && HCRP_INCLUDED == TRUE)
#if (defined(HCRP_CLIENT_INCLUDED) && HCRP_CLIENT_INCLUDED == TRUE)
    HCRP_Init();
#endif
#if (defined(HCRP_SERVER_INCLUDED) && HCRP_SERVER_INCLUDED == TRUE)
    HCRPM_Init();
#endif
#endif  /* HCRP Included */

#if (defined(SAP_SERVER_INCLUDED) && SAP_SERVER_INCLUDED == TRUE)
    SAP_Init();
#endif  /* SAP_SERVER_INCLUDED */

#if (defined(HID_DEV_INCLUDED) && HID_DEV_INCLUDED == TRUE)
    HID_DevInit();
#endif
#if (defined(HID_HOST_INCLUDED) && HID_HOST_INCLUDED == TRUE)
    HID_HostInit();
#endif

#if (defined(MCA_INCLUDED) && MCA_INCLUDED == TRUE)
    MCA_Init();
#endif  /* SAP_SERVER_INCLUDED */

/****************
** BTA Modules **
*****************/
// btla-specific ++
#if (BTA_INCLUDED == TRUE && BTA_DYNAMIC_MEMORY == TRUE)
    memset((void*)bta_sys_cb_ptr, 0, sizeof(tBTA_SYS_CB));
    memset((void*)bta_dm_cb_ptr, 0, sizeof(tBTA_DM_CB));
    memset((void*)bta_dm_search_cb_ptr, 0, sizeof(tBTA_DM_SEARCH_CB));
    memset((void*)bta_dm_di_cb_ptr, 0, sizeof(tBTA_DM_DI_CB));
    memset((void*)bta_prm_cb_ptr, 0, sizeof(tBTA_PRM_CB));

#if BTA_AC_INCLUDED == TRUE
    memset((void*)bta_acc_cb_ptr, 0, sizeof(tBTA_ACC_CB));
    memset((void*)bta_acs_cb_ptr, 0, sizeof(tBTA_ACS_CB));
#endif
#if BTA_AG_INCLUDED == TRUE
    memset((void*)bta_ag_cb_ptr, 0, sizeof(tBTA_AG_CB));
#endif
#if BTA_HS_INCLUDED == TRUE
    memset((void*)bta_hs_cb_ptr, 0, sizeof(tBTA_HS_CB));
#endif
#if BTA_DG_INCLUDED == TRUE
    memset((void*)bta_dg_cb_ptr, 0, sizeof(tBTA_DG_CB));
#endif
#if BTA_FT_INCLUDED==TRUE
    memset((void*)bta_ftc_cb_ptr, 0, sizeof(tBTA_FTC_CB));
    memset((void*)bta_fts_cb_ptr, 0, sizeof(tBTA_FTS_CB));
#endif
#if BTA_PBC_INCLUDED==TRUE
    memset((void*)bta_pbc_cb_ptr, 0, sizeof(tBTA_PBC_CB));
#endif
#if BTA_PBS_INCLUDED==TRUE
    memset((void*)bta_pbs_cb_ptr, 0, sizeof(tBTA_PBS_CB));
#endif
#if BTA_OP_INCLUDED==TRUE
    memset((void*)bta_opc_cb_ptr, 0, sizeof(tBTA_OPC_CB));
    memset((void*)bta_ops_cb_ptr, 0, sizeof(tBTA_OPS_CB));
#endif
#if BTA_SS_INCLUDED==TRUE
    memset((void*)bta_ss_cb_ptr, 0, sizeof(tBTA_SS_CB));
#endif
#if BTA_CT_INCLUDED==TRUE
    memset((void*)bta_ct_cb_ptr, 0, sizeof(tBTA_CT_CB));
#endif
#if BTA_CG_INCLUDED==TRUE
    memset((void*)bta_cg_cb_ptr, 0, sizeof(tBTA_CG_CB));
#endif
#if BTA_BI_INCLUDED==TRUE
    memset((void *)bta_bic_cb_ptr, 0, sizeof(tBTA_BIC_CB));
    memset((void *)bta_bis_cb_ptr, 0, sizeof(tBTA_BIS_CB));
#endif
#if BTA_AR_INCLUDED==TRUE
    memset((void *)bta_ar_cb_ptr, 0, sizeof(tBTA_AR_CB));
#endif
#if BTA_AV_INCLUDED==TRUE
    memset((void *)bta_av_cb_ptr, 0, sizeof(tBTA_AV_CB));
#endif
#if BTA_PR_INCLUDED==TRUE
    memset((void *)bta_pr_cb_ptr, 0, sizeof(tBTA_PR_CB));
#endif
#if BTA_SC_INCLUDED==TRUE
    memset((void *)bta_sc_cb_ptr, 0, sizeof(tBTA_SC_CB));
#endif
#if BTA_HD_INCLUDED==TRUE
    memset((void *)bta_hd_cb_ptr, 0, sizeof(tBTA_HD_CB));
#endif
#if BTA_HH_INCLUDED==TRUE
    memset((void *)bta_hh_cb_ptr, 0, sizeof(tBTA_HH_CB));
#endif
#if BTA_FM_INCLUDED==TRUE
    memset((void *)bta_fm_cb_ptr, 0, sizeof(tBTA_FM_CB));
#endif
#if BTA_FMTX_INCLUDED==TRUE
    memset((void *)bta_fmtx_cb_ptr, 0, sizeof(tBTA_FMTX_CB));
#endif
#if 0
#if BTA_JV_INCLUDED==TRUE
    memset((void *)bta_jv_cb_ptr, 0, sizeof(tBTA_JV_CB));
#endif
#endif
#if BTA_HL_INCLUDED==TRUE
    memset((void *)bta_hl_cb_ptr, 0, sizeof(tBTA_HL_CB));
#endif
#if BTA_GATT_INCLUDED==TRUE
    memset((void *)bta_gattc_cb_ptr, 0, sizeof(tBTA_GATTC_CB));
    memset((void *)bta_gatts_cb_ptr, 0, sizeof(tBTA_GATTS_CB));
#endif
#if BTA_PAN_INCLUDED==TRUE
    memset((void *)bta_pan_cb_ptr, 0, sizeof(tBTA_PAN_CB));
#endif

#endif /* BTA_INCLUDED == TRUE */
// btla-specific --
}
