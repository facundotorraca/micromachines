#ifndef MICROMACHINES_TERRAIN_H
#define MICROMACHINES_TERRAIN_H

#include <cstdint>
#include "Box2D/Box2D.h"
#include <server/UpdateClient.h>
#include <model/Vehicle/Wheel.h>

class Terrain {

    protected:
        int32_t map_x;
        int32_t map_y;
        int32_t rotation;

        int32_t ID;

        bool is_static;

        b2Body* terrain_body;
        b2Fixture* terrain_fixture;
        FixtureUserData* fixture_user_data;

    public:
        Terrain(int32_t x, int32_t y, int32_t rotation, int32_t ID, bool is_static);

        Terrain(Terrain&& other) noexcept;

        void transform_to_static();

        void add_to_world(b2World& world);

        virtual UpdateClient get_to_send() = 0;

        virtual void set_terrain_user_data() = 0;

        virtual void apply_effect(Wheel* wheel) = 0;

        ~Terrain();
};


#endif //MICROMACHINES_TERRAIN_H
