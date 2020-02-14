cmake_minimum_required(VERSION 3.2)
project(vector C CXX)

set(SOURCE_FILES
    vector.h
    vector.cpp
)

add_library(vector SHARED STATIC ${SOURCE_FILES})

install(TARGETS vector DESTINATION ${RAYTRACER_INSTALL_LIB_DIR})
install(FILES vector.h DESTINATION ${RAYTRACER_INSTALL_INCLUDE_DIR})
