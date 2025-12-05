#ifndef RP_GRAPHICS_MODEL_ANM_IMPLEMENT_H
#define RP_GRAPHICS_MODEL_ANM_IMPLEMENT_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpModel.h>
#include <Pack/RPGraphics/RPGrpModelAnm.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpModel;

/**
 * @brief Model animation implementation
 */
template <RPGrpModel::Kind K>
class RPGrpModelAnmImplement : public RPGrpModelAnm {
protected:
    char _6C[0xE8 - 0x6C];

public:
    static RPGrpModelAnm* Construct(RPGrpModel* pModel) DECOMP_DONT_INLINE {
        RPGrpModelAnm* pAnm = new RPGrpModelAnmImplement(pModel);
        pAnm->Configure();
        return pAnm;
    }

    virtual void Configure(); // at 0x8
    virtual void Construct(Anm anm, u16 idx, u16 rd);

    virtual void Regist(Anm anm, u16 idx, u16 rd, char const* pName,
                        u32 arg4); // at 0x10
    virtual void VF_0x14(UNKTYPE);
    virtual void VF_0x18(UNKTYPE);
    virtual void VF_0x1C(UNKTYPE);

    virtual void VF_0x20(UNKTYPE);
    virtual void VF_0x24(UNKTYPE);
    virtual void VF_0x28(UNKTYPE);
    virtual void VF_0x2C(UNKTYPE);

    virtual void VF_0x30(UNKTYPE);
    virtual void VF_0x34(UNKTYPE);
    virtual void VF_0x38(UNKTYPE);

    virtual void Cancel(Anm anm, u16 idx);
    virtual void Start(Anm anm, u16 idx, f32 frame = 1.0f); // at 0x40

    virtual f32 VF_0x44(UNKTYPE);
    virtual f32 VF_0x48(UNKTYPE);

    virtual u16 GetNumFrame(Anm anm, u16 idx) const; // at 0x4C
    virtual AnmPlayPolicy GetAnmPlayPolicy(Anm anm,
                                           u16 idx) const; // at 0x50

    virtual void SetFrame(Anm anm, u16 idx, f32 frame); // at 0x54
    virtual f32 GetFrame(Anm anm, u16 idx) const;       // at 0x58

    virtual void SetUpdateRate(Anm anm, u16 idx, f32 rate); // at 0x5C
    virtual f32 GetUpdateRate(Anm anm, u16 idx) const;      // at 0x60

    virtual void SetEnableQuaternionBlend(bool enable); // at 0x64

    virtual void VF_0x68(UNKTYPE); // at 0x68
    virtual void UpdateFrame();    // at 0x6C
    virtual void VF_0x70(UNKTYPE); // at 0x70
    virtual void VF_0x74(UNKTYPE); // at 0x74

    virtual nw4r::g3d::AnmObj* GetAnmObj(Anm anm, u16 idx) const; // at 0x78

    void CreateBuffer(Anm anm, u16 num);

    void Calc();

private:
    RPGrpModelAnmImplement(RPGrpModel* pModel);
    virtual ~RPGrpModelAnmImplement() {} // at 0x7C

    virtual void SetAnmObj(Anm anm, nw4r::g3d::AnmObj* pAnmObj); // at 0x80
    virtual void InternalCalc();                                 // at 0x84
};

// Shorthand names for specializations
typedef RPGrpModelAnmImplement<RPGrpModel::Kind_G3D> RPGrpModelAnmG3D;

//! @}

#endif
