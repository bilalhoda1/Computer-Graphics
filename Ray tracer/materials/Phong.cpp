#include "Phong.hpp"
#include "../BRDF/GlossySpecular.hpp"
#include "../BRDF/Lambertian.hpp"
#include "../lights/Light.hpp"
#include "../world/World.hpp"

Phong::Phong() : Material(), ambient_brdf(new Lambertian),
                diffuse_brdf(new Lambertian), specular_brdf(new GlossySpecular)
{}

Phong::Phong(const Phong& other) : Material() {
    if (other.ambient_brdf)
        ambient_brdf = other.ambient_brdf->clone();
    else
        ambient_brdf = NULL;
    if (other.diffuse_brdf)
        diffuse_brdf = other.diffuse_brdf->clone();
    else
        diffuse_brdf = NULL;

    if (other.specular_brdf)
        specular_brdf = other.specular_brdf->clone();
    else
        specular_brdf = NULL;
}

Phong& Phong::operator=(const Phong& rhs) {
    if (this == &rhs) {
        return *this;
    }
    if (ambient_brdf) {
        delete ambient_brdf;
        ambient_brdf = NULL;
    }
    if (diffuse_brdf) {
        delete diffuse_brdf;
        diffuse_brdf = NULL;
    }
    if (specular_brdf) {
        delete specular_brdf;
        specular_brdf = NULL;
    }

    if (rhs.ambient_brdf)
        ambient_brdf = rhs.ambient_brdf->clone();
    if (rhs.diffuse_brdf)
        diffuse_brdf = rhs.diffuse_brdf->clone();
    if (rhs.specular_brdf)
        specular_brdf = rhs.specular_brdf->clone();

    return *this;
}

Phong* Phong::clone() const {
    return (new Phong(*this));
}

Phong::~Phong() {
    if (ambient_brdf) {
        delete ambient_brdf;
        ambient_brdf = NULL;
    }
    if (diffuse_brdf) {
        delete diffuse_brdf;
        diffuse_brdf = NULL;
    }
    if (specular_brdf) {
        delete specular_brdf;
        specular_brdf = NULL;
    }
}

void Phong::set_ka(const float ka) {
    ambient_brdf->set_kd(ka);
}

void Phong::set_kd(const float kd) {
    diffuse_brdf->set_kd(kd);
}

void Phong::set_ks(const float ks) {
    specular_brdf->set_ks(ks);
}

void Phong::set_exp(const float exp) {
    specular_brdf->set_exp(exp);
}

void Phong::set_cd(const RGBColor c) {
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

void Phong::set_cd(const float r, const float g, const float b) {
    ambient_brdf->set_cd(r, g, b);
    diffuse_brdf->set_cd(r, g, b);
}

void Phong::set_cd(const float c) {
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

RGBColor Phong::shade(const ShadeInfo& si) const {
	Vector3D wo = -si.ray.d;
	RGBColor L = ambient_brdf->rho(si, wo) * si.w->ambient_ptr->L();
	int num_lights = si.w->lights.size();

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
                L += ( diffuse_brdf->f(si, wo, wi)
                      + specular_brdf->f(si, wo, wi))
                      * si.w->lights[i]->L() * ndotwi;
		}
    }
	return L;
}
