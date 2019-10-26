#ifndef MICROMACHINES_FIXTUREUSERDATA_H
#define MICROMACHINES_FIXTUREUSERDATA_H

#include <cstdint>
#include <common/EntityType.h>

class FixtureUserData {
    protected:
    int32_t type_ID;

    public:
        explicit FixtureUserData(int32_t type_ID):
            type_ID(type_ID)
        {}

        virtual int32_t get_type_ID() {
            return this->type_ID;
        }

        virtual ~FixtureUserData() = default;
};

class WheelUserData : public FixtureUserData {
    public:
        WheelUserData(): FixtureUserData(TYPE_WHEEL) {}
};

class AsphaltUserData : public FixtureUserData {
    public:
        AsphaltUserData(): FixtureUserData(TYPE_ASPHALT) {}
};

class GrassUserData : public FixtureUserData {
    public:
        GrassUserData(): FixtureUserData(TYPE_GRASS) {}
};

class DirtUserData : public FixtureUserData {
    public:
        DirtUserData(): FixtureUserData(TYPE_DIRT) {}
};

class SandUserData : public FixtureUserData {
    public:
        SandUserData(): FixtureUserData(TYPE_SAND) {}
};

#endif //MICROMACHINES_FIXTUREUSERDATA_H
