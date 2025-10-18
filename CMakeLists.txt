cmake_minimum_required(VERSION 3.28)
project(tracy.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# -g will enable debugging using gdb
# WARN: remove -Ofast if you face any floating point errors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Ofast")

add_executable(tracy
  main.cpp
  src/image_writer.cpp
  src/camera.cpp
  src/ray.cpp
  src/sphere.cpp
  src/hittable.cpp
  src/interval.cpp
)

target_include_directories(tracy PRIVATE include/)
target_include_directories(tracy PRIVATE external/stb)
