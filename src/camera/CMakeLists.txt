cmake_minimum_required(VERSION 3.2)
project(camera C CXX)

set(SOURCE_FILES
        camera.h
        )

install(FILES camera.h DESTINATION ${RAYTRACER_INSTALL_INCLUDE_DIR})
