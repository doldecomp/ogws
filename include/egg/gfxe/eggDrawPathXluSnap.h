#ifndef EGG_GFXE_DRAW_PATH_XLU_SNAP_H
#define EGG_GFXE_DRAW_PATH_XLU_SNAP_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggDrawPathBase.h>

namespace EGG {

class DrawPathXluSnap : public DrawPathBase {
    friend class ScnRenderer;

public:
    DrawPathXluSnap();
    virtual ~DrawPathXluSnap();     // at 0x8
    virtual u16 getNumStep() const; // at 0x1C
    virtual void internalCalc();    // at 0x24
    virtual void internalDraw(u16); // at 0x28

private:
    enum Step {
        cStep_0,
        cStep_1,
        cStep_2,
        cStep_3,

        cStep_Max
    };

private:
    u8 BYTE_0x7A;
    u8 BYTE_0x7B;
    u8 BYTE_0x7C;
    u8 BYTE_0x7D;
    int WORD_0x80;
    TextureBuffer* BUF_0x84;
    TextureBuffer* BUF_0x88;
    TextureBuffer* BUF_0x8C;
};

} // namespace EGG

#endif
