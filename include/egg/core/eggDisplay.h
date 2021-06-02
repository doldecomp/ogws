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
		volatile char UNK_0x1[3];

		Display(u8);
		void copyEFBtoXFB();
		void calcFrequency();
		virtual void beginFrame();
		virtual void beginRender();
		virtual void endRender();
		virtual void endFrame();
		virtual u32 getTickPerFrame();

		u8 BYTE_0x8;
		volatile char BYTE_0x9;
		UNKWORD WORD_0xC;
		UNKWORD WORD_0x10;
		nw4r::ut::Color mColor; // at 0x14
		UNKWORD WORD_0x18;
		s32 mBeginTick; // at 0x1C
		s32 mDeltaTick; // at 0x20
		f32 mFrequency; // at 0x24
	};
}

#endif