#include <list>
#include <iostream>
#include "server/Player.h"
#include "ThreadAcceptor.h"
#include "server/SocketAcceptorError.h"
#include "common/ProtocolSocket.h"

ThreadAcceptor::ThreadAcceptor(const std::string &port, ProtectedQueue<Player>& incoming_players, MatchTable& matches):
    incoming_players(incoming_players),
    server_running(true),
    matches(matches)
{
    this->acceptor.bind(port);
    this->acceptor.listen();
}

void ThreadAcceptor::stop() {
    this->acceptor.close();
}

void ThreadAcceptor::remove_confirmed_players() {
    for (auto new_player = this->new_players.begin(); new_player != this->new_players.end();) {
        if ((*new_player)->answered()) {
            (*new_player)->join();
            delete (*new_player);
            new_player = new_players.erase(new_player);
        } else {
            new_player++;
        }
    }
}

void ThreadAcceptor::kill_incoming_players() {
    for (auto & new_player : this->new_players) {
        new_player->stop();
    }
}

void ThreadAcceptor::run() {
    while (this->server_running) {
        try {
            Socket socket = this->acceptor.accept();
            ProtocolSocket p_socket(std::move(socket));

            auto* incoming_client = new ThreadIncomingPlayer(std::move(p_socket), this->incoming_players, this->matches);
            this->new_players.push_back(incoming_client);
            incoming_client->start();

            this->remove_confirmed_players();
        } catch (const SocketAcceptorError &exception) {
            this->kill_incoming_players();
            this->remove_confirmed_players();
            this->server_running = false;
        }
    }
}
