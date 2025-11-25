#ifndef RP_KERNEL_KOKESHI_CTRL_DATA_MGR_H
#define RP_KERNEL_KOKESHI_CTRL_DATA_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics.h>

#include <egg/core.h>

#include <nw4r/ut.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class IRPSysKokeshiCtrlDataCallback;
class RPSysKokeshiCtrlDataLoader;
class RPSysKokeshiIterater;

/**
 * @brief Controller Mii data manager
 */
class RPSysKokeshiCtrlDataMgr {
private:
    /**
     * @brief Mii file resource
     */
    struct FileResource {
        //! Linked-list node
        NW4R_UT_LIST_LINK_DECL(); // at 0x0
        //! Resource file descriptor
        u16 rd; // at 0x8
    };

    /**
     * @brief Mii model resource
     */
    struct ModelResource {
        //! Linked-list node
        NW4R_UT_LIST_LINK_DECL(); // at 0x0
        //! Model data
        RPGrpModel* pModel; // at 0x8
    };

    /**
     * @brief State machine state
     */
    enum EState {
        EState_Idle,    //!< Wait for a request
        EState_Release, //!< Notify the user of released resources
        EState_Reset,   //!< Release old data
        EState_Load,    //!< Load controller data
        EState_Create,  //!< Ready to create new resources
    };

private:
    //! Current state
    EState mState; // at 0x0
    //! Size of the controller data heap
    u32 mHeapSize; // at 0x4

    //! Controller data loader
    RPSysKokeshiCtrlDataLoader* mpLoader; // at 0x8
    //! Controller Mii iterator
    RPSysKokeshiIterater* mpIterator; // at 0xC
    //! Controller data callback
    IRPSysKokeshiCtrlDataCallback* mpCallback; // at 0x10

    //! Parent of the controller data heap
    EGG::Heap* mpParentHeap; // at 0x14
    //! Controller data heap
    EGG::Heap* mpHeap; // at 0x18
    //! Controller data allocator
    EGG::Allocator* mpAllocator; // at 0x1C

    //! List of acquired resources
    nw4r::ut::List mResourceList; // at 0x20
    //! List of created models
    nw4r::ut::List mModelList; // at 0x2C

public:
    /**
     * @brief Construct
     *
     * @param pCallback Controller data callback
     * @param pParentHeap Heap to use as the parent of the controller data heap
     * @param heapSize Size of the controller data heap
     * @param index WPAD channel to use
     */
    RPSysKokeshiCtrlDataMgr(IRPSysKokeshiCtrlDataCallback* pCallback,
                            EGG::Heap* pParentHeap, u32 heapSize, s32 chan);

    /**
     * @brief Destructor
     */
    virtual ~RPSysKokeshiCtrlDataMgr(); // at 0x8

    /**
     * @brief Notifies the user that all resources will be destroyed
     */
    void notifyReleaseResource();

    /**
     * @brief Resets the internal state for creating resources
     */
    void resetResource();

    /**
     * @brief Tests whether the manager is in an idle state
     */
    BOOL isIdle() const;

    /**
     * @brief Tests whether an error occured while loading data
     */
    BOOL isLoadError() const;

    /**
     * @brief Creates resources for the next Mii in the database
     */
    void createResource();

    /**
     * @brief Appends a new file to the file resource list
     *
     * @param rd File resource descriptor
     */
    void appendFile(u16 rd);

    /**
     * @brief Appends a new model to the model resource list
     *
     * @param pModel New model
     */
    void appendModel(RPGrpModel* pModel);

    /**
     * @brief Updates the manager state
     */
    void calc();

    /**
     * @brief Gets the heap used by this data manager
     */
    EGG::Heap* getHeap() const {
        return mpHeap;
    }

private:
    /**
     * @brief Releases resources and attempts to reload controller Mii data
     */
    void resetData();
};

//! @}

#endif
