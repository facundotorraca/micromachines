//
// Created by aacevedo on 24/10/19.
//

#ifndef MICROMACHINES_BOT_H
#define MICROMACHINES_BOT_H

#include <string>
#include <common/ProtectedQueue.h>

#include "Entities/CarInfo.h"
#include "Entities/Entity.h"

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
    ProtectedQueue<std::vector<int32_t>>& queue;

public:
    Bot(ProtectedQueue<std::vector<int32_t>>& queue);
    void execute();
    void add_tile(TileInfo &tailInfo);
    void update_car(CarInfo &carInfo);
    void set_id(int32_t id);
    ~Bot();

private:
    void check_error_lua(int error);
    void push_table_int(const char *key, int value);
    void load_definitions();
};


#endif //MICROMACHINES_BOT_H
