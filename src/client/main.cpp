#include <iostream>
#include <cstring>
#include <string>
#include <common/Socket.h>

#define SUCCESS 0

int main(int argc, char* argv[]) {
    std::string port("7778");
    std::string host("127.0.0.1");

    Socket s;
    s.connect(host, port);

    std::cout << "Press 1 to join match" << "\n";
    std::cout << "Press 2 to start match" << "\n";
    std::string mode; std::cin >> mode;

    if (mode == "1") {
        uint8_t join = 1;
        s.send(&join, 1);
    }
    if (mode == "2") {
        uint8_t start = 2;
        s.send(&start, 1);
    }

    std::cout << "Write match name" << "\n";
    std::string match_name; std::cin >> match_name;
    uint8_t match_name_size = (uint8_t) match_name.size();
    s.send(&match_name_size, 1);
    s.send((uint8_t*)match_name.data(),  match_name.size());

    std::cout << "Write your username name" << "\n";
    std::string username; std::cin >> username;
    uint8_t username_size = (uint8_t) username.size();
    s.send(&username_size, 1);
    s.send((uint8_t*)username.data(), username.size());

    if (mode == "2") {
        int any_key;
        std::cout << "Press any key to start" << "\n";
        std::cin >> any_key;
        uint8_t start_game = 1;
        s.send(&start_game, 1);
    } else {
        std::cout << "Waiting START game..." << "\n";
    }

    bool continue_receiving = true;
    while (continue_receiving) {
        uint8_t buf[10];
        s.receive(buf, 5);
        std::string msg(reinterpret_cast<const char *>(buf), 5);
        std::cout << msg << "\n";
    }

    return SUCCESS;
}