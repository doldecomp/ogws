#include <Pack/RPUtility.h>

#include <egg/math.h>

/**
 * @brief Sets the specified local axis of the input matrix
 *
 * @param pMtx Matrix
 * @param axis Axis index
 * @param pBase Base vector
 */
void RPUtlDohMath::MTX34SetBase(nw4r::math::MTX34* pMtx, AxisType axis,
                                const nw4r::math::VEC3* pBase) {
    if (pBase != NULL) {
        pMtx->m[0][axis] = pBase->x;
        pMtx->m[1][axis] = pBase->y;
        pMtx->m[2][axis] = pBase->z;
    }
}

/**
 * @brief Constructs a right-handed orthonormal basis from the local axes of
 * the specified matrix
 *
 * @param[out] pOut Output matrix
 * @param pIn Input matrix
 * @param order Axis priority order
 */
void RPUtlDohMath::MTX34Normalize(nw4r::math::MTX34* pOut,
                                  const nw4r::math::MTX34* pIn,
                                  AxisOrder order) {

    nw4r::math::VEC3 ax(pIn->_00, pIn->_10, pIn->_20);
    nw4r::math::VEC3 ay(pIn->_01, pIn->_11, pIn->_21);
    nw4r::math::VEC3 az(pIn->_02, pIn->_12, pIn->_22);

    switch (order) {
    case AxisOrder_XY: {
        nw4r::math::VEC3Normalize(&ax, &ax);
        nw4r::math::VEC3Cross(&az, &ax, &ay);

        nw4r::math::VEC3Normalize(&az, &az);
        nw4r::math::VEC3Cross(&ay, &az, &ax);

        nw4r::math::VEC3Normalize(&ay, &ay);
        break;
    }

    case AxisOrder_XZ: {
        nw4r::math::VEC3Normalize(&ax, &ax);
        nw4r::math::VEC3Cross(&ay, &az, &ax);

        nw4r::math::VEC3Normalize(&ay, &ay);
        nw4r::math::VEC3Cross(&az, &ax, &ay);

        nw4r::math::VEC3Normalize(&az, &az);
        break;
    }

    case AxisOrder_YZ: {
        nw4r::math::VEC3Normalize(&ay, &ay);
        nw4r::math::VEC3Cross(&ax, &ay, &az);

        nw4r::math::VEC3Normalize(&ax, &ax);
        nw4r::math::VEC3Cross(&az, &ax, &ay);

        nw4r::math::VEC3Normalize(&az, &az);
        break;
    }

    case AxisOrder_YX: {
        nw4r::math::VEC3Normalize(&ay, &ay);
        nw4r::math::VEC3Cross(&az, &ax, &ay);

        nw4r::math::VEC3Normalize(&az, &az);
        nw4r::math::VEC3Cross(&ax, &ay, &az);

        nw4r::math::VEC3Normalize(&ax, &ax);
        break;
    }

    case AxisOrder_ZX: {
        nw4r::math::VEC3Normalize(&az, &az);
        nw4r::math::VEC3Cross(&ay, &az, &ax);

        nw4r::math::VEC3Normalize(&ay, &ay);
        nw4r::math::VEC3Cross(&ax, &ay, &az);

        nw4r::math::VEC3Normalize(&ax, &ax);
        break;
    }

    case AxisOrder_ZY: {
        nw4r::math::VEC3Normalize(&az, &az);
        nw4r::math::VEC3Cross(&ax, &ay, &az);

        nw4r::math::VEC3Normalize(&ax, &ax);
        nw4r::math::VEC3Cross(&ay, &az, &ax);

        nw4r::math::VEC3Normalize(&ay, &ay);
        break;
    }

    default: {
        break;
    }
    }

    pOut->_00 = ax.x;
    pOut->_10 = ax.y;
    pOut->_20 = ax.z;

    pOut->_01 = ay.x;
    pOut->_11 = ay.y;
    pOut->_21 = ay.z;

    pOut->_02 = az.x;
    pOut->_12 = az.y;
    pOut->_22 = az.z;
}

/**
 * @brief Calculates a bend point between two endpoints
 *
 * @param[out] pMidPoint Bend point
 * @param[out] pDistance Distance between the endpoints
 * @param rBendDir Bend direction vector
 * @param rPointA Endpoint A
 * @param rPointB Endpoint B
 * @param lengthA Length of the segment from A to the bend joint
 * @param lengthB Length of the segment from the bend joint to B
 */
