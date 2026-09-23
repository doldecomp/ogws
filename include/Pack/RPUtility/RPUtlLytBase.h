#ifndef RP_UTILITY_LYT_BASE_H
#define RP_UTILITY_LYT_BASE_H

#include <Pack/types_pack.h>

#include <revolution/GX.h>

class RPUtlLytBase {

public:
    static void beginDrawLine(GXColor color, u16 num, u8 width);
};

#endif
