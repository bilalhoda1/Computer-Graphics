#pragma once

/**
    Courtesy Kevin Suffern
*/

#include "BRDF.hpp"

class Lambertian : public BRDF {
    private:
        float kd;     // diffuse coefficient
        RGBColor cd;  // diffuse color

    public:
        // constructor
        Lambertian();
        // copy constructor
        Lambertian(const Lambertian& l);
        // virtual copy constructor
        virtual Lambertian* clone() const;
        // destructor
        virtual ~Lambertian() = default;

        virtual RGBColor f(const ShadeInfo& sinfo,
                           const Vector3D& wo,
                           const Vector3D& wi) const;
        virtual RGBColor sample_f(const ShadeInfo& sinfo,
                                  const Vector3D& wo,
                                  Vector3D& wi) const;
        virtual RGBColor sample_f(const ShadeInfo& sinfo,
                                  const Vector3D& wo,
                                  Vector3D& wi, float& pdf) const;
        virtual RGBColor rho(const ShadeInfo& sinfo, const Vector3D& wo) const;

        void set_ka(const float k);
        void set_kd(const float k);
        void set_cd(const RGBColor& c);
        void set_cd(const float r, const float g, const float b);
        void set_cd(const float c);
};
