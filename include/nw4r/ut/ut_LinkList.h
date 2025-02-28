#ifndef NW4R_UT_LINK_LIST_H
#define NW4R_UT_LINK_LIST_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ut/ut_NonCopyable.h>

namespace nw4r {
namespace ut {

// Forward declarations
namespace detail {
class LinkListImpl;
} // namespace detail

/******************************************************************************
 *
 * Linked list node
 *
 ******************************************************************************/
class LinkListNode : private NonCopyable {
    friend class detail::LinkListImpl;

public:
    LinkListNode() : mNext(NULL), mPrev(NULL) {}

    LinkListNode* GetNext() const {
        return mNext;
    }
    LinkListNode* GetPrev() const {
        return mPrev;
    }

private:
    LinkListNode* mNext; // at 0x0
    LinkListNode* mPrev; // at 0x4
};

namespace detail {

/******************************************************************************
 *
 * Linked list implementation
 *
 ******************************************************************************/
class LinkListImpl : private NonCopyable {
public:
    // Forward declarations
    class ConstIterator;

    /******************************************************************************
     * Iterator implementation
     ******************************************************************************/
    class Iterator {
        friend class LinkListImpl;
        friend class ConstIterator;

    public:
        Iterator() : mNode(NULL) {}
        explicit Iterator(LinkListNode* pNode) : mNode(pNode) {}

        Iterator& operator++() {
            mNode = mNode->GetNext();
            return *this;
        }

        Iterator& operator--() {
            mNode = mNode->GetPrev();
            return *this;
        }

        LinkListNode* operator->() const {
            return mNode;
        }

        friend bool operator==(LinkListImpl::Iterator lhs,
                               LinkListImpl::Iterator rhs) {
            return lhs.mNode == rhs.mNode;
        }

    private:
        LinkListNode* mNode; // at 0x0
    };

    /******************************************************************************
     * Iterator implementation (const-view)
     ******************************************************************************/
    class ConstIterator {
        friend class LinkListImpl;

    public:
        explicit ConstIterator(Iterator it) : mNode(it.mNode) {}

        ConstIterator& operator++() {
            mNode = mNode->GetNext();
            return *this;
        }

        ConstIterator& operator--() {
            mNode = mNode->GetPrev();
            return *this;
        }

        const LinkListNode* operator->() const {
            return mNode;
        }

        friend bool operator==(LinkListImpl::ConstIterator lhs,
                               LinkListImpl::ConstIterator rhs) {
            return lhs.mNode == rhs.mNode;
        }

    private:
        LinkListNode* mNode; // at 0x0
    };

protected:
    static Iterator GetIteratorFromPointer(LinkListNode* pNode) {
        return Iterator(pNode);
    }

    LinkListImpl() {
        Initialize_();
    }
    ~LinkListImpl();

    Iterator GetBeginIter() {
        return Iterator(mNode.GetNext());
    }
    Iterator GetEndIter() {
        return Iterator(&mNode);
    }

    Iterator Insert(Iterator it, LinkListNode* pNode);

    Iterator Erase(Iterator it);
    Iterator Erase(LinkListNode* pNode);
    Iterator Erase(Iterator begin, Iterator end);

public:
    u32 GetSize() const {
        return mSize;
    }
    bool IsEmpty() const {
        return mSize == 0;
    }

    void PopFront() {
        Erase(GetBeginIter());
    }
    void PopBack() {
        Erase(--GetEndIter());
    }

