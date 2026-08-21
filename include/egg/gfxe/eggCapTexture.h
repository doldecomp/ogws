#ifndef EGG_GFXE_CAP_TEXTURE_H
#define EGG_GFXE_CAP_TEXTURE_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggCpuTexture.h>

#include <revolution/GX.h>

namespace EGG {

class CapTexture : public CpuTexture {
public:
    CapTexture() {}
    CapTexture(u16 width, u16 height, GXTexFmt format)
        : CpuTexture(width, height, format) {}

    virtual void configure();          // at 0xC
    virtual void load(GXTexMapID map); // at 0x14

    void capture(u16 x, u16 y, bool mipmap = false, int format = -1);

    GXTexMapID getLoadMap() const {
        return mLoadMap;
    }

    void setClearColor(const GXColor& rColor) {
        mClearColor = rColor;
    }
    void setClearZ(u32 clearZ) {
        mClearZ = clearZ;
    }

    void setVFilter(const u8* const pFilter) {
        enableVFilter();
        setVFilterInternal(pFilter);
    }
    void setVFilterBlur() {
        enableVFilter();
        setVFilterInternal(VFILTER_BLUR);
    }
    void setVFilterOff() {
        setVFilterInternal(VFILTER_OFF);
    }

    bool checkColorUpdate() const {
        return testFlag(cFlag_ColorUpdate);
    }
    void enableColorUpdate() {
        setFlag(cFlag_ColorUpdate);
    }
    void disableColorUpdate() {
        clearFlag(cFlag_ColorUpdate);
    }

    bool checkAlphaUpdate() const {
        return testFlag(cFlag_AlphaUpdate);
    }
    void enableAlphaUpdate() {
        setFlag(cFlag_AlphaUpdate);
    }
    void disableAlphaUpdate() {
        clearFlag(cFlag_AlphaUpdate);
    }

    bool checkZBufferUpdate() const {
        return testFlag(cFlag_ZBufferUpdate);
    }
    void enableZBufferUpdate() {
        setFlag(cFlag_ZBufferUpdate);
    }
    void disableZBufferUpdate() {
        clearFlag(cFlag_ZBufferUpdate);
    }

    bool checkVFilterEnable() const {
        return testFlag(cFlag_VFilterEnable);
    }
    void enableVFilter() {
        setFlag(cFlag_VFilterEnable);
    }
    void disableVFilter() {
        clearFlag(cFlag_VFilterEnable);
    }

    bool checkPixModeSync() const {
        return testFlag(cFlag_PixModeSync);
    }
    void enablePixModeSync() {
        setFlag(cFlag_PixModeSync);
    }
    void disablePixModeSync() {
        clearFlag(cFlag_PixModeSync);
    }

private:
    enum {
        cFlag_ColorUpdate = 1 << 3,
        cFlag_AlphaUpdate = 1 << 4,
        cFlag_ZBufferUpdate = 1 << 5,
        cFlag_VFilterEnable = 1 << 6,
        cFlag_PixModeSync = 1 << 7,
    };

private:
    void setVFilterInternal(const u8* const pFilter) {
        for (int i = 0; i < GX_VFILTER_SZ; i++) {
            mVerticalFilter[i] = pFilter[i];
        }
    }

private:
    GXTexMapID mLoadMap;               // at 0x18
    GXColor mClearColor;               // at 0x1C
    u32 mClearZ;                       // at 0x20
    u8 mVerticalFilter[GX_VFILTER_SZ]; // at 0x24

    static const u8 SAMPLE_PATTERN_OFF[12][2];
    static const u8 VFILTER_BLUR[GX_VFILTER_SZ];
    static const u8 VFILTER_OFF[GX_VFILTER_SZ];
};

} // namespace EGG

#endif
