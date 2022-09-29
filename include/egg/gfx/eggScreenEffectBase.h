#ifndef EGG_GFX_SCREEN_EFFECT_BASE_H
#define EGG_GFX_SCREEN_EFFECT_BASE_H
#include "types_egg.h"
#include "eggAssert.h"
#include "eggScreen.h"

namespace EGG
{
    class ScreenEffectBase
    {
    public:
        enum ScreenEffectFlags
        {
            EFFECT_VISIBLE = (1 << 0),
            EFFECT_0x2 = (1 << 1)
        };

        enum BufferType
        {
            cBufferType_Hide_1_16,
            cBufferType_1,
            cBufferType_2,
            cBufferType_3,
            cBufferType_Max
        };

        struct EffectBuffer
        {
            TextureBuffer* mpTexBuffer; // at 0x0
            const ScreenEffectBase* mpAllocBase; // at 0x4
            UNKWORD WORD_0x8; // at 0x8
        };

        // Workspace viewport
        struct WorkView
        {
            f32 x1; // at 0x0
            f32 y1; // at 0x4
            f32 x2; // at 0x8
            f32 y2; // at 0xC
            f32 FLOAT_0x10;
            f32 FLOAT_0x14;
        };

        // For constructing full viewport
        struct FullView
        {
            f32 x2; // at 0x0
            f32 y2; // at 0x4
            f32 x1; // at 0x8
            f32 y1; // at 0xC
            f32 cx; // at 0x10
            f32 cy; // at 0x14
            f32 z1; // at 0x18
            f32 z2; // at 0x1C
        };

    private:
        u8 mFlags; // at 0x0
        Screen mScreen; // at 0x4

    public:
        static void clean();

        static void setBuffer(BufferType type, TextureBuffer* buffer)
        {
            #line 163
            EGG_ASSERT(type < cBufferType_Max);
            spBufferSet[type].mpTexBuffer = buffer;
        }

        static void clearBuffer(BufferType type)
        {
            #line 174
            EGG_ASSERT(type < cBufferType_Max);
            spBufferSet[type].mpTexBuffer = NULL;
            spBufferSet[type].mpAllocBase = NULL;
            spBufferSet[type].WORD_0x8 = 0;
        }

        static TextureBuffer* getBuffer(BufferType type)
        {
            return spBufferSet[type].mpTexBuffer;
        }

        ScreenEffectBase();
        virtual ~ScreenEffectBase() {} // at 0x8

        Screen& GetScreen() { return mScreen; }
        const Screen& GetScreen() const { return mScreen; }

        bool isVisible() const { return mFlags & EFFECT_VISIBLE; }
        bool isFlag0x2() const { return mFlags & EFFECT_0x2; }

        void copyFromAnother(const Screen&);
        TextureBuffer* capture(BufferType, bool) const;
        bool release(BufferType) const;
        void doCapture(int) const;
        void setupGX(bool) const;
        const WorkView& setupView() const;

    private:
        static EffectBuffer spBufferSet[cBufferType_Max];

        static WorkView sWorkSpaceV;
        static WorkView sWorkSpaceHideV;

        static u32 sCaptureFlag;
    public:
        // Public for now, until flag test functions are determined
        static u32 sFlag;
    private:
        static u32 D_804BEC58;
        static u32 sPushCount;
        static s32 sWorkBuffer;
    };
}

#endif