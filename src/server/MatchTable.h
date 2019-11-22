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
    std::map<std::string, std::shared_ptr<Match>> map;
    std::mutex mtx;

    public:
        bool username_available(std::string& username, std::string& match_name);

        void add(const std::string& match_name, std::shared_ptr<Match> match);

        std::shared_ptr<Match> get(const std::string& match_name);

        bool match_name_available(std::string& match_name);

        void send_matches(ProtocolSocket &p_socket);

        void remove_match(std::string match_name);

        void remove_end_matches();
};


#endif //MICROMACHINES_MATCHTABLE_H

