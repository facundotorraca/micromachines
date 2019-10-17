#include <vector>
#include <string>
#include <iostream>
#include "Socket.h"
#include "ProtocolSocket.h"

#define END_BYTE '\n'

ProtocolSocket::ProtocolSocket(Socket &&socket):
    socket(std::move(socket))
{}

ProtocolSocket::ProtocolSocket(ProtocolSocket &&other) noexcept:
    socket(std::move(other.socket))
{}

void ProtocolSocket::send(std::string& message) {
    uint8_t len_message = message.length();
    this->socket.send(&len_message, 1);
    this->socket.send((uint8_t*)message.data(), len_message);
}

void ProtocolSocket::send(uint8_t byte) {
    this->socket.send(&byte, 1);
}

void ProtocolSocket::receive(std::vector<uint8_t>& buffer) {
    uint8_t len_next_message = 0;
    uint8_t buf[4096];
    this->socket.receive(&len_next_message, 1);
    size_t bytes_recv = this->socket.receive(buf, len_next_message);
    for (int i = 0; i < bytes_recv && i < 4096; i++){
        buffer.emplace_back(buf[i]);
    }
}

void ProtocolSocket::receive(uint8_t& byte) {
    this->socket.receive(&byte, 1);
}

void ProtocolSocket::close() {
    this->socket.close();
}

void ProtocolSocket::send(std::vector<uint8_t> &bytes) {
    uint8_t r = bytes.size();
    this->socket.send(&r, 1);
    for (auto byte : bytes) {
        this->socket.send(&byte, 1);
    }
}


