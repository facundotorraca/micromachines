#ifndef MICROMACHINES_COMMAND_H
#define MICROMACHINES_COMMAND_H

#include <memory>
#include <vector>
#include <client/Camera.h>
#include <common/MsgTypes.h>

class Command {
    public:
        static std::unique_ptr<Command> create(std::vector<int32_t>& command);

        virtual void apply(Camera& camera) = 0;
};

#endif //MICROMACHINES_COMMAND_H
