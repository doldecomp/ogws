#ifndef EGG_GFXE_TEXTURE_BUFFER_H
#define EGG_GFXE_TEXTURE_BUFFER_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggCapTexture.h>

#include <revolution/GX.h>

namespace EGG {

class TextureBuffer : public CapTexture {
public:
    static void initialize(u32 size, Heap* pHeap);

    TextureBuffer();
    virtual void configure(); // at 0xC

    void alloc(u32 size);
    void free();

    static TextureBuffer* alloc(u16 width, u16 height, GXTexFmt format) {
        if (width == 0 || height == 0) {
            return NULL;
        }

        TextureBuffer* pBuffer = getNotJoin();
        pBuffer->setWidth(width);
        pBuffer->setHeight(height);
        pBuffer->setFormat(format);
        pBuffer->configure();

        pBuffer->setWrapS(GX_CLAMP);
        pBuffer->setWrapT(GX_CLAMP);
        pBuffer->setMinFilter(GX_LINEAR);
        pBuffer->setMagFilter(GX_LINEAR);

        pBuffer->alloc(pBuffer->getTexBufferSize());
        return pBuffer;
    }

private:
    enum BufferState {
        STATE_FREE,
        STATE_ALLOCED,
    };

    static const u32 BUFFER_MAX = 64;

private:
    static TextureBuffer* getNotJoin();

    static void append(TextureBuffer* pBuffer) {
        if (spTailNotJoin != NULL) {
            spTailNotJoin->mpNext = pBuffer;
        }

        pBuffer->mpPrev = spTailNotJoin;
        pBuffer->mpNext = NULL;

        spTailNotJoin = pBuffer;
    }

private:
    u32 mSize;             // at 0x2C
    BufferState mState;    // at 0x30
    TextureBuffer* mpNext; // at 0x34
    TextureBuffer* mpPrev; // at 0x38

    static TextureBuffer* spHead;
    static TextureBuffer* spTailNotJoin;

    static TextureBuffer* spBufferAll;
    static u32 sBufferAllSize;

    static TextureBuffer spBufferTable[BUFFER_MAX];
};

} // namespace EGG

#endif
