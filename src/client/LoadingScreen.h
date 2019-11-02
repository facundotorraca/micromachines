//
// Created by javier on 2/11/19.
//

#ifndef MICROMACHINES_LOADINGSCREEN_H
#define MICROMACHINES_LOADINGSCREEN_H

#include "Camera.h"

class LoadingScreen {
    bool showing;
public:
    LoadingScreen();
    void show();
    void hide();
    void draw(Camera& camera);
};


#endif //MICROMACHINES_LOADINGSCREEN_H
