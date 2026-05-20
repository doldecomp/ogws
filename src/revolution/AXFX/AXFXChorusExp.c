#include <revolution/AXFX.h>
#include <revolution/OS.h>

#include <string.h>

void dummy(u32 zero, ...);

static BOOL __InitParams(AXFX_CHORUS_EXP* fx);
static BOOL __AllocDelay(AXFX_CHORUS_EXP* fx);
static BOOL __InitDelay(AXFX_CHORUS_EXP* fx);
static void __FreeDelay(AXFX_CHORUS_EXP* fx);
static void __CalcLFO(u32 param_1[], AXFX_CHORUS_EXP_LFO* fx);

u32 AXFXChorusExpGetMemSize(const AXFX_CHORUS_EXP* fx) {
    return 0x9600;
}

BOOL AXFXChorusExpInit(AXFX_CHORUS_EXP* fx) {
    BOOL enabled;

    enabled = OSDisableInterrupts();
    fx->active |= 1;
    (fx->delay).size = 0xc80;

    if (!__AllocDelay(fx)) {
        AXFXChorusExpShutdown(fx);
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    if (!__InitDelay(fx)) {
        AXFXChorusExpShutdown(fx);
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    if (!__InitParams(fx)) {
        AXFXChorusExpShutdown(fx);
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    fx->active &= ~1;
    OSRestoreInterrupts(enabled);

    return TRUE;
}

BOOL AXFXChorusExpSettings(AXFX_CHORUS_EXP* fx) {
    BOOL enabled;
    BOOL success;

    enabled = OSDisableInterrupts();
    fx->active |= TRUE;
    AXFXChorusExpShutdown(fx);

    success = AXFXChorusExpInit(fx);

    if (success == FALSE) {
        AXFXChorusExpShutdown(fx);
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    fx->active |= 2;
    fx->active &= ~1;
    OSRestoreInterrupts(enabled);

    return success;
}

void AXFXChorusExpShutdown(AXFX_CHORUS_EXP* fx) {
    BOOL enabled;

    enabled = OSDisableInterrupts();

    __FreeDelay(fx);

    OSRestoreInterrupts(enabled);
}

// Non-matching
void AXFXChorusExpCallback(AXFX_BUFFERUPDATE* bufferUpdate,
                           AXFX_CHORUS_EXP* fx) {

    int iVar1;
    f32 fVar2;
    u32 uVar3;
    s32 c;
    f32* pfVar4;
    u32 uVar4;
    u32 uVar5;
    u32 outPos;
    s32 size;
    AXFX_CHORUS_EXP* pAVar6;
    s32** ppsVar7;
    AXFX_BUS* busOut;
    s32 currentPos;
    s32** ppsVar8;
    AXFX_BUS* busIn;
    AXFX_CHORUS_EXP* pAVar9;
    s32** ppsVar10;
    u32 uVar11;
    s32* piVar12;
    f32* pfVar13;
    u32 samp;
    u32* ptr;
    u32 i;
    int ch;
    f32 dVar16;
    f32 dVar14;
    s32* input[3];
    s32* inBusData[3];
    s32* outBusData[3];
    u32 lfo[96];

    if (fx->active != 0) {
        fx->active &= ~2;
        return;
    }

    busIn = fx->busIn;
    input[0] = bufferUpdate->left;
    input[1] = bufferUpdate->right;
    input[2] = bufferUpdate->surround;
    if (busIn != NULL) {
        inBusData[0] = busIn->left;
        inBusData[1] = busIn->right;
        inBusData[2] = busIn->surround;
    }
    busOut = fx->busOut;
    if (busOut != NULL) {
        outBusData[0] = busOut->left;
        outBusData[1] = busOut->right;
        outBusData[2] = busOut->surround;
    }
    __CalcLFO(lfo, &fx->lfo);
    ptr = lfo;
    for (samp = 0; samp < 96; samp++) {
        size = (fx->delay).sizeFP;
        currentPos = (fx->delay).outPos + *ptr;
        if (currentPos >= size) {
            currentPos = currentPos - size;
        } else {
            if (currentPos < 0) {
                currentPos = currentPos + size;
            }
        }
        outPos = (fx->delay).lastPos;
        c = currentPos - outPos;
        if (c < 0) {
            c = c + size;
        }

        uVar11 = outPos / 65536;
        outPos = fx->histIndex;
        for (i = (u32)c / 65536; i != 0; i--) {
            fx->history[0][outPos] = (fx->delay).line[0][uVar11];
            fx->history[1][outPos] = (fx->delay).line[1][uVar11];
            fx->history[2][outPos] = (fx->delay).line[2][uVar11];

            uVar11++;

            outPos += 1;
            outPos = outPos & 3;

            if (uVar11 >= (fx->delay).size) {
                uVar11 = 0;
            }
        }
        (fx->delay).lastPos = currentPos & 0xffff0000;
        pfVar4 = __AXFXGetSrcCoef((c & 0xffffU) >> 9);
        ppsVar7 = inBusData;
        ppsVar8 = input;
        ppsVar10 = outBusData;
        pAVar6 = fx;
        pAVar9 = fx;
        for (ch = 3; ch != 0; ch--) {
            i = outPos + 1 & 3;
            pfVar13 = pAVar6->history[0] + outPos;
            uVar5 = i + 1 & 3;
            uVar11 = uVar5 + 1 & 3;
            outPos = uVar11 + 1 & 3;
            dVar14 = (f32)(*pfVar4 * *pfVar13 + 0.0 +
                           pfVar4[1] * pAVar6->history[0][i] +
                           pfVar4[2] * pAVar6->history[0][uVar5] +
                           pfVar4[3] * pAVar6->history[0][uVar11]);

            if (fx->busIn != NULL) {
                u32 sum = **ppsVar8 + **ppsVar7;

                (*ppsVar7)++;

                dVar16 = (double)(sum);
            } else {
                dVar16 = (double)(**ppsVar8);
            }
            uVar3 = (fx->delay).inPos;
            pfVar13 = (pAVar9->delay).line[0];
            piVar12 = *ppsVar8;
            *ppsVar8 = (s32*)(piVar12 + 1);

            iVar1 = (dVar14 * fx->outGain);
            *piVar12 = iVar1;
            if (fx->busOut != NULL) {
                fVar2 = fx->sendGain;
                piVar12 = *ppsVar10;
                *ppsVar10 = piVar12 + 1;
                iVar1 = (int)((f32)dVar14 * fVar2);
                *piVar12 = iVar1;
            }
            pAVar6 = (AXFX_CHORUS_EXP*)&(pAVar6->delay).outPos;
            ppsVar7++;
            ppsVar8++;
            ppsVar10++;
            pAVar9 = (AXFX_CHORUS_EXP*)((pAVar9->delay).line + 1);
        }
        i = (fx->delay).size;
        uVar5 = (fx->delay).inPos + 1;
        fx->histIndex = outPos;
        (fx->delay).inPos = uVar5;
        if (i >= uVar5) {
            (fx->delay).inPos = 0;
        }
        outPos = (fx->delay).outPos + 0x10000;
        (fx->delay).outPos = outPos;
        if ((fx->delay).sizeFP >= outPos) {
            (fx->delay).outPos = 0;
        }
        ptr = ptr + 1;
    }

    return;
}

static BOOL __AllocDelay(AXFX_CHORUS_EXP* fx) {
    f32** line = fx->delay.line;
    u32 i;

    for (i = 0; i < 3; i++, line++) {
        *line = __AXFXAlloc(fx->delay.size * sizeof(f32));
        if (*line == NULL) {
            return FALSE;
        }
    }

    return TRUE;
}

static BOOL __InitDelay(AXFX_CHORUS_EXP* fx) {
    f32** line = fx->delay.line;
    u32 i;
    u32 uVar2;

    for (i = 0; i < 3; i++, line++) {
        if (*line == NULL) {
            return FALSE;
        }

        memset(*line, 0, (fx->delay).size * sizeof(f32));
    }

    (fx->delay).inPos = 0;
    uVar2 = (u32)(fx->delayTime * 32.0f);
    uVar2 = ((fx->delay).size - uVar2) * 0x10000;
    (fx->delay).sizeFP = (fx->delay).size << 0x10;
    (fx->delay).outPos = uVar2;
    (fx->delay).lastPos = uVar2;

    return TRUE;
}

static void __FreeDelay(AXFX_CHORUS_EXP* fx) {
    u32 i;

    fx->active |= TRUE;
    for (i = 0; i < 3; i++) {
        if (fx->delay.line[i] != NULL) {
            __AXFXFree(fx->delay.line[i]);
        }
        fx->delay.line[i] = NULL;
    }
}

static BOOL __InitParams(AXFX_CHORUS_EXP* fx) {
    s32 j;
    s32 i;
    s32* table;

    s32 phaseAdd;
    s32 tempSamp;
    f32 gradFactor;
    f32 depthSamp;
    f32 tempVal;
    f32 stepSamp;

    if ((fx->delayTime < 0.1f) || (fx->delayTime > 50.0f)) {
        return FALSE;
    }
    if ((fx->depth < 0.0f) || (fx->depth > 1.0f)) {
        return FALSE;
    }
    if ((fx->rate < 0.1f) || (fx->rate > 2.0f)) {
        return FALSE;
    }
    if ((fx->feedback < 0.0f) || (fx->feedback >= 1.0f)) {
        return FALSE;
    }
    if ((fx->outGain < 0.0f) || (fx->outGain > 1.0f)) {
        return FALSE;
    }
    if ((fx->sendGain < 0.0f) || (fx->sendGain > 1.0f)) {
        return FALSE;
    }
    table = __AXFXGetLfoSinTable();
    fx->lfo.table = table;

    depthSamp = 32.0f * fx->delayTime * fx->depth;
    if (depthSamp >= 32.0f * fx->delayTime) {
        depthSamp -= 1.0f;
        if (depthSamp < 0.0f) {
            depthSamp = 0.0f;
        }
    }

    fx->lfo.lastNum = -1;
    fx->lfo.phase = 0;
    fx->lfo.sign = 0;

    tempSamp = (s32)(65536.0f * depthSamp);
    fx->lfo.depthSamp = tempSamp;

    fx->lfo.grad = fx->lfo.lastValue = 0;

    phaseAdd = (s32)(65536.0f * (((tempVal = 256.0f) * fx->rate) / 32000.0f));
    fx->lfo.phaseAdd = phaseAdd;

    stepSamp = (1.25f / 320) * (32000 / fx->rate);
    gradFactor = depthSamp / stepSamp;

    tempSamp = (s32)(65536.0f * stepSamp);
    fx->lfo.stepSamp = tempSamp;

    fx->lfo.gradFactor = (s32)(65536.0f * gradFactor);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            fx->history[i][j] = 0.0f;
        }
    }

    fx->histIndex = 0;

    return TRUE;
}

void __CalcLFO(u32* out, AXFX_CHORUS_EXP_LFO* lfo) {
    u32 samp;
    u32 lastNum;
    s32 tableVal;
    s64 value;
    u64 diff;
    s32 wtf;

    for (samp = 0x60; samp != 0; samp--) {
        lastNum = lfo->phase & 0xFFFF0000;
        if (lastNum != lfo->lastNum) {
            lfo->lastNum = lastNum;
            lastNum = lastNum >> 16;
            tableVal = lfo->table[lastNum];
            diff = lfo->table[(lastNum + (wtf = 1)) & 0x7F] - tableVal;
            lfo->grad = (s32)((((s64)diff) * (lfo->gradFactor)) >> 24);
            value = (((s64)tableVal) * lfo->depthSamp) >> 24;
        } else {
            value = (s64)(lfo->lastValue + lfo->grad);
        }

        lfo->lastValue = (s32)value;
        if (lfo->sign >= 1) {
            value = -value;
        }

        lfo->phase += lfo->phaseAdd;
        if ((lfo->phase & 0xFF800000) != 0) {
            lfo->phase &= 0x7FFFFF;
            lfo->sign ^= wtf;
        }
        *(out++) = (u32)value;
    }
}
