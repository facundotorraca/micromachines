#ifndef MICROMACHINES_COMMAND_H
#define MICROMACHINES_COMMAND_H

#include <memory>
#include <vector>
#include <client/Camera.h>
#include <common/MsgTypes.h>
#include <client/Map.h>
#include <client/Bot.h>

class Command {
protected:
    Map& map;
    Bot& bot;
    public:
        explicit Command(Map& map, Bot& bot) : map(map), bot(bot){}

        static std::unique_ptr<Command> create(std::vector<int32_t>& command, Map& map, Bot& bot);

        virtual void apply() = 0;
};

#endif //MICROMACHINES_COMMAND_H
