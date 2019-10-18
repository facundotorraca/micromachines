#include <iostream>
#include "Wheel.h"
#include "common/Key.h"
#include "Box2D/Box2D.h"
#include "RacingTrack.h"

#define RADTODEG 57.295779513082320876f

Wheel::Wheel(RacingTrack& racing_track, float max_forward_speed, float max_backward_speed, float max_driver_force) {
    this->max_forward_speed = max_forward_speed;
    this->max_backward_speed = max_backward_speed;
    this->max_driver_force= max_driver_force;

    b2BodyDef wheel_body_def;
    wheel_body_def.type = b2_dynamicBody;
    /*Allocates memory for the wheels's body*/
    this->wheel_body = racing_track.add_car(wheel_body_def);

    b2PolygonShape polygon;
    polygon.SetAsBox(0.5f, 1.25f);
    this->wheel_body->CreateFixture(/*Shape*/&polygon, 1);

    /*Set a reference of the container to the body*/
    wheel_body->SetUserData(this);
}

b2Vec2 Wheel::get_lateral_velocity() {
    b2Vec2 current_right_normal = this->wheel_body->GetWorldVector(b2Vec2(1, 0) );
    return b2Dot(current_right_normal,this->wheel_body->GetLinearVelocity()) * current_right_normal;
}

b2Vec2 Wheel::get_forward_velocity() {
    b2Vec2 current_forward_normal = this->wheel_body->GetWorldVector( b2Vec2(0,1) );
    return b2Dot(current_forward_normal,this->wheel_body->GetLinearVelocity()) * current_forward_normal;
}

void Wheel::update_drive(uint8_t key) {
    /*Find if whe want to go UP or DOWN*/
    float desiredSpeed = 0;
    if (key == KEY_UP) {
        desiredSpeed = this->max_forward_speed;
    } else if (key == KEY_DOWN) {
        desiredSpeed = this->max_backward_speed;
    } else {
        return; //Dont do anything
    }

    /*Find current speed in forward direction*/
    b2Vec2 current_forward_normal = this->wheel_body->GetWorldVector( b2Vec2(0,1) );
    float current_speed = b2Dot(this->get_forward_velocity(), current_forward_normal);

    /*Apply necessary force*/
    float force = 0;
    if (desiredSpeed > current_speed) {
        force = max_driver_force;
    } else if ( desiredSpeed < current_speed) {
        force = (-max_driver_force);
    }
    else {
        return;
    }
    this->wheel_body->ApplyForce(force * current_forward_normal,this->wheel_body->GetWorldCenter(),true);
}

void Wheel::update_turn(uint8_t key) {
    float desire_torque = 0;
    if (key == KEY_LEFT) {
        desire_torque = 15;
    } else if (key == KEY_RIGHT) {
        desire_torque = -15;
    } else {
        return; //Dont do anything
    }
    this->wheel_body->ApplyTorque(desire_torque, true);
}

void Wheel::update_friction() {
    //lateral linear velocity
    b2Vec2 impulse = this->wheel_body->GetMass() * this->get_lateral_velocity();

    if (impulse.Length() > max_lateral_impulse ) {
        impulse *= max_lateral_impulse / impulse.Length();
    }
    this->wheel_body->ApplyLinearImpulse(current_traction*impulse, this->wheel_body->GetWorldCenter(),true);

    //angular velocity
    this->wheel_body->ApplyAngularImpulse(current_traction*0.1f*this->wheel_body->GetInertia()*-this->wheel_body->GetAngularVelocity(),true);

    //forward linear velocity
    b2Vec2 current_forward_normal = this->get_forward_velocity();
    float current_forward_speed = current_forward_normal.Normalize();
    float drag_force_magnitude = (-2) * current_forward_speed;
    this->wheel_body->ApplyForce(this->current_traction * drag_force_magnitude * current_forward_normal, wheel_body->GetWorldCenter(), true);
}

const b2Vec2& Wheel::getPosition() {
    return this->wheel_body->GetLinearVelocity();
}

Wheel::~Wheel() {
    /* Capay os deberia destruir el sever*/
    //this->wheel_body->GetWorld()->DestroyBody(this->wheel_body);
}

void Wheel::update(uint8_t key) {
    this->update_friction();
    this->update_drive(key);
    this->update_turn(key);
}

float Wheel::get_angle() {
    return RADTODEG * this->wheel_body->GetAngle();
}
