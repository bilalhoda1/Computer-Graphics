#include "Matte.h"
#include "../BRDF/Lambertian.hpp"
#include "../world/World.hpp"
#include "../lights/Light.hpp"

Matte::Matte() : Material(), ambient_brdf(new Lambertian), diffuse_brdf(new Lambertian)
{}

Matte::Matte(const Matte& m) : Material(m) {
    if (m.ambient_brdf)
        ambient_brdf = m.ambient_brdf->clone();
    else
        ambient_brdf = nullptr;

    if (m.diffuse_brdf)
        diffuse_brdf = m.diffuse_brdf->clone();
    else
        diffuse_brdf = nullptr;
}

Matte& Matte::operator=(const Matte& rhs) {
    if (this == &rhs)
		return (*this);

	Material::operator=(rhs);

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = nullptr;
	}

	if (rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = nullptr;
	}

	if (rhs.diffuse_brdf)
		diffuse_brdf = rhs.diffuse_brdf->clone();

	return (*this);
}

Matte* Matte::clone() const {
    return (new Matte(*this));
}

// sets Lambertian::kd
void Matte::set_ka(const float ka) {
    ambient_brdf->set_kd(ka);
}

void Matte::set_kd(const float kd) {
    diffuse_brdf->set_kd(kd);
}

void Matte::set_cd(const RGBColor c) {
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

void Matte::set_cd(const float r, const float g, const float b) {
    ambient_brdf->set_cd(r, g, b);
    diffuse_brdf->set_cd(r, g, b);
}

void Matte::set_cd(const float c) {
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

RGBColor Matte::shade(const ShadeInfo& si) const {
    Vector3D wo = -si.ray.d;
    RGBColor L = ambient_brdf->rho(si, wo);
    int num_lights = si.w->lights.size();

    // check all the lights
    for (int i = 0; i < num_lights; i++) {
        Vector3D wi = si.w->lights[i]->get_direction(si);
        float ndotwi = si.normal * wi;

        if (ndotwi > 0.0) {
            bool in_shadow = false;

            if (si.w->lights[i]->casts_shadows()) {
                Ray shadowRay(si.hit_point, wi);
                in_shadow = si.w->lights[i]->in_shadow(shadowRay, si);
            }
            if (!in_shadow)
                 L += diffuse_brdf->f(si, wo, wi) * si.w->lights[i]->L() * ndotwi;
        }
    }
    return (L);
}

Matte::~Matte() {
    if (ambient_brdf){
        delete ambient_brdf;
        ambient_brdf = NULL;
    }
    if (diffuse_brdf){
        delete diffuse_brdf;
        diffuse_brdf = NULL;
    }
}
