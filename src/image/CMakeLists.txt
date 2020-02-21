cmake_minimum_required(VERSION 3.2)
project(image C CXX)

set(SOURCE_FILES
        image.h
        image.cpp
        )

add_library(image SHARED STATIC ${SOURCE_FILES})

install(TARGETS image DESTINATION ${RAYTRACER_INSTALL_LIB_DIR})
install(FILES image.h DESTINATION ${RAYTRACER_INSTALL_INCLUDE_DIR})
