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
    this->socket.receive(&len_next_message, 1);
    size_t bytes_recv = this->socket.receive(buffer.data(), len_next_message);
    buffer.resize(bytes_recv);
}


void ProtocolSocket::receive(uint8_t& byte) {
    this->socket.receive(&byte, 1);
}

void ProtocolSocket::send_end_byte() {
    uint8_t len_end_byte = 1;
    uint8_t end_byte = END_BYTE;
    this->socket.send(&len_end_byte, 1);
    this->socket.send(&end_byte, 1);
}

void ProtocolSocket::receive_until_end_byte(std::vector<uint8_t>& buffer) {
    std::vector<uint8_t> internal_buffer(4096);
    uint8_t len_next_msg;
    size_t bytes_recv = 0, bytes_saved = 0;
    do  {
        this->socket.receive(&len_next_msg, 1);
        bytes_recv += this->socket.receive(&buffer[bytes_recv], len_next_msg);
        std::cout << "Tam" << buffer.size() << "\n";
    } while (buffer.back() != END_BYTE && len_next_msg == 1);
}


