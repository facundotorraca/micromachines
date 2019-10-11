#ifndef MICROMACHINES_PROTECTEDQUEUEERROR_H
#define MICROMACHINES_PROTECTEDQUEUEERROR_H

#include <stdexcept>

class ProtectedQueueError : public std::runtime_error {
    public:
        explicit ProtectedQueueError(const char* error) : runtime_error(error) {}
};

#endif //MICROMACHINES_PROTECTEDQUEUEERROR_H
