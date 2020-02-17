cmake_minimum_required(VERSION 3.2)
project(bench)

find_package(benchmark)
if (benchmark_FOUND)
    include_directories(${VECTOR_HEADERS_DIR})

    set(SOURCE_FILES src/bench_intersection.cpp)

    add_executable(bench ${SOURCE_FILES})
    target_link_libraries(bench benchmark::benchmark_main object)
    install(TARGETS bench DESTINATION bin)
endif ()
