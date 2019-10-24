//
// Created by aacevedo on 24/10/19.
//

#ifndef MICROMACHINES_THREADBOT_H
#define MICROMACHINES_THREADBOT_H

#include <common/Thread.h>
#include "Bot.h"

#define FRAMES_PER_SECOND 30

class ThreadBot : public Thread {
    Bot &bot;
  public:
    ThreadBot(Bot &bot);
    void run();
};


#endif //MICROMACHINES_THREADBOT_H
