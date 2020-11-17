#include "snd_SeqFile.h"
#include "ut_algorithm.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		namespace detail
		{
			bool SeqFileReader::IsValidFileHeader(const void * ptr)
			{
				const BinaryFileHeader * pFileHeader = static_cast<const BinaryFileHeader *>(ptr);
				
				if (pFileHeader->magic != 'RSEQ') return false;
				
				if (pFileHeader->version < 0x0100) return false;
				
				return pFileHeader->version <= 0x0100;
			}
			
			SeqFileReader::SeqFileReader(const void * ptr) : mFile(), PTR_0x4()
			{
				const SeqFile * pFile = static_cast<const SeqFile *>(ptr);
				
				if (IsValidFileHeader(ptr))
				{
					mFile = pFile;
					PTR_0x4 = (UNKBLOCK *)AddOffsetToPtr<u32>(ptr, pFile->OFFSET_0x10);
				}
			}
			
			const void * SeqFileReader::GetBaseAddress() const
			{
				return AddOffsetToPtr<u32>(PTR_0x4, PTR_0x4->OFFSET_0x8);
			}
		}
	}
}