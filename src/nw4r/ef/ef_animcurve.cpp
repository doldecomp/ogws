#include <nw4r/ef.h>
#include <nw4r/math.h>
#include <nw4r/ut.h>

#include <cmath>

namespace nw4r {
namespace ef {

inline void getAnimHeaders(u8* header, AnimCurveHeader** pHeader, AnimCurveKey** pKey, AnimCurveRandom** pRandom, AnimCurveRandomTable** pRandomTable, AnimCurveNameTable** pNameTable) {
	*pHeader = reinterpret_cast<AnimCurveHeader*>(header);
	*pKey = reinterpret_cast<AnimCurveKey*>(reinterpret_cast<u8*>(*pHeader) + sizeof(AnimCurveHeader));
	*pRandom = reinterpret_cast<AnimCurveRandom*>(reinterpret_cast<u8*>(*pKey) + (*pHeader)->keyTable);
	*pRandomTable = reinterpret_cast<AnimCurveRandomTable*>(reinterpret_cast<u8*>(*pRandom) + (*pHeader)->rangeTable);
	*pNameTable = reinterpret_cast<AnimCurveNameTable*>(reinterpret_cast<u8*>(*pRandomTable) + (*pHeader)->randomTable);
}

inline void calcTick(u32 life, const AnimCurveHeader* pHeader, u32 origTick, u16* pTick, f32* pTickF32, u32* pDiv) {
	*pDiv = 0;
	
	if (pHeader->frameLength <= 1) {
		*pTick = 0;
		*pTickF32 = 0.0f;
		*pDiv = origTick;
		return;
	}
	
	if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_INFLOOP) && pHeader->loopCount <= 1) {
		if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_FITTING)) {
			*pTick = origTick >= pHeader->frameLength - 1 ? static_cast<u16>(pHeader->frameLength - 1) : static_cast<u16>(origTick);
			*pTickF32 = *pTick;
			return;
		}
		*pTickF32 = origTick;
		*pTickF32 *= static_cast<f32>(pHeader->frameLength - 1) / (life - 1);
		if (*pTickF32 > pHeader->frameLength - 1) {
			*pTickF32 = pHeader->frameLength - 1;
		}
		*pTick = *pTickF32;
	} else {
		if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_FITTING)) {
			u32 div = origTick / (pHeader->frameLength - 1);
			if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_TURN)) {
				if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_INFLOOP) && div >= pHeader->loopCount) {
					*pTick = pHeader->frameLength - 1;
					*pDiv = static_cast<u16>(pHeader->loopCount - 1);
				} else {
					*pTick = origTick - div * (pHeader->frameLength - 1);
					*pDiv = div;
				}
			} else {
				if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_INFLOOP) && div >= pHeader->loopCount) {
					*pTick = (pHeader->loopCount % 2 == 0) ? static_cast<u16>(0) : static_cast<u16>(pHeader->frameLength - 1);
					*pDiv = static_cast<u16>(pHeader->loopCount - 1);
				} else if (div % 2 == 0) {
					*pTick = origTick - div * (pHeader->frameLength - 1);
					*pDiv = div;
				} else {
					*pTick = (pHeader->frameLength - 1) * (div + 1) - origTick;
					*pDiv = div;
				}
			}
			*pTickF32 = *pTick;
		} else if (origTick >= life - 1) {
			if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_TURN) || pHeader->loopCount % 2 != 0) {
				*pTick = origTick - 1;
			} else {
				*pTick = 0;
			}
			*pDiv = static_cast<u16>(pHeader->loopCount - 1);
			*pTickF32 = *pTick;
		} else {
			f32 rate = pHeader->loopCount * (static_cast<f32>(pHeader->frameLength - 1) / (life - 1));
			u32 div = origTick * rate / (pHeader->frameLength - 1);
			*pTick = div * (pHeader->frameLength - 1);
			*pDiv = div;
			f32 pos = origTick * rate - div * (pHeader->frameLength - 1);
			if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_TURN)) {
				*pTickF32 = pos;
			} else if (div % 2 == 0) {
				*pTickF32 = pos;
			} else {
				*pTickF32 = (pHeader->frameLength - 1) - pos;
			}
			*pTick = *pTickF32;
		}
	}
}

