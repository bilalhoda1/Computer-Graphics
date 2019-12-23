#include "PerfectSpecular.hpp"

PerfectSpecular::PerfectSpecular() : BRDF(), kr(0.0), cr(1.0)
{}

PerfectSpecular::PerfectSpecular(const PerfectSpecular& ps)
    : BRDF(), kr(ps.kr), cr(ps.cr)
{}

PerfectSpecular* PerfectSpecular::clone() const {
    return (new PerfectSpecular(*this));
}

RGBColor PerfectSpecular::f(const ShadeInfo&,
                            const Vector3D&,
                            const Vector3D&) const {
    return black;
}

RGBColor PerfectSpecular::sample_f(const ShadeInfo& sinfo,
                                   const Vector3D& wo,
                                   Vector3D& wi, float& pdf) const {
    wi = -wo + 2.0 * sinfo.normal * (sinfo.normal * wo);
    pdf = fabs(sinfo.normal * wi);
    return (kr * cr / fabs(sinfo.normal * wi));
}

RGBColor PerfectSpecular::sample_f(const ShadeInfo& sinfo,
                                   const Vector3D& wo,
                                   Vector3D& wi) const {
    wi = -wo + 2.0 * sinfo.normal * (sinfo.normal * wo);
    return (kr * cr / fabs(sinfo.normal * wi));
}

RGBColor PerfectSpecular::rho(const ShadeInfo&, const Vector3D&) const {
    return black;
}

void PerfectSpecular::set_kr(const float k) { kr = k; }
void PerfectSpecular::set_cr(const RGBColor& c) { cr = c; }

void PerfectSpecular::set_cr(const float r, const float g, const float b) {
    cr.r = r;
    cr.g = g;
    cr.b = b;
}

void PerfectSpecular::set_cr(const float c) {
    cr.r = c;
    cr.g = c;
    cr.b = c;
}
