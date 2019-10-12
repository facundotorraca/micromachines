#include <iostream>
#include <cstring>
#include "common/Socket.h"
#include "server/ProtectedQueue.h"
#include "ThreadIncomingPlayer.h"
#include "server/Player.h"
#include "GameMode.h"

ThreadIncomingPlayer::ThreadIncomingPlayer(Socket&& socket, ProtectedQueue& incoming_players):
    incoming_players(incoming_players),
    socket(std::move(socket))
{
    this->dead = false;
}

bool ThreadIncomingPlayer::answered() {
    return this->dead;
}

/* Esto hay que arreglarlo es asqueroso*/
void ThreadIncomingPlayer::run() {
    uint8_t buf[20];
    memset(buf, 0, 20 * sizeof(uint8_t));

    uint8_t mode;
    this->socket.receive(&mode, 1);

    uint8_t len_match_name;
    this->socket.receive(&len_match_name, 1);

    this->socket.receive(buf, len_match_name);
    std::string match_name(reinterpret_cast<const char *>(buf), len_match_name);
    memset(buf, 0, 20 * sizeof(uint8_t));

    uint8_t len_username;
    this->socket.receive(&len_username, 1);

    this->socket.receive(buf, len_username);
    std::string username(reinterpret_cast<const char *>(buf), len_username);
    memset(buf, 0, 20 * sizeof(uint8_t));

    GameMode gamemode(mode, match_name);
    Player new_player(std::move(this->socket), gamemode, username);

    this->incoming_players.push(std::move(new_player));
    this->dead = true;
}
