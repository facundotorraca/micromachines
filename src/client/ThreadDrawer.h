//
// Created by javier on 16/10/19.
//

#ifndef MICROMACHINES_THREADDRAWER_H
#define MICROMACHINES_THREADDRAWER_H


#include <common/Thread.h>
#include "Scene.h"

class ThreadDrawer : public Thread{
    Scene* scene;
public:
    explicit ThreadDrawer(Scene& scene);
    void run() override;
};


#endif //MICROMACHINES_THREADDRAWER_H
