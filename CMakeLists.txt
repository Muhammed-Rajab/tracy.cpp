cmake_minimum_required(VERSION 3.28)
project(tracy.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# -g will enable debugging using gdb
# WARN: remove -Ofast if you face any floating point errors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Ofast")

add_executable(tracy
  main.cpp

  # ray and image writer
  src/ray.cpp
  src/image_writer.cpp

  # hittables
  src/hittable.cpp
  src/hittable_list.cpp
  src/sphere.cpp

  # materials
  src/materials/dielectric.cpp
  src/materials/lambertian.cpp
  src/materials/metal.cpp

  # camera
  src/camera.cpp

  # interval
  src/interval.cpp
)

target_include_directories(tracy PRIVATE include/)
target_include_directories(tracy PRIVATE external/stb)
