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
           case MSG_EFFECT_BOOST:
               camera.drawFullScreenTexture(BOOST_TEX);
           case MSG_EFFECT_ROCK:
               camera.drawFullScreenTexture(ROCK_TEX);
       }
       if (frames_drawing > FRAMES_PER_SECOND*3){
           showing = false;
       }
   }
}

void ScreenEffectDrawer::show(int32_t number) {
    showing = true;
    frames_drawing = 0;
    effect = number;
}

ScreenEffectDrawer::ScreenEffectDrawer() : showing(false), effect(-1), frames_drawing(0){}
