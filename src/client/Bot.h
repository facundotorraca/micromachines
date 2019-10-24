//
// Created by aacevedo on 24/10/19.
//

#ifndef MICROMACHINES_BOT_H
#define MICROMACHINES_BOT_H

#include <string>
#include <common/ProtectedQueue.h>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

class Bot {
    lua_State *state;
    std::string lua_path;
    std::string lua_init;
    std::string lua_fun;
    ProtectedQueue<std::vector<int32_t>>& queue;

public:
    Bot(ProtectedQueue<std::vector<int32_t>>& queue);
    void execute();
    ~Bot();

private:
    void check_error_lua(int error);
    void push_table_int(const char *key, int value);
    void load_tables();
};


#endif //MICROMACHINES_BOT_H
