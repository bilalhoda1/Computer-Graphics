#include "../cameras/Perspective.hpp"

#include "../tracer/Basic.h"
#include "../geometry/Sphere.hpp"

#include "../samplers/Simple.hpp"

#include "../materials/Matte.h"
#include "../materials/Reflective.hpp"

#include "../utilities/Point3D.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"

#include "../lights/Ambient.hpp"
#include "../lights/Point.hpp"
#include "../lights/Directional.hpp"

#include "../world/World.hpp"

void World::build(void) {
    // view plane
    vplane.top_left = Point3D(-20, 20, 20);
    vplane.bottom_right = Point3D(20, -20, 20);
    vplane.hres = 480;
    vplane.vres = 480;
    vplane.set_maxdepth(5);

    // Background color.
      bg_color = black;

    RGBColor brown(0.71, 0.40, 0.16);  // brown
    RGBColor lightGreen(0.65, 1, 0.30);
    RGBColor lightPurple(0.65, 0.3, 1);

    // camera and sampler.
    set_camera(new Perspective(0, 0, 50));
    set_tracer(new Basic(this));
    sampler_ptr = new Simple(camera_ptr, &vplane);

	Matte* matte_ptr = new Matte;
	matte_ptr->set_ka(0.45);
	matte_ptr->set_kd(0.75);
	matte_ptr->set_cd(white);   // grey rockets

	float ka = 0.75;
	float kd = 0.75;
	float ks = 0.1;
	float e = 20.0;
	float kr = 1.0;

	Reflective* reflective_ptr = new Reflective;
	reflective_ptr->set_ka(ka);
	reflective_ptr->set_kd(kd);
	reflective_ptr->set_cd(white);    		// white
	reflective_ptr->set_ks(ks);
	reflective_ptr->set_exp(e);
	reflective_ptr->set_kr(kr);

	srand(2);

	for (int i = 0; i < 150; i++){
        float offsetX = (-30) + (rand() % static_cast<int>(35 - (-30) + 1));;
        float offsetY = (-30) + (rand() % static_cast<int>(35 - (-30) + 1));
        Sphere* sphere_ptr = new Sphere(Point3D(offsetX, offsetY, -0.5), 0.25);
        sphere_ptr->set_material(reflective_ptr);
        add_geometry(sphere_ptr);
	}


	Reflective* reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(ka);
	reflective_ptr1->set_kd(kd);
	reflective_ptr1->set_ks(ks);
	reflective_ptr1->set_cd(0.7, 0.7, 0.08);    	// yellow
	reflective_ptr1->set_exp(e);
	reflective_ptr1->set_kr(kr);

	Sphere* sphere_ptr1 = new Sphere(Point3D(15.0, 18, 10.0), 4.866);
	sphere_ptr1->set_material(reflective_ptr1);
	add_geometry(sphere_ptr1);

	Reflective* reflective_ptr2 = new Reflective;
	reflective_ptr2->set_ka(ka);
	reflective_ptr2->set_kd(kd);
	reflective_ptr2->set_cd(0.8, 0.018, 0.164);     	// red
	reflective_ptr2->set_ks(ks);
	reflective_ptr2->set_exp(e);
	reflective_ptr2->set_kr(kr);

	Sphere* sphere_ptr2 = new Sphere(Point3D(10, -8, -0.5), 4.2);
	sphere_ptr2->set_material(reflective_ptr2);
	add_geometry(sphere_ptr2);

	Reflective* reflective_ptr3 = new Reflective;
	reflective_ptr3->set_ka(ka);
	reflective_ptr3->set_kd(kd);
	reflective_ptr3->set_cd(0.094, 0.7, 0.843);    		// blue
	reflective_ptr3->set_ks(ks);
	reflective_ptr3->set_exp(e);
	reflective_ptr3->set_kr(kr);

	Sphere* sphere_ptr3 = new Sphere(Point3D(-5, 8, -0.5), 5.866);
	sphere_ptr3->set_material(reflective_ptr3);
	add_geometry(sphere_ptr3);

	Reflective* reflective_ptr4 = new Reflective;
	reflective_ptr4->set_ka(ka);
	reflective_ptr4->set_kd(kd);
	reflective_ptr4->set_cd(lightPurple);    		//purple
	reflective_ptr4->set_ks(ks);
	reflective_ptr4->set_exp(e);
	reflective_ptr4->set_kr(kr);

	Sphere* sphere_ptr4 = new Sphere(Point3D(-22, 22, -0.5), 4.866);
	sphere_ptr4->set_material(reflective_ptr4);
	add_geometry(sphere_ptr4);

	//Mesh models
    add_mesh("../models/Rocket.ply", matte_ptr, Point3D(-25, -25, -10), Point3D(-15, -10, 10));
    add_mesh("../models/Rocket.ply", matte_ptr, Point3D(5, 25, -2), Point3D(8, 30, 2));
    add_mesh("../models/Rocket.ply", matte_ptr, Point3D(0, -8, 2), Point3D(2, -12, -2));
    add_mesh("../models/Rocket.ply", matte_ptr, Point3D(12, 10, -2), Point3D(15, 15, 2));
    add_mesh("../models/Rocket.ply", matte_ptr, Point3D(27, -20, -1), Point3D(30, -16, 1));
    add_mesh("../models/Rocket.ply", matte_ptr, Point3D(-28, 2, -2), Point3D(-25, 7, 2));
    add_mesh("../models/Rocket.ply", matte_ptr, Point3D(25, -1, -1), Point3D(28, 5, 1));
    add_mesh("../models/Rocket.ply", matte_ptr, Point3D(0, -30, -2), Point3D(5, -26, 2));
    add_mesh("../models/UFO2.ply", matte_ptr, Point3D(-2, 15, -0.5), Point3D(9, 18, 2));

    //Lighting
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);

	Point* light_ptr = new Point;
	light_ptr->set_position(0, 0, 20);
	light_ptr->scale_radiance(20.0);
	add_light(light_ptr);

	Point* light_ptr2 = new Point;
	light_ptr2->set_position(0, 0, 0);
	light_ptr2->scale_radiance(20.0);
	add_light(light_ptr2);

	Point* light_ptr3 = new Point;
	light_ptr3->set_position(-20, 18, 10);
	light_ptr3->scale_radiance(20.0);
	add_light(light_ptr3);

	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(15, 15, 2.5);
	add_light(light_ptr1);
}
