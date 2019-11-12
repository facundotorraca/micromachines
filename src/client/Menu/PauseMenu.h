//
// Created by javier on 12/11/19.
//

#ifndef MICROMACHINES_PAUSEMENU_H
#define MICROMACHINES_PAUSEMENU_H


#include "Menu.h"
#include "NoMenu.h"
#include <client/Camera.h>
#include <common/ProtectedQueue.h>
#include <memory>
#include <client/ServerCommands/ServerCommand.h>

class PauseMenu : public Menu {
public:
    void draw(Camera& camera) override;
    std::unique_ptr<Menu> handleKey(SDL_Keycode key, SDL_EventType type,
            ProtectedQueue<std::unique_ptr<ServerCommand>>& queue, bool& response) override;
    std::unique_ptr<Menu> receiveMessage(ProtocolSocket& socket, Scenario& scenario, Camera& camera) override;
};


#endif //MICROMACHINES_PAUSEMENU_H
