#ifndef RP_GRAPHICS_MODEL_H
#define RP_GRAPHICS_MODEL_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModelResManager.h>

#include <egg/core.h>
#include <egg/gfxe.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class IRPGrpModelCallback;
class RPGrpModelAnm;
class RPGrpModelBoundingInfo;
class RPGrpModelMaterial;
class RPGrpModelRecord;
class RPGrpTexture;

/**
 * @brief Base class for model implementations
 */
class RPGrpModel {
public:
    /**
     * @brief Model class type
     */
    enum Kind {
        Kind_None, //!< Dummy value
        Kind_G3D,  //!< RPGrpModelG3D
        Kind_RFL,  //!< RPGrpModelRfl
    };

    /**
     * @brief Model creation type flags
     */
    enum TypeOption {
        TypeOption_NoSimple = 1 << 0, //!< Require ScnMdl even without buffers
    };

    /**
     * @brief Bound creation type flags
     */
    enum BoundOption {
        BoundOption_Sphere = 1 << 0,
        BoundOption_SphereSet = 1 << 1,
        BoundOption_AABB = 1 << 2,
        BoundOption_AABBSet = 1 << 3,
    };

protected:
#if defined(VERSION_RSPE01_00)
    u8 unk0;
    u8 unk1;
    u16 mFlags;
    u16 unk4;
    u32 unkFlag;
    RPGrpModel* mpEntryNext; // at 0xC
    RPGrpModel* mpGenNext;   // at 0x10
    nw4r::math::MTX34 mtx14;
    nw4r::math::VEC3 mBaseScale;            // at 0x44
    RPGrpModelAnm* mpModelAnm;              // at 0x50
    RPGrpModelMaterial** mppMaterials;      // at 0x54
    RPGrpModelBoundingInfo* mpBoundingInfo; // at 0x58
    RPGrpModelRecord* mpRecord;             // at 0x5C
    BOOL mReverseCulling;                   // at 0x60
    IRPGrpModelCallback* mpCallback;        // at 0x64
    u8 mDrawScene;                          // at 0x68
    u8 mDrawGroup;                          // at 0x69
    u8 mViewNo;                             // at 0x6A
    u8 padding;
    u32 unk6C;

#elif defined(VERSION_RSPE01_01)
    u8 mViewNo;    // at 0x0
    u8 mDrawScene; // at 0x1
    u8 mDrawGroup; // at 0x2
    u8 unk3;
    char unk4;
    char unk5[0x8 - 0x5];
    u16 mFlags; // at 0x8
    u16 unkA;
    u32 unkFlag;
    u32 unk10;
    RPGrpModel* mpEntryNext;                // at 0x14
    RPGrpModel* mpGenNext;                  // at 0x18
    IRPGrpModelCallback* mpCallback;        // at 0x1C
    nw4r::math::VEC3 mBaseScale;            // at 0x20
    RPGrpModelAnm* mpModelAnm;              // at 0x2C
    RPGrpModelMaterial** mppMaterials;      // at 0x30
    RPGrpModelBoundingInfo* mpBoundingInfo; // at 0x34
    RPGrpModelRecord* mpRecord;             // at 0x38
    BOOL mReverseCulling;                   // at 0x3C
    EGG::ModelEx* mpModelEx;                // at 0x40
#endif

public:
    static RPGrpModel* Construct(RPGrpHandle handle, u8 viewNo, u32 typeOption,
                                 u32 bufferOption);

    static RPGrpModel* Construct(RPGrpHandle handle, int idx, u8 viewNo,
                                 u32 typeOption, u32 bufferOption);

    static RPGrpModel* Construct(RPGrpHandle handle, const char* pName,
                                 u8 viewNo, u32 typeOption, u32 bufferOption);

    virtual UNKTYPE VF_0x8(UNKTYPE) = 0;  // at 0x8
    virtual UNKTYPE VF_0xC(UNKTYPE) = 0;  // at 0xC
    virtual UNKTYPE VF_0x10(UNKTYPE) = 0; // at 0x10

    virtual Kind GetKind() = 0; // at 0x14

    virtual IRPGrpModelCallback*
    SetCallback(IRPGrpModelCallback* pCallback); // at 0x18

    virtual void SetReverseCulling(bool reverse); // at 0x1C

