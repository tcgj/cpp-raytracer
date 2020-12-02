#pragma once

#include "core/shape.hpp"

namespace TK {
    class Sphere : public Shape {
    public:
        Sphere(const Transform* objectToWorld, tkFloat radius, bool invertNormals = false)
            : Shape(objectToWorld, invertNormals), radius(radius) {}

        tkAABBf objectBoundingBox() const override;
        tkFloat surfaceArea() const override;
        bool intersect(const Ray& r, tkFloat* tHit, SurfaceInteraction* interaction) const override;
        bool hasIntersect(const Ray& r) const override;
        SurfaceInteraction sample(const Interaction& ref, const tkVec2f& samp, tkFloat* pdf) const override;
        tkFloat getPdf(const Interaction& ref, const tkVec3f& wi) const override;

    private:
        tkFloat radius;
    };
}  // namespace TK