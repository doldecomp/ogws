#include <egg/core.h>
#include <egg/gfxe.h>
#include <egg/prim.h>

namespace EGG {

TextureBuffer* TextureBuffer::spHead = NULL;
TextureBuffer* TextureBuffer::spTailNotJoin = NULL;

TextureBuffer* TextureBuffer::spBufferAll = NULL;
u32 TextureBuffer::sBufferAllSize = 0;

TextureBuffer TextureBuffer::spBufferTable[BUFFER_MAX];

TextureBuffer::TextureBuffer()
    : mSize(0), mState(STATE_FREE), mpNext(NULL), mpPrev(NULL) {}

void TextureBuffer::configure() {
    CapTexture::configure();
    setClearColor(StateGX::getEfbClearColor());
}

void TextureBuffer::free() {
#line 46
    EGG_ASSERT(mState == STATE_ALLOCED);

    mState = STATE_FREE;

    // Check if previous buffer is reclaimable
    if (mpPrev != NULL && mpPrev->mState == STATE_FREE) {
        // Merge with previous buffer
        mSize += mpPrev->mSize;
        setBuffer(static_cast<u8*>(getBuffer()) - mpPrev->mSize);

        // Append reusable buffer
        TextureBuffer* pBefore = mpPrev->mpPrev;
        append(mpPrev);

        // Repair mpPrev link
        mpPrev = pBefore;
        if (pBefore != NULL) {
            pBefore->mpNext = this;
        } else {
            spHead = this;
        }
    }

    // Check if next buffer is reclaimable
    if (mpNext != NULL && mpNext->mState == STATE_FREE) {
        // Merge with next buffer
        mSize += mpNext->mSize;

        // Append reusable buffer
        TextureBuffer* pAfter = mpNext->mpNext;
        append(mpNext);

        // Repair mpNext link
        mpNext = pAfter;
        if (pAfter != NULL) {
            pAfter->mpPrev = this;
        }
    }
}

void TextureBuffer::initialize(u32 size, Heap* pHeap) {
#line 89
    EGG_ASSERT(spBufferAll == NULL);
    EGG_ASSERT(size % 32 == 0);

    if (pHeap == NULL) {
        pHeap = Heap::getCurrentHeap();
    }

    sBufferAllSize = size;
    spBufferAll = reinterpret_cast<TextureBuffer*>(new (pHeap, 32) u8[size]);
#line 100
    EGG_ASSERT(spBufferAll);

    spTailNotJoin = NULL;
    for (int i = 0; i < BUFFER_MAX; i++) {
        append(&spBufferTable[i]);
    }

    // Initialize head
    spHead = getNotJoin();
    spHead->mState = STATE_FREE;
    spHead->mSize = size;
    spHead->setBuffer(spBufferAll);
}

TextureBuffer* TextureBuffer::getNotJoin() {
#line 122
    EGG_ASSERT_MSG(spBufferAll != NULL, "Please call TextureBuffer::initialize().");

    TextureBuffer* p_buffer = spTailNotJoin;
#line 125
    EGG_ASSERT(p_buffer);
    EGG_ASSERT(p_buffer->mpNext == NULL);

    // Move list tail back
    spTailNotJoin = spTailNotJoin->mpPrev;
    if (spTailNotJoin != NULL) {
        spTailNotJoin->mpNext = NULL;
    }

    // Pop old tail
    p_buffer->mpPrev = NULL;
    return p_buffer;
}

void TextureBuffer::alloc(u32 size) {
#line 148
    EGG_ASSERT(size > 0);

    size += (32 - (size % 32));
#line 156
    EGG_ASSERT(size % 32 == 0);

    // Try to find a free buffer with at least the requested size
    for (TextureBuffer* p_list = spHead; p_list != NULL;
         p_list = p_list->mpNext) {

        if (p_list->mState != STATE_FREE) {
            continue;
        }

        if (p_list->mSize < size) {
            continue;
        }

        // Assign free buffer data to new buffer
        mSize = size;
        mState = STATE_ALLOCED;
        setBuffer(p_list->getBuffer());

        // Prepend new buffer before old buffer
        mpNext = p_list;
        TextureBuffer* pOldPrev = p_list->mpPrev;
        mpPrev = pOldPrev;

        // Fix this->prev link
        if (pOldPrev != NULL) {
            pOldPrev->mpNext = this;
        }
        // NULL prev buffer must be list head
        else {
#line 181
            EGG_ASSERT(p_list == spHead);
            spHead = this;
        }

        // Remove requested size from old buffer
        p_list->mSize -= size;

        // Free old buffer if now empty
        if (p_list->mSize == 0) {
            if (p_list->mpNext != NULL) {
                p_list->mpNext->mpPrev = this;
            }

            mpNext = p_list->mpNext;
            append(p_list);
        }
        // Adjust old buffer by requested size
        else {
            p_list->setBuffer(static_cast<u8*>(p_list->getBuffer()) + size);
            p_list->mpPrev = this;
        }

        return;
    }

#line 206
    EGG_ASSERT_MSG(false, "No free area.");
}

} // namespace EGG
