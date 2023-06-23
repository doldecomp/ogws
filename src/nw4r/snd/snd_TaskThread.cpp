#pragma ipa file
#include "snd_TaskThread.h"
#include "snd_TaskManager.h"

namespace nw4r
{
    namespace snd
    {
        namespace detail
        {
            TaskThread::TaskThread()
            {
                mStackEnd = NULL;
                mIsExiting = false;
                mIsAlive = false;
            }

            TaskThread::~TaskThread()
            {
                if (mIsAlive) Destroy();
            }

            bool TaskThread::Create(s32 r4, void *stack, u32 r6)
            {
                if (mIsAlive) Destroy();

                if (!OSCreateThread(&mThread, ThreadFunc, &mThread, (void *)((u32)stack + r6), r6, r4, 0))
                    return false;

                mStackEnd = stack;
                mIsExiting = false;
                mIsAlive = true;
                OSResumeThread(&mThread);
                return true;
            }

            void TaskThread::Destroy()
            {
                if (mIsAlive)
                {
                    mIsExiting = true;
                    TaskManager *pInstance = TaskManager::GetInstance();
                    pInstance->CancelWaitTask();
                    OSJoinThread(&mThread, 0);
                    mIsAlive = false;
                }
            }

            void* TaskThread::ThreadFunc(void *p)
            {
                TaskThread *pThread = (TaskThread *)p;

                while (!pThread->mIsExiting)
                {
                    TaskManager *pInstance = TaskManager::GetInstance();
                    pInstance->WaitTask();

                    if (pThread->mIsExiting) break;
                    pInstance = TaskManager::GetInstance();
                    pInstance->ExecuteTask();
                }

                return NULL;
            }
        }
    }
}