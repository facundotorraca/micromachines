#ifndef MICROMACHINES_STATICTRACKOBJECT_H
#define MICROMACHINES_STATICTRACKOBJECT_H

#include "Body.h"
#include <server/UpdateClient.h>
#include <Box2D/Dynamics/b2Fixture.h>

class StaticTrackObject : public Body {
    protected:
        int32_t ID;
        int32_t map_x;
        int32_t map_y;

        b2Body* object_body;
        b2Fixture* object_fixture;

    public:
        StaticTrackObject(int32_t ID, int32_t x, int32_t y);

        StaticTrackObject(StaticTrackObject&& other) noexcept;

        void add_to_world(b2World& world);

        void collide(Body* body) override;

        int32_t get_ID() override ;
};

#endif //MICROMACHINES_STATICTRACKOBJECT_H
