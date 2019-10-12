#ifndef MICROMACHINES_THREADINCOMINGPLAYER_H
#define MICROMACHINES_THREADINCOMINGPLAYER_H

#include <atomic>
#include "Thread.h"
#include "common/Socket.h"

class ThreadIncomingPlayer : public Thread {
    Socket socket;
    ProtectedQueue& incoming_players;
    std::atomic<bool> dead;

    private:
        void run() override;

    public:
        ThreadIncomingPlayer(Socket&& socket, ProtectedQueue& incoming_players);

        bool answered();
};

#endif //MICROMACHINES_THREADINCOMINGPLAYER_H
