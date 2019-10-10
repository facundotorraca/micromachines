//
// Created by facundotorraca on 9/10/19.
//
#ifndef MICROMACHINES_SOCKETACCEPTORERROR_H
#define MICROMACHINES_SOCKETACCEPTORERROR_H

#include <stdexcept>

class SocketAcceptorError : public std::runtime_error {
    public:
        explicit SocketAcceptorError(const char* error) : runtime_error(error) {}
};

#endif //MICROMACHINES_SOCKETACCEPTORERROR_H
