cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3") # Flags de compilación a utilizar en general.

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/src/server")

file(GLOB server_lib *.cpp)
list(REMOVE_ITEM server_lib "main.cpp")

add_library(server ${server_lib})
target_link_libraries(server pthread common model yaml-cpp)