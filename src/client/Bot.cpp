//
// Created by aacevedo on 24/10/19.
//

#include "Bot.h"
Bot::Bot(ProtectedQueue<std::vector<int32_t>>& queue) : state(luaL_newstate()),
                                                        lua_path("lua/bot.lua"),
                                                        lua_fun("decide"),
                                                        queue(queue) {
    luaL_openlibs(this->state);
    this->check_error_lua(luaL_loadfile(this->state, this->lua_path.c_str()));
    this->check_error_lua(lua_pcall(this->state,0,0,0));
}

void Bot::execute() {
    auto key_event = std::vector<int32_t>();
    this->check_error_lua(lua_getglobal(this->state, this->lua_fun.c_str()));
    this->check_error_lua(lua_pcall(this->state,0,2,0));
    auto key = lua_tonumber(this->state, -1);
    lua_pop(this->state, 1);
    key_event.push_back(key);
    auto action = lua_tonumber(this->state, -1);
    lua_pop(this->state, 1);
    key_event.push_back(action);
    this->queue.push(key_event);
}

Bot::~Bot() {
    lua_close(this->state);
}

void Bot::check_error_lua(int error) {
    // DEBERIA TIRAR UNA EXCEPT?
    if (error > 0)
        std::cout << lua_tostring(this->state, -1) << std::endl;
}
