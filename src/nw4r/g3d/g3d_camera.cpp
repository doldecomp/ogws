#include "g3d_camera.h"
#include "g3d_state.h"
#include "math_types.h"
#include "math_triangular.h"
#include <revolution/MTX.h>
#include <revolution/GX.h>

namespace nw4r
{
    namespace g3d
    {
        Camera::Camera(CameraData * pCamData) : mCamData(pCamData) {}

        void Camera::Init()
        {
            GXRenderModeObj& rRenderMode = G3DState::GetRenderModeObj();
            Init(rRenderMode.fbWidth, rRenderMode.efbHeight, rRenderMode.fbWidth,
                rRenderMode.xfbHeight, rRenderMode.viWidth, rRenderMode.viHeight);
        }

        void Camera::Init(u16 r4, u16 r5, u16 r6, u16 r7, u16 r8, u16 r9)
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                rCamData.mFlags = 0x21;

                rCamData.mPos.x = 0.0f;
                rCamData.mPos.y = 0.0f;
                rCamData.mPos.z = 15.0f;

                rCamData.VEC3_0x80.x = 0.0f;
                rCamData.VEC3_0x80.y = 1.0f;
                rCamData.VEC3_0x80.z = 0.0f;

                rCamData.VEC3_0x8C.x = 0.0f;
                rCamData.VEC3_0x8C.y = 0.0f;
                rCamData.VEC3_0x8C.z = 0.0f;

                rCamData.VEC3_0x98.x = 0.0f;
                rCamData.VEC3_0x98.y = 0.0f;
                rCamData.VEC3_0x98.z = 0.0f;

