cmake_minimum_required(VERSION 3.2)
project(light C CXX)

set(SOURCE_FILES
        light.cpp
        light.h
        )

add_library(light SHARED STATIC ${SOURCE_FILES})

install(TARGETS light DESTINATION ${RAYTRACER_INSTALL_LIB_DIR})
install(FILES light.h DESTINATION ${RAYTRACER_INSTALL_INCLUDE_DIR})
