#ifndef NW4R_SND_TASK_MANAGER_H
#define NW4R_SND_TASK_MANAGER_H
#include "types_nw4r.h"
#include "snd_Task.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct TaskManager
			{
				enum TaskPriority
				{
					PRIORITY_1 = 1
				};
				
				static TaskManager * GetInstance();
				
				UNKTYPE AppendTask(Task *, TaskPriority);
				UNKTYPE CancelTask(Task *);
			};
		}
	}
}

#endif