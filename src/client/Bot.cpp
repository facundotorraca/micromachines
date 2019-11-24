//
// Created by aacevedo on 24/10/19.
//

#include "Bot.h"
#include <stdio.h>
#include <common/Key.h>
#include <common/Sizes.h>

Bot::Bot(ProtectedQueue<std::unique_ptr<ServerCommand>>& queue) : state(luaL_newstate()),
                                                        queue(queue) {
    std::lock_guard<std::mutex> lock(this->mutex);
    luaL_openlibs(this->state);
    this->check_error_lua(luaL_loadfile(this->state, BOT_PATH));
    this->check_error_lua(lua_pcall(this->state, 0, 0, 0));
    this->check_error_lua(lua_getglobal(this->state, INIT_FUN));
    this->load_definitions();
    this->check_error_lua(lua_pcall(this->state, 2, 0, 0));
}

void Bot::execute() {
    std::lock_guard<std::mutex> lock(this->mutex);
    //this->release_old_keys();
    auto key_event = std::vector<int32_t>();
    this->check_error_lua(lua_getglobal(this->state, DECIDE_FUN));
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

void Bot::set_id(int32_t id) {
    this->my_id = id;
}

void Bot::add_tile(TileInfo &tailInfo) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->check_error_lua(lua_getglobal(this->state, ADD_TILE_FUN));
    lua_pushnumber(this->state, tailInfo.posx/METER_TO_PIXEL);
    lua_pushnumber(this->state, tailInfo.posx/METER_TO_PIXEL + TILE_TERRAIN_SIZE);
    lua_pushnumber(this->state, tailInfo.posy/METER_TO_PIXEL);
    lua_pushnumber(this->state, tailInfo.posy/METER_TO_PIXEL + TILE_TERRAIN_SIZE);
    lua_pushnumber(this->state, tailInfo.type);
    this->check_error_lua(lua_pcall(this->state, 5, 0, 0));
}

void Bot::update_car(CarInfo &carInfo) {
    std::lock_guard<std::mutex> lock(this->mutex);
    if (carInfo.car_id != this->my_id) {
        return;
    }
    this->check_error_lua(lua_getglobal(this->state, UPDATE_CAR_FUN));
    lua_newtable(this->state);
    this->push_table_int("posX", carInfo.carx/METER_TO_PIXEL);
    this->push_table_int("posY", carInfo.cary/METER_TO_PIXEL);
    this->push_table_int("vel", carInfo.carvel/METER_TO_PIXEL);
    this->push_table_int("rot", carInfo.carrot);
    this->check_error_lua(lua_pcall(this->state, 1, 0, 0));
}

Bot::~Bot() {
    lua_close(this->state);
}

void Bot::check_error_lua(int error) {
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
    this->push_table_int("up", ACCELERATE);
    this->push_table_int("left", TURN_LEFT);
    this->push_table_int("right", TURN_RIGHT);
    lua_newtable(this->state);
    this->push_table_int("press", KEY_PRESSED);
    this->push_table_int("release", KEY_RELEASED);
}

void Bot::release_old_keys() {
    auto release_right = ServerCommand::create(TURN_RIGHT, KEY_RELEASED);
    if (release_right)
        queue.push(std::move(release_right));
    auto release_left = ServerCommand::create(TURN_LEFT, KEY_RELEASED);
    if (release_left)
        queue.push(std::move(release_left));
}