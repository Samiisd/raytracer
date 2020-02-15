cmake_minimum_required(VERSION 3.2)
project(bench)

find_package(benchmark)
if (benchmark_FOUND)
    include_directories(${VECTOR_HEADERS_DIR})

    set(SOURCE_FILES src/vector_bench.cpp)

    add_executable(bench ${SOURCE_FILES})
    target_link_libraries(bench benchmark::benchmark_main)
    install(TARGETS bench DESTINATION bin)
endif ()
