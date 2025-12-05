#include <Pack/RPGraphics.h>

#include <egg/math.h>

#include <nw4r/g3d.h>

/**
 * @brief Allocator used for model-related allocations
 */
RPGrpModelResManager* RPGrpModelResManager::spCurrent = NULL;

/**
 * @brief Constructor
 */
RPGrpModelResManager::RPGrpModelResManager() {}

/**
 * @brief Initializes the manager state
 */
void RPGrpModelResManager::Configure() {
    mResNum = 0;
    mpResList = NULL;
}

/**
 * @brief Allocates memory to hold the specified amount of resources
 *
 * @param num Resource list capacity
 */
void RPGrpModelResManager::CreateResourceList(u16 num) {
    if (mResNum > 0) {
        return;
    }

    if (num <= 0) {
        return;
    }

    mpResList = new Resource[num];
    mResNum = num;

    for (int i = 0; i < num; i++) {
        RPGrpHandle handle = static_cast<RPGrpHandle>(i);
        mpResList[handle].Reset();
    }
}

/**
 * @brief Releases the specified resource
 *
 * @param handle Resource handle
 */
void RPGrpModelResManager::Terminate(RPGrpHandle handle) {
    switch (mpResList[handle].type) {
    case Type_ResFile: {
        nw4r::g3d::ResFile file = mpResList[handle].pResFile->Get();

        file.Release();
        file.Terminate();
        break;
    }

    default: {
        break;
    }
    }

    mpResList[handle].Reset();
}

/**
 * @brief Releases all resources
 */
void RPGrpModelResManager::TerminateAll() {
    for (RPGrpHandle handle = 0; handle < mResNum; handle++) {
        Terminate(handle);
    }
}

/**
 * @brief Searches the resource list for the specified data
 *
 * @param pBinary Binary resource data
 * @return Resource handle, or -1 if not found
 */
int RPGrpModelResManager::SearchData(void* pBinary) const {
    for (int i = 0; i < mResNum; i++) {
        if (mpResList[i].pBinary == pBinary) {
            return i;
        }
    }

    return -1;
}

/**
 * @brief Creates a new resource from the specified data
 *
 * @param type Resource type
 * @param pBinary Binary resource data
 * @param arg2
 * @return New resource handle
 */
RPGrpHandle RPGrpModelResManager::CreateData(Type type, void* pBinary,
                                             u32 arg2) {
    for (int i = 0; i < mResNum; i++) {
        if (mpResList[i].pBinary == pBinary) {
            return static_cast<RPGrpHandle>(i);
        }
    }

    RPGrpHandle handle = static_cast<RPGrpHandle>(mResNum);
    while (handle > 0) {
        if (mpResList[--handle].pBinary == NULL) {
            break;
        }
    }

    InternalCreateData(handle, type, pBinary, arg2);
    return handle;
}

/**
 * @brief Gets the raw data of the specified resource subfile
 *
 * @param type Subfile type
 * @param handle File resource handle
 * @param pName Subfile name
 */
void* RPGrpModelResManager::GetPtr(Type type, RPGrpHandle handle,
                                   const char* pName) const {
    switch (type) {
    case Type_ResMdl: {
        return mpResList[handle].pResFile->Get().GetResMdl(pName).ptr();
    }

    case Type_ResPltt: {
        return mpResList[handle].pResFile->Get().GetResPltt(pName).ptr();
    }

    case Type_ResTex: {
        return mpResList[handle].pResFile->Get().GetResTex(pName).ptr();
    }

    case Type_ResAnmChr: {
        return mpResList[handle].pResFile->Get().GetResAnmChr(pName).ptr();
    }

    case Type_ResAnmVis: {
        return mpResList[handle].pResFile->Get().GetResAnmVis(pName).ptr();
    }

    case Type_ResAnmClr: {
        return mpResList[handle].pResFile->Get().GetResAnmClr(pName).ptr();
    }

    case Type_ResAnmTexPat: {
        return mpResList[handle].pResFile->Get().GetResAnmTexPat(pName).ptr();
    }

    case Type_ResAnmTexSrt: {
        return mpResList[handle].pResFile->Get().GetResAnmTexSrt(pName).ptr();
    }

    case Type_ResAnmShp: {
        return mpResList[handle].pResFile->Get().GetResAnmShp(pName).ptr();
    }

    case Type_ResAnmScn: {
        return mpResList[handle].pResFile->Get().GetResAnmShp(pName).ptr();
    }

    default: {
        return NULL;
    }
    }
}

