#ifndef EGG_GFXE_FRUSTUM_H
#define EGG_GFXE_FRUSTUM_H
#include <egg/types_egg.h>

#include <egg/math.h>
#include <egg/prim.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

#include <revolution/GX.h>

namespace EGG {

class Frustum {
public:
    enum ProjectionType { PROJTYPE_ORTHO, PROJTYPE_PERSP };

    enum CanvasMode {
        CANVASMODE_CC, // Center-canvas origin
        CANVASMODE_LU, // Left-upper origin
    };

    enum LoadScnFlag {
        LOADSCN_KEEP_FOVY = 1 << 0,
        LOADSCN_KEEP_CANVAS = 1 << 1,
        LOADSCN_KEEP_Z = 1 << 2,
    };

protected:
    ProjectionType mProjType; // at 0x0
    CanvasMode mCanvasMode;   // at 0x4
    nw4r::math::VEC2 mSize;   // at 0x8
    f32 mFovY;                // at 0x10
    f32 mTanFovY;             // at 0x14
    f32 mNearZ;               // at 0x18
    f32 mFarZ;                // at 0x1C
    nw4r::math::VEC2 mOffset; // at 0x20
    nw4r::math::VEC3 mScale;  // at 0x28
    mutable u16 mFlags;       // at 0x34

public:
    Frustum(ProjectionType projType, const nw4r::math::VEC2& rSize, f32 nearZ,
            f32 farZ, CanvasMode canvasMode);
    Frustum(const Frustum& rOther);

    virtual ~Frustum() {}                                   // at 0x8
    virtual void SetProjectionGX() const;                   // at 0xC
    virtual void CopyToG3D(nw4r::g3d::Camera camera) const; // at 0x10

    void LoadScnCamera(const nw4r::g3d::ResAnmScn anmScn, u8 refNumber,
                       f32 frame, u32 flags);

    void CopyFromAnother(const Frustum& rOther);

    void GetViewToScreen(nw4r::math::VEC3* pScreenPos,
                         const nw4r::math::VEC3& rViewPos) const;
    void GetScreenToView(nw4r::math::VEC3* pViewPos,
                         const nw4r::math::VEC3& rScreenPos) const;
    void GetScreenToView(nw4r::math::VEC3* pPosView,
                         const nw4r::math::VEC2& rPosScreen) const;

    void ConvertToCanvasLU(f32 x, f32 y, f32* pX, f32* pY) const {
        if (mCanvasMode == CANVASMODE_LU) {
            *pX = x;
            *pY = y;
        } else if (mCanvasMode == CANVASMODE_CC) {
            ConvertFromCanvasCC(x, y, pX, pY);
        }
    }
    void ConvertToCanvasCC(f32 x, f32 y, f32* pX, f32* pY) const {
        if (mCanvasMode == CANVASMODE_LU) {
            ConvertFromCanvasLU(x, y, pX, pY);
        } else if (mCanvasMode == CANVASMODE_CC) {
            *pX = x;
            *pY = y;
        }
    }

    void ConvertToNormalLU(f32 x, f32 y, f32* pX, f32* pY) const {
        if (mCanvasMode == CANVASMODE_LU) {
            *pX = x / (GetSize().x / 2.0f);
            *pY = y / (GetSize().y / 2.0f);
        } else if (mCanvasMode == CANVASMODE_CC) {
            ConvertFromCanvasCC(x, y, pX, pY);
            *pX /= GetSize().x / 2.0f;
            *pY /= GetSize().y / 2.0f;
        }
    }
    void ConvertToNormalCC(f32 x, f32 y, f32* pX, f32* pY) const {
        if (mCanvasMode == CANVASMODE_LU) {
            ConvertFromCanvasLU(x, y, pX, pY);
            *pX /= GetSize().x / 2.0f;
            *pY /= GetSize().y / 2.0f;
        } else if (mCanvasMode == CANVASMODE_CC) {
            *pX = x / (GetSize().x / 2.0f);
            *pY = y / (GetSize().y / 2.0f);
        }
    }

