#ifndef MICROMACHINES_OILEFFECT_H
#define MICROMACHINES_OILEFFECT_H

#include "Effect.h"
#include "NoEffect.h"
#include <common/MsgTypes.h>

#define OIL_EFFECT_DURATION 360 //6 sec

class OilEffect : public Effect {

    public:
        OilEffect(): Effect(0.3f, 1.0f, 1.0f, 0.7f, OIL_EFFECT_DURATION) {};

        std::unique_ptr<Effect> get_next_effect() override {
            return std::unique_ptr<Effect>(new NoEffect());
        }

        void send_effect_update(int32_t ID, ClientUpdater& updater) override {
            UpdateClient effect_info(std::vector<int32_t>{MSG_EFFECT_OIL, OIL_EFFECT_DURATION/FRAMES_PER_SECOND});
            updater.send_to(ID, effect_info);
        };

};


#endif //MICROMACHINES_OILEFFECT_H
