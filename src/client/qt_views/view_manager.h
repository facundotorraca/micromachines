//
// Created by Alejo Acevedo on 18/10/2019.
//

#ifndef MICROMACHINES_SRC_CLIENT_QT_VIEWS_CLIENT_VIEWS_VIEW_MANAGER_H_
#define MICROMACHINES_SRC_CLIENT_QT_VIEWS_CLIENT_VIEWS_VIEW_MANAGER_H_

#include <common/Socket.h>
#include "client/qt_views/client_views/ConectView.h"
#include "client/qt_views/client_views/MainWindow.h"
#include <QApplication>


class ViewManager {
  QApplication mainApp;
  ConectView conect_view;
  MainWindow main_window;
 public:
  ViewManager(int argc, char *argv[], Socket &sck);
  void run();
  ~ViewManager() {}
};

#endif //MICROMACHINES_SRC_CLIENT_QT_VIEWS_CLIENT_VIEWS_VIEW_MANAGER_H_
