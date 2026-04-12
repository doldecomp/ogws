#include <Pack/RPGraphics.h>

#include <cstdio>

/**
 * @brief Replaces a texture on the specified model
 *
 * @param pModel Target model
 * @param pName Texture name (format string)
 * @param ... Format string arguments
 */
void RPGrpShadowTexture::Replace(RPGrpModel* pModel, const char* pName, ...) {
    char buffer[256];

    std::va_list list;
    va_start(list, pName);

    // @bug Unsafe string operations
#if defined(BUG_FIX)
    std::vsnprintf(buffer, sizeof(buffer), pName, list);
#else
    std::vsprintf(buffer, pName, list);
#endif

    EGG::ShadowTexture::Replace(pModel->GetModelEx(), buffer);

    va_end(list);
}

/**
 * @brief Adds a new model to the shadow texture
 *
 * @param pModel Model
 * @param density Model density
 */
void RPGrpShadowTexture::AddModel(RPGrpModel* pModel, f32 density) {
    AddModelEx(pModel->GetModelEx(), density);
}

/**
 * @brief Adds a new model with materials to the shadow texture
 *
 * @param pModel Model
 * @param density Model density
 */
void RPGrpShadowTexture::AddModelUseMaterial(RPGrpModel* pModel, f32 density) {
    AddModelEx(pModel->GetModelEx(), density);
    GetModelBind(GetModelNum() - 1)->useMat = true;
}
