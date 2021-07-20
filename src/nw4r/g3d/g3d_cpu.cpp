#include "g3d_cpu.h"

namespace nw4r
{
    namespace g3d
    {
        namespace detail
        {
            void Copy32ByteBlocks(void *dest, const void *src, u32 n)
            {
                n /= 32;
                register const char *csrc = (const char *)src;
                register char *cdest = (char *)dest;

                while (n-- > 0)
                {
                    asm
                    {
                        lfd f0, 0(csrc)
                        stfd f0, 0(cdest)

                        lfd f1, 8(csrc)
                        stfd f1, 8(cdest)

                        lfd f0, 16(csrc)
                        stfd f0, 16(cdest)
                        
                        lfd f1, 24(csrc)
                        stfd f1, 24(cdest)
                    }

                    cdest += 32;
                    csrc += 32;
                }
            }

            void ZeroMemory32ByteBlocks(void *dest, u32 n)
            {
                n /= 32;
                register char *cdest = (char *)dest;

                while (n-- > 0)
                {
                    register f32 zero = 0.0f;
                    asm
                    {
                        psq_st zero, 0(cdest), 0, 0
                        psq_st zero, 8(cdest), 0, 0
                        psq_st zero, 16(cdest), 0, 0
                        psq_st zero, 24(cdest), 0, 0
                    }

                    cdest += 32;
                }
            }
        }
    }
}