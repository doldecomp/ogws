#ifndef NW4R_UT_DVD_FILE_STREAM
#define NW4R_UT_DVD_FILE_STREAM
#include "ut_IOStream.h"
#include "ut_FileStream.h"
#include "ut_algorithm.h"
#include <RevoSDK/DVD/dvd.h>

namespace nw4r
{
	namespace ut
	{
		struct DvdFileStream : FileStream
		{
			// For the async callbacks
			struct FileInfoStreamPair
			{
				union
				{
					DVDFileInfo mFileInfo;
					DVDCommandBlock mCmdBlock;
				};
				DvdFileStream *mStrm;
			};

			inline void Initialize_()
			{
				BOOL_0x6D = false;
				BOOL_0x6E = false;
				BOOL_0x4 = false;
				WORD_0x68 = 2;
				mIsBusy = false;
				ASYNC_0xC = NULL;
				PTR_0x10 = NULL;
				WORD_0x8 = 0;
				ASYNC_0x1C = NULL;
				BYTE_0x24 = 0;
				PTR_0x20 = NULL;
				THIS_0x64 = this;
			}

			inline bool Open(s32 r4)
			{
				if (BOOL_0x6D)
				{
					Close();
				}

				if (DVDFastOpen(r4, &mFileInfo))
				{
					mPosition.SetFileSize(mFileInfo.WORD_0x34);
					mPosition.Seek(0, 0);
					BOOL_0x6D = true;
					BOOL_0x6E = true;
					BOOL_0x4 = true;
					return true;
				}
				return false;
			}

			inline bool Open(const DVDFileInfo *pInfo, bool b)
			{
				if (BOOL_0x6D)
				{
					Close();
				}

				mFileInfo = *pInfo;
				mPosition.SetFileSize(mFileInfo.WORD_0x34);
				mPosition.Seek(0, 0);
				BOOL_0x6D = false;
				BOOL_0x6E = b;
				BOOL_0x4 = true;
				return true;
			}

			// Clamps read length from going beyond the amount
			// of data left in the buffer
			inline u32 AdjustReadLength_(u32 val)
			{
				u32 pos = mPosition.Tell();
				u32 size = mPosition.GetFileSize();
				
				u32 totalBytes = RoundUp<u32>(size, 32);
				u32 futurePosition = RoundUp<u32>(pos + val, 32);
				
				if (futurePosition > totalBytes)
				{
					val = RoundUp<u32>(size - pos, 32);
				}

				return val;
			}

			static void DvdAsyncCallback_(s32, DVDFileInfo *);
			static void DvdCBAsyncCallback_(s32, DVDCommandBlock *);
			
			virtual ~DvdFileStream();
			
			DvdFileStream(s32);
			DvdFileStream(const DVDFileInfo *, bool);
			void Close();
			int Read(void *, u32);
			bool ReadAsync(void *, u32, AsyncFunctor, void *);
			virtual UNKWORD Peek(void *, u32);
			virtual bool PeekAsync(void *, u32, AsyncFunctor, void *);
			void Seek(s32, u32);
			UNKTYPE Cancel();
			bool CancelAsync(AsyncFunctor, void *);
			u32 GetBufferAlign() const;
			u32 GetSizeAlign() const;
			u32 GetOffsetAlign() const;
			bool CanCancel() const;
			bool CanWrite() const;
			bool CanRead() const;
			bool CanSeek() const;
			bool CanAsync() const;
			u32 GetSize() const;
			u32 Tell() const;
			bool IsBusy() const;
			const detail::RuntimeTypeInfo * GetRuntimeTypeInfo() const;

			FilePosition mPosition; // at 0x14
			AsyncFunctor ASYNC_0x1C; // at 0x1C
			void * PTR_0x20;
			volatile bool BYTE_0x24;
			volatile char UNK_0x25[3];
			DVDFileInfo mFileInfo; // at 0x28
			DvdFileStream *THIS_0x64;
			UNKWORD WORD_0x68;
			volatile bool mIsBusy; // at 0x6C
			bool BOOL_0x6D;
			bool BOOL_0x6E;

			static detail::RuntimeTypeInfo typeInfo;
		};
	}
}
#endif