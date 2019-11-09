//
// Created by alejoacevedo on 11/9/19.
//

#include <fstream>
#include <iostream>
#include "Configs.h"

Configs::Configs() {
    std::cout << CONFIG_PATH << std::endl;
    std::ifstream conf_file(CONFIG_PATH);

    if (!conf_file.is_open()) {
        std::cerr << "CONFIG FILE ERROR" << std::endl;
        return; //ACA VA EXCEPION
    }

    this->conf_json << conf_file;
}

Configs& Configs::get_instance() {
    static Configs instance;
    return instance;
}
