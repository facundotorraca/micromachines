//
// Created by javier on 26/10/19.
//

#include <iostream>
#include "ServerCommand.h"
#include "SubClasses.h"

std::unique_ptr<ServerCommand> ServerCommand::create(int key, int type) {
    if (type == KEY_PRESSED){
        switch (key) {
            case KEY_LEFT:
                return std::unique_ptr<ServerCommand>(new StartLeftTurn());
            case KEY_RIGHT:
                return std::unique_ptr<ServerCommand>(new StartRightTurn());
            case KEY_UP:
                return std::unique_ptr<ServerCommand>(new StartAccelerate());
            case KEY_DOWN:
                return std::unique_ptr<ServerCommand>(new StartBrake());
        }
    } else if (type == KEY_RELEASED) {
        switch (key) {
            case KEY_LEFT:
                return std::unique_ptr<ServerCommand>(new EndLeftTurn());
            case KEY_RIGHT:
                return std::unique_ptr<ServerCommand>(new EndRightTurn());
            case KEY_UP:
                return std::unique_ptr<ServerCommand>(new EndAccelerate());
            case KEY_DOWN:
                return std::unique_ptr<ServerCommand>(new EndBrake());
        }
    }
    return std::unique_ptr<ServerCommand>(nullptr);
}

std::unique_ptr<ServerCommand>
ServerCommand::create(SDL_Keycode key, SDL_EventType type) {
    int _key = 0;
    int _type = 0;
    if (type == SDL_KEYDOWN)
        _type = KEY_PRESSED;
    if (type == SDL_KEYUP)
        _type = KEY_RELEASED;
    switch (key){
        case SDLK_DOWN:
            _key = KEY_DOWN; break;
        case SDLK_UP:
            _key = KEY_UP; break;
        case SDLK_RIGHT:
            _key = KEY_RIGHT; break;
        case SDLK_LEFT:
            _key = KEY_LEFT; break;
        default:
            break;
    }
    return ServerCommand::create(_key, _type);
}

void ServerCommand::send(ProtocolSocket &socket) {
    std::vector<int32_t> data{key, type};
    socket.send(data);
}
