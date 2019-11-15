#ifndef MICROMACHINES_COMMAND_H
#define MICROMACHINES_COMMAND_H

#include <memory>
#include <vector>
#include <client/Camera.h>
#include <common/MsgTypes.h>
#include <client/Map.h>
#include <client/Bot.h>
#include <client/Scenario.h>
#include <client/Menu/Menu.h>

class Command {
protected:
    Scenario& scenario;
    public:
        explicit Command(Scenario& scenario) : scenario(scenario){}

        static std::unique_ptr<Command> create(Scenario& scenario, ProtocolSocket& socket, Camera& camera);

        virtual std::unique_ptr<Menu> apply() = 0;
};

#endif //MICROMACHINES_COMMAND_H
