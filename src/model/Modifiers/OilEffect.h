#ifndef MICROMACHINES_OILEFFECT_H
#define MICROMACHINES_OILEFFECT_H

#include "Effect.h"
#include "NoEffect.h"

#define OIL_EFFECT_DURATION 360 //6 sec

class OilEffect : public Effect {

    public:
        OilEffect(): Effect(0.3f, 1.0f, 1.0f, 0.7f, OIL_EFFECT_DURATION) {};

        std::unique_ptr<Effect> get_next_effect() override {
            return std::unique_ptr<Effect>(new NoEffect());
        }

        void send_effect_update(int32_t ID, ClientUpdater& updater) override {};

};


#endif //MICROMACHINES_OILEFFECT_H
