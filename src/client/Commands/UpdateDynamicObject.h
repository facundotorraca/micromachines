#ifndef MICROMACHINES_UPDATEDYNAMICOBJECT_H
#define MICROMACHINES_UPDATEDYNAMICOBJECT_H

#include "Command.h"

class UpdateDynamicObject : public Command{
    int32_t ID;
    int32_t x;
    int32_t y;

    public:
        explicit UpdateDynamicObject(int32_t ID, int32_t x, int32_t y, Scenario& scenario):
        Command(scenario)
        {
            this->ID = ID;
            this->x = x;
            this->y = y;
        }

        std::unique_ptr<Menu> apply() override {
            scenario.updateDynamicObject(ID, x, y);
            return std::unique_ptr<Menu>();
        }

};


#endif //MICROMACHINES_UPDATEDYNAMICOBJECT_H
