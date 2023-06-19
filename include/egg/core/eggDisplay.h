#ifndef EGG_CORE_DISPLAY_H
#define EGG_CORE_DISPLAY_H
#include "types_egg.h"
#include "eggBitFlag.h"

#include "ut_Color.h"

namespace EGG
{
	struct Display
	{
		TBitFlag<u8> FLAG_0x0;

		Display(u8);
		void copyEFBtoXFB();
		void calcFrequency();

		virtual void beginFrame(); // at 0x8
		virtual void beginRender(); // at 0xC
		virtual void endRender(); // at 0x10
		virtual void endFrame(); // at 0x14
		virtual u32 getTickPerFrame(); // at 0x18

		bool isBlack() { return BYTE_0x9 & 0x1; }
		void setBlack(bool b)
		{
			if (b)
				BYTE_0x9 |= 0x1;
			else
				BYTE_0x9 &= (u8)~0x1;
		}

		nw4r::ut::Color getClearColor() const { return mClearColor; }
		void setClearColor(nw4r::ut::Color color) { mClearColor = color; }

		u8 mRetraceWait; // at 0x8
		volatile u8 BYTE_0x9;
		u32 mRetraceCount; // at 0xC
		u32 mFrameCount; // at 0x10
		nw4r::ut::Color mClearColor; // at 0x14
		u32 mClearZ; // at 0x20
		s32 mBeginTick; // at 0x1C
		s32 mDeltaTick; // at 0x20
		f32 mFrequency; // at 0x24
	};
}

#endif