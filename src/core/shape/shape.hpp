#pragma once

#include "system/system.hpp"
#include "geometry/aabb.hpp"
#include "geometry/transform.hpp"
#include "interaction/surfaceinteraction.hpp"

namespace TK {
    class Shape {
    public:
        Shape(const Transform *worldTransform, bool invertNormals = false)
            : worldTransform(worldTransform), invertNormals(invertNormals) {}
        virtual ~Shape();

        virtual tkAABBf objectBoundingBox() const = 0;
        virtual tkAABBf worldBoundingBox() const;
        virtual bool intersect(const Ray &r, tkFloat *tHit,
                               SurfaceInteraction *interaction) const = 0;
        virtual bool hasIntersect(const Ray &r) const;

    protected:
        const Transform *worldTransform = nullptr;
        bool invertNormals;
    };

    // Default inefficient intersection test
    inline bool Shape::hasIntersect(const Ray &r) const {
        tkFloat tHit;
        SurfaceInteraction interaction;
        return intersect(r, &tHit, &interaction);
    }

    inline tkAABBf Shape::worldBoundingBox() const {
        return (*worldTransform)(objectBoundingBox());
    }
} // namespace TK