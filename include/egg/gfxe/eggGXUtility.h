#ifndef EGG_GFXE_GX_UTILITY_H
#define EGG_GFXE_GX_UTILITY_H
#include <egg/types_egg.h>

#include <egg/gfx/eggResTIMG.h>

#include <nw4r/g3d.h>

#include <revolution/GX.h>

namespace EGG {

class GXUtility {
public:
    static u8 getTexMtxID(int no);

    static void setScaleOffsetPerspective(f32* p, f32 sx, f32 sy, f32 ox,
                                          f32 oy);

    static void getTexObj(GXTexObj* pObj, const ResTIMG& rRes);

    static void getTexObj(GXTexObj* pObj, const nw4r::g3d::ResTex tex,
                          GXTexWrapMode wrapS, GXTexWrapMode wrapT,
                          GXTexFilter minFilter, GXTexFilter magFilter);
};

} // namespace EGG

#endif
