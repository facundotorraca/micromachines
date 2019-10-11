#ifndef MICROMACHINES_SOCKETACCEPTOR_H
#define MICROMACHINES_SOCKETACCEPTOR_H

#include "common/Socket.h"
#include <string>
#include <sys/types.h>
#include <sys/socket.h>

class SocketAcceptor {
    int fd;

    public:
        SocketAcceptor();

        void bind(const std::string& port);

        void listen();

        void close();

        Socket accept();

        ~SocketAcceptor();
};

#endif //MICROMACHINES_SOCKETACCEPTOR_H
