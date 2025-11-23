#ifndef RVL_SDK_PUBLIC_BTE_H
#define RVL_SDK_PUBLIC_BTE_H
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *
 * BTE
 *
 ******************************************************************************/
#include <revolution/BTE/include/bt_target.h>
#include <revolution/BTE/include/bt_trace.h>
#include <revolution/BTE/include/bte.h>
#include <revolution/BTE/include/bte_appl.h>
#include <revolution/BTE/include/bte_common.h>
#include <revolution/BTE/include/gki_target.h>

/******************************************************************************
 *
 * BTA
 *
 ******************************************************************************/
#include <revolution/BTE/bta/include/bta_api.h>
#include <revolution/BTE/bta/include/bta_hh_api.h>

/******************************************************************************
 *
 * API
 *
 ******************************************************************************/
#include <revolution/BTE/stack/include/l2c_api.h>

/******************************************************************************
 *
 * RVL
 *
 ******************************************************************************/
#include <revolution/BTE/rvl/uusb_ppc.h>

// Yeah...
#undef TRUE

#ifdef __cplusplus
}
#endif
#endif
