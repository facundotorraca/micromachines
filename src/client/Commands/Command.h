#ifndef MICROMACHINES_COMMAND_H
#define MICROMACHINES_COMMAND_H

#include <memory>
#include <vector>
#include <client/Camera.h>
#include <common/MsgTypes.h>
#include <client/Map.h>
#include <client/Bot.h>
#include <client/Scenario.h>

class Command {
protected:
    Scenario& scenario;
    Bot& bot;
    public:
        explicit Command(Scenario& scenario, Bot& bot) : scenario(scenario), bot(bot){}

        static std::unique_ptr<Command> create(std::vector<int32_t>& command, Scenario& scenario, Bot& bot);

        virtual void apply() = 0;
};

#endif //MICROMACHINES_COMMAND_H
