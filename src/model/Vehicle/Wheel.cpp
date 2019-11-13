#include "Car.h"
#include "Wheel.h"
#include <iostream>
#include "common/Key.h"
#include "Box2D/Box2D.h"
#include <common/Sizes.h>
#include <common/EntityType.h>

#define MAX_PROPORTION 1

#define RADTODEG 57.295779513082320876f
#define DEGTORAD 0.0174532925199432957f


Wheel::Wheel(b2World& world, float max_forward_speed, float max_backward_speed, float max_driver_force, float max_lateral_impulse):
    wheel_state(max_forward_speed, max_backward_speed, max_driver_force, max_lateral_impulse)
{
    b2BodyDef wheel_body_def;
    wheel_body_def.type = b2_dynamicBody;

    this->speed_proportion = MAX_PROPORTION;
    this->traction_proportion = MAX_PROPORTION;

    /*Allocates memory for the wheels's body*/
    this->wheel_body = world.CreateBody(&wheel_body_def);
    this->wheel_body->SetUserData(this);

    b2PolygonShape polygon;
    polygon.SetAsBox(WIDTH_WHEEL/2/*0.1*/, HEIGHT_WHEEL/2 /*0.25*/);
    this->wheel_body->CreateFixture(/*Shape*/&polygon, /*16.875*/ 6.92 /*1.5*/ );
    //Wheels are like punctual particle
}

b2Vec2 Wheel::get_lateral_velocity() {
    /*GetWorldVector return the current orientation of these versor*/
    b2Vec2 current_lateral_orientation = wheel_body->GetWorldVector(b2Vec2(1, 0));
    return b2Dot(current_lateral_orientation,wheel_body->GetLinearVelocity()) * current_lateral_orientation;
}

b2Vec2 Wheel::get_forward_velocity() {
    /*GetWorldVector return the current orientation of these versor*/
    b2Vec2 current_forward_orientation = wheel_body->GetWorldVector(b2Vec2(0, 1));
    return b2Dot(current_forward_orientation, wheel_body->GetLinearVelocity()) * current_forward_orientation;
}

void Wheel::update_speed(uint8_t key) {
    /*Find if whe want to go UP or DOWN*/
    float desire_speed = 0;
    if (key == ACCELERATE) {
        desire_speed = this->speed_proportion * this->wheel_state.get_max_forward_speed();
    } else if (key == BRAKE) {
        desire_speed = this->speed_proportion * this->wheel_state.get_max_backward_speed();
    } else {
        return;
    }

    /*Find current speed in forward direction*/
    b2Vec2 current_forward_velocity = this->wheel_body->GetWorldVector(b2Vec2(0, 1) );
    float current_speed = b2Dot(this->get_forward_velocity(), current_forward_velocity);

    /*Apply necessary force*/
    float force = 0;
    if (desire_speed > current_speed) {
        force = this->wheel_state.get_max_driver_force();
    } else if (desire_speed < current_speed) {
        force = -this->wheel_state.get_max_driver_force();
    } else {
        return;
    }
    /*Apply a force on the wheels center*/
    this->wheel_body->ApplyForce(this->traction_proportion * force * current_forward_velocity, this->wheel_body->GetWorldCenter(), true);
}

void Wheel::update_friction() {
    /*lateral linear velocity*/
    b2Vec2 impulse = this->wheel_body->GetMass() * -this->get_lateral_velocity();

    /*---------------------------------------------*/
    /* restrict that impulse to some maximum value */
    /* and the tire will slip when the             */
    /* circumstances require a greater correction  */
    /* than allowable                              */
    /*---------------------------------------------*/
    if (impulse.Length()/*Absolute value*/ > this->wheel_state.get_max_lateral_impulse()) {
        impulse *= this->wheel_state.get_max_lateral_impulse() / impulse.Length();
    }
    this->wheel_body->ApplyLinearImpulse(this->traction_proportion * impulse, this->wheel_body->GetWorldCenter(), true);

    //angular velocity
    this->wheel_body->ApplyAngularImpulse(this->traction_proportion * 0.1f * this->wheel_body->GetInertia() * -this->wheel_body->GetAngularVelocity(), true);

    //forward linear velocity
    b2Vec2 current_forward_velocity = this->get_forward_velocity();
    float current_forward_speed = current_forward_velocity.Normalize(); /*Normalize returns absolute value*/
    float drag_force_magnitude = -2 * current_forward_speed;
    this->wheel_body->ApplyForce(this->traction_proportion * drag_force_magnitude * current_forward_velocity, this->wheel_body->GetWorldCenter(), true);
}

void Wheel::update(uint8_t key) {
    this->update_friction();
    this->update_speed(key);
    this->wheel_state.update();
}

const b2Vec2& Wheel::get_position() {
    return this->wheel_body->GetPosition();
}

float Wheel::get_angle() {
    return RADTODEG * this->wheel_body->GetAngle();
}

b2Body* Wheel::get_body() {
    return this->wheel_body;
}

void Wheel::restore_specs() {
    this->speed_proportion = MAX_PROPORTION;
    this->traction_proportion = MAX_PROPORTION;
}

void Wheel::reduce_max_traction(float proportion) {
    this->traction_proportion = proportion;
}

void Wheel::reduce_max_speed(float proportion) {
    this->speed_proportion = proportion;
}

void Wheel::collide(Body *static_object) {
    std::cout << "WHEEL: ME LA PUSE\n";
}

int32_t Wheel::get_ID() {
    return TYPE_WHEEL;
}

void Wheel::move_to(Coordinate coordinate) {
    float x_pos = coordinate.get_x() * TILE_TERRAIN_SIZE;
    float y_pos = coordinate.get_y() * TILE_TERRAIN_SIZE;
    float angle = coordinate.get_angle() * DEGTORAD;

    this->wheel_body->SetLinearVelocity(b2Vec2(0,0));
    this->wheel_body->SetAngularVelocity(0);

    this->wheel_body->SetTransform(b2Vec2(x_pos, y_pos), angle);
}

void Wheel::apply_effect(std::unique_ptr<Effect> effect) {
    this->wheel_state.apply_effect(std::move(effect));
}

void Wheel::send_effect_update(int32_t ID, ClientUpdater& updater) {
    this->wheel_state.send_effect_update(ID, updater);
}

Wheel::~Wheel() {
    this->wheel_body->GetWorld()->DestroyBody(this->wheel_body);
}

void Wheel::apply_plugin(float max_forward_speed, float max_backward_speed, float max_driver_force, float max_lateral_impulse) {
    this->wheel_state.apply_plugin(max_forward_speed, max_backward_speed, max_driver_force, max_lateral_impulse);
}




