#ifndef NW4R_UT_BINARY_FILE_FORMAT
#define NW4R_UT_BINARY_FILE_FORMAT
#include "types_nw4r.h"

namespace nw4r
{
	namespace ut
	{
		
		struct BinaryFileHeader
		{
			u32 magic; // File magic
			u16 bom; // Byte Order Mark
			u16 version; // File version
			u32 length; // Length of the file (including header)
			u16 headerLen; // Length of the header
			u16 sectionCount; // Number of sections
		};
		
		bool IsValidBinaryFile(const BinaryFileHeader *, u32, u16, u16);
	}
}

#endif