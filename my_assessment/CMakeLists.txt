cmake_minimum_required(VERSION 3.10)
project(my_block_chain)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)
link_libraries(${CMAKE_THREAD_LIBS_INIT})

add_executable(my_block_chain main.cpp sha256.cpp my_block_chain.cpp)