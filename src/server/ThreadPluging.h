//
// Created by alejoacevedo on 11/10/19.
//

#ifndef MICROMACHINES_THREADPLUGING_H
#define MICROMACHINES_THREADPLUGING_H

#include <common/Thread.h>
#include "PlugingsManager.h"

class ThreadPluging : public Thread {
    PlugingsManager &plugingsManager;

public:
    explicit ThreadPluging(PlugingsManager &plugingsManager);

private:
    void run();

};


#endif //MICROMACHINES_THREADPLUGING_H
