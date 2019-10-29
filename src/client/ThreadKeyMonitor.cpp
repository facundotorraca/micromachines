//
// Created by javier on 16/10/19.
//

#include "ThreadKeyMonitor.h"
#include <SDL2/SDL.h>

ThreadKeyMonitor::ThreadKeyMonitor(Scene &scene) : Thread(), scene(scene) {}

void ThreadKeyMonitor::run() {
    SDL_Event event;
    while (this->running && SDL_WaitEvent(&event)) {
        auto& keyEvent = (SDL_KeyboardEvent&) event;

        if (event.type == SDL_QUIT){
            running = false;
            return;
        }

        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
            scene.handleKeyEvent(keyEvent.keysym.sym,
                                 (SDL_EventType)(event.type));


        /*switch (event.type) {
            case SDL_QUIT: {
                running = false;
                break;
            }

            case (SDL_KEYDOWN & SDL_KEYUP): {
                scene.handleKeyEvent(keyEvent.keysym.sym, SDL_KEYDOWN);
                break;
            }

            case SDL_KEYUP: {
                scene.handleKeyEvent(keyEvent.keysym.sym, SDL_KEYUP);
                break;
            }
        }*/
    }
}
