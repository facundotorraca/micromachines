//
// Created by facundotorraca on 10/10/19.
//

#ifndef MICROMACHINES_PROTECTEDQUEUE_H
#define MICROMACHINES_PROTECTEDQUEUE_H

#include <queue>
#include <mutex>
#include <cstdbool>
#include <condition_variable>
#include "Player.h"

class ProtectedQueue {
        size_t max_q_len;
        std::queue<Player*> queue;
        std::condition_variable cv_pop;
        std::condition_variable cv_push;
        std::mutex q_mtx;
        bool q_closed;

    public:
        explicit ProtectedQueue(size_t max_q_len);

        ProtectedQueue(ProtectedQueue&& p_queue);

        void push(Player* player);

        bool empty();

        void close();

        bool closed();

        Player* pop();

        ~ProtectedQueue();
};


#endif //MICROMACHINES_PROTECTEDQUEUE_H
