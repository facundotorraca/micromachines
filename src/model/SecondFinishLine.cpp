#include "Box2D/Box2D.h"
#include <common/Sizes.h>
#include <common/EntityType.h>
#include <model/Vehicle/Car.h>
#include "SecondFinishLine.h"

SecondFinishLine::SecondFinishLine(Coordinate begin, Coordinate end, bool &cross_first, bool &cross_second, b2World &track):
    cross_first(cross_first),
    cross_second(cross_second)
{
    b2BodyDef body_def;
    this->fl_body = track.CreateBody(&body_def);

    b2PolygonShape polygon_shape;
    /*Center position*/
    float x_pos = ((end.get_x() + begin.get_x())/2) * TILE_TERRAIN_SIZE;
    float y_pos = ((end.get_y() + begin.get_y())/2) * TILE_TERRAIN_SIZE;

    float length_X = (end.get_x() - begin.get_x())* TILE_TERRAIN_SIZE;
    float length_Y = (end.get_y() - begin.get_y())* TILE_TERRAIN_SIZE;

    /*If length_X == 0, the line is vertical. If length_Y == 0, line is horizontal*/
    float offset = TILE_TERRAIN_SIZE/2;
    if (length_X == 0)
        x_pos += offset;
    else
        y_pos +=offset;

    /*The offset is to make the line start at the tile's edge*/

    polygon_shape.SetAsBox(length_X/2, length_Y/2, b2Vec2(x_pos, y_pos), 0);

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygon_shape;
    fixture_def.isSensor = true; /*Set fixture to contact*/
    this->fl_fixture = this->fl_body->CreateFixture(&fixture_def);
    this->fl_fixture->SetUserData(this);
}

void SecondFinishLine::apply_effect(Body *body) {
    if (body->get_ID() != TYPE_CAR)
        return;
    if (this->cross_first) {
        this->cross_first = false;
        this->cross_second = false;
        ((Car*)body)->complete_lap();
    } else {
        this->cross_first = false;
        this->cross_second = true;
    }



}
