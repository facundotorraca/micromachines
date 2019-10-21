#include <string>
#include <iostream>
#include <common/Socket.h>
#include <common/ProtocolSocket.h>
#include "view_manager.h"

#define SUCCESS 0

int main(int argc, char *argv[]) {
  ViewManager view_manager(argc, argv);
  ProtocolSocket ps = view_manager.run();
  while (true) {
    std::cout << "INFINITY LOOP\n";
  }
  /* Aca empieza SDL
   * "ps" es el ProtocolSocket ya conectado al servidor
   * se debería conectar en la ventana de qt
   */
  return SUCCESS;
}