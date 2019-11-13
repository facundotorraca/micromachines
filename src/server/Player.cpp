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
        p_socket(std::move(p_socket)),
        view_changed(false)
{
    this->ID = INVALID_ID;
    this->mode = mode;
    this->username = std::move(username);
    this->match_name = std::move(match_name);

    this->playing = true;
    this->current_view_ID = this->ID;
}

Player::Player(Player&& other) noexcept:
        p_socket(std::move(other.p_socket)),
        username(std::move(other.username)),
        match_name(std::move(other.match_name)),
        view_changed(false)
{
    this->ID = other.ID;
    this->mode = other.mode;
    this->playing = other.playing;
    this->current_view_ID = other.current_view_ID;

    other.playing = false;
    other.ID = INVALID_ID;
    other.current_view_ID = INVALID_ID;
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

void Player::send(uint8_t flag) {
    this->p_socket.send(flag);
}

uint8_t Player::receive_option() {
    uint8_t option;
    this->p_socket.receive(option);
    return option;
}

void Player::kill() {
    this->p_socket.close();
}

UpdateRace Player::receive_update() {
    std::vector<int32_t> buffer;
    this->p_socket.receive(buffer);
    try {
        return {this->ID, buffer.at(KEY_VALUE_POS), buffer.at(KEY_STATE_POS)};
    } catch (const std::out_of_range& e) {
        return {this->ID, NOT_PRESSED, NOT_PRESSED};
    }
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

Player::~Player() {
    this->kill();
}

void Player::set_view(int32_t key) {
    if (this->playing)
        return;
    this->view_changed = true;
    key == TURN_LEFT ? (this->current_view_ID -= 1) : (this->current_view_ID += 1);
}

void Player::update_view(int32_t total_players, ClientUpdater& updater) {
    if (this->view_changed) {
        UpdateClient update_view(std::vector<int32_t>{MSG_CAR_ID, (int32_t)(this->current_view_ID % total_players)});
        updater.send_to(this->ID, update_view);
        this->view_changed = false;
    }
}

void Player::set_finished(ClientUpdater& updater) {
    UpdateClient begin_username_flag(std::vector<int32_t>{MSG_PLAYER_FINISHED});
    UpdateClient username_info(this->username);
    updater.send_to_all(begin_username_flag);
    updater.send_to_all(username_info);
    this->playing = false;
}

void Player::restart_playing(ClientUpdater& updater) {
    this->current_view_ID = this->ID;

    UpdateClient update_view(std::vector<int32_t>{MSG_CAR_ID, this->ID});
    UpdateClient reset_hud(std::vector<int32_t>{MSG_RESET});
    updater.send_to(this->ID, update_view);
    updater.send_to(this->ID, reset_hud);

    this->playing = true;
}

int32_t Player::get_ID() {
    return this->ID;
}

bool Player::is_playing() {
    return this->playing;
}
