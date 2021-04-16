#ifndef NW4R_SND_TASKTHREAD_H
#define NW4R_SND_TASKTHREAD_H
#include "types_nw4r.h"
#include <RevoSDK/OS/OSThread.h>

namespace nw4r
{
    namespace snd
    {
        namespace detail
        {
            struct TaskThread
            {
                static int ThreadFunc(void *);
                
                TaskThread();
                ~TaskThread();
                bool Create(s32, void *, u32);
                void Destroy();

                OSThread mThread; // at 0x0
                void * mStackEnd; // at 0x318
                u8 BYTE_0x31C;
                bool mIsAlive; // at 0x31D
            };
        }
    }
}

#endif