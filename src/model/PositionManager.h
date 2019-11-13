#ifndef MICROMACHINES_POSITIONMANAGER_H
#define MICROMACHINES_POSITIONMANAGER_H

#include <cstdint>
#include <model/Vehicle/Car.h>
#include <bits/unordered_map.h>
#include <server/ClientUpdater.h>

struct Position{
    int32_t ID;
    int32_t laps;
    int32_t distance;

    bool operator <(const Position& other) const {
        if (this->laps == other.laps)
            return this->distance < other.distance;
        return this->laps < other.laps;
    }

    bool operator >(const Position& other) const {
        if (this->laps == other.laps)
            return this->distance > other.distance;
        return this->laps > other.laps;
    }
};

class PositionManager {

    std::unordered_map<int32_t, Car>& cars;
    std::unordered_map<int32_t, int32_t> positions;
    std::priority_queue<Position> positions_sorter;

    public:
        explicit PositionManager(std::unordered_map<int32_t, Car>& cars);

        int32_t get_position(int32_t ID);

        void update(LapCounter& lap_counter);

        void send_update(int32_t ID, ClientUpdater& updater);

        void get_dto_info(int32_t ID, DTO_Car &param);

        void restart();
};


#endif //MICROMACHINES_POSITIONMANAGER_H
