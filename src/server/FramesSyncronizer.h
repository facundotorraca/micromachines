#ifndef MICROMACHINES_SYNCHRONIZER_H
#define MICROMACHINES_SYNCHRONIZER_H

#include <thread>

class FramesSynchronizer {
    public:
        static void sync_FPS(int FPS) {
            std::this_thread::sleep_for(std::chrono::milliseconds(int(1000/FPS)));
        }
};


#endif //MICROMACHINES_SYNCHRONIZER_H
