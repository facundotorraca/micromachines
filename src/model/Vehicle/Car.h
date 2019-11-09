#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include <vector>
#include "Wheel.h"
#include "CarLife.h"
#include "CarSpecs.h"
#include "CarState.h"
#include "common/Key.h"
#include "Box2D/Box2D.h"
#include <model/DTO_Info.h>
#include <common/Coordinate.h>
#include <server/UpdateClient.h>
#include <server/ClientUpdater.h>
#include <model/Vehicle/LapState.h>
#include <model/Modifiers/Effect.h>

#define DEGTORAD 0.0174532925199432957f

class Car : public Body {
    CarLife life;
    CarSpecs specs;

    b2Body* car_body{};
    std::vector<Wheel*> wheels;

    b2RevoluteJoint* front_left_joint{};
    b2RevoluteJoint* front_right_joint{};

    int32_t throttle;
    int32_t steering_wheel;

    bool lap_altered;

    std::unique_ptr<LapState> lap_state;
    std::unique_ptr<CarState> car_state;

    private:
        void create_wheels(b2World& world);

        static float get_desire_angle(int32_t key);

    public:
        explicit Car(CarSpecs specs);

        void add_to_world(b2World& world);

        void set_spawn_point(Coordinate spawn_point);

        void collide(Body* static_object) override;

        void send_general_update(int32_t ID, ClientUpdater& client_updater);

        void stop(int32_t movement);

        void move(int32_t movement);

        int32_t get_ID() override;

        int32_t get_max_life();

        void set_max_life(int32_t);

        void move_to(Coordinate coordinate);

        void get_dto_info(int32_t ID, DTO_Car& car_info);

        void update();

        void turn_on();

        CarSpecs get_specs();

        ~Car();

        /*-------------Race_handlers---------*/
        void modify_laps(LapCounter& lap_counter, int32_t car_ID);

        void make_damage(int32_t damage);

        void apply_oil_effect();

        void apply_mud_effect();

        void apply_rock_effect();

        void apply_boost_effect();

        void repair();

        void restart_lap();

        void complete_lap();
};

#endif //MICROMACHINES_CAR_H
