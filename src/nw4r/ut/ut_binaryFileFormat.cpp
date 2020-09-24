#include "ut_binaryFileFormat.h"

#define BOM_BIG_ENDIAN 0xFEFF
#define BOM_LITTLE_ENDIAN 0xFFFE

namespace nw4r
{
	namespace ut
	{
		bool IsValidBinaryFile(const BinaryFileHeader * header, u32 fileMagic, u16 fileVersion, u16 r6)
		{
			if (header->magic != fileMagic) return false;
			
			if (header->bom != BOM_BIG_ENDIAN) return false;
			
			if (header->version != fileVersion) return false;
			
			if (header->length < sizeof(BinaryFileHeader) + (r6 << 3)) return false;
			
			return header->blockCount >= r6;
		}
	}
}