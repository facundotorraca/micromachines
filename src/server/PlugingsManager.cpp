//
// Created by alejo on 7/11/19.
//

#include "PlugingsManager.h"
#include <dlfcn.h>

#define MAX_LIFE 20 //1/3 sec

PlugingsManager::PlugingsManager(Race &race,
                                 std::string path) : race(race),
                                                     path(path),
                                                     libs()
{
    this->life = MAX_LIFE;
}

void PlugingsManager::load_plugings() {
    struct dirent *entry;
    void* (*fun_dl)();
    DIR *pDIR = opendir(this->path.c_str());
    if (pDIR) {
        entry = readdir(pDIR);
        while (entry) {
            if (std::string(".") != std::string(entry->d_name) &&
                std::string("..") != std::string(entry->d_name)) {
                std::string lib_path = this->path + std::string(entry->d_name);
                void *dll = dlopen(lib_path.c_str(), RTLD_NOW);
                *(void**) (&fun_dl) = dlsym(dll, PLUG_INIT);
                if (fun_dl != nullptr) {
                    this->libs_attrs.push_back(fun_dl());
                    this->libs.push_back(dll);
                }
                std::cout << path << std::endl;
            }
            entry = readdir(pDIR);
        }
    }
    closedir(pDIR);
}

void PlugingsManager::execute() {
    this->life -= 1;
    if (this->life > 0)
        return;
    this->life = MAX_LIFE;
    void (*fun_dl)(void*, DTO_Info*);
    DTO_Info params;
    race.get_dto_data(params);
    for (size_t ind = 0; ind < this->libs.size(); ind++ ) {
        *(void**) (&fun_dl) = dlsym(this->libs.at(ind), PLUG_EXECUTE);
        if (fun_dl != nullptr) {
            fun_dl(this->libs_attrs[ind], &params);
        }
    }
    this->race.apply_plugin(params);
};

PlugingsManager::~PlugingsManager() {
    void (*fun_dl)(void*);
    for (size_t ind = 0; ind < this->libs.size(); ind++ ) {
        *(void**) (&fun_dl) = dlsym(this->libs[ind], PLUG_DESTROY);
        if (fun_dl != nullptr) {
           fun_dl(this->libs_attrs[ind]);
        }
        dlclose(this->libs[ind]);
    }
}

