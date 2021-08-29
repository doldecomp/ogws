#ifndef EGG_GFX_TEXTURE_BUFFER_H
#define EGG_GFX_TEXTURE_BUFFER_H
#include "types_egg.h"
#include "eggCapTexture.h"
#include <GX/GXTexture.h>

namespace EGG
{
    class TextureBuffer
    {
    public:
        // Unofficial name
        class BufferNode : public CapTexture
        {
        public:
            enum ENodeState
            {
                STATE_FREED,
                STATE_ALLOCED
            };

            BufferNode();
            // Unofficial
            void free();

            virtual ~BufferNode() {} // at 0x8
            virtual void configure(); // at 0xC

            UNKWORD mSize; // at 0x2C
            ENodeState mState; // at 0x30
            BufferNode *mpNext; // at 0x34
            BufferNode *mpPrev; // at 0x38

        private:
            static GXColor sDefaultColor;
        };

        static void initialize(u32, Heap *);
        static BufferNode * getNotJoin();
        static void alloc(BufferNode *, u32);

        // Unofficial
        static void append(BufferNode *node)
        {
            if (spTail != NULL) spTail->mpNext = node;

            node->mpPrev = spTail;
            node->mpNext = NULL;

            spTail = node;
        }

    private:
        static const u32 cMaxNodes = 64;
        static BufferNode *spHead;
        static BufferNode *spTail;
        static BufferNode *spBufferAll;
        static u32 sBufferSize;
        static BufferNode sBufferNodes[cMaxNodes];
    };
}

#endif