#ifndef MICROMACHINES_THREADINCOMINGPLAYER_H
#define MICROMACHINES_THREADINCOMINGPLAYER_H

#include <atomic>
#include "Thread.h"
#include "Player.h"
#include "ProtectedMap.h"
#include "common/Socket.h"
#include "ProtectedQueue.h"

class ThreadIncomingPlayer : public Thread {
    Socket socket;

    ProtectedMap& matches;
    ProtectedQueue<Player>& incoming_players;

    std::atomic<bool> dead;

    private:
        void run() override;

    public:
        ThreadIncomingPlayer(Socket&& socket, ProtectedQueue<Player>& incoming_players,  ProtectedMap& matches);

        bool answered();
};

#endif //MICROMACHINES_THREADINCOMINGPLAYER_H
