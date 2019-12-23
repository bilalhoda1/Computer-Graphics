#include <iostream>
#include "../utilities/Ray.hpp"
#include "../cameras/Camera.hpp"
#include "../world/ViewPlane.hpp"
#include "Simple.hpp"

Simple::Simple(Camera* c_ptr, ViewPlane* v_ptr) {
    this->camera_ptr = c_ptr;
    this->viewplane_ptr = v_ptr;
}

Simple::Simple(const Simple& camera) {
    this->camera_ptr = camera.camera_ptr;
    this->viewplane_ptr = camera.viewplane_ptr;
}

Simple& Simple::operator=(const Simple& other) {
    this->camera_ptr = other.camera_ptr;
    this->viewplane_ptr = other.viewplane_ptr;
    return *this;
}

std::vector<Ray> Simple::get_rays(int px, int py) const {
    std::vector<Ray> rays;
    Ray r;
    Point3D origin;

    Vector3D dif = viewplane_ptr->bottom_right - viewplane_ptr->top_left;
    double divX = (double)px/(double)(viewplane_ptr->hres);
    double divY = (double)py/(double)(viewplane_ptr->vres);
    origin = viewplane_ptr->top_left + Vector3D(divX * dif.x, divY * dif.y, 0);

    r.o = origin;
    r.d = camera_ptr->get_direction(origin);
    r.d.normalize();
    rays.push_back(r);
    return rays;
}
