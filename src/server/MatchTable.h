#ifndef MICROMACHINES_MATCHTABLE_H
#define MICROMACHINES_MATCHTABLE_H

#include <map>
#include <list>
#include <mutex>
#include <vector>
#include <memory>
#include "Match.h"
#include "common/Socket.h"
#include "server/Player.h"
#include <common/ProtocolSocket.h>

class MatchTable {
    std::mutex mtx;
    std::map<std::string, std::shared_ptr<Match>> map;

    public:
        void add(const std::string& match_name, std::shared_ptr<Match> match);

        std::shared_ptr<Match> get(const std::string& match_name);

        void send_matches(ProtocolSocket &p_socket);

        void remove_end_matches();
};


#endif //MICROMACHINES_MATCHTABLE_H

