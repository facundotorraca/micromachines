//
// Created by alejo on 7/11/19.
//

#ifndef MICROMACHINES_PLUGINGSMANAGER_H
#define MICROMACHINES_PLUGINGSMANAGER_H

#define PLUG_EXECUTE "execute"


#include <unordered_map>
#include <model/Vehicle/Car.h>
#include <model/Race.h>
#include <dirent.h>

typedef struct {
    CarSpecs *cars;
    int car_len;
} PlugingsParams;

class PlugingsManager {

    std::unordered_map<int32_t, Car> &cars;
    std::vector<int32_t> cars_ids;
    std::string path;
    std::vector<void*> libs;
    PlugingsParams params;

public:
    explicit PlugingsManager(Race &race, std::string path);
    void load_plugings();
    void execute();
    ~PlugingsManager();

private:
    void setParams();
};


#endif //MICROMACHINES_PLUGINGSMANAGER_H
