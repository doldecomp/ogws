#pragma ipa file
#pragma use_lmw_stmw on
#include "eggDecomp.h"
#include "eggAssert.h"

// In some situations, the devs opted to build U32 values out of bytes,
// rather than casting a pointer to the type (u32 *)
#define GET_U32(data, ofs) \
    (data[ofs] << 24 | data[ofs + 1] << 16 | data[ofs + 2] << 8 | data[ofs + 3])

#define HAS_MAGIC(x, a, b, c) \
    (x[0] == a && x[1] == b && x[2] == c)

namespace EGG
{
    int Decomp::decode(u8 *in, u8 *out)
    {
        switch(checkCompressed(in))
        {
            case TYPE_SZS:
                return decodeSZS(in, out);
            case TYPE_ASH:
                return decodeASH(in, out);
            case TYPE_ASR:
                return decodeASR(in, out);
            default:
                return -1;
        }
    }

    // int Decomp::decodeSZS(u8 *in, u8 *out)
    // {
    //     int expandSize = getExpandSize(in);
    //     for (int i = 0; i < expandSize; i++)
    //     {
            
    //     }
    // }

    // int Decomp::decodeASH(u8 *in, u8 *out)
    // {

    // }

    // int Decomp::decodeASR(u8 *in, u8 *out)
    // {

    // }

    int Decomp::checkCompressed(u8 *binary)
    {
        if HAS_MAGIC(binary, 'Y', 'a', 'z') return TYPE_SZS;
        if HAS_MAGIC(binary, 'A', 'S', 'H') return TYPE_ASH;
        if HAS_MAGIC(binary, 'A', 'S', 'R') return TYPE_ASR;
        return TYPE_UNKNOWN;
    }

    int Decomp::getExpandSize(u8 *binary)
    {
        switch(checkCompressed(binary))
        {
            case TYPE_SZS:
                return binary[4] << 24 | binary[5] << 16 | binary[6] << 8 | binary[7];
            case TYPE_ASH:
                return binary[5] << 16 | binary[6] << 8 | binary[7];
            case TYPE_ASR:
                return binary[5] << 16 | binary[6] << 8 | binary[7];
            default:
                return -1;
        }
    }

    UNKWORD Decomp::getBitsCode(u8 *binary, int size, int bit)
    {
        UNKWORD uVar7 = lbl_804BED20[bit];
        UNKWORD uVar6 = lbl_804BED10[bit];
        u32 uVar4 = lbl_804BED28[bit];
        
        u32 uVar5;
        UNKWORD r3;
        if (uVar6 + size > 32)
        {
            uVar5 = GET_U32(binary, uVar7);
            r3 = uVar4 >> (32 - size) | uVar5 >> (64 - size) - uVar6;
            uVar6 += size - 32;
            lbl_804BED28[bit] = uVar5 << uVar6;
            lbl_804BED10[bit] = uVar6;
            lbl_804BED20[bit] = uVar7 + 4;
        }
        else if (uVar6 + size == 32)
        {
            r3 = uVar4 >> (32 - size);
            lbl_804BED28[bit] = GET_U32(binary, uVar7);
            lbl_804BED20[bit] = uVar7 + 4;
            lbl_804BED10[bit] = 0;
        }
        else
        {
            r3 = uVar4 >> (32 - size);
            lbl_804BED28[bit] = uVar4 << size;
            lbl_804BED10[bit] = uVar6 + size;
        }

        return r3;
    }

    UNKWORD Decomp::getBit1c(u8 *binary, int bit)
    {
        UNKWORD uVar6 = lbl_804BED20[bit];
        UNKWORD uVar7 = lbl_804BED10[bit];

        u32 uVar9 = lbl_804BED28[bit];
        UNKWORD r7 = uVar9 >> 31;

        if (uVar7 == 31)
        {            
            lbl_804BED28[bit] = GET_U32(binary, uVar6);
            lbl_804BED20[bit] = uVar6 + 4;
            lbl_804BED10[bit] = 0;
        }
        else
        {
            lbl_804BED28[bit] = uVar9 << 1;
            lbl_804BED10[bit] = uVar7 + 1;
        }

        return r7;
    }

    UNKWORD Decomp::readTree9(u8 *binary, u16 *r4, u16 *r5, u16 *stack)
    {
        UNKWORD uVar8;
        UNKWORD uVar7 = lbl_804BED18[0];
        uVar8 = uVar7;
        UNKWORD sp = 0;

        while (true)
        {
            if (getBit1c(binary, 0) != 0)
            {
                stack[sp] = uVar8 | 0x8000;
                stack[sp + 1] = uVar8 | 0x4000;
                uVar8++;
                uVar7++;
                sp += sizeof(u16);

                #line 620
                EGG_ASSERT(sp < cTreeStackSize);
            }
            else
            {
                UNKWORD code = getBitsCode(binary, 9, 0);
                while (true)
                {
                    u16 uVar1 = stack[--sp];

                    if (uVar1 & 0x8000)
                    {
                        r5[uVar1 & 0x3FFF] = code;
                        code = uVar1 & 0x3FFF;

                        if (sp == 0) return code;
                    }
                    else
                    {
                        r4[uVar1 & 0x3FFF] = code;
                        uVar8 = uVar7;
                        break;
                    }
                }
            }
        }
    }

    UNKWORD Decomp::readTree12(u8 *binary, u16 *r4, u16 *r5, u16 *stack)
    {
        UNKWORD uVar8;
        UNKWORD uVar7 = lbl_804BED18[1];
        uVar8 = uVar7;
        UNKWORD sp = 0;

        while (true)
        {
            if (getBit1c(binary, 1) != 0)
            {
                stack[sp] = uVar8 | 0x8000;
                stack[sp + 1] = uVar8 | 0x4000;
                uVar8++;
                uVar7++;
                sp += sizeof(u16);

                #line 668
                EGG_ASSERT(sp < cTreeStackSize);
            }
            else
            {
                UNKWORD code = getBitsCode(binary, 12, 0);
                while (true)
                {
                    u16 uVar1 = stack[--sp];

                    if (uVar1 & 0x8000)
                    {
                        r5[uVar1 & 0x3FFF] = code;
                        code = uVar1 & 0x3FFF;

                        if (sp == 0) return code;
                    }
                    else
                    {
                        r4[uVar1 & 0x3FFF] = code;
                        uVar8 = uVar7;
                        break;
                    }
                }
            }
        }
    }

    char *Decomp::sWorkArea;
    UNKWORD Decomp::lbl_804BED10[2];
    UNKWORD Decomp::lbl_804BED18[2];
    UNKWORD Decomp::lbl_804BED20[2];
    UNKWORD Decomp::lbl_804BED28[2];
}