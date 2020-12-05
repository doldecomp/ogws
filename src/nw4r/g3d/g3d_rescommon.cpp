#include "g3d_rescommon.h"
#include "string.h"

namespace nw4r
{
    namespace g3d
    {

        bool ResName::operator==(ResName other) const
        {
            if (this->GetLength() == other.GetLength())
            {
                return strcmp(this->GetName(), other.GetName()) == 0;
            }
            return false;
        }

        namespace detail
        {
            void ResWriteBPCmd(u8 *res, u32 arg)
            {
                ResWrite_u8(res, FIFO_ACCESS_BP);
                ResWrite_u32(res + 1, arg);
            }

            void ResWriteBPCmd(u8 *res, u32 arg, u32 writeMask)
            {
                arg &= writeMask;
                
                ResWrite_u8(res, FIFO_ACCESS_BP);
                ResWrite_u32(res + 1, arg | (ResRead_u32(res + 1) & ~writeMask));
            }

            void ResWriteCPCmd(u8 *res, u8 arg1, u32 arg2)
            {
                ResWrite_u8(res, FIFO_ACCESS_CP);
                ResWrite_u8(res + 1, arg1);
                ResWrite_u32(res + 2, arg2);
            }

            void ResWriteXFCmd(u8 *res, u16 arg1, u32 arg2)
            {
                ResWrite_u8(res, FIFO_ACCESS_XF);
                ResWrite_u16(res + 1, 0x0000);
                ResWrite_u16(res + 3, arg1);
                ResWrite_u32(res + 5, arg2);
            }

            void ResWriteSSMask(u8 *res, u32 arg)
            {
                u32 arg2 = ResRead_u32(res + 1);
                arg2 |= arg;
                ResWriteBPCmd(res, arg2 | (0xFE << 24));
            }
        }
    }
}