//
// Created by javier on 12/11/19.
//

#include "RestartMenu.h"
#include "NoMenu.h"
#include <client/ServerCommands/SubClasses.h>

void RestartMenu::draw(Camera &camera) {
    std::string quit("[R] Restart Race");
    camera.drawScreenTexture(PAUSE_MENU_TEX, 0.4, 0.4, 1);
    camera.drawText(quit, 0.45, 0.50, 0.5, quit.size());
    std::string resume("[Q] Quit");
    camera.drawText(resume, 0.45, 0.55, 0.5, resume.size());
}

std::unique_ptr<Menu>
RestartMenu::handleKey(SDL_Keycode key, SDL_EventType type,
                       ProtectedQueue<std::unique_ptr<ServerCommand>> &queue,
                       bool &response) {
    if (type == SDL_KEYDOWN){
        if (key == SDLK_r){
            response = true;
            auto command = std::unique_ptr<ServerCommand> (new RestartRaceCommand());
            queue.push(std::move(command));
            return std::unique_ptr<Menu>(new NoMenu);
        } else if (key == SDLK_q) {
            response = false;
            auto command = std::unique_ptr<ServerCommand> (new EndRaceCommand());
            queue.push(std::move(command));
        }
    }
    return std::unique_ptr<Menu>(nullptr);
}

std::unique_ptr<Menu>
RestartMenu::receiveMessage(ProtocolSocket &socket, Scenario &scenario,
                            Camera &camera) {
    return std::unique_ptr<Menu>(nullptr);
}
