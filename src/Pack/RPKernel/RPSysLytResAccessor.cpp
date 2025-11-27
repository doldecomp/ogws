#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <egg/core.h>

#include <nw4r/lyt.h>

/******************************************************************************
 *
 * InternalAccessor
 *
 ******************************************************************************/

/**
 * @brief Constructor
 */
RPSysLytResAccessor::InternalAccessor::InternalAccessor() {}

/**
 * @brief Gets the specified resource from the currently open archive
 * @details Font queries are redirected to the font manager
 *
 * @param type Resource type
 * @param pName Resource name
 * @param[out] pSize Resource data size
 */
void* RPSysLytResAccessor::InternalAccessor::GetResource(u32 type,
                                                         const char* pName,
                                                         u32* pSize) {
    switch (type) {
    case RES_TYPE_FONT: {
        return RP_GET_INSTANCE(RPSysFontManager)->GetResFontData(pName);
        break;
    }

    default: {
        return nw4r::lyt::ArcResourceAccessor::GetResource(type, pName, pSize);
    }
    }
}

/******************************************************************************
 *
 * RPSysLytResAccessor
 *
 ******************************************************************************/

/**
 * @brief Constructor
 */
RPSysLytResAccessor::RPSysLytResAccessor() : mpImpl(NULL) {}

/**
 * @brief Creates a resource accessor from the specified heap
 *
 * @param pHeap Heap to use for allocations
 */
RPSysLytResAccessor* RPSysLytResAccessor::create(EGG::Heap* pHeap) {
    if (pHeap == NULL) {
        pHeap = EGG::Heap::getCurrentHeap();
    }

    RPSysLytResAccessor* p = new (pHeap) RPSysLytResAccessor();

    if (p != NULL) {
        p->mpImpl = new (pHeap) InternalAccessor();
    }

    return p;
}

/**
 * @brief Attempts to mount an archive
 *
 * @param pBinary Archive binary data
 * @param pRootDir Root directory to open (optional)
 * @return Success
 */
bool RPSysLytResAccessor::mountArchive(void* pBinary, const char* pRootDir) {
    bool success = false;

    if (!mpImpl->IsAttached()) {
        if (pRootDir == NULL) {
            pRootDir = "";
        }

        success = mpImpl->Attach(pBinary, pRootDir);
    }

    return success;
}
