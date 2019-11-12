#include "Scene.h"

#define KEY_VALUE_POS 0

Scene::Scene(ProtectedQueue<std::unique_ptr<ServerCommand>>& queue, Bot &bot):
        queue(queue),
        bot(bot)
{}

bool Scene::handleKeyEvent(SDL_Keycode key, SDL_EventType type) {
    return scenario.handleKey(key, type, queue);
}

void Scene::draw() {
    this->scenario.draw();
}

std::unique_ptr<Command> Scene::receiveMessage(ProtocolSocket &socket) {
    return Command::create(scenario, bot, socket);
}

void Scene::togglePause() {
}

bool Scene::quit() {
}

void Scene::showConnectionLostMenu() {
    scenario.addConnectionLostMessage();
}
