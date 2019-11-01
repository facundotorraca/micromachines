#include "FinishLine.h"
#include "RacingTrack.h"
#include <common/EntityType.h>
#include <common/Sizes.h>


FinishLine::FinishLine(Coordinate begin, Coordinate end, b2World& track) {
    b2BodyDef body_def;
    this->fl_body = track.CreateBody(&body_def);

    b2PolygonShape polygon_shape;
    /*Center position*/
    float x_pos = ((end.get_x() + begin.get_x())/2) * TILE_TERRAIN_SIZE;
    float y_pos = ((end.get_y() + begin.get_y())/2) * TILE_TERRAIN_SIZE;

    float length_X = (end.get_x() - begin.get_x())* TILE_TERRAIN_SIZE;
    float length_Y = (end.get_y() - begin.get_y())* TILE_TERRAIN_SIZE;

    /*If length_X == 0, the line is vertical. If length_Y == 0, line is horizontal*/
    polygon_shape.SetAsBox(length_X/2, length_Y/2, b2Vec2(x_pos, y_pos), 0);

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygon_shape;
    fixture_def.isSensor = true; /*Set fixture to contact*/
    this->fl_fixture = this->fl_body->CreateFixture(&fixture_def);
    this->fl_fixture->SetUserData(this);
}

void FinishLine::apply_effect(Body *body) {
    if (body->get_ID() == TYPE_CAR) {
        std::cout << "AUTITO PASO POR LA LINEA\n";
    }
}
