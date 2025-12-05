#ifndef RP_GRAPHICS_MODEL_H
#define RP_GRAPHICS_MODEL_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModelResManager.h>

#include <egg/core.h>
#include <egg/gfxe.h>

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
    u8 mViewNo;    // at 0x0
    u8 mDrawScene; // at 0x1
    u8 mDrawGroup; // at 0x2
    char unk3;
    char unk4;
    char unk5[0x8 - 0x5];
    u16 mFlags; // at 0x8
    u16 unkA;
    u32 unkC;
    u32 unk10;
    RPGrpModel* mpEntryNext;         // at 0x14
    RPGrpModel* mpGenNext;           // at 0x18
    IRPGrpModelCallback* mpCallback; // at 0x1C
    f32 unk20;
    f32 unk24;
    f32 unk28;
    RPGrpModelAnm* mpModelAnm;              // at 0x2C
    RPGrpModelMaterial** mppMaterials;      // at 0x30
    RPGrpModelBoundingInfo* mpBoundingInfo; // at 0x34
    RPGrpModelRecord* mpRecord;             // at 0x38
    BOOL mReverseCulling;                   // at 0x3C
    EGG::ModelEx* mpModelEx;                // at 0x40

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

    virtual void SetJointVisible(u32 /* id */, bool enable) { // at 0x2C
        if (enable) {
            mFlags |= EFlag_Visible;
        } else {
            mFlags &= ~EFlag_Visible;
        }
    }

    virtual bool IsJointVisible() const { // at 0x30
        return mFlags & EFlag_Visible;
    }

    virtual void SetShapeVisible(u32 /* id */, bool enable) { // at 0x34
        if (enable) {
            mFlags |= EFlag_Visible;
        } else {
            mFlags &= ~EFlag_Visible;
        }
    }

    virtual bool IsShapeVisible() const { // at 0x38
        return mFlags & EFlag_Visible;
    }

    virtual void GetWorldMtx(u16 idx,
                             EGG::Matrix34f* pMtx) const = 0; // at 0x3C
    virtual EGG::Matrix34f* GetWorldMtx(u16 idx) const = 0;   // at 0x40
    virtual EGG::Matrix34f* ReferWorldMtx(u16 idx) const = 0; // at 0x44

    virtual void GetViewMtx(u16 idx,
                            EGG::Matrix34f* pMtx) const = 0; // at 0x48
    virtual EGG::Matrix34f* GetViewMtx(u16 idx) const = 0;   // at 0x4C

    virtual u16 GetJointNum() const { // at 0x50
        return mpModelEx->getNumNode();
    }

    virtual const char* GetJointName(u16 idx) const = 0;    // at 0x54
    virtual u16 GetJointIndex(const char* pName) const = 0; // at 0x58

    virtual u16 GetMaterialNum() const;                        // at 0x5C
    virtual const char* GetMaterialName(u16 idx) const = 0;    // at 0x60
    virtual u16 GetMaterialIndex(const char* pName) const = 0; // at 0x64

    virtual u16 GetShapeNum() const { // at 0x68
        return mpModelEx->getNumShape();
    }

    virtual const char* GetShapeName(u16 idx) const = 0;    // at 0x6C
    virtual u16 GetShapeIndex(const char* pName) const = 0; // at 0x70

    virtual u16 GetViewMtxNum() const { // at 0x74
        return mpModelEx->getNumViewMtx();
    }

    virtual void DrawDirect(u32 drawFlag, EGG::Matrix34f* pViewMtx) { // at 0x78
        mpModelEx->drawShapeDirectly(drawFlag, true, true, pViewMtx);
    }

    virtual void CalcMaterial(); // at 0x7C

    virtual void CalcBeforeDraw() { // at 0x80
        mpModelEx->setVisible(mFlags & EFlag_Visible);
    }

    virtual void CalcView(const EGG::Matrix34f& rViewMtx,
                          EGG::Matrix34f* pViewMtxArray) { // at 0x84

        if (pViewMtxArray != NULL) {
            mpModelEx->calcView(rViewMtx, pViewMtxArray);
            return;
        }

        nw4r::g3d::ScnObj* pScnObj = mpModelEx->getScnObj();
        if (pScnObj != NULL) {
            pScnObj->G3dProc(nw4r::g3d::G3dObj::G3DPROC_CALC_VIEW, 0,
                             const_cast<EGG::Matrix34f*>(&rViewMtx));
        }
    }

    void CreateMaterial(u16 idx);
    void CreateBoundingInfo(u32 flags);
    void CreateRecord(u16 frames);
    void UpdateFrame();
    void Calc();
    void Entry();
    void RemoveGenList();

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
    RPGrpModel(u8 viewNo);
    virtual ~RPGrpModel(); // at 0x88

    virtual void Configure();        // at 0x8C
    virtual void CreateAnm() = 0;    // at 0x90
    virtual void InternalCalc() = 0; // at 0x94

    virtual void GetShapeMinMax(u16 shapeIdx, EGG::Vector3f* pMin,
                                EGG::Vector3f* pMax) const { // at 0x98
        mpModelEx->getShapeMinMax(shapeIdx, pMin, pMax, false);
    }

protected:
    enum {
        EFlag_Visible = 1 << 0,
        EFlag_Entered = 1 << 1,
        EFlag_HasRecord = 1 << 2,
    };

protected:
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

    static EGG::Matrix34f* spCalcModelMtxArray;
    static EGG::Matrix34f* spCalcViewPosMtxArray;
};

//! @}

#endif
