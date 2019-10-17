#include "Wheel.h"
#include "common/Key.h"
#include "Box2D/Box2D.h"
#include "RacingTrack.h"

Wheel::Wheel(RacingTrack &racing_track) {
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

void Wheel::update_drive(Key controlState) {
    /*Find if whe want to go UO or DOWN*/
    float desiredSpeed = 0;
    switch (controlState) {
        case UP:
            desiredSpeed = m_maxForwardSpeed;
            break;
        case DOWN:
            desiredSpeed = m_maxBackwardSpeed;
            break;
        default:
            return;
    }

    /*Find current speed in forward direction*/
    b2Vec2 current_forward_normal = m_body->GetWorldVector( b2Vec2(0,1) );
    float currentSpeed = b2Dot(this->get_forward_velocity(), current_forward_normal);

    /*apply necessary force*/
    float force = 0;
    if ( desiredSpeed > currentSpeed )
        force = m_maxDriveForce;
    else if ( desiredSpeed < currentSpeed )
        force = -m_maxDriveForce;
    else
        return;
    m_body->ApplyForce( force * currentForwardNormal, m_body->GetWorldCenter() );
}

void Wheel::updateFriction() {
    //lateral linear velocity
    b2Vec2 impulse = this->wheel_body->GetMass() * this->get_lateral_velocity();
    if ( impulse.Length() > m_maxLateralImpulse )
        impulse *= m_maxLateralImpulse / impulse.Length();
    m_body->ApplyLinearImpulse( m_currentTraction * impulse, m_body->GetWorldCenter() );

    //angular velocity
    m_body->ApplyAngularImpulse( m_currentTraction * 0.1f * m_body->GetInertia() * -m_body->GetAngularVelocity() );

    //forward linear velocity
    b2Vec2 currentForwardNormal = getForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -2 * currentForwardSpeed;
    m_body->ApplyForce( m_currentTraction * dragForceMagnitude * currentForwardNormal, m_body->GetWorldCenter() );
}

void Wheel::updateTurn(int controlState) {
    float desiredTorque = 0;
    switch ( controlState & (TDC_LEFT|TDC_RIGHT) ) {
        case TDC_LEFT:  desiredTorque = 15;  break;
        case TDC_RIGHT: desiredTorque = -15; break;
        default: ;//nothing
    }
    m_body->ApplyTorque( desiredTorque );
}

Wheel::~Wheel() {
    /* Capay os deberia destruir el sever*/
    //this->wheel_body->GetWorld()->DestroyBody(this->wheel_body);
}
