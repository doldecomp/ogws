#ifndef RP_SYSTEM_RESOURCE_MANAGER_H
#define RP_SYSTEM_RESOURCE_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

#include <egg/core.h>

#include <nw4r/ut.h>

//! @addtogroup rp_system
//! @{

// Forward declarations
class RPSysFile;
class RPSportsAppMiiManager;
class RPPartyAppMiiManager;

/**
 * @brief Resource cache manager
 */
class RPSysResourceManager {
    RP_SINGLETON_DECL(RPSysResourceManager);

public:
    /**
     * @brief Loads a file from the DVD
     * @remark If no heap is specified, the current heap is used instead.
     * @see EGG::DvdRipper::EAllocDirection
     *
     * @param pPath Path to the file
     * @param pHeap Heap from which to allocate the buffer
     * @param allocDir Direction of heap allocation
     * @param[out] pSize Where the file's size will be written
     */
    void* LoadFromDVD(const char* pPath, EGG::Heap* pHeap, s32 allocDir,
                      s32* pSize);

    /**
     * @brief Loads and decompresses a file from the DVD
     * @remark If the file already exists in the cache, this function returns
     * the cached instance.
     * @remark If no heap is specified, the current heap is used instead.
     *
     * @param pPath Path to the file
     * @param pHeap Heap from which to allocate the buffer
     */
    void* LoadCompressed(const char* pPath, EGG::Heap* pHeap);

    /**
     * @brief Loads the local archive in the specified directory
     * @note The "local" archive is always named `local.carc`.
     *
     * @param pPath Path to the directory
     */
    EGG::Archive* LoadLocalArchive(const char* pPath);

    /**
     * @brief Loads the common archive for the specified scene
     * @note The "common" archive is always named `common.carc`.
     *
     * @param id Scene ID
     * @param pHeap Heap from which to allocate the buffer
     */
    static EGG::Archive* LoadGameCommonArchive(s32 id, EGG::Heap* pHeap);
    /**
     * @brief Loads the local archive for the specified scene
     * @note The "local" archive is always named `local.carc`.
     *
     * @param id Scene ID
     * @param pHeap Heap from which to allocate the buffer
     */
    static EGG::Archive* LoadGameLocalArchive(s32 id, EGG::Heap* pHeap);
    /**
     * @brief Loads the specified stage archive from the current scene's assets
     *
     * @param pName Name of the file in the scene's "Stage" directory
     */
    static EGG::Archive* LoadGameStageArchive(const char* pName);

    /**
     * @brief Gets the specified file from the specified archive
     *
     * @param pArc Archive which contains the file
     * @param pName Name of the file
     * @param[out] pSize Where the file's size will be written
     */
    static void* GetFileFromArchive(EGG::Archive* pArc, const char* pName,
                                    u32* pSize = NULL);

    /**
     * @brief Gets a message file by name from the message archive
     *
     * @param pName Name of the message file
     */
    static void* GetMessageResource(const char* pName);

    /**
     * @brief Tests whether the specified file exists in the game filesystem
     *
     * @param pPath Path to the file
     */
    bool IsExist(const char* pPath);

    /**
     * @brief Removes a file from the user cache
     * @note This is automatically called through the RPSysFile destructor.
     *
     * @param pFile File to remove
     */
    void RemoveFromFileList(RPSysFile* pFile);

    /**
     * @brief Loads the Kokeshi asset archive
     */
    void LoadKokeshiArchive();
    /**
     * @brief Loads the archives from the current pack's static directory
     * @remarks This also includes the message and font archives.
     */
    void LoadStaticArchives();
    /**
     * @brief Loads and caches the common archive of every scene
     */
    void LoadCacheArchives();

    /**
     * @brief Gets the common sound path of the current pack
     * @bug This function ignores the @p bufSize parameter and instead uses
     * unsafe versions of string functions.
     *
     * @param[out] pBuffer Buffer containing resulting path
     * @param bufSize Size of the buffer pointed to by @p pBuffer
     */
    void GetStaticSoundCommonPath(char* pBuffer, u32 bufSize);
    /**
     * @brief Gets the local sound path of the current pack
     * @bug This function ignores the @p bufSize parameter and instead uses
     * unsafe versions of string functions.
     *
     * @param[out] pBuffer Buffer containing resulting path
     * @param bufSize Size of the buffer pointed to by @p pBuffer
     */
    void GetStaticSoundLocalPath(char* pBuffer, u32 bufSize);

    /**
     * @brief Gets the common sound path of the specified scene
     * @bug This function ignores the @p bufSize parameter and instead uses
     * unsafe versions of string functions.
     *
     * @param[out] pBuffer Buffer containing resulting path
     * @param bufSize Size of the buffer pointed to by @p pBuffer
     * @param id Scene ID
     */
    void GetGameSoundCommonPath(char* pBuffer, u32 bufSize, s32 id);
    /**
     * @brief Gets the local sound path of the specified scene
     * @bug This function ignores the @p bufSize parameter and instead uses
     * unsafe versions of string functions.
     *
     * @param[out] pBuffer Buffer containing resulting path
     * @param bufSize Size of the buffer pointed to by @p pBuffer
     * @param id Scene ID
     */
    void GetGameSoundLocalPath(char* pBuffer, u32 bufSize, s32 id);

    EGG::Archive* GetKokeshiArchive() const {
        return mpKokeshiArchive;
    }

private:
    //! Resource cache for compressed files
    nw4r::ut::List mFileCache; // at 0x4
    //! Resource cache for decompressed files
    nw4r::ut::List mDecompFileCache; // at 0x10

    //! Work buffer for building filepaths
    char* mpPathWork; // at 0x1C

    //! Archive containing Kokeshi assets
    EGG::Archive* mpKokeshiArchive; // at 0x20
    //! Archive containing all message files
    EGG::Archive* mpMessageArchive; // at 0x24
    //! Archive containing all fonts
    EGG::Archive* mpFontArchive; // at 0x28

    //! Static common assets for this pack
    EGG::Archive* mpStaticCommonArchive; // at 0x2C
    //! Static locale assets for this pack
    EGG::Archive* mpStaticLocalArchive; // at 0x30
    //! Static layout assets for this pack
    EGG::Archive* mpStaticLayoutArchive; // at 0x34

#if defined(PACK_SPORTS)
    //! Sports Pack Mii manager
    RPSportsAppMiiManager* mpAppMiiManager; // at 0x38
#elif defined(PACK_PLAY)
    //! Party Pack Mii manager
    RPPartyAppMiiManager* mpAppMiiManager; // at 0x38
#endif

    //! @brief Handle for opening NAND sound archives
    //! @remark This seems to be for NAND titles using the Pack Project engine.
    void* mpMultiHandle; // at 0x3C
};

//! @}

#endif
