#include "snd_StrmChannel.h"
#include "ut_lock.h"
#include "ut_algorithm.h"
#include <RevoSDK/OS/OSThread.h>
#include <RevoSDK/TRK/__mem.h>

namespace nw4r
{
    namespace snd
    {
        namespace detail
        {
            void StrmBufferPool::Setup(void *pBuf, u32 bufSize, int numBlocks)
            {
                if (numBlocks)
                {
                    ut::AutoInterruptLock lock;

                    mBuffer = pBuf;
                    mStrmBufferSize = bufSize;
                    mBlockSize = bufSize / numBlocks;
                    mBlockCount = numBlocks;
                    mAllocCount = 0;
                    memset(&mAllocFlags, 0, sizeof(mAllocFlags));
                }
            }

            void StrmBufferPool::Shutdown()
            {
                ut::AutoInterruptLock lock;

                mBuffer = NULL;
                mStrmBufferSize = 0;
                mBlockSize = 0;
                mBlockCount = 0;
            }

            void * StrmBufferPool::Alloc()
            {
                ut::AutoInterruptLock lock;

                if (mAllocCount >= mBlockCount)
                {
                    return NULL;
                }
                else
                {
                    int numBlockAligned8 = ut::RoundUp<int>(mBlockCount, 8) / 8;

                    for (int i = 0; i < numBlockAligned8; i++)
                    {
                        const u8 flag = mAllocFlags[i];
                        if (flag != 0xff)
                        {
                            u8 k = 1;
                            for (int j = 0; j < 8; j++, k <<= 1)
                            {
                                if ((flag & k) == 0)
                                {
                                    mAllocFlags[i] |= k;
                                    mAllocCount++;

                                    const void * p = ut::AddOffsetToPtr<u32>(mBuffer, mBlockSize * (j + i * 8));
                                    return const_cast<void *>(p);
                                }
                            }
                        }
                    }
                }

                return NULL;
            }

            void StrmBufferPool::Free(void *p)
            {
                ut::AutoInterruptLock lock;

                u32 totalBlockSize = ut::GetOffsetFromPtr(mBuffer, p);
                u32 blockCount = totalBlockSize / mBlockSize;
                u32 bitToClear = 1 << (blockCount & 7);

                mAllocFlags[blockCount / 8] &= ~bitToClear;
                mAllocCount--;
            }
        }
    }
}