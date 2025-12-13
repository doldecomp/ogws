#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <cstring>

/**
 * @brief Constructor
 *
 * @param pPath File path (absolute)
 * @param size File data size
 * @param pData File data pointer
 */
RPSysFile::RPSysFile(const char* pPath, s32 size, const void* pData)
    : mSize(size) {

    // @bug Can easily overflow the fixed-size buffer
#if defined(BUG_FIX)
    std::strncpy(mPath, pPath, ARRAY_SIZE(mPath));
#else
    std::strcpy(mPath, pPath);
#endif

    mpData = static_cast<const u8*>(pData);
}

/**
 * @brief Destructor
 * @details The file is automatically removed from the resource cache.
 */
RPSysFile::~RPSysFile() {
    RP_GET_INSTANCE(RPSysResourceManager)->RemoveFromFileList(this);
}
