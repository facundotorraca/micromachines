cmake_minimum_required(VERSION 3.0)

project(prueba_din)

add_subdirectory(count)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

add_executable(countting
  main.cpp
)

target_link_libraries(countting libdl.so)