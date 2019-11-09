//
// Created by javier on 8/11/19.
//

#ifndef MICROMACHINES_PAUSEMENU_H
#define MICROMACHINES_PAUSEMENU_H

#include "Camera.h"

class PauseMenu {
    bool showing;
    bool connection_lost;
public:
    PauseMenu():showing(false), connection_lost(false){}
    void toggle(){
        showing = !showing;
    }
    bool canQuit(){
        return showing;
    }
    void draw(Camera& camera){
        if (showing){
            std::string quit("[Q] Quit");
            camera.drawScreenTexture(PAUSE_MENU_TEX, 0.4, 0.4, 1);
            camera.drawText(quit, 0.45, 0.50, 0.5, quit.size());
            if (connection_lost){
                std::string c_lost("Connection Lost");
                camera.drawText(c_lost, 0.41, 0.45, 0.54, c_lost.size());
            } else {
                std::string resume("[ESC] Resume");
                camera.drawText(resume, 0.45, 0.55, 0.5, resume.size());
            }
        }
    }

    void addConnectionLostMessage() {
        connection_lost = true;
    }

};


#endif //MICROMACHINES_PAUSEMENU_H
