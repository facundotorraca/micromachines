//
// Created by Alejo Acevedo on 18/10/2019.
//

#include "view_manager.h"

ViewManager::ViewManager(int argc, char *argv[], Socket &sck)
                        : mainApp(argc, argv),
                        main_window(sck),
                        conect_view(sck) {}

void ViewManager::run() {
    this->main_window.show();
    this->conect_view.show();
    this->mainApp.exec();
}