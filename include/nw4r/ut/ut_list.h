#ifndef NW4R_UT_LIST_H
#define NW4R_UT_LIST_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace ut {

struct List {
    void* first; // at 0x0
    void* last;  // at 0x4
    u16 size;    // at 0x8
    u16 offset;  // at 0xA
};

struct Node {
    void* prev; // at 0x0
    void* next; // at 0x4
};

void List_Init(List* pList, u16 offset);
void List_Append(List* pList, void* pObject);
void List_Prepend(List* pList, void* pObject);
void List_Insert(List* pList, void* pNext, void* pObject);
void List_Remove(List* pList, void* pObject);
void* List_GetNext(const List* pList, const void* pObject);
void* List_GetPrev(const List* pList, const void* pObject);
void* List_GetNth(const List* pList, u16 n);

inline void* List_GetFirst(const List* pList) {
    return List_GetNext(pList, NULL);
}

inline const void* List_GetFirstConst(const List* pList) {
    return List_GetFirst(pList);
}

inline void* List_GetLast(const List* pList) {
    return List_GetPrev(pList, NULL);
}

inline const void* List_GetLastConst(const List* pList) {
    return List_GetLast(pList);
}

inline const void* List_GetNextConst(const List* pList, const void* pObject) {
    return List_GetNext(pList, pObject);
}

inline const void* List_GetNthConst(const List* pList, u16 n) {
    return List_GetNth(pList, n);
}

inline u16 List_GetSize(const List* pList) {
    return pList->size;
}

} // namespace ut
} // namespace nw4r

#endif
