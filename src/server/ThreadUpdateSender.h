#ifndef MICROMACHINES_THREADUPDATESENDER_H
#define MICROMACHINES_THREADUPDATESENDER_H

#include "UpdateClient.h"
#include "ClientUpdater.h"
#include "server/Player.h"
#include <common/Thread.h>
#include <common/ProtectedQueue.h>

class ThreadUpdateSender : public Thread{
    ClientUpdater& client_updater;
    Player& player;

    private:
        void run() override;

    public:
        ThreadUpdateSender(Player& player, ClientUpdater& client_updater);
};


#endif //MICROMACHINES_THREADUPDATESENDER_H
