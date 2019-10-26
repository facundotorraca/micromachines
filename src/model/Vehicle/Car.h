#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include <vector>
#include "Wheel.h"
#include "CarSpecs.h"
#include "common/Key.h"
#include "Box2D/Box2D.h"
#include "model/RacingTrack.h"
#include <server/UpdateClient.h>

class Car {
    CarSpecs specs;
    b2Body* car_body;
    std::vector<Wheel*> wheels;
    b2RevoluteJoint* front_left_joint{};
    b2RevoluteJoint* front_right_joint{};
    int32_t key_v;
    int32_t key_h;

    private:
        void create_wheels(RacingTrack& racing_track);

        static float get_desire_angle(int32_t key);

    public:
        Car(RacingTrack& racing_track, CarSpecs specs);

        Car(Car&& other_car) noexcept;

        UpdateClient get_update(int32_t id);

        void release_key(int32_t key);

        void press_key(int32_t key);

        void update();

        ~Car();
};

#endif //MICROMACHINES_CAR_H
