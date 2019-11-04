#include <string>
#include <utility>
#include "Player.h"
#include <common/Socket.h>
#include <common/MsgTypes.h>

#define INVALID_ID -1
#define JOIN_MODE 1

#define KEY_VALUE_POS 0
#define KEY_STATE_POS 1

Player::Player(ProtocolSocket&& p_socket, uint8_t mode, std::string username, std::string match_name):
    p_socket(std::move(p_socket))
{
    this->ID = INVALID_ID;
    this->car_model = 0; //Esto despues lo hacemos con un objeto!
    this->mode = mode;
    this->username = std::move(username);
    this->match_name = std::move(match_name);

    this->playing = true;
    this->current_view_ID = this->ID;
}

Player::Player(Player&& other) noexcept:
    p_socket(std::move(other.p_socket)),
    username(std::move(other.username)),
    match_name(std::move(other.match_name))
{
    this->ID = other.ID;
    this->mode = other.mode;
    this->car_model = other.car_model;
    this->playing = other.playing;

    other.ID = INVALID_ID;
    other.playing = false;
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

void Player::set_car_model(int32_t _car_model) {
    this->car_model = _car_model;
}

UpdateRace Player::receive_update() {
    std::vector<int32_t> buffer;
    this->p_socket.receive(buffer);
    return {this->ID, buffer.at(KEY_VALUE_POS), buffer.at(KEY_STATE_POS)};
}

void Player::send(UpdateClient update) {
    update.send(p_socket);
}

void Player::set_ID(int32_t id) {
    this->ID = id;
}

bool Player::is_called(std::string& _username) {
    return this->username == _username;
}

void Player::send(uint8_t flag) {
    this->p_socket.send(flag);
}

Player::~Player() {
    this->kill();
}

void Player::set_view(int32_t key) {
    if (this->playing) {
        return;
    }
    key == KEY_LEFT ? (this->current_view_ID -= 1) : (this->current_view_ID += 1);

}

UpdateClient Player::get_view(int32_t total_players) {
    return UpdateClient({MSG_CAR_ID, (int32_t)(this->current_view_ID % total_players)} );
}

void Player::set_finished() {
    this->playing = false;
}
