//
// Created by javier on 16/10/19.
//

#ifndef MICROMACHINES_THREADKEYMONITOR_H
#define MICROMACHINES_THREADKEYMONITOR_H


#include <common/Thread.h>
#include "Scene.h"
#include <SDL2/SDL.h>

class ThreadKeyMonitor : public Thread {
        Scene& scene;
        void tryHandleJoystick(SDL_Event& event);
    public:
        explicit ThreadKeyMonitor(Scene& scene);
        void run() override;
};


#endif //MICROMACHINES_THREADKEYMONITOR_H
