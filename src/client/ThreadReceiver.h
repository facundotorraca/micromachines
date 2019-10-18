//
// Created by javier on 16/10/19.
//

#ifndef MICROMACHINES_THREADRECEIVER_H
#define MICROMACHINES_THREADRECEIVER_H

#include "Scene.h"
#include "common/Thread.h"
#include "common/ProtocolSocket.h"

class ThreadReceiver : public Thread {
    Scene* scene;
    ProtocolSocket* socket;
public:
    ThreadReceiver(ProtocolSocket& socket, Scene& scene);
    void run() override;
};


#endif //MICROMACHINES_THREADRECEIVER_H
