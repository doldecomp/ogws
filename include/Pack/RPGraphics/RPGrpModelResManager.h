#ifndef RP_GRAPHICS_MODEL_RES_MANAGER_H
#define RP_GRAPHICS_MODEL_RES_MANAGER_H
#include <Pack/types_pack.h>

#include <egg/math.h>

#include <nw4r/g3d.h>

//! @addtogroup rp_graphics
//! @{

//! Resource file handle
typedef u16 RPGrpHandle;

/**
 * @brief Model resource manager
 */
class RPGrpModelResManager {
    //! Only the model manager can change the current instance
    friend class RPGrpModelManager;

public:
    /**
     * @brief Resource file type
     */
    enum Type {
        Type_None = 0,
        Type_1,

        Type_Unknown = 11,

        Type_ResFile,
        Type_ResMdl,
        Type_ResPltt,
        Type_ResTex,
        Type_ResAnmChr,
        Type_ResAnmVis,
        Type_ResAnmClr,
        Type_ResAnmTexPat,
        Type_ResAnmTexSrt,
        Type_ResAnmShp,
        Type_ResAnmScn,

        Type_Max
    };

private:
    // Forward declarations
    struct Resource;
    template <Type> struct Int2Type;
    template <Type E, typename TInt2Type = Int2Type<E> > struct ResType;

private:
    //! Resource file list
    Resource* mpResList; // at 0x0
    //! Capacity of the resource list
    u16 mResNum; // at 0x4

public:
    /**
     * @brief Gets the currently active manager instance
     */
    static RPGrpModelResManager* GetCurrent() {
        return spCurrent;
    }

    /**
     * @brief Initializes the manager state
     */
    void Configure();

    /**
     * @brief Allocates memory to hold the specified amount of resources
     *
     * @param num Resource list capacity
     */
    void CreateResourceList(u16 num);

    /**
     * @brief Releases the specified resource
     *
     * @param handle Resource handle
     */
    void Terminate(RPGrpHandle handle);

    /**
     * @brief Releases all resources
     */
    void TerminateAll();

    /**
     * @brief Searches the resource list for the specified data
     *
     * @param pBinary Binary resource data
     * @return Resource handle, or -1 if not found
     */
    int SearchData(void* pBinary) const;

    /**
     * @brief Attempts to create a new resource from the specified data
     * @details If the resource already exists, this function returns the
     * existing handle.
     *
     * @param type Resource type
     * @param pBinary Binary resource data
     * @param arg2
     * @return New resource handle
     */
    RPGrpHandle CreateData(Type type, void* pBinary, u32 arg2 = 0);

    /**
     * @brief Gets the raw data of the specified resource subfile
     *
     * @param type Subfile type
     * @param handle File resource handle
     * @param pName Subfile name
     */
    void* GetPtr(Type type, RPGrpHandle handle, const char* pName) const;

    /**
     * @brief Gets the raw data of the specified resource subfile
     *
     * @param type Subfile type
     * @param handle File resource handle
     * @param index Subfile index
     */
    void* GetPtr(Type type, RPGrpHandle handle, int index) const;

    /**
     * @brief Tests whether the specified resource subfile exists
     *
     * @param type Subfile type
     * @param handle File resource handle
     * @param pName Subfile name
     */
    bool HasFile(Type type, RPGrpHandle handle, const char* pName) const;

    /**
     * @brief Gets an animation's transform result at the specified frame
     *
     * @param handle Animation resource handle
     * @param idx Animation node index
     * @param frame Animation frame
     * @param[out] pRotTrans Transformation matrix
     * @param[out] pTrans X/Y/Z translation
     * @param[out] pRotate X/Y/Z rotation (in degrees)
     * @param[out] pScale X/Y/Z scale
     */
    void GetResultTransform(RPGrpHandle handle, u16 idx, f32 frame,
                            EGG::Matrix34f* pRotTrans, EGG::Vector3f* pTrans,
                            EGG::Vector3f* pRotate, EGG::Vector3f* pScale);

    /**
     * @brief Gets an animation's transform result at the specified frame
     *
     * @param handle Animation resource handle
     * @param pName Animation node name
     * @param frame Animation frame
     * @param[out] pRotTrans Transformation matrix
     * @param[out] pTrans X/Y/Z translation
     * @param[out] pRotate X/Y/Z rotation (in degrees)
     * @param[out] pScale X/Y/Z scale
     */
    inline void GetResultTransform(RPGrpHandle handle, const char* pName,
                                   u16 idx, f32 frame,
                                   EGG::Matrix34f* pRotTrans,
                                   EGG::Vector3f* pTrans,
                                   EGG::Vector3f* pRotate,
                                   EGG::Vector3f* pScale);

