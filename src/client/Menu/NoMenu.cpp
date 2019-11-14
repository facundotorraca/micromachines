//
// Created by javier on 12/11/19.
//

#include <common/MsgTypes.h>
#include "PauseMenu.h"
#include "NoMenu.h"
#include "RestartMenu.h"

void NoMenu::draw(Camera& camera) {
}

std::unique_ptr<Menu> NoMenu::handleKey(SDL_Keycode key, SDL_EventType type,
        ProtectedQueue<std::unique_ptr<ServerCommand>>& queue, bool& response) {
    if (type == SDL_KEYDOWN){
        if (key == SDLK_ESCAPE){
            response = true;
            return std::unique_ptr<Menu>(new PauseMenu());
        }
    }
    auto command = ServerCommand::create(key, type);
    if (command)
        queue.push(std::move(command));
    response = true;
    return std::unique_ptr<Menu>(nullptr);
}

std::unique_ptr<Menu>
NoMenu::receiveMessage(ProtocolSocket &socket, Scenario &scenario,
                       Camera &camera) {
    std::vector<int32_t> command;
    socket.receive(command);
    int32_t msg_type = command[0];

    switch (msg_type) {
        case MSG_UPDATE_ENTITY: {
            int32_t entity_type = command[1];
            switch (entity_type) {
                case TYPE_CAR: {
                    CarInfo info{command[2], command[3],
                                 command[4], command[5], command[6],
                                 command[7], command[8], command[9],
                                 command[10], command[11], command[12],
                                 command[13], command[14], command[15],
                                 command[16], command[17], command[18]};
                    scenario.updateCar(info, camera); break;
                }
                default:
                    break;
            }
            break;
        }
        case MSG_CAR_ID:
            scenario.setOwnID(command[1]); break;
        case MSG_SEND_TILE: {
            TileInfo info{command[1], command[2], command[3], command[4]};
            scenario.addTile(info); break;
        }
        case MSG_SET_HEALTH:
            scenario.setCarHealth(command[1], command[2]); break;
        case MSG_SET_BACKGROUND:
            scenario.setBackground(command[1], command[2], command[3]); break;
        case MSG_SET_LAP:
            scenario.setLapNumber(command[1]); break;
        case MSG_TOTAL_LAPS:
            scenario.setTotalLaps(command[1]); break;
        case MSG_BEGIN_LOADING:
            break;
        case MSG_FINISH_LOADING:
            scenario.setLoadingScreen(false); break;
        case MSG_COUNTDOWN:
            scenario.showCountdownNumber(command[1]); break;
        case MSG_ADD_MODIFIER:
            scenario.addModifier(command[1], command[2], command[3]); break;
        case MSG_REMOVE_MODIFIER:
            scenario.removeModifier(command[1], command[2]); break;
        case MSG_PLAYER_FINISHED: {
            std::string player_name(MAX_LEN_NAME, '\0');
            socket.receive(player_name);
            scenario.addFinishedPlayer(player_name); break;
        }
        case MSG_EFFECT_BOOST:
        case MSG_EFFECT_MUD:
        case MSG_EFFECT_ROCK:
            scenario.showScreenEffect(command[0], command[1]); break;
        case MSG_SET_POSITION:
            scenario.setRacePosition(command[1]); break;
        case MSG_RESTART_RACE:
            return std::unique_ptr<Menu>(new RestartMenu);
        case MSG_RESET:
            scenario.reset(); break;
        default:
            break;
    }
    return std::unique_ptr<Menu>(nullptr);
}
