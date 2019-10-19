cmake_minimum_required(VERSION 3.10)
project(micromachines)

# Estándar C++11
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF) # -std=c++11 en lugar de -std=gnu++11

# Flags de compilación a utilizar en general.
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -Wno-sign-conversion")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpointer-arith")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunreachable-code -Wformat=2")

# Todos los #include son relativos a src
include_directories(src)
include_directories(libs)
# Archivos generados por CMake
include_directories(${PROJECT_BINARY_DIR}/src)

file(GLOB_RECURSE BOX2D_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libs/Box2D/*.cpp" "libs/Box2D/*.h")
add_library(Box2D STATIC ${BOX2D_SOURCES})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_subdirectory(src/common)
add_subdirectory(src/server)
add_subdirectory(src/client)
add_subdirectory(src/model)

# add sprites directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Generar el servidor
add_executable(micromachines-server src/server/main.cpp)
target_link_libraries(micromachines-server server common)

# Generar el cliente
add_executable(micromachines-client src/client/main.cpp)
target_link_libraries(micromachines-client client common)

# Genero un ejecutable de prueba del model
add_executable(prueba_sdl src/model/main.cpp)
target_link_libraries(prueba_sdl model common Box2D SDL2 SDL2_image)