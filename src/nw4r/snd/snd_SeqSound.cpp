#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {
namespace detail {

NW4R_UT_RTTI_DEF_DERIVED(SeqSound, BasicSound);

SeqSound::SeqSound(SoundInstanceManager<SeqSound>* pManager)
    // TODO: Fakematch
    : mTempSpecialHandle(reinterpret_cast<SeqSoundHandle*>(
          mPreparedFlag = mLoadingFlag = false)),
      mManager(pManager),
      mStartOffset(0),
      mFileStream(NULL) {

    OSInitMutex(&mMutex);
}

void SeqSound::InitParam() {
    BasicSound::InitParam();
    mStartOffset = 0;
}

SeqPlayer::SetupResult SeqSound::Setup(SeqTrackAllocator* pAllocator,
                                       u32 allocTrackFlags, int voices,
                                       NoteOnCallback* pCallback) {
    InitParam();
    return mSeqPlayer.Setup(pAllocator, allocTrackFlags, voices, pCallback);
}

void SeqSound::Prepare(const void* pBase, s32 seqOffset,
                       SeqPlayer::OffsetType startType, int startOffset) {
    mSeqPlayer.SetSeqData(pBase, seqOffset);
    Skip(startType, startOffset);

    mPreparedFlag = true;
}

void SeqSound::Prepare(ut::FileStream* pStream, s32 seqOffset,
                       SeqPlayer::OffsetType startType, int startOffset) {
    mFileStream = pStream;
    mSeqOffset = seqOffset;
    mStartOffsetType = startType;
    mStartOffset = startOffset;

    if (!LoadData(NotifyLoadAsyncEndSeqData, this)) {
        Shutdown();
    }
}

void SeqSound::NotifyLoadAsyncEndSeqData(bool success, const void* pBase,
                                         void* pCallbackArg) {
    SeqSound* p = static_cast<SeqSound*>(pCallbackArg);

    p->mLoadingFlag = false;

    if (!success) {
        p->Stop(0);
    } else {
        p->mSeqPlayer.SetSeqData(pBase, p->mSeqOffset);

        if (p->mStartOffset > 0) {
            p->mSeqPlayer.Skip(p->mStartOffsetType, p->mStartOffset);
        }

        p->mPreparedFlag = true;
    }
}

void SeqSound::Skip(SeqPlayer::OffsetType offsetType, int offset) {
    if (offset > 0) {
        mSeqPlayer.Skip(offsetType, offset);
    }
}

void SeqSound::Shutdown() {
    if (mLoadingFlag) {
        TaskManager::GetInstance().CancelTask(&mLoadTask);
    }

    if (mFileStream) {
        mFileStream->Close();
        mFileStream = NULL;
    }

    BasicSound::Shutdown();
    mManager->Free(this);
}

void SeqSound::SetTempoRatio(f32 tempo) {
    mSeqPlayer.SetTempoRatio(tempo);
}

void SeqSound::SetChannelPriority(int priority) {
    mSeqPlayer.SetChannelPriority(priority);
}

void SeqSound::SetReleasePriorityFix(bool flag) {
    mSeqPlayer.SetReleasePriorityFix(flag);
}

void SeqSound::SetPlayerPriority(int priority) {
    BasicSound::SetPlayerPriority(priority);
    mManager->UpdatePriority(this, BasicSound::CalcCurrentPlayerPriority());
}

void SeqSound::SetTrackVolume(u32 trackFlags, f32 volume) {
    mSeqPlayer.SetTrackVolume(trackFlags, volume);
}

void SeqSound::SetTrackPitch(u32 trackFlags, f32 pitch) {
    mSeqPlayer.SetTrackPitch(trackFlags, pitch);
}

bool SeqSound::WriteVariable(int i, s16 value) {
    mSeqPlayer.SetLocalVariable(i, value);
    return true;
}

bool SeqSound::WriteGlobalVariable(int i, s16 value) {
    SeqPlayer::SetGlobalVariable(i, value);
    return true;
}

bool SeqSound::IsAttachedTempSpecialHandle() {
    return mTempSpecialHandle != NULL;
}

void SeqSound::DetachTempSpecialHandle() {
    mTempSpecialHandle->DetachSound();
}

bool SeqSound::LoadData(SeqLoadCallback pCalllback, void* pCallbackArg) {
    mLoadingFlag = true;

    PlayerHeap* pHeap = static_cast<BasicSound*>(pCallbackArg)->GetPlayerHeap();
    if (pHeap == NULL) {
        return false;
    }

    u32 size = mFileStream->GetSize();
    void* pData = pHeap->Alloc(size);

    if (pData == NULL) {
        return false;
    }

    mLoadTask.fileStream = mFileStream;
    mLoadTask.buffer = pData;
    mLoadTask.bufferSize = size;
    mLoadTask.callback = pCalllback;
    mLoadTask.callbackData = this;

    TaskManager::GetInstance().AppendTask(&mLoadTask);
    return true;
}

SeqSound::SeqLoadTask::SeqLoadTask()
    : fileStream(NULL), buffer(NULL), callback(NULL), callbackData(NULL) {}

void SeqSound::SeqLoadTask::Execute() {
    fileStream->Seek(0, ut::FileStream::SEEK_BEG);

    s32 bytesRead = fileStream->Read(buffer, bufferSize);
    fileStream = NULL;

    if (bytesRead == DVD_RESULT_CANCELED) {
        if (callback != NULL) {
            callback(false, NULL, callbackData);
        }
    } else if (bytesRead != bufferSize) {
        if (callback != NULL) {
            callback(false, NULL, callbackData);
        }
    } else {
        SeqFileReader reader(buffer);
        const void* pBase = reader.GetBaseAddress();

        if (callback != NULL) {
            callback(true, pBase, callbackData);
        }
    }
}

void SeqSound::SeqLoadTask::Cancel() {
    if (callback != NULL) {
        callback(false, NULL, callbackData);
    }
}

void SeqSound::SeqLoadTask::OnCancel() {
    callback = NULL;

    if (fileStream != NULL) {
        fileStream->Cancel();
    }
}

} // namespace detail
} // namespace snd
} // namespace nw4r
