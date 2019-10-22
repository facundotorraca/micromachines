//
// Created by javier on 22/10/19.
//

#include "CarID.h"
#include "Command.h"
#include "TrackID.h"
#include "UpdateCar.h"
#include <common/EntityType.h>


std::unique_ptr<Command> Command::create(std::vector<int32_t>& command){
    int32_t msg_type = command[0];

    switch (msg_type) {
        case MSG_UPDATE_ENTITY: {
            int32_t entity_type = command[2];
            switch (entity_type) {
                case TYPE_CAR:
                    return std::unique_ptr<Command>(new UpdateCar(command[1],
                                                                     command[3],command[4], command[5],
                                                                     command[6],command[7],command[8],
                                                                     command[9],command[10],command[11],
                                                                     command[12],command[13],command[14],
                                                                     command[15],command[16],command[17]));
                default:
                    break;
            }
            break;
        }
        case MSG_TRACK_ID:
            return std::unique_ptr<Command>(new TrackID(command[1]));
        case MSG_CAR_ID:
            return std::unique_ptr<Command>(new CarID(command[1]));
        default:
            break; //aca hacer un unknown commnad
    }
}
