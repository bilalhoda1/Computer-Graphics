#pragma once

/**
    Courtesy Kevin Suffern
*/

#include "BRDF.hpp"

class PerfectSpecular : public BRDF {
    private:
        float kr;
        RGBColor cr;

    public:
        // constructor
        PerfectSpecular();
        PerfectSpecular(const PerfectSpecular& ps);

        // virtual copy constructor
        virtual PerfectSpecular* clone() const;

        // destructor
        virtual ~PerfectSpecular() = default;
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

        void set_kr(const float k);
        void set_cr(const RGBColor& c);
        void set_cr(const float r, const float g, const float b);
        void set_cr(const float c);
};
