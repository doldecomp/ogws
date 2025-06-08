#ifndef EGG_MATH_VECTOR_H
#define EGG_MATH_VECTOR_H
#include <egg/types_egg.h>

#include <egg/math/eggMath.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

namespace EGG {

class Vector2f : public nw4r::math::VEC2 {
public:
    static const Vector2f zero;
    static const Vector2f ex;
    static const Vector2f ey;

public:
    Vector2f() {}
    Vector2f(const nw4r::math::VEC2& rVec) : VEC2(rVec) {}
    Vector2f(f32 fx, f32 fy) : VEC2(fx, fy) {}
    ~Vector2f() {}

    operator Vec*() {
        return reinterpret_cast<Vec*>(this);
    }
    operator const Vec*() const {
        return reinterpret_cast<const Vec*>(this);
    }

    f32& operator()(int i) {
        return reinterpret_cast<f32*>(&x)[i];
    }
    const f32 operator()(int i) const {
        return reinterpret_cast<const f32*>(&x)[i];
    }

    void set(f32 fx, f32 fy) {
        x = fx;
        y = fy;
    }

    Vector2f& operator=(const Vector2f& rRhs) {
        x = rRhs.x;
        y = rRhs.y;
        return *this;
    }

    Vector2f operator-() const {
        return Vector2f(-x, -y);
    }

    Vector2f operator+(const Vector2f& rRhs) const {
        return Vector2f(x + rRhs.x, y + rRhs.y);
    }
    Vector2f operator-(const Vector2f& rRhs) const {
        return Vector2f(x - rRhs.x, y - rRhs.y);
    }

    Vector2f operator*(f32 scale) const {
        return Vector2f(x * scale, y * scale);
    }
    Vector2f operator/(f32 scale) const {
        f32 inv = 1 / scale;
        return Vector2f(x * inv, y * inv);
    }

    friend Vector2f operator*(f32 f, const Vector2f& rVec) {
        return Vector2f(rVec.x * f, rVec.y * f);
    }

    Vector2f& operator+=(const Vector2f& rRhs) {
        x += rRhs.x;
        y += rRhs.y;
        return *this;
    }
    Vector2f& operator-=(const Vector2f& rRhs) {
        x -= rRhs.x;
        y -= rRhs.y;
        return *this;
    }

    Vector2f& operator*=(f32 scale) {
        x *= scale;
        y *= scale;
        return *this;
    }
    Vector2f& operator/=(f32 scale) {
        f32 inv = 1 / scale;
        x *= inv;
        y *= inv;
        return *this;
    }

    bool operator==(const Vector2f& rRhs) const {
        return x == rRhs.x && y == rRhs.y;
    }
    bool operator!=(const Vector2f& rRhs) const {
        return x != rRhs.x || y != rRhs.y;
    }

    void vtx() const {
        GXPosition3f32(x, y, 0.0f);
    }
    void tex() const {
        GXTexCoord2f32(x, y);
    }

    void multScalar(f32 scale) {
        x *= scale;
        y *= scale;
    }
    void divScalar(f32 scale) {
        f32 inv = 1 / scale;
        x *= inv;
        y *= inv;
    }

    f32 squaredLength() const {
        return x * x + y * y;
    }
    f32 length() const {
        return Math<f32>::sqrt(squaredLength());
    }

    f32 dot(const Vector2f& rOther) const {
        return x * rOther.x + y * rOther.y;
    }
    f32 distance(const Vector2f& rOther) const {
        f32 fx = rOther.x - x * rOther.x - x;
        f32 fy = rOther.y - y * rOther.y - y;
        return Math<f32>::sqrt(fx + fy);
    }
};

class Vector3f : public nw4r::math::VEC3 {
public:
    static const Vector3f zero;
    static const Vector3f ex;
    static const Vector3f ey;
    static const Vector3f ez;

public:
    Vector3f() {}
    Vector3f(const nw4r::math::VEC3& rVec) : VEC3(rVec) {}
    Vector3f(f32 fx, f32 fy, f32 fz) : VEC3(fx, fy, fz) {}
    ~Vector3f() {}

