#pragma ipa file
#include <math.h>
#include "snd_SoundHandle.h"
#include "snd_Sound3DManager.h"
#include "snd_Sound3DListener.h"
#include "snd_AxManager.h"

namespace nw4r
{
	using namespace math;
	using namespace ut;
	
	namespace snd
	{
		using namespace detail;
		
		namespace
		{
			/*
			Solves the linear equation:
				a*x + b*y + c = d
			Where:
				a = dFactor - cFactor
				b = dAngle - cAngle
				c = cAngle * cFactor
				d = dAngle * dFactor
			*/
			float SolveLinerFunction(float x, float dAngle, float cAngle, float dFactor, float cFactor) // typo
			{
				if (dAngle == cAngle) return (dFactor + cFactor) / 2;
				
				float b = dAngle - cAngle;
				
				return x * (cFactor - dFactor) / b + (dAngle * dFactor - cAngle * cFactor) / b;
			}
		}
		
		Sound3DManager::Sound3DManager() :
			INT_0x10(0x20),
			FLOAT_0x14(NW4R_PI_F32 / 4),
			FLOAT_0x18(NW4R_PI_F32 / 6),
			FLOAT_0x1C(2 * NW4R_PI_F32 / 3),
			FLOAT_0x20(0.0f),
			FLOAT_0x24(0.9f)
		{
			
		}
		
		u32 Sound3DManager::GetRequiredMemSize(const SoundArchive * pArchive)
		{
			u32 actorParamCount = 0;
			SoundArchive::SoundArchivePlayerInfo playerInfo;
			
			if (pArchive->ReadSoundArchivePlayerInfo(&playerInfo))
			{
				actorParamCount = playerInfo.SIZE_0x0 + playerInfo.SIZE_0x8;
				actorParamCount += playerInfo.SIZE_0x14;
			}
			
			return actorParamCount * sizeof(Sound3DActorParam);
		}
		
		bool Sound3DManager::Setup(const SoundArchive *, void * ptr, u32 size)
		{
			mPool.Create(ptr, size);
			
			return true;
		}
		
		void Sound3DManager::detail_Update(SoundParam * r27_4, u32 r28_5, BasicSound * pSound, const void * r29_7, u32 r30_8)
		{
			SoundHandle handle;
			
			if (pSound) handle.detail_AttachSoundAsTempHandle(pSound);
			
			Update(r27_4, r28_5, pSound ? &handle : NULL, r29_7, r30_8);
		}
		
