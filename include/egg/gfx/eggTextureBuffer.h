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

        static void append(TextureBuffer *buf)
        {
            if (spTailNotJoin != NULL) spTailNotJoin->mpNext = buf;

            buf->mpPrev = spTailNotJoin;
            buf->mpNext = NULL;

            spTailNotJoin = buf;
        }

        TextureBuffer();
        virtual ~TextureBuffer() {} // at 0x8
        virtual void configure(); // at 0xC

        void free();

    private:
        u32 mSize; // at 0x2C
        EBufferState mState; // at 0x30
        TextureBuffer *mpNext; // at 0x34
        TextureBuffer *mpPrev; // at 0x38

        static const u32 NUM_BUFFERS = 64;
        static TextureBuffer *spHead;
        static TextureBuffer *spTailNotJoin;
        static TextureBuffer *spBufferAll;
        static u32 sBufferAllSize;
        static TextureBuffer spBufferTable[NUM_BUFFERS];
    };
}

#endif