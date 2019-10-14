#include <string>
#include <vector>
#include "Socket.h"

#ifndef MICROMACHINES_PROTOCOLSOCKET_H
#define MICROMACHINES_PROTOCOLSOCKET_H


class ProtocolSocket {
    Socket socket;

    public:
        explicit ProtocolSocket(Socket&& socket);

        ProtocolSocket(ProtocolSocket &&other) noexcept;

        void send(uint8_t byte);

        void send_end_byte();

        void send(std::string& message);

        void receive(uint8_t& byte);

        void receive(std::vector<uint8_t>& buffer);

        void receive_until_end_byte(std::vector<uint8_t>& buffer);

    void close();
};


#endif //MICROMACHINES_PROTOCOLSOCKET_H
