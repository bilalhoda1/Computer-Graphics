#pragma once

/**
    Courtesy Kevin Suffern
*/

#include "Sampler.hpp"

class Regular : public Sampler{
    public:
        Regular() = default;
        Regular(Camera *c_ptr, ViewPlane *v_ptr, int n); // set members.

        // Copy constuctor and assignment operator.
        Regular(const Regular &camera);
        Regular &operator=(const Regular &other);

        // Desctructor.
        virtual ~Regular() = default;

        // Shoot a ray of weight 1 through the center of the pixel.
        std::vector<Ray> get_rays(int px, int py) const override;
};

