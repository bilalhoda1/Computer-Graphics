#include "Random.h"
#include "../utilities/Ray.hpp"
#include "../cameras/Camera.hpp"
#include "../world/ViewPlane.hpp"
#include "../utilities/Constants.hpp"

Random::Random(Camera* c_ptr, ViewPlane* v_ptr, int n) {
    this->camera_ptr = c_ptr;
    this->viewplane_ptr = v_ptr;
    this->num_rays = n;
}

Random::Random(const Random& camera) {
    this->camera_ptr = camera.camera_ptr;
    this->viewplane_ptr = camera.viewplane_ptr;
}

Random& Random::operator=(const Random& other) {
    this->camera_ptr = other.camera_ptr;
    this->viewplane_ptr = other.viewplane_ptr;
    this->num_rays = other.num_rays;
    return *this;
}

std::vector<Ray> Random::get_rays(int px, int py) const {
    std::vector<Ray> rays;

    for (int i = 0; i < num_rays; i++) {
        for (int j = 0; j < num_rays; j++) {
            Vector3D dif = viewplane_ptr->bottom_right - viewplane_ptr->top_left;
            double divX = (double)px/(double)(viewplane_ptr->hres);
            double divY = (double)py/(double)(viewplane_ptr->vres);
            double randX = (double)rand() * invRAND_MAX;
            double randY = (double)rand() * invRAND_MAX;
            Point3D origin(viewplane_ptr->top_left + Vector3D(divX * dif.x + randX, divY * dif.y + randY, 0));
            Ray r(origin, camera_ptr->get_direction(origin));
            r.d.normalize();
            rays.push_back(r);
        }
    }
    return rays;
}
