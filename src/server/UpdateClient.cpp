//
// Created by facundotorraca on 19/10/19.
//

#include "UpdateClient.h"

UpdateClient::UpdateClient(std::vector<int32_t>&& message):
    message(std::move(message))
{}

void UpdateClient::send(ProtocolSocket &p_socket) {
    p_socket.send(message);
}