/**
 * @brief Gets the raw data of the specified resource subfile
 *
 * @param type Subfile type
 * @param handle File resource handle
 * @param index Subfile index
 */
void* RPGrpModelResManager::GetPtr(Type type, RPGrpHandle handle,
                                   int index) const {
    switch (type) {
    case Type_ResMdl: {
        return mpResList[handle].pResFile->Get().GetResMdl(index).ptr();
    }

    case Type_ResPltt: {
        return mpResList[handle].pResFile->Get().GetResPltt(index).ptr();
    }

    case Type_ResTex: {
        return mpResList[handle].pResFile->Get().GetResTex(index).ptr();
    }

    case Type_ResAnmChr: {
        return mpResList[handle].pResFile->Get().GetResAnmChr(index).ptr();
    }

    case Type_ResAnmVis: {
        return mpResList[handle].pResFile->Get().GetResAnmVis(index).ptr();
    }

    case Type_ResAnmClr: {
        return mpResList[handle].pResFile->Get().GetResAnmClr(index).ptr();
    }

    case Type_ResAnmTexPat: {
        return mpResList[handle].pResFile->Get().GetResAnmTexPat(index).ptr();
    }

    case Type_ResAnmTexSrt: {
        return mpResList[handle].pResFile->Get().GetResAnmTexSrt(index).ptr();
    }

    case Type_ResAnmShp: {
        return mpResList[handle].pResFile->Get().GetResAnmShp(index).ptr();
    }

    case Type_ResAnmScn: {
        return mpResList[handle].pResFile->Get().GetResAnmShp(index).ptr();
    }

    default: {
        return NULL;
    }
    }
}

void RPGrpModelResManager::InternalCreateData(RPGrpHandle handle, Type type,
                                              void* pBinary, u32 arg3) {
    Resource& rResource = mpResList[handle];
    rResource.pBinary = pBinary;
    rResource.type = type;
    rResource.unkC = arg3;

    switch (type) {
    case Type_ResFile: {
        nw4r::g3d::ResFile* pResFile =
            new nw4r::g3d::ResFile(rResource.pBinary);

        pResFile->CheckRevision();
        pResFile->Init();
        pResFile->Bind(*pResFile);

        for (u32 i = 0; i < pResFile->GetResAnmScnNumEntries(); i++) {
            nw4r::g3d::ResAnmScn scn = pResFile->GetResAnmScn(i);
            scn.Bind(scn);
        }

        // TODO(kiwi) Not sure how this wrapper works.
        // Could ResType be ResCommon? But then you access private members...
        rResource.pResFile = reinterpret_cast<ResType<Type_ResFile>*>(pResFile);
        break;
    }

    case Type_ResMdl: {
        rResource.pResMdl = new ResType<Type_ResMdl>();

        rResource.pResMdl->pResData =
            static_cast<nw4r::g3d::ResMdlData*>(pBinary);
        break;
    }

    case Type_ResPltt: {
        rResource.pResPltt = new ResType<Type_ResPltt>();

        rResource.pResPltt->pResData =
            static_cast<nw4r::g3d::ResPlttData*>(pBinary);
        break;
    }

    case Type_ResTex: {
        rResource.pResTex = new ResType<Type_ResTex>();

        rResource.pResTex->pResData =
            static_cast<nw4r::g3d::ResTexData*>(pBinary);
        break;
    }

    case Type_ResAnmChr: {
        rResource.pResAnmChr = new ResType<Type_ResAnmChr>();

        rResource.pResAnmChr->pResData =
            static_cast<nw4r::g3d::ResAnmChrData*>(pBinary);
        break;
    }

    case Type_ResAnmVis: {
        rResource.pResAnmVis = new ResType<Type_ResAnmVis>();

        rResource.pResAnmVis->pResData =
            static_cast<nw4r::g3d::ResAnmVisData*>(pBinary);
        break;
    }

    case Type_ResAnmClr: {
        rResource.pResAnmClr = new ResType<Type_ResAnmClr>();

        rResource.pResAnmClr->pResData =
            static_cast<nw4r::g3d::ResAnmClrData*>(pBinary);
        break;
    }

    case Type_ResAnmTexPat: {
        rResource.pResAnmTexPat = new ResType<Type_ResAnmTexPat>();

        rResource.pResAnmTexPat->pResData =
            static_cast<nw4r::g3d::ResAnmTexPatData*>(pBinary);
        break;
    }

    case Type_ResAnmTexSrt: {
        rResource.pResAnmTexSrt = new ResType<Type_ResAnmTexSrt>();

        rResource.pResAnmTexSrt->pResData =
            static_cast<nw4r::g3d::ResAnmTexSrtData*>(pBinary);
        break;
    }

    case Type_ResAnmShp: {
        rResource.pResAnmShp = new ResType<Type_ResAnmShp>();

        rResource.pResAnmShp->pResData =
            static_cast<nw4r::g3d::ResAnmShpData*>(pBinary);
        break;
    }

    case Type_ResAnmScn: {
        rResource.pResAnmScn = new ResType<Type_ResAnmScn>();

        rResource.pResAnmScn->pResData =
            static_cast<nw4r::g3d::ResAnmScnData*>(pBinary);
        break;
    }

    case Type_Unknown: {
        rResource.pResUnknown = new ResType<Type_Unknown>();
        rResource.pResUnknown->pResData = pBinary;
        break;
    }

    default: {
        break;
    }
    }
}

