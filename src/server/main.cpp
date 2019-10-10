#include <iostream>
#include <string>

#define SUCCESS 0

int main(int argc, char *argv[]) {
    std::string port(argv[1]);

    std::cout << "Port: " << port << "\n";

    return SUCCESS;
}