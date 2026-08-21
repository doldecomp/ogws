#ifndef EGG_GFXE_MODEL_SNAPSHOT_H
#define EGG_GFXE_MODEL_SNAPSHOT_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggCapTexture.h>

namespace EGG {

// Forward declarations
class ModelEx;

class ModelSnapshot : public CapTexture {
public:
    ModelSnapshot(u16 width, u16 height, GXTexFmt format, u16 mdlMax);

    virtual void InitList();  // at 0x18
    virtual void ResetList(); // at 0x1C

    void AddModelEx(ModelEx* pModel, f32 adjust = 1.0f);
    void GatherModel(f32 adjust = 1.0f);

protected:
    struct ModelBind {
        ModelEx* pModel; // at 0x0
        f32 adjust;      // at 0x4
        bool useMat;     // at 0x8
    };

protected:
    u16 m_mdlMax; // at 0x2C
    u16 m_width;  // at 0x2E
    u16 m_height; // at 0x30
    u16 m_mdlNum; // at 0x32
    u8 m_flags;   // at 0x34
    u32 unk38;
    ModelBind* m_mdlList; // at 0x3C
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    nw4r::math::VEC3 m_center; // at 0x50
    nw4r::math::VEC3 unk5C;
    f32 m_radius; // at 0x68
    f32 unk6C;

protected:
    enum {
        cFlag_1 = 1 << 1,
    };
};

} // namespace EGG

#endif
