#ifndef MICROMACHINES_PROTECTEDLIST_H
#define MICROMACHINES_PROTECTEDLIST_H

#include <list>
#include <mutex>
#include "Player.h"

class ProtectedList {
    std::mutex mtx;
    std::list<Player*> list;

    public:
        void append(Player* player);

        size_t size();

        Player* back();

};


#endif //MICROMACHINES_PROTECTEDLIST_H
