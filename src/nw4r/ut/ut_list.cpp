#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

void List_Init(List* pList, u16 offset) {
    pList->headObject = NULL;
    pList->tailObject = NULL;
    pList->numObjects = 0;
    pList->offset = offset;
}

static void SetFirstObject(List* pList, void* pObject) {
    Link* pLink = NW4R_UT_LIST_GET_LINK(*pList, pObject);
    pLink->nextObject = NULL;
    pLink->prevObject = NULL;

    pList->headObject = pObject;
    pList->tailObject = pObject;
    pList->numObjects++;
}

void List_Append(List* pList, void* pObject) {
    if (pList->headObject == NULL) {
        SetFirstObject(pList, pObject);
        return;
    }

    // Old tail <- New tail relationship
    Link* pLink = NW4R_UT_LIST_GET_LINK(*pList, pObject);
    pLink->prevObject = pList->tailObject;
    pLink->nextObject = NULL;

    // Old tail -> New tail relationship
    NW4R_UT_LIST_GET_LINK(*pList, pList->tailObject)->nextObject = pObject;
    pList->tailObject = pObject;

    pList->numObjects++;
}

void List_Prepend(List* pList, void* pObject) {
    if (pList->headObject == NULL) {
        SetFirstObject(pList, pObject);
        return;
    }

    // New head -> Old head relationship
    Link* pLink = NW4R_UT_LIST_GET_LINK(*pList, pObject);
    pLink->prevObject = NULL;
    pLink->nextObject = pList->headObject;

    // New head <- Old head relationship
    NW4R_UT_LIST_GET_LINK(*pList, pList->headObject)->prevObject = pObject;
    pList->headObject = pObject;

    pList->numObjects++;
}

void List_Insert(List* pList, void* pTarget, void* pObject) {
    if (pTarget == NULL) {
        List_Append(pList, pObject);
        return;
    }

    if (pTarget == pList->headObject) {
        List_Prepend(pList, pObject);
        return;
    }

    Link* pLink = NW4R_UT_LIST_GET_LINK(*pList, pObject);
    void* pPrev = NW4R_UT_LIST_GET_LINK(*pList, pTarget)->prevObject;
    Link* pPrevLink = NW4R_UT_LIST_GET_LINK(*pList, pPrev);

    // pPrev <- pObject
    pLink->prevObject = pPrev;
    // pPrev <- pObject -> pTarget
    pLink->nextObject = pTarget;
    // pPrev <-> pObject -> pTarget
    pPrevLink->nextObject = pObject;
    // pPrev <-> pObject <-> pTarget
    NW4R_UT_LIST_GET_LINK(*pList, pTarget)->prevObject = pObject;

    pList->numObjects++;
}

void List_Remove(List* pList, void* pObject) {
    Link* pLink = NW4R_UT_LIST_GET_LINK(*pList, pObject);

    // Fix previous node relationship
    if (pLink->prevObject == NULL) {
        pList->headObject = NW4R_UT_LIST_GET_LINK(*pList, pObject)->nextObject;
    } else {
        NW4R_UT_LIST_GET_LINK(*pList, pLink->prevObject)->nextObject =
            pLink->nextObject;
    }

    // Fix next node relationship
    if (pLink->nextObject == NULL) {
        pList->tailObject = pLink->prevObject;
    } else {
        NW4R_UT_LIST_GET_LINK(*pList, pLink->nextObject)->prevObject =
            pLink->prevObject;
    }

    pLink->prevObject = NULL;
    pLink->nextObject = NULL;

    pList->numObjects--;
}

void* List_GetNext(const List* pList, const void* pObject) {
    if (pObject == NULL) {
        return pList->headObject;
    }

    return NW4R_UT_LIST_GET_LINK(*pList, pObject)->nextObject;
}

void* List_GetPrev(const List* pList, const void* pObject) {
    if (pObject == NULL) {
        return pList->tailObject;
    }

    return NW4R_UT_LIST_GET_LINK(*pList, pObject)->prevObject;
}

void* List_GetNth(const List* pList, u16 n) {
    int i;
    void* pIt = NULL;

    for (i = 0, pIt = NULL; (pIt = List_GetNext(pList, pIt)) != NULL; i++) {
        if (n == i) {
            return pIt;
        }
    }

    return NULL;
}

} // namespace ut
} // namespace nw4r
