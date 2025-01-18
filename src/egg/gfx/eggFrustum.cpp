#pragma ipa file

#include "eggFrustum.h"
#include "eggAssert.h"
#include "eggStateGX.h"
#include "eggGXUtility.h"

namespace EGG
{
    using namespace nw4r;

    Frustum::Frustum(ProjectionType proj, const math::VEC2& size,
        f32 nearZ, f32 farZ, CanvasMode canvas) :
        mProjType(proj),
        mCanvasMode(canvas),
        mSize(size),
        mFovY(45.0f),
        mTanFovY(0.41421357f),
        mNearZ(nearZ),
        mFarZ(farZ),
        mOffset(0.0f, 0.0f),
        mScale(1.0f, 1.0f, 1.0f),
        mFlags(FLAG_DIRTY)
    {
    }

    Frustum::Frustum(const Frustum& other) :
        mProjType(other.mProjType),
        mCanvasMode(other.mCanvasMode),
        mSize(other.mSize),
        mFovY(other.mFovY),
        mTanFovY(other.mTanFovY),
        mNearZ(other.mNearZ),
        mFarZ(other.mFarZ),
        mOffset(other.mOffset),
        mScale(other.mScale),
        mFlags(other.mFlags)
    {
    }

    void Frustum::SetProjectionGX() const
    {
        if (mProjType == PROJ_ORTHO)
        {
            SetProjectionOrthographicGX_();
        }
        else
        {
            SetProjectionPerspectiveGX_();
        }
    }

    void Frustum::CopyToG3D(g3d::Camera cam) const
    {
        if (mProjType == PROJ_ORTHO)
        {
            CopyToG3D_Orthographic_(cam);
        }
        else
        {
            CopyToG3D_Perspective_(cam);
        }
    }

    void Frustum::SetProjectionPerspectiveGX_() const
    {
        f32 params[7];
        GetPerspectiveParam_(params);
        StateGX::GXSetProjectionv_(params);
    }

    void Frustum::SetProjectionOrthographicGX_() const
    {
        math::MTX44 mtx;
        GetOrthographicParam_(&mtx);
        StateGX::GXSetProjection_(mtx, 1);
    }

    void Frustum::CopyToG3D_Perspective_(g3d::Camera cam) const
    {
        math::MTX44 mtx;
        cam.SetPerspective(mFovY, mSize.x / mSize.y, mNearZ, mFarZ);
        CalcMtxPerspective_(&mtx);
        cam.SetProjectionMtxDirectly(&mtx);
    }

    void Frustum::CopyToG3D_Orthographic_(g3d::Camera cam) const
    {
        f32 t, b, l, r;
        GetOrthographicParam_(&t, &b, &l, &r);
        cam.SetOrtho(t, b, l, r, mNearZ, mFarZ);
    }

    void Frustum::CalcMtxPerspective_(math::MTX44 *out) const
    {
        f32 params[7];
        GetPerspectiveParam_(params);

        out->m[0][3] = 0.0f;
        out->m[0][1] = 0.0f;
        out->m[0][0] = params[1];
        out->m[0][2] = params[2];

        out->m[1][3] = 0.0f;
        out->m[1][0] = 0.0f;
        out->m[1][1] = params[3];
        out->m[1][2] = params[4];

        out->m[2][1] = 0.0f;
        out->m[2][0] = 0.0f;
        out->m[2][2] = params[5];
        out->m[2][3] = params[6];

        out->m[3][3] = 0.0f;
        out->m[3][1] = 0.0f;
        out->m[3][0] = 0.0f;
        out->m[3][2] = -1.0f;
    }

    void Frustum::GetOrthographicParam_(math::MTX44 *pMtx) const
    {
        #line 267
        EGG_ASSERT(pMtx);

        f32 t, b, l, r;
        GetOrthographicParam_(&t, &b, &l, &r);
        C_MTXOrtho(*pMtx, t, b, l, r, mNearZ, mFarZ);
    }

    void Frustum::LoadScnCamera(g3d::ResAnmScn scn, u8 id, f32 f1, u32 flags)
    {
        if (!scn.IsValid()) return;
        
        g3d::ResAnmCamera cam = scn.GetResAnmCameraByRefNumber(id);    
        #line 296
        EGG_ASSERT_MSG(cam.IsValid(), "Illegal camera number.");
    
        g3d::CameraAnmResult result;
        cam.GetAnmResult(&result, f1);

        switch(result.projType)
        {
            case GX_PERSPECTIVE:
                mProjType = PROJ_PERSP;
                if ((flags & 0x1) == 0)
                {
                    SetFovY(result.FLOAT_0x30);
                }
                if ((flags & 0x2) == 0)
                {
                    SetSizeX(mSize.y * result.FLOAT_0x14);                    
                    mScale = math::VEC3(1.0f, 1.0f, 1.0f);
                }
                break;
            case GX_ORTHOGRAPHIC:
                mProjType = PROJ_ORTHO;
                if ((flags & 0x2) == 0)
                {
                    if (mCanvasMode != CANVASMODE_0)
                    {
                        mCanvasMode = CANVASMODE_0;
                        mFlags |= 0x1;
                    }

                    SetSizeY(result.FLOAT_0x30);
                    SetSizeX(mSize.y * result.FLOAT_0x14);
                    mScale = math::VEC3(1.0f, 1.0f, 1.0f);
                    mOffset = math::VEC2(0.0f, 0.0f);
                }
                break;
            default:
                #line 331
                EGG_ASSERT_MSG(false, "Unknown GXProjectionType");
                break;
        }

        if ((flags & 0x4) == 0)
        {
            mNearZ = result.FLOAT_0x18;
            mFarZ = result.FLOAT_0x1C;
        }
    }

