//
// Created by javier on 8/11/19.
//

#include "ScreenEffectDrawer.h"
#include "common/MsgTypes.h"

void ScreenEffectDrawer::draw(Camera &camera) {
   if (showing) {
       frames_drawing++;
       switch (effect){
           case MSG_EFFECT_MUD:
               camera.drawFullScreenTexture(MUD_TEX);
               break;
           case MSG_EFFECT_BOOST:
               camera.drawScreenTexture(BOOST_TEX, 0.5, 0.8, 0.1);
               break;
           case MSG_EFFECT_ROCK:
               camera.drawFullScreenTexture(ROCK_TEX);
               break;
       }
       if (frames_drawing > FRAMES_PER_SECOND*duration){
           showing = false;
       }
   }
}

void ScreenEffectDrawer::show(int32_t number, int32_t duration) {
    showing = true;
    this->duration = duration;
    frames_drawing = 0;
    effect = number;
}

ScreenEffectDrawer::ScreenEffectDrawer() : showing(false), effect(-1), frames_drawing(0),
duration(0){}
