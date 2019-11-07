#include "Car.h"
#include "Wheel.h"
#include <iostream>
#include "CarSpecs.h"
#include "common/Key.h"
#include "CarStopped.h"
#include "CarRunning.h"
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include <common/EntityType.h>

#define NOT_PRESSED 0

#define MAX_ROTATION_ANGLE 45.0f
#define ROTATION_PER_SECOND 90.0

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

Car::Car(CarSpecs specs):
        specs(specs),
        lap_altered(false),
        key_h(NOT_PRESSED),
        key_v(NOT_PRESSED),
        life(specs.max_life),
        lap_state(new LapRunning()),
        car_state(new CarStopped())
{}

void Car::add_to_world(b2World &world) {
    /*create car body*/
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    this->car_body = world.CreateBody(&bodyDef);

    /*reduce the world velocity of bodies*/
    this->car_body->SetAngularDamping(0.1);

    b2PolygonShape polygon_shape;
    polygon_shape.SetAsBox(CAR_WIDTH/2 + 0.05, CAR_HEIGHT/2 + 0.05);
    this->car_fixture = this->car_body->CreateFixture(/*shape*/&polygon_shape, 0.2f);

    this->car_body->SetUserData(this);
    this->create_wheels(world);
}

void Car::create_wheels(b2World& world) {
    //common joint parameters
    b2RevoluteJointDef joint_params;
    joint_params.bodyA = this->car_body; /*Main body*/
    joint_params.enableLimit = true;
    joint_params.localAnchorB.SetZero(); /*center of tire*/

    /*back left tire*/
    auto* back_left_wheel = new Wheel(world, this->specs.max_forward_speed,
                                      this->specs.max_backward_speed,
                                      this->specs.back_wheel_max_force,
                                      this->specs.back_max_lateral_impulse);
    joint_params.bodyB = back_left_wheel->get_body();
    joint_params.localAnchorA.Set(CAR_WIDTH/2.15, -(CAR_HEIGHT/2)*0.62);
    world.CreateJoint(&joint_params);
    this->wheels.push_back(back_left_wheel);

    //back right tire
    auto* back_right_wheel = new Wheel(world, this->specs.max_forward_speed,
                                       this->specs.max_backward_speed,
                                       this->specs.back_wheel_max_force,
                                       this->specs.back_max_lateral_impulse);
    joint_params.bodyB = back_right_wheel->get_body();
    joint_params.localAnchorA.Set(-CAR_WIDTH/2.15, -(CAR_HEIGHT/2)*0.62);
    world.CreateJoint(&joint_params);
    this->wheels.push_back(back_right_wheel);

    //front left tire
    auto* front_left_wheel = new Wheel(world, this->specs.max_forward_speed,
                                       this->specs.max_backward_speed,
                                       this->specs.front_wheel_max_force,
                                       this->specs.front_max_lateral_impulse);
    joint_params.bodyB = front_left_wheel->get_body();
    joint_params.localAnchorA.Set( CAR_WIDTH/2.15, (CAR_HEIGHT/2)*0.62);
    front_left_joint = (b2RevoluteJoint*)world.CreateJoint(&joint_params);
    this->wheels.push_back(front_left_wheel);

    //front right tire
    auto* front_right_wheel = new Wheel(world, this->specs.max_forward_speed,
                                        this->specs.max_backward_speed,
                                        this->specs.front_wheel_max_force,
                                        this->specs.front_max_lateral_impulse);
    joint_params.bodyB = front_right_wheel->get_body();
    joint_params.localAnchorA.Set( -CAR_WIDTH/2.15, (CAR_HEIGHT/2)*0.62);
    front_right_joint = (b2RevoluteJoint*)world.CreateJoint(&joint_params);
    this->wheels.push_back(front_right_wheel);
}

void Car::update() {
    for (auto & wheel : wheels) {
        wheel->update(key_v);
    }

    /*axis direction*/
    float desire_angle = get_desire_angle(key_h);
    /*0.5 seconds a complete rotation*/
    float rotation_per_step = (ROTATION_PER_SECOND * DEGTORAD) / 60.0f;

    /*front_left_joint & front_right_joint has the same angle*/
    float current_angle = front_left_joint->GetJointAngle();
    auto r = this->car_body->GetLinearVelocity().Length();
    float angle_to_turn = desire_angle*(exp(-r/32)) - current_angle;

    angle_to_turn = b2Clamp(angle_to_turn, -rotation_per_step, rotation_per_step);

    /*update axis*/
    front_left_joint->SetLimits(current_angle + angle_to_turn, current_angle + angle_to_turn);
    front_right_joint->SetLimits(current_angle + angle_to_turn, current_angle + angle_to_turn);
}

