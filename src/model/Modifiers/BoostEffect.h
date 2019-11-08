#ifndef MICROMACHINES_BOOSTEFFECT_H
#define MICROMACHINES_BOOSTEFFECT_H

#include "Effect.h"
#include "NoEffect.h"

#define BOOST_EFFECT_DURATION 360 //6 sec

class BoostEffect : public Effect {

    public:
        BoostEffect(): Effect(1.1f, 2.5f, 1.2f, 1.7f, BOOST_EFFECT_DURATION) {};

        std::unique_ptr<Effect> get_next_effect() override {
            return std::unique_ptr<Effect>(new NoEffect());
        }

};


#endif //MICROMACHINES_BOOSTEFFECT_H
