#ifndef RP_KERNEL_KOKESHI_CONTROLLER_MGR_H
#define RP_KERNEL_KOKESHI_CONTROLLER_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics.h>
#include <Pack/RPKernel/RPSysKokeshiManager.h>

#include <egg/core.h>

#include <revolution/WPAD.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class IRPSysKokeshiCtrlDataCallback;
class RPSysKokeshiCtrlDataMgr;

/**
 * @brief Controller Mii manager
 */
class RPSysKokeshiCtrlMgr {
private:
    /**
     * @brief Lifetime manager
     */
    class Disposer : public EGG::Disposer {
    public:
        /**
         * @brief Destructor
         */
        virtual ~Disposer() override { // at 0x8
            RP_GET_INSTANCE(RPSysKokeshiManager)->ClearCtrlMgr();
        }
    };

    //! Disposer for this manager
    Disposer mDisposer; // at 0x0

private:
    void* unk10; // at 0x10
    //! Data manager for each controller
    RPSysKokeshiCtrlDataMgr* mpDataMgrs[WPAD_MAX_CONTROLLERS]; // at 0x14

public:
    /**
     * @brief Constructor
     *
     * @param pCallback Controller data callback
     * @param pParentHeap Heap to use as the parent of the controller data heap
     * @param heapSize Size of the controller data heap
     */
    RPSysKokeshiCtrlMgr(IRPSysKokeshiCtrlDataCallback* pCallback,
                        EGG::Heap* pParentHeap, u32 heapSize);

    /**
     * @brief Destructor
     */
    virtual ~RPSysKokeshiCtrlMgr(); // at 0x8

    /**
     * @brief Notifies the user that all resources will be destroyed
     *
     * @param chan WPAD channel of the data manager
     */
    void notifyReleaseResource(s32 chan);

    /**
     * @brief Resets the internal state for creating resources
     *
     * @param chan WPAD channel of the data manager
     */
    void resetResource(s32 chan);

    /**
     * @brief Tests whether the specified data manager is in an idle state
     *
     * @param chan WPAD channel of the data manager
     */
    BOOL isIdle(s32 chan) const;

    /**
     * @brief Tests whether an error occured while loading data
     *
     * @param chan WPAD channel of the data manager
     */
    BOOL isLoadError(s32 chan) const;

    /**
     * @brief Creates resources for the next Mii in each database
     */
    void createResource();

    /**
     * @brief Gets the heap used for resource allocation by the specified data
     * manager
     *
     * @param chan WPAD channel of the data manager
     */
    EGG::Heap* getResourceHeap(s32 chan);

    /**
     * @brief Appends a new file to the file resource list
     *
     * @param chan WPAD channel of the data manager
     * @param rd File resource descriptor
     */
    void appendFile(s32 chan, u16 rd);

    /**
     * @brief Appends a new model to the model resource list
     *
     * @param chan WPAD channel of the data manager
     * @param pModel New model
     */
    void appendModel(s32 chan, RPGrpModel* pModel);

    /**
     * @brief Updates each data manager's state
     */
    void calc();
};

//! @}

#endif