inline void searchKey(int& rFrameIdx, bool& rOnKey, u16& rLoFrame, u16& rHiFrame, int tick, f32 tickF32, u8* ptrBase, int framesize, int start, int end) {
	int lo = start;
	int hi = end;
	int md = (start + end) / 2;
	bool isInt = std::fabsf(tick - tickF32) < NW4R_MATH_FLT_EPSILON;
	
	rLoFrame = *reinterpret_cast<u16*>(ptrBase + lo * framesize);
	if (tick < rLoFrame) {
		rFrameIdx = lo;
		rOnKey = true;
		return;
	}
	if (tick == rLoFrame) {
		rFrameIdx = lo;
		if (lo == end) {
			rOnKey = true;
		} else {
			rOnKey = isInt;
			if (!rOnKey) {
				rHiFrame = *reinterpret_cast<u16*>(ptrBase + (lo + 1) * framesize);
			}
		}
		return;
	}
	rHiFrame = *reinterpret_cast<u16*>(ptrBase + hi * framesize);
	if (rHiFrame <= tick) {
		rFrameIdx = hi;
		rOnKey = true;
		return;
	}
	u16 mdFrame = *reinterpret_cast<u16*>(ptrBase + md * framesize);
	while (lo < md) {
		if (tick == mdFrame) {
			rFrameIdx = md;
			rOnKey = isInt;
			if (!rOnKey) {
				rLoFrame = mdFrame;
				rHiFrame = *reinterpret_cast<u16*>(ptrBase + (rFrameIdx + 1) * framesize);
			}
			return;
		}
		if (mdFrame < tick) {
			lo = md;
			rLoFrame = mdFrame;
		} else {
			hi = md;
			rHiFrame = mdFrame;
		}
		md = (lo + hi) / 2;
		mdFrame = *reinterpret_cast<u16*>(ptrBase + md * framesize);
	}
	rFrameIdx = lo;
	rOnKey = false;
}

inline void CalcTurnDiv(const AnimCurveHeader* pHeader, const AnimCurveKey* pKey, int frameIdx, u32* pDivL, u32* pDivH) {
	*pDivH = *pDivL;
	if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_TURN)) {
		return;
	}
	if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_INFLOOP) && pHeader->loopCount <= 1) {
		return;
	}
	if (*pDivL % 2 == 0 && frameIdx + 1 >= pKey->count - 1 && ((pHeader->processFlag & AnimCurveHeader::PROC_FLAG_INFLOOP) || pHeader->loopCount < *pDivL - 1)) {
		++*pDivH;
	}
	if (*pDivL % 2 != 0 && frameIdx == 0 && *pDivL > 0 /* redundant since every unsigned odd integer is positive */) {
		++*pDivL;
	}
}

inline u8 AnimCurveInterpHermite(u32 posF, u8 valL, u8 valH, u8 type) {
	switch (type & 0x3 /* magic number */) {
	case 0 /* magic number (linear) */: {
		return valL + (posF * (valH - valL) >> 0x10);
	}
	case 1 /* magic number (Hermite) */: {
		f32 p = posF;
		p = p / 0x10000;
		if (type == 1 /* magic number */) {
			return valL + (valH - valL) * (3.0f - 2.0f * p) * p * p;
		}
		f32 p1 = !((type >> 2 /* magic number (derivative at valH) */) & 1) ? 0.0f : 1.5f;
		f32 p2 = !((type >> 3 /* magic number (derivative at valL) */) & 1) ? 0.0f : 1.5f;
		f32 result = valL + (valH - valL) * p * ((p2 + p1 - 2.0f) * p * p + (-2.0f * p2 - p1 + 3.0f) * p + p2);
		if (result < 0) {
			return 0;
		}
		if (result > 0xFF) {
			return 0xFF;
		}
		return result;
	}
	case 2 /* magic number (piecewise constant/last keyframe?) */: {
		return valL;
	}
	}
	return 0;
}

