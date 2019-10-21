//
// Created by Alejo Acevedo on 18/10/2019.
//

#include "view_manager.h"
#include "client_views/ConectView.h"
#include "client_views/MainWindow.h"
#include <iostream>

ViewManager::ViewManager(int argc, char *argv[])
                        : mainApp(argc, argv),
                        sck() {}

ProtocolSocket ViewManager::run() {
    ConectView conect_view(this->sck);
    conect_view.show();
    this->mainApp.exec();
    ProtocolSocket ps(std::move(this->sck));
    if(ps.is_connected()) {
        MainWindow main_window(ps);
        main_window.show();
        this->mainApp.exec();
        if(!main_window.is_fixed())
            return std::move(ProtocolSocket(std::move(Socket())));
    }
    return std::move(ps);
}