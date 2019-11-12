//
// Created by javier on 12/11/19.
//

#include "PauseMenu.h"

void PauseMenu::draw(Camera& camera) {
    std::string quit("[Q] Quit");
    camera.drawScreenTexture(PAUSE_MENU_TEX, 0.4, 0.4, 1);
    camera.drawText(quit, 0.45, 0.50, 0.5, quit.size());
    std::string resume("[ESC] Resume");
    camera.drawText(resume, 0.45, 0.55, 0.5, resume.size());
}

std::unique_ptr<Menu> PauseMenu::handleKey(SDL_Keycode key, SDL_EventType type,
        ProtectedQueue<std::unique_ptr<ServerCommand>>& queue, bool& response) {
    if (key == SDLK_ESCAPE && type == SDL_KEYDOWN){
        response = true;
        return std::unique_ptr<Menu> (new NoMenu());
    }
    if (key == SDLK_q && type == SDL_KEYDOWN){
        response = false;
        return std::unique_ptr<Menu> (nullptr);
    }
    return std::unique_ptr<Menu> (nullptr);
}

std::unique_ptr<Menu>
PauseMenu::receiveMessage(ProtocolSocket &socket, Scenario &scenario,
                          Camera &camera) {
    return std::unique_ptr<Menu>(nullptr);
}
