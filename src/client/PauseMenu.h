//
// Created by javier on 8/11/19.
//

#ifndef MICROMACHINES_PAUSEMENU_H
#define MICROMACHINES_PAUSEMENU_H

#include "Camera.h"

class PauseMenu {
    bool showing;
public:
    PauseMenu():showing(false){}
    void toggle(){
        showing = !showing;
    }
    bool canQuit(){
        return showing;
    }
    void draw(Camera& camera){
        if (showing){
            std::string quit("[Q] Quit");
            std::string resume("[ESC] Resume");
            camera.drawScreenTexture(PAUSE_MENU_TEX, 0.4, 0.4, 1);
            camera.drawText(quit, 0.45, 0.45, 0.5, quit.size());
            camera.drawText(resume, 0.45, 0.50, 0.5, resume.size());
        }
    }
};


#endif //MICROMACHINES_PAUSEMENU_H
