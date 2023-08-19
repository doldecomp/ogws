#pragma ipa file
#pragma use_lmw_stmw on
#include <OS.h>
#include "eggTaskThread.h"
#include "eggAssert.h"

namespace EGG
{
	TaskThread::TaskThread(int jobCount, int r27_4, u32 size)
		: Thread(size, jobCount, r27_4, NULL), MSG_QUEUE_0x50(NULL)
	{
		resume();
	}
	
	TaskThread * TaskThread::create(int jobCount, int r27_4, u32 size, Heap * pHeap)
	{
		if (!pHeap) pHeap = Heap::getCurrentHeap();
		
		TaskThread * pTaskThread = new (pHeap, 4) TaskThread(jobCount, r27_4, size); // at r31
		
		if (!pTaskThread) return NULL;
		
		pTaskThread->mCurrentJob = NULL;
		pTaskThread->mJobs = new (pHeap, 4) TJob[jobCount];
		pTaskThread->mJobCount = jobCount;
		
		if (!pTaskThread->mJobs)
		{
			delete pTaskThread;
			return NULL;
		}
		
		for (int i = 0; i < jobCount; i++)
		{
			pTaskThread->mJobs[i].mFunction = NULL;
			
			pTaskThread->mJobs[i].clearFunctions();
		}
		
		return pTaskThread;
	}
	
	bool TaskThread::request(TFunction function, void * r5, OSMessage r6)
	{
		TJob * pTJob = findBlank();
		
		if (!pTJob) return false;
		
		pTJob->mFunction = function;
		pTJob->WORD_0x4 = r5;
		pTJob->MSG_0x8 = r6;
		
		bool success = sendMessage(pTJob);
		
		if (!success) pTJob->mFunction = NULL;
		
		return success;
	}
	
	OSMessageQueue * TaskThread::createTaskEndMessageQueue(int size, Heap * pHeap)
	{
		#line 378
		EGG_ASSERT(size > 0);
		
		sEndMesgBufSize = size;
		
		sEndMesgBuffer = (OSMessage *)Heap::alloc(size * sizeof(OSMessage), 4, pHeap);
		
		#line 389
		EGG_ASSERT(sEndMesgBuffer);
		
		OSInitMessageQueue(&sEndMesgQueue, sEndMesgBuffer, sEndMesgBufSize);
		
		return &sEndMesgQueue;
	}
	
	bool TaskThread::isTaskExist() const
	{
		for (int i = 0; i < mJobCount; i++)
		{
			if (mJobs[i].mFunction) return true;
		}
		return false;
	}
	
	TaskThread::~TaskThread() {}
	
	void TaskThread::onEnter()
	{
		if (mCurrentJob && mCurrentJob->mEnterFunction)
		{
			mCurrentJob->mEnterFunction(mCurrentJob->WORD_0x4);
		}
	}
	
	void TaskThread::onExit()
	{
		if (mCurrentJob && mCurrentJob->mExitFunction)
		{
			mCurrentJob->mExitFunction(mCurrentJob->WORD_0x4);
		}
	}
	
	void* TaskThread::run()
	{
		OSInitFastCast();
		
		for (;;)
		{
			TJob * pJob = (TJob *)waitMessageBlock();
			mCurrentJob = pJob;
			
			if (pJob->mFunction)
			{
				pJob->mFunction(pJob->WORD_0x4);
				
				if (MSG_QUEUE_0x50) OSSendMessage(MSG_QUEUE_0x50, pJob->MSG_0x8, 0);
			}
			
			pJob->mFunction = NULL;
			
			if (mCurrentJob && mCurrentJob->TFUNCTION_0x14)
			{
				mCurrentJob->TFUNCTION_0x14(mCurrentJob->WORD_0x4);
			}
			
			mCurrentJob = NULL;
			
			pJob->clearFunctions();
		}
	}
	
	TaskThread::TJob * TaskThread::findBlank()
	{
		for (int i = 0; i < mJobCount; i++)
		{
			if (!mJobs[i].mFunction)
			{
				mJobs[i].clearFunctions();
				
				return mJobs + i;
			}
		}
		
		return NULL;
	}
	
	OSMessage TaskThread::waitQueueMessage(OSMessageQueue * pQueue, BOOL * pSuccess)
	{
		OSMessage message = NULL;
		
		BOOL success = FALSE;
		
		if (pQueue) success = OSReceiveMessage(pQueue, &message, 0);
		
		if (pSuccess) *pSuccess = success;
		
		return message;
	}
	
	OSMessage * TaskThread::sEndMesgBuffer;
	int TaskThread::sEndMesgBufSize;
	
	OSMessageQueue TaskThread::sEndMesgQueue;
}