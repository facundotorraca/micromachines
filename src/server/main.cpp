#include <iostream>
#include <string>
#include "Server.h"

#define SUCCESS 0

int main() {
    std::string port("7777");

    Server server(port);
    server.start();

    return SUCCESS;
}