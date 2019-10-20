//
// Created by facundotorraca on 19/10/19.
//

#include "UpdateClient.h"

void UpdateClient::send(ProtocolSocket &p_socket) {
    std::vector<int32_t> hola{MSG_CAR_ID, 1};
    std::vector<int32_t> track{MSG_MAP, 1};
}
