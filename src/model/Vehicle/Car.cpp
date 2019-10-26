#include "Car.h"
#include "Wheel.h"
#include <iostream>
#include "CarSpecs.h"
#include "common/Key.h"
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include <common/EntityType.h>

#define NOT_PRESSED 0

#define MAX_ROTATION_ANGLE 45.0f
#define ROTATION_PER_SECOND 90.0

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

Car::Car(RacingTrack& racing_track, CarSpecs specs):
    specs(specs), key_h(NOT_PRESSED), key_v(NOT_PRESSED)
{
    /*create car body*/
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    this->car_body = racing_track.add_body(bodyDef);

    /*reduce the world velocity of bodies*/
    this->car_body->SetAngularDamping(0.1);
    this->create_wheels(racing_track);

}

Car::Car(Car&& other_car) noexcept:
    specs(other_car.specs),
    car_body(other_car.car_body),
    wheels(std::move(other_car.wheels)),
    front_left_joint(other_car.front_left_joint),
    front_right_joint(other_car.front_right_joint)
{
    this->key_h = other_car.key_h;
    this->key_v = other_car.key_v;

    other_car.key_h = NOT_PRESSED;
    other_car.key_v = NOT_PRESSED;

    other_car.car_body = nullptr;
    other_car.front_right_joint = nullptr;
    other_car.front_left_joint = nullptr;
}

void Car::create_wheels(RacingTrack& racing_track) {
    b2PolygonShape polygon_shape;
    polygon_shape.SetAsBox(CAR_WIDTH/2, CAR_HEIGHT/2);
    this->car_body->CreateFixture(/*shape*/&polygon_shape, 0.2f);

    //common joint parameters
    b2RevoluteJointDef joint_params;
    joint_params.bodyA = this->car_body; /*Main body*/
    joint_params.enableLimit = true;
    joint_params.localAnchorB.SetZero(); /*center of tire*/

    /*back left tire*/
    auto* back_left_wheel = new Wheel(racing_track.get_world(), this->specs.max_forward_speed,
                                      this->specs.max_backward_speed,
                                      this->specs.back_wheel_max_force,
                                      this->specs.back_max_lateral_impulse);
    joint_params.bodyB = back_left_wheel->get_body();
    joint_params.localAnchorA.Set(CAR_WIDTH/2.15, -(CAR_HEIGHT/2)*0.62);
    racing_track.get_world().CreateJoint(&joint_params);
    this->wheels.push_back(back_left_wheel);

    //back right tire
    auto* back_right_wheel = new Wheel(racing_track.get_world(), this->specs.max_forward_speed,
                                       this->specs.max_backward_speed,
                                       this->specs.back_wheel_max_force,
                                       this->specs.back_max_lateral_impulse);
    joint_params.bodyB = back_right_wheel->get_body();
    joint_params.localAnchorA.Set(-CAR_WIDTH/2.15, -(CAR_HEIGHT/2)*0.62);
    racing_track.get_world().CreateJoint(&joint_params);
    this->wheels.push_back(back_right_wheel);

    //front left tire
    auto* front_left_wheel = new Wheel(racing_track.get_world(), this->specs.max_forward_speed,
                                       this->specs.max_backward_speed,
                                       this->specs.front_wheel_max_force,
                                       this->specs.front_max_lateral_impulse);
    joint_params.bodyB = front_left_wheel->get_body();
    joint_params.localAnchorA.Set( CAR_WIDTH/2.15, (CAR_HEIGHT/2)*0.62);
    front_left_joint = (b2RevoluteJoint*)racing_track.get_world().CreateJoint(&joint_params);
    this->wheels.push_back(front_left_wheel);

    //front right tire
    auto* front_right_wheel = new Wheel(racing_track.get_world(), this->specs.max_forward_speed,
                                        this->specs.max_backward_speed,
                                        this->specs.front_wheel_max_force,
                                        this->specs.front_max_lateral_impulse);
    joint_params.bodyB = front_right_wheel->get_body();
    joint_params.localAnchorA.Set( -CAR_WIDTH/2.15, (CAR_HEIGHT/2)*0.62);
    front_right_joint = (b2RevoluteJoint*)racing_track.get_world().CreateJoint(&joint_params);
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
    if (key == KEY_DOWN || key == KEY_UP)
        key_v = key;
    else
        key_h = key;
}

void Car::release_key(int32_t key) {
    if (key == KEY_DOWN || key == KEY_UP)
        key_v = NOT_PRESSED;
    else
        key_h = NOT_PRESSED;
}

Car::~Car() {
    for (auto & wheel : this->wheels) {
        delete wheel;
    }
}

UpdateClient Car::get_update(const int32_t id) {
    std::vector<int32_t> params {MSG_UPDATE_ENTITY, TYPE_CAR, id,
                                (int32_t)(METER_TO_PIXEL * (this->car_body->GetPosition().x - (CAR_WIDTH*0.5))),
                                (int32_t)(METER_TO_PIXEL * (this->car_body->GetPosition().y - (CAR_HEIGHT*0.5))),
                                (int32_t)(RADTODEG * this->car_body->GetAngle())};

    for (auto& wheel : wheels){
        params.emplace_back(int32_t(METER_TO_PIXEL * (wheel->get_position().x - (WIDTH_WHEEL*0.5))));
        params.emplace_back(int32_t(METER_TO_PIXEL * (wheel->get_position().y - (HEIGHT_WHEEL*0.5))));
        params.emplace_back(int32_t(wheel->get_angle()));
    }
    return UpdateClient(std::move(params));
}
