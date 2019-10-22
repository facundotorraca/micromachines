//
// Created by javier on 16/10/19.
//

#include "ThreadKeyMonitor.h"
#include <SDL2/SDL.h>

ThreadKeyMonitor::ThreadKeyMonitor(Scene &scene) : Thread(), scene(scene) {}

void ThreadKeyMonitor::run() {
    SDL_Event event;
    while (SDL_WaitEvent(&event) && this->running) {
        auto& keyEvent = (SDL_KeyboardEvent&) event;

        switch (event.type) {
            case SDL_QUIT: {
                running = false;
                break;
            }

            case SDL_KEYDOWN: {
                scene.handleKeyEvent(keyEvent.keysym.sym, SDL_KEYDOWN);
                break;
            }

            case SDL_KEYUP: {
                scene.handleKeyEvent(keyEvent.keysym.sym, SDL_KEYUP);
                break;
            }
        }
    }
}
