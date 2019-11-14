//
// Created by alejo on 7/11/19.
//

#ifndef MICROMACHINES_PLUGINSMANAGER_H
#define MICROMACHINES_PLUGINSMANAGER_H

#define PLUG_INIT "init"
#define PLUG_EXECUTE "execute"
#define PLUG_DESTROY "destroy"


#include <unordered_map>
#include <model/Vehicle/Car.h>
#include <model/Race.h>
#include <dirent.h>

class PluginsManager {

    Race &race;
    int32_t life;
    std::string path;
    std::vector<void*> libs;
    std::vector<void*> libs_attrs;

public:
    explicit PluginsManager(Race &race, std::string path);
    void load_plugins();
    void execute();
    ~PluginsManager();

};


#endif //MICROMACHINES_PLUGINSMANAGER_H
