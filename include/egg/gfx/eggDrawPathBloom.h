#ifndef EGG_GFX_DRAW_PATH_BLOOM_H
#define EGG_GFX_DRAW_PATH_BLOOM_H
#include "types_egg.h"
#include "eggDrawPathBase.h"
#include "eggIBinary.h"

namespace EGG
{
    class DrawPathBloom : public DrawPathBase, public IBinary<DrawPathBloom>
    {
    public:
        DrawPathBloom();
        virtual int getNumScnProc() const; // at 0x1C
        virtual void calc(); // at 0x24
        virtual void draw(u16); // at 0x28
        virtual ~DrawPathBloom(); // at 0x8

        virtual void SetBinaryInner(const Bin&); // at 0x8
        virtual void GetBinaryInner(Bin *) const; // at 0xC
        virtual const char * GetBinaryType() const; // at 0x10
        virtual u8 GetVersion() const; // at 0x18

        void setFlag(u8 f) { mFlags |= f; }
        void clearFlag(u8 f) { mFlags &= ~f; }

    private:
        u8 mFlags; // at 0x80
        char UNK_0x81[0x134 - 0x81];
    };
}

#endif