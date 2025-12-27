cmake_minimum_required(VERSION 3.10)

project(donut)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(donut
    src/main.cpp
    src/donut.cpp
    src/linear_algebra.cpp
)

target_include_directories(donut PRIVATE ${CMAKE_SOURCE_DIR}/src)