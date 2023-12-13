#ifndef EGG_GFX_FRUSTUM_H
#define EGG_GFX_FRUSTUM_H
#include "types_egg.h"
#include "eggVector.h"
#include "eggMatrix.h"
#include "eggAssert.h"
#include "g3d_camera.h"
#include "g3d_resanmscn.h"
#include "math_triangular.h"
#include <revolution/GX.h>

namespace EGG
{
    class Frustum
    {
    public:
        enum Flag
        {
            FLAG_DIRTY = (1 << 0)
        };

        enum ProjectionType
        {
            PROJ_ORTHO,
            PROJ_PERSP
        };

        enum CanvasMode
        {
            CANVASMODE_0,
            CANVASMODE_1,
        };

    protected:
        ProjectionType mProjType; // at 0x0
        CanvasMode mCanvasMode; // at 0x4
        nw4r::math::VEC2 mSize; // at 0x8
        f32 mFovY; // at 0x10
        f32 mTanFovY; // at 0x14
        f32 mNearZ; // at 0x18
        f32 mFarZ; // at 0x1C
        nw4r::math::VEC2 mOffset; // at 0x20
        nw4r::math::VEC3 mScale; // at 0x28
        mutable u16 mFlags; // at 0x34
        
    public:
        static void GetGlobalScaleOffset(f32* sx, f32* sy, f32* ox, f32* oy)
        {
            *sx = sGlobalScale.x;
            *sy = sGlobalScale.y;
            *ox = sGlobalOffset.x;
            *oy = sGlobalOffset.y;
        }

        static void SetGlobalScaleOffset(f32 sx, f32 sy, f32 ox, f32 oy)
        {
            sGlobalScale.x = sx;
            sGlobalScale.y = sy;
            sGlobalOffset.x = ox;
            sGlobalOffset.y = oy;
        }

        Frustum(ProjectionType, const nw4r::math::VEC2&, f32, f32, CanvasMode);
        Frustum(const Frustum&);
        
        virtual ~Frustum() {} // at 0x8
        virtual void SetProjectionGX() const; // at 0xC
        virtual void CopyToG3D(nw4r::g3d::Camera) const; // at 0x10

        void CopyFromAnother(const Frustum&);

        void GetViewToScreen(nw4r::math::VEC3 *, const nw4r::math::VEC3&) const;
        void GetScreenToView(nw4r::math::VEC3 *, const nw4r::math::VEC3&) const;
        void GetScreenToView(nw4r::math::VEC3 *, const nw4r::math::VEC2&) const;

        void LoadScnCamera(nw4r::g3d::ResAnmScn, u8, f32, u32);

        void SetDirty(bool dirty) const
        {
            if (dirty)
                mFlags |= FLAG_DIRTY;
            else
                mFlags &= ~FLAG_DIRTY;
        }

        void ConvertToCanvasLU(f32 ix, f32 iy, f32* ox, f32* oy) const
        {
            if (mCanvasMode == CANVASMODE_1)
            {
                *ox = ix;
                *oy = iy;
            }
            else if (mCanvasMode == CANVASMODE_0)
            {
                ConvertToCanvasLU_Inline_0(ix, iy, ox, oy);
            }
        }

        void ConvertToCanvasLU_Inline_0(f32 ix, f32 iy, f32* ox, f32* oy) const
        {
            const f32 sx = GetSize().x;
            *ox = ix + (sx / 2.0f);

            const f32 sy = GetSize().y;
            *oy = -(iy - (sy / 2.0f));
        }        

        ProjectionType GetProjectionType() const { return mProjType; }
        void SetProjectionType(ProjectionType type) { mProjType = type; }

        CanvasMode GetCanvasMode() const { return mCanvasMode; }
        void SetCanvasMode(CanvasMode mode)
        {
            if (mCanvasMode != mode)
            {
                SetDirty(true);
                mCanvasMode = mode;
            }
        }

        const nw4r::math::VEC2& GetSize() const { return mSize; }

        u16 GetWidth() const { return mSize.x; }
        f32 GetSizeX() const { return mSize.x; }
        void SetSizeX(f32 sizeX)
        {
            #line 117
            EGG_ASSERT(sizeX >= 0.f);
            SetDirty(true);
            mSize.x = sizeX;
        }

        u16 GetHeight() const { return mSize.y; }
        f32 GetSizeY() const { return mSize.y; }
        void SetSizeY(f32 sizeY)
        {
            #line 123
            EGG_ASSERT(sizeY >= 0.f);
            SetDirty(true);
            mSize.y = sizeY;
        }

        void SetFovY(f32 fovy)
        {
            if (mFovY == fovy) return;
          
            #line 391
            EGG_ASSERT(0.f < fovy && fovy < 180.f);
            mFovY = fovy;

            f32 sin, cos;
            nw4r::math::SinCosDeg(&sin, &cos, fovy / 2.0f);
            mTanFovY = sin / cos;
        }

        void SetNearZ(f32 nearZ) { mNearZ = nearZ; }
        f32 GetNearZ() const { return mNearZ; }

        void SetFarZ(f32 farZ) { mFarZ = farZ; }
        f32 GetFarZ() const { return mFarZ; }

        void SetScale(const nw4r::math::VEC3& scale) { mScale = scale; }
        void SetOffset(const nw4r::math::VEC2& offset) { mOffset = offset; }

        void SetFlag(u32 flag) { mFlags |= flag; }

    private:
        void SetProjectionPerspectiveGX_() const;
        void SetProjectionOrthographicGX_() const;

        void CopyToG3D_Perspective_(nw4r::g3d::Camera) const;
        void CopyToG3D_Orthographic_(nw4r::g3d::Camera) const;

        void CalcMtxPerspective_(nw4r::math::MTX44 *) const;

        void GetOrthographicParam_(nw4r::math::MTX44 *) const;
        void GetOrthographicParam_(f32 *) const;
        void GetPerspectiveParam_(f32 *) const;
        void GetOrthographicParam_(f32 *, f32 *, f32 *, f32 *) const;

    private:
        static nw4r::math::VEC2 sGlobalScale;
        static nw4r::math::VEC2 sGlobalOffset;
    };
}

#endif