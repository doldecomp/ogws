#include <egg/gfxe.h>
#include <egg/prim.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

#include <revolution/GX.h>

#include <cstring>

namespace EGG {

template <> const char* IBinary<LightTextureManager>::spExtension = "blmap";

LightTextureManager::LightTextureManager(const LightManager* pManager)
    : mFlags(cFlag_ClearWorkSpace | cFlag_4 | cFlag_5 | cFlag_6),
      mTexNum(0),
      mppLightTextures(NULL),
      mpLightManager(pManager),
      mDrawFlags(0),
      mLightObjNum(LIGHT_OBJ_MAX),
      mppLightObjs(NULL) {

    EGG_ASSERT_LINE(36, pManager);

    mppLightTextures = new LightTexture*[LIGHT_TEX_MAX];
    for (int i = 0; i < LIGHT_TEX_MAX; i++) {
        mppLightTextures[i] = NULL;
    }

    mppLightObjs = new LightObj*[mLightObjNum];
    for (int i = 0; i < mLightObjNum; i++) {
        mppLightObjs[i] = NULL;
    }
}

u16 LightTextureManager::createTexture(const char* pName) {
    EGG_ASSERT_LINE(78, mTexNum < getMax());

    for (int i = 0; i < mTexNum; i++) {
        if (std::strcmp(pName, mppLightTextures[i]->getName()) == 0) {
            return i;
        }
    }

    mppLightTextures[mTexNum] = new LightTexture(mTexNum, pName, this);
    mppLightTextures[mTexNum]->configure();

    return mTexNum++;
}

u16 LightTextureManager::replaceModelTexture(int index, ModelEx* pMdl) const {
    EGG_ASSERT_LINE(121, pMdl);
    EGG_ASSERT_LINE(122, 0 <= index && index < mTexNum);

    GXTexObj tobj;
    mppLightTextures[index]->getTexObj(&tobj);

    TextureReplaceResult resultSet[255];
    u16 resultNum =
        pMdl->replaceTexture(mppLightTextures[index]->getName(), tobj, false,
                             resultSet, ARRAY_SIZE(resultSet), false);

    pMdl->replaceTexture(mppLightTextures[index]->getName(), tobj, false, NULL,
                         0, true);

    for (int i = 0; i < resultNum; i++) {
        u16 matIdx = resultSet[i].materialID;
        GXTexCoordID coord = static_cast<GXTexCoordID>(resultSet[i].texCoordID);

        nw4r::g3d::ResTexSrt srt = pMdl->getResMat(matIdx).GetResTexSrt();
        EGG_ASSERT_LINE(138, srt.IsValid());

        srt.SetMapMode(
            coord,                                                     //
            nw4r::g3d::G3DState::SCNDEPENDENT_TEXMTX_FUNCTYPE_SRC_NRM, //
            -1, -1);

        nw4r::g3d::ResMatTexCoordGen gen =
            pMdl->getResMat(matIdx).GetResMatTexCoordGen();
        EGG_ASSERT_LINE(144, gen.IsValid());

        GXTexGenType func;
        GXTexGenSrc param;
        GXBool normalize;
        u32 postMtx;
        gen.GXGetTexCoordGen2(coord, &func, &param, &normalize, &postMtx);

        gen.GXSetTexCoordGen2(coord, GX_TG_MTX3x4, GX_TG_NRM, GX_TRUE, postMtx);
        gen.EndEdit();
    }

    return resultNum;
}

int LightTextureManager::getTextureIndex(const char* pName) const {
    for (int i = 0; i < mTexNum; i++) {
        if (std::strcmp(pName, mppLightTextures[i]->getName()) == 0) {
            return i;
        }
    }

    return -1;
}

// void LightTextureManager::correctLightObject() {
//     int numLight = 0;
//     for (int i = 0; i < mpLightManager->GetNum(); i++) {
//         LightObj* p_obj = mpLightManager->GetLightObj(i);
// #line 234
//         EGG_ASSERT(p_obj);

//         if (p_obj->getFlags() & 0x1 && p_obj->getFlags() & 0x20) {
//             mppLightObjs[numLight] = p_obj;
//             if (++numLight >= mLightObjNum)
//                 break;
//         }
//     }

//     for (int i = numLight; i < mLightObjNum; i++) {
//         mppLightObjs[i] = NULL;
//     }
// }

// void LightTextureManager::frameReset() {
//     correctLightObject();
//     mDrawFlags = 0;
//     mFlags &= ~0x2;
// }

// // https://decomp.me/scratch/rqOkd
// void LightTextureManager::draw(LightManager* pManager,
//                                const Screen::DataEfb& efb, f32 x1, f32 y1,
//                                f32 x2, f32 y2) {
//     u8 view = 1 << pManager->GetCurrentView();
//     bool setPixelFmt = mFlags >> 5 & 1;
//     if (!(mFlags & 0x10) || (mDrawFlags & view) || mTexNum == 0)
//         return;

//     if (mFlags & 0x40) {
//         x1 = 0.0f;
//         y1 = StateGX::getEfbHeight();
//         x2 = StateGX::getEfbWidth();
//         y2 = 528 - StateGX::getEfbHeight();
//     }

//     mDrawFlags |= view;

//     StateGX::AutoColorUpdate color(true);
//     StateGX::AutoAlphaUpdate alpha(false);

//     // TODO

//     LightTexture::initDrawSetting(x1, y1, x2, y2);

//     TextureBuffer* texBuf = NULL;

//     u16 x, y, w, h;
//     LightTexture::getDrawSetting(&x, &y, &w, &h, mTexNum);
//     w += (w & 3);
//     h += (h & 3);

//     if (!(mFlags & 0x40) && (mFlags & 0x4)) {
//         texBuf = TextureBuffer::alloc(w, h, GX_TF_RGBA8);
//         texBuf->capture(x, y, false, -1);
//     }

//     if (setPixelFmt)
//         StateGX::setPixelFormatGX(GX_PF_RGB8_Z24, GX_ZC_LINEAR);

//     for (int i = 0; i < mTexNum; i++) {
//         mppLightTextures[i]->draw();
//     }

//     for (int i = 0; i < mTexNum; i++) {
//         bool b = setPixelFmt && (mFlags & 0x8);
//         // mppLightTextures[i]->capture(b);
//     }

//     if (setPixelFmt) {
//         StateGX::setPixelFormatGX(StateGX::getDefaultPixelFormat(),
//                                   StateGX::getDefaultZFmt16());
//     }

//     if (!(mFlags & 0x40)) {
//         StateGX::AutoColorUpdate color(true);
//         StateGX::AutoAlphaUpdate alpha(true);

//         if ((mFlags & 0x8) || texBuf != NULL) {
//             math::MTX34 proj;
//             C_MTXOrtho(proj, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
//             StateGX::GXSetProjection_(proj, GX_ORTHOGRAPHIC);
//             StateGX::GXSetViewport_(x, y, w, h, 0.0f, 1.0f);
//             StateGX::GXSetScissor_(x, y, w, h);
//             StateGX::GXSetScissorBoxOffset_(0, 0);

//             math::MTX34 forDL;
//             math::MTX34Identity(&forDL);

//             if (texBuf != NULL) {
//                 DrawGX::BeginDrawScreen(true, true, false);
//                 DrawGX::SetBlendMode(DrawGX::BLEND_REPLACE);
//                 GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
//                                GX_LO_CLEAR);
//                 texBuf->load(GX_TEXMAP0);
//                 DrawGX::DrawDL(DrawGX::DL_SCREEN_TEXTURE, forDL,
//                 DrawGX::WHITE); texBuf->free();
//             } else {
// #line 382
//                 EGG_ASSERT(isEnableClearWorkSpace());

//                 if (setPixelFmt) {
//                     DrawGX::BeginDrawScreen(true, false, true);
//                     DrawGX::SetBlendMode(DrawGX::BLEND_REPLACE);
//                     DrawGX::DrawDL(DrawGX::DL_SCREEN, forDL,
//                                    StateGX::getEfbClearColor());
//                 }
//             }
//         }
//     }
//     GXInvalidateTexAll();
// }

} // namespace EGG
