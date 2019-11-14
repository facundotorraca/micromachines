#include <iostream>
#include "UpdateClient.h"

UpdateClient::UpdateClient(std::vector<int32_t>&& message):
    message(std::move(message))
{}

UpdateClient::UpdateClient(std::string string_message):
    string_message(std::move(string_message))
{}

void UpdateClient::send(ProtocolSocket &p_socket) {
    if (!message.empty())
        p_socket.send(message);
    if (!string_message.empty())
        p_socket.send(string_message);
}
