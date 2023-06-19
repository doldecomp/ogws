#ifndef EGG_GFX_G3D_UTILITY_H
#define EGG_GFX_G3D_UTILITY_H
#include "types_egg.h"
#include "eggAssert.h"
#include "types_nw4r.h"
#include "g3d_resmat.h"
#include "g3d_scnmdl.h"

namespace EGG
{
    class G3DUtility
    {
    public:
        static MEMAllocator * getAllocator() { return sAllocator; }

        static void initialize(u32, Heap *);
        static bool setManualMapMode(nw4r::g3d::ResTexSrt, u32);
        static void texCamMtxFunc(nw4r::math::MTX34 *, s8, s8);
        static bool light_func_8008F59C(nw4r::g3d::LightSetting *, nw4r::g3d::ResAnmScn, u32);
        static int searchStringResNode(nw4r::g3d::ResMdl, const char *, u16 *, u32);
        static void searchStringResMat(nw4r::g3d::ResMdl, const char *, u16 *, u32);
        static void searchStringResTexPlttInfo(nw4r::g3d::ResMdl, const char *, u16 *, u32);
        static int replaceTexture(nw4r::g3d::ResMat, nw4r::g3d::ScnMdl::CopiedMatAccess *,
            const char *, const int&, bool, u16);

        static void clearTempMem() { sTempMemIndex = 0; }
        static void * allocTempMem(size_t size)
        {
            int blockEnd = sTempMemIndex + size;
            void *block = &sTempMem[sTempMemIndex];
            sTempMemIndex = blockEnd;

            #line 170
            EGG_ASSERT_MSG(sTempMemIndex < sTempMemSize, "Size over.");
            return block;
        }

    private:
        static u8 sManualProjectionMapMode;
        static MEMAllocator *sAllocator;
        static char *sTempMem;
        static u32 sTempMemIndex;
        static u32 sTempMemSize;
    };
}

#endif