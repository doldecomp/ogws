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
            EFFECT_VISIBLE = 0x1
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
            TextureBuffer *mpTexBuffer; // at 0x0
            ScreenEffectBase * mpAllocBase; // at 0x4
            UNKWORD WORD_0x8; // at 0x8
        };

    private:
        u8 mFlags;
        eggScreen mScreen;

        static EffectBuffer spBufferSet[cBufferType_Max];

    public:
        ScreenEffectBase();
        virtual ~ScreenEffectBase() {} // at 0x8

        bool isVisible() const { return mFlags & EFFECT_VISIBLE; }

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

        void CopyScreenFromAnother(eggScreen&);
       
        static void initialize();
        bool freeEffectBuffer(BufferType);
    };
}

#endif