#ifndef MICROMACHINES_MODIFIER_H
#define MICROMACHINES_MODIFIER_H

#include <cstdint>
#include <common/Coordinate.h>

class Modifier {
    int32_t map_x;
    int32_t map_y;
    int32_t remaining_time;

    public:
        explicit Modifier(int32_t time_of_life, int32_t map_x, int32_t map_y) {
            this->remaining_time = time_of_life;
            this->map_x = map_x;
            this->map_y = map_y;
        }

        void update_remaining_life() {
            this->remaining_time -= 1;
        }

        bool is_dead() {
            return this->remaining_time <= 0;
        }

        Coordinate get_coordinate() {
            return {float(this->map_x), float(this->map_y), 0};
        }

};


#endif //MICROMACHINES_MODIFIER_H
