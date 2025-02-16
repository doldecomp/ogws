#ifndef NW4R_LYT_LAYOUT_H
#define NW4R_LYT_LAYOUT_H
#include <nw4r/types_nw4r.h>

#include <nw4r/lyt/lyt_animation.h>
#include <nw4r/lyt/lyt_types.h>

#include <revolution/MEM.h>

namespace nw4r {
namespace lyt {

// Forward declarations
class GroupContainer;
class Pane;

/******************************************************************************
 *
 * Layout
 *
 ******************************************************************************/
class Layout {
public:
    static void* AllocMemory(u32 size) {
        return MEMAllocFromAllocator(mspAllocator, size);
    }
    static void FreeMemory(void* pBlock) {
        MEMFreeToAllocator(mspAllocator, pBlock);
    }

    Pane* GetRootPane() const {
        return mpRootPane;
    }

    GroupContainer* GetGroupContainer() const {
        return mpGroupContainer;
    }

    static MEMAllocator* GetAllocator() {
        return mspAllocator;
    }
    static void SetAllocator(MEMAllocator* pAllocator) {
        mspAllocator = pAllocator;
    }

protected:
    AnimTransformList mAnimTransList; // at 0x4
    Pane* mpRootPane;                 // at 0x10
    GroupContainer* mpGroupContainer; // at 0x14
    Size mLayoutSize;                 // at 0x18

private:
    static MEMAllocator* mspAllocator;
};

/******************************************************************************
 *
 * CreateObject
 *
 ******************************************************************************/
template <typename TObj> TObj* CreateObject() {
    void* pBuffer = Layout::AllocMemory(sizeof(TObj));
    if (pBuffer == NULL) {
        return NULL;
    }

    return new (pBuffer) TObj();
}

template <typename TObj, typename TParam> TObj* CreateObject(TParam param) {
    void* pBuffer = Layout::AllocMemory(sizeof(TObj));
    if (pBuffer == NULL) {
        return NULL;
    }

    return new (pBuffer) TObj(param);
}

template <typename TObj, typename TParam1, typename TParam2>
TObj* CreateObject(TParam1 param1, TParam2 param2) {

    void* pBuffer = Layout::AllocMemory(sizeof(TObj));
    if (pBuffer == NULL) {
        return NULL;
    }

    return new (pBuffer) TObj(param1, param2);
}

} // namespace lyt
} // namespace nw4r

#endif
