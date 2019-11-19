#include <fstream>
#include <iostream>
#include <model/Vehicle/CarSpecs.h>
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

    specs.max_life = this->conf_json["max_life"];
    specs.max_forward_speed = this->conf_json["max_forward_speed"];
    specs.max_backward_speed = this->conf_json["max_backward_speed"];
    specs.back_wheel_max_force = this->conf_json["back_wheel_max_force"];
    specs.front_wheel_max_force = this->conf_json["front_wheel_max_force"];
    specs.back_max_lateral_impulse = this->conf_json["back_max_lateral_impulse"];
    specs.front_max_lateral_impulse = this->conf_json["front_max_lateral_impulse"];

    use_dynamic_objects = this->conf_json["use_dynamic_objects"];
}

Configs& Configs::get_configs() {
    static Configs instance;
    return instance;
}
