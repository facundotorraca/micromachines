#include "ContactListener.h"

bool is_sensor(b2Fixture *fixture) {
    return fixture->GetUserData();
}

bool is_body(b2Fixture *fixture) {
    return fixture->GetBody()->GetUserData();
}

Sensor* get_sensor(b2Fixture *fixture) {
    return (Sensor*)(fixture->GetUserData());
}

Body* get_body(b2Fixture *fixture) {
    return (Body*)(fixture->GetBody()->GetUserData());
}

void ContactListener::BeginContact(b2Contact* contact){
    b2Fixture* fixture_A = contact->GetFixtureA();
    b2Fixture* fixture_B = contact->GetFixtureB();

    if (!fixture_A || !fixture_B) return;

    if (is_sensor(fixture_A) && is_body(fixture_B)) {
        Sensor* sensor = get_sensor(fixture_A);
        Body* body = get_body(fixture_B);
        sensor->apply_effect(body);
        return;
    }

    if (is_sensor(fixture_B) && is_body(fixture_A)) {
        Sensor* sensor = get_sensor(fixture_B);
        Body* body = get_body(fixture_A);
        sensor->apply_effect(body);
        return;
    }

    if (is_body(fixture_A) && is_body(fixture_B)) {
        Body* body_A = get_body(fixture_A);
        Body* body_B = get_body(fixture_B);

        body_A->collide(body_B);
        body_B->collide(body_A);
    }
}

void ContactListener::EndContact(b2Contact *contact) {/*Por ahora no hace nada*/}
