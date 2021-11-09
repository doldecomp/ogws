#ifndef NW4R_UT_LINK_LIST
#define NW4R_UT_LINK_LIST
#include "types_nw4r.h"
#include "ut_NonCopyable.h"

namespace nw4r
{
    namespace ut
    {
        struct LinkListNode : public NonCopyable
        {            
            LinkListNode() : mNext(NULL), mPrev(NULL) {}

            LinkListNode *mNext; // at 0x0
            LinkListNode *mPrev; // at 0x4
        };
        
        namespace detail
        {
            class LinkListImpl : public NonCopyable
            {
            public:            
                struct Iterator
                {
                    Iterator(LinkListNode *node) : mPointer(node) {}
                    
                    Iterator& operator++()
                    {
                        mPointer = mPointer->mNext;
                        return *this;
                    }

                    Iterator& operator--()
                    {
                        mPointer = mPointer->mPrev;
                        return *this;
                    }
                    
                    LinkListNode * operator->() const
                    {
                        return mPointer;
                    }

                    LinkListNode *mPointer; // at 0x0
                };
                                
                LinkListImpl()
                {
                    Initialize_();
                }

                ~LinkListImpl();

                void Initialize_()
                {
                    mSize = 0;

                    LinkListNode *end = &mNode;
                    mNode.mNext = end;
                    mNode.mPrev = end;
                }

                int GetSize() const { return mSize; }
                bool IsEmpty() const { return (mSize == 0); }

                Iterator GetEndIter()
                {
                    return Iterator(&mNode);
                }
                
                Iterator GetBeginIter()
                {
                    return Iterator(mNode.mNext);
                }

                LinkListNode * Erase(Iterator);
                LinkListNode * Erase(LinkListNode *);
                LinkListNode * Erase(Iterator, Iterator);

                LinkListNode * Insert(Iterator, LinkListNode *);
                
                void Clear();

            private:
                int mSize; // at 0x0
                LinkListNode mNode; // at 0x4
            };
            
            inline bool operator ==(LinkListImpl::Iterator iter1, LinkListImpl::Iterator iter2)
            {
                return iter1.mPointer == iter2.mPointer;
            }
        }
        
        template <typename T, int I>
        class LinkList : public detail::LinkListImpl
        {
        public:            
            struct Iterator
            {
                Iterator(LinkListImpl::Iterator iter) : mIterator(iter) {}
                
                bool operator==(Iterator other)
                {
                    return (mIterator == other.mIterator);
                }
                
                bool operator!=(Iterator other)
                {
                    return !(*this == other);
                }
                
                Iterator& operator++()
                {
                    mIterator.operator++();
                    return *this;
                }
                
                Iterator& operator--()
                {
                    mIterator.operator--;
                    return *this;
                }
                
                Iterator operator++(int)
                {
                    Iterator ret = *this;
                    ++*this;
                    return ret;
                }
                
                T * operator->() const
                {
                    return GetPointerFromNode(mIterator.mPointer);
                }
                
                T& operator*() const
                {
                    return *GetPointerFromNode(mIterator.mPointer);
                }

                LinkListImpl::Iterator mIterator; // at 0x0
            };
            
            LinkList() {}
            ~LinkList() {}

            Iterator GetEndIter()
            {
                return Iterator(LinkListImpl::GetEndIter());
            }
            
            Iterator GetBeginIter()
            {
                return Iterator(LinkListImpl::GetBeginIter());
            }
            
            Iterator Insert(Iterator iter, T *p)
            {
                return Iterator(LinkListImpl::Insert(iter.mIterator, GetNodeFromPointer(p)));
            }
            
            UNKTYPE PushBack(T *p)
            {
                Insert(GetEndIter(), p);
            }
            
            Iterator Erase(T *p)
            {
                return Iterator(LinkListImpl::Erase(GetNodeFromPointer(p)));
            }

            Iterator Erase(Iterator iter)
            {
                return Iterator(LinkListImpl::Erase(iter.mIterator));
            }
            
            T * GetBack()
            {
                return &*--GetEndIter();
            }

            static inline LinkListNode * GetNodeFromPointer(T *p)
            {
                return (LinkListNode *)((char *)p + I);
            }
            
            static inline T * GetPointerFromNode(LinkListNode *node)
            {
                return (T *)((char *)node - I);
            }
        };
    }
}

#endif