    /**
     * @brief Gets the type of the resource acquired through the handle
     *
     * @param handle Resource handle
     */
    Type GetType(RPGrpHandle handle) const {
        return mpResList[handle].type;
    }

    /**
     * @brief Gets the specified NW4R resource using the file handle
     * @details This function accesses the resource at index zero.
     *
     * @tparam E Resource type
     * @param handle File resource handle
     */
    template <Type E>                              //
    inline typename ResType<E, Int2Type<E> >::TRes //
    GetData(RPGrpHandle handle) const;

    /**
     * @brief Gets the specified NW4R resource using the file handle
     * @details This function accesses the resource at the specified index.
     *
     * @tparam E Resource type
     * @param handle File resource handle
     * @param idx Resource index
     */
    template <Type E>                              //
    inline typename ResType<E, Int2Type<E> >::TRes //
    GetData(RPGrpHandle handle, int idx) const;

    /**
     * @brief Gets the specified NW4R resource using the file handle
     * @details This function accesses the resource with the specified name.
     *
     * @tparam E Resource type
     * @param handle File resource handle
     * @param pName Resource name
     */
    template <Type E>                              //
    inline typename ResType<E, Int2Type<E> >::TRes //
    GetData(RPGrpHandle handle, const char* pName) const;

    /**
     * @brief Gets the specified NW4R resource using the file handle
     * @details This function accesses the resource at index zero.
     *
     * @tparam E Resource type
     * @param handle File resource handle
     */
    template <Type E> //
    inline bool HasFile(RPGrpHandle handle) const {
        return GetData<E>(handle).IsValid();
    }

    /**
     * @brief Gets the specified NW4R resource using the file handle
     * @details This function accesses the resource at the specified index.
     *
     * @tparam E Resource type
     * @param handle File resource handle
     * @param idx Resource index
     */
    template <Type E> //
    inline bool HasFile(RPGrpHandle handle, int idx) const {
        return GetData<E>(handle, idx).IsValid();
    }

    /**
     * @brief Gets the specified NW4R resource using the file handle
     * @details This function accesses the resource with the specified name.
     *
     * @tparam E Resource type
     * @param handle File resource handle
     * @param pName Resource name
     */
    template <Type E> //
    inline bool HasFile(RPGrpHandle handle, const char* pName) const {
        return GetData<E>(handle, pName).IsValid();
    }

private:
    /**
     * @brief Generic resource type
     */
    struct Resource {
        //! File type
        Type type; // at 0x0
        //! Raw file data
        void* pBinary; // at 0x4

        //! Resource accessors
        union {
            ResType<Type_ResFile>* pResFile;
            ResType<Type_ResMdl>* pResMdl;
            ResType<Type_ResPltt>* pResPltt;
            ResType<Type_ResTex>* pResTex;
            ResType<Type_ResAnmChr>* pResAnmChr;
            ResType<Type_ResAnmVis>* pResAnmVis;
            ResType<Type_ResAnmClr>* pResAnmClr;
            ResType<Type_ResAnmTexPat>* pResAnmTexPat;
            ResType<Type_ResAnmTexSrt>* pResAnmTexSrt;
            ResType<Type_ResAnmShp>* pResAnmShp;
            ResType<Type_ResAnmScn>* pResAnmScn;
            ResType<Type_Unknown>* pResUnknown;
        }; // at 0x8

        u32 unkC;

        /**
         * @brief Clears the data of this resource
         */
        void Reset() {
            pBinary = NULL;
            pResUnknown = NULL;
            type = Type_None;
            unkC = 0;
        }
    };

private:
    /**
     * @brief Constructor
     */
    RPGrpModelResManager();

    /**
     * @brief Destructor
     */
    virtual ~RPGrpModelResManager() {} // at 0x8

    /**
     * @brief Creates a new resource from the specified data
     *
     * @param handle Handle for the new resource
     * @param type Resource type
     * @param pBinary Binary resource data
     * @param arg3
     */
    void InternalCreateData(RPGrpHandle handle, Type type, void* pBinary,
                            u32 arg3 = 0);

    /**
     * @brief Gets an animation's transform result at the specified frame
     *
     * @param chr Animation resource
     * @param idx Animation node index
     * @param frame Animation frame
     * @param[out] pRotTrans Transformation matrix
     * @param[out] pTrans X/Y/Z translation
     * @param[out] pRotate X/Y/Z rotation (in degrees)
     * @param[out] pScale X/Y/Z scale
     */
    static void InternalGetResultTransform(const nw4r::g3d::ResAnmChr chr,
                                           u16 idx, f32 frame,
                                           EGG::Matrix34f* pRotTrans,
                                           EGG::Vector3f* pTrans,
                                           EGG::Vector3f* pRotate,
                                           EGG::Vector3f* pScale);

private:
    //! Allocator used for model-related allocations
    static RPGrpModelResManager* spCurrent;
};

