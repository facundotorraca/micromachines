#ifndef MICROMACHINES_PROTECTEDQUEUEMATCH_H
#define MICROMACHINES_PROTECTEDQUEUEMATCH_H

#include <queue>
#include <mutex>
#include "Match.h"
#include <cstdbool>
#include <condition_variable>

class ProtectedQueueMatch {
        std::queue<Match*> queue;
        size_t max_q_len;

        std::condition_variable cv_pop;
        std::condition_variable cv_push;
        std::mutex q_mtx;

        bool q_closed;

    public:
        explicit ProtectedQueueMatch(size_t max_q_len);

    //  ProtectedQueue(ProtectedQueue&& p_queue);

        void push(Match* match);

        bool empty();

        void close();

        bool closed();

        Match* pop();

        ~ProtectedQueueMatch();
};


#endif //MICROMACHINES_PROTECTEDQUEUEMATCH_H
