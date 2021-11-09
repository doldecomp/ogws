#pragma ipa file
#include "ut_LinkList.h"

namespace nw4r
{
    namespace ut
    {
        namespace detail
        {
            LinkListImpl::~LinkListImpl()
            {
                Erase(GetBeginIter(), GetEndIter());
            }
            
            LinkListNode * LinkListImpl::Erase(LinkListImpl::Iterator it)
            {
                Iterator begin(it.mPointer);
                return Erase(begin, begin->mNext);
            }
            
            void LinkListImpl::Clear()
            {
                Erase(GetBeginIter(), GetEndIter());
            }
            
            LinkListNode * LinkListImpl::Insert(Iterator it, LinkListNode *p)
            {
                LinkListNode *pIt = it.mPointer;
                LinkListNode *pItPrev = pIt->mPrev;

                p->mNext = pIt;
                p->mPrev = pItPrev;
                pIt->mPrev = p;
                pItPrev->mNext = p;
                mSize++;

                return p;
            }
            
            LinkListNode * LinkListImpl::Erase(LinkListNode *p)
            {
                LinkListNode *pPrev;
                LinkListNode *pNext;

                pNext = p->mNext;
                pPrev = p->mPrev;
                pNext->mPrev = pPrev;
                pPrev->mNext = pNext;
                mSize--;

                p->mNext = NULL;
                p->mPrev = NULL;

                return pNext;
            }

            LinkListNode * LinkListImpl::Erase(Iterator begin, Iterator end)
            {
                LinkListNode *pCur = begin.mPointer;
                LinkListNode *pEnd = end.mPointer;

                LinkListNode *pNext;
                while (pCur != pEnd)
                {
                    pNext = pCur->mNext;
                    Erase(pCur);

                    pCur = pNext;
                }

                return pEnd;
            }
        }
    }
}