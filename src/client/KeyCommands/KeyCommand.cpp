//
// Created by javier on 8/11/19.
//

#include "KeyCommand.h"
#include "PauseCommand.h"
#include "QuitCommand.h"
#include "DriveCommand.h"

KeyCommand::KeyCommand(Scene &scene) : scene(scene) {}

std::unique_ptr<KeyCommand>
KeyCommand::create(Scene &scene, SDL_Keycode key, SDL_EventType type) {
    if (key == SDLK_ESCAPE && type == SDL_KEYDOWN)
        return std::unique_ptr<KeyCommand> (new PauseCommand(scene));
    if (key == SDLK_q && type == SDL_KEYDOWN)
        return std::unique_ptr<KeyCommand> (new QuitCommand(scene));
    return std::unique_ptr<KeyCommand> (new DriveCommand(scene, key, type));
}
