#ifndef NW4R_MATH_TYPES_H
#define NW4R_MATH_TYPES_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math/math_arithmetic.h>
#include <nw4r/math/math_triangular.h>

#include <revolution/MTX.h>

namespace nw4r {
namespace math {

/******************************************************************************
 *
 * VEC2 structure
 *
 ******************************************************************************/
// Provides a POD type that can be upcasted to the real structure.
// (Has the added benefit of forcing struct copies to use lwz/stw.)
struct _VEC2 {
    f32 x, y;
};

struct VEC2 : _VEC2 {
    VEC2() {}
    VEC2(f32 fx, f32 fy) {
        x = fx;
        y = fy;
    }

    operator f32*() {
        return reinterpret_cast<f32*>(this);
    }
    operator const f32*() const {
        return reinterpret_cast<const f32*>(this);
    }

    VEC2 operator+(const VEC2& rRhs) const {
        return VEC2(x + rRhs.x, y + rRhs.y);
    }
    VEC2 operator-(const VEC2& rRhs) const {
        return VEC2(x - rRhs.x, y - rRhs.y);
    }

    VEC2& operator+=(const VEC2& rRhs) {
        x += rRhs.x;
        y += rRhs.y;
        return *this;
    }
    VEC2& operator-=(const VEC2& rRhs) {
        x -= rRhs.x;
        y -= rRhs.y;
        return *this;
    }

    bool operator==(const VEC2& rRhs) const {
        return x == rRhs.x && y == rRhs.y;
    }
    bool operator!=(const VEC2& rRhs) const {
        return x != rRhs.x || y != rRhs.y;
    }
};

/******************************************************************************
 *
 * VEC3 structure
 *
 ******************************************************************************/
// Forward declarations
struct VEC3;
VEC3* VEC3Add(VEC3* pOut, const VEC3* pA, const VEC3* pB);
VEC3* VEC3Sub(VEC3* pOut, const VEC3* pA, const VEC3* pB);
VEC3* VEC3Scale(VEC3* pOut, const VEC3* pIn, f32 scale);

// Provides a POD type that can be upcasted to the real structure.
// (Has the added benefit of forcing struct copies to use lwz/stw.)
struct _VEC3 {
    f32 x, y, z;
};

struct VEC3 : _VEC3 {
    VEC3() {}
    VEC3(f32 fx, f32 fy, f32 fz) {
        x = fx;
        y = fy;
        z = fz;
    }
    VEC3(const _VEC3& rVec) {
        x = rVec.x;
        y = rVec.y;
        z = rVec.z;
    }
    VEC3(const Vec& rVec) {
        x = rVec.x;
        y = rVec.y;
        z = rVec.z;
    }
    VEC3(const f32* pData) {
        x = pData[0];
        y = pData[1];
        z = pData[2];
    }

    operator Vec*() {
        return reinterpret_cast<Vec*>(this);
    }
    operator const Vec*() const {
        return reinterpret_cast<const Vec*>(this);
    }

    f32 LenSq() const {
        return x * x + y * y + z * z;
    }

    VEC3 operator-() const {
        return VEC3(-x, -y, -z);
    }

    VEC3 operator+(const VEC3& rRhs) const {
        VEC3 out;
        VEC3Add(&out, this, &rRhs);
        return out;
    }
    VEC3 operator-(const VEC3& rRhs) const {
        VEC3 out;
        VEC3Sub(&out, this, &rRhs);
        return out;
    }
    VEC3 operator*(f32 x) const {
        VEC3 out;
        VEC3Scale(&out, this, x);
        return out;
    }
    VEC3 operator/(f32 x) const {
        f32 r = 1 / x;
        return *this * r;
    }

    VEC3& operator+=(const VEC3& rRhs) {
        VEC3Add(this, this, &rRhs);
        return *this;
    }
    VEC3& operator-=(const VEC3& rRhs) {
        VEC3Sub(this, this, &rRhs);
        return *this;
    }
    VEC3& operator*=(f32 x) {
        VEC3Scale(this, this, x);
        return *this;
    }
    VEC3& operator/=(f32 x) {
        return *this *= (1 / x);
    }

    bool operator==(const VEC3& rRhs) const {
        return x == rRhs.x && y == rRhs.y && z == rRhs.z;
    }
    bool operator!=(const VEC3& rRhs) const {
        return x != rRhs.x || y != rRhs.y || z != rRhs.z;
    }
};

/******************************************************************************
 *
 * MTX33 structure
 *
 ******************************************************************************/
// Provides a POD type that can be upcasted to the real structure.
// (Has the added benefit of forcing struct copies to use lwz/stw.)
struct _MTX33 {
    union {
        struct {
            f32 _00, _01, _02;
            f32 _10, _11, _12;
            f32 _20, _21, _22;
        };

