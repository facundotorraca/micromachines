#include <common/Socket.h>
#include <string>
#include <iostream>
#include "Player.h"

#define JOIN_MODE 1

Player::Player(Socket&& socket, uint8_t mode, std::string username, std::string match_name):
    socket(std::move(socket))
{
    this->mode = mode;
    this->username = username;
    this->match_name = match_name;
}

Player::Player(Player&& other) noexcept:
    socket(std::move(other.socket)),
    username(other.username),
    match_name(other.match_name)
{
    this->mode = other.mode;
}

bool Player::is_on_join_mode() {
    return this->mode == JOIN_MODE;
}

std::string Player::get_match_name() {
    return this->match_name;
}

std::string Player::get_username() {
    return this->username;
}

void Player::send(std::string& msg) {
    this->socket.send((uint8_t*)msg.data(), msg.length());
}

uint8_t Player::receive_option() {
    uint8_t option;
    this->socket.receive(&option, 1);
    return option;
}