void AnimCurveExecuteU8(u8* pCmdList, u8* pTarget, u32 origTick, u16 seed,
                        u32 life) {
	u8 enableFlag = pCmdList[3];
	u32 i;
	u8 mask;
	
	for (i = 8, mask = 0x80; mask; mask >>= 1, i--) {
		if (enableFlag & mask) {
			break;
		}
	}
	if (i == 0) {
		return;
	}
	
	int framesize = (i + 0xC + 1) & ~0x1;
	
	AnimCurveHeader* pHeader;
	AnimCurveKey* pKey;
	AnimCurveRandom* pRandom;
	AnimCurveRandomTable* pRandomTable;
	AnimCurveNameTable* pNameTable;
	getAnimHeaders(pCmdList, &pHeader, &pKey, &pRandom, &pRandomTable, &pNameTable);
	
	const int RNDRANGE_SIZE = i * 2;
	const int RNDSET_SIZE = i * 2;
	
	f32 tickF32;
	u16 tick;
	u32 divL;
	calcTick(life, pHeader, origTick, &tick, &tickF32, &divL);
	u32 divH = divL;
	u8* ptrBase = pKey->datas;
	int frameIdx;
	bool onKey;
	u16 loFrame;
	u16 hiFrame;
	searchKey(frameIdx, onKey, loFrame, hiFrame, tick, tickF32, ptrBase, framesize, 0, pKey->count - 1);
	
	if (onKey) {
		u8* ptrFixed = ptrBase + frameIdx * framesize + 0xC;
		if (!*(ptrFixed - 0xC + 0x2)) {
			for (; mask; pTarget++, mask >>= 1) {
				if (enableFlag & mask) {
					*pTarget = *ptrFixed++;
				}
			}
		} else {
			u16 randIdx = *reinterpret_cast<u16*>(ptrFixed);
			u32 rand = RANDOM_INIT(seed, pHeader->randomSeed, randIdx, divL);
			u8* tbl;
			int val;
			if (!(*(ptrFixed - 0xC + 0x2) & 2)) {
				tbl = pKey->datas + randIdx * RNDRANGE_SIZE;
			} else {
				tbl = pRandomTable->datas + (rand >> 0x10) % pRandomTable->count * RNDSET_SIZE;
				rand = RANDOM_NEXT(rand);
			}
			for (; mask; pTarget++, mask >>= 1) {
				if (enableFlag & mask) {
					val = *tbl++;
					val += *tbl++ * (s16)(rand >> 0x10) / 0x8000;
					if (val < 0) {
						val = 0;
					}
					if (val > 0xFF) {
						val = 0xFF;
					}
					if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_SYNC)) {
						rand = RANDOM_NEXT(rand);
					}
					*pTarget = val;
				}
			}
		}
	} else {
		CalcTurnDiv(pHeader, pKey, frameIdx, &divL, &divH);
		u32 posF = (tickF32 - loFrame) * 0x10000;
		posF /= hiFrame - loFrame;
		u8* ptrL_ = ptrBase + frameIdx * framesize;
		u8* ptrL = ptrBase + frameIdx * framesize + 0xC;
		u8* ptrH = ptrBase + (frameIdx + 1) * framesize + 0xC;
		u8* pType = ptrBase + frameIdx * framesize + 0x4;
		bool isRandL = *(ptrL - 0xC + 0x2);
		bool isRandH = *(ptrH - 0xC + 0x2);
		if (!isRandL && !isRandH) {
			for (; mask; pTarget++, mask >>= 1) {
				if (enableFlag & mask) {
					if (*ptrL == *ptrH) {
						*pTarget = *ptrL;
					} else {
						*pTarget = AnimCurveInterpHermite(posF, *ptrL, *ptrH, *pType);
					}
					ptrL++;
					ptrH++;
				}
				pType++;
			}
		} else if (isRandL && !isRandH) {
			u16 randIdx = *reinterpret_cast<u16*>(ptrL);
			u32 rand = RANDOM_INIT(seed, pHeader->randomSeed, randIdx, divL);
			u8* tbl;
			int val;
			if (!(*(ptrL - 0xC + 0x2) & 2)) {
				tbl = pKey->datas + randIdx * RNDRANGE_SIZE;
			} else {
				tbl = pRandomTable->datas + (rand >> 0x10) % pRandomTable->count * RNDSET_SIZE;
				rand = RANDOM_NEXT(rand);
			}
			for (; mask; pTarget++, mask >>= 1) {
				if (enableFlag & mask) {
					val = *tbl++;
					val += *tbl++ * (s16)(rand >> 0x10) / 0x8000;
					if (val < 0) {
						val = 0;
					}
					if (val > 0xFF) {
						val = 0xFF;
					}
					if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_SYNC)) {
						rand = RANDOM_NEXT(rand);
					}
					*pTarget = AnimCurveInterpHermite(posF, val, *ptrH, *pType);
					ptrL++;
					ptrH++;
				}
				pType++;
			}
		} else if (!isRandL && isRandH) {
			u16 randIdx = *reinterpret_cast<u16*>(ptrH);
			u32 rand = RANDOM_INIT(seed, pHeader->randomSeed, randIdx, divH);
			u8* tbl;
			int val;
			if (!(*(ptrH - 0xC + 0x2) & 2)) {
				tbl = pKey->datas + randIdx * RNDRANGE_SIZE;
			} else {
				tbl = pRandomTable->datas + (rand >> 0x10) % pRandomTable->count * RNDSET_SIZE;
				rand = RANDOM_NEXT(rand);
			}
			for (; mask; pTarget++, mask >>= 1) {
				if (enableFlag & mask) {
					val = *tbl++;
					val += *tbl++ * (s16)(rand >> 0x10) / 0x8000;
					if (val < 0) {
						val = 0;
					}
					if (val > 0xFF) {
						val = 0xFF;
					}
					if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_SYNC)) {
						rand = RANDOM_NEXT(rand);
					}
					*pTarget = AnimCurveInterpHermite(posF, *ptrL, val, *pType);
					ptrL++;
					ptrH++;
				}
				pType++;
			}
		} else {
			u16 randIdx;
			randIdx = *reinterpret_cast<u16*>(ptrL);
			u32 randL = RANDOM_INIT(seed, pHeader->randomSeed, randIdx, divL);
			u8* tblL;
			if (!(*(ptrL - 0xC + 0x2) & 2)) {
				tblL = pKey->datas + randIdx * RNDRANGE_SIZE;
			} else {
				tblL = pRandomTable->datas + (randL >> 0x10) % pRandomTable->count * RNDSET_SIZE;
				randL = RANDOM_NEXT(randL);
			}
			randIdx = *reinterpret_cast<u16*>(ptrH);
			u32 randH = RANDOM_INIT(seed, pHeader->randomSeed, randIdx, divH);
			u8* tblH;
			if (!(*(ptrH - 0xC + 0x2) & 2)) {
				tblH = pKey->datas + randIdx * RNDRANGE_SIZE;
			} else {
				tblH = pRandomTable->datas + (randH >> 0x10) % pRandomTable->count * RNDSET_SIZE;
				randH = RANDOM_NEXT(randH);
			}
			int valL;
			int valH;
			for (; mask; pTarget++, mask >>= 1) {
				if (enableFlag & mask) {
					valL = *tblL++;
					valL += *tblL++ * (s16)(randL >> 0x10) / 0x8000;
					if (valL < 0) {
						valL = 0;
					}
					if (valL > 0xFF) {
						valL = 0xFF;
					}
					if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_SYNC)) {
						randL = RANDOM_NEXT(randL);
					}
					valH = *tblH++;
					valH += *tblH++ * (s16)(randH >> 0x10) / 0x8000;
					if (valH < 0) {
						valH = 0;
					}
					if (valH > 0xFF) {
						valH = 0xFF;
					}
					if (!(pHeader->processFlag & AnimCurveHeader::PROC_FLAG_SYNC)) {
						randH = RANDOM_NEXT(randH);
					}
					*pTarget = AnimCurveInterpHermite(posF, valL, valH, *pType);
					ptrL++;
					ptrH++;
				}
				pType++;
			}
		}
	}
}

void AnimCurveExecuteF32(u8* pCmdList, f32* pTarget, u32 tick, u16 seed,
                         u32 life);

void AnimCurveExecuteRotate(u8* pCmdList, f32* pTarget, u32 tick, u16 seed,
                            u32 life);

void AnimCurveExecuteTexture(u8* pCmdList, Particle* pParticle, u32 tick,
                             u16 seed, u32 life);

void AnimCurveExecuteChild(u8* pCmdList, Particle* pParticle, u32 tick,
                           u16 seed, u32 life);

} // namespace ef
} // namespace nw4r
