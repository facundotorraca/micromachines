#include <thread>
#include <common/Socket.h>
#include "ProtectedQueue.h"
#include "ThreadIncomingClient.h"
#include "Player.h"
#include "GameMode.h"

#define LEN_COMMAND_MODE 1

ThreadIncomingClient::ThreadIncomingClient(Socket&& socket, ProtectedQueue& incoming_players):
    incoming_players(incoming_players),
    socket(std::move(socket))
{
    this->dead = false;
}

void ThreadIncomingClient::start() {
    this->thread = std::thread(&ThreadIncomingClient::wait_answer, this);
}

void ThreadIncomingClient::join() {
    this->thread.join();
}

bool ThreadIncomingClient::answered() {
    return this->dead;
}

void ThreadIncomingClient::wait_answer() {
    uint8_t mode;
    this->socket.receive(&mode, LEN_COMMAND_MODE);

    uint8_t len_match_name;
    this->socket.receive(&len_match_name, 1);

    std::string match_name;
    this->socket.receive((uint8_t*)match_name.data(), len_match_name);

    GameMode gamemode(mode, match_name);
    auto* new_player = new Player(std::move(this->socket), gamemode);

    this->incoming_players.push(new_player);
    this->dead = true;
}
