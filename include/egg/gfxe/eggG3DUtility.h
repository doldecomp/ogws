#ifndef EGG_GFXE_G3D_UTILITY_H
#define EGG_GFXE_G3D_UTILITY_H
#include <egg/types_egg.h>

#include <egg/prim.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

#include <revolution/GX.h>

namespace EGG {

// Forward declarations
class Heap;

struct StringSearchResult {
    u16 id;            // at 0x0
    const char* pName; // at 0x4
};

struct TextureReplaceResult {
    u16 materialID; // at 0x0
    u8 texMapID;    // at 0x2
    u8 texCoordID;  // at 0x3
};

class G3DUtility {
public:
    static void initialize(u32 tmpSize, Heap* pHeap);

    static bool setManualMapMode(nw4r::g3d::ResTexSrt srt, u32 id);

    static void manualProjectionMapping(nw4r::math::MTX34* pM, s8 camRef,
                                        s8 lightRef);

    static bool setUpLightSet(nw4r::g3d::LightSetting& rSetting,
                              const nw4r::g3d::ResAnmScn scn, int lightSetRef);

    static u16 searchStringResNode(const nw4r::g3d::ResMdl mdl,
                                   const char* pName,
                                   StringSearchResult* pResultSet,
                                   u32 resultNum);

    static u16 searchStringResMat(const nw4r::g3d::ResMdl mdl,
                                  const char* pName,
                                  StringSearchResult* pResultSet,
                                  u32 resultNum);

    static u16 searchStringResTexPlttInfo(const nw4r::g3d::ResMdl mdl,
                                          const char* pName,
                                          StringSearchResult* pResultSet,
                                          u32 resultNum);

    static u16 replaceTexture(nw4r::g3d::ResMat mat,
                              nw4r::g3d::ScnMdl::CopiedMatAccess* pMatAccess,
                              const char* pName, const GXTexObj& rTexObj,
                              bool saveFilterWrap,
                              TextureReplaceResult* pResultSet, u16 resultNum);

    static void reset() {
        sTempMemIndex = 0;
    }

    static void* alloc(u32 size) {
        void* pBlock = sTempMem + sTempMemIndex;
        sTempMemIndex += size;

#line 170
        EGG_ASSERT_MSG(sTempMemIndex < sTempMemSize, "Size over.");
        return pBlock;
    }

    template <typename T> static T* allocObj() {
        return static_cast<T*>(alloc(sizeof(T)));
    }

    template <typename T> static T* allocArray(u32 count) {
        return static_cast<T*>(alloc(sizeof(T) * count));
    }

    static MEMAllocator* getAllocator() {
        return sAllocator;
    }

private:
    static u8 sManualProjectionMapMode;
    static MEMAllocator* sAllocator;
    static u8* sTempMem;
    static u32 sTempMemIndex;
    static u32 sTempMemSize;
};

} // namespace EGG

#endif
