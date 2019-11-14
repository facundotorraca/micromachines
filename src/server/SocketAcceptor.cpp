//
// Created by facundotorraca on 9/10/19.
//
#include "SocketAcceptor.h"
#include "SocketAcceptorError.h"
#include "common/Socket.h"
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <string>
#include <common/Configs.h>

#define ERROR -1
#define SUCCESS 0
#define INVALID_FD -1
#define MAX_PENDING_CONNECTIONS 10

/*--------------------------PUBLIC------------------------------*/
SocketAcceptor::SocketAcceptor() {
    this->fd = INVALID_FD;
}

void SocketAcceptor::bind(const std::string& port) {
    struct addrinfo *result;  //Pointer to the result list

    struct addrinfo hints = {}; //Criteria for selecting the socket addr structures
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;        //IPv4
    hints.ai_socktype = SOCK_STREAM;  //TCP
    hints.ai_flags = AI_PASSIVE;        //AI_PASSIVE for server, 0 for client
    getaddrinfo(nullptr, port.c_str(), &hints, &result);

    int yes=1;
    struct addrinfo *rst_iter = result;
    while (rst_iter) {
        this->fd = socket(rst_iter->ai_family, rst_iter->ai_socktype, rst_iter->ai_protocol);
        setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

        if (::bind(this->fd, rst_iter->ai_addr, rst_iter->ai_addrlen) == SUCCESS) {
            freeaddrinfo(result);
            return; //Bound successfully
        }
        ::close(this->fd);
        rst_iter = rst_iter->ai_next;
    }
    freeaddrinfo(result);
    throw SocketAcceptorError("SocketAcceptor: BIND Error");
}

void SocketAcceptor::listen() {
    if (::listen(this->fd, Configs::get_configs().socket_pending_connections) == ERROR) {
        throw SocketAcceptorError("SocketAceptor: LISTEN ERROR");
    }
}

Socket SocketAcceptor::accept() {
    int new_fd = ::accept(this->fd, nullptr, nullptr);
    if (new_fd == INVALID_FD) {
        throw SocketAcceptorError("Accept Failed");
    }
    Socket new_socket(new_fd);
    return new_socket;
}

void SocketAcceptor::close() {
    if (this->fd != INVALID_FD) {
        shutdown(this->fd, SHUT_RDWR);
        ::close(this->fd);
        this->fd = INVALID_FD;
    }
}

/*--------------------------PRIVATE-----------------------------*/
SocketAcceptor::~SocketAcceptor() {
    this->close();
}
