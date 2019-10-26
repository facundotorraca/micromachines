#ifndef MICROMACHINES_TERRAINCONTACTLISTENER_H
#define MICROMACHINES_TERRAINCONTACTLISTENER_H

#include <iostream>
#include "Box2D/Box2D.h"
#include <model/Vehicle/Wheel.h>
#include <model/FixtureUserData.h>
#include <model/Terrains/Terrain.h>
#include <Box2D/Dynamics/b2WorldCallbacks.h>

class TerrainContactListener : public b2ContactListener {

    void BeginContact(b2Contact *contact) override {
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

    void EndContact(b2Contact* contact) override { /*Por ahora no hace nada*/ }

};

#endif //MICROMACHINES_TERRAINCONTACTLISTENER_H
