//
// Created by javier on 16/10/19.
//

#include "ThreadDrawer.h"
#include "Scene.h"
#include <thread>
#include <chrono>

ThreadDrawer::ThreadDrawer(Scene &scene) : Thread(), scene(&scene) {}

void ThreadDrawer::run() {
    while (running) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(33));
        SDL_Delay(16);
        this->scene->draw();
    }
}
