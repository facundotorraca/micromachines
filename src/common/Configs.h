//
// Created by alejoacevedo on 11/9/19.
//

#ifndef MICROMACHINES_CONFIGS_H
#define MICROMACHINES_CONFIGS_H

#define CONFIG_PATH "configs.json"

#include <string>
#include "json/json.hpp"

using json = nlohmann::json;

class Configs {
    json conf_json;
    Configs();

public:
    static Configs& get_instance();
    template <typename T>
    T get(const std::string &key) {
        return this->conf_json[key].get<T>();
    }

};


#endif //MICROMACHINES_CONFIGS_H
