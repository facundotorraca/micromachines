#include "Scene.h"
#include <common/Key.h>
#include <common/Sizes.h>

#define KEY_VALUE_POS 0

Scene::Scene(ProtectedQueue<std::vector<int32_t>>& queue):
        queue(queue),
        win(nullptr),
        rend(nullptr),
        camera(nullptr, WIDTH_SCREEN, HEIGHT_SCREEN)
{
    SDL_CreateWindowAndRenderer(WIDTH_SCREEN, HEIGHT_SCREEN, 0, &win, &rend);
    this->camera.setRenderer(rend);
    /*Para el fullscreen hay que manejar errores me parece*/
    //SDL_SetWindowFullscreen(this->win, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void Scene::handleKeyEvent(SDL_Keycode key, SDL_EventType type) {
    auto key_event = std::vector<int32_t>();

    switch (key) {
        case SDLK_DOWN:
            key_event.push_back(KEY_DOWN);
            break;
        case SDLK_LEFT:
            key_event.push_back(KEY_LEFT);
            break;
        case SDLK_RIGHT:
            key_event.push_back(KEY_RIGHT);
            break;
        case SDLK_UP:
            key_event.push_back(KEY_UP);
            break;
        default:
            key_event.push_back(UNKNOWN_KEY);
            break;
    }

    switch (type) {
        case (SDL_KEYDOWN):
            key_event.push_back(KEY_PRESSED);
            break;
        case (SDL_KEYUP):
            key_event.push_back(KEY_RELEASED);
            break;
        default:
            break;
    }

    if (key_event[KEY_VALUE_POS] != UNKNOWN_KEY)
        queue.push(key_event);
}

void Scene::handleServerEvent(std::unique_ptr<Command> command) {
    command->apply(camera);
}

void Scene::draw() {
    SDL_RenderClear(rend);
    this->camera.draw();
    SDL_RenderPresent(rend);
}

Scene::~Scene() {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
}
