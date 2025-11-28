#ifndef EGG_GFXE_MODEL_SNAPSHOT_H
#define EGG_GFXE_MODEL_SNAPSHOT_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggCapTexture.h>

namespace EGG {

class ModelSnapshot : public CapTexture {
public:
    struct ModelBind {
        ModelEx* pModel; // at 0x0
        f32 density;     // at 0x4
        bool useMat;     // at 0x8
    };

public:
    ModelSnapshot(u16 w, u16 h, GXTexFmt fmt, u16 mdlMax);
    virtual ~ModelSnapshot() {} // at 0x8

    virtual void DoResetList(); // at 0x18
    virtual void ResetList();   // at 0x1C

    void AddModelEx(ModelEx* pModel, f32 density);
    void GatherModel(f32);

private:
    u16 m_mdlMax; // at 0x2C
    u16 m_width;  // at 0x2E
    u16 m_height; // at 0x30
    u16 m_mdlNum; // at 0x32
    u8 m_flags;   // at 0x34
    UNKWORD WORD_0x38;
    ModelBind* m_mdlList; // at 0x3C
    f32 FLOAT_0x40;
    f32 FLOAT_0x44;
    f32 FLOAT_0x48;
    f32 FLOAT_0x4C;
    f32 FLOAT_0x50;
    f32 FLOAT_0x54;
    f32 FLOAT_0x58;
    f32 FLOAT_0x5C;
    f32 FLOAT_0x60;
    f32 FLOAT_0x64;
    f32 FLOAT_0x68;
    f32 FLOAT_0x6C;

private:
    enum {
        EFlag_1 = 1 << 1,
    };
};

} // namespace EGG

#endif
