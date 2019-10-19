//
// Created by javier on 19/10/19.
//

#ifndef MICROMACHINES_THREADUPDATESENDER_H
#define MICROMACHINES_THREADUPDATESENDER_H

#include <common/ProtectedQueue.h>
#include "server/Player.h"
#include "UpdateClient.h"
#include <common/Thread.h>

class ThreadUpdateSender : public Thread{
    Player& player;
    ProtectedQueue<UpdateClient>& updates;
    void run() override;

public:
    ThreadUpdateSender(Player& player, ProtectedQueue<UpdateClient>& updates);
};


#endif //MICROMACHINES_THREADUPDATESENDER_H