                rCamData.FLOAT_0xA4 = 0.0f;
                rCamData.INT_0xA8 = 0;
                rCamData.FLOAT_0xAC = 60.0f;
                rCamData.FLOAT_0xB0 = (4.0f / 3.0f);
                rCamData.FLOAT_0xB4 = 0.1f;
                rCamData.FLOAT_0xB8 = 1000.f;
                rCamData.FLOAT_0xBC = 0.0f;
                rCamData.FLOAT_0xC0 = (float)r9;
                rCamData.FLOAT_0xC4 = 0.0f;
                rCamData.FLOAT_0xC8 = (float)r8;
                rCamData.FLOAT_0xCC = 0.5f;
                rCamData.FLOAT_0xD0 = 0.5f;
                rCamData.FLOAT_0xD4 = 0.5f;
                rCamData.FLOAT_0xD8 = 0.5f;
                rCamData.FLOAT_0xDC = 0.0f;
                rCamData.FLOAT_0xE0 = 0.0f;
                rCamData.FLOAT_0xE4 = (float)r6;
                rCamData.FLOAT_0xE8 = (float)r7;
                rCamData.FLOAT_0xEC = 0.0;
                rCamData.FLOAT_0xF0 = 1.0f;
                rCamData.INT_0xF4 = 0;
                rCamData.INT_0xF8 = 0;
                rCamData.INT_0xFC = r4;
                rCamData.INT_0x100 = r5;
                rCamData.INT_0x104 = 0;
                rCamData.INT_0x108 = 0;
            }
        }

        void Camera::SetPosition(f32 x, f32 y, f32 z)
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                rCamData.mPos.x = x;
                rCamData.mPos.y = y;
                rCamData.mPos.z = z;

                rCamData.mFlags &= ~0x8;
            }
        }

        void Camera::SetPosition(const math::VEC3& rPos)
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                rCamData.mPos = rPos;
                rCamData.mFlags &= ~0x8;
            }
        }

        void Camera::SetPosture(const PostureInfo& rPosture)
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                switch (rPosture.INT_0x0)
                {
                    case 0:
                        if (rCamData.mFlags & 0x1)
                        {
                            bool b = (rPosture.VEC3_0x04 != rCamData.VEC3_0x80);
                            if (!b)
                            {
                                b = (rPosture.VEC3_0x10 != rCamData.VEC3_0x8C);
                                if (!b) return;
                            }
                        }
                        rCamData.mFlags &= ~0x7;
                        rCamData.mFlags |= 0x1;
                        rCamData.VEC3_0x80 = rPosture.VEC3_0x04;
                        rCamData.VEC3_0x8C = rPosture.VEC3_0x10;
                        rCamData.mFlags &= ~0x8;
                        break;

                    case 1:
                        if (rCamData.mFlags & 0x2)
                        {
                            bool b = (rPosture.VEC3_0x1C != rCamData.VEC3_0x98);
                            if (!b) return;
                        }
                        rCamData.mFlags &= ~0x7;
                        rCamData.mFlags |= 0x2;
                        rCamData.VEC3_0x98 = rPosture.VEC3_0x1C;
                        rCamData.mFlags &= ~0x8;
                        break;

                    case 2:
                        if (rCamData.mFlags & 0x4)
                        {
                            bool b = (rPosture.VEC3_0x10 != rCamData.VEC3_0x8C);
                            if (!b && rPosture.FLOAT_0x28 == rCamData.FLOAT_0xA4) return;
                        }
                        rCamData.mFlags &= ~0x7;
                        rCamData.mFlags |= 0x4;
                        rCamData.VEC3_0x8C = rPosture.VEC3_0x10;
                        rCamData.FLOAT_0xA4 = rPosture.FLOAT_0x28;
                        rCamData.mFlags &= ~0x8;
                        break;

                    default:
                        break;
                }
            }
        }

        void Camera::SetCameraMtxDirectly(const math::MTX34& rMtx)
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                math::MTX34Copy(&rCamData.mCamMtx, &rMtx);
                rCamData.mFlags |= 0x8;
            }
        }

        void Camera::SetPerspective(f32 f1, f32 f2, f32 f3, f32 f4)
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                rCamData.INT_0xA8 = 0;

                rCamData.FLOAT_0xAC = f1;
                rCamData.FLOAT_0xB0 = f2;
                rCamData.FLOAT_0xB4 = f3;
                rCamData.FLOAT_0xB8 = f4;
                
                rCamData.mFlags &= ~0xF0;
                rCamData.mFlags |= 0x20;
            }
        }

        void Camera::SetOrtho(f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6)
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                rCamData.INT_0xA8 = 1;

                rCamData.FLOAT_0xBC = f1;
                rCamData.FLOAT_0xC0 = f2;
                rCamData.FLOAT_0xC4 = f3;
                rCamData.FLOAT_0xC8 = f4;
                rCamData.FLOAT_0xB4 = f5;
                rCamData.FLOAT_0xB8 = f6;

                rCamData.mFlags &= ~0xF0;
                rCamData.mFlags |= 0x40;
            }
        }
        
        void Camera::SetProjectionMtxDirectly(const math::MTX44 *pMtx)
        {
            if (pMtx)
            {
                CameraData& rCamData = mCamData.ref();
                
                if (mCamData.IsValid())
                {
                    math::MTX44Copy(&rCamData.mProjMtx, pMtx);
                    rCamData.mFlags |= 0x80;
                }
            }
        }

        void Camera::SetScissor(u32 r4, u32 r5, u32 r6, u32 r7)
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                rCamData.INT_0xF4 = r4;
                rCamData.INT_0xF8 = r5;
                rCamData.INT_0xFC = r6;
                rCamData.INT_0x100 = r7;
            }
        }

        void Camera::SetScissorBoxOffset(s32 x, s32 y)
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                rCamData.INT_0x104 = x;
                rCamData.INT_0x108 = y;
            }
        }

        void Camera::SetViewport(f32 f1, f32 f2, f32 f3, f32 f4)
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                rCamData.FLOAT_0xDC = f1;
                rCamData.FLOAT_0xE0 = f2;
                rCamData.FLOAT_0xE4 = f3;
                rCamData.FLOAT_0xE8 = f4;

                // inlined
                SetScissor((u32)f1, (u32)f2, (u32)f3, (u32)f4);
            }
        }

        void Camera::SetViewportZRange(f32 f1, f32 f2)
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                rCamData.FLOAT_0xEC = f1;
                rCamData.FLOAT_0xF0 = f2;
            }
        }

        void Camera::GetViewport(f32 *r4, f32 *r5, f32 *r6, f32 *r7, f32 *r8, f32 *r9) const
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                if (r4) *r4 = rCamData.FLOAT_0xDC;
                if (r5) *r5 = rCamData.FLOAT_0xE0;
                if (r6) *r6 = rCamData.FLOAT_0xE4;
                if (r7) *r7 = rCamData.FLOAT_0xE8;
                if (r8) *r8 = rCamData.FLOAT_0xEC;
                if (r9) *r9 = rCamData.FLOAT_0xF0;
            }
        }

        void Camera::GetCameraMtx(math::MTX34 *pOutMtx) const
        {
            if (pOutMtx)
            {
                CameraData& rCamData = mCamData.ref();

                if (mCamData.IsValid())
                {
                    if ((rCamData.mFlags & 0x8) == 0)
                    {
                        UpdateCameraMtx();
                    }
                    
                    math::MTX34Copy(pOutMtx, &rCamData.mCamMtx);
                }
            }
        }

        void Camera::GetProjectionMtx(math::MTX44 *pOutMtx) const
        {
            if (pOutMtx)
            {
                const CameraData& rCamData = mCamData.ref();

                if (mCamData.IsValid())
                {
                    if ((rCamData.mFlags & 0x80) == 0)
                    {
                        UpdateProjectionMtx();
                    }

                    math::MTX44Copy(pOutMtx, &rCamData.mProjMtx);
                }
            }
        }

        void Camera::GetProjectionTexMtx(math::MTX34 *pOutMtx) const
        {
            if (pOutMtx)
            {
                CameraData& rCamData = mCamData.ref();

                if (mCamData.IsValid())
                {
                    if ((rCamData.mFlags & 0x40) != 0)
                    {
                        C_MTXLightOrtho(*pOutMtx, rCamData.FLOAT_0xBC, rCamData.FLOAT_0xC0, rCamData.FLOAT_0xC4,
                            rCamData.FLOAT_0xC8, rCamData.FLOAT_0xCC, -(rCamData.FLOAT_0xD0),
                            rCamData.FLOAT_0xD4, rCamData.FLOAT_0xD8);
                    }
                    else
                    {
                        if ((rCamData.mFlags & 0x10) != 0)
                        {
                            C_MTXLightFrustum(*pOutMtx, rCamData.FLOAT_0xBC, rCamData.FLOAT_0xC0, rCamData.FLOAT_0xC4,
                                rCamData.FLOAT_0xC8, rCamData.FLOAT_0xB4, rCamData.FLOAT_0xCC,
                                -(rCamData.FLOAT_0xD0), rCamData.FLOAT_0xD4, rCamData.FLOAT_0xD8);
                        }
                        else
                        {
                            C_MTXLightPerspective(*pOutMtx, rCamData.FLOAT_0xAC, rCamData.FLOAT_0xB0, rCamData.FLOAT_0xCC,
                                -(rCamData.FLOAT_0xD0), rCamData.FLOAT_0xD4, rCamData.FLOAT_0xD8);
                        }
                    }
                }
            }
        }

        void Camera::GetEnvironmentTexMtx(math::MTX34 *pOutMtx) const
        {
            if (pOutMtx)
            {
                CameraData& rCamData = mCamData.ref();

                if (mCamData.IsValid())
                {
                    math::MTX34Identity(pOutMtx);
                    pOutMtx->m[0][0] = rCamData.FLOAT_0xCC;
                    pOutMtx->m[0][3] = rCamData.FLOAT_0xD4;
                    pOutMtx->m[1][1] = -(rCamData.FLOAT_0xD0);
                    pOutMtx->m[1][3] = rCamData.FLOAT_0xD8;
                    pOutMtx->m[2][2] = 0.0f;
                    pOutMtx->m[2][3] = 1.0f;
                }
            }
        }

        void Camera::GXSetViewport() const
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                GXRenderModeObj& rRenderMode = G3DState::GetRenderModeObj();
                if (rRenderMode.field_rendering)
                {
                    ::GXSetViewportJitter(rCamData.FLOAT_0xDC, rCamData.FLOAT_0xE0, rCamData.FLOAT_0xE4,
                        rCamData.FLOAT_0xE8, rCamData.FLOAT_0xEC, rCamData.FLOAT_0xF0, rCamData.mFlags >> 8 & 1);
                }
                else
                {
                    ::GXSetViewport(rCamData.FLOAT_0xDC, rCamData.FLOAT_0xE0, rCamData.FLOAT_0xE4,
                        rCamData.FLOAT_0xE8, rCamData.FLOAT_0xEC, rCamData.FLOAT_0xF0);
                }
            }
        }

        void Camera::GXSetProjection() const
        {
            const CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                if ((rCamData.mFlags & 0x80) == 0)
                {
                    UpdateProjectionMtx();
                }

                ::GXSetProjection(const_cast<math::MTX44&>(rCamData.mProjMtx),
                    (GXProjectionType)rCamData.INT_0xA8);
            }
        }

        void Camera::GXSetScissor() const
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                ::GXSetScissor(rCamData.INT_0xF4, rCamData.INT_0xF8,
                    rCamData.INT_0xFC, rCamData.INT_0x100);
            }
        }

        void Camera::GXSetScissorBoxOffset() const
        {
            CameraData& rCamData = mCamData.ref();

            if (mCamData.IsValid())
            {
                ::GXSetScissorBoxOffset(rCamData.INT_0x104, rCamData.INT_0x108);
            }
        }

        void Camera::UpdateCameraMtx() const
        {
            CameraData& rCamData = mCamData.ref();

            if ((rCamData.mFlags & 0x1) != 0)
            {
                C_MTXLookAt(rCamData.mCamMtx, rCamData.mPos, rCamData.VEC3_0x80, rCamData.VEC3_0x8C);
            }
            else
            {
                if ((rCamData.mFlags & 0x4) != 0)
                {
                    math::VEC3 delta(rCamData.mPos.x - rCamData.VEC3_0x8C.x,
                        rCamData.mPos.y - rCamData.VEC3_0x8C.y,
                        rCamData.mPos.z - rCamData.VEC3_0x8C.z);

                    if ((delta.x == 0.0f) && (delta.z == 0.0f))
                    {
                        rCamData.mCamMtx[0][0] = 1.0f;
                        rCamData.mCamMtx[0][1] = 0.0f;
                        rCamData.mCamMtx[0][2] = 0.0f;
                        rCamData.mCamMtx[0][3] = -rCamData.mPos.x;

                        rCamData.mCamMtx[1][0] = 0.0f;
                        rCamData.mCamMtx[1][1] = 0.0f;
                        rCamData.mCamMtx[2][0] = 0.0f;
                        rCamData.mCamMtx[2][2] = 0.0f;

                        if (delta.y <= 0.0f)
                        {
                            rCamData.mCamMtx[1][2] = 1.0f;
                            rCamData.mCamMtx[1][3] = -rCamData.mPos.z;
                            rCamData.mCamMtx[2][1] = -1.0f;
                            rCamData.mCamMtx[2][3] = rCamData.mPos.y;
                        }
                        else
                        {
                            rCamData.mCamMtx[1][2] = -1.0f;
                            rCamData.mCamMtx[1][3] = rCamData.mPos.z;
                            rCamData.mCamMtx[2][1] = 1.0f;
                            rCamData.mCamMtx[2][3] = -rCamData.mPos.y;
                        }
                    }
                    else
                    {
                        math::VEC3 stack_0x7C(delta.z, 0.0f, -delta.x);

                        math::VEC3 cross;
                        math::VEC3Normalize(&delta, &delta);
                        math::VEC3Normalize(&stack_0x7C, &stack_0x7C);
                        math::VEC3Cross(&cross, &delta, &stack_0x7C);

                        f32 stack_0x20, stack_0x24;
                        math::SinCosDeg(&stack_0x20, &stack_0x24, rCamData.FLOAT_0xA4);

                        math::VEC3 stack_0x60;
                        stack_0x60.x = stack_0x20 * cross.x + stack_0x24 * stack_0x7C.x;
                        stack_0x60.y = stack_0x20 * cross.y;
                        stack_0x60.z = stack_0x20 * cross.z + stack_0x24 * stack_0x7C.z;
                        
                        math::VEC3 stack_0x54;
                        stack_0x54.x = stack_0x24 * cross.x - stack_0x20 * stack_0x7C.x;
                        stack_0x54.y = stack_0x24 * cross.y;
                        stack_0x54.z = stack_0x24 * cross.z - stack_0x20 * stack_0x7C.z;

                        rCamData.mCamMtx[0][0] = stack_0x60.x;
                        rCamData.mCamMtx[0][1] = stack_0x60.y;
                        rCamData.mCamMtx[0][2] = stack_0x60.z;
                        rCamData.mCamMtx[0][3] = -math::VEC3Dot(&rCamData.mPos, &stack_0x60);

                        rCamData.mCamMtx[1][0] = stack_0x54.x;
                        rCamData.mCamMtx[1][1] = stack_0x54.y;
                        rCamData.mCamMtx[1][2] = stack_0x54.z;
                        rCamData.mCamMtx[1][3] = -math::VEC3Dot(&rCamData.mPos, &stack_0x54);

                        rCamData.mCamMtx[2][0] = delta.x;
                        rCamData.mCamMtx[2][1] = delta.y;
                        rCamData.mCamMtx[2][2] = delta.z;
                        rCamData.mCamMtx[2][3] = -math::VEC3Dot(&rCamData.mPos, &delta);
                    }
                }
                else
                {
                    f32 x1, y1, z1, x2, y2, z2;
                    math::SinCosDeg(&x1, &x2, rCamData.VEC3_0x98.x);
                    math::SinCosDeg(&y1, &y2, rCamData.VEC3_0x98.y);
                    math::SinCosDeg(&z1, &z2, rCamData.VEC3_0x98.z);

                    math::VEC3 a;
                    a.x = x1 * y1 * z1 + y2 * z2;
                    a.y = x2 * z1;
                    a.z = x1 * y2 * z1 - y1 * z2;

                    math::VEC3 b;
                    b.x = x1 * y1 * z2 - y2 * z1;
                    b.y = x2 * z2;
                    b.z = x1 * y2 * z2 + y1 * z1;

                    math::VEC3 c;
                    c.x = x2 * y1;
                    c.y = -x1;
                    c.z = x2 * y2;

                    rCamData.mCamMtx[0][0] = a.x; 
                    rCamData.mCamMtx[0][1] = a.y;
                    rCamData.mCamMtx[0][2] = a.z;
                    rCamData.mCamMtx[0][3] = -math::VEC3Dot(&rCamData.mPos, &a);

                    rCamData.mCamMtx[1][0] = b.x;
                    rCamData.mCamMtx[1][1] = b.y;
                    rCamData.mCamMtx[1][2] = b.z;
                    rCamData.mCamMtx[1][3] = -math::VEC3Dot(&rCamData.mPos, &b);

                    rCamData.mCamMtx[2][0] = c.x;
                    rCamData.mCamMtx[2][1] = c.y;
                    rCamData.mCamMtx[2][2] = c.z;
                    rCamData.mCamMtx[2][3] = -math::VEC3Dot(&rCamData.mPos, &c);
                }
            }

            rCamData.mFlags |= 0x8;
        }
    }
}