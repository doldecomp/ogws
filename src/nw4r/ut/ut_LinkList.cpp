#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

namespace nw4r {
namespace ut {
namespace detail {

LinkListImpl::~LinkListImpl() {
    Clear();
}

LinkListImpl::Iterator LinkListImpl::Erase(LinkListImpl::Iterator it) {
    Iterator copy(it);
    return Erase(it, ++copy);
}

void LinkListImpl::Clear() {
    Erase(GetBeginIter(), GetEndIter());
}

LinkListImpl::Iterator LinkListImpl::Insert(Iterator it, LinkListNode* pNode) {
    LinkListNode* next = it.mNode;
    LinkListNode* prev = next->mPrev;

    // prev <- pNode -> next
    pNode->mNext = next;
    pNode->mPrev = prev;
    // prev <-> pNode <-> next
    next->mPrev = pNode;
    prev->mNext = pNode;

    mSize++;

    return Iterator(pNode);
}

LinkListImpl::Iterator LinkListImpl::Erase(LinkListNode* pNode) {
    LinkListNode* next = pNode->mNext;
    LinkListNode* prev = pNode->mPrev;

    // Remove connections to node
    next->mPrev = prev;
    prev->mNext = next;

    mSize--;

    // Isolate node
    pNode->mNext = NULL;
    pNode->mPrev = NULL;

    return Iterator(next);
}

LinkListImpl::Iterator LinkListImpl::Erase(Iterator begin, Iterator end) {
    LinkListNode* pIt = begin.mNode;
    LinkListNode* pEnd = end.mNode;

    while (pIt != pEnd) {
        // Preserve next node before erasing pointers
        LinkListNode* pNext = pIt->mNext;
        // Erase current node
        Erase(pIt);
        pIt = pNext;
    }

    return Iterator(pEnd);
}

} // namespace detail
} // namespace ut
} // namespace nw4r