    operator Vec*() {
        return reinterpret_cast<Vec*>(this);
    }
    operator const Vec*() const {
        return reinterpret_cast<const Vec*>(this);
    }

    f32& operator()(int i) {
        return reinterpret_cast<f32*>(&x)[i];
    }
    const f32 operator()(int i) const {
        return reinterpret_cast<const f32*>(&x)[i];
    }

    void set(f32 fx, f32 fy, f32 fz) {
        x = fx;
        y = fy;
        z = fz;
    }

    Vector3f& operator=(const Vector3f& rRhs) {
        x = rRhs.x;
        y = rRhs.y;
        z = rRhs.z;
        return *this;
    }

    Vector3f operator-() const {
        return Vector3f(-x, -y, -z);
    }

    Vector3f operator+(const Vector3f& rRhs) const {
        return Vector3f(x + rRhs.x, y + rRhs.y, z + rRhs.z);
    }
    Vector3f operator-(const Vector3f& rRhs) const {
        return Vector3f(x - rRhs.x, y - rRhs.y, z - rRhs.z);
    }

    Vector3f operator*(f32 scale) const {
        return Vector3f(x * scale, y * scale, z * scale);
    }
    Vector3f operator/(f32 scale) const {
        f32 inv = 1 / scale;
        return Vector3f(x * inv, y * inv, z * inv);
    }

    friend Vector3f operator*(f32 f, const Vector3f& rVec) {
        return Vector3f(rVec.x * f, rVec.y * f, rVec.z * f);
    }

    Vector3f& operator+=(const Vector3f& rRhs) {
        x += rRhs.x;
        y += rRhs.y;
        z += rRhs.z;
        return *this;
    }
    Vector3f& operator-=(const Vector3f& rRhs) {
        x -= rRhs.x;
        y -= rRhs.y;
        z -= rRhs.z;
        return *this;
    }

    Vector3f& operator*=(f32 scale) {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }
    Vector3f& operator/=(f32 scale) {
        f32 inv = 1 / scale;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }

    bool operator==(const Vector3f& rRhs) const {
        return x == rRhs.x && y == rRhs.y && z == rRhs.z;
    }
    bool operator!=(const Vector3f& rRhs) const {
        return x != rRhs.x || y != rRhs.y && z != rRhs.z;
    }

    void vtx() const {
        GXPosition3f32(x, y, z);
    }
    void nrm() const {
        GXNormal3f32(x, y, z);
    }

    void multScalar(f32 scale) {
        x *= scale;
        y *= scale;
        z *= scale;
    }
    void divScalar(f32 scale) {
        f32 inv = 1 / scale;
        x *= inv;
        y *= inv;
        z *= inv;
    }

    f32 squaredLength() const {
        return x * x + y * y + z * z;
    }
    f32 length() const {
        return Math<f32>::sqrt(squaredLength());
    }

    f32 dot(const Vector3f& rOther) const {
        return x * rOther.x + y * rOther.y + z * rOther.z;
    }
    Vector3f cross(const Vector3f& rOther) const {
        f32 fx = y * rOther.z - z * rOther.y;
        f32 fy = z * rOther.x - x * rOther.z;
        f32 fz = x * rOther.y - y * rOther.x;
        return Vector3f(fx, fy, fz);
    }
    f32 distance(const Vector3f& rOther) const {
        f32 fx = rOther.x - x * rOther.x - x;
        f32 fy = rOther.y - y * rOther.y - y;
        f32 fz = rOther.z - z * rOther.z - z;
        return Math<f32>::sqrt(fx + fy + fz);
    }

    f32 normalise();
    f32 normalize() {
        return normalise();
    }

    bool isZero(f32 threshold) const {
        return length() <= threshold;
    }
};

} // namespace EGG

#endif
