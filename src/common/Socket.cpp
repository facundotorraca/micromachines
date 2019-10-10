//
// Created by facundotorraca on 9/10/19.
//

#include "Socket.h"
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <string>

#define ERROR 1
#define SUCCESS 0
#define INVALID_FD -1

/*--------------------------PUBLIC------------------------------*/
Socket::Socket() {
    this->fd = INVALID_FD;
}

Socket::Socket(int fd) {
    this->fd = fd;
}

Socket::Socket(Socket&& other) {
    this->fd = other.fd;
    other.fd = INVALID_FD;
}

int Socket::receive(std::string& buf) {
    int flag;
    char byte_buf;
    do {
        flag = recv(this->fd, (void*)&byte_buf, 1, MSG_NOSIGNAL);
        if (flag == 0 || flag == -1) {
            return ERROR;
        }
        buf.push_back(byte_buf);
    } while (byte_buf != '\n');
    return SUCCESS;
}

int Socket::send(const std::string& msg) {
    const char* msg_buf = reinterpret_cast<const char*>(msg.data());
    int msg_size = msg.length();

    int bytes_sent = 0, total_bytes = 0, rem_bytes = 0;
    while (total_bytes != msg_size) {
        rem_bytes = msg_size - total_bytes;
        bytes_sent = ::send(this->fd,
                            (void*)&msg_buf[total_bytes],
                            rem_bytes,
                            MSG_NOSIGNAL);

        if (bytes_sent == 0 || bytes_sent == -1) {
            return ERROR;
        }
        total_bytes = total_bytes + bytes_sent;
    }
    return SUCCESS;
}

int Socket::connect(const std::string host, const std:: string port) {
    struct addrinfo *result;  //Pointer to the result list

    struct addrinfo hints; //Criteria for selecting the socket addr structures
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;        //IPv4
    hints.ai_socktype = SOCK_STREAM;  //TCP
    hints.ai_flags = 0;        //AI_PASSIVE for server, 0 for client
    getaddrinfo(host.c_str(), port.c_str(), &hints, &result);

    struct addrinfo *rst_iter = result;
    while (rst_iter) {
        this->fd = socket(rst_iter->ai_family,
                          rst_iter->ai_socktype,
                          rst_iter->ai_protocol);

        if (this->fd == -1) {
            freeaddrinfo(result);
            return ERROR;
        }

        if (::connect(this->fd,
                      rst_iter->ai_addr,
                      rst_iter->ai_addrlen) == SUCCESS) {
            freeaddrinfo(result);
            return SUCCESS;
        }
        ::close(this->fd);
        rst_iter = rst_iter->ai_next;
    }
    freeaddrinfo(result);
    return ERROR;
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