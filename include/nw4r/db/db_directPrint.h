#ifndef NW4R_DB_DIRECT_PRINT_H
#define NW4R_DB_DIRECT_PRINT_H

#include <nw4r/types_nw4r.h>

#include <revolution/GX.h>

namespace nw4r {
namespace db {

void DirectPrint_Init();
bool DirectPrint_IsActive();
void DirectPrint_ChangeXfb(void* pFrameBuf, u16 width, u16 height);
void DirectPrint_ChangeXfb(void* pFrameBuf);

namespace detail {

void* DirectPrint_SetupFB(const GXRenderModeObj* pRenderMode);

} // namespace detail

} // namespace db
} // namespace nw4r

#endif
