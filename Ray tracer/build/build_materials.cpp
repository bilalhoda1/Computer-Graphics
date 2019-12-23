#include "../cameras/Perspective.hpp"
#include "../cameras/Parallel.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"

#include "../tracer/Basic.h"
#include "../tracer/Whitted.hpp"

#include "../lights/Ambient.hpp"
#include "../lights/Point.hpp"

#include "../materials/Cosine.hpp"
#include "../materials/Matte.h"
#include "../materials/Reflective.hpp"

#include "../samplers/Simple.hpp"
#include "../samplers/Regular.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"

#include "../world/World.hpp"

void World::build(void) {
  // view plane
  vplane.top_left.x = -200;
  vplane.top_left.y = 200;
  vplane.top_left.z = 100;
  vplane.bottom_right.x = 200;
  vplane.bottom_right.y = -200;
  vplane.bottom_right.z = 100;
  vplane.hres = 1000;
  vplane.vres = 1000;
  vplane.set_maxdepth(1);
  bg_color = black;  // background color.

  // camera and sampler.
  set_camera(new Perspective(0, 0, 200));
  set_tracer(new Whitted(this));
  sampler_ptr = new Simple(camera_ptr, &vplane);
  //sampler_ptr = new Regular(camera_ptr, &vplane, 16);
  //sampler_ptr = new Random(camera_ptr, &vplane, 4);

  Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);

	Point* light_ptr = new Point;
	light_ptr->set_position(100, 100, 100);
	light_ptr->scale_radiance(3.0);
	add_light(light_ptr);

  // colors
  RGBColor yellow(1, 1, 0);  // yellow
  RGBColor brown(0.71, 0.40, 0.16);  // brown
  RGBColor darkGreen(0.0, 0.41, 0.41);  // darkGreen
  RGBColor orange(1, 0.75, 0);  // orange
  RGBColor green(0, 0.6, 0.3);  // green
  RGBColor lightGreen(0.65, 1, 0.30);  // light green
  RGBColor darkYellow(0.61, 0.61, 0);  // dark yellow
  RGBColor lightPurple(0.65, 0.3, 1);  // light purple
  RGBColor darkPurple(0.5, 0, 1);  // dark purple
  RGBColor grey(0.25);  // grey

  Reflective* reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(0.25);
	reflective_ptr1->set_kd(0.5);
	reflective_ptr1->set_cd(0, 0, 1);    	// yellow
	reflective_ptr1->set_ks(0.15);
	reflective_ptr1->set_exp(100.0);
	reflective_ptr1->set_kr(0.75);
	reflective_ptr1->set_cr(0.65, 1, 0.30); 			// default color*/

	// orange non-reflective sphere
	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.45);
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(0.5, 0, 1);   // orange

	Sphere* sphere_ptr1 = new Sphere(Point3D(-100, 60, 0), 60);
	sphere_ptr1->set_material(reflective_ptr1);
	add_geometry(sphere_ptr1);

	Sphere* sphere_ptr2 = new Sphere(Point3D(100, 60, 0), 60);
	sphere_ptr2->set_material(matte_ptr1);
	add_geometry(sphere_ptr2);

    Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.45);
	matte_ptr2->set_kd(0.75);
	matte_ptr2->set_cd(0.65, 1, 0.30);

	Plane* plane_ptr = new Plane(Point3D(0, 1, 0), Vector3D(0, 2, 2));
	plane_ptr->set_material(matte_ptr2);
	add_geometry(plane_ptr);

    //delete reflective_ptr1;
    //delete matte_ptr1;
    //delete matte_ptr2;
}

