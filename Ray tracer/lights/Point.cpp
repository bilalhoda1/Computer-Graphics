#include "Point.hpp"
#include "../utilities/Vector3D.hpp"
#include "../world/World.hpp"
#include "../geometry/Geometry.hpp"

Point::Point() : Light()
{}

Point::Point(float c) : Light(c)
{}

Point::Point(float r, float g, float b) : Light(r, g, b)
{}

Point::Point(const RGBColor& c) : Light(c)
{}

void Point::set_position(float c) {
    position = Point3D(c, c, c);
}

void Point::set_position(float x, float y, float z) {
    position = Point3D(x, y, z);
}

void Point::set_position(const Point3D& p) {
    position = p;
}

void Point::scale_radiance(const float b) {
   this->ls = b;
}

// normalized direction vector from light source to hit point
Vector3D Point::get_direction(const ShadeInfo& s) const {
  Vector3D value = (position - s.hit_point);
  value.normalize();
  return value;
}

// luminance from this light source at hit Point
RGBColor Point::L() const {
    return ls * color;
}

bool Point::in_shadow(const Ray& ray, const ShadeInfo& si) const {
    float t;
    int num_objects = si.w->geometry.size();
    float d = position.distance(ray.o);

    for (int i = 0; i < num_objects; i++)
        if (si.w->geometry[i]->shadow_hit(ray, t) && t < d)
            return true;
    return false;
}

void Point::set_shadows(bool s) {
    shadows = s;
}
