#include "Server.h"
#include <common/Configs.h>

#define SUCCESS 0

int main() {
    Server server(Configs::get_configs().server_port);
    server.start();

    return SUCCESS;
}