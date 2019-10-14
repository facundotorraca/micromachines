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
    
    lua_pcall(L, 2, 1, 0);
    auto x = lua_tonumber(L, -1);
    std::cout << "Lua function returned: " << x << std::endl;
	
	lua_close(L);
}
