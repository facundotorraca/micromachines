//
// Created by javier on 2/11/19.
//

#include "Countdown.h"

Countdown::Countdown() : showing(false), number("3"), frames_drawing(0) {}

void Countdown::draw(Camera &camera) {
    if (showing){
        camera.drawCountdownNumber(number);
        frames_drawing++;
        if (frames_drawing > FRAMES_PER_SECOND){
            showing = false;
        }
    }
}

void Countdown::show(int32_t n) {
    if (n > 0)
        this->number = std::to_string(n);
    else
        this->number = std::string("GO!");
    showing = true;
    frames_drawing = 0;
}
