#ifndef MICROMACHINES_THREADUPDATESENDER_H
#define MICROMACHINES_THREADUPDATESENDER_H

#include <common/ProtectedQueue.h>
#include "server/Player.h"
#include "UpdateClient.h"
#include <common/Thread.h>

class ThreadUpdateSender : public Thread{
    ProtectedQueue<UpdateClient>& updates;
    Player& player;

    private:
        void run() override;

    public:
        ThreadUpdateSender(Player& player, ProtectedQueue<UpdateClient>& updates);
};


#endif //MICROMACHINES_THREADUPDATESENDER_H
