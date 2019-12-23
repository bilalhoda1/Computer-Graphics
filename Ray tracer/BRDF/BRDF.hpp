#pragma once

/**
    Courtesy Kevin Suffern
*/

#include <math.h>
#include <random>
#include "../utilities/Constants.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Vector3D.hpp"

/**
   This file declares the BRDF class which is an abstract class for concrete
   BRDFs to inherit from.

   Courtesy Kevin Suffern.
*/

class BRDF {
    protected:
        float exp;

    public:
        // constructors.
        BRDF() = default;

        // copy constructor and assignment operator.
        BRDF(const BRDF& camera) = default;
        BRDF& operator=(const BRDF& other) = default;

        // virtual copy constructor.
        virtual BRDF* clone() const = 0;

        // destructor.
        virtual ~BRDF() = default;

        // get colors.
        virtual RGBColor f(const ShadeInfo& sinfo,
                           const Vector3D& wo,
                           const Vector3D& wi) const = 0;
        virtual RGBColor sample_f(const ShadeInfo& sinfo,
                                  const Vector3D& wo,
                                  Vector3D& wi) const = 0;
        virtual RGBColor sample_f(const ShadeInfo& sinfo,
                                  const Vector3D& wo,
                                  Vector3D& wi, float& pdf) const = 0;
        virtual RGBColor rho(const ShadeInfo& sinfo, const Vector3D& wo) const = 0;

        Point3D sample_hemisphere() const;
};

inline Point3D BRDF::sample_hemisphere() const {
    std::uniform_real_distribution<double> unif(-1.0, 1.0);
    std::random_device rd;

    double x = unif(rd);
    double y = unif(rd);

    float cos_phi = cos(2.0 * PI * x);
    float sin_phi = sin(2.0 * PI * x);
    float cos_theta = pow((1.0 - y), 1.0 / (exp + 1.0));
    float sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    float pu = sin_theta * cos_phi;
    float pv = sin_theta * sin_phi;
    float pw = cos_theta;

    return Point3D(pu, pv, pw);
}
