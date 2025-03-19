#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <cstdint>
#include "Vec3.h"

class RayTracer {
public:
    RayTracer(int width, int height);
    
    // Render the scene into the provided pixel buffer (32-bit ARGB)
    void render(uint32_t* pixels);
    
    // Set the current light position in world space
    void setLightPosition(const Vec3& lightPos);
    
private:
    int width;
    int height;
    Vec3 lightPos;
};

#endif // RAYTRACER_H

