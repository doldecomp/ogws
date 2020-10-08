#ifndef NW4R_EF_LIST
#define NW4R_EF_LIST
#include "types_nw4r.h"
#include "ut_list.h"

namespace nw4r
{
	namespace ef
	{
		struct ActivityList
		{
			ut::List mActive;
			ut::List mClosing;
			u16 SHORT_0x18;
			
			inline ActivityList(u16 offset)
			{
				ut::List_Init(&mActive, offset);
				ut::List_Init(&mClosing, offset);
				SHORT_0x18 = 0;
			}
			
			inline void Initialize()
			{
				mActive.first = NULL;
				mActive.size = 0;
				mActive.last = NULL;
				
				mClosing.first = NULL;
				mClosing.size = 0;
				mClosing.last = NULL;
				
				SHORT_0x18 = 0;
			}
			
			inline void ToActive(void * pNode)
			{
				ut::List_Append(&mActive, pNode);
				SHORT_0x18++;
				//static_cast<ReferencedObject *>(pNode)->WORD_0xC = 1;
			}
			
			inline void ToClosing(void * pNode)
			{
				ut::List_Remove(&mActive, pNode);
				ut::List_Append(&mClosing, pNode);
				//static_cast<ReferencedObject *>(pNode)->WORD_0xC = 3;
			}
			
			inline void ToWait(void * pNode)
			{
				SHORT_0x18--;
				/*
				ReferencedObject * pRef = static_cast<ReferencedObject *>(pNode);
				
				pRef->DestroyFunc();
				pRef->WORD_0xC = 2;
				if (pRef->mRefCount == 0) pRef->SendClosing();
				*/
			}
		};
	}
}

#endif
