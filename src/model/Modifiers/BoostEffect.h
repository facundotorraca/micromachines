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

        void send_effect_update(int32_t ID, ClientUpdater& updater) override {
            UpdateClient effect_info(std::vector<int32_t>{MSG_EFFECT_BOOST, BOOST_EFFECT_DURATION/FRAMES_PER_SECOND});
            updater.send_to(ID, effect_info);
        };

};


#endif //MICROMACHINES_BOOSTEFFECT_H
