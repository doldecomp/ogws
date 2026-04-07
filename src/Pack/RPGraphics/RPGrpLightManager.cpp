#include <Pack/RPGraphics.h>

/**
 * @brief Applies light settings from the specified scene resource
 *
 * @param handle File resource handle
 * @param pName Scene file name
 * @param frame Animation frame (defaults to the first frame)
 * @param lightSetRef Light set reference number (defaults to index 0)
 */
void RPGrpLightManager::LoadScnLight(RPGrpHandle handle, const char* pName,
                                     f32 frame, u32 lightSetRef) {

    const nw4r::g3d::ResAnmScn scn =
        RPGrpModelResManager::GetCurrent()
            ->GetData<RPGrpModelResManager::Type_ResAnmScn>(handle, pName);

    LoadScnLightInner(scn, frame, lightSetRef);
}
