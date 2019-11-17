#ifndef MICROMACHINES_GAMEMAIN_H
#define MICROMACHINES_GAMEMAIN_H

#include <common/ProtocolSocket.h>

class GameMain {
    ProtocolSocket socket;
    bool use_bot;

    public:
        explicit GameMain(ProtocolSocket &socket, bool use_bot);

        void start();
};

#endif //MICROMACHINES_GAMEMAIN_H
