cmake_minimum_required(VERSION 3.2)
project(object C CXX)

set(SOURCE_FILES
        object.h
        texture.h
        object.cpp
        )

add_library(object SHARED STATIC ${SOURCE_FILES})

install(TARGETS object DESTINATION ${RAYTRACER_INSTALL_LIB_DIR})
install(FILES object.h DESTINATION ${RAYTRACER_INSTALL_INCLUDE_DIR})
