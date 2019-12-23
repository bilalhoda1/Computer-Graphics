#pragma once

/**
   Courtesy Kevin Suffern.
*/

#include "Material.hpp"

class GlossySpecular;
class Lambertian;

class Phong : public Material {
	public:
		Phong();
		Phong(const Phong& other);

		Phong& operator= (const Phong& rhs);

		virtual Phong* clone() const override;
		virtual ~Phong();

        void set_ka(const float ka);
        void set_kd(const float kd);
        void set_ks(const float ks);
        void set_exp(const float exp);
        void set_cd(const RGBColor c);
        void set_cd(const float r, const float g, const float b);
        void set_cd(const float c);

		virtual RGBColor shade(const ShadeInfo& s)const override;

	protected:
		Lambertian* ambient_brdf;
		Lambertian* diffuse_brdf;
		GlossySpecular*	specular_brdf;
};
