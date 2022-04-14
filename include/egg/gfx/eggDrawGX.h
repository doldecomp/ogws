#ifndef EGG_GFX_DRAWGX_H
#define EGG_GFX_DRAWGX_H
#include "types_egg.h"
#include <GX/GX.h>

namespace EGG
{
    class DrawGX
    {
    public:
        enum VtxType
        {
            VTX_TYPE_0,
            VTX_TYPE_1,
            VTX_TYPE_2,
            VTX_TYPE_3,
            VTX_TYPE_4,
            VTX_TYPE_5,
            VTX_TYPE_6,
            VTX_TYPE_7,
            VTX_TYPE_8,
            VTX_TYPE_9,
            VTX_TYPE_10,
            VTX_TYPE_11,
            VTX_TYPE_12,
            VTX_TYPE_13
        };

        enum Blend
        {
            BLEND_0,
            BLEND_1,
            BLEND_2,
            BLEND_3,
            BLEND_4,
            BLEND_5,
            BLEND_6,
            BLEND_7,
            BLEND_8,
            BLEND_9,

            BLEND_MAX
        };

        struct DisplayList
        {
            void *m_list; // at 0x0
            u32 m_size; // at 0x4
        };

    public:
        static DisplayList * GetDisplayList(u32 i) { return &s_DL[i]; }
        static void SetVtxState(VtxType);
        static void SetBlendMode(Blend);

    public:
        static const GXColor sColorBlack;
        static const GXColor sColorWhite;
        static const GXColor sColorRed;
        static const GXColor sColorGreen;
        static const GXColor sColorBlue;
        static const GXColor sColorOrange;

        static Matrix34f s_cameraMtx;

    private:
        static DisplayList s_DL[18];
    };
}

#endif