#ifndef NW4R_DB_DIRECT_PRINT_H
#define NW4R_DB_DIRECT_PRINT_H

#include <nw4r/types_nw4r.h>

#include <revolution/GX.h>

#define NW4R_DB_FONT_CHAR_WIDTH 6
#define NW4R_DB_FONT_CHAR_HEIGHT 7
#define NW4R_DB_FONT_LEADING 10

namespace nw4r {
namespace db {

void DirectPrint_Init();
bool DirectPrint_IsActive();

void DirectPrint_EraseXfb(int x, int y, int width, int height);

void DirectPrint_ChangeXfb(void* pXfb, u16 width, u16 height);
void DirectPrint_ChangeXfb(void* pXfb);

void DirectPrint_StoreCache();

void DirectPrint_Printf(int x, int y, const char* pFmt, ...);
void DirectPrint_Printf(int x, int y, bool turnOver, const char* pFmt, ...);

void DirectPrint_DrawString(int x, int y, const char* pFmt, ...);
void DirectPrint_DrawString(int x, int y, bool turnOver, const char* pFmt, ...);

void DirectPrint_SetColor(GXColor color);
void DirectPrint_SetColor(u8 r, u8 g, u8 b);
GXColor DirectPrint_GetColor();

namespace detail {

void DirectPrint_DrawStringToXfb(int x, int y, const char* pFmt,
                                 std::va_list list, bool turnOver,
                                 bool backErase);

void* DirectPrint_SetupFB(const GXRenderModeObj* pRenderMode);

} // namespace detail
} // namespace db
} // namespace nw4r

#endif
