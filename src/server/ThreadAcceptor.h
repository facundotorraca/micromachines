#ifndef MICROMACHINES_THREADACCEPTOR_H
#define MICROMACHINES_THREADACCEPTOR_H

#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include "SocketAcceptor.h"
#include "ProtectedQueue.h"
#include "ThreadIncomingClient.h"

class ThreadAcceptor {
    SocketAcceptor acceptor;
    std::thread thread;
    ProtectedQueue& incoming_players;
    std::atomic<bool> server_running{};
    std::vector<ThreadIncomingClient*> incoming_clients;

    private:
        void accept_clients();

        void verify_client_answer();

    public:

        ThreadAcceptor(const std::string& port, ProtectedQueue& incoming_players);

        void start();

        void stop();

        void join();

        ~ThreadAcceptor();
};

#endif //MICROMACHINES_THREADACCEPTOR_H
