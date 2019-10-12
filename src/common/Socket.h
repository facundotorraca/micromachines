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

        explicit Socket(int fd);

        Socket(Socket&& other) noexcept;

        int receive(uint8_t* buf, size_t len);

        int send(uint8_t* buf, size_t len) const;

        void connect(const std::string& host, const std::string& port);

        void close();

        ~Socket();
};

#endif //MICROMACHINES_SOCKET_H
