#ifndef MICROMACHINES_MATCHTABLE_H
#define MICROMACHINES_MATCHTABLE_H

#include <map>
#include <list>
#include <mutex>
#include <vector>
#include "Match.h"
#include "common/Socket.h"
#include "server/Player.h"
#include <common/ProtocolSocket.h>

class MatchTable {
    std::mutex mtx;
    std::map<std::string, Match*> map;

    public:
        void add(const std::string& match_name, Match* match);

        Match* get(const std::string& match_name);

        void send_matches(ProtocolSocket &p_socket);

        void remove_end_matches();
};


#endif //MICROMACHINES_MATCHTABLE_H

