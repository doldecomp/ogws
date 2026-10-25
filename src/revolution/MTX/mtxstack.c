#include <revolution/MTX.h>
#include <revolution/MTX/internal/mtxAssert.h>
#include <revolution/OS.h>

#define STACK_OVERFLOW_CHECK(sPtr)                                             \
    (u32)((sPtr->stackPtr - sPtr->stackBase) / 3) >= sPtr->numMtx - 1

void MTXInitStack(MtxStackPtr sPtr, u32 numMtx) {
    OS_DEBUG_ASSERT(sPtr, "MTXInitStack():  NULL MtxStackPtr 'sPtr' ");
    OS_DEBUG_ASSERT(sPtr->stackBase, "MTXInitStack():  'sPtr' contains a NULL ptr to stack memory ");
    OS_DEBUG_ASSERT(numMtx != 0, "MTXInitStack():  'numMtx' is 0 ");

    sPtr->numMtx = numMtx;
    sPtr->stackPtr = NULL;
}

MtxPtr MTXPush(MtxStackPtr sPtr, CMtxPtr m) {
    OS_DEBUG_ASSERT(sPtr, "MTXPush():  NULL MtxStackPtr 'sPtr' ");
    OS_DEBUG_ASSERT(sPtr->stackBase, "MTXPush():  'sPtr' contains a NULL ptr to stack memory ");
    OS_DEBUG_ASSERT(m, "MTXPush():  NULL MtxPtr 'm' ");

    if (sPtr->stackPtr == NULL) {
        sPtr->stackPtr = sPtr->stackBase;
        MTXCopy(m, sPtr->stackPtr);
    } else {
        if (STACK_OVERFLOW_CHECK(sPtr)) {
            OS_DEBUG_ASSERT(FALSE, "MTXPush():  stack overflow ");
        }

        MTXCopy(m, sPtr->stackPtr + 3);
        sPtr->stackPtr += 3;
    }

    return sPtr->stackPtr;
}

MtxPtr MTXPushFwd(MtxStackPtr sPtr, CMtxPtr m) {
    OS_DEBUG_ASSERT(sPtr, "MTXPushFwd():  NULL MtxStackPtr 'sPtr' ");
    OS_DEBUG_ASSERT(sPtr->stackBase, "MTXPushFwd():  'sPtr' contains a NULL ptr to stack memory ");
    OS_DEBUG_ASSERT(m, "MTXPushFwd():  NULL MtxPtr 'm' ");

    if (sPtr->stackPtr == NULL) {
        sPtr->stackPtr = sPtr->stackBase;
        MTXCopy(m, sPtr->stackPtr);
    } else {
        if (STACK_OVERFLOW_CHECK(sPtr)) {
            OS_DEBUG_ASSERT(FALSE, "MTXPushFwd():  stack overflow");
        }

        MTXConcat(sPtr->stackPtr, m, sPtr->stackPtr + 3);
        sPtr->stackPtr += 3;
    }

    return sPtr->stackPtr;
}

MtxPtr MTXPushInv(MtxStackPtr sPtr, CMtxPtr m) {
    Mtx inv;

    OS_DEBUG_ASSERT(sPtr, "MTXPushInv():  NULL MtxStackPtr 'sPtr' ");
    OS_DEBUG_ASSERT(sPtr->stackBase, "MTXPushInv():  'sPtr' contains a NULL ptr to stack memory ");
    OS_DEBUG_ASSERT(m, "MTXPushInv():  NULL MtxPtr 'm' ");

    MTXInverse(m, inv);

    if (sPtr->stackPtr == NULL) {
        sPtr->stackPtr = sPtr->stackBase;
        MTXCopy(inv, sPtr->stackPtr);
    } else {
        if (STACK_OVERFLOW_CHECK(sPtr)) {
            OS_DEBUG_ASSERT(FALSE, "MTXPushInv():  stack overflow");
        }

        MTXConcat(inv, sPtr->stackPtr, sPtr->stackPtr + 3);
        sPtr->stackPtr += 3;
    }

    return sPtr->stackPtr;
}

MtxPtr MTXPushInvXpose(MtxStackPtr sPtr, CMtxPtr m) {
    Mtx invXpose;

    OS_DEBUG_ASSERT(sPtr, "MTXPushInvXpose():  NULL MtxStackPtr 'sPtr' ");
    OS_DEBUG_ASSERT(sPtr->stackBase, "MTXPushInvXpose():  'sPtr' contains a NULL ptr to stack memory ");
    OS_DEBUG_ASSERT(m, "MTXPushInvXpose():  NULL MtxPtr 'm' ");

    MTXInverse(m, invXpose);
    MTXTranspose(invXpose, invXpose);

    if (sPtr->stackPtr == NULL) {
        sPtr->stackPtr = sPtr->stackBase;
        MTXCopy(invXpose, sPtr->stackPtr);
    } else {
        if (STACK_OVERFLOW_CHECK(sPtr)) {
            OS_DEBUG_ASSERT(FALSE, "MTXPushInvXpose():  stack overflow ");
        }

        MTXConcat(sPtr->stackPtr, invXpose, sPtr->stackPtr + 3);
        sPtr->stackPtr += 3;
    }

    return sPtr->stackPtr;
}

MtxPtr MTXPop(MtxStackPtr sPtr) {
    OS_DEBUG_ASSERT(sPtr, "MTXPop():  NULL MtxStackPtr 'sPtr' ");
    OS_DEBUG_ASSERT(sPtr->stackBase, "MTXPop():  'sPtr' contains a NULL ptr to stack memory ");

    if (sPtr->stackPtr == NULL) {
        return NULL;
    }

    if (sPtr->stackBase == sPtr->stackPtr) {
        sPtr->stackPtr = NULL;
        return NULL;
    }

    sPtr->stackPtr -= 3;
    return sPtr->stackPtr;
}

MtxPtr MTXGetStackPtr(MtxStackPtr sPtr) {
    OS_DEBUG_ASSERT(sPtr, "MTXGetStackPtr():  NULL MtxStackPtr 'sPtr' ");
    OS_DEBUG_ASSERT(sPtr->stackBase, "MTXGetStackPtr():  'sPtr' contains a NULL ptr to stack memory ");
    return sPtr->stackPtr;
}
