#include <string>
#include "Server.h"

#define SUCCESS 0

int main() {
    std::string port("7778");

    Server server(port);
    server.start();

    return SUCCESS;
}