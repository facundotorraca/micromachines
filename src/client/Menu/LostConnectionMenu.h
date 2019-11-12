//
// Created by javier on 12/11/19.
//

#ifndef MICROMACHINES_LOSTCONNECTIONMENU_H
#define MICROMACHINES_LOSTCONNECTIONMENU_H


#include "Menu.h"

class LostConnectionMenu : public Menu {
public:
    void draw(Camera& camera) override;
    std::unique_ptr<Menu> handleKey(SDL_Keycode key, SDL_EventType type,
                                    ProtectedQueue<std::unique_ptr<ServerCommand>>& queue, bool& response) override;
    std::unique_ptr<Menu> receiveMessage(ProtocolSocket& socket, Scenario& scenario, Camera& camera) override;
};


#endif //MICROMACHINES_LOSTCONNECTIONMENU_H
