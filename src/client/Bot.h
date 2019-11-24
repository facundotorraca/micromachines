//
// Created by aacevedo on 24/10/19.
//

#ifndef MICROMACHINES_BOT_H
#define MICROMACHINES_BOT_H

#define BOT_PATH "lua/bot.lua"
#define INIT_FUN "init"
#define ADD_TILE_FUN "addTile"
#define UPDATE_CAR_FUN "updateCar"
#define DECIDE_FUN "decide"

#include <string>
#include <common/ProtectedQueue.h>

#include "Entities/CarInfo.h"
#include "Entities/TileInfo.h"
#include "ServerCommands/ServerCommand.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

class Bot {
    lua_State *state;
    std::string lua_path;
    std::string lua_init;
    std::string lua_add_tile;
    std::string lua_update_car;
    std::string lua_fun;
    int32_t my_id;
    ProtectedQueue<std::unique_ptr<ServerCommand>>& queue;
    std::mutex mutex;

public:
    Bot(ProtectedQueue<std::unique_ptr<ServerCommand>>& queue);
    void execute();
    void add_tile(TileInfo &tailInfo);
    void update_car(CarInfo &carInfo);
    void set_id(int32_t id);
    ~Bot();

private:
    void check_error_lua(int error);
    void push_table_int(const char *key, int value);
    void load_definitions();
    void release_old_keys();
};


#endif //MICROMACHINES_BOT_H
