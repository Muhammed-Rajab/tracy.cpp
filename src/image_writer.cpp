// this part is to avoid getting warning messages from std_image_write
#include "interval.hpp"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../external/stb/stb_image_write.h"
#pragma GCC diagnostic pop

#include "vec3.hpp"
#include <cstdint>
#include <vector>

void write_framebuffer_to_png(const char *filename,
                              const std::vector<Vec3> &framebuffer,
                              std::size_t width, std::size_t height,
                              std::size_t channels) {
  auto image = std::vector<uint8_t>(width * height * channels);

  for (std::size_t j = 0; j < height; j += 1) {
    for (std::size_t i = 0; i < width; i += 1) {
      std::size_t idx = j * width + i;

      // TODO:: Gamma correction, along with clipping of x, y, and z values to
      // be in [0, 0.999] is important.
      static const Interval intensity(0.000, 0.999);
      auto r = framebuffer[idx].x();
      auto g = framebuffer[idx].y();
      auto b = framebuffer[idx].z();

      image[3 * idx + 0] = static_cast<uint8_t>(256 * intensity.clamp(r));
      image[3 * idx + 1] = static_cast<uint8_t>(256 * intensity.clamp(g));
      image[3 * idx + 2] = static_cast<uint8_t>(256 * intensity.clamp(b));
    }
  }

  stbi_write_png(filename, width, height, channels, image.data(),
                 width * channels);
}
