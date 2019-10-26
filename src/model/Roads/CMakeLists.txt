cmake_minimum_required(VERSION 3.10)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/src/model/Roads")

file(GLOB roads_lib *.cpp *.h)

add_library(roads ${roads_lib})
target_link_libraries(roads server Box2D model common terrain)