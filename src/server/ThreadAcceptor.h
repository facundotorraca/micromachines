#ifndef MICROMACHINES_THREADACCEPTOR_H
#define MICROMACHINES_THREADACCEPTOR_H

#include <list>
#include <string>
#include <atomic>
#include "common/Thread.h"
#include "server/Player.h"
#include "server/MatchTable.h"
#include "ThreadIncomingPlayer.h"
#include "server/SocketAcceptor.h"
#include "common/ProtectedQueue.h"

class ThreadAcceptor : public Thread {
    SocketAcceptor acceptor;

    MatchTable& matches;
    ProtectedQueue<Player>& incoming_players;

    std::list<ThreadIncomingPlayer*> new_players;
    std::atomic<bool> server_running{};

    private:
        void run() override;

        void remove_confirmed_players();

        void kill_incoming_players();

    public:
        ThreadAcceptor(const std::string& port, ProtectedQueue<Player>& incoming_players, MatchTable& matches);

        void stop();
};



#endif //MICROMACHINES_THREADACCEPTOR_H
