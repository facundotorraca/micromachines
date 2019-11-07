cmake_minimum_required(VERSION 3.10)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/src/model/Terrain")

file(GLOB terrain_lib *.cpp *.h)

add_library(terrain ${terrain_lib})
target_link_libraries(terrain server Box2D model common vehicle modifiers)