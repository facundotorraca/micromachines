#ifndef MICROMACHINES_CARLIFE_H
#define MICROMACHINES_CARLIFE_H

#include <cstdint>

class CarLife {

    float life;
    float max_life;

    public:
        explicit CarLife(float life);

        void make_damage(float damage);

        bool is_dead();

        void restart_life();

        UpdateClient get_life_update(int32_t ID);
};


#endif //MICROMACHINES_CARLIFE_H
