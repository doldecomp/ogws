#ifndef EGG_CORE_TASK_THREAD_H
#define EGG_CORE_TASK_THREAD_H
#include "eggThread.h"
#include "eggHeap.h"

namespace EGG
{
	class TaskThread : public Thread
	{
	public:
		typedef void (*TFunction)(void *);
		
		struct TJob
		{
			TFunction mFunction; // at 0x0
			void * WORD_0x4;
			OSMessage MSG_0x8;
			TFunction mEnterFunction; // at 0xc
			TFunction mExitFunction; // at 0x10
			TFunction TFUNCTION_0x14;
			
			inline TJob() : mEnterFunction(NULL), mExitFunction(NULL), TFUNCTION_0x14(NULL) {}
			
			inline void clearFunctions()
			{
				mFunction = NULL;
				mEnterFunction = NULL;
				mExitFunction = NULL;
				TFUNCTION_0x14 = NULL;
			}
		};
		
		TaskThread(int, int, u32);
		
		static TaskThread * create(int, int, u32, Heap *);
		
		bool request(TFunction, void *, OSMessage);
		
		static OSMessageQueue * createTaskEndMessageQueue(int, Heap *);
		
		bool isTaskExist() const;
		
		~TaskThread();
		
		void onEnter();
		void onExit();
		
		void* run();
		
		TJob * findBlank();
		
		static OSMessage waitQueueMessage(OSMessageQueue *, BOOL *);
	private:
		TJob * mCurrentJob; // at 0x44
		TJob * mJobs; // at 0x48
		int mJobCount; // at 0x4c
		OSMessageQueue * MSG_QUEUE_0x50;
		
		static OSMessage * sEndMesgBuffer;
		static int sEndMesgBufSize;
		
		static OSMessageQueue sEndMesgQueue;
	};
}

#endif