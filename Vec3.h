#ifndef VEC3_H
#define VEC3_H

#include <cmath>

class Vec3 {
public:
    double x, y, z;
    
    Vec3() : x(0), y(0), z(0) {}
    Vec3(double e0, double e1, double e2) : x(e0), y(e1), z(e2) {}
    
    inline Vec3 operator-() const { return Vec3(-x, -y, -z); }
    inline Vec3& operator+=(const Vec3 &v) {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    inline Vec3& operator*=(const double t) {
        x *= t; y *= t; z *= t;
        return *this;
    }
    inline Vec3& operator/=(const double t) {
        return *this *= 1/t;
    }
    inline double length() const { return std::sqrt(x*x + y*y + z*z); }
};

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.x, t*v.y, t*v.z);
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

#endif // VEC3_H

