//
// Created by javier on 22/10/19.
//

#ifndef MICROMACHINES_COMMAND_H
#define MICROMACHINES_COMMAND_H


#include <memory>

class Command {

public:
    static std::unique_ptr<Command> create(std::vector<int32_t>& command);
};


#endif //MICROMACHINES_COMMAND_H
