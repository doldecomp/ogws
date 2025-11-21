#ifndef EGG_GFXE_CAP_TEXTURE_H
#define EGG_GFXE_CAP_TEXTURE_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggCpuTexture.h>

#include <revolution/GX.h>

namespace EGG {

class CapTexture : public CpuTexture {
public:
    CapTexture() {}
    CapTexture(u16 w, u16 h, GXTexFmt fmt) : CpuTexture(w, h, fmt) {}

    virtual ~CapTexture() {}           // at 0x8
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
        return testFlag(FLAG_COLOR_UPDATE);
    }
    void enableColorUpdate() {
        setFlag(FLAG_COLOR_UPDATE);
    }
    void disableColorUpdate() {
        clearFlag(FLAG_COLOR_UPDATE);
    }

    bool checkAlphaUpdate() const {
        return testFlag(FLAG_ALPHA_UPDATE);
    }
    void enableAlphaUpdate() {
        setFlag(FLAG_ALPHA_UPDATE);
    }
    void disableAlphaUpdate() {
        clearFlag(FLAG_ALPHA_UPDATE);
    }

    bool checkZBufferUpdate() const {
        return testFlag(FLAG_ZBUFFER_UPDATE);
    }
    void enableZBufferUpdate() {
        setFlag(FLAG_ZBUFFER_UPDATE);
    }
    void disableZBufferUpdate() {
        clearFlag(FLAG_ZBUFFER_UPDATE);
    }

    bool checkVFilterEnable() const {
        return testFlag(FLAG_VFILTER_ENABLE);
    }
    void enableVFilter() {
        setFlag(FLAG_VFILTER_ENABLE);
    }
    void disableVFilter() {
        clearFlag(FLAG_VFILTER_ENABLE);
    }

    bool checkPixModeSync() const {
        return testFlag(FLAG_PIXMODE_SYNC);
    }
    void enablePixModeSync() {
        setFlag(FLAG_PIXMODE_SYNC);
    }
    void disablePixModeSync() {
        clearFlag(FLAG_PIXMODE_SYNC);
    }

private:
    enum {
        FLAG_COLOR_UPDATE = 1 << 3,
        FLAG_ALPHA_UPDATE = 1 << 4,
        FLAG_ZBUFFER_UPDATE = 1 << 5,
        FLAG_VFILTER_ENABLE = 1 << 6,
        FLAG_PIXMODE_SYNC = 1 << 7,
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
