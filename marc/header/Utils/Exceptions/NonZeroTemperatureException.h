#ifndef NONZEROTEMPERATUREEXCEPTION_H
#define NONZEROTEMPERATUREEXCEPTION_H

#include <exception>

struct NonZeroTemperatureException : public std::exception {

    const char* what() const noexcept override {
        return "First Choice Hill Climbing requires a zero temperature function";
    }

};

#endif //NONZEROTEMPERATUREEXCEPTION_H
