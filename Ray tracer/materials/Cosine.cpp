#include <iostream>
#include "../utilities/Vector3D.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "Cosine.hpp"

Cosine::Cosine() : color(0)
{}

Cosine::Cosine(float c) : color(c)
{}

Cosine::Cosine(float r, float g, float b) : color(r, g, b)
{}

Cosine::Cosine(const RGBColor& c) : color(c)
{}

Cosine::Cosine(const Cosine& other) : color(other.color.r, other.color.g, other.color.b)
{}

Cosine& Cosine::operator=(const Cosine& other) {
    color.r = other.color.r;
	color.g = other.color.g;
	color.b = other.color.b;
    return *this;
}

Cosine* Cosine::clone() const {
    return (new Cosine(*this));
}

RGBColor Cosine::shade(const ShadeInfo& sinfo) const {
    return color * (sinfo.normal * -sinfo.ray.d);
}
