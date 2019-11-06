cmake_minimum_required(VERSION 3.10)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/src/model/Modifiers")

file(GLOB modifiers_lib *.cpp *.h)

add_library(modifiers ${modifiers_lib})
target_link_libraries(modifiers server Box2D model common vehicle)