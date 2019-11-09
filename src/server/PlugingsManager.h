//
// Created by alejo on 7/11/19.
//

#ifndef MICROMACHINES_PLUGINGSMANAGER_H
#define MICROMACHINES_PLUGINGSMANAGER_H

#define PLUG_INIT "init"
#define PLUG_EXECUTE "execute"
#define PLUG_DESTROY "destroy"


#include <unordered_map>
#include <model/Vehicle/Car.h>
#include <model/Race.h>
#include <dirent.h>

class PlugingsManager {

    Race &race;
    int32_t life;
    std::string path;
    std::vector<void*> libs;
    std::vector<void*> libs_attrs;

public:
    explicit PlugingsManager(Race &race, std::string path);
    void load_plugings();
    void execute();
    ~PlugingsManager();

};


#endif //MICROMACHINES_PLUGINGSMANAGER_H