void RPUtlDohMath::GetMidPoint(nw4r::math::VEC3* pMidPoint, f32* pDistance,
                               const nw4r::math::VEC3& rBendDir,
                               const nw4r::math::VEC3& rPointA,
                               const nw4r::math::VEC3& rPointB, f32 lengthA,
                               f32 lengthB) {
    nw4r::math::VEC3 bend;

    nw4r::math::VEC3 delta(    //
        rPointB.x - rPointA.x, //
        rPointB.y - rPointA.y, //
        rPointB.z - rPointA.z);

    // Create an orthonormal basis for the bend direction
    nw4r::math::MTX34 mtx;
    MTX34SetBase(&mtx, AxisType_Y, &delta);
    MTX34SetBase(&mtx, AxisType_Z, &rBendDir);
    MTX34Normalize(&mtx, &mtx, AxisOrder_YZ);

    bend.x = mtx._02;
    bend.y = mtx._12;
    bend.z = mtx._22;

    // Find the position of the joint along the segment AB
    f32 total = lengthA + lengthB;
    f32 ratio = lengthA / total;

    nw4r::math::VEC3 joint( //
        ratio * rPointB.x + (1.0f - ratio) * rPointA.x,
        ratio * rPointB.y + (1.0f - ratio) * rPointA.y,
        ratio * rPointB.z + (1.0f - ratio) * rPointA.z);

    f32 distance = nw4r::math::VEC3Len(&delta);

    if (distance >= total) {
        // Segment chain is fully extended, no bend
        *pMidPoint = joint;
    } else {
        // Construct a right triangle, solving for the bend height
        f32 along = distance * ratio;
        f32 height = nw4r::math::FSqrt(lengthA * lengthA - along * along);

        f32 jx = joint.x + bend.x * height;
        f32 jy = joint.y + bend.y * height;
        f32 jz = joint.z + bend.z * height;

        pMidPoint->x = jx;
        pMidPoint->y = jy;
        pMidPoint->z = jz;
    }

    if (pDistance != NULL) {
        *pDistance = distance;
    }
}

/**
 * @brief Zero vector (3D)
 */
const nw4r::math::VEC3 RPUtlDohMath::VEC3_ZERO(0.0f, 0.0f, 0.0f);

/**
 * @brief Zero vector (2D)
 */
const nw4r::math::VEC2 RPUtlDohMath::VEC2_ZERO(0.0f, 0.0f);

/**
 * @brief Positive X-axis unit vector
 */
const nw4r::math::VEC3 RPUtlDohMath::AXIS_XP(1.0f, 0.0f, 0.0f);

/**
 * @brief Negative X-axis unit vector
 */
const nw4r::math::VEC3 RPUtlDohMath::AXIS_XN(-1.0f, 0.0f, 0.0f);

/**
 * @brief Positive Y-axis unit vector
 */
const nw4r::math::VEC3 RPUtlDohMath::AXIS_YP(0.0f, 1.0f, 0.0f);

/**
 * @brief Negative Y-axis unit vector
 */
const nw4r::math::VEC3 RPUtlDohMath::AXIS_YN(0.0f, -1.0f, 0.0f);

/**
 * @brief Positive Z-axis unit vector
 */
const nw4r::math::VEC3 RPUtlDohMath::AXIS_ZP(0.0f, 0.0f, 1.0f);

/**
 * @brief Negative Z-axis unit vector
 */
const nw4r::math::VEC3 RPUtlDohMath::AXIS_ZN(0.0f, 0.0f, -1.0f);

/**
 * @brief 3x4 identity matrix
 */
const nw4r::math::MTX34 RPUtlDohMath::MTX34_IDENT( //
    1.0f, 0.0f, 0.0f, 0.0f,                        //
    0.0f, 1.0f, 0.0f, 0.0f,                        //
    0.0f, 0.0f, 1.0f, 0.0f                         //
);

/**
 * @brief 3x3 identity matrix
 */
const nw4r::math::MTX33 RPUtlDohMath::MTX33_IDENT( //
    1.0f, 0.0f, 0.0f,                              //
    0.0f, 1.0f, 0.0f,                              //
    0.0f, 0.0f, 1.0f                               //
);

/**
 * @brief Identity quaternion
 */
const nw4r::math::QUAT RPUtlDohMath::QUAT_IDENT(0.0f, 0.0f, 0.0f, 1.0f);
