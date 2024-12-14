#ifndef NW4R_G3D_CALCWORLD_H
#define NW4R_G3D_CALCWORLD_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resmdl.h>
#include <nw4r/g3d/g3d_scnobj.h>

#include <nw4r/math.h>

namespace nw4r {
namespace g3d {

// Forward declarations
class AnmObjChr;
struct ChrAnmResult;
class FuncObjCalcWorld;

class WorldMtxManip {
public:
    WorldMtxManip(math::MTX34* pM, math::VEC3* pS, u32* pWMAttr)
        : mpM(pM), mpS(pS), mpWMAttr(pWMAttr) {}

private:
    math::MTX34* mpM; // at 0x0
    math::VEC3* mpS;  // at 0x4
    u32* mpWMAttr;    // at 0x8
};

class ICalcWorldCallback {
public:
    virtual ~ICalcWorldCallback() = 0; // at 0x8

    virtual void ExecCallbackA(ChrAnmResult* pResult, ResMdl mdl,
                               FuncObjCalcWorld* pFuncObj) = 0; // at 0xC

    virtual void ExecCallbackB(WorldMtxManip* pManip, ResMdl mdl,
                               FuncObjCalcWorld* pFuncObj) = 0; // at 0x10

    virtual void ExecCallbackC(math::MTX34* pMtxArray, ResMdl mdl,
                               FuncObjCalcWorld* pFuncObj) = 0; // at 0x14
};

class FuncObjCalcWorld {
public:
    FuncObjCalcWorld(ICalcWorldCallback* pCallback, u32 timing, u32 nodeID)
        : mpCallback(pCallback), mTiming(timing), mNodeID(nodeID) {}
    ~FuncObjCalcWorld() {}

    void CheckCallbackA(u32 nodeID, ChrAnmResult* pResult, ResMdl mdl) {
        if (nodeID == mNodeID && (mTiming & ScnObj::CALLBACK_TIMING_A)) {
            mpCallback->ExecCallbackA(pResult, mdl, this);
        }
    }

    void CheckCallbackB(u32 nodeID, math::MTX34* pM, math::VEC3* pS,
                        u32* pWMAttr, ResMdl mdl) {

        if (nodeID == mNodeID && (mTiming & ScnObj::CALLBACK_TIMING_B)) {
            WorldMtxManip manip(pM, pS, pWMAttr);
            mpCallback->ExecCallbackB(&manip, mdl, this);
        }
    }

    void CheckCallbackC(math::MTX34* pMtxArray, ResMdl mdl) {
        if (mTiming & ScnObj::CALLBACK_TIMING_C) {
            mpCallback->ExecCallbackC(pMtxArray, mdl, this);
        }
    }

private:
    ICalcWorldCallback* mpCallback; // at 0x0
    u8 mTiming;                     // at 0x4
    u8 _;                           // at 0x5
    u16 mNodeID;                    // at 0x6
};

void CalcWorld(math::MTX34*, u32*, const u8*, const math::MTX34*, ResMdl,
               AnmObjChr*, FuncObjCalcWorld*, u32);

void CalcWorld(math::MTX34*, u32*, const u8*, const math::MTX34*, ResMdl,
               AnmObjChr*, FuncObjCalcWorld*);

void CalcSkinning(math::MTX34*, u32*, ResMdl, const u8*);

} // namespace g3d
} // namespace nw4r

#endif