    void Frustum::GetPerspectiveParam_(f32 *p) const
    {
        #line 267
        EGG_ASSERT(p != NULL);

        const f32 inv = 1.0f / mTanFovY;
        p[0] = 0.0f;
        p[1] = (inv / (mSize.x / mSize.y)) / mScale.x;
        p[2] = mOffset.x / (0.5f * mSize.x);
        p[3] = inv / mScale.y;
        p[4] = mOffset.y / (0.5f * mSize.y);
        
        const f32 z = -mNearZ / (mFarZ - mNearZ);
        p[5] = z;
        p[6] = mFarZ * z;

        GXUtility::setScaleOffsetPerspective(p, sGlobalScale.x, sGlobalScale.y,
            sGlobalOffset.x / (0.5f * mSize.x),
            sGlobalOffset.y / (0.5f * mSize.y));
    }

    void Frustum::GetOrthographicParam_(f32 *pT, f32 *pB, f32 *pL, f32 *pR) const
    {
        #line 387
        EGG_ASSERT(pT);
        EGG_ASSERT(pB);
        EGG_ASSERT(pL);
        EGG_ASSERT(pR);

        if (mCanvasMode == CANVASMODE_0)
        {
            const math::VEC2 adjScale(
                mScale.x * sGlobalScale.x,
                mScale.y * sGlobalScale.y
            );
            
            *pT = adjScale.y * ((0.5f * mSize.y) + (mOffset.y + sGlobalOffset.y));
            *pB = adjScale.y * ((-0.5f * mSize.y) + (mOffset.y + sGlobalOffset.y));
            *pL = adjScale.x * ((-0.5f * mSize.x) + (mOffset.x + sGlobalOffset.x));
            *pR = adjScale.x * ((0.5f * mSize.x) + (mOffset.x + sGlobalOffset.x));
        }
        else if (mCanvasMode == CANVASMODE_1)
        {
            *pT = mOffset.y + sGlobalOffset.y;
            const f32 new_var = mOffset.y + sGlobalOffset.y;
            *pB = new_var + -1.0f * mSize.y * mScale.y;
            *pL = mOffset.x + sGlobalOffset.x;
            *pR = mOffset.x + sGlobalOffset.x + mSize.x * mScale.x;
            
            *pT *= -sGlobalScale.y;
            *pB *= -sGlobalScale.y;
            *pL *= sGlobalScale.x;
            *pR *= sGlobalScale.x;

            const f32 x = -(sGlobalScale.x - 1.0f) * (0.5f * mSize.x);
            const f32 y = -(sGlobalScale.y - 1.0f) * (0.5f * mSize.y);
            *pT += y;
            *pB += y;
            *pL += x;
            *pR += x;
        }
    }

    void Frustum::CopyFromAnother(const Frustum& other)
    {
        *this = other;
    }

    // https://decomp.me/scratch/XO2Aa
    void Frustum::GetViewToScreen(nw4r::math::VEC3 *pScreenPos, const nw4r::math::VEC3& viewPos) const
    {
    }

    // https://decomp.me/scratch/r9gD9
    void Frustum::GetScreenToView(nw4r::math::VEC3 *pViewPos, const nw4r::math::VEC3& screenPos) const
    {
    }

    void Frustum::GetScreenToView(math::VEC3 *pPosView, const math::VEC2& screenPos) const
    {
        #line 568
        EGG_ASSERT(pPosView);

        f32 screenX, screenY;
        switch(mProjType)
        {
            case PROJ_PERSP:
                screenY = screenPos.y;
                screenX = screenPos.x;
                
                math::VEC2 adjustedPos;
                if (mCanvasMode == CANVASMODE_1)
                {
                    const f32 x = -(mSize.x / 2.0f - screenX);
                    const f32 y = -(mSize.y / 2.0f - screenY);
                    
                    adjustedPos.x = x;
                    adjustedPos.y = -y;
                }
                else if (mCanvasMode == CANVASMODE_0)
                {
                    adjustedPos.x = screenX;
                    adjustedPos.y = screenY;
                }

                pPosView->x = adjustedPos.x;
                pPosView->y = adjustedPos.y;
                pPosView->z = -(mSize.y / 2.0f) / mTanFovY;
                break;
            case PROJ_ORTHO:
                screenY = screenPos.y;
                screenX = screenPos.x;
                
                pPosView->x = screenX / mScale.x;
                pPosView->y = screenY / mScale.y;
                pPosView->z = mNearZ;
                break;
        }
    }

    math::VEC2 Frustum::sGlobalScale(1.0f, 1.0f);
    math::VEC2 Frustum::sGlobalOffset(0.0f, 0.0f);
}
