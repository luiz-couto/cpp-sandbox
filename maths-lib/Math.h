#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <print>
#include <format>
#include <algorithm>

#define SQ(x) ((x) * (x))

template<typename T>
static T lerp(const T a, const T b, float t) {
    return a * (1.0f - t) + (b * t);
}

class Vec3 {
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

    float dot(const Vec3 &pVec) const {
        return v[0] * pVec.v[0] + v[1] * pVec.v[1] + v[2] * pVec.v[2];
    }

    Vec3 cross(const Vec3 &v1) {
        return Vec3(v1.v[1] * v[2] - v1.v[2] * v[1], v1.v[2] * v[0] - v1.v[0] * v[2], v1.v[0] * v[1] - v1.v[1] * v[0]);
    }

    float Max() const {
        return std::max(std::max(x, y), z);
    }

    float Min() const {
        return std::min(std::min(x, y), z);
    }
};

float dot(const Vec3 &a, const Vec3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
};

Vec3 Max(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(
        std::max(v1.x, v2.x),
        std::max(v1.y, v2.y),
        std::max(v1.z, v2.z)
    );
};

Vec3 Min(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(
        std::min(v1.x, v2.x),
        std::min(v1.y, v2.y),
        std::min(v1.z, v2.z)
    );
};

template <>
struct std::formatter<Vec3> : std::formatter<float> {
auto format(const Vec3& v, auto& ctx) const {
    return std::format_to(ctx.out(), "Vec3[{}, {}, {}]", v.x, v.y, v.z);
}};

class Vec4 {
    public:
    union
    {
        float v[4];
        struct { float x, y, z, w; };
    };

    Vec4() : x(0), y(0), z(0), w(0) {}
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Vec4 operator+(const Vec4 &pVec) const {
        return Vec4(v[0] + pVec.v[0], v[1] + pVec.v[1], v[2] + pVec.v[2], v[3] + pVec.v[3]); 
    }

    Vec4 operator+(const float scalar) const {
        return Vec4(v[0] + scalar, v[1] + scalar, v[2] + scalar, v[3] + scalar); 
    }

    Vec4& operator+=(const Vec4& pVec) {
        v[0] += pVec.v[0];
        v[1] += pVec.v[1];
        v[2] += pVec.v[2];
        v[3] += pVec.v[3];
        return *this;
    }

    Vec4& operator+=(const float scalar) {
        v[0] += scalar;
        v[1] += scalar;
        v[2] += scalar;
        v[3] += scalar;
        return *this;
    }

    Vec4 operator*(const Vec4 &pVec) const {
        return Vec4(v[0] * pVec.v[0], v[1] * pVec.v[1], v[2] * pVec.v[2], v[3] * pVec.v[3]); 
    }

    Vec4 operator*(const float scalar) const {
        return Vec4(v[0] * scalar, v[1] * scalar, v[2] * scalar, v[3] * scalar); 
    }

    Vec4& operator*=(const Vec4& pVec) {
        v[0] *= pVec.v[0];
        v[1] *= pVec.v[1];
        v[2] *= pVec.v[2];
        v[3] *= pVec.v[3];
        return *this;
    }

    Vec4& operator*=(const float scalar) {
        v[0] *= scalar;
        v[1] *= scalar;
        v[2] *= scalar;
        v[3] *= scalar;
        return *this;
    }

    Vec4 operator/(const Vec4 &pVec) const {
        return Vec4(v[0] / pVec.v[0], v[1] / pVec.v[1], v[2] / pVec.v[2], v[3] / pVec.v[3]); 
    }

    Vec4 operator/(const float scalar) const {
        return Vec4(v[0] / scalar, v[1] / scalar, v[2] / scalar, v[3] / scalar); 
    }

    Vec4& operator/=(const Vec4& pVec) {
        v[0] /= pVec.v[0];
        v[1] /= pVec.v[1];
        v[2] /= pVec.v[2];
        v[3] /= pVec.v[3];
        return *this;
    }

    Vec4& operator/=(const float scalar) {
        v[0] /= scalar;
        v[1] /= scalar;
        v[2] /= scalar;
        v[3] /= scalar;
        return *this;
    }

    Vec4 operator-(const Vec4 &pVec) const {
        return Vec4(v[0] - pVec.v[0], v[1] - pVec.v[1], v[2] - pVec.v[2], v[3] - pVec.v[3]); 
    }

    Vec4 operator-(const float scalar) const {
        return Vec4(v[0] - scalar, v[1] - scalar, v[2] - scalar, v[3] - scalar); 
    }

    Vec4& operator-=(const Vec4& pVec) {
        v[0] -= pVec.v[0];
        v[1] -= pVec.v[1];
        v[2] -= pVec.v[2];
        v[3] -= pVec.v[3];
        return *this;
    }

    Vec4& operator-=(const float scalar) {
        v[0] -= scalar;
        v[1] -= scalar;
        v[2] -= scalar;
        v[3] -= scalar;
        return *this;
    }

    Vec4 operator-() const {
        return Vec4(-v[0], -v[1], -v[2], -v[3]);
    }

    float length() const {
        return std::sqrt(SQ(x) + SQ(y) + SQ(z) + SQ(w));
    }

    float lengthSquared() const {
        return SQ(x) + SQ(y) + SQ(z) + SQ(w);
    }

    Vec4 normalize(void) {
        float len = 1.0f / sqrtf(SQ(x) + SQ(y) + SQ(z) + SQ(w)); 
        return Vec4(x * len, y * len, z * len, w * len);
    }

    float normalize_GetLength() {
        float length = sqrtf(SQ(x) + SQ(y) + SQ(z) + SQ(w)); 
        float len = 1.0f / length;
        v[0] *= len; v[1] *= len; v[2] *= len; v[3] *= len;
        return length;
    }

    float Max() const {
        return std::max(std::max(x, y), std::max(z, w));
    }

    float Min() const {
        return std::min(std::min(x, y), std::min(z, w));
    }
};

Vec4 Max(const Vec4 &v1, const Vec4 &v2) {
    return Vec4(
        std::max(v1.x, v2.x),
        std::max(v1.y, v2.y),
        std::max(v1.z, v2.z),
        std::max(v1.w, v2.w)
    );
};

Vec4 Min(const Vec4 &v1, const Vec4 &v2) {
    return Vec4(
        std::min(v1.x, v2.x),
        std::min(v1.y, v2.y),
        std::min(v1.z, v2.z),
        std::min(v1.w, v2.w)
    );
};

template <>
struct std::formatter<Vec4> : std::formatter<float> {
auto format(const Vec4& v, auto& ctx) const {
    return std::format_to(ctx.out(), "Vec4[{}, {}, {}, {}]", v.x, v.y, v.z, v.w);
}};