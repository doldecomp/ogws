#ifndef EGG_GFX_ANALIZE_DL_H
#define EGG_GFX_ANALIZE_DL_H
#include "types_egg.h"
#include "eggAssert.h"
#include "g3d_resshp.h"

namespace EGG
{
    class AnalizeDL
    {
    public:
        enum EResultType
        {
            TYPE_0,
            TYPE_1,
            TYPE_2,
            TYPE_3,
            TYPE_VERTEX
        };

        struct Result
        {
            int m_type; // at 0x0
            u16 SHORT_0x4;
            u16 SHORT_0x6;
            u16 SHORT_0x8;
            u16 SHORT_0xA;
            u16 SHORT_0xC;
            u16 SHORT_0xE;
            u16 SHORT_0x10;
            u16 SHORT_0x12;
            u16 SHORT_0x14;
            u16 SHORT_0x16;
            u16 SHORT_0x18;
            u16 SHORT_0x1A;
            u16 SHORT_0x1C;
            u16 SHORT_0x1E;
            u16 SHORT_0x20;
            u16 SHORT_0x22;
            u16 SHORT_0x24;
            u16 SHORT_0x26;
            u16 SHORT_0x28;
            u16 SHORT_0x2A;
            u32 WORD_0x2C;
            u32 WORD_0x30;
            u32 WORD_0x34;
            int WORD_0x38;
            int WORD_0x3C;
            nw4r::math::VEC3 VEC3_0x40;
        };

    public:
        static void FUN_800854f8(const void *, nw4r::g3d::ResShp);
        static int FUN_80085670(const void *);

        static Result * getVtxResult()
        {
            #line 115
            EGG_ASSERT(s_result.m_type == TYPE_VERTEX);
            return &s_result;
        }

    private:
        static Result s_result;
    };
}

#endif