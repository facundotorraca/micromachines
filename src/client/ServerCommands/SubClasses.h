//
// Created by javier on 26/10/19.
//

#ifndef MICROMACHINES_SUBCLASSES_H
#define MICROMACHINES_SUBCLASSES_H

#include <common/Key.h>
#include "ServerCommand.h"

class StartLeftTurn : public ServerCommand {
public:
    StartLeftTurn() : ServerCommand() {
        type = KEY_PRESSED;
        key = KEY_LEFT;
    }
};

class StartRightTurn : public ServerCommand {
public:
    StartRightTurn() : ServerCommand() {
        type = KEY_PRESSED;
        key = KEY_RIGHT;
    }
};

class StartAccelerate : public ServerCommand {
public:
    StartAccelerate(): ServerCommand() {
        type = KEY_PRESSED;
        key = KEY_UP;
    }
};

class StartBrake : public ServerCommand {
public:
    StartBrake(): ServerCommand() {
        type = KEY_PRESSED;
        key = KEY_DOWN;
    }
};

class EndLeftTurn : public ServerCommand {
public:
    EndLeftTurn(): ServerCommand() {
        type = KEY_RELEASED;
        key = KEY_LEFT;
    }
};

class EndRightTurn : public ServerCommand {
public:
    EndRightTurn(): ServerCommand() {
        type = KEY_RELEASED;
        key = KEY_RIGHT;
    }
};

class EndAccelerate : public ServerCommand {
public:
    EndAccelerate(): ServerCommand() {
        type = KEY_RELEASED;
        key = KEY_UP;
    }
};

class EndBrake : public ServerCommand {
public:
    EndBrake(): ServerCommand() {
        type = KEY_RELEASED;
        key = KEY_DOWN;
    }
};

#endif //MICROMACHINES_SUBCLASSES_H
