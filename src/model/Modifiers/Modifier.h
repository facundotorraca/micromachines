#ifndef MICROMACHINES_MODIFIER_H
#define MICROMACHINES_MODIFIER_H

#include <mutex>
#include <cstdint>
#include <iostream>
#include "Box2D/Box2D.h"
#include <model/Sensor.h>
#include <common/Sizes.h>
#include <common/Coordinate.h>

class Modifier : public Sensor {

    protected:
        int32_t map_x;
        int32_t map_y;
        int32_t remaining_time;

        float side_size;

        b2Body* modifier_body;
        b2Fixture* modifier_fixture;

        std::mutex mtx;

    public:
        explicit Modifier(int32_t time_of_life, int32_t map_x, int32_t map_y, float side_size) {
            this->remaining_time = time_of_life;
            this->map_x = map_x;
            this->map_y = map_y;
            this->side_size = side_size;


            this->modifier_body = nullptr;
            this->modifier_fixture = nullptr;
        }

        void add_to_world(b2World &world) {
            b2BodyDef body_def;
            this->modifier_body = world.CreateBody(&body_def);

            b2PolygonShape polygon_shape;
            /*Center position*/
            int32_t x_pos = this->map_x * (TILE_TERRAIN_SIZE);
            int32_t y_pos = this->map_y * (TILE_TERRAIN_SIZE);
            polygon_shape.SetAsBox(this->side_size/2, this->side_size/2,b2Vec2(x_pos, y_pos), 0);

            b2FixtureDef fixture_def;
            fixture_def.shape = &polygon_shape;
            fixture_def.isSensor = true; /*Set fixture to contact*/
            this->modifier_fixture = this->modifier_body->CreateFixture(&fixture_def);
            this->set_modifier_user_data();
        }

        virtual void apply_modifier_effect(Body* body) = 0;

        void apply_effect(Body* body) override {
            this->apply_modifier_effect(body);
        }

        virtual void set_modifier_user_data() = 0;

        void update_remaining_life() {
            this->remaining_time -= 1;
        }

        bool is_dead() {
            std::unique_lock<std::mutex> lock(mtx);
            return this->remaining_time <= 0;
        }

        Coordinate get_coordinate() {
            return {float(this->map_x), float(this->map_y), 0};
        }

        virtual int32_t get_modifier_type() = 0;

        ~Modifier() override {
            if (this->modifier_body)
                this->modifier_body->GetWorld()->DestroyBody(this->modifier_body);
        }

};


#endif //MICROMACHINES_MODIFIER_H
