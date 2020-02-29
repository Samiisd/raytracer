cmake_minimum_required(VERSION 3.2)

project(raytracer)

FIND_PACKAGE(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wpedantic -Wextra -m64")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -finline-functions -march=native -mtune=native")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g -fsanitize=address")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(RAYTRACER_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(RAYTRACER_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(RAYTRACER_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(VECTOR_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/ray)
set(RENDERER_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/renderer)
set(LIGHT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/light)
set(IMAGE_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/image)
set(OBJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/object)
set(CAMERA_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/camera)

include_directories(${VECTOR_HEADERS_DIR})
include_directories(${RENDERER_HEADERS_DIR})
include_directories(${CAMERA_HEADERS_DIR})
include_directories(${LIGHT_HEADERS_DIR})
include_directories(${OBJECT_HEADERS_DIR})
include_directories(${IMAGE_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(bench)
