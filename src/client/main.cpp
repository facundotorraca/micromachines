//
// Created by aacevedo on 22/10/19.
//
#include <string>
#include <iostream>
#include <common/Socket.h>
#include <common/ProtocolSocket.h>
#include <client/qt_views/view_manager.h>
#include "GameMain.h"

#define SUCCESS 0

int main(int argc, char *argv[]) {
    ViewManager view_manager(argc, argv);
    ProtocolSocket ps(view_manager.run());
    if(!ps.is_connected()) return SUCCESS; // Deberia ser success?

    bool continue_receiving = true;

    GameMain game(ps);
    game.start();

    /* Aca empieza SDL
     * "ps" es el ProtocolSocket ya conectado al servidor
     * se debería conectar en la ventana de qt
     */
    return SUCCESS;
}
