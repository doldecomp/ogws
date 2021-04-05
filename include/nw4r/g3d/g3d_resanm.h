#ifndef NW4R_G3D_RESANM_H
#define NW4R_G3D_RESANM_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace g3d
	{
		struct ResKeyFrameAnmFramesData
		{
			float mTime; // at 0x0
			float mValue; // at 0x4
			float mDerivative; // at 0x8
		};
		
		struct ResKeyFrameAnmData
		{
			u16 mCount; // at 0x0
			float FLOAT_0x4;
			ResKeyFrameAnmFramesData mFrames[]; // at 0x8
		};
		
		struct ResColorAnmFramesData
		{
			u32 mColor; // at 0x0
		};
		
		struct ResColorAnmData
		{
			UNKWORD WORD_0x0;
			UNKWORD WORD_0x4;
		};
		
		struct ResBoolAnmFramesData
		{
			u32 mFlags; // at 0x0
		};
		
		namespace detail
		{
			float GetResKeyFrameAnmResult(const ResKeyFrameAnmData *, float);
			
			u32 GetResColorAnmResult(const ResColorAnmFramesData *, float);
			
			inline u32 GetResColorAnmResult(const ResColorAnmData * pData, float time, bool b)
			{
				if (b) return pData->WORD_0x4;
				
				return GetResColorAnmResult((const ResColorAnmFramesData *)((u8 *)&pData->WORD_0x4 + pData->WORD_0x4), time);
			}
			
			inline bool GetResBoolAnmFramesResult(const ResBoolAnmFramesData * pData, int i)
			{
				u32 index = i;
				
				u32 mask = 0x80000000 >> (index % 32);
				u32 flags = pData[index / 32].mFlags;
				
				return flags & mask;
			}
			
			template <typename T>
			inline float ClipFrame(T & info, float time)
			{
				if (time <= 0.0f) return 0.0f;
				
				if (info.MAX_0x8 <= time) return info.MAX_0x8;
				
				return time;
			}
		}
	}
}

#endif