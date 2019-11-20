//
// Created by javier on 12/11/19.
//

#include "LostConnectionMenu.h"

void LostConnectionMenu::draw(Camera &camera) {
    std::string quit("Connection Lost");
    camera.drawScreenTexture(PAUSE_MENU_TEX, 0.3, 0.4, 0.4, 0.3);
    camera.drawText(quit, 0.4, 0.50, 0.56, quit.size());
    std::string resume("Press any key to quit");
    camera.drawText(resume, 0.35, 0.55, 0.5, resume.size());
}

std::unique_ptr<Menu>
LostConnectionMenu::handleKey(SDL_Keycode key, SDL_EventType type,
                              ProtectedQueue<std::unique_ptr<ServerCommand>> &queue,
                              bool &response) {
    response = false;
    return std::unique_ptr<Menu>(nullptr);
}