		void Sound3DManager::Update(SoundParam * pParam, u32, SoundHandle *, const void * r30_7, u32 r31_8)
		{
			//r28 <- this
			//r29 <- pParam
			const Sound3DActorParam * pActorParam = static_cast<const Sound3DActorParam *>(r30_7);
			float angle;
			float f30;
			float distance;
			float f29;
			float f28;
			float f_5;
			float f_0;
			
			Sound3DListener * pListener = mListener;
			
			if (!pListener)
			{
				pParam->FLOAT_0x0 = 0.0f;
				return;
			}
			
			VEC3 stack_0x20;
			
			VEC3Transform(&stack_0x20, &pListener->mMatrix, &pActorParam->mPosition);
			
			distance = VEC3Len(&stack_0x20); // at f31
			f29 = 1.0f;
			if (r31_8 & 9 && distance > pListener->mMaxVolumeDistance)
			{
				float f2_0;
				float f2_1;
				float f2;
				float f1;
				//800414CC
				switch (pActorParam->mSound3DParam.BYTE_0x4)
				{
					case 1:
						f2_0 = distance - pListener->mMaxVolumeDistance;
						f2_1 = pListener->mUnitDistance;
						f2 = f2_0 / f2_1;
						f1 = pActorParam->mSound3DParam.BYTE_0x5 / 256.0f;
						f29 = pow(f1, f2);
						break;
					case 2:
						//80041524
						f2_0 = distance - pListener->mMaxVolumeDistance;
						f2_1 = pListener->mUnitDistance;
						f2 = f2_0 / f2_1 * pActorParam->mSound3DParam.BYTE_0x5;
						f2 = f2 / 256.0f;
						f29 = Max<float>(0.0f, 1.0f - f2);
						break;
				}
				//80041570
			}
			//80041570
			if (r31_8 & 1 && !(pActorParam->mSound3DParam.WORD_0x0 & 1)) pParam->FLOAT_0x0 = f29;
			//80041588
			
			if (r31_8 & 6)
			{
				//80041590
				VEC3 stack_0x14;
				if (0.0f == distance)
				{
					stack_0x14.mCoords.z = 0.0f;
					stack_0x14.mCoords.y = 0.0f;
					stack_0x14.mCoords.x = 0.0f;
					//goto 80041628
				}
				else
				{
					VEC3 stack_0x8(stack_0x20.mCoords.x, 0.0f, stack_0x20.mCoords.z);
					//800415AC
					/*
					stack_0x8.mCoords.x = stack_0x20.mCoords.x;
					stack_0x8.mCoords.y = 0.0f;
					stack_0x8.mCoords.z = stack_0x20.mCoords.z;
					*/
					//800415C4
					float f1_1 = VEC3Len(&stack_0x8);
					if (f1_1 > pListener->mInteriorSize)
					{
						stack_0x8.mCoords.x *= pListener->mInteriorSize / f1_1;
						stack_0x8.mCoords.z *= pListener->mInteriorSize / f1_1;
					}
					//800415F8
					float f1_2 = VEC3Len(&stack_0x8);
					
					stack_0x14.mCoords.x = stack_0x20.mCoords.x * f1_2 / distance;
					stack_0x14.mCoords.y = 0.0f;
					stack_0x14.mCoords.z = stack_0x20.mCoords.z * f1_2 / distance;
					//80041628
				}
				//80041628
				
				angle = atan2(stack_0x14.mCoords.x, -stack_0x14.mCoords.z); // at f31
				
				f28 = VEC3Len(&stack_0x14) / pListener->mInteriorSize;
				
				float f31_0;
				float f31_1;
				float f31;
				float f27;
				float f4;
				float f3;
				
				switch (AxManager::GetInstance()->GetOutputMode())
				{
					case OUTPUT_MODE_1:
					case OUTPUT_MODE_2:
					{	//80041670
						static float angleRearLeft = -FLOAT_0x1C; // at 0x804BEAC0
						static float angleFrontLeft = -FLOAT_0x18; // at 0x804BEAC8
						static float angleFrontRight = FLOAT_0x18; // at 0x804BEAD0
						static float angleRearRight = FLOAT_0x1C; // at 0x804BEAD8
						
						//800416E8
						//float f30, f27;
						if (angle < angleRearLeft)
						{
							//800416F4
							f30 = SolveLinerFunction(angle, -NW4R_PI_F32, angleRearLeft, -1.0f, 0.0f);
							//80041730
							f27 = 1.0f;
							//goto 800418E8
						}
						else if (angle < -NW4R_PI_F32 / 2)
						{
							//80041738
							f30 = -1.0f;
							f27 = SolveLinerFunction(angle, angleRearLeft, -NW4R_PI_F32 / 2, 0.0f, 1.0f);
							//goto 800418E8
						}
						else if (angle < angleFrontLeft)
						{
							//80041780
							f30 = -1.0f;
							f27 = SolveLinerFunction(angle, -NW4R_PI_F32 / 2, angleFrontLeft, -1.0f, 0.0f);
							//goto 800418E8
						}
						else if (angle < angleFrontRight)
						{
							//800417CC
							f30 = SolveLinerFunction(angle, angleFrontLeft, angleFrontRight, 1.0f, -1.0f);
							//80041814
							f27 = -1.0f;
							//goto 800418E8
						}
						else if (angle < NW4R_PI_F32 / 2)
						{
							//8004181C
							f30 = 1.0f;
							f27 = SolveLinerFunction(angle, angleFrontRight, NW4R_PI_F32 / 2, 0.0f, -1.0f);
							//goto 800418E8
						}
						else if (angle < angleRearRight)
						{
							//80041864
							f30 = 1.0f;
							f27 = SolveLinerFunction(angle, NW4R_PI_F32 / 2, angleRearRight, 1.0f, 0.0f);
							//goto 800418E8
						}
						else
						{
							//800418AC
							f30 = SolveLinerFunction(angle, angleRearRight, NW4R_PI_F32, 0.0f, 1.0f);
							//800418E4
							f27 = 1.0f;
							//800418E8
						}
						//800418E8
						f31 = cos(FLOAT_0x1C);
						f31_1 = FLOAT_0x18;
						f31_0 = cos(f31_1);
						f31 = (f31_0 + f31) / 2;
						
						//80041914
						f3 = cos(FLOAT_0x1C);
						f3 = -f3;
						f4 = f31 + f3;
						f30 *= FLOAT_0x24;
						f_5 = f30 * f28;
						f27 *= FLOAT_0x24;
						f3 = f27 * f28;
						f4 = f31 / f4;
						f_0 = 1.0f + (f4 * (1.0f - f28) + f3) + FLOAT_0x20;
						break;
						//goto 80041B7C
					}
					case OUTPUT_MODE_0:
					{
						//8004195C
						static float angleRearLeft = -NW4R_PI_F32 + FLOAT_0x14; // at 0x804BEAE0
						static float angleFrontLeft = -FLOAT_0x14; // at 0x804BEAE8
						static float angleFrontRight = FLOAT_0x14; // at 0x804BEAF0
						static float angleRearRight = NW4R_PI_F32 - FLOAT_0x14; // at 0x804BEAF8
						//800419E0
						if (angle < angleRearLeft)
						{
							//800419EC
							f30 = SolveLinerFunction(angle, -NW4R_PI_F32, angleRearLeft, -1.0f, 0.0f);
							f27 = 1.0f;
							//goto 80041B54
						}
						else if (angle < angleFrontLeft)
						{
							//80041A3C
							f30 = -1.0f;
							f27 = SolveLinerFunction(angle, angleRearLeft, angleFrontLeft, -1.0f, 1.0f);
							//goto 80041B54
						}
						else if (angle < angleFrontRight)
						{
							//80041A88
							f30 = SolveLinerFunction(angle, angleFrontLeft, angleFrontRight, 1.0f, -1.0f);
							f27 = -1.0f;
							//goto 80041B54
						}
						else if (angle < angleRearRight)
						{
							//80041AD8
							f30 = 1.0f;
							f27 = SolveLinerFunction(angle, angleFrontRight, angleRearRight, 1.0f, -1.0f);
							//goto 80041B54
						}
						else
						{
							//80041B18
							f30 = SolveLinerFunction(angle, angleRearRight, NW4R_PI_F32, 0.0f, 1.0f);
							f27 = 1.0f;
							//80041B54
						}
						//80041B54
						f30 *= FLOAT_0x24;
						f27 *= FLOAT_0x24;
						f_0 = 1.0f + f27 * f28;
						f_5 = f30 * f28;
						break;
						//goto 80041B7C
					}
					case OUTPUT_MODE_3:
					default:
						//80041B74
						f_5 = 0.0f;
						f_0 = 0.0f;
						//80041B7C
				}
				//80041B7C
			}
			//80041B7C
			if (r31_8 & 2 && !(pActorParam->mSound3DParam.WORD_0x0 & 2)) pParam->FLOAT_0x8 = f_5;
			//80041B94
			if (r31_8 & 4 && !(pActorParam->mSound3DParam.WORD_0x0 & 4)) pParam->FLOAT_0xC = f_0;
			//80041BAC
			if (r31_8 & 8 && !(pActorParam->mSound3DParam.WORD_0x0 & 8))
			{
				//80041BC0
				pParam->INT_0x18 = -(int)((1.0f - f29) * INT_0x10);
				//80041C00
			}
		}
		
		void * Sound3DManager::detail_AllocAmbientArg(u32 size)
		{
			if (size != sizeof(Sound3DActorParam)) return NULL;
			
			return mPool.Alloc();
		}
		
		void Sound3DManager::detail_FreeAmbientArg(void * pArg, const detail::BasicSound *)
		{
			mPool.Free(static_cast<Sound3DActorParam *>(pArg));
		}
		
		Sound3DManager::Sound3DActorParam::Sound3DActorParam() : WORD_0x0(-1)
		{
			mSound3DParam.WORD_0x0 = 0;
			mSound3DParam.BYTE_0x4 = 1;
			mSound3DParam.BYTE_0x5 = 0x80;
		}
	}
}