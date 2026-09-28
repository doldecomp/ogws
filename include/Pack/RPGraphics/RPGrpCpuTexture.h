#ifndef RP_GRAPHICS_CPU_TEXTURE_H
#define RP_GRAPHICS_CPU_TEXTURE_H

#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpResTIMG.h>

#include <revolution/GX.h>

//! TODO(texline) Confirm this

/**
 * @note Superseded by EGG::CpuTexture in rev 1.
 */
class RPGrpCpuTexture {
private:
    u16 mFlags;    // at 0x0
    u16 mWidth;    // at 0x2
    u16 mHeight;   // at 0x4
    u8 mFormat;    // at 0x6
    u8 mWrapS;     // at 0x7
    u8 mWrapT;     // at 0x8
    u8 mMinFilter; // at 0x9
    u8 mMagFilter; // at 0xA
    char UNK_0xB[0x10 - 0xB];
    void* mpBuffer; // at 0x10

public:
    enum EGradationKind {
        GRADATION_LINEAR,            // y=x
        GRADATION_QUADRATIC,         // y=x^2
        GRADATION_CUBIC,             // y=x^3
        GRADATION_QUARTIC,           // y=x^4
        GRADATION_QUINTIC,           // y=x^5
        GRADATION_QUADRATIC_EASEOUT, // y=1-(1-x)^2
        GRADATION_QUARTIC_EASEOUT,   // y=1-(1-x)^4
    };

public:
    //! @bug Texture buffer is leaked
    virtual ~RPGrpCpuTexture() {}                 // at 0x8
    virtual void configure();                     // at 0xC
    virtual void getTexObj(GXTexObj* pObj) const; // at 0x10
    virtual void load(GXTexMapID map);            // at 0x14

    RPGrpCpuTexture();
    RPGrpCpuTexture(u16 width, u16 height, GXTexFmt format);

    void alloc();
    void allocWithHeaderDebug();

    RPGrpResTIMG* getResTIMG() const;
    u32 getTexBufferSize() const;

    void fillNormalMapSphere();
    void fillGradationTable(EGradationKind kind, int dir, u16 tableStart,
                            u16 tableGoal, const GXColor& c1, const GXColor& c2,
                            bool wrap, bool setAll);

    void setColor(u16 x, u16 y, GXColor color);

    void invalidate() const;
    void flush() const;

    bool checkIsConfigure() const {
        return testFlag(cFlag_Configured);
    }
    bool checkHasHeader() const {
        return testFlag(cFlag_HasHeader);
    }

    void setFlag(u8 flag) {
        mFlags |= flag;
    }
    void clearFlag(u8 flag) {
        mFlags &= ~flag;
    }
    bool testFlag(u8 flag) const {
        return (mFlags & flag) ? true : false;
    }

    u16 getWidth() const {
        return mWidth;
    }
    void setWidth(u16 w) {
        mWidth = w;
    }

    u16 getHeight() const {
        return mHeight;
    }
    void setHeight(u16 h) {
        mHeight = h;
    }

    GXTexFmt getFormat() const {
        return static_cast<GXTexFmt>(mFormat);
    }
    void setFormat(GXTexFmt format) {
        mFormat = format;
    }

    GXTexWrapMode getWrapS() const {
        return static_cast<GXTexWrapMode>(mWrapS);
    }
    void setWrapS(u8 wrap) {
        mWrapS = wrap;
    }

    GXTexWrapMode getWrapT() const {
        return static_cast<GXTexWrapMode>(mWrapT);
    }
    void setWrapT(u8 wrap) {
        mWrapT = wrap;
    }

    GXTexFilter getMinFilter() const {
        return static_cast<GXTexFilter>(mMinFilter);
    }
    void setMinFilter(u8 filter) {
        mMinFilter = filter;
    }

    GXTexFilter getMagFilter() const {
        return static_cast<GXTexFilter>(mMagFilter);
    }
    void setMagFilter(u8 filter) {
        mMagFilter = filter;
    }

    void* getBuffer() const {
        return mpBuffer;
    }
    void setBuffer(void* pBuffer) {
        mpBuffer = pBuffer;
        clearFlag(cFlag_HasHeader);
    }

private:
    enum {
        cFlag_Configured = 1 << 0,
        cFlag_HasHeader = 1 << 1,
    };

private:
    void initResTIMG() const;

    RPGrpResTIMG* getHeader() const {
        // clang-format off
        return reinterpret_cast<RPGrpResTIMG*>(
            reinterpret_cast<u8*>(mpBuffer) - sizeof(RPGrpResTIMG));
        // clang-format on
    }
};

#endif
