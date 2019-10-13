cmake_minimum_required(VERSION 3.0)

project(prubea_biblio_dinamica)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)

add_library(
  gretting
  gretting.cpp
)

add_executable(
  grettingTest
  main.cpp
)
target_link_libraries(grettingTest gretting)