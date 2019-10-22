#ifndef MICROMACHINES_THREAD_H
#define MICROMACHINES_THREAD_H

#include <thread>
#include <atomic>

class Thread {
        std::thread thread;
    protected:
    std::atomic<bool> running;
public:
        Thread() : thread(), running(false){}

        void start() {
            this->running = true;
            thread = std::thread(&Thread::run, this);
        }

        void join() {
            thread.join();
        }

        virtual void run() = 0;

        virtual ~Thread() = default;

        void shutdown() {
            this->running = false;
        }

        bool dead() {
            return !this->running;
        }
};


#endif //MICROMACHINES_THREAD_H
