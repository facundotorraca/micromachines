//
// Created by javier on 12/11/19.
//

#include "PauseMenu.h"
#include "NoMenu.h"

void NoMenu::draw(Camera& camera) {
}

std::unique_ptr<Menu> NoMenu::handleKey(SDL_Keycode key, SDL_EventType type,
        ProtectedQueue<std::unique_ptr<ServerCommand>>& queue, bool& response) {
    if (key == SDLK_ESCAPE && type == SDL_KEYDOWN){
        response = true;
        std::unique_ptr<Menu> a(new PauseMenu());
        return a;
    }
    auto command = ServerCommand::create(key, type);
    if (command)
        queue.push(std::move(command));
    response = true;
    return std::unique_ptr<Menu>(nullptr);
}
