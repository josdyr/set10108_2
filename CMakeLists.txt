cmake_minimum_required(VERSION 3.10)
project(set10108)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)
link_libraries(${CMAKE_THREAD_LIBS_INIT})

add_subdirectory("labs/lab01")
add_subdirectory("labs/lab01/exercises")

add_subdirectory("labs/lab02")
add_subdirectory("labs/lab02/exercises")

add_subdirectory("labs/lab03")

add_subdirectory("labs/lab04")

add_subdirectory("labs/lab05")

add_subdirectory("assessment")
add_subdirectory("my_assessment")
add_subdirectory("my_assessment_openMP")
add_subdirectory("my_assessment_atomic")
add_subdirectory("my_assessment_mut_lock")
add_subdirectory("my_assessment_futures")