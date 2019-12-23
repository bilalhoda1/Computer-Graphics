#include "../cameras/Perspective.hpp"

#include "../tracer/Basic.h"

#include "../geometry/Sphere.hpp"

#include "../materials/Cosine.hpp"

#include "../samplers/Simple.hpp"
#include "../samplers/Regular.hpp"

#include "../materials/Matte.h"
#include "../materials/Reflective.hpp"

#include "../utilities/Point3D.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"

#include "../lights/Ambient.hpp"
#include "../lights/Point.hpp"
#include "../lights/Directional.hpp"

#include "../tracer/Whitted.hpp"

#include "../world/World.hpp"

void World::build(void) {
    // view plane
    vplane.top_left = Point3D(-3, 3, 3);
    vplane.bottom_right = Point3D(3, -3, 3);
    vplane.hres = 1200;
    vplane.vres = 1200;
    vplane.set_maxdepth(12); //depth for recursion

    // Background color.
    bg_color = black;

    // camera and sampler.
    set_camera(new Perspective(0, 0, 25));
    set_tracer(new Whitted(this));
    sampler_ptr = new Simple(camera_ptr, &vplane);

    //Lighting
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);

	Point* light_ptr = new Point;
	light_ptr->set_position(0, 0, 10);
	light_ptr->scale_radiance(20.0);
	add_light(light_ptr);


	Directional* light_ptr1 = new Directional;	// for Figure 15.8(a)
	light_ptr1->set_direction(15, 15, 2.5);
	add_light(light_ptr1);

	// the four spheres
	float ka = 0.75;
	float kd = 0.75;
	float ks = 0.1;
	float e = 20.0;
	float kr = 1.0;

	Reflective* reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(ka);
	reflective_ptr1->set_kd(kd);
	reflective_ptr1->set_ks(ks);
	reflective_ptr1->set_cd(0.168, 0.171, 0.009);    	// pink
	reflective_ptr1->set_exp(e);
	reflective_ptr1->set_kr(kr);

	Sphere* sphere_ptr1 = new Sphere(Point3D(0.0, 1.414, 0.0), 0.866);
	sphere_ptr1->set_material(reflective_ptr1);
	add_geometry(sphere_ptr1);

	Reflective* reflective_ptr2 = new Reflective;
	reflective_ptr2->set_ka(ka);
	reflective_ptr2->set_kd(kd);
	reflective_ptr2->set_cd(0.243, 0.018, 0.164);     	// red
	reflective_ptr2->set_ks(ks);
	reflective_ptr2->set_exp(e);
	reflective_ptr2->set_kr(kr);

	Sphere* sphere_ptr2 = new Sphere(Point3D(0.866, 0.0, -0.5), 0.866);
	sphere_ptr2->set_material(reflective_ptr2);
	add_geometry(sphere_ptr2);

	Reflective* reflective_ptr3 = new Reflective;
	reflective_ptr3->set_ka(ka);
	reflective_ptr3->set_kd(kd);
	reflective_ptr3->set_cd(0.094, 0.1, 0.243);    		// blue
	reflective_ptr3->set_ks(ks);
	reflective_ptr3->set_exp(e);
	reflective_ptr3->set_kr(kr);

	Sphere* sphere_ptr3 = new Sphere(Point3D(-0.866, 0.0, -0.5), 0.866);
	sphere_ptr3->set_material(reflective_ptr3);
	add_geometry(sphere_ptr3);
}
