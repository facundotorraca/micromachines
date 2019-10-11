#ifndef MICROMACHINES_PROTECTEDMAP_H
#define MICROMACHINES_PROTECTEDMAP_H

#include "Player.h"
#include "ProtectedList.h"
#include <vector>
#include <mutex>
#include <map>

class ProtectedMap {
    std::mutex mtx;
    std::map<std::string, ProtectedList*> map;

    public:
        void add(std::string match_name, ProtectedList* lobby);

        ProtectedList* get(std::string match_name);
};


#endif //MICROMACHINES_PROTECTEDMAP_H
