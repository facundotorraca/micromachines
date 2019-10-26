#include "TerrainContactListener.h"

void TerrainContactListener::BeginContact(b2Contact *contact) {
    auto* fixtureUserData_a = (FixtureUserData *) contact->GetFixtureA()->GetUserData();
    auto* fixtureUserData_b = (FixtureUserData *) contact->GetFixtureB()->GetUserData();

    if (!fixtureUserData_a || !fixtureUserData_b) return;

    if (fixtureUserData_a->get_type_ID() == TYPE_WHEEL && fixtureUserData_b->get_type_ID() != TYPE_WHEEL) {
        auto* wheel = (Wheel*)contact->GetFixtureA()->GetBody()->GetUserData();
        auto* terrain = (Terrain*) contact->GetFixtureB()->GetBody()->GetUserData();

        terrain->apply_effect(wheel);
    }

    if (fixtureUserData_b->get_type_ID() == TYPE_WHEEL && fixtureUserData_a->get_type_ID() != TYPE_WHEEL) {
        auto* wheel = (Wheel*)contact->GetFixtureB()->GetBody()->GetUserData();
        auto* terrain = (Terrain*) contact->GetFixtureA()->GetBody()->GetUserData();

        terrain->apply_effect(wheel);
    }
}

void TerrainContactListener::EndContact(b2Contact *contact) {
    /*Por ahora no hace nada*/
}
