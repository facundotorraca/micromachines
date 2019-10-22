//
// Created by javier on 16/10/19.
//

#ifndef MICROMACHINES_THREADKEYMONITOR_H
#define MICROMACHINES_THREADKEYMONITOR_H


#include <common/Thread.h>
#include "Scene.h"

class ThreadKeyMonitor : public Thread {
        Scene& scene;
    public:
        explicit ThreadKeyMonitor(Scene& scene);
        void run() override;
};


#endif //MICROMACHINES_THREADKEYMONITOR_H
