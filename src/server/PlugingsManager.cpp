//
// Created by alejo on 7/11/19.
//

#include "PlugingsManager.h"
#include <dlfcn.h>



PlugingsManager::PlugingsManager(Race &race,
                                 std::string path) : cars(race.get_cars()),
                                                     cars_ids(this->cars.size()),
                                                     path(path),
                                                     libs(),
                                                     params() {
    this->params.car_len = 0;
    this->params.cars = new CarSpecs[MAX_USER_PER_MATCH];
}

void PlugingsManager::load_plugings() {
    DIR *pDIR;
    struct dirent *entry;
    if (pDIR = opendir(this->path.c_str())) {
        while (entry = readdir(pDIR)) {
            if (std::string(".").compare(entry->d_name) !=0 && std::string("..").compare(entry->d_name) != 0) {
                std::string path = this->path + std::string(entry->d_name);
                this->libs.push_back(dlopen(path.c_str(), RTLD_NOW));
                std::cout << path << std::endl;
            }
        }
    }
    closedir(pDIR);
}

void PlugingsManager::execute() {
    void (*fun_dl)(PlugingsParams*);
    this->setParams();
    for (size_t ind = 0; ind < this->libs.size(); ind++ ) {
        *(void**) (&fun_dl) = dlsym(this->libs.at(ind), PLUG_EXECUTE);
        if (fun_dl == NULL) {
            std::cout << "NO ENCCONTRE LA FUNCION " << PLUG_EXECUTE << std::endl;
        } else {
            std::cout << "SI ENCONTRE LA FUNCION " << PLUG_EXECUTE <<std::endl;
            fun_dl(&this->params);
        }
    }
    for (size_t ind = 0; ind < this->params.car_len; ind++) {
        std::cout << this->params.cars[ind].max_life << std::endl;
    }
};

PlugingsManager::~PlugingsManager() {
    for (size_t ind = 0; ind < this->libs.size(); ind++ ) {
        dlclose(this->libs[ind]);
    }
    delete[] this->params.cars;
}

void PlugingsManager::setParams(){
    size_t ind = 0;
    for (auto& it : this->cars) {
        std::cout << "SET PARAMS DEL " << ind << std::endl;
        this->cars_ids.push_back(it.first);
        this->params.cars[ind] = it.second.get_specs();
        ind++;
    }
    this->params.car_len = ind;
}