        f32 m[3][3];
        f32 a[3 * 3];
    };
};

struct MTX33 : _MTX33 {
    MTX33() {}
};

/******************************************************************************
 *
 * MTX34 structure
 *
 ******************************************************************************/
// Provides a POD type that can be upcasted to the real structure.
// (Has the added benefit of forcing struct copies to use lwz/stw.)
struct _MTX34 {
    union {
        struct {
            f32 _00, _01, _02, _03;
            f32 _10, _11, _12, _13;
            f32 _20, _21, _22, _23;
        };

        f32 m[3][4];
        f32 a[3 * 4];
        Mtx mtx;
    };
};

struct MTX34 : _MTX34 {
    typedef f32 (*MtxRef)[4];
    typedef const f32 (*MtxRefConst)[4];

    MTX34() {}

    // clang-format off
    MTX34(f32 f00, f32 f01, f32 f02, f32 f03,
          f32 f10, f32 f11, f32 f12, f32 f13,
          f32 f20, f32 f21, f32 f22, f32 f23) {
        _00 = f00; _01 = f01; _02 = f02; _03 = f03;
        _10 = f10; _11 = f11; _12 = f12; _13 = f13;
        _20 = f20; _21 = f21; _22 = f22; _23 = f23;
    }
    // clang-format on

    operator MtxRef() {
        return mtx;
    }
    operator MtxRefConst() const {
        return mtx;
    }
};

/******************************************************************************
 *
 * MTX44 structure
 *
 ******************************************************************************/
// Provides a POD type that can be upcasted to the real structure.
// (Has the added benefit of forcing struct copies to use lwz/stw.)
struct _MTX44 {
    union {
        struct {
            f32 _00, _01, _02, _03;
            f32 _10, _11, _12, _13;
            f32 _20, _21, _22, _23;
            f32 _30, _31, _32, _33;
        };

        f32 m[4][4];
        f32 a[4 * 4];
        Mtx44 mtx;
    };
};

struct MTX44 : _MTX44 {
    typedef f32 (*Mtx44Ref)[4];
    typedef const f32 (*Mtx44RefConst)[4];

    MTX44() {}

    operator Mtx44Ref() {
        return mtx;
    }
    operator Mtx44RefConst() const {
        return mtx;
    }
};

/******************************************************************************
 *
 * QUAT structure
 *
 ******************************************************************************/
// Provides a POD type that can be upcasted to the real structure.
// (Has the added benefit of forcing struct copies to use lwz/stw.)
struct _QUAT {
    f32 x, y, z, w;
};

struct QUAT : _QUAT {
    QUAT() {}
    QUAT(f32 fx, f32 fy, f32 fz, f32 fw) {
        x = fx;
        y = fy;
        z = fz;
        w = fw;
    }

