cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE model_lib *.cpp)

add_library(model ${model_lib})