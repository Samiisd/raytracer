cmake_minimum_required(VERSION 3.2)
project(scene C CXX)

set(SOURCE_FILES
        scene.cpp
        )

add_library(scene SHARED STATIC ${SOURCE_FILES})

install(TARGETS scene DESTINATION ${RAYTRACER_INSTALL_LIB_DIR})
install(FILES scene.h DESTINATION ${RAYTRACER_INSTALL_INCLUDE_DIR})