    void ConvertFromCanvasLU(f32 x, f32 y, f32* pX, f32* pY) const {
        *pX = -(GetSize().x / 2.0f - x);
        *pY = -(-(GetSize().y / 2.0f - y));
    }
    void ConvertFromCanvasCC(f32 x, f32 y, f32* pX, f32* pY) const {
        *pX = x + GetSize().x / 2.0f;
        *pY = -(y - GetSize().y / 2.0f);
    }

    ProjectionType GetProjectionType() const {
        return mProjType;
    }
    void SetProjectionType(ProjectionType projType) {
        mProjType = projType;
    }

    CanvasMode GetCanvasMode() const {
        return mCanvasMode;
    }
    void SetCanvasMode(CanvasMode canvasMode) {
        if (mCanvasMode != canvasMode) {
            mFlags |= FLAG_DIRTY;
            mCanvasMode = canvasMode;
        }
    }

    const nw4r::math::VEC2& GetSize() const {
        return mSize;
    }

    u16 GetWidth() const {
        return static_cast<u16>(GetSize().x);
    }
    void SetSizeX(f32 sizeX) {
#line 117
        EGG_ASSERT(sizeX >= 0.f);
        mFlags |= FLAG_DIRTY;
        mSize.x = sizeX;
    }

    u16 GetHeight() const {
        return static_cast<u16>(GetSize().y);
    }
    void SetSizeY(f32 sizeY) {
#line 123
        EGG_ASSERT(sizeY >= 0.f);
        mFlags |= FLAG_DIRTY;
        mSize.y = sizeY;
    }

    f32 GetAspect() const {
        return GetSize().x / GetSize().y;
    }

    f32 GetFovy() const {
        return mFovY;
    }
    void SetFovy(f32 fovy) {
        if (mFovY == fovy)
            return;

#line 391
        EGG_ASSERT(0.f < fovy && fovy < 180.f);
        mFovY = fovy;

        f32 sin, cos;
        nw4r::math::SinCosDeg(&sin, &cos, fovy / 2.0f);
        mTanFovY = sin / cos;
    }

    f32 GetNearZ() const {
        return mNearZ;
    }
    void SetNearZ(f32 nearZ) {
        mNearZ = nearZ;
    }

    f32 GetFarZ() const {
        return mFarZ;
    }
    void SetFarZ(f32 farZ) {
        mFarZ = farZ;
    }

    const nw4r::math::VEC2& GetOffset() const {
        return mOffset;
    }
    void SetOffset(const nw4r::math::VEC2& rOffset) {
        mOffset = rOffset;
    }

    const nw4r::math::VEC3& GetScale() const {
        return mScale;
    }
    void SetScale(const nw4r::math::VEC3& rScale) {
        mScale = rScale;
    }

    static void GetGlobalScaleOffset(f32* pSX, f32* pSY, f32* pOX, f32* pOY) {
        *pSX = sGlobalScale.x;
        *pSY = sGlobalScale.y;
        *pOX = sGlobalOffset.x;
        *pOY = sGlobalOffset.y;
    }
    static void SetGlobalScaleOffset(f32 sx, f32 sy, f32 ox, f32 oy) {
        sGlobalScale.x = sx;
        sGlobalScale.y = sy;
        sGlobalOffset.x = ox;
        sGlobalOffset.y = oy;
    }

protected:
    enum {
        FLAG_DIRTY = 1 << 0,
    };

private:
    void SetProjectionPerspectiveGX_() const;
    void SetProjectionOrthographicGX_() const;

    void CopyToG3D_Perspective_(nw4r::g3d::Camera camera) const;
    void CopyToG3D_Orthographic_(nw4r::g3d::Camera camera) const;

    void CalcMtxPerspective_(nw4r::math::MTX44* pMtx) const;

    void GetOrthographicParam_(nw4r::math::MTX44* pMtx) const;
    void GetPerspectiveParam_(f32* p) const;
    void GetOrthographicParam_(f32* pT, f32* pB, f32* pL, f32* pR) const;

private:
    static nw4r::math::VEC2 sGlobalScale;
    static nw4r::math::VEC2 sGlobalOffset;
};

} // namespace EGG

#endif
