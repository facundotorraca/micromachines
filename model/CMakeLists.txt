cmake_minimum_required(VERSION 3.10)
project(model)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/model)

file(GLOB_RECURSE model_lib *.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(model ${model_lib})

add_executable(car main.cpp)
target_link_libraries(car Box2D SDL2 SDL2_image)

