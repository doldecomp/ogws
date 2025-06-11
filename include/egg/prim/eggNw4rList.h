#ifndef EGG_PRIM_NW4R_LIST_H
#define EGG_PRIM_NW4R_LIST_H
#include <egg/types_egg.h>

#include <nw4r/ut.h>

namespace EGG {

template <typename T> class TNw4rList {
public:
    TNw4rList() {
        nw4r::ut::List_Init(&mList, T::getLinkOffset());
    }

    void append(T* pObject) {
        nw4r::ut::List_Append(&mList, pObject);
    }
    void remove(T* pObject) {
        nw4r::ut::List_Remove(&mList, pObject);
    }

    T* getNext(T* pObject) {
        return static_cast<T*>(nw4r::ut::List_GetNext(&mList, pObject));
    }

private:
    nw4r::ut::List mList; // at 0x0
};

} // namespace EGG

/**
 * List for-each macro.
 *
 * @param TYPE Element type
 * @param NAME Element name
 * @param LIST Reference to list
 */
#define EGG_NW4R_LIST_FOREACH(TYPE, NAME, LIST)                                \
    for (TYPE* NAME = NULL; (NAME = (LIST).getNext(NAME)) != NULL;)

#endif
