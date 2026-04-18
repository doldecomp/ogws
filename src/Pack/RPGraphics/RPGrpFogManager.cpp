#include <Pack/RPGraphics.h>

#include <nw4r/g3d.h>

/**
 * @brief Applies fog settings from the specified scene resource
 *
 * @param handle File resource handle
 * @param pName Scene file name
 * @param frame Animation frame (defaults to the first frame)
 */
void RPGrpFogManager::LoadScnFog(RPGrpHandle handle, const char* pName,
                                 f32 frame) {

    const nw4r::g3d::ResAnmScn scn =
        RPGrpModelResManager::GetCurrent()
            ->GetData<RPGrpModelResManager::Type_ResAnmScn>(handle, pName);

    EGG::FogManager::LoadScnFog(scn, frame);
}
