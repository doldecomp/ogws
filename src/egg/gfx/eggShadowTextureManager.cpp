#include "eggShadowTextureManager.h"
#include "eggShadowTexture.h"
#include "eggPostEffectBase.h"
#include "eggStateGX.h"
#include "eggDrawGX.h"
#include "eggTextureBuffer.h"
#include "eggAssert.h"
#include <revolution/GX.h>

namespace EGG
{
    ShadowTextureManager::ShadowTextureManager() :
        mFlags(SHADOW_MGR_ACTIVE),
        mFreeGroup(GROUP_MAX),
        mShadowIdx(0)
    {
        for (int i = 0; i < GROUP_MAX; i++)
        {
            mGroups[i] = NULL;
        }
    }

    void ShadowTextureManager::Reset()
    {
        for (int i = 0; i < GROUP_MAX; i++)
        {
            mGroups[i] = NULL;
        }

        mShadowIdx = 0;
    }

    void ShadowTextureManager::Set(u16 group, ShadowTexture *tex)
    {
        #line 65
        EGG_ASSERT(group < GROUP_MAX);
        mGroups[group] = tex;
    }

    u16 ShadowTextureManager::Append(ShadowTexture *tex)
    {
        mFreeGroup = GROUP_MAX;
        while (mGroups[--mFreeGroup] != NULL)
        {
            #line 88
            EGG_ASSERT_MSG(mFreeGroup > 0, "Can't set texture any more.");
        }

        Set(mFreeGroup, tex);
        return mFreeGroup;
    }

    void ShadowTextureManager::Calc()
    {
        if (!IsActive()) return;

        mShadowIdx = 0;
        for (int i = 0; i < GROUP_MAX; i++)
        {
            if (mGroups[i] != NULL)
            {
                mGroups[i]->Calc();
                mShadowIdx++;
            }
        }
    }

    void ShadowTextureManager::Draw(Screen *screen)
    {
        if (!IsActive() || mShadowIdx == 0) return;

        StateGX::ScopedDither dither(true);

        GXSetChanAmbColor(GX_COLOR0A0, DrawGX::scColorWhite);

        GXColor fog = {0, 0, 0, 255};
        GXSetFog(GX_FOG_NONE, fog, 0.0f, 1.0f, 0.0f, 1.0f);
        
        TextureBuffer *localGroups[GROUP_MAX];
        int firstGroupIdx = -1;
        int iVar15 = -1;
        for (int i = 0; i < GROUP_MAX; i++)
        {
            ShadowTexture *group = mGroups[i];
            localGroups[i] = NULL;

            if (group != NULL)
            {
                const bool b = ((group->SHORT_0x70 & 0x10) && ((group->SHORT_0x70 & 0x8) == 0));
                if (b)
                {
                    if ((group->SHORT_0x70 & 0x2) || (group->SHORT_0x70 & 0x4))
                    {
                        u16 w = group->getWidth();
                        u16 h = group->getHeight();

                        if (group->SHORT_0x70 & 0x4)
                        {
                            w <<= 1;
                            h <<= 1;
                        }
                        
                        localGroups[i] = TextureBuffer::alloc(w, h, GX_TF_I8);
                        group->SetCapTexture0(localGroups[i]);
                        group->SetCapTexture1(localGroups[i]);
                    }
                    
                    if (firstGroupIdx == -1) firstGroupIdx = i;
                    if (i > iVar15) iVar15 = i;
                }
            }
        }

        GXInvalidateTexAll();
        for (int i = 0; i < GROUP_MAX; i++)
        {
            ShadowTexture *group = mGroups[i];
            if (group != NULL)
            {
                const bool b = ((group->SHORT_0x70 & 0x10) && ((group->SHORT_0x70 & 0x8) == 0));
                if (b)
                {
                    group->Draw(screen, StateGX::getDefaultPixelFormat() == GX_PF_RGBA6_Z24,
                        i == firstGroupIdx, i == iVar15);
                }
            }
        }

        for (int i = 0; i < GROUP_MAX; i++)
        {
            if (localGroups[i] != NULL)
                localGroups[i]->free();
        }
    }
}
