#include <SDL2/SDL.h>
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}
#include <iostream>
#include <string>

#define SUCCESS 0

int main() {
    /* LUA STUFF
     */
    auto L = luaL_newstate();
    luaL_openlibs(L);
    int err = luaL_loadfile(L, "plugins/luatest.lua");
    if ((err) > 0){
        std::cout << std::string(lua_tostring(L, -1)) << std::endl;
    }
    lua_pcall(L, 0, 0, 0);
    lua_getglobal(L, "foo");
    lua_pushnumber(L, (int)5);
    lua_pushnumber(L, (int)6);
    lua_pcall(L, 2, 1, 0);
    auto x = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);

    std::cout << "Lua function returned: " << x << std::endl;

    return SUCCESS;
}
