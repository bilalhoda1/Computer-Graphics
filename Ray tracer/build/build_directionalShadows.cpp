/**
    This builds the scene which contains directional shadows.
    Courtesy Kevin Suffern, figure 16.01.
**/
#include "../cameras/Perspective.hpp"
#include "../cameras/Parallel.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"

#include "../tracer/Basic.h"

#include "../lights/Ambient.hpp"
#include "../lights/Point.hpp"
#include "../lights/Directional.hpp"

#include "../materials/Cosine.hpp"
#include "../materials/Matte.h"
#include "../materials/Reflective.hpp"

#include "../samplers/Simple.hpp"
#include "../samplers/Regular.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"

#include "../world/World.hpp"

void
World::build(void) {
	// view plane
    vplane.top_left.x = -200;
    vplane.top_left.y = 200;
    vplane.top_left.z = 100;
    vplane.bottom_right.x = 200;
    vplane.bottom_right.y = -200;
    vplane.bottom_right.z = 100;
    vplane.hres = 600;
    vplane.vres = 600;

    bg_color = black;  // background color.

    // camera and sampler.
    set_camera(new Perspective(0, 100, 200));
    set_tracer(new Basic(this));
    sampler_ptr = new Regular(camera_ptr, &vplane, 16);

    //Lighting
    Directional* dir_ptr = new Directional;
    dir_ptr->set_direction(1, 1, 0);
    add_light(dir_ptr);
    dir_ptr->set_shadows(true);

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.65);
	matte_ptr1->set_cd(1, 1, 0);

	Sphere*	sphere_ptr1 = new Sphere(Point3D(50, -10, 0), 50);
	sphere_ptr1->set_material(matte_ptr1);
	add_geometry(sphere_ptr1);

	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.15);
	matte_ptr2->set_kd(0.5);
	matte_ptr2->set_cd(0, 0.4, 0.2);
	Plane* plane_ptr = new Plane(Point3D(0, -50, 0), Vector3D(0, 1, 0));
	plane_ptr->set_material(matte_ptr2);
	add_geometry(plane_ptr);
}



