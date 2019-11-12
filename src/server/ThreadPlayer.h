#ifndef MICROMACHINES_THREADPLAYER_H
#define MICROMACHINES_THREADPLAYER_H

#include "Player.h"
#include "UpdateRace.h"
#include "UpdateClient.h"
#include "ClientUpdater.h"
#include <common/Thread.h>
#include "ThreadUpdateSender.h"
#include <common/ProtectedQueue.h>

class ThreadPlayer : public Thread {
    ClientUpdater& client_updater;
    ProtectedQueue<UpdateRace>& updates_recv;

    ThreadUpdateSender sender;
    Player& player;

    std::atomic<bool> on_hold;

    private:
        void run() override;

        void stop();

    public:
        ThreadPlayer(ClientUpdater& client_updater, ProtectedQueue<UpdateRace>& updates_recv, Player& player);

        void resume();

        void set_on_hold();
};


#endif //MICROMACHINES_THREADPLAYER_H
