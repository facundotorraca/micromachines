//
// Created by javier on 18/11/19.
//

#include "Car.h"

Car::Car(int32_t id) {
    int32_t texture = id%5;
    switch (texture){
        case 0: car_tex = CAR_1_TEX; dmg_tex = DMG_CAR_1_TEX; break;
        case 1: car_tex = CAR_2_TEX; dmg_tex = DMG_CAR_2_TEX; break;
        case 2: car_tex = CAR_3_TEX; dmg_tex = DMG_CAR_3_TEX; break;
        case 3: car_tex = CAR_4_TEX; dmg_tex = DMG_CAR_4_TEX; break;
        default:
            car_tex = CAR_5_TEX; dmg_tex = DMG_CAR_5_TEX;
    }
}

void Car::draw(Camera& camera){
    wheel1.draw(camera);
    wheel2.draw(camera);
    wheel3.draw(camera);
    wheel4.draw(camera);
    int32_t size_w = CAR_WIDTH * METER_TO_PIXEL;
    int32_t size_h = CAR_HEIGHT * METER_TO_PIXEL;
    if (health <= 0){
        camera.drawWorldTexture(WRECKED_CAR_TEX, posX, posY, size_w, size_h, rot);
        if (i <= 7) {
            camera.drawWorldTexture(EXPLOSION_TEX+(int)i, posX, posY, 2.5*size_w, 2.5*size_w, rot);
        }
        i+=0.08;
    } else {
        i = 0;
        if (health <= 50) {
            camera.drawWorldTexture(dmg_tex, posX, posY, size_w, size_h, rot);
        } else {
            camera.drawWorldTexture(car_tex, posX, posY, size_w, size_h, rot);
        }
    }
}

void Car::updateAll(CarInfo& info, SoundSystem& sound) {
    sound.playEngineSound(info.car_id, posX, posY, info.carvel);
    if (velocities.size() > 5)
        velocities.erase(velocities.begin());
    velocities.emplace_back(info.carvel);
    auto accel = this->getAccel();
    if (accel < ACCELERATION_SOUND_BOTTOM && accel > ACCELERATION_SOUND_TOP && info.carvel > 200*3.6/METER_TO_PIXEL){
        sound.playBrakesSound(posX, posY);
    }
    posX = info.carx; posY = info.cary; rot = info.carrot;
    wheel1.update_position(info.w1x, info.w1y, info.w1rot);
    wheel2.update_position(info.w2x, info.w2y, info.w2rot);
    wheel3.update_position(info.w3x, info.w3y, info.w3rot);
    wheel4.update_position(info.w4x, info.w4y, info.w4rot);
}

float Car::getAccel(){
    int c = 0;
    if (velocities.empty() || velocities.size() == 1)
        return 0;
    auto prev_vel = *velocities.begin();
    for (auto iter = velocities.begin()++; iter != velocities.end(); iter++){
        c += (*iter - prev_vel);
        prev_vel = *iter;
    }
    return (float)c/velocities.size();
}

void Car::setHealth(int32_t health, SoundSystem& sound){
    if (health <= 0)
        sound.playExplosionSound(posX, posY);
    else if (health > this->health)
        sound.playFixSound(posX, posY);
    else if (health < this->health && !Mix_Playing(16))
        sound.playCrashSound(posX, posY);
    this->health = health;
}

