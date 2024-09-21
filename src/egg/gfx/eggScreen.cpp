#include "eggScreen.h"
#include "eggStateGX.h"
#include "eggDrawGX.h"

#include <SC/scapi.h>

using namespace nw4r;

namespace EGG
{
    Screen::TVMode Screen::sTVMode;
    u16 Screen::sTVModeWidths[TV_MODE_MAX] = {
        600, // TV_MODE_4_3
        800  // TV_MODE_16_9
    };
    u16 Screen::sTVModeHeights[TV_MODE_MAX] = {
        480, // TV_MODE_4_3
        480  // TV_MODE_16_9
    };

    Screen* Screen::spRoot = NULL;

    Screen::ChangeTVModeFunc Screen::sChangeTVModeFunc = NULL;
    void* Screen::spChangeTVModeFuncInfo = NULL;
    Screen::TVModeRatio Screen::sTVModeRatios[Screen::TV_MODE_MAX];

    math::VEC2 Screen::sCanvasScale(1.0f, 1.0f);
    math::VEC2 Screen::sCanvasOffset(0.0f, 0.0f);

    void Screen::Initialize(const u16* maxX, const u16* maxY, Screen* userRoot)
    {
        #line 47
        EGG_ASSERT(maxX != NULL);
        EGG_ASSERT(maxY != NULL);

        sTVModeWidths[TV_MODE_4_3] = maxX[0];
        sTVModeHeights[TV_MODE_4_3] = maxY[0];

        sTVModeWidths[TV_MODE_16_9] = maxX[1];
        sTVModeHeights[TV_MODE_16_9] = maxY[1];

        static Screen defaultRoot;
        defaultRoot.SetProjectionType(PROJ_ORTHO);
        defaultRoot.SetCanvasMode(CANVASMODE_1);
        defaultRoot.SetNearZ(0.0f);
        defaultRoot.SetFarZ(1.0f);

        userRoot = (userRoot == NULL) ? &defaultRoot : userRoot;
        spRoot = userRoot;
        userRoot->SetParent(NULL);

        CalcRatio();
        SetTVMode(sTVMode); 
    }

    Screen::Screen() :
        Frustum(PROJ_PERSP, math::VEC2(sTVModeWidths[sTVMode], sTVModeHeights[sTVMode]),
            10.0f, 10000.0f, CANVASMODE_1)
    {
        mPosition.x = 0.0f;
        mPosition.y = 0.0f;
        SetParent(NULL);
        NullSub_0();
    }

    Screen::Screen(f32 x, f32 y, f32 w, f32 h,
                   const Screen* userRoot, CanvasMode canvasMode) :
        Frustum(PROJ_PERSP, math::VEC2(w, h), 10.0f, 10000.0f, canvasMode)
    {
        mPosition.x = x;
        mPosition.y = y;
        SetParent(userRoot);
        NullSub_0();
    }

    Screen::Screen(const Screen& other) :
        Frustum(other),
        mPosition(other.mPosition),
        mDataEfb(other.mDataEfb)
    {
        SetParent(other.mParent);
        NullSub_0();
    }


    // Debug stripped?
    // NOTE: This needs to NOT inline in the Screen ctors (see FillBufferGX)
    void Screen::NullSub_0() {}

    void Screen::SetProjectionGX() const
    {
        if (!(mFlags & 0x80))
        {
            f32 sx, sy, ox, oy;
            GetGlobalScaleOffset(&sx, &sy, &ox, &oy);

            SetGlobalScaleOffset(sCanvasScale.x, sCanvasScale.y,
                sCanvasOffset.x, sCanvasOffset.y);
            Frustum::SetProjectionGX();

            SetGlobalScaleOffset(sx, sy, ox, oy);
        }
        else
        {
            Frustum::SetProjectionGX();
        }

        SetViewGX();
    }

    void Screen::CopyToG3D(g3d::Camera cam) const
    {
        if (!(mFlags & 0x80))
        {
            f32 sx, sy, ox, oy;
            GetGlobalScaleOffset(&sx, &sy, &ox, &oy);

            SetGlobalScaleOffset(sCanvasScale.x, sCanvasScale.y,
                sCanvasOffset.x, sCanvasOffset.y);
            Frustum::CopyToG3D(cam);

            SetGlobalScaleOffset(sx, sy, ox, oy);
        }
        else
        {
            Frustum::CopyToG3D(cam);
        }

        SetViewG3D(cam);
    }

