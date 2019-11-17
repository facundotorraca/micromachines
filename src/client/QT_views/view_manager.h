//
// Created by Alejo Acevedo on 18/10/2019.
//

#ifndef MICROMACHINES_SRC_CLIENT_QT_VIEWS_CLIENT_VIEWS_VIEW_MANAGER_H_
#define MICROMACHINES_SRC_CLIENT_QT_VIEWS_CLIENT_VIEWS_VIEW_MANAGER_H_

#include <common/Socket.h>
#include <common/ProtocolSocket.h>
#include <QApplication>


class ViewManager {
    QApplication mainApp;
    Socket sck;
    bool arranged;
    bool box_check;
 public:
    ViewManager(int argc, char *argv[]);
    ProtocolSocket run();
    bool is_game_arranged();
    bool use_bot();
    ~ViewManager() {}
};

#endif //MICROMACHINES_SRC_CLIENT_QT_VIEWS_CLIENT_VIEWS_VIEW_MANAGER_H_
