//
// Created by alejo on 7/11/19.
//

#include "PlugingsManager.h"
#include <dlfcn.h>



PlugingsManager::PlugingsManager(Race &race,
                                 std::string path) : race(race),
                                                     path(path),
                                                     libs() {}

void PlugingsManager::load_plugings() {
    DIR *pDIR;
    struct dirent *entry;
    void* (*fun_dl)(void);
    if (pDIR = opendir(this->path.c_str())) {
        while (entry = readdir(pDIR)) {
            if (std::string(".").compare(entry->d_name) !=0 && std::string("..").compare(entry->d_name) != 0) {
                std::string path = this->path + std::string(entry->d_name);
                void *dll = dlopen(path.c_str(), RTLD_NOW);
                *(void**) (&fun_dl) = dlsym(dll, PLUG_INIT);
                if (fun_dl != NULL) {
                    this->libs_attrs.push_back(fun_dl());
                    this->libs.push_back(dll);
                }
                std::cout << path << std::endl;
            }
        }
    }
    closedir(pDIR);
}

void PlugingsManager::execute() {
    void (*fun_dl)(void*, DTO_Info*);
    DTO_Info params;
    race.get_dto_data(params);
    for (size_t ind = 0; ind < this->libs.size(); ind++ ) {
        *(void**) (&fun_dl) = dlsym(this->libs.at(ind), PLUG_EXECUTE);
        if (fun_dl != NULL) {
            fun_dl(this->libs_attrs[ind], &params);
        }
    }
};

PlugingsManager::~PlugingsManager() {
    void (*fun_dl)(void*);
    for (size_t ind = 0; ind < this->libs.size(); ind++ ) {
        *(void**) (&fun_dl) = dlsym(this->libs[ind], PLUG_DESTROY);
        if (fun_dl != NULL) {
           fun_dl(this->libs_attrs[ind]);
        }
        dlclose(this->libs[ind]);
    }
}

