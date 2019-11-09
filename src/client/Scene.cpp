#include "Scene.h"

#define KEY_VALUE_POS 0

Scene::Scene(ProtectedQueue<std::unique_ptr<ServerCommand>>& queue, Bot &bot):
        queue(queue),
        bot(bot)
{}

void Scene::handleKeyEvent(SDL_Keycode key, SDL_EventType type) {
    auto event = ServerCommand::create(key, type);
    if (event)
        queue.push(std::move(event));
}

void Scene::draw() {
    this->scenario.draw();
}

std::unique_ptr<Command> Scene::receiveMessage(ProtocolSocket &socket) {
    return Command::create(scenario, bot, socket);
}

void Scene::togglePause() {
    scenario.togglePause();
}

bool Scene::quit() {
    return scenario.quit();
}