    // TODO: These are not real AFAIK. Do they really manually cast the QUAT?
    operator Quaternion*() {
        return reinterpret_cast<Quaternion*>(this);
    }
    operator const Quaternion*() const {
        return reinterpret_cast<const Quaternion*>(this);
    }
};

/******************************************************************************
 *
 * VEC2 functions
 *
 ******************************************************************************/
inline f32 VEC2Len(const VEC2* pVec) {
    return FSqrt(pVec->x * pVec->x + pVec->y * pVec->y);
}

/******************************************************************************
 *
 * VEC3 functions
 *
 ******************************************************************************/
VEC3* VEC3Maximize(VEC3* pOut, const VEC3* pA, const VEC3* pB);
VEC3* VEC3Minimize(VEC3* pOut, const VEC3* pA, const VEC3* pB);
VEC3* VEC3TransformNormal(VEC3* pOut, const MTX34* pMtx, const VEC3* pVec);

inline VEC3* VEC3Add(register VEC3* pOut, register const VEC3* pA,
                     register const VEC3* pB) {
    register f32 work0, work1, work2;

    // clang-format off
    asm {
        // Add XY
        psq_l  work0, VEC3.x(pA),   0, 0
        psq_l  work1, VEC3.x(pB),   0, 0
        ps_add work2, work0, work1
        psq_st work2, VEC3.x(pOut), 0, 0
        
        // Add Z
        psq_l  work0, VEC3.z(pA),   1, 0
        psq_l  work1, VEC3.z(pB),   1, 0
        ps_add work2, work0, work1
        psq_st work2, VEC3.z(pOut), 1, 0
    }
    // clang-format on

    return pOut;
}

inline f32 VEC3Dot(register const VEC3* pA, register const VEC3* pB) {
    register f32 dot;
    register f32 work0, work1, work2, work3;

    // clang-format off
    asm {
        // YZ product
        psq_l  work0, VEC3.y(pA), 0, 0
        psq_l  work1, VEC3.y(pB), 0, 0
        ps_mul work0, work0, work1
        
        // X product + YZ product
        psq_l   work3, VEC3.x(pA), 1, 0
        psq_l   work2, VEC3.x(pB), 1, 0
        ps_madd work1, work3, work2, work0
        
        // Dot product
        ps_sum0 dot, work1, work0, work0
    }
    // clang-format on

    return dot;
}

inline f32 VEC3LenSq(register const VEC3* pVec) {
    register f32 work0, work1, work2;

    // clang-format off
    asm {
        // Square XY
        psq_l  work0, VEC3.x(pVec), 0, 0
        ps_mul work0, work0, work0

        // Square Z
        lfs     work1, VEC3.z(pVec)
        ps_madd work2, work1, work1, work0

        // Sum products
        ps_sum0 work2, work2, work0, work0
    }
    // clang-format on

    return work2;
}

inline VEC3* VEC3Lerp(register VEC3* pOut, register const VEC3* pVec1,
                      register const VEC3* pVec2, register f32 t) {
    register f32 work0, work1, work2;

    // clang-format off
    asm {
        // X/Y delta
        psq_l  work0, VEC3.x(pVec1), 0, 0
        psq_l  work1, VEC3.x(pVec2), 0, 0
        ps_sub work2, work1, work0
        // Scale with time and add to v0
        ps_madds0 work2, work2, t, work0
        psq_st    work2, VEC3.x(pOut), 0, 0
        
        // Z delta
        psq_l  work0, VEC3.z(pVec1), 1, 0
        psq_l  work1, VEC3.z(pVec2), 1, 0
        ps_sub work2, work1, work0
        // Scale with time and add to v0
        ps_madds0 work2, work2, t, work0
        psq_st    work2, VEC3.z(pOut), 1, 0
    }
    // clang-format on

    return pOut;
}

inline VEC3* VEC3Scale(register VEC3* pOut, register const VEC3* pIn,
                       register f32 scale) {
    register f32 work0, work1;

    // clang-format off
    asm {
        // Scale XY
        psq_l    work0, VEC3.x(pIn),  0, 0
        ps_muls0 work1, work0, scale
        psq_st   work1, VEC3.x(pOut), 0, 0

        // Scale Z
        psq_l    work0, VEC3.z(pIn),  1, 0
        ps_muls0 work1, work0, scale
        psq_st   work1, VEC3.z(pOut), 1, 0
    }
    // clang-format on

    return pOut;
}

inline VEC3* VEC3Sub(register VEC3* pOut, register const VEC3* pA,
                     register const VEC3* pB) {
    register f32 work0, work1, work2;

    // clang-format off
    asm {
        // Sub XY
        psq_l  work0, VEC3.x(pA),   0, 0
        psq_l  work1, VEC3.x(pB),   0, 0
        ps_sub work2, work0, work1
        psq_st work2, VEC3.x(pOut), 0, 0
        
        // Sub Z
        psq_l  work0, VEC3.z(pA),   1, 0
        psq_l  work1, VEC3.z(pB),   1, 0
        ps_sub work2, work0, work1
        psq_st work2, VEC3.z(pOut), 1, 0
    }
    // clang-format on

    return pOut;
}

inline VEC3* VEC3Cross(VEC3* pOut, const VEC3* pA, const VEC3* pB) {
    PSVECCrossProduct(*pA, *pB, *pOut);
    return pOut;
}

inline f32 VEC3DistSq(const VEC3* pA, const VEC3* pB) {
    return PSVECSquareDistance(*pA, *pB);
}

inline f32 VEC3Len(const VEC3* pVec) {
    return PSVECMag(*pVec);
}

inline VEC3* VEC3Normalize(VEC3* pOut, const VEC3* pIn) {
    PSVECNormalize(*pIn, *pOut);
    return pOut;
}

inline VEC3* VEC3Transform(VEC3* pOut, const MTX34* pMtx, const VEC3* pVec) {
    PSMTXMultVec(*pMtx, *pVec, *pOut);
    return pOut;
}

inline VEC3* VEC3TransformCoord(VEC3* pOut, const MTX34* pMtx,
                                const VEC3* pVec) {
    PSMTXMultVec(*pMtx, *pVec, *pOut);
    return pOut;
}

/******************************************************************************
 *
 * MTX33 functions
 *
 ******************************************************************************/
MTX33* MTX33Identity(MTX33* pMtx);

/******************************************************************************
 *
 * MTX34 functions
 *
 ******************************************************************************/
MTX33* MTX34ToMTX33(MTX33* pOut, const MTX34* pIn);
u32 MTX34InvTranspose(MTX33* pOut, const MTX34* pIn);
MTX34* MTX34Zero(MTX34* pMtx);
MTX34* MTX34Scale(MTX34* pOut, const MTX34* pIn, const VEC3* pScale);
MTX34* MTX34Trans(MTX34* pOut, const MTX34* pIn, const VEC3* pTrans);
MTX34* MTX34RotAxisFIdx(MTX34* pMtx, const VEC3* pAxis, f32 fidx);
MTX34* MTX34RotXYZFIdx(MTX34* pMtx, f32 fx, f32 fy, f32 fz);

inline MTX34* MTX34Copy(MTX34* pOut, const MTX34* pIn) {
    PSMTXCopy(*pIn, *pOut);
    return pOut;
}

inline MTX34* MTX34Identity(MTX34* pMtx) {
    PSMTXIdentity(*pMtx);
    return pMtx;
}

inline u32 MTX34Inv(MTX34* pOut, const MTX34* pIn) {
    return PSMTXInverse(*pIn, *pOut);
}

inline u32 MTX34InvTranspose(MTX34* pOut, const MTX34* pIn) {
    return PSMTXInvXpose(*pIn, *pOut);
}

inline MTX34* MTX34LookAt(MTX34* pMtx, const VEC3* pPos, const VEC3* pUp,
                          const VEC3* pTarget) {
    C_MTXLookAt(*pMtx, *pPos, *pUp, *pTarget);
    return pMtx;
}

inline MTX34* MTX34Mult(MTX34* pOut, const MTX34* pA, const MTX34* pB) {
    PSMTXConcat(*pA, *pB, *pOut);
    return pOut;
}

inline MTX34* MTX34MultArray(MTX34* pOut, const MTX34* p1, const MTX34* pSrc,
                             u32 len) {
    PSMTXConcatArray(*p1, *pSrc, *pOut, len);
    return pOut;
}

inline MTX34* MTX34RotAxisRad(MTX34* pOut, const VEC3* pAxis, f32 frad) {
    return MTX34RotAxisFIdx(pOut, pAxis, NW4R_MATH_RAD_TO_FIDX(frad));
}

inline MTX34* MTX34RotXYZDeg(MTX34* pMtx, f32 dx, f32 dy, f32 dz) {
    return MTX34RotXYZFIdx(pMtx, NW4R_MATH_DEG_TO_FIDX(dx),
                           NW4R_MATH_DEG_TO_FIDX(dy),
                           NW4R_MATH_DEG_TO_FIDX(dz));
}

inline MTX34* MTX34RotXYZRad(MTX34* pMtx, f32 rx, f32 ry, f32 rz) {
    return MTX34RotXYZFIdx(pMtx, NW4R_MATH_RAD_TO_FIDX(rx),
                           NW4R_MATH_RAD_TO_FIDX(ry),
                           NW4R_MATH_RAD_TO_FIDX(rz));
}

inline MTX34* MTX34Scale(MTX34* pOut, const VEC3* pScale, const MTX34* pIn) {
    PSMTXScaleApply(*pIn, *pOut, pScale->x, pScale->y, pScale->z);
    return pOut;
}

inline QUAT* MTX34ToQUAT(QUAT* pQuat, const MTX34* pMtx) {
    C_QUATMtx(*pQuat, *pMtx);
    return pQuat;
}

inline MTX34* MTX34Trans(MTX34* pOut, const VEC3* pTrans, const MTX34* pIn) {
    PSMTXTransApply(*pIn, *pOut, pTrans->x, pTrans->y, pTrans->z);
    return pOut;
}

/******************************************************************************
 *
 * MTX44 functions
 *
 ******************************************************************************/
MTX44* MTX44Identity(MTX44* pMtx);
MTX44* MTX44Copy(MTX44* pDst, const MTX44* pSrc);

/******************************************************************************
 *
 * QUAT functions
 *
 ******************************************************************************/
inline MTX34* QUATToMTX34(MTX34* pMtx, const QUAT* pQuat) {
    PSMTXQuat(*pMtx, *pQuat);
    return pMtx;
}

// @bug QUATSlerp macro changes this function name!
inline QUAT* C_QUATSlerp(QUAT* pOut, const QUAT* p1, const QUAT* p2, f32 t) {
    ::C_QUATSlerp(*p1, *p2, *pOut, t);
    return pOut;
}

} // namespace math
} // namespace nw4r

#endif
