#ifndef POINT3_HPP
#define POINT3_HPP

class Point3 {
public:
    Point3() : x(0.0f), y(0.0f), z(0.0f) {}
    Point3(float f) : x(f), y(f), z(f) {}
    Point3(float p0, float p1, float p2) : x(p0), y(p1), z(p2) {}
    Point3(const Point3& p) : x(p.x), y(p.y), z(p.z) {}

    // Unary/subscript operators
    const Point3& operator+() const;
    Point3 operator-() const;
    Point3 operator/(float w) const;
    float operator[](int i) const;
    float& operator[](int i);

    // Assignment operators
    Point3& operator=(const Point3& p);
    Point3& operator+=(const Vec3& v);
    Point3& operator-=(const Vec3& v);

    // Explicit cast
    explicit operator Vec3() const;

    union {
        struct { float x, y, z; };
        float data[3];
    };

    static const Point3 zero;
};

inline const Point3 Point3::zero = Point3(0.0f);

inline const Point3& Point3::operator+() const {
    return *this;
}
inline Point3 Point3::operator-() const {
    return Point3(-x, -y, -z);
}
inline Point3 Point3::operator/(float w) const {
    return Point3(x / w, y / w, z / w);
}
inline float Point3::operator[](int i) const {
    return data[i];
}
inline float& Point3::operator[](int i) {
    return data[i];
}

inline Point3& Point3::operator=(const Point3& p) {
    x = p.x;
    y = p.y;
    z = p.z;
    return *this;
}
inline Point3& Point3::operator+=(const Vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}
inline Point3& Point3::operator-=(const Vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

// Additional operations
inline Point3 operator*(const Point3& p, float f) {
    return Point3(p.x * f, p.y * f, p.z * f);
}
inline Point3 operator*(float f, const Point3& p) {
    return Point3(p.x * f, p.y * f, p.z * f);
}
inline Vec3 operator-(const Point3& p1, const Point3& p2) {
    return Vec3(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

// Math
inline float distance(const Point3& p1, const Point3& p2) {
    return (p2 - p1).magnitude();
}

#endif // POINT3_HPP
