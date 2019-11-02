//
// Created by javier on 2/11/19.
//

#ifndef MICROMACHINES_COUNTDOWN_H
#define MICROMACHINES_COUNTDOWN_H

#include "Camera.h"

class Countdown {
    bool showing;
    std::string number;
    int32_t frames_drawing;
public:
    Countdown();
    void show(int32_t number);
    void draw(Camera& camera);
};


#endif //MICROMACHINES_COUNTDOWN_H
