#ifndef MICROMACHINES_GAMEMAIN_H
#define MICROMACHINES_GAMEMAIN_H

#include <common/ProtocolSocket.h>

class GameMain {
    ProtocolSocket socket;

    public:
        explicit GameMain(ProtocolSocket &socket);
        ~GameMain();
        void start();
};

#endif //MICROMACHINES_GAMEMAIN_H
