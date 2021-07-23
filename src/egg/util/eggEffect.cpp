#include "eggEffect.h"
#include "ef_particlemanager.h"
#include "ef_effect.h"

namespace
{
    using namespace nw4r;

    // Create weak function instances
    UNKTYPE INSTANTIATE_WEAK(ef::Effect *e)
    {
        e->ForeachParticleManager(
            ef::ParticleManager::ModifierTravFunc_SetRotate,
            0,
            false);

        e->ForeachParticleManager(
            ef::ParticleManager::ModifierTravFunc_SetScale,
            0,
            false);

        e->ForeachParticleManager(
            ef::ParticleManager::ModifierTravFunc_SetSimpleLightAmbient,
            0,
            false);

        e->ForeachParticleManager(
            ef::ParticleManager::ModifierTravFunc_SetSimpleLightType,
            0,
            false);
    }
}