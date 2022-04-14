#ifndef EGG_GFX_FRUSTUM_H
#define EGG_GFX_FRUSTUM_H
#include "types_egg.h"
#include "eggVector.h"
#include "eggMatrix.h"
#include "g3d_camera.h"
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
        f32 FLOAT_0x14;
        f32 mNearZ; // at 0x18
        f32 mFarZ; // at 0x1C
        nw4r::math::VEC2 mOffset; // at 0x20
        nw4r::math::VEC3 mScale; // at 0x28
        u16 mFlags; // at 0x34
        
    public:
        Frustum(ProjectionType, const nw4r::math::VEC2&, f32, f32, CanvasMode);
        Frustum(Frustum&);
        
        virtual ~Frustum() {} // at 0x8
        virtual void SetProjectionGX() const; // at 0xC
        virtual void CopyToG3D(nw4r::g3d::Camera) const; // at 0x10

        void CopyFromAnother(Frustum&);

        void GetViewToScreen(nw4r::math::VEC3 *, const nw4r::math::VEC3&) const;
        void GetScreenToView(nw4r::math::VEC3 *, const nw4r::math::VEC3&) const;
        void GetScreenToView(nw4r::math::VEC3 *, const nw4r::math::VEC2&) const;

        UNKTYPE FUN_800a0b90(UNKTYPE);

        ProjectionType getProjectionType() const { return mProjType; }
        void setProjectionType(ProjectionType type) { mProjType = type; }
        CanvasMode getCanvasMode() const { return mCanvasMode; }
        void setCanvasMode(CanvasMode mode) { mCanvasMode = mode; }

        void setNearZ(f32 nearZ) { mNearZ = nearZ; }
        f32 getNearZ() const { return mNearZ; }
        void setFarZ(f32 farZ) { mFarZ = farZ; }
        f32 getFarZ() const { return mFarZ; }

        void setScale(const nw4r::math::VEC3& scale) { mScale = scale; }
        void setOffset(const nw4r::math::VEC2& offset) { mOffset = offset; }
        void setFlag(u32 flag) { mFlags |= flag; }

    private:
        void SetProjectionPerspectiveGX_() const;
        void SetProjectionOrthographicGX_() const;

        void CopyToG3D_Perspective_(nw4r::g3d::Camera) const;
        void CopyToG3D_Orthographic_(nw4r::g3d::Camera) const;

        void CalcMtxPerspective_(nw4r::math::MTX44 *) const;

        void GetOrthographicParam_(f32 *) const;
        void GetPerspectiveParam_(f32 *) const;
        void GetOrthographicParam_(f32 *, f32 *, f32 *, f32 *) const;

    private:
        static const Vector2f sGlobalScale;
        static const Vector2f sGlobalOffset;
    };
}

#endif