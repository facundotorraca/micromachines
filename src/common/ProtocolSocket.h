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
        void send(int32_t word);

        void send(std::string& message);

        void send(std::vector<int32_t>& bytes);
        void send(std::vector<uint8_t>& bytes);

        void receive(uint8_t& byte);

        void receive(std::vector<int32_t>& buffer);
        void receive(std::vector<uint8_t>& buffer);
        
        bool is_connected();

        void close();
};

#endif //MICROMACHINES_PROTOCOLSOCKET_H
