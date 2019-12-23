#include "Reflective.hpp"
#include <iostream>
#include "../BRDF/PerfectSpecular.hpp"
#include "../lights/Light.hpp"
#include "../tracer/Tracer.h"
#include "../world/World.hpp"

Reflective::Reflective(void) : Phong(), reflective_brdf(new PerfectSpecular)
{}

Reflective::Reflective(const Reflective& rm) : Phong(rm) {
    if (rm.reflective_brdf)
        reflective_brdf = rm.reflective_brdf->clone();
    else
        reflective_brdf = NULL;
}

Reflective& Reflective::operator=(const Reflective& rhs) {
    if (this == &rhs)
		return (*this);

	Phong::operator=(rhs);

	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();

	return *this;
}

Reflective* Reflective::clone (void) const {
    return new Reflective(*this);
}

Reflective::~Reflective(void) {
    if (reflective_brdf) {
        delete reflective_brdf;
        reflective_brdf = NULL;
    }
}

void Reflective::set_kr(const float k) {
    reflective_brdf->set_kr(k);
}

void Reflective::set_cr(const RGBColor& c) {
    reflective_brdf->set_cr(c);
}

void Reflective::set_cr(const float r, const float g, const float b) {
    reflective_brdf->set_cr(r, g, b);
}

void Reflective::set_cr(const float c) {
    reflective_brdf->set_cr(c);
}

RGBColor Reflective::shade(const ShadeInfo& si) const {
    RGBColor L(Phong::shade(si));           // direct illumination

    Vector3D wo = -si.ray.d;
    Vector3D wi;
    RGBColor fr = reflective_brdf->sample_f(si, wo, wi);
    Ray reflected_ray(si.hit_point, wi);
    reflected_ray.w = si.depth + 1;
    L += fr * si.w->tracer_ptr->trace_ray(reflected_ray, si.depth + 1) * (si.normal * wi);

    return L;
}
