#include "Sphere.h"
#include <cmath>

bool Sphere::hit(const Ray& r, double t_min, double t_max, double &t_hit) const {
    // oc = origin - center
    Vec3 oc = r.orig - center;
    double a = dot(r.dir, r.dir);
    double b = 2.0 * dot(oc, r.dir);
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return false;
    }
    
    double sqrt_disc = std::sqrt(discriminant);
    double t = (-b - sqrt_disc) / (2*a);
    if (t < t_min || t > t_max) {
        t = (-b + sqrt_disc) / (2*a);
        if (t < t_min || t > t_max) {
            return false;
        }
    }
    t_hit = t;
    return true;
}

