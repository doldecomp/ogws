#ifndef EGG_CORE_GRAPHICS_FIFO_H
#define EGG_CORE_GRAPHICS_FIFO_H
#include "types_egg.h"
#include "ut_algorithm.h"

namespace EGG
{
    struct GraphicsFifo
    {
        struct GpStatus
        {
            u8 b0;
            u8 b1;
            u8 b2;
            u8 b3;
            u8 b4;
        };

        GraphicsFifo(u32, Heap *);
        static GraphicsFifo * create(u32, Heap *);
        virtual ~GraphicsFifo();

        void *PTR_0x4;
        void *mBufBase; // at 0x8
        u32 mBufSize; // at 0xC

        static GraphicsFifo *sGraphicsFifo;
        static GpStatus sGpStatus;
    };
}

#endif