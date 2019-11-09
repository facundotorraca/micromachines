#ifndef MICROMACHINES_NOEFFECT_H
#define MICROMACHINES_NOEFFECT_H

#include <memory>
#include "Effect.h"
#include <common/Sizes.h>

class NoEffect : public Effect {

    public:
        NoEffect(): Effect(1.0f, 1.0f, 1.0f, 1.0f, INFINITE) {}

        std::unique_ptr<Effect> get_next_effect() override {
            return std::unique_ptr<Effect>(new NoEffect());
        }

        void update() override {
            this->life = INFINITE;
        }

        void send_effect_update(int32_t ID, ClientUpdater& updater) override {};

};


#endif //MICROMACHINES_NOEFFECT_H
