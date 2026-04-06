#ifndef RP_SYSTEM_RESOURCE_MANAGER_H
#define RP_SYSTEM_RESOURCE_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>
#include <Pack/RPSports.h>
#include <Pack/RPSystem/RPSysSceneCreator.h>

#include <egg/core.h>

#include <nw4r/ut.h>

//! @addtogroup rp_system
//! @{

// Forward declarations
class RPSysFile;

/**
 * @brief Resource cache manager
 */
class RPSysResourceManager {
    RP_SINGLETON_DECL(RPSysResourceManager);

public:
    /**
     * @brief Resource list type
     */
    enum EList {
        EList_FileCache, //!< Cached, compressed files
        EList_FileList,  //!< Decompressed files ready for access

        EList_Max
    };

public:
    /**
     * @brief Gets the path to the common asset folder for the specified scene
     *
     * @param[out] pBuffer Path output buffer
     * @param maxlen Output buffer size
     * @param id Scene ID (defaults to the current scene)
     */
    void GetGameCommonPath(char* pBuffer, u32 maxlen, s32 id = -1);

    /**
     * @brief Loads the common asset archive for the specified scene
     *
     * @param id Scene ID (defaults to the current scene)
     * @param pHeap Heap to use for allocations (defaults to the current heap)
     */
    static EGG::Archive* LoadGameCommonArchive(s32 id = -1,
                                               EGG::Heap* pHeap = NULL);

    /**
     * @brief Gets the path to the local asset folder for the specified scene
     *
     * @param[out] pBuffer Path output buffer
     * @param maxlen Output buffer size
     * @param id Scene ID (defaults to the current scene)
     */
    void GetGameLocalPath(char* pBuffer, u32 maxlen, s32 id = -1);

    /**
     * @brief Loads the local asset archive for the specified scene
     *
     * @param id Scene ID (defaults to the current scene)
     * @param pHeap Heap to use for allocations (defaults to the current heap)
     */
    static EGG::Archive* LoadGameLocalArchive(s32 id = -1,
                                              EGG::Heap* pHeap = NULL);

    /**
     * @brief Gets the path to the stage asset folder for the specified scene
     *
     * @param[out] pBuffer Path output buffer
     * @param maxlen Output buffer size
     * @param id Scene ID (defaults to the current scene)
     */
    void GetGameStagePath(char* pBuffer, u32 maxlen, s32 id = -1);

    /**
     * @brief Loads the specified archive from the current scene's stage assets
     *
     * @param pName Archive name
     */
    static EGG::Archive* LoadGameStageArchive(const char* pName);

    /**
     * @brief Gets the specified file from the provided archive
     *
     * @param pArchive Archive containing the file
     * @param pName File name
     * @param[out] pSize Size of the specified file
     */
    static void* GetFileFromArchive(EGG::Archive* pArchive, const char* pName,
                                    u32* pSize = NULL);

    /**
     * @brief Gets the specified file from the message archive
     *
     * @param pName Message file name
     */
    static void* GetMessageResource(const char* pName);

    /**
     * @brief Tests whether a file exists at the specified path
     *
     * @param pPath Path to examine
     */
    bool IsExist(const char* pPath);

    /**
     * @brief Removes a file from the list of decompressed files
     * @note RPSysFile automatically removes itself when it is destroyed.
     *
     * @param pFile File to remove
     */
    void RemoveFromFileList(RPSysFile* pFile);

    /**
     * @brief Loads all archives and other assets with static lifetime
     */
    void LoadStaticArchives();

    /**
     * @brief Loads the specified file and adds it to the resource cache
     * @details If the file has already been cached, this function does nothing.
     *
     * @param pPath File path
     * @param list List that the file should be moved to
     * @param pHeap Heap to use for allocations
     */
    void LoadCachedFile(const char* pPath, EList list, EGG::Heap* pHeap);

    /**
     * @brief Loads all archives designated for cached access
     */
    void LoadCacheArchives();

    /**
     * @brief Loads the archive containing all kokeshi assets
     */
    void LoadKokeshiArchive();

    /**
     * @brief Gets the path to the common sound folder
     *
     * @param[out] pBuffer Path output buffer
     * @param maxlen Output buffer size
     */
    void GetStaticSoundCommonPath(char* pBuffer, u32 maxlen);

    /**
     * @brief Gets the path to the local sound folder
     *
     * @param[out] pBuffer Path output buffer
     * @param maxlen Output buffer size
     */
    void GetStaticSoundLocalPath(char* pBuffer, u32 maxlen);

    /**
     * @brief Gets the path to the common sound folder for the specified scene
     *
     * @param[out] pBuffer Path output buffer
     * @param maxlen Output buffer size
     * @param id Scene ID (defaults to the current scene)
     */
    void GetGameSoundCommonPath(char* pBuffer, u32 maxlen, s32 id = -1);

