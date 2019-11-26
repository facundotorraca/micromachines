//
// Created by javier on 16/10/19.
//

#include "ThreadKeyMonitor.h"
#include "KeyCommands/KeyCommand.h"

ThreadKeyMonitor::ThreadKeyMonitor(Scene &scene) : Thread(), scene(scene) {}

void ThreadKeyMonitor::tryHandleJoystick(SDL_Event& event){
    SDL_Keycode key;
    SDL_EventType downorup;
     
    if (event.type == SDL_JOYBUTTONDOWN){
        downorup = SDL_KEYDOWN;
    } else if (event.type == SDL_JOYBUTTONUP) {
        downorup = SDL_KEYUP;
    }

    if (event.type == SDL_JOYHATMOTION){
        if (event.jhat.value == SDL_HAT_LEFT || event.jhat.value == SDL_HAT_LEFTUP || event.jhat.value == SDL_HAT_LEFTDOWN){
            downorup = SDL_KEYDOWN;
            key = SDLK_LEFT;
        } else if (event.jhat.value == SDL_HAT_RIGHT || event.jhat.value == SDL_HAT_RIGHTUP || event.jhat.value == SDL_HAT_RIGHTDOWN){
            downorup = SDL_KEYDOWN;
            key = SDLK_RIGHT;
        } else if (event.jhat.value == SDL_HAT_UP || event.jhat.value == SDL_HAT_CENTERED || event.jhat.value == SDL_HAT_DOWN){
            downorup = SDL_KEYUP;
            key = SDLK_RIGHT;
        }
    } else if (event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP) {
        switch (event.jbutton.button){
            case 2: key = SDLK_UP; break;
            case 3: key = SDLK_DOWN; break;
            default: return;
        }
    } else {
        return;
    }
    this->scene.handleKeyEvent(key, downorup);
}

void ThreadKeyMonitor::run() {
    SDL_Event event;
    while (this->running && SDL_WaitEvent(&event)) {
        auto& keyEvent = (SDL_KeyboardEvent&) event;

        if (event.type == SDL_QUIT){
            running = false;
            return;
        }

        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            auto command = KeyCommand::create(scene, keyEvent.keysym.sym,
                                              (SDL_EventType) event.type);
            this->running = command->apply();
        } else {
            tryHandleJoystick(event);
        }
    }
}
