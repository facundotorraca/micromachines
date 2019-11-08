//
// Created by javier on 8/11/19.
//

#ifndef MICROMACHINES_SCREENEFFECTDRAWER_H
#define MICROMACHINES_SCREENEFFECTDRAWER_H

#include "Camera.h"

class ScreenEffectDrawer {
    bool showing;
    int32_t effect;
    int32_t frames_drawing;
public:
    ScreenEffectDrawer();
    void show(int32_t number);
    void draw(Camera& camera);
};


#endif //MICROMACHINES_SCREENEFFECTDRAWER_H
