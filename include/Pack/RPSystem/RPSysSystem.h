#ifndef RP_SYSTEM_SYSTEM_H
#define RP_SYSTEM_SYSTEM_H
#include <Pack/types_pack.h>

#include <Pack/RPSystem/RPSysSceneCreator.h>

#include <egg/core.h>

#include <nw4r/ut.h>

#include <revolution/GX.h>
#include <revolution/OS.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Pack Project engine system
 */
class RPSysSystem {
public:
    /**
     * @brief Gets this class's singleton instance
     */
    static RPSysSystem* instance() {
        return spInstance;
    }

    /**
     * @brief Auto-detects the screen's aspect ratio
     */
    static void setupTVMode();
    /**
     * @brief Auto-detects the render mode and progressive setting
     */
    static void setupRenderMode();

    /**
     * @brief Initializes the RP engine and its core components
     */
    static void initialize();

    /**
     * @brief Creates this class's singleton instance
     */
    static void create();

    /**
     * @brief Gets the width of the framebuffer, in pixels
     */
    u16 getFBWidth() const;
    /**
     * @brief Gets the height of the framebuffer, in pixels
     */
    u16 getFBHeight() const;

    /**
     * @brief Loads the Pack Project build timestamp from the disc
     */
    void createTimeStamp();
    /**
     * @brief Creates a work buffer for the effect manager
     */
    void createEffectWork();
    /**
     * @brief Creates the engine's core components using the system heap
     */
    void createFromSystemHeap();

    /**
     * @brief Prepares the engine for the first frame
     */
    void setup();
    /**
     * @brief Enters the engine's main loop
     */
    void mainLoop();

    /**
     * @brief Gets the ID of the boot scene
     */
    RPSysSceneCreator::ESceneID getBootScene();

    /**
     * @brief Gets the current clock time represented as a 32-bit calendar time
     */
    RPTime32 getCalendarTime32();
    /**
     * @brief Gets the current clock time represented as a 16-bit calendar time
     */
    RPTime16 getCalendarTime16();

    /**
     * @brief Splits 32-bit calendar time into parts
     * @note If no input time is specified, this function operates on the
     * current clock time.
     *
     * @param pTime32 Input time
     * @param rWDay Day of the week
     * @param rYear Year
     * @param rMon Month (one-indexed)
     * @param rMDay Day of the month
     * @param rHour Hour
     */
    void getCalendarTime(const RPTime32* pTime32, u32& rWDay, u32& rYear,
                         u32& rMon, u32& rMDay, u32& rHour);

    /**
     * @brief Splits 16-bit calendar time into parts
     * @note If no input time is specified, this function operates on the
     * current clock time.
     *
     * @param pTime16 Input time
     * @param rYear Year
     * @param rMon Month (one-indexed)
     * @param rMDay Day of the month
     */
    void getCalendarTime(const RPTime16* pTime16, u32& rYear, u32& rMon,
                         u32& rMDay);

    /**
     * @brief Shuts down the engine and exits the application
     * @details Depending on the instructions from the scene manager, this will
     * either exit to the system menu or shutdown the console.
     */
    void systemShutDown();

    /**
     * @brief Updates the system state during resource loading
     *
     * @param hide Disable "Now Loading" text
     */
    void loadFrameWork(bool hide);

    /**
     * @brief Gets the number of ticks per frame
     */
    u8 getFrameRate() const;
    /**
     * @brief Gets the modify ratio of the display
     */
    f32 getModifyRatio() const;

    /**
     * @brief Sets the background clear color of the EFB
     *
     * @param color Clear color
     */
    void setDisplayClearColor(nw4r::ut::Color color);

    /**
     * @brief Destroys the specified heap
     *
     * @param pHeap Heap to destroy
     */
    void destroyHeap(EGG::Heap* pHeap);

    /**
     * @brief Allocates memory from the specified heap
     *
     * @param pHeap Heap to allocate from
     * @param size Amount of memory required
     * @param align Required byte-alignment
     * @return void* Allocated memory block
     */
    void* alloc(EGG::Heap* pHeap, u32 size, s32 align = 4) {
        return EGG::Heap::alloc(size, align, pHeap);
    }

    /**
     * @brief Frees memory to the specified heap
     *
     * @param pHeap Heap to free to
     * @param pBlock Memory block to free
     */
    void free(EGG::Heap* pHeap, void* pBlock) {
        return EGG::Heap::free(pBlock, pHeap);
    }

