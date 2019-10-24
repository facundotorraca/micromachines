project(prueba_lua)
find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})
add_executable(prueba_lua main.cpp)
target_link_libraries(prueba_lua
        lua
        dl)
