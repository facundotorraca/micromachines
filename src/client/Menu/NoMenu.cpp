//
// Created by javier on 12/11/19.
//

#include <common/MsgTypes.h>
#include "PauseMenu.h"
#include "NoMenu.h"
#include "RestartMenu.h"

void NoMenu::draw(Camera& camera) {
}

std::unique_ptr<Menu> NoMenu::handleKey(SDL_Keycode key, SDL_EventType type,
        ProtectedQueue<std::unique_ptr<ServerCommand>>& queue, bool& response) {
    if (type == SDL_KEYDOWN){
        if (key == SDLK_ESCAPE){
            response = true;
            return std::unique_ptr<Menu>(new PauseMenu());
        }
    }
    auto command = ServerCommand::create(key, type);
    if (command)
        queue.push(std::move(command));
    response = true;
    return std::unique_ptr<Menu>(nullptr);
}

