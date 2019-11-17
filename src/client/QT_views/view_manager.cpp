//
// Created by Alejo Acevedo on 18/10/2019.
//

#include "view_manager.h"
#include "./views/menuwindow.h"
#include "./views/connectview.cpp"
#include <iostream>

ViewManager::ViewManager(int argc, char *argv[])
                        : mainApp(argc, argv),
                        sck(),
                        arranged(false),
                        box_check(false) {}

ProtocolSocket ViewManager::run() {
    ConnectView connectView(this->sck);
    connectView.show();
    this->mainApp.exec();
    ProtocolSocket ps(std::move(this->sck));
    if (!ps.is_connected()) {
        return std::move(ps);
    }
    MenuWindow menuWindow(ps);
    menuWindow.show();
    this->mainApp.exec();
    if (!menuWindow.is_game_arranged()){
        return std::move(ps);
    }
    this->box_check = menuWindow.get_bot_check();
    this->arranged = true;
    return std::move(ps);
}

bool ViewManager::is_game_arranged() {
    return this->arranged;
}

bool ViewManager::use_bot() {
    return this->box_check;
}