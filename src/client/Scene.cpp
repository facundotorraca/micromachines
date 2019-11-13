#include <client/Menu/NoMenu.h>
#include <client/Menu/LostConnectionMenu.h>
#include "Scene.h"

#define KEY_VALUE_POS 0

Scene::Scene(ProtectedQueue<std::unique_ptr<ServerCommand>>& queue, Bot &bot):
        queue(queue),
        scenario(bot),
        menu(new NoMenu)
{}

bool Scene::handleKeyEvent(SDL_Keycode key, SDL_EventType type) {
    bool response = true;
    auto new_state = menu->handleKey(key, type, queue, response);
    if (new_state){
        std::unique_lock<std::mutex> lock(mtx);
        this->menu.swap(new_state);
    }
    return response;
}

void Scene::draw() {
    std::unique_lock<std::mutex> lock(mtx);
    camera.clear();
    this->scenario.draw(camera);
    menu->draw(camera);
    camera.draw();
}

void Scene::receiveMessage(ProtocolSocket &socket) {
    auto new_state = menu->receiveMessage(socket, scenario, camera);
    if (new_state){
        std::unique_lock<std::mutex> lock(mtx);
        menu.swap(new_state);
    }
}

void Scene::togglePause() {
}

bool Scene::quit() {
}

void Scene::showConnectionLostMenu() {
    auto new_state = std::unique_ptr<Menu>(new LostConnectionMenu);
    std::unique_lock<std::mutex> lock(mtx);
    menu.swap(new_state);
}
