#ifndef EGG_GFXE_MODEL_EX_H
#define EGG_GFXE_MODEL_EX_H
#include <egg/types_egg.h>

#include <egg/prim.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

namespace EGG {

struct TextureReplaceResult {
    union Data {
        void* p;
        u32 l;
        u16 s;
        u8 b;
    } data[256];
};

class ModelEx {
public:
    enum EType {
        cType_ScnMdlSimple,
        cType_ScnMdl,
        cType_ScnMdl1Mat1Shp,
        cType_ScnProcModel,
        cType_ScnRfl,
        cType_Unknown
    };

    enum EDrawShape { cDrawShape_None = 1 << 0 };

    enum EDrawFlag {
        cDrawFlag_IgnoreMaterial = 1 << 1,
        cDrawFlag_ForceLightOff = 1 << 2,
        cDrawFlag_ShapeOnly = 1 << 3,
    };

private:
    static u32 sDrawFlag;

    EType mType;                // at 0x0
    u16 mFlag;                  // at 0x4
    nw4r::g3d::ScnObj* mScnObj; // at 0x8
    ModelBoundingInfo* mpBV;    // at 0xC

public:
    ModelEx(nw4r::g3d::ScnObj* pScnObj);
    virtual ~ModelEx(); // at 0x8

    void reset();

    u16 getNumShape() const;
    u16 getNumMaterial() const;
    u16 getNumNode() const;
    u16 getNumViewMtx() const;

    void getShapeMinMax(u16 shapeIndex, nw4r::math::VEC3* pMin,
                        nw4r::math::VEC3* pMax, bool doCalcWorld);
    void setVisible(bool enable);
    void calcWorld(nw4r::math::MTX34* pWorldMtxArray) const;
    void calcView(const nw4r::math::MTX34& rViewMtx,
                  nw4r::math::MTX34* pViewMtxArray) const;
    void drawShapeDirectly(u32 drawFlag, bool opa, bool xlu,
                           nw4r::math::MTX34* pViewMtx);
    u16 replaceTexture(const char*, const int&, bool, TextureReplaceResult*,
                       u16, bool);
    void attachBoundingInfo(ModelBoundingInfo* pBV);

    nw4r::g3d::ResShp getResShp(u16 shapeIndex) const;
    nw4r::g3d::ResMat getResMat(u16 matIndex) const;

    static u32 getDrawMode(u32 drawFlag);
    static u32 getDrawCtrl(u32 drawFlag, bool* pUseMat);

    nw4r::g3d::ResTexSrt getResTexSrt(u16 matIndex);

    ModelBoundingInfo* getBoundingInfo() const {
        return mpBV;
    }

    nw4r::g3d::ScnMdl* getScnMdl() const {
        return mType == cType_ScnMdl ? static_cast<nw4r::g3d::ScnMdl*>(mScnObj)
                                     : NULL;
    }

    nw4r::g3d::ScnMdlSimple* getScnMdlSimple() const {
        return mType == cType_ScnMdlSimple || mType == cType_ScnMdl
                   ? static_cast<nw4r::g3d::ScnMdlSimple*>(mScnObj)
                   : NULL;
    }

    nw4r::g3d::ScnMdl1Mat1Shp* getScnMdl1Mat1Shp() const {
        return mType == cType_ScnMdl1Mat1Shp
                   ? static_cast<nw4r::g3d::ScnMdl1Mat1Shp*>(mScnObj)
                   : NULL;
    }

    IScnProcModel* getScnProcModel() const {
#line 310
        EGG_ASSERT(mType == cType_ScnProcModel);

        void* pUserData =
            static_cast<nw4r::g3d::ScnProc*>(mScnObj)->GetUserData();

        return reinterpret_cast<IScnProcModel*>(pUserData);
    }

    nw4r::g3d::ScnRfl* getScnRfl() const {
        return mType == cType_ScnRfl ? static_cast<nw4r::g3d::ScnRfl*>(mScnObj)
                                     : NULL;
    }

    void getLocalMtx(nw4r::math::MTX34* pMtx) const {
#line 333
        EGG_ASSERT(pMtx);

        if (mScnObj != NULL) {
            nw4r::math::MTX34Copy(
                pMtx, mScnObj->GetMtxPtr(nw4r::g3d::ScnObj::MTX_LOCAL));
        } else {
            nw4r::math::MTX34Identity(pMtx);
        }
    }

private:
    enum { cFlag_HasOriginalBV = 1 << 0 };
};

} // namespace EGG

#endif
