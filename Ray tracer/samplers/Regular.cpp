#include "Regular.hpp"
#include "../utilities/Ray.hpp"
#include "../cameras/Camera.hpp"
#include "../world/ViewPlane.hpp"
#include <cmath>

Regular::Regular(Camera *c_ptr, ViewPlane *v_ptr, int n)
    : Sampler(c_ptr, v_ptr) {
    num_rays = n;
}

Regular::Regular(const Regular &camera)
    : Sampler(camera.camera_ptr, camera.viewplane_ptr)
{}

Regular& Regular::operator=(const Regular &other) {
    this->camera_ptr = other.camera_ptr;
    this->viewplane_ptr = other.viewplane_ptr;
    this->num_rays = other.num_rays;
    return *this;
}

std::vector<Ray> Regular::get_rays(int px, int py) const {
    int n = (int)sqrt((float)num_rays);
    std::vector<Ray> rays;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Vector3D dif = viewplane_ptr->bottom_right - viewplane_ptr->top_left;
            double divX = (double)px/(double)(viewplane_ptr->hres);
            double divY = (double)py/(double)(viewplane_ptr->vres);
            Point3D origin(viewplane_ptr->top_left + Vector3D(divX * dif.x + (j + 0.5)/n, divY * dif.y + (i + 0.5)/n, 0));
            Ray r(origin, camera_ptr->get_direction(origin));
            r.d.normalize();
            rays.push_back(r);
        }
    }
    return rays;
}
