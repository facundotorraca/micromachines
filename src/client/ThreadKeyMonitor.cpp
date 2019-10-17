//
// Created by javier on 16/10/19.
//

#include "ThreadKeyMonitor.h"
#include <SDL2/SDL.h>

ThreadKeyMonitor::ThreadKeyMonitor(Scene &scene) : scene(&scene) {}

void ThreadKeyMonitor::run() {
    auto running = true;
    SDL_Event e;
    while (SDL_WaitEvent(&e) && running) {
        auto& keyEvent = (SDL_KeyboardEvent&) e;
        switch (e.type) {
            case SDL_QUIT: running = false; break;
            case SDL_KEYDOWN: {
                scene->handleKeyEvent(keyEvent.keysym.sym, SDL_KEYDOWN);
            }
            case SDL_KEYUP: {
                scene->handleKeyEvent(keyEvent.keysym.sym, SDL_KEYUP);
            }
        }
    }
}
