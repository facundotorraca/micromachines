#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include <vector>
#include "Wheel.h"
#include "CarSpecs.h"
#include "common/Key.h"
#include "Box2D/Box2D.h"
#include "RacingTrack.h"

class Car {
    CarSpecs specs;
    b2Body* car_body;
    std::vector<Wheel*> wheels;
    b2RevoluteJoint* front_left_joint{};
    b2RevoluteJoint* front_right_joint{};
    uint8_t key_v;
    uint8_t key_h;

    private:
        void create_wheels(RacingTrack& racing_track);

        float get_desire_angle(uint8_t key);

    public:
        Car(RacingTrack& racing_track, CarSpecs specs);

        Car(Car&& other_car) noexcept;

        void update();

        std::vector<b2Vec2> get_wheels_position();

        std::vector<float> get_wheels_angle();

        float get_position_x();

        float get_position_y();

        float get_angle();

        void press_key(uint8_t key);
        void release_key(uint8_t key);

        ~Car();
};

#endif //MICROMACHINES_CAR_H
