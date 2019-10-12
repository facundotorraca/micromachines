#include <iostream>
#include <cstring>
#include <string>
#include "common/Socket.h"

#define SUCCESS 0

int main(int argc, char *argv[]) {
    Socket s;
    s.connect("127.0.0.1", "7777");

    uint8_t mode = atoi(argv[1]);

    uint8_t len = strlen(argv[2]);
    std::string match_name(argv[2]);

    s.send(&mode, 1);

    s.send(&len, 1);
    s.send((uint8_t*)match_name.data(), len);

    uint8_t len_name = strlen(argv[3]);
    std::string username(argv[3]);

    s.send(&len_name, 1);
    s.send((uint8_t*)username.data(), len_name);

    uint8_t start = 1;

    std::string a;
    std::cout << "Press 1 to start... \n";
    std::cin >> a;
    // std::cout << "enviado " << start;

    s.send(&start, 1);
    std::cout << "enviado" << start << "\n";

    uint8_t buf[5];
    s.receive(buf, 5);
    std::cout <<"recibi" << "\n";
    std::string msg(reinterpret_cast<const char *>(buf), 5);
    std::cout << msg << "\n";

    return SUCCESS;
}