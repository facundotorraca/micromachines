//
// Created by javier on 12/11/19.
//

#ifndef MICROMACHINES_RESTARTMENU_H
#define MICROMACHINES_RESTARTMENU_H


#include "Menu.h"

class RestartMenu : public Menu{
    void draw(Camera& camera) override;
    std::unique_ptr<Menu> handleKey(SDL_Keycode key, SDL_EventType type,
            ProtectedQueue<std::unique_ptr<ServerCommand>>& queue, bool& response) override;
    std::unique_ptr<Menu> receiveMessage(ProtocolSocket& socket, Scenario& scenario, Camera& camera) override;
};


#endif //MICROMACHINES_RESTARTMENU_H
