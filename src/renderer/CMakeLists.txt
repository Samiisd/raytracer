cmake_minimum_required(VERSION 3.2)
project(renderer C CXX)

set(SOURCE_FILES
        scene.h
        renderer.h
        renderer.cpp
        )

add_library(renderer SHARED STATIC ${SOURCE_FILES})

install(TARGETS renderer DESTINATION ${RAYTRACER_INSTALL_LIB_DIR})
install(FILES renderer.h DESTINATION ${RAYTRACER_INSTALL_INCLUDE_DIR})
