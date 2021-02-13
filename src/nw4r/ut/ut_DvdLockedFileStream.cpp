#include "ut_IOStream.h"
#include "ut_FileStream.h"
#include "ut_DvdFileStream.h"
#include <RevoSDK/OS/OSMutex.h>
#include <RevoSDK/OS/OSInterrupt.h>
#include "ut_DvdLockedFileStream.h"

namespace nw4r
{
	namespace ut
	{
		DvdLockedFileStream::DvdLockedFileStream(s32 id) : DvdFileStream(id)
		{
			InitMutex_();
		}
		
		DvdLockedFileStream::DvdLockedFileStream(const DVDFileInfo * file, bool b) : DvdFileStream(file, b)
		{
			InitMutex_();
		}
		
		DvdLockedFileStream::~DvdLockedFileStream()
		{
			
		}
		
		int DvdLockedFileStream::Read(void * buffer, u32 count)
		{
			OSLockMutex(&sMutex);
			int ret = this->DvdFileStream::Read(buffer, count);
			OSUnlockMutex(&sMutex);
			return ret;
		}
		
		UNKWORD DvdLockedFileStream::Peek(void * buffer, u32 count)
		{
			OSLockMutex(&sMutex);
			UNKWORD ret = this->DvdFileStream::Peek(buffer, count);
			OSUnlockMutex(&sMutex);
			return ret;
		}
		
		bool DvdLockedFileStream::CanAsync() const
		{
			return false;
		}
		
		bool DvdLockedFileStream::PeekAsync(void *, u32, AsyncFunctor, void *)
		{
			return false;
		}
		
		bool DvdLockedFileStream::ReadAsync(void *, u32, AsyncFunctor, void *)
		{
			return false;
		}
		
		const detail::RuntimeTypeInfo * DvdLockedFileStream::GetRuntimeTypeInfo() const
		{
			return &typeInfo;
		}
		
		detail::RuntimeTypeInfo DvdLockedFileStream::typeInfo(&DvdFileStream::typeInfo);
		
		OSMutex DvdLockedFileStream::sMutex;
		bool DvdLockedFileStream::sInitialized;
		
	}
}