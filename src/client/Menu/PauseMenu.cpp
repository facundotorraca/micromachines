//
// Created by javier on 12/11/19.
//

#include <common/MsgTypes.h>
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
    std::vector<int32_t> command;
    socket.receive(command);
    int32_t msg_type = command[0];

    switch (msg_type) {
        case MSG_UPDATE_ENTITY: {
            int32_t entity_type = command[1];
            switch (entity_type) {
                case TYPE_CAR: {
                    CarInfo info{command[2], command[3],
                                 command[4], command[5], command[6],
                                 command[7], command[8], command[9],
                                 command[10], command[11], command[12],
                                 command[13], command[14], command[15],
                                 command[16], command[17], command[18]};
                    scenario.updateCar(info, camera); break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
    return std::unique_ptr<Menu>(nullptr);
}
