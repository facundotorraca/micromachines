#ifndef MICROMACHINES_THREADINCOMINGPLAYER_H
#define MICROMACHINES_THREADINCOMINGPLAYER_H

#include "common/Socket.h"
#include "Thread.h"

class ThreadIncomingPlayer : public Thread {
    ProtectedQueue& incoming_players;
    Socket socket;
    bool dead;

    private:
        void run();

    public:
        ThreadIncomingPlayer(Socket&& socket, ProtectedQueue& incoming_players);

        bool answered();
};

#endif //MICROMACHINES_THREADINCOMINGPLAYER_H
