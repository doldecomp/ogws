#ifndef EGG_GFX_TEXTURE_BUFFER_H
#define EGG_GFX_TEXTURE_BUFFER_H
#include "types_egg.h"
#include "eggCapTexture.h"
#include <GX/GXTexture.h>

namespace EGG
{
    class TextureBuffer : public CapTexture
    {
    public:
        enum EBufferState
        {
            STATE_FREE,
            STATE_ALLOCED
        };

        static void initialize(u32, Heap *);
        static TextureBuffer * getNotJoin();
        static void alloc(TextureBuffer *, u32);

        // Unofficial
        static void append(TextureBuffer *buf)
        {
            if (spTail != NULL) spTail->mpNext = buf;

            buf->mpPrev = spTail;
            buf->mpNext = NULL;

            spTail = buf;
        }

        virtual ~TextureBuffer() {} // at 0x8
        virtual void configure(); // at 0xC

        TextureBuffer();
        void free();

    private:
        u32 mSize; // at 0x2C
        EBufferState mState; // at 0x30
        TextureBuffer *mpNext; // at 0x34
        TextureBuffer *mpPrev; // at 0x38

        static const u32 cMaxBuffers = 64;
        static TextureBuffer *spHead;
        static TextureBuffer *spTail;
        static TextureBuffer *spBufferAll;
        static u32 sBufferSize;
        static TextureBuffer sBuffers[cMaxBuffers];
    };
}

#endif