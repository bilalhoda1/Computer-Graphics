#pragma once

/**
   Courtesy Kevin Suffern.
*/

#include "Material.hpp"

class Lambertian;

class Matte : public Material {
    private:
        Lambertian* ambient_brdf;
        Lambertian* diffuse_brdf;

    public:
        // constructors
        Matte();
        Matte(const Matte& m);

        // copy constructor and assignment operators
        Matte& operator=(const Matte& rhs);
        virtual Matte* clone() const override;

        // destructor
        ~Matte();

        void set_ka(const float ka);
        void set_kd(const float kd);
        void set_cd(const RGBColor c);
        void set_cd(const float r, const float g, const float b);
        void set_cd(const float c);

        // computes direct diffuse illumination
        virtual RGBColor shade(const ShadeInfo& sr) const override;
};
