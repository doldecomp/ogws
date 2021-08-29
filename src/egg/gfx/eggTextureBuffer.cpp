#include "eggTextureBuffer.h"
#include "eggAssert.h"
#include "eggHeap.h"
#include "eggStateGX.h"

namespace EGG
{
    TextureBuffer::BufferNode::BufferNode() :
        mSize(0), mState(STATE_FREED), mpNext(NULL), mpPrev(NULL) {}

    void TextureBuffer::BufferNode::configure()
    {
        CapTexture::configure();
        setColor(StateGX::sDefaultTexColor);
    }

    void TextureBuffer::BufferNode::free()
    {
        #line 46
        EGG_ASSERT(mState == STATE_ALLOCED);

        mState = STATE_FREED;

        if (mpPrev != NULL && mpPrev->mState == STATE_FREED)
        {
            mSize += mpPrev->mSize;
            setBuffer((u8 *)getBuffer() - mpPrev->mSize);

            BufferNode *beforeAppend = mpPrev->mpPrev;

            append(mpPrev);

            mpPrev = beforeAppend;
            if (beforeAppend != NULL)
            {
                beforeAppend->mpNext = this;
            }
            else
            {
                spHead = this;
            }
        }
        
        if (mpNext != NULL && mpNext->mState == STATE_FREED)
        {
            mSize += mpNext->mSize;

            BufferNode *afterAppend = mpNext->mpNext;
            
            append(mpNext);

            mpNext = afterAppend;
            if (afterAppend != NULL)
            {
                afterAppend->mpPrev = this;
            }
        }
    }

    void TextureBuffer::initialize(u32 size, Heap *heap)
    {
        #line 89
        EGG_ASSERT(spBufferAll == NULL);
        EGG_ASSERT(size % 32 == 0);

        if (heap == NULL) heap = Heap::sCurrentHeap;

        sBufferSize = size;
        spBufferAll = (BufferNode *)new (heap, 32) char[size];
        #line 100
        EGG_ASSERT(spBufferAll);

        spTail = NULL;

        for (u32 i = 0; i < cMaxNodes; i++)
        {
            append(&sBufferNodes[i]);
        }

        spHead = getNotJoin();
        spHead->mState = BufferNode::STATE_FREED;
        spHead->mSize = size;
        spHead->setBuffer(spBufferAll);
    }

    TextureBuffer::BufferNode * TextureBuffer::getNotJoin()
    {
        #line 122
        EGG_ASSERT_MSG(spBufferAll != NULL, "Please call TextureBuffer::initialize().");

        BufferNode *p_buffer = spTail;
        #line 125
        EGG_ASSERT(p_buffer);
        EGG_ASSERT(p_buffer->mpNext == NULL);

        spTail = spTail->mpPrev;
        if (spTail != NULL) spTail->mpNext = NULL;

        p_buffer->mpPrev = NULL;

        return p_buffer;
    }

    void TextureBuffer::alloc(BufferNode *n, u32 size)
    {
        #line 148
        EGG_ASSERT(size > 0);

        size += (32 - (size % 32));
        #line 156
        EGG_ASSERT(size % 32 == 0);

        for (BufferNode *p_list = spHead; p_list != NULL; p_list = p_list->mpNext)
        {
            if (p_list->mState == BufferNode::STATE_FREED && p_list->mSize >= size)
            {
                n->mSize = size;
                n->mState = BufferNode::STATE_ALLOCED;
                n->setBuffer(p_list->getBuffer());

                n->mpNext = p_list;
                BufferNode *p = p_list->mpPrev;
                n->mpPrev = p;
                if (p != NULL)
                {
                    p->mpNext = n;
                }
                else
                {
                    #line 181
                    EGG_ASSERT(p_list == spHead);

                    spHead = n;
                }

                p_list->mSize -= size;
                if (p_list->mSize == 0)
                {
                    if (p_list->mpNext != NULL) p_list->mpNext->mpPrev = n;
                    n->mpNext = p_list->mpNext;
                    append(p_list);

                    return;
                }

                p_list->setBuffer((u8 *)p_list->getBuffer() + size);
                p_list->mpPrev = n;

                return;
            }
        }

        #line 206
        EGG_ASSERT_MSG(false, "No free area.");
    }

    TextureBuffer::BufferNode *TextureBuffer::spHead;
    TextureBuffer::BufferNode *TextureBuffer::spTail;
    TextureBuffer::BufferNode *TextureBuffer::spBufferAll;

    u32 TextureBuffer::sBufferSize;

    TextureBuffer::BufferNode TextureBuffer::sBufferNodes[cMaxNodes];
}