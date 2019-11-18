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
        std::unique_lock<std::mutex> lock(camera_mtx);
        this->menu.swap(new_state);
    }
    return response;
}



void Scene::draw() {
    std::unique_lock<std::mutex> lock(camera_mtx);
    camera.clear();
    drawScenario();
    if (camera.isRecording()){
        camera.drawRecordingTexture();
        camera.setRecordingTarget();
        drawScenario();
        camera.sendToRecorder();
        camera.setDefaultTarget();
    }
    lock.unlock();
    std::unique_lock<std::mutex> menu_lock(menu_mtx);
    menu->draw(camera);
    lock.lock();
    camera.draw();
}

void Scene::receiveMessage(ProtocolSocket &socket) {
    auto command = Command::create(scenario, socket, camera);
    if (command){
        auto new_state = std::unique_ptr<Menu>();
        new_state = applyCommand(*command);
        if (new_state){
            std::lock_guard<std::mutex> lock(menu_mtx);
            menu.swap(new_state);
        }
    }
}

void Scene::showConnectionLostMenu() {
    auto new_state = std::unique_ptr<Menu>(new LostConnectionMenu);
    std::lock_guard<std::mutex> lock(menu_mtx);
    menu.swap(new_state);
}

void Scene::toggleRecording() {
    std::cerr << "stopping: getting lock" << std::endl;
    std::lock_guard<std::mutex> lock(camera_mtx);
    std::cerr << "stopping: got lock" << std::endl;
    if (camera.isRecording())
        camera.stopRecording();
    else
        camera.startRecording();
}

void Scene::drawScenario() {
    std::lock_guard<std::mutex> scenario_lock(scenario_mtx);
    this->scenario.draw(camera);
}

std::unique_ptr<Menu> Scene::applyCommand(Command &command) {
    std::lock_guard<std::mutex> scenario_lock(scenario_mtx);
    return command.apply();
}