float Car::get_desire_angle(int32_t key) {
    float desire_angle = 0;
    if (key == KEY_RIGHT) {
        desire_angle = MAX_ROTATION_ANGLE * DEGTORAD;
    }
    if (key == KEY_LEFT) {
        desire_angle = -MAX_ROTATION_ANGLE * DEGTORAD;
    }
    return desire_angle;
}

void Car::press_key(int32_t key) {
    this->car_state->move(key, this->key_v, this->key_h);
}

void Car::release_key(int32_t key) {
    this->car_state->stop(key, this->key_v, this->key_h);
}

Car::~Car() {
    for (auto & wheel : this->wheels) {
        delete wheel;
    }
}

void Car::set_spawn_point(Coordinate spawn_point) {
    float x_pos = spawn_point.get_x() * TILE_TERRAIN_SIZE;
    float y_pos = spawn_point.get_y() * TILE_TERRAIN_SIZE;

    /*Minus because default start position of Box2D is inverted*/
    float angle = -spawn_point.get_angle() * DEGTORAD;

    this->car_body->SetTransform(b2Vec2(x_pos, y_pos), angle);
    for (auto &wheel : this->wheels) {
        wheel->set_spawn_point(spawn_point);
    }
}

void Car::collide(Body* stactic_object) {
    this->life.make_damage(10);
    if (this->life.is_dead()) {
        this->life.restart_life();
    }
}

int32_t Car::get_ID() {
    return TYPE_CAR;
}

void Car::complete_lap() {
    this->lap_altered = true;
    this->lap_state.reset(new LapCompleted());
}

void Car::restart_lap() {
    this->lap_altered = true;
    this->lap_state.reset(new LapRestarted());
}

void Car::modify_laps(LapCounter& lap_counter, int32_t car_ID) {
    if (lap_altered) {//Just for performance
        this->lap_state = this->lap_state->modify_car_laps(lap_counter, car_ID);
        if (lap_counter.car_complete_laps(car_ID)) {
            this->key_v = NOT_PRESSED;
            this->car_state.reset(new CarStopped());
        }
        this->lap_altered = false;
    }
}

void Car::move_to(Coordinate coordinate) {
    if (this->car_body->GetLinearVelocity().Length() > 20)
        //avoid teleporting very roughly
        return;

    float x_pos = coordinate.get_x() * TILE_TERRAIN_SIZE;
    float y_pos = coordinate.get_y() * TILE_TERRAIN_SIZE;
    float angle = -coordinate.get_angle() * DEGTORAD;

    this->car_body->SetTransform(b2Vec2(x_pos, y_pos), angle);
    for (auto& wheel : this->wheels) {
        wheel->move_to(coordinate);
    }
}

void Car::turn_on() {
    this->car_state.reset(new CarRunning());
}

void Car::send_general_update(int32_t ID, ClientUpdater &client_updater) {
    std::vector<int32_t> params {MSG_UPDATE_ENTITY, TYPE_CAR, ID,
                                 (int32_t)(METER_TO_PIXEL * (car_body->GetPosition().x - (CAR_WIDTH*0.5))),
                                 (int32_t)(METER_TO_PIXEL * (car_body->GetPosition().y - (CAR_HEIGHT*0.5))),
                                 (int32_t)(RADTODEG * car_body->GetAngle()),
                                 (int32_t)(METER_TO_PIXEL * car_body->GetLinearVelocity().Length())};

    for (auto& wheel : wheels) {
        params.emplace_back(int32_t(METER_TO_PIXEL * (wheel->get_position().x - (WIDTH_WHEEL*0.5))));
        params.emplace_back(int32_t(METER_TO_PIXEL * (wheel->get_position().y - (HEIGHT_WHEEL*0.5))));
        params.emplace_back(int32_t(wheel->get_angle()));
    }

    client_updater.send_to_all(UpdateClient(std::move(params)));
    this->life.send_general_update(ID, client_updater);
}
