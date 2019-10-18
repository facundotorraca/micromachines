cmake_minimum_required(VERSION 3.10)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/src/model")

file(GLOB model_lib *.cpp)
list(REMOVE_ITEM model_lib "main.cpp")

add_library(model ${model_lib})
target_link_libraries(model Box2D) #yaml-cpp)