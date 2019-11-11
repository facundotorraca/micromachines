#ifndef MICROMACHINES_ALIVE_H
#define MICROMACHINES_ALIVE_H

#include "CarState.h"

#define MAX_ALLOWED_DISTANCE 2 //3 tiles

class Alive : public CarState {

    public:
        bool try_respawn(Coordinate respawn_point, b2Body* car_body, std::vector<Wheel*> wheels) override {
            return false;
        }

        bool try_explode(Coordinate last_track_point, b2Body* car_body, CarLife& life) override {
            float x_map = car_body->GetPosition().x / TILE_TERRAIN_SIZE;
            float y_map = car_body->GetPosition().y / TILE_TERRAIN_SIZE;

            Coordinate car_coordinate(x_map, y_map);
            float x_distance = car_coordinate.x_distance_with(last_track_point);
            float y_distance = car_coordinate.y_distance_with(last_track_point);

            if (x_distance >= MAX_ALLOWED_DISTANCE && y_distance >= MAX_ALLOWED_DISTANCE) {
                life.kill();
                return true;
            }
            return false;
        }

        void set_last_track_position(Coordinate& car_last_track_pos, Coordinate new_position) override {
            car_last_track_pos = new_position;
        }

};


#endif //MICROMACHINES_ALIVE_H
