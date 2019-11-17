#include <string>
#include <iostream>
#include "GameMain.h"
#include <common/Socket.h>
#include <common/MsgTypes.h>
#include <common/ProtocolSocket.h>

#define SUCCESS 0

void get_matches(ProtocolSocket& ps) {
    std::string matches(1024, '\0');

    ps.receive(matches);
    //std::string matches(reinterpret_cast<const char *>(buffer.data()), buffer.size());

    std::cout << "#-----------------PARTIDAS EXISTENTES---------------#\n";
    std::cout << matches;
    std::cout << "#---------------------------------------------------#\n";
}

int main(int argc, char *argv[]) {
    /*Todo esto es lo que hizo facu
    * Habría que reemplazarlo por Qt*/

    std::string port("7777");
    std::string host("127.0.0.1");

    Socket s;
    s.connect(host, port);
    ProtocolSocket ps(std::move(s));

    get_matches(ps);

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

    uint8_t flag_error_username = 1;
    ps.send((uint8_t)MSG_SET_USERNAME);
    std::cout << "Write your username..." << "\n";
    std::string username; std::cin >> username;
    ps.send(username);
    ps.receive(flag_error_username);
    std::cout << "Answer: " << unsigned(flag_error_username) << "\n";


    ps.send((uint8_t)MSG_SET_MATCH_NAME);
    uint8_t flag_error_match = 1;
    while (flag_error_match == 1) {
        std::cout << "Write match name..." << "\n";
        std::string match_name; std::cin >> match_name;
        ps.send(match_name);
        ps.receive(flag_error_match);
        std::cout << "Answer: " << unsigned(flag_error_match) << "\n";
    }

    ps.send((uint8_t)MSG_SET_USERNAME);
    flag_error_username = 1;
    while (flag_error_username == 1) {
        std::cout << "Write your username..." << "\n";
        std::string username; std::cin >> username;
        ps.send(username);
        ps.receive(flag_error_username);
        std::cout << "Answer: " << unsigned(flag_error_username) << "\n";
    }


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
    uint8_t flag_join_match;
    ps.receive(flag_join_match);
    std::cout << "Flag JOIN: " << unsigned(flag_join_match) << "\n";

    /* Aca empieza SDL
     * "ps" es el ProtocolSocket ya conectado al servidor
     * se debería conectar en la ventana de qt
     */

    uint8_t flag_start_match = 1;
    ps.receive(flag_start_match);

    if (flag_start_match == 0) {
        GameMain game(ps, false);
        game.start();
    } else {
        std::cout << "Flag MATCH: " << unsigned(flag_start_match) << " ERROR\n";
    }

    return SUCCESS;
}