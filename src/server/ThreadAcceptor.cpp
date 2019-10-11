#include <iostream>
#include "ThreadAcceptor.h"
#include "SocketAcceptorError.h"

ThreadAcceptor::ThreadAcceptor(const std::string &port, ProtectedQueue& incoming_players):
        incoming_players(incoming_players),
        server_running(true)
{
    this->acceptor.bind(port);
    this->acceptor.listen();
    //Socket ready to accept
}

void ThreadAcceptor::start() {
    this->thread = std::thread(&ThreadAcceptor::accept_clients, this);
}

void ThreadAcceptor::stop() {
    this->acceptor.close();
}

void ThreadAcceptor::join() {
    this->thread.join();
}

void ThreadAcceptor::verify_client_answer() {
    for (size_t i = 0; i < this->incoming_clients.size(); i++) {
        if (this->incoming_clients[i]->answered()) {
            this->incoming_clients[i]->join();
            delete this->incoming_clients[i];
            this->incoming_clients.erase(this->incoming_clients.begin() + i);
        }
    }
}

void ThreadAcceptor::accept_clients() {
    while (this->server_running) {
        try {
            std::cout << "Esperando cliente" << "\n";
            Socket socket = this->acceptor.accept();

            auto* incoming_client = new ThreadIncomingClient(std::move(socket), this->incoming_players);
            incoming_client->start();

            this->incoming_clients.push_back(incoming_client);
            this->verify_client_answer();
        } catch (const SocketAcceptorError &exception) {
            this->server_running = false;
        }
    }
}

ThreadAcceptor::~ThreadAcceptor() = default;
