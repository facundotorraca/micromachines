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

void Scene::handleServerEvent(std::vector<int32_t>& data) {
    auto command = Command::create(data, scenario, bot);
    if (command)
        command->apply();
}

void Scene::draw() {
    this->scenario.draw();
}
