#include <iostream>
#include <cstring>
#include <string>
#include <common/Socket.h>
#include <common/ProtocolSocket.h>

#define SUCCESS 0

void get_matches(ProtocolSocket& ps) {
    std::vector<uint8_t> buffer(4096, 1);

    ps.receive(buffer);
    std::string matches(reinterpret_cast<const char *>(buffer.data()), buffer.size());

    std::cout << "#-----------------PARTIDAS EXISTENTES---------------#\n";
    std::cout << matches;
    std::cout << "#---------------------------------------------------#\n";
}

int main(int argc, char* argv[]) {
    std::string port("7778");
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

    std::cout << "Write match name" << "\n";
    std::string match_name; std::cin >> match_name;
    ps.send(match_name);

    std::cout << "Write your username name" << "\n";
    std::string username; std::cin >> username;
    ps.send(username);

    if (mode == "2") {
        int any_key;
        std::cout << "Press any key to start" << "\n";
        std::cin >> any_key;
        uint8_t start_game = 1;
        ps.send(start_game);
    } else {
        std::cout << "Waiting START game..." << "\n";
    }

    bool continue_receiving = true;
    while (continue_receiving) {
        std::vector<uint8_t> buffer(4096);
        ps.receive(buffer);
        std::string msg(reinterpret_cast<const char *>(buffer.data()), 5);
        std::cout << msg << "\n";
        buffer.clear();
    }
    return SUCCESS;
}