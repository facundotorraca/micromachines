cmake_minimum_required(VERSION 3.15)

file(GLOB_RECURSE common_lib *.cpp)

add_library(common ${common_lib})