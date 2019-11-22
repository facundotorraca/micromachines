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

#-------------------SOLO MAC--------------------------
include_directories(include)
include_directories(lib)
#------------------------------------------------------
# Archivos generados por CMake
include_directories(${PROJECT_BINARY_DIR}/src)

file(GLOB_RECURSE BOX2D_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libs/Box2D/*.cpp" "libs/Box2D/*.h")
add_library(Box2D STATIC ${BOX2D_SOURCES})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}
    ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

set(CMAKE_CXX_FLAGS "-fPIC")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})

add_subdirectory(src/client/QT_views)
add_subdirectory(src/model/Modifiers)
add_subdirectory(src/model/Terrains)
add_subdirectory(src/model/Vehicle)
add_subdirectory(src/plugins)
add_subdirectory(src/common)
add_subdirectory(src/server)
add_subdirectory(src/client)
add_subdirectory(src/model)
add_subdirectory(libs/json)

# add sprites directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY lua DESTINATION ${CMAKE_BINARY_DIR})
file(COPY configs.json DESTINATION ${CMAKE_BINARY_DIR})
file(COPY stylesheets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY backgrounds DESTINATION ${CMAKE_BINARY_DIR})

#file(COPY plugins DESTINATION ${CMAKE_BINARY_DIR})

file(COPY maps DESTINATION ${CMAKE_BINARY_DIR})
# Generar el servidor
add_executable(micromachines-server src/server/main.cpp)
target_link_libraries(micromachines-server model server common)

# Generar el cliente
add_executable(micromachines-client src/client/main.cpp)
target_link_libraries(micromachines-client client viewManager)

add_executable(client-old src/client/main.old.cpp)
target_link_libraries(client-old client)
