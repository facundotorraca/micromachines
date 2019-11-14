cmake_minimum_required(VERSION 3.10)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/src/client")

find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

file(GLOB client_lib *.cpp *.h)
list(REMOVE_ITEM client_lib "main.old.cpp" "main.cpp")
file(GLOB entities Entities/*.h Entities/*.cpp)
file(GLOB menu Menu/*.h Menu/*.cpp)
file(GLOB keycommands KeyCommands/*.h KeyCommands/*.cpp)
file(GLOB ffmpeg_folder ffmpeg/*.h ffmpeg/*.cpp)
file(GLOB servercommands ServerCommands/*.h ServerCommands/*.cpp)
file(GLOB_RECURSE qt_libs QT_views/*.cpp QT_views/*.h)

SET_SOURCE_FILES_PROPERTIES(${qt_libs} PROPERTIES COMPILE_FLAGS "-O0")
SET_SOURCE_FILES_PROPERTIES(${client_lib} PROPERTIES COMPILE_FLAGS "-O3")
SET_SOURCE_FILES_PROPERTIES(${entities} PROPERTIES COMPILE_FLAGS "-O3")
SET_SOURCE_FILES_PROPERTIES(${menu} PROPERTIES COMPILE_FLAGS "-O3")
SET_SOURCE_FILES_PROPERTIES(${keycommands} PROPERTIES COMPILE_FLAGS "-O3")
SET_SOURCE_FILES_PROPERTIES(${ffmpeg_folder} PROPERTIES COMPILE_FLAGS "-O3")
SET_SOURCE_FILES_PROPERTIES(${servercommands} PROPERTIES COMPILE_FLAGS "-O3")

add_library(client ${client_lib} ${qt_libs} ${entities} ${menu} ${keycommands} ${ffmpeg_folder} ${servercommands})
target_link_libraries(client
        common
        SDL2
        SDL2_image
        SDL2_ttf
        pthread
        lua
        dl
        avformat
        avcodec
        avutil
        swscale
        )