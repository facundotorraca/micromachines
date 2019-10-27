//
// Created by javier on 22/10/19.
//

#ifndef MICROMACHINES_TRACKID_H
#define MICROMACHINES_TRACKID_H

#include "Command.h"

class TrackID : public Command {
    int32_t id;

    public:
        explicit TrackID(int32_t id, Map& map, Bot& bot) : Command(map, bot), id(id){}

        void apply() override {
            map.setTrack(id);
        }
};

#endif //MICROMACHINES_TRACKID_H
