project(prueba_lua)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/prueba_lua)
find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})
add_executable(prueba_lua main.cpp)
target_link_libraries(prueba_lua
        lua
        dl)
