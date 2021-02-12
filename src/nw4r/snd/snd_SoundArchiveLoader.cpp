#include "snd_SoundArchiveLoader.h"
#include "snd_SoundArchive.h"
#include "ut_algorithm.h"
#include "ut_lock.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		namespace detail
		{
			SoundArchiveLoader::SoundArchiveLoader(const SoundArchive & archive) : mArchive(archive), mFileStream(NULL)
			{
				OSInitMutex(&mMutex);
			}
			
			SoundArchiveLoader::~SoundArchiveLoader() {}
			
			void * SoundArchiveLoader::LoadGroup(u32 index, SoundMemoryAllocatable * pAllocatable, void ** pWaveDataPointer, u32 alignment)
			{
				//r31 <- this
				//r26 <- index
				//r25 <- pAllocatable
				//r23 <- pWaveDataPointer
				//r24 <- alignment
				ut::detail::AutoLock<OSMutex> lock(mMutex);
				FileStreamHandle handle(mArchive.detail_OpenGroupStream(index, mBuffer, sizeof mBuffer)); // at r29
				
				SoundArchive::GroupInfo groupInfo; // at 0x8
				
				if (!handle) return NULL;
				
				//80043518
				if (!handle->CanSeek() || !handle->CanRead()) return NULL;
				
				//80043578
				
				void * pGroup = pAllocatable->Alloc(handle->GetSize()); // at r27
				
				if (!pGroup) return NULL;
				
				mFileStream = handle.mFileStream;
				
				if (!alignment)
				{
					//800435E8
					int bytesRead = handle->Read(pGroup, handle->GetSize());
					
					if (bytesRead < 0)
					{
						mFileStream = NULL;
						return NULL;
					}
				}
				else
				{
					//80043654
					u8 * pBuffer = static_cast<u8 *>(pGroup); // at r28
					u32 bytesLeft = handle->GetSize(); // at r30
					
					while (bytesLeft)
					{
						int bytesRead = handle->Read(pBuffer, Min<u32>(alignment, bytesLeft));
						
						if (bytesRead < 0)
						{
							mFileStream = NULL;
							return NULL;
						}
						
						if (bytesLeft > bytesRead)
						{
							bytesLeft -= bytesRead;
							pBuffer += bytesRead;
						}
						else
						{
							bytesLeft = 0;
						}
					}
				}
				//800436F8
				mFileStream = NULL;
				
				if (!mArchive.detail_ReadGroupInfo(index, &groupInfo)) return NULL;
				
				//80043744
				if (groupInfo.INT_0x14)
				{
					//80043750
					FileStreamHandle waveDataHandle(mArchive.detail_OpenGroupWaveDataStream(index, mBuffer, sizeof mBuffer));
					
					if (!waveDataHandle) return NULL;
					
					//800437B0
					if (!waveDataHandle->CanSeek() || !waveDataHandle->CanRead()) return NULL;
					
					//8004382C
					void * pGroupWaveData = pAllocatable->Alloc(waveDataHandle->GetSize()); // at r26
					
					if (!pGroupWaveData) return NULL;
					
					mFileStream = waveDataHandle.mFileStream;
					
					//800438AC
					if (!alignment)
					{
						//800438B8
						int bytesRead = waveDataHandle->Read(pGroupWaveData, waveDataHandle->GetSize());
						
						if (bytesRead < 0)
						{
							mFileStream = NULL;
							return NULL;
						}
					}
					else
					{
						//8004393C
						u8 * pBuffer = static_cast<u8 *>(pGroupWaveData); // at r30
						u32 bytesLeft = waveDataHandle->GetSize(); // at r25
						
						while (bytesLeft)
						{
							int bytesRead = waveDataHandle->Read(pBuffer, Min<u32>(alignment, bytesLeft));
							
							if (bytesRead < 0)
							{
								mFileStream = NULL;
								return NULL;
							}
							
							if (bytesLeft > bytesRead)
							{
								bytesLeft -= bytesRead;
								pBuffer += bytesRead;
							}
							else
							{
								bytesLeft = 0;
							}
						}
					}
					
					//800439FC
					mFileStream = NULL;
					
					if (pWaveDataPointer) *pWaveDataPointer = pGroupWaveData;
				}
				else if (pWaveDataPointer)
				{
					//80043A30
					*pWaveDataPointer = NULL;
				}
				
				return pGroup;
			}
		}
	}
}