    void Clear();

private:
    void Initialize_() {
        mSize = 0;
        mNode.mNext = &mNode;
        mNode.mPrev = &mNode;
    }

private:
    u32 mSize;          // at 0x0
    LinkListNode mNode; // at 0x4
};

/******************************************************************************
 *
 * Reverse iterator
 *
 ******************************************************************************/
template <typename TIter> class ReverseIterator {
public:
    explicit ReverseIterator(TIter it) : mCurrent(it) {}

    TIter GetBase() const {
        return mCurrent;
    }

    ReverseIterator& operator++() {
        --mCurrent;
        return *this;
    }

    const typename TIter::TElem* operator->() const {
        return &this->operator*();
    }

    typename TIter::TElem& operator*() const {
        TIter it = mCurrent;
        return *--it;
    }

    friend bool operator==(const ReverseIterator& rLhs,
                           const ReverseIterator& rRhs) {
        return rLhs.mCurrent == rRhs.mCurrent;
    }

    friend bool operator!=(const ReverseIterator& rLhs,
                           const ReverseIterator& rRhs) {
        return !(rLhs.mCurrent == rRhs.mCurrent);
    }

private:
    TIter mCurrent; // at 0x0
};

} // namespace detail

/******************************************************************************
 *
 * Templated linked list
 *
 ******************************************************************************/
template <typename T, int Ofs> class LinkList : public detail::LinkListImpl {
public:
    // Forward declarations
    class ConstIterator;

    /******************************************************************************
     * Templated iterator
     ******************************************************************************/
    class Iterator {
        friend class LinkList;
        friend class ConstIterator;

    public:
        // Element type must be visible to ReverseIterator
        typedef T TElem;

    public:
        Iterator() : mIterator(NULL) {}
        explicit Iterator(LinkListImpl::Iterator it) : mIterator(it) {}

        Iterator& operator++() {
            ++mIterator;
            return *this;
        }

        Iterator& operator--() {
            --mIterator;
            return *this;
        }

        Iterator operator++(int) {
            Iterator ret = *this;
            ++*this;
            return ret;
        }

        T* operator->() const {
            return GetPointerFromNode(mIterator.operator->());
        }

        T& operator*() const {
            return *this->operator->();
        }

        friend bool operator==(Iterator lhs, Iterator rhs) {
            return lhs.mIterator == rhs.mIterator;
        }

        friend bool operator!=(Iterator lhs, Iterator rhs) {
            return !(lhs == rhs);
        }

    private:
        LinkListImpl::Iterator mIterator; // at 0x0
    };

    /******************************************************************************
     * Templated iterator (const-view)
     ******************************************************************************/
    class ConstIterator {
        friend class LinkList;

    public:
        // Element type must be visible to ReverseIterator
        typedef T TElem;

    public:
        explicit ConstIterator(LinkListImpl::Iterator it) : mIterator(it) {}
        explicit ConstIterator(Iterator it) : mIterator(it.mIterator) {}

        ConstIterator& operator++() {
            ++mIterator;
            return *this;
        }

        ConstIterator& operator--() {
            --mIterator;
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator ret = *this;
            ++*this;
            return ret;
        }

        const T* operator->() const {
            return GetPointerFromNode(mIterator.operator->());
        }

        const T& operator*() const {
            return *this->operator->();
        }

        friend bool operator==(ConstIterator lhs, ConstIterator rhs) {
            return lhs.mIterator == rhs.mIterator;
        }

        friend bool operator!=(ConstIterator lhs, ConstIterator rhs) {
            return !(lhs == rhs);
        }

    private:
        LinkListImpl::ConstIterator mIterator; // at 0x0
    };

public:
    // Shorthand names for reverse iterator types
    typedef detail::ReverseIterator<Iterator> RevIterator;
    typedef detail::ReverseIterator<ConstIterator> ConstRevIterator;

public:
    LinkList() {}

    Iterator GetBeginIter() {
        return Iterator(LinkListImpl::GetBeginIter());
    }
    ConstIterator GetBeginIter() const {
        return ConstIterator(const_cast<LinkList*>(this)->GetBeginIter());
    }
    RevIterator GetBeginReverseIter() {
        return RevIterator(GetBeginIter());
    }
    ConstRevIterator GetBeginReverseIter() const {
        return ConstRevIterator(GetBeginIter());
    }

    Iterator GetEndIter() {
        return Iterator(LinkListImpl::GetEndIter());
    }
    ConstIterator GetEndIter() const {
        return ConstIterator(const_cast<LinkList*>(this)->GetEndIter());
    }
    RevIterator GetEndReverseIter() {
        return RevIterator(GetEndIter());
    }
    ConstRevIterator GetEndReverseIter() const {
        return ConstRevIterator(GetEndIter());
    }

    Iterator Insert(Iterator it, T* pElem) {
        return Iterator(
            LinkListImpl::Insert(it.mIterator, GetNodeFromPointer(pElem)));
    }

    Iterator Erase(T* pElem) {
        return Iterator(LinkListImpl::Erase(GetNodeFromPointer(pElem)));
    }
    Iterator Erase(Iterator it) {
        return Iterator(LinkListImpl::Erase(it.mIterator));
    }

    void PushBack(T* pElem) {
        Insert(GetEndIter(), pElem);
    }

    T& GetFront() {
        return *GetBeginIter();
    }
    const T& GetFront() const {
        return *GetBeginIter();
    }

    T& GetBack() {
        return *--GetEndIter();
    }
    const T& GetBack() const {
        return *--GetEndIter();
    }

    static Iterator GetIteratorFromPointer(T* pElem) {
        return GetIteratorFromPointer(GetNodeFromPointer(pElem));
    }

    static Iterator GetIteratorFromPointer(LinkListNode* pNode) {
        return Iterator(LinkListImpl::GetIteratorFromPointer(pNode));
    }

    static LinkListNode* GetNodeFromPointer(T* pElem) {
        return reinterpret_cast<LinkListNode*>(reinterpret_cast<char*>(pElem) +
                                               Ofs);
    }

    static T* GetPointerFromNode(LinkListNode* pNode) {
        return reinterpret_cast<T*>(reinterpret_cast<char*>(pNode) - Ofs);
    }

    static const T* GetPointerFromNode(const LinkListNode* pNode) {
        return reinterpret_cast<const T*>(reinterpret_cast<const char*>(pNode) -
                                          Ofs);
    }
};

} // namespace ut
} // namespace nw4r

