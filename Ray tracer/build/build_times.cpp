
/**
   This builds a simple scene that consists of a sphere, a triangle, and a
   plane.
   Parallel viewing is used with a single sample per pixel.
*/
#include <iostream>
#include "../cameras/Perspective.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"
#include "../utilities/BBox.hpp"

#include "../tracer/Basic.h"
#include "../tracer/Whitted.hpp"

#include "../lights/Ambient.hpp"
#include "../lights/Point.hpp"
#include "../lights/Directional.hpp"

#include "../materials/Cosine.hpp"
#include "../materials/Matte.h"
#include "../materials/Phong.hpp"
#include "../materials/Reflective.hpp"

#include "../samplers/Simple.hpp"
#include "../samplers/Random.h"

#include "../utilities/Constants.hpp"

#include "../world/World.hpp"

void
World::build(void) {
  // View plane  .
  vplane.top_left.x = -10;
  vplane.top_left.y = 10;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = 10;
  vplane.bottom_right.y = -10;
  vplane.bottom_right.z = 10;
  vplane.hres = 480;
  vplane.vres = 480;

  bg_color = RGBColor(0.15);

  // Camera and sampler.
  set_camera(new Perspective(0, 0, 20));
  set_tracer(new Basic(this));
  sampler_ptr = new Simple(camera_ptr, &vplane);

  int num = 100;
  for (int i=0; i<num; i++){
    RGBColor c(((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)));
    int randomX = (-10) + (rand() % static_cast<int>(10 - (-10) + 1));
    int randomY = (-10) + (rand() % static_cast<int>(10 - (-10) + 1));
    Sphere* sphere_ptr = new Sphere(Point3D(randomX, randomY, 0), 3);
    sphere_ptr->set_material(new Cosine(c));
    add_geometry(sphere_ptr);
  }
}
