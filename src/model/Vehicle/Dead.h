#ifndef MICROMACHINES_DEAD_H
#define MICROMACHINES_DEAD_H



#include <cstdint>
#include "CarState.h"

#define RESPAWN_TIME 90 //1.5sec

class Dead : public CarState {

    private:
        int32_t remaining_time;

    public:
        Dead() { this->remaining_time = RESPAWN_TIME; }

        bool try_respawn(Coordinate respawn_point, b2Body* car_body, std::vector<Wheel*> wheels) override {
            this->remaining_time -= 1;
            if (this->remaining_time == 0) {
                float x = respawn_point.get_x() * TILE_TERRAIN_SIZE;
                float y = respawn_point.get_y() * TILE_TERRAIN_SIZE;
                float angle = respawn_point.get_angle() * DEGTORAD;

                car_body->SetTransform(b2Vec2(x, y), angle);

                for (auto& wheel : wheels)
                    wheel->move_to(respawn_point);
                return true;
            }
            return false;
        }

        void set_respawn_position(Coordinate& car_last_track_pos, Coordinate new_position) override {}
};



#endif //MICROMACHINES_DEAD_H