    /**
     * @brief Initializes the load count to zero frames
     */
    void startLoadCount();
    /**
     * @brief Tests whether the current load count is over five seconds (600f)
     */
    bool isLoadCountEnd() const;

    /**
     * @brief Turns on/off screen dimming
     * @note If "Screen Saver Mode" is disabled, dimming is always OFF.
     *
     * @param dim Whether to dim the screen
     */
    void setDimming(BOOL dim);

    /**
     * @brief Gets the heap for the resource manager
     */
    EGG::Heap* getResourceHeap() const {
        return mpResourceHeap;
    }

    /**
     * @brief Gets the thread for asynchronous NAND operations
     */
    EGG::TaskThread* getNandThread();
    /**
     * @brief Gets the thread for asynchronous disc operations
     */
    EGG::TaskThread* getDvdThread();
    /**
     * @brief Gets the thread for asynchronous WiiConnect24 operations
     */
    EGG::TaskThread* getWc24Thread();

    /**
     * @brief Gets the task-end thread message for asynchronous NAND operations
     */
    OSMessage getNandEndMessage() const;
    /**
     * @brief Gets the task-end thread message for asynchronous disc operations
     */
    OSMessage getDvdEndMessage() const;

    /**
     * @brief Gets the Pack Project build information
     */
    const char* getTimeStampString();

    /**
     * @brief Auto-detects project locale settings
     */
    void setupLocalSettings();

    /**
     * @brief Blocks the main thread until it is safe to change the render mode
     * @details Waits for either 100 frames or 1.6 seconds to pass.
     *
     * @history This arbitrary 1.6 second delay is likely from performance
     * metrics taken during development. This code exists in other EAD games
     * (notably Big Brain Academy and Mario Kart Wii), where the delay is
     * slightly changed.
     */
    void waitRenderModeChange();

    /**
     * @brief Installs reset and shutdown callbacks to the OS
     */
    void setCallBack();

private:
    /**
     * @brief Constructor
     */
    RPSysSystem();
    /**
     * @brief Destructor
     */
    virtual ~RPSysSystem();

    /**
     * @brief OS reset callback
     */
    static void softResetCallBack();
    /**
     * @brief OS shutdown callback
     */
    static void shutdownSystemCallBack();

private:
    //! Effect manager work memory size
    u32 mEffectWorkSize; // at 0x4

    //! Heap used by the resource manager
    EGG::Heap* mpResourceHeap; // at 0x8
    //! Heap reserving memory in the MEM1 region
    EGG::Heap* mpReserveHeap; // at 0xC
    //! Heap used for error handling when other heaps are exhausted
    EGG::Heap* mpAssertHeap; // at 0x10
    //! @unused
    EGG::Heap* HEAP_0x14;

    //! Backup of the EGG current heap while it is changed
    EGG::Heap* mpCurrentHeap; // at 0x18
    //! Mutex to guard changing the current heap
    OSMutex mCurrentHeapMutex; // at 0x1C

    //! Thread for asynchronous NAND operations
    EGG::TaskThread* mpNandThread; // at 0x34
    //! Thread for asynchronous disc operations
    EGG::TaskThread* mpDvdThread; // at 0x38
    //! Thread for asynchronous WiiConnect24 operations
    EGG::TaskThread* mpWc24Thread; // at 0x3C

    //! Task-end thread message for asynchronous NAND operations
    u32 mNandEndMessage; // at 0x40
    //! Task-end thread message for asynchronous disc operations
    u32 mDvdEndMessage; // at 0x44
    //! Task-end thread message for asynchronous WiiConnect24 operations
    u32 mWc24EndMessage; // at 0x48

    //! Number of ticks per frame
    u8 mFrameRate; // at 0x4C
    //! Average frame duration, in seconds (assumes 60fps)
    f32 mFrameTime; // at 0x50
    //! Total number of frames spent loading resources
    u32 mLoadCount; // at 0x54

    //! Pack Project build information
    char* mpTimeStampString; // at 0x58

    //! Engine configuration
    // static RPSysConfigData sConfigData;

    //! Active render mode
    static GXRenderModeObj* spRenderModeObj;
    //! Render mode format @see RPSysRenderMode::EFormat
    // static u32 sRenderModeFormat;
    //! @brief Time (in milliseconds) when the render mode was setup
    //! @remark This value is only non-zero when scan mode/TV format is changed
    //! and the system must wait.
    static u32 sRenderModeWaitStart;

    //! Class singleton instance
    static RPSysSystem* spInstance;
};

//! @}

#endif
