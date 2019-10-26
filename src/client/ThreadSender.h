//
// Created by javier on 16/10/19.
//

#ifndef MICROMACHINES_THREADSENDER_H
#define MICROMACHINES_THREADSENDER_H


#include <common/Thread.h>
#include <common/ProtocolSocket.h>
#include "Scene.h"

class ThreadSender : public Thread{
        ProtocolSocket& socket;
        ProtectedQueue<std::unique_ptr<ServerCommand>>& queue;
    public:
        explicit ThreadSender(ProtocolSocket& socket, ProtectedQueue<std::unique_ptr<ServerCommand>>& queue);
        void run() override;
};


#endif //MICROMACHINES_THREADSENDER_H
