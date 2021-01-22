#ifndef NW4R_SND_BASIC_SOUND_H
#define NW4R_SND_BASIC_SOUND_H
#include "types_nw4r.h"
#include "snd_MoveValue.h"
#include "snd_AxManager.h"
#include "snd_BasicPlayer.h"
#include "ut_RTTI.h"
#include "ut_algorithm.h"

namespace nw4r
{
	namespace snd
	{
		struct SoundParam
		{
			float FLOAT_0x0;
			float FLOAT_0x4;
			float FLOAT_0x8;
			float FLOAT_0xC;
			float FLOAT_0x10;
			float FLOAT_0x14;
			int INT_0x18;
		};
		
		namespace detail
		{
			struct BasicSound : ut::Polymorphic
			{
				struct AmbientParamUpdateCallback
				{
					virtual void detail_Update(SoundParam *, u32, BasicSound *, const void *, u32) = 0;
				};
				
				struct AmbientArgUpdateCallback
				{
					virtual void detail_Update(void *, const BasicSound *) = 0;
				};
				
				struct AmbientArgAllocaterCallback
				{
					virtual void * detail_AllocAmbientArg(u32) = 0;
					virtual void detail_FreeAmbientArg(void *, const BasicSound *) = 0;
				};
				
				struct AmbientArgInfo
				{
					AmbientParamUpdateCallback * mParamUpdateCallback; // at 0x0
					AmbientArgUpdateCallback * mArgUpdateCallback; // at 0x4
					AmbientArgAllocaterCallback * mArgAllocaterCallback; // at 0x8
					void * PTR_0xC;
					UNKWORD WORD_0x10;
				};
				
				static ut::detail::RuntimeTypeInfo typeInfo;
				
				inline const ut::detail::RuntimeTypeInfo * GetRuntimeTypeInfo() const { return &typeInfo; } // at 0x8
				inline virtual ~BasicSound() {}; // at 0xc
				virtual UNKTYPE Update(); // at 0x10
				virtual UNKTYPE StartPrepared(); // at 0x14
				virtual UNKTYPE Stop(int); // at 0x18
				virtual UNKTYPE Pause(bool, int); // at 0x1c
				virtual UNKTYPE SetAutoStopCounter(int); // at 0x20
				virtual UNKTYPE FadeIn(int); // at 0x24
				virtual UNKTYPE Shutdown(); // at 0x28
				virtual bool IsPrepared() const = 0; // at 0x2c
				virtual bool IsPause() const; // at 0x30
				virtual UNKTYPE SetInitialVolume(float); // at 0x34
				virtual UNKTYPE SetVolume(float, int); // at 0x38
				virtual UNKTYPE SetPitch(float); // at 0x3c
				virtual UNKTYPE SetPan(float); // at 0x40
				virtual UNKTYPE SetSurroundPan(float); // at 0x44
				virtual UNKTYPE SetLpfFreq(float); // at 0x48
				virtual UNKTYPE SetPlayerPriority(int); // at 0x4c
				virtual UNKTYPE SetRemoteFilter(int); // at 0x50
				virtual UNKTYPE SetPanMode(PanMode); // at 0x54
				virtual UNKTYPE SetPanCurve(PanCurve); // at 0x58
				virtual bool IsAttachedTempSpecialHandle() = 0; // at 0x5c
				virtual UNKTYPE DetachTempSpecialHandle() = 0; // at 0x60
				virtual UNKTYPE InitParam(); // at 0x64
				virtual BasicPlayer * GetBasicPlayer() = 0; // at 0x68
				virtual const BasicPlayer * GetBasicPlayer() const = 0; // at 0x6c
				
				PlayerHeap * mPlayerHeap; // at 0x4
				SoundHandle * mGeneralHandle; // at 0x8
				SoundHandle * mTempGeneralHandle; // at 0xc
				SoundPlayer * mSoundPlayer; // at 0x10
				struct ExternalSoundPlayer * mExternalSoundPlayer; // at 0x14
				AmbientParamUpdateCallback * mAmbientParamUpdateCallback; // at 0x18
				AmbientArgUpdateCallback * mAmbientArgUpdateCallback; // at 0x1c
				AmbientArgAllocaterCallback * mAmbientArgAllocaterCallback; // at 0x20
				UNKTYPE * PTR_0x24; // at 0x24
				
				SoundParam mParam; // at 0x28
				
				MoveValue<float, int> MV_0x44;
				MoveValue<float, int> MV_0x54;
				bool BOOL_0x64;
				bool BOOL_0x65;
				bool BOOL_0x66;
				bool mPauseFlag; // at 0x67
				bool BOOL_0x68;
				bool BOOL_0x69;
				
				int mAutoStopCounter; // at 0x6c
				u32 WORD_0x70;
				u8 mPlayerPriority; // at 0x74
				u32 mId; // at 0x78
				MoveValue<float, int> mVolume; // at 0x7c
				float mInitialVolume; // at 0x8c
				float mPan; // at 0x90
				float mSurroundPan; // at 0x94
				float mPitch; // at 0x98
				bool BOOL_0x9C;
				int mOutputLine; // at 0xa0
				float mMainOutVolume; // at 0xa4
				float mRemoteOutVolumes[4]; // at 0xa8
				UNKWORD WORD_0xB8;
				UNKWORD WORD_0xBC;
				UNKWORD WORD_0xC0;
				UNKWORD WORD_0xC4;
				UNKWORD WORD_0xC8;
				UNKWORD WORD_0xCC;
				UNKWORD WORD_0xD0;
				UNKWORD WORD_0xD4;
				
				BasicSound();
				UNKTYPE SetOutputLine(int);
				UNKTYPE SetMainOutVolume(float);
				UNKTYPE SetRemoteOutVolume(int, float);
				UNKTYPE SetFxSend(AuxBus, float);
				UNKTYPE SetAmbientParamCallback(AmbientParamUpdateCallback *, AmbientArgUpdateCallback *, AmbientArgAllocaterCallback *, void *);
				bool IsAttachedGeneralHandle();
				UNKTYPE DetachGeneralHandle();
				bool IsAttachedTempGeneralHandle();
				UNKTYPE DetachTempGeneralHandle();
				UNKTYPE SetId(u32);
				
				inline int CalcCurrentPlayerPriority() const
				{
					return ut::Clamp<int>(0, 0x7F, mPlayerPriority + mParam.INT_0x18);
				}
			};
		}
	}
}

#endif