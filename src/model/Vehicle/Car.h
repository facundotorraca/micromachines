#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include <vector>
#include "Wheel.h"
#include "CarSpecs.h"
#include "common/Key.h"
#include "Box2D/Box2D.h"
#include "model/RacingTrack.h"
#include "CarLife.h"
#include <server/UpdateClient.h>
#include <common/Coordinate.h>

class Car : public Body {
    CarLife life;
    CarSpecs specs;

    b2Body* car_body;
    b2Fixture* car_fixture;
    std::vector<Wheel*> wheels;

    b2RevoluteJoint* front_left_joint{};
    b2RevoluteJoint* front_right_joint{};

    int32_t key_v;
    int32_t key_h;

    bool lap_complete;
    bool lap_restarted;

    private:
        void create_wheels(RacingTrack& racing_track);

        static float get_desire_angle(int32_t key);

    public:
        Car(RacingTrack& racing_track, CarSpecs specs);

        Car(Car&& other_car) noexcept;

        void set_spawn_point(Coordinate spawn_point);

        void collide(Body* stactic_object) override;

        UpdateClient get_update(int32_t id);

        void release_key(int32_t key);

        void press_key(int32_t key);

        int32_t get_ID() override;

        void update();

        ~Car();

        /*-------------Race_handlers---------*/
        bool lap_was_completed();

        bool lap_was_restarted();

        void restart_lap();

        void complete_lap();
};

#endif //MICROMACHINES_CAR_H
