#include "ThreadDrawer.h"
#include "Scene.h"
#include <thread>
#include <chrono>

#define FPS_CONSTANT 22

ThreadDrawer::ThreadDrawer(Scene &scene) : Thread(), scene(scene) {}

void ThreadDrawer::run() {
    auto ticks = SDL_GetTicks();
    float prev_ticks;
    while (this->running) {
        prev_ticks = ticks;
        ticks = SDL_GetTicks();
        this->scene.draw();
        auto x = ticks - prev_ticks;
        std::cerr << (x) << std::endl;
        if (x < 16)
            SDL_Delay(16 - x);
    }
}
