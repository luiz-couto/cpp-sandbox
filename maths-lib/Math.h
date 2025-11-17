#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <print>
#include <format>

#define SQ(x) ((x) * (x))

template<typename T>
static T lerp(const T a, const T b, float t){
    return a * (1.0f - t) + (b * t);
}

class Vec3
{
    public:
    union
    {
        float v[3];
        struct { float x, y, z; };
    };

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3 &pVec) const {
        return Vec3(v[0] + pVec.v[0], v[1] + pVec.v[1], v[2] + pVec.v[2]); 
    }

    Vec3 operator+(const float scalar) const {
        return Vec3(v[0] + scalar, v[1] + scalar, v[2] + scalar); 
    }

    Vec3& operator+=(const Vec3& pVec) {
        v[0] += pVec.v[0];
        v[1] += pVec.v[1];
        v[2] += pVec.v[2];
        return *this;
    }

    Vec3& operator+=(const float scalar) {
        v[0] += scalar;
        v[1] += scalar;
        v[2] += scalar;
        return *this;
    }

    Vec3 operator*(const Vec3 &pVec) const {
        return Vec3(v[0] * pVec.v[0], v[1] * pVec.v[1], v[2] * pVec.v[2]); 
    }

    Vec3 operator*(const float scalar) const {
        return Vec3(v[0] * scalar, v[1] * scalar, v[2] * scalar); 
    }

    Vec3& operator*=(const Vec3& pVec) {
        v[0] *= pVec.v[0];
        v[1] *= pVec.v[1];
        v[2] *= pVec.v[2];
        return *this;
    }

    Vec3& operator*=(const float scalar) {
        v[0] *= scalar;
        v[1] *= scalar;
        v[2] *= scalar;
        return *this;
    }

    Vec3 operator/(const Vec3 &pVec) const {
        return Vec3(v[0] / pVec.v[0], v[1] / pVec.v[1], v[2] / pVec.v[2]); 
    }

    Vec3 operator/(const float scalar) const {
        return Vec3(v[0] / scalar, v[1] / scalar, v[2] / scalar); 
    }

    Vec3& operator/=(const Vec3& pVec) {
        v[0] /= pVec.v[0];
        v[1] /= pVec.v[1];
        v[2] /= pVec.v[2];
        return *this;
    }

    Vec3& operator/=(const float scalar) {
        v[0] /= scalar;
        v[1] /= scalar;
        v[2] /= scalar;
        return *this;
    }

    Vec3 operator-(const Vec3 &pVec) const {
        return Vec3(v[0] - pVec.v[0], v[1] - pVec.v[1], v[2] - pVec.v[2]); 
    }

    Vec3 operator-(const float scalar) const {
        return Vec3(v[0] - scalar, v[1] - scalar, v[2] - scalar); 
    }

    Vec3& operator-=(const Vec3& pVec) {
        v[0] -= pVec.v[0];
        v[1] -= pVec.v[1];
        v[2] -= pVec.v[2];
        return *this;
    }

    Vec3& operator-=(const float scalar) {
        v[0] -= scalar;
        v[1] -= scalar;
        v[2] -= scalar;
        return *this;
    }

    Vec3 operator-() const {
        return Vec3(-v[0], -v[1], -v[2]);
    }

    float length() const {
        return std::sqrt(SQ(x) + SQ(y) + SQ(z));
    }

    float lengthSquared() const {
        return SQ(x) + SQ(y) + SQ(z);
    }

    Vec3 normalize(void) {
        float len = 1.0f / sqrtf(SQ(x) + SQ(y) + SQ(z)); 
        return Vec3(x * len, y * len, z * len);
    }

    float normalize_GetLength() {
        float length = sqrtf(SQ(x) + SQ(y) + SQ(z)); 
        float len = 1.0f / length;
        v[0] *= len; v[1] *= len; v[2] *= len;
        return length;
    }
};

template <>
struct std::formatter<Vec3> : std::formatter<float> {
auto format(const Vec3& v, auto& ctx) const {
    return std::format_to(ctx.out(), "Vec3[{}, {}, {}]", v.x, v.y, v.z);
}};