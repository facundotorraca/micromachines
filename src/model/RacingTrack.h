#ifndef MICROMACHINES_RACINGTRACK_H
#define MICROMACHINES_RACINGTRACK_H

#include <list>
#include <memory>
#include "Grass.h"
#include "Box2D/Box2D.h"
#include <common/ProtocolSocket.h>

class RacingTrack {
    b2World racing_track;

    float32 time_step;
    int32 velocity_iterations;
    int32 position_iterations;

    std::list<std::unique_ptr<Terrain>> terrains;

    public:
        explicit RacingTrack();

        void send(ProtocolSocket& p_socket);

        b2Body* add_body(b2BodyDef& body);

        b2World& get_world();

        void add_map_part(std::unique_ptr<Terrain>&& terrain);

        void update();
};


#endif //MICROMACHINES_RACINGTRACK_H
