#include "Spotlight.hpp"
#include <math.h>

Spotlight::Spotlight() : Point()
{}

Spotlight::Spotlight(float c) : Point(c)
{}

Spotlight::Spotlight(float r, float g, float b) : Point(r, g, b)
{}

Spotlight::Spotlight(const RGBColor& c) : Point(c)
{}

void Spotlight::set_theta(float t) {
    theta = t;
}

void Spotlight::set_direction(float c) {
    dir = Vector3D(c, c, c);
}

void Spotlight::set_direction(float x, float y, float z) {
  dir = Vector3D(x, y, z);
}

void Spotlight::set_direction(const Vector3D& p) {
    dir = p;
}

Vector3D Spotlight::get_direction(const ShadeInfo& s) const {
  Vector3D vecDir = (position - s.hit_point);
  vecDir.normalize();
  float val = acos(dir * vecDir);           //calculates the inverse cosine or the angle

  if (val <= theta) {
    return vecDir;
  }
  return dir;
}

RGBColor Spotlight::L() const {
    return ls * color;
}
