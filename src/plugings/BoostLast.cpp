//
// Created by alejo on 7/11/19.
//

#include <server/PlugingsManager.h>
#include <model/Vehicle/Car.h>

void run(PlugingsParams *params) {
    std::cout << "RUN PLUGINNG" << std::endl;
    std::cout << params->car_len << std::endl;
    for (size_t ind = 0; ind < params->car_len; ind++) {
        Car oneCar(params->cars[ind]);
        std::cout << oneCar.get_max_life() << std::endl;
        oneCar.set_max_life(5);
        params->cars[ind] = oneCar.get_specs();
    }
}

extern "C" {
    void execute(PlugingsParams *params) {
        run(params);
    }
}