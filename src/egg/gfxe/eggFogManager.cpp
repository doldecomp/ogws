#include <egg/gfxe.h>

namespace EGG {

FogManager::FogManager() : mFlags(0) {
    for (int i = 0; i < FOG_MAX; i++) {
        mFog[i] = new Fog();
    }
}

void FogManager::Reset() {
    for (int i = 0; i < FOG_MAX; i++) {
        mFog[i]->Reset();
    }
}

void FogManager::Calc() {
    if (mFlags & EFlag_AwaitDraw) {
        return;
    }

    for (int i = 0; i < FOG_MAX; i++) {
        mFog[i]->Calc();
    }

    mFlags |= EFlag_AwaitDraw;
}

void FogManager::LoadScreenClip(const Screen& rScreen) {
    for (int i = 0; i < FOG_MAX; i++) {
        mFog[i]->mNearZ = rScreen.GetNearZ();
        mFog[i]->mFarZ = rScreen.GetFarZ();
    }
}

void FogManager::CopyToG3D(nw4r::g3d::ScnRoot* pScnRoot) const {
    for (int i = 0; i < FOG_MAX; i++) {
        mFog[i]->CopyToG3D(pScnRoot->GetFog(i));
    }
}

void FogManager::LoadScnFog(const nw4r::g3d::ResAnmScn scn, f32 frame) {
    if (!scn.IsValid()) {
        return;
    }

    if (scn.GetResAnmFogMaxRefNumber() <= 0) {
        return;
    }

    u32 fogNum = scn.GetResAnmFogMaxRefNumber() >= FOG_MAX
                     ? FOG_MAX
                     : scn.GetResAnmFogMaxRefNumber();

    for (int i = 0; i < fogNum; i++) {
        mFog[i]->Unbind();
        mFog[i]->Bind(scn.GetResAnmFogByRefNumber(i), frame);
    }
}

void FogManager::DoneDraw() {
    mFlags &= ~EFlag_AwaitDraw;
}

} // namespace EGG
