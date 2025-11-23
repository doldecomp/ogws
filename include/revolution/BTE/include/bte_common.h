/******************************************************************************
 *
 *  NOTICE OF CHANGES
 *  2025/11/23:
 *      - Create header for common BTE/BTA prototypes
 *
 *  Compile with REVOLUTION defined to include these changes.
 *
 ******************************************************************************/

#ifndef BTE_COMMON_H
#define BTE_COMMON_H

#include <revolution/BTE/bta/include/bta_api.h>

void BTE_InitSys(void);
void BTE_BringUpStack(void);
tBTA_STATUS BTA_Init(void);

typedef void (*BTA_CleanUpCallback)(tBTA_STATUS status);
void BTA_CleanUp(BTA_CleanUpCallback p_cb);

#endif /* BTE_COMMON_H */
