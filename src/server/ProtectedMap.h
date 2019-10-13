#ifndef MICROMACHINES_PROTECTEDMAP_H
#define MICROMACHINES_PROTECTEDMAP_H

#include <map>
#include <list>
#include <mutex>
#include <vector>
#include "Match.h"
#include "common/Socket.h"
#include "server/Player.h"

class ProtectedMap {
    std::mutex mtx;
    std::map<std::string, Match*> map;

    public:
        void add(const std::string& match_name, Match* match);

        Match* get(const std::string& match_name);

        void send_matches(Socket& socket);

        void remove_end_matches();
};


#endif //MICROMACHINES_PROTECTEDMAP_H

