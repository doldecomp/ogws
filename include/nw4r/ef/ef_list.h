#ifndef NW4R_EF_LIST
#define NW4R_EF_LIST
#include "types_nw4r.h"
#include "ut_list.h"

namespace nw4r
{
	namespace ef
	{
		//sizeof(ActivityList) = 0x1C
		struct ActivityList
		{
			ut::List mActive;
			ut::List mClosing;
			u16 mNumActive;
			
			inline void SetOffset(u16 offset)
			{
				ut::List_Init(&mActive, offset);
				ut::List_Init(&mClosing, offset);
				mNumActive = 0;
			}
			
			inline ActivityList(u16 offset)
			{
				SetOffset(offset);
			}
			
			inline ActivityList()
			{
				SetOffset(0);
			}
			
			inline void Initialize()
			{
				mActive.headObject = NULL;
				mActive.numObjects = 0;
				mActive.tailObject = NULL;
				
				mClosing.headObject = NULL;
				mClosing.numObjects = 0;
				mClosing.tailObject = NULL;
				
				mNumActive = 0;
			}
			
			inline void ToActive(void * pNode)
			{
				ut::List_Append(&mActive, pNode);
				mNumActive++;
			}
			
			inline void ToClosing(void * pNode)
			{
				ut::List_Remove(&mActive, pNode);
				ut::List_Append(&mClosing, pNode);
			}
			
			inline void ToWait(void * /* pNode */)
			{
				mNumActive--;
			}
		};
	}
}

#endif
