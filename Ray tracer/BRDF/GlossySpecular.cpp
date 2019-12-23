#include "GlossySpecular.hpp"
#include "../utilities/Point3D.hpp"

GlossySpecular::GlossySpecular()
    : BRDF(), ks(0.0), cs(1.0) {
    BRDF::exp = 3.0;
}

GlossySpecular::GlossySpecular(const GlossySpecular& gs)
    : BRDF(), ks(gs.ks), cs(gs.cs)
{}

GlossySpecular* GlossySpecular::clone() const {
    return (new GlossySpecular(*this));
}

RGBColor GlossySpecular::f(const ShadeInfo& sinfo,
                           const Vector3D& wo,
                           const Vector3D& wi) const {
    RGBColor L;
    Vector3D r(-wi + 2.0 * sinfo.normal * (sinfo.normal * wi));
    if ((r * wo) > 0.0) {
        L = ks * cs * pow((r * wo), exp);
    }
    return L;
}

RGBColor GlossySpecular::sample_f(const ShadeInfo& sinfo,
                                  const Vector3D& wo,
                                  Vector3D& wi, float& pdf) const {
    float ndotwo = sinfo.normal * wo;
    Vector3D r = wo + 2.0 * sinfo.normal * ndotwo;
    Vector3D w = r;
    Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
    u.normalize();
    Vector3D v = u ^ w;
    Point3D sp = BRDF::sample_hemisphere();
    wi = sp.x * u + sp.y * v + sp.z * w;

    if (sinfo.normal * wi < 0.0)
        wi = -sp.x * u - sp.y * v + sp.z * w;

    pdf = (pow(r * wi, exp)) * (sinfo.normal * wi);
    return (ks * cs * (pow(r * wi, exp)));
}

RGBColor GlossySpecular::sample_f(const ShadeInfo& sinfo,
                                  const Vector3D& wo,
                                  Vector3D& wi) const {
    Vector3D r = -wo + 2.0 * sinfo.normal * (sinfo.normal * wo);
    Vector3D w = r;
    Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
    u.normalize();
    Vector3D v = u ^ w;
    Point3D sp = BRDF::sample_hemisphere();
    wi = sp.x * u + sp.y * v + sp.z * w;

    if (sinfo.normal * wi < 0.0)
        wi = -sp.x * u - sp.y * v + sp.z * w;

    return (ks * cs * (pow(r * wi, exp)));
}

RGBColor GlossySpecular::rho(const ShadeInfo&, const Vector3D&) const {
    return black;
}

void GlossySpecular::set_ks(const float k) { ks = k; }
void GlossySpecular::set_exp(const float e) { exp = e; }
void GlossySpecular::set_cs(const RGBColor& c) { cs = c; }

void GlossySpecular::set_cs(const float r, const float g, const float b) {
    cs.r = r;
    cs.g = g;
    cs.b = b;
}

void GlossySpecular::set_cs(const float c) {
    cs.r = c;
    cs.g = c;
    cs.b = c;
}