/******************************************************************************
 *
 * Macros
 *
 ******************************************************************************/
/**
 * Declare typedef for linked-list specialization.
 */
#define NW4R_UT_LINKLIST_TYPEDEF_DECL(T)                                       \
    typedef nw4r::ut::LinkList<T, offsetof(T, node)> T##List;

/**
 * Declare typedef for linked-list specialization.
 *
 * Use the specified link node (name suffix) for classes with multiple nodes.
 */
#define NW4R_UT_LINKLIST_TYPEDEF_DECL_EX(T, SUFFIX)                            \
    typedef nw4r::ut::LinkList<T, offsetof(T, node##SUFFIX)> T##SUFFIX##List;

/**
 * Declare a member LinkListNode for use with the typedef.
 */
#define NW4R_UT_LINKLIST_NODE_DECL() nw4r::ut::LinkListNode node

/**
 * Declare a member LinkListNode for use with the typedef.
 *
 * Use the specified link node (name suffix) for classes with multiple nodes.
 */
#define NW4R_UT_LINKLIST_NODE_DECL_EX(SUFFIX)                                  \
    nw4r::ut::LinkListNode node##SUFFIX

/**
 * Explicitly instantiate a linked list specialization.
 * (RESERVED FOR MATCHING DECOMP HACKS)
 */
#ifndef __DECOMP_NON_MATCHING
#define NW4R_UT_LINKLIST_TYPEDEF_FORCE(T)                                      \
    template struct nw4r::ut::LinkList<T, offsetof(T, node)>
#else
#define NW4R_UT_LINKLIST_TYPEDEF_FORCE(T)
#endif

/**
 * Linked-list for-each macro.
 *
 * @param NAME Element name
 * @param LIST Reference to list
 * @param ... Statement(s) to execute
 */
#define NW4R_UT_LINKLIST_FOREACH(NAME, LIST, ...)                              \
    {                                                                          \
        typedef DECLTYPE((LIST).GetBeginIter()) IterType;                      \
                                                                               \
        for (IterType NAME = (LIST).GetBeginIter();                            \
             NAME != (LIST).GetEndIter(); ++NAME) {                            \
                                                                               \
            __VA_ARGS__;                                                       \
        }                                                                      \
    }

/**
 * List for-each macro, with robust iteration.
 *
 * @param NAME Element name
 * @param LIST Reference to list
 * @param ... Statement(s) to execute
 */
#define NW4R_UT_LINKLIST_FOREACH_SAFE(NAME, LIST, ...)                         \
    {                                                                          \
        typedef DECLTYPE((LIST).GetBeginIter()) IterType;                      \
                                                                               \
        for (IterType __impl__ = (LIST).GetBeginIter();                        \
             __impl__ != (LIST).GetEndIter();) {                               \
                                                                               \
            IterType NAME = __impl__++;                                        \
            __VA_ARGS__;                                                       \
        }                                                                      \
    }

#endif
