#ifndef EGG_GFX_DRAW_PATH_LIGHT_MAP_H
#define EGG_GFX_DRAW_PATH_LIGHT_MAP_H
#include "types_egg.h"
#include "eggDrawPathBase.h"

namespace EGG
{
    class DrawPathLightMap : public DrawPathBase
    {
    public:
        DrawPathLightMap();
        virtual int getNumScnProc() const; // at 0x1C
        virtual void calc(); // at 0x24
        virtual void draw(u16); // at 0x28
        virtual ~DrawPathLightMap(); // at 0x8

    private:
        u8 BYTE_0x7A;
        u8 BYTE_0x7B;
        u8 BYTE_0x7C;
        u8 BYTE_0x7D;
        int WORD_0x80;
        TextureBuffer *BUF_0x84;
        TextureBuffer *BUF_0x88;
        TextureBuffer *BUF_0x8C;

        static const int NUM_SCNPROC = 4;
    };
}

#endif