#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include <client/Camera.h>
#include <client/SoundSystem.h>
#include "Entity.h"
#include "Wheel.h"
#include "CarInfo.h"

#define ACCELERATION_SOUND_TOP -100
#define ACCELERATION_SOUND_BOTTOM -60

class Car : public Entity{
    int32_t car_tex;
    int32_t dmg_tex;
    Wheel wheel1;
    Wheel wheel2;
    Wheel wheel3;
    Wheel wheel4;
    int32_t health = 100;
    std::list<int32_t> velocities;
    float i = 0;
    float getAccel();
public:
    explicit Car(int32_t id);
    void draw(Camera& camera) override;
    void updateAll(CarInfo& info, SoundSystem& sound);
    void setHealth(int32_t health, SoundSystem& sound);
};


#endif //MICROMACHINES_CAR_H
