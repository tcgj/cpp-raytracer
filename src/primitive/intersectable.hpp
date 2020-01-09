#ifndef INTERSECTABLE_HPP
#define INTERSECTABLE_HPP

#include "ray.hpp"

struct RayInteraction {
    float t;
    Point3 point;
    Vec3 normal;
};

class Intersectable {
public:
    virtual bool intersects(const Ray& r, float tMin, float tMax, RayInteraction& ri) const = 0;
};

#endif // INTERSECTABLE_HPP