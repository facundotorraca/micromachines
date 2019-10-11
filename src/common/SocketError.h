//
// Created by facundotorraca on 10/10/19.
//

#ifndef MICROMACHINES_SOCKETERROR_H
#define MICROMACHINES_SOCKETERROR_H

#include <stdexcept>

class SocketError : public std::runtime_error {
    public:
        explicit SocketError(const char* error) : runtime_error(error) {}
};

#endif //MICROMACHINES_SOCKETERROR_H
