#include <sstream>
#include "../utilities/Ray.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/BBox.hpp"
#include "Plane.hpp"

Plane::Plane() : a(0), n(0,0,1)
{}

Plane::Plane(const Point3D& pt, const Vector3D& n) {
    a = pt;
    this->n = n;
    this->n.normalize();
}

Plane::Plane(const Plane& object) : a(object.a), n(object.n)
{}

Plane& Plane::operator=(const Plane& rhs) {
    a = rhs.a;
    n = rhs.n;
    return *this;
}

std::string Plane::to_string() const {
    std::stringstream stream;
    stream << "Point a: (" << a.x << "," << a.y << "," << a.z << ")" << '\n';
    stream << "Normal n: (" << n.x << "," << n.y << "," << n.z << ")";
    return stream.str();
}

bool Plane::hit(const Ray& ray, float& t, ShadeInfo& s) const {
    float _t = ((a - ray.o)*n)/(ray.d * n);

    if (_t > kEpsilon) {
        t = _t;
        s.hit_point = ray.o + (t*ray.d);
        s.normal = n;
        s.normal.normalize();
        s.ray = ray;
        s.t = t;
        return true;
    }
    return false;
}

BBox Plane::getBBox() const {
    BBox box;
    return box;
}

Point3D Plane::getCenter() const {
    return a;
}

bool Plane::shadow_hit(const Ray& ray, float& t) const {
    float _t = ((a - ray.o)*n)/(ray.d * n);

    if (_t > kEpsilon) {
        t = _t;
        return true;
    }
    return false;
}
