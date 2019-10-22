//
// Created by javier on 22/10/19.
//

#include <vector>
#include "Command.h"
#include "UpdateCar.h"
#include "TrackID.h"
#include "CarID.h"


std::unique_ptr<Command> Command::create(std::vector<int32_t>& command){
    int32_t msg_type = command[0];

    switch (msg_type) {
        case MSG_UPDATE_ENTITY:
            return std::unique_ptr<Command>(new UpdateCar());
        case MSG_TRACK_ID:
            return std::unique_ptr<Command>(new TrackID());
        case MSG_CAR_ID:
            return std::unique_ptr<Command>(new CarID());
        default:
            break;
    }
}
