cmake_minimum_required(VERSION 3.15)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/src/client")

file(GLOB client_lib *.cpp)
list(REMOVE_ITEM client_lib "main.cpp")

add_library(client ${client_lib})
target_link_libraries(client
        common)