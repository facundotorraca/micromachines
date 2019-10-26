cmake_minimum_required(VERSION 3.10)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/src/model")

file(GLOB vehicle_lib *.cpp *.h)

add_library(vehicle ${vehicle_lib})
target_link_libraries(vehicle server Box2D common)