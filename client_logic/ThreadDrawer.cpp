//
// Created by javier on 16/10/19.
//

#include "ThreadDrawer.h"
#include "Scene.h"

ThreadDrawer::ThreadDrawer(Scene &scene) : scene(&scene) {}

void ThreadDrawer::run() {
    this->scene->draw();
}
