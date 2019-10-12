#ifndef MICROMACHINES_THREADACCEPTOR_H
#define MICROMACHINES_THREADACCEPTOR_H

#include <list>
#include <string>
#include <atomic>
#include "Thread.h"
#include "SocketAcceptor.h"
#include "ProtectedQueue.h"
#include "ThreadIncomingPlayer.h"

class ThreadAcceptor : public Thread {
    SocketAcceptor acceptor;

    std::atomic<bool> server_running{};

    ProtectedQueue& incoming_players;
    std::list<ThreadIncomingPlayer*> new_players;

    private:
        void run() override;

        void remove_confirmed_players();

    public:

        ThreadAcceptor(const std::string& port, ProtectedQueue& incoming_players);

        void stop();
};


#endif //MICROMACHINES_THREADACCEPTOR_H
