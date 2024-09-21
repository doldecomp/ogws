#include "eggCpuTexture.h"
#include "eggHeap.h"
#include <OS/OSCache.h>

namespace EGG
{
    void CpuTexture::makeGradient()
    {

    }

    CpuTexture::CpuTexture() : mWidth(0), mHeight(0), mTexFormat(GX_TF_RGBA8),
        mWrapS(0), mWrapT(0), mMinFilt(1), mMagFilt(1), mpBuffer(NULL) {}

    CpuTexture::CpuTexture(u16 width, u16 height, GXTexFmt format) : mWidth(width), mHeight(height), mTexFormat(format),
        mWrapS(0), mWrapT(0), mMinFilt(1), mMagFilt(1), mpBuffer(NULL) {}

    void CpuTexture::configure()
    {
        mFlags = CONFIGURED;
    }

    void CpuTexture::getTexObj(GXTexObj *pObj) const
    {
        #line 230
        EGG_ASSERT_MSG(checkIsConfigure(), "Please call configure() after construct!");
        EGG_ASSERT(pObj);
        EGG_ASSERT(mpBuffer);

        GXInitTexObj(pObj, mpBuffer, mWidth, mHeight,
            static_cast<GXTexFmt>(mTexFormat), static_cast<GXTexWrapMode>(mWrapS),
            static_cast<GXTexWrapMode>(mWrapT), FALSE);
        GXInitTexObjLOD(pObj, static_cast<GXTexFilter>(mMinFilt),
            static_cast<GXTexFilter>(mMagFilt), 0.0f, 0.0f, 0.0f, FALSE, FALSE, GX_ANISO_1);
    }

    void CpuTexture::load(GXTexMapID id) const
    {
        #line 247
        EGG_ASSERT(mpBuffer);

        GXTexObj obj;
        getTexObj(&obj);

        GXLoadTexObj(&obj, id);
    }
    
    void CpuTexture::checkTexBuffer() const
    {
        #line 259
        EGG_ASSERT(mpBuffer);
    }

    void CpuTexture::invalidate() const
    {
        checkTexBuffer();
        DCInvalidateRange(mpBuffer, getTexBufferSize());
    }

    void CpuTexture::flush() const
    {
        checkTexBuffer();
        DCFlushRange(mpBuffer, getTexBufferSize());
    }

    u32 CpuTexture::getTexBufferSize() const
    {
        return GXGetTexBufferSize(mWidth, mHeight, getFormat(), 0, 1);
    }

    void CpuTexture::buildHeader() const
    {
        #line 294
        EGG_ASSERT_MSG(checkIsConfigure(), "Please call configure() after construct!");
        EGG_ASSERT(checkHasHeader());

        CpuTexture::Header *pHdr = getHeader();

        pHdr->mTexFormat = mTexFormat;
        pHdr->BYTE_0x1 = 0;
        pHdr->mWidth = mWidth;
        pHdr->mHeight = mHeight;
        pHdr->mWrapS = mWrapS;
        pHdr->mWrapT = mWrapT;
        pHdr->BYTE_0x8 = 0;
        pHdr->SHORT_0x9 = 0;
        pHdr->WORD_0xC = 0;
        pHdr->BYTE_0xD = 0;
        pHdr->BYTE_0xE = 0;
        pHdr->BYTE_0xF = 0;
        pHdr->BYTE_0x10 = 0;
        pHdr->mMinFilt = mMinFilt;
        pHdr->mMagFilt = mMagFilt;
        pHdr->BYTE_0x13 = 0;
        pHdr->BYTE_0x14 = 0;
        pHdr->BYTE_0x15 = 1;
        pHdr->SHORT_0x16 = 0;
        pHdr->WORD_0x18 = 32;
    }

    CpuTexture::Header * CpuTexture::initHeader()
    {
        buildHeader();
        return getHeader();
    }

    // Non-matching
    void CpuTexture::fillNormalMapSphere()
    {
    }

    // Non-matching
    UNKTYPE CpuTexture::func_80086C8C(UNKTYPE)
    {
    }

    void CpuTexture::allocTexBuffer()
    {
        #line 469
        EGG_ASSERT(getTexBufferSize() > 0);

        u8 *pBuffer = new (32) u8[getTexBufferSize()];
        #line 472
        EGG_ASSERT(pBuffer);
        
        setBuffer(pBuffer);
    }

    void CpuTexture::allocTexBufferAndHeader()
    {
        #line 480
        EGG_ASSERT(getTexBufferSize() > 0);

        u8 *pBuffer = new (32) u8[getTexBufferSize() + sizeof(CpuTexture::Header)];
        #line 482
        EGG_ASSERT(pBuffer);

        setBuffer(pBuffer + sizeof(CpuTexture::Header));
        mFlags |= HAS_HEADER;
        initHeader();
    }

    void CpuTexture::setColor(u16 x, u16 y, GXColor c)
    {
        #line 497
        EGG_ASSERT(x < getWidth());
        EGG_ASSERT(y < getHeight());
        EGG_ASSERT(getBuffer());

        // TO-DO
        switch(getFormat())
        {
            case GX_TF_RGBA8:
                break;

            case GX_TF_I8:
                break;
        }
    }
}
