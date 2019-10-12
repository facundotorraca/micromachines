#include <iostream>
#include <cstring>
#include <string>
#include <common/Socket.h>

#define SUCCESS 0

int main(int argc, char *argv[]) {
    std::string port("7777");
    std::string host("127.0.0.1");

    Socket s;
    s.connect(host, port);

    uint8_t mode = (uint8_t)atoi(argv[1]);
    uint8_t len_match = strlen(argv[2]);
    uint8_t len_name = strlen(argv[3]);

    s.send(&mode, 1);
    s.send(&len_match, 1);
    s.send((uint8_t*)argv[2],len_match);
    s.send(&len_name,1);
    s.send((uint8_t*)argv[3],len_name);

    uint8_t start = 1;

    std::cout << "Press 1 to start match" << "\n";
    uint8_t a; std::cin >> a;

    std::cout << unsigned(start) << "\n";

    s.send(&start, 1);

    uint8_t buf[10];
    s.receive(buf, 5);
    std::string msg(reinterpret_cast<const char *>(buf), 5);

    std::cout << msg << "\n";
    return SUCCESS;
}