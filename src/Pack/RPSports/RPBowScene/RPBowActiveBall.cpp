#include <Pack/RPSports/RPBowScene/bowling.h>

// Returns a packed 32-bit color (RGBA) from the model
u32 fn_801C389C(RPGrpModel* pModel, int unk1, int unk2);

// Applies the given color to the model
void fn_801C37EC(RPGrpModel* pModel, int unk1, int unk2, GXColor* pColor);

namespace Bowling {

/**
 * @brief Initializes the render object to its default state
 */
void RPBowActiveBall::ResetRenderState() {
    MTX34Identity(&mtx);

    field_0x74 = 0.0f;
    index = 0;

    mtx._23 = 9999.0f;
    alpha = 1.0f;
}

/**
 * @brief Renders the currently selected model set
 *
 * Updates the main model's transform and color, renders a mirrored version used
 * for reflections, and optionally submits the model to the shadow texture renderer.
 */
void RPBowActiveBall::RenderModelSet() {
    if (mtx._23 > 49.0f) {
        return;
    }

    nw4r::math::MTX34 worldMtx = mtx;

    f32 scale = 1.0f;
    worldMtx._00 *= scale;
    worldMtx._01 *= scale;
    worldMtx._02 *= scale;

    worldMtx._10 *= scale;
    worldMtx._11 *= scale;
    worldMtx._12 *= scale;

    worldMtx._20 *= scale;
    worldMtx._21 *= scale;
    worldMtx._22 *= scale;

    u32 packedColor = fn_801C389C(models[index].pRealModel, 0, 0);

    GXColor color;
    color.a = (s8) (255.0f * alpha);
    color.r = GX_BITGET(packedColor, 16, 8);
    color.g = GX_BITGET(packedColor, 8, 8);
    color.b = GX_BITGET(packedColor, 0, 8);

    GXColor modelColor = color;

    fn_801C37EC(models[index].pRealModel, 0, 0, &modelColor);

    if (models[index].pRealModel->GetScnObj() != NULL) {
        models[index].pRealModel->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &worldMtx);
    }

    models[index].pRealModel->UpdateFrame();
    models[index].pRealModel->Calc();
    models[index].pRealModel->Entry();

    nw4r::math::MTX34 reflectionMtx = worldMtx;

    reflectionMtx._10 *= -1.0f;
    reflectionMtx._11 *= -1.0f;
    reflectionMtx._12 *= -1.0f;
    reflectionMtx._13 *= -1.0f;

    nw4r::math::VEC3 src(0.0f, 0.0f, 0.0f);
    nw4r::math::VEC3 dst;

    f32 limit = 1.075f;
    f32 thresholdZ = -192.0f + limit;
    f32 thresholdY = -limit;
    f32 offset = 0.0f;

    VEC3Transform(&dst, &reflectionMtx, &src);

    if (dst.y > thresholdY && dst.z > thresholdZ) {
        f32 diff = thresholdY - dst.y;

        if (offset > diff) {
            offset = diff;
        }
    }

    reflectionMtx._13 += offset;

    if (models[index].pReflectionModel->GetScnObj() != NULL) {
        models[index].pReflectionModel->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &reflectionMtx);
    }

    models[index].pReflectionModel->UpdateFrame();
    models[index].pReflectionModel->Calc();
    models[index].pReflectionModel->Entry();

    if (!disableShadow) {
        pShadowTexture->AddModel(models[index].pRealModel, 1.0f);
    }
}

} // namespace Bowling
