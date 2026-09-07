#ifndef RVL_SDK_BTE_DECOMP_STUBS_H
#define RVL_SDK_BTE_DECOMP_STUBS_H
#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DECOMPCTX)

typedef u8 UINT8;
typedef u16 UINT16;
typedef u32 UINT32;

#define BD_ADDR_LEN 6
typedef UINT8 BD_ADDR[BD_ADDR_LEN];
typedef BD_ADDR* BD_ADDR_PTR;

#define LINK_KEY_LEN 16
typedef UINT8 LINK_KEY[LINK_KEY_LEN];

typedef UINT16 tBTA_HH_ATTR_MASK;
typedef UINT16 tBTA_HH_EVT;
typedef void tBTA_HH;
typedef UINT32 tBTA_SERVICE_MASK;

#endif

#ifdef __cplusplus
}
#endif
#endif
