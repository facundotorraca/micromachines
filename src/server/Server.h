#ifndef MICROMACHINES_SERVER_H
#define MICROMACHINES_SERVER_H

#include <list>
#include "ThreadMatch.h"
#include "MatchTable.h"
#include "ProtectedQueue.h"
#include "ThreadAcceptor.h"
#include "ThreadMatchStarter.h"
#include "ThreadPlayerLocator.h"

class Server {
    MatchTable matches;
    ProtectedQueue<Player> incoming_players;
    ProtectedQueue<Match*> not_ready_matches;

    ThreadAcceptor* acceptor;
    ThreadPlayerLocator* player_locator;
    ThreadMatchStarter* match_starter;

    std::list<ThreadMatch*> running_matches;

    private:
        static void wait_quit();

        void stop_matches();

    public:
        explicit Server(const std::string& port);

        void start();

        ~Server();
};

#endif //MICROMACHINES_SERVER_H
