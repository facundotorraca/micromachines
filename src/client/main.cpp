#include <iostream>
#include <string>

#define SUCCESS 0

int main(int argc, char *argv[]) {
    std::string host(argv[1]);
    std::string port(argv[2]);

    std::cout << "Host: " << host << "\n";
    std::cout << "Port: " << port

    return SUCCESS;
}