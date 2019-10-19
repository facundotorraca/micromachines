#include <common/Socket.h>
#include <string>
#include <iostream>
#include <utility>
#include "Player.h"

#define JOIN_MODE 1

Player::Player(ProtocolSocket&& p_socket, uint8_t mode, std::string username, std::string match_name):
    p_socket(std::move(p_socket))
{
    this->car_model = 0; //Esto despues lo hacemos con un objeto!
    this->mode = mode;
    this->username = std::move(username);
    this->match_name = std::move(match_name);
}

Player::Player(Player&& other) noexcept:
    p_socket(std::move(other.p_socket)),
    username(std::move(other.username)),
    match_name(std::move(other.match_name))
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

void Player::send(std::vector<int32_t>& msg) {
    this->p_socket.send(msg);
}

void Player::send(std::string& msg) {
    this->p_socket.send(msg);
}

uint8_t Player::receive_option() {
    uint8_t option;
    this->p_socket.receive(option);
    return option;
}

void Player::kill() {
    this->p_socket.close();
}

bool Player::is_called(std::string &username) {
    return this->username == username;
}

void Player::set_car_model(uint8_t car_model) {
    this->car_model = car_model;
}


