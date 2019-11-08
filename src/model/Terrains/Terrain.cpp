#include <iostream>
#include "Terrain.h"
#include "Box2D/Box2D.h"
#include <common/Sizes.h>
#include <common/EntityType.h>

Terrain::Terrain(int32_t x, int32_t y, int32_t rotation, int32_t ID) {
    this->ID = ID;
    this->map_x = x; //Relative position on a grid
    this->map_y = y; //Relative position on a grid
    this->rotation = rotation;
    this->terrain_body = nullptr;
    this->terrain_fixture = nullptr;
    /*The real position is calculated with Box2D settings*/
}

void Terrain::add_to_world(b2World &world) {
    b2BodyDef body_def;
    this->terrain_body = world.CreateBody(&body_def);

    b2PolygonShape polygon_shape;
    /*Center position*/
    int32_t x_pos = this->map_x * (TILE_TERRAIN_SIZE);
    int32_t y_pos = this->map_y * (TILE_TERRAIN_SIZE);
    polygon_shape.SetAsBox(TILE_TERRAIN_SIZE/2, TILE_TERRAIN_SIZE/2,b2Vec2(x_pos, y_pos), 0);

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygon_shape;
    fixture_def.isSensor = true; /*Set fixture to contact*/
    this->terrain_fixture = this->terrain_body->CreateFixture(&fixture_def);
    this->set_terrain_user_data();
}

Terrain::Terrain(Terrain &&other) noexcept {
    this->ID = other.ID;
    this->map_x = other.map_x;
    this->map_y = other.map_y;
    this->rotation = other.rotation;
    this->terrain_body = other.terrain_body;
    this->terrain_fixture = other.terrain_fixture;

    other.terrain_body = nullptr;
    other.terrain_fixture = nullptr;
}

void Terrain::apply_effect(Body *body) {
    if (body->get_ID() == TYPE_WHEEL)
        this->apply_terrain_effect(body);
}

Coordinate Terrain::get_map_coordinate() {
    return {(float)this->map_x, (float)this->map_y, 0};
}

