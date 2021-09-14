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

    void FogManager::reset()
    {
        for (int i = 0; i < cNumFog; i++)
        {
            mFog[i]->reset();
        }
    }

    void FogManager::callVF_0x10()
    {
        if ((mFlags & FLAG_4) == 0)
        {
            for (int i = 0; i < cNumFog; i++)
            {
                mFog[i]->VF_0x10();
            }

            mFlags |= FLAG_4;
        }
    }

    void FogManager::useScreenZ(eggScreen *screen)
    {
        for (int i = 0; i < cNumFog; i++)
        {
            mFog[i]->mNearZ = screen->mNearZ;
            mFog[i]->mFarZ = screen->mFarZ;
        }
    }

    void FogManager::setG3D(nw4r::g3d::ScnRoot *root)
    {
        for (int i = 0; i < cNumFog; i++)
        {
            nw4r::g3d::Fog f = root->GetFog(i);
            mFog[i]->setG3D(f);
        }
    }

    void FogManager::initialize(nw4r::g3d::ResAnmScn *scene, f32 f1)
    {
        if (scene->IsValid() && scene->GetResAnmFogMaxRefNumber() > 0)
        {
            u32 numFog = (scene->GetResAnmFogMaxRefNumber() >= cNumFog)
                ? cNumFog : scene->GetResAnmFogMaxRefNumber();
            
            for (int i = 0; i < numFog; i++)
            {
                mFog[i]->setFlags();
                mFog[i]->initialize(scene->GetResAnmFogByRefNumber(i), f1);
            }
        }
    }

    void FogManager::resetFlags()
    {
        mFlags &= ~FLAG_4;
    }

    FogManager::~FogManager()
    {
        
    }
}