    virtual u16 ReplaceTexture(const char* pName, const RPGrpTexture& rTexture,
                               bool keepFilterWrap); // at 0x20

    virtual void SetCallbackJointIndex(u16 idx) = 0; // at 0x24
    virtual u16 GetCallbackJointIndex() const = 0;   // at 0x28

    virtual void SetJointVisible(u32 /* idx */, bool enable) { // at 0x2C
        if (enable) {
            mFlags |= EFlag_Visible;
        } else {
            mFlags &= ~EFlag_Visible;
        }
    }

    virtual bool IsJointVisible(u32 /* idx */) const { // at 0x30
        return mFlags & EFlag_Visible;
    }

    virtual void SetShapeVisible(u32 /* idx */, bool enable) { // at 0x34
        if (enable) {
            mFlags |= EFlag_Visible;
        } else {
            mFlags &= ~EFlag_Visible;
        }
    }

    virtual bool IsShapeVisible(u32 /* idx */) const { // at 0x38
        return mFlags & EFlag_Visible;
    }

    virtual void GetWorldMtx(u16 idx,
                             nw4r::math::MTX34* pMtx) const = 0; // at 0x3C
    virtual const nw4r::math::MTX34*
    GetWorldMtx(u16 nodeIdx) const = 0;                              // at 0x40
    virtual nw4r::math::MTX34* ReferWorldMtx(u16 nodeIdx) const = 0; // at 0x44

    virtual void GetViewMtx(u16 idx,
                            nw4r::math::MTX34* pMtx) const = 0; // at 0x48
    virtual void GetViewMtx(nw4r::math::MTX34* pMtx) const = 0; // at 0x4C

#if defined(VERSION_RSPE01_00)
    virtual u16 GetJointNum() const { // at 0x50
        return 0;                     // stubbed in rev 0
    }
#elif defined(VERSION_RSPE01_01)
    virtual u16 GetJointNum() const {
        return mpModelEx->getNumNode();
    }
#endif

    virtual const char* GetJointName(u16 idx) const = 0;    // at 0x54
    virtual u16 GetJointIndex(const char* pName) const = 0; // at 0x58

    virtual u16 GetMaterialNum() const;                        // at 0x5C
    virtual const char* GetMaterialName(u16 idx) const = 0;    // at 0x60
    virtual u16 GetMaterialIndex(const char* pName) const = 0; // at 0x64

#if defined(VERSION_RSPE01_00)
    virtual u16 GetShapeNum() const { // at 0x68
        return 0;
    }
#elif defined(VERSION_RSPE01_01)
    virtual u16 GetShapeNum() const { // at 0x68
        return mpModelEx->getNumShape();
    }
#endif

    virtual const char* GetShapeName(u16 idx) const = 0;    // at 0x6C
    virtual u16 GetShapeIndex(const char* pName) const = 0; // at 0x70

#if defined(VERSION_RSPE01_00)
    virtual u16 GetViewMtxNum() const { // at 0x74
        return 0;
    }
#elif defined(VERSION_RSPE01_01)
    virtual u16 GetViewMtxNum() const { // at 0x74
        return mpModelEx->getNumViewMtx();
    }
#endif

#if defined(VERSION_RSPE01_01)
    virtual void DrawDirect(u32 drawFlag,
                            nw4r::math::MTX34* pViewMtx) { // at 0x78
        mpModelEx->drawShapeDirectly(drawFlag, true, true, pViewMtx);
    }
#endif

    virtual void CalcMaterial(); // at 0x7C

#if defined(VERSION_RSPE01_01)
    virtual void CalcBeforeDraw() { // at 0x80
        mpModelEx->setVisible(mFlags & EFlag_Visible);
    }

    virtual void CalcView(const nw4r::math::MTX34& rViewMtx,
                          nw4r::math::MTX34* pViewMtxArray) { // at 0x84

        if (pViewMtxArray != NULL) {
            mpModelEx->calcView(rViewMtx, pViewMtxArray);
            return;
        }

        if (GetScnObj() != NULL) {
            GetScnObj()->G3dProc(nw4r::g3d::G3dObj::G3DPROC_CALC_VIEW, 0,
                                 const_cast<nw4r::math::MTX34*>(&rViewMtx));
        }
    }
#endif

