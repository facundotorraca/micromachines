#include <client/Menu/NoMenu.h>
#include <client/Menu/LostConnectionMenu.h>
#include "Commands/Command.h"
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
    {
        std::unique_lock<std::mutex> scenario_lock(scenario_mtx);
        this->scenario.draw(camera);
    }
    if (camera.isRecording()){
        camera.drawRecordingTexture();
        camera.setRecordingTarget();
        {
            std::unique_lock<std::mutex> scenario_lock(scenario_mtx);
            this->scenario.draw(camera);
        }
        camera.sendToRecorder();
        camera.setDefaultTarget();
    }
    menu->draw(camera);
    camera.draw();
}

void Scene::receiveMessage(ProtocolSocket &socket) {
    auto command = Command::create(scenario, socket, camera);
    if (command){
        auto new_state = std::unique_ptr<Menu>();
        {
            std::unique_lock<std::mutex> scenario_lock(scenario_mtx);
            new_state = command->apply();
        }
        if (new_state){
            std::unique_lock<std::mutex> lock(mtx);
            menu.swap(new_state);
        }
    }
}

void Scene::showConnectionLostMenu() {
    auto new_state = std::unique_ptr<Menu>(new LostConnectionMenu);
    std::unique_lock<std::mutex> lock(mtx);
    menu.swap(new_state);
}

void Scene::toggleRecording() {
    std::unique_lock<std::mutex> lock(mtx);
    if (camera.isRecording())
        camera.stopRecording();
    else
        camera.startRecording();
}
