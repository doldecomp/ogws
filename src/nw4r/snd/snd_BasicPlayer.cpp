#include "snd_BasicPlayer.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			BasicPlayer::BasicPlayer() : mId(-1)
			{
				InitParam();
			}
			
			void BasicPlayer::InitParam()
			{
				FLOAT_0x10 = 1.0f; // for register allocation
				FLOAT_0x10 = 0.0f;
				FLOAT_0x8 = 1.0f;
				FLOAT_0xC = 1.0f;
				FLOAT_0x14 = 0.0f;
				mLpfFreq = 0.0f;
				
				mRemoteFilter = 0;
				mPanMode = PAN_MODE_0;
				mPanCurve = PAN_CURVE_0;
				mOutputLine = 1;
				
				FLOAT_0x28 = 0.0f;
				FLOAT_0x24 = 1.0f;
				
				ARR_0x2C[AUX_A] = 0.0f;
				ARR_0x2C[AUX_B] = 0.0f;
				ARR_0x2C[AUX_C] = 0.0f;
				
				mRemoteOutputVolumes[0] = 1.0f;
				ARR_0x48[0] = 0.0f;
				ARR_0x58[0] = 0.0f;
				mRemoteOutputVolumes[1] = 1.0f;
				ARR_0x48[1] = 0.0f;
				ARR_0x58[1] = 0.0f;
				mRemoteOutputVolumes[2] = 1.0f;
				ARR_0x48[2] = 0.0f;
				ARR_0x58[2] = 0.0f;
				mRemoteOutputVolumes[3] = 1.0f;
				ARR_0x48[3] = 0.0f;
				ARR_0x58[3] = 0.0f;
			}
			
			void BasicPlayer::SetFxSend(AuxBus bus, float f)
			{
				ARR_0x2C[bus] = f;
			}
			
			float BasicPlayer::GetFxSend(AuxBus bus) const
			{
				return ARR_0x2C[bus];
			}
			
			void BasicPlayer::SetRemoteOutVolume(int remote, float vol)
			{
				mRemoteOutputVolumes[remote] = vol;
			}
			
			float BasicPlayer::GetRemoteOutVolume(int remote) const
			{
				return mRemoteOutputVolumes[remote];
			}
			
			float BasicPlayer::GetRemoteSend(int remote) const
			{
				return ARR_0x48[remote];
			}
			
			float BasicPlayer::GetRemoteFxSend(int remote) const
			{
				return ARR_0x58[remote];
			}
		}
	}
}