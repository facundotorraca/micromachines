#include <iostream>
#include "Terrain.h"
#include "Box2D/Box2D.h"
#include <common/Sizes.h>
#include <common/EntityType.h>
#include <model/Vehicle/Car.h>

Terrain::Terrain(int32_t ID, int32_t x, int32_t y):
    coordinate(x,y)
{
    this->ID = ID;
    this->is_limit = false;
    this->terrain_body = nullptr;
    this->terrain_fixture = nullptr;
    this->begin_distance = INFINITE;
}

void Terrain::add_to_world(b2World &world) {
    b2BodyDef body_def;
    this->terrain_body = world.CreateBody(&body_def);

    b2PolygonShape polygon_shape;
    /*Center position*/
    int32_t x_pos = this->coordinate.get_x() * (TILE_TERRAIN_SIZE);
    int32_t y_pos = this->coordinate.get_y() * (TILE_TERRAIN_SIZE);
    polygon_shape.SetAsBox(TILE_TERRAIN_SIZE/2, TILE_TERRAIN_SIZE/2,b2Vec2(x_pos, y_pos), 0);

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygon_shape;
    fixture_def.isSensor = true; /*Set fixture to contact*/
    this->terrain_fixture = this->terrain_body->CreateFixture(&fixture_def);
    this->set_terrain_user_data();
}

Terrain::Terrain(Terrain &&other) noexcept:
    coordinate(other.coordinate)
{
    this->ID = other.ID;
    this->is_limit = other.is_limit;
    this->terrain_body = other.terrain_body;
    this->begin_distance = other.begin_distance;
    this->terrain_fixture = other.terrain_fixture;

    other.terrain_body = nullptr;
    other.terrain_fixture = nullptr;
}

void Terrain::apply_effect(Body *body) {
    if (body->get_ID() == TYPE_CAR && this->begin_distance != INFINITE)
        ((Car*)body)->set_begin_distance(this->begin_distance);
     this->apply_terrain_effect(body);
}

Coordinate Terrain::get_map_coordinate() {
    return this->coordinate;
}

int32_t Terrain::get_ID() {
    return this->ID;
}

void Terrain::set_begin_distance(int32_t distance) {
    this->begin_distance = distance;
}

void Terrain::set_orientation(Orientation orientation) {
    float x = this->coordinate.get_x();
    float y = this->coordinate.get_y();
    this->coordinate = Coordinate(x, y, orientation);
}

void Terrain::set_as_limit() {
    this->is_limit = true;
}

