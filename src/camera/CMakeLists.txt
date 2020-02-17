cmake_minimum_required(VERSION 3.2)
project(camera C CXX)

set(SOURCE_FILES
        camera.cpp
        camera.h
        )

add_library(camera SHARED STATIC ${SOURCE_FILES})

install(TARGETS camera DESTINATION ${RAYTRACER_INSTALL_LIB_DIR})
install(FILES camera.h DESTINATION ${RAYTRACER_INSTALL_INCLUDE_DIR})
