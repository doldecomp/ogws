#ifndef RP_KERNEL_FILE_H
#define RP_KERNEL_FILE_H
#include <Pack/types_pack.h>

#include <egg/core.h>

#include <nw4r/ut.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Cached resource file
 */
class RPSysFile : public EGG::Disposer {
public:
    /**
     * @brief Constructor
     *
     * @param pPath File path (absolute)
     * @param size File data size
     * @param pData File data pointer
     */
    RPSysFile(const char* pPath, s32 size, const void* pData);

    /**
     * @brief Destructor
     * @details The file is automatically removed from the resource cache.
     */
    virtual ~RPSysFile(); // at 0x8

    /**
     * @brief Gets the path to this file
     */
    const char* GetPath() const {
        return mPath;
    }

    /**
     * @brief Gets the size of this file
     */
    s32 GetSize() const {
        return mSize;
    }

    /**
     * @brief Gets the data of this file
     */
    const void* GetData() const {
        return mpData;
    }

public:
    //! Linked-list node used for cache lists
    NW4R_UT_LIST_LINK_DECL(); // at 0x10

private:
    //! File path
    char mPath[128]; // at 0x18
    //! File data size
    s32 mSize; // at 0x98
    //! File data contents
    const u8* mpData; // at 0x9C
};

//! @}

#endif
