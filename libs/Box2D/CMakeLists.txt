cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE box2d_lib *.cpp *.h)

add_library(Box2D ${box2d_lib})