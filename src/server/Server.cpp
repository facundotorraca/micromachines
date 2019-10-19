#include "Server.h"
#include <iostream>

Server::Server(const std::string &port):
    incoming_players(50),
    not_ready_matches(50)
{
    this->acceptor = new ThreadAcceptor(port, this->incoming_players, this->matches);
    this->player_locator = new ThreadPlayerLocator(this->incoming_players,this->matches,this->not_ready_matches);
    this->match_starter = new ThreadMatchStarter(this->matches,this->running_matches,this->not_ready_matches);
}

void Server::wait_quit() {
    char input;
    do {
        input = std::cin.get();
    } while (input != 'q');
}

void Server::stop_matches() {
    for (auto running_match = this->running_matches.begin(); running_match != this->running_matches.end();) {
        (*running_match)->stop();
        (*running_match)->join();
        running_match = running_matches.erase(running_match);
    }
}

void Server::start() {
    this->acceptor->start();
    this->player_locator->start();
    this->match_starter->start();

    this->wait_quit();
    this->stop_matches();

    this->acceptor->stop();
    this->match_starter->stop();
    this->player_locator->stop();

    this->player_locator->join();
    this->match_starter->join();
    this->acceptor->join();
}

Server::~Server() {
    delete this->player_locator;
    delete this->match_starter;
    delete this->acceptor;
}
