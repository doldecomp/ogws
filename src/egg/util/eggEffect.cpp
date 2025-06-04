// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/util.h>

#include <nw4r/ef.h>

namespace EGG {

static const nw4r::ef::Handle<nw4r::ef::Effect> cInvalidHandle;

DECOMP_FORCEACTIVE(eggEffect_cpp,
                   nw4r::ef::ParticleManager::ModifierTravFunc_SetSimpleLightType,
                   nw4r::ef::ParticleManager::ModifierTravFunc_SetSimpleLightAmbient,
                   nw4r::ef::ParticleManager::ModifierTravFunc_SetScale,
                   nw4r::ef::ParticleManager::ModifierTravFunc_SetRotate);

} // namespace EGG
