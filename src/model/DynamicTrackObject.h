#ifndef MICROMACHINES_DYNAMICTRACKOBJECT_H
#define MICROMACHINES_DYNAMICTRACKOBJECT_H

#include "Body.h"
#include <server/UpdateClient.h>
#include <Box2D/Dynamics/b2Fixture.h>

class DynamicTrackObject : public Body {
    protected:
        int32_t ID;
        int32_t map_x;
        int32_t map_y;

        int32_t original_x;
        int32_t original_y;

        b2Body* object_body;
        b2Fixture* object_fixture;

    public:
        DynamicTrackObject(int32_t ID, int32_t x, int32_t y);

        DynamicTrackObject(DynamicTrackObject&& other) noexcept;

        void restart_position();

        void add_to_world(b2World& world);

        void collide(Body* body) override;

        void send_updates(ClientUpdater& updater);

        int32_t get_ID() override;
};


#endif //MICROMACHINES_DYNAMICTRACKOBJECT_H
