#ifndef MICROMACHINES_MODIFIER_H
#define MICROMACHINES_MODIFIER_H

#include <mutex>
#include <cstdint>
#include <iostream>
#include "Box2D/Box2D.h"
#include <model/Sensor.h>
#include <common/Sizes.h>
#include <common/Coordinate.h>

class Modifier : public Sensor {

    protected:
        int32_t map_x;
        int32_t map_y;
        int32_t remaining_time;

        float side_size;

        b2Body* modifier_body;
        b2Fixture* modifier_fixture;

    public:
        explicit Modifier(int32_t time_of_life, int32_t map_x, int32_t map_y, float side_size);

        virtual void apply_modifier_effect(Body* body) = 0;

        void apply_effect(Body* body) override;

        virtual void set_modifier_user_data() = 0;

        virtual int32_t get_modifier_type() = 0;

        void add_to_world(b2World &world);

        void update_remaining_life();

        Coordinate get_coordinate();

        bool is_dead();

        ~Modifier() override;
};


#endif //MICROMACHINES_MODIFIER_H
