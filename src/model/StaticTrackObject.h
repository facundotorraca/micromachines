#ifndef MICROMACHINES_STATICTRACKOBJECT_H
#define MICROMACHINES_STATICTRACKOBJECT_H

#include <server/UpdateClient.h>
#include <Box2D/Dynamics/b2Fixture.h>

class StaticTrackObject {
    protected:
        int32_t map_x;
        int32_t map_y;
        int32_t rotation;

        int32_t ID{};

        b2Body* object_body;
        b2Fixture* object_fixture;

    public:
        StaticTrackObject(int32_t x, int32_t y, int32_t rotation, int32_t ID);

        StaticTrackObject(StaticTrackObject&& other) noexcept;

        void add_to_world(b2World& world);

        UpdateClient get_to_send();
};

#endif //MICROMACHINES_STATICTRACKOBJECT_H
