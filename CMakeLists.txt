cmake_minimum_required(VERSION 3.2)

project(raytracer)

FIND_PACKAGE(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wpedantic -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS} -O0 -g --coverage")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(RAYTRACER_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(RAYTRACER_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(RAYTRACER_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(VECTOR_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/vector)
set(IMAGE_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/image)

include_directories(${RAYTRACER_INSTALL_INCLUDE_DIR})
include_directories(${VECTOR_HEADERS_DIR})
include_directories(${IMAGE_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(bench)
