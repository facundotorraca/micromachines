#ifndef MICROMACHINES_SERVER_H
#define MICROMACHINES_SERVER_H

#include <list>
#include "ThreadMatch.h"
#include "ProtectedMap.h"
#include "ProtectedQueue.h"
#include "ThreadAcceptor.h"
#include "ThreadPlayerLocator.h"
#include "ThreadMatchStarter.h"

class Server {
    ProtectedMap matches;
    ProtectedQueue incoming_players;

    ThreadAcceptor* acceptor;
    ThreadPlayerLocator* player_locator;
    ThreadMatchStarter* match_starter;

    std::list<ThreadMatch*> running_matches;

    private:
        void wait_quit();

        void stop_matches();

    public:
        explicit Server(const std::string& port);

        void start();

        ~Server();
};

#endif //MICROMACHINES_SERVER_H
