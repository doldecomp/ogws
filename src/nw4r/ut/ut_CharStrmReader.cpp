#include "ut_CharStrmReader.h"

namespace nw4r
{
	namespace ut
	{
		namespace
		{
			static inline bool IsSJISLeadByte(u8 byte)
			{
				return byte >= 0x81 && byte < 0xa0 || byte >= 0xe0;
			}
		}
		
		u16 CharStrmReader::ReadNextCharUTF8()
		{
			u16 ret;
			
			if ((GetChar<u8>(0) & 0x80) == 0)
			{
				ret = GetChar<u8>(0);
				StepStrm<u8>(1);
			}
			else if ((GetChar<u8>(0) & 0xE0) == 0xC0)
			{
				ret = ((GetChar<u8>(0) & 0x1f) << 6) | (GetChar<u8>(1) & 0x3f);
				StepStrm<u8>(2);
			}
			else
			{
				ret = ((GetChar<u8>(0) & 0x1f) << 12) | ((GetChar<u8>(1) & 0x3f) << 6) | (GetChar<u8>(2) & 0x3f);
				StepStrm<u8>(3);
			}
			
			return ret;
		}
		
		u16 CharStrmReader::ReadNextCharUTF16()
		{
			u16 ret = GetChar<u16>(0);
			
			StepStrm<u16>(1);
			
			return ret;
		}
		
		u16 CharStrmReader::ReadNextCharCP1252()
		{
			u16 ret = GetChar<u8>(0);
			
			StepStrm<u8>(1);
			
			return ret;
		}
		
		u16 CharStrmReader::ReadNextCharSJIS()
		{
			u16 ret;
			
			if (IsSJISLeadByte(GetChar<u8>(0)))
			{
				ret = (GetChar<u8>(0) << 8) | GetChar<u8>(1);
				StepStrm<u8>(2);
			}
			else
			{
				ret = GetChar<u8>(0);
				StepStrm<u8>(1);
			}
			
			return ret;
		}
	}
}