cmake_minimum_required(VERSION 3.10)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/src/client")

file(GLOB_RECURSE client_lib *.cpp *.h)
list(REMOVE_ITEM client_lib "main.old.cpp" "main.cpp")

add_library(client ${client_lib})
target_link_libraries(client
        common
        SDL2
        SDL2_image
        pthread)