#pragma ipa file
#include "snd_EnvGenerator.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			const s16 EnvGenerator::DecibelSquareTable[0x80] = {
				-723, -722, -721, -651,
				-601, -562, -530, -503,
				-480, -460, -442, -425,
				-410, -396, -383, -371,
				-360, -349, -339, -330,
				-321, -313, -305, -297,
				-289, -282, -276, -269,
				-263, -257, -251, -245,
				-239, -234, -229, -224,
				-219, -214, -210, -205,
				-201, -196, -192, -188,
				-184, -180, -176, -173,
				-169, -165, -162, -158,
				-155, -152, -149, -145,
				-142, -139, -136, -133,
				-130, -127, -125, -122,
				-119, -116, -114, -111,
				-109, -106, -103, -101,
				-99, -96, -94, -91,
				-89, -87, -85, -82,
				-80, -78, -76, -74,
				-72, -70, -68, -66,
				-64, -62, -60, -58,
				-56, -54, -52, -50,
				-49, -47, -45, -43,
				-42, -40, -38, -36,
				-35, -33, -31, -30,
				-28, -27, -25, -23,
				-22, -20, -19, -17,
				-16, -14, -13, -11,
				-10, -8, -7, -6,
				-4, -3, -1, 0
			};
			const volatile float EnvGenerator::VOLUME_INIT = -90.4f;
			
			EnvGenerator::EnvGenerator()
			{
				Init(VOLUME_INIT);
			}
			
			UNKTYPE EnvGenerator::Init(float value)
			{
				SetAttack(0x7F);
				SetDecay(0x7F);
				SetSustain(0x7F);
				SetRelease(0x7F);
				Reset(value);
			}
			
			UNKTYPE EnvGenerator::Reset(float value)
			{
				mValue = value * 10.0f;
				mStatus = Status_Attack;
			}
			
			float EnvGenerator::GetValue() const
			{
				if (mStatus == Status_Attack && 0.0f == mAttack) return 0.0f;
				
				return mValue / 10.0f;
			}
			
			void EnvGenerator::Update(int r4)
			{
				switch (mStatus)
				{
					case Status_Attack:
						int count = r4;
						for (int i = 0; i < count; i++)
						{
							r4--;
							if ((mValue *= mAttack) > -0.03125f)
							{
								mValue = 0.0f;
								mStatus = Status_Decay;
							}
						}
						if (mStatus != Status_Decay) break; // intentional switch fallthrough
					case Status_Decay:
						float f1 = DecibelSquareTable[mSustain];
						mValue -= mDecay * r4;
						if (mValue > f1) break;
						mValue = f1;
						mStatus = Status_Sustain;
						break;
					case Status_Sustain:
						break;
					case Status_Release:
						mValue -= mRelease * r4;
						break;
				}
			}
			
			float EnvGenerator::CalcRelease(int num)
			{
				if (num == 0x7F) return 65535.0f;
				if (num == 0x7E) return 24.0f;
				if (num < 0x32) return (num * 2 + 1) / 128.0f / 5.0f;
				return 60.0f / (0x7E - num) / 5.0f;
			}
			
			UNKTYPE EnvGenerator::SetAttack(int i)
			{
				static const float attackTable[0x80] = {
					//80375940
					0.9992175f, 0.9984326f, 0.9976452f, 0.9968553f,
					//80375950
					0.9960629f, 0.9952679f, 0.9944704f, 0.9936704f,
					//80375960
					0.9928677f, 0.9920625f, 0.9912546f, 0.9904441f,
					//80375970
					0.9896309f, 0.9888151f, 0.9879965f, 0.9871752f,
					//80375980
					0.9863512f, 0.9855244f, 0.9846949f, 0.9838625f,
					//80375990
					0.9830273f, 0.9821893f, 0.9813483f, 0.9805045f,
					//803759a0
					0.9796578f, 0.9788081f, 0.9779555f, 0.9770999f,
					//803759b0
					0.9762413f, 0.9753797f, 0.974515f, 0.9736472f,
					//803759c0
					0.9727763f, 0.9719023f, 0.9710251f, 0.9701448f,
					//803759d0
					0.9692612f, 0.9683744f, 0.9674844f, 0.966591f,
					//803759e0
					0.9656944f, 0.9647944f, 0.963891f, 0.9629842f,
					//803759f0
					0.962074f, 0.9611604f, 0.9602433f, 0.9593226f,
					//80375a00
					0.9583984f, 0.9574706f, 0.9565392f, 0.9556042f,
					//80375a10
					0.9546655f, 0.9537231f, 0.9527769f, 0.951827f,
					//80375a20
					0.9508732f, 0.9499157f, 0.9489542f, 0.9479888f,
					//80375a30
					0.9470195f, 0.9460462f, 0.9450689f, 0.9440875f,
					//80375a40
					0.943102f, 0.9421124f, 0.9411186f, 0.9401206f,
					//80375a50
					0.9391184f, 0.9381118f, 0.9371009f, 0.9360856f,
					//80375a60
					0.9350659f, 0.9340417f, 0.9330131f, 0.9319798f,
					//80375a70
					0.930942f, 0.9298995f, 0.9288523f, 0.9278004f,
					//80375a80
					0.9267436f, 0.9256821f, 0.9246156f, 0.9235442f,
					//80375a90
					0.9224678f, 0.9213864f, 0.9202998f, 0.9192081f,
					//80375aa0
					0.9181112f, 0.9170091f, 0.9159016f, 0.9147887f,
					//80375ab0
					0.9136703f, 0.9125465f, 0.9114171f, 0.9102821f,
					//80375ac0
					0.9091414f, 0.9079949f, 0.9068427f, 0.9056845f,
					//80375ad0
					0.9045204f, 0.9033502f, 0.902174f, 0.9009916f,
					//80375ae0
					0.8998029f, 0.898608f, 0.8974066f, 0.8961988f,
					//80375af0
					0.8949844f, 0.8900599f, 0.8824622f, 0.8759247f,
					//80375b00
					0.8691861f, 0.8636406f, 0.8535788f, 0.8430189f,
					//80375b10
					0.8286135f, 0.8149099f, 0.8002172f, 0.7780663f,
					//80375b20
					0.755475f, 0.7242125f, 0.6828239f, 0.6329169f,
					//80375b30
					0.5592135f, 0.4551411f, 0.329877f, 0.0f
				};
				
				mAttack = attackTable[i];
			}
			
			UNKTYPE EnvGenerator::SetDecay(int num)
			{
				mDecay = CalcRelease(num);
			}
			
			UNKTYPE EnvGenerator::SetSustain(int sustain)
			{
				mSustain = sustain;
			}
			
			UNKTYPE EnvGenerator::SetRelease(int num)
			{
				mRelease = CalcRelease(num);
			}
		}
	}
}