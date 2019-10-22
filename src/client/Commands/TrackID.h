//
// Created by javier on 22/10/19.
//

#ifndef MICROMACHINES_TRACKID_H
#define MICROMACHINES_TRACKID_H

#include "Command.h"

class TrackID : public Command {
    int32_t id;
public:
    explicit TrackID(int32_t id) : id(id){}

    void apply(Camera& camera) override {
        camera.setTrack(id);
    }
};

#endif //MICROMACHINES_TRACKID_H
