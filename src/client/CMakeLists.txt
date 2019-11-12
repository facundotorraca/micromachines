cmake_minimum_required(VERSION 3.10)

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/src/client")

find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

file(GLOB_RECURSE client_lib *.cpp *.h)
list(REMOVE_ITEM client_lib "main.old.cpp" "main.cpp")

add_library(client ${client_lib})
target_link_libraries(client
        common
        SDL2
        SDL2_image
        SDL2_ttf
        pthread
        lua
        dl
        #avformat
        #avcodec
        #avutil
        #swscale
        )