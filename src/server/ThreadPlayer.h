//
// Created by facundotorraca on 19/10/19.
//

#ifndef MICROMACHINES_THREADPLAYER_H
#define MICROMACHINES_THREADPLAYER_H


#include <common/Thread.h>
#include <common/ProtectedQueue.h>
#include "UpdateClient.h"
#include "UpdateRace.h"
#include "Player.h"

class ThreadPlayer : public Thread {
    ProtectedQueue<UpdateClient>& updates_send;
    ProtectedQueue<UpdateRace>& updates_recv;
    Player& player;

    private:
        void run() override;

    public:
        ThreadPlayer(ProtectedQueue<UpdateClient>& updates_send, ProtectedQueue<UpdateRace>& updates_recv, Player& player);
};


#endif //MICROMACHINES_THREADPLAYER_H
