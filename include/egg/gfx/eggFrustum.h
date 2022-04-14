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

    private:
        u32 mProjection; // at 0x0
        CanvasMode mCanvas; // at 0x4
        Vector2f mScale; // at 0x8
        Matrix33f mMatrix; // at 0x10
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

        void setProjectionType(ProjectionType type) { mProjection = type; }

        CanvasMode getCanvasMode() const { return mCanvas; }
        void setCanvasMode(CanvasMode mode) { mCanvas = mode; }

        Matrix33f& getMatrix() { return mMatrix; }
        
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