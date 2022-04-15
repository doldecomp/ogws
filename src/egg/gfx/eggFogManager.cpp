#include "eggFogManager.h"
#include "eggFog.h"
#include "eggScreen.h"
#include "g3d_fog.h"
#include "g3d_scnroot.h"
#include "g3d_resanmscn.h"

namespace EGG
{
    FogManager::FogManager() : mFlags(0)
    {
        for (int i = 0; i < cNumFog; i++)
        {
            mFog[i] = new Fog();
        }
    }

    void FogManager::Reset()
    {
        for (int i = 0; i < cNumFog; i++)
        {
            mFog[i]->Reset();
        }
    }

    void FogManager::Calc()
    {
        if ((mFlags & DRAW_READY) == 0)
        {
            for (int i = 0; i < cNumFog; i++)
            {
                mFog[i]->Calc();
            }

            mFlags |= DRAW_READY;
        }
    }

    void FogManager::UseScreenZ(Screen& screen)
    {
        for (int i = 0; i < cNumFog; i++)
        {
            mFog[i]->mNearZ = screen.GetNearZ();
            mFog[i]->mFarZ = screen.GetFarZ();
        }
    }

    void FogManager::CopyToG3D(nw4r::g3d::ScnRoot *root) const
    {
        for (int i = 0; i < cNumFog; i++)
        {
            nw4r::g3d::Fog f = root->GetFog(i);
            mFog[i]->CopyToG3D(f);
        }
    }

    void FogManager::LoadScnFog(nw4r::g3d::ResAnmScn *scene, f32 f1)
    {
        if (scene->IsValid() && scene->GetResAnmFogMaxRefNumber() > 0)
        {
            u32 numFog = (scene->GetResAnmFogMaxRefNumber() >= cNumFog)
                ? cNumFog : scene->GetResAnmFogMaxRefNumber();
            
            for (int i = 0; i < numFog; i++)
            {
                mFog[i]->Unbind();
                mFog[i]->Bind(scene->GetResAnmFogByRefNumber(i), f1);
            }
        }
    }

    void FogManager::DoneDraw()
    {
        mFlags &= ~DRAW_READY;
    }

    FogManager::~FogManager()
    {
        
    }
}