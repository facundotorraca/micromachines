
#ifndef MICROMACHINES_ADDDYNAMICOBJECT_H
#define MICROMACHINES_ADDDYNAMICOBJECT_H

#include "Command.h"

class AddDynamicObject : public Command {

    int32_t ID;
    int32_t type;
    int32_t x;
    int32_t y;

    public:
        explicit AddDynamicObject(int32_t ID, int32_t type, int32_t x, int32_t y, Scenario& scenario) : Command(scenario) {
            this->ID = ID;
            this->type = type;
            this->x = x;
            this->y = y;
        }

        std::unique_ptr<Menu> apply() override{
            scenario.addDynamicObject(ID, type, x, y);
            return std::unique_ptr<Menu>();
        }

};


#endif //MICROMACHINES_ADDDYNAMICOBJECT_H
