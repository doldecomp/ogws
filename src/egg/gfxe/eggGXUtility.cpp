#include <egg/gfx.h>
#include <egg/gfxe.h>
#include <egg/prim.h>

#include <nw4r/g3d.h>

namespace EGG {

u8 GXUtility::getTexMtxID(int no) {
#line 22
    EGG_ASSERT(0 <= no && no < 8);

    static const u8 ID[] = {GX_TEXMTX0, GX_TEXMTX1, GX_TEXMTX2, GX_TEXMTX3,
                            GX_TEXMTX4, GX_TEXMTX5, GX_TEXMTX6, GX_TEXMTX7};

    return ID[no];
}

void GXUtility::setScaleOffsetPerspective(f32* p, f32 sx, f32 sy, f32 ox,
                                          f32 oy) {
#line 38
    EGG_ASSERT(p != NULL);
    EGG_ASSERT(sx != 0.f);
    EGG_ASSERT(sy != 0.f);

    p[1] *= 1.0f / sx;
    p[3] *= 1.0f / sy;
    p[2] += ox;
    p[4] += oy;
}

DECOMP_FORCEACTIVE(eggGXUtility_cpp,
                   "Not implemented.");

void GXUtility::getTexObj(GXTexObj* pObj, const ResTIMG& rRes) {
#line 70
    EGG_ASSERT(pObj);

    s32 offset = rRes.imageOffset != 0 ? rRes.imageOffset : sizeof(ResTIMG);
    const u8* pImage = reinterpret_cast<const u8*>(&rRes) + offset;

    // clang-format off
    GXInitTexObj(
        pObj,
        const_cast<u8*>(pImage),
        rRes.width,
        rRes.height,
        static_cast<GXTexFmt>(rRes.format),
        static_cast<GXTexWrapMode>(rRes.wrapS),
        static_cast<GXTexWrapMode>(rRes.wrapT),
        rRes.mipMap ? GX_TRUE : GX_FALSE);
    // clang-format on

    // clang-format off
    GXInitTexObjLOD(
        pObj, 
        static_cast<GXTexFilter>(rRes.minFilter),
        static_cast<GXTexFilter>(rRes.magFilter),
        rRes.minLOD / 8.0f,
        rRes.maxLOD / 8.0f, 
        rRes.LODBias / 100.0f, 
        rRes.biasClampEnable,
        rRes.edgeLODEnable, 
        static_cast<GXAnisotropy>(rRes.anisotropy));
    // clang-format on
}

void GXUtility::getTexObj(GXTexObj* pObj, const nw4r::g3d::ResTex tex,
                          GXTexWrapMode wrapS, GXTexWrapMode wrapT,
                          GXTexFilter minFilt, GXTexFilter magFilt) {
#line 113
    EGG_ASSERT(pObj);
    EGG_ASSERT(tex.IsValid());

    void* pImage;
    u16 width, height;
    GXTexFmt format;
    f32 minLod, maxLod;
    GXBool mipmap;

    if (tex.GetTexObjParam(&pImage, &width, &height, &format, &minLod, &maxLod,
                           &mipmap)) {
        GXInitTexObj(pObj, pImage, width, height, format, wrapS, wrapT, mipmap);

        GXInitTexObjLOD(pObj, minFilt, magFilt, minLod, maxLod, 0.0f, GX_FALSE,
                        GX_FALSE, GX_ANISO_1);
    }
}

} // namespace EGG
