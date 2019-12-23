#include "../cameras/Perspective.hpp"

#include "../tracer/Basic.h"

#include "../materials/Cosine.hpp"

#include "../samplers/Simple.hpp"

#include "../utilities/Point3D.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"

#include "../world/World.hpp"

void World::build(void) {
  // view plane
  vplane.top_left = Point3D(-1, 1, 2);
  vplane.bottom_right = Point3D(1, -1, 2);
  vplane.hres = 800;
  vplane.vres = 800;

  // Background color.
  RGBColor grey(0.3, 0.35, 0.3);
  bg_color = grey;

  // camera and sampler.
  set_camera(new Perspective(0, 0, 10));
  set_tracer(new Basic(this));
  sampler_ptr = new Simple(camera_ptr, &vplane);

  //load mesh
  add_mesh("models/bun_zipper.ply", new Cosine(blue), Point3D(-1, -1, -1), Point3D(1, 1, 1));
}
