#ifndef NW4R_EF_ACTIVITY_LIST_H
#define NW4R_EF_ACTIVITY_LIST_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ut.h>

namespace nw4r {
namespace ef {

inline u16 UtlistSize(const ut::List* pList) {
    return pList->numObjects;
}

class ActivityList {
public:
    ut::List mActiveList;  // at 0x0
    ut::List mClosingList; // at 0xC
    u16 mNumActive;        // at 0x18

public:
    ActivityList() {
        SetOffset(0);
    }

    explicit ActivityList(u16 offset) {
        SetOffset(offset);
    }

    void SetOffset(u16 offset) {
        ut::List_Init(&mActiveList, offset);
        ut::List_Init(&mClosingList, offset);
        mNumActive = 0;
    }

    void Initialize() {
        mActiveList.headObject = NULL;
        mActiveList.numObjects = 0;
        mActiveList.tailObject = NULL;

        mClosingList.headObject = NULL;
        mClosingList.numObjects = 0;
        mClosingList.tailObject = NULL;

        mNumActive = 0;
    }

    u32 GetNumActive() const {
        return mActiveList.numObjects;
    }

    void ToActive(void* pObject) {
        ut::List_Append(&mActiveList, pObject);
        mNumActive++;
    }

    void ToClosing(void* pObject) {
        ut::List_Remove(&mActiveList, pObject);
        ut::List_Append(&mClosingList, pObject);
    }

    void ToWait(void* /* pObject */) {
        mNumActive--;
    }

    void ToFree(void* pObject) {
        ut::List_Remove(&mClosingList, pObject);
    }
};

} // namespace ef
} // namespace nw4r

#endif
