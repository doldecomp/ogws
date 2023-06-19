#ifndef EGG_CORE_DECOMP_H
#define EGG_CORE_DECOMP_H
#include "types_egg.h"

namespace EGG
{
    class Decomp
    {
    public:
        enum CompressedType
        {
            TYPE_UNKNOWN = 0,
            TYPE_SZS = 1,
            TYPE_ASH = 2,
            TYPE_ASR = 3
        };

        static int decode(u8 *, u8 *);
        static int decodeSZS(u8 *, u8 *);
        static int decodeASH(u8 *, u8 *);
        static int decodeASR(u8 *, u8 *);
        static int checkCompressed(u8 *);
        static int getExpandSize(u8 *);
        static UNKWORD getBitsCode(u8 *, int, int);
        static UNKWORD getBit1c(u8 *, int);
        static UNKWORD readTree9(u8 *, u16 *, u16 *, u16 *);
        static UNKWORD readTree12(u8 *, u16 *, u16 *, u16 *);

    private:
        static const int cTreeStackSize = 256;

        static char *sWorkArea; // sizeof = 0x9008
        static UNKWORD lbl_804BED10[2];
        static UNKWORD lbl_804BED18[2];
        static UNKWORD lbl_804BED20[2];
        static UNKWORD lbl_804BED28[2];
    };
}

#endif