#include <fstream>
#include <iostream>
#include "Configs.h"

Configs::Configs() {
    std::cout << CONFIG_PATH << std::endl;
    std::ifstream conf_file(CONFIG_PATH);

    if (!conf_file.is_open())
        std::cerr << "Config File ERROR: Not found" << std::endl;

    conf_file >> this->conf_json;

    map_name = this->conf_json["map_name"]; //Max 8!
    map_path = this->conf_json["map_path"];
    server_port = this->conf_json["server_port"];
    max_players = this->conf_json["max_players"];
    plugins_path = this->conf_json["plugins_path"];
    max_len_name = this->conf_json["max_len_name"];
    mod_oil_prob = this->conf_json["mod_oil_prob"];
    mod_mud_prob = this->conf_json["mod_mud_prob"];
    mod_fix_prob = this->conf_json["mod_fix_prob"];
    mod_rock_prob = this->conf_json["mod_rock_prob"];
    mod_boost_prob = this->conf_json["mod_boost_prob"];
    respawn_time = this->conf_json["respawn_time"]; //seconds
    server_frames = this->conf_json["server_frames"]; //FPS
    time_to_start = this->conf_json["time_to_start"]; //seconds
    modifier_spawn_prob = this->conf_json["modifier_spawn_prob"]; //0-1
    socket_pending_connections = this->conf_json["socket_pending_connections"];
}

Configs& Configs::get_configs() {
    static Configs instance;
    return instance;
}
