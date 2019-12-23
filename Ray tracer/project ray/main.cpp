#include <iostream>
#include "../materials/Cosine.hpp"

#include "../samplers/Sampler.hpp"

#include "../utilities/Image.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../acceleration/BVH.h"

#include "../tracer/Tracer.h"

#include "../world/World.hpp"
#include "../world/ViewPlane.hpp"

int main(int argc, char **argv) {
  World world;
  world.build();
  //world.set_acceleration(new KDTree(&world));
  world.set_acceleration(new BVH(&world));
  Tracer* tracer = world.tracer_ptr;
  Sampler *sampler = world.sampler_ptr;
  ViewPlane &viewplane = world.vplane;
  Image image(viewplane);

  std::vector<Ray> rays;
  for (int x = 0; x < viewplane.hres; x++) {   // across.
    for (int y = 0; y < viewplane.vres; y++) { // down.
      // Get rays for the pixel from the sampler. The pixel color is the
      // weighted sum of the shades for each ray.
      RGBColor pixel_color(0);
      rays = sampler->get_rays(x, y);
      for (const auto &ray : rays) {
        pixel_color += tracer->trace_ray(ray, 0);
      }
      //pixel_color /= sampler->get_num_rays(); //for regular sampling
      // Save color to image.
      image.set_pixel(x, y, pixel_color);
    }
  }
  // Write image to file.
  image.write_ppm("proj_scene.ppm");

  std::cout << "Wrote image.\n";

  return 0;
}
