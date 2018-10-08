cmake_minimum_required (VERSION 3.10)
project("lab04")

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})
link_libraries(${MPI_LIBRARIES})

add_executable(simd128 simd128.cpp)
add_executable(simd-add simd-add.cpp)
add_executable(simd-normal simd-normal.cpp)