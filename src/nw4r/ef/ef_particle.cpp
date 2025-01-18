#include <nw4r/ef.h>

#include <cmath>

namespace nw4r {
namespace ef {

Particle::Particle() {}

Particle::~Particle() {}

void Particle::SendClosing() {
    mParticleManager->Closing(this);
}

void Particle::DestroyFunc() {}

void ParticleParameter::Initialize(ParticleParameterDesc* pDesc,
                                   ParticleManager* pManager) {

    int i, j;

    for (i = 0; i < COLOR_LAYER_MAX; i++) {
        for (j = 0; j < COLOR_IDX_MAX; j++) {
            mColor[i][j] = pDesc->mColor[i][j];
        }
    }

    mSize = pDesc->size;
    mScale = pDesc->scale;
    mRotate = pDesc->rotate;

    for (i = 0; i < AXIS_MAX; i++) {
        f32 rad = pDesc->rotateOffset[i];

        if (pDesc->rotateOffsetRandom[i] > 0) {
            // clang-format off
            rad += pDesc->rotateOffsetRandom[i] *
                   (rad * (2.0f * pManager->mManagerEM->mRandom.RandFloat() - 1.0f)) / 100.0f;
            // clang-format on
        }

        mRotateOffset[i] = ConvertF32RadToU8(rad);
    }

    for (i = 0; i < TEX_LAYER_MAX; i++) {
        mTexture[i] = pDesc->mTexture[i];
        mTextureScale[i] = pDesc->textureScale[i];
        mTextureRotate[i] = pDesc->textureRotate[i];
        mTextureTranslate[i] = pDesc->textureTranslate[i];
    }

    mTextureWrap = pDesc->textureWrap;
    mTextureReverse = pDesc->textureReverse;
    mACmpRef0 = pDesc->mACmpRef0;
    mACmpRef1 = pDesc->mACmpRef1;
}

bool Particle::Initialize(u16 life, math::VEC3 pos, math::VEC3 vel,
                          ParticleManager* pManager, const math::MTX34* pSpace,
                          float momentum, const EmitterInheritSetting* pSetting,
                          Particle* pReferencePtcl) {

    ReferencedObject::Initialize();

    if (life == 0) {
        life = 1;
    }

    mParticleManager = pManager;
    pManager->Ref();

    mEvalStatus = NW4R_EF_ES_WAIT;
    mCalcRemain = 0;

    (void)Resource::GetInstance(); // unused

    EmitterDesc* pEmitDesc = pManager->mResource->GetEmitterDesc();
    ParticleParameterDesc* pPtclDesc =
        pManager->mResource->GetParticleParameterDesc();

    mParameter.Initialize(pPtclDesc, pManager);
    mParameter.mMomentum = momentum;

    mTick = 0;
    mRandSeed = pManager->mManagerEM->mRandom.Rand();
    mLife = life;
    mParameter.mAlphaFlickRnd =
        (pManager->mManagerEM->mRandom.Rand() % 254) - 127;

    mParameter.mPosition = pos;
    mParameter.mPrevPosition = mParameter.mPosition;
    mParameter.mVelocity = vel;

    const math::VEC3* pEffVel = pManager->mManagerEM->mManagerEF->GetVelocity();

    if (pEffVel->x != 0.0f || pEffVel->y != 0.0f || pEffVel->z != 0.0f) {
        math::MTX34 glbMtx;
        pManager->mManagerEM->CalcGlobalMtx(&glbMtx);

        math::MTX34Inv(&glbMtx, &glbMtx);
        glbMtx._03 = glbMtx._13 = glbMtx._23 = 0.0f;

        math::VEC3 glbVel;
        math::VEC3Transform(&glbVel, &glbMtx, pEffVel);
        mParameter.mVelocity += glbVel;
    }

    if (pSpace != NULL) {
        math::VEC3Transform(&mParameter.mPosition, pSpace,
                            &mParameter.mPosition);

        math::MTX34 spaceProj(*pSpace);
        spaceProj._03 = spaceProj._13 = spaceProj._23 = 0.0f;

        math::VEC3Transform(&mParameter.mVelocity, &spaceProj,
                            &mParameter.mVelocity);
    }

    mPrevAxis = math::VEC3(2.0f, 0.0f, 0.0f);

    if (pReferencePtcl != NULL && pSetting != NULL) {
        if (pSetting->speed != 0) {
            math::VEC3 glbSpeed;
            math::MTX34 glbMtx;

            pReferencePtcl->mParticleManager->CalcGlobalMtx(&glbMtx);
            glbMtx._03 = glbMtx._13 = glbMtx._23 = 0.0f;
            math::VEC3Transform(&glbSpeed, &glbMtx,
                                &pReferencePtcl->mParameter.mVelocity);

            mParticleManager->CalcGlobalMtx(&glbMtx);
            glbMtx._03 = glbMtx._13 = glbMtx._23 = 0.0f;
            math::MTX34Inv(&glbMtx, &glbMtx);
            math::VEC3Transform(&glbSpeed, &glbMtx, &glbSpeed);

            mParameter.mVelocity.x +=
                glbSpeed.x * pSetting->speed * (1.0f / 100.0f);
            mParameter.mVelocity.y +=
                glbSpeed.y * pSetting->speed * (1.0f / 100.0f);
            mParameter.mVelocity.z +=
                glbSpeed.z * pSetting->speed * (1.0f / 100.0f);
        }

        if (pSetting->scale != 0) {
            mParameter.mSize.x = pSetting->scale *
                                 pReferencePtcl->Draw_GetSizeX() *
                                 (1.0f / 100.0f);
            mParameter.mSize.y = pSetting->scale *
                                 pReferencePtcl->Draw_GetSizeY() *
                                 (1.0f / 100.0f);
        }

        if (pSetting->alpha != 0) {
            for (int i = 0; i < COLOR_LAYER_MAX; i++) {
                for (int j = 0; j < COLOR_IDX_MAX; j++) {
                    // clang-format off
                    mParameter.mColor[i][j].a = pSetting->alpha *
                        pReferencePtcl->mParameter.mColor[i][j].a / 100;
                    // clang-format on
                }
            }
        }

        if (pSetting->color != 0) {
            for (int i = 0; i < COLOR_LAYER_MAX; i++) {
                for (int j = 0; j < COLOR_IDX_MAX; j++) {
                    // clang-format off
                    mParameter.mColor[i][j].r = pSetting->color *
                        pReferencePtcl->mParameter.mColor[i][j].r / 100;

                    mParameter.mColor[i][j].g = pSetting->color *
                        pReferencePtcl->mParameter.mColor[i][j].g / 100;

                    mParameter.mColor[i][j].b = pSetting->color *
                        pReferencePtcl->mParameter.mColor[i][j].b / 100;
                    // clang-format on
                }
            }
        }

        if (pSetting->flag & EmitterInheritSetting::FLAG_INHERIT_ROT) {
            f32 rad;

            rad = pReferencePtcl->mParameter.mRotate.x;
            rad += NW4R_MATH_FIDX_TO_RAD(
                pReferencePtcl->mParameter.mRotateOffset[AXIS_X]);
            mParameter.mRotateOffset[AXIS_X] = ConvertF32RadToU8(rad);

            rad = pReferencePtcl->mParameter.mRotate.y;
            rad += NW4R_MATH_FIDX_TO_RAD(
                pReferencePtcl->mParameter.mRotateOffset[AXIS_Y]);
            mParameter.mRotateOffset[AXIS_Y] = ConvertF32RadToU8(rad);

            rad = pReferencePtcl->mParameter.mRotate.z;
            rad += NW4R_MATH_FIDX_TO_RAD(
                pReferencePtcl->mParameter.mRotateOffset[AXIS_Z]);
            mParameter.mRotateOffset[AXIS_Z] = ConvertF32RadToU8(rad);
        }
    }

    return true;
}

void Particle::Draw_GetColor(int layer, GXColor* pColorPri,
                             GXColor* pColorSec) {

    const EmitterDesc* pDesc = mParticleManager->mResource->GetEmitterDesc();
    const EmitterDrawSetting& rSetting = pDesc->drawSetting;

    GetColor(layer, COLOR_IDX_PRI, pColorPri);
    GetColor(layer, COLOR_IDX_SEC, pColorSec);

    u32 cycleL;
    u16 cycle;
    u16 pos;
    s16 alpha;

    if (rSetting.mAlphaFlickType != EmitterDrawSetting::ALPHAFLICK_NONE) {
        cycleL = rSetting.mAlphaFlickCycle +
                 rSetting.mAlphaFlickCycle * mParameter.mAlphaFlickRnd *
                     rSetting.mAlphaFlickRandom / 12700;

        if (cycleL <= 0xFFFF) {
            cycle = cycleL;
        } else {
            cycle = 0xFFFF;
        }

        pos = (mTick - 1) % cycle;
        alpha = 0;

        switch (rSetting.mAlphaFlickType) {
        case EmitterDrawSetting::ALPHAFLICK_TRIANGLE: {
            if (pos * 2 <= cycle) {
                alpha = 128 - rSetting.mAlphaFlickAmplitude +
                        rSetting.mAlphaFlickAmplitude * (pos * 4) / cycle;
            } else {
                alpha = 128 + rSetting.mAlphaFlickAmplitude * 3 +
                        -(rSetting.mAlphaFlickAmplitude * pos * 4) / cycle;
            }
            break;
        }

        case EmitterDrawSetting::ALPHAFLICK_SAWTOOTH1: {
            alpha = 128 + rSetting.mAlphaFlickAmplitude +
                    -(rSetting.mAlphaFlickAmplitude * pos * 2) / cycle;
            break;
        }

        case EmitterDrawSetting::ALPHAFLICK_SAWTOOTH2: {
            alpha = 128 - rSetting.mAlphaFlickAmplitude +
                    rSetting.mAlphaFlickAmplitude * (pos * 2) / cycle;
            break;
        }

        case EmitterDrawSetting::ALPHAFLICK_SQUARE: {
            if (pos * 2 <= cycle) {
                alpha = 128 + rSetting.mAlphaFlickAmplitude;
            } else {
                alpha = 128 - rSetting.mAlphaFlickAmplitude;
            }
            break;
        }

        case EmitterDrawSetting::ALPHAFLICK_SINE: {
            alpha = 128 + rSetting.mAlphaFlickAmplitude *
                              std::sinf(2 * NW4R_MATH_PI * pos / cycle);
            break;
        }

        default: {
            break;
        }
        }

        if (alpha < 0) {
            alpha = 0;
        }
        if (alpha > 255) {
            alpha = 255;
        }

        pColorPri->a = (pColorPri->a * alpha + 128) >> 8;
        pColorSec->a = (pColorSec->a * alpha + 128) >> 8;
    }

    mParticleManager->Draw_ModifyColor(this, pColorPri, pColorSec);
}

} // namespace ef
} // namespace nw4r
