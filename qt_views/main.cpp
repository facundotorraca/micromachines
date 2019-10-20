#include <string>
#include <iostream>
#include <common/Socket.h>
#include <common/ProtocolSocket.h>
#include "view_manager.h"

#define SUCCESS 0

int main(int argc, char *argv[]) {
  ViewManager view_manager(argc, argv);
  ProtocolSocket ps = view_manager.run();

  std::vector<uint8_t> buffer(4096);
  std::string mode = "2";
  if (mode == "2") {
    int any_key;
    std::cout << "Press any key to START" << "\n";
    std::cin >> any_key;
    uint8_t start_game = 1;
    ps.send(start_game);
  } else {
    std::cout << "Waiting for the game to START \n";
    uint8_t car = 1;
    ps.send(car);
  }

  bool continue_receiving = true;
  ps.receive(buffer);
  std::string welcome_message(reinterpret_cast<const char *>(buffer.data()), buffer.size());
  std::cout << welcome_message;
  if (welcome_message.substr(0,5) == "ERROR") {
    continue_receiving = false;
  }

  /* Aca empieza SDL
   * "ps" es el ProtocolSocket ya conectado al servidor
   * se debería conectar en la ventana de qt
   */
  return SUCCESS;
}