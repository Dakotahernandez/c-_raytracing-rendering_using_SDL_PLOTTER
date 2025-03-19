#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray {
public:
    Vec3 orig;
    Vec3 dir;
    
    Ray() {}
    Ray(const Vec3& origin, const Vec3& direction) : orig(origin), dir(direction) {}
    
    // Returns the point along the ray at parameter t
    Vec3 at(double t) const {
        return orig + t * dir;
    }
};

#endif // RAY_H

