#ifndef MICROMACHINES_ASPHALTTURN_H
#define MICROMACHINES_ASPHALTTURN_H


#include <model/Terrains/Asphalt.h>

class AsphaltTurn : public Asphalt {

    public:
        AsphaltTurn(int32_t x, int32_t y, int32_t rotation);

        UpdateClient get_to_send() override;
};


#endif //MICROMACHINES_ASPHALTTURN_H
