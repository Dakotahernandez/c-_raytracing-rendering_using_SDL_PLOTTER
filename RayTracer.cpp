#include "RayTracer.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vec3.h"
#include <algorithm>
#include <cmath>

// Utility to clamp color channels [0, 1) → [0, 255] for ARGB
static uint32_t toARGB(const Vec3& color) {
    auto clamp = [](double x) -> int {
        return static_cast<int>(std::max(0.0, std::min(0.999, x)) * 256);
    };
    int r = clamp(color.x);
    int g = clamp(color.y);
    int b = clamp(color.z);
    // Alpha channel set to 255 (fully opaque).
    return (255 << 24) | (r << 16) | (g << 8) | b;
}

// Lambertian shading for a single sphere with a moving light source
static Vec3 ray_color(const Ray& r, const Sphere& sphere, const Vec3& lightPos) {
    double t_hit;
    if (sphere.hit(r, 0.001, 1000.0, t_hit)) {
        // Intersection
        Vec3 hit_point = r.at(t_hit);
        Vec3 normal = unit_vector(hit_point - sphere.center);
        
        // Basic Lambertian shading:
        // color = (ambient + diffuse) * sphereColor
        //   where diffuse = kd * max(0, dot(N, L)) and L = unit(lightPos - hitPoint)
        
        // Sphere base color
        Vec3 sphereColor(1.0, 0.2, 0.2); // red-ish
        
        // Light direction
        Vec3 L = lightPos - hit_point;
        double dist2 = dot(L, L);   // squared distance to light
        L = unit_vector(L);
        
        // Lambert factor
        double lambert = std::max(0.0, dot(normal, L));
        
        // Simple attenuation based on distance (optional)
        double attenuation = 1.0 / (1.0 + 0.1 * dist2);
        
        double ambient = 0.1;
        double kd = 0.9;
        double intensity = ambient + kd * lambert;
        
        Vec3 color = sphereColor * (intensity * attenuation);
        return color;
    }
    
    // If no hit, return a background gradient (white to sky-blue)
    Vec3 unit_dir = unit_vector(r.dir);
    double t = 0.5 * (unit_dir.y + 1.0);
    return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

RayTracer::RayTracer(int w, int h) : width(w), height(h), lightPos(0,0,-2) {}

void RayTracer::setLightPosition(const Vec3& lp) {
    lightPos = lp;
}

void RayTracer::render(uint32_t* pixels) {
    // Camera setup
    Vec3 origin(0, 0, 0);
    double viewport_height = 2.0;
    double viewport_width = double(width) / double(height) * viewport_height;
    double focal_length = 1.0;
    
    Vec3 horizontal(viewport_width, 0, 0);
    Vec3 vertical(0, viewport_height, 0);
    Vec3 lower_left_corner = origin
                             - horizontal * 0.5
                             - vertical * 0.5
                             - Vec3(0, 0, focal_length);
    
    // Sphere at z = -5 for a bit more distance
    Sphere sphere(Vec3(0, 0, -5), 1.0);
    
    // Ray trace each pixel
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            double u = double(i) / (width - 1);
            double v = double(j) / (height - 1);
            
            Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            Vec3 color = ray_color(r, sphere, lightPos);
            
            pixels[j * width + i] = toARGB(color);
        }
    }
}

