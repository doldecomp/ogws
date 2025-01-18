#ifndef NW4R_UT_LINKLIST_H
#define NW4R_UT_LINKLIST_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace ut {

struct List {
    void* headObject; // at 0x0
    void* tailObject; // at 0x4
    u16 numObjects;   // at 0x8
    u16 offset;       // at 0xA
};

struct Link {
    void* prevObject; // at 0x0
    void* nextObject; // at 0x4
};

void List_Init(List* pList, u16 offset);

void List_Append(List* pList, void* pObject);
void List_Prepend(List* pList, void* pObject);

void List_Insert(List* pList, void* pTarget, void* pObject);
void List_Remove(List* pList, void* pObject);

void* List_GetNext(const List* pList, const void* pObject);
inline const void* List_GetNextConst(const List* pList, const void* pObject) {
    return List_GetNext(pList, pObject);
}

void* List_GetPrev(const List* pList, const void* pObject);
inline const void* List_GetPrevConst(const List* pList, const void* pObject) {
    return List_GetPrev(pList, pObject);
}

void* List_GetNth(const List* pList, u16 n);
inline const void* List_GetNthConst(const List* pList, u16 n) {
    return List_GetNth(pList, n);
}

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

inline u16 List_GetSize(const List* pList) {
    return pList->numObjects;
}

/**
 * Gets the underlying Link within the specified object.
 */
#define NW4R_UT_LIST_GET_LINK(LIST, OBJ)                                       \
    reinterpret_cast<nw4r::ut::Link*>((u8*)(OBJ) + (LIST).offset)

/**
 * List for-each macro.
 *
 * Access the current element with "it"
 */
#define NW4R_UT_LIST_FOREACH(T, LIST, ...)                                     \
    {                                                                          \
        for (T* it = static_cast<T*>(nw4r::ut::List_GetFirst(&(LIST)));        \
             it != NULL;                                                       \
             it = static_cast<T*>(nw4r::ut::List_GetNext(&(LIST), it))) {      \
                                                                               \
            __VA_ARGS__;                                                       \
        }                                                                      \
    }

/**
 * List for-each macro, with robust iteration.
 *
 * Access the current element with "it"
 */
#define NW4R_UT_LIST_FOREACH_SAFE(T, LIST, ...)                                \
    {                                                                          \
        T* it;                                                                 \
        T* impl;                                                               \
                                                                               \
        for (it = static_cast<T*>(nw4r::ut::List_GetFirst(&(LIST)));           \
             it != NULL; it = impl) {                                          \
                                                                               \
            impl = static_cast<T*>(nw4r::ut::List_GetNext(&(LIST), it));       \
                                                                               \
            __VA_ARGS__;                                                       \
        }                                                                      \
    }

} // namespace ut
} // namespace nw4r

#endif
