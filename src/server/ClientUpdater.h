#ifndef MICROMACHINES_CLIENTUPDATER_H
#define MICROMACHINES_CLIENTUPDATER_H

#include <cstdint>
#include <unordered_map>
#include "UpdateClient.h"
#include <common/ProtectedQueue.h>

class ClientUpdater {

    std::unordered_map<int32_t, ProtectedQueue<UpdateClient>> updates_players;

    public:
        void close_queue(int32_t ID);

        void remove_queue(int32_t ID);

        UpdateClient get_update(int32_t ID);

        void send_to_all(UpdateClient update);

        void send_to(int32_t ID, UpdateClient update);

        void create_update_queue(int32_t ID, size_t max_size);
};


#endif //MICROMACHINES_CLIENTUPDATER_H
