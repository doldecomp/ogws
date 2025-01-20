#include <nw4r/ef.h>

#include <cstring>

namespace nw4r {
namespace ef {

Resource Resource::mResource;

Resource* Resource::GetInstance() {
    return &mResource;
}

Resource::Resource() {
    Initialize();
}

void Resource::Initialize() {
    ut::List_Init(&mBREFFList, offsetof(EffectProject, projectlink));
    ut::List_Init(&mBREFTList, offsetof(TextureProject, projectlink));
    mNumEmitter = 0;
    mNumTexture = 0;
}

/******************************************************************************
 *
 * Binary resource implementation
 *
 ******************************************************************************/
struct FileHeader {
    char signature[4]; // at 0x0
    u8 byteorder[2];   // at 0x4
    u16 version;       // at 0x6
    u32 filesize;      // at 0x8
    u16 headersize;    // at 0xC
    u16 blocknum;      // at 0xE
};

struct BlockHeader {
    char type[4];   // at 0x0
    u32 headersize; // at 0x4
};

struct NameTable {
    u32 tablesize;   // at 0x0
    u16 numEntry;    // at 0x5
    u16 PADDING_0x4; // at 0x6
};

/* static */ void breffRelocate(EffectProject* pEffProject) {
    u8* pPtr = reinterpret_cast<u8*>(pEffProject);
    pPtr += pEffProject->headersize;

    u8* pData = pPtr;
    NameTable* pNameTable = reinterpret_cast<NameTable*>(pPtr);

    pData += sizeof(NameTable);

    for (int i = 0; i < pNameTable->numEntry; i++) {
        int len = (pData[0] << 8) + pData[1];
        pData += sizeof(u16);

        char* pName = reinterpret_cast<char*>(pData);
        pData += len;

        u32 offset =
            (pData[0] << 24) + (pData[1] << 16) + (pData[2] << 8) + pData[3];
        pData += sizeof(u32);

        u32 size =
            (pData[0] << 24) + (pData[1] << 16) + (pData[2] << 8) + pData[3];
        pData += sizeof(u32);

        EmitterResource* pResource = reinterpret_cast<EmitterResource*>(
            reinterpret_cast<u8*>(pNameTable) + offset);

        // I think they really did this, the member is private...
        *reinterpret_cast<char**>(pResource) = pName;

        pResource->LocateTracks();
    }
}

static u16 breffNumEmitter(EffectProject* pEffProject) {
    u8* pPtr = reinterpret_cast<u8*>(pEffProject);
    pPtr += pEffProject->headersize;

    NameTable* pNameTable = reinterpret_cast<NameTable*>(pPtr);
    return pNameTable->numEntry;
}

static u16 breftNumTexture(TextureProject* pTexProject) {
    u8* pPtr = reinterpret_cast<u8*>(pTexProject);
    pPtr += pTexProject->headersize;

    NameTable* pNameTable = reinterpret_cast<NameTable*>(pPtr);
    return pNameTable->numEntry;
}

static EmitterResource* breffSearchName(EffectProject* pEffProject,
                                        const char* pEffName) {

    u8* pPtr = reinterpret_cast<u8*>(pEffProject);
    pPtr += pEffProject->headersize;

    u8* pData = pPtr;
    NameTable* pNameTable = reinterpret_cast<NameTable*>(pPtr);

    pData += sizeof(NameTable);

    for (int i = 0; i < pNameTable->numEntry; i++) {
        int len = (pData[0] << 8) + pData[1];
        pData += sizeof(u16);

        char* pName = reinterpret_cast<char*>(pData);
        pData += len;

        u32 offset =
            (pData[0] << 24) + (pData[1] << 16) + (pData[2] << 8) + pData[3];
        pData += sizeof(u32);

        // Skip size
        pData += sizeof(u32);

        if (std::strcmp(pEffName, pName) == 0) {
            return reinterpret_cast<EmitterResource*>(
                reinterpret_cast<u8*>(pNameTable) + offset);
        }
    }

    return NULL;
}

static EmitterResource* breffIndexOf(EffectProject* pEffProject, u16 idx) {
    u8* pPtr = reinterpret_cast<u8*>(pEffProject);
    pPtr += pEffProject->headersize;

    u8* pData = pPtr;
    NameTable* pNameTable = reinterpret_cast<NameTable*>(pPtr);

    if (idx >= pNameTable->numEntry) {
        return NULL;
    }

    pData += sizeof(NameTable);

    for (int i = 0; i < pNameTable->numEntry; i++) {
        int len = (pData[0] << 8) + pData[1];
        pData += sizeof(u16);

        char* pEffName = reinterpret_cast<char*>(pData);
        pData += len;

        u32 offset =
            (pData[0] << 24) + (pData[1] << 16) + (pData[2] << 8) + pData[3];
        pData += sizeof(u32);

        // Skip size
        pData += sizeof(u32);

        if (i == idx) {
            return reinterpret_cast<EmitterResource*>(
                reinterpret_cast<u8*>(pNameTable) + offset);
        }
    }

    return NULL;
}

static void breftRelocate(TextureProject* pTexProject) {
    u8* pPtr = reinterpret_cast<u8*>(pTexProject);
    pPtr += pTexProject->headersize;

    u8* pData = pPtr;
    NameTable* pNameTable = reinterpret_cast<NameTable*>(pPtr);

    pData += sizeof(NameTable);

    for (int i = 0; i < pNameTable->numEntry; i++) {
        int len = (pData[0] << 8) + pData[1];
        pData += sizeof(u16);

        char* pName = reinterpret_cast<char*>(pData);
        pData += len;

        u32 offset =
            (pData[0] << 24) + (pData[1] << 16) + (pData[2] << 8) + pData[3];
        pData += sizeof(u32);

        u32 size =
            (pData[0] << 24) + (pData[1] << 16) + (pData[2] << 8) + pData[3];
        pData += sizeof(u32);

        TextureData* pTexData = reinterpret_cast<TextureData*>(
            reinterpret_cast<u8*>(pNameTable) + offset);

        pTexData->name = pName;
        pTexData->texture =
            reinterpret_cast<u8*>(pTexData) + sizeof(TextureData);
        pTexData->tlut = reinterpret_cast<u8*>(pTexData) + sizeof(TextureData) +
                         pTexData->dataSize;
    }
}

static TextureData* breftSearchName(TextureProject* pTexProject,
                                    const char* pTexName) {

    u8* pPtr = reinterpret_cast<u8*>(pTexProject);
    pPtr += pTexProject->headersize;

    u8* pData = pPtr;
    NameTable* pNameTable = reinterpret_cast<NameTable*>(pPtr);

    pData += sizeof(NameTable);

    for (int i = 0; i < pNameTable->numEntry; i++) {
        int len = (pData[0] << 8) + pData[1];
        pData += sizeof(u16);

        char* pName = reinterpret_cast<char*>(pData);
        pData += len;

        u32 offset =
            (pData[0] << 24) + (pData[1] << 16) + (pData[2] << 8) + pData[3];
        pData += sizeof(u32);

        // Skip size
        pData += sizeof(u32);

        if (std::strcmp(pTexName, pName) == 0) {
            return reinterpret_cast<TextureData*>(
                reinterpret_cast<u8*>(pNameTable) + offset);
        }
    }

    return NULL;
}

/******************************************************************************
 *
 * Resource interface
 *
 ******************************************************************************/
EffectProject* Resource::Add(u8* pData) {
    u8* pPtr = pData;

    FileHeader* pFileHeader = reinterpret_cast<FileHeader*>(pPtr);
    pPtr += pFileHeader->headersize;

    BlockHeader* pBlockHeader = reinterpret_cast<BlockHeader*>(pPtr);
    pPtr += sizeof(BlockHeader);

    EffectProject* pEffProject = reinterpret_cast<EffectProject*>(pPtr);

    memset(&pEffProject->projectlink, 0, sizeof(ut::Link));
    ut::List_Append(&mBREFFList, pEffProject);

    mNumEmitter += breffNumEmitter(pEffProject);
    breffRelocate(pEffProject);

    return pEffProject;
}

ResEmitter Resource::FindEmitter(const char* pName,
                                 EffectProject* pEffProject) const {

    EmitterResource* const pResource = _FindEmitter(pName, pEffProject);
    return ResEmitter(pResource);
}

EmitterResource* Resource::_FindEmitter(const char* pName,
                                        EffectProject* pEffProject) const {

    EmitterResource* pResource;

    if (pEffProject != NULL) {
        pResource = breffSearchName(pEffProject, pName);
        if (pResource != NULL) {
            return pResource;
        }
    }

    pEffProject = static_cast<EffectProject*>(ut::List_GetLast(&mBREFFList));

    while (pEffProject != NULL) {
        pResource = breffSearchName(pEffProject, pName);
        if (pResource != NULL) {
            return pResource;
        }

        pEffProject = static_cast<EffectProject*>(
            ut::List_GetPrev(&mBREFFList, pEffProject));
    }

    return NULL;
}

ResTexture Resource::FindTexture(const char* pName,
                                 TextureProject* pTexProject) const {

    TextureData* pTexData = _FindTexture(pName, pTexProject);
    return ResTexture(pTexData);
}

TextureData* Resource::_FindTexture(const char* pName,
                                    TextureProject* pTexProject) const {

    TextureData* pTexData;

    if (pName[0] == 0) {
        return NULL;
    }

    if (pTexProject != NULL) {
        pTexData = breftSearchName(pTexProject, pName);
        if (pTexData != NULL) {
            return pTexData;
        }
    }

    pTexProject = static_cast<TextureProject*>(ut::List_GetLast(&mBREFTList));

    while (pTexProject != NULL) {
        pTexData = breftSearchName(pTexProject, pName);
        if (pTexData != NULL) {
            return pTexData;
        }

        pTexProject = static_cast<TextureProject*>(
            ut::List_GetPrev(&mBREFTList, pTexProject));
    }

    return NULL;
}

u32 Resource::NumEmitter(EffectProject* pEffProject) const {
    if (pEffProject != NULL) {
        return breffNumEmitter(pEffProject);
    }

    return mNumEmitter;
}

EmitterResource*
Resource::_GetEmitterIndexOf(u32 idx, EffectProject* pEffProject) const {
    if (pEffProject != NULL) {
        u16 numEmitter = breffNumEmitter(pEffProject);

        if (idx < numEmitter) {
            return breffIndexOf(pEffProject, idx);
        }

        return NULL;
    }

    pEffProject = static_cast<EffectProject*>(ut::List_GetFirst(&mBREFFList));

    while (pEffProject != NULL) {
        u16 numEmitter = breffNumEmitter(pEffProject);

        if (idx < numEmitter) {
            return breffIndexOf(pEffProject, idx);
        }

        idx -= numEmitter;

        pEffProject = static_cast<EffectProject*>(
            ut::List_GetNext(&mBREFFList, pEffProject));
    }

    return NULL;
}

TextureProject* Resource::AddTexture(u8* pData) {
    u8* pPtr = pData;

    FileHeader* pFileHeader = reinterpret_cast<FileHeader*>(pPtr);
    pPtr += pFileHeader->headersize;

    BlockHeader* pBlockHeader = reinterpret_cast<BlockHeader*>(pPtr);
    pPtr += sizeof(BlockHeader);

    TextureProject* pTexProject = reinterpret_cast<TextureProject*>(pPtr);

    memset(&pTexProject->projectlink, 0, sizeof(ut::Link));
    ut::List_Append(&mBREFTList, pTexProject);

    mNumTexture += breftNumTexture(pTexProject);
    breftRelocate(pTexProject);

    return pTexProject;
}

u32 Resource::relocateCurveTexture(u8* pCmdList) {
    u32 error = 0;

    AnimCurveHeader* pHeader = reinterpret_cast<AnimCurveHeader*>(pCmdList);

    AnimCurveKey* pKey = reinterpret_cast<AnimCurveKey*>(
        reinterpret_cast<u8*>(pHeader) + sizeof(AnimCurveHeader));

    AnimCurveRandom* pRandom = reinterpret_cast<AnimCurveRandom*>(
        reinterpret_cast<u8*>(pKey) + pHeader->keyTable);

    AnimCurveRandomTable* pRandomTable =
        reinterpret_cast<AnimCurveRandomTable*>(reinterpret_cast<u8*>(pRandom) +
                                                pHeader->rangeTable);

    AnimCurveNameTable* pNameTable = reinterpret_cast<AnimCurveNameTable*>(
        reinterpret_cast<u8*>(pRandomTable) + pHeader->randomTable);

    u8* pName = reinterpret_cast<u8*>(pNameTable) +
                offsetof(AnimCurveNameTable, datas) +
                pNameTable->count * sizeof(AnimCurveNameTable::Name);

    for (int i = 0; i < pNameTable->count; i++) {
        int size = *reinterpret_cast<u16*>(pName);
        pName += sizeof(u16);

        pNameTable->datas[i].work = reinterpret_cast<u32>(
            _FindTexture(reinterpret_cast<const char*>(pName), NULL));

        if (pName[0] != 0 && pNameTable->datas[i].work == 0) {
            error++;
        }

        pName += size;
    }

    return error;
}

u32 Resource::relocateCurveChild(u8* pCmdList) {
    u32 error = 0;

    AnimCurveHeader* pHeader = reinterpret_cast<AnimCurveHeader*>(pCmdList);

    AnimCurveKey* pKey = reinterpret_cast<AnimCurveKey*>(
        reinterpret_cast<u8*>(pHeader) + sizeof(AnimCurveHeader));

    AnimCurveRandom* pRandom = reinterpret_cast<AnimCurveRandom*>(
        reinterpret_cast<u8*>(pKey) + pHeader->keyTable);

    AnimCurveRandomTable* pRandomTable =
        reinterpret_cast<AnimCurveRandomTable*>(reinterpret_cast<u8*>(pRandom) +
                                                pHeader->rangeTable);

    AnimCurveNameTable* pNameTable = reinterpret_cast<AnimCurveNameTable*>(
        reinterpret_cast<u8*>(pRandomTable) + pHeader->randomTable);

    u8* pName = reinterpret_cast<u8*>(pNameTable) +
                offsetof(AnimCurveNameTable, datas) +
                pNameTable->count * sizeof(AnimCurveNameTable::Name);

    for (int i = 0; i < pNameTable->count; i++) {
        int size = *reinterpret_cast<u16*>(pName);
        pName += sizeof(u16);

        pNameTable->datas[i].work = reinterpret_cast<u32>(
            _FindEmitter(reinterpret_cast<char*>(pName), NULL));

        if (pNameTable->datas[i].work == 0) {
            error++;
        }

        pName += size;
    }

    return error;
}

u32 Resource::RelocateCommand() {
    u32 error = 0;

    for (u32 idx = 0; idx < NumEmitter(NULL); idx++) {
        EmitterResource* pResource = _GetEmitterIndexOf(idx, NULL);
        if (pResource == NULL) {
            continue;
        }

        ParticleParameterDesc* pPtclDesc =
            pResource->GetParticleParameterDesc();
        TextureData** ppWork = pPtclDesc->mTexture;
        u8* pPtr = pPtclDesc->textureNames;

        for (int i = 0; i < TEX_LAYER_MAX; i++) {
            u16 size = *reinterpret_cast<u16*>(pPtr);
            pPtr += sizeof(u16);

            ppWork[i] = _FindTexture(reinterpret_cast<char*>(pPtr), NULL);

            if (pPtr[0] != 0 && ppWork[i] == NULL) {
                error++;
            }

            pPtr += size;
        }

        for (u16 pidx = 0; pidx < pResource->NumPtclTrack(); pidx++) {
            u8* pPtr = pResource->GetPtclTrack(pidx);

#define pTrackAsHeader reinterpret_cast<AnimCurveHeader*>(pPtr)

            if (pTrackAsHeader->magic != NW4R_EF_MAGIC_ANIMCURVE) {
                continue;
            }

            // Load curveFlag and kindEnable
            u16 ctrl = *reinterpret_cast<u16*>(&pTrackAsHeader->curveFlag);

            switch (ctrl) {
            case (AC_TYPE_PARTICLE_TEXTURE << 8 | 0b001): {
                error += relocateCurveTexture(pPtr);
                break;
            }

            case (AC_TYPE_CHILD << 8 | 0b001): {
                error += relocateCurveChild(pPtr);
                break;
            }

            case (AC_TYPE_PARTICLE_U8 << 8 | 0b111):
            case (AC_TYPE_PARTICLE_F32 << 8 | 0b011): {
                break;
            }
            }

#undef pTrackAsHeader
        }
    }

    return error;
}

bool Resource::RemoveEffectProject(EffectProject* pEffProject) {
    EffectProject* pIt =
        static_cast<EffectProject*>(ut::List_GetFirst(&mBREFFList));

    for (; pIt != NULL; pIt = static_cast<EffectProject*>(
                            ut::List_GetNext(&mBREFFList, pIt))) {

        if (pIt != pEffProject) {
            continue;
        }

        ut::List_Remove(&mBREFFList, pEffProject);

        mNumEmitter -=
            pEffProject != NULL ? breffNumEmitter(pEffProject) : mNumEmitter;

        return true;
    }

    return false;
}

bool Resource::RemoveTextureProject(TextureProject* pTexProject) {
    TextureProject* pIt =
        static_cast<TextureProject*>(ut::List_GetFirst(&mBREFTList));

    for (; pIt != NULL; pIt = static_cast<TextureProject*>(
                            ut::List_GetNext(&mBREFTList, pIt))) {

        if (pIt != pTexProject) {
            continue;
        }

        ut::List_Remove(&mBREFTList, pTexProject);

        mNumTexture -=
            pTexProject != NULL ? breftNumTexture(pTexProject) : mNumTexture;

        return true;
    }

    return false;
}

} // namespace ef
} // namespace nw4r
