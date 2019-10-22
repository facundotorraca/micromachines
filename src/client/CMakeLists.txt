cmake_minimum_required(VERSION 3.10)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/src/client")

find_package(Qt5Widgets)


file(GLOB_RECURSE client_lib *.cpp)
list(REMOVE_ITEM client_lib "main.old.cpp")

add_library(client ${client_lib} main.cpp)
target_link_libraries(client
        common
        #Qt5::Widgets
        #Qt5::Core
        SDL2
        SDL2_image
        pthread)