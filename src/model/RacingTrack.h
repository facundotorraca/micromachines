#ifndef MICROMACHINES_RACINGTRACK_H
#define MICROMACHINES_RACINGTRACK_H

#include <list>
#include <memory>
#include "Box2D/Box2D.h"
#include "ContactListener.h"
#include <model/FinishLine.h>
#include "StaticTrackObject.h"
#include <common/ProtocolSocket.h>
#include <common/ProtectedQueue.h>
#include "model/Terrains/Terrain.h"

class RacingTrack {
    b2World racing_track;

    float32 time_step;
    int32 velocity_iterations;
    int32 position_iterations;

    int32_t height;
    int32_t width;
    int32_t track_terrain;

    FinishLine* finish_line;
    std::list<std::unique_ptr<Terrain>> terrains;
    std::list<StaticTrackObject> static_track_objects;

    ContactListener contact_listener;

    public:
        explicit RacingTrack();

        void update();

        b2World& get_world();

        b2Body* add_body(b2BodyDef& body);

        void set_track_terrain(int32_t terrain);

        void add_terrain(std::unique_ptr<Terrain>&& terrain);

        void send(ProtectedQueue<UpdateClient>& player_queue);

        void set_finish_line(Coordinate begin, Coordinate end);

        void set_track_size(int32_t height, int32_t track_width);

        void add_static_track_object(StaticTrackObject&& object);

        ~RacingTrack();
};


#endif //MICROMACHINES_RACINGTRACK_H
