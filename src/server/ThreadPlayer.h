#ifndef MICROMACHINES_THREADPLAYER_H
#define MICROMACHINES_THREADPLAYER_H

#include "Player.h"
#include "UpdateRace.h"
#include "UpdateClient.h"
#include <common/Thread.h>
#include "ThreadUpdateSender.h"
#include <common/ProtectedQueue.h>

class ThreadPlayer : public Thread {
    ProtectedQueue<UpdateClient>& updates_send;
    ProtectedQueue<UpdateRace>& updates_recv;

    std::atomic<bool> player_on_hold;

    ThreadUpdateSender sender;
    Player& player;

    private:
        void run() override;

        void stop();

    public:
        ThreadPlayer(ProtectedQueue<UpdateClient>& updates_send, ProtectedQueue<UpdateRace>& updates_recv, Player& player);

        void set_player_on_hold();

        void set_player_free();
};


#endif //MICROMACHINES_THREADPLAYER_H
