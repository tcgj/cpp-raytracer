#pragma once

#include "system/toki.hpp"
#include "util/mathutil.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "point2.hpp"
#include "point3.hpp"
#include "matrix44.hpp"

#define TK_PI 3.141592653589793
#define TK_INVPI 0.31830988618
#define TK_INV2PI 0.15915494309
#define TK_INV4PI 0.07957747154
#define TK_PIOVER2 1.57079632679
#define TK_PIOVER4 0.78539816339

// Used for small offsets, e.g. shadow epsilon
#define TK_EPSILON (tkFloat)0.00001
// Represents the largest float below 1
#ifdef TK_USE_DOUBLE
#define TK_ONE_MINUS_EPSILON 0x1.fffffffffffffp-1
#else
#define TK_ONE_MINUS_EPSILON 0x1.fffffep-1f
#endif

#define degToRad(x) x * TK_PI / 180.0
#define radToDeg(x) x * 180.0 / TK_PI

namespace TK {
    // Constants
    constexpr tkFloat TK_MAXFLOAT = std::numeric_limits<tkFloat>::max();
    constexpr tkFloat TK_INFINITY = std::numeric_limits<tkFloat>::infinity();

    // Explicit casts
    template <typename T>
    inline Vec2<T>::operator Point2<T>() const {
        return Point2<T>(x, y);
    }
    template <typename T>
    inline Vec2<T>::operator Vec3<T>() const {
        return Vec3<T>(x, y, 0);
    }
    template <typename T>
    inline Vec3<T>::operator Point2<T>() const {
        return Point2<T>(x, y);
    }
    template <typename T>
    inline Vec3<T>::operator Point3<T>() const {
        return Point3<T>(x, y, z);
    }
    template <typename T>
    inline Vec3<T>::operator Vec2<T>() const {
        return Vec2<T>(x, y);
    }
    template <typename T>
    inline Point2<T>::operator Point3<T>() const {
        return Point3<T>(x, y, 0);
    }
    template <typename T>
    inline Point2<T>::operator Vec2<T>() const {
        return Vec2<T>(x, y);
    }
    template <typename T>
    inline Point3<T>::operator Point2<T>() const {
        return Point2<T>(x, y);
    }
    template <typename T>
    inline Point3<T>::operator Vec2<T>() const {
        return Vec2<T>(x, y);
    }
    template <typename T>
    inline Point3<T>::operator Vec3<T>() const {
        return Vec3<T>(x, y, z);
    }
} // namespace TK
