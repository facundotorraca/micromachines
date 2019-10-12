#include <iostream>
#include "Server.h"

Server::Server(const std::string &port):
    incoming_players(50),
    not_ready_matches(50)
{
    this->acceptor = new ThreadAcceptor(port, this->incoming_players);
    this->player_locator = new ThreadPlayerLocator(this->incoming_players, this->matches, this->not_ready_matches);
    this->match_starter = new ThreadMatchStarter(this->matches, this->running_matches, this->not_ready_matches);
}

void Server::wait_quit() {
    char input;
    do {
        input = std::cin.get();
    } while (input != 'q');
}

void Server::stop_matches() {
    /*
     * Aca frenamos las partidas!
     */
}

void Server::start() {
    this->acceptor->start();
    this->player_locator->start();
    this->match_starter->start();

    this->wait_quit();
    this->stop_matches();

    this->acceptor->stop();
    this->player_locator->stop();

    this->acceptor->join();
    this->player_locator->join();
}

Server::~Server() {
    delete this->acceptor;
    delete this->player_locator;
}
