#ifndef RP_KERNEL_NWC24_MANAGER_H
#define RP_KERNEL_NWC24_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

#include <egg/core.h>

//! @addtogroup rp_kernel
//! @{

// Forward declaration
class RPSysAvatar;

/**
 * @brief WiiConnect24 library manager
 */
class RPSysNWC24Manager {
protected:
    //! Work buffer for NWC24
    u8* mpNwc24Work; // at 0x0
    //! Work buffer for message formatting
    wchar_t* mpMsgWork; // at 0x4

public:
    /**
     * @brief Suspends the WiiConnect24 scheduler so the library can be opened
     */
    static void initialize();

    /**
     * @brief Constructor
     *
     * @param pHeap Heap to use for allocations
     */
    RPSysNWC24Manager(EGG::Heap* pHeap);

    /**
     * @brief Destructor
     */
    virtual ~RPSysNWC24Manager(); // at 0x8

    /**
     * @brief Attempts to commit a message to the Wii Message Board
     *
     * @param pWork Library work buffer
     * @param pAltName Mail letter alt name
     * @param pMsg Mail letter message (can be a format string)
     * @param date Mail letter send date
     * @param pAvatar Mii avatar to include
     * @param argc Number of message format arguments
     * @param argv Message format arguments
     * @return Success
     */
    bool commitMail(const wchar_t* pAltName, const wchar_t* pMsg, RPTime16 date,
                    const RPSysAvatar* pAvatar, int argc, va_list argv);

private:
    //! Size of the message work buffer
    static const int MSG_BUFFER_SIZE = 1024;

private:
    /**
     * @brief Attempts to open the WiiConnect24 library for use
     *
     * @return Success
     */
    bool openLib() DECOMP_DONT_INLINE;

    /**
     * @brief Closes the WiiConnect24 library
     */
    void closeLib();

private:
    //! Whether the last NWC24 operation was successful
    static BOOL sSuccess;
};

//! @}

#endif
