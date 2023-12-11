#pragma ipa file
#include <string.h>
#include <new>
#include <OSCache.h>
#include "ut_algorithm.h"
#include "snd_NandSoundArchive.h"

namespace nw4r
{
    using namespace ut;
    
    namespace snd
    {
        using namespace detail;
        
        struct NandSoundArchive::NandFileStream : public ut::NandFileStream
        {
            int mStartOffset; // at 0x16c
            int mSize; // at 0x170
            
            NandFileStream(const NANDFileInfo *, u32, u32); //inlined
            NandFileStream(const char *, u32, u32); //inlined
            
            virtual ~NandFileStream() {} // at 0xC
            virtual s32 Read(void *, u32); // at 0x14
            virtual u32 GetSize() const; // at 0x40
            virtual void Seek(s32, u32); // at 0x44
            virtual u32 Tell() const; // at 0x58
        };

        NandSoundArchive::NandSoundArchive() : mOpenFlag(false) {}
        
        NandSoundArchive::~NandSoundArchive()
        {
            Close();
        }
        
        bool NandSoundArchive::Open(const char * pPath)
        {
            char currentDir[0x40];
            char externalFileRoot[0x100];
            
            if (mOpenFlag) Close();
            
            if (NANDOpen(pPath, &mFileInfo, 1)) return false;
            
            mOpenFlag = true;
            
            if (!LoadFileHeader()) return false;
            
            NANDGetCurrentDir(currentDir);
            
            u32 curDirLength = strlen(currentDir);
            
            strncpy(externalFileRoot, currentDir, curDirLength);
            
            for (int i = strlen(pPath) - 1; i >= 0; i--)
            {
                if (pPath[i] == '/' || pPath[i] == '\\')
                {
                    strncat(externalFileRoot, pPath, i);
                    externalFileRoot[curDirLength + i] = '\0';
                    break;
                }
            }
            
            SoundArchive::SetExternalFileRoot(externalFileRoot);
            
            return true;
        }
        
        void NandSoundArchive::Close()
        {
            if (mOpenFlag)
            {
                NANDClose(&mFileInfo);
                mOpenFlag = false;
            }
            
            SoundArchive::Shutdown();
        }
        
        FileStream * NandSoundArchive::OpenStream(void * pBuffer, int bufferSize, u32 startOffset, u32 streamSize) const
        {
            if (mOpenFlag) return NULL;
            
            if (bufferSize < sizeof(NandFileStream)) return NULL;
            
            return new (pBuffer) NandFileStream(&mFileInfo, startOffset, streamSize);
        }
        
        FileStream * NandSoundArchive::OpenExtStream(void * pBuffer, int bufferSize,  const char * pPath, u32 startOffset, u32 streamSize) const
        {
            if (mOpenFlag) return NULL;
            
            if (bufferSize < sizeof(NandFileStream)) return NULL;
            
            NandFileStream * pExtStream = new (pBuffer) NandFileStream(pPath, startOffset, streamSize);
            
            if (pExtStream->BOOL_0x4)
            {
                pExtStream->~NandFileStream();
                return NULL;
            }
            
            return pExtStream;
        }
        
        int NandSoundArchive::detail_GetRequiredStreamBufferSize() const
        {
            return sizeof(NandFileStream);
        }
        
        #ifdef __DECOMP_NON_MATCHING
        bool NandSoundArchive::LoadFileHeader()
        {
            u8 unalignedHeader[0x68];

            static const u32 headerAlignSize = RoundUp<u32>(sizeof(SoundArchiveFile::Header), 32);
            void * alignedHeader = RoundUp<u8 *>(unalignedHeader, 32);
            
            if (NANDSeek(&mFileInfo, 0, 0)) return false;
            
            u32 bytesRead = NANDRead(&mFileInfo, alignedHeader, headerAlignSize);
            
            if (bytesRead != headerAlignSize) return false;
            
            mFileReader.Init(alignedHeader);
            SoundArchive::Setup(&mFileReader);
            
            return true;
        }
        #else
        #error This file has yet to be decompiled accurately. Use "snd_NandSoundArchive.s" instead.
        #endif

