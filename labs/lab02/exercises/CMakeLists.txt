cmake_minimum_required(VERSION 3.10)
project(lab02)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)
link_libraries(${CMAKE_THREAD_LIBS_INIT})

add_executable(_02_02_monte-carlo-pi_atomics _02_02_monte-carlo-pi_atomics.cpp)