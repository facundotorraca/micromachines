#include <string>
#include <iostream>
#include <common/Socket.h>
#include <common/ProtocolSocket.h>
#include "GameMain.h"

#define SUCCESS 0

int main(int argc, char *argv[]) {
      /*Todo esto es lo que hizo facu
      * Habría que reemplazarlo por Qt*/

    std::string port("7778");
    std::string host("127.0.0.1");

    ViewManager view_manager(argc, argv);

    ProtocolSocket ps(view_manager.run());

    std::cout << "Press 1 to join match" << "\n";
    std::cout << "Press 2 to start match" << "\n";
    std::string mode; std::cin >> mode;

    if (mode == "1") {
        uint8_t join = 1;
        ps.send(join);
    }
    if (mode == "2") {
        uint8_t start = 2;
        ps.send(start);
    }

    std::vector<uint8_t> buffer(4096);

    std::string server_match_answer("ERROR");
    while (server_match_answer.substr(0,5) == "ERROR") {
        std::cout << "Write match name..." << "\n";
        std::string match_name; std::cin >> match_name;
        ps.send(match_name);
        ps.receive(buffer);
        server_match_answer.assign(reinterpret_cast<const char *>(buffer.data()), buffer.size());
        buffer.clear(); buffer.resize(4096);
        std::cout << server_match_answer;
    }

    std::string server_username_answer("ERROR");
    while (server_username_answer.substr(0,5) == "ERROR") {
        std::cout << "Write your username..." << "\n";
        std::string username; std::cin >> username;
        ps.send(username);
        ps.receive(buffer);
        server_username_answer.assign(reinterpret_cast<const char *>(buffer.data()), buffer.size());
        buffer.clear(); buffer.resize(4096);
        std::cout << server_username_answer;
    }

    if (mode == "2") {
        int any_key;
        std::cout << "Press any key to START" << "\n";
        std::cin >> any_key;
        uint8_t start_game = 1;
        ps.send(start_game);
    } else {
        std::cout << "Waiting for the game to START \n";
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

    //GameMain game(ps);
    //game.start();

    return SUCCESS;
}