#ifndef MICROMACHINES_MUDEFFECT_H
#define MICROMACHINES_MUDEFFECT_H

#include "Effect.h"
#include "NoEffect.h"
#include <common/MsgTypes.h>

#define MUD_EFFECT_DURATION 180 //3sec

class MudEffect : public Effect {

    public:
        MudEffect(): Effect(1.0f, 1.0f, 1.0f, 1.0f, MUD_EFFECT_DURATION) {};

        std::unique_ptr<Effect> get_next_effect() override {
            return std::unique_ptr<Effect>(new NoEffect());
        }

        void send_effect_update(int32_t ID, ClientUpdater& updater) override {
            UpdateClient effect_info({MSG_COUNTDOWN, 1});
            updater.send_to(ID, effect_info);
        };

};


#endif //MICROMACHINES_MUDEFFECT_H
