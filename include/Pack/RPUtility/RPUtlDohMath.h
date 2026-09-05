#ifndef RP_UTILITY_DOH_MATH_H
#define RP_UTILITY_DOH_MATH_H
#include <Pack/types_pack.h>

#include <nw4r/math.h>

/**
 * @brief Dohta's math utilities
 */
class RPUtlDohMath {
public:
    /**
     * @brief Axis priority order during orthonormalization
     */
    enum AxisOrder {
        AxisOrder_XY, //! X-axis is preserved, Y-axis is the reference
        AxisOrder_XZ, //! X-axis is preserved, Z-axis is the reference

        AxisOrder_YZ, //! Y-axis is preserved, Z-axis is the reference
        AxisOrder_YX, //! Y-axis is preserved, X-axis is the reference

        AxisOrder_ZX, //! Z-axis is preserved, X-axis is the reference
        AxisOrder_ZY, //! Z-axis is preserved, Y-axis is the reference
    };

    /**
     * @brief Matrix axis index
     */
    enum AxisType {
        AxisType_X, //! X-axis
        AxisType_Y, //! Y-axis
        AxisType_Z, //! Z-axis
    };

public:
    /**
     * @brief Sets the specified local axis of the input matrix
     *
     * @param pMtx Matrix
     * @param axis Axis index
     * @param pBase Base vector
     */
    static void MTX34SetBase(nw4r::math::MTX34* pMtx, AxisType axis,
                             const nw4r::math::VEC3* pBase);

    /**
     * @brief Constructs a right-handed orthonormal basis from the local axes of
     * the specified matrix
     *
     * @param[out] pOut Output matrix
     * @param pIn Input matrix
     * @param order Axis priority order
     */
    static void MTX34Normalize(nw4r::math::MTX34* pOut,
                               const nw4r::math::MTX34* pIn, AxisOrder order);

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
    static void GetMidPoint(nw4r::math::VEC3* pMidPoint, f32* pDistance,
                            const nw4r::math::VEC3& rBendDir,
                            const nw4r::math::VEC3& rPointA,
                            const nw4r::math::VEC3& rPointB, f32 lengthA,
                            f32 lengthB);

public:
    //! Zero vector (3D)
    static const nw4r::math::VEC3 VEC3_ZERO;
    //! Zero vector (2D)
    static const nw4r::math::VEC2 VEC2_ZERO;

    //! Positive X-axis unit vector
    static const nw4r::math::VEC3 AXIS_XP;
    //! Negative X-axis unit vector
    static const nw4r::math::VEC3 AXIS_XN;

    //! Positive Y-axis unit vector
    static const nw4r::math::VEC3 AXIS_YP;
    //! Negative Y-axis unit vector
    static const nw4r::math::VEC3 AXIS_YN;

    //! Positive Z-axis unit vector
    static const nw4r::math::VEC3 AXIS_ZP;
    //! Negative Z-axis unit vector
    static const nw4r::math::VEC3 AXIS_ZN;

    //! 3x4 identity matrix
    static const nw4r::math::MTX34 MTX34_IDENT;
    //! 3x3 identity matrix
    static const nw4r::math::MTX33 MTX33_IDENT;
    //! Identity quaternion
    static const nw4r::math::QUAT QUAT_IDENT;

    //! Float close to zero for tolerance checks
    static const f32 FLOAT_EPSILON;
};

#endif
