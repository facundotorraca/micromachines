#ifndef MICROMACHINES_THREAD_H
#define MICROMACHINES_THREAD_H

#include <thread>

class Thread {
    std::thread thread{};

    public:
        Thread() {}

        void start() {
            thread = std::thread(&Thread::run, this);
        }

        void join() {
            thread.join();
        }

        virtual void run() = 0;

        virtual ~Thread() {}
};


#endif //MICROMACHINES_THREAD_H
