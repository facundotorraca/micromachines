//
// Created by alejo on 7/11/19.
//

#ifndef MICROMACHINES_PLUGINGSMANAGER_H
#define MICROMACHINES_PLUGINGSMANAGER_H


#include <unordered_map>
#include <model/Vehicle/Car.h>
#include <boost/filesystem.hpp>

typedef struct {
    CarSpecs *cars

} pluging_params;

class PlugingsManager {

    std::unordered_map<int32_t, Car> cars;

public:
    PlugingsManager();

};


#endif //MICROMACHINES_PLUGINGSMANAGER_H
