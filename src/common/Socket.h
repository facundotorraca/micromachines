//
// Created by facundotorraca on 9/10/19.
//

#ifndef MICROMACHINES_SOCKET_H
#define MICROMACHINES_SOCKET_H

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <vector>

class Socket {
    int fd;

public:

    Socket();

    Socket(int fd);

    Socket(Socket&& other);

    int receive(std::string& buf);

    int send(const std::string& msg);

    int connect(const std::string host, const std::string port);

    void close();

    ~Socket();
};

#endif //MICROMACHINES_SOCKET_H
