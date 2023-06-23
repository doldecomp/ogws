#ifndef EGG_GFX_TEXTURE_BUFFER_H
#define EGG_GFX_TEXTURE_BUFFER_H
#include "types_egg.h"
#include "eggCapTexture.h"
#include <revolution/GX.h>

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

        static TextureBuffer * alloc(u16 w, u16 h, GXTexFmt fmt)
        {
            if (w == 0 || h == 0) return NULL;

            TextureBuffer *buf = getNotJoin();
            buf->setWidth(w);
            buf->setHeight(h);
            buf->setFormat(fmt);
            buf->configure();

            buf->setWrapS(0);
            buf->setWrapT(0);
            buf->setMinFilt(1);
            buf->setMagFilt(1);

            buf->alloc(buf->getTexBufferSize());
            return buf;
        }

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

        void alloc(u32);
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