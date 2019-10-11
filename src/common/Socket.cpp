//
// Created by facundotorraca on 9/10/19.
//
#include "Socket.h"
#include "SocketError.h"
#include <sys/socket.h>
#include <unistd.h>
#include <cstdint>
#include <cstring>
#include <netdb.h>
#include <string>

#define ERROR -1
#define SUCCESS 0
#define INVALID_FD -1

/*--------------------------PUBLIC------------------------------*/
Socket::Socket() {
    this->fd = INVALID_FD;
}

Socket::Socket(int fd) {
    this->fd = fd;
}

Socket::Socket(Socket&& other) noexcept {
    this->fd = other.fd;
    other.fd = INVALID_FD;
}

int Socket::receive(uint8_t* buf, size_t len) {
    size_t bytes_recv = 0, total_bytes = 0;
    while (total_bytes < len) {
        bytes_recv = recv(this->fd, (void*)&buf[total_bytes], len - total_bytes , MSG_NOSIGNAL);
        if (bytes_recv <= 0) {
            throw SocketError("Socket: RECV Error");
        }
        total_bytes += bytes_recv;
    }
    return total_bytes;
}

int Socket::send(uint8_t* buf, size_t len) {
    size_t bytes_sent = 0, total_bytes = 0;
    while (total_bytes < len) {
        bytes_sent = ::send(this->fd, (void*)&buf[total_bytes], len -total_bytes, MSG_NOSIGNAL);
        if (bytes_sent <= 0) {
            throw SocketError("Socket: SEND Error");
        }
        total_bytes += bytes_sent;
    }
    return total_bytes;
}

void Socket::connect(const std::string& host, const std::string& port) {
    struct addrinfo *result;  //Pointer to the result list

    struct addrinfo hints = {}; //Criteria for selecting the socket addr structures
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;        //IPv4
    hints.ai_socktype = SOCK_STREAM;  //TCP
    hints.ai_flags = 0;               //AI_PASSIVE for server, 0 for client
    getaddrinfo(host.c_str(), port.c_str(), &hints, &result);

    struct addrinfo *rst_iter = result;
    while (rst_iter) {
        this->fd = socket(rst_iter->ai_family, rst_iter->ai_socktype, rst_iter->ai_protocol);

        if (this->fd == ERROR) {
            freeaddrinfo(result);
            throw SocketError("Socket: CONNECT Error");
        }

        if (::connect(this->fd, rst_iter->ai_addr, rst_iter->ai_addrlen) == SUCCESS) {
            freeaddrinfo(result);
            return; //Connect succesfully
        }
        ::close(this->fd);
        rst_iter = rst_iter->ai_next;
    }
    freeaddrinfo(result);
    throw SocketError("Socket: CONNECT Error");
}

void Socket::close() {
    if (this->fd != INVALID_FD) {
        shutdown(this->fd, SHUT_RDWR);
        ::close(this->fd);
        this->fd = INVALID_FD;
    }
}

/*--------------------------PRIVATE-----------------------------*/
Socket::~Socket() {
    this->close();
}