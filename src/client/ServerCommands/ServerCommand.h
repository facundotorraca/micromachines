//
// Created by javier on 26/10/19.
//

#ifndef MICROMACHINES_SERVERCOMMAND_H
#define MICROMACHINES_SERVERCOMMAND_H

#include <common/Key.h>
#include <memory>
#include <vector>
#include <common/ProtocolSocket.h>
#include <SDL2/SDL.h>

class ServerCommand {
protected:
    int32_t key;
    int32_t type;
public:
    static std::unique_ptr<ServerCommand> create(int key, int type);
    static std::unique_ptr<ServerCommand> create(SDL_Keycode key, SDL_EventType type);
    void send(ProtocolSocket& socket);
};


#endif //MICROMACHINES_SERVERCOMMAND_H
