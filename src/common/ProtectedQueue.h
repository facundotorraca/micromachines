#ifndef MICROMACHINES_PROTECTEDQUEUE_H
#define MICROMACHINES_PROTECTEDQUEUE_H

#include <queue>
#include <mutex>
#include <cstdbool>
#include <condition_variable>
#include <iostream>
#include "ProtectedQueueError.h"

template <class T>
class ProtectedQueue {
    std::queue<T> queue;
    size_t max_q_len{};

    std::condition_variable cv_pop;
    std::condition_variable cv_push;
    std::mutex q_mtx;

    bool q_closed;

    public:
        explicit ProtectedQueue(size_t max_q_len):
            q_closed(false)
        {
            this->max_q_len = max_q_len;
            this->q_closed = false;
        }

        /* Esta bien esto*/
        void push(T&& t) {
            std::unique_lock<std::mutex> lock(this->q_mtx);
            while (this->queue.size() >= this->max_q_len) {
                this->cv_push.wait(lock);
            }

            this->queue.push(std::move(t));
            this->cv_pop.notify_all();
        }


        void push(T& t) {
            std::unique_lock<std::mutex> lock(this->q_mtx);
            while (this->queue.size() >= this->max_q_len) {
                this->cv_push.wait(lock);
            }

            this->queue.push(t);
            this->cv_pop.notify_all();
        }


        bool empty() {
            std::unique_lock<std::mutex> lock(this->q_mtx);
            return this->queue.empty();
        }

        void close() {
            std::unique_lock<std::mutex> lock(this->q_mtx);
            this->q_closed = true;
            //Notify free pass to take!
            this->cv_pop.notify_all();
        }

        bool closed() {
            std::unique_lock<std::mutex> lock(this->q_mtx);
            return this->q_closed;
        }

        T pop() {
            std::unique_lock<std::mutex> lock(this->q_mtx);
            while (this->queue.empty() && !this->q_closed) {
                this->cv_pop.wait(lock);
            }

            if (this->queue.empty()) {
                throw ProtectedQueueError("ProtectedQueue: POP Error");
            } else {
                T t = std::move(this->queue.front());
                this->queue.pop();
                this->cv_push.notify_all();
                return std::move(t);
            }
        }
};


#endif //MICROMACHINES_PROTECTEDQUEUE_H
