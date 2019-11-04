#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include <vector>
#include "Wheel.h"
#include "CarLife.h"
#include "CarSpecs.h"
#include "common/Key.h"
#include "Box2D/Box2D.h"
#include <model/Vehicle/LapState.h>
#include <common/Coordinate.h>
#include "CarState.h"
#include <server/UpdateClient.h>

#define DEGTORAD 0.0174532925199432957f

class Car : public Body {
    CarLife life;
    CarSpecs specs;

    b2Body* car_body{};
    b2Fixture* car_fixture{};
    std::vector<Wheel*> wheels;

    b2RevoluteJoint* front_left_joint{};
    b2RevoluteJoint* front_right_joint{};

    int32_t key_v;
    int32_t key_h;

    bool lap_altered;
    std::unique_ptr<LapState> lap_state;
    std::unique_ptr<CarState> car_state;

    private:
        void create_wheels(b2World& world);

        static float get_desire_angle(int32_t key);

    public:
        explicit Car(CarSpecs specs);

        Car(Car&& other_car) noexcept;

        void add_to_world(b2World& world);

        void set_spawn_point(Coordinate spawn_point);

        void collide(Body* static_object) override;

        UpdateClient get_update(int32_t id);

        void release_key(int32_t key);

        void press_key(int32_t key);

        int32_t get_ID() override;

        void move_to(Coordinate coordinate);

        void update();

        void turn_on();

        ~Car();

        /*-------------Race_handlers---------*/
        void modify_laps(LapCounter& lap_counter, int32_t car_ID);

        void restart_lap();

        void complete_lap();
};

#endif //MICROMACHINES_CAR_H
