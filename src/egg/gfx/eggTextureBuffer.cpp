#include "eggTextureBuffer.h"
#include "eggAssert.h"
#include "eggHeap.h"
#include "eggStateGX.h"

namespace EGG
{
    TextureBuffer::TextureBuffer() :
        mSize(0), mState(STATE_FREE), mpNext(NULL), mpPrev(NULL) {}

    void TextureBuffer::configure()
    {
        CapTexture::configure();
        setClearColor(StateGX::getDefaultTexColor());
    }

    // Allow buffer to be reclaimed
    void TextureBuffer::free()
    {
        #line 46
        EGG_ASSERT(mState == STATE_ALLOCED);

        mState = STATE_FREE;

        // Check if previous buffer is reclaimable
        if (mpPrev != NULL && mpPrev->mState == STATE_FREE)
        {
            // Merge with previous buffer
            mSize += mpPrev->mSize;
            setBuffer((u8 *)getBuffer() - mpPrev->mSize);

            // Append reusable buffer
            TextureBuffer *beforeAppend = mpPrev->mpPrev;
            append(mpPrev);

            // Repair mpPrev link
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
        
        // Check if next buffer is reclaimable
        if (mpNext != NULL && mpNext->mState == STATE_FREE)
        {
            // Merge with next buffer
            mSize += mpNext->mSize;

            // Append reusable buffer
            TextureBuffer *afterAppend = mpNext->mpNext;
            append(mpNext);

            // Repair mpNext link
            mpNext = afterAppend;
            if (afterAppend != NULL)
            {
                afterAppend->mpPrev = this;
            }
        }
    }

    // Alloc list buffer
    void TextureBuffer::initialize(u32 size, Heap *heap)
    {
        #line 89
        EGG_ASSERT(spBufferAll == NULL);
        EGG_ASSERT(size % 32 == 0);

        if (heap == NULL) heap = Heap::getCurrentHeap();

        sBufferAllSize = size;
        spBufferAll = (TextureBuffer *)new (heap, 32) char[size];
        #line 100
        EGG_ASSERT(spBufferAll);

        spTailNotJoin = NULL;
        for (u32 i = 0; i < NUM_BUFFERS; i++)
        {
            append(&spBufferTable[i]);
        }

        // Initialize head
        spHead = getNotJoin();
        spHead->mState = STATE_FREE;
        spHead->mSize = size;
        spHead->setBuffer(spBufferAll);
    }

    // Remove and return buffer at list end
    TextureBuffer * TextureBuffer::getNotJoin()
    {
        #line 122
        EGG_ASSERT_MSG(spBufferAll != NULL, "Please call TextureBuffer::initialize().");

        TextureBuffer *p_buffer = spTailNotJoin;
        #line 125
        EGG_ASSERT(p_buffer);
        EGG_ASSERT(p_buffer->mpNext == NULL);

        // Move list tail back
        spTailNotJoin = spTailNotJoin->mpPrev;
        if (spTailNotJoin != NULL) spTailNotJoin->mpNext = NULL;

        // Pop old tail
        p_buffer->mpPrev = NULL;
        return p_buffer;
    }

    // Attempt to alloc buffer of specified size
    void TextureBuffer::alloc(u32 size)
    {
        #line 148
        EGG_ASSERT(size > 0);

        size += (32 - (size % 32));
        #line 156
        EGG_ASSERT(size % 32 == 0);

        // Try to find a free buffer with at least the requested size
        for (TextureBuffer *p_list = spHead; p_list != NULL; p_list = p_list->mpNext)
        {
            if (p_list->mState == STATE_FREE && p_list->mSize >= size)
            {
                // Assign free buffer data to new buffer
                mSize = size;
                mState = STATE_ALLOCED;
                setBuffer(p_list->getBuffer());

                // Prepend new buffer before old buffer
                mpNext = p_list;
                TextureBuffer *oldPrev = p_list->mpPrev;
                mpPrev = oldPrev;

                // Fix this->prev link
                if (oldPrev != NULL)
                {
                    oldPrev->mpNext = this;
                }
                else
                {
                    // NULL prev buffer must be list head
                    #line 181
                    EGG_ASSERT(p_list == spHead);

                    spHead = this;
                }

                // Remove requested size from old buffer
                p_list->mSize -= size;

                // Free old buffer if now empty
                if (p_list->mSize == 0)
                {
                    if (p_list->mpNext != NULL) p_list->mpNext->mpPrev = this;
                    mpNext = p_list->mpNext;
                    append(p_list);
                }
                // Adjust old buffer by requested size
                else
                {
                    p_list->setBuffer((u8 *)p_list->getBuffer() + size);
                    p_list->mpPrev = this;
                }

                return;
            }
        }

        #line 206
        EGG_ASSERT_MSG(false, "No free area.");
    }

    TextureBuffer *TextureBuffer::spHead;
    TextureBuffer *TextureBuffer::spTailNotJoin;
    TextureBuffer *TextureBuffer::spBufferAll;
    u32 TextureBuffer::sBufferAllSize;
    TextureBuffer TextureBuffer::spBufferTable[NUM_BUFFERS];
}