#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

#define OBJ_TO_NODE(LIST, OBJECT)                                              \
    reinterpret_cast<Node*>((char*)OBJECT + LIST->offset)

void List_Init(List* pList, u16 offset) {
    pList->first = NULL;
    pList->last = NULL;
    pList->size = NULL;
    pList->offset = offset;
}

static void SetFirstObject(List* pList, void* pObject) {
    Node* node = OBJ_TO_NODE(pList, pObject);
    node->next = NULL;
    node->prev = NULL;

    pList->first = pObject;
    pList->last = pObject;

    pList->size++;
}

void List_Append(List* pList, void* pObject) {
    if (pList->first == NULL) {
        SetFirstObject(pList, pObject);
    } else {
        // Old tail <- New tail relationship
        Node* node = OBJ_TO_NODE(pList, pObject);
        node->prev = pList->last;
        node->next = NULL;

        // Old tail -> New tail relationship
        OBJ_TO_NODE(pList, pList->last)->next = pObject;
        pList->last = pObject;

        pList->size++;
    }
}

void List_Prepend(List* pList, void* pObject) {
    if (pList->first == NULL) {
        SetFirstObject(pList, pObject);
    } else {
        // New head -> Old head relationship
        Node* node = OBJ_TO_NODE(pList, pObject);
        node->prev = NULL;
        node->next = pList->first;

        // New head <- Old head relationship
        OBJ_TO_NODE(pList, pList->first)->prev = pObject;
        pList->first = pObject;

        pList->size++;
    }
}

void List_Insert(List* pList, void* pNext, void* pObject) {
    if (pNext == NULL) {
        List_Append(pList, pObject);
    } else if (pNext == pList->first) {
        List_Prepend(pList, pObject);
    } else {
        Node* nextNode = OBJ_TO_NODE(pList, pNext);
        Node* prevNode = OBJ_TO_NODE(pList, nextNode->prev);
        Node* newNode = OBJ_TO_NODE(pList, pObject);

        // prevNode <- newNode
        newNode->prev = nextNode->prev;
        // prevNode <- newNode -> nextNode
        newNode->next = pNext;
        // prevNode <-> newNode -> nextNode
        prevNode->next = pObject;
        // prevNode <-> newNode <-> nextNode
        OBJ_TO_NODE(pList, pNext)->prev = pObject;

        pList->size++;
    }
}

void List_Remove(List* pList, void* pObject) {
    Node* node = OBJ_TO_NODE(pList, pObject);

    // Fix previous node relationship
    if (node->prev == NULL) {
        pList->first = OBJ_TO_NODE(pList, pObject)->next;
    } else {
        OBJ_TO_NODE(pList, node->prev)->next = node->next;
    }

    // Fix next node relationship
    if (node->next == NULL) {
        pList->last = node->prev;
    } else {
        OBJ_TO_NODE(pList, node->next)->prev = node->prev;
    }

    node->prev = NULL;
    node->next = NULL;

    pList->size--;
}

void* List_GetNext(const List* pList, const void* pObject) {
    if (pObject == NULL) {
        return pList->first;
    }

    return OBJ_TO_NODE(pList, pObject)->next;
}

void* List_GetPrev(const List* pList, const void* pObject) {
    if (pObject == NULL) {
        return pList->last;
    }

    return OBJ_TO_NODE(pList, pObject)->prev;
}

void* List_GetNth(const List* pList, u16 n) {
    int i;
    void* pIt;

    for (i = 0, pIt = NULL; pIt = List_GetNext(pList, pIt); i++) {
        if (n == i) {
            return pIt;
        }
    }

    return NULL;
}

} // namespace ut
} // namespace nw4r
