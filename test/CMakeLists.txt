cmake_minimum_required(VERSION 3.2)
project(tests)

find_package(GTest REQUIRED)

include_directories(${VECTOR_HEADERS_DIR})

set(SOURCE_FILES main.cpp
        src/vector_tests.cpp)

add_executable(tests ${SOURCE_FILES})
target_link_libraries(tests gtest pthread)
install(TARGETS tests DESTINATION bin)
