cmake_minimum_required(VERSION 3.2)
project(raytracer)

add_subdirectory(light)
add_subdirectory(camera)
add_subdirectory(image)
add_subdirectory(object)
add_subdirectory(texture)
add_subdirectory(renderer)
set(SOURCE_FILES main.cpp)

add_executable(raytracer ${SOURCE_FILES})
target_link_libraries(raytracer renderer camera light image object texture)
install(TARGETS raytracer DESTINATION ${RAYTRACER_INSTALL_BIN_DIR})
