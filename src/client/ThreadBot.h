
#ifndef MICROMACHINES_THREADBOT_H
#define MICROMACHINES_THREADBOT_H

#include "Bot.h"
#include <common/Thread.h>

class ThreadBot : public Thread {
    Bot &bot;
  public:
    ThreadBot(Bot &bot);
    void run();
};


#endif //MICROMACHINES_THREADBOT_H