    /**
     * @brief Gets the path to the local sound folder for the specified scene
     *
     * @param[out] pBuffer Path output buffer
     * @param maxlen Output buffer size
     * @param id Scene ID (defaults to the current scene)
     */
    void GetGameSoundLocalPath(char* pBuffer, u32 maxlen, s32 id = -1);

    /**
     * @brief Loads the local archive in the specified static asset directory
     *
     * @param pStaticDir Static asset directory
     */
    EGG::Archive* LoadStaticLocalArchive(const char* pStaticDir)
        DECOMP_DONT_INLINE;

    /**
     * @brief Loads the common archive in the specified static asset directory
     *
     * @param pStaticDir Static asset directory
     */
    EGG::Archive* LoadStaticCommonArchive(const char* pPath);

    /**
     * @brief Loads the archive containing all message data
     */
    void LoadMessageArchive();

    /**
     * @brief Loads the archive containing all font data
     */
    void LoadFontArchive();

    /**
     * @brief Gets the archive containing all kokeshi assets
     */
    EGG::Archive* GetKokeshiArchive() const {
        return mpKokeshiArchive;
    }

    /**
     * @brief Gets the archive containing all message data
     */
    EGG::Archive* GetMessageArchive() const {
        return mpMessageArchive;
    }

    /**
     * @brief Gets the archive containing all font data
     */
    EGG::Archive* GetFontArchive() const {
        return mpFontArchive;
    }

    /**
     * @brief Gets the extra handle for opening files outside the DVD
     */
    void* GetMultiHandle() {
        return &mpMultiHandle;
    }

private:
    /**
     * @brief Loads the specified file from the DVD, decompressing its contents
     * if applicable
     *
     * @param pPath File path
     * @param pHeap Heap to use for allocations
     * @return Raw file contents
     */
    u8* LoadCompressed(const char* pPath, EGG::Heap* pHeap);

    /**
     * @brief Loads the specified file from the DVD
     *
     * @param pPath Path to the file
     * @param pHeap Heap to use for allocations
     * @param allocDir Direction of heap allocations
     * @param[out] pSize Size of the specified file
     */
    u8* LoadFromDVD(const char* pPath, EGG::Heap* pHeap,
                    EGG::DvdRipper::EAllocDirection allocDir,
                    s32* pSize = NULL);

    /**
     * @brief Searches the specified resource list for the provided filepath
     *
     * @param pPath File path
     * @param list Resource list
     */
    RPSysFile* FindFile(const char* pPath, EList list) const;

    /**
     * @brief Creates a new entry in the specified resource list
     *
     * @param pPath File path
     * @param list Resource list
     * @param size File size
     * @param pData File data
     * @param pHeap Heap to use for allocations
     */
    void MakeFile(const char* pPath, EList list, s32 size, const void* pData,
                  EGG::Heap* pHeap);

    /**
     * @brief Decompresses the contents of the specified data
     * @details If the data is not compressed, this function returns the
     * original file contents
     *
     * @param pData File data
     * @param size Data size
     * @param[out] pExpandSize The data size after decompression
     * @param pHeap Heap to use for allocations
     * @return Decompressed data
     */
    u8* ExpandCompressed(u8* pData, s32 size, s32* pExpandSize,
                         EGG::Heap* pHeap) const;

private:
    //! List of scenes whose resources should be cached
    static const RPSysSceneCreator::ESceneID CACHED_SCENES[];
    //! Static directory names for each pack
    static const char* STATIC_DIR_NAMES[RPSysSceneCreator::EPackID_Max];
    //! Absolute path to the kokeshi asset archive
    static const char* KOKESHI_ARCHIVE_PATH;

    //! Resource lists
    nw4r::ut::List mResourceLists[EList_Max]; // at 0x4

    //! Work buffer for building filepaths
    char* mpPathWork; // at 0x1C

    //! Archive containing all kokeshi assets
    EGG::Archive* mpKokeshiArchive; // at 0x20
    //! Archive containing all message data
    EGG::Archive* mpMessageArchive; // at 0x24
    //! Archive containing all font data
    EGG::Archive* mpFontArchive; // at 0x28

    //! Archive containing static common assets for this pack
    EGG::Archive* mpStaticCommonArchive; // at 0x2C
    //! Archive containing static locale assets for this pack
    EGG::Archive* mpStaticLocalArchive; // at 0x30
    //! Archive containing static layout assets for this pack
    EGG::Archive* mpStaticLayoutArchive; // at 0x34

#if defined(PACK_SPORTS)
    //! Sports Pack Mii manager
    RPSportsAppMiiManager* mpAppMiiManager; // at 0x38
#endif

    //! Extra handle for opening files outside the DVD
    void* mpMultiHandle; // at 0x3C
};

//! @}

#endif
