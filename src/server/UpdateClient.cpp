//
// Created by facundotorraca on 19/10/19.
//

#include "UpdateClient.h"

UpdateClient::UpdateClient(uint8_t msg_type, std::vector<int32_t>&& message):
    message(std::move(message))
{
    this->msg_type = msg_type;
}

void UpdateClient::send(ProtocolSocket &p_socket) {
    //p_socket.send(msg_type);
    p_socket.send(message);
}
