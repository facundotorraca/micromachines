#include <cstring>
#include <iostream>
#include "server/Player.h"
#include "common/SocketError.h"
#include "ThreadIncomingPlayer.h"
#include "server/ProtectedQueue.h"
#include <common/ProtocolSocket.h>

ThreadIncomingPlayer::ThreadIncomingPlayer(ProtocolSocket&& p_socket, ProtectedQueue<Player>& incoming_players, MatchTable& matches):
    incoming_players(incoming_players),
    p_socket(std::move(p_socket)),
    matches(matches),
    dead(false)
{}

bool ThreadIncomingPlayer::answered() {
    return this->dead;
}

void ThreadIncomingPlayer::stop() {
    this->p_socket.close();
    this->dead = true;
}


void ThreadIncomingPlayer::run() {
    try {
        this->matches.send_matches(this->p_socket);

        uint8_t mode;
        this->p_socket.receive(mode);

        std::vector<uint8_t> buffer(4096);

        this->p_socket.receive(buffer);
        std::string match_name(reinterpret_cast<const char *>(buffer.data()), buffer.size());
        buffer.resize(4096);

        this->p_socket.receive(buffer);
        std::string username(reinterpret_cast<const char *>(buffer.data()), buffer.size());
        buffer.resize(4096);

        Player new_player(std::move(this->p_socket), mode, username, match_name);
        this->incoming_players.push(std::move(new_player));

        this->dead = true;
    } catch (const SocketError& exception) {
        this->dead = true;
    }

}
