#ifndef EGG_GFX_FRUSTUM_H
#define EGG_GFX_FRUSTUM_H
#include "types_egg.h"
#include "eggVector.h"
#include "eggMatrix.h"
#include "eggAssert.h"
#include "g3d_camera.h"
#include "g3d_resanmscn.h"
#include "math_triangular.h"
#include <GX/GXTransform.h>

namespace EGG
{
    class Frustum
    {
    public:
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
        f32 mTanFovy;
        f32 mNearZ; // at 0x18
        f32 mFarZ; // at 0x1C
        nw4r::math::VEC2 mOffset; // at 0x20
        nw4r::math::VEC3 mScale; // at 0x28
        u16 mFlags; // at 0x34
        
    public:
        Frustum(ProjectionType, const nw4r::math::VEC2&, f32, f32, CanvasMode);
        Frustum(Frustum&);
        
        virtual ~Frustum() {} // at 0x8
        virtual void SetProjectionGX(); // at 0xC
        virtual void CopyToG3D(nw4r::g3d::Camera); // at 0x10

        void CopyFromAnother(Frustum&);

        void GetViewToScreen(nw4r::math::VEC3 *, const nw4r::math::VEC3&);
        void GetScreenToView(nw4r::math::VEC3 *, const nw4r::math::VEC3&);
        void GetScreenToView(nw4r::math::VEC3 *, const nw4r::math::VEC2&);

        void LoadScnCamera(nw4r::g3d::ResAnmScn, u8, f32, u32);

        ProjectionType GetProjectionType() const { return mProjType; }
        void SetProjectionType(ProjectionType type) { mProjType = type; }
        CanvasMode GetCanvasMode() const { return mCanvasMode; }
        void SetCanvasMode(CanvasMode mode) { mCanvasMode = mode; }

        void SetSizeX(f32 sizeX)
        {
            #line 117
            EGG_ASSERT(sizeX >= 0.f);
            mFlags |= 0x1;
            mSize.mCoords.x = sizeX;
        }

        void SetSizeY(f32 sizeY)
        {
            #line 123
            EGG_ASSERT(sizeY >= 0.f);
            mFlags |= 0x1;
            mSize.mCoords.y = sizeY;
        }

        void SetFovy(f32 fovy)
        {
            if (mFovY == fovy) return;
          
            #line 391
            EGG_ASSERT(0.f < fovy && fovy < 180.f);
            mFovY = fovy;

            f32 sin, cos;
            nw4r::math::SinCosDeg(&sin, &cos, fovy / 2.0f);
            mTanFovy = sin / cos;
        }

        void SetNearZ(f32 nearZ) { mNearZ = nearZ; }
        f32 GetNearZ() const { return mNearZ; }
        void SetFarZ(f32 farZ) { mFarZ = farZ; }
        f32 GetFarZ() const { return mFarZ; }

        void SetScale(const nw4r::math::VEC3& scale) { mScale = scale; }
        void SetOffset(const nw4r::math::VEC2& offset) { mOffset = offset; }
        void SetFlag(u32 flag) { mFlags |= flag; }

    private:
        void SetProjectionPerspectiveGX_();
        void SetProjectionOrthographicGX_();

        void CopyToG3D_Perspective_(nw4r::g3d::Camera);
        void CopyToG3D_Orthographic_(nw4r::g3d::Camera);

        void CalcMtxPerspective_(nw4r::math::MTX44 *);

        void GetOrthographicParam_(nw4r::math::MTX44 *);
        void GetOrthographicParam_(f32 *);
        void GetPerspectiveParam_(f32 *);
        void GetOrthographicParam_(f32 *, f32 *, f32 *, f32 *);

    private:
        static const nw4r::math::VEC2 sGlobalScale;
        static const nw4r::math::VEC2 sGlobalOffset;
    };
}

#endif