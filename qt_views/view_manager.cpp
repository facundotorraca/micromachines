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
  MainWindow main_window(ps);
  main_window.show();
  this->mainApp.exec();
  return std::move(ps);
}