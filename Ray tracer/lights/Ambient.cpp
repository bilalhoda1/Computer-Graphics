#include "Ambient.hpp"
#include "../utilities/Vector3D.hpp"
#include "../world/World.hpp"

Ambient::Ambient() : Light()
{}

Ambient* Ambient::clone() const {
    return new Ambient(*this);
}

Ambient::Ambient(float c) : Light(c)
{}

Ambient::Ambient(float r, float g, float b) : Light(r, g, b)
{}

Ambient::Ambient(const RGBColor& c) : Light(c)
{}

Vector3D Ambient::get_direction(const ShadeInfo& s) const {
    return Vector3D(0);
}

RGBColor Ambient::L() const {
    return (ls * color);
}

void Ambient::scale_radiance(const float b) {
   ls = b;
}

bool Ambient::in_shadow(const Ray& ray, const ShadeInfo& si) const {
    return false;
}
