#pragma once

#include "vec3.hpp"
#include <vector>

using Color = Vec3;

void write_framebuffer_to_png(const char *filename,
                              const std::vector<Vec3> &framebuffer,
                              std::size_t width, std::size_t height,
                              std::size_t channels);
