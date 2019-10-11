#include <list>
#include <thread>
#include <iostream>
#include "ThreadPlayerLocator.h"
#include "ProtectedQueue.h"
#include "ProtectedList.h"
#include "ProtectedMap.h"

ThreadPlayerLocator::ThreadPlayerLocator(ProtectedQueue& incoming_players, ProtectedMap &lobbies, std::list<ThreadMatch*>& matches):
        lobbies(lobbies),
        incoming_players(incoming_players),
        matches(matches)
{}

void ThreadPlayerLocator::start() {
    this->thread = std::thread(&ThreadPlayerLocator::run, this);
}

void ThreadPlayerLocator::run() {
    bool accept_players = true;
    while (accept_players) {
        std::cout << "Esperando player" << "\n";
        Player* new_player = this->incoming_players.pop();
        std::string match_name = new_player->get_match_name();
        if (new_player->is_on_join_mode()) {
            ProtectedList* lobby = this->lobbies.get(match_name);
            lobby->append(new_player);
        } else {
            auto* new_lobby = new ProtectedList();
            new_lobby->append(new_player);
            auto* new_match = new ThreadMatch(new_lobby);
            new_match->start();
            this->lobbies.add(match_name, new_lobby);
            this->matches.push_back(new_match);
            std::cout <<
        }
    }
}

void ThreadPlayerLocator::stop() {
    /*
     * stopea al hilo de esperar la cola
     */
}

void ThreadPlayerLocator::join() {
    this->thread.join();
}
