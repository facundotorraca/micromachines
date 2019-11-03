#include "ThreadDrawer.h"
#include "Scene.h"
#include <thread>
#include <chrono>

ThreadDrawer::ThreadDrawer(Scene &scene) : Thread(), scene(scene) {}

void ThreadDrawer::run() {
    while (this->running) {
        auto start = std::chrono::high_resolution_clock::now();
        this->scene.draw();
        auto finish = std::chrono::high_resolution_clock::now();
        float duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
        std::cerr << duration << std::endl;
        if (duration > 16 || duration < 0)
            duration = 0;
        SDL_Delay(1000.0f/60.0f - duration);
    }
}
