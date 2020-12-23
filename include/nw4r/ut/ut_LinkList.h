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
			
			inline LinkListNode() : mNext(NULL), mPrev(NULL) {}
		};
		
		namespace detail
		{
			struct LinkListImpl
			{
				u32 mCount;
				
				LinkListNode mEndNode;
				
				struct Iterator
				{
					LinkListNode * mNode;
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
					return Iterator(&mEndNode);
				}
				
				inline Iterator GetBeginIter()
				{
					return Iterator(mEndNode.mNext);
				}
				
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
				
				inline void Initialize_() volatile
				{
					mEndNode.mNext = NULL;
					mEndNode.mPrev = NULL;
					mCount = 0;
				}
				
				LinkListImpl() : mCount(0), mEndNode()
				{
					LinkListNode *lp = &mEndNode;
					Initialize_();
					mEndNode.mNext = lp;
					mEndNode.mPrev = lp;
				}
				
				~LinkListImpl();
			};
			
			inline bool operator ==(LinkListImpl::Iterator iter1, LinkListImpl::Iterator iter2)
			{
				return iter1.mNode == iter2.mNode;
			}
		}
		
		template <typename T, int I>
		struct LinkList : detail::LinkListImpl
		{
			static inline LinkListNode * GetNodeFromPointer(T * ptr)
			{
				return (LinkListNode *)((char *)ptr + I);
			}
			
			static inline T * GetPointerFromNode(LinkListNode * node)
			{
				return (T *)((char *)node - I);
			}
			
			struct Iterator
			{
				detail::LinkListImpl::Iterator mIterator; // at 0x0
				
				inline Iterator(detail::LinkListImpl::Iterator iter) : mIterator(iter) {}
				
				inline bool operator ==(Iterator other)
				{
					return detail::operator==(mIterator, other.mIterator);
				}
				
				inline bool operator !=(Iterator other)
				{
					return !(*this == other);
				}
				
				inline Iterator & operator ++()
				{
					mIterator.operator++();
					return *this;
				}
				
				inline Iterator & operator --()
				{
					mIterator.mNode = mIterator.mNode->mPrev;
					return *this;
				}
				
				inline Iterator operator ++(int)
				{
					Iterator ret = *this;
					++*this;
					return ret;
				}
				
				inline T * operator->() const
				{
					return GetPointerFromNode(mIterator.mNode);
				}
				
				inline T & operator*() const
				{
					return *GetPointerFromNode(mIterator.mNode);
				}
			};
			
			inline Iterator GetEndIter()
			{
				return Iterator(detail::LinkListImpl::GetEndIter());
			}
			
			inline Iterator GetBeginIter()
			{
				return Iterator(detail::LinkListImpl::GetBeginIter());
			}
			
			inline UNKTYPE Insert(Iterator iter, T * ptr)
			{
				detail::LinkListImpl::Insert(iter.mIterator, GetNodeFromPointer(ptr));
			}
			
			inline UNKTYPE PushBack(T * ptr)
			{
				Insert(GetEndIter(), ptr);
			}
			
			inline UNKTYPE Erase(T * ptr)
			{
				detail::LinkListImpl::Erase(GetNodeFromPointer(ptr));
			}
			
			inline T * GetBack()
			{
				return &*--GetEndIter();
			}
			
			~LinkList();
			inline LinkList() {}
		};
		
		template <typename T, int I> LinkList<T,I>::~LinkList() {}
		//template <typename T, int I> inline LinkList<T,I>::LinkList() {}
	}
}

#endif