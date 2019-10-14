cmake_minimum_required(VERSION 3.0)

project(prueba_din)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(
  grettingTest
  main.cpp
)
target_link_libraries(grettingTest )