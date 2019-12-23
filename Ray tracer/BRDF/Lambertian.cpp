#include "Lambertian.hpp"
#include "../utilities/Point3D.hpp"

Lambertian::Lambertian() : BRDF(), kd(0.0), cd(0.0) {
	BRDF::exp = 1.0;
}

Lambertian::Lambertian(const Lambertian& l) : BRDF(), kd(l.kd), cd(l.cd)
{}

Lambertian* Lambertian::clone() const { return (new Lambertian(*this)); }

RGBColor Lambertian::f(const ShadeInfo&,
                       const Vector3D&,
                       const Vector3D&) const {
    return (kd * cd * invPI);
}

RGBColor Lambertian::sample_f(const ShadeInfo& sinfo,
                              const Vector3D&,
                              Vector3D& wi, float& pdf) const {
    Vector3D w = sinfo.normal;
    Vector3D v = Vector3D(0.0034, 1, 0.0071) ^ w;
    v.normalize();
    Vector3D u = v ^ w;

    Point3D sp = BRDF::sample_hemisphere();
    wi = sp.x * u + sp.y * v + sp.z * w;
    wi.normalize();

    pdf = sinfo.normal * wi * invPI;

    return (kd * cd * invPI);
}

RGBColor Lambertian::sample_f(const ShadeInfo&,
                              const Vector3D&,
                              Vector3D&) const {
    return (kd * cd * invPI);
}

RGBColor Lambertian::rho(const ShadeInfo&, const Vector3D&) const {
    return (kd * cd);
}

void Lambertian::set_ka(const float k) { kd = k; }
void Lambertian::set_kd(const float k) { kd = k; }
void Lambertian::set_cd(const RGBColor& c) { cd = c; }

void Lambertian::set_cd(const float r, const float g, const float b) {
    cd.r = r;
    cd.g = g;
    cd.b = b;
}

void Lambertian::set_cd(const float c) {
    cd.r = c;
    cd.g = c;
    cd.b = c;
}
