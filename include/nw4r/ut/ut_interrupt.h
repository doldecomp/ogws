#ifndef NW4R_UT_INTERRUPT
#define NW4R_UT_INTERRUPT
#include <RevoSDK/OS/OSInterrupt.h>

namespace nw4r
{
	namespace ut
	{
		struct AutoInterruptLock
		{
			UNKWORD WORD_0x0;
			
			inline AutoInterruptLock() : WORD_0x0(OSDisableInterrupts()) {}
			inline ~AutoInterruptLock() { OSRestoreInterrupts(WORD_0x0); }
		};
	}
}

#endif