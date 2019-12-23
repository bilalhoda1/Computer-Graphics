#pragma once

/**
    Courtesy Kevin Suffern
*/

#include "BRDF.hpp"

class GlossySpecular : public BRDF {
    private:
        float ks;
        RGBColor cs;

    public:
        // constructor
        GlossySpecular();
        // copy constructor
        GlossySpecular(const GlossySpecular& gs);
        // virtual copy constructor
        virtual GlossySpecular* clone() const;
        // destructor
        virtual ~GlossySpecular() = default;

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

        void set_ks(const float ks);
        void set_exp(const float exp);
        void set_cs(const RGBColor& c);
        void set_cs(const float r, const float g, const float b);
        void set_cs(const float c);
};
