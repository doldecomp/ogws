#include "snd_PlayerHeap.h"
#include "snd_TaskManager.h"
#include "snd_SeqFile.h"
#include "snd_SeqSoundHandle.h"
#include "snd_SeqSound.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		namespace detail
		{
			SeqSound::SeqSound(SoundInstanceManager<SeqSound> * pManager)
				: mPlayer(),
				//mLoadingFlag(false), mPreparedFlag(false),
				mTempSpecialHandle((SeqSoundHandle *)(mPreparedFlag = mLoadingFlag = false)), mManager(pManager),
				mOffset(0), mFileStream(NULL),
				mLoadTask()
			{
				OSInitMutex(&MUTEX_0x434);
			}
			
			UNKTYPE SeqSound::InitParam()
			{
				BasicSound::InitParam();
				
				mOffset = 0;
			}
			
			UNKTYPE SeqSound::Setup(SeqTrackAllocator * pAllocator, u32 r29, int r30, NoteOnCallback * r31)
			{
				InitParam();
				
				mPlayer.Setup(pAllocator, r29, r30, r31);
			}
			
			UNKTYPE SeqSound::Skip(SeqPlayer::OffsetType offsetType, int offset)
			{
				if (offset > 0) mPlayer.Skip(offsetType, offset);
			}
			
			void SeqSound::Prepare(const void * r_4, s32 r_5, SeqPlayer::OffsetType offsetType, int offset)
			{
				mPlayer.SetSeqData(r_4, r_5);
				
				Skip(offsetType, offset);
				
				mPreparedFlag = true;
			}
			
			bool SeqSound::LoadData(SeqLoadCallback callback, void * ptr)
			{
				PlayerHeap * pPlayerHeap = static_cast<PlayerHeap *>(ptr);
				mLoadingFlag = true;
				
				if (!pPlayerHeap) return false;
				
				u32 size = mFileStream->GetSize(); // at r31
				void * pData = pPlayerHeap->Alloc(size);
				
				if (!pData) return false;
				
				mLoadTask.mData = pData;
				mLoadTask.mFileStream = mFileStream;
				mLoadTask.mSize = size;
				mLoadTask.mCallback = callback;
				mLoadTask.mSound = this;
				
				TaskManager::GetInstance()->AppendTask(&mLoadTask, TaskManager::PRIORITY_1);
				
				return true;
			}
			
			void SeqSound::Prepare(FileStream * pFileStream, s32 r_5, SeqPlayer::OffsetType offsetType, int offset)
			{
				mFileStream = pFileStream;
				INT_0x1FC = r_5;
				mOffsetType = offsetType;
				mOffset = offset;
				
				if (!LoadData(NotifyLoadAsyncEndSeqData, mPlayerHeap)) Shutdown();
			}
			
			void SeqSound::NotifyLoadAsyncEndSeqData(bool success, const void * pSeqData, void * ptr)
			{
				SeqSound * pSound = static_cast<SeqSound *>(ptr);
				pSound->mLoadingFlag = false;
				
				if (!success)
				{
					pSound->Stop(0);
				}
				else
				{
					pSound->mPlayer.SetSeqData(pSeqData, pSound->INT_0x1FC);
					
					if (pSound->mOffset > 0) pSound->mPlayer.Skip(pSound->mOffsetType, pSound->mOffset);
					
					pSound->mPreparedFlag = true;
				}
			}
			
			void SeqSound::Shutdown()
			{
				if (mLoadingFlag) TaskManager::GetInstance()->CancelTask(&mLoadTask);
				
				if (mFileStream)
				{
					mFileStream->Close();
					mFileStream = NULL;
				}
				
				BasicSound::Shutdown();
				
				mManager->Free(this);
			}
			
			UNKTYPE SeqSound::SetTempoRatio(float tempoRatio)
			{
				mPlayer.SetTempoRatio(tempoRatio);
			}
			
			UNKTYPE SeqSound::SetChannelPriority(int channelPriority)
			{
				mPlayer.SetChannelPriority(channelPriority);
			}
			
			UNKTYPE SeqSound::SetReleasePriorityFix(bool r_4)
			{
				mPlayer.SetReleasePriorityFix(r_4);
			}
			
			UNKTYPE SeqSound::SetPlayerPriority(int playerPriority)
			{
				BasicSound::SetPlayerPriority(playerPriority);
				
				mManager->UpdatePriority(this, BasicSound::CalcCurrentPlayerPriority());
			}
			
			UNKTYPE SeqSound::SetTrackVolume(u32 r_3, float f_1)
			{
				mPlayer.SetTrackVolume(r_3, f_1);
			}
			
			UNKTYPE SeqSound::SetTrackPitch(u32 r_3, float f_1)
			{
				mPlayer.SetTrackPitch(r_3, f_1);
			}
			
			bool SeqSound::WriteVariable(int r_4, short r_5)
			{
				mPlayer.SetLocalVariable(r_4, r_5);
				
				return true;
			}
			
			bool SeqSound::WriteGlobalVariable(int r_3, short r_4)
			{
				SeqPlayer::SetGlobalVariable(r_3, r_4);
				
				return true;
			}
			
			bool SeqSound::IsAttachedTempSpecialHandle()
			{
				return mTempSpecialHandle;
			}
			
			UNKTYPE SeqSound::DetachTempSpecialHandle()
			{
				mTempSpecialHandle->DetachSound();
			}
			
			void SeqSound::SeqLoadTask::Execute()
			{
				mFileStream->Seek(0, 0);
				UNKWORD read = mFileStream->Read(mData, mSize);
				mFileStream = NULL;
				
				if (read == -3)
				{
					if (mCallback) mCallback(false, NULL, mSound);
				}
				else if (read != mSize)
				{
					if (mCallback) mCallback(false, NULL, mSound);
				}
				else
				{
					SeqFileReader fileReader(mData);
					const void * pBaseAddress = fileReader.GetBaseAddress();
					
					if (mCallback) mCallback(true, pBaseAddress, mSound);
				}
			}
			
			void SeqSound::SeqLoadTask::Cancel()
			{
				if (mCallback) mCallback(false, NULL, mSound);
			}
			
			void SeqSound::SeqLoadTask::OnCancel()
			{
				mCallback = NULL;
				
				if (mFileStream) mFileStream->Cancel();
			}
			
			ut::detail::RuntimeTypeInfo SeqSound::typeInfo(&BasicSound::typeInfo);
		}
	}
}