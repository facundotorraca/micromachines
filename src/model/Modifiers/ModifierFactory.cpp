#include "Oil.h"
#include "Mud.h"
#include "Fix.h"
#include "Rock.h"
#include <random>
#include "Boost.h"
#include "ModifierFactory.h"

static double get_uniform_number() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(mt);
}


ModifierFactory::ModifierFactory(ModifierProbability probability):
    probability(probability)
{}

std::shared_ptr<Modifier> ModifierFactory::get_modifier_randomly(int32_t time_of_life, int32_t map_x, int32_t map_y) {
    double rand = get_uniform_number();

    if (rand < probability.oil) {
        return std::shared_ptr<Modifier>(new Oil(time_of_life, map_x, map_y));
    }

    else if (rand < probability.oil+probability.mud) {
        return std::shared_ptr<Modifier>(new Mud(time_of_life, map_x, map_y));
    }

    else if (rand < probability.oil+probability.mud+probability.fix) {
        return std::shared_ptr<Modifier>(new Fix(time_of_life, map_x, map_y));
    }

    else if (rand < probability.oil+probability.mud+probability.fix+probability.rock) {
        return std::shared_ptr<Modifier>(new Rock(time_of_life, map_x, map_y));
    }

    else {
        return std::shared_ptr<Modifier>(new Boost(time_of_life, map_x, map_y));
    }
}

std::shared_ptr<Modifier> ModifierFactory::get_life_or_boost(int32_t time_of_life, int32_t map_x, int32_t map_y) {
    double rand = get_uniform_number();

    if (rand < 0.5)
        return std::shared_ptr<Modifier>(new Fix(time_of_life, map_x, map_y));
    else
        return std::shared_ptr<Modifier>(new Boost(time_of_life, map_x, map_y));

}
