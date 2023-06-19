#ifndef EGG_GFX_MODEL_EX_H
#define EGG_GFX_MODEL_EX_H
#include "types_egg.h"
#include "eggAssert.h"
#include "g3d_scnobj.h"
#include "g3d_scnproc.h"
#include "g3d_resmdl.h"
#include "g3d_resmat.h"
#include "g3d_resshp.h"
#include "math_types.h"
namespace EGG
{
    struct TextureReplaceResult
    {
        union Data
        {
            void *p;
            u32 l;
            u16 s;
            u8 b;
        } data[256];
    };

    class ModelEx
    {
    public:
        enum EType
        {
            cType_ScnMdlSimple,
            cType_ScnMdl,
            cType_ScnMdl1Mat1Shp,
            cType_ScnProcModel,
            cType_ScnRfl,
            cType_None
        };

        enum EFlag
        {
            cFlag_HasOriginalBV = (1 << 0)
        };

        enum EDrawShape
        {
            cDrawShape_None = (1 << 0)
        };

    private:
        EType mType; // at 0x0
        u16 mFlag; // at 0x4
        nw4r::g3d::ScnObj *mScnObj; // at 0x8
        ModelBoundingInfo *mpBV; // at 0xC

        static u32 sDrawFlag;
        static const char* sByteCodeCalcStr;
        static const char* sByteCodeMixStr;

    public:
        ModelEx(nw4r::g3d::ScnObj *);
        virtual ~ModelEx();
        
        void reset();
        u16 getNumShape() const;
        u16 getNumMaterial() const;
        u16 getNumNode() const;
        u16 getNumViewMtx() const;
        void getShapeMinMax(u16, nw4r::math::VEC3 *, nw4r::math::VEC3 *, bool);
        void setVisible(bool);
        void calcWorld(nw4r::math::MTX34 *) const;
        void calcView(const nw4r::math::MTX34 *, nw4r::math::MTX34 *) const;
        void drawShapeDirectly(u32, bool, bool, const nw4r::math::MTX34 *);
        u16 replaceTexture(const char *, const int&, bool,
            TextureReplaceResult *, u16, bool);
        void attachBoundingInfo(ModelBoundingInfo *);
        nw4r::g3d::ResShp getResShp(u16) const;
        nw4r::g3d::ResMat getResMat(u16) const;
        static int getDrawMode(u32);
        static int getDrawCtrl(u32, bool *);
        nw4r::g3d::ResTexSrt getResTexSrt(u16);

        ModelBoundingInfo * getBoundingInfo() const { return mpBV; }

        nw4r::g3d::ScnMdl * getScnMdl() const
        {
            return (mType == cType_ScnMdl)
                ? (nw4r::g3d::ScnMdl *)mScnObj : NULL;
        }

        nw4r::g3d::ScnMdlSimple * getScnMdlSimple() const
        {
            return (mType == cType_ScnMdlSimple || mType == cType_ScnMdl)
                ? (nw4r::g3d::ScnMdlSimple *)mScnObj : NULL;
        }

        nw4r::g3d::ScnMdl1Mat1Shp * getScnMdl1Mat1Shp() const
        {
            return (mType == cType_ScnMdl1Mat1Shp)
                ? (nw4r::g3d::ScnMdl1Mat1Shp *)mScnObj : NULL;
        }

        IScnProcModel * getScnProcModel() const
        {
            #line 310
            EGG_ASSERT(mType == cType_ScnProcModel);
            return (IScnProcModel *)((nw4r::g3d::ScnProc *)mScnObj)->GetUserData();
        }

        nw4r::g3d::ScnRfl * getScnRfl() const
        {
            return (mType == cType_ScnRfl)
                ? (nw4r::g3d::ScnRfl *)mScnObj : NULL;
        }

        void getMtxType0(nw4r::math::MTX34 *pMtx) const
        {
            #line 333
            EGG_ASSERT(pMtx);

            if (mScnObj != NULL)
            {
                nw4r::math::MTX34Copy(pMtx,
                    mScnObj->GetMtxPtr(nw4r::g3d::ScnObj::MTX_TYPE_0));
            }
            else
            {
                nw4r::math::MTX34Identity(pMtx);
            }
        }
    };
}

#endif