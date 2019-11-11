#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include <vector>
#include "Wheel.h"
#include "CarLife.h"
#include "CarSpecs.h"
#include "EngineState.h"
#include "common/Key.h"
#include "Box2D/Box2D.h"
#include "CarState.h"
#include <model/DTO_Info.h>
#include <common/Coordinate.h>
#include <server/UpdateClient.h>
#include <server/ClientUpdater.h>
#include <model/Vehicle/LapState.h>
#include <model/Modifiers/Effect.h>

class Car : public Body {
    CarLife life;
    CarSpecs specs;

    b2Body* car_body{};
    std::vector<Wheel*> wheels;

    b2RevoluteJoint* front_left_joint{};
    b2RevoluteJoint* front_right_joint{};

    Coordinate last_track_tile;

    int32_t throttle;
    int32_t steering_wheel;

    int32_t begin_distance;

    bool lap_altered;

    std::unique_ptr<CarState> car_state;
    std::unique_ptr<LapState> lap_state;
    std::unique_ptr<EngineState> engine_state;

    private:
        void create_wheels(b2World& world);

        static float get_desire_angle(int32_t steering_wheel_movement);

    public:
        explicit Car(CarSpecs specs);

        void add_to_world(b2World& world);

        void set_start_position(Coordinate start_position);

        void collide(Body* body) override;

        void send_updates(int32_t ID, ClientUpdater& client_updater);

        void stop(int32_t movement);

        void move(int32_t movement);

        int32_t get_ID() override;

        void move_to(Coordinate coordinate);

        void get_dto_info(int32_t ID, DTO_Car& car_info);

        void apply_plugin(DTO_Car& car_info);

        void update();

        void turn_on();

        ~Car();

        /*-------------Race_handlers---------*/
        void modify_laps(LapCounter& lap_counter, int32_t car_ID);

        void set_begin_distance(int32_t begin_distance);

        void set_respawn(Coordinate respawn);

        int32_t get_begin_distance();

        void make_damage(int32_t damage);

        void apply_oil_effect();

        void apply_mud_effect();

        void apply_rock_effect();

        void apply_boost_effect();

        void restart_lap();

        void complete_lap();

    void repair();
};

#endif //MICROMACHINES_CAR_H
