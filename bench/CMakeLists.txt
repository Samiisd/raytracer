cmake_minimum_required(VERSION 3.2)
project(divider_bench)

find_package(benchmark)
if (benchmark_FOUNDD)
    include_directories(${DIVISION_HEADERS_DIR})

    set(SOURCE_FILES src/divider_bench.cpp)

    add_executable(divider_bench ${SOURCE_FILES})
    target_link_libraries(divider_bench division benchmark::benchmark_main)
    install(TARGETS divider_bench DESTINATION bin)
endif ()

