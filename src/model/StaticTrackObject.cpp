#include "Box2D/Box2D.h"
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include <common/EntityType.h>
#include <model/Vehicle/Car.h>
#include "StaticTrackObject.h"

StaticTrackObject::StaticTrackObject(int32_t ID, int32_t x, int32_t y, int32_t rotation) {
    this->ID = ID;
    this->map_x = x; //Relative position on a grid
    this->map_y = y; //Relative position on a grid
    this->rotation = rotation;
    this->object_body = nullptr;
    this->object_fixture = nullptr;
    /*The real position is calculated with Box2D settings*/
}

StaticTrackObject::StaticTrackObject(StaticTrackObject &&other) noexcept {
    this->ID = other.ID;
    this->map_x = other.map_x;
    this->map_y = other.map_y;
    this->rotation = other.rotation;
    this->object_body = other.object_body;
    this->object_fixture = other.object_fixture;

    other.object_body = nullptr;
    other.object_fixture = nullptr;
}

void StaticTrackObject::add_to_world(b2World &world) {
    b2BodyDef body_def;
    body_def.type = b2_staticBody;
    this->object_body = world.CreateBody(&body_def);

    b2PolygonShape polygon_shape;

    /*Center position*/
    int32_t x_pos = this->map_x * (TILE_TERRAIN_SIZE);
    int32_t y_pos = this->map_y * (TILE_TERRAIN_SIZE);
    polygon_shape.SetAsBox(TILE_TERRAIN_SIZE/2, TILE_TERRAIN_SIZE/2,b2Vec2(x_pos, y_pos), 0);

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygon_shape;
    //fixture_def.isSensor = true; /*Set fixture to contact*/
    this->object_fixture = this->object_body->CreateFixture(&fixture_def);

    this->object_body->SetUserData(this); //Set a self reference to handler collisions
}

UpdateClient StaticTrackObject::get_to_send() {
    int32_t x = METER_TO_PIXEL * ((this->map_x * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    int32_t y = METER_TO_PIXEL * ((this->map_y * (TILE_TERRAIN_SIZE)) - TILE_TERRAIN_SIZE*0.5);
    std::vector<int32_t> update_info {MSG_SEND_TILE, this->ID, x, y, this->rotation};
    return UpdateClient(std::move(update_info));
}

void StaticTrackObject::collide(Body *body) {
    if (body->get_ID() == TYPE_CAR)
        ((Car*)body)->make_damage(10);
}

int32_t StaticTrackObject::get_ID() {
    return TYPE_STATIC_OBJECT;
}
