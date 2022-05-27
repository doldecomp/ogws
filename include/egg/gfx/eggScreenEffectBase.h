#ifndef EGG_GFX_SCREEN_EFFECT_BASE_H
#define EGG_GFX_SCREEN_EFFECT_BASE_H
#include "types_egg.h"
#include "eggAssert.h"
#include "eggScreen.h"
#include "eggTextureBuffer.h"

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
            TextureBuffer * mpTexBuffer; // at 0x0
            ScreenEffectBase * mpAllocBase; // at 0x4
            UNKWORD WORD_0x8; // at 0x8
        };

    private:
        u8 mFlags; // at 0x0
        Screen mScreen; // at 0x4

        static EffectBuffer spBufferSet[cBufferType_Max];

    public:
        ScreenEffectBase();
        virtual ~ScreenEffectBase() {} // at 0x8

        Screen& GetScreen() { return mScreen; }
        const Screen& GetScreen() const { return mScreen; }

        bool isVisible() const { return mFlags & EFFECT_VISIBLE; }
        bool isFlag0x2() const { return mFlags & EFFECT_0x2; }

        static void clearEffectBuffer(BufferType type)
        {
            #line 174
            EGG_ASSERT(type < cBufferType_Max);
            spBufferSet[type].mpTexBuffer = NULL;
            spBufferSet[type].mpAllocBase = NULL;
            spBufferSet[type].WORD_0x8 = 0;
        }

        TextureBuffer * getBuffer(BufferType type) const
        {
            return spBufferSet[type].mpTexBuffer;
        }

        void CopyScreenFromAnother(Screen&);
       
        static void initialize();
        void g_capture_for_efb(BufferType, bool);
        bool freeEffectBuffer(BufferType);

        // TO-DO
        static u32 lbl_804BEC54;
    };
}

#endif