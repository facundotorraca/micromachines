//
// Created by javier on 16/10/19.
//

#ifndef MICROMACHINES_GAMEMAIN_H
#define MICROMACHINES_GAMEMAIN_H


#include <common/ProtocolSocket.h>

class GameMain {
    ProtocolSocket socket;
public:
    explicit GameMain(ProtocolSocket &socket);
    void start();
};


#endif //MICROMACHINES_GAMEMAIN_H
