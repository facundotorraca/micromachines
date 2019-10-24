#include "ThreadDrawer.h"
#include "Scene.h"
#include <thread>
#include <chrono>

ThreadDrawer::ThreadDrawer(Scene &scene) : Thread(), scene(scene) {}

void ThreadDrawer::run() {
    while (this->running) {
        SDL_Delay(1000.0f/30.0f);
        this->scene.draw();
    }
}
