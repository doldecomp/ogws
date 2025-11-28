#ifndef EGG_GFXE_DRAW_PATH_XLU_SNAP_H
#define EGG_GFXE_DRAW_PATH_XLU_SNAP_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggDrawPathBase.h>

namespace EGG {

class DrawPathXluSnap : public DrawPathBase {
public:
    DrawPathXluSnap();
    virtual ~DrawPathXluSnap();     // at 0x8
    virtual int getNumStep() const; // at 0x1C
    virtual void internalCalc();    // at 0x24
    virtual void internalDraw(u16); // at 0x28

private:
    enum EStep {
        EStep_0,
        EStep_1,
        EStep_2,
        EStep_3,

        EStep_Max
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
