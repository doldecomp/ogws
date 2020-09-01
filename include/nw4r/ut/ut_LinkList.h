#ifndef NW4R_UT_LINK_LIST
#define NW4R_UT_LINK_LIST
#include "types_nw4r.h"

namespace nw4r
{
	namespace ut
	{
		struct LinkListNode
		{
			LinkListNode * mNext;
			LinkListNode * mPrev;
		};
		
		namespace detail
		{
			struct LinkListImpl
			{
				u32 mCount;
				
				LinkListNode mNode;
				
				struct Iterator
				{
					LinkListNode * mNode;
					inline Iterator(const Iterator & other) : mNode(other.mNode) {}
					inline Iterator(LinkListNode * pNode) : mNode(pNode) {}
					
					inline Iterator & operator++()
					{
						mNode = mNode->mNext;
						return *this;
					}
					
					inline LinkListNode * operator->() const
					{
						return mNode;
					}
				};
				
				inline Iterator GetEndIter()
				{
					return Iterator(&mNode);
				}
				
				inline Iterator GetBeginIter()
				{
					return Iterator(mNode.mNext);
				}
				
				~LinkListImpl();
				
				LinkListNode * Erase(Iterator);
				LinkListNode * Erase(LinkListNode *);
				inline LinkListNode * Erase(Iterator iBegin, Iterator iEnd)
				{
					LinkListNode * pPrev;
					LinkListNode * pNext;
					
					LinkListNode * pCurNode;
					
					LinkListNode * pEndNode;
					LinkListNode * pBeginNode;
					
					pBeginNode = iBegin.mNode;
					pEndNode = iEnd.mNode;
					
					pCurNode = pBeginNode;
					
					while (pCurNode != pEndNode)
					{
						pNext = pCurNode->mNext;
						pPrev = pCurNode->mPrev;
						
						pNext->mPrev = pPrev;
						pPrev->mNext = pNext;
						
						this->mCount--;
						
						pCurNode->mNext = NULL;
						pCurNode->mPrev = NULL;
						
						pCurNode = pNext;
					}
					
					return pEndNode;
				}
				
				void Clear();
				
				LinkListNode * Insert(Iterator, LinkListNode *);
			};
			
			inline bool operator ==(LinkListImpl::Iterator iter1, LinkListImpl::Iterator iter2)
			{
				return iter1.mNode == iter1.mNode;
			}
		}
	}
}

#endif