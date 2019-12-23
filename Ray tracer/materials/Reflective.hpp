#pragma once

/**
   Courtesy Kevin Suffern.
*/

#include "Phong.hpp"

class PerfectSpecular;

class Reflective : public Phong {
    private:
		PerfectSpecular* reflective_brdf;
    public:
        // constructors
        Reflective(void);
        Reflective(const Reflective& rm);

        // assignment operator
        Reflective& operator= (const Reflective& rhs);

        virtual Reflective* clone (void) const override;

        // destructor
        virtual ~Reflective();

        // set variables
        void set_kr(const float k);
		void set_cr(const RGBColor& c);
		void set_cr(const float r, const float g, const float b);
		void set_cr(const float c);

		virtual RGBColor shade(const ShadeInfo& s) const;
};
