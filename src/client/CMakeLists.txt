cmake_minimum_required(VERSION 3.10)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/src/client")

file(GLOB client_lib *.cpp)
list(REMOVE_ITEM client_lib "main.cpp")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

include_directories(plugins)

add_library(client ${client_lib})
target_link_libraries(client
        lua
        dl
        common)