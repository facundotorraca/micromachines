//
// Created by javier on 22/10/19.
//

#include "CarID.h"
#include "Command.h"
#include "UpdateCar.h"
#include "AddTile.h"
#include "SetCarHealth.h"
#include "SetBackground.h"
#include "SetLap.h"
#include "SetTotalLaps.h"
#include "BeginLoadingScreen.h"
#include "FinishLoadingScreen.h"
#include "CountdownCommand.h"
#include "AddModifier.h"
#include "RemoveModifier.h"
#include "PlayerFinished.h"
#include "ScreenEffect.h"
#include "SetRacePosition.h"
#include "ShowRestartMenu.h"
#include "ResetRace.h"
#include <common/EntityType.h>
#include <client/Entities/CarInfo.h>


std::unique_ptr<Command> Command::create(Scenario& scenario, ProtocolSocket& socket, Camera& camera){
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
                    return std::unique_ptr<Command>(new UpdateCar(info, scenario, camera));
                }
                default:
                    break;
            }
            break;
        }
        case MSG_CAR_ID:
            return std::unique_ptr<Command>(new CarID(command[1], scenario));
        case MSG_SEND_TILE: {
            TileInfo info{command[1], command[2], command[3], command[4]};
            return std::unique_ptr<Command>(new AddTile(info, scenario));
        }
        case MSG_SET_HEALTH:
            return std::unique_ptr<Command>(new SetCarHealth(scenario, command[1], command[2]));
        case MSG_SET_BACKGROUND:
            return std::unique_ptr<Command>(new SetBackground(scenario, command[1], command[2], command[3]));
        case MSG_SET_LAP:
            return std::unique_ptr<Command>(new SetLap(scenario, command[1]));
        case MSG_TOTAL_LAPS:
            return std::unique_ptr<Command>(new SetTotalLaps(scenario, command[1]));
        case MSG_BEGIN_LOADING:
            return std::unique_ptr<Command>(new BeginLoadingScreen(scenario));
        case MSG_FINISH_LOADING:
            return std::unique_ptr<Command>(new FinishLoadingScreen(scenario));
        case MSG_COUNTDOWN:
            return std::unique_ptr<Command>(new CountdownCommand(scenario, command[1]));
        case MSG_ADD_MODIFIER:
            return std::unique_ptr<Command>(new AddModifier(scenario, command[1], command[2], command[3]));
        case MSG_REMOVE_MODIFIER:
            return std::unique_ptr<Command>(new RemoveModifier(scenario, command[1], command[2]));
        case MSG_PLAYER_FINISHED: {
                std::string player_name(MAX_LEN_NAME, '\0');
                socket.receive(player_name);
                return std::unique_ptr<Command>(new PlayerFinished(scenario, player_name));
            }
        case MSG_EFFECT_BOOST:
        case MSG_EFFECT_MUD:
        case MSG_EFFECT_ROCK:
            return std::unique_ptr<Command> (new ScreenEffect(scenario, command[0], command[1]));
        case MSG_SET_POSITION:
            return std::unique_ptr<Command> (new SetRacePosition(scenario, command[1]));
        case MSG_RESTART_RACE:
            return std::unique_ptr<Command>(new ShowRestartMenu(scenario));
        case MSG_RESET:
            return std::unique_ptr<Command>(new ResetRace(scenario));
        default:
            return std::unique_ptr<Command>(nullptr); //aca hacer un unknown commnad
    }
}
