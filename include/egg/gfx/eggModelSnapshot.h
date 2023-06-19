#ifndef EGG_GFX_MODEL_SNAPSHOT_H
#define EGG_GFX_MODEL_SNAPSHOT_H
#include "types_egg.h"
#include "eggCapTexture.h"

namespace EGG
{
    class ModelSnapshot : public CapTexture
    {
    public:
        enum SnapshotFlag
        {
            SNAPSHOT_0x2 = (1 << 1)
        };

        struct ModelBind
        {
            ModelEx *model; // at 0x0
            f32 FLOAT_0x4;
            u8 BYTE_0x8;
        };

    public:
        ModelSnapshot(u16, u16, GXTexFmt, u16);
        virtual ~ModelSnapshot(); // at 0x8
        virtual void DoResetList(); // at 0x18
        virtual void ResetList(); // at 0x1C
        
        void AddModelEx(ModelEx *, f32);
        void GatherModel(f32);

    private:
        u16 m_mdlMax; // at 0x2C
        u16 m_width; // at 0x2E
        u16 m_height; // at 0x30
        u16 m_mdlNum; // at 0x32
        u8 m_flags; // at 0x34
        UNKWORD WORD_0x38;
        ModelBind *m_mdlList; // at 0x3C
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
    };
}

#endif