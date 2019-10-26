//
// Created by aacevedo on 24/10/19.
//

#include "Bot.h"
#include <common/Key.h>
Bot::Bot(ProtectedQueue<std::unique_ptr<ServerCommand>>& queue) : state(luaL_newstate()),
                                                        lua_path("lua/bot.lua"),
                                                        lua_init("init"),
                                                        lua_add_tile("addTile"),
                                                        lua_update_car("updateCar"),
                                                        lua_fun("decide"),
                                                        queue(queue) {
    luaL_openlibs(this->state);
    this->check_error_lua(luaL_loadfile(this->state, this->lua_path.c_str()));
    this->check_error_lua(lua_pcall(this->state, 0, 0, 0));
    this->check_error_lua(lua_getglobal(this->state, this->lua_init.c_str()));
    this->load_definitions();
    this->check_error_lua(lua_pcall(this->state, 2, 0, 0));
}

void Bot::execute() {
    auto key_event = std::vector<int32_t>();
    this->check_error_lua(lua_getglobal(this->state, this->lua_fun.c_str()));
    this->check_error_lua(lua_pcall(this->state, 0, 2, 0));
    auto key = lua_tonumber(this->state, -1);
    lua_pop(this->state, 1);
    key_event.push_back(key);
    auto action = lua_tonumber(this->state, -1);
    lua_pop(this->state, 1);
    key_event.push_back(action);
    auto event = ServerCommand::create(key, action);
    if (event)
        queue.push(std::move(event));
}

void Bot::add_tile(TileInfo &tailInfo) {
  this->check_error_lua(lua_getglobal(this->state, this->lua_add_tile.c_str()));
  lua_pushnumber(this->state, tailInfo.posx);
  lua_pushnumber(this->state, tailInfo.posy);
  lua_pushnumber(this->state, tailInfo.type);
  this->check_error_lua(lua_pcall(this->state, 3, 0, 0));
}

void Bot::update_car(CarInfo &carInfo) {
  this->check_error_lua(lua_getglobal(this->state, this->lua_update_car.c_str()));
  this->push_table_int("posX", carInfo.carx);
  this->push_table_int("posY", carInfo.cary);
  this->push_table_int("rot", carInfo.carrot);
  this->check_error_lua(lua_pcall(this->state, 1, 0, 0));
}

Bot::~Bot() {
    lua_close(this->state);
}

void Bot::check_error_lua(int error) {
    // DEBERIA TIRAR UNA EXCEPT?
    if (error > 0)
        std::cout << lua_tostring(this->state, -1) << std::endl;
}

void Bot::push_table_int(const char *key, int value) {
    lua_pushstring(this->state, key);
    lua_pushnumber(this->state, value);
    lua_settable(this->state, -3);
}

void Bot::load_definitions() {
    lua_newtable(this->state);
    this->push_table_int("up", KEY_UP);
    this->push_table_int("left", KEY_LEFT);
    this->push_table_int("right", KEY_RIGHT);
    lua_newtable(this->state);
    this->push_table_int("press", KEY_PRESSED);
    this->push_table_int("release", KEY_RELEASED);
}