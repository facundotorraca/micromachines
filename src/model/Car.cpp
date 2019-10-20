#include <iostream>
#include "Car.h"
#include "Wheel.h"
#include "CarSpecs.h"
#include "common/Key.h"

#define CAR_HEIGHT 6.0f
#define CAR_WIDTH 4.0f
#define MAX_ROTATION_ANGLE 35.0f
#define ROTATION_PER_SECOND 140.0f
#define NOT_PRESSED 0
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

Car::Car(RacingTrack& racing_track, CarSpecs specs):
    specs(specs), key_h(NOT_PRESSED), key_v(NOT_PRESSED)
{
    //create car body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    this->car_body = racing_track.add_body(bodyDef);
    /*reduce the world velocity of bodies*/
    this->car_body->SetAngularDamping(0.2);
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
    polygon_shape.SetAsBox(CAR_WIDTH, CAR_HEIGHT);
    this->car_body->CreateFixture(/*shape*/&polygon_shape, 0.1f);

    //common joint parameters
    b2RevoluteJointDef joint_params;
    joint_params.bodyA = this->car_body; /*Main body*/
    joint_params.enableLimit = true;
    joint_params.localAnchorB.SetZero(); /*center of tire*/

    /*back left tire*/
    auto* back_left_wheel = new Wheel(racing_track, this->specs.get_max_forward_speed(),
                                      this->specs.get_max_backward_speed(),
                                      this->specs.get_back_wheel_max_force(),
                                      this->specs.get_back_max_lateral_impulse());
    joint_params.bodyB = back_left_wheel->get_body();
    joint_params.localAnchorA.Set(1.75, -2 );
    racing_track.get_world().CreateJoint(&joint_params);
    this->wheels.push_back(back_left_wheel);

    //back right tire
    auto* back_right_wheel = new Wheel(racing_track, this->specs.get_max_forward_speed(),
                                       this->specs.get_max_backward_speed(),
                                       this->specs.get_back_wheel_max_force(),
                                       this->specs.get_back_max_lateral_impulse());
    joint_params.bodyB = back_right_wheel->get_body();
    joint_params.localAnchorA.Set(-1.75, -2 );
    racing_track.get_world().CreateJoint(&joint_params);
    this->wheels.push_back(back_right_wheel);

    //front left tire
    auto* front_left_wheel = new Wheel(racing_track, this->specs.get_max_forward_speed(),
                                       this->specs.get_max_backward_speed(),
                                       this->specs.get_front_wheel_max_force(),
                                       this->specs.get_front_max_lateral_impulse());
    joint_params.bodyB = front_left_wheel->get_body();
    joint_params.localAnchorA.Set( 1.75, 2 );
    front_left_joint = (b2RevoluteJoint*)racing_track.get_world().CreateJoint(&joint_params);
    this->wheels.push_back(front_left_wheel);

    //front right tire
    auto* front_right_wheel = new Wheel(racing_track, this->specs.get_max_forward_speed(),
                                        this->specs.get_max_backward_speed(),
                                        this->specs.get_front_wheel_max_force(),
                                        this->specs.get_front_max_lateral_impulse());
    joint_params.bodyB = front_right_wheel->get_body();
    joint_params.localAnchorA.Set( -1.75, 2 );
    front_right_joint = (b2RevoluteJoint*)racing_track.get_world().CreateJoint(&joint_params);
    this->wheels.push_back(front_right_wheel);
}

void Car::update() {
    for (auto & wheel : wheels) {
        wheel->update(key_v);
    }

    /*axis direction*/
    float desire_angle = this->get_desire_angle(key_h);
    /*0.5 seconds a complete rotation*/
    float rotation_per_step = (ROTATION_PER_SECOND * DEGTORAD) / 60.0f;

    /*front_left_joint & front_right_joint has the same angle*/
    float current_angle = front_left_joint->GetJointAngle();
    float angle_to_turn = desire_angle - current_angle;

    angle_to_turn = b2Clamp(angle_to_turn, -rotation_per_step, rotation_per_step);

    /*update axis*/
    front_left_joint->SetLimits(current_angle + angle_to_turn, current_angle + angle_to_turn);
    front_right_joint->SetLimits(current_angle + angle_to_turn, current_angle + angle_to_turn);
}

std::vector<b2Vec2> Car::get_wheels_position() {
    std::vector<b2Vec2> positions;
    for (auto & m_tire : wheels) {
        positions.push_back(m_tire->get_position());
    }
    return positions;
}

std::vector<float> Car::get_wheels_angle() {
    std::vector<float> angles;
    for (auto & m_tire : wheels) {
        angles.push_back(m_tire->get_angle());
    }
    return angles;
}

float Car::get_desire_angle(uint8_t key) {
    float desire_angle = 0;
    if (key == KEY_RIGHT) {
        desire_angle = MAX_ROTATION_ANGLE * DEGTORAD;
    }
    if (key == KEY_LEFT) {
        desire_angle = -MAX_ROTATION_ANGLE * DEGTORAD;
    }
    return desire_angle;
}

float Car::getPositionX() {
    return 50.0f * this->car_body->GetPosition().x;
}

float Car::getPositionY() {
    return 50.0f * this->car_body->GetPosition().y;
}


float Car::get_angle() {
    return RADTODEG * this->car_body->GetAngle();
}

Car::~Car() {
    for (auto & m_tire : wheels) {
        delete m_tire;
    }
}

void Car::press_key(uint8_t key) {
    if (key == KEY_DOWN || key == KEY_UP)
        key_v = key;
    else
        key_h = key;
}

void Car::release_key(uint8_t key) {
    if (key == KEY_DOWN || key == KEY_UP)
        key_v = NOT_PRESSED;
    else
        key_h = NOT_PRESSED;
}
