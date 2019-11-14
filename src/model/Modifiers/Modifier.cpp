#include "Modifier.h"
#include <common/EntityType.h>

Modifier::Modifier(int32_t time_of_life, int32_t map_x, int32_t map_y, float side_size) {
    this->remaining_time = time_of_life;
    this->map_x = map_x;
    this->map_y = map_y;
    this->side_size = side_size;

    this->modifier_body = nullptr;
    this->modifier_fixture = nullptr;
}

void Modifier::add_to_world(b2World &world) {
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

void Modifier::apply_effect(Body *body) {
    if (body->get_ID() == TYPE_CAR)
        this->apply_modifier_effect(body);
}

void Modifier::update_remaining_life() {
    this->remaining_time -= 1;
}

bool Modifier::is_dead() {
    //std::unique_lock<std::mutex> lock(mtx);
    return this->remaining_time <= 0;
}

Coordinate Modifier::get_coordinate() {
    return {float(this->map_x), float(this->map_y)};
}

Modifier::~Modifier() {
    if (this->modifier_body)
        this->modifier_body->GetWorld()->DestroyBody(this->modifier_body);
}


