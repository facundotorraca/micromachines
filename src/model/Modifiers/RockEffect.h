#ifndef MICROMACHINES_ROCKEFFECT_H
#define MICROMACHINES_ROCKEFFECT_H

#include "Effect.h"
#include "NoEffect.h"

#define ROCK_EFFECT_DURATION 90 //1.5sec

class RockEffect : public Effect {

    public:
        RockEffect(): Effect(0.9f, 0.1f, 0.1f, 0.0f, ROCK_EFFECT_DURATION) {};

        std::unique_ptr<Effect> get_next_effect() override {
            return std::unique_ptr<Effect>(new NoEffect());
        }
};


#endif //MICROMACHINES_ROCKEFFECT_H
