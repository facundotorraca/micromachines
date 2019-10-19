#ifndef MICROMACHINES_THREADDRAWER_H
#define MICROMACHINES_THREADDRAWER_H

#include "Scene.h"
#include <common/Thread.h>

class ThreadDrawer : public Thread {
    Scene* scene;
public:
    explicit ThreadDrawer(Scene& scene);
    void run() override;
};


#endif //MICROMACHINES_THREADDRAWER_H