    void RemoveGenList();
    void CreateMaterial(u16 idx);
    void CreateBoundingInfo(u32 flags);
    void CreateRecord(u16 frames);
    void UpdateFrame();
    void Calc();
    void Entry();

//! This is a bit hacky, but it's meant for nw4r functions
//! that require a pointer, not the matrix itself (texline)
#if defined(VERSION_RSPE01_00)
    nw4r::math::MTX34* GetMtxPtr() {
        return &mtx14;
    }
#endif

#if defined(VERSION_RSPE01_01)
    EGG::ModelEx* GetModelEx() const {
        return mpModelEx;
    }

    nw4r::g3d::ScnObj* GetScnObj() const {
        return mpModelEx->getScnObj();
    }

    nw4r::g3d::ScnLeaf* GetScnLeaf() const {
        return mpModelEx->getScnLeaf();
    }

    nw4r::g3d::ScnMdlSimple* GetScnMdlSimple() const {
        return mpModelEx->getScnMdlSimple();
    }

    nw4r::g3d::ScnMdl* GetScnMdl() const {
        return mpModelEx->getScnMdl();
    }

    nw4r::g3d::ScnRfl* GetScnRfl() const {
        return mpModelEx->getScnRfl();
    }
#endif

    RPGrpModelAnm* GetModelAnm() const {
        return mpModelAnm;
    }

    const nw4r::math::VEC3& GetBaseScale() const {
        return mBaseScale;
    }

    void SetBaseScale(const nw4r::math::VEC3& rBaseScale) {
        mBaseScale = rBaseScale;
    }

    void SetBaseScale(f32 x, f32 y, f32 z) {
        mBaseScale.x = x;
        mBaseScale.y = y;
        mBaseScale.z = z;
    }

    void SetBaseScale(f32 scale) {
        mBaseScale.x = mBaseScale.y = mBaseScale.z = scale;
    }

    RPGrpModelMaterial* GetMaterial(const char* pName) const {
        return mppMaterials[GetMaterialIndex(pName)];
    }
    RPGrpModelMaterial* GetMaterial(u16 idx) const {
        return mppMaterials[idx];
    }

    bool IsVisible() const {
        return (mFlags & EFlag_Visible) ? true : false;
    }

    u8 GetDrawScene() const {
        return mDrawScene;
    }

    void SetDrawScene(u8 drawScene) {
        mDrawScene = drawScene;
    }

    u8 GetUnk4() const {
        return unk4;
    }

    u8 GetDrawGroup() const {
        return mDrawGroup;
    }

    /**
     * @brief Gets the allocator used for model-related allocations
     */
    static EGG::Allocator* GetAllocator() {
        return spAllocator;
    }
    /**
     * @brief Sets the allocator used for model-related allocations
     *
     * @param pAllocator New allocator
     */
    static void SetAllocator(EGG::Allocator* pAllocator) {
        spAllocator = pAllocator;
    }

protected:
    explicit RPGrpModel(u8 viewNo);
    virtual ~RPGrpModel(); // at 0x88

    virtual void Configure();        // at 0x8C
    virtual void CreateAnm() = 0;    // at 0x90
    virtual void InternalCalc() = 0; // at 0x94

#if defined(VERSION_RSPE01_01)
    virtual void GetShapeMinMax(u16 shapeIdx, nw4r::math::VEC3* pMin,
                                nw4r::math::VEC3* pMax) const { // at 0x98
        mpModelEx->getShapeMinMax(shapeIdx, pMin, pMax, false);
    }
#endif

protected:
    enum {
        EFlag_Visible = 1 << 0,
        EFlag_Entered = 1 << 1,
        EFlag_HasRecord = 1 << 2,
    };

protected:
    static const nw4r::math::_VEC3 GEOMETRY_MAGNIFY[/* ??? */];

    //! Allocator used for model-related allocations
    static EGG::Allocator* spAllocator;

    //! First model in the draw ("entry") list
    static RPGrpModel* spEntryHead;
    //! Last model in the draw ("entry") list
    static RPGrpModel* spEntryTail;

    //! List of all active models in generation order
    static RPGrpModel* spGenList;

    //! Model currently running Calc
    static RPGrpModel* spCalcModel;

    static nw4r::math::MTX34* spCalcWorldMtxArray;
    static nw4r::math::MTX34* spCalcViewMtxArray;
};

//! @}

#endif
