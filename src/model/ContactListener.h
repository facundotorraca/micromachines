#ifndef MICROMACHINES_TERRAINCONTACTLISTENER_H
#define MICROMACHINES_TERRAINCONTACTLISTENER_H

#include <iostream>
#include "Box2D/Box2D.h"
#include <model/Vehicle/Wheel.h>
#include <model/FixtureUserData.h>
#include <model/Terrains/Terrain.h>
#include <Box2D/Dynamics/b2WorldCallbacks.h>

class ContactListener : public b2ContactListener {

    void BeginContact(b2Contact *contact) override;

    void EndContact(b2Contact* contact) override;
};

#endif //MICROMACHINES_TERRAINCONTACTLISTENER_H