        #ifdef __DECOMP_NON_MATCHING
        bool NandSoundArchive::LoadHeader(void * pBuffer, u32 bufferSize)
        {
            u32 infoChunkSize = mFileReader.GetInfoChunkSize();
            s32 infoChunkOffset = mFileReader.GetInfoChunkOffset();
            
            if (bufferSize < infoChunkSize) return false;
            
            s32 currentOffset = NANDSeek(&mFileInfo, infoChunkOffset, 0);
            
            if (currentOffset != infoChunkOffset) return false;
            
            u32 bytesRead = NANDRead(&mFileInfo, pBuffer, infoChunkSize);
            
            if (bytesRead != infoChunkSize) return false;
            
            mFileReader.SetInfoChunk(pBuffer, infoChunkSize);
            
            return true;
        }
        #else
        #error This file has yet to be decompiled accurately. Use "snd_NandSoundArchive.s" instead.
        #endif
        
        #ifdef __DECOMP_NON_MATCHING
        bool NandSoundArchive::LoadLabelStringData(void * pBuffer, u32 bufferSize)
        {
            u32 labelStringChunkSize = mFileReader.GetLabelStringChunkSize();
            s32 labelStringChunkOffset = mFileReader.GetLabelStringChunkOffset();
            
            if (bufferSize < labelStringChunkSize) return false;
            
            s32 currentOffset = NANDSeek(&mFileInfo, labelStringChunkOffset, 0);
            
            if (currentOffset != labelStringChunkOffset) return false;
            
            u32 bytesRead = NANDRead(&mFileInfo, pBuffer, labelStringChunkSize);
            
            if (bytesRead != labelStringChunkSize) return false;
            
            mFileReader.SetStringChunk(pBuffer, labelStringChunkSize);
            
            return true;
        }
        #else
        #error This file has yet to be decompiled accurately. Use "snd_NandSoundArchive.s" instead.
        #endif

        NandSoundArchive::NandFileStream::NandFileStream(const NANDFileInfo * pFileInfo, u32 startOffset, u32 size)
            : ut::NandFileStream(pFileInfo, 1, false), mStartOffset(startOffset), mSize(size)
        {
            if (BOOL_0x4)
            {
                if (!mSize) mSize = mPosition.GetFileSize();
                
                ut::NandFileStream::Seek(mStartOffset, 0);
            }
        }

        NandSoundArchive::NandFileStream::NandFileStream(const char * pFileName, u32 startOffset, u32 size)
            : ut::NandFileStream(pFileName, 1), mStartOffset(startOffset), mSize(size)
        {
            if (BOOL_0x4)
            {
                if (!mSize) mSize = mPosition.GetFileSize();
                
                ut::NandFileStream::Seek(mStartOffset, 0);
            }
        }

        int NandSoundArchive::NandFileStream::Read(void * pBuffer, u32 count)
        {
            u32 endOffset = mStartOffset + mSize;
            
            if (mPosition.Tell() + count > endOffset) count = RoundUp<u32>(endOffset - mPosition.Tell(), 0x20);
            
            int ret = ut::NandFileStream::Read(pBuffer, count);
            
            DCStoreRange(pBuffer, count);
            
            return ret;
        }
        
        void NandSoundArchive::NandFileStream::Seek(s32 offset, u32 origin)
        {
            switch (origin)
            {
                case 0:
                    offset += mStartOffset;
                    break;
                case 1:
                    offset += mPosition.Tell();
                    break;
                case 2:
                    offset = mStartOffset + mSize - offset;
                    break;
                default:
                    return;
            }
            
            if (offset < mStartOffset)
            {
                offset = mStartOffset;
            }
            else if (offset > mStartOffset + mSize)
            {
                offset = mStartOffset + mSize;
            }
            
            ut::NandFileStream::Seek(offset, 0);
        }
        
        u32 NandSoundArchive::NandFileStream::GetSize() const
        {
            return mSize;
        }
        
        u32 NandSoundArchive::NandFileStream::Tell() const
        {
            return mPosition.Tell() - mStartOffset;
        }
        
        const void * NandSoundArchive::detail_GetWaveDataFileAddress(u32) const
        {
            return NULL;
        }
        
        const void * NandSoundArchive::detail_GetFileAddress(u32) const
        {
            return NULL;
        }
    }
}