/******************************************************************************
 *
 * ResType specializations
 *
 ******************************************************************************/

template <RPGrpModelResManager::Type E, typename TInt2Type>
struct RPGrpModelResManager::ResType {
    typedef typename TInt2Type::TRes TRes;
    typedef typename TInt2Type::TResData TResData;

    //! Raw resource data (like ResCommon)
    TResData* pResData; // at 0x0

    ResType() : pResData(NULL) {}
    ResType(void* pResData_) : pResData(static_cast<TResData*>(pResData_)) {}

    TRes Get() const {
        return TRes(pResData);
    }
};

template <>
struct RPGrpModelResManager::ResType<RPGrpModelResManager::Type_None> {
    void* pResData; // at 0x0
};

template <>
struct RPGrpModelResManager::ResType<RPGrpModelResManager::Type_Unknown> {
    void* pResData; // at 0x0
};

/******************************************************************************
 *
 * Int2Type specializations
 *
 ******************************************************************************/

#define SUBFILE_NAME_LIST                                                      \
    X(ResMdl)                                                                  \
    X(ResPltt)                                                                 \
    X(ResTex)                                                                  \
    X(ResAnmChr)                                                               \
    X(ResAnmVis)                                                               \
    X(ResAnmClr)                                                               \
    X(ResAnmTexPat)                                                            \
    X(ResAnmTexSrt)                                                            \
    X(ResAnmShp)                                                               \
    X(ResAnmScn)

#define ALL_NAME_LIST                                                          \
    X(ResFile)                                                                 \
    SUBFILE_NAME_LIST

#define X(Y)                                                                   \
    template <>                                                                \
    struct RPGrpModelResManager::Int2Type<RPGrpModelResManager::Type_##Y> {    \
        typedef const nw4r::g3d::Y TRes;                                       \
        typedef nw4r::g3d::Y##Data TResData;                                   \
    };

ALL_NAME_LIST;
#undef X

/******************************************************************************
 *
 * GetData specializations
 *
 ******************************************************************************/

#define X(Y)                                                                   \
    template <>                                                                \
    inline RPGrpModelResManager::ResType<RPGrpModelResManager::Type_##Y>::TRes \
    RPGrpModelResManager::GetData<RPGrpModelResManager::Type_##Y>(             \
        RPGrpHandle handle) const {                                            \
                                                                               \
        return mpResList[handle].pResFile->Get().Get##Y(0);                    \
    }

SUBFILE_NAME_LIST;
#undef X

#define X(Y)                                                                   \
    template <>                                                                \
    inline RPGrpModelResManager::ResType<RPGrpModelResManager::Type_##Y>::TRes \
    RPGrpModelResManager::GetData<RPGrpModelResManager::Type_##Y>(             \
        RPGrpHandle handle, int index) const {                                 \
                                                                               \
        return mpResList[handle].pResFile->Get().Get##Y(index);                \
    }

SUBFILE_NAME_LIST;
#undef X

#define X(Y)                                                                   \
    template <>                                                                \
    inline RPGrpModelResManager::ResType<RPGrpModelResManager::Type_##Y>::TRes \
    RPGrpModelResManager::GetData<RPGrpModelResManager::Type_##Y>(             \
        RPGrpHandle handle, const char* pName) const {                         \
                                                                               \
        return mpResList[handle].pResFile->Get().Get##Y(pName);                \
    }

SUBFILE_NAME_LIST;
#undef X

#undef ALL_NAME_LIST
#undef SUBFILE_NAME_LIST

/******************************************************************************
 *
 * Inline functions
 *
 ******************************************************************************/

/**
 * @brief Gets an animation's transform result at the specified frame
 *
 * @param handle Animation resource handle
 * @param pName Animation node name
 * @param frame Animation frame
 * @param[out] pRotTrans Transformation matrix
 * @param[out] pTrans X/Y/Z translation
 * @param[out] pRotate X/Y/Z rotation (in degrees)
 * @param[out] pScale X/Y/Z scale
 */
inline void RPGrpModelResManager::GetResultTransform(
    RPGrpHandle handle, const char* pName, u16 idx, f32 frame,
    EGG::Matrix34f* pRotTrans, EGG::Vector3f* pTrans, EGG::Vector3f* pRotate,
    EGG::Vector3f* pScale) {

    const nw4r::g3d::ResAnmChr chr =
        spCurrent->GetData<Type_ResAnmChr>(handle, pName);

    return InternalGetResultTransform(chr, idx, frame, pRotTrans, pTrans,
                                      pRotate, pScale);
}

//! @}

#endif
