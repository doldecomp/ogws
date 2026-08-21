#include <egg/gfxe.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

#include <cstring>

namespace EGG {

void G3DUtility::initialize(u32 tmpSize, Heap* pHeap) {
#line 31
    EGG_ASSERT(tmpSize % 32 == 0);

    if (pHeap == NULL) {
        pHeap = Heap::getCurrentHeap();
    }

    if (tmpSize > 0) {
        sTempMem = new (pHeap, 32) u8[tmpSize];
        sTempMemSize = tmpSize;
    } else {
        sTempMem = NULL;
        sTempMemSize = 0;
    }

    sTempMemIndex = 0;

    for (u32 i = nw4r::g3d::G3DState::MAX_SCNDEPENDENT_TEXMTX_FUNCTYPE + 1;
         i < nw4r::g3d::G3DState::NUM_SCNDEPENDENT_TEXMTX_FUNCTYPE; i++) {

        nw4r::g3d::G3DState::ScnDependentTexMtxFuncPtr pFunc;
        if (!nw4r::g3d::G3DState::GetScnDependentTexMtxFunc(i, &pFunc, NULL)) {
            continue;
        }

        if (pFunc != manualProjectionMapping) {
            continue;
        }

#line 56
        EGG_ASSERT(sManualProjectionMapMode == i);
        return;
    }

    for (u32 i = nw4r::g3d::G3DState::MAX_SCNDEPENDENT_TEXMTX_FUNCTYPE + 1;
         i < nw4r::g3d::G3DState::NUM_SCNDEPENDENT_TEXMTX_FUNCTYPE; i++) {

        nw4r::g3d::G3DState::ScnDependentTexMtxFuncPtr pFunc;
        if (!nw4r::g3d::G3DState::GetScnDependentTexMtxFunc(i, &pFunc, NULL)) {
            continue;
        }

        if (pFunc != manualProjectionMapping) {
            continue;
        }

        sManualProjectionMapMode = i;

        nw4r::g3d::G3DState::SetScnDependentTexMtxFunc(
            i, manualProjectionMapping,
            nw4r::g3d::G3DState::SCNDEPENDENT_TEXMTX_FUNCTYPE_SRC_POS);

        return;
    }

#line 77
    EGG_ASSERT(sManualProjectionMapMode != 0);
}

bool G3DUtility::setManualMapMode(nw4r::g3d::ResTexSrt srt, u32 id) {
#line 90
    EGG_ASSERT(srt.IsValid());

    u32 mode;
    int camRef;
    int lightRef;

    if (srt.GetMapMode(id, &mode, &camRef, &lightRef)) {
        // @bug SetMapMode can still fail
#if defined(BUG_FIX)
        return srt.SetMapMode(id, sManualProjectionMapMode, camRef, lightRef);
#else
        srt.SetMapMode(id, sManualProjectionMapMode, camRef, lightRef);
        return true;
#endif
    }

    return false;
}

void G3DUtility::manualProjectionMapping(nw4r::math::MTX34* pM, s8 /* camRef */,
                                         s8 /* lightRef */) {
#line 134
    EGG_ASSERT(pM);

    nw4r::math::MTX34Copy(pM, nw4r::g3d::G3DState::GetProjectionTexMtxPtr());
}

bool G3DUtility::setUpLightSet(nw4r::g3d::LightSetting& rSetting,
                               const nw4r::g3d::ResAnmScn scn,
                               int lightSetRef) {
    if (!scn.IsValid()) {
        return false;
    }

    int endLightSetRef =
        scn.GetResLightSetMaxRefNumber() < rSetting.GetNumLightSet()
            ? scn.GetResLightSetMaxRefNumber()
            : rSetting.GetNumLightSet();

    int i_set = 0;

    if (lightSetRef >= 0) {
        i_set = lightSetRef;
        endLightSetRef = lightSetRef + 1;
    }

    for (; i_set < endLightSetRef; i_set++) {
        nw4r::g3d::LightSet lightSet = rSetting.GetLightSet(i_set);

        const nw4r::g3d::ResLightSet resLightSet =
            scn.GetResLightSetByRefNumber(i_set);

        if (!lightSet.IsValid()) {
            return false;
        }

        // Specular lights are set from the end of the set
        u32 specLightIdx = nw4r::g3d::G3DState::NUM_LIGHT_IN_LIGHT_SET - 1;

        u32 i_light = 0;
        int endLightIdx = resLightSet.GetNumLight();

        for (; i_light < endLightIdx; i_light++) {
            u32 lightID = resLightSet.GetLightID(i_light);

            if (lightID != nw4r::g3d::ResLightSetData::INVALID_ID) {
                const nw4r::g3d::ResAnmLight anmLight =
                    scn.GetResAnmLight(lightID);

                lightSet.SelectLightObj(i_light, anmLight.GetRefNumber());

                if (anmLight.HasSpecularLight()) {
                    lightSet.SelectLightObj(specLightIdx--,
                                            anmLight.GetSpecularLightIdx());
                }

            } else {
                lightSet.SelectLightObj(i_light, -1);
            }
        }

        for (; endLightIdx <= specLightIdx; endLightIdx++) {
            lightSet.SelectLightObj(endLightIdx, -1);
        }

        if (resLightSet.HasAmbLight()) {
            const nw4r::g3d::ResAnmAmbLight anmAmb =
                scn.GetResAnmAmbLight(resLightSet.GetAmbLightID());

            lightSet.SelectAmbLightObj(anmAmb.GetRefNumber());
        } else {
            lightSet.SelectAmbLightObj(-1);
        }
    }

    return true;
}

u16 G3DUtility::searchStringResNode(const nw4r::g3d::ResMdl mdl,
                                    const char* pName,
                                    StringSearchResult* pResultSet,
                                    u32 resultNum) {
    u16 found = 0;

    for (u32 id = 0; id < mdl.GetResNodeNumEntries(); id++) {
        const nw4r::g3d::ResNode node = mdl.GetResNode(id);

        if (pName != NULL && std::strstr(node.GetName(), pName) == NULL) {
            continue;
        }

        if (found < resultNum) {
            pResultSet[found].id = id;
            pResultSet[found].pName = node.GetName();
        }

        found++;
    }

    return found;
}

u16 G3DUtility::searchStringResMat(const nw4r::g3d::ResMdl mdl,
                                   const char* pName,
                                   StringSearchResult* pResultSet,
                                   u32 resultNum) {
    u16 found = 0;

    for (u32 id = 0; id < mdl.GetResMatNumEntries(); id++) {
        const nw4r::g3d::ResMat mat = mdl.GetResMat(id);

        if (pName != NULL && std::strstr(mat.GetName(), pName) == NULL) {
            continue;
        }

        if (found < resultNum) {
            pResultSet[found].id = id;
            pResultSet[found].pName = mat.GetName();
        }

        found++;
    }

    return found;
}

u16 G3DUtility::searchStringResTexPlttInfo(const nw4r::g3d::ResMdl mdl,
                                           const char* pName,
                                           StringSearchResult* pResultSet,
                                           u32 resultNum) {
    u16 found = 0;

    for (u32 id_info = 0;
         id_info < mdl.GetResTexPlttInfoOffsetFromTexNameNumEntries();
         id_info++) {

        nw4r::g3d::ResTexPlttInfoOffset offset =
            mdl.GetResTexPlttInfoOffsetFromTexName(id_info);

        for (u16 id_ofs = 0; id_ofs < offset.GetNumOffset(); id_ofs++) {
            const nw4r::g3d::ResTexPlttInfo info =
                offset.GetResTexPlttInfo(id_ofs);

            if (pName != NULL &&
                std::strstr(info.GetTexName(), pName) == NULL) {

                continue;
            }

            if (found < resultNum) {
                pResultSet[found].id = id_info;
                pResultSet[found].pName = info.GetTexName();
            }

            found++;
        }
    }

    return found;
}

u16 G3DUtility::replaceTexture(nw4r::g3d::ResMat mat,
                               nw4r::g3d::ScnMdl::CopiedMatAccess* pMatAccess,
                               const char* pName, const GXTexObj& rTexObj,
                               bool saveFilterWrap,
                               TextureReplaceResult* pResultSet,
                               u16 resultNum) {
#line 343
    EGG_ASSERT(pName);

    if (!mat.IsValid()) {
        return 0;
    }

    u16 found = 0;

    for (u16 id = 0; id < mat.GetNumResTexPlttInfo(); id++) {
        const nw4r::g3d::ResTexPlttInfo info = mat.GetResTexPlttInfo(id);

        if (std::strcmp(pName, info.GetTexName()) != 0) {
            continue;
        }

        bool fromAccess =
            pMatAccess != NULL && pMatAccess->GetResTexObj(false).IsValid();

        nw4r::g3d::ResTexObj texObj =
            fromAccess ? pMatAccess->GetResTexObj(false) : mat.GetResTexObj();

        GXTexObj* p_resObj = texObj.GetTexObj(info.GetTexMapID());
#line 360
        EGG_ASSERT(p_resObj);

        if (saveFilterWrap) {
            void* pImagePtr;
            u16 width, height;
            GXTexFmt format;
            GXTexWrapMode wrapS, wrapT;
            GXBool mipmap;

            GXGetTexObjAll(p_resObj, &pImagePtr, &width, &height, &format,
                           &wrapS, &wrapT, &mipmap);

            GXTexFilter minFilt, magFilt;
            f32 minLod, maxLod, lodBias;
            GXBool biasClamp, edgeLod;
            GXAnisotropy maxAniso;

            GXGetTexObjLODAll(p_resObj, &minFilt, &magFilt, &minLod, &maxLod,
                              &lodBias, &biasClamp, &edgeLod, &maxAniso);

            *p_resObj = rTexObj;

            GXInitTexObjFilter(p_resObj, minFilt, magFilt);
            GXInitTexObjWrapMode(p_resObj, wrapS, wrapT);

        } else {
            *p_resObj = rTexObj;
        }

        if (pResultSet != NULL && found < resultNum) {
            const nw4r::g3d::ResTev tev = mat.GetResTev();

            for (u8 i = 0; i < tev.GetNumTevStages(); i++) {
                GXTexCoordID coord;
                GXTexMapID map;

                if (!tev.GXGetTevOrder(static_cast<GXTevStageID>(i), &coord,
                                       &map, NULL)) {
                    continue;
                }

                if (map == info.GetTexMapID()) {
                    pResultSet[found].texMapID = map;
                    pResultSet[found].texCoordID = coord;
                }
            }
        }

        found++;
    }

    return found;
}

} // namespace EGG
