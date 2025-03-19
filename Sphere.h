#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"
#include "Ray.h"

class Sphere {
public:
    Vec3 center;
    double radius;
    
    Sphere() : center(), radius(0) {}
    Sphere(const Vec3& c, double r) : center(c), radius(r) {}
    
    // Ray-sphere intersection test.
    // If hit, returns true and writes the hit distance into t_hit.
    bool hit(const Ray& r, double t_min, double t_max, double &t_hit) const;
};

#endif // SPHERE_H

