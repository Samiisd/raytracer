cmake_minimum_required(VERSION 3.2)
project(texture C CXX)

set(SOURCE_FILES
        texture.cpp
        )

add_library(texture SHARED STATIC ${SOURCE_FILES})

install(TARGETS texture DESTINATION ${RAYTRACER_INSTALL_LIB_DIR})
install(FILES texture.h DESTINATION ${RAYTRACER_INSTALL_INCLUDE_DIR})