/**
 * @brief Tests whether the specified resource subfile exists
 *
 * @param type Subfile type
 * @param handle File resource handle
 * @param pName Subfile name
 */
bool RPGrpModelResManager::HasFile(Type type, RPGrpHandle handle,
                                   const char* pName) const {
    switch (type) {
    case Type_ResMdl: {
        return mpResList[handle].pResFile->Get().GetResMdl(pName).IsValid();
    }

    case Type_ResPltt: {
        return mpResList[handle].pResFile->Get().GetResPltt(pName).IsValid();
    }

    case Type_ResTex: {
        return mpResList[handle].pResFile->Get().GetResTex(pName).IsValid();
    }

    case Type_ResAnmChr: {
        return mpResList[handle].pResFile->Get().GetResAnmChr(pName).IsValid();
    }

    case Type_ResAnmVis: {
        return mpResList[handle].pResFile->Get().GetResAnmVis(pName).IsValid();
    }

    case Type_ResAnmClr: {
        return mpResList[handle].pResFile->Get().GetResAnmClr(pName).IsValid();
    }

    case Type_ResAnmTexPat: {
        return mpResList[handle]
            .pResFile->Get()
            .GetResAnmTexPat(pName)
            .IsValid();
    }

    case Type_ResAnmTexSrt: {
        return mpResList[handle]
            .pResFile->Get()
            .GetResAnmTexSrt(pName)
            .IsValid();
    }

    case Type_ResAnmShp: {
        return mpResList[handle].pResFile->Get().GetResAnmShp(pName).IsValid();
    }

    case Type_ResAnmScn: {
        return mpResList[handle].pResFile->Get().GetResAnmShp(pName).IsValid();
    }

    default: {
        return false;
    }
    }
}

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
void RPGrpModelResManager::GetResultTransform(
    RPGrpHandle handle, u16 idx, f32 frame, EGG::Matrix34f* pRotTrans,
    EGG::Vector3f* pTrans, EGG::Vector3f* pRotate, EGG::Vector3f* pScale) {

    switch (mpResList[handle].type) {
    case Type_ResAnmChr: {
        InternalGetResultTransform(mpResList[handle].pResAnmChr->Get(), idx,
                                   frame, pRotTrans, pTrans, pRotate, pScale);
        break;
    }

    default: {
        break;
    }
    }
}

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
void RPGrpModelResManager::InternalGetResultTransform(
    const nw4r::g3d::ResAnmChr chr, u16 idx, f32 frame,
    EGG::Matrix34f* pRotTrans, EGG::Vector3f* pTrans, EGG::Vector3f* pRotate,
    EGG::Vector3f* pScale) {

    nw4r::g3d::ChrAnmResult result;
    chr.GetAnmResult(&result, idx, frame);

    if (pRotTrans != NULL) {
        result.GetRotTrans(pRotTrans);
    }

    if (pScale != NULL) {
        result.GetScale(pScale);
    }

    if (pTrans != NULL) {
        result.GetTranslate(pTrans);
    }

    if (pRotate != NULL) {
        result.GetRotateDeg(pRotate);
    }
}