    void Screen::SetViewGX() const
    {
        const DataEfb& efb = GetDataEfb();

        StateGX::GXSetViewport_(efb.vp.x1, efb.vp.y1, efb.vp.x2, efb.vp.y2,
            efb.vp.z1, efb.vp.z2);
        StateGX::GXSetScissor_(efb.vp.x1, efb.vp.y1, efb.vp.x2, efb.vp.y2);
        StateGX::GXSetScissorBoxOffset_(efb.sc_ox, efb.sc_oy);
    }

    void Screen::SetViewG3D(nw4r::g3d::Camera cam) const
    {
        const DataEfb& efb = GetDataEfb();

        f32 x1, x2, y1, y2;
        f32 z1, z2;
        
        y2 = efb.vp.y2;
        x2 = efb.vp.x2;
        
        y1 = efb.vp.y1;
        x1 = efb.vp.x1;
        
        z2 = efb.vp.z2;
        z1 = efb.vp.z1;

        cam.SetViewport(x1, y1, x2, y2);
        cam.SetViewportZRange(z1, z2);
        cam.SetScissor(efb.vp.x1, efb.vp.y1, efb.vp.x2, efb.vp.y2);
        cam.SetScissorBoxOffset(efb.sc_ox, efb.sc_oy);
    }

    void Screen::CopyFromAnother(const Screen& other)
    {
        Frustum::CopyFromAnother(other);

        SetParent(other.mParent);
        mPosition = other.mPosition;
        mDataEfb = other.mDataEfb;
    }

    void Screen::GetPosSizeInEfb() const
    {
        const TVMode tvMode = (!(mFlags & 0x20)) ? sTVMode : TV_MODE_4_3;
        const TVModeRatio& tvRatio = sTVModeRatios[tvMode];
        
        f32* px = &mDataEfb.vp.x1;
        f32* py = &mDataEfb.vp.y1;
        GetGlobalPos(px, py);

        *px = sCanvasScale.x * *px;
        *py = sCanvasScale.y * *py;

        *px *= tvRatio.w_ratio;
        *py *= tvRatio.h_ratio;

        mDataEfb.sc_oy = 0;
        mDataEfb.sc_ox = 0;

        const f32 x = *px;
        if (x < 0.0f)
        {
            *px = 0.0f;

            const s32 lx = static_cast<s32>(-x);
            mDataEfb.sc_ox = lx - (lx & 0x1);
        }

        const f32 y = *py;
        if (y < 0.0f)
        {
            *py = 0.0f;

            const s32 ly = static_cast<s32>(-y);
            mDataEfb.sc_oy = ly - (ly & 0x1);
        }

        if (mFlags & 0x2)
        {
            *px -= static_cast<s32>(*px) & 0x1;
            *py -= static_cast<s32>(*py) & 0x1;
        }

        *px = static_cast<s32>(*px);
        *py = static_cast<s32>(*py);
        
        mDataEfb.vp.x2 = mSize.x;
        mDataEfb.vp.y2 = mSize.y;

        if (!(mFlags & 0x8))
        {
            mDataEfb.vp.x2 = mSize.x * tvRatio.w_ratio;
            mDataEfb.vp.y2 = mSize.y * tvRatio.h_ratio;
        }

        if (mFlags & 0x4)
        {
            mDataEfb.vp.x2 -= static_cast<s32>(mDataEfb.vp.x2) & 0x3;
            mDataEfb.vp.y2 -= static_cast<s32>(mDataEfb.vp.y2) & 0x3;
        }

        mDataEfb.vp.x2 = (mDataEfb.vp.x2 >= 0.0f) ? mDataEfb.vp.x2 : 0.0f;
        mDataEfb.vp.y2 = (mDataEfb.vp.y2 >= 0.0f) ? mDataEfb.vp.y2 : 0.0f;

        mDataEfb.vp.x2 = static_cast<s32>(mDataEfb.vp.x2);
        mDataEfb.vp.y2 = static_cast<s32>(mDataEfb.vp.y2);
    }

