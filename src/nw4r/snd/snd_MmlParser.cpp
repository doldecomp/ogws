#include <OSError.h>
#include "ut_algorithm.h"
#include "snd_MmlParser.h"
#include "snd_SeqPlayer.h"
#include "snd_Util.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		namespace detail
		{
			using namespace Util;
			
			u16 MmlParser::Read16(const u8 ** pPointer) const
			{
				u16 val = ReadByte(pPointer);
				
				val <<= 8;
				val |= ReadByte(pPointer);
				
				return val;
			}
			
			u32 MmlParser::Read24(const u8 ** pPointer) const
			{
				u32 val = ReadByte(pPointer);
				
				val <<= 8;
				val |= ReadByte(pPointer);
				
				val <<= 8;
				val |= ReadByte(pPointer);
				
				return val;
			}
			
			u32 MmlParser::ReadVar(const u8 ** pPointer) const
			{
				u8 curByte;
				u32 val = 0;
				
				do
				{
					curByte = ReadByte(pPointer);
					val <<= 7;
					val |= curByte & 0x7F;
				} while (curByte & 0x80);
				
				return val;
			}
			
			volatile s16 * MmlParser::GetVariablePtr(SeqPlayer * pPlayer, SeqTrack * pTrack, int i) const
			{
				if (i < SEQ_VARIABLE_COUNT * 2) return pPlayer->GetVariablePtr(i);
				
				if (i < SEQ_VARIABLE_COUNT * 3) return pTrack->GetVariablePtr(i - SEQ_VARIABLE_COUNT * 2);
				
				return NULL;
			}
			
			UNKWORD MmlParser::Parse(MmlSeqTrack * pTrack, bool r29_5) const
			{
				//r28 (r4) <- pTrack
				//r27 (r3) <- this
				SeqPlayer * pPlayer = pTrack->mPlayer; // at r9
				bool r5 = false;
				bool r31 = true;
				u32 r30 = ReadByte(&pTrack->PTR_0x54);
				SeqArgType r10;
				
				if (r30 == 0xA2)
				{
					r31 = pTrack->mMmlParserParam.mPredicate != false;
					r30 = ReadByte(&pTrack->PTR_0x54);
				}
				if (r30 == 0xA0)
				{
					r10 = SEQ_ARG_TYPE_RANDOM;
					r5 = true;
					r30 = ReadByte(&pTrack->PTR_0x54);
				}
				if (r30 == 0xA1)
				{
					r10 = SEQ_ARG_TYPE_VARIABLE;
					r5 = true;
					r30 = ReadByte(&pTrack->PTR_0x54);
				}
				
				if (!(r30 & 0x80))
				{
					//8003B960
					u8 r26 = ReadByte(&pTrack->PTR_0x54);
					s32 noteLength = ReadArg(&pTrack->PTR_0x54, pPlayer, pTrack, r5 ? r10 : SEQ_ARG_TYPE_IMMEDIATE_VAR); // at r31
					int r3 = r30 + pTrack->BYTE_0x8B;
					
					if (!r31) return 0;
					
					//8003B9B0
					int r5 = Clamp<int>(r3, 0, 0x7F);
					//8003B9C8
					if (!pTrack->BOOL_0x5C && r29_5)
					{
						//8003B9DC
						NoteOnCommandProc(pTrack, r5, r26, noteLength > 0 ? noteLength : -1, pTrack->mMmlParserParam.BOOL_0x2);
					}
					//8003BA0C
					if (pTrack->mMmlParserParam.BOOL_0x1)
					{
						pTrack->TIMER_0x58 = noteLength;
						
						if (!noteLength) pTrack->BOOL_0x5E = true;
						//goto 8003BECC
					}
					//goto 8003BECC
				}
				else
				{
					//8003BA30
					s32 r26 = 0;
					s32 r25 = 0;
					switch (r30 & 0xF0)
					{
						case 0x80:
							//8003BA90
							switch (r30)
							{
								case 0x80:
									//8003BAC4
									s32 arg_c80 = ReadArg(&pTrack->PTR_0x54, pPlayer, pTrack, r5 ? r10 : SEQ_ARG_TYPE_IMMEDIATE_VAR);
									
									if (r31) pTrack->TIMER_0x58 = arg_c80;
									
									break;
								case 0x81:
									//8003BAF8
									s32 arg_c81 = ReadArg(&pTrack->PTR_0x54, pPlayer, pTrack, r5 ? r10 : SEQ_ARG_TYPE_IMMEDIATE_VAR);
									
									if (r31) CommandProc(pTrack, r30, arg_c81, 0);
									
									break;
								case 0x88:
									//8003BB4C
									u8 arg_c88 = ReadByte(&pTrack->PTR_0x54);
									u32 arg2_c88 = Read24(&pTrack->PTR_0x54);
									
									if (r31) CommandProc(pTrack, r30, arg_c88, arg2_c88);
									
									break;
								case 0x89:
									//8003BBB4
									u32 arg_c89 = Read24(&pTrack->PTR_0x54);
									
									if (r31) CommandProc(pTrack, r30, arg_c89, 0);
									
									break;
								case 0x8A:
									//8003BC14
									u32 arg_c8a = Read24(&pTrack->PTR_0x54);
									
									if (r31) CommandProc(pTrack, r30, arg_c8a, 0);
									
									break;
							}
							break;
						case 0xB0:
						case 0xC0:
						case 0xD0:
							//8003BC74
							register s32 arg_c_b0_c0 = ReadArg(&pTrack->PTR_0x54, pPlayer, pTrack, r5 ? r10 : SEQ_ARG_TYPE_IMMEDIATE_BYTE);
							if (r31)
							{
								//8003BCA0
								switch (r30)
								{
									case 0xC3:
									case 0xC4:
										arg_c_b0_c0 &= 0xFF;
										asm
										{
											extsb arg_c_b0_c0, arg_c_b0_c0
										}
										break;
									default:
										arg_c_b0_c0 &= 0xFF;
										break;
								}
								//8003BCC4
								CommandProc(pTrack, r30, arg_c_b0_c0, 0);
							}
							break;
						case 0x90:
							//8003BCE8
							if (r31) CommandProc(pTrack, r30, 0, 0);
							
							break;
						case 0xE0:
							//8003BD18
							s16 arg_c_e0 = ReadArg(&pTrack->PTR_0x54, pPlayer, pTrack, r5 ? r10 : SEQ_ARG_TYPE_IMMEDIATE_16);
							
							if (r31) CommandProc(pTrack, r30, arg_c_e0, 0);
							
							break;
						case 0xF0:
							//8003BD6C
							switch (r30)
							{
								case 0xFE:
									pTrack->PTR_0x54 += 2;
									break;
								case 0xFF:
									return 1;
								case 0xF0:
									//8003BDA8
									u8 r29 = ReadByte(&pTrack->PTR_0x54);
									switch (r29 & 0xF0)
									{
										case 0xE0:
											//8003BDE0
											r26 = (s16)ReadArg(&pTrack->PTR_0x54, pPlayer, pTrack, r5 ? r10 : SEQ_ARG_TYPE_IMMEDIATE_16);
											
											if (r31)
											{
												//8003BE10
												CommandProc(pTrack, (r30 << 8) + r29, r26, 0);
											}
											
											break;
										case 0x80:
										case 0x90:
											//8003BE3C
											r26 = ReadByte(&pTrack->PTR_0x54);
											r25 = (s16)ReadArg(&pTrack->PTR_0x54, pPlayer, pTrack, r5 ? r10 : SEQ_ARG_TYPE_IMMEDIATE_16);
											
											if (r31) CommandProc(pTrack, (r30 << 8) + r29, r26, r25);
											
											break;
									}
									// Intentional fallthrough
								default:
									//8003BEA0
									if (r31) CommandProc(pTrack, r30, r26, r25);
									
									break;
							}
							break;
					}
				}
				
				return 0;
			}
			
			void MmlParser::CommandProc(MmlSeqTrack * pTrack, u32 command, s32 arg, s32 arg2) const
			{
				// r25 (r4) <- pTrack
				// r26 (r6) <- arg
				// r29 (r8) <- arg2
				SeqPlayer * pPlayer = pTrack->mPlayer;
				MmlSeqTrack::MmlParserParam * pMmlParserParam = &pTrack->mMmlParserParam; // at r31
				// SMALLEST CASE = 0x81
				// LARGEST CASE = 0xFD
				if (command <= 0xFF)
				{
					switch (command)
					{
						case 0xE1:
							//8003BF3C
							pPlayer->SHORT_0xAC = arg;
							break;
						case 0xB0:
							//8003BF3C
							pPlayer->BYTE_0xAA = arg;
							break;
						case 0x81:
							//8003BF4C
							if (arg < 0x10000) pTrack->WORD_0x68 = (u16)arg;
							
							break;
						case 0xDD:
							//8003BF64
							pTrack->SetMute((SeqMute)arg);
							break;
						case 0xC1:
							//8003BF74
							pTrack->BYTE_0x84 = arg;
							break;
						case 0xD5:
							//8003BF7C
							pTrack->BYTE_0x85 = arg;
							break;
						case 0xC2:
							//8003BF84
							pPlayer->BYTE_0xA8 = arg;
							break;
						case 0xC3:
							//8003BF8C
							pTrack->BYTE_0x8B = arg;
							break;
						case 0xC4:
							//8003BF94
							pTrack->BYTE_0x86 = arg;
							break;
						case 0xC5:
							//8003BF9C
							pTrack->BYTE_0x87 = arg;
							break;
						case 0xC0:
							//8003BFA4
							pTrack->BYTE_0x88 = arg - 0x40;
							break;
						case 0xDC: //8003BFB0
							pTrack->BYTE_0x89 = arg - 0x40;
							break;
						case 0xD7: //8003BFBC
							pTrack->BYTE_0x8A = arg;
							break;
						case 0xC6: //8003BFC4
							pTrack->BYTE_0x8C = arg;
							break;
						case 0xC7: //8003BFCC
							pMmlParserParam->BOOL_0x1 = arg;
							break;
						case 0xCF: //8003BFE0
							pTrack->BYTE_0x8E = arg;
							break;
						case 0xCA: //8003BFE8
							pTrack->mLfoParam.FLOAT_0x0 = (u8)arg / 128.0f;
							break;
						case 0xCB: //8003C014
							pTrack->mLfoParam.FLOAT_0x4 = (u8)arg * 0.390625f;
							break;
						case 0xCC: //8003C040
							pTrack->BYTE_0x7C = arg;
							break;
						case 0xCD: //8003C048
							pTrack->mLfoParam.BYTE_0xC = arg;
							break;
						case 0xE0: //8003C050
							pTrack->mLfoParam.WORD_0x8 = arg * 5;
							break;
						case 0xE3: //8003C060
							pTrack->FLOAT_0x80 = arg / 32.0f;
							break;
						case 0xD0: //8003C08C
							pTrack->mAttack = arg;
							break;
						case 0xD1: //8003C094
							pTrack->mDecay = arg;
							break;
						case 0xD2: //8003C09C
							pTrack->mSustain = arg;
							break;
						case 0xD3: //8003C0A4
							pTrack->mRelease = arg;
							break;
						case 0xDF: //8003C0AC
							pTrack->BOOL_0x60 = (u8)arg >= 0x40;
							break;
						case 0xC8: //8003C0D0
							pMmlParserParam->BOOL_0x2 = arg;
							pTrack->ReleaseAllChannel(-1);
							pTrack->FreeAllChannel();
							break;
						case 0xC9: //8003C0F8
							pTrack->BYTE_0x8D = arg + pTrack->BYTE_0x8B;
							pTrack->BOOL_0x5F = true;
							break;
						case 0xCE: //8003C110
							pTrack->BOOL_0x5F = arg;
							break;
						case 0xD8: //8003C124
							pTrack->BYTE_0x97 = arg;
							break;
						case 0xD9: //8003C12C
							pTrack->BYTES_0x94[0] = arg;
							break;
						case 0xDA: //8003C134
							pTrack->BYTES_0x94[1] = arg;
							break;
						case 0xDE: //8003C13C
							pTrack->BYTES_0x94[2] = arg;
							break;
						case 0xDB: //8003C144
							pTrack->BYTE_0x93 = arg;
							break;
						case 0xD6: //8003C14C
							if (mPrintVarEnabledFlag)
							{
								volatile s16 * pVariable = GetVariablePtr(pPlayer, pTrack, arg);
								int i = (arg >= SEQ_VARIABLE_COUNT * 2) ?
									arg - SEQ_VARIABLE_COUNT * 2 :
									(arg >= SEQ_VARIABLE_COUNT ? arg - SEQ_VARIABLE_COUNT : arg);
								const char * pVarTypeString = (arg >= SEQ_VARIABLE_COUNT * 2) ?
									"T" :
									(arg >= SEQ_VARIABLE_COUNT ? "G" : "");
								OSReport("#%08x[%d]: printvar %sVAR_%d(%d) = %d\n",
									pPlayer, pTrack->mPlayerTrackNo, pVarTypeString, i, arg, *pVariable);
							}
							break;
						case 0x88: //8003C1F8
							SeqTrack * pPlayerTrack = pPlayer->GetPlayerTrack(arg);
							if (pPlayerTrack && pPlayerTrack != pTrack)
							{
								pPlayerTrack->Close();
								pPlayerTrack->SetSeqData(pTrack->PTR_0x50, arg2);
								pPlayerTrack->Open();
							}
							break;
						case 0x89: //8003C238
							pTrack->PTR_0x54 = pTrack->PTR_0x50 + arg;
							break;
						case 0x8A: //8003C248
							if (pMmlParserParam->mStackIndex < MmlSeqTrack::STACK_FRAME_COUNT)
							{
								pMmlParserParam->mReturnAddresses[pMmlParserParam->mStackIndex] = pTrack->PTR_0x54;
								pMmlParserParam->mStackIndex++;
								pTrack->PTR_0x54 = pTrack->PTR_0x50 + arg;
							}
							break;
						case 0xFD: //8003C280
							if (pMmlParserParam->mStackIndex)
							{
								pTrack->PTR_0x54 = pMmlParserParam->mReturnAddresses[--pMmlParserParam->mStackIndex];
							}
							break;
						case 0xD4: //8003C2A8
							if (pMmlParserParam->mStackIndex < MmlSeqTrack::STACK_FRAME_COUNT)
							{
								pMmlParserParam->mReturnAddresses[pMmlParserParam->mStackIndex] = pTrack->PTR_0x54;
								pMmlParserParam->mLoopCounters[pMmlParserParam->mStackIndex] = arg;
								pMmlParserParam->mStackIndex++;
							}
							break;
						case 0xFC: //8003C2E0
							if (pMmlParserParam->mStackIndex)
							{
								u8 curLoopCounter = pMmlParserParam->mLoopCounters[pMmlParserParam->mStackIndex - 1];
								
								if (curLoopCounter && !--curLoopCounter)
								{
									pMmlParserParam->mStackIndex--;
								}
								else
								{
									pMmlParserParam->mLoopCounters[pMmlParserParam->mStackIndex - 1] = curLoopCounter;
									pTrack->PTR_0x54 = pMmlParserParam->mReturnAddresses[pMmlParserParam->mStackIndex - 1];
								}
							}
							break;
					}
				}
				//8003C334
				else if (command <= 0xFFFF)
				{
					//8003C33C
					u8 r0 = command & 0xF0;
					u8 r27 = command;
					volatile s16 * pVariable = NULL; // at r30
					if (r0 == 0x80 || r0 == 0x90)
					{
						//8003C358
						pVariable = GetVariablePtr(pPlayer, pTrack, arg);
						
						if (!pVariable) return;
					}
					//8003C398
					switch (r27)
					{
						case 0x80:
							//8003C444
							*pVariable = arg2;
							break;
						case 0x81: //8003C44C
							*pVariable += arg2;
							break;
						case 0x82: //8003C45C
							*pVariable -= arg2;
							break;
						case 0x83: //8003C46C
							*pVariable *= arg2;
							break;
						case 0x84: //8003C47C
							if (arg2) *pVariable /= arg2;
							
							break;
						case 0x85: //8003C494
							if (arg2 >= 0) *pVariable <<= arg2;
							else *pVariable >>= -arg2;
							
							break;
						case 0x86: //8003C4C0
							bool arg2Sign = false; // at r27
							
							if (arg2 < 0)
							{
								arg2Sign = true;
								arg2 = (s16)-arg2;
							}
							//8003C4D8
							int random = CalcRandom();
							random *= arg2 + 1;
							random >>= 0x10;
							
							if (arg2Sign) random = -random;
							
							*pVariable = random;
							break;
						case 0x87: //8003C500
							*pVariable &= arg2;
							break;
						case 0x88: //8003C510
							*pVariable |= arg2;
							break;
						case 0x89: //8003C520
							*pVariable ^= arg2;
							break;
						case 0x8A: //8003C530
							*pVariable = ~(u16)arg2;
							break;
						case 0x8B: //8003C540
							if (arg2) *pVariable %= arg2;
							
							break;
						case 0x90: //8003C560
							pMmlParserParam->mPredicate = *pVariable == arg2;
							break;
						case 0x91: //8003C578
							pMmlParserParam->mPredicate = *pVariable >= arg2;
							break;
						case 0x92: //8003C594
							pMmlParserParam->mPredicate = *pVariable > arg2;
							break;
						case 0x93: //8003C5B4
							pMmlParserParam->mPredicate = *pVariable <= arg2;
							break;
						case 0x94: //8003C5D0
							pMmlParserParam->mPredicate = *pVariable < arg2;
							break;
						case 0x95: //8003C5F0
							pMmlParserParam->mPredicate = *pVariable != arg2;
							break;
						case 0xE0:
							break;
					}
				}
			}
			
			Channel * MmlParser::NoteOnCommandProc(MmlSeqTrack * pTrack, int r4_5, int r5_6, s32 r6_7, bool r7_8) const
			{
				return pTrack->NoteOn(r4_5, r5_6, r6_7, r7_8);
			}
			
			s32 MmlParser::ReadArg(const u8 ** pPointer, SeqPlayer * pPlayer, SeqTrack * pTrack, SeqArgType seqArgType) const
			{
				switch (seqArgType)
				{
					case SEQ_ARG_TYPE_IMMEDIATE_BYTE:
						return ReadByte(pPointer);
					case SEQ_ARG_TYPE_IMMEDIATE_16:
						return Read16(pPointer);
					case SEQ_ARG_TYPE_IMMEDIATE_VAR:
						return ReadVar(pPointer);
					case SEQ_ARG_TYPE_VARIABLE:
						volatile s16 * pVariable = GetVariablePtr(pPlayer, pTrack, ReadByte(pPointer));
						
						if (!pVariable) return (s32)pVariable;
						
						return *pVariable;
					case SEQ_ARG_TYPE_RANDOM:
						s16 r30 = Read16(pPointer);
						s16 r31 = Read16(pPointer);
						int r4 = CalcRandom();
						r4 *= r31 - r30 + 1;
						r4 >>= 0x10;
						r4 += r30;
						return r4;// + r30;
				}
			}
			
			bool MmlParser::mPrintVarEnabledFlag;
		}
	}
}