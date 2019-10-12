#ifndef MICROMACHINES_PROTECTEDMAP_H
#define MICROMACHINES_PROTECTEDMAP_H

#include "server/Player.h"
#include "Match.h"
#include <vector>
#include <mutex>
#include <list>
#include <map>

class ProtectedMap {
    std::mutex mtx;
    std::map<std::string, Match*> map;

    public:
        void add(std::string match_name, Match* match);

        Match* get(std::string match_name);

        void remove_end_matches();
};


#endif //MICROMACHINES_PROTECTEDMAP_H

