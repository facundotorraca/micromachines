#include "Box2D/Box2D.h"
#include <common/Sizes.h>
#include <common/MsgTypes.h>
#include <common/EntityType.h>
#include <model/Vehicle/Car.h>
#include "DynamicTrackObject.h"

DynamicTrackObject::DynamicTrackObject(int32_t ID, int32_t x, int32_t y) {
    this->ID = ID;
    this->map_x = x; //Relative position on a grid
    this->map_y = y; //Relative position on a grid

    this->original_x = x;
    this->original_y = y;

    this->object_body = nullptr;
    this->object_fixture = nullptr;
    /*The real position is calculated with Box2D settings*/
}

DynamicTrackObject::DynamicTrackObject(DynamicTrackObject &&other) noexcept {
    this->ID = other.ID;
    this->map_x = other.map_x;
    this->map_y = other.map_y;
    this->original_x = other.original_x;
    this->original_y = other.original_y;
    this->object_body = other.object_body;
    this->object_fixture = other.object_fixture;

    other.object_body = nullptr;
    other.object_fixture = nullptr;
}

void DynamicTrackObject::add_to_world(b2World &world) {
    b2BodyDef body_def;
    body_def.linearDamping = 0.7f;
    body_def.angularDamping	= 0.5f;
    body_def.type = b2_dynamicBody;
    this->object_body = world.CreateBody(&body_def);

    b2PolygonShape polygon_shape;
    int32_t x_pos = this->map_x * (TILE_TERRAIN_SIZE);
    int32_t y_pos = this->map_y * (TILE_TERRAIN_SIZE);
    polygon_shape.SetAsBox(TILE_TERRAIN_SIZE/2, TILE_TERRAIN_SIZE/2);
    this->object_body->SetTransform(b2Vec2(x_pos, y_pos), 0);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 5;
    fixtureDef.friction = 1;
    fixtureDef.shape = &polygon_shape;

    this->object_body->CreateFixture(&fixtureDef);
    this->object_body->SetUserData(this); //Set a self reference to handler collisions
}

void DynamicTrackObject::collide(Body *body) {
}

int32_t DynamicTrackObject::get_ID() {
    return TYPE_DYNAMIC_OBJECT;;
}

void DynamicTrackObject::send_updates(ClientUpdater &updater) {
    int32_t x = METER_TO_PIXEL * (this->object_body->GetPosition().x - (TILE_TERRAIN_SIZE*0.5));
    int32_t y = METER_TO_PIXEL * (this->object_body->GetPosition().y - (TILE_TERRAIN_SIZE*0.5));

    std::vector<int32_t> update_info{MSG_UPDATE_ENTITY, TYPE_DYNAMIC_OBJECT, ID, x, y};

    updater.send_to_all(UpdateClient(std::move(update_info)));
}

void DynamicTrackObject::restart_position() {
    int32_t x_pos = this->original_x * TILE_TERRAIN_SIZE;
    int32_t y_pos = this->original_y * TILE_TERRAIN_SIZE;
    this->object_body->SetTransform(b2Vec2(x_pos, y_pos), 0);
}
