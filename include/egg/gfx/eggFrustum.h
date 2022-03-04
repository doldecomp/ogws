#ifndef EGG_GFX_FRUSTUM_H
#define EGG_GFX_FRUSTUM_H
#include "types_egg.h"
#include "eggVector.h"
#include "eggMatrix.h"
#include "g3d_camera.h"
#include <GX/GXTransform.h>

namespace EGG
{
    class eggFrustum
    {
    public:
        enum ProjectionType
        {
            PROJ_ORTHO,
            PROJ_PERSP
        };

        enum CanvasMode
        {

        };

    private:
        u32 mProjection; // at 0x0
        CanvasMode mCanvas; // at 0x4
        Vector2f mScale; // at 0x8
        Matrix33f mMatrix; // at 0x10
        u16 mFlags; // at 0x34
        
    public:
        eggFrustum(ProjectionType, const Vector2f&, f32, f32, CanvasMode);
        eggFrustum(eggFrustum&);
        
        virtual ~eggFrustum() {} // at 0x8
        virtual void SetProjectionGX() const; // at 0xC
        virtual void CopyToG3D(nw4r::g3d::Camera) const; // at 0x10

        Matrix33f& getMatrix() { return mMatrix; }

        // void g_mtx_projection(Matrix44f *) const;
        // void g_camera_projection();
        void GetViewToScreen(Vector3f *, const Vector3f&) const;
        void GetScreenToView(Vector3f *, const Vector3f&) const;
        void GetScreenToView(Vector3f *, const Vector2f&) const;
        void CopyFromAnother(eggFrustum&);

    private:
        void SetProjectionOrthographicGX_() const;
        void SetProjectionPerspectiveGX_() const;

        void CopyToG3D_Orthographic_(nw4r::g3d::Camera) const;
        void CopyToG3D_Perspective_(nw4r::g3d::Camera) const;

        void CalcMtxOrthographic_(Matrix44f *) const;
        void CalcMtxPerspective_(Matrix44f *) const;

        void GetOrthographicParam_(f32 *, f32 *, f32 *, f32 *) const;

    private:
        static const Vector2f sScale, sOffset;
    };
}

#endif