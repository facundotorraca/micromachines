extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}
#include <iostream>

lua_State* L;

#define SUCCESS 0
void check (int err){
    if (err>0){
	std::cout << lua_tostring(L, -1) << std::endl;
    }
}

int main() {
    /* LUA STUFF
     */
    L = luaL_newstate();
    luaL_openlibs(L);
    int err = luaL_loadfile(L, "plugins/luatest.lua");
	  lua_pcall(L, 0, 0, 0);
    err = lua_getglobal(L, "foo");
    lua_pushnumber(L, (int)5);
    lua_pushnumber(L, (int)6);
    lua_pcall(L, 2, 2, 0);
    auto y = lua_tonumber(L, -1);
    std::cout << "Y: " << y << std::endl;
    lua_pop(L, 1);
    auto x = lua_tonumber(L, -1);
    std::cout << "X: " << x << std::endl;
    lua_pop(L, 1);
    lua_close(L);
}
