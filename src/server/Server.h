#ifndef MICROMACHINES_SERVER_H
#define MICROMACHINES_SERVER_H

#include <string>
#include "ThreadAcceptor.h"
#include "ThreadPlayerLocator.h"
#include "ProtectedQueue.h"
#include "ProtectedMap.h"
#include "ThreadMatch.h"

class Server {
    ProtectedMap lobbies;
    ProtectedQueue incoming_players;

    ThreadAcceptor* acceptor;
    ThreadPlayerLocator* player_locator;
    std::list<ThreadMatch*> matches;

    private:
        static void wait_quit();

        static void stop_matches();

    public:
        explicit Server(const std::string& port);

        void start();

        ~Server();
};

#endif //MICROMACHINES_SERVER_H
