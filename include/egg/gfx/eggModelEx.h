#ifndef EGG_GFX_MODEL_EX_H
#define EGG_GFX_MODEL_EX_H
#include "types_egg.h"
#include "types_nw4r.h"

namespace EGG
{
    class ModelEx
    {
    public:
        ModelEx(nw4r::g3d::ScnObj *);
        virtual ~ModelEx();

        ModelBoundingInfo * getBoundingInfo() const { return mBounding; }

    private:
        char UNK_0x4[0xC - 0x4];
        ModelBoundingInfo *mBounding; // at 0xC
    };
}

#endif