    const Screen::DataEfb& Screen::GetDataEfb() const
    {
        if (IsChangeEfb())
        {
            GetPosSizeInEfb();
            mDataEfb.vp.z1 = 0.0f;
            mDataEfb.vp.z2 = 1.0f;
            SetDirty(false);
        }

        return mDataEfb;
    }

    bool Screen::IsChangeEfb() const
    {
        if (mFlags & FLAG_DIRTY)
            return true;

        if (mParent != NULL)
            return mParent->IsChangeEfb();

        return false;
    }

    void Screen::CalcMatrixForDrawQuad(math::MTX34* mtx,
                                       f32 x, f32 y, f32 sx, f32 sy) const
    {
        PSMTXScale(*mtx, sx, sy, 1.0f);

        mtx->m[0][3] = x;
        mtx->m[2][3] = 0.0f;

        if (mCanvasMode == CANVASMODE_0)
            mtx->m[1][3] = y - sy;
        else
            mtx->m[1][3] = y;
    }

    // https://decomp.me/scratch/vufIs
    // 1. Bools for ClearEfb are not evaluated in the correct order.
    // 2. The NullSub_0 when constructing the clone must inline
    //    (even though the actual ctor must NOT inline it) 
    void Screen::FillBufferGX(u32 flags, GXColor color, u32 r6) const
    {
        #pragma unused(r6)

        if (flags != 0)
        {
            math::MTX34 drawMtx;
            Screen clone(*this);

            clone.SetCanvasMode(CANVASMODE_1);
            clone.SetNearZ(0.0f);
            clone.SetFarZ(1.0f);
            clone.SetProjectionType(PROJ_ORTHO);

            clone.SetProjectionGX();
            clone.CalcMatrixForDrawQuad(&drawMtx, 0.0f, 0.0f,
                mSize.x * mScale.x, mSize.y * mScale.y);

            DrawGX::ClearEfb(drawMtx, (flags & 1), (flags & 2), (flags & 4), color, true);
        }
    }

    // https://decomp.me/scratch/WmO2A
    // 1. Recursion is incorrect (lots of extra stack storage)
    // 2. Seems like -ipa file must be off, despite other functions
    //    in this file requiring it (see SetTVModeDefault)
    void Screen::GetGlobalPos(f32* ox, f32* oy) const
    {
        f32 px, py;
        const Screen* parent = GetParent();
        
        if (parent != NULL)
        {
            parent->GetGlobalPos(&px, &py);
            parent->ConvertToCanvasLU(mPosition.x,
                mPosition.y, ox, oy);
            
            *ox += px;
            *oy += py;
        }
        else
        {
            #line 485
            EGG_ASSERT(spRoot == NULL || ( spRoot != NULL && spRoot == this ));

            *ox = mPosition.x;
            *oy = mPosition.y;
        }
    }

    void Screen::SetTVMode(TVMode tvMode)
    {
        sTVMode = tvMode;

        if (spRoot != NULL)
        {
            spRoot->SetSizeX(GetSizeXMax());
            spRoot->SetSizeY(GetSizeYMax());
        }

        if (sChangeTVModeFunc != NULL)
            sChangeTVModeFunc(spChangeTVModeFuncInfo);
    }

    void Screen::SetTVModeDefault()
    {
        SetTVMode(SCGetAspectRatio() == SC_ASPECT_STD
            ? TV_MODE_4_3 : TV_MODE_16_9);
    }

    void Screen::CalcRatio()
    {
        #line 530
        EGG_ASSERT(GetSizeXMax() > 0);
        EGG_ASSERT(GetSizeYMax() > 0);

        sTVModeRatios[TV_MODE_4_3].w_ratio =
            static_cast<f32>(StateGX::getEfbWidth()) / static_cast<f32>(sTVModeWidths[TV_MODE_4_3]);
        sTVModeRatios[TV_MODE_4_3].h_ratio =
            static_cast<f32>(StateGX::getEfbHeight()) / static_cast<f32>(sTVModeHeights[TV_MODE_4_3]);

        sTVModeRatios[TV_MODE_16_9].w_ratio =
            static_cast<f32>(StateGX::getEfbWidth()) / static_cast<f32>(sTVModeWidths[TV_MODE_16_9]);
        sTVModeRatios[TV_MODE_16_9].h_ratio =
            static_cast<f32>(StateGX::getEfbHeight()) / static_cast<f32>(sTVModeHeights[TV_MODE_16_9]);
    }
}
