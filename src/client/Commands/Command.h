#ifndef MICROMACHINES_COMMAND_H
#define MICROMACHINES_COMMAND_H

#include <memory>
#include <vector>
#include <client/Camera.h>
#include <common/MsgTypes.h>
#include <client/Map.h>

class Command {
protected:
    Map& map;
    public:
        explicit Command(Map& map) : map(map){}

        static std::unique_ptr<Command> create(std::vector<int32_t>& command, Map& map);

        virtual void apply() = 0;
};

#endif //MICROMACHINES_COMMAND_H
