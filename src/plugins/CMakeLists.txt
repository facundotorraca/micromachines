cmake_minimum_required(VERSION 3.10)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)

add_library(BoostLast SHARED BoostLast.cpp)
target_link_libraries(BoostLast model)
