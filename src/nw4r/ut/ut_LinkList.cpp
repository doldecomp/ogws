#include "ut_LinkList.h"

namespace nw4r
{
	namespace ut
	{
		namespace detail
		{
			LinkListImpl::~LinkListImpl()
			{
				Iterator iBegin = this->GetBeginIter();
				Iterator iEnd = this->GetEndIter();
				Erase(iBegin, iEnd);
			}
			
			LinkListNode * LinkListImpl::Erase(LinkListImpl::Iterator iNode)
			{
				Iterator iBegin(iNode.mNode);
				
				return Erase(iBegin, iBegin->mNext);
			}
			
			void LinkListImpl::Clear()
			{
				Iterator iBegin = this->GetBeginIter();
				Iterator iEnd = this->GetEndIter();
				Erase(iBegin, iEnd);
			}
			
			LinkListNode * LinkListImpl::Insert(Iterator i, LinkListNode * pNode)
			{
				LinkListNode * r4 = i.mNode;
				LinkListNode * r6;
				
				r6 = r4->mPrev;
				pNode->mNext = r4;
				pNode->mPrev = r6;
				r4->mPrev = pNode;
				r6->mNext = pNode;
				this->mCount++;
				
				return pNode;
			}
			
			LinkListNode * LinkListImpl::Erase(LinkListNode * pNode)
			{
				LinkListNode * pPrev;
				LinkListNode * pNext;
				
				pNext = pNode->mNext;
				pPrev = pNode->mPrev;
				
				pNext->mPrev = pPrev;
				pPrev->mNext = pNext;
				
				this->mCount--;
				
				pNode->mNext = NULL;
				pNode->mPrev = NULL;
				
				return pNext;
			}
		}
	}
}
