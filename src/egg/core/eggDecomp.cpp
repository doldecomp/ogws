// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

namespace EGG {

u8* Decomp::sWorkArea = NULL;

int Decomp::sStreamBit[cTreeMax] = {};
int Decomp::sNextNodeID[cTreeMax] = {};
int Decomp::sStreamByte[cTreeMax] = {};
u32 Decomp::sStreamData[cTreeMax] = {};

DECOMP_FORCEACTIVE(eggDecomp_cpp,
                  "eggDecomp.cpp",
                  "!sWorkArea");

int Decomp::decode(u8* pSrc, u8* pDst) {
    switch (checkCompressed(pSrc)) {
    case cCompress_SZS: {
        return decodeSZS(pSrc, pDst);
    }

    case cCompress_ASH: {
        return decodeASH(pSrc, pDst);
    }

    case cCompress_ASR: {
        return decodeASR(pSrc, pDst);
    }

    default: {
        return -1;
    }
    }
}

int Decomp::decodeSZS(u8* pSrc, u8* pDst) {
    int expandSize = pSrc[4] << 24 | pSrc[5] << 16 | pSrc[6] << 8 | pSrc[7];
    int srcIdx = 0x10; // Skip header
    u8 bit = 0;
    u8 chunk;

    for (int dstIdx = 0; dstIdx < expandSize; bit >>= 1) {
        // Refresh code bits
        if (bit == 0) {
            bit = 0b10000000;
            chunk = pSrc[srcIdx++];
        }

        // Literal (chunk bit is set)
        if (chunk & bit) {
            pDst[dstIdx++] = pSrc[srcIdx++];
        }
        // Back-reference (chunk bit is not set)
        else {
            // Next bytes contain run offset, length
            int packed = pSrc[srcIdx] << 8 | pSrc[srcIdx + 1];
            srcIdx += 2;

            /**
             * Short runs (N <= 15 + 2) use two bytes:
             *     NF FF (N=size, F=offset)
             * Minimum run size is 2 (overhead)
             *
             * Long runs (N <= 255 + 3) use three bytes:
             *     0F FF NN (N=size, F=offset)
             * Minimum run size is 0xF (max short run) + 3 (overhead)
             */
            int runIdx = dstIdx - (packed & 0x0FFF);
            int runLen = (packed >> 12) == 0
                             ? pSrc[srcIdx++] + 0xF + 3 // Long run
                             : (packed >> 12) + 2;      // Short run

            for (; runLen > 0; runLen--, dstIdx++, runIdx++) {
                pDst[dstIdx] = pDst[runIdx - 1];
            }
        }
    }

    return expandSize;
}

int Decomp::decodeASH(u8* pSrc, u8* pDst) {
#line 190
    EGG_ASSERT(sWorkArea);

    int root9, root12;
    int node12, node9;

    u16 *pLeft9, *pRight9;
    u16 *pLeft12, *pRight12;
    u16* pStack;

    u32 expandSize = pSrc[5] << 16 | pSrc[6] << 8 | pSrc[7];
    u32 backRefOfs = pSrc[8] << 24 | pSrc[9] << 16 | pSrc[10] << 8 | pSrc[11];

    // TODO: what are these sizes
    pLeft9 = reinterpret_cast<u16*>(sWorkArea);
    pRight9 = pLeft9 + 0xFFC / sizeof(u16);
    pLeft12 = pRight9 + 0xFFC / sizeof(u16);
    pRight12 = pLeft12 + 0x3FFC / sizeof(u16);
    pStack = pRight12 + 0x3FFC / sizeof(u16);

    sStreamByte[cTreeLiteral] = 0xC; // Skip header
    sStreamByte[cTreeBackRef] = backRefOfs;

    sStreamBit[cTreeLiteral] = sStreamBit[cTreeBackRef] = 0;

    sNextNodeID[cTreeLiteral] = cNode9Min;
    sNextNodeID[cTreeBackRef] = cNode12Min;

    getBitsCode(pSrc, 32, cTreeLiteral);
    getBitsCode(pSrc, 32, cTreeBackRef);

    root9 = readTree9(pSrc, pLeft9, pRight9, pStack);
    root12 = readTree12(pSrc, pLeft12, pRight12, pStack);

    int dstIdx = 0;
    while (dstIdx < expandSize) {
        for (node9 = root9; node9 >= cNode9Min;) {
            if (getBit1c(pSrc, cTreeLiteral) != 0) {
                node9 = pRight9[node9];
            } else {
                node9 = pLeft9[node9];
            }
        }

        if (node9 < 0x100) {
            pDst[dstIdx++] = static_cast<u8>(node9);
            continue;
        }

        for (node12 = root12; node12 >= cNode12Min;) {
            if (getBit1c(pSrc, cTreeBackRef) != 0) {
                node12 = pRight12[node12];
            } else {
                node12 = pLeft12[node12];
            }
        }

        int runIdx = dstIdx - node12 - 1;
        node9 -= 253;

        for (; node9 > 0; node9--, dstIdx++, runIdx++) {
            pDst[dstIdx] = pDst[runIdx];
        }
    }

    return dstIdx;
}

// int Decomp::decodeASR(u8* pSrc, u8* pDst) {
//     ;
// }

Decomp::ECompressKind Decomp::checkCompressed(u8* pData) {
    if (pData[0] == 'Y' && pData[1] == 'a' && pData[2] == 'z') {
        return cCompress_SZS;
    }

    if (pData[0] == 'A' && pData[1] == 'S' && pData[2] == 'H') {
        return cCompress_ASH;
    }

    if (pData[0] == 'A' && pData[1] == 'S' && pData[2] == 'R') {
        return cCompress_ASR;
    }

    return cCompress_None;
}

int Decomp::getExpandSize(u8* pData) {
    switch (checkCompressed(pData)) {
    case cCompress_SZS: {
        return pData[4] << 24 | pData[5] << 16 | pData[6] << 8 | pData[7];
    }

    case cCompress_ASH: {
        return pData[5] << 16 | pData[6] << 8 | pData[7];
    }

    case cCompress_ASR: {
        return pData[5] << 16 | pData[6] << 8 | pData[7];
    }

    default: {
        return -1;
    }
    }
}

int Decomp::getBitsCode(u8* pData, int size, int tree) {
    int byteIdx = sStreamByte[tree];
    int bitIdx = sStreamBit[tree];
    u32 bits = sStreamData[tree];

    int code = 0;

    // Read past end of bitstream
    if (bitIdx + size > 32) {
        // Need to refresh bitstream
        u32 newBits = pData[byteIdx + 0] << 24 | pData[byteIdx + 1] << 16 |
                      pData[byteIdx + 2] << 8 | pData[byteIdx + 3];

        // Need to read part of old bits and part of new bits
        int oldPos = 32 - size;
        int newPos = 64 - size - bitIdx;
        code = bits >> oldPos | newBits >> newPos;

        bitIdx += size - 32;

        sStreamData[tree] = newBits << bitIdx;
        sStreamBit[tree] = bitIdx;
        sStreamByte[tree] = byteIdx + sizeof(u32);
    }
    // Read to end of bitstream
    else if (bitIdx + size == 32) {
        code = bits >> 32 - size;

        // Need to refresh bitstream
        sStreamData[tree] = pData[byteIdx + 0] << 24 |
                            pData[byteIdx + 1] << 16 | pData[byteIdx + 2] << 8 |
                            pData[byteIdx + 3];

        sStreamByte[tree] = byteIdx + sizeof(u32);
        sStreamBit[tree] = 0;
    }
    // Read some bits
    else {
        code = bits >> 32 - size;
        sStreamData[tree] = bits << size;
        sStreamBit[tree] = bitIdx + size;
    }

    return code;
}

int Decomp::getBit1c(u8* pData, int tree) {
    int byteIdx = sStreamByte[tree];
    int bitIdx = sStreamBit[tree];
    u32 bits = sStreamData[tree];

    int code = bits >> 31;

    // Read to end of bitstream
    if (bitIdx == 31) {
        // Need to refresh bitstream
        sStreamData[tree] = pData[byteIdx + 0] << 24 |
                            pData[byteIdx + 1] << 16 | pData[byteIdx + 2] << 8 |
                            pData[byteIdx + 3];

        sStreamByte[tree] = byteIdx + sizeof(u32);
        sStreamBit[tree] = 0;
    }
    // Read next bit
    else {
        sStreamData[tree] = bits << 1;
        sStreamBit[tree] = bitIdx + 1;
    }

    return code;
}

int Decomp::readTree9(u8* pData, u16* pLeft, u16* pRight, u16* pStack) {
    u32 index, index2; // ???
    index2 = sNextNodeID[cTreeLiteral];
    index = index2;

    int sp = 0;

    while (true) {
        // Push left/right node to the stack
        if (getBit1c(pData, cTreeLiteral) != 0) {
            pStack[sp] = cNodeRight | index;
            pStack[sp + 1] = cNodeLeft | index;
            index++;
            index2++;

            sp += 2;
#line 620
            EGG_ASSERT(sp < cTreeStackSize);
            continue;
        }

        // Assign value to the previous node
        int code = getBitsCode(pData, 9, cTreeLiteral);

        while (true) {
            // Pop last node from the stack
            u16 node = pStack[--sp];

            if (node & cNodeRight) {
                pRight[node & cNodeIndexMask] = code;
                code = node & cNodeIndexMask;

                if (sp == 0) {
                    // Tree root
                    return code;
                }
            } else /* cNodeLeft */ {
                pLeft[node & cNodeIndexMask] = code;
                index = index2;
                break;
            }
        }
    }
}

int Decomp::readTree12(u8* pData, u16* pLeft, u16* pRight, u16* pStack) {
    u32 index, index2; // ???
    index2 = sNextNodeID[cTreeBackRef];
    index = index2;

    int sp = 0;

    while (true) {
        // Push left/right node to the stack
        if (getBit1c(pData, cTreeBackRef) != 0) {
            pStack[sp] = cNodeRight | index;
            pStack[sp + 1] = cNodeLeft | index;
            index++;
            index2++;

            sp += 2;
#line 668
            EGG_ASSERT(sp < cTreeStackSize);
            continue;
        }

        // Assign value to the previous node
        int code = getBitsCode(pData, 11, cTreeBackRef);

        while (true) {
            // Pop last node from the stack
            u16 node = pStack[--sp];

            if (node & cNodeRight) {
                pRight[node & cNodeIndexMask] = code;
                code = node & cNodeIndexMask;

                if (sp == 0) {
                    // Tree root
                    return code;
                }
            } else /* cNodeLeft */ {
                pLeft[node & cNodeIndexMask] = code;
                index = index2;
                break;
            }
        }
    }
}

} // namespace EGG
