#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <egg/core.h>

#include <nw4r/lyt.h>

#include <revolution/MEM.h>

/**
 * @brief Disables freeing layout memory in favor of garbage collection
 *
 * @param pAllocator Memory allocator
 * @param pBlock Memory block
 */
static void FreeMemory(MEMAllocator* /* pAllocator */, void* /* pBlock */) {}

/**
 * @brief Constructor
 *
 * @param pHeap Heap to use for allocations
 * @param align Required byte alignment for allocations
 */
RPSysLytAllocator::RPSysLytAllocator(EGG::Heap* pHeap, s32 align)
    : EGG::Allocator(pHeap, align) {

    mExFuncs.allocFunc = funcs->allocFunc;
    mExFuncs.freeFunc = FreeMemory;

    // Redirect base allocator
    funcs = &mExFuncs;
}

/**
 * @brief Destructor
 */
RPSysLytAllocator::~RPSysLytAllocator() {}
