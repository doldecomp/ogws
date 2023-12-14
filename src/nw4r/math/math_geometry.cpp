#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <algorithm>
#include <nw4r/math.h>

DECOMP_FORCELITERAL(math_geometry_cpp, 0.5f, 0.0f);

namespace nw4r {
namespace math {

void PLANE::Set(const VEC3* p0, const VEC3* p1, const VEC3* p2) {
    VEC3 v0, v1, v2;

    VEC3Sub(&v0, p2, p0);
    VEC3Sub(&v1, p1, p0);
    VEC3Normalize(&n, VEC3Cross(&v2, &v0, &v1));
    d = -VEC3Dot(&n, p0);
}

void AABB::Set(const VEC3* points, unsigned int num) {
    min = points[0];
    max = points[0];

    for (unsigned int i = 1; i < num; i++) {
        if (points[i].x < min.x) {
            min.x = points[i].x;
        } else if (points[i].x > max.x) {
            max.x = points[i].x;
        }

        if (points[i].y < min.y) {
            min.y = points[i].y;
        } else if (points[i].y > max.y) {
            max.y = points[i].y;
        }

        if (points[i].z < min.z) {
            min.z = points[i].z;
        } else if (points[i].z > max.z) {
            max.z = points[i].z;
        }
    }
}

void AABB::Set(const AABB* box, const MTX34* mtx) {
    f32 x0, y0, z0;
    f32 x1, y1, z1;
    f32 a0, a1;
    f32 b0, b1;

    x0 = mtx->_00 * box->min.x + mtx->_03;
    x1 = mtx->_00 * box->max.x + mtx->_03;

    a0 = mtx->_01 * box->min.y;
    a1 = mtx->_01 * box->max.y;

    b0 = mtx->_02 * box->min.z;
    b1 = mtx->_02 * box->max.z;

    if (x0 > x1) {
        std::swap(x0, x1);
    }

    if (a0 < a1) {
        x0 += a0;
        x1 += a1;
    } else {
        x0 += a1;
        x1 += a0;
    }

    if (b0 < b1) {
        x0 += b0;
        x1 += b1;
    } else {
        x0 += b1;
        x1 += b0;
    }

    y0 = mtx->_10 * box->min.x + mtx->_13;
    y1 = mtx->_10 * box->max.x + mtx->_13;

    a0 = mtx->_11 * box->min.y;
    a1 = mtx->_11 * box->max.y;

    b0 = mtx->_12 * box->min.z;
    b1 = mtx->_12 * box->max.z;

    if (y0 > y1) {
        std::swap(y0, y1);
    }

    if (a0 < a1) {
        y0 += a0;
        y1 += a1;
    } else {
        y0 += a1;
        y1 += a0;
    }

    if (b0 < b1) {
        y0 += b0;
        y1 += b1;
    } else {
        y0 += b1;
        y1 += b0;
    }

    z0 = mtx->_20 * box->min.x + mtx->_23;
    z1 = mtx->_20 * box->max.x + mtx->_23;

    a0 = mtx->_21 * box->min.y;
    a1 = mtx->_21 * box->max.y;

    b0 = mtx->_22 * box->min.z;
    b1 = mtx->_22 * box->max.z;

    if (z0 > z1) {
        std::swap(z0, z1);
    }

    if (a0 < a1) {
        z0 += a0;
        z1 += a1;
    } else {
        z0 += a1;
        z1 += a0;
    }

    if (b0 < b1) {
        z0 += b0;
        z1 += b1;
    } else {
        z0 += b1;
        z1 += b0;
    }

    min.x = x0;
    min.y = y0;
    min.z = z0;

    max.x = x1;
    max.y = y1;
    max.z = z1;
}

void FRUSTUM::Set(f32 fovy, f32 aspect, f32 n, f32 f, const MTX34& cam) {
    f32 tan = TanDeg(fovy * 0.5f);
    f32 ny = tan * n;
    f32 nx = ny * aspect;
    Set(ny, -ny, -nx, nx, n, f, cam);
}

void FRUSTUM::Set(f32 t, f32 b, f32 l, f32 r, f32 n, f32 f, const MTX34& cam) {
    MTX34 invcam;
    MTX34Inv(&invcam, &cam);
    MTX34Copy(&mCamMtx, &cam);

    VEC3 p0(0.0f, 0.0f, 0.0f);
    VEC3 p[POINT_MAX];

    f32 f_n = f / n;

    p[POINT_NEAR_TL].x = l;
    p[POINT_NEAR_TL].y = t;
    p[POINT_NEAR_TL].z = -n;

    p[POINT_NEAR_TR].x = r;
    p[POINT_NEAR_TR].y = t;
    p[POINT_NEAR_TR].z = -n;

    p[POINT_NEAR_BR].x = r;
    p[POINT_NEAR_BR].y = b;
    p[POINT_NEAR_BR].z = -n;

    p[POINT_NEAR_BL].x = l;
    p[POINT_NEAR_BL].y = b;
    p[POINT_NEAR_BL].z = -n;

    p[POINT_FAR_TL].x = f_n * l;
    p[POINT_FAR_TL].y = f_n * t;
    p[POINT_FAR_TL].z = -f;

    p[POINT_FAR_TR].x = f_n * r;
    p[POINT_FAR_TR].y = f_n * t;
    p[POINT_FAR_TR].z = -f;

    p[POINT_FAR_BR].x = f_n * r;
    p[POINT_FAR_BR].y = f_n * b;
    p[POINT_FAR_BR].z = -f;

    p[POINT_FAR_BL].x = f_n * l;
    p[POINT_FAR_BL].y = f_n * b;
    p[POINT_FAR_BL].z = -f;

    mNearZ = -n;
    mFarZ = -f;

    mPlaneL.Set(&p0, &p[POINT_NEAR_BL], &p[POINT_NEAR_TL]);
    mPlaneR.Set(&p0, &p[POINT_NEAR_TR], &p[POINT_NEAR_BR]);
    mPlaneT.Set(&p0, &p[POINT_NEAR_TL], &p[POINT_NEAR_TR]);
    mPlaneB.Set(&p0, &p[POINT_NEAR_BR], &p[POINT_NEAR_BL]);

    for (int i = 0; i < POINT_MAX; i++) {
        VEC3TransformCoord(&p[i], &invcam, &p[i]);
    }

    VEC3TransformCoord(&p0, &invcam, &p0);
    mBox.Set(p, POINT_MAX);

    // clang-format off
    mPlanes[PLANE_L].Set(&p0,               &p[POINT_NEAR_BL], &p[POINT_NEAR_TL]);
    mPlanes[PLANE_R].Set(&p0,               &p[POINT_NEAR_TR], &p[POINT_NEAR_BR]);
    mPlanes[PLANE_N].Set(&p[POINT_NEAR_TL], &p[POINT_NEAR_TR], &p[POINT_NEAR_BR]);
    mPlanes[PLANE_F].Set(&p[POINT_FAR_TL],  &p[POINT_FAR_BL],  &p[POINT_FAR_BR]);
    mPlanes[PLANE_T].Set(&p0,               &p[POINT_NEAR_TL], &p[POINT_NEAR_TR]);
    mPlanes[PLANE_B].Set(&p0,               &p[POINT_NEAR_BR], &p[POINT_NEAR_BL]);
    // clang-format on
}

bool IntersectionAABB(const AABB* a, const AABB* b) {
    if (a->min.x > b->max.x || b->min.x > a->max.x || a->min.y > b->max.y ||
        b->min.y > a->max.y || a->min.z > b->max.z || b->min.z > a->max.z) {
        return false;
    }

    return true;
}

IntersectionResult FRUSTUM::IntersectAABB_Ex(const AABB* box) const {
    if (!IntersectionAABB(box, &mBox)) {
        return INTERSECTION_OUTSIDE;
    }

    IntersectionResult result = INTERSECTION_INSIDE;
    VEC3 p, n;

    for (int i = 0; i < PLANE_MAX; i++) {
        if (mPlanes[i].n.x >= 0.0f) {
            p.x = box->min.x;
            n.x = box->max.x;
        } else {
            p.x = box->max.x;
            n.x = box->min.x;
        }

        if (mPlanes[i].n.y >= 0.0f) {
            p.y = box->min.y;
            n.y = box->max.y;
        } else {
            p.y = box->max.y;
            n.y = box->min.y;
        }

        if (mPlanes[i].n.z >= 0.0f) {
            p.z = box->min.z;
            n.z = box->max.z;
        } else {
            p.z = box->max.z;
            n.z = box->min.z;
        }

        if (mPlanes[i].Test(p) > 0.0f) {
            return INTERSECTION_NONE;
        }

        if (mPlanes[i].Test(n) > 0.0f) {
            result = INTERSECTION_INTERSECT;
        }
    }

    return result;
}

} // namespace math
} // namespace nw4r
