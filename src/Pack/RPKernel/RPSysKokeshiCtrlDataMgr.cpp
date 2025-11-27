#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>

#include <egg/core.h>

#include <nw4r/ut.h>

#include <RVLFaceLib.h>

/**
 * @brief Constructor
 *
 * @param pCallback Controller data callback
 * @param pParentHeap Heap to use as the parent of the controller data heap
 * @param heapSize Size of the controller data heap
 * @param chan WPAD channel to use
 */
RPSysKokeshiCtrlDataMgr::RPSysKokeshiCtrlDataMgr(
    IRPSysKokeshiCtrlDataCallback* pCallback, EGG::Heap* pParentHeap,
    u32 heapSize, s32 chan) {

    mHeapSize = heapSize;

    mpLoader = RP_GET_INSTANCE(RPSysKokeshiManager)->GetCtrlDataLoader(chan);
    mpIterator = new RPSysKokeshiIterater(
        static_cast<RFLDataSource>(RFLDataSource_Controller1 + chan));

    mpCallback = pCallback;
    mpParentHeap = pParentHeap;

    mpHeap = EGG::ExpHeap::create(mHeapSize, mpParentHeap);
    mpAllocator = new (mpHeap) EGG::Allocator(mpHeap);

    NW4R_UT_LIST_INIT(mResourceList, FileResource);
    NW4R_UT_LIST_INIT(mModelList, ModelResource);

    mState = EState_Idle;
}

/**
 * @brief Destructor
 */
RPSysKokeshiCtrlDataMgr::~RPSysKokeshiCtrlDataMgr() {}

/**
 * @brief Notifies the user that all resources will be destroyed
 */
void RPSysKokeshiCtrlDataMgr::notifyReleaseResource() {
    if (mState != EState_Idle) {
        return;
    }

    mState = EState_Release;

    for (u8 i = 0; i < RFL_CTRL_CHAR_MAX; i++) {
        mpCallback->onReleaseResource(mpLoader->getChannel(), i);
    }
}

/**
 * @brief Resets the internal state for creating resources
 */
void RPSysKokeshiCtrlDataMgr::resetResource() {
    if (mState != EState_Idle) {
        return;
    }

    if (mpLoader->isError() == TRUE) {
        mState = EState_Idle;
    }

    mState = EState_Create;
    mpIterator->Reset();
}

/**
 * @brief Tests whether the manager is in an idle state
 */
BOOL RPSysKokeshiCtrlDataMgr::isIdle() const {
    return mState == EState_Idle ? TRUE : FALSE;
}

/**
 * @brief Tests whether an error occured while loading data
 */
BOOL RPSysKokeshiCtrlDataMgr::isLoadError() const {
    return mpLoader->isError();
}

/**
 * @brief Creates resources for the next Mii in the database
 */
void RPSysKokeshiCtrlDataMgr::createResource() {
    if (mState != EState_Create) {
        return;
    }

    EGG::Heap* pOldHeap = EGG::Heap::getCurrentHeap();
    EGG::Allocator* pOldAllocator = RPGrpModel::GetAllocator();

    // Take ownership of any graphics allocations in the callback
    mpHeap->becomeCurrentHeap();
    RPGrpModel::SetAllocator(mpAllocator);
    {
        if (mpIterator->Update()) {
            mpCallback->onCreateResource(mpLoader->getChannel(),
                                         mpIterator->GetIndex());
        } else {
            mState = EState_Idle;
        }
    }
    RPGrpModel::SetAllocator(pOldAllocator);
    pOldHeap->becomeCurrentHeap();
}

/**
 * @brief Appends a new file to the file resource list
 *
 * @param rd File resource descriptor
 */
void RPSysKokeshiCtrlDataMgr::appendFile(u16 rd) {
    FileResource* pResFile = new (mpHeap) FileResource();
    pResFile->rd = rd;
    nw4r::ut::List_Append(&mResourceList, pResFile);
}

/**
 * @brief Appends a new model to the model resource list
 *
 * @param pModel New model
 */
void RPSysKokeshiCtrlDataMgr::appendModel(RPGrpModel* pModel) {
    ModelResource* pResModel = new (mpHeap) ModelResource();
    pResModel->pModel = pModel;
    nw4r::ut::List_Append(&mModelList, pResModel);
}

/**
 * @brief Updates the manager state
 */
void RPSysKokeshiCtrlDataMgr::calc() {
    mpLoader->calc();

    switch (mState) {
    case EState_Idle: {
        break;
    }

    case EState_Release: {
        // Destroy logic happens outside of this function
        mState = EState_Reset;
        break;
    }

    case EState_Reset: {
        resetData();
        break;
    }

    case EState_Load: {
        if (!mpLoader->isIdle()) {
            break;
        }

        if (mpLoader->isError() == TRUE) {
            mState = EState_Idle;
        }

        mState = EState_Create;
        mpIterator->Reset();
        break;
    }

    case EState_Create: {
        break;
    }
    }
}

/**
 * @brief Releases resources and attempts to reload controller Mii data
 */
void RPSysKokeshiCtrlDataMgr::resetData() {
    RPGrpModelResManager* pResManager = RPGrpModelResManager::GetCurrent();

    NW4R_UT_LIST_FOREACH_SAFE (FileResource, it, mResourceList, {
        pResManager->Terminate(it->rd);
        nw4r::ut::List_Remove(&mResourceList, it);
    })

    NW4R_UT_LIST_FOREACH_SAFE (ModelResource, it, mModelList, {
        it->pModel->RemoveGenList();
        nw4r::ut::List_Remove(&mModelList, it);
    })

    if (mpHeap != NULL) {
        mpHeap->destroy();
    }

    mpHeap = NULL;
    mpAllocator = NULL;

    mpHeap = EGG::ExpHeap::create(mHeapSize, mpParentHeap);
    mpAllocator = new (mpHeap) EGG::Allocator(mpHeap);

    mState = EState_Load;
    mpLoader->load();
}
