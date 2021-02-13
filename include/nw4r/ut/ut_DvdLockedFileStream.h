#ifndef NW4R_UT_DVD_LOCKED_FILE_STREAM
#define NW4R_UT_DVD_LOCKED_FILE_STREAM
#include "ut_IOStream.h"
#include "ut_FileStream.h"
#include "ut_DvdFileStream.h"
#include <OSMutex.h>
#include <OSInterrupt.h>

namespace nw4r
{
	namespace ut
	{
		struct DvdLockedFileStream : DvdFileStream
		{
			DvdLockedFileStream(s32);
			DvdLockedFileStream(const DVDFileInfo *, bool);
			
			virtual ~DvdLockedFileStream();
			
			int Read(void *, u32);
			UNKWORD Peek(void *, u32);
			
			bool CanAsync() const;

			bool PeekAsync(void *, u32, AsyncFunctor, void *);
			bool ReadAsync(void *, u32, AsyncFunctor, void *);
			
			const detail::RuntimeTypeInfo * GetRuntimeTypeInfo() const;
			
			static bool sInitialized;
			static OSMutex sMutex;
			
			static detail::RuntimeTypeInfo typeInfo;
			
			inline void InitMutex_()
			{
				UNKWORD r31 = OSDisableInterrupts();
				
				if (!sInitialized)
				{
					OSInitMutex(&sMutex);
					sInitialized = true;
				}
				
				OSRestoreInterrupts(r31);
			}
			
		};
	}
}
#endif