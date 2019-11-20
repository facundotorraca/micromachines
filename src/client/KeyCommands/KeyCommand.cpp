//
// Created by javier on 8/11/19.
//

#include "KeyCommand.h"
#include "MenuDependantCommand.h"
#include "RecordCommand.h"
#include "FullscreenCommand.h"

KeyCommand::KeyCommand(Scene &scene) : scene(scene) {}

std::unique_ptr<KeyCommand>
KeyCommand::create(Scene &scene, SDL_Keycode key, SDL_EventType type) {
    if (key == SDLK_F9 && type == SDL_KEYDOWN)
        return std::unique_ptr<KeyCommand> (new RecordCommand(scene));
    if (key == SDLK_F11 && type == SDL_KEYDOWN)
        return std::unique_ptr<KeyCommand> (new FullscreenCommand(scene));
    return std::unique_ptr<KeyCommand> (new MenuDependantCommand(scene, key, type));
}
