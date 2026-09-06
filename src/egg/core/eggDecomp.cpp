// TODO(kiwi) REMOVE AFTER REFACTOR
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

    // TODO(kiwi) what are these sizes
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

int Decomp::decodeASR(u8* in, u8* out) {
#line 277
    EGG_ASSERT(sWorkArea);

    int model_index;
    int symbol;
    u32 literal_code;
    u32 dist_code;
    u32 step;
    int target_size;
    int dist_in_pos;
    int copy_src;
    int literal_in_pos;
    int out_pos;
    u32 literal_range;
    u32 range_adjust;
    int low_bound;
    int high_bound;
    u32* count9;
    u32* countsum9;
    u32* count11;
    u32* countsum11;
    u32 dist_range;
    u32 literal_low;
    u32 dist_low;
    int i;
    int j;
    int dist_model_size;
    u32 scaled_value;

    target_size = (in[5] << 16) | (in[6] << 8) | in[7];
    dist_in_pos = (in[8] << 24) | (in[9] << 16) | (in[10] << 8) | in[11];
    dist_model_size = (in[4] & 0x80) ? 0x1000 : 0x200;
    literal_range = 0xFFFFFFFF;
    dist_range = 0xFFFFFFFF;
    literal_low = 0;
    dist_low = 0;

    count9 = reinterpret_cast<u32*>(sWorkArea);
    countsum9 = count9 + 0x200;
    count11 = countsum9 + 0x201;
    countsum11 = count11 + 0x1000;

    countsum9[0] = countsum11[0] = 0;

    for (i = 0; i < 0x200; i++) {
        count9[i] = 1;
        countsum9[i + 1] = countsum9[i] + 1;
    }

    for (i = 0; i < dist_model_size; i++) {
        count11[i] = 1;
        countsum11[i + 1] = countsum11[i] + 1;
    }

    out_pos = 0;
    literal_in_pos = 0x10;
    literal_code = (in[12] << 24) | (in[13] << 16) | (in[14] << 8) | in[15];
    dist_code = (in[dist_in_pos] << 24) | (in[dist_in_pos + 1] << 16) |
                (in[dist_in_pos + 2] << 8) | in[dist_in_pos + 3];
    dist_in_pos += 4;

    while (out_pos < target_size) {
        step = literal_range / countsum9[0x200];
        scaled_value = (literal_code - literal_low) / step;
        low_bound = 0;
        high_bound = 0x200;

        while (low_bound < high_bound) {
            model_index = (low_bound + high_bound) >> 1;
            if (scaled_value < countsum9[model_index]) {
                high_bound = model_index;
            } else {
                low_bound = model_index + 1;
            }
        }

        while (model_index >= 0) {
            if ((countsum9[model_index] <= scaled_value) &&
                (scaled_value < countsum9[model_index + 1]))
                break;
            model_index--;
        }
        symbol = model_index;

        literal_low += step * countsum9[symbol];
        literal_range = step * count9[symbol];
        count9[symbol]++;

        while (++model_index <= 0x200) {
            countsum9[model_index]++;
        }

        if (countsum9[0x200] >= 0x10000) {
            countsum9[0] = 0;
            for (j = 0; j < 0x200; j++) {
                count9[j] = (count9[j] >> 1) | 1;
                countsum9[j + 1] = countsum9[j] + count9[j];
            }
        }

        while ((literal_low & 0xFF000000) ==
               ((literal_low + literal_range) & 0xFF000000)) {
            literal_low <<= 8;
            literal_range <<= 8;
            literal_code = in[literal_in_pos++] + (literal_code << 8);
        }
        while (literal_range < 0x10000) {
            range_adjust = 0x10000 - (literal_low & 0xFFFF);
            literal_range = range_adjust << 8;
            literal_low <<= 8;
            literal_code = in[literal_in_pos++] + (literal_code << 8);
        }

        if (symbol < 0x100) {
            out[out_pos++] = (u8)symbol;
            continue;
        }

        step = dist_range / countsum11[dist_model_size];
        scaled_value = (dist_code - dist_low) / step;
        low_bound = 0;
        high_bound = dist_model_size;

        while (low_bound < high_bound) {
            model_index = (low_bound + high_bound) >> 1;
            if (scaled_value < countsum11[model_index]) {
                high_bound = model_index;
            } else {
                low_bound = model_index + 1;
            }
        }

        while (model_index >= 0) {
            if ((countsum11[model_index] <= scaled_value) &&
                (scaled_value < countsum11[model_index + 1]))
                break;
            model_index--;
        }

        copy_src = out_pos - model_index - 1;
        symbol -= 0xFD;
        while (symbol > 0) {
            out[out_pos] = out[copy_src++];
            symbol--;
            out_pos++;
        }

        dist_low += step * countsum11[model_index];
        dist_range = step * count11[model_index];
        count11[model_index]++;

        while (++model_index <= dist_model_size) {
            countsum11[model_index]++;
        }

        if (countsum11[dist_model_size] >= 0x10000) {
            countsum11[0] = 0;
            for (j = 0; j < dist_model_size; j++) {
                count11[j] = (count11[j] >> 1) | 1;
                countsum11[j + 1] = countsum11[j] + count11[j];
            }
        }

        while ((dist_low & 0xFF000000) ==
               ((dist_low + dist_range) & 0xFF000000)) {
            dist_low <<= 8;
            dist_range <<= 8;
            dist_code = in[dist_in_pos++] + (dist_code << 8);
        }

        while (dist_range < 0x10000) {
            range_adjust = 0x10000 - (dist_low & 0xFFFF);
            dist_range = range_adjust << 8;
            dist_low <<= 8;
            dist_code = in[dist_in_pos++] + (dist_code << 8);
        }
    }

    return out_pos;
}

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
        code = bits >> (32 - size);

        // Need to refresh bitstream
        sStreamData[tree] = pData[byteIdx + 0] << 24 |
                            pData[byteIdx + 1] << 16 | pData[byteIdx + 2] << 8 |
                            pData[byteIdx + 3];

        sStreamByte[tree] = byteIdx + sizeof(u32);
        sStreamBit[tree] = 0;
    }
    // Read some bits
    else {
        code = bits >> (32 - size);
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
