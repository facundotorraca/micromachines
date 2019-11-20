//
// Created by javier on 12/11/19.
//

#ifndef MICROMACHINES_MENU_H
#define MICROMACHINES_MENU_H

#include <SDL2/SDL.h>
#include <common/ProtectedQueue.h>
#include <memory>
#include <client/Camera.h>
#include <client/ServerCommands/ServerCommand.h>
#include <client/Scenario.h>
#include <common/ProtocolSocket.h>

class Menu {
public:
    virtual void draw(Camera& camera) = 0;
    virtual std::unique_ptr<Menu> handleKey(SDL_Keycode key, SDL_EventType type,
           ProtectedQueue<std::unique_ptr<ServerCommand>>& queue, bool& response) = 0;
};


#endif //MICROMACHINES_MENU_H
