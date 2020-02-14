cmake_minimum_required(VERSION 3.2)
project(raytracer)

add_subdirectory(vector)
set(SOURCE_FILES main.cpp)

add_executable(raytracer ${SOURCE_FILES})
target_link_libraries(raytracer vector)
install(TARGETS raytracer DESTINATION ${RAYTRACER_INSTALL_BIN_DIR})
