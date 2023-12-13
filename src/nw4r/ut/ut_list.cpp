#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

#define OBJ_TO_NODE(list, object)                                              \
    reinterpret_cast<Node*>((char*)object + list->offset)

void List_Init(List* list, u16 offset) {
    list->first = NULL;
    list->last = NULL;
    list->size = NULL;
    list->offset = offset;
}

static void SetFirstObject(List* list, void* object) {
    Node* node = OBJ_TO_NODE(list, object);
    node->next = NULL;
    node->prev = NULL;

    list->first = object;
    list->last = object;

    list->size++;
}

void List_Append(List* list, void* object) {
    if (list->first == NULL) {
        SetFirstObject(list, object);
    } else {
        // Old tail <- New tail relationship
        Node* node = OBJ_TO_NODE(list, object);
        node->prev = list->last;
        node->next = NULL;

        // Old tail -> New tail relationship
        OBJ_TO_NODE(list, list->last)->next = object;
        list->last = object;

        list->size++;
    }
}

void List_Prepend(List* list, void* object) {
    if (list->first == NULL) {
        SetFirstObject(list, object);
    } else {
        // New head -> Old head relationship
        Node* node = OBJ_TO_NODE(list, object);
        node->prev = NULL;
        node->next = list->first;

        // New head <- Old head relationship
        OBJ_TO_NODE(list, list->first)->prev = object;
        list->first = object;

        list->size++;
    }
}

void List_Insert(List* list, void* next, void* object) {
    if (next == NULL) {
        List_Append(list, object);
    } else if (next == list->first) {
        List_Prepend(list, object);
    } else {
        Node* nextNode = OBJ_TO_NODE(list, next);
        Node* prevNode = OBJ_TO_NODE(list, nextNode->prev);
        Node* newNode = OBJ_TO_NODE(list, object);

        // prevNode <- newNode
        newNode->prev = nextNode->prev;
        // prevNode <- newNode -> nextNode
        newNode->next = next;
        // prevNode <-> newNode -> nextNode
        prevNode->next = object;
        // prevNode <-> newNode <-> nextNode
        OBJ_TO_NODE(list, next)->prev = object;

        list->size++;
    }
}

void List_Remove(List* list, void* object) {
    Node* node = OBJ_TO_NODE(list, object);

    // Fix previous node relationship
    if (node->prev == NULL) {
        list->first = OBJ_TO_NODE(list, object)->next;
    } else {
        OBJ_TO_NODE(list, node->prev)->next = node->next;
    }

    // Fix next node relationship
    if (node->next == NULL) {
        list->last = node->prev;
    } else {
        OBJ_TO_NODE(list, node->next)->prev = node->prev;
    }

    node->prev = NULL;
    node->next = NULL;

    list->size--;
}

void* List_GetNext(const List* list, const void* object) {
    if (object == NULL) {
        return list->first;
    }

    return OBJ_TO_NODE(list, object)->next;
}

void* List_GetPrev(const List* list, const void* object) {
    if (object == NULL) {
        return list->last;
    }

    return OBJ_TO_NODE(list, object)->prev;
}

void* List_GetNth(const List* list, u16 n) {
    int i;
    void* object;

    for (i = 0, object = NULL; object = List_GetNext(list, object); i++) {
        if (n == i) {
            return object;
        }
    }

    return NULL;
}

} // namespace ut
} // namespace nw4r
