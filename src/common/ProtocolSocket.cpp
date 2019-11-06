#include <vector>
#include <string>
#include "Socket.h"
#include <iostream>
#include <netinet/in.h>
#include "ProtocolSocket.h"

ProtocolSocket::ProtocolSocket(Socket &&socket):
    socket(std::move(socket))
{}

ProtocolSocket::ProtocolSocket(ProtocolSocket &&other) noexcept:
    socket(std::move(other.socket))
{}

void ProtocolSocket::send(uint8_t byte) {
    this->socket.send(&byte, 1);
}

void ProtocolSocket::send(int32_t word) {
    this->socket.send((uint8_t*)&word, 4);
}

void ProtocolSocket::send(std::string& message) {
    uint8_t len_message = message.length();
    this->socket.send(&len_message, 1);
    this->socket.send((uint8_t*)message.data(), len_message);
}

void ProtocolSocket::send(std::vector<int32_t> &buffer) {
    uint8_t r = buffer.size();
    this->socket.send(&r, 1);
    for (auto byte : buffer) {
        auto net = htonl(byte);
        this->socket.send((uint8_t*)&net, 4);
    }
}

void ProtocolSocket::receive(int32_t &word) {
    this->socket.receive((uint8_t*)&word, 4);
}

void ProtocolSocket::receive(uint8_t& byte) {
    this->socket.receive(&byte, 1);
}

void ProtocolSocket::receive(std::string& message) {
    uint8_t len_next_message = 0;
    this->socket.receive(&len_next_message, 1);
    size_t bytes_recv = this->socket.receive((uint8_t*)message.data(), len_next_message);
    message.resize(bytes_recv);
}

void ProtocolSocket::receive(std::vector<int32_t>& buffer) {
    uint8_t len_next_message = 0;
    int32_t buf;
    this->socket.receive(&len_next_message, 1);

    for (int i = 0; i < len_next_message; i++) {
        this->socket.receive((uint8_t*)&buf, 4);
        buffer.emplace_back(ntohl(buf));
    }
}

void ProtocolSocket::close() {
    this->socket.close();
}

bool ProtocolSocket::is_connected() {
    return this->socket.get_connect();
}


